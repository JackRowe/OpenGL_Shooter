#include "input.h"

void input::setKeyState(unsigned char key, bool state) {
	if (keyStates[key] == state) return;
	keyStates[key] = state;
	//std::cout << key << " | " << state << std::endl;

	updateInputVector();
}

void input::updateInputVector() {
	int forward = keyStates['s'] - keyStates['w'];
	int horizontal = keyStates['d'] - keyStates['a'];
	int vertical = keyStates['e'] - keyStates['q'];
	//std::cout << horizontal << ", " << vertical << ", " << forward << std::endl;
	inputVector = { horizontal, vertical, forward };
}

void input::setMouseState(int button, int state, int x, int y) {
	mouseStates[tolower(button)] = !state;
	//std::cout << button << " | " << state << std::endl;
	//mouseDelta = { 0, 0 };
}

void input::updateMouseMotion(int x, int y) {
	if (abs(x - mousePosition.x) > WINDOW_WIDTH / 4 || abs(y - mousePosition.y) > WINDOW_HEIGHT / 4) mouseDelta = { 0 };
	else mouseDelta = { x - mousePosition.x, y - mousePosition.y };

	mousePosition = { x, y };
}