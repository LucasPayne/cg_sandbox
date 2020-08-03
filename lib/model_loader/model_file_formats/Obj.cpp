// references:
//    http://www.martinreddy.net/gfx/3d/OBJ.spec
//
// Changes to the loader due to encountering an exceptional model
// are prefixed with EXCEPTION.
#include "model_loader/model_loader.h"
#include <string.h>

static int g_obj_line_number = 0; // For printing the line number in the file where a parsing failure occurs.

#define MAX_NUM_OBJCOMMAND_PARAMETERS 64
#define OBJCOMMAND_BUFFER_SIZE 1024
struct ObjCommand {
    char *token(int index) {
        return &buffer[token_indices[index]];
    }
    int num_tokens;
    uint16_t token_indices[MAX_NUM_OBJCOMMAND_PARAMETERS];
    char buffer[OBJCOMMAND_BUFFER_SIZE];
};
bool next_command(std::istream &stream, ObjCommand &command)
{
    std::string line;
    while (true) {
        if (!std::getline(stream, line)) {
            return false;
        }
        g_obj_line_number++;
        const char *c_str = line.c_str();
        // Skip lines that are all whitespace.
        const char *line_ptr = c_str;
        while (*line_ptr == ' ') ++line_ptr;
        if (*c_str == '\0') continue;
        // Skip comment lines.
        if (*c_str == '#') continue;
        break;
    }
    // std::cout << "line: " << line << "\n";
    strncpy(command.buffer, line.c_str(), OBJCOMMAND_BUFFER_SIZE-1);

    // Break the line up into tokens.
    char *token = command.buffer;
    command.num_tokens = 0;
    while (true) {
        while (*token == ' ') ++token;
        if (*token == '\0') break;
        command.token_indices[command.num_tokens] = (uint16_t) (token - command.buffer);
        command.num_tokens ++;
        char *end;
        if ((end = strchr(token, ' ')) == NULL) break;
        *end = '\0';
        token = end + 1;
    } 
    return true;
}

enum ObjModes {
    OBJ_READING
};
struct ObjGroup {
    ObjGroup(const std::string &_name) : face_num_elements{0}, name{_name}
    {}
    int face_num_elements;
    std::string name;

    bool set_format; // false until one line is encountered. The group face entries must be defined with a consistent format, e.g. 1//1.
    std::vector<uint32_t> vertex_elements;
    bool has_normal_index;
    std::vector<uint32_t> normal_elements;
    bool has_texture_index;
    std::vector<uint32_t> texture_elements;

    // Check if a new element entry (vertex index, optional normal and texture indices)
    // is the same format as previously used in this group. If this is the first entry, set the format to the format of this entry.
    bool check_format(bool texture_indices, bool normal_indices) {
        if (!set_format) {
            has_texture_index = texture_indices;
            has_normal_index = normal_indices;
            set_format = true;
        } else {
            if (has_texture_index != texture_indices) return false;
            if (has_normal_index != normal_indices) return false;
        }
        return true;
    }

    uint32_t num_faces() const {
        return vertex_elements.size() / face_num_elements;
    }
};
struct ObjState {
    uint8_t mode;
    std::vector<vec3> vertices;

    bool has_texture_coordinates;
    int texture_coordinates_dimension; // 2 or 3-dimensional
    std::vector<float> texture_coordinates;

    bool has_normals;
    std::vector<vec3> normals;

    std::vector<ObjGroup> groups;
    ObjGroup &current_group() {
        return groups.back();
    }
    // Convert negative indices, e.g.
    //    f -1//-1 -3//-3 -2//-2
    // into the absolute index (starting at 1).
    uint32_t absolute_texture_index(int i) {
        // note: at least one vertex texture coordinate must have been defined previously for this to work.
        if (i < 0) {
            return texture_coordinates.size()/texture_coordinates_dimension + i;
        }
        return i-1; //remember, in Obj, indices start at 1.
    }
    uint32_t absolute_normal_index(int i) {
        if (i < 0) {
            return normals.size() + i;
        }
        return i-1;
    }
    uint32_t absolute_vertex_index(int i) {
        if (i < 0) {
            return vertices.size() + i;
        }
        return i-1;
    }

    uint32_t num_vertices() const { return vertices.size(); }
    uint32_t num_texture_coordinates() const { return texture_coordinates.size()/texture_coordinates_dimension; }
    uint32_t num_normals() const { return normals.size(); }

    void print() const {
        #define YESNO(BOOLEAN) (( BOOLEAN ) ? "Yes" : "No")
        printf("num_vertices: %u\n", num_vertices());
        printf("has_texture_coordinates: %s\n", YESNO(has_texture_coordinates));
        if (has_texture_coordinates) printf("num_texture_coordinates: %u\n", num_texture_coordinates());
        printf("has_normals: %s\n", YESNO(has_normals));
        if (has_normals) printf("num_normals: %u\n", num_normals());
        for (const ObjGroup &group : groups) {
            printf("group %s:\n", group.name.c_str());
            printf("    face_num_elements: %d\n", group.face_num_elements);
            printf("    has_normal_index: %s\n", YESNO(group.has_normal_index));
            printf("    has_texture_index: %s\n", YESNO(group.has_texture_index));
            printf("    num_elements: %zu\n", group.vertex_elements.size());
        }
    }
};

// Commands use this macro when they fail, to log the reason for failure and return the error code (false)
// to the command interpreter.
#define FAIL(ERROR_STRING) {\
    fprintf(stderr, "Obj error (line %d): %s\n", g_obj_line_number, ERROR_STRING);\
    return false;\
}
bool vertex_command(ObjCommand &command, ObjState &state)
{
    if (state.mode != OBJ_READING) FAIL("Not in reading state.");
    if (command.num_tokens < 4) FAIL("A vertex must be defined with three coordinates.");
    // EXCEPTION: Ignoring extra vertex values, since a model from sketchfab seems to use 6.
    float x,y,z;
    if (sscanf(command.token(1), "%f", &x) != 1) FAIL("Invalid x coordinate.");
    if (sscanf(command.token(2), "%f", &y) != 1) FAIL("Invalid y coordinate.");
    if (sscanf(command.token(3), "%f", &z) != 1) FAIL("Invalid z coordinate.");;
    state.vertices.push_back(vec3(x,y,z));
    return true;
}
bool vertex_texture_command(ObjCommand &command, ObjState &state)
{
    if (state.mode != OBJ_READING) FAIL("Not in reading state.");

    if (command.num_tokens == 3) {
        if (state.has_texture_coordinates) {
            if (state.texture_coordinates_dimension != 2) FAIL("Inconsistent texture coordinates dimension (2, should be 3).");
        }
        state.has_texture_coordinates = true;
        state.texture_coordinates_dimension = 2;
        float u,v;
        if (sscanf(command.token(1), "%f", &u) != 1) FAIL("Invalid u entry.");
        if (sscanf(command.token(2), "%f", &v) != 1) FAIL("Invalid v entry.");
        state.texture_coordinates.push_back(u);
        state.texture_coordinates.push_back(v);
    } else if (command.num_tokens == 4) {
        if (state.has_texture_coordinates) {
            if (state.texture_coordinates_dimension != 3) FAIL("Inconsistent texture coordinates dimension (3, should be 2).");
        }
        state.has_texture_coordinates = true;
        state.texture_coordinates_dimension = 3;
        float u,v,w;
        if (sscanf(command.token(1), "%f", &u) != 1) FAIL("Invalid u entry.");
        if (sscanf(command.token(2), "%f", &v) != 1) FAIL("Invalid v entry.");
        if (sscanf(command.token(3), "%f", &w) != 1) FAIL("Invalid w entry.");
        state.texture_coordinates.push_back(u);
        state.texture_coordinates.push_back(v);
        state.texture_coordinates.push_back(w);
    } else {
        FAIL("Texture coordinates can only be 2 or 3-dimensional.");
    }
    return true;
}
bool vertex_normal_command(ObjCommand &command, ObjState &state)
{
    if (command.num_tokens != 4) FAIL("Normals must be defined with three coordinates."); 
    state.has_normals = true;
    float x,y,z;
    if (sscanf(command.token(1), "%f", &x) != 1) FAIL("Invalid x entry.");
    if (sscanf(command.token(2), "%f", &y) != 1) FAIL("Invalid y entry.");
    if (sscanf(command.token(3), "%f", &z) != 1) FAIL("Invalid z entry.");
    state.normals.push_back(vec3(x,y,z));
    return true;
}
bool group_command(ObjCommand &command, ObjState &state)
{
    if (command.num_tokens != 2) FAIL("Invalid group command (g {name}).");
    state.groups.push_back(ObjGroup(command.token(1)));
}
bool face_command(ObjCommand &command, ObjState &state)
{
    if (command.num_tokens < 2) FAIL("Faces must have at least one element.");

    // If a face command hasn't been encountered yet for this group, its number of elements per face is decided here.
    int num_elements = command.num_tokens - 1;
    ObjGroup &group = state.current_group();
    if (group.face_num_elements == 0) {
        group.face_num_elements = num_elements;
    } else if (group.face_num_elements != num_elements) {
        // The number of elements per face in a group must be the same.
        FAIL("Inconsistent number of elements per face.");
    }

    // Either set the group's format (vertex, vertex+normal, vertex+texture, or vertex+texture+normal) or validate that
    // the format of this new face is consistent with that format.
    int a,b,c;
    int format;
    if (sscanf(command.token(1), "%d/%d/%d", &a, &b, &c) == 3) {
        if (!group.check_format(true, true)) {
            FAIL("Inconsistent element format in group.");
        }
        format = 0;
    }
    else if (sscanf(command.token(1), "%d//%d", &a, &b) == 2) {
        if (!group.check_format(false, true)) {
            FAIL("Inconsistent element format in group.");
        }
        format = 1;
    }
    else if (sscanf(command.token(1), "%d/%d", &a, &b) == 2) {
        if (!group.check_format(true, false)) {
            FAIL("Inconsistent element format in group.");
        }
        format = 2;
    }
    else if (sscanf(command.token(1), "%d", &a) == 1) {
        if (!group.check_format(false, false)) {
            FAIL("Inconsistent element format in group.");
        }
        format = 3;
    }
    else FAIL("Badly formed element entry.");

    // Read face elements.
    static const char *zero_index_error = "Indices must be non-zero (absolute indexing starts from 1).";
    static const char *badly_formed_entry_error = "Badly formed element entry.";
    for (int i = 0; i < num_elements; i++) {
	int v,vt,vn;
        switch (format) {
            case 0:
                if (sscanf(command.token(i+1), "%d/%d/%d", &v, &vt, &vn) != 3) FAIL(badly_formed_entry_error);
                if (v == 0 || vt == 0 || vn == 0) FAIL(zero_index_error);
                group.vertex_elements.push_back(state.absolute_vertex_index(v));
                group.texture_elements.push_back(state.absolute_texture_index(vt));
                group.normal_elements.push_back(state.absolute_normal_index(vn));
                break;
            case 1:
                if (sscanf(command.token(i+1), "%d//%d", &v, &vn) != 2) FAIL(badly_formed_entry_error);
                if (v == 0 || vn == 0) FAIL(zero_index_error);
                group.vertex_elements.push_back(state.absolute_vertex_index(v));
                group.normal_elements.push_back(state.absolute_normal_index(vn));
                break;
            case 2:
                if (sscanf(command.token(i+1), "%d/%d", &v, &vt) != 2) FAIL(badly_formed_entry_error);
                if (v == 0 || vt == 0) FAIL(zero_index_error);
                group.vertex_elements.push_back(state.absolute_vertex_index(v));
                group.texture_elements.push_back(state.absolute_texture_index(vt));
                break;
            case 3:
                if (sscanf(command.token(i+1), "%d", &v) != 1) FAIL(badly_formed_entry_error);
                if (v == 0) FAIL(zero_index_error);
                group.vertex_elements.push_back(state.absolute_vertex_index(v));
                break;
        }
    }
    return true;
}
bool ignore_command(ObjCommand &command, ObjState &state)
{
    return true;
}

bool ObjState_to_model(const ObjState &obj, MLModel &model)
{
    // !-IMPORTANT-! This assumes that all vertex attributes in the ObjState are defined together.
    // However, in a general Obj file, there may be, for example, a different number of normals than vertex positions.

    model.num_vertices = obj.num_vertices();
    model.positions = std::vector<vec3>(obj.vertices.size());
    for (int i = 0; i < obj.num_vertices(); i++) {
        model.positions[i] = obj.vertices[i];
    }
    model.has_normals = obj.has_normals;
    model.has_uvs = obj.has_texture_coordinates;
    // Copy over texture coordinates (uvs).
    if (obj.has_texture_coordinates) {
        // if (obj.num_texture_coordinates() != obj.num_vertices()) {
        //     FAIL("Currently, there must be the same number of vertex positions/texture coordinates/normals.");
        // }
        if (obj.texture_coordinates_dimension != 2) {
            FAIL("Only two-dimensional texture coordinates are currently supported.");
        }
        model.uvs = std::vector<TexCoord>(obj.num_texture_coordinates());
        for (int i = 0; i < obj.num_texture_coordinates(); i++) {
            model.uvs[i] = TexCoord(obj.texture_coordinates[2*i+0], obj.texture_coordinates[2*i+1]);
        }
    }
    // Copy over normals.
    if (obj.has_normals) {
        // if (obj.num_normals() != obj.num_vertices()) {
        //     FAIL("Currently, there must be the same number of vertex positions/texture coordinates/normals.");
        // }
        model.normals = std::vector<vec3>(obj.num_normals());
        for (int i = 0; i < obj.num_normals(); i++) {
            model.normals[i] = obj.normals[i];
        }
    }

    bool set_format; // false until one line is encountered. The group face entries must be defined with a consistent format, e.g. 1//1.
    std::vector<uint32_t> vertex_elements;
    bool has_normal_index;
    std::vector<uint32_t> normal_elements;
    bool has_texture_index;
    std::vector<uint32_t> texture_elements;

    // Currently, groups don't really mean anything.
    model.num_triangles = 0;
    for (const ObjGroup &group : obj.groups) {
        if (group.face_num_elements != 3) {
            // Currently, do nothing with non-triangles ...
            continue;
        }
        // Triangles.
        model.has_triangles = true;
        // Add this group's triangles.
        model.num_triangles += group.num_faces();
        for (int i = 0; i < group.num_faces(); i++) {
            // Still assuming that Obj vertex attributes are defined in packets with the same index ...
            uint32_t index_a = group.vertex_elements[3*i + 0];
            uint32_t index_b = group.vertex_elements[3*i + 1];
            uint32_t index_c = group.vertex_elements[3*i + 2];
            model.triangles.push_back(MLModelTriangle(index_a, index_b, index_c));
        }
    }
    return true;
}

bool load_Obj_model(std::istream &stream, MLModel &model)
{
    ObjState state;
    memset(&state, 0, sizeof(state));
    state.mode = OBJ_READING;
    state.groups.push_back(ObjGroup("root"));

    ObjCommand command;

    g_obj_line_number = 0; // Reset this. It is updated while parsing commands, so that the line number can be printed if there is an error.
    #define COMMAND(NAME, FUNCTION)\
        if (strcmp(command.token(0), NAME) == 0) {\
            if (!( FUNCTION )(command, state)) {\
                fprintf(stderr, "Error interpreting Obj \"%s\" command.\n", NAME);\
                return false;\
            }\
            continue;\
        }
            // printf("Command \"%s\"\n", NAME);
            // getchar();
    while (next_command(stream, command)) {
        // printf("%d tokens.\n", command.num_tokens);
        COMMAND("v", vertex_command);
        COMMAND("vt", vertex_texture_command);
        COMMAND("vn", vertex_normal_command);
        COMMAND("f", face_command);
        COMMAND("mtllib", ignore_command);
        COMMAND("usemtl", ignore_command);
    }

    // printf("%d\n", state.vertices.size());
    // state.print();

    // Interpret the ObjState structure and attempt to turn it into a model.
    if (!ObjState_to_model(state, model)) {
        FAIL("Parsed Obj file but failed to convert into an MLModel.");
    }
}
