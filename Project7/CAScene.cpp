#include "CAScene.h"
#include "CATransform.h"
#include "CACylinder.h"
#include "CASphere.h"
#include "CAGround.h"
#include "CABalljoint.h"
#include <iostream>

//
// FUNCIÓN: CAScene::CAScene(CAVulkanState* vulkan)
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CAScene::CAScene(CAVulkanState* vulkan)
{
	CALight light = {};
	light.Ldir = glm::normalize(glm::vec3(1.0f, -0.8f, -0.7f));
	light.La = glm::vec3(0.2f, 0.2f, 0.2f);
	light.Ld = glm::vec3(0.8f, 0.8f, 0.8f);
	light.Ls = glm::vec3(1.0f, 1.0f, 1.0f);

	CAMaterial groundMat = {};
	groundMat.Ka = glm::vec3(0.0f, 0.3f, 0.0f);
	groundMat.Kd = glm::vec3(0.0f, 0.3f, 0.0f);
	groundMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	groundMat.Shininess = 16.0f;

	ground = new CAGround(5.0f, 5.0f);
	ground->initialize(vulkan);
	ground->setLight(light);
	ground->setMaterial(groundMat);

	CAMaterial blueMat = {};
	blueMat.Ka = glm::vec3(0.0f, 0.0f, 0.8f);
	blueMat.Kd = glm::vec3(0.0f, 0.0f, 0.8f);
	blueMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	blueMat.Shininess = 16.0f;

	column = new CACylinder(2, 10, 0.05f, 0.75f);
	column->initialize(vulkan);
	column->translate(glm::vec3(0.0f, 0.75f, 0.0f));
	column->rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	column->setLight(light);
	column->setMaterial(blueMat);

	cross = new CACylinder(2, 10, 0.05f, 0.25f);
	cross->initialize(vulkan);
	cross->translate(glm::vec3(0.0f, 1.25f, 0.0f));
	cross->rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	cross->setLight(light);
	cross->setMaterial(blueMat);

	armL = new CABalljoint(0.4f);
	armL->initialize(vulkan);
	armL->setLocation(glm::vec3(0.25f, 1.25f, 0.0f));
	armL->setOrientation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	armL->setLight(light);

	armR = new CABalljoint(0.4f);
	armR->initialize(vulkan);
	armR->setLocation(glm::vec3(-0.25f, 1.25f, 0.0f));
	armR->setOrientation(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	armR->setLight(light);

	angle = 0.0;
}

//
// FUNCIÓN: CAScene::~CAScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CAScene::~CAScene()
{
	delete ground;
	delete column;
	delete cross;
	delete armL;
	delete armR;
}

//
// FUNCIÓN: CAScene::finalize(CAVulkanState* vulkan)
//
// PROPÓSITO: Destruyelos buffers de las figuras que forman la escena
//
void CAScene::finalize(CAVulkanState* vulkan)
{
	ground->finalize(vulkan);
	column->finalize(vulkan);
	cross->finalize(vulkan);
	armL->finalize(vulkan);
	armR->finalize(vulkan);
}

//
// FUNCIÓN: CAScene::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAScene::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
	ground->addCommands(vulkan, commandBuffer, index);
	column->addCommands(vulkan, commandBuffer, index);
	cross->addCommands(vulkan, commandBuffer, index);
	armL->addCommands(vulkan, commandBuffer, index);
	armR->addCommands(vulkan, commandBuffer, index);
}

//
// FUNCIÓN: CAScene::	void update(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
// 
// PROPÓSITO: Actualiza los datos para dibujar la escena
//
void CAScene::update(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
{
	angle += 1.0f;
	if (angle >= 90.0f) angle = 0.0f;
	armL->setPose(angle, 0.0f, 0.0f);
	armR->setPose(0.0f, angle, 0.0f);

	ground->updateUniformBuffers(vulkan, view, projection);
	column->updateUniformBuffers(vulkan, view, projection);
	cross->updateUniformBuffers(vulkan, view, projection);
	armL->updateUniformBuffers(vulkan, view, projection);
	armR->updateUniformBuffers(vulkan, view, projection);
}
