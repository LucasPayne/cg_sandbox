#ifndef MODELS_H
#define MODELS_H
#include "core.h"
#include "rendering/vertex_arrays.h"

namespace Models {

VertexArrayData load_OFF_model(const std::string &path)
{
    #define load_error(ERROR_STR) {\
        printf("OFF MODEL LOAD ERROR: %s\n", ( ERROR_STR ));\
        exit(EXIT_FAILURE);\
    }
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
        load_error("Failed to open path.");
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line;
    }
}

}; // namespace Models
#endif // MODELS_H
