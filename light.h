#pragma once

#include "object.h"

class light : public object
{
private:
    int lightID;
	float ambient[4];
	float diffuse[4];
	float specular[4];
    float position[4];
public:
    light(
        const int newLightID,
        Vector4<float>& newAmbient,
        Vector4<float>& newDiffuse,
        Vector4<float>& newSpecular,
        const Vector3<float>& newPosition,
        const Vector3<float>& newRotation,
        const Vector3<float>& newScale,
        object* newParent
    );
};

