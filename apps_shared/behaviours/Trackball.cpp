
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

    void trackball_stop_dragging()
    {
        vec3 p = last_ball_point;
        vec3 pp = last_last_ball_point;
        float cos_theta = vec3::dot(p.normalized(), pp.normalized());
        if (cos_theta > 1) cos_theta = 1;
        if (cos_theta < -1) cos_theta = -1;
        const float theta_max = 2*M_PI;
        float theta = acos(cos_theta);
        if (theta > theta_max) theta = theta_max;
        vec3 axis = vec3::cross(p, pp).normalized();
        angular_velocity = (theta / (dt == 0 ? 0.01 : dt)) * axis;
        dragging = false;
    }

    void update() {
        if (vec3::dot(angular_velocity, angular_velocity) > 1.3) {
            angular_velocity = (1.0 - 2*dt) * angular_velocity;
            auto t = entity.get<Transform>();
            t->rotation = Quaternion::from_axis_angle(angular_velocity * dt) * t->rotation;
        } else {
            angular_velocity = vec3::zero();
        }
    }

    void mouse_handler(MouseEvent e) {
        vec3 pos = entity.get<Transform>()->position;

        if (dragging) {
            if (e.action == MOUSE_BUTTON_RELEASE && e.button.code == MOUSE_LEFT) {
                trackball_stop_dragging();
            } else if (e.action == MOUSE_MOVE) {
                Ray ray;
                if (world->screen_to_ray(e.cursor.x, e.cursor.y, &ray)) {
                    vec3 intersection;
                    if (ray.intersect(Sphere(pos, radius), &intersection)) {

                        vec3 ball_point = intersection - pos;

                        std::cout << intersection << "\n";
                        std::cout << ball_point << "\n";
                        std::cout << last_ball_point << "\n";

                        vec3 axis = vec3::cross(ball_point, last_ball_point).normalized();
                        float cos_theta = vec3::dot(ball_point.normalized(), last_ball_point.normalized());
                        if (cos_theta > 1) cos_theta = 1;
                        if (cos_theta < -1) cos_theta = -1;
                        float theta = acos(cos_theta);
                        std::cout << "axis: " << axis << "\n";
                        printf("angle: %.6f\n", theta);
                        // getchar();
                        entity.get<Transform>()->rotation = Quaternion::from_axis_angle(axis, theta) * entity.get<Transform>()->rotation;
	                last_last_ball_point = last_ball_point;
	                last_ball_point = ball_point;
		    }
	        }
            }
        } else {
            if (e.action == MOUSE_BUTTON_PRESS && e.button.code == MOUSE_LEFT) {
                Ray ray;
                if (world->screen_to_ray(e.cursor.x, e.cursor.y, &ray)) {
                    vec3 intersection;
                    if (ray.intersect(Sphere(pos, radius), &intersection)) {
                        last_ball_point = intersection - pos;
                        last_last_ball_point = last_ball_point;
                        dragging = true;
                        angular_velocity = vec3::zero();
                    }
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
