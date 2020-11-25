#include "world/graphics/image.h"

template <>
Image<vec3>::Image(int m, int n) : Image(m, n, IMAGE_RGB) {}
template <>
Image<float>::Image(int m, int n) : Image(m, n, IMAGE_GRAYSCALE) {}
