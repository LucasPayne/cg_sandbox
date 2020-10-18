#include "world/world.h"



void Painting::render_spheres()
{
    GLuint spheres_vao;
    glCreateVertexArrays(1, &spheres_vao);
    glBindVertexArray(spheres_vao);

    GLuint spheres_vertex_buffer;
    glGenBuffers(1, &spheres_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, spheres_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PaintingSphere) * spheres.size(), (const void *) &spheres[0], GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) 0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) offsetof(PaintingSphere, radius));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) offsetof(PaintingSphere, color));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw spheres
    spheres_shader_program->bind();
    for (auto camera : world.entities.aspects<Camera>()) {

        if (!camera->rendering_to_framebuffer) continue;
        graphics.begin_camera_rendering(camera);

        // mat4x4 vp_matrix = camera->view_projection_matrix();
        // glUniformMatrix4fv(spheres_shader_program->uniform_location("vp_matrix"), 1, GL_FALSE, (const GLfloat *) &vp_matrix);

        mat4x4 view_matrix = camera->view_matrix();
        glUniformMatrix4fv(spheres_shader_program->uniform_location("view_matrix"), 1, GL_FALSE, (const GLfloat *) &view_matrix);
        glUniformMatrix4fv(spheres_shader_program->uniform_location("projection_matrix"), 1, GL_FALSE, (const GLfloat *) &camera->projection_matrix);
        glUniform1f(spheres_shader_program->uniform_location("aspect_ratio"), camera->aspect_ratio());

        glPatchParameteri(GL_PATCH_VERTICES, 1);
        glDrawArrays(GL_PATCHES, 0, spheres.size());
        // glPointSize(10);
        // glDrawArrays(GL_POINTS, 0, spheres.size());

        graphics.end_camera_rendering(camera);
    }
    spheres_shader_program->unbind();

    glDeleteVertexArrays(1, &spheres_vao);
    glDeleteBuffers(1, &spheres_vertex_buffer);
}



void Painting::render_lines()
{
    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->rendering_to_framebuffer) continue;
        graphics.begin_camera_rendering(camera);

        lines_shader_program->bind();

        mat4x4 vp_matrix = camera->view_projection_matrix();
        glUniformMatrix4fv(lines_shader_program->uniform_location("vp_matrix"), 1, GL_FALSE, (const GLfloat *) &vp_matrix);

        for (auto &line_chain : lines) {
            glUniform4fv(lines_shader_program->uniform_location("color"), 1, (const GLfloat *) &line_chain.color);
    
            GLuint vao;
            glCreateVertexArrays(1, &vao);
            glBindVertexArray(vao);

            GLuint vertex_buffer;
            glGenBuffers(1, &vertex_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * line_chain.points.size(), (const void *) &line_chain.points[0], GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
            glEnableVertexAttribArray(0);

            glLineWidth(line_chain.width);
            glDrawArrays(GL_LINE_STRIP, 0, line_chain.points.size());

            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vertex_buffer);
        }

        graphics.end_camera_rendering(camera);
    }
}


void Painting::wireframe(SurfaceGeometry &geom, mat4x4 model_matrix, float width)
{
    struct WireframeVertexAttributes {
        vec3 position;
        int edge_is_boundary;
    };
    std::vector<WireframeVertexAttributes> vertex_attributes;
    for (auto face : geom.faces()) {
        size_t n = face.num_vertices();
        if (n == 3) {
            auto start = face.halfedge();
            auto he = start;
            do {
                auto vertex = he.vertex();
                vertex_attributes.push_back({geom.vertex_positions[vertex], 1});
                he = he.next();
            } while (he != start);
        } else if (n > 3) {
            // Create a triangle fan.
            auto start = face.halfedge();
            auto origin = start.vertex();
            auto he = start;
            bool first = true;
            do {
                auto a = he.next().vertex();
                auto b = he.next().next().vertex();
                auto c = he.next().next().next().vertex();
                int edge_is_boundary[3];
                if (first) {
                    edge_is_boundary[0] = 1;
                    edge_is_boundary[1] = 1;
                    edge_is_boundary[2] = 0;
                } else if (c == origin) {
                    edge_is_boundary[0] = 0;
                    edge_is_boundary[1] = 1;
                    edge_is_boundary[2] = 1;
                } else {
                    edge_is_boundary[0] = 0;
                    edge_is_boundary[1] = 1;
                    edge_is_boundary[2] = 0;
                }
                vertex_attributes.push_back({geom.vertex_positions[origin], edge_is_boundary[0]});
                vertex_attributes.push_back({geom.vertex_positions[a], edge_is_boundary[1]});
                vertex_attributes.push_back({geom.vertex_positions[b], edge_is_boundary[2]});
                first = false;
                he = he.next();
                if (c == origin) break;
            } while (he != start);
        }
    }
    size_t num_vertices = vertex_attributes.size();
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(WireframeVertexAttributes) * num_vertices, (const void *) &vertex_attributes[0], GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(WireframeVertexAttributes), (const void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_INT, GL_FALSE, sizeof(WireframeVertexAttributes), (const void *) offsetof(WireframeVertexAttributes, edge_is_boundary));
    glEnableVertexAttribArray(1);

    WireframeRenderData render_data;
    render_data.vao = vao;
    render_data.vertex_attribute_buffer = vertex_buffer;
    render_data.model_matrix = model_matrix;
    render_data.width = width;
    render_data.num_vertices = num_vertices;
    wireframe_render_data.push_back(render_data);
}


void Painting::render_wireframes()
{
    if (wireframe_render_data.size() == 0) return;

    wireframe_shader_program->bind();
    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->rendering_to_framebuffer) continue;
        graphics.begin_camera_rendering(camera);
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        int viewport_width = (int) viewport[2];
        int viewport_height = (int) viewport[3];

        mat4x4 vp_matrix = camera->view_projection_matrix();
        glUniformMatrix4fv(wireframe_shader_program->uniform_location("vp_matrix"), 1, GL_FALSE, (const GLfloat *) &vp_matrix);

        for (auto render_data : wireframe_render_data) {
            glUniformMatrix4fv(wireframe_shader_program->uniform_location("model_matrix"), 1, GL_FALSE, (const GLfloat *) &render_data.model_matrix);
            glUniform1f(wireframe_shader_program->uniform_location("half_width"), 0.5 * render_data.width);
            glUniform1i(wireframe_shader_program->uniform_location("viewport_width"), viewport_width);
            glUniform1i(wireframe_shader_program->uniform_location("viewport_height"), viewport_height);
            glBindVertexArray(render_data.vao);

            glDrawArrays(GL_TRIANGLES, 0, render_data.num_vertices);
        }
        graphics.end_camera_rendering(camera);
    }
    wireframe_shader_program->unbind();

    glBindVertexArray(0);
}



void Painting::render()
{
    render_spheres();
    render_lines();
    render_wireframes();
    render_circles();
}


void Painting::clear()
{
    spheres.clear();
    lines.clear();

    for (auto render_data : wireframe_render_data) {
        glDeleteVertexArrays(1, &render_data.vao);
        glDeleteBuffers(1, &render_data.vertex_attribute_buffer);
        glDeleteBuffers(1, &render_data.triangle_index_buffer);
    }
    wireframe_render_data.clear();
    circle_buffer.clear();
    circle_positions.clear();
}


void Painting::sphere(vec3 position, float radius, vec4 color)
{
    spheres.push_back(PaintingSphere(position, radius, color));
}

void Painting::chain(std::vector<vec3> &points, float width, vec4 color)
{
    lines.push_back(PaintingLines(points, width, color));
}

void Painting::bspline(Aspect<Camera> camera, int degree, std::vector<vec2> positions, std::vector<float> knots, float width, vec4 color)
{
    // The B-spline is immediately rendered.
    int m = knots.size()-1; // The knot vector is U = { u_0,...,u_m }
    int n = positions.size(); // Number of control points.
    int num_patches = n - degree; // Number of patches to renders == number of index windows to create.
    assert(m - degree == n); // Make sure that the knot vector has the correct length.
    int patch_num_vertices = degree + 1; // Number of points that determine a patch.

    // Data initialization.
    //------------------------------------------------------------
    // Use the smallest type of index possible.
    int index_bytes;
    GLenum index_type;
    if (n-1 <= 0xFF) {
        index_bytes = 1;
        index_type = GL_UNSIGNED_BYTE;
    } else if (n-1 <= 0xFFFF) {
        index_bytes = 2;
        index_type = GL_UNSIGNED_SHORT;
    } else {
        // It is assumed that 32 bits will be sufficient, so no check is made.
        index_bytes = 4;
        index_type = GL_UNSIGNED_INT;
    }
    // Create the index array, consisting of windows of patch_num_vertices indices.
    // For example, if n == 5 and degree == 2, then (012, 123, 234) is created.
    std::vector<uint8_t> index_array_bytes(patch_num_vertices * index_bytes * num_patches);
    for (int i = 0; i < num_patches; i++) {
        for (int j = 0; j < patch_num_vertices; j++) {
            if (index_bytes == 1) {
                index_array_bytes[patch_num_vertices*i + j] = i + j;
            } else if (index_bytes == 2) {
                *((uint16_t *) &index_array_bytes[patch_num_vertices*i + j]) = i + j;
            } else {
                *((uint32_t *) &index_array_bytes[patch_num_vertices*i + j]) = i + j;
            }
        }
    }

    // GPU data upload.
    //------------------------------------------------------------
    // Create vertex array.
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * n, (const void *) &positions[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, patch_num_vertices * index_bytes * num_patches, (const void *) &index_array_bytes[0], GL_DYNAMIC_DRAW);

    // Upload 1D texture of knots.
    GLuint knot_texture_buffer;
    glGenBuffers(1, &knot_texture_buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, knot_texture_buffer);
    glBufferData(GL_TEXTURE_BUFFER, (m+1)*sizeof(float), (const void *) &knots[0], GL_DYNAMIC_DRAW);

    GLuint knot_texture;
    glGenTextures(1, &knot_texture);
    glBindTexture(GL_TEXTURE_BUFFER, knot_texture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, knot_texture_buffer);

    // Rendering.
    //------------------------------------------------------------
    graphics.begin_camera_rendering(camera);
    glDisable(GL_DEPTH_TEST);
    const bool test_primitive_lines = false;
    if (test_primitive_lines) {
        primitive_lines_2D_shader_program->bind();
        glLineWidth(4);
        glDrawArrays(GL_LINE_STRIP, 0, positions.size());
        glUniform4f(primitive_lines_2D_shader_program->uniform_location("color"), 0.5,0.5,0.5,0.45);
        primitive_lines_2D_shader_program->unbind();
    }

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int viewport_width = (int) viewport[2];
    int viewport_height = (int) viewport[3];

    Resource<GLShaderProgram> programs[2] = {bspline_2D_fillets_shader_programs[degree], bspline_2D_shader_programs[degree]};
    for (int i = 0; i < 2; i++) {
        auto &program = programs[i];
        program->bind();
        glUniform4fv(program->uniform_location("color"), 1, (const GLfloat *) &color);
        glUniform1i(program->uniform_location("knots"), 0);
        glUniform1f(program->uniform_location("half_width"), 0.5*width);
        glUniform1f(program->uniform_location("viewport_height_over_width"), camera->aspect_ratio()); //note: Currently aspect ratios are height/width.
        glUniform1f(program->uniform_location("inv_viewport_width_squared"), 1.0 / (viewport_width * viewport_width));
        glUniform1f(program->uniform_location("inv_viewport_height_squared"), 1.0 / (viewport_height * viewport_height));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_BUFFER, knot_texture);

        glPatchParameteri(GL_PATCH_VERTICES, 3);
        glLineWidth(10);
        glDrawElements(GL_PATCHES, 3*num_patches, index_type, (const void *) 0);
        program->unbind();
    }

    glEnable(GL_DEPTH_TEST); // note: Assuming this was on before.
    graphics.end_camera_rendering(camera);

    // Cleanup.
    //------------------------------------------------------------
    glDeleteBuffers(1, &index_buffer);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &knot_texture);
    glDeleteBuffers(1, &knot_texture_buffer);
}


void Painting::quadratic_bspline(Aspect<Camera> camera, std::vector<vec2> positions, std::vector<float> knots, float width, vec4 color)
{
    bspline(camera, 2, positions, knots, width, color);
}


void Painting::circles(Aspect<Camera> camera, std::vector<vec2> &positions, float radius, vec4 color, float outline_width, vec4 outline_color)
{
    PaintingCircles circles;
    circles.camera = camera;
    circles.n = positions.size();
    circles.radius = radius;
    circles.color = color;
    circles.outline_width = outline_width;
    if (outline_width == 0.f) outline_color = color; //prevent antialiasing artifacts.
    circles.outline_color = outline_color;
    circle_buffer.push_back(circles);

    for (auto &v : positions) {
        circle_positions.push_back(v);
    }
}

void Painting::render_circles()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * circle_positions.size(), (const void *) &circle_positions[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
    glEnableVertexAttribArray(0);

    
    glDisable(GL_DEPTH_TEST);
    auto &program = circles_2D_shader_program;
    program->bind();
    glPatchParameteri(GL_PATCH_VERTICES, 1);
    size_t positions_index = 0;
    for (auto &circles : circle_buffer) {

        graphics.begin_camera_rendering(circles.camera);

        glUniform1f(program->uniform_location("viewport_width_over_height"), 1.0 / circles.camera->aspect_ratio());
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        int viewport_width = (int) viewport[2];
        float antialiasing_extent = 0.5 / (viewport_width * circles.radius);
        glUniform1f(program->uniform_location("antialiasing_extent"), antialiasing_extent);

        glUniform4fv(program->uniform_location("color"), 1, (const GLfloat *) &circles.color);
        glUniform1f(program->uniform_location("radius"), circles.radius);
        glUniform1f(program->uniform_location("outline_width"), circles.outline_width);
        glUniform4fv(program->uniform_location("outline_color"), 1, (const GLfloat *) &circles.outline_color);

        glDrawArrays(GL_PATCHES, positions_index, circles.n);

        positions_index += circles.n;
        graphics.end_camera_rendering(circles.camera);
    }
    program->unbind();
    glEnable(GL_DEPTH_TEST);
}


const int Painting::max_bspline_degree = 3;
void Painting::init()
{
    spheres_shader_program = world.resources.add<GLShaderProgram>();
    spheres_shader_program->add_shader(GLShader(VertexShader, "resources/painting/spheres.vert"));
    spheres_shader_program->add_shader(GLShader(TessControlShader, "resources/painting/spheres.tcs"));
    spheres_shader_program->add_shader(GLShader(TessEvaluationShader, "resources/painting/spheres.tes"));
    spheres_shader_program->add_shader(GLShader(FragmentShader, "resources/painting/spheres.frag"));
    spheres_shader_program->link();

    wireframe_shader_program = world.resources.add<GLShaderProgram>();
    wireframe_shader_program->add_shader(GLShader(VertexShader, "resources/painting/triangle_wireframe.vert"));
    wireframe_shader_program->add_shader(GLShader(GeometryShader, "resources/painting/triangle_wireframe.geom"));
    wireframe_shader_program->add_shader(GLShader(FragmentShader, "resources/painting/triangle_wireframe.frag"));
    wireframe_shader_program->link();

    for (int degree = 1; degree <= max_bspline_degree; degree++) {
        {
        auto program = world.resources.add<GLShaderProgram>();
        program->add_shader(GLShader(VertexShader, "resources/painting/bspline_2D.vert"));
        program->add_shader(GLShader(TessControlShader, "resources/painting/quadratic_bspline_2D.tcs"));
        program->add_shader(GLShader(TessEvaluationShader, "resources/painting/quadratic_bspline_2D.tes"));
        program->add_shader(GLShader(GeometryShader, "resources/painting/bspline_2D.geom"));
        program->add_shader(GLShader(FragmentShader, "resources/painting/bspline_2D.frag"));
        program->link();
        bspline_2D_shader_programs.push_back(program);
        }
        {
        auto program = world.resources.add<GLShaderProgram>();
        program->add_shader(GLShader(VertexShader, "resources/painting/bspline_2D.vert"));
        program->add_shader(GLShader(TessControlShader, "resources/painting/quadratic_bspline_2D.tcs"));
        program->add_shader(GLShader(TessEvaluationShader, "resources/painting/quadratic_bspline_2D_point_mode.tes"));
        program->add_shader(GLShader(GeometryShader, "resources/painting/bspline_2D_fillets.geom"));
        program->add_shader(GLShader(FragmentShader, "resources/painting/bspline_2D_fillets.frag"));
        program->link();
        bspline_2D_fillets_shader_programs.push_back(program);
        }
    }

    lines_shader_program = world.resources.add<GLShaderProgram>();
    lines_shader_program->add_shader(GLShader(VertexShader, "resources/painting/lines.vert"));
    lines_shader_program->add_shader(GLShader(FragmentShader, "resources/painting/lines.frag"));
    lines_shader_program->link();

    primitive_lines_2D_shader_program = world.resources.add<GLShaderProgram>();
    primitive_lines_2D_shader_program->add_shader(GLShader(VertexShader, "resources/painting/primitive_lines_2D.vert"));
    primitive_lines_2D_shader_program->add_shader(GLShader(FragmentShader, "resources/painting/primitive_lines_2D.frag"));
    primitive_lines_2D_shader_program->link();

    circles_2D_shader_program = world.resources.add<GLShaderProgram>();
    circles_2D_shader_program->add_shader(GLShader(VertexShader, "resources/painting/circles_2D.vert"));
    circles_2D_shader_program->add_shader(GLShader(TessControlShader, "resources/painting/circles_2D.tcs"));
    circles_2D_shader_program->add_shader(GLShader(TessEvaluationShader, "resources/painting/circles_2D.tes"));
    circles_2D_shader_program->add_shader(GLShader(FragmentShader, "resources/painting/circles_2D.frag"));
    circles_2D_shader_program->link();
}
