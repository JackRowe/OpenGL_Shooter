#pragma once

#include <iostream>

#include "vectors.h"

class input
{
private:
	bool keyStates[256] = { 0 };
	bool mouseStates[5] = { 0 };

	Vector2<int> mouseDelta = { 0 };
	Vector2<int> mousePosition = { 0 };

	Vector3<int> inputVector = { 0 };
public:
	void setKeyState(unsigned char key, bool state);
	bool getKeyState(unsigned char key) { return keyStates[key]; };

	void updateInputVector();
	const Vector3<int>& getInputVector() { return inputVector; };
};

