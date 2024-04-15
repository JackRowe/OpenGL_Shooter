#pragma once

#include <vector>
#include <string>

#include "vectors.h"

class mesh
{
private:
	std::vector<Vector3<float>*> vertices = { {} };
	std::vector<Vector3<float>*> normals = { {} };
	std::vector<Vector3<float>*> uvs = { {} };
	std::vector<Vector3<int>*> faces = { {} };
public:
	mesh(const std::string& path = "");
	~mesh();

	void clean();
	bool load(const std::string& path = "");
};

