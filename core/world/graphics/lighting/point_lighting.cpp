
DESCRIPTOR_INSTANCE(PointLight);
BEGIN_ENTRIES(PointLight)
    ENTRY(color)
    ENTRY(radius)
END_ENTRIES()


void Graphics::update_point_lights()
{
    auto shadow_map_sm = shading.shading_models.load("shaders/shadows/shadow_map.sm");
    auto shadow_map_shading_model = ShadingModelInstance(shadow_map_sm);
}

void Graphics::point_lighting(Aspect<Camera> camera)
{

}
