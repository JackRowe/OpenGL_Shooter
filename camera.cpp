#include "camera.h"

void camera::update() {
	const Vector3<float>& position = getPosition();

	gluLookAt(
		position.x,
		position.y,
		position.z,

		position.x,
		position.y,
		position.z - 1.0f,

		0.0f,
		1.0f,
		0.0f
	);
}