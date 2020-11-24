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


void Graphics::clear_cameras()
{
    for (auto &camera : world.entities.aspects<Camera>()) {
        begin_camera_rendering(camera, true);
        end_camera_rendering(camera);
    }
}

GLint g_saved_viewport[4]; //horrible global...
void Graphics::begin_camera_rendering(Aspect<Camera> &camera, bool clear)
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
    if (clear) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < 4; i++) g_saved_viewport[i] = viewport[i]; //-Lazily using a global to restore the last viewport dimensions.

}
void Graphics::end_camera_rendering(Aspect<Camera> &camera)
{
    glDisable(GL_SCISSOR_TEST);
    glViewport(g_saved_viewport[0], g_saved_viewport[1], g_saved_viewport[2], g_saved_viewport[3]);
}


void Graphics::render_drawables(std::string sm_name)
{
    // auto sm = world.graphics.shading.shading_models.load("resources/model_test/model_test.sm");
    auto sm = world.graphics.shading.shading_models.load(sm_name);
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

        log_render("Calculating view-projection matrix...");
        // mat4x4 view_matrix = camera_transform->inverse_matrix();
        // mat4x4 vp_matrix = camera->projection_matrix * view_matrix;
        mat4x4 vp_matrix = camera->view_projection_matrix();
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



// Compile an OpenGL shader and store it in the shader cache.
Resource<GLShader> Graphics::ShaderCache::compile(const std::string &path)
{
    // Try to match the file extension to a shader type (e.g. ".vert" to vertex shader).
    const char *c_path = path.c_str();
    int path_len = strlen(c_path);
    struct ShaderExtension {
        const char *name;
        GLenum type;
    };
    static ShaderExtension extensions[5] = {
        {"vert", GL_VERTEX_SHADER},
        {"frag", GL_FRAGMENT_SHADER},
        {"geom", GL_GEOMETRY_SHADER},
        {"tes", GL_TESS_CONTROL_SHADER},
        {"tcs", GL_TESS_EVALUATION_SHADER},
    };
    GLenum shader_type = 0;
    for (unsigned int i = 0; i < sizeof(extensions)/sizeof(ShaderExtension); i++) {
        int len = strlen(extensions[i].name);
        if (path_len >= len+1 && (strcmp(strchr(c_path, '\0') - len - 1, extensions[i].name) == 0)) {
            // Matched a valid extension.
            shader_type = extensions[i].type;
            break;
        }
    }
    if (shader_type == 0) {
        fprintf(stderr, "ERROR: Graphics::ShaderCache::Compile: Failed to match extension for shader \"%s\".\n", c_path);
        exit(EXIT_FAILURE);
    }

    auto shader = world.resources.add<GLShader>();
    *shader = GLShader(shader_type, path);
    return shader;
}
// Reflect opengl_utilities classes.
DESCRIPTOR_INSTANCE(GLShader);
BEGIN_ENTRIES(GLShader)
    //...unreflected
END_ENTRIES()

DESCRIPTOR_INSTANCE(GLShaderProgram);
BEGIN_ENTRIES(GLShaderProgram)
    //...unreflected
END_ENTRIES()



void Graphics::refresh_gbuffer_textures()
{
    int w, h;
    for (auto iter : gbuffer_textures) {
        GLuint tex = iter.second;
    }
}

void Graphics::bind_gbuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_fb);
}
void Graphics::unbind_gbuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Graphics::init()
{
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    paint.init();

    // Set up G-buffer.
    // The viewport at initialization should have the dimensions of the screen, so it is used to initialize gbuffer texture size.
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    world.screen_width = viewport[2];
    world.screen_height = viewport[3];

    glGenFramebuffers(1, &gbuffer_fb);
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_fb);
    
    std::vector<std::string> buffer_names = {"position", "normal", "albedo"};
    std::vector<GLenum> buffer_internal_formats = {GL_RGBA16F, GL_RGBA16F, GL_RGBA};
    std::vector<GLenum> buffer_external_formats = {GL_RGBA, GL_RGBA, GL_RGBA};
    std::vector<GLenum> buffer_types = {GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};
    GLenum buffer_enums[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    for (unsigned int i = 0; i < buffer_names.size(); i++) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, buffer_internal_formats[i], world.screen_width, world.screen_height, 0, buffer_external_formats[i], buffer_types[i], NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, buffer_enums[i], GL_TEXTURE_2D, texture, 0);
        gbuffer_textures[buffer_names[i]] = texture;
    }
    glDrawBuffers(3, buffer_enums);

    GLuint depth_rbo;
    glGenRenderbuffers(1, &depth_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, world.screen_width, world.screen_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "G-buffer framebuffer incomplete.\n");
        exit(EXIT_FAILURE);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
