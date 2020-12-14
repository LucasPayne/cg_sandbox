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
    int w = width;
    int h = height;
    for (int i = 0; i < num_mips; i++) {
        glTexImage3D(GL_TEXTURE_2D_ARRAY, i, GL_RG16, w, h, num_frustum_segments, 0, GL_RG, GL_UNSIGNED_SHORT, NULL);
        w = max(1, w / 2);
        h = max(1, h / 2);
    }
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    // Summed-area table texture
    GLuint sat_tex;
    glGenTextures(1, &sat_tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, sat_tex);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RG32F, width, height, num_frustum_segments, 0, GL_RG, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    GLuint sat_swap_tex; //note: This is only a texture array since OpenGL <=4.2 doesn't have texture views, and its easier to treat each sat texture the same...
    glGenTextures(1, &sat_swap_tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, sat_swap_tex);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RG32F, width, height, num_frustum_segments, 0, GL_RG, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
    sm.texture_num_mips = num_mips;
    sm.summed_area_table_texture = sat_tex;
    sm.summed_area_table_swap_buffer = sat_swap_tex;
    sm.depth_buffer = depth_rbo;
    sm.fbo = fbo;
    sm.num_frustum_segments = num_frustum_segments;
    sm.average_moments = std::vector<vec2>(sm.num_frustum_segments);
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

                // Extend the box to roughly account for summed-area table filtering size.
                // This is to attempt to prevent artifacts at the edges of this segment.
                // mins -=  (2.f / 0.008726618569493142) * fabs(light->radius) * (X + Y + Z);
                // maxs += (2.f / 0.008726618569493142) * fabs(light->radius) * (X + Y + Z);

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
                // glClearColor(10000,0,0,0);
                glClearColor(0,0,0,0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                int num_drawn = 0;
                for_drawables(OrientedBox(mins, maxs, mat3x3(X, Y, Z)), [&](Aspect<Drawable> &drawable) {
                    render_drawable(drawable, shadow_map_shading_model);
                    num_drawn ++;
                });
                printf("shadow map num drawn: %d\n", num_drawn);
            }
            glBindTexture(GL_TEXTURE_2D_ARRAY, sm.texture);
            glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

            GLint f_w, f_h, f_d;
	    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, sm.texture_num_mips, GL_TEXTURE_WIDTH, &f_w);
	    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, sm.texture_num_mips, GL_TEXTURE_HEIGHT, &f_h);
	    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, sm.texture_num_mips, GL_TEXTURE_DEPTH, &f_d);
            printf("%d %d %d\n", f_w, f_h, f_d);
            if (f_w != 1 || f_h != 1 || f_d != sm.num_frustum_segments || sm.average_moments.size() != 4) {
                fprintf(stderr, "Something went wrong with mips or parameter buffer when computing average moments.\n");
                exit(EXIT_FAILURE);
            }
	    glGetTexImage(GL_TEXTURE_2D_ARRAY, sm.texture_num_mips, GL_RG, GL_FLOAT, (void *) &sm.average_moments[0]);
            for (int i = 0; i < sm.num_frustum_segments; i++) {
                std::cout << sm.average_moments[i] << "\n";
            }
	    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
            
            Resource<GLShaderProgram> program;

            #if 0
            // Blur the moments.
            program = box_filter_texture_layer_program;
	    program->bind();
            glUniform1i(program->uniform_location("image"), 0);
	    glUniform2i(program->uniform_location("image_dimensions"), sm.width, sm.height);
	    glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
            glViewport(0, 0, sm.width, sm.height);
            glEnable(GL_SCISSOR_TEST);
	    glDisable(GL_DEPTH_TEST);
            glScissor(0, 0, sm.width, sm.height);
	    glBindVertexArray(postprocessing_quad_vao);
            int kernel_radius = 1;
	    glUniform1i(program->uniform_location("n"), kernel_radius);
	    glUniform1f(program->uniform_location("inv_2n_plus_1"), 1.f / (2*kernel_radius + 1));
            for (int segment = 0; segment < sm.num_frustum_segments; segment++) {
                glUniform1i(program->uniform_location("image_layer"), segment);

                glUniform1i(program->uniform_location("axis"), 0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D_ARRAY, sm.texture);
	        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, sm.summed_area_table_swap_buffer, 0, segment);
	        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

                glUniform1i(program->uniform_location("axis"), 1);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D_ARRAY, sm.summed_area_table_swap_buffer);
	        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, sm.texture, 0, segment);
	        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            }
	    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	    program->unbind();
            #endif

            // Initialize the summed area table as the unsummed moments.
            program = copy_texture_layer_program;
	    program->bind();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D_ARRAY, sm.texture);
            glUniform1i(program->uniform_location("image"), 0);
            glUniform2i(program->uniform_location("image_dimensions"), sm.width, sm.height);
	    glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
            glViewport(0, 0, sm.width, sm.height);
            glEnable(GL_SCISSOR_TEST);
	    glDisable(GL_DEPTH_TEST);
            glScissor(0, 0, sm.width, sm.height);
	    glBindVertexArray(postprocessing_quad_vao);
            for (int segment = 0; segment < sm.num_frustum_segments; segment++) {
                glUniform2fv(program->uniform_location("average_moments"), 1, (GLfloat *) &sm.average_moments[segment]);
	        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, sm.summed_area_table_texture, 0, segment);
                glUniform1i(program->uniform_location("image_layer"), segment);
	        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            }
	    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	    program->unbind();

            // Create the summed area table by recursive doubling.
            // This is done in horizontal then vertical pass, each having multiple passes, around log2 of the resolution of that axis.
            // Each pass ping-pongs between two buffers. After the final pass, if the target buffer is the spare ping-pong buffer, swap it.
            program = summed_area_table_program;
            program->bind();
            GLuint textures[2] = {sm.summed_area_table_texture, sm.summed_area_table_swap_buffer};
            int swap_bit = 0;
            glUniform1i(program->uniform_location("image"), 0);
            glUniform2i(program->uniform_location("image_dimensions"), sm.width, sm.height);

            glBindFramebuffer(GL_FRAMEBUFFER, sm.fbo);
            glViewport(0, 0, sm.width, sm.height);
            glDisable(GL_SCISSOR_TEST);
            glDisable(GL_DEPTH_TEST);
            glBindVertexArray(postprocessing_quad_vao);
            for (int segment = 0; segment < sm.num_frustum_segments; segment++) {
	        int pass = 0;
                glUniform1i(program->uniform_location("image_layer"), segment);
                for (int axis = 0; axis <= 1; axis++) {
		    glUniform1i(program->uniform_location("is_vertical"), axis);
                    int n = 1;
                    while (n < sm.width) {
                        // printf("Summed area table pass %d axis %d segment %d\n", pass, axis, segment);
                        glUniform1i(program->uniform_location("n"), n);
                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D_ARRAY, textures[swap_bit]);
                        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textures[(swap_bit + 1) % 2], 0, segment);
                        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                        n *= 2;
                        pass += 1;
                        swap_bit = (swap_bit + 1) % 2;
                    }
                }
            }
            if (swap_bit != 0) {
                // If the last pass is into the other texture, swap these textures.
                // note: This means that the SAT texture ID is not consistent.
                auto tmp = sm.summed_area_table_texture;
                sm.summed_area_table_texture = sm.summed_area_table_swap_buffer;
                sm.summed_area_table_swap_buffer = tmp;
            }
            program->unbind();
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
        glUniform1f(program->uniform_location("light_radius"), light->radius);

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

            uniform_name = std::string("average_moments[") + std::to_string(i) + std::string("]");
            glUniform2fv(program->uniform_location(uniform_name), 1, (GLfloat *) &shadow_map.average_moments[i]);

            uniform_name = std::string("_pre_1[") + std::to_string(i) + std::string("]");
            // _pre_1[i] : light_radius*box_extents[i].z * inv_box_extents[i].xy
            vec2 _pre_1 = light->radius * shadow_map.box_extents[i].z() * vec2(1.f / shadow_map.box_extents[i].x(), 1.f / shadow_map.box_extents[i].y());
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
