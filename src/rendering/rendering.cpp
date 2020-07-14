/*--------------------------------------------------------------------------------
BUGS:
PROBLEMS:
IDEAS/THINGS/NOTES:
    When things aren't in inner loops, or just aren't performance critical, and especially if they also
    involve non-fixed-size data (trees, strings, etc.), maybe using the standard
    C++ facilities which are easiest to use and read, no matter the overhead (as long as it is not very noticeable),
    will be fine. Also, especially when prototyping or trying out ideas for ways to structure data relationships / control flow.
--------------------------------------------------------------------------------*/
#include "rendering/rendering.h"
namespace Rendering {

ShadingProgram::ShadingProgram(GeometricMaterial g, Material m, ShadingModel sm)
{
    //todo: lookup in cache.
    *this = new_shading_program(g, m, sm);
}

ShadingProgram new_shading_program(GeometricMaterial g, Material m, ShadingModel sm)
{
    // Generate glsl code for the relevant stages, compile it, store the OpenGL handle to the program object,
    // and compute and store introspective information about the program.

    // Generating glsl code.
    // ---------------------
    // First, propogate requirements to the minimal set the ShadingModel says it needs for inputs.
    // Do this for both inputs and uniforms. First, minimize the outputs of each shading stage, all the way until the vertex attribute
    // set is minimized. Then, pass over again and minimize the uniforms.
    // While doing this, catch whether requirements are missing. If so, give an error.

    //-Copy shading stages.
    // Shading stage preprocess: minimize inputs, uniforms, and outputs.
    for (const ShadingOutput &sm_output : sm.outputs) {
        // For each ShadingModel output, find the inputs in the Material.
        for (const ShadingParameter &sm_output_requires : sm_output.inputs) {
            // Look for this input from the previous stage (which must be the Material stage).
            bool found = false;
            for (const ShadingOutput &m_output : m.outputs) {
                if (m_output.output == sm_output_required) {
                    found = true;
                    sm_winnowed
                    break;
                }
            }
            if (!found) {
                fprintf(stderr, "ERROR\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Generate glsl code for each relevant shader stage.
    // (Maybe the term shading versus shader is useful to distinguish between G+M+SM model and actual glsl and the shader model.)
}


void test_shading_dataflow()
{
    ShadingDataflow dataflow;
    
    ShadingOutput output1;
    output1.output = ShadingParameter("vec3", "world_position");
    output1.inputs.push_back(ShadingParameter("vec3", "v_position"));
    output1.uniforms.push_back(ShadingParameter("mat4x4", "model_matrix"));
    output1.snippet = "return (model_matrix * vec4(v_position, 1)).xyz\n";

    dataflow.outputs.push_back(output1);
    dataflow.print();
}

} // namespace Rendering
