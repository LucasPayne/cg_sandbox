#include "standard_aspects/standard_aspects.h"

void Transform::init(vec3 _position, vec3 _rotation)
{
    position = _position;
    rotation = _rotation;
}
void Transform::init(float x, float y, float z)
{
    position = vec3(x,y,z);
    rotation = vec3(0,0,0);
}
void Transform::init(float x, float y, float z, float theta_x, float theta_y, float theta_z)
{
    position = vec3(x,y,z);
    rotation = vec3(theta_x,theta_y,theta_z);
}
