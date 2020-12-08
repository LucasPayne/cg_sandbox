#version 420

uniform samplerCube sprite;
uniform int layer;

in vec2 f_uv;
out vec4 color;

void main(void)
{
    vec3 dir;
    switch (layer) {
        case 0: // +X
            dir = vec3(1, 2*f_uv.y-1, 2*f_uv.x-1); break;
        case 1: // -X
            dir = vec3(-1, 2*f_uv.y-1, -(2*f_uv.x-1)); break;
        case 2: // +Y
            dir = vec3(2*f_uv.x-1, 1, 2*f_uv.y-1); break;
        case 3: // -Y
            dir = vec3(2*f_uv.x-1, -1, -(2*f_uv.y-1)); break;
        case 4: // +Z
            dir = vec3(-(2*f_uv.x-1), 2*f_uv.y-1, 1); break;
        case 5: // -Z
            dir = vec3(2*f_uv.x-1, 2*f_uv.y-1, -1); break;
    };
    color = vec4(texture(sprite, dir).rgb, 1);
}
