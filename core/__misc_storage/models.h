#ifndef MODELS_H
#define MODELS_H
#include "core.h"
#include "mathematics/mathematics.h"

struct TexCoord {
    float u;
    float v;
    TexCoord(float u, float v) : u{u}, v{v} {}
};
struct ModelTriangle {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    ModelTriangle(uint32_t a, uint32_t b, uint32_t c) : a{a}, b{b}, c{c} {}
};
struct Model {
    int num_vertices;
    std::vector<vec3> positions;
    bool has_normals;
    std::vector<vec3> normals;
    bool has_uvs;
    std::vector<TexCoord> uvs;

    bool has_triangles;
    std::vector<ModelTriangle> triangles;
    int num_triangles;

    static Model load(const std::string &path);
};

typedef bool (*ModelFileFormatLoader)(const std::istream &, Model &);
extern static const ModelFileFormatLoader model_file_format_loaders[];
enum ModelFileFormats {
    MODEL_FILE_FORMAT_OFF,
    MODEL_FILE_FORMAT_OBJ,
};
#include "assets/models/model_file_format_OFF.cpp"
#include "assets/models/model_file_format_OBJ.cpp"

#endif // MODELS_H
