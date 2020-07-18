#ifndef RENDERING_H
#define RENDERING_H
#include "core.h"
#include "gl/gl.h"
#include <string>
#include <string_view>//read char buffers as std::strings, so it can be used in string arithmetic overloads.

// Geometry, Material, and ShadingModel all describe dataflow,
// describing what the stage provides in terms of glsl snippets and required inputs and properties.
// - Efficiency of data representation is not very important here, as these will only be used when compiling a shading pipeline.
//   The most important thing is for this to be easily used by the code generator.

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

void test_shading_dataflow();
void test_new_shading_program();


// These structs (GeometricMaterial, Material, ShadingModel)
// are purely for processing when making ShadingPrograms.
struct GeometricMaterial {
    //-Vertex shader only.
    GLenum primitive;
    ShadingDataflow dataflow;
};
struct Material {
    ShadingDataflow dataflow;
};
struct ShadingModel {
    ShadingDataflow geom_post_dataflow;
    ShadingDataflow frag_post_dataflow;
};
#if 0
define_resource(GeometricMaterial)
    //-Vertex shader only.
    GLenum primitive;
    ShadingDataflow dataflow;
end_define_resource(GeometricMaterial)

define_resource(Material)
    ShadingDataflow dataflow;
end_define_resource(Material)

define_resource(ShadingModel)
    ShadingDataflow geom_post_dataflow;
    ShadingDataflow frag_post_dataflow;
end_define_resource(ShadingModel)
#endif

// A ShadingProgram encapsulates the result of resolving a GeometricMaterial+Material+ShadingModel triple,
// including an API handle to the program object, and introspective information so that property sheets can be synchronized.
class ShadingProgram {
    // Other than construction and caching, this class just holds data. All usage interface goes through
    // the Draw class, which could be thought of as a ShadingProgram "instance".
public:
    ShadingProgram() {};
    ShadingProgram(GeometricMaterial g, Material m, ShadingModel sm);
    static ShadingProgram new_shading_program(GeometricMaterial &g, Material &m, ShadingModel &sm);
private:
    // OpenGL-related data
    GLuint program_id;
    //... State interface information.
    //... Vertex attribute bindings stuff.
    //... Render target bindings stuff.
};


#if 0
struct PropertySheet {
    //...
    void set(char *property_name, int int_val) {
        //...
    }
};
struct VertexArray {
    GLuint gl_vao_id;
    bool indexed;
    uint32_t num_vertices;
    uint32_t vertex_starting_index;
    GLenum indices_type; // GL_UNSIGNED{BYTE,SHORT,INT}
    uint32_t num_indices;
    uint32_t indices_starting_index;
};
struct GeometricMaterialInstance {
    Resource<GeometricMaterial> type;
    Resource<VertexArray> vertex_array;
    PropertySheet properties;
};
// type = load_asset<GeometricMaterial>("triangle_mesh");
// vertex_array = new_resource<VertexArray>(create_mesh_icosahedron(...));
// ...
// properties.set("model_matrix", transform->model_matrix());
class Draw {
public:
    Draw(GeometricMaterialInstance &gi, MaterialInstance &mi, ShadingModelInstance &smi) {
        g_instance = &gi;
        m_instance = &mi;
        sm_instance = &smi;

        shading_program = ShadingProgram(get_resource(g_instance.type),
                                         get_resource(m_instance.type),
                                         get_resource(sm_instance.type));
    };
    void bind() {
        glUseProgram(shading_program.program_id);
        glBindVertexArray(g_instance.vao.id); //-Make sure this binds the element buffer as well.
    }
    void upload_properties() {
        //...
        // Instances could have dirty flags.
        // UBOs, samplers with glUniform1i, 
    }
    void draw() {
        if (g_instance.indexed) {
            glDrawElements(g_instance.geometry.primitive, //mode
                           g_instance.vao.num_indices, // count
                           g_instance.vao.indices_type, // type (GL_UNSIGNED_{BYTE,SHORT,INT})
                           (const void *) g_instance.vao.indices_starting_index);
        } else {
            glDrawArrays(g_instance.geometry.primitive, //mode
                         g_instance.vao.vertex_starting_index //first
                         g_instance.vao.num_vertices); // count
        }
    }
private:
    GeometryInstance *g_instance;
    MaterialInstance *m_instance;
    ShadingModelInstance *sm_instance;

    ShadingProgram shading_program;
};
#endif

/*--------------------------------------------------------------------------------
    Shading file parsing.
--------------------------------------------------------------------------------*/

// Shading file AST the parser constructs.
// This information will be used when deciding if this file makes sense in terms of a geometric material, etc.,
// depending on the way the files sections and directives are structured.

enum ShadingFileASTNodeKinds {
    SHADING_FILE_NODE_ROOT,
    SHADING_FILE_NODE_DIRECTIVE,
    SHADING_FILE_NODE_SECTION,
    SHADING_FILE_NODE_OUTPUT,
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
    uint8_t kind; // uniform, in, out
    const char *type;
    const char *name;
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
    const char *snippet;
    ShadingFileASTParameter *parameter_list;
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
GeometricMaterial parse_geometric_material_file(const std::string string_path);
Material parse_material_file(const std::string string_path);
ShadingModel parse_shading_model_file(const std::string string_path);

// Implementation details.
ShadingFileASTNode *parse_shading_file(const std::string string_path); // Returns the root of the parsed AST.
// Interact with the stack of files set for parsing. This can be used to concatenate files,
// and implement C-style #includes.
//     note: this should probably not be in the usage interface.
void parse_shading_file_push_file(FILE *file);
void parse_shading_file_pop_file(void);
// Errors must be handled by a user-supplied function, declared here.
void yyerror(ShadingFileASTNode **ast_root_out, char *str);
#define SHADING_FILE_BISON_PARSE_FUNCTION yyparse
int SHADING_FILE_BISON_PARSE_FUNCTION(ShadingFileASTNode **ast_root_out);
#define SHADING_FILE_FLEX_LEX_FUNCTION yylex
int SHADING_FILE_FLEX_LEX_FUNCTION(void);

// Debug
void print_shading_file_ast(ShadingFileASTNode *root, int indent = 0);

#endif // RENDERING_H
