#include "object.h"

object::object(const Vector3<float>& newPosition, const Vector3<float>& newRotation, const Vector3<float>& newScale, object* newParent) {
	position = newPosition;
	rotation = newRotation;
	scale = newScale;
	parent = newParent;
}