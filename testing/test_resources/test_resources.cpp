#include "core.h"
#include "reflector/reflector.h"
#include "data_structures/table.h"
#include "world/resources/resources.h"
#include "world/entities/entities.h"


// Test packing/unpacking by writing an object to disk and reading it back.
template <typename T>
T transporter(T &obj)
{
    printf("Packing...\n");
    {
    std::ofstream file;
    file.open("transporter_tempfile.binary", std::ios::trunc | std::ios::out | std::ios::binary);
    Reflector::pack(obj, file);
    file.close();
    }


    printf("Unpacking...\n");
    std::ifstream file;
    T transportered_obj;
    file.open("transporter_tempfile.binary", std::ios::in | std::ios::binary);
    Reflector::unpack(file, transportered_obj);
    file.close();

    return transportered_obj;
}



struct Thing : IAspectType {
    int a;
    int b;
    Thing() {}
    Thing(int _a, int _b) :
        a{_a}, b{_b}
    {}
};
REFLECT_STRUCT(Thing);
BEGIN_ENTRIES(Thing)
    ENTRY(a)
    ENTRY(b)
END_ENTRIES()
DESCRIPTOR_INSTANCE(Thing);

struct OtherThing : IAspectType {
    Thing t;
    Thing k;
    OtherThing() {}
    OtherThing(Thing _t, Thing _k) :
        t{_t}, k{_k}
    {}
};
REFLECT_STRUCT(OtherThing);
BEGIN_ENTRIES(OtherThing)
    ENTRY(t)
    ENTRY(k)
END_ENTRIES()
DESCRIPTOR_INSTANCE(OtherThing);



int main(void)
{
    Table table(Reflector::get_descriptor<Thing>());
    for (int i = 0; i < 3; i++) {
        auto e = table.add();
        ((Thing *) table[e])->a = i+1;
        ((Thing *) table[e])->b = i*3+1;
    }
    Reflector::printl(table);

    auto table_t = transporter(table);
    Reflector::printl(table_t);


    Resources resources;
    resources.register_resource_type<Thing>();
    resources.register_resource_type<OtherThing>();

    for (int i = 0; i < 4; i++) {
        auto a = resources.add<Thing>();
        a->a = i*30 + 123;
        a->b = i*i + 100;
        Reflector::printl(*a);
        auto b = resources.add<Thing>();
        b->a = i*i*i;
        b->b = i+1;
        Reflector::printl(*b);

        auto c = resources.add<OtherThing>();
        c->t = *a;
        c->k = *b;
        Reflector::printl(*c);
    }

    printf("--------------------------------------------------------------------------------\n");
    Reflector::printl(resources);
    auto resources_t = transporter(resources);
    printf("--------------------------------------------------------------------------------\n");
    Reflector::printl(resources_t);

    Entities entities;
    entities.register_aspect_type<Thing>();
    entities.register_aspect_type<OtherThing>();
    for (int i = 0; i < 10; i++) {
        auto e = entities.add();
        auto t = e.add<Thing>(i, i+1);
        auto k = e.add<Thing>(2*i, 2*i+1);
        auto o = e.add<OtherThing>(*t, *k);
        for (auto aspect : e) {
            // std::cout << aspect.type()->name() << "\n";
            aspect.type()->print(*aspect.get_data());
            std::cout << "\n";
        }
        std::cout << "Sibling OtherThing:\n";
        auto sib = t.sibling<OtherThing>();
        sib.type()->print((uint8_t &)*sib);
        getchar();
    }
    Reflector::printl(entities);
    auto entities_t = transporter(entities);
    printf("-TRANSPORTING-------------------------------------------------------------------\n");
    getchar();
    Reflector::printl(entities_t);
}
