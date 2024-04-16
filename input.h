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
	Vector3<int>& getInputVector() { return inputVector; };

	void setMouseState(int button, int state, int x, int y);
	bool getMouseState(int button) { return mouseStates[button]; };

	void updateMouseMotion(int x, int y);

	Vector2<int> getMouseDelta() { return mouseDelta; };
	void setMouseDelta(const Vector2<int>& newMouseDelta) { mouseDelta = newMouseDelta; };
};

