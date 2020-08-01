#include "core.h"
#include "serialization/serialization.h"

void print_type_tree(TypeTree &tree)
{
    #define YESNO(BOOLEAN) (( BOOLEAN ) ? "Yes" : "No")
    printf("TypeTree {\n");
    for (TypeEntry entry : tree) {
        printf("    %s, %zu, Struct: %s\n", entry.type_functions->name(), entry.type_functions->size(), YESNO(entry.is_struct));
    }
    printf("}\n");
}
