#include "world/world.h"


void Painting::render_sprites()
{
    std::vector<vec2> vertex_data(8 * sprites.size());
    for (unsigned int i = 0; i < sprites.size(); i++) {
        auto &sp = sprites[i];
        vertex_data[8*i + 0] = sp.bottom_left;
        vertex_data[8*i + 2] = vec2(sp.bottom_left.x() + sp.width, sp.bottom_left.y());
        vertex_data[8*i + 4] = vec2(sp.bottom_left.x() + sp.width, sp.bottom_left.y() + sp.height);
        vertex_data[8*i + 6] = vec2(sp.bottom_left.x(), sp.bottom_left.y() + sp.height);
        vertex_data[8*i + 1] = vec2(0,0);
        vertex_data[8*i + 3] = vec2(1,0);
        vertex_data[8*i + 5] = vec2(1,1);
        vertex_data[8*i + 7] = vec2(0,1);
    }

    for (auto v : vertex_data) std::cout << v << "\n";
    printf("!^!\n");

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * vertex_data.size(), (const void *) &vertex_data[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2)*2, (const void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2)*2, (const void *) sizeof(vec2));
    glEnableVertexAttribArray(1);

    sprite_shader_program->bind();
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(sprite_shader_program->uniform_location("sprite"), 0);
    for (unsigned int i = 0; i < sprites.size(); i++) {
        auto &sp = sprites[i];
        if (sp.is_depth) continue;
        graphics.begin_camera_rendering(sp.camera);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sp.texture);
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);
        glBindTexture(GL_TEXTURE_2D, 0);

        graphics.end_camera_rendering(sp.camera);
    }
    sprite_shader_program->unbind();

    depth_sprite_shader_program->bind();
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(depth_sprite_shader_program->uniform_location("depth_map"), 0);
    for (unsigned int i = 0; i < sprites.size(); i++) {
        auto &sp = sprites[i];
        if (!sp.is_depth) continue;
        graphics.begin_camera_rendering(sp.camera);

        glBindTexture(GL_TEXTURE_2D, sp.texture);
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

        graphics.end_camera_rendering(sp.camera);
    }
    depth_sprite_shader_program->unbind();

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vao);
}

void Painting::bordered_sprite(Aspect<Camera> camera, GLuint texture, vec2 bottom_left, float width, float height, float border_width, vec4 border_color)
{
    std::vector<vec2> points = {bottom_left,
                                vec2(bottom_left.x()+width, bottom_left.y()),
                                vec2(bottom_left.x()+width, bottom_left.y()+height),
                                vec2(bottom_left.x(), bottom_left.y()+height),
                                bottom_left};
    chain_2D(camera, points, border_width, border_color);
    sprite(camera, texture, bottom_left, width, height);
}
void Painting::bordered_depth_sprite(Aspect<Camera> camera, GLuint texture, vec2 bottom_left, float width, float height, float border_width, vec4 border_color)
{
    std::vector<vec2> points = {bottom_left,
                                vec2(bottom_left.x()+width, bottom_left.y()),
                                vec2(bottom_left.x()+width, bottom_left.y()+height),
                                vec2(bottom_left.x(), bottom_left.y()+height),
                                bottom_left};
    chain_2D(camera, points, border_width, border_color);
    depth_sprite(camera, texture, bottom_left, width, height);
}

void Painting::sprite(Aspect<Camera> camera, GLuint texture, vec2 bottom_left, float width, float height)
{
    sprites.push_back(SpriteRenderData(camera, texture, bottom_left, width, height, false));
}
void Painting::depth_sprite(Aspect<Camera> camera, GLuint texture, vec2 bottom_left, float width, float height)
{
    sprites.push_back(SpriteRenderData(camera, texture, bottom_left, width, height, true));
}
