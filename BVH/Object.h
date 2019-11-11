#pragma once

#ifndef Object_h_
#define Object_h_

#include "IntersectionInfo.h"
#include "Ray.h"
#include "BBox.h"

struct Object {
    Object() {
        transform = inverseTransform = normalTransform = inverseNormalTransform = glm::mat3x3(1.f);
    }
    virtual ~Object(){}
  //! All "Objects" must be able to test for intersections with rays.
  virtual bool getIntersection(
      const Ray& ray,
      IntersectionInfo* intersection)
    const = 0;

  //! Return an object normal based on an intersection
  virtual glm::vec3 getNormal(const IntersectionInfo& I) const = 0;

  //! Return a bounding box for this object
  virtual BBox getBBox() const = 0;

  //! Return the centroid for this object. (Used in BVH Sorting)
  virtual glm::vec3 getCentroid() const = 0;

    virtual void setTransform(const glm::mat3x3 transform) {
        this->transform = transform;
        this->inverseTransform = glm::inverse(transform);
        this->normalTransform = transform;
        this->inverseNormalTransform = glm::transpose(glm::inverse(transform));
    }

    glm::mat3x3 transform;
    glm::mat3x3 normalTransform;
    glm::mat3x3 inverseTransform;
    glm::mat3x3 inverseNormalTransform;
};

#endif
