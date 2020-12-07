
#include "directional_lighting.cpp"
#include "point_lighting.cpp"

void Graphics::update_lights()
{
    update_directional_lights();
    update_point_lights();
}

void Graphics::lighting(Aspect<Camera> camera)
{
    directional_lighting(camera);
    point_lighting(camera);
}
