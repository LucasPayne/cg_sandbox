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





static const bool logging_rendering = false;
[[maybe_unused]] static void log_render(const char *format, ...)
{
    if (!logging_rendering) return;
    va_list args;
    va_start(args, format);
    printf("[graphics] ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}


void Graphics::render_drawables(ShadingModelInstance shading_model)
{
    for (auto drawable : world.entities.aspects<Drawable>()) {
        mat4x4 model_matrix = drawable->model_matrix();
        mat4x4 normal_matrix = drawable->normal_matrix();
        drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);
        drawable->geometric_material.properties.set_mat4x4("normal_matrix", normal_matrix);
        draw(drawable->geometric_material, drawable->material, shading_model);
    }
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



void Graphics::refresh_framebuffers()
{
    /*--------------------------------------------------------------------------------
        Resize, if necessary, the full-sized framebuffers (G-buffer, full-resolution screenspace post-processing)
        to be the minimum required to work with each camera.
    --------------------------------------------------------------------------------*/
    int max_res_x = 0;
    int max_res_y = 0;
    for (auto camera : world.entities.aspects<Camera>()) {
        if (camera->framebuffer.resolution_x > max_res_x) max_res_x = camera->framebuffer.resolution_x;
        if (camera->framebuffer.resolution_y > max_res_y) max_res_y = camera->framebuffer.resolution_y;
    }
    if (max_res_x != framebuffer_res_x || max_res_y != framebuffer_res_y) {
        glBindRenderbuffer(GL_RENDERBUFFER, gbuffer_depth_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, max_res_x, max_res_y);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        
        for (auto &component : gbuffer_components) {
            glBindTexture(GL_TEXTURE_2D, component.texture);
            glTexImage2D(GL_TEXTURE_2D, 0, component.internal_format, max_res_x, max_res_y, 0, component.external_format, component.type, NULL);
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        for (int i = 0; i < 2; i++) {
            glBindTexture(GL_TEXTURE_2D, post_buffers[i].texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, max_res_x, max_res_y, 0, GL_RGBA, GL_FLOAT, NULL);
            glBindTexture(GL_TEXTURE_2D, 0);
            post_buffers[i].resolution_x = max_res_x;
            post_buffers[i].resolution_y = max_res_y;
        }
        glBindTexture(GL_TEXTURE_2D, screen_buffer.texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, max_res_x, max_res_y, 0, GL_RGBA, GL_FLOAT, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        screen_buffer.resolution_x = max_res_x;
        screen_buffer.resolution_y = max_res_y;
    }
    framebuffer_res_x = max_res_x;
    framebuffer_res_y = max_res_y;
}

void Graphics::render(Aspect<Camera> camera)
{
    auto viewport = camera->viewport();

    /*--------------------------------------------------------------------------------
        Set default state
    --------------------------------------------------------------------------------*/
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    /*--------------------------------------------------------------------------------
        Render surfaces into the G-buffer.
        The G-buffer and other general framebuffers are sized such that
        all viewport ranges will have space.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_fb);
    glViewport(0, 0, viewport.w, viewport.h);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    auto sm = world.graphics.shading.shading_models.load("shaders/gbuffer/position_normal_albedo.sm");
    auto shading_model = ShadingModelInstance(sm);
    shading_model.properties.set_mat4x4("vp_matrix", camera->view_projection_matrix());
    render_drawables(shading_model);
    //---Explicitly destroy shading model.
    shading_model.properties.destroy();
    glDisable(GL_DEPTH_TEST);
    /*--------------------------------------------------------------------------------
        Lighting and rendering of surfaces using the G-buffer.
        This is the first pass that fills the target framebuffer, so will
        clear to the camera's background color first.
        Further rendering will interleave into this rendering using a blitted depth buffer.
    --------------------------------------------------------------------------------*/
    lighting(camera);
    /*--------------------------------------------------------------------------------
        Blit the G-buffer depth-buffer to the target framebuffer.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_READ_FRAMEBUFFER, gbuffer_fb);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, camera->framebuffer.id);
    glBlitFramebuffer(0, 0, viewport.w, viewport.h,
                      viewport.x, viewport.y, viewport.x+viewport.w, viewport.y+viewport.h,
                      GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /*--------------------------------------------------------------------------------
        Post-processing.
    --------------------------------------------------------------------------------*/
    depth_of_field(camera);
}

void Graphics::render()
{
    // Connect screen-cameras to the screen.
    for (auto camera : world.entities.aspects<Camera>()) {
        if (camera->rendering_to_screen) camera->framebuffer = screen_buffer;
    }
    // Resize framebuffers if necessary.
    refresh_framebuffers();

    /*--------------------------------------------------------------------------------
        Update lighting data, such as shadow maps.
    --------------------------------------------------------------------------------*/
    update_lights();
    /*--------------------------------------------------------------------------------
        Render each camera into it's framebuffer section.
    --------------------------------------------------------------------------------*/
    for (auto camera : world.entities.aspects<Camera>()) {
        render(camera);
    }

    /*--------------------------------------------------------------------------------
        Place the screen buffer in the window.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, world.screen_width, world.screen_height);
    glClearColor(0,0,0,1); // clear window background
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, screen_buffer.id);
    glBlitFramebuffer(0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // source
                      window_viewport.x, window_viewport.y, window_viewport.x+window_viewport.w, window_viewport.y+window_viewport.h, // destination
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
}



void Graphics::lighting(Aspect<Camera> camera)
{
    // Clear to background color.
    glBindFramebuffer(GL_FRAMEBUFFER, camera->framebuffer.id);
    glDisable(GL_DEPTH_TEST);
    auto viewport = camera->viewport();
    glViewport(VIEWPORT_EXPAND(viewport));
    glScissor(VIEWPORT_EXPAND(viewport));
    glEnable(GL_SCISSOR_TEST);
    glClearColor(camera->background_color.x(), camera->background_color.y(), camera->background_color.z(), camera->background_color.w());
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    directional_lights(camera);
}


void Graphics::directional_lights(Aspect<Camera> camera)
{
    auto &program = directional_light_shader_program;
    auto &filter_program = directional_light_filter_shader_program;

    auto camera_transform = camera.sibling<Transform>();

    bool first_light_pass = true; // The first pass blends differently into the framebuffer.
    for (auto light : world.entities.aspects<DirectionalLight>()) {
        auto &shadow_map = directional_light_data(light).shadow_map(camera);

        // Render the screenspace shadowing signal into a buffer.
        program->bind();

        vec3 camera_position = camera_transform->position;
        vec3 camera_forward = -camera_transform->forward();
        float near = camera->near_plane_distance;
        float far = fmin(shadow_map.distance, camera->far_plane_distance);

        // Some uniforms are shared between both passes, so using this function avoids code duplication.
        auto upload_shared_uniforms = [&](Resource<GLShaderProgram> prog) {
            glUniform3fv(prog->uniform_location("camera_position"), 1, (GLfloat *) &camera_position);
            glUniform3fv(prog->uniform_location("camera_forward"), 1, (GLfloat *) &camera_forward);
            glUniform1i(prog->uniform_location("num_frustum_segments"), shadow_map.num_frustum_segments);
            for (int i = 0; i < shadow_map.num_frustum_segments-1; i++) {
                // Compute the distances of the segment dividers in camera space, from the frustum dividers in the range [0,1].
                float t = shadow_map.frustum_segment_dividers[i];
                float frustum_segment_distance = (1-t)*near + t*far;
                auto uniform_name = std::string("frustum_segment_distances[") + std::to_string(i) + std::string("]");
                glUniform1f(prog->uniform_location(uniform_name), frustum_segment_distance);
            }
            {
                // The last "frustum segment" distance in the shader's array is the distance to the far plane.
                    auto uniform_name = std::string("frustum_segment_distances[") + std::to_string(shadow_map.num_frustum_segments-1) + std::string("]");
                glUniform1f(prog->uniform_location(uniform_name), far);
            }
            for (unsigned int i = 0; i < gbuffer_components.size(); i++) {
                auto &component = gbuffer_components[i];
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, component.texture);
                glUniform1i(prog->uniform_location(component.name), i);
            }
            glUniform3fv(prog->uniform_location("direction"), 1, (GLfloat *) &light->direction);
            glUniform3fv(prog->uniform_location("light_color"), 1, (GLfloat *) &light->color);
            glUniform1f(program->uniform_location("width"), light->width);
            for (unsigned int i = 0; i < gbuffer_components.size(); i++) {
                auto &component = gbuffer_components[i];
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, component.texture);
                glUniform1i(prog->uniform_location(component.name), i);
            }
        };

        upload_shared_uniforms(program);
        int shadow_map_slot = gbuffer_components.size();
        glActiveTexture(GL_TEXTURE0 + shadow_map_slot);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map.texture);
        glBindSampler(shadow_map_slot, shadow_map.sampler_comparison);
        glActiveTexture(GL_TEXTURE0 + shadow_map_slot+1);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map.texture);
        glBindSampler(shadow_map_slot+1, shadow_map.sampler_raw);
        glUniform1f(program->uniform_location("shadow_map_width_inv"), 1.f / shadow_map.width);
        glUniform1f(program->uniform_location("shadow_map_height_inv"), 1.f / shadow_map.height);
        glUniform1i(program->uniform_location("shadow_map_width"), shadow_map.width);
        glUniform1i(program->uniform_location("shadow_map_height"), shadow_map.height);
        glUniform1i(program->uniform_location("shadow_map"), shadow_map_slot);
        glUniform1i(program->uniform_location("shadow_map_raw"), shadow_map_slot+1);
        for (int i = 0; i < shadow_map.num_frustum_segments; i++) {
            auto uniform_name = std::string("shadow_matrices[") + std::to_string(i) + std::string("]");
            glUniformMatrix4fv(program->uniform_location(uniform_name), 1, GL_FALSE, (GLfloat *) &shadow_map.shadow_matrices[i]);
            uniform_name = std::string("box_extents[") + std::to_string(i) + std::string("]");
            glUniform3fv(program->uniform_location(uniform_name), 1, (GLfloat *) &shadow_map.box_extents[i]);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, post_buffer().id);
        glBlendFunc(GL_ONE, GL_ZERO);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(postprocessing_quad_vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        program->unbind();

        // Blend the directional light pass into the image, using a filtered shadowing signal.
        filter_program->bind();
        upload_shared_uniforms(filter_program);
        glUniform1f(filter_program->uniform_location("inv_screen_width"), 1.f / post_buffer().resolution_x);
        glUniform1f(filter_program->uniform_location("inv_screen_height"), 1.f / post_buffer().resolution_y);
        int shadow_signal_slot = gbuffer_components.size();
        glActiveTexture(GL_TEXTURE0 + shadow_signal_slot);
        glBindTexture(GL_TEXTURE_2D, post_buffer().texture);
        glUniform1i(filter_program->uniform_location("shadow"), shadow_signal_slot);

        glBindFramebuffer(GL_FRAMEBUFFER, camera->framebuffer.id);
        if (first_light_pass) {
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, // RGB
                                GL_ZERO, GL_ONE);                     // Alpha
            first_light_pass = false;
        } else {
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, // RGB
                                GL_ZERO, GL_ONE);     // Alpha
        }
        glBindVertexArray(postprocessing_quad_vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        filter_program->unbind();
    }
}



GBufferComponent &Graphics::gbuffer_component(std::string name)
{
    for (auto &component : gbuffer_components) {
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

    glGenRenderbuffers(1, &gbuffer_depth_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, gbuffer_depth_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, world.screen_width, world.screen_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, gbuffer_depth_rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "G-buffer framebuffer incomplete.\n");
        exit(EXIT_FAILURE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

    auto create_color_framebuffer = [](Framebuffer &fb) {
        GLuint &fbo = fb.id;
        GLuint &tex = fb.texture;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 256, 256, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            fprintf(stderr, "Framebuffer incomplete.\n");
            exit(EXIT_FAILURE);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    };
    create_color_framebuffer(screen_buffer);
    create_color_framebuffer(post_buffers[0]);
    create_color_framebuffer(post_buffers[1]);

    directional_light_shader_program = world.resources.add<GLShaderProgram>();
    directional_light_shader_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    directional_light_shader_program->add_shader(GLShader(FragmentShader, "shaders/deferred/directional_light.frag"));
    directional_light_shader_program->link();
    directional_light_filter_shader_program = world.resources.add<GLShaderProgram>();
    directional_light_filter_shader_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    directional_light_filter_shader_program->add_shader(GLShader(FragmentShader, "shaders/deferred/directional_light_filter.frag"));
    directional_light_filter_shader_program->link();

    depth_of_field_confusion_radius_program = world.resources.add<GLShaderProgram>();
    depth_of_field_confusion_radius_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    depth_of_field_confusion_radius_program->add_shader(GLShader(FragmentShader, "shaders/depth_of_field/depth_of_field_confusion_radius.frag"));
    depth_of_field_confusion_radius_program->link();

    depth_of_field_near_field_program = world.resources.add<GLShaderProgram>();
    depth_of_field_near_field_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    depth_of_field_near_field_program->add_shader(GLShader(FragmentShader, "shaders/depth_of_field/depth_of_field_near_field.frag"));
    depth_of_field_near_field_program->link();
}

DirectionalLightData &Graphics::directional_light_data(Aspect<DirectionalLight> light)
{
    auto iter = directional_light_data_map.find(light.ID());
    if (iter != directional_light_data_map.end()) {
        return directional_light_data_map[light.ID()];
    }
    DirectionalLightData data;
    // Initialize ...
    //-
    directional_light_data_map[light.ID()] = data;
    return directional_light_data_map[light.ID()];
}

DirectionalLightShadowMap &DirectionalLightData::shadow_map(Aspect<Camera> camera)
{
    auto iter = shadow_maps.find(camera.ID());
    if (iter != shadow_maps.end()) {
        // The shadow map already exists.
        return shadow_maps[camera.ID()];
    }
    int width = 1024;
    int height = 1024;
    int num_frustum_segments = 4;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, width, height, num_frustum_segments, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    GLuint sampler; // For use with sampler2DShadow[Array].
    glGenSamplers(1, &sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, GL_GEQUAL);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLuint sampler_raw; // For direct access of shadow map texels.
    glGenSamplers(1, &sampler_raw);
    glSamplerParameteri(sampler_raw, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glSamplerParameteri(sampler_raw, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glSamplerParameteri(sampler_raw, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glSamplerParameteri(sampler_raw, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tex, 0, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Incomplete framebuffer when initializing shadow maps.\n");
        exit(EXIT_FAILURE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    DirectionalLightShadowMap sm;
    sm.camera = camera;
    sm.width = width;
    sm.height = height;
    sm.texture = tex;
    sm.sampler_comparison = sampler;
    sm.sampler_raw = sampler_raw;
    sm.fbo = fbo;
    sm.num_frustum_segments = num_frustum_segments;
    sm.shadow_matrices = std::vector<mat4x4>(sm.num_frustum_segments);
    sm.box_extents = std::vector<vec3>(sm.num_frustum_segments);
    sm.frustum_segment_dividers = std::vector<float>(sm.num_frustum_segments-1);

    sm.distance = 20; //an arbitrarily chosen default
    if (sm.num_frustum_segments == 2) {
        // These hard-coded frustum segment dividers are chosen to be generally good while standing at ground level.
        sm.frustum_segment_dividers[0] = 0.31;
    } else if (sm.num_frustum_segments == 3) {
        sm.frustum_segment_dividers[0] = 0.2;
        sm.frustum_segment_dividers[0] = 0.5;
    } else if (sm.num_frustum_segments == 4) {
        sm.frustum_segment_dividers[0] = 0.15;
        sm.frustum_segment_dividers[1] = 0.39;
        sm.frustum_segment_dividers[2] = 0.68;
    } else {
        // Evenly spaced. This is not very good.
        for (int i = 1; i < sm.num_frustum_segments; i++) {
            float d = i/(1.f * sm.num_frustum_segments);
            sm.frustum_segment_dividers[i-1] = d;
        }
    }

    shadow_maps[camera.ID()] = sm;
    return shadow_maps[camera.ID()];
}



void Graphics::update_lights()
{
    /*--------------------------------------------------------------------------------
        Directional lights
    --------------------------------------------------------------------------------*/
    auto shadow_map_sm = shading.shading_models.load("shaders/shadows/directional_light_shadow_map.sm");
    auto shadow_map_shading_model = ShadingModelInstance(shadow_map_sm);

    // Render shadow maps.
    for (auto light : world.entities.aspects<DirectionalLight>()) {
        for (auto camera : world.entities.aspects<Camera>()) {
            auto &sm = directional_light_data(light).shadow_map(camera);
            float near = camera->near_plane_distance;
            float far = fmin(sm.distance, camera->far_plane_distance);
            // Since frustum coordinates range in z from 0 at the near plane to 1 at the far plane,
            // make a correction to a shorter frustum if the shadows have a shorter render distance.
            float distance_multiplier = (far - near) / (camera->far_plane_distance - camera->near_plane_distance);

            for (int segment = 0; segment < sm.num_frustum_segments; segment++) {
                // Bound the camera frustum section with a box, elongated in the direction of the light.
                float a = segment == 0 ? 0.f : sm.frustum_segment_dividers[segment-1];
                float b = segment == sm.num_frustum_segments-1 ? 1.f : sm.frustum_segment_dividers[segment];
                a *= distance_multiplier;
                b *= distance_multiplier;
                vec3 frustum_points[8] = {
                    camera->frustum_point(-1,-1,a),
                    camera->frustum_point(1,-1,a),
                    camera->frustum_point(1,1,a),
                    camera->frustum_point(-1,1,a),
                    camera->frustum_point(-1,-1,b),
                    camera->frustum_point(1,-1,b),
                    camera->frustum_point(1,1,b),
                    camera->frustum_point(-1,1,b),
                };

                vec3 Z = light->direction;
                // Create a frame of reference.
                // ---todo: This should be chosen to make the shadow maps denser.
                vec3 X = vec3(light->direction.x() + 1, light->direction.y() - 1, light->direction.z() + 1);
                X = (X - vec3::dot(X, Z) * Z).normalized();
                vec3 Y = vec3::cross(X, Z);
                vec3 transformed_frustum[8];
                for (int i = 0; i < 8; i++) {
                    vec3 d = frustum_points[i];
                    transformed_frustum[i] = vec3(vec3::dot(d, X), vec3::dot(d, Y), vec3::dot(d, Z));
                }
                vec3 mins = transformed_frustum[0];
                vec3 maxs = transformed_frustum[0];
                for (int i = 1; i < 8; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (transformed_frustum[i][j] < mins[j]) {
                            mins[j] = transformed_frustum[i][j];
                        } else if (transformed_frustum[i][j] > maxs[j]) {
                            maxs[j] = transformed_frustum[i][j];
                        }
                    }
                }
                // Shrink the box in X and Y, and max Z, to bound all drawables. This increases the density of the shadow map.
                vec3 drawable_maxs = mins;
                vec3 drawable_mins = maxs;
                for (auto drawable : world.entities.aspects<Drawable>()) {
                    if (!drawable->shadow_caster) continue;
                    auto s = drawable->bounding_sphere();
                    vec3 p = vec3(vec3::dot(s.origin, X),
                                  vec3::dot(s.origin, Y),
                                  vec3::dot(s.origin, Z));
                    float r = s.radius;
                    if (p + vec3(r) > mins && p - vec3(r) < maxs) {
                        for (int i = 0; i < 3; i++) {
                            if (p[i] + r > drawable_maxs[i]) drawable_maxs[i] = p[i] + r;
                            if (p[i] - r < drawable_mins[i]) drawable_mins[i] = p[i] - r;
                        }
                    }
                }
                for (int i = 0; i < 3; i++) {
                    drawable_maxs[i] = fmin(drawable_maxs[i], maxs[i]);
                    drawable_mins[i] = fmax(drawable_mins[i], mins[i]);
                }

                // Only update the bounds if there were any drawables, otherwise there will be issues with a degenerate projection.
                for (int i = 0; i < 3; i++) {
                    if (drawable_mins[i] < drawable_maxs[i]) {
                        maxs[i] = drawable_maxs[i];
                        mins[i] = drawable_mins[i];
                    }
                }
                // Extend the box to include all possible shadow casters.
                for (auto drawable : world.entities.aspects<Drawable>()) {
                    if (!drawable->shadow_caster) continue;
                    auto s = drawable->bounding_sphere();
                    vec3 p = vec3(vec3::dot(s.origin, X),
                                  vec3::dot(s.origin, Y),
                                  vec3::dot(s.origin, Z));
                    float r = s.radius;
                    // Extend the box to possible shadow casters.
                    if (p.z() - r < mins.z()) {
                        if (p.x() + r > mins.x() && p.x() - r < maxs.x() && p.y() + r > mins.y() && p.y() - r < maxs.y()) {
                            mins.z() = p.z() - r;
                        }
                    }
                }

                float width = maxs.x() - mins.x();
                float height = maxs.y() - mins.y();
                float depth = maxs.z() - mins.z();

                vec3 min_point = mins.x()*X + mins.y()*Y + mins.z()*Z;
                mat4x4 shadow_matrix = mat4x4::orthogonal_projection(0, width, 0, height, 0, depth)
                                     * mat4x4::to_rigid_frame(min_point, X, Y, Z);
                sm.shadow_matrices[segment] = shadow_matrix;
                sm.box_extents[segment] = vec3(width, height, depth);
                shadow_map_shading_model.properties.set_mat4x4("vp_matrix", shadow_matrix);


                glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
                glViewport(0, 0, sm.width, sm.height);
                glDisable(GL_SCISSOR_TEST);
                glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, sm.texture, 0, segment);
                glEnable(GL_DEPTH_TEST);
                glClear(GL_DEPTH_BUFFER_BIT);
                render_drawables(shadow_map_shading_model);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
        }
    }
    //---todo: Garbage collection. Clean up rendering data for removed lights and cameras.
    shadow_map_shading_model.properties.destroy();
}

Framebuffer Graphics::post_buffer()
{
    return post_buffers[post_buffer_flag];
}
void Graphics::swap_post()
{
    post_buffer_flag = (post_buffer_flag + 1) % 2;
}



void Graphics::depth_of_field(Aspect<Camera> camera)
{
    auto camera_transform = camera.sibling<Transform>();
    vec3 camera_position = camera_transform->position;
    vec3 camera_forward = -camera_transform->forward();

    /*--------------------------------------------------------------------------------
        Near field splitting.
    --------------------------------------------------------------------------------*/
    auto &program = depth_of_field_confusion_radius_program;
    program->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gbuffer_component("position").texture);
    glUniform1i(program->uniform_location("position"), 0);
    glUniform3fv(program->uniform_location("camera_position"), 1, (GLfloat *) &camera_position);
    glUniform3fv(program->uniform_location("camera_forward"), 1, (GLfloat *) &camera_forward);
    glUniform2fv(program->uniform_location("depth_of_field"), 1, (GLfloat *) &camera->depth_of_field);
    float focus = 0.5*camera->depth_of_field.x() + 0.5*camera->depth_of_field.y();
    glUniform1f(program->uniform_location("focus"), focus);


    auto confusion_buffer = post_buffer();
    std::cout << gbuffer_component("position").texture << "\n";
    std::cout << confusion_buffer << "\n";
    glBindFramebuffer(GL_FRAMEBUFFER, confusion_buffer.id);
    glBlendFunc(GL_ONE, GL_ZERO);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(postprocessing_quad_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    program->unbind();

    /*--------------------------------------------------------------------------------
        Near field filtering.
    --------------------------------------------------------------------------------*/
    program = depth_of_field_near_field_program;
    program->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, confusion_buffer.texture);
    glUniform1i(program->uniform_location("confusion"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, screen_buffer.texture);
    glUniform1i(program->uniform_location("image"), 1);
    glUniform1f(program->uniform_location("inv_screen_width"), 1.f / post_buffer().resolution_x);
    glUniform1f(program->uniform_location("inv_screen_height"), 1.f / post_buffer().resolution_y);

    swap_post();
    std::cout << post_buffer() << "\n";
    // glBindFramebuffer(GL_FRAMEBUFFER, post_buffer().id);
    glBindFramebuffer(GL_FRAMEBUFFER, screen_buffer.id);
    glBlendFunc(GL_ONE, GL_ZERO);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(postprocessing_quad_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, post_buffer().id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, screen_buffer.id);
    glBlitFramebuffer(0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // source
                      0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // destination
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    
    program->unbind();
}
