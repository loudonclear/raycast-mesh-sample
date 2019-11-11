#include "mesh.h"


#include <iostream>

using namespace std;

void Mesh::init(const std::vector<glm::vec3> &vertices,
           const std::vector<glm::vec3> &normals,
           const std::vector<glm::vec2> &uvs,
           const std::vector<glm::vec3> &colors,
           const std::vector<glm::ivec3> &faces,
           const std::vector<int> &materialIds,
           const std::vector<tinyobj::material_t> &materials)
{
    _vertices = vertices;
    _normals = normals;
    _colors = colors;
    _uvs = uvs;
    _faces = faces;
    _materialIds = materialIds;
    _materials = materials;
    calculateMeshStats();
    createMeshBVH();
}

Mesh::~Mesh()
{
    delete _meshBvh;
    delete _objects;
    delete[] _triangles;
}

bool Mesh::getIntersection(const Ray &ray, IntersectionInfo *intersection) const
{
    IntersectionInfo i;
    bool col = _meshBvh->getIntersection(ray, &i, false);
    if(col) {
        intersection->t = i.t;
        intersection->object = this;
        intersection->data = i.object;

        return true;
    }
    return false;
}

glm::vec3 Mesh::getNormal(const IntersectionInfo &I) const
{
    return static_cast<const Object *>(I.data)->getNormal(I);
}

BBox Mesh::getBBox() const
{
    //return transformed_bbox;
    return _bbox;
}

glm::vec3 Mesh::getCentroid() const
{
    //return transform * _centroid;
    return _centroid;
}

const glm::ivec3 Mesh::getTriangleIndices(int faceIndex) const
{
    return _faces[faceIndex];
}

const tinyobj::material_t &Mesh::getMaterial(int faceIndex) const
{
    return _materials[_materialIds[faceIndex]];
}

const glm::vec3 Mesh::getVertex(int vertexIndex) const
{
    return _vertices[vertexIndex];
}

const glm::vec3 Mesh::getNormal(int vertexIndex) const
{
    return _normals[vertexIndex];
}

const glm::vec3 Mesh::getColor(int vertexIndex) const
{
    return _colors[vertexIndex];
}

const glm::vec2 Mesh::getUV(int vertexIndex) const
{
    return _uvs[vertexIndex];
}

void Mesh::setTransform(glm::mat3x3 transform)
{
// Not implemented
}

void Mesh::calculateMeshStats()
{
    _bbox.setP(_vertices[0]);
    for(auto v : _vertices) {
        _centroid += v;
        _bbox.expandToInclude(v);
    }
    transformed_bbox = _bbox;
    _centroid /= _vertices.size();
}

void Mesh::createMeshBVH()
{
    _triangles = new Triangle[_faces.size()];
    _objects = new std::vector<Object *>;
    _objects->resize(_faces.size());
    for(unsigned int i = 0; i < _faces.size(); ++i) {
        glm::ivec3 face = _faces[i];
        glm::vec3 v1 = _vertices[face[0]];
        glm::vec3 v2 = _vertices[face[1]];
        glm::vec3 v3 = _vertices[face[2]];
        glm::vec3 n1 = _normals[face[0]];
        glm::vec3 n2 = _normals[face[1]];
        glm::vec3 n3 = _normals[face[2]];
        _triangles[i] = Triangle(v1, v2, v3, n1, n2, n3, i);
        (*_objects)[i] = &_triangles[i];
    }

    _meshBvh = new BVH(_objects);
}
