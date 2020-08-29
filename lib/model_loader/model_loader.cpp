#include "model_loader.h"
#include "spatial_algebra/spatial_algebra.h"
#include <stdarg.h>


static ModelFileFormatLoader model_file_format_loaders[] = {
    load_OFF_model,
    load_Obj_model,
};

// Error logging for this library.
static void MLModel_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("[model_loader]: ");
    vprintf(format, args);
    va_end(args);
    exit(EXIT_FAILURE);
}
// Logging for this library.
static void log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("[model_loader]: ");
    vprintf(format, args);
    va_end(args);
}

MLModel MLModel::load(const std::string &path, MLLoadFlags flags)
{
    // Select a format based on the file suffix.
    log("Loading model from path \"%s\"...\n", path.c_str());
    const char *c_path = path.c_str();
    int file_format;
    #define FORMAT(FORMAT_NAME,DOT_SUFFIX)\
        if (strncmp(strchr(c_path, '\0')-strlen(DOT_SUFFIX), DOT_SUFFIX, strlen(DOT_SUFFIX)) == 0) {\
            file_format = MODEL_FILE_FORMAT_ ## FORMAT_NAME;\
            goto continue_here_when_format_selected;\
        }
    FORMAT(OFF, ".off");
    FORMAT(OFF, ".OFF");
    FORMAT(OBJ, ".obj");
    FORMAT(OBJ, ".OBJ");
    MLModel_error("Could not interpret model file format for file \"%s\".\n", path.c_str());
continue_here_when_format_selected:
    MLModel model;
    ModelFileFormatLoader loader = model_file_format_loaders[file_format];

    log("Interpreted suffix, loading file...\n");
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
        MLModel_error("Failed to open file \"%s\".\n", path.c_str());
    }
    bool success = loader(file, model);
    if (!success) {
        MLModel_error("Error loading model \"%s\".\n", path.c_str());
    }
    log("Successfully loaded model.\n");
    model.name = path;
    file.close();
    
    // Model post-processing.
    if (ML_LOAD_FLAG(flags, ML_COMPUTE_PHONG_NORMALS)) {
        log("Computing Phong normals...\n");
        // model.compute_phong_normals_uniformly_weighted();
        model.compute_phong_normals_angle_weighted();
    }
    if (ML_LOAD_FLAG(flags, ML_INVERT_WINDING_ORDER)) {
        log("Inverting winding order...\n");
        model.invert_winding_order();
    }

    return model;
}

void MLModel::print() const
{
    #define YESNO(BOOLEAN) ( ( BOOLEAN ) ? "Yes" : "No" )
    std::cout << "Model metadata\n";
    std::cout << "    name: " << name << "\n";
    std::cout << "    num_vertices: " << num_vertices << "\n";
    std::cout << "    has_normals: " << YESNO(has_normals) << "\n";
    std::cout << "    has_uvs: " << YESNO(has_uvs) << "\n";
    std::cout << "    has_triangles: " << YESNO(has_triangles) << "\n";
    std::cout << "    num_triangles: " << num_triangles << "\n";
}

// Model post-processing.

void MLModel::compute_phong_normals_uniformly_weighted()
{
    if (!has_triangles) return;
    if (has_normals) normals.clear();
    normals = std::vector<vec3>(num_vertices);

    for (unsigned int i = 0; i < num_triangles; i++) {
        // Assuming the model is consistently counter-clockwise winding.
        uint32_t index_a = triangles[i].a;
        uint32_t index_b = triangles[i].b;
        uint32_t index_c = triangles[i].c;
        vec3 a = positions[index_a];
        vec3 b = positions[index_b];
        vec3 c = positions[index_c];
        vec3 n = vec3::cross(b - a, c - a).normalized();
        normals[index_a] += n;
        normals[index_b] += n;
        normals[index_c] += n;
    }
    for (unsigned int i = 0; i < num_vertices; i++) {
        normals[i] = normals[i].normalized();
    }
    has_normals = true;
}
// Angle weighted normals are triangulation independent and of higher quality than uniform weighted normals.
// These normals are derived in a more principled way, attempting to mimic normals of smooth surfaces.
void MLModel::compute_phong_normals_angle_weighted()
{
    if (!has_triangles) return;
    if (has_normals) normals.clear();
    normals = std::vector<vec3>(num_vertices);

    for (unsigned int i = 0; i < num_triangles; i++) {
        // Assuming the model is consistently counter-clockwise winding.
        uint32_t index_a = triangles[i].a;
        uint32_t index_b = triangles[i].b;
        uint32_t index_c = triangles[i].c;
        vec3 a = positions[index_a];
        vec3 b = positions[index_b];
        vec3 c = positions[index_c];
        vec3 n = vec3::cross(b - a, c - a).normalized();

        float theta_a = fabs(acos(vec3::dot((b - a).normalized(), (c - a).normalized())));
        float theta_b = fabs(acos(vec3::dot((c - b).normalized(), (a - b).normalized())));
        float theta_c = fabs(acos(vec3::dot((a - c).normalized(), (b - c).normalized())));

        normals[index_a] += theta_a * n;
        normals[index_b] += theta_b * n;
        normals[index_c] += theta_c * n;
    }
    for (unsigned int i = 0; i < num_vertices; i++) {
        normals[i] = normals[i].normalized();
    }
    has_normals = true;
}


void MLModel::invert_winding_order()
{
    if (!has_triangles) return;
    for (unsigned int i = 0; i < num_triangles; i++) {
        uint32_t a = triangles[i].a;
        triangles[i].a = triangles[i].c;
        triangles[i].c = a;
    }
}
