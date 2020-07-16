/*--------------------------------------------------------------------------------
    Shading file parsing.
--------------------------------------------------------------------------------*/
#include "rendering/rendering.h"

ShadingFileASTNode *parse_shading_file(const std::string string_path)
{
    const char *path = string_path.c_str();
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Shading file \"%s\" doesn't exist.\n", path);
        exit(EXIT_FAILURE);
    }
    parse_shading_file_push_file(file);
    ShadingFileASTNode *root = NULL;
    int error_code = SHADING_FILE_BISON_PARSE_FUNCTION(&root);
    if (root == NULL) {
        // no AST retrieved.
        fprintf(stderr, "ERROR: Bison yyparse function did not output the AST root!\n");
        exit(EXIT_FAILURE);
    } else if (error_code == 1) {
        // invalid input.
        fprintf(stderr, "ERROR: Failed to parse shading file.\n");
        exit(EXIT_FAILURE);
    } else if (error_code == 2) {
        // out-of-memory error (or maybe a misc. bison error ...)
        fprintf(stderr, "FATAL ERROR: Something went very wrong when attempting to parse a shading file.\n");
        exit(EXIT_FAILURE);
    }
    return root;
}
