

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



void Graphics::lighting(Aspect<Camera> camera)
{
    directional_lights(camera);
}



void Graphics::directional_lights(Aspect<Camera> camera)
{
    auto &program = directional_light_shader_program;
    auto &filter_program = directional_light_filter_shader_program;

    auto camera_transform = camera.sibling<Transform>();
    auto viewport = camera->viewport();
    set_post(viewport); // ping-pong post-processing with the camera's target viewport.
    glEnable(GL_BLEND);

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
        int shadow_signal_slot = gbuffer_components.size();
        glActiveTexture(GL_TEXTURE0 + shadow_signal_slot);
        glBindTexture(GL_TEXTURE_2D, write_post().framebuffer->texture);
        glUniform1i(filter_program->uniform_location("shadow"), shadow_signal_slot);

        swap_post();
        begin_post(filter_program);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, // RGB
                            GL_ONE, GL_ZERO);     // Alpha
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        filter_program->unbind();
    }
}
