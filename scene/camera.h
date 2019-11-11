#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
    Camera() {}

    virtual glm::mat4x4 getViewMatrix() const = 0;
    virtual glm::mat4x4 getScaleMatrix() const = 0;
};

#endif // CAMERA_H
