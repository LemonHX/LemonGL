//
// Created by LemonHX on 2020/9/3.
//

#include "model.hxx"
#include <fstream>
#include <iostream>
#include <sstream>

Model::Model(const char *filename)
    : verts(), faces(), norms(), uvs(), textures() {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail())
        return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i = 0; i < 3; i++)
                iss >> v[i];
            verts.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec3f n;
            for (int i = 0; i < 3; i++)
                iss >> n[i];
            norms.push_back(n);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f uv;
            for (int i = 0; i < 2; i++)
                iss >> uv[i];
            uvs.push_back(uv);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<Vec3i> f;
            Vec3i tmp;
            iss >> trash;
            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                for (int i = 0; i < 3; i++)
                    tmp[i]--; // in wavefront obj all indices start at 1, not
                              // zero
                f.push_back(tmp);
            }
            faces.push_back(f);
        }
    }
    std::cerr << "# v# " << verts.size() << " f# " << faces.size() << " vt# "
              << uvs.size() << " vn# " << norms.size() << std::endl;
}

Model::~Model() {}

int Model::nverts() { return (int)verts.size(); }

int Model::nfaces() { return (int)faces.size(); }

std::vector<int> Model::face(int idx) {
    std::vector<int> face;
    for (int i = 0; i < (int)faces[idx].size(); i++)
        face.push_back(faces[idx][i][0]);
    return face;
}

Vec3f Model::vert(int i) { return verts[i]; }

Vec3f Model::vert(int iface, int vert) { return verts[faces[iface][vert][0]]; }

Vec2f Model::uv(int iface, int vert) { return uvs[faces[iface][vert][1]]; }

Texture &Model::getTexture(int idx) { return textures[idx]; }
