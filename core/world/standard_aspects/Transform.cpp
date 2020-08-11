#include "world/standard_aspects/standard_aspects.h"


void Transform::init(vec3 _position, Quaternion _rotation)
{
    position = _position;
    rotation = _rotation;
}


void Transform::init(float x, float y, float z)
{
    position = vec3(x,y,z);
    rotation = Quaternion::identity();
}


void Transform::init(vec3 _position)
{
    position = _position;
    rotation = Quaternion::identity();
}


void Transform::init_lookat(vec3 position, vec3 target)
{
    position = position;
    lookat(target);
}


vec3 axis_angle_rotate(vec3 axis, float angle, vec3 v)
{
    vec3 Z = vec3::cross(v, axis);
    vec3 X = vec3::cross(axis, Z);
    return vec3::dot(v, axis)*axis + cos(angle)*X + sin(angle)*Z;
}


// lookat assumes that the plane of pitch rotation is spanned by the world Y-axis and the direction to the target.
void Transform::lookat(vec3 target)
{
    vec3 f = (target - position).normalized();
    vec3 fp = vec3(f.x(), 0, f.z()).normalized();
    float theta = acos(fp.z());
    if (fp.x() < 0) theta = -theta;
    // X' = cross(f', (0,1,0))
    vec3 Xp = vec3(-fp.z(), 0, fp.x());
    float psi = acos(vec3::dot(f, fp));
    if (f.y() < 0) psi = -psi;

    Quaternion q1 = Quaternion::from_axis_angle(vec3(0,1,0), theta);
    Quaternion q2 = Quaternion::from_axis_angle(Xp, psi);
    rotation = q2 * q1;
}


mat4x4 Transform::matrix() const
{
    Quaternion inverse_rotation = rotation.inverse();
    Quaternion q1 = rotation * Quaternion(0,1,0,0) * inverse_rotation;
    Quaternion q2 = rotation * Quaternion(0,0,1,0) * inverse_rotation;
    Quaternion q3 = rotation * Quaternion(0,0,0,1) * inverse_rotation;

    // note: mat4x4 constructor parameter order is column-major.
    return mat4x4(q1.i(),q1.j(),q1.k(),0,
                  q2.i(),q2.j(),q2.k(),0,
                  q3.i(),q3.j(),q3.k(),0,
                  position.x(),position.y(),position.z(),1);
}


mat4x4 Transform::inverse_matrix() const
{
    Quaternion inverse_rotation = rotation.inverse();
    Quaternion q1 = rotation * Quaternion(0,1,0,0) * inverse_rotation;
    Quaternion q2 = rotation * Quaternion(0,0,1,0) * inverse_rotation;
    Quaternion q3 = rotation * Quaternion(0,0,0,1) * inverse_rotation;
    mat4x4 M(q1.i(),q2.i(),q3.i(),0,
             q1.j(),q2.j(),q3.j(),0,
             q1.k(),q2.k(),q3.k(),0,
             0,0,0,1);
    vec4 p = M * vec4(-position, 1);
    M.entry(0,3) = p.x();
    M.entry(1,3) = p.y();
    M.entry(2,3) = p.z();
    return M;
}
