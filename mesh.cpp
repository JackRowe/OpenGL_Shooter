#include "mesh.h"

mesh::mesh(const std::string& path) {

}

mesh::~mesh() {
	clean();
}

void mesh::clean() {
	vertices.clear();
	normals.clear();
	uvs.clear();
	faces.clear();
}

bool mesh::load(const std::string& path) {
	return true;
}