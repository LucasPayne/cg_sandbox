//---todo: Make this work.
#version 420

uniform sampler2D hdr_image;
uniform ivec2 hdr_image_dimensions;
// Multisampling.
// uniform int num_samples;
// uniform sampler2DMs hdr_multisample_image;

in vec2 uv;
out vec4 color;

// // https://stackoverflow.com/questions/42878216/opengl-how-to-draw-to-a-multisample-framebuffer-and-then-use-the-result-as-a-n
// vec4 multisample(sampler2DMS sampler)

void main(void)
{
    // vec3 col = texelFetch(hdr_image, ivec2(hdr_image_dimensions * uv), 0).rgb;
    // col /= col + vec3(1.f); // Reinhard tone map
    // color = vec4(max(min(12.92 * col, vec3(0.04045)), 1.055 * pow(col, vec3(1/2.4f)) - vec3(0.055)), 1); // Gamma correct

    // color = texture(hdr_image, uv);

    

}
