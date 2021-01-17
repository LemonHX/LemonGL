#ifndef LEMONGL_MODEL_HXX
#define LEMONGL_MODEL_HXX

#include "geometry.hxx"
#include "texture.hxx"
#include "tga_image.hxx"
#include <string>
#include <vector>

class Model {
  private:
    std::vector<Vec3f> verts;
    // Vec3i means vertex/uv/normal
    std::vector<std::vector<Vec3i>> faces;
    std::vector<Vec3f> norms;
    std::vector<Vec2f> uvs;

  public:
    std::vector<Texture> textures;
    explicit Model(const char *filename);
    ~Model();
    int nverts();
    int nfaces();
    Vec3f vert(int i);
    Vec3f vert(int iface, int vert);
    Vec2f uv(int iface, int vert);
    std::vector<int> face(int idx);
    Texture &getTexture(int idx);
};

#endif // LEMONGL_MODEL_HXX
