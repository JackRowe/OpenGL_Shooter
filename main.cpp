#include "renderer.h"

int main(int argc, char* argv[]) {
	std::cout << "stated" << std::endl;

	renderer* root = new renderer(argc, argv);
	delete root;
	return 0;
}