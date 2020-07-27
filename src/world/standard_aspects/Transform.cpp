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


void Transform::init_lookat(vec3 position, vec3 target, vec3 up)
{
    position = position;
    lookat(target, up);
}
void Transform::lookat(vec3 target, vec3 up)
{
    // Compute the angle to rotate the plane spanned by Z and forward, to send Z to forward.
    vec3 forward = (target - position).normalized();
    vec3 axis = vec3(-forward.y(), forward.x(), 0).normalized();
    float angle = acos(forward.z());
    
    // Transform the given up vector (it is taken along when Z is sent to forward).
    vec3 new_up;
    {
        vec3 X = vec3::cross(up, axis);
        vec3 Z = vec3::cross(axis, X);
        //cos(angle) = forward.z(), sin(angle) = sqrt(1 - forward.z()*forward.z())
        new_up = axis * vec3::dot(up, axis) + cos(angle)*X + sin(angle)*Z;
    }
    // Compute the angle new_up makes with its projection onto span{new_up, forward}.
    vec3 proj_new_up = new_up * (1 - vec3::dot(new_up, vec3::cross(up, forward)));
    vec3 new_up_rotated_to_plane = proj_new_up.normalized();
    float angle_to_plane = acos(vec3::dot(new_up, new_up_rotated_to_plane));
    vec3 axis_to_plane = vec3::cross(new_up, new_up_rotated_to_plane);

    Quaternion q1 = Quaternion::from_axis_angle(angle * axis);
    Quaternion q2 = Quaternion::from_axis_angle(angle_to_plane * axis_to_plane);
    rotation = q1 * q2;
}

mat4x4 Transform::matrix() const
{
    Quaternion q1 = rotation * Quaternion(0,1,0,0) * rotation.inverse();
    Quaternion q2 = rotation * Quaternion(0,0,1,0) * rotation.inverse();
    Quaternion q3 = rotation * Quaternion(0,0,0,1) * rotation.inverse();

    // note: mat4x4 constructor parameter order is column-major.
    return mat4x4(q1.i(),q1.j(),q1.k(),0,
                  q2.i(),q2.j(),q2.k(),0,
                  q3.i(),q3.j(),q3.k(),0,
                  position.x(),position.y(),position.z(),1);
}
mat4x4 Transform::inverse_matrix() const
{
    return mat4x4(1,0,0,0,
                  0,1,0,0,
                  0,0,1,0,
                  -position.x(),-position.y(),-position.z(),1);
}
