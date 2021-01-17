//
// Created by LemonHX on 2020/9/3.
//

#ifndef LEMONGL_TEXTURE_HXX
#define LEMONGL_TEXTURE_HXX

#include "geometry.hxx"
#include "tga_image.hxx"

class Texture {
  protected:
    TGAImage image;

  public:
    Texture(const std::string &filename);
    virtual ~Texture() = default;
};

class DiffuseMap : public Texture {
  public:
    TGAColor getValue(Vec2f uv);
    ~DiffuseMap() override = default;
};

class NormalMap : public Texture {
  public:
    Vec3f getValue(Vec2f uvf);
    ~NormalMap() override = default;
};

class SpecMap : public Texture {
  public:
    float getValue(Vec2f uvf);
    ~SpecMap() override = default;
};
#endif // LEMONGL_TEXTURE_HXX
