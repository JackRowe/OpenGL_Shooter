#pragma once

#include <iostream>

#include "vectors.h"

class object
{
private:
	Vector3<float> position = { 0.0f };
	Vector3<float> rotation = { 0.0f };
	Vector3<float> scale = { 0.0f };
public:
	object(
		const Vector3<float>& newPosition = { 0.0f },
		const Vector3<float>& newRotation = { 0.0f },
		const Vector3<float>& newScale = { 0.0f }
	);

	~object() {};
};