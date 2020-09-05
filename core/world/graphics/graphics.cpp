#include "world/world.h"


void Graphics::draw(GeometricMaterialInstance &geometric_material_instance,
                    MaterialInstance &material_instance,
                    ShadingModelInstance &shading_model_instance)
{
    ShadingProgram *shading_program = shading.get_program(geometric_material_instance.base,
                                                          material_instance.base,
                                                          shading_model_instance.base);
    GeometricMaterial &geometric_material = *(geometric_material_instance.base);
    Material &material = *(material_instance.base);
    ShadingModel &shading_model = *(shading_model_instance.base);

    glUseProgram(shading_program->program_id);
    glBindVertexArray(geometric_material_instance.vertex_array->gl_vao_id);

    // Bind property sheets.
    // First, make sure that the data in graphics memory is up-to-date.
    // Then, bind the property sheet buffers to the reserved binding points, 0, 1, and 2.
    //     0: GeometricMaterial properties
    //     1: Material properties
    //     2: ShadingModel properties
    if (geometric_material.has_properties) {
        geometric_material_instance.properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, geometric_material_instance.properties.buffer_id);
    }
    if (material.has_properties) {
        material_instance.properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, material_instance.properties.buffer_id);
    }
    if (shading_model.has_properties) {
        shading_model_instance.properties.synchronize();
        glBindBufferBase(GL_UNIFORM_BUFFER, 2, shading_model_instance.properties.buffer_id);
    }

    GLenum primitive_type = geometric_material_instance.base->primitive;
    VertexArrayLayout &layout = geometric_material_instance.vertex_array->layout;
    if (layout.indexed) {
        glDrawElements(primitive_type,
                       (GLsizei) layout.num_indices,
                       layout.index_type,
                       (const void *) 0);
    } else {
        glDrawArrays(primitive_type,
                     (GLint) 0,
                     (GLsizei) layout.num_vertices);
    }
    // Unbind OpenGL state.
    glUseProgram(0);
}



void Graphics::clear()
{
    float bg_color[4] = {0,0,0,0};
    float fg_color[4] = {1,1,1,1};

    // Clearing: window clear to background color, viewport clear to the foreground color.
    glClearColor(bg_color[0],bg_color[1],bg_color[2],bg_color[3]);
    glDisable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glEnable(GL_SCISSOR_TEST);
    glScissor(viewport[0], viewport[1], viewport[2], viewport[3]);
    glClearColor(fg_color[0],fg_color[1],fg_color[2],fg_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}



static const bool logging_rendering = false;
static void log_render(const char *format, ...)
{
    if (!logging_rendering) return;
    va_list args;
    va_start(args, format);
    printf("[graphics] ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}



GLint g_saved_viewport[4]; //horrible global...
void Graphics::begin_camera_rendering(Aspect<Camera> &camera)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    GLint viewport_x = viewport[0];
    GLint viewport_y = viewport[1];
    GLint viewport_width = viewport[2];
    GLint viewport_height = viewport[3];
    float bl_x = viewport_x + floor(viewport_width * camera->bottom_left[0]);
    float bl_y = viewport_y + floor(viewport_height * camera->bottom_left[1]);
    float width = floor(viewport_width * (camera->top_right[0] - camera->bottom_left[0]));
    float height = floor(viewport_height * (camera->top_right[1] - camera->bottom_left[1]));
    glViewport(bl_x, bl_y, width, height);
    glScissor(bl_x, bl_y, width, height);
    glClearColor(camera->background_color.x(), camera->background_color.y(), camera->background_color.z(), camera->background_color.w());
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < 4; i++) g_saved_viewport[i] = viewport[i]; //-Lazily using a global to restore the last viewport dimensions.

}
void Graphics::end_camera_rendering(Aspect<Camera> &camera)
{
    glDisable(GL_SCISSOR_TEST);
    glViewport(g_saved_viewport[0], g_saved_viewport[1], g_saved_viewport[2], g_saved_viewport[3]);
}


void Graphics::render_drawables()
{
    auto sm = world.graphics.shading.shading_models.load("resources/model_test/model_test.sm");
    auto shading_model = ShadingModelInstance(sm);

    // Render.
    bool any_camera = false;
    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->rendering_to_framebuffer) continue;
        any_camera = true;
        printf("[graphics] Camera rendering...\n");
        // print_entity(camera->entity());


        // Set up viewport.
        begin_camera_rendering(camera);

        log_render("Getting camera transform...");
        auto camera_transform = camera.sibling<Transform>();
        log_render("Calculating view-projection matrix...");
        mat4x4 view_matrix = camera_transform->inverse_matrix();
        mat4x4 vp_matrix = camera->projection_matrix * view_matrix;
        log_render("Uploading view-projection matrix...");
        shading_model.properties.set_mat4x4("vp_matrix", vp_matrix);

        log_render("Rendering Drawables:");
        for (auto drawable : world.entities.aspects<Drawable>()) {
            log_render("  Rendering drawable.");
            log_render("    Calculating model matrix...");
            mat4x4 model_matrix = drawable->model_matrix();
            log_render("    Uploading model matrix...");
            drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);

            log_render("    Draw.");
            draw(drawable->geometric_material, drawable->material, shading_model);
        }

        end_camera_rendering(camera);
    }
    if (!any_camera) printf("[graphics] No camera.\n"); // Make it easier to tell when the camera is not working.


    // Free the buffer holding shading model parameters (such as the projection matrix).
    shading_model.properties.destroy();
}



void Graphics::init()
{
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    paint.init();
}
