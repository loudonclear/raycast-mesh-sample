#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "BVH/BVH.h"
#include "basiccamera.h"
#include "shape/mesh.h"

#include <memory>

class Scene
{
public:
    Scene();
    virtual ~Scene();

    static Mesh *loadMesh(std::string filePath);
};

#endif // SCENE_H
