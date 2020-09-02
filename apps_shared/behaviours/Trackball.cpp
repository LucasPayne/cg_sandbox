
struct Trackball : public IBehaviour {
    bool dragging;
    float radius;

    vec3 last_ball_point;
    vec3 last_last_ball_point;
    vec3 angular_velocity;

    void init() {
        radius = 0.5;
        dragging = false;
        angular_velocity = vec3::zero();
    }

    void trackball_stop_dragging() {

    }

    void mouse_handler(MouseEvent e) {
        if (dragging) {
            if (e.action == MOUSE_BUTTON_RELEASE && e.button.code == MOUSE_LEFT) {
                trackball_stop_dragging();
            }
        } else {
            if (e.action == MOUSE_BUTTON_PRESS && e.button.code == MOUSE_LEFT) {
                Ray ray;
                if (world->screen_to_ray(e.cursor.x, e.cursor.y, &ray)) {
                    vec3 intersection;
                    vec3 pos = entity.get<Transform>()->position;
                    if (ray.intersect(Sphere(pos, radius), &intersection)) {
                        last_ball_point = intersection - pos;
                        last_last_ball_point = last_ball_point;
                        // dragging = true;
                        angular_velocity = vec3::zero();
                        printf("Hit ball\n");
                    }
                    printf("Cast a ray.\n");
                    std::cout << ray << "\n";
                    getchar();
                }
            }
        }
    }
};

REFLECT_STRUCT(Trackball)
BEGIN_ENTRIES(Trackball)
    // Base IBehaviour
    ENTRY(world)
    ENTRY(entity)
END_ENTRIES()
DESCRIPTOR_INSTANCE(Trackball);
