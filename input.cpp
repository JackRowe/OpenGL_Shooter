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

	inputVector = { horizontal, vertical, forward };
}

void input::setMouseState(int button, int state, int x, int y) {
	mouseStates[tolower(button)] = !state;
	//std::cout << button << " | " << state << std::endl;
	//mouseDelta = { 0, 0 };
}

void input::updateMouseMotion(int x, int y) {

	// reset flag
	
	//if (x == WINDOW_WIDTH / 2 && y == WINDOW_HEIGHT / 2) {
	//	// at centre of the screen
	//	std::cout << "ignore: " << x - mousePosition.x << ", " << y - mousePosition.y << " | new: (" << x << ", " << y << ") | old: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
	//	mouseDelta = { 0 };
	//}
	//else if ((x - mousePosition.x) + x == WINDOW_WIDTH / 2 && (y - mousePosition.y) + y == WINDOW_HEIGHT / 2) {
	//	// wants to go to centre of the screen
	//	std::cout << "ignore: " << x - mousePosition.x << ", " << y - mousePosition.y << " | new: (" << x << ", " << y << ") | old: (" << mousePosition.x << ", " << mousePosition.y << ") | ???: (" << (x - mousePosition.x) + x << ", " << (y - mousePosition.y) + y << ")" << std::endl;
	//	mouseDelta = { 0 };
	//}
	//else {
	//	// apply
	//	std::cout << "apply: " << x - mousePosition.x << ", " << y - mousePosition.y << " | new: (" << x << ", " << y << ") | old: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
	////	mouseDelta = { x - mousePosition.x, y - mousePosition.y };
	//}

	//if (!ignoreMouseFlag) {
	//	mouseDelta = { 0 };
	//}
	//else {
	//	mouseDelta = { x - mousePosition.x, y - mousePosition.y };
	//}

	//if (mousedelta.x > 10 || mousedelta.y > 10)
	//{
	//	mousedelta.x = 0;
	//	mousedelta.y = 0;
	//}

	mouseDelta = { x - mousePosition.x, y - mousePosition.y };
	mousePosition = { x, y };

	/*if (abs(mousePosition.x - WINDOW_WIDTH) >= WINDOW_WIDTH / 2 || abs(mousePosition.y - WINDOW_HEIGHT) >= WINDOW_HEIGHT / 2) {
		glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}*/
}