#include "core.h"
#include "data_structures/table.h"

struct ThingHandle : public GenericTableHandle {};
struct Thing {
    int a;
    char b[8];
    int c;
};

struct Stuff {
    static TableCollectionType type_id;
    Thing thing;
    int num;
    uint16_t shorts[20];
};
TableCollectionType Stuff::type_id = 0;

struct OtherStuff {
    static TableCollectionType type_id;
    int num;
    uint64_t longs[3];
};
TableCollectionType OtherStuff::type_id = 0;

int main(void)
{
    printf("hello, world\n");
    Table<Thing, ThingHandle> table(1);
    for (int i = 0; i < 10; i++) {
        ThingHandle h = table.add();
        printf("%u : %u\n", h.index, h.id);
        if (frand() > 0.5) {
            printf("removing\n");
            table.remove(h);
        }
        if (frand() > 0.5) {
            printf("lookup\n");
            Thing *t = table.lookup(h);
            if (t == nullptr) printf("GONE\n");
            else {
                printf("Found\n");
                int n = (i*i)%7;
                printf("    Storing %d\n", n);
                t->a = n;
                t = table.lookup(h);
                printf("    Lookup %d\n", t->a);
            }
        }
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("table collections\n");
    printf("--------------------------------------------------------------------------------\n");

    TableCollection collection;
    collection.add_type<Stuff>("Stuff");
    collection.add_type<OtherStuff>("OtherStuff");
}
