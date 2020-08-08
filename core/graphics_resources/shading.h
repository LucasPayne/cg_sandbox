#ifndef SHADING_H
#define SHADING_H
/*--------------------------------------------------------------------------------
Shading submodule of the rendering module.

Provides rendering resources:
    GeometricMaterial - Describes geometry-processing dataflow, taking a vertex array
                        and global data and giving outputs (for example, a triangle mesh).
    Material          - Describes per-fragment outputs, which can be understood by ShadingModels
                        (for example, modulated diffuse from a texture).
    ShadingModel      - Describes geometry-post-processing (such as a screenspace transformation),
                        definition of clip position, and final fragment processing.
    ShadingProgram    - Encapsulates a GPU rasterization dataflow resolved from a GM+M+SM triple.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"


/*--------------------------------------------------------------------------------
    GeometricMaterial + Material + ShadingModel system.
--------------------------------------------------------------------------------*/
//-Shading dataflow structure-----------------------------------------------------
//    --- only this module will want to know about dataflows. Could they be hidden from this interface?
//    --- Can the structs just be defined and the rest put in the ShadingFileDetails:: namespace?
struct ShadingParameter {
    uint8_t kind; // uniform, in, out
    #define MAX_SHADING_PARAMETER_TYPE_NAME_LENGTH 63
    #define MAX_SHADING_PARAMETER_NAME_LENGTH 63
    char type_buffer[MAX_SHADING_PARAMETER_TYPE_NAME_LENGTH + 1];
    char name_buffer[MAX_SHADING_PARAMETER_NAME_LENGTH + 1];
    std::string type;
    std::string name;
    ShadingParameter(const char *_type, const char *_name, uint8_t _kind) :
        kind{_kind}
    {
        if (strlen(_type) > MAX_SHADING_PARAMETER_TYPE_NAME_LENGTH
            || strlen(_name) > MAX_SHADING_PARAMETER_NAME_LENGTH) {
            fprintf(stderr, "ERROR: Shading file parameter type/name too long.\n");
            exit(EXIT_FAILURE);
        }
        strncpy(type_buffer, _type, MAX_SHADING_PARAMETER_TYPE_NAME_LENGTH);
        strncpy(name_buffer, _name, MAX_SHADING_PARAMETER_NAME_LENGTH);
        type = std::string(type_buffer);
        name = std::string(name_buffer);
    }
    ShadingParameter() {}
    // for std::find
    bool operator==(ShadingParameter other) {
        return (type == other.type) && (name == other.name);
    }
    // for std::sort
    bool operator<(ShadingParameter other) {
        if (type < other.type) return true;
        if (type == other.type) return name < other.name;
        return false;
    }

    // scratch space for convenience of code generator.
    bool used;
    // "source" only makes sense for inputs, and denotes the shading stage the inputs came from, or whether it comes from the vertex array.
    uint8_t source;
};
struct ShadingOutput {
    ShadingParameter output;
    std::vector<ShadingParameter> inputs;
    std::vector<ShadingParameter> uniforms;
    std::string snippet;
    ShadingOutput() {}
    // This operator overload is here so that std::find can find a matching output to an input parameter.
    bool operator==(ShadingParameter parameter) {
        return output == parameter;
    }
    // scratch space
    bool used;
    uint8_t latest_using_stage;
};
struct ShadingDataflow {
    std::vector<ShadingOutput> outputs;
    void print();
    ShadingDataflow() {}
};
//-End shading dataflow structure-------------------------------------------------

/*--------------------------------------------------------------------------------
A ShadingBlock describes the layout of a block of memory with
named entries declared in shading files. These lead to, in generated glsl code,
deterministic-layout (achieved with glsl's std140 feature) uniform/constant blocks
that can be mapped to ranges of uniform/constant buffers, whose data can be uploaded by
the application.

Since the application has a ShadingBlock structure detailing the layout, it can
write to it correctly and update uniform values available in the shader program.
--------------------------------------------------------------------------------*/
#define MAX_SHADING_BLOCK_ENTRY_NAME_LENGTH 31
struct ShadingBlockEntry {
    GLSLTypeID type;
    char name[MAX_SHADING_BLOCK_ENTRY_NAME_LENGTH + 1];
    bool is_array;
    unsigned int array_length;
};
struct ShadingBlockEntryLayout {
    // Contains layout information for a single entry in a ShadingBlock.
    size_t offset;
};
struct ShadingBlock {
    size_t block_size;
    std::vector<ShadingBlockEntry> entries;
    std::unordered_map<std::string, ShadingBlockEntryLayout> entry_layout;
};

/*--------------------------------------------------------------------------------
    GeometricMaterial, Material, ShadingModel
--------------------------------------------------------------------------------*/
struct GeometricMaterial {
    bool load(const std::istream &stream);
    //-Vertex shader only.
    ShadingDataflow dataflow;
    // The dataflow is dependent on the primitives it processes, so that information is here.
    GLenum primitive;
    uint32_t patch_length; // used if primitive == GL_PATCHES

    bool has_properties;
    ShadingBlock properties;
};
struct Material {
    bool load(const std::istream &stream);
    ShadingDataflow dataflow;

    bool has_properties;
    ShadingBlock properties;
};
struct ShadingModel {
    bool load(const std::istream &stream);
    ShadingDataflow geom_post_dataflow;
    ShadingDataflow frag_post_dataflow;

    bool has_properties;
    ShadingBlock properties;
};

/*--------------------------------------------------------------------------------
    ShadingProgram, outcome of GeometricMaterial+Material+ShadingModel.
--------------------------------------------------------------------------------*/
struct ShadingProgram {
    // There is no loading from a stream. ShadingPrograms are rather created with create(),
    // constructed from a G+M+SM triple.
    static ShadingProgram create(GeometricMaterial &geometric_material,
                                 Material &material,
                                 ShadingModel &shading_model);
    GLuint program_id;
};

/*================================================================================
    BEGIN private implementation details.
================================================================================*/
namespace ShadingFileDetails {
// Create a new shading program from the triple of GeometricMaterial + Material + ShadingModel.
ShadingProgram new_shading_program(GeometricMaterial &g, Material &m, ShadingModel &sm);

/*--------------------------------------------------------------------------------
    Shading file abstract-syntax-tree structure.
--------------------------------------------------------------------------------*/
enum ShadingSources {
    // It is important that these are in the correct order.
    SHADING_SOURCE_NONE,
    SHADING_SOURCE_VERTEX_ARRAY,
    SHADING_SOURCE_GEOMETRIC_MATERIAL,
    SHADING_SOURCE_GEOM_POST,
    SHADING_SOURCE_MATERIAL,
    SHADING_SOURCE_FRAG_POST,
};
enum ShadingParameterKinds {
    SHADING_PARAMETER_UNIFORM,
    SHADING_PARAMETER_IN,
    SHADING_PARAMETER_OUT,
};
enum ShadingFileASTNodeKinds {
    SHADING_FILE_NODE_ROOT,
    SHADING_FILE_NODE_DIRECTIVE,
    SHADING_FILE_NODE_SECTION,
    SHADING_FILE_NODE_OUTPUT,
    SHADING_FILE_NODE_BLOCK,
};
struct ShadingFileASTNode {
    virtual int kind() const { return SHADING_FILE_NODE_ROOT; }
    ShadingFileASTNode *next;
    ShadingFileASTNode() : next{nullptr} {}
};
struct ShadingFileASTDirective : ShadingFileASTNode {
    int kind() const { return SHADING_FILE_NODE_DIRECTIVE; }
    const char *text;
    ShadingFileASTDirective(const char *_text) :
        text{_text}
    {}
};
struct ShadingFileASTSection : ShadingFileASTNode {
    int kind() const { return SHADING_FILE_NODE_SECTION; }
    const char *name;
    ShadingFileASTNode *first_child;
    ShadingFileASTSection(const char *_name) :
        name{_name}, first_child{nullptr}
    {}
};
struct ShadingFileASTParameter {
    const char *type;
    const char *name;
    uint8_t kind; // uniform, in, out
    ShadingFileASTParameter *next;
    ShadingFileASTParameter(const char *_type, const char *_name, uint8_t _kind) :
        type{_type}, name{_name}, kind{_kind}, next{nullptr}
    {}
    ShadingParameter deastify() const {
        ShadingParameter param(type, name, kind);
        return param;
    }
};
struct ShadingFileASTOutput : ShadingFileASTNode {
    int kind() const { return SHADING_FILE_NODE_OUTPUT; }
    const char *type;
    const char *name;
    ShadingFileASTParameter *parameter_list;
    const char *snippet;
    ShadingFileASTOutput(const char *_type, const char *_name, ShadingFileASTParameter *_parameter_list, const char *_snippet) :
        type{_type}, name{_name}, parameter_list{_parameter_list}, snippet{_snippet}
    {}
    // This is the AST version of the ShadingOutput structure.
    // This is more convenient for parsing, but will need to be converted to the original structure,
    // by "de-AST-ifying" it.
    ShadingOutput deastify() const {
        ShadingOutput deastified;
        deastified.output = ShadingParameter(type, name, SHADING_PARAMETER_OUT);
        ShadingFileASTParameter *param = parameter_list;
        while (param != nullptr) {
            if (param->kind == SHADING_PARAMETER_IN) {
                deastified.inputs.push_back(param->deastify());
            } else { // should be SHADING_PARAMETER_UNIFORM
                deastified.uniforms.push_back(param->deastify());
            }
            param = param->next;
        }
        deastified.snippet = std::string(snippet);
        return deastified;
    };
};

// Block AST parts.
struct ShadingFileASTBlockEntry {
    const char *type;
    const char *name;
    bool is_array;
    unsigned int array_length;
    ShadingFileASTBlockEntry *next_entry;

    ShadingFileASTBlockEntry(const char *_type, const char *_name) :
        type{_type}, name{_name}, is_array{false}, next_entry{nullptr}
    {}
    ShadingFileASTBlockEntry(const char *_type, const char *_name, unsigned int _array_length) :
        type{_type}, name{_name}, is_array{true}, array_length{_array_length}, next_entry{nullptr}
    {}

    ShadingBlockEntry deastify() const;
};
struct ShadingFileASTBlock : ShadingFileASTNode {
    int kind() const { return SHADING_FILE_NODE_BLOCK; }
    const char *name;
    ShadingFileASTBlockEntry *first_entry;
    ShadingFileASTBlock(const char *_name) :
        name{_name}, first_entry{nullptr}
    {}

    ShadingBlock deastify() const;
};


/*--------------------------------------------------------------------------------
    Low level parser details.
--------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------
    Using the parser.
--------------------------------------------------------------------------------*/
// Given an input stream, parse this into a shading file AST and return the root. 
ShadingFileASTNode *parse_shading_file(const std::istream &stream);

/*--------------------------------------------------------------------------------
    Traversing and interpreting the parsed AST.
--------------------------------------------------------------------------------*/
// Functions for traversing the shading-file abstract syntax tree.
// These are used by the specialized functions for parsing different types of shading files,
// and converting them to the data structure that the application runtime will actually use.
ShadingFileASTDirective *find_directive(ShadingFileASTNode *node, const std::string match);
ShadingFileASTNode *find_section(ShadingFileASTNode *node, const std::string name);
ShadingFileASTBlock *find_block(ShadingFileASTNode *node, const std::string name);
ShadingFileASTOutput *first_output(ShadingFileASTNode *node);
ShadingFileASTOutput *next_output(ShadingFileASTNode *node);
// Collect the ouputs in the node's section, starting at the node, into a dataflow structure.
ShadingDataflow read_dataflow(ShadingFileASTNode *node);
} // namespace ShadingFileDetails

//================================================================================
// Implementation details in the top namespace. I don't know if this is necessary,
// but it allows flex/bison to access these functions properly.
//================================================================================
using namespace ShadingFileDetails;
// Errors must be handled by a user-supplied function, declared here.
void yyerror(ShadingFileASTNode **ast_root_out, char *str);
#define SHADING_FILE_BISON_PARSE_FUNCTION yyparse
int SHADING_FILE_BISON_PARSE_FUNCTION(ShadingFileASTNode **ast_root_out);
#define SHADING_FILE_FLEX_LEX_FUNCTION yylex
int SHADING_FILE_FLEX_LEX_FUNCTION(void);
void shading_file_lexer_set_istream(const std::istream &stream);
//================================================================================

/*================================================================================
    END private implementation details.
================================================================================*/
#endif // SHADING_H
