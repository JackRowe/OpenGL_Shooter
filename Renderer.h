#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <vector>

#include "GL\freeglut.h"
#include "glut.h"
#include "constants.h"
#include "vectors.h"
#include "model.h"
#include "mesh.h"

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