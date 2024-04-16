#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <chrono>

#include "vectors.h"

class mesh
{
private:
	std::vector<Vector3<float>> vertices = { {} };
	std::vector<Vector3<float>> normals = { {} };
	std::vector<Vector2<float>> uvs = { {} };
	std::vector<std::vector<Vector3<int>>> faces = { { {} } };
public:
	enum objHeader {
		none,
		vertex,
		normal,
		uv,
		face,
		smoothing,
		object,
		material,
		comment
	};

	std::map<std::string, objHeader> stringToHeader = {
		{"mtllib", material},
		{"usemtl", material},
		{"o", object},
		{"v", vertex},
		{"vn", normal},
		{"vt", uv},
		{"s", smoothing},
		{"f", face},
		{"#", comment},
	};

	mesh(const std::string& path = "");
	~mesh();

	std::vector<Vector3<float>>* getVertices() { return &vertices; };
	std::vector<std::vector<Vector3<int>>>* getFaces() { return &faces; };

	void clean();
	bool load(const std::string& path = "");
};

