#include "model_loader/model_loader.h"
#include <map>
#include <tuple>


bool load_STL_model(std::istream &stream, MLModel &model)
{
    auto load_error = [&](const std::string &error_string) {
        std::cerr << "STL model load error: " << error_string << "\n";
        exit(1);
    };
    std::string line;
    auto next_line = [&]()->bool {
        while (true) {
            if (!std::getline(stream, line)) return false;
            // Skip lines which are all whitespace.
            if (strspn(line.c_str(), " ") == line.length()) continue;
            // Remove leading whitespace.
            for (auto c = line.begin(); c != line.end(); ++c) {
                if (*c == ' ') line.erase(c);
            }
            return true;
        }
    };
    if (!next_line()) load_error("No data.");
    if (!(line.length() >= strlen("solid ") && strncmp(line.c_str(), "solid ", strlen("solid ")))) {
        load_error("An STL file must start with \"solid {name}\".");
    }

    // Vertices
    std::map<std::tuple<float, float, float>, uint32_t> position_to_index;
    std::vector<vec3> positions;
    // Triangles
    std::vector<MLModelTriangle> triangles;

    int num_triangles = 0;
    int num_vertices = 0;
    while (next_line()) {
        float nx, ny, nz;
        if (sscanf(line.c_str(), "facet normal %f %f %f\n", &nx, &ny, &nz) != 3) load_error("Malformed facet normal line.");

        MLModelTriangle triangle;

        if (!next_line() || line != "outer loop") load_error("Next line must be \"outer loop\".");
        for (int i = 0; i < 3; i++) {
            float x, y, z;
            if (!next_line() || sscanf(line.c_str(), "vertex %f %f %f", &x, &y, &z)) {
                load_error("Three vertices of the form \"vertex x y z\" must be declared.");
            }
            uint32_t vertex_index;
            auto position_tuple = std::tuple<float, float, float>(x, y, z);
            auto found = position_to_index.find(position_tuple);
            if (found == position_to_index.end()) {
                vertex_index = num_vertices;
                position_to_index[position_tuple] = vertex_index;
                positions.push_back(vec3(x,y,z));
                num_vertices ++;
            } else {
                vertex_index = found->second;
            }
            triangle[i] = vertex_index;
        }
        if (!next_line() || line != "endloop") load_error("Next line must be \"endloop\".");
        if (!next_line() || line != "endfacet") load_error("Next line must be \"endfacet\".");
        triangles[num_triangles] = triangle;
        num_triangles ++;
    }
    if (!next_line() || 
            !(line.length() >= strlen("solid ") && strncmp(line.c_str(), "solid ", strlen("solid ")))) {
        load_error("An STL file must end with \"endsolid {name}\".");
    }

    model.num_vertices = num_vertices;
    model.positions = positions;
    model.has_triangles = true;
    model.triangles = triangles;
    model.num_triangles = num_triangles;

    return true;
}
