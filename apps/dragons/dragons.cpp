#include "cg_sandbox.h"
#include "gl/gl.h"
#include "data_structures/table.h"
#include "registry/registry.h"

#include "behaviours/CameraController.h"
#include "utils/force_aspect_ratio.cpp"
#include "utils/check_quit_key.cpp"


// Table serialization functions.
// These are not auto-generated since a table is a container which needs its own custom serialization.
template <typename T>
void pack(Table<T> &obj, std::ostream &out) {
    // length : uint32_t
    // next ID : TableEntryID
    // computed first_free_index : uint32_t
    // number of active entries : uint32_t
    // for each active entry:
    //    entry index : uint32_t
    //    entry ID : TableEntryID
    //    entry object : T

    // Pack the metadata first.
    // Recomputing the first free index, since the free list will be different on reconstruction.
    pack(obj.m_table.m_length, out);
    pack(obj.m_table.m_next_id, out);

    // Pack the first free index, which is recomputed to be the least such index, so that a free list can be constructed
    // on unpack.
    uint32_t first_free_index; // A table always has at least one free slot, so find the free slot with least index.
    for (int i = 0; i < obj.m_table.m_length; i++) {
        if (obj.m_table.get_header(i)->id == 0) {
            first_free_index = i;
            break;
        }
    }
    pack(first_free_index, out);

    // Pack the number of active entries in the table, since the unpacker will need to know when to stop.
    uint32_t num_active_entries = 0;
    {
        GenericTable::Iterator iter = obj.iterator();
        for (TableHandle handle : iter) {
            num_active_entries++;
        }
        pack(num_active_entries, out);
    }

    // Densely pack the entries.
    GenericTable::Iterator iter = obj.iterator();
    for (TableHandle handle : iter) {
        // pack index, id, object entry

        // For each entry, store its index, so this can be unpacked into the sparse array.
        pack(handle.index, out);

        // Pack the entry ID.
        pack(handle.id, out);

        // Pack the actual entry object.
        T *entry_pointer = obj.lookup(handle);
        pack(*entry_pointer, out);
    }
}
template <typename T>
void unpack(std::istream &in, Table<T> &obj) {
    // length : uint32_t
    // next ID : TableEntryID
    // computed first_free_index : uint32_t
    // number of active entries : uint32_t
    // for each active entry:
    //    entry index : uint32_t
    //    entry ID : TableEntryID
    //    entry object : T

    uint32_t table_length;
    unpack(in, table_length);
    obj = Table<T>(table_length);

    unpack(in, obj.m_table.m_next_id);
    unpack(in, obj.m_table.m_first_free_index);

    uint32_t num_active_entries;
    unpack(in, num_active_entries);
    for (int i = 0; i < num_active_entries; i++) {
        TableHandle handle;
        unpack(in, handle.index);
        unpack(in, handle.id);
        // Set the ID in the header of this slot to flag that this slot is active.
        GenericTable::Header *header = obj.m_table.get_header(handle.index);
        header->id = handle.id;
        // Unpack the object.
        T *entry_pointer = obj.lookup(handle);
        unpack(in, *entry_pointer);
    }
    
    // Construct the free list.
    uint32_t connecting_index = obj.m_table.m_first_free_index;
    for (uint32_t i = connecting_index+1; i < obj.m_table.m_length; i++) {
        if (obj.m_table.get_header(i)->id == 0) {
            // Connect the free list to this index.
            obj.m_table.get_header(connecting_index)->next_free_index = i;
            // Proceed to connect this index further into the free list.
            connecting_index = i;
        }
    }
    obj.m_table.get_header(connecting_index)->next_free_index = 0; // Signify that this empty slot is at the end of the free list.
}


// Table serialization functions.
// These are not auto-generated since a table is a container which needs its own custom serialization.
// template <typename T>
// void pack(Table<T> &obj, std::ostream &out) {
//     const bool debug = true;
//     if (debug) { printf("PACK\n"); }
//     // Pack the metadata first.
//     if (debug){ printf("%u\n", obj.m_table.m_first_free_index);getchar();}
//     pack(obj.m_table.m_first_free_index, out);
//     if (debug){ printf("%u\n", obj.m_table.m_length);getchar();}
// 
//     pack(obj.m_table.m_length, out);
//     if (debug){ printf("%u\n", obj.m_table.m_next_id);getchar();}
//     pack(obj.m_table.m_next_id, out);
// 
//     // Pack the number of active entries in the table, since the unpacker will need to know when to stop.
//     int num_entries = 0;
//     {
//         GenericTable::Iterator iter = obj.iterator();
//         for (TableHandle handle : iter) {
//             num_entries++;
//         }
//         pack(num_entries, out);
//     }
//     if (debug){ printf("num_entries: %d\n", num_entries);getchar();}
// 
//     // Densely pack the entries.
//     GenericTable::Iterator iter = obj.iterator();
//     for (TableHandle handle : iter) {
//         // pack index, id, next_free_index, object entry
// 
//         if (debug){ printf("Packing entry\n");}
//         // For each entry, store its index, so this can be unpacked into the sparse array.
//         if (debug){ printf("index: %u\n", handle.index);getchar();}
//         pack(handle.index, out);
//         // Pack the entry header metadata, which is needed for the table to make sense.
//         TableEntryID id = obj.m_table.get_header(handle.index)->id;
//         if (debug){ printf("id: %u\n", id);getchar();}
//         pack(id, out);
//         // Pack the actual entry object.
//         T *entry_pointer = obj.lookup(handle);
//         if (entry_pointer == nullptr) {
//             printf("WHAT!\n");getchar();
//         }
//         pack(*entry_pointer, out);
//     }
// }
// template <typename T>
// void unpack(std::istream &in, Table<T> &obj) {
//     const bool debug = true;
//     if (debug) { printf("UNPACK\n"); }
//     // Unpack the metadata.
//     unpack(in, obj.m_table.m_first_free_index);
//     if (debug){ printf("%u\n", obj.m_table.m_first_free_index);getchar();}
//     unpack(in, obj.m_table.m_length);
//     if (debug){ printf("%u\n", obj.m_table.m_length);getchar();}
//     unpack(in, obj.m_table.m_next_id);
//     if (debug){ printf("%u\n", obj.m_table.m_next_id);getchar();}
//     obj.m_table.m_entry_size = sizeof(T); // This didn't need to be packed, since it is known here.
//     
//     // Retrieve the number of active entries in the table.
//     int num_entries;
//     unpack(in, num_entries);
//     if (debug){ printf("num_entries: %d\n", num_entries);getchar();}
//     // Prepare the table buffer.
//     obj.m_table.m_buffer = std::vector<uint8_t>(sizeof(T) * obj.m_table.m_length);
//         //note: It is required for this to be zero-initialized, so that unused table IDs are null.
//     // Unpack the densely packed entries into the sparse table.
//     for (int i = 0; i < num_entries; i++) {
//         // unpack index, id, object entry
// 
//         if (debug){ printf("Unpacking entry\n");}
//         // Retrieve the index of this entry.
//         uint32_t index;
//         unpack(in, index);
//         if (debug){ printf("index: %u\n", index);getchar();}
//         // Unpack the entry header metadata at this index.
//         TableEntryID id;
//         unpack(in, id);
//         if (debug){ printf("id: %u\n", id);getchar();}
//         obj.m_table.get_header(index)->id = id;
//         // Unpack the entry at this index.
//         // The lookup works since the header metadata has been set up.
//         TableHandle handle;
//         handle.index = index;
//         handle.id = obj.m_table.get_header(index)->id;
//         T *entry_pointer = obj.lookup(handle);
//         if (entry_pointer == nullptr) {
//             printf("WHAT!\n");getchar();
//         }
//         unpack(in, *entry_pointer);
//     }
// }
template <typename T>
void print(Table<T> &obj) {
    std::cout << "Table<T> {\n";
    std::cout << "    m_first_free_index: " << obj.m_table.m_first_free_index << "\n";
    std::cout << "    m_length: " << obj.m_table.m_length << "\n";
    std::cout << "    m_next_id: " << obj.m_table.m_next_id << "\n";
    std::cout << "    table: [\n";
    GenericTable::Iterator iter = obj.iterator();
    for (TableHandle handle : iter) {
        std::cout << "        ";
        print(*obj.lookup(handle));
        std::cout << "\n";
    }
    std::cout << "    ]\n";
    std::cout << "}\n";
}



// Transporter for testing serialization.
template <typename T>
T transporter(T &obj) {
    std::ofstream outfile;
    outfile.open("test.binary", std::ios::trunc);
    pack(obj, outfile);
    outfile.close();
    
    std::ifstream infile;
    T transportered_obj;
    infile.open("test.binary");
    unpack(infile, transportered_obj);
    infile.close();
    return transportered_obj;
}
template <typename T>
void transporter_test(T &obj) {
    printf("Testing transporter...\n");
    printf("--------------------------------------------------------------------------------\n");
    printf(" PRE-TRANSPORTED\n");
    printf("--------------------------------------------------------------------------------\n");
    print(obj);
    T obj_t = transporter(obj);
    printf("--------------------------------------------------------------------------------\n");
    printf(" TRANSPORTED\n");
    printf("--------------------------------------------------------------------------------\n");
    print(obj_t);
    getchar();
}

struct Dolphin : public IBehaviour {
    vec3 velocity;
    void update() {
        Transform *t = world->em.get_aspect<Transform>(entity);
        if (world->input.keyboard.down(KEY_DOWN_ARROW)) t->position.y() -= dt;
        if (world->input.keyboard.down(KEY_UP_ARROW)) t->position.y() += dt;
        if (world->input.keyboard.down(KEY_LEFT_ARROW)) t->position.x() -= dt;
        if (world->input.keyboard.down(KEY_RIGHT_ARROW)) t->position.x() += dt;
    }
};
struct Bunny : public IBehaviour {
    void update() {
        Transform *t = world->em.get_aspect<Transform>(entity);
        t->rotation = Quaternion::from_axis_angle(total_time * vec3(1,0,0));
    }
};

class App : public IGC::Callbacks {
public:
    World &world;
    App(World &world);

    void close();
    void loop();
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    void window_handler(WindowEvent e);
};
App::App(World &_world) : world{_world}
{
    // Create a camera man.
#if 1
    {
        Entity cameraman = world.em.new_entity();
        Camera *camera = world.em.add_aspect<Camera>(cameraman);
        camera->init_projective(0.1, 300, 0.1, 0.566);

        Transform *t = world.em.add_aspect<Transform>(cameraman);
        //-test serialization
        t->init(vec3(2,1,8.3232), Quaternion(1,2,3,-4.5));
        // print(*t);getchar();
        transporter_test(*t);

        t->init(0,0,0);

        CameraController *controller = world.add_behaviour<CameraController>(cameraman);
        controller->init();
    }


#endif 

    // Create a dolphin.

    // Resource<GeometricMaterial> gmat = assets.GeometricMaterial("resources/model_test/model_test.gmat");
    // Resource<Material> gmat = assets.Material("resources/model_test/model_test.mat");
    // Resource<ShadingModel> gmat = assets.ShadingModel("resources/model_test/model_test.sm");

    Resource<GeometricMaterial> gmat = world.assets.shading.load_geometric_material("resources/model_test/model_test.gmat");
    Resource<Material> mat = world.assets.shading.load_material("resources/model_test/model_test.mat");
#if 1
{
    for (int i = 0; i < 25; i++) {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/dragon.off");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        vec3 base(3,3,0);
        t->init(base + vec3(2*(frand()-0.5),2*(frand()-0.5),-2));
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);

        Dolphin *b = world.add_behaviour<Dolphin>(dolphin);
        b->velocity = vec3::random(-0.1,0.1);
    }
}
#endif
#if 1
    {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/large/nefertiti.obj");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(0,0,-3);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
    }
#endif
#if 1
    {
        Resource<VertexArray> dolphin_model = world.assets.models.load("resources/models/large/buddha.obj");
        Entity dolphin = world.em.new_entity();
        Transform *t = world.em.add_aspect<Transform>(dolphin);
        t->init(1,0,-3);
        Drawable *drawable = world.em.add_aspect<Drawable>(dolphin);
        drawable->geometric_material = GeometricMaterialInstance(gmat, dolphin_model);
        drawable->material = MaterialInstance(mat);
        drawable->material.properties.set_vec4("diffuse", frand(),frand(),frand(),1);
        Bunny *b = world.add_behaviour<Bunny>(dolphin);
    }
#endif

    // transporter_test(world.em.m_entity_table);

    // Teleport the entity table out to disk and read it back.
    world.em.m_entity_table = transporter(world.em.m_entity_table);
}
void App::close()
{
    printf("see ya\n");
}
void App::loop()
{
    for (Transform *t : world.em.aspects<Transform>()) {
        if (t->position == vec3(0,0,-3)) continue;
        // t->lookat(vec3(0,0,-3));
        t->rotation = Quaternion::from_axis_angle(t->position.x()*0.2*t->position.y()*sin(total_time*0.2)*vec3(total_time, total_time, 0));
    }
    /* for (Dolphin *dolphin : world.behaviours<Dolphin>()) { */
    /*     Transform *t = world.em.get_aspect<Transform>(dolphin->entity); */
    /*     t->position += dolphin->velocity * dt; */
    /* } */
}

void App::window_handler(WindowEvent e)
{
    force_aspect_ratio(e);
}
void App::keyboard_handler(KeyboardEvent e)
{
    check_quit_key(e, KEY_Q);
}
void App::mouse_handler(MouseEvent e)
{
}

int main(int argc, char *argv[])
{
    printf("[main] Creating context...\n");
    IGC::Context context("Dragons");
    printf("[main] Creating world...\n");
    Reference<World> world = World::new_world();
    printf("[main] Adding world callbacks...\n");
    context.add_callbacks(*world);
    context.add_callbacks(world->input);

    printf("[main] Creating app...\n");
    App app(*world);
    printf("[main] Adding app callbacks...\n");
    context.add_callbacks(app);

    printf("[main] Entering loop...\n");
    context.enter_loop();
    context.close();
}
