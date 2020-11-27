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
        drawable->geometric_material.properties.set_mat4x4("model_matrix", model_matrix);
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
            auto &shadow_map = directional_light_data(light).shadow_map(camera);

            int shadow_map_slot = gbuffer_components.size();
            glActiveTexture(GL_TEXTURE0 + shadow_map_slot);
            glBindTexture(GL_TEXTURE_2D, shadow_map.texture);
            glUniform1i(program->uniform_location("shadow_map"), shadow_map_slot);
            std::cout << "Aye " << shadow_map.shadow_matrix << "\n";
            glUniformMatrix4fv(program->uniform_location("shadow_matrix"), 1, GL_FALSE, (GLfloat *) &shadow_map.shadow_matrix);

            vec3 direction = light.sibling<Transform>()->forward();
            glUniform3fv(program->uniform_location("direction"), 1, (GLfloat *) &direction);
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
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Incomplete framebuffer when initializing shadow maps.\n");
        exit(EXIT_FAILURE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    DirectionalLightShadowMap sm;
    sm.width = width;
    sm.height = height;
    sm.texture = tex;
    sm.fbo = fbo;

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
        auto light_transform = light.sibling<Transform>();
        for (auto camera : world.entities.aspects<Camera>()) {
            auto &sm = directional_light_data(light).shadow_map(camera);
            
            // Bound the camera frustum section with a box, elongated in the direction of the light.
            float extent_a = 0;
            float extent_b = 0.01;
            vec3 frustum_points[8] = {
                camera->frustum_point(-1,-1,extent_a),
                camera->frustum_point(1,-1,extent_a),
                camera->frustum_point(1,1,extent_a),
                camera->frustum_point(-1,1,extent_a),
                camera->frustum_point(-1,-1,extent_b),
                camera->frustum_point(1,-1,extent_b),
                camera->frustum_point(1,1,extent_b),
                camera->frustum_point(-1,1,extent_b),
            };
            for (int i = 0; i < 8; i++) std::cout << frustum_points[i] << "\n";

            vec3 X = light_transform->right();
            vec3 Y = light_transform->up();
            vec3 Z = light_transform->forward();
            vec3 transformed_frustum[8];
            for (int i = 0; i < 8; i++) {
                vec3 d = frustum_points[i];
                transformed_frustum[i] = vec3(vec3::dot(d, X), vec3::dot(d, Y), vec3::dot(d, Z));
            }
            for (int i = 0; i < 8; i++) std::cout << transformed_frustum[i] << "\n";
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
            float width = maxs.x() - mins.x();
            float height = maxs.y() - mins.y();
            float depth = maxs.z() - mins.z();

            std::cout << "mins " << mins << "\n";
            std::cout << "maxs " << maxs << "\n";

            vec3 min_point = mins.x()*X + mins.y()*Y + mins.z()*Z;
            mat4x4 shadow_matrix = mat4x4::orthogonal_projection(0, width, 0, height, 0, depth)
                                 * mat4x4::to_rigid_frame(min_point, X, Y, Z);
            std::cout << shadow_matrix << "\n";
            std::cout << min_point << "\n";
            shadow_map_shading_model.properties.set_mat4x4("vp_matrix", shadow_matrix);
            sm.shadow_matrix = shadow_matrix;

            vec3 bounding_box[8];
            vec3 minsmaxs[2] = {mins, maxs};
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        vec3 p = X*minsmaxs[i].x() + Y*minsmaxs[j].y() + Z*minsmaxs[k].z();
                        bounding_box[4*i + 2*j + k] = p;
                        std::cout << shadow_matrix * vec4(p, 1) << "\n";
                    }
                }
            }

            glViewport(0, 0, sm.width, sm.height);
            glDisable(GL_SCISSOR_TEST);
            glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
            glClear(GL_DEPTH_BUFFER_BIT);
            render_drawables(shadow_map_shading_model);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(viewport_x, viewport_y, viewport_width, viewport_height); // Restore the previous viewport.
            glEnable(GL_SCISSOR_TEST);
        }
    }
    //---todo: Garbage collection. Clean up rendering data for removed lights and cameras.
    shadow_map_shading_model.properties.destroy();

    // getchar();
}
