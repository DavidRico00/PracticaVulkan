#pragma once

#include "CAVulkanState.h"
#include "CAFigure.h"
#include "CABalljoint.h"
#include "CASkeleton.h"

class CAScene {
public:
	CAScene(CAVulkanState* vulkan);
	~CAScene();
	void finalize(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void update(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);

private:
	CAFigure* ground;
	CASkeleton* esqueleto;
};

