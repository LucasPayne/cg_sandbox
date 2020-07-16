/*--------------------------------------------------------------------------------
    Shading file parsing.
--------------------------------------------------------------------------------*/
#include "rendering/rendering.h"

#define SHADING_FILE_BISON_PARSE_FUNCTION yyparse
int SHADING_FILE_BISON_PARSE_FUNCTION(void);

ShadingFile parse_shading_file(const std::string string_path)
{
    const char *path = string_path.c_str();
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Shading file \"%s\" doesn't exist.\n", path);
        exit(EXIT_FAILURE);
    }
    parse_shading_file_push_file(file);
    SHADING_FILE_BISON_PARSE_FUNCTION();
}
