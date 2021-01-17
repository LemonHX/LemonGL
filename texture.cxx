#include "texture.hxx"

Texture::Texture(const std::string &filename) {
    std::cerr << "texture file " << filename << " loading "
              << (image.read_tga_file(filename.c_str()) ? "ok" : "failed")
              << std::endl;
    image.flip_vertically();
}

TGAColor DiffuseMap::getValue(Vec2f uv) {
    Vec2i uvf(uv[0] * image.get_width(), uv[1] * image.get_height());
    return image.get(uvf[0], uvf[1]);
}

Vec3f NormalMap::getValue(Vec2f uvf) {
    Vec2i uv(uvf[0] * image.get_width(), uvf[1] * image.get_height());
    TGAColor c = image.get(uv[0], uv[1]);
    Vec3f res;
    for (int i = 0; i < 3; i++)
        res[2 - i] = (float)c[i] / 255.f * 2.f - 1.f;
    return res;
}

float SpecMap::getValue(Vec2f uvf) {
    Vec2i uv(uvf[0] * image.get_width(), uvf[1] * image.get_height());
    return image.get(uv[0], uv[1])[0] / 1.f;
}
