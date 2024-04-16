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
	glutKeyboardFunc(GLUT::keyboardDown);
	glutKeyboardUpFunc(GLUT::keyboardUp);
	glutMotionFunc(GLUT::mouseMotion);
	glutPassiveMotionFunc(GLUT::mouseMotion);
	glutMouseFunc(GLUT::mouseButton);

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
	stbi_set_flip_vertically_on_load(true);

	meshes.push_back(new mesh("Assets/cube.obj"));
	textures.push_back(new texture("Assets/cube.png"));
	objects.push_back(new model(meshes[0], textures[0], {10.0f, 0.0f, 0.0f}));
	objects.push_back(new model(meshes[0], textures[0], { 0.0f, -10.0f, 0.0f }, { 0.0f }, {20.0f, 1.0f, 20.0f}));

	cam = new camera;
	controller = new input;
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

void updateVector(std::vector<object*> objs)
{
	for (int i = 0; i < objs.size(); i++)
	{
		object* obj = objs[i];


		if (obj->getChildren()->size() <= 0) obj->update();
		else updateVector(*obj->getChildren());
	}
}

void renderer::update(int deltaTime) {
	glutPostRedisplay();
	glLoadIdentity();

	if (controller->getMouseState(0))
	{
		Vector2<int> mouseDelta = controller->getMouseDelta();
		float pitch = cam->getPitch();
		float yaw = cam->getYaw();

		cam->setPitch(pitch + ((float)mouseDelta.y));
		cam->setYaw(yaw + ((float)mouseDelta.x));
	}

	controller->setMouseDelta({ 0 });

	cam->update(controller->getInputVector());

	updateVector(objects);
}

void renderer::keyboard(unsigned char key, int x, int y, bool state) {
	controller->setKeyState(key, state);
}

void renderer::mouseButton(int button, int state, int x, int y) {
	controller->setMouseState(button, state, x, y);
}

void renderer::mouseMotion(int x, int y) {
	controller->updateMouseMotion(x, y);
}