#pragma once

#ifndef MESH_H
#define MESH_H

#include <BVH/Object.h>
#include <BVH/BVH.h>

#include "triangle.h"

#include <util/tiny_obj_loader.h>

#include <vector>


class Mesh : public Object
{
public:
    virtual ~Mesh();
    void init(const std::vector<glm::vec3> &vertices,
         const std::vector<glm::vec3> &normals,
         const std::vector<glm::vec2> &uvs,
         const std::vector<glm::vec3> &colors,
         const std::vector<glm::ivec3> &faces,
         const std::vector<int> &materialIds,
         const std::vector<tinyobj::material_t> &materials);

    virtual bool getIntersection(const Ray &ray, IntersectionInfo *intersection) const;

    virtual glm::vec3 getNormal(const IntersectionInfo &I) const;

    virtual BBox getBBox() const;

    virtual glm::vec3 getCentroid() const;

    const glm::ivec3 getTriangleIndices(int faceIndex) const;
    const tinyobj::material_t& getMaterial(int faceIndex) const;

    const glm::vec3 getVertex(int vertexIndex) const;
    const glm::vec3 getNormal(int vertexIndex) const;
    const glm::vec3 getColor(int vertexIndex) const;
    const glm::vec2 getUV(int vertexIndex) const;

    virtual void setTransform(glm::mat3x3 transform) override;

private:
    // Properties fromt the scene file
    //CS123SceneMaterial _wholeObjectMaterial;

    // Properties from the .obj file
    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec3> _normals;
    std::vector<glm::vec3> _colors;
    std::vector<glm::vec2> _uvs;
    std::vector<glm::ivec3> _faces;
    std::vector<int> _materialIds;
    std::vector<tinyobj::material_t> _materials;

    BVH *_meshBvh;

    glm::vec3 _centroid;

    BBox _bbox;
    BBox transformed_bbox;

    std::vector<Object *> *_objects;
    Triangle *_triangles;

    void calculateMeshStats();
    void createMeshBVH();
};

#endif // MESH_H
