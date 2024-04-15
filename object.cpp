#include "object.h"

object::object(Vector3<float> newPosition, Vector3<float> newRotation, Vector3<float> newScale) {
	position = newPosition;
	rotation = newRotation;
	scale = newScale;

	std::cout << "object constructer" << std::endl;
}