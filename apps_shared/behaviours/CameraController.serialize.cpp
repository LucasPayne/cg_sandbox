void pack(CameraController &obj, std::ostream &out) {
    pack((IBehaviour &)obj, out);
    pack(obj.azimuth, out);
    pack(obj.angle, out);
    pack(obj.strafe_speed, out);
    pack(obj.forward_speed, out);
    pack(obj.lift_speed, out);
    pack(obj.view_with_mouse, out);
    pack(obj.key_view_speed_horizontal, out);
    pack(obj.key_view_speed_vertical, out);
    pack(obj.min_angle, out);
    pack(obj.max_angle, out);
    pack(obj.mouse_sensitivity, out);
}
void unpack(std::istream &in, CameraController &obj) {
    unpack(in, (IBehaviour &)obj);
    unpack(in, obj.azimuth);
    unpack(in, obj.angle);
    unpack(in, obj.strafe_speed);
    unpack(in, obj.forward_speed);
    unpack(in, obj.lift_speed);
    unpack(in, obj.view_with_mouse);
    unpack(in, obj.key_view_speed_horizontal);
    unpack(in, obj.key_view_speed_vertical);
    unpack(in, obj.min_angle);
    unpack(in, obj.max_angle);
    unpack(in, obj.mouse_sensitivity);
}
void print(CameraController &obj) {
    std::cout << "CameraController {\n";
    std::cout << "    base IBehaviour {\n";
    print((IBehaviour &)obj);
    std::cout << "    }\n";
    std::cout << "    azimuth: ";
    print(obj.azimuth);
    std::cout << "\n";
    std::cout << "    angle: ";
    print(obj.angle);
    std::cout << "\n";
    std::cout << "    strafe_speed: ";
    print(obj.strafe_speed);
    std::cout << "\n";
    std::cout << "    forward_speed: ";
    print(obj.forward_speed);
    std::cout << "\n";
    std::cout << "    lift_speed: ";
    print(obj.lift_speed);
    std::cout << "\n";
    std::cout << "    view_with_mouse: ";
    print(obj.view_with_mouse);
    std::cout << "\n";
    std::cout << "    key_view_speed_horizontal: ";
    print(obj.key_view_speed_horizontal);
    std::cout << "\n";
    std::cout << "    key_view_speed_vertical: ";
    print(obj.key_view_speed_vertical);
    std::cout << "\n";
    std::cout << "    min_angle: ";
    print(obj.min_angle);
    std::cout << "\n";
    std::cout << "    max_angle: ";
    print(obj.max_angle);
    std::cout << "\n";
    std::cout << "    mouse_sensitivity: ";
    print(obj.mouse_sensitivity);
    std::cout << "\n";
    std::cout << "}\n";
}

