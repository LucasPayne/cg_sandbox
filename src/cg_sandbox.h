/*--------------------------------------------------------------------------------
Declarations and interface for the CGSandbox class.
--------------------------------------------------------------------------------*/
#ifndef CG_SANDBOX_H
#define CG_SANDBOX_H
#include "core.h"
#include "resource_model/resource_model.h"
#include "entity_model/entity_model.h"

class CGSandbox : public Looper, public InputListener {
public:
    CGSandbox() {}

    // Looper stuff.
    void init();
    void close();
    void loop();
    // InputListener stuff.
    void key_callback(int key, int action);
    void cursor_position_callback(double x, double y);
    void cursor_move_callback(double x, double y);
    void mouse_button_callback(int button, int action);

    // Testing and debugging.
    void test_init();
    void test_loop();
private:
    EntityModel entity_model;
    ResourceModel resource_model;
};

#endif // CG_SANDBOX_H
