#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL\freeglut.h"
#include "glut.h"
#include "constants.h"

class renderer
{
private:
	int frame = 0;
public:
	renderer() {};
	renderer(int argc, char* argv[]);
	~renderer();

	void start();
	void display(int deltaTime);
	void update(int deltaTime);
};