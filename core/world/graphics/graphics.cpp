#include "world/world.h"


#include "postprocessing.cpp"
#include "lighting.cpp"

std::string gl_error_string()
{
    GLenum err = glGetError();
    switch(err) {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
    }
    return "UNKNOWN";
}






void Graphics::init()
{
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    background_color = vec4(0,0,0,1);
    window_background_color = vec4(0,0,0,1);

    glEnable(GL_BLEND);
    // The standard blending mode. Remember to reset to this if changed!
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize the painting module, for 2D and 3D vector graphics.
    paint.init();

    // Set up the G-buffer.
    glGenFramebuffers(1, &gbuffer_fb);
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_fb);
    gbuffer_components = {
        GBufferComponent("position", GL_RGBA16F, GL_RGBA, GL_FLOAT),
        GBufferComponent("normal", GL_RGBA16F, GL_RGBA, GL_FLOAT),
        GBufferComponent("albedo", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE),
        GBufferComponent("velocity", GL_RGBA16F, GL_RGBA, GL_FLOAT),
    };
    std::vector<GLenum> buffer_enums(gbuffer_components.size());
    for (unsigned int i = 0; i < gbuffer_components.size(); i++) buffer_enums[i] = GL_COLOR_ATTACHMENT0 + i;
    int i = 0;
    for (auto &component : gbuffer_components) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, component.internal_format, 256, 256, 0, component.external_format, component.type, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, buffer_enums[i], GL_TEXTURE_2D, texture, 0);
        component.texture = texture;
        i += 1;
    }
    glDrawBuffers(buffer_enums.size(), &buffer_enums[0]);

    glGenRenderbuffers(1, &gbuffer_depth_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, gbuffer_depth_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 256, 256);
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
    create_color_framebuffer(post_buffer);

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

    temporal_aa_program = world.resources.add<GLShaderProgram>();
    temporal_aa_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    temporal_aa_program->add_shader(GLShader(FragmentShader, "shaders/antialiasing/temporal_quincunx.frag"));
    temporal_aa_program->link();
}


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
        if (!drawable->has_prev_model_matrix) {
            drawable->has_prev_model_matrix = true;
            drawable->prev_model_matrix = model_matrix;
        }
        mat4x4 normal_matrix = drawable->normal_matrix();
        drawable->geometric_material.properties.set_mat4x4("prev_model_matrix", drawable->prev_model_matrix);
        drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);
        drawable->geometric_material.properties.set_mat4x4("normal_matrix", normal_matrix);
        draw(drawable->geometric_material, drawable->material, shading_model);
        drawable->prev_model_matrix = model_matrix;
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
        auto viewport = camera->viewport();
        if (viewport.w > max_res_x) max_res_x = viewport.w;
        if (viewport.h > max_res_y) max_res_y = viewport.h;
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

        glBindTexture(GL_TEXTURE_2D, post_buffer.texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, max_res_x, max_res_y, 0, GL_RGBA, GL_FLOAT, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        post_buffer.resolution_x = max_res_x;
        post_buffer.resolution_y = max_res_y;
    }
    framebuffer_res_x = max_res_x;
    framebuffer_res_y = max_res_y;

    //-----only refresh when changed
    glBindTexture(GL_TEXTURE_2D, screen_buffer.texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, window_viewport.w, window_viewport.h, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    screen_buffer.resolution_x = window_viewport.w;
    screen_buffer.resolution_y = window_viewport.h;
}

void Graphics::render(Aspect<Camera> camera)
{
    auto viewport = camera->viewport();


    /*--------------------------------------------------------------------------------
        Render surfaces into the G-buffer.
        The G-buffer and other general framebuffers are sized such that
        all viewport ranges will have space.
    --------------------------------------------------------------------------------*/
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_fb);
    glViewport(0, 0, viewport.w, viewport.h);
    glScissor(0, 0, viewport.w, viewport.h);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto sm = world.graphics.shading.shading_models.load("shaders/gbuffer/position_normal_albedo_velocity.sm");
    auto shading_model = ShadingModelInstance(sm);
    mat4x4 vp_matrix = camera->view_projection_matrix();
    shading_model.properties.set_mat4x4("vp_matrix", vp_matrix);
    if (!camera->has_prev_view_projection_matrix) {
        camera->has_prev_view_projection_matrix = true;
        camera->prev_view_projection_matrix = vp_matrix;
    }
    shading_model.properties.set_mat4x4("prev_vp_matrix", camera->prev_view_projection_matrix);
    camera->prev_view_projection_matrix = vp_matrix;
    render_drawables(shading_model);
    //---Explicitly destroy shading model.
    shading_model.properties.destroy();

    /*--------------------------------------------------------------------------------
        Clear this camera's framebuffer section.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, camera->framebuffer.id);
    glEnable(GL_SCISSOR_TEST);
    glViewport(VIEWPORT_EXPAND(viewport));
    glScissor(VIEWPORT_EXPAND(viewport));
    glClearColor(VEC4_EXPAND(camera->background_color));
    glClear(GL_COLOR_BUFFER_BIT);
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
    glDisable(GL_SCISSOR_TEST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, gbuffer_fb);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, camera->framebuffer.id);
    glBlitFramebuffer(0, 0, viewport.w, viewport.h,
                      viewport.x, viewport.y, viewport.x+viewport.w, viewport.y+viewport.h,
                      GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /*--------------------------------------------------------------------------------
        Temporal anti-aliasing.
    --------------------------------------------------------------------------------*/
    // temporal_antialiasing(camera);

    /*--------------------------------------------------------------------------------
        Post-processing.
    --------------------------------------------------------------------------------*/
    // depth_of_field(camera);

    /*--------------------------------------------------------------------------------
        If the final image is in the post-processing buffer, blit it over to the
        target.
    --------------------------------------------------------------------------------*/
    if (write_post().framebuffer->id != viewport.framebuffer->id) {
        Viewport write_viewport = write_post();
        glBindFramebuffer(GL_READ_FRAMEBUFFER, write_viewport.framebuffer->id);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, viewport.framebuffer->id);
        glBlitFramebuffer(write_viewport.x, write_viewport.y, write_viewport.x+write_viewport.w, write_viewport.y+write_viewport.h,
                          viewport.x, viewport.y, viewport.x+viewport.w, viewport.y+viewport.h,
                          GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
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
        Clear the screen buffer.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, screen_buffer.id);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0,0, window_viewport.w, window_viewport.h);
    glClearColor(VEC4_EXPAND(background_color));
    glClear(GL_COLOR_BUFFER_BIT);

    // /*--------------------------------------------------------------------------------
    //     Update lighting data, such as shadow maps.
    // --------------------------------------------------------------------------------*/
    update_lights();

    // /*--------------------------------------------------------------------------------
    //     Render each camera into it's framebuffer section.
    // --------------------------------------------------------------------------------*/
    for (auto camera : world.entities.aspects<Camera>()) {
        render(camera);
    }
    // /*--------------------------------------------------------------------------------
    //     Render 2D and 3D vector graphics.
    // --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, screen_buffer.id);
    glEnable(GL_SCISSOR_TEST);
    glViewport(0, 0, window_viewport.w, window_viewport.h);
    glScissor(0, 0, window_viewport.w, window_viewport.h);
    paint.render();
    paint.clear();

    /*--------------------------------------------------------------------------------
        Place the screen buffer in the window.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, window_width, window_height);
    glClearColor(VEC4_EXPAND(window_background_color));
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, screen_buffer.id);
    glBlitFramebuffer(0,0, window_viewport.w, window_viewport.h, // source: screen buffer
                      window_viewport.x, window_viewport.y, window_viewport.x+window_viewport.w, window_viewport.y+window_viewport.h, // destination: default buffer
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
}






GBufferComponent &Graphics::gbuffer_component(std::string name)
{
    for (auto &component : gbuffer_components) {
        if (component.name == name) return component;
    }
    fprintf(stderr, "\"%s\" is not the name of a G-buffer component.\n", name.c_str());
    exit(EXIT_FAILURE);
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




