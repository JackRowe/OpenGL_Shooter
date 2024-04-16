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

	object* parent = nullptr;
	std::vector<object*> children = {};
public:
	object(
		const Vector3<float>& newPosition = { 0.0f },
		const Vector3<float>& newRotation = { 0.0f },
		const Vector3<float>& newScale = { 1.0f },
		object* newParent = nullptr
	);
	~object() {};

	virtual void draw() {};
	virtual void update() {};

	const Vector3<float>& getPosition() const { return position; }
	const Vector3<float>& getRotation() const { return rotation; }
	const Vector3<float>& getScale() const { return scale; }

	void setParent(object* newParent = nullptr) { parent = newParent; };
	object* getParent() { return parent; };

	void addChild(object* newChild = nullptr) { children.push_back(newChild); };
	std::vector<object*>* getChildren() { return &children; };
};