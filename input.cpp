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