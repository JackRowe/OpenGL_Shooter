#pragma once

#include <iostream>
#include <vector>

#include "vectors.h"
#include "constants.h"

class object
{
private:
	Vector3<float> position = { 0.0f };
	Vector3<float> rotation = { 0.0f };
	Vector3<float> scale = { 1.0f };
	Vector3<float> velocity = { 0.0f };

	object* parent = nullptr;
	std::vector<object*> children = {};

	bool anchored = true;
public:
	object(
		const Vector3<float>& newPosition = { 0.0f },
		const Vector3<float>& newRotation = { 0.0f },
		const Vector3<float>& newScale = { 1.0f },
		object* newParent = nullptr
	);
	~object() {};

	virtual void draw();
	virtual void update();

	void setPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; };
	void setRotation(float x, float y, float z) { rotation.x = x; rotation.y = y; rotation.z = z; };
	void setScale(float x, float y, float z) { scale.x = x; scale.y = y; scale.z = z; };
	void setVelocity(float x, float y, float z) { velocity.x = x; velocity.y = y; velocity.z = z; };

	void setAnchored(bool state) { anchored = state; };

	Vector3<float> getPosition() { return position; }
	Vector3<float> getRotation(){ return rotation; }
	Vector3<float> getScale() { return scale; }
	Vector3<float> getVeloicty() { return velocity; }

	const bool getAnchored() const { return anchored; };

	void setParent(object* newParent = nullptr) { parent = newParent; };
	object* getParent() { return parent; };

	void addChild(object* newChild = nullptr) { children.push_back(newChild); };
	std::vector<object*>* getChildren() { return &children; };
};