#ifndef MODELS_H
#define MODELS_H
#include <vector>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
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
    ModelTriangle() {}
    ModelTriangle(uint32_t a, uint32_t b, uint32_t c) : a{a}, b{b}, c{c} {}
};
struct Model {
    std::string name; // The name is usually the path the model was loaded from.

    uint32_t num_vertices;
    std::vector<vec3> positions;
    bool has_normals;
    std::vector<vec3> normals;
    bool has_uvs;
    std::vector<TexCoord> uvs;

    bool has_triangles;
    std::vector<ModelTriangle> triangles;
    uint32_t num_triangles;

    void print() const;

    Model() :
        num_vertices{0},
        has_normals{false},
        has_uvs{false},
        has_triangles{false},
        num_triangles{0}
    {}

    static Model load(const std::string &path);
};

typedef bool (*ModelFileFormatLoader)(std::istream &, Model &);
enum ModelFileFormats {
    MODEL_FILE_FORMAT_OFF,
    MODEL_FILE_FORMAT_OBJ,
};

#endif // MODELS_H
