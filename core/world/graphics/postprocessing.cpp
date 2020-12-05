

// Prepare the post-processing quad, with its uv rectangle extents.
void Graphics::begin_post(Resource<GLShaderProgram> &program,
                          Viewport read_viewport,
                          Viewport target_viewport)
{
    glBindFramebuffer(GL_FRAMEBUFFER, target_viewport.framebuffer->id);
    glViewport(VIEWPORT_EXPAND(target_viewport));
    glEnable(GL_SCISSOR_TEST);
    glScissor(VIEWPORT_EXPAND(target_viewport));

    vec4 uv_quad = vec4(
        read_viewport.x / (1.f * read_viewport.framebuffer->resolution_x),
        read_viewport.y / (1.f * read_viewport.framebuffer->resolution_y),
        read_viewport.w / (1.f * read_viewport.framebuffer->resolution_x),
        read_viewport.h / (1.f * read_viewport.framebuffer->resolution_y)
    );
    glUniform4fv(program->uniform_location("uv_quad"), 1, (GLfloat *) &uv_quad);
    vec4 gbuffer_uv_quad = vec4(
        0,
        0,
        read_viewport.w / (1.f * framebuffer_res_x),
        read_viewport.h / (1.f * framebuffer_res_y)
    );
    glUniform4fv(program->uniform_location("gbuffer_uv_quad"), 1, (GLfloat *) &gbuffer_uv_quad);
    glBindVertexArray(postprocessing_quad_vao);
}

void Graphics::begin_post(Resource<GLShaderProgram> &program)
{
    begin_post(program, read_post(), write_post());
}

void Graphics::set_post(Viewport &viewport)
{
    second_post_viewport = viewport;
    post_flag = 0;
}


Viewport Graphics::read_post()
{
    if (post_flag == 0) {
        return second_post_viewport;
    }
    return Viewport(post_buffer, 0,0, second_post_viewport.w, second_post_viewport.h);
}
Viewport Graphics::write_post()
{
    if (post_flag == 0) {
        return Viewport(post_buffer, 0,0, second_post_viewport.w, second_post_viewport.h);
    }
    return second_post_viewport;
}

void Graphics::swap_post()
{
    post_flag = (post_flag + 1) % 2;
}





void Graphics::depth_of_field(Aspect<Camera> camera)
{
    // auto camera_transform = camera.sibling<Transform>();
    // vec3 camera_position = camera_transform->position;
    // vec3 camera_forward = -camera_transform->forward();
    // auto viewport = camera->viewport();

    // /*--------------------------------------------------------------------------------
    //     Near field splitting.
    // --------------------------------------------------------------------------------*/
    // auto &program = depth_of_field_confusion_radius_program;
    // program->bind();
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, gbuffer_component("position").texture);
    // glUniform1i(program->uniform_location("position"), 0);
    // glUniform3fv(program->uniform_location("camera_position"), 1, (GLfloat *) &camera_position);
    // glUniform3fv(program->uniform_location("camera_forward"), 1, (GLfloat *) &camera_forward);
    // glUniform2fv(program->uniform_location("depth_of_field"), 1, (GLfloat *) &camera->depth_of_field);
    // float focus = 0.5*camera->depth_of_field.x() + 0.5*camera->depth_of_field.y();
    // glUniform1f(program->uniform_location("focus"), focus);

    // auto confusion_buffer = post_buffer();
    // std::cout << gbuffer_component("position").texture << "\n";
    // std::cout << confusion_buffer << "\n";
    // glBindFramebuffer(GL_FRAMEBUFFER, confusion_buffer.id);
    // glBlendFunc(GL_ONE, GL_ZERO);
    // glClearColor(0,0,0,0);
    // glClear(GL_COLOR_BUFFER_BIT);

    // prepare_ppq(program,
    //             screen_buffer, Viewport(0,0, viewport.w, viewport.h),
    //             confusion_buffer, Viewport(0,0, viewport.w, viewport.h));

    // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // program->unbind();

    // // glBindFramebuffer(GL_READ_FRAMEBUFFER, confusion_buffer.id);
    // // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, screen_buffer.id);
    // // glBlitFramebuffer(0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // source
    // //                   0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // destination
    // //                   GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // /*--------------------------------------------------------------------------------
    //     Near field filtering.
    // --------------------------------------------------------------------------------*/
    // auto filter_program = depth_of_field_near_field_program;
    // filter_program->bind();
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, confusion_buffer.texture);
    // glUniform1i(filter_program->uniform_location("confusion"), 0);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, screen_buffer.texture);
    // glUniform1i(filter_program->uniform_location("image"), 1);
    // glUniform1f(filter_program->uniform_location("inv_screen_width"), 1.f / post_buffer().resolution_x);
    // glUniform1f(filter_program->uniform_location("inv_screen_height"), 1.f / post_buffer().resolution_y);

    // swap_post();
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, screen_buffer.id);
    // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, post_buffer().id);
    // glBlitFramebuffer(0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // source
    //                   0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // destination
    //                   GL_COLOR_BUFFER_BIT, GL_NEAREST);
    // glBindFramebuffer(GL_FRAMEBUFFER, post_buffer().id);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 
    // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, post_buffer().id);
    // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, screen_buffer.id);
    // glBlitFramebuffer(0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // source
    //                   0,0, screen_buffer.resolution_x, screen_buffer.resolution_y, // destination
    //                   GL_COLOR_BUFFER_BIT, GL_NEAREST);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // filter_program->unbind();
}


void Graphics::temporal_antialiasing(Aspect<Camera> camera)
{
    auto viewport = camera->viewport();
    auto &program = temporal_aa_program;
    program->bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gbuffer_component("velocity").texture);
    glUniform1i(program->uniform_location("velocity"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, camera->framebuffer.texture);
    glUniform1i(program->uniform_location("image"), 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, camera->taa_buffer.texture);
    glUniform1i(program->uniform_location("prev_image"), 2);

    set_post(viewport);
    begin_post(program);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    program->unbind();

    // Update this camera's TAA history buffer.
    glBindFramebuffer(GL_READ_FRAMEBUFFER, camera->framebuffer.id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, camera->taa_buffer.id);
    glBlitFramebuffer(viewport.x, viewport.y, viewport.x+viewport.w, viewport.y+viewport.h,
                      0,0, camera->taa_buffer.resolution_x, camera->taa_buffer.resolution_y,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Overwrite the section of the target framebuffer buffer with the anti-aliased image.
    glBindFramebuffer(GL_READ_FRAMEBUFFER, write_post().framebuffer->id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, camera->framebuffer.id);
    glBlitFramebuffer(0,0, viewport.w, viewport.h,
                      viewport.x, viewport.y, viewport.x+viewport.w, viewport.y+viewport.h,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
