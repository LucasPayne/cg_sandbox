#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in int face_number;

uniform mat4x4 mvp_matrix;

out vec2 f_uv;
flat out int f_face;

uniform float time;

void main()
{
    f_uv = uv;
    f_face = face_number;

    //vec3 pos = position + 0.1*vec3(0, 0.025*sin(time)+0.01*sin(2.2*time), 0.005*cos(0.666*time));
    //gl_Position = mvp_matrix * vec4(pos, 1);

    gl_Position = mvp_matrix * vec4(position, 1);
}
