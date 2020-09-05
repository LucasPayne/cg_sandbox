#include "world/world.h"


void Painting::render()
{
    printf("rendering spheres.\n");
    for (auto position : sphere_positions) {
        std::cout << position << "\n";
    }

    // GLuint vao;
    // glCreateVertexArrays(1, &vao);
    // glBindVertexArray(vao);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) 0);
    // glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) offsetof(PaintingSphere, radius));
    // glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(PaintingSphere), (const void *) offsetof(PaintingSphere, color));
    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);
    // glEnableVertexAttribArray(2);

    // GLuint vertex_buffer;
    // glGenBuffers(1, &vertex_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(PaintingSphere) * spheres.size(), (const void *) &spheres[0], GL_DYNAMIC_DRAW);

    
    VertexArrayData vad;
    vad.layout.num_vertices = sphere_positions.size();
    vad.layout.indexed = false;
    vad.add_attribute("v_position", 3, GL_FLOAT, &sphere_positions[0]);
    vad.add_attribute("sphere_radius", 1, GL_FLOAT, &sphere_radii[0]);
    vad.add_attribute("v_color", 4, GL_FLOAT, &sphere_colors[0]);

    auto va = VertexArray::from_vertex_array_data(vad);
    auto va_resource = world.resources.add<VertexArray>();
    *va_resource = va;

    for (auto camera : world.entities.aspects<Camera>()) {
        if (!camera->rendering_to_framebuffer) continue;
        graphics.begin_camera_rendering(camera);
        graphics.end_camera_rendering(camera);
    }
}


void Painting::clear()
{
    // spheres.clear();
    sphere_positions.clear();
    sphere_radii.clear();
    sphere_colors.clear();
}


void Painting::sphere(vec3 position, float radius, vec4 color)
{
    // spheres.push_back(PaintingSphere(position, radius, color));
    sphere_positions.push_back(position);
    sphere_radii.push_back(radius);
    sphere_colors.push_back(color);
}


void Painting::init()
{
}
