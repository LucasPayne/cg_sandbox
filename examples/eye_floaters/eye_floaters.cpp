#include "cg_sandbox.h"

#include <functional>

#include <IL/il.h>

Aspect<Camera> camera;
IGC::Context *pContext;
float brightness = 1.f;

typedef struct RGBImageData_s {
    uint8_t *image; // length: 3*width*height.
    int width;
    int height;
} RGBImageData;

typedef struct RGBAImageData_s {
    uint8_t *image;
    int width;
    int height;
} RGBAImageData;


class FloaterSheet
{
public:
    struct Motion
    {
        float radius;
        std::function<float(float)> curve;
        std::function<vec2(vec2,vec2)> impulse_modifier;
        vec2 position;
        vec2 velocity;
        Motion()
        {
            position = vec2(0,0);
            velocity = vec2(0,0);
        }
    };
    float impulse_multiplier;
    std::vector<Motion> motions;

    struct Segment
    {
        // generative
        float radius;
        float opacity;
        std::vector<vec2> points;
    };
    std::vector<Segment> segments;
};

struct Skybox : public IBehaviour
{
    GLuint textures[6];
    GLuint vao;
    GLuint vbo;
    int num_vertices;
    Resource<GLShaderProgram> shader;

    GLuint book_texture;
    GLuint book_vao;
    GLuint book_vbo;
    Resource<GLShaderProgram> book_shader;
    mat4x4 book_model_matrix;

    Skybox()
    {
    }

    RGBImageData load_rgb_bmp(std::string filename)
    {
        ILuint image;
        ilGenImages(1, &image);
        ilBindImage(image);

        if ( !ilLoadImage(filename.c_str()) )
        {
            printf("image load fail\n");
            exit(0);
        }
        int width = ilGetInteger(IL_IMAGE_WIDTH);
        int height = ilGetInteger(IL_IMAGE_HEIGHT);
        uint8_t *bytes = (uint8_t *) malloc(width*height*3);
        ilCopyPixels(0, 0, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, bytes);

        RGBImageData data;
        data.width = width;
        data.height = height;
        data.image = bytes;

        ilDeleteImages(1, &image);
        return data;
    }

    RGBAImageData load_rgba_bmp(std::string filename)
    {
        ILuint image;
        ilGenImages(1, &image);
        ilBindImage(image);

        if ( !ilLoadImage(filename.c_str()) )
        {
            printf("image load fail\n");
            exit(0);
        }
        int width = ilGetInteger(IL_IMAGE_WIDTH);
        int height = ilGetInteger(IL_IMAGE_HEIGHT);
        uint8_t *bytes = (uint8_t *) malloc(width*height*4);
        ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, bytes);

        RGBAImageData data;
        data.width = width;
        data.height = height;
        data.image = bytes;

        ilDeleteImages(1, &image);
        return data;
    }

    GLuint load_texture(std::string path, bool use_alpha = false)
    {
        // Textures can only be loaded from BMP files. These BMP files must also be uncompressed, use minimal BMP functionality, and be 8-bit-channel RGB.
   
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
   
        // Make sure texture-related state allows the correct loading of textures.
        // https://stackoverflow.com/questions/7380773/glteximage2d-segfault-related-to-width-height
        // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        // glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        // glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
   
        if (use_alpha)
        {
            RGBAImageData image_data = load_rgba_bmp(path);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_data.width, image_data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.image);
            free(image_data.image);
        }
        else
        {
            RGBImageData image_data = load_rgb_bmp(path);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_data.width, image_data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data.image);
            free(image_data.image);
        }
   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   
        glBindTexture(GL_TEXTURE_2D, 0);
   
        return texture_id;
    }


    void init ()
    {
        measuring = false;
        std::vector<std::string> image_paths = {
            "/home/lucas/code/cg_sandbox/examples/eye_floaters/skybox_0.png",
            "/home/lucas/code/cg_sandbox/examples/eye_floaters/skybox_1.png",
            "/home/lucas/code/cg_sandbox/examples/eye_floaters/skybox_2.png",
            "/home/lucas/code/cg_sandbox/examples/eye_floaters/skybox_3.png",
            "/home/lucas/code/cg_sandbox/examples/eye_floaters/skybox_4.png",
            "/home/lucas/code/cg_sandbox/examples/eye_floaters/skybox_5.png",
        };
        for (int i = 0; i < 6; i++)
        {
            textures[i] = load_texture(image_paths[i]);
        }

        book_texture = load_texture("/home/lucas/code/cg_sandbox/examples/eye_floaters/book.png", true);
        book_model_matrix = mat4x4::translation(0,-0.5,0.2) * Quaternion::from_axis_angle(vec3(1,0,0)).matrix() * mat4x4::scale(0.25);

        struct Vertex
        {
            vec3 position;
            vec2 uv;
            int face_number;
        };
        std::vector<Vertex> vertices;

        auto create_face = [&](mat3x3 rotation, int face_number)
        {
            std::vector<vec3> positions = {
                {-1,-1,1},
                {1,-1,1},
                {1,1,1},
                {-1,1,1},
            };
            std::vector<vec2> uvs = {
                {0,0},
                {1,0},
                {1,1},
                {0,1},
            };
            std::vector<Vertex> new_vertices;
            for (int i = 0; i < 4; i++)
            {
                Vertex vertex = {
                    rotation * positions[i],
                    uvs[i],
                    face_number
                };
                new_vertices.push_back(vertex);
            }
            vertices.push_back(new_vertices[0]);
            vertices.push_back(new_vertices[1]);
            vertices.push_back(new_vertices[2]);
            vertices.push_back(new_vertices[0]);
            vertices.push_back(new_vertices[2]);
            vertices.push_back(new_vertices[3]);
        };
        create_face(mat3x3::identity(), 0);
        create_face(Quaternion::from_axis_angle(vec3(0,1,0), M_PI/2).matrix().top_left(),  1);
        create_face(Quaternion::from_axis_angle(vec3(0,1,0), M_PI).matrix().top_left(),    2);
        create_face(Quaternion::from_axis_angle(vec3(0,1,0), -M_PI/2).matrix().top_left(), 3);
        create_face(Quaternion::from_axis_angle(vec3(1,0,0), -M_PI/2).matrix().top_left(), 4);
        create_face(Quaternion::from_axis_angle(vec3(1,0,0), M_PI/2).matrix().top_left(),  5);

        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), (const void *) &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) sizeof(vec3));
        glEnableVertexAttribArray(1);
        glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), (const void *) (sizeof(vec3) + sizeof(vec2)));
        glEnableVertexAttribArray(2);

        shader = world->resources.add<GLShaderProgram>();
        shader->add_shader(GLShader(VertexShader, "/home/lucas/code/cg_sandbox/examples/eye_floaters/skybox_shader.vert"));
        shader->add_shader(GLShader(FragmentShader, "/home/lucas/code/cg_sandbox/examples/eye_floaters/skybox_shader.frag"));
        shader->link();
        num_vertices = vertices.size();

        // book
        struct BookVertex
        {
            vec3 position;
            vec2 uv;
        };
        std::vector<BookVertex> book_vertices =
        {
            {{-1,-1,0}, {0,0}},
            {{1,-1,0}, {1,0}},
            {{1,1,0}, {1,1}},
            {{-1,-1,0}, {0,0}},
            {{1,1,0}, {1,1}},
            {{-1,1,0}, {0,1}},
        };
        glCreateVertexArrays(1, &book_vao);
        glBindVertexArray(book_vao);
        glGenBuffers(1, &book_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, book_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(BookVertex) * book_vertices.size(), (const void *) &book_vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BookVertex), (const void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BookVertex), (const void *) sizeof(vec3));
        glEnableVertexAttribArray(1);
       
        book_shader = world->resources.add<GLShaderProgram>();
        book_shader->add_shader(GLShader(VertexShader, "/home/lucas/code/cg_sandbox/examples/eye_floaters/book_shader.vert"));
        book_shader->add_shader(GLShader(FragmentShader, "/home/lucas/code/cg_sandbox/examples/eye_floaters/book_shader.frag"));
        book_shader->link();
    }

    bool measuring;
    std::vector<vec2> measured_positions;
    std::vector<vec3> measured_intersections;
    void keyboard_handler(KeyboardEvent e)
    {
        if (e.action == KEYBOARD_PRESS)
        {
            if (e.key.code == KEY_R)
            {
                if (measuring)
                {
                    FILE *file = fopen("measurements.txt", "w+");
                    for (vec2 pos : measured_positions)
                    {
                        char s[4096];
                        sprintf(s, "%.5f %.5f\n", pos.x(), pos.y());
                        fwrite(s, 1, strlen(s), file);
                    }
                    fclose(file);
                    measuring = false;
                }
                else
                {
                    measured_positions.clear();
                    measured_intersections.clear();
                    measuring = true;
                }
            }
        }
    };
    void mouse_handler(MouseEvent e)
    {
    };
    void post_render_update()
    {
        shader->bind();
        mat4x4 vp_matrix = camera->view_projection_matrix();
        glUniformMatrix4fv(shader->uniform_location("mvp_matrix"), 1, GL_FALSE, (const GLfloat *) &vp_matrix);
        glUniform1f(shader->uniform_location("time"), pContext->time());
        glUniform1f(shader->uniform_location("brightness"), brightness);

        for (int i= 0; i < 6; i++)
        {
            std::string name = "images[" + std::to_string(i) + "]";
            glUniform1i(shader->uniform_location(name), i);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textures[i]);
        }

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, num_vertices);
        shader->unbind();
        glBindVertexArray(0);

        // book
        book_shader->bind();
        mat4x4 mvp_matrix = camera->view_projection_matrix() * book_model_matrix;
        glUniformMatrix4fv(book_shader->uniform_location("mvp_matrix"), 1, GL_FALSE, (const GLfloat *) &mvp_matrix);
        glUniform1f(book_shader->uniform_location("brightness"), brightness);
        glBindVertexArray(book_vao);
        glUniform1i(book_shader->uniform_location("image"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, book_texture);
        glEnable(GL_BLEND);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        book_shader->unbind();

        //for (vec3 pos : measured_intersections)
        //{
        //    std::cout << "measure: " << pos << "\n";
        //    world->graphics.paint.sphere(pos, 0.0018, vec4(0,1,0,1));
        //}
        for (vec2 pos : measured_positions)
        {
            world->graphics.paint.sphere((book_model_matrix * vec4(pos.x(), pos.y(), 0, 1)).xyz(), 0.0018, vec4(0,1,0,1));
        }
    };
};

class App : public IGC::Callbacks
{
public:
    World &world;
    IGC::Context &context;
    App(World &world, IGC::Context &context);

    void saccadic_motion(vec3 from, vec3 to);
    float time_since_saccadic_motion;

    vec3 head_forward;
    vec3 head_forward_to;
    vec3 head_up()
    {
        return vec3::cross(vec3::cross(head_forward, vec3(0,1,0)), head_forward).normalized();
    }

    void lookat(vec3 to)
    {
        Quaternion q = Quaternion::from_axis_angle(std::acos(vec3::dot(head_up(), vec3(0,1,0))) * vec3::cross(head_forward, head_up()).normalized());
        cameraman.get<Transform>()->lookat(q * to);
        cameraman.get<Transform>()->rotation = q.inverse() * cameraman.get<Transform>()->rotation;
    }
    vec3 eyes_forward;
    float fov_angle;

    float saccade_widget_radius;
    float saccade_widget_origin_x;
    float saccade_widget_origin_y;

    std::vector<FloaterSheet> sheets;

    Skybox *skybox;

    Entity cameraman;

    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    void window_handler(WindowEvent e);

    std::vector<vec2> replaying;
    float replay_start_time;
};


App::App(World &_world, IGC::Context &_context) : world{_world}, context{_context}
{
    cameraman = world.entities.add();
    camera = cameraman.add<Camera>(0.1, 300, 0.1, 0.566);
    cameraman.add<Transform>(0,0,0);

    time_since_saccadic_motion = 0;

    // skybox
    auto skybox_entity = world.entities.add();
    skybox = world.add<Skybox>(skybox_entity);
    skybox_entity.add<Transform>(0,0,0);

    head_forward = vec3(0,0,1);
    eyes_forward = vec3(0,0,1);
    fov_angle = M_PI/3.25f;

    lookat(eyes_forward);

    saccade_widget_radius = 0.05;
    float h_mul = 1.f / camera->m_aspect_ratio;
    saccade_widget_origin_x = 1 - saccade_widget_radius - 0.025;
    saccade_widget_origin_y = h_mul * (saccade_widget_radius + 0.025);

    {
        FloaterSheet sheet;
        sheet.impulse_multiplier = 0.1;
        {
            FloaterSheet::Motion motion;
            motion.radius = 0.16f;
            motion.curve = [](float dist)->float {
                return 4.f;
            };
            motion.impulse_modifier = [](vec2 pos, vec2 impulse)->vec2 {
                impulse.y() *= 0.2;
                return 5*impulse;
            };
            sheet.motions.push_back(motion);
        }
        {
            FloaterSheet::Motion motion;
            motion.radius = 0.0033;
            motion.curve = [](float dist)->float {
                return 0.02;
            };
            motion.impulse_modifier = [](vec2 pos, vec2 impulse)->vec2 {
                return vec2(0.2f*impulse.x(), 0.25*impulse.y()+0.1*impulse.x());
            };
            sheet.motions.push_back(motion);
        }
        {
            FloaterSheet::Motion motion;
            motion.radius = 0.005;
            motion.curve = [](float dist)->float {
                return 1.f;
            };
            motion.impulse_modifier = [](vec2 pos, vec2 impulse)->vec2 {
                return 3*vec2(0.2f*impulse.y()*impulse.x(), 0.25*impulse.y()+0.1*impulse.x());
            };
            sheet.motions.push_back(motion);
        }
        {
            FloaterSheet::Motion motion;
            motion.radius = 0.01f;
            motion.curve = [](float dist)->float {
                return 0.0001f;
            };
            motion.impulse_modifier = [](vec2 pos, vec2 impulse)->vec2 {
                return 0.2*impulse;
            };
            sheet.motions.push_back(motion);
        }
        // segments
        {
            FloaterSheet::Segment segment;
            segment.radius = 0.01f;
            segment.opacity = 0.5;
            segment.points.push_back(vec2(0.026,0));
            for (int i = 0; i < 100; i++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + vec2(2*frand()-1, 2*frand()-1)*0.001);
            }
            for (int i = 0; i < 30; i++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + vec2(2*frand()-0.3, 2*frand()-0.77)*0.0015);
            }
            sheet.segments.push_back(segment);
        }
        {
            FloaterSheet::Segment segment;
            segment.radius = 0.04f;
            segment.opacity = 0.2;
            //segment.points = {vec2(0,0), vec2(0,0.01), vec2(0.01,0.01)};
            segment.points.push_back(vec2(0.026,0));
            for (int i = 0; i < 30; i++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + vec2(2*frand()-0.3, 2*frand()-1.33)*0.0015);
            }
            sheet.segments.push_back(segment);
        }
        for (int n = 0; n < 10; n++)
        {
            FloaterSheet::Segment segment;
            segment.radius = 0.01f + frand()*0.02;
            segment.opacity = 0.4*(0.2+frand()*0.1);
            //segment.points = {vec2(0,0), vec2(0,0.01), vec2(0.01,0.01)};
            segment.points.push_back(vec2(0.026,0));
            vec2 shift = vec2(frand(),2*frand()-1);
            float wander = 0.0015 + frand()*0.01;
            for (int i = 0; i < 30; i++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + (vec2(2*frand()-1, 2*frand()-1)+shift)*wander);
            }
            sheet.segments.push_back(segment);
        }
        sheets.push_back(sheet);
    }
    for (int n = 0; n < 30; n++)
    {
        FloaterSheet sheet;
        sheet.impulse_multiplier = 1;
        //float radius = 0.2+0.1*(2*frand()-1);
        float radius = 1;
        float curve_value = 0.5*(1 + 2*frand());
        float impulse_multiplier = 0.25*(5+2.5*frand());
        mat2x2 impulse_matrix = mat2x2(1+0.1*(2*frand()-1),0.1*(2*frand()-1),0.1*(2*frand()-1),1+0.1*(2*frand()-1));
        {
            FloaterSheet::Motion motion;
            motion.radius = radius;
            motion.curve = [curve_value](float dist)->float {
                return curve_value;
            };
            motion.impulse_modifier = [impulse_matrix, impulse_multiplier](vec2 pos, vec2 impulse)->vec2 {
                return impulse_multiplier * (impulse_matrix * impulse).normalized() * impulse.length();
            };
            sheet.motions.push_back(motion);
        }
        // segments
        for (int i = 0; i < 20; i++)
        {
            FloaterSheet::Segment segment;
            segment.radius = 15*(0.005f + frand()*0.002);
            segment.opacity = 0.4*0.08*(0.2+frand()*0.2);
            if ( frand() > 0.9 )
            {
                segment.opacity = 0.15+frand()*0.025;
                segment.radius *= 0.3;
            }
            //segment.opacity = 1;
            vec2 shift = 0.2*vec2(2*frand()-1,2*frand()-1);
            float wander = 0.0015 + frand()*0.01;
            segment.points.push_back(2*vec2(2*frand()-1, 2*frand()-1));
            int num_central = frand()*100;
            for (int j = 0; j < num_central; j++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + vec2(2*frand()-1, 2*frand()-1)*0.001);
            }
            for (int j = 0; j < 30; j++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + (vec2(2*frand()-1, 2*frand()-1)+shift)*wander);
            }
            sheet.segments.push_back(segment);
        }
        sheets.push_back(sheet);
    }
    // big sheets
    for (int n = 0; n < 3; n++)
    {
        FloaterSheet sheet;
        sheet.impulse_multiplier = 1;
        float radius = 1;
        float curve_value = 0.5*(1 + 2*frand());
        float impulse_multiplier = 0.25*(5+2.5*frand());
        mat2x2 impulse_matrix = mat2x2(1+0.1*(2*frand()-1),0.1*(2*frand()-1),0.1*(2*frand()-1),1+0.1*(2*frand()-1));
        {
            FloaterSheet::Motion motion;
            motion.radius = radius;
            motion.curve = [curve_value](float dist)->float {
                return curve_value;
            };
            motion.impulse_modifier = [impulse_matrix, impulse_multiplier](vec2 pos, vec2 impulse)->vec2 {
                return impulse_multiplier * (impulse_matrix * impulse).normalized() * impulse.length();
            };
            sheet.motions.push_back(motion);
        }
        FloaterSheet::Segment segment;
        segment.radius = 1;
        segment.opacity = 0.066;
        int num = 50;
        for (int i = 0; i < num; i++)
        {
            segment.points.push_back(vec2(-10+20*(i*1.f)/num,0.01*(2*frand()-1)));
        }
        sheet.segments.push_back(segment);

        sheets.push_back(sheet);
    }
    for (int n = 0; n < 10; n++)
    {
        FloaterSheet sheet;
        sheet.impulse_multiplier = 1;
        //float radius = 0.2+0.1*(2*frand()-1);
        float radius = 0.1+frand()*0.05;
        float curve_value = 0.5*(1 + 2*frand());
        float impulse_multiplier = 1*(5+2.5*frand());
        //mat2x2 impulse_matrix = mat2x2(1+0.1*(2*frand()-1),0.1*(2*frand()-1),0.1*(2*frand()-1),1+0.1*(2*frand()-1));
        mat2x2 impulse_matrix = mat2x2::identity();
        {
            FloaterSheet::Motion motion;
            motion.radius = radius;
            motion.curve = [curve_value](float dist)->float {
                return curve_value;
            };
            motion.impulse_modifier = [impulse_matrix, impulse_multiplier](vec2 pos, vec2 impulse)->vec2 {
                return impulse_multiplier * (impulse_matrix * impulse).normalized() * impulse.length();
            };
            sheet.motions.push_back(motion);
        }
        // segments
        for (int i = 0; i < 20; i++)
        {
            FloaterSheet::Segment segment;
            segment.radius = 1*(0.005f + frand()*0.002);
            segment.opacity = 0.4*0.5*(0.2+frand()*0.2);
            //segment.opacity = 1;
            vec2 shift = 0.2*vec2(2*frand()-1,2*frand()-1);
            float wander = 0.0015 + frand()*0.01;
            segment.points.push_back(2*vec2(2*frand()-1, 2*frand()-1));
            int num_central = frand()*100;
            for (int j = 0; j < num_central; j++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + vec2(2*frand()-1, 2*frand()-1)*0.001);
            }
            for (int j = 0; j < 30; j++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + (vec2(2*frand()-1, 2*frand()-1)+shift)*wander);
            }
            sheet.segments.push_back(segment);
        }
        sheets.push_back(sheet);
    }

    // more bigs
    {
        FloaterSheet sheet;
        sheet.impulse_multiplier = 0.1;
        {
            FloaterSheet::Motion motion;
            motion.radius = 0.25f;
            motion.curve = [](float dist)->float {
                return 16.f;
            };
            motion.impulse_modifier = [](vec2 pos, vec2 impulse)->vec2 {
                impulse.y() *= 0.5;
                return 15*impulse;
            };
            sheet.motions.push_back(motion);
        }
        {
            FloaterSheet::Motion motion;
            motion.radius = 0.0033;
            motion.curve = [](float dist)->float {
                return 0.02;
            };
            motion.impulse_modifier = [](vec2 pos, vec2 impulse)->vec2 {
                return vec2(0.2f*impulse.x(), 0.25*impulse.y()+0.1*impulse.x());
            };
            sheet.motions.push_back(motion);
        }
        {
            FloaterSheet::Motion motion;
            motion.radius = 0.005;
            motion.curve = [](float dist)->float {
                return 1.f;
            };
            motion.impulse_modifier = [](vec2 pos, vec2 impulse)->vec2 {
                return 3*vec2(0.2f*impulse.y()*impulse.x(), 0.25*impulse.y()+0.1*impulse.x());
            };
            sheet.motions.push_back(motion);
        }
        {
            FloaterSheet::Motion motion;
            motion.radius = 0.01f;
            motion.curve = [](float dist)->float {
                return 0.0001f;
            };
            motion.impulse_modifier = [](vec2 pos, vec2 impulse)->vec2 {
                return 0.2*impulse;
            };
            sheet.motions.push_back(motion);
        }
        // segments
        {
            FloaterSheet::Segment segment;
            segment.radius = 0.015f;
            segment.opacity = 0.07;
            //segment.points = {vec2(0,0), vec2(0,0.01), vec2(0.01,0.01)};
            segment.points.push_back(vec2(-0.06,0.015));
            for (int i = 0; i < 100; i++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + vec2(2*frand()-1, 2*frand()-1)*0.0015);
            }
            for (int i = 0; i < 30; i++)
            {
                segment.points.push_back(segment.points[segment.points.size()-1] + vec2(2*frand()-1 - 0.5, 2*frand()-1-0.1)*0.0015);
            }
            sheet.segments.push_back(segment);
        }
        sheets.push_back(sheet);
    }
}

void App::close()
{
}

void App::loop()
{
    // head snap
    head_forward = (head_forward + 10*head_forward_to*pContext->delta_time()).normalized();
   
    // std::vector<vec2> points = {vec2(-0.05, 0), vec2(0.05, 0)};
    float thickness = 2;
    float crosshair_radius = 0.01;
    {
        std::vector<vec2> points = {vec2(0.5-crosshair_radius, 0.5), vec2(0.5 + crosshair_radius, 0.5)};
        world.graphics.paint.chain_2D(points, thickness, vec4(0,1,0,1));
    }
    {
        std::vector<vec2> points = {vec2(0.5, 0.5-crosshair_radius/camera->m_aspect_ratio), vec2(0.5, 0.5+crosshair_radius/camera->m_aspect_ratio)};
        world.graphics.paint.chain_2D(points, thickness, vec4(0,1,0,1));
    }

    mat4x4 M = camera->view_projection_matrix();
    vec4 T = M * vec4(head_forward, 0);
    float head_x = T.x()/T.w()*0.5 + 0.5;
    float head_y = T.y()/T.w()*0.5 + 0.5;
    {
        vec4 T = M * vec4(head_forward, 0);
        {
            std::vector<vec2> points = {vec2(head_x-crosshair_radius, head_y), vec2(head_x+crosshair_radius, head_y)};
            world.graphics.paint.chain_2D(points, thickness*2, vec4(1,1,1,1));
        }
        {
            std::vector<vec2> points = {vec2(head_x, head_y-crosshair_radius/camera->m_aspect_ratio), vec2(head_x, head_y+crosshair_radius/camera->m_aspect_ratio)};
            world.graphics.paint.chain_2D(points, thickness*2, vec4(1,1,1,1));
        }
    }

    // draw fov circle in worldspace
    /*
    {
        vec3 X = vec3::cross(head_forward, vec3(0,1,0)).normalized();
        vec3 Y = vec3::cross(X, head_forward);
        std::vector<vec2> points(361);
        for (int i = 0; i < 361; i++ )
        {
            float angle = 2*M_PI/360 * i;
            vec3 angled = std::cos(fov_angle)*head_forward + std::sin(fov_angle)*std::cos(angle)*X + std::sin(fov_angle)*std::sin(angle)*Y;
            vec4 T = M * vec4(angled, 0);
            float x = T.x()/T.w()*0.5 + 0.5;
            float y = T.y()/T.w()*0.5 + 0.5;
            points[i] = vec2(x, y);
        }
        world.graphics.paint.chain_2D(points, thickness, vec4(0,0,1,1));
    }
    */

    // Draw saccade widget
    {
        float r = saccade_widget_radius;
        float h_mul = 1.f / camera->m_aspect_ratio;
        std::vector<vec2> points(361);
        float o_x = saccade_widget_origin_x;
        float o_y = saccade_widget_origin_y;
        for (int i = 0; i < 361; i++ )
        {
            float angle = 2*M_PI/360 * i;
            float x = o_x + r*std::cos(angle);
            float y = o_y + h_mul*r*std::sin(angle);
            points[i] = vec2(x, y);
        }
        world.graphics.paint.chain_2D(points, 1, vec4(0,0,0,1));

        {
            std::vector<vec2> points = {vec2(o_x-0.01, o_y), vec2(o_x+0.01, o_y)};
            world.graphics.paint.chain_2D(points, 1, vec4(1,0,0,1));
        }
        {
            std::vector<vec2> points = {vec2(o_x, o_y-0.01*h_mul), vec2(o_x, o_y+0.01*h_mul)};
            world.graphics.paint.chain_2D(points, 1, vec4(1,0,0,1));
        }

        float angle = std::acos( vec3::dot(head_forward, eyes_forward) );
        float angle_factor = angle / fov_angle;
        vec3 X = vec3::cross(head_forward, vec3(0,1,0)).normalized();
        vec3 Y = vec3::cross(X, head_forward);
        vec2 dir = vec2(vec3::dot(eyes_forward, X), vec3::dot(eyes_forward, Y)).normalized();
        vec2 shift = vec2(angle_factor*dir.x()*r, angle_factor*dir.y()*r*h_mul);
        {
            std::vector<vec2> points = {shift+vec2(o_x-0.01, o_y), shift+vec2(o_x+0.01, o_y)};
            world.graphics.paint.chain_2D(points, 1, vec4(0,1,0,1));
        }
        {
            std::vector<vec2> points = {shift+vec2(o_x, o_y-0.01*h_mul), shift+vec2(o_x, o_y+0.01*h_mul)};
            world.graphics.paint.chain_2D(points, 1, vec4(0,1,0,1));
        }
    }
    //if (!camera->enabled) camera->enabled = true;


    // Sheets
    for (FloaterSheet &sheet : sheets)
    {
        vec2 position = vec2(0,0);
        for (FloaterSheet::Motion &motion : sheet.motions)
        {
            if (motion.position.length() > motion.radius)
            {
                vec2 dir = motion.position.normalized();
                motion.position = motion.radius * dir;
                if (vec2::dot(dir, motion.velocity) > 0)
                {
                    motion.velocity -= vec2::dot(dir, motion.velocity)*dir;
                    motion.velocity *= 1-context.delta_time()*1.f;
                }
            }
            motion.velocity *= 1 - context.delta_time()*motion.curve(motion.position.length() / motion.radius);
            motion.position += context.delta_time() * motion.velocity;

            position += motion.position;
        }
        for (FloaterSheet::Segment &segment : sheet.segments)
        {
            std::vector<vec2> positions;
            for (vec2 point : segment.points)
            {
                positions.push_back(vec2(0.5, 0.5) + vec2(point.x() + position.x(), (point.y() + position.y())/camera->m_aspect_ratio));
            }
            //world.graphics.paint.chain_2D(positions, 10, vec4(0,0,0,0.2));
            std::vector<float> knots(positions.size()+3);
            if (knots.size() > 1) for (int i = 0; i < knots.size(); i++) knots[i] = (1.f*i)/(knots.size()-1);

            vec2 velocity = vec2(0,0);
            for (FloaterSheet::Motion &motion : sheet.motions)
            {
                velocity += motion.velocity;
            }
            float alpha = 100*velocity.length();
            alpha += 0.2;
            if (alpha < 0) alpha = 0;
            if (alpha > 1) alpha = 1;
            alpha = std::max(alpha, 1-0.2f*time_since_saccadic_motion);

            // brightness
            alpha *= std::pow(std::min(brightness + 0.6f, 1.f), 8);
           
            world.graphics.paint.bspline(camera, 2, positions, knots, segment.radius, vec4(0,0,0,segment.opacity*alpha));
        }
    }

    // breathing
    float time = pContext->time();
    vec3 before = cameraman.get<Transform>()->position;
    vec3 after = 0.18*vec3(0, 0.025*std::sin(time)+0.01*std::sin(2.2*time), 0.005*std::cos(0.666*time));

    float ts[3];
    for (int i = 0; i < 3; i++) ts[i] = ((eyes_forward[i] < 0 ? -1 : 1) - before[i])/eyes_forward[i];
    float t = std::min(std::min(ts[0], ts[1]), ts[2]);
    vec3 new_eyes_forward = (before + t*eyes_forward - after).normalized();
    lookat( after + new_eyes_forward );
    saccadic_motion(eyes_forward, new_eyes_forward);
    eyes_forward = new_eyes_forward;
    cameraman.get<Transform>()->position = after;

    // replay
    if ( replaying.size() > 0 )
    {
        float t = pContext->time() - replay_start_time;
        int i = int(t*6);
        if ( i >= replaying.size() )
        {
            replaying.clear();
        }
        else
        {
            vec2 pos = replaying[i];
            vec3 new_eyes_forward = ((skybox->book_model_matrix * vec4(pos.x(), pos.y(), 0, 1)).xyz() - cameraman.get<Transform>()->position).normalized();
            lookat( new_eyes_forward );
            saccadic_motion(eyes_forward, new_eyes_forward);
            eyes_forward = new_eyes_forward;
        }
    }

    time_since_saccadic_motion += pContext->delta_time();
}

void App::window_handler(WindowEvent e)
{
}

void App::keyboard_handler(KeyboardEvent e)
{
    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == KEY_UP_ARROW) {
            brightness += 0.1;
            if (brightness > 1) brightness = 1;
        }
        if (e.key.code == KEY_DOWN_ARROW) {
            brightness -= 0.1;
            if (brightness < 0) brightness = 0;
        }
        if (e.key.code == KEY_Q) {
            exit(EXIT_SUCCESS);
        }
        if (e.key.code == KEY_E) {
            head_forward_to = eyes_forward;
            for (auto &sheet : sheets)
            {
                for (auto &motion : sheet.motions)
                {
                    motion.position = vec2(0,0);
                    motion.velocity = vec2(0,0);
                }
            }
        }
        if (e.key.code == KEY_P || e.key.code == KEY_O) {
            if (replaying.size() > 0) replaying.clear();
            else
            {
                FILE *file = fopen(e.key.code == KEY_P ? "page_read.txt" : "measurements.txt", "r");
                replaying.clear();
                if (file)
                {
                    float x, y;
                    while ( fscanf(file, "%f %f\n", &x, &y) != EOF )
                    {
                        replaying.push_back(vec2(x, y));
                    }
                }
                replay_start_time = pContext->time();
                fclose(file);
            }
        }
    }
}

void App::mouse_handler(MouseEvent e)
{
    if ( e.action == MOUSE_BUTTON_PRESS && e.button.code == MOUSE_LEFT )
    {
        // Check if in the saccade widget.
        float dist = std::sqrt((e.cursor.x - saccade_widget_origin_x)*(e.cursor.x - saccade_widget_origin_x)
                + (e.cursor.y - saccade_widget_origin_y)*(e.cursor.y - saccade_widget_origin_y)*(camera->m_aspect_ratio*camera->m_aspect_ratio) );
        vec3 new_eyes_forward;
        if ( dist < saccade_widget_radius )
        {
            float angle = fov_angle * dist / saccade_widget_radius;
            vec3 X = vec3::cross(head_forward, vec3(0,1,0)).normalized();
            vec3 Y = vec3::cross(X, head_forward);
            float theta = std::acos((e.cursor.x - saccade_widget_origin_x)/dist);
            if (e.cursor.y < saccade_widget_origin_y) theta = -theta;
            new_eyes_forward = std::cos(angle)*head_forward + std::sin(angle)*(std::cos(theta)*X + std::sin(theta)*Y);
        }
        else
        {
            new_eyes_forward = camera->ray(e.cursor.x, e.cursor.y).direction;
            //context.set_cursor_position(0.5, 0.5);
        }
        float angle = std::acos( vec3::dot(head_forward, new_eyes_forward) );
        #if 1
        if ( angle > fov_angle )
        {
            vec3 line = vec3::cross( new_eyes_forward, head_forward ).normalized();
            vec3 right = vec3::cross( head_forward, line );
            new_eyes_forward = std::cos(fov_angle)*head_forward + std::sin(fov_angle)*right;
        }
        #endif
        lookat( new_eyes_forward );
        saccadic_motion(eyes_forward, new_eyes_forward);
        eyes_forward = new_eyes_forward;
        //camera->enabled = false;

        if (skybox->measuring)
        {
            vec3 n = (skybox->book_model_matrix * vec4(0,0,1,0)).xyz();
            vec3 right = (skybox->book_model_matrix * vec4(1,0,0,0)).xyz();
            vec3 up = (skybox->book_model_matrix * vec4(0,1,0,0)).xyz();
            vec3 origin = (skybox->book_model_matrix * vec4(0,0,0,1)).xyz();
            float t = -vec3::dot(cameraman.get<Transform>()->position - origin, n)/(vec3::dot(eyes_forward, n));
            vec3 inter = cameraman.get<Transform>()->position + t*eyes_forward;
            vec3 local = (skybox->book_model_matrix.inverse() * vec4(inter,1)).xyz();
            vec2 measurement = vec2(local.x(),local.y()*(1/0.461));
            skybox->measured_positions.push_back(measurement);
            skybox->measured_intersections.push_back(inter);
        }
    }
}

void App::saccadic_motion(vec3 from, vec3 to)
{
    float dot = vec3::dot(from, to);
    if ( dot < 0 ) dot = 0;
    if ( dot > 1 ) dot = 1;
    float angle = std::acos(dot);
    if (angle > 0.02) time_since_saccadic_motion = 0.f;
    vec3 X = vec3::cross(from, vec3(0,1,0)).normalized();
    vec3 Y = vec3::cross(X, from);
    vec2 dir = vec2(vec3::dot(to, X), vec3::dot(to, Y)).normalized();
    for (FloaterSheet &sheet : sheets)
    {
        for (FloaterSheet::Motion &motion : sheet.motions)
        {
            motion.velocity += angle * sheet.impulse_multiplier * motion.impulse_modifier(motion.position, dir);
        }
    }
}

int main(int argc, char *argv[])
{
    ilInit();

    printf("[main] Creating context...\n");
    IGC::Context context("eye floaters");
    pContext = &context;
    printf("[main] Creating world...\n");
    World world(context);

    printf("[main] Creating app...\n");
    App app(world, context);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(&app);
    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
