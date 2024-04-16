#include "camera.h"

void camera::update() {
	gluLookAt(
		0.0f,
		0.0f,
		1.0f,

		0.0f,
		0.0f,
		-1.0f,

		0.0f,
		1.0f,
		0.0f
	);
}