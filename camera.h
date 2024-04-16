#pragma once

#include "object.h"
#include "vectors.h"

class camera : public object
{
private:
	Vector3<float> up = { 0.0f, 1.0f, 0.0f };
	float pitch, yaw = 0.0f;
};

