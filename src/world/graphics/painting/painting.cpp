#include "world/world.h"


void Painting::render(Aspect<Camera> camera)
{
    glEnable(GL_DEPTH_TEST);
    render_spheres(camera);
    render_wireframes(camera);
    render_lines(camera); // needs to be rendered last because of transparency for antialiasing.

    glDepthMask(false);
    glDisable(GL_DEPTH_TEST);
    render_circles();
    render_lines_2D();
    render_sprites();
    glDepthMask(true);
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
    spheres_shader_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/spheres.vert"));
    spheres_shader_program->add_shader(GLShader(TessControlShader, RESOURCE_PATH "shaders/painting/spheres.tcs"));
    spheres_shader_program->add_shader(GLShader(TessEvaluationShader, RESOURCE_PATH "shaders/painting/spheres.tes"));
    spheres_shader_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/spheres.frag"));
    spheres_shader_program->link();

    wireframe_shader_program = world.resources.add<GLShaderProgram>();
    wireframe_shader_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/triangle_wireframe.vert"));
    wireframe_shader_program->add_shader(GLShader(GeometryShader, RESOURCE_PATH "shaders/painting/triangle_wireframe.geom"));
    wireframe_shader_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/triangle_wireframe.frag"));
    wireframe_shader_program->link();

    for (int degree = 1; degree <= max_bspline_degree; degree++) {
        {
        auto program = world.resources.add<GLShaderProgram>();
        program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/bspline_2D.vert"));
        program->add_shader(GLShader(TessControlShader, RESOURCE_PATH "shaders/painting/quadratic_bspline_2D.tcs"));
        program->add_shader(GLShader(TessEvaluationShader, RESOURCE_PATH "shaders/painting/quadratic_bspline_2D.tes"));
        program->add_shader(GLShader(GeometryShader, RESOURCE_PATH "shaders/painting/bspline_2D.geom"));
        program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/bspline_2D.frag"));
        program->link();
        bspline_2D_shader_programs.push_back(program);
        }
        {
        auto program = world.resources.add<GLShaderProgram>();
        program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/bspline_2D.vert"));
        program->add_shader(GLShader(TessControlShader, RESOURCE_PATH "shaders/painting/quadratic_bspline_2D.tcs"));
        program->add_shader(GLShader(TessEvaluationShader, RESOURCE_PATH "shaders/painting/quadratic_bspline_2D_point_mode.tes"));
        program->add_shader(GLShader(GeometryShader, RESOURCE_PATH "shaders/painting/bspline_2D_fillets.geom"));
        program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/bspline_2D_fillets.frag"));
        program->link();
        bspline_2D_fillets_shader_programs.push_back(program);
        }
    }

    primitive_lines_shader_program = world.resources.add<GLShaderProgram>();
    primitive_lines_shader_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/lines.vert"));
    primitive_lines_shader_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/lines.frag"));
    primitive_lines_shader_program->link();

    lines_shader_program = world.resources.add<GLShaderProgram>();
    lines_shader_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/lines_3D/lines_3D.vert"));
    lines_shader_program->add_shader(GLShader(GeometryShader, RESOURCE_PATH "shaders/painting/lines_3D/lines_3D.geom"));
    lines_shader_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/lines_3D/lines_3D.frag"));
    lines_shader_program->link();

    primitive_lines_2D_shader_program = world.resources.add<GLShaderProgram>();
    primitive_lines_2D_shader_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/primitive_lines_2D.vert"));
    primitive_lines_2D_shader_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/primitive_lines_2D.frag"));
    primitive_lines_2D_shader_program->link();


    circles_2D_shader_program = world.resources.add<GLShaderProgram>();
    circles_2D_shader_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/circles_2D.vert"));
    circles_2D_shader_program->add_shader(GLShader(TessControlShader, RESOURCE_PATH "shaders/painting/circles_2D.tcs"));
    circles_2D_shader_program->add_shader(GLShader(TessEvaluationShader, RESOURCE_PATH "shaders/painting/circles_2D.tes"));
    circles_2D_shader_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/circles_2D.frag"));
    circles_2D_shader_program->link();


    sprite_program = world.resources.add<GLShaderProgram>();
    sprite_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/sprite/sprite.vert"));
    sprite_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/sprite/sprite.frag"));
    sprite_program->link();
    depth_sprite_program = world.resources.add<GLShaderProgram>();
    depth_sprite_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/sprite/sprite.vert"));
    depth_sprite_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/sprite/depth_sprite.frag"));
    depth_sprite_program->link();
    array_sprite_program = world.resources.add<GLShaderProgram>();
    array_sprite_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/sprite/sprite.vert"));
    array_sprite_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/sprite/array_sprite.frag"));
    array_sprite_program->link();
    array_depth_sprite_program = world.resources.add<GLShaderProgram>();
    array_depth_sprite_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/sprite/sprite.vert"));
    array_depth_sprite_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/sprite/array_depth_sprite.frag"));
    array_depth_sprite_program->link();
    cube_map_sprite_program = world.resources.add<GLShaderProgram>();
    cube_map_sprite_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/sprite/sprite.vert"));
    cube_map_sprite_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/sprite/cube_map_sprite.frag"));
    cube_map_sprite_program->link();
    cube_map_depth_sprite_program = world.resources.add<GLShaderProgram>();
    cube_map_depth_sprite_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/painting/sprite/sprite.vert"));
    cube_map_depth_sprite_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/painting/sprite/cube_map_depth_sprite.frag"));
    cube_map_depth_sprite_program->link();
}
