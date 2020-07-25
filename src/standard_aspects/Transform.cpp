#include "standard_aspects/standard_aspects.h"

void Transform::init(float x, float y, float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
    rotation[0] = 0;
    rotation[1] = 0;
    rotation[2] = 0;
}
void Transform::init(float x, float y, float z, float theta_x, float theta_y, float theta_z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
    rotation[0] = theta_x;
    rotation[1] = theta_y;
    rotation[2] = theta_z;
}
