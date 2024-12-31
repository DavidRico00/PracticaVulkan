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

	esqueleto = new CASkeleton("body", glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), vulkan);
	esqueleto->initialize(vulkan);
	esqueleto->setLight(light);
	esqueleto->setMaterial(blueMat);

	animacion = new Animation(0.7f, esqueleto);
	animacion->crearAnimacion();
}

//
// FUNCIÓN: CAScene::~CAScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CAScene::~CAScene()
{
	delete ground;
	delete esqueleto;
}

//
// FUNCIÓN: CAScene::finalize(CAVulkanState* vulkan)
//
// PROPÓSITO: Destruyelos buffers de las figuras que forman la escena
//
void CAScene::finalize(CAVulkanState* vulkan)
{
	ground->finalize(vulkan);
	esqueleto->finalize(vulkan);
}

//
// FUNCIÓN: CAScene::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAScene::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
	ground->addCommands(vulkan, commandBuffer, index);
	esqueleto->addCommands(vulkan, commandBuffer, index);
}

//
// FUNCIÓN: CAScene::	void update(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
// 
// PROPÓSITO: Actualiza los datos para dibujar la escena
//
void CAScene::update(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
{
	ground->updateUniformBuffers(vulkan, view, projection);
	esqueleto->updateUniformBuffers(vulkan, view, projection);

	if (tiempo >= -0.2f && tiempo < 2.0f)
		this->tiempo += this->incremento;

	if (tiempo >= 2.0f)
		this->tiempo = 0.0f;

	if (tiempo <= -0.2f)
		this->tiempo = 1.9f;

	animacion->animacion(tiempo);
}

Animation* CAScene::getAnimation()
{
	return animacion;
}

void CAScene::modificarIncremento(float f)
{
	this->incremento = f;
}

void CAScene::setInicioToCero()
{
	this->tiempo = 0.0f;
}
