#include "core.h"
#include "reflector/reflector.h"
#include "data_structures/table.h"



struct Thing {
    int a;
    int b;
};
REFLECT_STRUCT(Thing);
BEGIN_ENTRIES(Thing)
    ENTRY(a)
    ENTRY(b)
END_ENTRIES()
DESCRIPTOR_INSTANCE(Thing);



int main(void)
{
    Table(Reflector::get_descriptor<Thing>());
}
