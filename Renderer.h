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
#include "camera.h"
#include "input.h"
#include "stb_image.h"

class renderer
{
private:
	int frame = 0;
	input* controller;

	std::vector<object*> objects = {};
	std::vector<mesh*> meshes = {};
	std::vector<texture*> textures = {};
public:
	renderer() {};
	renderer(int argc, char* argv[]);
	~renderer();

	void start();
	void display(int deltaTime);
	void update(int deltaTime);
	void keyboard(unsigned char key, int x, int y, bool state);
};