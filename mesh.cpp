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
				Vector3<float> vertex = { 0.0f };
				// loop over each component of the vertex and add it to vertex before removing that component from the line
				for (int i = 0; i < 3; i++)
				{
					std::string s = line.substr(0, line.find_first_of(' '));
					if (i == 0){
						vertex.x = std::stof(s);
					}
					else if (i == 1){
						vertex.y = std::stof(s);
					}
					else{
						vertex.z = std::stof(s);
					}
					line = line.substr(line.find_first_of(' ') + 1, line.length());
				}
				// push back the vertices vector with a pointer to the vertex data
				vertices.push_back(&vertex);
				break;
			}

			case uv: {
				Vector2<float> uv = { 0.0f };
				// loop over each component of the uv and add it to uv before removing that component from the line
				for (int i = 0; i < 3; i++)
				{
					std::string s = line.substr(0, line.find_first_of(' '));
					if (i == 0) {
						uv.x = std::stof(s);
					}
					else {
						uv.y = std::stof(s);
					}
					line = line.substr(line.find_first_of(' ') + 1, line.length());
				}
				// push back the vertices vector with a pointer to the uv data
				uvs.push_back(&uv);
				break;
			}

			case normal: {
				Vector3<float> normal = { 0.0f };
				// loop over each component of the normal and add it to normal before removing that component from the line
				for (int i = 0; i < 3; i++)
				{
					std::string s = line.substr(0, line.find_first_of(' '));
					if (i == 0) {
						normal.x = std::stof(s);
					}
					else if (i == 1) {
						normal.y = std::stof(s);
					}
					else {
						normal.z = std::stof(s);
					}
					line = line.substr(line.find_first_of(' ') + 1, line.length());
				}
				// push back the vertices vector with a pointer to the normal data
				normals.push_back(&normal);
				break;
			}

			case face: {
				std::vector<Vector3<int>*> face = { {} };
				std::string lastLine = "";

				for (int i = 0; i < 4; i++)
				{
					std::string tempLine = line.substr(0, line.find_first_of(' '));

					if (lastLine == tempLine) continue;

					Vector3<int> index = { 0 };
					// loop over each component of the index and add it to index before removing that component from the line
					for (int i = 0; i < 3; i++)
					{
						std::string s = line.substr(0, line.find_first_of('/'));
						if (i == 0) {
							index.x = std::stof(s);
						}
						else if (i == 1) {
							index.y = std::stof(s);
						}
						else {
							index.z = std::stof(s);
						}
						line = line.substr(line.find_first_of('/') + 1, line.length());
					}
					// push back the vertices vector with a pointer to the index data
					face.push_back(&index);
					
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