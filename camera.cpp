#include "camera.h"

float toRadians(float Input) { return Input * 3.14159265359 / 180.0f; };

void camera::update(Vector3<int>& inputVector) {
	const Vector3<float>& position = getPosition();

	pitch = min(80.0f, max(pitch, -80.0f));

	// create a direction vector
	Vector3<GLfloat> direction = {
		cos(toRadians(yaw)) * cos(toRadians(pitch)),
		sin(toRadians(pitch)),
		sin(toRadians(yaw)) * cos(toRadians(pitch)),
	};

	direction = direction.normalize();

	std::cout << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
	setRotation(direction.x, direction.y, direction.z);

	Vector3<GLfloat> RelativeMovementVector = {
		cos(toRadians(yaw)) * -inputVector.z - sin(toRadians(yaw)) * inputVector.x,
		(float)inputVector.y,
		sin(toRadians(yaw)) * -inputVector.z + cos(toRadians(yaw)) * inputVector.x
	};

	setPosition(
		position.x + RelativeMovementVector.x,
		position.y + RelativeMovementVector.y,
		position.z + RelativeMovementVector.z
	);

	gluLookAt(
		position.x,
		position.y,
		position.z,

		position.x + direction.x,
		position.y + direction.y,
		position.z + direction.z,

		0.0f,
		1.0f,
		0.0f
	);
}