#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>
#include <iostream>
#include <chrono>

#include "GL\freeglut.h"

class texture
{
private:
	int width = 0;
	int height = 0;

	GLuint textureID = -1;
public:
	texture(const std::string& path = "");
	~texture() {};

	bool load(const char* path = "");
	GLuint getTextureID() { return textureID; };
};

