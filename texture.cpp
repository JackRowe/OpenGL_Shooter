#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

texture::texture(const std::string& path) {
	load(path.c_str());
}

bool texture::load(const char* path) {
	auto start = std::chrono::high_resolution_clock::now();

	// create texture and bind it to the id
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// get the image data using the stb image library
	int nrChannels;
	unsigned char* Data = stbi_load(path, &width, &height, &nrChannels, 4);

	// set texture data and it's parameters
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, Data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "loaded: " << path << " : in " << duration.count() << " ms" << std::endl;
	return true;
}