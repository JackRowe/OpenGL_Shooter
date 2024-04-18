#include "camera.h"

float toRadians(float Input) { return Input * 3.14159265359 / 180.0f; };

void camera::update(Vector3<int>& inputVector) {
	const Vector3<float>& position = getPosition();

	pitch = min(80.0f, max(pitch, -80.0f));

	//std::cout << inputVector.x << ", " << inputVector.y << ", " << inputVector.z << std::endl;

	// create a direction vector
	Vector3<float> direction = {
		cos(toRadians(yaw)) * cos(toRadians(pitch)),
		sin(toRadians(pitch)),
		sin(toRadians(yaw)) * cos(toRadians(pitch)),
	};

	direction = direction.normalize();
	setRotation(position.x + direction.x, position.y + direction.y, position.z + direction.z);

	Vector3<float> relativeVector = {
		cos(toRadians(yaw)) * -inputVector.z - sin(toRadians(yaw)) * inputVector.x,
		(float)inputVector.y,
		sin(toRadians(yaw)) * -inputVector.z + cos(toRadians(yaw)) * inputVector.x
	};

	setPosition(
		position.x + relativeVector.x * CAMERA_SPEED,
		position.y + relativeVector.y * CAMERA_SPEED,
		position.z + relativeVector.z * CAMERA_SPEED
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