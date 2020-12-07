#include "lighting/directional_lighting.h"
#include "lighting/point_lighting.h"

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
