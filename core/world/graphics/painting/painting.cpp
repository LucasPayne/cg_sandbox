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
    /*
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PaintingLine) * lines.size(), (const void *) &lines[0], GL_DYNAMIC_DRAW);

    struct LineVertexAttributes {
        vec3 position;
        
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) offsetof(PaintingLine, b));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) offsetof(PaintingLine, width));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) offsetof(PaintingLine, color));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    lines_shader_program->bind();
    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->rendering_to_framebuffer) continue;
        graphics.begin_camera_rendering(camera);

        mat4x4 view_matrix = camera->view_matrix();
        glUniformMatrix4fv(lines_shader_program->uniform_location("view_matrix"), 1, GL_FALSE, (const GLfloat *) &view_matrix);
        glUniformMatrix4fv(lines_shader_program->uniform_location("projection_matrix"), 1, GL_FALSE, (const GLfloat *) &camera->projection_matrix);
        glUniform1f(lines_shader_program->uniform_location("aspect_ratio"), camera->aspect_ratio());

        graphics.end_camera_rendering(camera);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertex_buffer);
    */
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
}


void Painting::sphere(vec3 position, float radius, vec4 color)
{
    spheres.push_back(PaintingSphere(position, radius, color));
}

void Painting::line(vec3 a, vec3 b, float width, vec4 color)
{
    lines.push_back(PaintingLine(a, b, width, color));
}


void Painting::quadratic_bspline(Aspect<Camera> camera, std::vector<vec2> positions, std::vector<float> knots, float width, vec4 color)
{
    // The B-spline is immediately rendered.
    int m = knots.length()-1; // The knot vector is U = { u_0,...,u_m }
    int n = positions.length(); // Number of control points.
    int num_patches = n - 2; // Number of patches to renders == number of index windows to create.
    assert(m - 2 == n); // Make sure that the knot vector has the correct length.

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
        index_bytes = GL_UNSIGNED_SHORT;
    } else {
        // It is assumed that 32 bits will be sufficient, so no check is made.
        index_bytes = 4;
        index_bytes = GL_UNSIGNED_INT;
    }
    // Create the index array, consisting of windows of three indices.
    // For example, if n == 5, then (012, 123, 234) is created.
    std::vector<uint8_t> index_array_bytes(3 * index_bytes * num_patches);
    for (int i = 0; i < num_patches; i++) {
        for (int j = 0; j < 3; j++) {
            if (index_bytes == 1) {
                index_array_bytes[3*i + j] = i + j;
            } else if (index_bytes == 2) {
                *((uint16_t *) &index_array_bytes[3*i + j]) = i + j;
            } else {
                *((uint32_t *) &index_array_bytes[3*i + j]) = i + j;
            }
        }
    }

    // // Convert the knot vector into knot span lengths.
    // std::vector<float> knot_span_lengths(m);
    // for (int i = 0; i < m; i++) {
    //     knot_span_lengths[i] = knots[i+1] - knots[i];
    // }

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

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * index_bytes * num_patches, (const void *) &index_array_bytes[0], GL_DYNAMIC_DRAW);

    // Upload 1D texture of knots.
    GLuint knot_texture_buffer;
    glGenBuffers(1, &knot_texture_buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, knot_texture_buffer);
    glBufferData(GL_TEXTURE_BUFFER, (m+1)*sizeof(float), (const void *) &knots[0], GL_DYNAMIC_DRAW);

    GLuint knot_texture;
    glGenTextures(1, &knot_texture);
    glBindTexture(GL_TEXTURE_BUFFER, knot_texture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, knot_texture_buffer);
    glTexParameteri(GL_TEXTURE_BUFFER, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_BUFFER, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Rendering.
    //------------------------------------------------------------
    quadratic_bspline_2D_shader_program->bind();

    glUniform4fv(quadratic_bspline_2D_shader_program->uniform_location("color"), (const GLfloat *) &color);
    glUniform1f(quadratic_bspline_2D_shader_program->uniform_location("inv_num_patches"), 1.0 / num_patches);

    graphics.begin_camera_rendering(camera);

    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glDrawElements(GL_PATCHES, num_patches, index_type, (const void *) 0);

    graphics.end_camera_rendering(camera);
    quadratic_bspline_2D_shader_program->unbind();

    // Cleanup.
    //------------------------------------------------------------
    glDeleteBuffers(1, &index_buffer);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &knot_texture);
    glDeleteBuffers(1, &knot_texture_buffer);
}



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

    quadratic_bspline_2D_shader_program = world.resources.add<GLShaderProgram>();
    quadratic_bspline_2D_shader_program->add_shader(GLShader(VertexShader, "resources/painting/bspline_2D.vert"));
    quadratic_bspline_2D_shader_program->add_shader(GLShader(TessControlShader, "resources/painting/quadratic_bspline_2D.tcs"));
    quadratic_bspline_2D_shader_program->add_shader(GLShader(TessEvaluationShader, "resources/painting/quadratic_bspline_2D.tes"));
    quadratic_bspline_2D_shader_program->add_shader(GLShader(FragmentShader, "resources/painting/bspline_2D.frag"));
    quadratic_bspline_2D_shader_program->link();
}
