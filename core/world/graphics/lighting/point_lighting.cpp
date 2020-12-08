

void Graphics::update_point_lights()
{
    auto shadow_map_sm = shading.shading_models.load("shaders/shadows/distance_shadow_map.sm");
    // auto shadow_map_sm = shading.shading_models.load("shaders/shadows/shadow_map.sm");
    auto shadow_map_shading_model = ShadingModelInstance(shadow_map_sm);

    // +X,-X,  +Y,-Y,  +Z,-Z. See https://learnopengl.com/Advanced-OpenGL/Cubemaps for cubemap layout.
    const mat3x3 orientations[6] = {
        mat3x3(0,0,-1,  0,-1,0,  -1,0,0), // +X
        mat3x3(0,0,1, 0,-1,0,  1,0,0),  // -X

        mat3x3(1,0,0,  0,0,1, 0,-1,0), // +Y
        mat3x3(1,0,0,  0,0,-1, 0,1,0), // -Y

        mat3x3(1,0,0, 0,-1,0,  0,0,-1), // +Z
        mat3x3(-1,0,0, 0,-1,0,  0,0,1), // -Z
    };
    for (auto light : world.entities.aspects<PointLight>()) {
        auto light_transform = light.sibling<Transform>();
        shadow_map_shading_model.properties.set_vec4("light_position", vec4(light_transform->position, 1));
        float extent = light->extent();
        for (auto camera : world.entities.aspects<Camera>()) {
            auto &sm = point_light_data(light).shadow_map(camera);
            float near = 0.05;

            for (int face = 0; face < 6; face++) {
                // The initial frustum extends as far as the light does.
                auto frustum = Frustum(light_transform->position, orientations[face], near, extent, near, near);
                mat4x4 shadow_matrix = frustum.matrix();
                shadow_map_shading_model.properties.set_mat4x4("vp_matrix", shadow_matrix);
                shadow_map_shading_model.properties.set_float("far_plane_distance", frustum.f);

	        // For efficiency, the transformation to texture space is concatenated for the shadow matrix uploaded to the lighting shaders.
	        sm.shadow_matrices[face] = mat4x4::translation(vec3(0.5,0.5,0.5)) * mat4x4::scale(0.5) * shadow_matrix;

                glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
                glViewport(0, 0, sm.width, sm.height);
                glDisable(GL_SCISSOR_TEST);
                glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, sm.cube_map, 0, face);
                glEnable(GL_DEPTH_TEST);
                glClear(GL_DEPTH_BUFFER_BIT);

                int num_drawn = 0;
                for_drawables(frustum, [&](Aspect<Drawable> &drawable) {
                    render_drawable(drawable, shadow_map_shading_model);
                    num_drawn ++;
                });
                printf("shadow map cube face num drawn: %d\n", num_drawn);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
        }
    }
}


PointLightShadowMap &PointLightData::shadow_map(Aspect<Camera> camera)
{
    auto iter = shadow_maps.find(camera.ID());
    if (iter != shadow_maps.end()) {
        // The shadow map already exists.
        return shadow_maps[camera.ID()];
    }
    int width = 512;
    int height = 512;

    GLuint cube_map;
    glGenTextures(1, &cube_map);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map);
    for (int i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0,
                     GL_DEPTH_COMPONENT32F,
                     width, height,
                     0,
                     GL_DEPTH_COMPONENT,
                     GL_FLOAT,
                     NULL);
    }
    GLuint sampler; // For use with samplerCubeShadow.
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
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, cube_map, 0, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Incomplete framebuffer when initializing shadow maps.\n");
        exit(EXIT_FAILURE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    PointLightShadowMap sm;
    sm.fbo = fbo;
    sm.camera = camera;
    sm.width = width;
    sm.height = height;
    sm.cube_map = cube_map;
    sm.sampler_comparison = sampler;
    sm.sampler_raw = sampler_raw;
    shadow_maps[camera.ID()] = sm;
    return shadow_maps[camera.ID()];
}


PointLightData &Graphics::point_light_data(Aspect<PointLight> light)
{
    auto iter = point_light_data_map.find(light.ID());
    if (iter != point_light_data_map.end()) {
        return point_light_data_map[light.ID()];
    }
    PointLightData data;
    point_light_data_map[light.ID()] = data;
    return point_light_data_map[light.ID()];
}


void Graphics::point_lighting(Aspect<Camera> camera)
{
    auto &program = point_light_shader_program;
    program->bind();
    auto gbuffer_depth = gbuffer_component("depth");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gbuffer_depth.texture);
    glUniform1i(program->uniform_location("depth"), 0);
    auto gbuffer_normal = gbuffer_component("normal");
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gbuffer_normal.texture);
    glUniform1i(program->uniform_location("normal"), 1);
    auto gbuffer_albedo = gbuffer_component("albedo");
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gbuffer_albedo.texture);
    glUniform1i(program->uniform_location("albedo"), 2);


    auto camera_transform = camera.sibling<Transform>();
    auto camera_matrix = camera_transform->matrix();
    mat4x4 inverse_vp_matrix = camera->view_projection_matrix().inverse();
    glUniformMatrix4fv(program->uniform_location("inverse_vp_matrix"), 1, GL_FALSE, (GLfloat *) &inverse_vp_matrix);
    auto viewport = camera->viewport();
    set_post(viewport); // ping-pong post-processing with the camera's target viewport.
                        // The write target starts off as the post-buffer.
    swap_post(); // Blend straight into the target viewport.
    glEnable(GL_BLEND);
    // Additive blending. When the destination alpha is 0, however, this just overwrites.
    glBlendFuncSeparate(GL_ONE, GL_DST_ALPHA, // RGB
                        GL_ONE, GL_ZERO); // Alpha
    for (auto light : world.entities.aspects<PointLight>()) {
        if (!light->active) continue;
        auto light_transform = light.sibling<Transform>();
        auto &shadow_map = point_light_data(light).shadow_map(camera);

        glUniform1f(program->uniform_location("far_plane_distance"), light->extent());
        for (int i = 0; i < 6; i++) {
            auto uniform_name = std::string("shadow_matrices[") + std::to_string(i) + std::string("]");
            mat4x4 shadow_matrix = shadow_map.shadow_matrices[i];
            glUniformMatrix4fv(program->uniform_location(uniform_name), 1, GL_FALSE, (GLfloat *) &shadow_matrix);
        }

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_map.cube_map);
        glBindSampler(3, shadow_map.sampler_comparison);
        glUniform1i(program->uniform_location("shadow_map"), 3);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_map.cube_map);
        glBindSampler(4, shadow_map.sampler_raw);
        glUniform1i(program->uniform_location("shadow_map_raw"), 4);
    
        glUniform3fv(program->uniform_location("light_position"), 1, (GLfloat *) &light_transform->position);
        glUniform3fv(program->uniform_location("light_color"), 1, (GLfloat *) &light->color);
        glUniform1f(program->uniform_location("light_radius"), light->radius);

        begin_post(program);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
}

