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
	KeyFrame kf;

	kf.tiempo = 0.0f;
	kf.direccion = {
	glm::vec2(0.0f, 0.0f),		//leg_l
	glm::vec2(0.0f, 0.0f),		//knee_l
	glm::vec2(0.0f, 0.0f),		//leg_r
	glm::vec2(0.0f, 0.0f),		//knee_r
	glm::vec2(0.0f, 0.0f),		//spine
	glm::vec2(0.0f, 0.0f),		//pelvis
	glm::vec2(0.0f, 0.0f),		//shoulder_l
	glm::vec2(0.0f, 0.0f),		//elbow_l
	glm::vec2(0.0f, 0.0f),		//shoulder_r
	glm::vec2(0.0f, 0.0f)		//elbow_r
	};
	addKeyFrame(kf);

	kf.tiempo = 0.5f;
	kf.direccion = {
	glm::vec2(-90.0f, 0.0f),	//leg_l
	glm::vec2(100.0f, 0.0f),	//knee_l
	glm::vec2(20.0f, 0.0f),		//leg_r
	glm::vec2(0.0f, 0.0f),		//knee_r
	glm::vec2(-20.0f, 0.0f),	//spine
	glm::vec2(-10.0f, 0.0f),	//pelvis
	glm::vec2(0.0f, 0.0f),		//shoulder_l
	glm::vec2(0.0f, 0.0f),		//elbow_l
	glm::vec2(0.0f, 0.0f),		//shoulder_r
	glm::vec2(0.0f, 0.0f)		//elbow_r
	};
	addKeyFrame(kf);
	
	kf.tiempo = 1.0f;
	kf.direccion = {
	glm::vec2(-90.0f, 0.0f),	//leg_l
	glm::vec2(0.0f, 0.0f),		//knee_l
	glm::vec2(30.0f, -70.0f),	//leg_r
	glm::vec2(100.0f, 0.0f),	//knee_r
	glm::vec2(-50.0f, 0.0f),	//spine
	glm::vec2(-20.0f, 0.0f),	//pelvis
	glm::vec2(0.0f, 0.0f),		//shoulder_l
	glm::vec2(0.0f, 0.0f),		//elbow_l
	glm::vec2(0.0f, 0.0f),		//shoulder_r
	glm::vec2(0.0f, 0.0f)		//elbow_r
	};
	addKeyFrame(kf);

	kf.tiempo = 1.5f;
	kf.direccion = {
	glm::vec2(-45.0f, 0.0f),	//leg_l
	glm::vec2(0.0f, 0.0f),		//knee_l
	glm::vec2(-30.0f, -10.0f),	//leg_r
	glm::vec2(120.0f, 0.0f),	//knee_r
	glm::vec2(-20.0f, 0.0f),	//spine
	glm::vec2(-10.0f, 0.0f),	//pelvis
	glm::vec2(0.0f, 0.0f),		//shoulder_l
	glm::vec2(0.0f, 0.0f),		//elbow_l
	glm::vec2(0.0f, 0.0f),		//shoulder_r
	glm::vec2(0.0f, 0.0f)		//elbow_r
	};
	addKeyFrame(kf);

	kf.tiempo = 1.8f;
	kf.direccion = {
	glm::vec2(0.0f, 0.0f),		//leg_l
	glm::vec2(0.0f, 0.0f),		//knee_l
	glm::vec2(0.0f, 0.0f),		//leg_r
	glm::vec2(0.0f, 0.0f),		//knee_r
	glm::vec2(0.0f, 0.0f),		//spine
	glm::vec2(0.0f, 0.0f),		//pelvis
	glm::vec2(0.0f, 0.0f),		//shoulder_l
	glm::vec2(0.0f, 0.0f),		//elbow_l
	glm::vec2(0.0f, 0.0f),		//shoulder_r
	glm::vec2(0.0f, 0.0f)		//elbow_r
	};
	addKeyFrame(kf);

}

void Animation::addKeyFrame(KeyFrame kf)
{
	this->vKeyFrame.push_back({
		kf.tiempo, kf.direccion});
}

void Animation::animacion(float tiempo)
{
	for (int i = 0; i < vKeyFrame.size()-1; i++)
	{
		if (vKeyFrame[i].tiempo <= tiempo && tiempo <= vKeyFrame[i+1].tiempo)
		{
			float intT = (tiempo - vKeyFrame[i].tiempo) / (vKeyFrame[i+1].tiempo - vKeyFrame[i].tiempo);
						
			std::vector<glm::vec2> ini = vKeyFrame[i].direccion;
			std::vector<glm::vec2> fin = vKeyFrame[i+1].direccion;


			for (int j = 0; j < vKeyFrame[i].direccion.size(); j++)
			{
				glm::vec2 pos = ini[j] + intT * (fin[j] - ini[j]);

				switch (j)
				{
				case 0:
					interpolacion_pose("leg_l", NULL, pos);
					break;

				case 1:
					interpolacion_pose("knee_l", NULL, pos);
					break;

				case 2:
					interpolacion_pose("leg_r", NULL, pos);
					break;

				case 3:
					interpolacion_pose("knee_r", NULL, pos);
					break;

				case 4:
					interpolacion_pose("spine", NULL, pos);
					break;

				case 5:
					interpolacion_pose("pelvis", NULL, pos);
					break;

				case 6:
					interpolacion_pose("shoulder_l", NULL, pos);
					break;

				case 7:
					interpolacion_pose("elbow_l", NULL, pos);
					break;

				case 8:
					interpolacion_pose("shoulder_r", NULL, pos);
					break;

				case 9:
					interpolacion_pose("elbow_r", NULL, pos);
					break;

				default:
					break;
				}
			}
		}
	}
}

void Animation::interpolacion_pose(std::string nombre, CABalljoint* ballJoint, glm::vec2 v) 
{
	std::vector<CABalljoint*> art;

	if(ballJoint == NULL)
		art = this->esqueleto->getHijos();
	else
		art = ballJoint->getHijos();

	for (int i = 0; i < art.size(); i++)
	{
		if (art[i]->getName() == nombre)
		{
			art[i]->setPose(v.x, v.y, 0.0f);
			break;
		}

		interpolacion_pose(nombre, art[i], v);
	}

}