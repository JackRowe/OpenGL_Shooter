#include "renderer.h"

renderer::renderer(int argc, char* argv[]) {
	// initalize both the glut callbacks and glut
	GLUT::start(this);
	glutInit(&argc, argv);

	// initalize display properties
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("OpenGL");

	// enable face culling & depth testing
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_TRUE);

	start();

	glutTimerFunc(REFRESH_RATE, GLUT::loop, REFRESH_RATE);

	// set up the projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	gluPerspective(45, 1, 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
}

renderer::~renderer() {
	// add delete loops for meshes objects and textures
}

void renderer::start() {
	meshes.push_back(new mesh("Assets/cube.obj"));
	objects.push_back(new model(meshes[0], nullptr, {2.0f, 0.0f, -10.0f}));
	objects.push_back(new model(meshes[0], nullptr, { -2.0f, 0.0f, -10.0f }));
}

void drawVector(std::vector<object*> objs)
{
	for (int i = 0; i < objs.size(); i++)
	{
		object* obj = objs[i];


		if (obj->getChildren()->size() <= 0) obj->draw();
		else drawVector(*obj->getChildren());
	}
}

void renderer::display(int deltaTime) {
	// clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawVector(objects);

	frame++;
	glutSwapBuffers();
}

void renderer::update(int deltaTime) {
	glutPostRedisplay();
	glLoadIdentity();
	gluLookAt(
		0.0f,
		0.0f,
		1.0f,

		0.0f,
		0.0f,
		-1.0f,

		0.0f,
		1.0f,
		0.0f
	);
}
