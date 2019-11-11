#pragma once

#ifndef TRACER_H
#define TRACER_H

#include <glm/glm.hpp>

#include "scene/basiccamera.h"
#include "scene/shape/mesh.h"


class Tracer
{
public:
    Tracer(int width, int height);

    void traceScene(const Mesh& mesh, const std::vector<BasicCamera> &cams, std::vector<glm::vec3> &hits);

private:
    int m_width, m_height;

    glm::vec3 tracePixel(int x, int y, const Mesh& mesh, const glm::mat4x4 &invViewMatrix, std::vector<glm::vec3> &hits);
    glm::vec3 traceRay(const Ray& r, const Mesh& mesh, std::vector<glm::vec3> &hits);
};

#endif // TRACER_H
