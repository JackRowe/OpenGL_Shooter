#include "glut.h"

namespace GLUT {
	namespace {
		renderer* _renderer = nullptr;
	}

	void start(renderer* newRenderer) {
		_renderer = newRenderer;
	}

	void loop(int refreshRate) {
		if (_renderer == nullptr) return;

		int deltaTime = glutGet(GLUT_ELAPSED_TIME);
		_renderer->display(deltaTime);
		_renderer->update(deltaTime);
		deltaTime = glutGet(GLUT_ELAPSED_TIME) - deltaTime;

		glutTimerFunc(refreshRate - deltaTime, GLUT::loop, refreshRate);
	}

	void keyboardDown(unsigned char key, int x, int y) {
		if (_renderer == nullptr) return;
		_renderer->keyboard(key, x, y, true);
	}

	void keyboardUp(unsigned char key, int x, int y) {
		if (_renderer == nullptr) return;
		_renderer->keyboard(key, x, y, false);
	}
}