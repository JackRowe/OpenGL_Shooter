#pragma once

struct light {
	int id;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
};

struct material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
};