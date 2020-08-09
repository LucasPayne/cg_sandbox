void pack(GeometricMaterial &obj, std::ostream &out);
void unpack(std::istream &in, GeometricMaterial &obj);
void print(GeometricMaterial &obj);
void pack(Material &obj, std::ostream &out);
void unpack(std::istream &in, Material &obj);
void print(Material &obj);
void pack(ShadingModel &obj, std::ostream &out);
void unpack(std::istream &in, ShadingModel &obj);
void print(ShadingModel &obj);
void pack(ShadingProgram &obj, std::ostream &out);
void unpack(std::istream &in, ShadingProgram &obj);
void print(ShadingProgram &obj);

