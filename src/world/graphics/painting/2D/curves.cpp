#include "world/world.h"


void Painting::bspline(Aspect<Camera> camera, int degree, std::vector<vec2> positions, std::vector<float> knots, float width, vec4 color)
{
    if (positions.size() < degree + 1) return;
    bsplines.push_back(PaintingBSpline(positions, knots, width, degree, color));
}

void Painting::render_bsplines(Aspect<Camera> camera)
{
    for (auto &_bspline : bsplines)
    {
        render_bspline(camera, _bspline);
    }
}
void Painting::render_bspline(Aspect<Camera> camera, PaintingBSpline _bspline)
{
    std::vector<vec2> &positions = _bspline.points;
    std::vector<float> &knots = _bspline.knots;
    float width = _bspline.width;
    int degree = _bspline.degree;
    vec4 color = _bspline.color;

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

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int viewport_width = (int) viewport[2];
    int viewport_height = (int) viewport[3];

    const bool test_primitive_lines = false;
    if (test_primitive_lines) {
        primitive_lines_2D_shader_program->bind();
        glLineWidth(10);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDrawArrays(GL_LINE_STRIP, 0, positions.size());
        glUniform4f(primitive_lines_2D_shader_program->uniform_location("color"), 0,0,0,0);
        primitive_lines_2D_shader_program->unbind();
    }

#if 1
    //Resource<GLShaderProgram> programs[2] = {bspline_2D_fillets_shader_programs[degree], bspline_2D_shader_programs[degree]};
    Resource<GLShaderProgram> programs[2] = {bspline_2D_shader_programs[degree]};
    //for (int i = 0; i < 2; i++) {
    for (int i = 0; i < 1; i++) {
        auto &program = programs[i];
        //auto &program = primitive_lines_2D_shader_program;
        program->bind();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //
        //
        glUniform4fv(program->uniform_location("color"), 1, (const GLfloat *) &color);
        glUniform1i(program->uniform_location("knots"), 0);
        glUniform1f(program->uniform_location("half_width"), 0.5*width);
        glUniform1f(program->uniform_location("viewport_height_over_width"), camera->aspect_ratio()); //note: Currently aspect ratios are height/width.
        glUniform1f(program->uniform_location("inv_viewport_width_squared"), 1.0 / (viewport_width * viewport_width));
        glUniform1f(program->uniform_location("inv_viewport_height_squared"), 1.0 / (viewport_height * viewport_height));
        glUniform1f(program->uniform_location("viewport_width"), viewport_width);
        glUniform1f(program->uniform_location("viewport_height"), viewport_height);
        glUniform1i(program->uniform_location("tessellation_level"), 25);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_BUFFER, knot_texture);
        glPatchParameteri(GL_PATCH_VERTICES, 3);
        glDrawElements(GL_PATCHES, 3*num_patches, index_type, (const void *) 0);
        //glDrawElements(GL_TRIANGLES, 3*num_patches, index_type, (const void *) 0);
        program->unbind();
    }
#endif

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
