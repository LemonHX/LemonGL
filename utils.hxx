#ifndef LEMONGL_UTILS_HXX
#define LEMONGL_UTILS_HXX

#include "geometry.hxx"
#include "shader.hxx"
#include "tga_image.hxx"

Matrix viewport(int x, int y, int w, int h);
Matrix projection(float coeff = 0.f); // coeff = -1/c
Matrix lookat(Vec3f eye, Vec3f center, Vec3f up);

void triangle(Vec4f *pts, IShader &shader, TGAImage &image, TGAImage &zbuffer);

#endif // LEMONGL_UTILS_HXX
