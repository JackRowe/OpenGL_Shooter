#include "glut.h"

namespace GLUT {
	namespace {
		renderer* _renderer = nullptr;
		int lastTimeFromStart = 0;
	}

	void start(renderer* newRenderer) {
		_renderer = newRenderer;
	}

	void loop(int refreshRate) {
		if (_renderer == nullptr) return;

		int timeFromStart = glutGet(GLUT_ELAPSED_TIME);
		int deltaTime = timeFromStart - lastTimeFromStart;
		lastTimeFromStart = timeFromStart;

		_renderer->display(deltaTime);
		_renderer->update(deltaTime);

		glutTimerFunc(refreshRate - deltaTime, GLUT::loop, refreshRate);
	}

	void idle() {
		if (_renderer == nullptr) return;
		_renderer->idle();
	}

	void keyboardDown(unsigned char key, int x, int y) {
		if (_renderer == nullptr) return;
		_renderer->keyboard(key, x, y, true);
	}

	void keyboardUp(unsigned char key, int x, int y) {
		if (_renderer == nullptr) return;
		_renderer->keyboard(key, x, y, false);
	}

	void mouseButton(int button, int state, int x, int y) {
		if (_renderer == nullptr) return;
		_renderer->mouseButton(button, state, x, y);
	}

	void mouseMotion(int x, int  y) {
		if (_renderer == nullptr) return;
		_renderer->mouseMotion(x, y);
	}
}