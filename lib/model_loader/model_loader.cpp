#include "model_loader.h"

#include "model_file_format_OFF.cpp"
#include "model_file_format_OBJ.cpp"
static ModelFileFormatLoader model_file_format_loaders[] = {
    load_OFF_model,
    load_OBJ_model,
};

Model Model::load(const std::string &path)
{
    // Select a format based on the file suffix.
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
    fprintf(stderr, "ERROR: Could not interpret model file format for file \"%s\".\n", path.c_str());
    exit(EXIT_FAILURE);
continue_here_when_format_selected:
    Model model;
    ModelFileFormatLoader loader = model_file_format_loaders[file_format];

    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
        fprintf(stderr, "Failed to open file.\n");
        exit(EXIT_FAILURE);
    }
    bool success = loader(file, model);
    if (!success) {
        fprintf(stderr, "Error loading model.\n");
        exit(EXIT_FAILURE);
    }
    model.name = path;
    return model;
}

void Model::print() const
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
