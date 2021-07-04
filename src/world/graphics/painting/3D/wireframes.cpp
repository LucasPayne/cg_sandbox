#include "world/world.h"
#include "mesh_processing/mesh_processing.h"


void Painting::wireframe(SurfaceGeometry &geom, mat4x4 model_matrix, float width)
{
    struct WireframeVertexAttributes {
        vec_t position;
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


void Painting::render_wireframes(Aspect<Camera> camera)
{
    if (wireframe_render_data.size() == 0) return;
    auto viewport = camera->viewport();

    wireframe_shader_program->bind();
    mat4x4 vp_matrix = camera->view_projection_matrix();
    glUniformMatrix4fv(wireframe_shader_program->uniform_location("vp_matrix"), 1, GL_FALSE, (const GLfloat *) &vp_matrix);

    for (auto render_data : wireframe_render_data) {
        glUniformMatrix4fv(wireframe_shader_program->uniform_location("model_matrix"), 1, GL_FALSE, (const GLfloat *) &render_data.model_matrix);
        glUniform1f(wireframe_shader_program->uniform_location("half_width"), 0.5 * render_data.width);
        glUniform1i(wireframe_shader_program->uniform_location("viewport_width"), viewport.w);
        glUniform1i(wireframe_shader_program->uniform_location("viewport_height"), viewport.h);
        glBindVertexArray(render_data.vao);

        glDrawArrays(GL_TRIANGLES, 0, render_data.num_vertices);
    }
    wireframe_shader_program->unbind();

    glBindVertexArray(0);
}
