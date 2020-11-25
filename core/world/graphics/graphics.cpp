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



void Graphics::clear(vec4 bg_color, vec4 fg_color)
{
    // Clearing: window clear to background color, viewport clear to the foreground color.
    glDisable(GL_SCISSOR_TEST);
    glClearColor(bg_color.x(),bg_color.y(),bg_color.z(),bg_color.w());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
    glClearColor(fg_color.x(),fg_color.y(),fg_color.z(),fg_color.w());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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


void Graphics::set_viewport(int _viewport_x, int _viewport_y, int _viewport_width, int _viewport_height)
{
    // Set the default viewport. This will be, for example, the fixed-aspect-ratio subrectangle of the window.
    viewport_x = _viewport_x;
    viewport_y = _viewport_y;
    viewport_width = _viewport_width;
    viewport_height = _viewport_height;
    glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
}

void Graphics::subviewport_begin(vec2 bottom_left, vec2 top_right)
{
    // Begin a subviewport, given in terms of screen coordinates ((0,0) bottom-left) of the default viewport.
    // After rendering into this subviewport, subviewport_end() must be called to restore the default viewport.
    float bl_x = viewport_x + floor(viewport_width * bottom_left.x());
    float bl_y = viewport_y + floor(viewport_height * bottom_left.y());
    float width = floor(viewport_width * (top_right.x() - bottom_left.x()));
    float height = floor(viewport_height * (top_right.y() - bottom_left.y()));
    glViewport(bl_x, bl_y, width, height);
    glScissor(bl_x, bl_y, width, height);
}
void Graphics::subviewport_end()
{
    glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
    glScissor(viewport_x, viewport_y, viewport_width, viewport_height);
}

void Graphics::begin_camera_rendering(Aspect<Camera> &camera, bool clear)
{
    subviewport_begin(camera->bottom_left, camera->top_right);
    if (clear) {
        glClearColor(camera->background_color.x(), camera->background_color.y(), camera->background_color.z(), camera->background_color.w());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
void Graphics::end_camera_rendering(Aspect<Camera> &camera)
{
    subviewport_end();
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
    // When the window is resized, the G-buffer texture/renderbuffer storage needs to be updated to match the default framebuffer.
    glBindRenderbuffer(GL_RENDERBUFFER, depth_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, world.screen_width, world.screen_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    for (auto &component : gbuffer_components) {
        glBindTexture(GL_TEXTURE_2D, component.texture);
        glTexImage2D(GL_TEXTURE_2D, 0, component.internal_format, world.screen_width, world.screen_height, 0, component.external_format, component.type, NULL);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Graphics::deferred_lighting()
{
    glDisable(GL_DEPTH_TEST);
    // The alpha of the default framebuffer is all one.
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, // RGB
                        GL_ZERO, GL_ONE);                     // Alpha

    glBindVertexArray(postprocessing_quad_vao);
    auto &program = directional_light_shader_program;
    program->bind();
    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->rendering_to_framebuffer) continue;
        begin_camera_rendering(camera);
        for (unsigned int i = 0; i < gbuffer_components.size(); i++) {
            auto &component = gbuffer_components[i];
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, component.texture);
            glUniform1i(program->uniform_location(component.name), i);
        }
        for (auto light : world.entities.aspects<DirectionalLight>()) {
            glUniform3fv(program->uniform_location("direction"), 1, (GLfloat *) &light->direction);
            glUniform3fv(program->uniform_location("light_color"), 1, (GLfloat *) &light->color);
            glUniform1f(program->uniform_location("width"), light->width);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, // RGB
                                GL_ZERO, GL_ONE);     // Alpha
        }
        end_camera_rendering(camera);
    }
    program->unbind();
    glBindVertexArray(0);

    // Reset to the standard blending mode.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}


GBufferComponent &Graphics::gbuffer_component(std::string name)
{
    for (auto &component : gbuffer_components) {
        std::cout << component.name << "\n";
        if (component.name == name) return component;
    }
    fprintf(stderr, "\"%s\" is not the name of a G-buffer component.\n", name.c_str());
    exit(EXIT_FAILURE);
}

void Graphics::init()
{
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    // The standard blending mode. Remember to reset to this if changed!
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize the painting module, for 2D and 3D vector graphics.
    paint.init();

    // Set up the G-buffer.
    // The viewport at initialization should have the dimensions of the screen, so it is used to initialize gbuffer texture size.
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    world.screen_width = viewport[2];
    world.screen_height = viewport[3];

    glGenFramebuffers(1, &gbuffer_fb);
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_fb);

    gbuffer_components = {GBufferComponent("position", GL_RGBA16F, GL_RGBA, GL_FLOAT),
                          GBufferComponent("normal", GL_RGBA16F, GL_RGBA, GL_FLOAT),
                          GBufferComponent("albedo", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE)};
    GLenum buffer_enums[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    int i = 0;
    for (auto &component : gbuffer_components) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, component.internal_format, world.screen_width, world.screen_height, 0, component.external_format, component.type, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, buffer_enums[i], GL_TEXTURE_2D, texture, 0);
        component.texture = texture;
        i += 1;
    }
    glDrawBuffers(3, buffer_enums);

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

    directional_light_shader_program = world.resources.add<GLShaderProgram>();
    directional_light_shader_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    directional_light_shader_program->add_shader(GLShader(FragmentShader, "shaders/deferred/directional_light.frag"));
    directional_light_shader_program->link();

    // Initialize the vertex array for the post-processing quad. This is stored on the GPU and can be used at
    // any time for post-processing effects or deferred rendering.
    vec2 ppq_data[8] = {vec2(-1,-1),vec2(0,0),
                        vec2(-1,1),vec2(0,1),
                        vec2(1,1),vec2(1,1),
                        vec2(1,-1),vec2(1,0)}; // y is flipped since the framebuffer is flipped vertically.
    glGenVertexArrays(1, &postprocessing_quad_vao);
    glBindVertexArray(postprocessing_quad_vao);
    GLuint ppq_vbo;
    glGenBuffers(1, &ppq_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ppq_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 8, (const void *) &ppq_data[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2)*2, (const void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2)*2, (const void *) sizeof(vec2));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
