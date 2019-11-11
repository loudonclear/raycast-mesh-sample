#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <BVH/Object.h>

class Triangle : public Object
{
public:
    Triangle();
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
             glm::vec3 n1, glm::vec3 n2, glm::vec3 n3,
             int index);

    virtual bool getIntersection(const Ray &ray, IntersectionInfo *intersection) const;

    virtual glm::vec3 getNormal(const IntersectionInfo &I) const;
    virtual glm::vec3 getNormal(const glm::vec3 &p) const;

    virtual BBox getBBox() const;

    virtual glm::vec3 getCentroid() const;

    int getIndex() const;

private:
    glm::vec3 _v1, _v2, _v3;
    glm::vec3 _n1, _n2, _n3;

    int m_index;

    BBox _bbox;

    glm::vec3 _centroid;
};

#endif // TRIANGLE_H
