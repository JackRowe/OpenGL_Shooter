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
}