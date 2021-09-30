#include "world/world.h"

/*
    // old non-antialised line rendering
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    auto &prog = primitive_lines_shader_program;

    prog->bind();
    auto viewport = camera->viewport();

    mat4x4 vp_matrix = camera->view_projection_matrix();
    glUniformMatrix4fv(prog->uniform_location("vp_matrix"), 1, GL_FALSE, (const GLfloat *) &vp_matrix);

    for (auto &line_chain : lines) {
        glUniform4fv(prog->uniform_location("color"), 1, (const GLfloat *) &line_chain.color);
    
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
    prog->unbind();
*/

void Painting::render_lines(Aspect<Camera> camera)
{

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int viewport_width = (int) viewport[2];
    int viewport_height = (int) viewport[3];

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto mvp_matrix = camera->view_projection_matrix();


    graphics.begin_camera_rendering(camera);
    auto &prog = lines_shader_program;
    prog->bind();
    for (auto &l : lines) {
        int n = l.points.size();
        vec4 color = l.color;
        float width = l.width;

        // Create vertex array.
        GLuint vao;
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vertex_buffer;
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        
        // Duplicate each point.
        auto duplicated_points = std::vector<vec3>(2*n);
        for (int i = 0; i < n; i++) {
            duplicated_points[2*i+0] = l.points[i];
            duplicated_points[2*i+1] = l.points[i];
        }
        glBufferData(GL_ARRAY_BUFFER, 2*sizeof(vec3)*n, (const void *) &duplicated_points[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *) 0);
        glEnableVertexAttribArray(0);
    
        glUniform4fv(prog->uniform_location("color"), 1, (const GLfloat *) &color);
        glUniform1f(prog->uniform_location("half_width"), 0.5*width);
        glUniform1f(prog->uniform_location("viewport_height_over_width"), camera->aspect_ratio()); //note: Currently aspect ratios are height/width.
        glUniform1f(prog->uniform_location("inv_viewport_width_squared"), 1.0 / (viewport_width * viewport_width));
        glUniform1f(prog->uniform_location("inv_viewport_height_squared"), 1.0 / (viewport_height * viewport_height));
        glUniformMatrix4fv(prog->uniform_location("mvp_matrix"), 1, GL_FALSE, (const GLfloat *) &mvp_matrix);

        glLineWidth(10);
        glDrawArrays(GL_LINE_STRIP, 0, 2*n);

        // Cleanup.
        //------------------------------------------------------------
        glDeleteBuffers(1, &vertex_buffer);
        glDeleteVertexArrays(1, &vao);
    }
    prog->unbind();
    


    // Resource<GLShaderProgram> programs[2] = {bspline_2D_fillets_shader_programs[degree], bspline_2D_shader_programs[degree]};
    // for (int i = 0; i < 2; i++) {
    //     auto &program = programs[i];
    //     program->bind();
    //     glUniform4fv(program->uniform_location("color"), 1, (const GLfloat *) &color);
    //     glUniform1i(program->uniform_location("knots"), 0);
    //     glUniform1f(program->uniform_location("half_width"), 0.5*width);
    //     glUniform1f(program->uniform_location("viewport_height_over_width"), camera->aspect_ratio()); //note: Currently aspect ratios are height/width.
    //     glUniform1f(program->uniform_location("inv_viewport_width_squared"), 1.0 / (viewport_width * viewport_width));
    //     glUniform1f(program->uniform_location("inv_viewport_height_squared"), 1.0 / (viewport_height * viewport_height));

    //     glActiveTexture(GL_TEXTURE0);
    //     glBindTexture(GL_TEXTURE_BUFFER, knot_texture);

    //     glPatchParameteri(GL_PATCH_VERTICES, 3);
    //     glLineWidth(10);
    //     glDrawElements(GL_PATCHES, 3*num_patches, index_type, (const void *) 0);
    //     program->unbind();
    // }

    // glEnable(GL_DEPTH_TEST); // note: Assuming this was on before.
    // graphics.end_camera_rendering(camera);

}


void Painting::chain(std::vector<vec3> &points, float width, vec4 color)
{
    lines.push_back(PaintingLines(points, width, color));
}

void Painting::line(vec3 a, vec3 b, float width, vec4 color)
{
    std::vector<vec3> points(2);
    points[0] = a;
    points[1] = b;
    lines.push_back(PaintingLines(points, width, color));
}
