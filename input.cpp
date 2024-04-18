#include "input.h"

void input::setKeyState(unsigned char key, bool state) {
	if (keyStates[key] == state) return;
	keyStates[key] = state;
	std::cout << key << " | " << state << std::endl;

	updateInputVector();
}

void input::updateInputVector() {
	int forward = keyStates['s'] - keyStates['w'];
	int horizontal = keyStates['d'] - keyStates['a'];
	int vertical = keyStates['e'] - keyStates['q'];

	inputVector = { horizontal, vertical, forward };
}

void input::setMouseState(int button, int state, int x, int y) {
	mouseStates[tolower(button)] = !state;
	//std::cout << button << " | " << state << std::endl;
	mouseDelta = { 0, 0 };
}

void input::updateMouseMotion(int x, int y) {
	mouseDelta = { mousePosition.x - x, mousePosition.y - y };
	mousePosition = { x, y };
}