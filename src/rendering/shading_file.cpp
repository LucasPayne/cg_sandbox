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
    ShadingFileASTNode *root = nullptr;
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


// Functions for traversing the shading-file abstract syntax tree.
// These are used by the specialized functions for parsing different types of shading files,
// and converting them to the data structure that the application runtime will actually use.
static ShadingFileASTDirective *find_directive(ShadingFileASTNode *node, const std::string match)
{
    // Search this section for a certain directive. Only registers the last match.
    ShadingFileASTDirective *last_found = nullptr;
    while (node != nullptr) {
        if (node->kind() == SHADING_FILE_NODE_DIRECTIVE) {
            auto *directive = (ShadingFileASTDirective *) node;
            if (directive->text == match) { //-could do a regex thing, if that would be useful.
                last_found = directive;
            }
        }
        node = node->next;
    }
    return last_found;
}
static ShadingFileASTNode *find_section(ShadingFileASTNode *node, const std::string name)
{
    // Find a subsection of the given name in the section starting at the given node.
    // Returns the first node in that subsection.
    ShadingFileASTSection *last_found = nullptr;
    while (node != nullptr) {
        if (node->kind() == SHADING_FILE_NODE_SECTION) {
            ShadingFileASTSection *section = (ShadingFileASTSection *) node;
            if (section->name == name) {
                last_found = section;
            }
        }
        node = node->next;
    }
    return last_found->first_child;
}

static ShadingFileASTOutput *first_output(ShadingFileASTNode *node)
{
    // Find the first output starting at the given node in this section.
    if (node == nullptr) return nullptr;
    do {
        if (node->kind() == SHADING_FILE_NODE_OUTPUT) return (ShadingFileASTOutput *) node;
        node = node->next;
    } while (node != nullptr);
    return nullptr;
}
static ShadingFileASTOutput *next_output(ShadingFileASTNode *node)
{
    // Find the next output starting at the given node in this section.
    while (node != nullptr) {
        if ((node = node->next) == nullptr) return nullptr;
        if (node->kind() == SHADING_FILE_NODE_OUTPUT) return (ShadingFileASTOutput *) node;
    }
    return nullptr;
}

static ShadingDataflow read_dataflow(ShadingFileASTNode *node)
{
    // Collect the ouputs in the node's section, starting at the node, into a dataflow structure.

    ShadingDataflow dataflow;

    ShadingFileASTOutput *output = first_output(node);
    std::vector<ShadingOutput> outputs(0);
    do {
        // Each output is converted from its form in the AST to its form as stored in the ShadingDataflow structure.
        outputs.push_back(output->deastify());
    } while ((output = next_output(output)) != nullptr);
    dataflow.outputs = outputs;
    return dataflow;
}

/*
gmat
Starts with directive
#type gmat
Has directive
#primitive {primitive_type}
Has one section (currently)
section vertex { }

mat
Starts with directive
#type mat
outputs in root section are used.
*/
GeometricMaterial parse_geometric_material_file(const std::string string_path)
{
    printf("Parsing geometric material file.\n");
    #define parse_error(ERROR_STR) {\
        fprintf(stderr, "GEOMETRIC MATERIAL PARSE ERROR: %s\n", ( ERROR_STR ));\
        exit(EXIT_FAILURE);\
    }
    ShadingFileASTNode *root = parse_shading_file(string_path);
    print_shading_file_ast(root);

    // Validate that this has the relevant directives and sections for a geometric material (gmat) shading file.
    if (find_directive(root, "type gmat") == nullptr) parse_error("Geometric materials must contain \"#type gmat\"");
    //-todo: primitive type
    ShadingFileASTNode *vertex_section;
    if ((vertex_section = find_section(root, "vertex")) == nullptr) parse_error("Geometric materials must contain a \"vertex\" section.");

    // Collect outputs in the vertex section.
    ShadingDataflow dataflow = read_dataflow(vertex_section);

    GeometricMaterial gmat;
    //-todo: set primitive type
    gmat.dataflow = dataflow;
    printf("Parsed dataflow\n");
    gmat.dataflow.print();
    return gmat;
    #undef parse_error
}
Material parse_material_file(const std::string string_path)
{
    printf("Parsing material file.\n");
    #define parse_error(ERROR_STR) {\
        fprintf(stderr, "MATERIAL PARSE ERROR: %s\n", ( ERROR_STR ));\
        exit(EXIT_FAILURE);\
    }
    ShadingFileASTNode *root = parse_shading_file(string_path);
    print_shading_file_ast(root);

    // Validate that this has the relevant directives and sections for a material (mat) shading file.
    if (find_directive(root, "type mat") == nullptr) parse_error("Materials must contain \"#type gmat\"");

    ShadingFileASTNode *frag_section;
    if ((frag_section = find_section(root, "frag")) == nullptr) parse_error("Materials must contain a \"frag\" section.");

    // Collect outputs in the root section.
    ShadingDataflow dataflow = read_dataflow(frag_section);

    Material mat;
    mat.dataflow = dataflow;
    return mat;
    #undef parse_error
}
ShadingModel parse_shading_model_file(const std::string string_path)
{
    printf("Parsing shading model file.\n");
    #define parse_error(ERROR_STR) {\
        fprintf(stderr, "SHADING MODEL PARSE ERROR: %s\n", ( ERROR_STR ));\
        exit(EXIT_FAILURE);\
    }
    ShadingFileASTNode *root = parse_shading_file(string_path);
    print_shading_file_ast(root);

    // Validate that this has the relevant directives and sections for a shading model (sm) shading file.
    if (find_directive(root, "type shading_model") == nullptr) parse_error("Shading models must contain \"#type shading_model\"");
    ShadingFileASTNode *geom_post_section;
    if ((geom_post_section = find_section(root, "geom_post")) == nullptr) parse_error("Shading models must contain a \"geom_post\" section.");
    ShadingFileASTNode *frag_post_section;
    if ((frag_post_section = find_section(root, "frag_post")) == nullptr) parse_error("Shading models must contain a \"frag_post\" section.");

    // Collect outputs into the dataflows.
    ShadingModel sm;
    sm.frag_post_dataflow = read_dataflow(frag_post_section);
    sm.geom_post_dataflow = read_dataflow(geom_post_section);

    printf("Parsed dataflow\n");
    sm.frag_post_dataflow.print();
    sm.geom_post_dataflow.print();
    return sm;
    #undef parse_error
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
            while (param != nullptr) {
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
