
void Graphics::update_directional_lights()
{
    /*--------------------------------------------------------------------------------
        Directional lights
    --------------------------------------------------------------------------------*/
    auto shadow_map_sm = shading.shading_models.load("shaders/shadows/shadow_map.sm");
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
                shadow_map_shading_model.properties.set_mat4x4("vp_matrix", shadow_matrix);
                // For efficiency, the transformation to texture space is concatenated for the shadow matrix uploaded to the lighting shaders.
                sm.shadow_matrices[segment] = mat4x4::translation(vec3(0.5,0.5,0.5)) * mat4x4::scale(0.5) * shadow_matrix;
                // sm.shadow_matrices[segment] = shadow_matrix;
                sm.box_extents[segment] = vec3(width, height, depth);

                glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
                glViewport(0, 0, sm.width, sm.height);
                glDisable(GL_SCISSOR_TEST);
                glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, sm.texture, 0, segment);
                glEnable(GL_DEPTH_TEST);
                glClear(GL_DEPTH_BUFFER_BIT);

                int num_drawn = 0;
                for_drawables(OrientedBox(mins, maxs, mat3x3(X, Y, Z)), [&](Aspect<Drawable> &drawable) {
                    render_drawable(drawable, shadow_map_shading_model);
                    num_drawn ++;
                });
                printf("shadow map num drawn: %d\n", num_drawn);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
        }
    }
    //---todo: Garbage collection. Clean up rendering data for removed lights and cameras.
    shadow_map_shading_model.properties.destroy();
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
    int width = 512;
    int height = 512;
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



void Graphics::directional_lighting(Aspect<Camera> camera)
{
    auto &program = directional_light_shader_program;
    auto &filter_program = directional_light_filter_shader_program;

    auto camera_transform = camera.sibling<Transform>();
    auto camera_matrix = camera_transform->matrix();
    auto viewport = camera->viewport();
    set_post(viewport); // ping-pong post-processing with the camera's target viewport.
                        // The write target starts off as the post-buffer.
    glEnable(GL_BLEND);

    for (auto light : world.entities.aspects<DirectionalLight>()) {
        if (!light->active) continue;
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
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map.texture);
        glBindSampler(0, shadow_map.sampler_comparison);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map.texture);
        glBindSampler(1, shadow_map.sampler_raw);
        glUniform1i(program->uniform_location("shadow_map"), 0);
        glUniform1i(program->uniform_location("shadow_map_raw"), 1);

        glUniformMatrix4fv(program->uniform_location("camera_matrix"), 1, GL_FALSE, (GLfloat *) &camera_matrix);

        for (int i = 0; i < shadow_map.num_frustum_segments; i++) {
            // The shadow matrix transforms from camera space, so post-multiply the world-space shadow matrix with the camera's model-matrix.
            auto uniform_name = std::string("shadow_matrices[") + std::to_string(i) + std::string("]");
            mat4x4 shadow_matrix = shadow_map.shadow_matrices[i] * camera_matrix;
            glUniformMatrix4fv(program->uniform_location(uniform_name), 1, GL_FALSE, (GLfloat *) &shadow_matrix);

            uniform_name = std::string("world_shadow_matrices[") + std::to_string(i) + std::string("]");
            glUniformMatrix4fv(program->uniform_location(uniform_name), 1, GL_FALSE, (GLfloat *) &shadow_map.shadow_matrices[i]);

            // // Form the inverse transpose of the non-translating world-space shadow-box matrix.
            // // This will be used to transform normals in the shader, for biasing.
            // mat4x4 shadow_normal_matrix = mat4x4::identity();
            // for (int j = 0; j < 3; j++) {
            //     for (int k = 0; k < 3; k++) {
            //         shadow_normal_matrix.entry(j, k) = shadow_map.shadow_matrices[i].entry(k, j);
            //     }
            // }
            // std::cout << shadow_normal_matrix *  shadow_normal_matrix.inverse() << "\n";
            // shadow_normal_matrix = shadow_normal_matrix.inverse();
            // std::cout << shadow_normal_matrix << "\n";
            // uniform_name = std::string("shadow_normal_matrices[") + std::to_string(i) + std::string("]");
            // glUniformMatrix4fv(program->uniform_location(uniform_name), 1, GL_FALSE, (GLfloat *) &shadow_normal_matrix);

            uniform_name = std::string("box_extents[") + std::to_string(i) + std::string("]");
            glUniform3fv(program->uniform_location(uniform_name), 1, (GLfloat *) &shadow_map.box_extents[i]);
            uniform_name = std::string("inv_box_extents[") + std::to_string(i) + std::string("]");
            vec3 inv_box_extents = 1.f / shadow_map.box_extents[i];
            glUniform3fv(program->uniform_location(uniform_name), 1, (GLfloat *) &inv_box_extents);

            uniform_name = std::string("_pre_1[") + std::to_string(i) + std::string("]");
            // _pre_1[i] : 0.5*width*box_extents[i].z * inv_box_extents[i].xy
            vec2 _pre_1 = 0.5 * light->width * shadow_map.box_extents[i].z() * vec2(1.f / shadow_map.box_extents[i].x(), 1.f / shadow_map.box_extents[i].y());
            glUniform2fv(program->uniform_location(uniform_name), 1, (GLfloat *) &_pre_1);
        }
	auto gbuffer_depth = gbuffer_component("depth");
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuffer_depth.texture);
	glUniform1i(program->uniform_location("depth"), 2);
	auto gbuffer_normal = gbuffer_component("normal");
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gbuffer_normal.texture);
	glUniform1i(program->uniform_location("normal"), 3);

        mat4x4 inverse_projection_matrix = camera->projection_matrix.inverse();
        glUniformMatrix4fv(program->uniform_location("inverse_projection_matrix"), 1, GL_FALSE, (GLfloat *) &inverse_projection_matrix);

        begin_post(program);
        glBlendFunc(GL_ONE, GL_ZERO);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        program->unbind();

        // Blend the directional light pass into the image, using a filtered shadowing signal.
        filter_program->bind();
        upload_shared_uniforms(filter_program);
        glUniform1f(filter_program->uniform_location("inv_screen_width"), 1.f / write_post().framebuffer->resolution_x);
        glUniform1f(filter_program->uniform_location("inv_screen_height"), 1.f / write_post().framebuffer->resolution_y);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, write_post().framebuffer->texture);
        glUniform1i(filter_program->uniform_location("shadow"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuffer_normal.texture);
	glUniform1i(filter_program->uniform_location("normal"), 1);
	auto gbuffer_albedo = gbuffer_component("albedo");
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuffer_albedo.texture);
	glUniform1i(filter_program->uniform_location("albedo"), 2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gbuffer_depth.texture);
	glUniform1i(filter_program->uniform_location("depth"), 3);

        swap_post(); // Swap to write to the viewport buffer.
        begin_post(filter_program);
        // Additive blending. When the destination alpha is 0, however, this just overwrites.
        glBlendFuncSeparate(GL_ONE, GL_DST_ALPHA, // RGB
                            GL_ONE, GL_ZERO); // Alpha
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        filter_program->unbind();
        swap_post(); // Swap to write to the post-buffer.
    }
    swap_post(); // The viewport buffer contains the image, so signify this by leaving it as the write buffer.
}
