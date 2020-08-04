#include "registry/registry.h"
#include "registry/registry.serialize.cpp"

// Static initialization of the registry. Everything that depends on the registry should not be statically initialized,
// as the order of static initialization is undefined!
static Table<GenericTable> init_registry() {
    printf("[registry] Initializing registry...\n");
    Table<GenericTable> registry = Table<GenericTable>(1);
    printf("[registry] Created registry.\n");
    return registry;
}
Table<GenericTable> Registry::registry(init_registry());
