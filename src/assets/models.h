#ifndef MODELS_H
#define MODELS_H
#include "core.h"
#include "gl/gl.h"
#include "rendering/vertex_arrays.h"
#include "mathematics/mathematics.h"

struct TexCoord {
    float u;
    float v;
    TexCoord(float u, float v) : u{u}, v{v} {}
};

struct Model {
    int num_vertices;
    std::vector<vec3> positions;
    bool has_normals;
    std::vector<vec3> normals;
    bool has_uvs;
    std::vector<TexCoord> uvs;
};

namespace Models {

typedef uint32_t ModelPostprocessBits;
// Duplicate vertices for each triangle that uses it. This vertex has the normal of the triangle.
// This allows flat shading to be done.
#define MODEL_FLAT_NORMALS (1 << 0)
// Compute normals for each vertex as the average normal of incident triangles.
// Incompatible with MODEL_FLAT_NORMALS.
#define MODEL_PHONG_NORMALS (1 << 1)
// Compute tangent frames, consisting of tangents and binormals,
// Depends on UV coordinates being available.
#define MODEL_COMPUTE_TANGENTS_AND_BINORMALS (1 << 2)

Model load(const std::string &path);

VertexArrayData load_OFF_model(const std::string &path, bool compute_normals = true, float scale = 1.0);

}; // namespace Models
#endif // MODELS_H
