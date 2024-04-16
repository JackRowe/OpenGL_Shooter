#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "object.h"
#include "vectors.h"

class camera : public object
{
private:
	Vector3<float> up = { 0.0f, 1.0f, 0.0f };
	float pitch, yaw = 0.0f;
public:
	camera(
		const Vector3<float>& newPosition = { 0.0f },
		const Vector3<float>& newRotation = { 0.0f },
		const Vector3<float>& newScale = { 1.0f },
		object* newParent = nullptr
	) : object(newPosition, newRotation, newScale, newParent) {};

	float getPitch() { return pitch; };
	float getYaw() { return yaw; };

	void setPitch(const float& newPitch) { pitch = newPitch; };
	void setYaw(const float& newYaw) { yaw = newYaw; };

	void update(Vector3<int>& inputVector);
};

