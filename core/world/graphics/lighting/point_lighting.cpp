
DESCRIPTOR_INSTANCE(PointLight);
BEGIN_ENTRIES(PointLight)
    ENTRY(color)
    ENTRY(radius)
END_ENTRIES()


void Graphics::update_point_lights()
{
    auto shadow_map_sm = shading.shading_models.load("shaders/shadows/shadow_map.sm");
    auto shadow_map_shading_model = ShadingModelInstance(shadow_map_sm);

    for (auto light : world.entities.aspects<PointLight>()) {
        for (auto camera : world.entities.aspects<Camera>()) {
            auto &sm = point_light_data(light).shadow_map(camera);
            
            // for_drawable(


        }
    }

}

void Graphics::point_lighting(Aspect<Camera> camera)
{

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

    PointLightShadowMap sm;
    // Create a framebuffer for each side of the cube.
    for (int i = 0; i < 6; i++) {
        GLuint fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, cube_map, 0, i);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            fprintf(stderr, "Incomplete framebuffer when initializing shadow maps.\n");
            exit(EXIT_FAILURE);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        sm.fbos[i] = fbo;
    }
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

