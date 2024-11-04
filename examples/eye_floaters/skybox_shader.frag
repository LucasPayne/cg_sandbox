#version 420

in vec2 f_uv;
flat in int f_face;

out vec4 color;

uniform sampler2D images[6];
uniform float time;
uniform float brightness;

void main()
{
    //if (int(f_uv * 10) % 2 == 0)
    //{
    //    color = vec4(texture(images[f_face], f_uv).rgb, 1);
    //}
    //else {
    //    color = vec4(f_face/5.f, 0, 0, 1);
    //}
    //float alpha = 0.0025;
    //if (f_uv.x < alpha || f_uv.x > 1-alpha || f_uv.y < alpha || f_uv.y > 1-alpha) color = vec4(f_face/5.f,0,0,1);

    color = vec4(texture(images[f_face], vec2(f_uv.x, 1-f_uv.y)).rgb, 1);
    //color *= 1.3+0.05*sin(0.2*time);

    color.rgb *= brightness;

    color.rgb *= 1.25;
    color.r = clamp(color.r, 0, 1);
    color.g = clamp(color.g, 0, 1);
    color.b = clamp(color.b, 0, 1);
}
