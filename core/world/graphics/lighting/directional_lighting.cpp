/*--------------------------------------------------------------------------------
    Initialize directional light.
--------------------------------------------------------------------------------*/
DirectionalLightShadowMap &DirectionalLightData::shadow_map(Aspect<Camera> camera)
{
    auto iter = shadow_maps.find(camera.ID());
    if (iter != shadow_maps.end()) {
        // The shadow map already exists.
        return shadow_maps[camera.ID()];
    }
    int n = 256;
    int width = n;
    int height = n;
    int num_mips = 0;
    for (int c = n; c > 1; c /= 2) { num_mips ++; }
    int num_frustum_segments = 4;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
    // glTexStorage3D(GL_TEXTURE_2D_ARRAY,
    //                num_mips,
    //                GL_RG16,
    //                width, height, num_frustum_segments);
    int w = width;
    int h = height;
    for (int i = 0; i < num_mips; i++) {
        glTexImage3D(GL_TEXTURE_2D_ARRAY, i, GL_RG16, w, h, num_frustum_segments, 0, GL_RG, GL_UNSIGNED_SHORT, NULL);
        w = max(1, w / 2);
        h = max(1, h / 2);
    }
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    // Summed-area table texture
    GLuint sat_tex;
    glGenTextures(1, &sat_tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, sat_tex);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RG32F, w, h, num_frustum_segments, 0, GL_RG, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    GLuint depth_rbo;
    glGenRenderbuffers(1, &depth_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Incomplete framebuffer when initializing directional light shadow maps.\n");
        exit(EXIT_FAILURE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    DirectionalLightShadowMap sm;
    sm.camera = camera;
    sm.width = width;
    sm.height = height;
    sm.texture = tex;
    sm.summed_area_table_texture = sat_tex;
    sm.depth_buffer = depth_rbo;
    sm.fbo = fbo;
    sm.num_frustum_segments = num_frustum_segments;
    sm.shadow_matrices = std::vector<mat4x4>(sm.num_frustum_segments);
    sm.box_extents = std::vector<vec3>(sm.num_frustum_segments);
    sm.frustum_segment_dividers = std::vector<float>(sm.num_frustum_segments-1);

    sm.distance = 20; //an arbitrarily chosen default
    if (sm.num_frustum_segments == 2) {
        // Hard-coded frustum segment dividers.
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



/*--------------------------------------------------------------------------------
    Get directional light's graphics data.
--------------------------------------------------------------------------------*/
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



/*--------------------------------------------------------------------------------
    Update directional lights.
--------------------------------------------------------------------------------*/
void Graphics::update_directional_lights()
{
    auto shadow_map_sm = shading.shading_models.load("shaders/shadows/distance_to_plane_variance_shadow_map.sm");
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

            std::vector<vec3> images(sm.width * sm.height * sm.num_frustum_segments);
            std::vector<vec3> new_images(sm.width * sm.height * sm.num_frustum_segments);

            std::vector<vec3> summed_area_tables(sm.width * sm.height * sm.num_frustum_segments);

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
                sm.box_extents[segment] = vec3(width, height, depth);

                glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
                glViewport(0, 0, sm.width, sm.height);
                glDisable(GL_SCISSOR_TEST);
                glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, sm.texture, 0, segment);
                glEnable(GL_DEPTH_TEST);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                int num_drawn = 0;
                for_drawables(OrientedBox(mins, maxs, mat3x3(X, Y, Z)), [&](Aspect<Drawable> &drawable) {
                    render_drawable(drawable, shadow_map_shading_model);
                    num_drawn ++;
                });
                printf("shadow map num drawn: %d\n", num_drawn);

                glReadBuffer(GL_COLOR_ATTACHMENT0);
                glReadPixels(0, 0, sm.width, sm.height, GL_RGB, GL_FLOAT, &images[segment * sm.width * sm.height]);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

	    // int box_r = 1;
            // float weight = 1.f / (2*box_r + 1);
            // for (int segment = 0; segment < sm.num_frustum_segments; segment++) {
            //     for (int i = 0; i < sm.width; i++) {
            //         for (int j = 0; j < sm.height; j++) {
            //             vec3 x = vec3::zero();
            //             for (int ii = -box_r; ii <= box_r; ii++) {
	    //     	    x += weight * images[segment * (sm.width*sm.height) + clamp(i+ii, 0, sm.width) + j*sm.width];
            //             }
            //             new_images[segment * (sm.width*sm.height) + i + j*sm.width] = x;
            //         }
            //     }
            //     for (int i = 0; i < sm.width; i++) {
            //         for (int j = 0; j < sm.height; j++) {
            //             vec3 x = vec3::zero();
            //             for (int jj = -box_r; jj <= box_r; jj++) {
            //                 x += weight * new_images[segment * (sm.width*sm.height) + i + clamp(j+jj, 0, sm.height)*sm.width];
            //             }
            //             images[segment * (sm.width*sm.height) + i + j*sm.width] = x;
            //         }
            //     }
            // }

            glBindTexture(GL_TEXTURE_2D_ARRAY, sm.texture);
            // glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RG16, sm.width, sm.height, sm.num_frustum_segments, 0, GL_RGB, GL_FLOAT, &images[0]);
            glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
            glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

            for (int segment = 0; segment < sm.num_frustum_segments; segment++) {
                // for (int i = 0; i < sm.height; i++) {
                //     for (int j = 0; j < sm.width; j++) {
                //         vec3 total = vec3::zero();
                //         for (int ii = 0; ii <= i; ii++) {
                //             for (int jj = 0; jj <= j; jj++) {
                //                 total += images[segment*(sm.width*sm.height) + ii*sm.width + jj];
                //             }
                //         }
                //         new_images[segment*(sm.width*sm.height) + i*sm.width + j] = total;
                //     }
                // }
                
                int n = 1;
                while (n < sm.width) {
                    for (int i = 0; i < sm.height; i++) {
                        for (int j = sm.width-1; j >= n; j--) {
                            images[segment * (sm.width*sm.height) + i*sm.width + j] += images[segment * (sm.width*sm.height) + i*sm.width + j-n];
                        }
                    }
                    n *= 2;
                }
                n = 1;
                while (n < sm.height) {
                    for (int j = 0; j < sm.width; j++) {
                        for (int i = sm.height-1; i >= n; i--) {
                            images[segment * (sm.width*sm.height) + i*sm.width + j] += images[segment * (sm.width*sm.height) + (i-n)*sm.width + j];
                        }
                    }
                    n *= 2;
                }

            
                // for (int i = 0; i < sm.height*sm.width*sm.num_frustum_segments; i++) {
                //     if ((images[i]-new_images[i]).x() > 1.f) { printf("BAD!\n"); exit(EXIT_FAILURE); }
                // }
            }
            glBindTexture(GL_TEXTURE_2D_ARRAY, sm.summed_area_table_texture);
            glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RG32F, sm.width, sm.height, sm.num_frustum_segments, 0, GL_RGB, GL_FLOAT, &images[0]);
            glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
            glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        }
    }
    //---todo: Garbage collection. Clean up rendering data for removed lights and cameras.
    shadow_map_shading_model.properties.destroy();
}



/*--------------------------------------------------------------------------------
    Accumulate effect of directional lighting on surfaces.
--------------------------------------------------------------------------------*/
void Graphics::directional_lighting(Aspect<Camera> camera)
{
    auto viewport = camera->viewport();
    auto &program = directional_light_program;
    program->bind();

    set_post(viewport);
    swap_post(); // Write to the target camera viewport rather than the post-processing buffer.
    begin_post(program);
    // Additive blending. When the destination alpha is 0, however, this just overwrites.
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_ONE, GL_DST_ALPHA, // RGB
                        GL_ONE, GL_ZERO);     // Alpha

    // Bind G-buffer textures.
    auto gbuffer_depth = gbuffer_component("depth");
    auto gbuffer_normal = gbuffer_component("normal");
    auto gbuffer_albedo = gbuffer_component("albedo");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gbuffer_depth.texture);
    glUniform1i(program->uniform_location("depth"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gbuffer_normal.texture);
    glUniform1i(program->uniform_location("normal"), 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gbuffer_albedo.texture);
    glUniform1i(program->uniform_location("albedo"), 2);

    // Upload camera data.
    auto camera_transform = camera.sibling<Transform>();
    vec3 camera_forward = -camera_transform->forward();
    auto camera_matrix = camera_transform->matrix();
    glUniform3fv(program->uniform_location("camera_position"), 1, (GLfloat *) &camera_transform->position);
    glUniform3fv(program->uniform_location("camera_forward"), 1, (GLfloat *) &camera_forward);
    glUniformMatrix4fv(program->uniform_location("camera_matrix"), 1, GL_FALSE, (GLfloat *) &camera_matrix);
    mat4x4 inverse_projection_matrix = camera->projection_matrix.inverse();
    glUniformMatrix4fv(program->uniform_location("inverse_projection_matrix"), 1, GL_FALSE, (GLfloat *) &inverse_projection_matrix);

    // Add contributions from each light to the target viewport.
    for (auto light : world.entities.aspects<DirectionalLight>()) {
        if (!light->active) continue;
        auto &shadow_map = directional_light_data(light).shadow_map(camera);
        float near = camera->near_plane_distance;
        float far = fmin(shadow_map.distance, camera->far_plane_distance);

        // Upload light and shadow mapping data.

        // Upload frustum segment divider data.
        glUniform1i(program->uniform_location("num_frustum_segments"), shadow_map.num_frustum_segments);
        for (int i = 0; i < shadow_map.num_frustum_segments-1; i++) {
            // Compute the distances of the segment dividers in camera space, from the frustum dividers in the range [0,1].
            float t = shadow_map.frustum_segment_dividers[i];
            float frustum_segment_distance = (1-t)*near + t*far;
            auto uniform_name = std::string("frustum_segment_distances[") + std::to_string(i) + std::string("]");
            glUniform1f(program->uniform_location(uniform_name), frustum_segment_distance);
        }
        {
            // The last "frustum segment" distance in the shader's array is the distance to the far plane.
	    auto uniform_name = std::string("frustum_segment_distances[") + std::to_string(shadow_map.num_frustum_segments-1) + std::string("]");
            glUniform1f(program->uniform_location(uniform_name), far);
        }

        // Upload directional light properties.
        glUniform3fv(program->uniform_location("light_direction"), 1, (GLfloat *) &light->direction);
        glUniform3fv(program->uniform_location("light_color"), 1, (GLfloat *) &light->color);
        glUniform1f(program->uniform_location("light_width"), light->width);

        // Upload per-frustum-segment data.
        for (int i = 0; i < shadow_map.num_frustum_segments; i++) {
            // The shadow matrix transforms from camera space, so post-multiply the world-space shadow matrix with the camera's model-matrix.
            auto uniform_name = std::string("shadow_matrices[") + std::to_string(i) + std::string("]");
            mat4x4 shadow_matrix = shadow_map.shadow_matrices[i] * camera_matrix;
            glUniformMatrix4fv(program->uniform_location(uniform_name), 1, GL_FALSE, (GLfloat *) &shadow_matrix);

            uniform_name = std::string("world_shadow_matrices[") + std::to_string(i) + std::string("]");
            glUniformMatrix4fv(program->uniform_location(uniform_name), 1, GL_FALSE, (GLfloat *) &shadow_map.shadow_matrices[i]);

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

        // Upload shadow map metadata.
        glUniform2i(program->uniform_location("shadow_map_resolution"), shadow_map.width, shadow_map.height);

        // Bind the variance shadow map.
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map.texture);
        glUniform1i(program->uniform_location("shadow_map"), 3);
        // Bind the summed area of the variance shadow map.
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map.summed_area_table_texture);
        glUniform1i(program->uniform_location("shadow_map_summed_area_table"), 4);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    program->unbind();
}
