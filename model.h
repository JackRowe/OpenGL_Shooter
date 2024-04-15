#pragma once

#include <iostream>

#include "object.h"
#include "mesh.h"
#include "texture.h"
#include "constants.h"

class model : public object
{
private:
    mesh* _mesh = nullptr;
    texture* _texture = nullptr;
public:
    model(
        mesh* newMesh = nullptr,
        texture* newTexture = nullptr,
        const Vector3<float>& newPosition = { 0.0f }, 
        const Vector3<float>& newRotation = { 0.0f }, 
        const Vector3<float>& newScale = { 0.0f },
        object* parent = nullptr
    );
    ~model() {};
};

