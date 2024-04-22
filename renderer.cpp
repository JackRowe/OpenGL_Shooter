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
	glutIdleFunc(GLUT::idle);
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
	for (int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
	}

	for (int i = 0; i < textures.size(); i++) {
		delete textures[i];
	}

	for (int i = 0; i < objects.size(); i++) {
		// loop thru each object and clear children
		delete objects[i];
	}

	for (int i = 0; i < lights.size(); i++) {
		delete lights[i];
	}

	for (int i = 0; i < materials.size(); i++) {
		delete materials[i];
	}
}

void renderer::start() {
	stbi_set_flip_vertically_on_load(true);
	//objects.push_back(new model(meshes[0], textures[0], { 0.0f, -10.0f, 0.0f }, { 0.0f }, {20.0f, 1.0f, 20.0f}));

	cam = new camera;
	controller = new input;

	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);

	Vector3<float> camPosition = cam->getPosition();
	Vector3<float> camRotation = cam->getRotation();

	gluLookAt(
		camPosition.x,
		camPosition.y,
		camPosition.z,

		camRotation.x,
		camRotation.y,
		camRotation.z,

		0.0f,
		1.0f,
		0.0f
	);

	lights.push_back(new light{
		GL_LIGHT0,
		{1.0f, 1.0f, 1.0f, 0.0f},
		{1.0f, 1.0f, 1.0f, 0.0f},
		{0.5f, 0.5f, 0.5f, 1.0f},
		{1.0f, 1.0f, 1.0f, 0.0f},
	});

	glLightfv(lights[0]->id, GL_AMBIENT, lights[0]->ambient);
	glLightfv(lights[0]->id, GL_DIFFUSE, lights[0]->diffuse);
	glLightfv(lights[0]->id, GL_SPECULAR, lights[0]->specular);
	glLightfv(lights[0]->id, GL_POSITION, lights[0]->position);

	materials.push_back(new material{
		{1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		100.0f,
	});

	meshes.push_back(new mesh("Assets/cube.obj"));
	textures.push_back(new texture("Assets/cube.png"));

	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, 0.0f, 0.0f }));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, 0.0f, 0.0f }));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 0.0f, 10.0f }));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 0.0f, -10.0f }));

	glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	controller->setMouseDelta({ 0 });
	cam->setPitch(0);
	cam->setYaw(0);
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

float lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

void renderer::update(int deltaTime) {
	if (controller->getKeyState(27)) {
		exit(0);
	}

	glutPostRedisplay();
	glLoadIdentity();

	Vector2<int> mouseDelta = controller->getMouseDelta();
	float pitch = cam->getPitch();
	float yaw = cam->getYaw();

	cam->setPitch(pitch + (static_cast<float>(mouseDelta.y) * CAMERA_SENSITIVITY * static_cast<float>(deltaTime) / 1000.0f));
	cam->setYaw(yaw - (static_cast<float>(mouseDelta.x) * CAMERA_SENSITIVITY * static_cast<float>(deltaTime) / 1000.0f));

	cam->update(controller->getInputVector());

	// Update other objects
	updateVector(objects);

	controller->setMouseDelta({ 0 });
	controller->setIgnoreMouseFlag(true);
}

void renderer::idle() {
	//std::cout << "idle" << std::endl;
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