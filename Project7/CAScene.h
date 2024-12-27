#pragma once

#include "CAVulkanState.h"
#include "CAFigure.h"
#include "CABalljoint.h"
#include "CASkeleton.h"
#include "Animation.h"

class CAScene {
public:
	CAScene(CAVulkanState* vulkan);
	~CAScene();
	void finalize(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void update(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection);
	void setInicioToCero();

	Animation* getAnimation();

private:
	CAFigure* ground;
	CASkeleton* esqueleto;
	Animation* animacion;
	float inicio = 0.0f;
};

