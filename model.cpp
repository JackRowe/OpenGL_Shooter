#include "model.h"

model::model(mesh* newMesh, texture* newTexture, const Vector3<float>& newPosition, const Vector3<float>& newRotation, const Vector3<float>& newScale) : object(newPosition, newRotation, newScale) {
	_mesh = newMesh;
	_texture = newTexture;
}