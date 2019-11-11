#pragma once

#ifndef Ray_h
#define Ray_h

#include <glm/glm.hpp>

#include "util/common.h"

struct Ray {

    Ray(const glm::vec3 ov, const glm::vec3 dv) {
	o = ov;
        d = glm::normalize(dv);
	inv_d = glm::normalize(glm::vec3(1.f) / dv);
    }

    Ray transform(glm::mat4x4 mat) const {
        glm::vec4 oo = mat * glm::vec4(o, 1);
        glm::vec4 od = mat * glm::vec4(d, 0);
        return Ray(glm::vec3(oo), glm::vec3(od));
    }

    Ray transform(glm::mat3x3 transform) const {
        glm::vec3 oo = transform * o;
        glm::vec3 od = glm::transpose(glm::inverse(transform)) * d;
        return Ray(oo, od);
    }

  glm::vec3 o; // Ray Origin
  glm::vec3 d; // Ray Direction
  glm::vec3 inv_d; // Inverse of each Ray Direction component
};

#endif
