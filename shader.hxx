#ifndef LEMONGL_SHADER_HXX
#define LEMONGL_SHADER_HXX

#include "geometry.hxx"
#include "tga_image.hxx"
#include <map>

class IShader {
  public:
    virtual Vec4f vertex_shader(int iface, int nvert) = 0;
    virtual bool fragment_shader(Vec3f bar, TGAColor &color) = 0;
    virtual ~IShader() = default;
};

#endif // LEMONGL_SHADER_HXX
