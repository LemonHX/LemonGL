#include "model.hxx"
#include "shader.hxx"
#include "utils.hxx"
#include <iostream>
struct Shader : public virtual IShader {
    Model &model;
    Matrix ModelView;
    Matrix Viewport;
    Matrix Projection;
    Vec3f light_dir;
    mat<2, 3, float> vuv;
    Shader(Model &model, const Matrix &modelView, const Matrix &viewport,
           const Matrix &projection, const Vec3f &lightDir)
        : model(model), ModelView(modelView), Viewport(viewport),
          Projection(projection), light_dir(lightDir) {}
    ~Shader() override = default;
    Vec4f vertex_shader(int iface, int nthvert) override {
        vuv.set_col(nthvert, model.uv(iface, nthvert));
        Vec4f gl_Vertex = embed<4>(
            model.vert(iface, nthvert)); // read the vertex from .obj file
        return Viewport * Projection * ModelView *
               gl_Vertex; // transform it to screen coordinates
    }
    bool fragment_shader(Vec3f bar, TGAColor &color) override {
        auto proj_model_view = Projection * ModelView;
        DiffuseMap &diffuse_map =
            static_cast<DiffuseMap &>(model.getTexture(0));
        NormalMap &normal_map = static_cast<NormalMap &>(model.getTexture(1));
        SpecMap &spec_map = static_cast<SpecMap &>(model.getTexture(2));

        Vec2f uv = vuv * bar;
        Vec3f n = proj<3>(proj_model_view.invert_transpose() *
                          embed<4>(normal_map.getValue(uv)))
                      .normalize();
        Vec3f l = proj<3>(proj_model_view * embed<4>(light_dir)).normalize();
        Vec3f r = (n * (n * l * 2.f) - l).normalize(); // reflected light
        float spec = pow(std::max(r.z, 0.0f), spec_map.getValue(uv));
        float diff = std::max(0.f, n * l);
        TGAColor c = diffuse_map.getValue(uv);
        color = c;
        for (int i = 0; i < 3; i++)
            color[i] = std::min<float>(5 + c[i] * (diff + .6 * spec), 255);
        return false;
    }
};

int main() {
    int width = 800;
    int height = width;
    auto model = Model("./obj/af.obj");
    auto diffuse = Texture("./obj/af_diff.tga");
    auto normal = Texture("./obj/af_norm.tga");
    auto spec = Texture("./obj/af_spec.tga");
    std::vector<Texture> textures{diffuse, normal, spec};
    model.textures = textures;
    const Vec3f light_dir(1, 1, 1); // light source
    const Vec3f eye(1, 1, 3);       // camera position
    const Vec3f center(0, 0, 0);    // camera direction
    const Vec3f up(0, 1, 0);        // camera up vector
    Shader shader(
        model, lookat(eye, center, up),
        viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4),
        projection(-1.f / (eye - center).norm()), light_dir);
    TGAImage image(width, height, TGAImage::RGB);
    TGAImage zbuffer(width, height, TGAImage::GRAYSCALE);
    for (int i = 0; i < model.nfaces(); i++) {
        Vec4f screen_coords[3];
        for (int j = 0; j < 3; j++) {
            screen_coords[j] = shader.vertex_shader(i, j);
        }
        triangle(screen_coords, shader, image, zbuffer);
    }

    image.flip_vertically(); // to place the origin in the bottom left corner of
                             // the image
    zbuffer.flip_vertically();
    image.write_tga_file("./output.tga");
    zbuffer.write_tga_file("./zbuffer.tga");
    return 0;
}
