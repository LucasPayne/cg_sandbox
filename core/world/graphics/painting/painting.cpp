#include "world/world.h"


void Painting::render()
{
    glEnable(GL_DEPTH_TEST);
    render_spheres();
    render_lines();
    render_wireframes();

    glDisable(GL_DEPTH_TEST);
    render_circles();
    render_lines_2D();
    render_sprites();
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
    circle_buffer.clear();
    circle_positions.clear();
    lines_2D.clear();
    sprites.clear();
}


const int Painting::max_bspline_degree = 3;
void Painting::init()
{
    spheres_shader_program = world.resources.add<GLShaderProgram>();
    spheres_shader_program->add_shader(GLShader(VertexShader, "shaders/painting/spheres.vert"));
    spheres_shader_program->add_shader(GLShader(TessControlShader, "shaders/painting/spheres.tcs"));
    spheres_shader_program->add_shader(GLShader(TessEvaluationShader, "shaders/painting/spheres.tes"));
    spheres_shader_program->add_shader(GLShader(FragmentShader, "shaders/painting/spheres.frag"));
    spheres_shader_program->link();

    wireframe_shader_program = world.resources.add<GLShaderProgram>();
    wireframe_shader_program->add_shader(GLShader(VertexShader, "shaders/painting/triangle_wireframe.vert"));
    wireframe_shader_program->add_shader(GLShader(GeometryShader, "shaders/painting/triangle_wireframe.geom"));
    wireframe_shader_program->add_shader(GLShader(FragmentShader, "shaders/painting/triangle_wireframe.frag"));
    wireframe_shader_program->link();

    for (int degree = 1; degree <= max_bspline_degree; degree++) {
        {
        auto program = world.resources.add<GLShaderProgram>();
        program->add_shader(GLShader(VertexShader, "shaders/painting/bspline_2D.vert"));
        program->add_shader(GLShader(TessControlShader, "shaders/painting/quadratic_bspline_2D.tcs"));
        program->add_shader(GLShader(TessEvaluationShader, "shaders/painting/quadratic_bspline_2D.tes"));
        program->add_shader(GLShader(GeometryShader, "shaders/painting/bspline_2D.geom"));
        program->add_shader(GLShader(FragmentShader, "shaders/painting/bspline_2D.frag"));
        program->link();
        bspline_2D_shader_programs.push_back(program);
        }
        {
        auto program = world.resources.add<GLShaderProgram>();
        program->add_shader(GLShader(VertexShader, "shaders/painting/bspline_2D.vert"));
        program->add_shader(GLShader(TessControlShader, "shaders/painting/quadratic_bspline_2D.tcs"));
        program->add_shader(GLShader(TessEvaluationShader, "shaders/painting/quadratic_bspline_2D_point_mode.tes"));
        program->add_shader(GLShader(GeometryShader, "shaders/painting/bspline_2D_fillets.geom"));
        program->add_shader(GLShader(FragmentShader, "shaders/painting/bspline_2D_fillets.frag"));
        program->link();
        bspline_2D_fillets_shader_programs.push_back(program);
        }
    }

    lines_shader_program = world.resources.add<GLShaderProgram>();
    lines_shader_program->add_shader(GLShader(VertexShader, "shaders/painting/lines.vert"));
    lines_shader_program->add_shader(GLShader(FragmentShader, "shaders/painting/lines.frag"));
    lines_shader_program->link();

    primitive_lines_2D_shader_program = world.resources.add<GLShaderProgram>();
    primitive_lines_2D_shader_program->add_shader(GLShader(VertexShader, "shaders/painting/primitive_lines_2D.vert"));
    primitive_lines_2D_shader_program->add_shader(GLShader(FragmentShader, "shaders/painting/primitive_lines_2D.frag"));
    primitive_lines_2D_shader_program->link();

    circles_2D_shader_program = world.resources.add<GLShaderProgram>();
    circles_2D_shader_program->add_shader(GLShader(VertexShader, "shaders/painting/circles_2D.vert"));
    circles_2D_shader_program->add_shader(GLShader(TessControlShader, "shaders/painting/circles_2D.tcs"));
    circles_2D_shader_program->add_shader(GLShader(TessEvaluationShader, "shaders/painting/circles_2D.tes"));
    circles_2D_shader_program->add_shader(GLShader(FragmentShader, "shaders/painting/circles_2D.frag"));
    circles_2D_shader_program->link();


    sprite_program = world.resources.add<GLShaderProgram>();
    sprite_program->add_shader(GLShader(VertexShader, "shaders/painting/sprite/sprite.vert"));
    sprite_program->add_shader(GLShader(FragmentShader, "shaders/painting/sprite/sprite.frag"));
    sprite_program->link();
    depth_sprite_program = world.resources.add<GLShaderProgram>();
    depth_sprite_program->add_shader(GLShader(VertexShader, "shaders/painting/sprite/sprite.vert"));
    depth_sprite_program->add_shader(GLShader(FragmentShader, "shaders/painting/sprite/depth_sprite.frag"));
    depth_sprite_program->link();
    array_sprite_program = world.resources.add<GLShaderProgram>();
    array_sprite_program->add_shader(GLShader(VertexShader, "shaders/painting/sprite/sprite.vert"));
    array_sprite_program->add_shader(GLShader(FragmentShader, "shaders/painting/sprite/array_sprite.frag"));
    array_sprite_program->link();
    array_depth_sprite_program = world.resources.add<GLShaderProgram>();
    array_depth_sprite_program->add_shader(GLShader(VertexShader, "shaders/painting/sprite/sprite.vert"));
    array_depth_sprite_program->add_shader(GLShader(FragmentShader, "shaders/painting/sprite/array_depth_sprite.frag"));
    array_depth_sprite_program->link();
    cube_map_sprite_program = world.resources.add<GLShaderProgram>();
    cube_map_sprite_program->add_shader(GLShader(VertexShader, "shaders/painting/sprite/sprite.vert"));
    cube_map_sprite_program->add_shader(GLShader(FragmentShader, "shaders/painting/sprite/cube_map_sprite.frag"));
    cube_map_sprite_program->link();
    cube_map_depth_sprite_program = world.resources.add<GLShaderProgram>();
    cube_map_depth_sprite_program->add_shader(GLShader(VertexShader, "shaders/painting/sprite/sprite.vert"));
    cube_map_depth_sprite_program->add_shader(GLShader(FragmentShader, "shaders/painting/sprite/cube_map_depth_sprite.frag"));
    cube_map_depth_sprite_program->link();
}
