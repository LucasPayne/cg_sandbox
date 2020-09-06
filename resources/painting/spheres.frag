#version 420

in tessellated {
    vec2 uv;
    vec4 f_color;
};

out vec4 color;




void main(void)
{
    float x = 2*uv.x - 1;
    float y = 2*uv.y - 1;

    // Sphere origin: 0,0,0
    // Sphere radius: 1
    // Ray origin: x,y,-2
    // Ray direction: 0,0,1
    float discrim = 16 - 4*(x*x + y*y + 3);
    if (discrim < 0) discard;
    float t = 0.5 * (4 + sqrt(discrim));
    vec3 pos = vec3(x,y,-2 + t);

    vec3 light_dir = vec3(1,1,1);

    vec3 n = normalize(pos);
    color = f_color * max(0, dot(n, light_dir));
}
