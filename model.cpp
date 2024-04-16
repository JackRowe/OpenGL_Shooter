#include "model.h"

model::model(mesh* newMesh, texture* newTexture, const Vector3<float>& newPosition, const Vector3<float>& newRotation, const Vector3<float>& newScale, object* newParent) : object(newPosition, newRotation, newScale, newParent) {
	_mesh = newMesh;
	_texture = newTexture;
}

void model::draw() {
	if (_mesh == nullptr) return;

	std::vector<Vector3<float>>* vertices = _mesh->getVertices();
	std::vector<Vector2<float>>* uvs = _mesh->getUVs();
	std::vector<std::vector<Vector3<int>>>* faces = _mesh->getFaces();

	const Vector3<float>& position = getPosition();
	const Vector3<float>& rotation = getRotation();
	const Vector3<float>& scale = getScale();

	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);

	_texture == nullptr ? glDisable(GL_TEXTURE_2D) : glEnable(GL_TEXTURE_2D);

	for (int i = 0; i < faces->size(); i++) {
		std::vector<Vector3<int>> face = faces->at(i);

		glBegin(face.size() <= 3 ? GL_TRIANGLES : GL_QUADS);

		for (int j = 0; j < face.size(); j++)
		{
			Vector3<int> index = face[j];
			Vector3<float> vertex = vertices->at(index.x - 1);
			Vector2<float> uv = uvs->at(index.y - 1);

			glTexCoord2f(uv.x, uv.y);
			glVertex3f(vertex.x * scale.x, vertex.y * scale.y, vertex.z * scale.z);
		}

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void model::update() {
	
}