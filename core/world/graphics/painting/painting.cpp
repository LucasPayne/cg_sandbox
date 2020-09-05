#include "world/world.h"


void Painting::render()
{
    printf("rendering spheres.\n");

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

    for (auto sphere : spheres) {
        std::cout << sphere.position << "\n";
    }
    // Draw spheres
    spheres_shader_program->bind();
    for (auto camera : world.entities.aspects<Camera>()) {

        if (!camera->rendering_to_framebuffer) continue;
        graphics.begin_camera_rendering(camera);

        mat4x4 vp_matrix = camera->view_projection_matrix();
        glUniformMatrix4fv(spheres_shader_program->uniform_location("vp_matrix"), 1, GL_FALSE, (const GLfloat *) &vp_matrix);

        // glPatchParameteri(GL_PATCH_VERTICES, 1);
        // glDrawArrays(GL_PATCHES, 0, spheres.size());
        glPointSize(10);
        glDrawArrays(GL_POINTS, 0, spheres.size());

        graphics.end_camera_rendering(camera);
    }
    spheres_shader_program->unbind();

    glDeleteVertexArrays(1, &spheres_vao);
    glDeleteBuffers(1, &spheres_vertex_buffer);
    
}


void Painting::clear()
{
    spheres.clear();
}


void Painting::sphere(vec3 position, float radius, vec4 color)
{
    spheres.push_back(PaintingSphere(position, radius, color));
}


void Painting::init()
{
    spheres_shader_program = world.resources.add<GLShaderProgram>();
    spheres_shader_program->add_shader(GLShader(VertexShader, "resources/painting/spheres.vert"));
    spheres_shader_program->add_shader(GLShader(FragmentShader, "resources/painting/spheres.frag"));
    spheres_shader_program->link();
}
