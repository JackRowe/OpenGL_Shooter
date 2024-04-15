#pragma once

#include <vector>

#include "vectors.h"

class mesh
{
private:
	std::vector<Vector3<float>> vertices = { {} };
	std::vector<Vector3<float>> normals = { {} };
	std::vector<Vector3<float>> uvs = { {} };
	std::vector<Vector3<int>> faces = { {} };
public:
	
};

