#include "src/primitives.hpp"

static bool g_initialized_default_textures = false;
static Texture *g_default_diffuse_texture = NULL;
static Texture *g_default_specular_texture = NULL;
static void initialize_default_textures()
{
    g_default_diffuse_texture = new ConstantTextureRGB(RGB(1,1,1));
    g_default_specular_texture = new ConstantTextureFloat(0);
}
GeometricPrimitive::GeometricPrimitive(Shape *_shape,
	                               Texture *_diffuse_texture,
	                               Texture *_specular_texture,
                                       float _reflectiveness,
                                       float _refractive_index,
                                       float _refraction_amount)
{
    shape = _shape;
    if (_diffuse_texture == NULL) {
        if (!g_initialized_default_textures) initialize_default_textures();
        diffuse_texture = g_default_diffuse_texture;
    } else {
        diffuse_texture = _diffuse_texture;
    }
    if (_specular_texture == NULL) {
        if (!g_initialized_default_textures) initialize_default_textures();
        specular_texture = g_default_specular_texture;
    } else {
        specular_texture = _specular_texture;
    }
    reflectiveness = _reflectiveness;
    refractive_index = _refractive_index;
    refraction_amount = _refraction_amount;
}

bool Primitive::intersect(Ray &ray, Intersection *inter) {
    std::cerr << "ERROR: Unimplemented intersect() routine of primitive called.\n";
    exit(EXIT_FAILURE);
}
bool Aggregate::intersect(Ray &ray, Intersection *inter) {
    std::cerr << "ERROR: Unimplemented intersect() routine of aggregate called.\n";
    exit(EXIT_FAILURE);
}
bool Primitive::does_intersect(Ray &ray) {
    std::cerr << "ERROR: Unimplemented does_intersect() routine of primitive called.\n";
    exit(EXIT_FAILURE);
}
bool Aggregate::does_intersect(Ray &ray) {
    std::cerr << "ERROR: Unimplemented does_intersect() routine of aggregate called.\n";
    exit(EXIT_FAILURE);
}
