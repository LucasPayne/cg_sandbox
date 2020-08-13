#include "core.h"
#include "reflector/reflector.h"
#include "data_structures/table.h"


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
    Table table(Reflector::get_descriptor<Thing>());
    for (int i = 0; i < 3; i++) {
        TableElement e = table.add();
        ((Thing *) table[e])->a = i+1;
        ((Thing *) table[e])->b = i*3+1;
    }
    Reflector::printl(table);

    auto table_t = transporter(table);
    Reflector::printl(table_t);
}
