
struct Trackball : public IBehaviour {
    float radius;

    vec3 last_ball_point;
    vec3 last_last_ball_point;
    vec3 angular_velocity;

    Quaternion snap_to_default_start; // The orientation when the state was changed to SnappingToDefault.
    float snap_to_default_timer;

    int mode;
    enum Mode {
        Free,
        Dragging,
        SnappingToDefault
    };

    void init() {
        radius = 0.5;
        angular_velocity = vec3::zero();
        mode = Free;
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
    }

    void update() {
        if (mode == Free) {
            if (vec3::dot(angular_velocity, angular_velocity) > 1.3) {
                angular_velocity = (1.0 - 2*dt) * angular_velocity;
                auto t = entity.get<Transform>();
                t->rotation = Quaternion::from_axis_angle(angular_velocity * dt) * t->rotation;
            } else {
                angular_velocity = vec3::zero();
            }
        } else if (mode == SnappingToDefault) {
            auto t = entity.get<Transform>();
            const float time_to_snap_to_default = 0.3;

            if (snap_to_default_timer >= time_to_snap_to_default) {
                t->rotation = Quaternion::identity();
                mode = Free;
                angular_velocity = vec3::zero();
            } else {
                // Lerp approximation to slerp.
                t->rotation = Quaternion::lerp(snap_to_default_start, Quaternion::identity(), snap_to_default_timer / time_to_snap_to_default).normalized();
                snap_to_default_timer += dt;
            }
        }
    }

    void mouse_handler(MouseEvent e) {
        vec3 pos = entity.get<Transform>()->position;

        if (mode == Dragging) {
            if (e.action == MOUSE_BUTTON_RELEASE && e.button.code == MOUSE_LEFT) {
                trackball_stop_dragging();
                mode = Free;
            } else if (e.action == MOUSE_MOVE) {
                Ray ray;
                if (world->screen_to_ray(e.cursor.x, e.cursor.y, &ray)) {
                    vec3 intersection;
                    if (ray.intersect(Sphere(pos, radius), &intersection)) {

                        vec3 ball_point = intersection - pos;
                        vec3 axis = vec3::cross(ball_point, last_ball_point).normalized();
                        float cos_theta = vec3::dot(ball_point.normalized(), last_ball_point.normalized());
                        if (cos_theta > 1) cos_theta = 1;
                        if (cos_theta < -1) cos_theta = -1;
                        float theta = acos(cos_theta);
                        entity.get<Transform>()->rotation = Quaternion::from_axis_angle(axis, theta) * entity.get<Transform>()->rotation;
	                last_last_ball_point = last_ball_point;
	                last_ball_point = ball_point;
		    }
	        }
            }
        } else if (mode == Free || mode == SnappingToDefault) { // SnappingToDefault can be interrupted to start dragging again.
            if (e.action == MOUSE_BUTTON_PRESS) {
                Ray ray;
                if (world->screen_to_ray(e.cursor.x, e.cursor.y, &ray)) {
                    vec3 intersection;
                    if (ray.intersect(Sphere(pos, radius), &intersection)) {
                        if (e.button.code == MOUSE_LEFT) {
                            last_ball_point = intersection - pos;
                            last_last_ball_point = last_ball_point;
                            mode = Dragging;
                            angular_velocity = vec3::zero();
                        } else if (e.button.code == MOUSE_MIDDLE) {
                            mode = SnappingToDefault;
                            snap_to_default_timer = 0;
                            // Quaternion double-cover means that its possible for the journey back to the identity to be longer than needed,
                            // so use the closest rotation representative.
                            snap_to_default_start = entity.get<Transform>()->rotation.to_hemisphere(Quaternion::identity());
                        }
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
