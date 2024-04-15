#include "model.h"

model::model(mesh* newMesh, texture* newTexture, Vector3<float> newPosition, Vector3<float> newRotation, Vector3<float> newScale) : object(newPosition, newRotation, newScale) {
	std::cout << "model constructer" << std::endl;
}

model::~model() {
	delete _mesh;
	delete _texture;
}