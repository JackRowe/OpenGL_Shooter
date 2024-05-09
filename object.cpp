#include "object.h"

object::object(const Vector3<float>& newPosition, const Vector3<float>& newRotation, const Vector3<float>& newScale, object* newParent) {
	position = newPosition;
	rotation = newRotation;
	scale = newScale;
	parent = newParent;
}

void object::draw() {
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->draw();
	}
}

void object::update() {
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->update();
	}
}