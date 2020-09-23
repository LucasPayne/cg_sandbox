#version 420


// in TES_OUT {
//     vec3 normal;
// } fs_in;


out vec4 color;

void main(void)
{
    color = vec4(1,0,0,1);

    // vec3 light_dir = vec3(1,-1,1);
    // vec3 diffuse = vec3(0, 0.6, 0);
    // color = vec4(max(0, dot(normal, -light_dir)) * diffuse, 1);
}

