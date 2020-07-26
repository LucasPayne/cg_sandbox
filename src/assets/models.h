#ifndef MODELS_H
#define MODELS_H
#include "core.h"
#include "gl/gl.h" // probably shouldn't have this
#include "rendering/vertex_arrays.h"
#include "mathematics/mathematics.h"
namespace Models {

VertexArrayData load_OFF_model(const std::string &path, bool compute_normals = true, float scale = 1.0);

}; // namespace Models
#endif // MODELS_H
