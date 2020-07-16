#ifndef RENDERING_H
#define RENDERING_H
#include "core.h"
#include "gl/gl.h"
#include <string>

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
struct ShadingParameter {
    std::string type;
    std::string name;
    ShadingParameter(std::string _type, std::string _name) {
        type = _type;
        name = _name;
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

// A ShadingProgram encapsulates the end-product of resolving a GeometricMaterial+Material+ShadingModel triple,
// including an API handle to the program object, and introspective information so that property sheets can be synchronized.
class ShadingProgram {
    // Other than construction and caching, this class just holds data. All usage interface goes through
    // the Draw class, which could be thought of as a ShadingProgram "instance".
public:
    ShadingProgram() {}
    ShadingProgram(GeometricMaterial g, Material m, ShadingModel sm);
private:
    // OpenGL-related data
    GLuint program_id;
    //... State interface information.
    //... Vertex attribute bindings stuff.
    //... Render target bindings stuff.
};
ShadingProgram new_shading_program(GeometricMaterial &g, Material &m, ShadingModel &sm);


#if 0
struct PropertySheet {
    //...
    void set(char *property_name, int int_val) {
        //...
    }
};
struct VAO {
    GLuint vao_id;
    bool indexed;
    uint32_t num_vertices;
    uint32_t vertex_starting_index;
    GLenum indices_type; // GL_UNSIGNED{BYTE,SHORT,INT}
    uint32_t num_indices;
    uint32_t indices_starting_index;
};
struct GeometryInstance {
    Geometry &geometry; //instance of this
    VAO vao;
    PropertySheet properties;
};
struct Material {

};
struct MaterialInstance {

};
struct ShadingModel {

};
struct ShadingModelInstance {

};

#include <unordered_map>
// https://en.cppreference.com/w/cpp/container/unordered_map
struct GMSMHash {
    uint32_t g;
    uint32_t m;
    uint32_t sm;
    GMSMHash(uint32_t _g, uint32_t _m, uint32_t _sm) : g{_g}, m{_m}, sm{_sm} {}
};
class ShadingProgram {
    // Other than construction and caching, this class just holds data. All usage interface goes through
    // the Draw class, which could be thought of as a ShadingProgram "instance".
public:
    ShadingProgram(Geometry g, Material m, ShadingModel sm) {
        GMSMHash hash(g.id, m.id, sm.id);
        for (auto &found : cache.find(hash)) {
            *this = found;
            return;
        }
        // Not cached.
        cache[hash] = new_shading_program(g, m, sm);
        *this = cache[hash];
    }
private:
    ShadingProgram new_shading_program(Geometry g, Material m, ShadingModel sm) {
        // Construct a new shading program. This is where all of the code generation starts.
        //...
    }
    //-Global cache. Maybe should not be global.
    static std::unordered_map<GMSMHash, ShadingProgram> cache;

    // OpenGL-related data
    GLuint program_id;
    //... State interface information.
    //... Vertex attribute bindings stuff.
    //... Render target bindings stuff.
};
std::unordered_map<GMSMHash, ShadingProgram> ShadingProgram::cache;

class Draw {
public:
    Draw(GeometryInstance &gi, MaterialInstance &mi, ShadingModelInstance &smi) {
        g_instance = gi;
        m_instance = mi;
        sm_instance = smi;

        shading_program = ShadingProgram(g_instance.geometry, m_instance.material, sm_instance.shading_model);
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
    GeometryInstance g_instance;
    MaterialInstance m_instance;
    ShadingModelInstance sm_instance;

    ShadingProgram shading_program;
};
#endif

/*--------------------------------------------------------------------------------
    Shading file parsing.
--------------------------------------------------------------------------------*/

struct ShadingFile {
    int nice;
};

ShadingFile parse_shading_file(const std::string string_path);

// Interact with the stack of files set for parsing. This can be used to concatenate files,
// and implement C-style #includes.
//     note: this should probably not be in the usage interface.
void parse_shading_file_push_file(FILE *file);
void parse_shading_file_pop_file(void);
// Errors must be handled by a user-supplied function, declared here.
void yyerror(char *str);

#endif // RENDERING_H
