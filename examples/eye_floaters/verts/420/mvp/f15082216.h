#version 420

uniform mat4x4 mvp_matrix;
uniform float aspect_ratio;
uniform float frand;

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 fColor;

void main(void)
{
    gl_Position = mvp_matrix * vPosition;
    gl_Position.w = -gl_Position.z;

    gl_Position.x *= aspect_ratio;

    /* fColor = vec4(1 - exp(0.12*gl_Position.z), 1 - exp(0.12*gl_Position.z), 1 - exp(0.12*gl_Position.z), 1.0); */

    fColor = vColor;
    /* fColor.rgb *= 1 - 0.1 * frand; */

    /* fColor = vec4(0.1, 0.1, 1.0, 1.0); */
    /* fColor = vec4(exp(gl_Position.z), 0.0, 0.0, 1.0); */
    /* fColor = vec4(1.0, 0.5, 0.0, 1.0); */
    /* fColor.rgb *= vPosition.z; */
}
