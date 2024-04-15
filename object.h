#pragma once

#include <iostream>

#include "vectors.h"

class object
{
private:
	Vector3<float> position = { 0.0f, 0.0f, 0.0f };
	Vector3<float> rotation = { 0.0f, 0.0f, 0.0f };
	Vector3<float> scale = { 0.0f, 0.0f, 0.0f };
public:
	object() { std::cout << "obj constructed" << std::endl; };

	object(
		Vector3<float> newPosition = { 0.0f, 0.0f, 0.0f },
		Vector3<float> newRotation = { 0.0f, 0.0f, 0.0f },
		Vector3<float> newScale = { 0.0f, 0.0f, 0.0f }
	);

	~object() {};
};

