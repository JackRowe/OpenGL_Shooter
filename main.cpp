#include "renderer.h"

int main(int argc, char* argv[]) {
	renderer* root = new renderer(argc, argv);
	delete root;
	return 0;
}