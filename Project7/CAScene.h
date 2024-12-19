#pragma once

#include "CAVulkanState.h"
#include "CAFigure.h"
#include "CABalljoint.h"

class CAScene {
public:
	CAScene(CAVulkanState* vulkan);
	~CAScene();
	void finalize(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void update(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);

private:
	CAFigure* ground;
	CAFigure* column;
	CAFigure* cross;
	CABalljoint* armL;
	CABalljoint* armR;
	float angle;
};

