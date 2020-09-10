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
    };
    size_t num_vertices = geom.num_vertices();
    size_t num_faces = geom.num_faces();
    auto vertex_indices = VertexAttachment<uint32_t>(geom.mesh);
    std::vector<WireframeVertexAttributes> vertex_attributes(num_vertices);
    std::vector<uint32_t> triangle_indices(3*num_faces); //note: It will be checked later that all faces really are triangles.

    int index = 0;
    for (auto vertex : geom.vertices()) {
        vertex_indices[vertex] = index;
        vertex_attributes[index].position = geom.vertex_positions[vertex];
        index ++;
    }

    index = 0;
    for (auto face : geom.faces()) {
        assert(face.num_vertices() == 3); // currently only triangle wireframes.
        auto start = face.halfedge();
        auto he = start;
        int triangle_index = 0;
        do {
            uint32_t vertex_index = vertex_indices[he.vertex()];
            triangle_indices[3*index + triangle_index] = vertex_index;
            he = he.next();
            triangle_index ++;
        } while (start != he);
        index ++;
    }

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(WireframeVertexAttributes) * num_vertices, (const void *) &vertex_attributes[0], GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(WireframeVertexAttributes), (const void *) 0);
    glEnableVertexAttribArray(0);

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 3 * num_faces, (const void *) &triangle_indices[0], GL_DYNAMIC_DRAW);

    WireframeRenderData render_data;
    render_data.vao = vao;
    render_data.vertex_attribute_buffer = vertex_buffer;
    render_data.triangle_index_buffer = index_buffer;
    render_data.num_indices = 3*num_faces;
    render_data.model_matrix = model_matrix;
    render_data.width = width;
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

            glDrawElements(GL_TRIANGLES,
                           (GLsizei) render_data.num_indices,
                           GL_UNSIGNED_INT,
                           (const void *) 0);
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
}
