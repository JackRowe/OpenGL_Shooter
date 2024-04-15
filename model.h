#pragma once

#include <iostream>

#include "object.h"

class model : public object
{
private:

public:
    model(): object({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }) {
        
    }

    model(Vector3<float> newPosition, Vector3<float> newRotation, Vector3<float> newScale);
};

