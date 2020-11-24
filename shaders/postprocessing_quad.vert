// Post-processing effects and deferred lighting shaders can use this simple vertex shader,
// which will pass on the screen coordinates ((0,0) top-left) to the fragment shader, when used with
// the standard screen-filling quad.
#version 420

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 v_uv;

out vec2 uv;

void main(void)
{
    gl_Position = vec4(position, 0, 1);
    uv = v_uv;
}
