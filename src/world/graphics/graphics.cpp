#include "world/world.h"
#include "reflector/reflector.h"

// Reflect opengl_utilities classes.
DESCRIPTOR_INSTANCE(GLShader);
BEGIN_ENTRIES(GLShader)
    //...unreflected
END_ENTRIES()

DESCRIPTOR_INSTANCE(GLShaderProgram);
BEGIN_ENTRIES(GLShaderProgram)
    //...unreflected
END_ENTRIES()


void Graphics::init()
{
    // Multisample initialization.
    // https://learnopengl.com/Advanced-OpenGL/Anti-Aliasing
    GLint max_framebuffer_samples;
    glGetIntegerv(GL_MAX_FRAMEBUFFER_SAMPLES, &max_framebuffer_samples);
    num_samples = 8;
    if (num_samples > max_framebuffer_samples) num_samples = max_framebuffer_samples;

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

    // Create the screen buffer.
    auto create_framebuffer = [&](Framebuffer &fb) {
        GLuint &fbo = fb.id;
        GLuint &tex = fb.texture;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glGenTextures(1, &tex);

        // multisampling
        // https://learnopengl.com/Advanced-OpenGL/Anti-Aliasing

        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, num_samples, GL_RGBA16F, 256, 256, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, tex, 0);
        
        // glBindTexture(GL_TEXTURE_2D, tex);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 256, 256, 0, GL_RGBA, GL_FLOAT, NULL);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // glBindTexture(GL_TEXTURE_2D, 0);
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

        // Give these framebuffers depth buffers.
        GLuint &depth = fb.depth_texture;
        // glGenTextures(1, &depth);
        // glBindTexture(GL_TEXTURE_2D, depth);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, 256, 256, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        // glBindTexture(GL_TEXTURE_2D, 0);
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);
        glGenTextures(1, &depth);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depth);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, num_samples, GL_DEPTH_COMPONENT32F, 256, 256, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, depth, 0);

        GLenum framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (framebuffer_status == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE) {
            fprintf(stderr, "Framebuffer incomplete: GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE.\n");
            exit(EXIT_FAILURE);
        } else if(framebuffer_status != GL_FRAMEBUFFER_COMPLETE) {
            fprintf(stderr, "Framebuffer incomplete.\n");
            exit(EXIT_FAILURE);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    };
    create_framebuffer(screen_buffer);


    // Initialize the vertex array for the post-processing quad. This is stored on the GPU and can be used at
    // any time for post-processing effects or deferred rendering.
    vec2 ppq_data[8] = {vec2(-1,-1),vec2(0,0),
                        vec2(-1,1),vec2(0,1),
                        vec2(1,1),vec2(1,1),
                        vec2(1,-1),vec2(1,0)}; // y is flipped since the framebuffer is flipped vertically.
    glGenVertexArrays(1, &postprocessing_quad_vao);
    glBindVertexArray(postprocessing_quad_vao); GLuint ppq_vbo;
    glGenBuffers(1, &ppq_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ppq_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 8, (const void *) &ppq_data[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2)*2, (const void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2)*2, (const void *) sizeof(vec2));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    compile_shaders();
}

void Graphics::screenshot(std::string filename)
{
    // Take a full screen screenshot.
    screenshot(filename, 0,0, window_viewport.w, window_viewport.h);
}
void Graphics::screenshot(std::string filename, int x0, int y0, int w, int h)
{
    // Take a screenshot of the given rectangle of the screen buffer (x0,y0 is the bottom left, w,h are the extents).
    if (w <= 0 || h <= 0) {
        fprintf(stderr, "ERROR: Graphics::screenshot(): Rectangle width and height must be positive.\n");
        exit(EXIT_FAILURE);
    }
    if (x0 < 0) x0 = 0;
    if (w > window_viewport.w - x0) w = window_viewport.w - x0;
    if (y0 < 0) y0 = 0;
    if (h > window_viewport.h - y0) h = window_viewport.h - y0;
    // if (x0 < 0 || x0 + w > window_viewport.w || y0 < 0 || y0 + h > window_viewport.h) {
    //     fprintf(stderr, "ERROR: Graphics::screenshot(): Screenshot dimensions must be restricted to the window viewport.\n");
    //     exit(EXIT_FAILURE);
    // }

    FILE *file = fopen(filename.c_str(), "w+");

    // The multisampled framebuffer needs to be blitted into a regular framebuffer,
    // then the regular framebuffer can be read from.
    GLuint temp_fb;
    glGenFramebuffers(1, &temp_fb);
    glBindFramebuffer(GL_FRAMEBUFFER, temp_fb);

    GLuint temp_tex;
    glGenTextures(1, &temp_tex);
    glBindTexture(GL_TEXTURE_2D, temp_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, window_viewport.w, window_viewport.h, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, temp_tex, 0);

    GLenum framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(framebuffer_status != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Framebuffer incomplete.\n");
        exit(EXIT_FAILURE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Blit the screen buffer to the temporary non-multisampled framebuffer.
    glBindFramebuffer(GL_READ_FRAMEBUFFER, screen_buffer.id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, temp_fb);
    glBlitFramebuffer(0, 0, window_viewport.w, window_viewport.h, 0, 0, window_viewport.w, window_viewport.h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    // Read the (x0,y0, w,h)-rectangle pixels from the temporary framebuffer.
    glBindFramebuffer(GL_FRAMEBUFFER, temp_fb);
    auto pixel_data = std::vector<uint8_t>(w * h * 4);
    glReadPixels(x0,y0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, &pixel_data[0]);

    fprintf(file, "P3\n");
    fprintf(file, "# cg_sandbox screenshot: %s\n", filename.c_str());
    fprintf(file, "%d %d\n", w, h);
    fprintf(file, "255\n");
    for (int i = h-1; i >= 0; --i) {
        for (int j = 0; j < w; j++) {
            uint8_t r = pixel_data[4*(i*w + j)+0];
            uint8_t g = pixel_data[4*(i*w + j)+1];
            uint8_t b = pixel_data[4*(i*w + j)+2];
            fprintf(file, "%d %d %d ", r,g,b);
        }
	fprintf(file, "\n");
    }

    // Clean up.
    glDeleteFramebuffers(1, &temp_fb);
    glDeleteTextures(1, &temp_tex);
    fclose(file);
}



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
    framebuffer_res_x = max_res_x;
    framebuffer_res_y = max_res_y;

    std::cout << "w:" << window_viewport.w << " h:" << window_viewport.h  << "\n";

    if (prev_window_viewport.w != window_viewport.w || prev_window_viewport.h != window_viewport.h) {
        // glBindTexture(GL_TEXTURE_2D, screen_buffer.texture);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, window_viewport.w, window_viewport.h, 0, GL_RGBA, GL_FLOAT, NULL);
        // glBindTexture(GL_TEXTURE_2D, 0);
        // glBindTexture(GL_TEXTURE_2D, screen_buffer.depth_texture);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, window_viewport.w, window_viewport.h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        // glBindTexture(GL_TEXTURE_2D, 0);
        // screen_buffer.resolution_x = window_viewport.w;
        // screen_buffer.resolution_y = window_viewport.h;
        
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, screen_buffer.texture);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, num_samples, GL_RGBA16F, window_viewport.w, window_viewport.h, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, screen_buffer.depth_texture);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, num_samples, GL_DEPTH_COMPONENT32F, window_viewport.w, window_viewport.h, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        screen_buffer.resolution_x = window_viewport.w;
        screen_buffer.resolution_y = window_viewport.h;
    }
    prev_window_viewport = window_viewport;
}

void Graphics::render(Aspect<Camera> camera)
{
    auto viewport = camera->viewport();

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
        Render 2D and 3D vector graphics.
    --------------------------------------------------------------------------------*/
    glBindFramebuffer(GL_FRAMEBUFFER, camera->framebuffer.id);
    glEnable(GL_SCISSOR_TEST);
    glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
    glScissor(viewport.x, viewport.y, viewport.w, viewport.h);

    #if 1
    /*--------------------------------------------------------------------------------
        Post-render update entities.
        NOTE: Moved here, see World.cpp.
        NOTE: This calls post_render_update for each camera!
        NOTE: This isn't reall "post render", but it has been changed quickly in order to get some mathematical rendering working...
    --------------------------------------------------------------------------------*/
    for (auto b : world.entities.aspects<Behaviour>()) {
        if (b->enabled) b->post_render_update();
    }
    #endif

    paint.render(camera);

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
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, window_width, window_height);
    glClearColor(window_background_color.x(), window_background_color.y(), window_background_color.z(), window_background_color.w());
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
    glViewport(window_viewport.x, window_viewport.y, window_width, window_height);
    glScissor(window_viewport.x, window_viewport.y, window_width, window_height);

    // Blit the multisampled screen buffer to the default framebuffer.
    glBindFramebuffer(GL_READ_FRAMEBUFFER, screen_buffer.id);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    // glBlitFramebuffer(0, 0, screen_buffer.resolution_x, screen_buffer.resolution_y,
    //                   window_viewport.x, window_viewport.y, window_width, window_height,
    //                   GL_COLOR_BUFFER_BIT, GL_NEAREST); 
    glBlitFramebuffer(0, 0, window_width, window_height,
                      0, 0, window_width, window_height,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);  //------------------------------------------------------------fix this!!!!!
                      // When blitting the framebuffer size needs to be the same as that set up in the context...
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // auto program = tone_map_gamma_correction_program;
    // program->bind();
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, screen_buffer.texture);
    // glUniform1i(program->uniform_location("hdr_image"), 0);
    // glUniform2i(program->uniform_location("hdr_image_dimensions"), screen_buffer.resolution_x, screen_buffer.resolution_y);
    // glBindVertexArray(postprocessing_quad_vao);
    // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    // glBindVertexArray(0);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // program->unbind();
}






void Graphics::compile_shaders()
{
    tone_map_gamma_correction_program = world.resources.add<GLShaderProgram>();
    tone_map_gamma_correction_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/screen_quad.vert"));
    tone_map_gamma_correction_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/tone_mapping/tone_map_gamma_correction_reinhard.frag"));
    tone_map_gamma_correction_program->link();
}
