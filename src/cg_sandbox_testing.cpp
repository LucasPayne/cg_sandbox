/*--------------------------------------------------------------------------------
    This file is included in cg_sandbox if TESTING is enabled.
--------------------------------------------------------------------------------*/

//-Idea for syntax, somehow with overloading or function objects or something.
// add_aspect<SomeValues>(e)(2.3, ... constructor stuff);

define_aspect(Logic)
    void (*update)(Logic *);
    void *data;
end_define_aspect(Logic)

// struct ThingThatSaysHello : Logic {
//     void update() {
//         printf("hello\n");
//     }
// };

define_aspect(SomeValues)
    float x;
    int nums[16];
    bool flag;
end_define_aspect(SomeValues)

define_aspect(SomeMoreStuff)
    float x;
    int nums[23];
end_define_aspect(SomeMoreStuff)

void say_cool(Logic *logic)
{
    printf("cool\n");
}

void CGSandbox::test_init()
{
    AspectType type1 = SomeValues::type;
    AspectType type = SomeMoreStuff::type;
    printf("type: %d\n", type);
    AspectInfo info = AspectInfo::type_info(type);
    std::cout << "size: " << info.size << "\n";

    #define N 15
    Entity entities[N];

    for (int i = 0; i < N; i++) {
        Entity e = entity_model.new_entity();

        SomeValues *sv = entity_model.add_aspect<SomeValues>(e);
        sv->x = 12.31;
        SomeMoreStuff *sms = entity_model.add_aspect<SomeMoreStuff>(e);
        // entity_model.print_entity(e);

        SomeValues *_sv = entity_model.get_aspect<SomeValues>(e);
        if (frand() > 0.35) entity_model.destroy_aspect(_sv);
        printf("x: %.2f\n", _sv->x);
        entities[i] = e;
        Logic *logic = entity_model.add_aspect<Logic>(e);
        logic->update = say_cool;
        if (frand() > 0.7) entity_model.destroy_aspect(logic);
    }
    // for (int i = 0; i < N; i++) {
    //     if (frand() > 0.5) entity_model.destroy_entity(entities[i]);
    // }
    entity_model.print_entity_ids();
    entity_model.print_aspect_ids(0);
    entity_model.print_aspect_ids(1);
    entity_model.print_aspect_ids(Logic::type);
    

    // e.add<SomeValues>(1.3, 32, true);
    // e.add<SomeMoreStuff>(1.66, 12);
    // e.remove<SomeValues>();
    // Aspect a = e.add<SomeValues>(2.87, 10, false);
    // a.x = 87.13;
    // a.print();
}

void CGSandbox::test_loop()
{
    //-It is entirely possible that the entity model is interacted with during iteration.

    // {
    //     Logic *logic = (Logic *) &entity_model.aspect_lists[Logic::type][0];
    //     //-There is a lot wrong with this iteration logic, but I think nothing bad will happen yet ...
    //     for (int i = 0; i < entity_model.aspect_lists[Logic::type].size() / AspectInfo::type_info(Logic::type).size; i++) {
    //         if (logic->id != 0) {
    //             logic->update(logic);
    //         }
    //         logic ++;
    //     }
    // }

    for (auto &logic : entity_model.aspects<Logic>()) {
        printf("updating\n");
        logic.update(&logic);
    }

    // for_aspect(Logic, logic)
    //     
    // end_for_aspect()
    // Run loop testing/debugging code, if there is any.
}
