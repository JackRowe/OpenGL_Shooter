#include "light.h"

void vectorToArray(Vector4<float>& input, float output[])
{
	output[0] = input.x;
	output[1] = input.y;
	output[2] = input.z;
	output[3] = input.w;
}

light::light(const int newLightID, Vector4<float>& newAmbient, Vector4<float>& newDiffuse, Vector4<float>& newSpecular, const Vector3<float>& newPosition, const Vector3<float>& newRotation, const Vector3<float>& newScale, object* newParent) : object(newPosition, newRotation, newScale, newParent) {
	lightID = newLightID;
	vectorToArray(newAmbient, ambient);
	std::cout << ambient[0] << ", " << ambient[1] << ", " << ambient[2] << ", " << ambient[3] << std::endl;
}