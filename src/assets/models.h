#ifndef MODELS_H
#define MODELS_H
#include "core.h"
#include "gl/gl.h" // probably shouldn't have this
#include "rendering/vertex_arrays.h"
namespace Models {

VertexArrayData load_OFF_model(const std::string &path);

}; // namespace Models
#endif // MODELS_H
