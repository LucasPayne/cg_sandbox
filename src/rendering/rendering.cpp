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
#include <algorithm>
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
    // First, propogate requirements to the minimal set that the ShadingModel says it needs for inputs.
    // Do this for both inputs and uniforms. First, minimize the outputs of each shading stage, all the way until the vertex attribute
    // set is minimized. Then, pass over again and minimize the uniforms.
    // While doing this, catch whether requirements are missing. If so, give an error.

    // Disable the "used" flag on all dataflow structures.
    ShadingDataflow *dataflows[] = {&g.dataflow, &m.dataflow, &sm.frag_post_dataflow, &sm.geom_post_dataflow};
    for (ShadingDataflow *dataflow : dataflows) {
        for (ShadingOutput &output : dataflow->outputs) {
            output.used = false;
            for (ShadingParameter &input : output.inputs) {
                input.used = false;
            }
            for (ShadingParameter &uniform : output.uniforms) {
                uniform.used = false;
            }
        }
    }

    /*--------------------------------------------------------------------------------
    After this pass:
        All ShadingModel frag-post outputs are marked as used.
        The minimum set of required outputs at each stage are marked as used.
        The minimum set of required vertex attributes, inputs to the GeometricMaterial stage, are marked as used.
    --------------------------------------------------------------------------------*/
    // Propogate requirements back from the ShadingModel frag-post outputs. This sets the "used" flag, to later signify to the
    // code generator what it should include.
    for (ShadingOutput &frag_post_output : sm.frag_post_dataflow.outputs) {
        // All ShadingModel frag-post outputs are used.
        frag_post_output.used = true;
        // For each ShadingModel frag-post output, propogate requirements.
        for (ShadingParameter &frag_post_requires : frag_post_output.inputs) {
            // Find matching input from the Material stage.
            auto found_for_frag_post = std::find(std::begin(m.dataflow.outputs), std::end(m.dataflow.outputs), frag_post_requires);
            if (found_for_frag_post == std::end(m.dataflow.outputs)) {
                // Not found. The Material doesn't provide the wanted output.
                fprintf(stderr, "ERROR\n");
                exit(EXIT_FAILURE);
            }
            found_for_frag_post->used = true;
            // Now propogate requirements to both:
            //    - Geometry processing,
            //    - ShadingModel geometry post-processing,
            // either of which can provide the Material's requirements.
            auto &material_requirements = found_for_frag_post->inputs;
            for (ShadingParameter &material_requires : material_requirements) {
                // Search GeometricMaterial outputs.
                auto found_for_material = std::find(std::begin(g.dataflow.outputs), std::end(g.dataflow.outputs), material_requires);
                if (found_for_material == std::end(g.dataflow.outputs)) {
                    // Not found. The GeometricMaterial doesn't provide the wanted output.
                    // However, possibly the ShadingModel geom-post dataflow does.
                    found_for_material = std::find(std::begin(sm.geom_post_dataflow.outputs), std::end(sm.geom_post_dataflow.outputs), material_requires);
                    if (found_for_material == std::end(sm.geom_post_dataflow.outputs)) {
                        fprintf(stderr, "ERROR\n");
                        exit(EXIT_FAILURE);
                    }
                    found_for_material->used = true;
                    // Propogate geom-post requirements to GeometricMaterial.
                    auto &geom_post_requirements = found_for_material->inputs;
                    for (ShadingParameter &geom_post_requires : geom_post_requirements) {
                        // Search GeometricMaterial outputs (required by geom-post).
                        auto found_for_geom_post = std::find(std::begin(g.dataflow.outputs), std::end(g.dataflow.outputs), geom_post_requires);
                        if (found_for_geom_post == std::end(g.dataflow.outputs)) {
                            fprintf(stderr, "ERROR\n");
                            exit(EXIT_FAILURE);
                        }
                        found_for_geom_post->used = true;
                        // Flag vertex attribute inputs of GeometricMaterial as used.
                        for (auto &vertex_attribute : found_for_geom_post->inputs) vertex_attribute.used = true;
                    }
                } else {
                    found_for_material->used = true;
                    // Flag vertex attribute inputs of GeometricMaterial as used.
                    for (auto &vertex_attribute : found_for_material->inputs) vertex_attribute.used = true;
                }
            }
            //---clip_position
            //---uniforms
        }
    }

    // Generate glsl code for each relevant shader stage.
    // (Maybe the term shading versus shader is useful to distinguish between G+M+SM model and actual glsl and the shader model.)

    // Compile the program and retrieve a handle.

    // Compute introspective information.
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
