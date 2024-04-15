#pragma once

#include "renderer.h"

class renderer;

namespace GLUT {
	void start(renderer* newRenderer);
	void loop(int refreshRate);
}