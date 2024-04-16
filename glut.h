#pragma once

#include "renderer.h"

class renderer;

namespace GLUT {
	void start(renderer* newRenderer);
	void loop(int refreshRate);
	void keyboardDown(unsigned char key, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);
}