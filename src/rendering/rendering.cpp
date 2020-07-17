/*--------------------------------------------------------------------------------
BUGS:
PROBLEMS:
    Maybe parameter passing for GeometricMaterial and geom-post was uneccessary, if
    glsl functions can just read from previously-written-to out variables.
TO DO:
    Duplicate inputs and outputs are fine, but remember to setify them when generating code.
IDEAS/THINGS/NOTES:
    When things aren't in inner loops, or just aren't performance critical, and especially if they also
    involve non-fixed-size data (trees, strings, etc.), maybe using the standard
    C++ facilities which are easiest to use and read, no matter the overhead (as long as it is not very noticeable),
    will be fine. Also, especially when prototyping or trying out ideas for ways to structure data relationships / control flow.

    Maybe the term shading versus shader is useful to distinguish between G+M+SM model and actual glsl and the shader model.

    So far this has been assuming vertex+fragment. Since a major reason for geometric materials is seamless
    use of tessellated surfaces, the other stages will be needed. I think this will just be more case-by-case for
    the code-generator, deciding where to put what (such as geometry post-processing being in either the vertex shader or evaluation shader).

    It looks like a lot of the logic in the first pass over the shading pipeline is constructing a graph.
    Maybe start with thinking about what the code-generator wants to pass over, then construct that as a data structure
    with a pass over the dataflow structures.
--------------------------------------------------------------------------------*/
#include "rendering/rendering.h"
#include <algorithm> //find
#include <functional>
#include <sstream> //istringstream

static void print_dataflows(GeometricMaterial &g, Material &m, ShadingModel &sm)
{
    printf("ShadingModel frag-post dataflow\n");
    sm.frag_post_dataflow.print();
    printf("\nMaterial dataflow\n");
    m.dataflow.print();
    printf("\nShadingModel geom-post dataflow\n");
    sm.geom_post_dataflow.print();
    printf("\nGeometricMaterial dataflow\n");
    g.dataflow.print();
}

ShadingProgram::ShadingProgram(GeometricMaterial g, Material m, ShadingModel sm)
{
    //todo: lookup in cache.
    *this = new_shading_program(g, m, sm);
}


void print_listing(const std::string &text)
{
    // Print the given text with numbered lines.
    std::istringstream lines(text);
    std::string line;
    int line_num = 1;
    while (std::getline(lines, line)) {
        std::cout << std::to_string(line_num) << ": " << line << "\n";
        line_num ++;
    }
}

ShadingProgram new_shading_program(GeometricMaterial &g, Material &m, ShadingModel &sm)
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
    // Set the "source" flag to SHADING_SOURCE_NONE on all dataflow structures (this flag is only meaningful for inputs).
    // Set the "latest_using_stage" flag to SHADING_SOURCE_NONE on all outputs.
    ShadingDataflow *dataflows[] = {&g.dataflow, &m.dataflow, &sm.frag_post_dataflow, &sm.geom_post_dataflow};
    for (ShadingDataflow *dataflow : dataflows) {
        for (ShadingOutput &output : dataflow->outputs) {
            output.used = false;
            // latest_using_stage will be updated to the stage furthest in the shading pipeline that uses this output.
            //    This information, for example, can be used to determine what is an "out" versus a function parameter,
            //    since shading stages don't map 1-to-1 to shader stages.
            output.latest_using_stage = SHADING_SOURCE_NONE; // using the SOURCE enum for convenience.
            for (ShadingParameter &input : output.inputs) {
                input.used = false;
                input.source = SHADING_SOURCE_NONE;
            }
            for (ShadingParameter &uniform : output.uniforms) {
                uniform.used = false;
                uniform.source = SHADING_SOURCE_NONE;
            }
        }
    }
    /*--------------------------------------------------------------------------------
    After this pass:
        All ShadingModel frag-post outputs are marked as used.
        The minimum set of required outputs at each stage are marked as used.
        The minimum set of required vertex attributes, inputs to the GeometricMaterial stage, are marked as used.
        The special case of the always-required clip_position is accounted for.
        Used uniforms will be stored in a list. This is all that is needed for the uniform-declaration code.
        Used vertex attributes will be stored in a list.
    notes/todo:
        Possibly frag-post will also want to look for inputs from geom-post and GeometricMaterial.
    --------------------------------------------------------------------------------*/

    std::vector<ShadingParameter *> used_uniforms(0);
    std::vector<ShadingParameter *> used_vertex_attributes(0);

    // This macro is used to mark an output as used, along with its inputs and uniforms.
    // This also collects used uniforms into the list. This is purely so another pass doesn't need to go find them again.
    #define set_used(SHADING_OUTPUT){\
        ( SHADING_OUTPUT ).used = true;\
        for (auto &input : ( SHADING_OUTPUT ).inputs) input.used = true;\
        for (ShadingParameter &uniform : ( SHADING_OUTPUT ).uniforms) {\
            uniform.used = true;\
            bool add_to_used_uniforms = true;\
            for (ShadingParameter *used_uniform : used_uniforms) {\
                if (*used_uniform == uniform) add_to_used_uniforms = false;\
            }\
            if (add_to_used_uniforms) used_uniforms.push_back(&uniform);\
        }\
    }
    // This macro is used to collect used vertex attributes, so that another pass isn't needed for this.
    #define collect_used_vertex_attributes(SHADING_OUTPUT){\
        for (auto &vertex_attribute : ( SHADING_OUTPUT ).inputs) {\
            bool add_to_used_vertex_attributes = true;\
            for (ShadingParameter *used_vertex_attribute : used_vertex_attributes) {\
                if (*used_vertex_attribute == vertex_attribute) add_to_used_vertex_attributes = false;\
            }\
            if (add_to_used_vertex_attributes) used_vertex_attributes.push_back(&vertex_attribute);\
        }\
    }
    // This macro updates the latest stage in the shading pipeline that uses this output.
    // This information can be useful for the code generator, when deciding how to map shading stages to GLSL shader stages.
    #define update_latest_using_stage(SHADING_OUTPUT,SHADING_STAGE){\
        if (( SHADING_OUTPUT ).latest_using_stage < ( SHADING_STAGE )) {\
            ( SHADING_OUTPUT ).latest_using_stage = ( SHADING_STAGE );\
        }\
    }
        
    // Propogate requirements back from the ShadingModel frag-post outputs. This sets the "used" flag, to later signify to the
    // code generator what it should include.
    for (ShadingOutput &frag_post_output : sm.frag_post_dataflow.outputs) {
        // All ShadingModel frag-post outputs are used.
        set_used(frag_post_output);
        // For each ShadingModel frag-post output, propogate requirements.
        for (ShadingParameter &frag_post_requires : frag_post_output.inputs) {
            // The inputs to frag-post always come from the Material.
            frag_post_requires.source = SHADING_SOURCE_MATERIAL;
            // Find matching input from the Material stage.
            auto found_for_frag_post = std::find(std::begin(m.dataflow.outputs), std::end(m.dataflow.outputs), frag_post_requires);
            if (found_for_frag_post == std::end(m.dataflow.outputs)) {
                // Not found. The Material doesn't provide the wanted output.
                fprintf(stderr, "ERROR: Material does not provide the wanted output.\n");
                exit(EXIT_FAILURE);
            }
            // Flag this output as being required by frag-post. This might be useful during code generation.
            update_latest_using_stage(*found_for_frag_post, SHADING_SOURCE_FRAG_POST);
            set_used(*found_for_frag_post);
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
                        fprintf(stderr, "ERROR: Material inputs could not be provided.\n");
                        exit(EXIT_FAILURE);
                    }
                    // The Material input has geom-post source.
                    material_requires.source = SHADING_SOURCE_GEOM_POST;
                    // Flag the output as being used by the Material stage.
                    update_latest_using_stage(*found_for_material, SHADING_SOURCE_MATERIAL);
                    set_used(*found_for_material);
                    // Propogate geom-post requirements to GeometricMaterial.
                    auto &geom_post_requirements = found_for_material->inputs;
                    for (ShadingParameter &geom_post_requires : geom_post_requirements) {
                        // Search GeometricMaterial outputs (required by geom-post).
                        auto found_for_geom_post = std::find(std::begin(g.dataflow.outputs), std::end(g.dataflow.outputs), geom_post_requires);
                        if (found_for_geom_post == std::end(g.dataflow.outputs)) {
                            // Propogate geom-post requirements to vertex attributes.
                            // This geom-post input is now a used vertex attribute.
                            geom_post_requires.source = SHADING_SOURCE_VERTEX_ARRAY;
                            // Flag the output as being used by the geom-post stage.
                            update_latest_using_stage(*found_for_geom_post, SHADING_SOURCE_GEOM_POST);
                            geom_post_requires.used = true;
                            used_vertex_attributes.push_back(&geom_post_requires);
                        } else {
                            // The geom-post input has GeometricMaterial source.
                            geom_post_requires.source = SHADING_SOURCE_GEOMETRIC_MATERIAL;
                            set_used(*found_for_geom_post);
                            // collect_used_vertex_attributes(*found_for_geom_post);
                        }
                    }
                } else {
                    // The Material input has GeometricMaterial source.
                    material_requires.source = SHADING_SOURCE_GEOMETRIC_MATERIAL;
                    // Flag the output as being used by the Material stage.
                    update_latest_using_stage(*found_for_material, SHADING_SOURCE_MATERIAL);
                    set_used(*found_for_material);
                    collect_used_vertex_attributes(*found_for_material);
                }
            }
        }
    }
    // clip position (vec4 gl_Position)
    // ShadingModel geometry post-processing must always output clip position.
    auto clip_position_output_found = std::find(std::begin(sm.geom_post_dataflow.outputs),
                                      std::end(sm.geom_post_dataflow.outputs),
                                      ShadingParameter("vec4", "gl_Position", SHADING_PARAMETER_OUT));
    if (clip_position_output_found == std::end(sm.geom_post_dataflow.outputs)) {
        fprintf(stderr, "ERROR: No vec4 gl_Position output defined in shading model.\n");
        exit(EXIT_FAILURE);
    }
    set_used(*clip_position_output_found);
    // Propogate this requirement, which is only to the GeometricMaterial.
    auto &clip_position_requirements = clip_position_output_found->inputs;
    for (auto &clip_position_requires : clip_position_requirements) {
        auto found_for_clip_position = std::find(std::begin(g.dataflow.outputs),
                                                 std::end(g.dataflow.outputs),
                                                 clip_position_requires);
        if (found_for_clip_position == std::end(g.dataflow.outputs)) {
            // Propogate geom-post requirements to vertex attributes.
            // This geom-post input is now a used vertex attribute.
            clip_position_requires.source = SHADING_SOURCE_VERTEX_ARRAY;
            clip_position_requires.used = true;
            used_vertex_attributes.push_back(&clip_position_requires);
        } else {
            // clip_position required input has GeometricMaterial source.
            clip_position_requires.source = SHADING_SOURCE_GEOMETRIC_MATERIAL;
            set_used(*found_for_clip_position);
	    collect_used_vertex_attributes(*found_for_clip_position);
        }
	// No matter the input source, flag the output as being used by the geom-post stage.
        update_latest_using_stage(*found_for_clip_position, SHADING_SOURCE_GEOM_POST);
    }

    // Generate glsl code for each relevant shader stage.
    //================================================================================
    // Shared uniforms. This snippet will be included in each shader file.
    std::string uniforms_snippet = "";
    for (ShadingParameter *uniform : used_uniforms) {
        uniforms_snippet += "uniform " + uniform->type + " " + uniform->name + ";\n";
    }
    // Vertex shader
    //--------------------------------------------------------------------------------
    std::string vertex_shader(
        "// Generated vertex shader.\n"
        "#version 420\n"
    );
    // Input vertex attributes.
    for (ShadingParameter *va : used_vertex_attributes) {
        vertex_shader += "in " + va->type + " " + va->name + ";\n";
    }
    vertex_shader += "\n";
    vertex_shader += uniforms_snippet;
    vertex_shader += "\n";
    // Outputs to next shader stage.
    // First, outputs from the GeometricMaterial.
    // Secondly, outputs from the ShadingModel geom-post.
    ShadingDataflow *out_dataflows[] = {&g.dataflow, &sm.geom_post_dataflow};
    for (ShadingDataflow *dataflow : out_dataflows) {
        for (ShadingOutput &output : dataflow->outputs) {
            if (!output.used) continue;
            // Don't use an "out" variable if this output is passed at most to geom-post.
            // This will be defined in the "main" function otherwise.
            if (output.latest_using_stage > SHADING_SOURCE_GEOM_POST) {
                vertex_shader += "out " + output.output.type + " " + output.output.name + ";\n";
            }
        }
    }
    vertex_shader += "\n";
    // GeometricMaterial functions. These need no function inputs, as they definitely only depend on vertex attributes
    // and uniforms.
    for (ShadingOutput &output : g.dataflow.outputs) {
        if (!output.used) continue;
        vertex_shader += output.output.type + " _FUNCTION_" + output.output.name + "() {\n";
        std::istringstream lines(output.snippet);
        std::string line;
        while (std::getline(lines, line)) {
            vertex_shader += "    " + line + "\n";
        }
        vertex_shader += "}\n";
    }
    vertex_shader += "\n";
    // ShadingModel geom-post functions. These may need function inputs if a geom-post output requires
    // any GeometricMaterial outputs.
    for (ShadingOutput &output : sm.geom_post_dataflow.outputs) {
        if (!output.used) continue;
        vertex_shader += output.output.type + " _FUNCTION_" + output.output.name + "(";
        // Function inputs.
        bool any_params = false; // used to help comma insertion
        for (ShadingParameter &input : output.inputs) {
            if (input.source == SHADING_SOURCE_GEOMETRIC_MATERIAL) {
                if (any_params) vertex_shader += ", ";
                vertex_shader += "in " + input.type + " " + input.name;
                any_params = true;
            }
        }
        vertex_shader += ") {\n";
        std::istringstream lines(output.snippet);
        std::string line;
        while (std::getline(lines, line)) {
            vertex_shader += "    " + line + "\n";
        }
        vertex_shader += "}\n";
    }
    vertex_shader += "\n";
    // Main function
    vertex_shader += "void main(void) {\n";
    // GeometricMaterial outputs.
    // There are two cases for declarations here:
    //    - out variable from this shader stage This means it is required by something other than geom-post.
    //    - Declared inline in the main function. This means it is only required by geom-post.
    for (ShadingOutput &output : g.dataflow.outputs) {
        if (!output.used) continue;
        // Only declare in the main function if this GeometricMaterial output is used only by at most geom-post.
        // Otherwise, it will have been declared as an "out" variable.
        if (output.latest_using_stage == SHADING_SOURCE_GEOM_POST) {
            vertex_shader += "    " + output.output.type + " " + output.output.name + " = _FUNCTION_" + output.output.name + "();\n";
        }
        vertex_shader += "    " + output.output.name + " = _FUNCTION_" + output.output.name + "();\n";
    }
    // Geom-post outputs (which can have GeometricMaterial outputs as parameters).
    for (ShadingOutput &output : sm.geom_post_dataflow.outputs) {
        if (!output.used) continue;
        vertex_shader += "    " + output.output.name + " = _FUNCTION_" + output.output.name + "(";
        // Parameters.
        bool any_params = false; // used to help comma insertion
        for (ShadingParameter &input : output.inputs) {
            if (input.source == SHADING_SOURCE_GEOMETRIC_MATERIAL) {
                if (any_params) vertex_shader += ", ";
                vertex_shader += input.name;
                any_params = true;
            }
        }
        vertex_shader += ");\n";
    }
    vertex_shader += "}\n";
    
    // Fragment shader
    //--------------------------------------------------------------------------------
    std::string fragment_shader(
        "// Generated fragment shader.\n"
        "#version 420\n"
    );
    // Output rendertargets. These are what frag-post outputs. All outputs are used.
    for (ShadingOutput &output : sm.frag_post_dataflow.outputs) {
        fragment_shader += "out " + output.output.type + " " + output.output.name + ";\n";
    }
    fragment_shader += "\n";
    // Input interpolators.
    // Material interpolator inputs.
    for (ShadingOutput &output : m.dataflow.outputs) {
        if (!output.used) continue;
        for (ShadingParameter &input : output.inputs) {
            fragment_shader += "in " + input.type + " " + input.name + ";\n";
        }
    }
    // Frag-post interpolator inputs. This is everything the material does not output, but is output from previous stages.
    //todo------------------- (this will also remove inputs from the parameter lists of generated functions).
    // Uniforms
    fragment_shader += "\n";
    fragment_shader += uniforms_snippet;
    fragment_shader += "\n";
    // The material provides inputs to frag-post. The functions are defined here, which are called in the "main" function.
    for (ShadingOutput &output : m.dataflow.outputs) {
        if (!output.used) continue;
        fragment_shader += output.output.type + " _FUNCTION_" + output.output.name + "() {\n";
        // Function body.
        std::istringstream lines(output.snippet);
        std::string line;
        while (std::getline(lines, line)) {
            fragment_shader += "    " + line + "\n";
        }
        fragment_shader += "}\n";
    }
    // frag-post output functions. Code is generated in "main" to set rendertargets to the return values of these functions.
    // These can depend on material outputs.
    for (ShadingOutput &output : sm.frag_post_dataflow.outputs) {
        if (!output.used) continue;
        fragment_shader += output.output.type + " _FUNCTION_" + output.output.name + "(";
        // Function inputs.
        bool any_params = false; // used to help comma insertion
        for (ShadingParameter &input : output.inputs) {
	    if (any_params) fragment_shader += ", ";
	    fragment_shader += "in " + input.type + " " + input.name;
	    any_params = true;
        }
        fragment_shader += ") {\n";
        // Function body.
        std::istringstream lines(output.snippet);
        std::string line;
        while (std::getline(lines, line)) {
            fragment_shader += "    " + line + "\n";
        }
        fragment_shader += "}\n";
    }

    // Main function
    fragment_shader += "void main(void) {\n";
    // Computing the material outputs, which will be passed to functions to compute rendertarget outputs.
    for (ShadingOutput &output : m.dataflow.outputs) {
        if (!output.used) continue;
        fragment_shader += "    " + output.output.type + " " + output.output.name + " = _FUNCTION_" + output.output.name + "();\n";
    }
    // Writing the rendertarget outputs.
    for (ShadingOutput &output : sm.frag_post_dataflow.outputs) {
        fragment_shader += "    " + output.output.name + " = _FUNCTION_" + output.output.name + "(";
        // Parameters
        bool any_params = false;
        for (ShadingParameter &input : output.inputs) {
            if (any_params) fragment_shader += ", ";
            fragment_shader += input.name;
            any_params = true;
        }
        fragment_shader += ");\n";
    }
    fragment_shader += "}\n";
    

    std::cout << fragment_shader; getchar();

    // Compute introspective information.

    print_dataflows(g, m, sm);
    std::cout << "Used uniforms:\n";
    for (auto *uniform : used_uniforms) {
        std::cout << "    " << uniform->type << " " << uniform->name << "\n";
    }
    std::cout << "Used vertex attributes:\n";
    for (auto *va : used_vertex_attributes) {
        std::cout << "    " << va->type << " " << va->name << "\n";
    }
    print_listing(vertex_shader);
    print_listing(fragment_shader);
    // Create a ShadingProgram.
    ShadingProgram program;
    GLShader vertex_shader_object = GLShader::from_string(GL_VERTEX_SHADER, vertex_shader.c_str());
    GLShader fragment_shader_object = GLShader::from_string(GL_FRAGMENT_SHADER, fragment_shader.c_str());

    getchar();

    return program;
}


void test_shading_dataflow()
{
    ShadingDataflow dataflow;
    
    ShadingOutput output1;
    output1.output = ShadingParameter("vec3", "world_position", SHADING_PARAMETER_OUT);
    output1.inputs.push_back(ShadingParameter("vec3", "v_position", SHADING_PARAMETER_IN));
    output1.uniforms.push_back(ShadingParameter("mat4x4", "model_matrix", SHADING_PARAMETER_UNIFORM));
    output1.snippet = "return (model_matrix * vec4(v_position, 1)).xyz\n";

    dataflow.outputs.push_back(output1);
    dataflow.print();
}

void test_new_shading_program()
{
    GeometricMaterial g;
    {
        ShadingOutput output1;
        ShadingOutput output2;
        ShadingOutput output3;
        ShadingDataflow dataflow;
        output1.output = ShadingParameter("vec3", "world_position", SHADING_PARAMETER_OUT);
        output1.inputs.push_back(ShadingParameter("vec3", "v_position", SHADING_PARAMETER_IN));
        output1.uniforms.push_back(ShadingParameter("mat4x4", "model_matrix", SHADING_PARAMETER_UNIFORM));
        output1.snippet = "return (model_matrix * vec4(v_position, 1)).xyz;\n";
        dataflow.outputs.push_back(output1);

        output2.output = ShadingParameter("vec3", "f_normal", SHADING_PARAMETER_OUT);
        output2.inputs.push_back(ShadingParameter("vec3", "v_normal", SHADING_PARAMETER_IN));
        output2.snippet = "return f_normal;\n";
        dataflow.outputs.push_back(output2);

        output3.output = ShadingParameter("vec3", "f_position", SHADING_PARAMETER_OUT);
        output3.inputs.push_back(ShadingParameter("vec3", "v_position", SHADING_PARAMETER_IN));
        output3.snippet = "return v_position;\n";
        dataflow.outputs.push_back(output3);

        g.dataflow = dataflow;
    }
    Material m;
    {
        ShadingDataflow dataflow;
        ShadingOutput output1;
        output1.output = ShadingParameter("vec4", "color", SHADING_PARAMETER_OUT);
        output1.inputs.push_back(ShadingParameter("vec3", "f_position", SHADING_PARAMETER_OUT));
        output1.uniforms.push_back(ShadingParameter("vec4", "uniform_color", SHADING_PARAMETER_OUT));
        output1.snippet = "return f_position.x * uniform_color;\n";
        dataflow.outputs.push_back(output1);

        ShadingOutput output2;
        output2.output = ShadingParameter("float", "an_unused_thing", SHADING_PARAMETER_OUT);
        output2.inputs.push_back(ShadingParameter("vec3", "f_uv", SHADING_PARAMETER_IN));
        output2.inputs.push_back(ShadingParameter("vec3", "f_normal", SHADING_PARAMETER_IN));
        output2.uniforms.push_back(ShadingParameter("mat4x4", "the_unused_matrix", SHADING_PARAMETER_UNIFORM));
        output2.snippet = "return f_uv.x + f_normal.y + (the_unused_matrix * vec4(f_normal, 1)).z;\n";
        dataflow.outputs.push_back(output2);

        m.dataflow = dataflow;
    }
    ShadingModel sm;
    {
        ShadingDataflow dataflow;
        ShadingOutput output1;
        output1.output = ShadingParameter("vec4", "gl_Position", SHADING_PARAMETER_OUT);
        output1.inputs.push_back(ShadingParameter("vec3", "world_position", SHADING_PARAMETER_IN));
        output1.uniforms.push_back(ShadingParameter("mat4x4", "vp_matrix", SHADING_PARAMETER_UNIFORM));
        output1.snippet = "return (vp_matrix * vec4(world_position, 1));\n";
        dataflow.outputs.push_back(output1);

        sm.geom_post_dataflow = dataflow;
    }
    {
        ShadingDataflow dataflow;
        ShadingOutput output1;
        output1.output = ShadingParameter("vec4", "rt_color", SHADING_PARAMETER_OUT);
        output1.inputs.push_back(ShadingParameter("vec4", "color", SHADING_PARAMETER_IN));
        output1.snippet = "return color;\n";
        dataflow.outputs.push_back(output1);

        sm.frag_post_dataflow = dataflow;
    }
    new_shading_program(g, m, sm);
}

static char *shading_source_to_string(uint8_t source)
{
    if (source == SHADING_SOURCE_NONE) return "NONE";
    if (source == SHADING_SOURCE_VERTEX_ARRAY) return "VERTEX_ARRAY";
    if (source == SHADING_SOURCE_GEOMETRIC_MATERIAL) return "GEOMETRIC_MATERIAL";
    if (source == SHADING_SOURCE_GEOM_POST) return "GEOM_POST";
    if (source == SHADING_SOURCE_MATERIAL) return "MATERIAL";
    if (source == SHADING_SOURCE_FRAG_POST) return "FRAG_POST";
    return "!-ERROR-!";
}
void ShadingDataflow::print() {
    for (const ShadingOutput &output : outputs) {
        if (output.used) {
            std::cout << "USED ";
            std::cout << "REQUIRED(" << shading_source_to_string(output.latest_using_stage) << ") ";
        }
        std::cout << "out " << output.output.type << " " << output.output.name << "\n";
        for (const ShadingParameter &input : output.inputs) {
            std::cout << "    ";
            if (input.used) {
                std::cout << "USED ";
                std::cout << "SOURCE(" << shading_source_to_string(input.source) << ") ";
            }
	    std::cout << "in " << input.type << " " << input.name << "\n";
        }
        for (const ShadingParameter &uniform : output.uniforms) {
            std::cout << "    " << (uniform.used ? "USED " : "") << "uniform " << uniform.type << " " << uniform.name << "\n";
        }
        std::cout << "    snippet ------------------------------------------------\n";
        std::cout << output.snippet;
        std::cout << "------------------------------------------------------------\n";
    }
}
