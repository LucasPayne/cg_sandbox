/*--------------------------------------------------------------------------------
    Depth of field near field pass.
--------------------------------------------------------------------------------*/
#version 420


uniform sampler2D confusion;
uniform sampler2D image;

uniform float inv_screen_width;
uniform float inv_screen_height;

in vec2 uv;
out vec4 color;

#define PI 3.14159

void main(void)
{
    #define NUM_SAMPLES 12
    float inv_num_samples = 1.f / NUM_SAMPLES;
    const vec2 poisson_samples[NUM_SAMPLES] = {
        vec2(-0.3835597153857353, -0.7778487407064922),
        vec2(0.40130091048388405, 0.19374174659263033),
        vec2(-0.45187866361450846, -0.25544445301371344),
        vec2(-0.31441265317647504, 0.5091412445894341),
        vec2(-0.10533080746062273, 0.3357803156039252),
        vec2(-0.5155143691045783, 0.30967491037873374),
        vec2(-0.2969392791180032, 0.0010459758074339298),
        vec2(-0.16470787945426935, -0.37760477122852754),
        vec2(-0.056825134835887914, -0.9681567383908469),
        vec2(0.7031362634484448, 0.4255112306648199),
        vec2(-0.17933857483077387, 0.8697576875147421),
        vec2(-0.15206507065241204, -0.7761207861878452)
    };
    // Pseudo-random noise taken off of stackoverflow.
    float rand_theta = 2*PI*fract(sin(dot(uv.xy, vec2(12.9898, 78.233))) * 43758.5453);
    float cos_rand_theta = cos(rand_theta);
    float sin_rand_theta = sin(rand_theta);

    float r = 20*texture(confusion, uv).x;
    vec4 accumulation = vec4(0,0,0,0);
    for (int i = 0; i < NUM_SAMPLES; i++) {
        vec2 rotated_poisson_sample = vec2(cos_rand_theta*poisson_samples[i].x + sin_rand_theta*poisson_samples[i].y,
                                           -sin_rand_theta*poisson_samples[i].x + cos_rand_theta*poisson_samples[i].y);
        vec2 sample_uv = uv + r * vec2(inv_screen_width, inv_screen_height) * rotated_poisson_sample;
        accumulation += inv_num_samples * texture(confusion, sample_uv).a * texture(image, sample_uv);
    }
    // color = vec4(0.5*(texture(image, uv).rgb * texture(image,uv).a) + 0.5 * accumulation.rgb, 1);
    color = vec4(accumulation.rgb, 1);
}
