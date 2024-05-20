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
#include "structures.h"
#include "model.h"
#include "mesh.h"
#include "camera.h"
#include "input.h"
#include "stb_image.h"

class renderer
{
private:
	int frame = 0;
	bool mouseLocked = true;
	input* controller;
	camera* cam;

	std::vector<object*> objects = {};
	std::vector<mesh*> meshes = {};
	std::vector<texture*> textures = {};
	std::vector<light*> lights = {};
	std::vector<material*> materials = {};
public:
	renderer() {};
	renderer(int argc, char* argv[]);
	~renderer();

	void updateVector(std::vector<object*> objs);
	void drawString(std::string text, Vector2<float>* position);

	void start();
	void display(int deltaTime);
	void update(int deltaTime);
	void idle();
	void keyboard(unsigned char key, int x, int y, bool state);
	void mouseButton(int button, int state, int x, int y);
	void mouseMotion(int x, int y);
};