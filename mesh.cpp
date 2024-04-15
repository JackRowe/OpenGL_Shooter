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

template <typename T>
void parseComponents(std::string& line, std::vector<T*>& components, const char& delimiter) {
	T component = T();
	int componentSize = sizeof(T) / sizeof(float);

	for (int i = 0; i < componentSize; i++) {
		std::string s = line.substr(0, line.find_first_of(' '));
		float value = std::stof(s);

		switch (i) {
		case 0:
			component.x = value;
			break;
		case 1:
			component.y = value;
			break;
		case 2:
			component.z = value;
			break;
		case 3:
			component.w = value;
			break;
		}

		line = line.substr(line.find_first_of(' ') + 1, line.length());
	}

	components.push_back(&component);
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
				parseComponents<Vector3<float>>(line, vertices, ' ');
				break;
			}

			case uv: {
				parseComponents<Vector2<float>>(line, uvs, ' ');
				break;
			}

			case normal: {
				parseComponents<Vector3<float>>(line, vertices, ' ');
				break;
			}

			case face: {
				std::vector<Vector3<int>*> face = { {} };
				std::string lastLine = "";

				for (int i = 0; i < 4; i++)
				{
					std::string tempLine = line.substr(0, line.find_first_of(' '));

					if (lastLine == tempLine) continue;

					parseComponents<Vector3<int>>(tempLine, face, '/');
					line = line.substr(line.find_first_of(' ') + 1, line.length());
					lastLine = tempLine;
				}

				faces.push_back(face);
				break;
			}

			default: {
				break;
			}
		}
	}

	return true;
}