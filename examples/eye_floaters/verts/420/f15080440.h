/*--------------------------------------------------------------------------------
    Testing tesselation.
control shader
--------------------------------------------------------------------------------*/
#version 420

layout (vertices = 4) out;

void main(void)
{
    gl_TessLevelOuter[0] = 2.0;
    gl_TessLevelOuter[1] = 4.0;
    gl_TessLevelOuter[2] = 6.0;
    gl_TessLevelOuter[3] = 8.0;

    gl_TessLevelInner[0] = 8.0;
    gl_TessLevelInner[1] = 8.0;

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
