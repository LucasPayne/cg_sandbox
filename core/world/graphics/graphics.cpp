#include "world/world.h"


#include "postprocessing.cpp"
#include "lighting/lighting.cpp"








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

    prev_window_viewport.w = -1; // make sure to force a refresh of the screen buffer.

    // Set up the G-buffer.
    glGenFramebuffers(1, &gbuffer_fb);
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_fb);

    gbuffer_components.clear();
    int num_color_attachments = 0;
    std::vector<GLenum> color_buffer_enums;
    auto add_gbuffer_component = [&](GBufferComponent component, bool is_depth) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, component.internal_format, 256, 256, 0, component.external_format, component.type, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);
        GLenum attachment = is_depth ? GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0 + (num_color_attachments++);
        if (!is_depth) color_buffer_enums.push_back(attachment);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);
        component.texture = texture;

        gbuffer_components.push_back(component);
    };
    add_gbuffer_component(GBufferComponent("normal", GL_RG16, GL_RG, GL_UNSIGNED_SHORT), false);
    add_gbuffer_component(GBufferComponent("albedo", GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE), false);
    add_gbuffer_component(GBufferComponent("velocity", GL_RGBA16F, GL_RGBA, GL_FLOAT), false);
    add_gbuffer_component(GBufferComponent("depth", GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT), true);
    glDrawBuffers(color_buffer_enums.size(), &color_buffer_enums[0]);

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

    auto create_framebuffer = [](Framebuffer &fb) {
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
        // Give these framebuffers depth buffers.
        GLuint &depth = fb.depth_texture;
        glGenTextures(1, &depth);
        glBindTexture(GL_TEXTURE_2D, depth);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, 256, 256, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            fprintf(stderr, "Framebuffer incomplete.\n");
            exit(EXIT_FAILURE);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    };
    create_framebuffer(screen_buffer);
    create_framebuffer(post_buffer);

    compile_shaders();
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



// Apply a function to each drawable which (approximately) intersects a given oriented box.
void Graphics::for_drawables(OrientedBox box, std::function<void(Aspect<Drawable> &)> function)
{
    // Search is currently through a flat list.
    for (auto drawable : world.entities.aspects<Drawable>()) {
        if (drawable->bounding_sphere().approx_intersects(box)) {
            function(drawable);
        }
    }
}
// ... (approximately) intersects the frustum.
void Graphics::for_drawables(Frustum frustum, std::function<void(Aspect<Drawable> &)> function)
{
    vec3 far_quad[4];
    far_quad[0] = frustum.point(-1,-1,1);
    far_quad[1] = frustum.point(1,-1,1);
    far_quad[2] = frustum.point(1,1,1);
    far_quad[3] = frustum.point(-1,1,1);
    vec3 points[6];
    vec3 normals[6];
    points[0] = frustum.point(-1,-1,0);
    points[1] = frustum.point(1,-1,0);
    points[2] = frustum.point(1,1,0);
    points[3] = frustum.point(-1,1,0);
    for (int i = 0; i < 4; i++) {
        normals[i] = vec3::cross(far_quad[i] - points[i], points[(i+1)%4] - points[i]).normalized();
    }
    vec3 forward = frustum.orientation * vec3(0,0,1);
    points[4] = points[0];
    normals[4] = forward;
    points[5] = far_quad[0];
    normals[5] = -forward;

    // Search is currently through a flat list.
    for (auto drawable : world.entities.aspects<Drawable>()) {
        Sphere sphere = drawable->bounding_sphere();
        bool culled = false;
        for (int i = 0; i < 6; i++) {
            if (vec3::dot(sphere.origin - points[i], normals[i]) > sphere.radius) {
                culled = true;
                break;
            }
        }
        if (!culled) function(drawable);
    }
}
void Graphics::for_drawables(Aspect<Camera> camera, std::function<void(Aspect<Drawable> &)> function)
{
    for_drawables(camera->frustum(), function);
}



void Graphics::render_drawable(Aspect<Drawable> drawable, ShadingModelInstance shading_model)
{
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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, max_res_x, max_res_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindTexture(GL_TEXTURE_2D, post_buffer.depth_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, max_res_x, max_res_y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        post_buffer.resolution_x = max_res_x;
        post_buffer.resolution_y = max_res_y;
    }
    framebuffer_res_x = max_res_x;
    framebuffer_res_y = max_res_y;

    if (prev_window_viewport.w != window_viewport.w || prev_window_viewport.h != window_viewport.h) {
        glBindTexture(GL_TEXTURE_2D, screen_buffer.texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, window_viewport.w, window_viewport.h, 0, GL_RGBA, GL_FLOAT, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindTexture(GL_TEXTURE_2D, screen_buffer.depth_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, window_viewport.w, window_viewport.h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        screen_buffer.resolution_x = window_viewport.w;
        screen_buffer.resolution_y = window_viewport.h;
    }
    prev_window_viewport = window_viewport;


    // Update camera TAA data.
    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->has_taa_buffer) {
            auto viewport = camera->viewport();
            GLuint &fbo = camera->taa_buffer.id;
            GLuint &tex = camera->taa_buffer.texture;
            glGenFramebuffers(1, &fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, viewport.w, viewport.h, 0, GL_RGBA, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                fprintf(stderr, "Framebuffer incomplete.\n");
                exit(EXIT_FAILURE);
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            camera->has_taa_buffer = true;
        }
    }
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
    auto sm = world.graphics.shading.shading_models.load("shaders/gbuffer/normal_albedo_velocity.sm");
    auto shading_model = ShadingModelInstance(sm);
    mat4x4 vp_matrix = camera->view_projection_matrix();
    shading_model.properties.set_mat4x4("vp_matrix", vp_matrix);
    if (!camera->has_prev_view_projection_matrix) {
        camera->has_prev_view_projection_matrix = true;
        camera->prev_view_projection_matrix = vp_matrix;
    }
    shading_model.properties.set_mat4x4("prev_vp_matrix", camera->prev_view_projection_matrix);
    camera->prev_view_projection_matrix = vp_matrix;

    int num_drawn = 0;
    for_drawables(camera, [&](Aspect<Drawable> &drawable) {
        render_drawable(drawable, shading_model);
        num_drawn ++;
    });
    printf("camera num drawn: %d\n", num_drawn);

    //---Explicitly destroy shading model.
    shading_model.properties.destroy();

    /*--------------------------------------------------------------------------------
        Clear this camera's framebuffer section.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, camera->framebuffer.id);
    glEnable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
    glScissor(viewport.x, viewport.y, viewport.w, viewport.h);
    // An alpha value of zero signifies that this is a background pixel.
    // This distinction is needed so that deferred lighting can blend correctly.
    glClearColor(camera->background_color.x(), camera->background_color.y(), camera->background_color.z(), 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*--------------------------------------------------------------------------------
        Lighting and rendering of surfaces using the G-buffer.
        This is the first pass that fills the target framebuffer, so will
        clear to the camera's background color first.
        Further rendering will interleave into this rendering using a blitted depth buffer.
    --------------------------------------------------------------------------------*/
    glDisable(GL_DEPTH_TEST);
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
        Render 2D and 3D vector graphics.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, camera->framebuffer.id);
    glEnable(GL_SCISSOR_TEST);
    glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
    glScissor(viewport.x, viewport.y, viewport.w, viewport.h);
    paint.render(camera);

    /*--------------------------------------------------------------------------------
        Temporal anti-aliasing.
    --------------------------------------------------------------------------------*/
    // temporal_antialiasing(camera);

    /*--------------------------------------------------------------------------------
        Post-processing.
    --------------------------------------------------------------------------------*/
    // depth_of_field(camera);
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
        Clear the screen buffer and postprocessing buffer.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, screen_buffer.id);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0,0, window_viewport.w, window_viewport.h);
    glClearColor(background_color.x(), background_color.y(), background_color.z(), background_color.w());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, post_buffer.id);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0,0, window_viewport.w, window_viewport.h);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    paint.clear();

    /*--------------------------------------------------------------------------------
        Place the screen buffer in the window.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, window_width, window_height);
    glClearColor(window_background_color.x(), window_background_color.y(), window_background_color.z(), window_background_color.w());
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



void Graphics::compile_shaders()
{
    directional_light_program = world.resources.add<GLShaderProgram>();
    directional_light_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    directional_light_program->add_shader(GLShader(FragmentShader, "shaders/lighting/variance_directional_light.frag"));
    directional_light_program->link();

    point_light_program = world.resources.add<GLShaderProgram>();
    point_light_program->add_shader(GLShader(VertexShader, "shaders/postprocessing_quad.vert"));
    point_light_program->add_shader(GLShader(FragmentShader, "shaders/lighting/variance_point_light.frag"));
    point_light_program->link();

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


