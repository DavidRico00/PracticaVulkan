#include "Animation.h"

Animation::Animation(float t, CASkeleton* e)
{
	this->tDuracion = t;
	this->esqueleto = e;
}

Animation::~Animation()
{
	delete this->esqueleto;
}

void Animation::crearAnimacion()
{
	KeyFrame kf1, kf2;

	kf1.tiempo = 0.7f;
	kf1.direcion = {
	glm::vec2(0.0f, 0.0f),
	glm::vec2(90.0f, 0.0f),
	glm::vec2(0.0f, 0.0f),
	glm::vec2(-90.0f, 0.0f)
	};


	kf2.tiempo = 0.7f;
	kf2.direcion = {
	glm::vec2(0.0f, 0.0f),
	glm::vec2(-90.0f, 0.0f),
	glm::vec2(0.0f, 0.0f),
	glm::vec2(90.0f, 0.0f)
	};

	addKeyFrame(kf1);
	addKeyFrame(kf2);
}

void Animation::addKeyFrame(KeyFrame kf)
{
	this->vKeyFrame.push_back(kf);
}

void Animation::animacion(float tiempo)
{
	for (int i = 0; i < vKeyFrame.size()-1; i++)
	{
		if (vKeyFrame[i].tiempo <= tiempo && tiempo <= vKeyFrame[i+1].tiempo)
		{
			float intT = (tiempo - vKeyFrame[i].tiempo) / (vKeyFrame[i+1].tiempo - vKeyFrame[i].tiempo);
						
			std::vector<glm::vec2> ini = vKeyFrame[i].direcion;
			std::vector<glm::vec2> fin = vKeyFrame[i+1].direcion;


			for (int j = 0; j < vKeyFrame[i].direcion.size(); j++)
			{
				glm::vec2 pos = ini[j] + intT * (fin[j] - ini[j]);

				interpolacion_pos1("leg_l", pos);

				/*switch (j)
				{
				case 0:
					interpolacion_pos1("leg_l", pos);
					break;

				case 1:
					interpolacion_pos1("leg_R", pos);
					break;

				case 2:
					interpolacion_pos1("knee_r", pos);
					break;

				case 3:
					interpolacion_pos1("knee_l", pos);
					break;

				default:
					break;
				}*/
			}
		}
	}
}

void Animation::interpolacion_pos1(std::string nombre, glm::vec2 v)
{
	std::vector<CABalljoint*> art = this->esqueleto->getHijos();

	for (int i = 0; i < art.size(); i++)
	{
		if (art[i]->getName() == nombre)
		{
			art[i]->setPose(v.x, v.y, 0.0f);
		}
		
		interpolacion_pos2(nombre, art[i], v);
	}
}

void Animation::interpolacion_pos2(std::string nombre, CABalljoint* ballJoint, glm::vec2 v)
{
	std::vector<CABalljoint*> art = ballJoint->getHijos();

	for (int i = 0; i < art.size(); i++)
	{
		if (art[i]->getName() == nombre)
		{
			art[i]->setPose(v.x, v.y, 0.0f);
		}

		interpolacion_pos2(nombre, art[i], v);
	}
}