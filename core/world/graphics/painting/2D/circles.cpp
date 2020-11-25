#include "world/world.h"


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
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
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
