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
    auto render_sprites = [&](Resource<GLShaderProgram> &program, bool is_depth, int mode) {
        // mode: 0: sprite
        //       1: array sprite
        //       2: cube map sprite
        program->bind();
        glUniform1i(program->uniform_location(is_depth ? "depth_map" : "sprite"), 0);
        for (unsigned int i = 0; i < sprites.size(); i++) {
            auto &sp = sprites[i];
            if (sp.is_depth != is_depth) continue;
	    if (mode == 0 && sp.layer != -1) continue;
	    if (mode == 1 && (sp.layer == -1 || sp.is_cube_map)) continue;
	    if (mode == 2 && (sp.layer == -1 || !sp.is_cube_map)) continue;
            if (sp.layer != -1) glUniform1i(program->uniform_location("layer"), sp.layer);
            GLenum target = mode == 0 ? GL_TEXTURE_2D : (mode == 1 ? GL_TEXTURE_2D_ARRAY : GL_TEXTURE_CUBE_MAP);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(target, sp.texture);
            glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);
            glBindTexture(target, 0);
        }
        program->unbind();
    };

    glDisable(GL_BLEND);

    render_sprites(sprite_program, false, 0);
    render_sprites(depth_sprite_program, true, 0);
    render_sprites(array_sprite_program, false, 1);
    render_sprites(array_depth_sprite_program, true, 1);
    render_sprites(cube_map_sprite_program, false, 2);
    render_sprites(cube_map_depth_sprite_program, true, 2);

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vao);
}


void Painting::sprite(GLuint texture, vec2 bottom_left, float width, float height)
{
    auto s = SpriteRenderData(texture, bottom_left, width, height);
    s.is_depth = false;
    s.layer = -1;
    s.is_cube_map = false;
    sprites.push_back(s);
}
void Painting::array_sprite(GLuint texture, vec2 bottom_left, float width, float height, int layer)
{
    auto s = SpriteRenderData(texture, bottom_left, width, height);
    s.is_depth = false;
    s.layer = layer;
    s.is_cube_map = false;
    sprites.push_back(s);
}
void Painting::cube_map_sprite(GLuint texture, vec2 bottom_left, float width, float height, int layer)
{
    auto s = SpriteRenderData(texture, bottom_left, width, height);
    s.is_depth = false;
    s.layer = layer;
    s.is_cube_map = true;
    sprites.push_back(s);
}

void Painting::depth_sprite(GLuint texture, vec2 bottom_left, float width, float height)
{
    auto s = SpriteRenderData(texture, bottom_left, width, height);
    s.is_depth = true;
    s.layer = -1;
    s.is_cube_map = false;
    sprites.push_back(s);
}
void Painting::array_depth_sprite(GLuint texture, vec2 bottom_left, float width, float height, int layer)
{
    auto s = SpriteRenderData(texture, bottom_left, width, height);
    s.is_depth = true;
    s.layer = layer;
    s.is_cube_map = false;
    sprites.push_back(s);
}
void Painting::cube_map_depth_sprite(GLuint texture, vec2 bottom_left, float width, float height, int layer)
{
    auto s = SpriteRenderData(texture, bottom_left, width, height);
    s.is_depth = true;
    s.layer = layer;
    s.is_cube_map = true;
    sprites.push_back(s);
}
