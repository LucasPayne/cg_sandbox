/*--------------------------------------------------------------------------------
    Implementations for the shading submodule of the rendering module.
--------------------------------------------------------------------------------*/
#include "rendering/shading.h"
using namespace ShadingFileDetails;
#include <algorithm> //find
#include <sstream> //istringstream

/*--------------------------------------------------------------------------------
    GeometricMaterial + Material + ShadingModel system.

Resource loading and unloading functions.
--------------------------------------------------------------------------------*/
bool GeometricMaterial::load(void *data, std::istream &stream)
{
    GeometricMaterial *geometric_material = reinterpret_cast<GeometricMaterial *>(data);
    // printf("Parsing geometric material file.\n");
    #define parse_error(ERROR_STR) {\
        printf("GEOMETRIC MATERIAL PARSE ERROR: %s\n", ( ERROR_STR ));\
        return false;\
    }
    ShadingFileASTNode *root = parse_shading_file(stream);
    // print_shading_file_ast(root);

    // Validate that this has the relevant directives and sections for a geometric material (gmat) shading file.
    if (find_directive(root, "type gmat") == nullptr) parse_error("Geometric materials must contain \"#type gmat\"");
    ShadingFileASTNode *vertex_section;
    if ((vertex_section = find_section(root, "vertex")) == nullptr) parse_error("Geometric materials must contain a \"vertex\" section.");

    //-todo: primitive type
    GLenum primitive_type;
    primitive_type = GL_TRIANGLES;

    // Collect outputs in the vertex section.
    ShadingDataflow dataflow = read_dataflow(vertex_section);

    //-todo: set primitive type
    geometric_material->dataflow = dataflow;
    geometric_material->primitive = primitive_type;
    // printf("Parsed dataflow\n");
    // geometric_material->dataflow.print();
    return true;
    #undef parse_error
}
bool GeometricMaterial::unload(void *data)
{
}

bool Material::load(void *data, std::istream &stream)
{
    Material *material = reinterpret_cast<Material *>(data);
    // printf("Parsing material file.\n");
    #define parse_error(ERROR_STR) {\
        printf("MATERIAL PARSE ERROR: %s\n", ( ERROR_STR ));\
        return false;\
    }
    ShadingFileASTNode *root = parse_shading_file(stream);
    // print_shading_file_ast(root);

    // Validate that this has the relevant directives and sections for a material (mat) shading file.
    if (find_directive(root, "type mat") == nullptr) parse_error("Materials must contain \"#type gmat\"");

    ShadingFileASTNode *frag_section;
    if ((frag_section = find_section(root, "frag")) == nullptr) parse_error("Materials must contain a \"frag\" section.");

    // Collect outputs in the root section.
    ShadingDataflow dataflow = read_dataflow(frag_section);

    material->dataflow = dataflow;
    return true;
    #undef parse_error
}
bool Material::unload(void *data)
{
}

bool ShadingModel::load(void *data, std::istream &stream)
{
    ShadingModel *shading_model = reinterpret_cast<ShadingModel *>(data);

    // printf("Parsing shading model file.\n");
    #define parse_error(ERROR_STR) {\
        printf("SHADING MODEL PARSE ERROR: %s\n", ( ERROR_STR ));\
        return false;\
    }
    ShadingFileASTNode *root = parse_shading_file(stream);
    // print_shading_file_ast(root);

    // Validate that this has the relevant directives and sections for a shading model (sm) shading file.
    if (find_directive(root, "type shading_model") == nullptr) parse_error("Shading models must contain \"#type shading_model\"");
    ShadingFileASTNode *geom_post_section;
    if ((geom_post_section = find_section(root, "geom_post")) == nullptr) parse_error("Shading models must contain a \"geom_post\" section.");
    ShadingFileASTNode *frag_post_section;
    if ((frag_post_section = find_section(root, "frag_post")) == nullptr) parse_error("Shading models must contain a \"frag_post\" section.");

    // Collect outputs into the dataflows.
    shading_model->frag_post_dataflow = read_dataflow(frag_post_section);
    shading_model->geom_post_dataflow = read_dataflow(geom_post_section);

    // printf("Parsed dataflow\n");
    // shading_model->frag_post_dataflow.print();
    // shading_model->geom_post_dataflow.print();
    return true;
    #undef parse_error
}
bool ShadingModel::unload(void *data)
{
}

Resource<ShadingProgram> ShadingProgram::create(ResourceModel &rm,
                                                Resource<GeometricMaterial> geometric_material,
                                                Resource<Material> material,
                                                Resource<ShadingModel> shading_model)
{
    //-todo: Caching

    GeometricMaterial *g = rm.get_resource<GeometricMaterial>(geometric_material);
    Material *m = rm.get_resource<Material>(material);
    ShadingModel *sm = rm.get_resource<ShadingModel>(shading_model);
    
    Resource<ShadingProgram> program_handle = rm.new_resource<ShadingProgram>();
    ShadingProgram *program = rm.get_resource<ShadingProgram>(program_handle);
    *program = new_shading_program(*g, *m, *sm);
    return program_handle;
}
bool ShadingProgram::unload(void *data)
{
}

/*================================================================================
    BEGIN private implementation details.
================================================================================*/
/*--------------------------------------------------------------------------------
Create a new shading program from the triple of GeometricMaterial + Material + ShadingModel.

1) Generate glsl code for the relevant stages
2) Compile it, and store the OpenGL handle to the program object,
3) Compute and store introspective information about the program.
--------------------------------------------------------------------------------*/
ShadingProgram ShadingFileDetails::new_shading_program(GeometricMaterial &g,
                                                       Material &m,
                                                       ShadingModel &sm)
{
    // Generating glsl code.
    // ---------------------
    // First, propogate requirements to the minimal set that the ShadingModel says it needs for inputs.
    // Do this for both inputs and uniforms. First, minimize the outputs of each shading stage, all the way until the vertex attribute
    // set is minimized. Then, pass over again and minimize the uniforms.
    // While doing this, catch whether requirements are missing. If so, give an error.

    // Reset each dataflow's scratch-space data.
    //   - Disable the "used" flag on all dataflow structures.
    //   - Set the "source" flag to SHADING_SOURCE_NONE on all dataflow structures (this flag is only meaningful for inputs).
    //   - Set the "latest_using_stage" flag to SHADING_SOURCE_NONE on all outputs.
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
            // Use an "out" variable only if this output is passed further than geom-post.
            // This will be defined in the "main" function if not.
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
    

    // print_dataflows(g, m, sm);
    // std::cout << "Used uniforms:\n";
    // for (auto *uniform : used_uniforms) {
    //     std::cout << "    " << uniform->type << " " << uniform->name << "\n";
    // }
    // std::cout << "Used vertex attributes:\n";
    // for (auto *va : used_vertex_attributes) {
    //     std::cout << "    " << va->type << " " << va->name << "\n";
    // }
    // print_listing("vertex_shader", vertex_shader);
    // print_listing("fragment_shader", fragment_shader);

    // Compile and link OpenGL program object.
    GLShader vertex_shader_object = GLShader::from_string(GL_VERTEX_SHADER, vertex_shader.c_str());
    GLShader fragment_shader_object = GLShader::from_string(GL_FRAGMENT_SHADER, fragment_shader.c_str());
    GLShaderProgram program_object(vertex_shader_object, fragment_shader_object);

    // Compute introspective information.
    //todo----------

    ShadingProgram program;
    program.program_id = program_object.ID();

    return program;
}

ShadingFileASTNode *ShadingFileDetails::parse_shading_file(std::istream &stream)
{
    shading_file_lexer_set_istream(stream);
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
ShadingFileASTDirective *ShadingFileDetails::find_directive(ShadingFileASTNode *node, const std::string match)
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
ShadingFileASTNode *ShadingFileDetails::find_section(ShadingFileASTNode *node, const std::string name)
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

ShadingFileASTOutput *ShadingFileDetails::first_output(ShadingFileASTNode *node)
{
    // Find the first output starting at the given node in this section.
    if (node == nullptr) return nullptr;
    do {
        if (node->kind() == SHADING_FILE_NODE_OUTPUT) return (ShadingFileASTOutput *) node;
        node = node->next;
    } while (node != nullptr);
    return nullptr;
}
ShadingFileASTOutput *ShadingFileDetails::next_output(ShadingFileASTNode *node)
{
    // Find the next output starting at the given node in this section.
    while (node != nullptr) {
        if ((node = node->next) == nullptr) return nullptr;
        if (node->kind() == SHADING_FILE_NODE_OUTPUT) return (ShadingFileASTOutput *) node;
    }
    return nullptr;
}

ShadingDataflow ShadingFileDetails::read_dataflow(ShadingFileASTNode *node)
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
/*================================================================================
    END private implementation details.
================================================================================*/
