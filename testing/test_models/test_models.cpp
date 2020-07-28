#include "core.h"
#include "assets/models/models.h"

void test_load(std::string path)
{
    Model model = Model::load(path);
    model.print();
}

int main(void)
{
    std::cout << "i'm in\n";

    test_load("../../resources/models/dragon.off");
    test_load("../../resources/models/bunny.off");
    test_load("../../resources/models/dolphins.off");
    test_load("../../resources/models/icosahedron.off");
}
