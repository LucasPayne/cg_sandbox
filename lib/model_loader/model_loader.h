#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H
#include <vector>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include "spatial_algebra/spatial_algebra.h"

struct TexCoord {
    float u;
    float v;
    TexCoord(float u, float v) : u{u}, v{v} {}
};
struct MLModelTriangle {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    MLModelTriangle() {}
    MLModelTriangle(uint32_t a, uint32_t b, uint32_t c) : a{a}, b{b}, c{c} {}
};
struct MLModel {
    std::string name; // The name is usually the path the model was loaded from.

    uint32_t num_vertices;
    std::vector<vec3> positions;
    bool has_normals;
    std::vector<vec3> normals;
    bool has_uvs;
    std::vector<TexCoord> uvs;

    bool has_triangles;
    std::vector<MLModelTriangle> triangles;
    uint32_t num_triangles;

    void print() const;

    MLModel() :
        num_vertices{0},
        has_normals{false},
        has_uvs{false},
        has_triangles{false},
        num_triangles{0}
    {}

    static MLModel load(const std::string &path);
};

typedef bool (*ModelFileFormatLoader)(std::istream &, MLModel &);
enum ModelFileFormats {
    MODEL_FILE_FORMAT_OFF,
    MODEL_FILE_FORMAT_OBJ,
};
bool load_Obj_model(std::istream &stream, MLModel &model);
bool load_OFF_model(std::istream &stream, MLModel &model);

#endif // MODEL_LOADER_H