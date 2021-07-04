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
        Tone map and gamma correct the screen buffer when copying.
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
    auto program = tone_map_gamma_correction_program;
    program->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, screen_buffer.texture);
    glUniform1i(program->uniform_location("hdr_image"), 0);
    glUniform2i(program->uniform_location("hdr_image_dimensions"), screen_buffer.resolution_x, screen_buffer.resolution_y);
    glBindVertexArray(postprocessing_quad_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    program->unbind();
}






void Graphics::compile_shaders()
{
    tone_map_gamma_correction_program = world.resources.add<GLShaderProgram>();
    tone_map_gamma_correction_program->add_shader(GLShader(VertexShader, RESOURCE_PATH "shaders/screen_quad.vert"));
    tone_map_gamma_correction_program->add_shader(GLShader(FragmentShader, RESOURCE_PATH "shaders/tone_mapping/tone_map_gamma_correction_reinhard.frag"));
    tone_map_gamma_correction_program->link();
}
