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


    // Different types of sprites use different shader programs. To avoid too many program rebinds,
    // multiple searches are made for the relevant sprites, for each shader program.
    auto render_sprites = [&](Resource<GLShaderProgram> &program, std::string sprite_name, bool is_depth, bool is_layer) {
        program->bind();
        glUniform1i(program->uniform_location(sprite_name), 0);
        for (unsigned int i = 0; i < sprites.size(); i++) {
            auto &sp = sprites[i];
            if (sp.is_depth != is_depth || (sp.layer != -1) != is_layer) continue;
            if (is_layer) glUniform1i(program->uniform_location("layer"), sp.layer);
            glActiveTexture(GL_TEXTURE0);
            GLenum target = is_layer ? GL_TEXTURE_2D_ARRAY : GL_TEXTURE_2D;
            glBindTexture(target, sp.texture);
            glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);
            glBindTexture(target, 0);
        }
        program->unbind();
    };

    glDisable(GL_BLEND);

    render_sprites(sprite_shader_program, "sprite", false, false);
    render_sprites(sprite_layer_shader_program, "sprite", false, true);
    render_sprites(depth_sprite_shader_program, "depth_map", true, false);
    render_sprites(depth_sprite_layer_shader_program, "depth_map", true, true);

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vao);
}

void Painting::bordered_sprite(GLuint texture, vec2 bottom_left, float width, float height, float border_width, vec4 border_color)
{
    bordered_sprite_layer(texture, bottom_left, width, height, border_width, border_color, -1);
}
void Painting::bordered_sprite_layer(GLuint texture, vec2 bottom_left, float width, float height, float border_width, vec4 border_color, int layer)
{
    std::vector<vec2> points = {bottom_left,
                                vec2(bottom_left.x()+width, bottom_left.y()),
                                vec2(bottom_left.x()+width, bottom_left.y()+height),
                                vec2(bottom_left.x(), bottom_left.y()+height),
                                bottom_left};
    chain_2D(points, border_width, border_color);
    sprite_layer(texture, bottom_left, width, height, layer);
}
void Painting::bordered_depth_sprite(GLuint texture, vec2 bottom_left, float width, float height, float border_width, vec4 border_color)
{
    bordered_depth_sprite_layer(texture, bottom_left, width, height, border_width, border_color, -1);
}
void Painting::bordered_depth_sprite_layer(GLuint texture, vec2 bottom_left, float width, float height, float border_width, vec4 border_color, int layer)
{
    std::vector<vec2> points = {bottom_left,
                                vec2(bottom_left.x()+width, bottom_left.y()),
                                vec2(bottom_left.x()+width, bottom_left.y()+height),
                                vec2(bottom_left.x(), bottom_left.y()+height),
                                bottom_left};
    chain_2D(points, border_width, border_color);
    depth_sprite_layer(texture, bottom_left, width, height, layer);
}

void Painting::sprite(GLuint texture, vec2 bottom_left, float width, float height)
{
    sprite_layer(texture, bottom_left, width, height, -1);
}
void Painting::sprite_layer(GLuint texture, vec2 bottom_left, float width, float height, int layer)
{
    sprites.push_back(SpriteRenderData(texture, bottom_left, width, height, false, layer));
}
void Painting::depth_sprite(GLuint texture, vec2 bottom_left, float width, float height)
{
    depth_sprite_layer(texture, bottom_left, width, height, -1);
}
void Painting::depth_sprite_layer(GLuint texture, vec2 bottom_left, float width, float height, int layer)
{
    sprites.push_back(SpriteRenderData(texture, bottom_left, width, height, true, layer));
}
