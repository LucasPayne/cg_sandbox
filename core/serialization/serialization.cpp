#include "core.h"
#include "serialization/serialization.h"

void print_type_tree(TypeTree &tree)
{
    for (TypeEntry entry : tree) {
        printf("%s, %zu\n", entry.type_info->name(), entry.type_info->size());
    }
}
