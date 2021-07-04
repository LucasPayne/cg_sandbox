//---todo: Make this work.
#version 420

uniform sampler2D hdr_image;
uniform ivec2 hdr_image_dimensions;

in vec2 uv;
out vec4 color;

void main(void)
{
    // vec3 col = texelFetch(hdr_image, ivec2(hdr_image_dimensions * uv), 0).rgb;
    // col /= col + vec3(1.f); // Reinhard tone map
    // color = vec4(max(min(12.92 * col, vec3(0.04045)), 1.055 * pow(col, vec3(1/2.4f)) - vec3(0.055)), 1); // Gamma correct
    color = texture(hdr_image, uv);
}
