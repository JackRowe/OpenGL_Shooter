#include "object.h"

object::object(const Vector3<float>& newPosition, const Vector3<float>& newRotation, const Vector3<float>& newScale) {
	position = newPosition;
	rotation = newRotation;
	scale = newScale;
}