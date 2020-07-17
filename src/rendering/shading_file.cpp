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

GeometricMaterial parse_geometric_material_file(const std::string string_path)
{
    ShadingFileASTNode *root = parse_shading_file(string_path);
    // Validate that this has the relevant directives and sections for a geometric material (gmat) shading file.

    print_shading_file_ast(root);
    
    GeometricMaterial gmat;
    return gmat;
}

// print with indents
#include <stdarg.h>
static void iprint(int num_indents, const char *format, ...)
{
    const int indent_width = 4;
    va_list args;
    va_start(args, format);
    for (int i = 0; i < num_indents*indent_width; i++) putchar(' ');
    vprintf(format, args);
    va_end(args);
}
void print_shading_file_ast(ShadingFileASTNode *root, int indent)
{
    ShadingFileASTNode *cur = root;
    while (cur != nullptr) {
        if (cur->kind() == SHADING_FILE_NODE_ROOT) {
            iprint(indent, "Root\n");
        } else if (cur->kind() == SHADING_FILE_NODE_DIRECTIVE) {
            iprint(indent, "Directive\n");
            ShadingFileASTDirective *directive = (ShadingFileASTDirective *) cur;
            iprint(indent, " text: %s\n", directive->text);
        } else if (cur->kind() == SHADING_FILE_NODE_SECTION) {
            iprint(indent, "Section\n");
            ShadingFileASTSection *section = (ShadingFileASTSection *) cur;
            iprint(indent, " name: %s\n", section->name);
            print_shading_file_ast(section->first_child, indent + 1);
        } else if (cur->kind() == SHADING_FILE_NODE_OUTPUT) {
            iprint(indent, "Output\n");
            ShadingFileASTOutput *output = (ShadingFileASTOutput *) cur;
            iprint(indent+1, "%s %s\n", output->type, output->name);
            iprint(indent+1, "snippet----------------------------------------------------\n");
            iprint(indent+1, "%s", output->snippet);
            iprint(indent+1, "-----------------------------------------------------------\n");
            ShadingFileASTParameter *param = output->parameter_list;
            while (param != NULL) {
                if (param->kind == SHADING_PARAMETER_IN) {
                    iprint(indent+2, "in %s %s\n", param->type, param->name);
                } else {
                    iprint(indent+2, "uniform %s %s\n", param->type, param->name);
                }
                param = param->next;
            }
        }
        cur = cur->next;
    }
}
