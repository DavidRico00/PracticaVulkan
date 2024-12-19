#pragma once

#include "CASphere.h"
#include "CACylinder.h"
#include <glm\glm.hpp>
#include <vector>
#include <string>

//
// CLASE: Balljoint
//
// DESCRIPCIÓN: Representa una articulación con 3 grados de libertad
// 
class CABalljoint {
private:
	GLfloat length;
	glm::vec3 location;
	glm::vec3 dir;
	glm::vec3 up;
	glm::vec3 right;
	GLfloat angles[3];
	CASphere* joint;
	CACylinder* bone;
	void ComputeMatrix();

	std::string nombre;
	std::vector<CABalljoint*> hijos;
	glm::mat2x3 limite;

public:
	CABalljoint(float length, std::string nombre);
	~CABalljoint();
	void initialize(CAVulkanState* vulkan);
	void finalize(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);

	void setLight(CALight l);
	void setLocation(glm::vec3 loc);
	void setOrientation(glm::vec3 nDir, glm::vec3 nUp);
	void setPose(float xrot, float yrot, float zrot);

	void anadirHijo(CABalljoint* c);
	void setLimitX(GLfloat min, GLfloat max);
	void setLimitY(GLfloat min, GLfloat max);
	void setLimitZ(GLfloat min, GLfloat max);
};


