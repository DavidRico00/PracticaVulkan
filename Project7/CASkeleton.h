#pragma once

#include "CABalljoint.h"

class CASkeleton {
protected:
	glm::mat4 location;
	CALight light;
	CAMaterial material;

	std::string name;
	glm::vec3 offset;
	glm::vec3 dir;
	glm::vec3 up;
	glm::vec3 right;
	std::vector<CABalljoint*> articulaciones;


public:
	CASkeleton(std::string name, glm::vec3 offset, glm::vec3 up, glm::vec3 dir, CAVulkanState* vulkan);
	~CASkeleton();
	void initialize(CAVulkanState* vulkan);
	void finalize(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);
	void resetLocation();
	void setLocation(glm::mat4 m);
	void translate(glm::vec3 t);
	void rotate(float angle, glm::vec3 axis);
	void setLight(CALight l);
	void setMaterial(CAMaterial m);

private:
	CAUniformBuffer transformBuffer;
	CAUniformBuffer lightBuffer;
	CAUniformBuffer materialBuffer;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
};