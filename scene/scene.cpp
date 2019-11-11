#include "scene.h"


#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "util/tiny_obj_loader.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

Mesh *Scene::loadMesh(std::string filePath)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err,
                                filePath.c_str(), (filePath + "/").c_str(), true);
    if(!err.empty()) {
        std::cerr << err << std::endl;
    }

    if(!ret) {
        std::cerr << "Failed to load/parse .obj file" << std::endl;
        return nullptr;
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec2> uvs;
    std::vector<int> materialIds;
    std::vector<glm::ivec3> faces;

    for(size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            unsigned int fv = shapes[s].mesh.num_face_vertices[f];

            glm::ivec3 face;
            for(size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                tinyobj::real_t nx;
                tinyobj::real_t ny;
                tinyobj::real_t nz;
                tinyobj::real_t tx;
                tinyobj::real_t ty;

                if(idx.normal_index != -1) {
                    nx = attrib.normals[3*idx.normal_index+0];
                    ny = attrib.normals[3*idx.normal_index+1];
                    nz = attrib.normals[3*idx.normal_index+2];
                } else {
                    nx = 0;
                    ny = 0;
                    nz = 0;
                }
                if(idx.texcoord_index != -1) {
                    tx = attrib.texcoords[2*idx.texcoord_index+0];
                    ty = attrib.texcoords[2*idx.texcoord_index+1];
                } else {
                    tx = 0;
                    ty = 0;
                }

                tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
                tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
                tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];

                face[v] = vertices.size();
                vertices.push_back(glm::vec3(vx, vy, vz));
                normals.push_back(glm::normalize(glm::vec3(nx, ny, nz)));

                uvs.push_back(glm::vec2(tx, ty));
                colors.push_back(glm::vec3(red, green, blue));
            }
            faces.push_back(face);
            materialIds.push_back(shapes[s].mesh.material_ids[f]);

            index_offset += fv;
        }
    }
    std::cout << "Loaded " << faces.size() << " faces" << std::endl;

    Mesh *m = new Mesh;
    m->init(vertices,
            normals,
            uvs,
            colors,
            faces,
            materialIds,
            materials);
    return m;
}

