bool load_OFF_model(std::istream &stream, Model &model)
{
    #define load_error(ERROR_STR) {\
        printf("OFF model load error: %s\n", ( ERROR_STR ));\
        return false;\
    }
    // Macro to get the next line, skipping lines which are just spaces and commented lines.
    #define next_line(STREAM,LINE,ERROR_MESSAGE) {\
        while (true) {\
            if (!std::getline(STREAM, LINE)) {\
                fprintf(stderr, "OFF model load error: %s\n", ERROR_MESSAGE);\
                exit(EXIT_FAILURE);\
            }\
            if (strspn(( LINE ).c_str(), " ") == strlen(( LINE ).c_str())) continue;\
            if (strncmp("#", ( LINE ).c_str(), 1) != 0) break;\
        }\
    }
    std::string line;
    next_line(stream, line, "Empty stream.");
    if (line != "OFF") load_error("OFF files must start with the magic line, \"OFF\".");
    next_line(stream, line, "No feature count declaration.");
    // Non-triangle faces are not supported.
    uint32_t num_vertices, num_triangles, num_edges;
    if (sscanf(line.c_str(), "%u %u %u", &num_vertices, &num_triangles, &num_edges) != 3) {
        load_error("Invalid num_vertices num_faces num_edges line.");
    }
    // Vertices
    std::vector<vec3> positions(num_vertices);

    for (uint32_t i = 0; i < num_vertices; i++) {
        next_line(stream, line, "Not enough vertex lines.");
        float x, y, z;
        if (sscanf(line.c_str(), "%f %f %f", &x, &y, &z) != 3) load_error("Invalid vertex line.");
        positions[i] = vec3(x,y,z);
    }
    // Triangles
    std::vector<ModelTriangle> triangles(num_triangles);
    for (uint32_t i = 0; i < num_triangles; i++) {
        next_line(stream, line, "Not enough triangle index lines.");
        uint32_t should_be_three, a,b,c;
        if (sscanf(line.c_str(), "%u %u %u %u", &should_be_three, &a, &b, &c) != 4) load_error("Invalid triangle index line.");
        if (should_be_three != 3) load_error("Non-triangle faces are not supported.");
        triangles[i] = ModelTriangle(a,b,c);
    }
    // Edge data is ignored.
    //-

    model.num_vertices = num_vertices;
    model.positions = positions;
    model.has_triangles = true;
    model.triangles = triangles;
    model.num_triangles = num_triangles;

    return true;
}
