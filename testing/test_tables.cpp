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

typedef TypedTableHandle Asset;

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

    std::vector<Asset> added_assets(0);

    TableCollection assets;
    assets.add_type<Stuff>("Stuff");
    assets.add_type<OtherStuff>("OtherStuff");
    for (int i = 0; i < 10; i++) {
        {
            Asset a = assets.add<Stuff>();
            printf("Adding Stuff\n");
            Stuff *stuff = assets.lookup<Stuff>(a);
            stuff->num = ((i + 1)*13)%7;
            printf("    storing num=%d\n", stuff->num);
            if (frand() > 0.5) {
                printf("    REMOVED\n");
                assets.remove(a);
            }
            printf("    Lookup:\n");
            stuff = assets.lookup<Stuff>(a);
            if (stuff == nullptr) printf("    GONE\n");
            else printf("    FOUND, num=%d\n", stuff->num);
            added_assets.push_back(a);
        }
        {
            Asset a = assets.add<OtherStuff>();
            printf("Adding OtherStuff\n");
            OtherStuff *stuff = assets.lookup<OtherStuff>(a);
            stuff->longs[1] = ((i + 1)*13)%7;
            printf("    storing longs[1]=%lu\n", stuff->longs[1]);
            if (frand() > 0.5) {
                printf("    REMOVED\n");
                assets.remove(a);
            }
            printf("    Lookup:\n");
            stuff = assets.lookup<OtherStuff>(a);
            if (stuff == nullptr) printf("    GONE\n");
            else printf("    FOUND, longs[1]=%lu\n", stuff->longs[1]);
            added_assets.push_back(a);
        }
    }
    for (Asset a : added_assets) {
        printf("Removing ...\n");
        assets.remove(a);
    }
}
