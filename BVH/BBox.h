#pragma once

#ifndef BBox_h
#define BBox_h

#include "Ray.h"
#include <glm/glm.hpp>
#include <stdint.h>

struct BBox {

  glm::vec3 min;
  glm::vec3 max;
  glm::vec3 extent;

  void setMinMax(const glm::vec3& min, const glm::vec3& max);
  void setP(const glm::vec3& min);

  bool intersect(const Ray& ray, float *tnear, float *tfar) const;
  void expandToInclude(const glm::vec3& p);
  void expandToInclude(const BBox& b);
  uint32_t maxDimension() const;
  float surfaceArea() const;
};

#endif
