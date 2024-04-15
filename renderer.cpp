#include "renderer.h"

renderer::renderer(int argc, char* argv[]) {
	// initalize both the glut callbacks and glut
	GLUT::start(this);
	glutInit(&argc, argv);

	// initalize display properties
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("OpenGL");

	glutTimerFunc(REFRESH_RATE, GLUT::loop, REFRESH_RATE);

	start();

	glutMainLoop();
}

renderer::~renderer() {

}

void renderer::start() {
	meshes.push_back(new mesh("Assets/barrel.obj"));
	objects.push_back(new model(meshes[0]));
}

void renderer::display(int deltaTime) {
	// clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// hello triangle
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(-0.5f, -0.5f);
		glEnd();
	glPopMatrix();

	frame++;
	glutSwapBuffers();
}

void renderer::update(int deltaTime) {

}
