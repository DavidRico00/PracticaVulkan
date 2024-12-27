#pragma once

#include "CASkeleton.h"

struct KeyFrame {
	float tiempo;
	std::vector<glm::vec2> direccion;
};

class Animation
{
private:
	float tDuracion;
	CASkeleton* esqueleto;
	std::vector<KeyFrame> vKeyFrame;

public:
	Animation(float t, CASkeleton* e);
	~Animation();

	void crearAnimacion();

	void addKeyFrame(KeyFrame kf);
	void animacion(float t);
	void interpolacion_pose(std::string nombre, CABalljoint* ballJoint, glm::vec2 v);
};

