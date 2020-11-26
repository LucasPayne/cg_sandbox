#include "mathematics/mathematics.h"
#include "graphics_resources/graphics_resources.h"


typedef uint8_t ImageType;
#define IMAGE_RGB 0
#define IMAGE_GRAYSCALE 1

template <typename T>
class Image {
public:
    Image(int m, int n);
    Image(int m, int n, ImageType image_type);
    Image() {}

    inline T &operator()(int i, int j) {
        if (i < 0 || i >= _height || j < 0 || j >= _width) return dummy;
        dirty = true;
        return pixels[i*_width + j];
    }
    inline T operator()(int i, int j) const {
        return pixels[i*_width + j];
    }
    GLuint texture();

    inline int width() const { return _width; }
    inline int height() const { return _height; }

private:
    int _height;
    int _width;
    ImageType _image_type;
    GLuint _texture;
    std::vector<T> pixels;
    bool dirty;
    T dummy; // Out of bounds pixel writes write to this.
};




template <typename T>
Image<T>::Image(int m, int n, ImageType image_type) :
    _height{m}, _width{n}, _image_type{image_type}, dirty{true}
{
    pixels = std::vector<T>(_height * _width);
    
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    if (_image_type == IMAGE_RGB) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _width, _height, 0, GL_RGBA, GL_FLOAT, (void *) &pixels[0]);
    } else if (_image_type == IMAGE_GRAYSCALE) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _width, _height, 0, GL_RED, GL_FLOAT, (void *) &pixels[0]);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}


template <typename T>
GLuint Image<T>::texture()
{
    // if (!dirty) return _texture; //----
    if (_image_type == IMAGE_RGB) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _width, _height, 0, GL_RGBA, GL_FLOAT, (void *) &pixels[0]);
    } else if (_image_type == IMAGE_GRAYSCALE) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _width, _height, 0, GL_RED, GL_FLOAT, (void *) &pixels[0]);
    }
    dirty = false;
    return _texture;
}
