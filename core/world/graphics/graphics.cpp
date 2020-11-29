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

void Graphics::render_drawables_to_cameras(std::string sm_name)
{
    auto sm = world.graphics.shading.shading_models.load(sm_name);
    auto shading_model = ShadingModelInstance(sm);

    // Render.
    bool any_camera = false;
    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->rendering_to_framebuffer) continue;
        any_camera = true;

        // Set up viewport.
        begin_camera_rendering(camera);
        mat4x4 vp_matrix = camera->view_projection_matrix();
        shading_model.properties.set_mat4x4("vp_matrix", vp_matrix);

        render_drawables(shading_model);
        end_camera_rendering(camera);
    }
    if (!any_camera) printf("[graphics] No camera.\n"); // Make it easier to tell when the camera is not working.


    // Free the buffer holding shading model parameters (such as the projection matrix).
    shading_model.properties.destroy();
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



void Graphics::refresh_gbuffer_textures()
{
    // When the window is resized, the G-buffer texture/renderbuffer storage needs to be updated to match the default viewport.
    glBindRenderbuffer(GL_RENDERBUFFER, gbuffer_depth_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, viewport_width, viewport_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    for (auto &component : gbuffer_components) {
        glBindTexture(GL_TEXTURE_2D, component.texture);
        glTexImage2D(GL_TEXTURE_2D, 0, component.internal_format, viewport_width, viewport_height, 0, component.external_format, component.type, NULL);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Graphics::deferred_lighting()
{
    glDisable(GL_DEPTH_TEST);

    bool first_light_pass = true;

    glBindVertexArray(postprocessing_quad_vao);
    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->rendering_to_framebuffer) continue;
        auto camera_transform = camera.sibling<Transform>();
        for (auto light : world.entities.aspects<DirectionalLight>()) {
            auto &program = directional_light_shader_program;
            program->bind();
            glBindFramebuffer(GL_FRAMEBUFFER, postprocessing_fbo);
            glBlendFunc(GL_ONE, GL_ZERO);
            glClearColor(0,0,0,0);
            glClear(GL_COLOR_BUFFER_BIT);

            vec3 camera_position = camera_transform->position;
            vec3 camera_forward = -camera_transform->forward();
            glUniform3fv(program->uniform_location("camera_position"), 1, (GLfloat *) &camera_position);
            glUniform3fv(program->uniform_location("camera_forward"), 1, (GLfloat *) &camera_forward);

            begin_camera_rendering(camera);
            for (unsigned int i = 0; i < gbuffer_components.size(); i++) {
                auto &component = gbuffer_components[i];
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, component.texture);
                glUniform1i(program->uniform_location(component.name), i);
            }

            glUniform3fv(program->uniform_location("direction"), 1, (GLfloat *) &light->direction);
            glUniform3fv(program->uniform_location("light_color"), 1, (GLfloat *) &light->color);
            glUniform1f(program->uniform_location("width"), light->width);
            auto &shadow_map = directional_light_data(light).shadow_map(camera);

            int shadow_map_slot = gbuffer_components.size();
            glActiveTexture(GL_TEXTURE0 + shadow_map_slot);
            glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map.texture);
            glBindSampler(shadow_map_slot, shadow_map.sampler_comparison);
            glActiveTexture(GL_TEXTURE0 + shadow_map_slot+1);
            glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map.texture);
            glBindSampler(shadow_map_slot+1, shadow_map.sampler_raw);

            glUniform1i(program->uniform_location("shadow_map"), shadow_map_slot);
            glUniform1i(program->uniform_location("shadow_map_raw"), shadow_map_slot+1);

            glUniform1i(program->uniform_location("num_frustum_segments"), shadow_map.num_frustum_segments);
            glUniform1f(program->uniform_location("shadow_map_width_inv"), 1.f / shadow_map.width);
            glUniform1f(program->uniform_location("shadow_map_height_inv"), 1.f / shadow_map.height);
            glUniform1i(program->uniform_location("shadow_map_width"), shadow_map.width);
            glUniform1i(program->uniform_location("shadow_map_height"), shadow_map.height);
            glUniform3fv(program->uniform_location("box_extents"), 1, (GLfloat *) &shadow_map.box_extents);

            float near = camera->near_plane_distance;
            float far = fmin(shadow_map.distance, camera->far_plane_distance);

            for (int i = 0; i < shadow_map.num_frustum_segments; i++) {
                auto uniform_name = std::string("shadow_matrices[") + std::to_string(i) + std::string("]");
                glUniformMatrix4fv(program->uniform_location(uniform_name), 1, GL_FALSE, (GLfloat *) &shadow_map.shadow_matrices[i]);
            }
            for (int i = 0; i < shadow_map.num_frustum_segments-1; i++) {
                float t = shadow_map.frustum_segment_dividers[i];
                // Compute the distances of the segment dividers in camera space, from the frustum dividers in the range [0,1].
                float frustum_segment_distance = (1-t)*near + t*far;
                auto uniform_name = std::string("frustum_segment_distances[") + std::to_string(i) + std::string("]");
                glUniform1f(program->uniform_location(uniform_name), frustum_segment_distance);
            }
            {
                // The last "frustum segment" distance in the shader's array is the distance to the far plane.
	        auto uniform_name = std::string("frustum_segment_distances[") + std::to_string(shadow_map.num_frustum_segments-1) + std::string("]");
                glUniform1f(program->uniform_location(uniform_name), far);
            }


            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            program->unbind();
            directional_light_filter_shader_program->bind();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, postprocessing_fbo_texture);
            glUniform1i(directional_light_filter_shader_program->uniform_location("lighting"), 0);
            if (first_light_pass) {
                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, // RGB
                                    GL_ZERO, GL_ONE);                     // Alpha
                first_light_pass = false;
            } else {
                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, // RGB
                                    GL_ZERO, GL_ONE);     // Alpha
            }
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            directional_light_filter_shader_program->unbind();
        }
        end_camera_rendering(camera);
    }
    glBindVertexArray(0);

    // Reset to the standard blending mode.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
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

    directional_light_shader_program = world.resources.add<GLShaderProgram>();
    directional_light_shader_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    directional_light_shader_program->add_shader(GLShader(FragmentShader, "shaders/deferred/directional_light.frag"));
    directional_light_shader_program->link();
    directional_light_filter_shader_program = world.resources.add<GLShaderProgram>();
    directional_light_filter_shader_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    directional_light_filter_shader_program->add_shader(GLShader(FragmentShader, "shaders/deferred/directional_light_filter.frag"));
    directional_light_filter_shader_program->link();

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

    // Set up framebuffer object useful for postprocessing effects.
    glGenFramebuffers(1, &postprocessing_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, postprocessing_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, postprocessing_fbo);
    glGenTextures(1, &postprocessing_fbo_texture);
    glBindTexture(GL_TEXTURE_2D, postprocessing_fbo_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, world.screen_width, world.screen_height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postprocessing_fbo_texture, 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "G-buffer framebuffer incomplete.\n");
        exit(EXIT_FAILURE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

    GLuint sampler;
    glGenSamplers(1, &sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, GL_GEQUAL);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLuint sampler_raw;
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
    sm.frustum_segment_dividers = std::vector<float>(sm.num_frustum_segments-1);
    sm.box_extents = vec3::zero();

    sm.distance = 20; //an arbitrarily chosen default
    if (sm.num_frustum_segments == 2) {
        // These hard-coded frustum segment dividers are chosen to be generally good while standing at ground level.
        sm.frustum_segment_dividers[0] = 0.31;
    } else if (sm.num_frustum_segments == 3) {
        sm.frustum_segment_dividers[0] = 0.2;
        sm.frustum_segment_dividers[0] = 0.5;
    } else if (sm.num_frustum_segments == 3) {
        sm.frustum_segment_dividers[0] = 0.1;
        sm.frustum_segment_dividers[1] = 0.3;
        sm.frustum_segment_dividers[2] = 0.6;
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
            // Since frustum coordinates are range in z from 0 at the near plane to 1 at the far plane,
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
                sm.box_extents = vec3(width, height, depth);
                shadow_map_shading_model.properties.set_mat4x4("vp_matrix", shadow_matrix);

                glViewport(0, 0, sm.width, sm.height);
                glDisable(GL_SCISSOR_TEST);
                glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
                glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, sm.texture, 0, segment);
                glClear(GL_DEPTH_BUFFER_BIT);
                render_drawables(shadow_map_shading_model);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glViewport(viewport_x, viewport_y, viewport_width, viewport_height); // Restore the previous viewport.
                glEnable(GL_SCISSOR_TEST);
            }
        }
    }
    //---todo: Garbage collection. Clean up rendering data for removed lights and cameras.
    shadow_map_shading_model.properties.destroy();
}
