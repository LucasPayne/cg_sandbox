#ifndef RENDERING_H
#define RENDERING_H
#include "core.h"
#include "gl/gl.h"
#include <string>
namespace Rendering {

// Geometry, Material, and ShadingModel all describe dataflow,
// describing what the stage provides in terms of glsl snippets and required inputs and properties.
// - Efficiency of data representation is not very important here, as these will only be used when compiling a shading pipeline.
//   The most important thing is for this to be easily used by the code generator.
struct ShadingParameter {
    std::string type;
    std::string name;
    ShadingParameter(std::string _type, std::string _name) {
        type = _type;
        name = _name;
    }
    ShadingParameter() {}
    bool operator==(ShadingParameter other) {
        return (type == other.type) && (name == other.name);
    }
    // scratch space for convenience of code generator.
    bool used;
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
};
struct ShadingDataflow {
    std::vector<ShadingOutput> outputs;
    void print() {
        std::cout << "============================================================\n";
        std::cout << "Shading dataflow\n";
        std::cout << "------------------------------------------------------------\n";
        for (const ShadingOutput &output : outputs) {
            std::cout << output.output.type << " " << output.output.name << "\n";
            for (const ShadingParameter &input : output.inputs) {
                std::cout << "    in " << input.type << " " << input.name << "\n";
            }
            for (const ShadingParameter &uniform : output.uniforms) {
                std::cout << "    uniform " << uniform.type << " " << uniform.name << "\n";
            }
            std::cout << "------------------------------------------------------------\n";
            std::cout << "snippet:\n" << output.snippet;
            std::cout << "============================================================\n";
        }
    }
    ShadingDataflow() {}
};

void test_shading_dataflow();


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
    ShadingProgram(GeometricMaterial g, Material m, ShadingModel sm);
private:
    // OpenGL-related data
    GLuint program_id;
    //... State interface information.
    //... Vertex attribute bindings stuff.
    //... Render target bindings stuff.
};
ShadingProgram new_shading_program(GeometricMaterial g, Material m, ShadingModel sm);


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


} // namespace Rendering
#endif // RENDERING_H
