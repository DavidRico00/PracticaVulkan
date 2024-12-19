#pragma once

#include "CASphere.h"
#include "CACylinder.h"
#include <glm\glm.hpp>

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

public:
	CABalljoint(float length);
	~CABalljoint();
	void initialize(CAVulkanState* vulkan);
	void finalize(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);

	void setLight(CALight l);
	void setLocation(glm::vec3 loc);
	void setOrientation(glm::vec3 nDir, glm::vec3 nUp);
	void setPose(float xrot, float yrot, float zrot);
};


