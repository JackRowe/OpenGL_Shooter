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
	gluPerspective(45, 1, 0.01, 20000);
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
		{0.5f, 0.5f, 1.0f, 1.0f},
		{0.5f, 0.5f, 1.0f, 1.0f},
		{0.5f, 0.5f, 1.0f, 1.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
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

	meshes.push_back(new mesh("Assets/skybox2.obj"));
	textures.push_back(new texture("Assets/skyboxer.jpg"));

	meshes.push_back(new mesh("Assets/ground.obj"));
	textures.push_back(new texture("Assets/grass.jpg"));

	meshes.push_back(new mesh("Assets/ball.obj"));
	textures.push_back(new texture("Assets/ball.png"));

	meshes.push_back(new mesh("Assets/rafale.obj"));
	meshes.push_back(new mesh("Assets/missile.obj"));

	objects.push_back(new model(meshes[1], textures[1], materials[0], { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -90.0f }, { 10000.0f, 10000.0f, 10000.0f }));

	objects.push_back(new model(meshes[2], textures[2], materials[0], { 0.0f, -50.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 10.0f, 5.0f, 10.0f }));

	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 0.0f, 0.0f }));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, {1.0f, 1.0f, 1.0f}, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 5.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f }, objects[2]));

	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, 10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 00.0f, 10.0f, 00.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));

	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, 10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, -10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, -10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, 0.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, -10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, 10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, -10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, -10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 10.0f, 10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));

	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, -10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, -10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, -10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 0.0f, 0.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { -10.0f, 0.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));
	objects.push_back(new model(meshes[0], textures[0], materials[0], { 00.0f, -10.0f, 00.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, objects[2]));

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

void renderer::drawString(std::string text, Vector2<float>* position) {
	glDisable(GL_DEPTH_TEST);
	glRasterPos2f(position->x, position->y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
	glEnable(GL_DEPTH_TEST);
}

void renderer::display(int deltaTime) {
	// clear the screen
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);

	drawVector(objects);
	glDisable(GL_LIGHTING);

	lastFrame += (float)deltaTime / 1000.0f;

	std::cout << deltaTime << std::endl;

	if (lastFrame > 1.0f) {
		fps = framesSinceLastFrame;
		framesSinceLastFrame = 0;
		lastFrame = 0.0f;
	}


	Vector2<float> pos = { 0.0f, 0.0f };
	drawString("WASD: Camera Movement", &pos);

	pos.y -= 1.0f;
	drawString("IJKL: Object Movement", &pos);

	pos.y -= 1.0f;
	drawString("Objects: " + std::to_string(objects.size()), &pos);

	pos.y -= 1.0f;
	drawString("FPS: " + std::to_string(fps), &pos);

	frame++;
	framesSinceLastFrame++;
	glutSwapBuffers();
}

void renderer::updateVector(std::vector<object*> objs)
{
	// starts at 1 cause 0 is skybox
	for (int i = 2; i < objs.size(); i++)
	{
		object* obj = objs[i];

		obj->setRotation(frame, 0, 0);

		obj->update();
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

	cam->setPitch(pitch - (static_cast<float>(mouseDelta.y) * CAMERA_SENSITIVITY * static_cast<float>(deltaTime) / 1000.0f));
	cam->setYaw(yaw + (static_cast<float>(mouseDelta.x) * CAMERA_SENSITIVITY * static_cast<float>(deltaTime) / 1000.0f));

	Vector2<int> MousePosition = controller->getMousePosition();

	if ((MousePosition.x < MOUSE_BORDER || MousePosition.x > WINDOW_WIDTH - MOUSE_BORDER) || (MousePosition.y < MOUSE_BORDER || MousePosition.y > WINDOW_HEIGHT - MOUSE_BORDER)) {
		controller->setMouseDelta({ 0 });
		controller->setMousePosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
		glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}


	cam->update(controller->getInputVector());

	Vector3<float> position = objects[2]->getPosition();
	float x = position.x;
	float y = position.y;
	float z = position.z;

	if (controller->getKeyState('i')) {
		z += 1.0f;
		z += 1.0f;
	}

	if (controller->getKeyState('j')) {
		x -= 1.0f;
	}

	if (controller->getKeyState('k')) {
		z -= 1.0f;
	}

	if (controller->getKeyState('l')) {
		x += 1.0f;
	}

	if (controller->getKeyState('u')) {
		y += 1.0f;
	}

	if (controller->getKeyState('o')) {
		y -= 1.0f;
	}

	objects[2]->setPosition(x, y, z);

	// Update other objects
	this->updateVector(objects);
	controller->setMouseDelta({ 0 });
}

void renderer::idle() {
	//std::cout << "idle" << std::endl;
}

// i: 105
// j: 106
// k: 107
// l: 108

void renderer::keyboard(unsigned char key, int x, int y, bool state) {
	std::cout << (int)key << std::endl;
	controller->setKeyState(key, state);
}

void renderer::mouseButton(int button, int state, int x, int y) {
	controller->setMouseState(button, state, x, y);
}

void renderer::mouseMotion(int x, int y) {

	controller->updateMouseMotion(x, y);
}