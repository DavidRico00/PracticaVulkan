#pragma once

#include "CASkeleton.h"

struct KeyFrame {
	float tiempo;
	std::vector<glm::vec2> direcion;
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
	void interpolacion_pos1(std::string nombre, glm::vec2 v);
	void interpolacion_pos2(std::string nombre, CABalljoint* ballJoint, glm::vec2 v);
};

