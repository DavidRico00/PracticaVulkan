#include "CABalljoint.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

//
// FUNCI�N: CABalljoint::CABalljoint()
//
// PROP�SITO: Construye una articulaci�n.
//
CABalljoint::CABalljoint(float l)
{
	length = l;

	location = glm::vec3(0.0f, 0.0f, 0.0f);
	dir = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);

	angles[0] = 0.0f;
	angles[1] = 0.0f;
	angles[2] = 0.0f;

}

//
// FUNCI�N: CABalljoint::~CABalljoint()
//
// PROP�SITO: Destruye una articulaci�n.
//
CABalljoint::~CABalljoint()
{
	delete joint;
	delete bone;
}

//
// FUNCI�N: CABalljoint::ComputeMatrix()
//
// PROP�SITO: Crea la matriz de transformaci�n a partir de la posici�n, la orientaci�n y la pose.
//
void CABalljoint::ComputeMatrix()
{
	// Formato glm::mat4[column][row]
	glm::mat4 jointm;
	jointm[0][0] = right.x;
	jointm[0][1] = right.y;
	jointm[0][2] = right.z;
	jointm[0][3] = 0.0;

	jointm[1][0] = up.x;
	jointm[1][1] = up.y;
	jointm[1][2] = up.z;
	jointm[1][3] = 0.0;

	jointm[2][0] = dir.x;
	jointm[2][1] = dir.y;
	jointm[2][2] = dir.z;
	jointm[2][3] = 0.0;

	jointm[3][0] = location.x;
	jointm[3][1] = location.y;
	jointm[3][2] = location.z;
	jointm[3][3] = 1.0;

	float cx = (float)cos(glm::radians(angles[0]));
	float sx = (float)sin(glm::radians(angles[0]));
	float cy = (float)cos(glm::radians(angles[1]));
	float sy = (float)sin(glm::radians(angles[1]));
	float cz = (float)cos(glm::radians(angles[2]));
	float sz = (float)sin(glm::radians(angles[2]));

	glm::mat4 posem;
	posem[0][0] = cz * cy;
	posem[1][0] = -sz * cx + cz * sy*sx;
	posem[2][0] = sz * sx + cz * sy*cx;
	posem[3][0] = 0;

	posem[0][1] = sz * cy;
	posem[1][1] = cz * cx + sz * sy*sx;
	posem[2][1] = -cz * sx + sz * sy*cx;
	posem[3][1] = 0;

	posem[0][2] = -sy;
	posem[1][2] = cy * sx;
	posem[2][2] = cy * cx;
	posem[3][2] = 0;

	posem[0][3] = 0;
	posem[1][3] = 0;
	posem[2][3] = 0;
	posem[3][3] = 1;

	glm::mat4 matrix = jointm * posem;

	joint->setLocation(matrix);
	glm::mat4 mm = glm::translate(matrix, glm::vec3(0.0f, 0.0f, length / 2));
	bone->setLocation(mm);
}

//
// FUNCI�N: CABalljoint::createBuffers(CAVulkanState* vulkan)
//
// PROP�SITO: Inicializa las piezas de la figura
//
void CABalljoint::initialize(CAVulkanState* vulkan)
{
	CAMaterial jointMat = {};
	jointMat.Ka = glm::vec3(1.0f, 0.0f, 0.0f);
	jointMat.Kd = glm::vec3(1.0f, 0.0f, 0.0f);
	jointMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	jointMat.Shininess = 16.0f;

	joint = new CASphere(10, 20, 0.1f);
	joint->initialize(vulkan);
	joint->setMaterial(jointMat);

	CAMaterial boneMat = {};
	boneMat.Ka = glm::vec3(0.0f, 0.0f, 0.8f);
	boneMat.Kd = glm::vec3(0.0f, 0.0f, 0.8f);
	boneMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	boneMat.Shininess = 16.0f;

	bone = new CACylinder(2, 10, 0.05f, length / 2);
	bone->initialize(vulkan);
	bone->setMaterial(boneMat);

	ComputeMatrix();
}

//
// FUNCI�N: CABalljoint::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
//
// PROP�SITO: Actualiza las variables uniformes
//
void CABalljoint::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
{
	joint->updateUniformBuffers(vulkan, view, projection);
	bone->updateUniformBuffers(vulkan, view, projection);
}

//
// FUNCI�N: CABalljoint::finalize(CAVulkanState* vulkan)
//
// PROP�SITO: Destruye los buffers de las piezas
//
void CABalljoint::finalize(CAVulkanState* vulkan)
{
	joint->finalize(vulkan);
	bone->finalize(vulkan);
}

//
// FUNCI�N: CABalljoint::setLocation(glm::vec3 loc)
//
// PROP�SITO: Asigna la posici�n de la articulaci�n
//
void CABalljoint::setLocation(glm::vec3 loc)
{
	location = loc;
	ComputeMatrix();
}

//
// FUNCI�N: CABalljoint::setOrientation(glm::vec3 nDir, glm::vec3 nUp)
//
// PROP�SITO: Asigna la orientaci�n de la articulaci�n (con pose 0,0,0).
//
void CABalljoint::setOrientation(glm::vec3 nDir, glm::vec3 nUp)
{
	dir = nDir;
	up = nUp;
	right = glm::cross(up, dir);
	ComputeMatrix();
}

//
// FUNCI�N: CABalljoint::setPose()
//
// PROP�SITO: Asigna la rotaci�n de la articulaci�n
//
void CABalljoint::setPose(float xrot, float yrot, float zrot)
{
	angles[0] = xrot;
	angles[1] = yrot;
	angles[2] = zrot;
	ComputeMatrix();
}

//
// FUNCI�N: CABalljoint::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
//
// PROP�SITO: A�ade los comandos de dibujo
//
void CABalljoint::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
	joint->addCommands(vulkan, commandBuffer, index);
	bone->addCommands(vulkan, commandBuffer, index);
}

//
// FUNCI�N: CABalljoint::setLight(CALight l)
//
// PROP�SITO: Asigna las propiedades de la luz
//
void CABalljoint::setLight(CALight l)
{
	joint->setLight(l);
	bone->setLight(l);
}