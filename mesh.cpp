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
	clean();

	// open the file from the provided path
	std::ifstream file;
	file.open(path);

	// make sure the file is valid
	if (!file || !file.is_open() || !file.good()) return false;

	std::string line = "";

	// loop over every line of the file
	while (getline(file, line))
	{
		// get the header of the current line and remove it from the line afterwards
		objHeader currentHeader = stringToHeader[line.substr(0, line.find_first_of(' '))];
		line = line.substr(line.find_first_of(' ') + 1, line.length());

		switch (currentHeader) {
			case vertex: {
				Vector3<float> v = { 0.0f };

				// loop over each component of the vertex and add it to v before removing that component from the line
				for (int i = 0; i < 3; i++)
				{
					std::string s = line.substr(0, line.find_first_of(' '));

					if (i == 0)
					{
						v.x = std::stof(s);
					}
					else if (i == 1)
					{
						v.y = std::stof(s);
					}
					else
					{
						v.z = std::stof(s);
					}

					line = line.substr(line.find_first_of(' ') + 1, line.length());
				}
			}

			case uv: {
				break;
			}

			case normal: {
				break;
			}

			case face: {
				break;
			}

			default: {
				break;
			}
		}
	}

	return true;
}