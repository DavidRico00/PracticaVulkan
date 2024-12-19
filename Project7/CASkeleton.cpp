#include "CASkeleton.h"

#include <glm/gtc/matrix_transform.hpp>

CASkeleton::CASkeleton(std::string name, glm::vec3 offset_p, glm::vec3 eje_y, glm::vec3 eje_z, CAVulkanState* vulkan) {
    offset = offset_p;
    dir = glm::normalize(eje_z);
    up = glm::normalize(eje_y);
    right = glm::normalize(glm::cross(up, dir));
    this->name = name;

    CABalljoint* pelvis = new CABalljoint(0.3f, "pelvis");
    pelvis->initialize(vulkan);
    pelvis->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    pelvis->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    CABalljoint* spine = new CABalljoint(0.4f, "spine");
    spine->initialize(vulkan);
    pelvis->anadirHijo(spine);

    CABalljoint* neck = new CABalljoint(0.35f, "neck");
    neck->initialize(vulkan);
    spine->anadirHijo(neck);

    CABalljoint* clavicleL = new CABalljoint(0.25f, "clavicle_l");
    clavicleL->initialize(vulkan);
    clavicleL->setLocation(glm::vec3(-0.05f, 0.0f, -0.05f));
    clavicleL->setOrientation(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    spine->anadirHijo(clavicleL);

    CABalljoint* shoulderL = new CABalljoint(0.35f, "shoulder_l");
    shoulderL->initialize(vulkan);
    clavicleL->anadirHijo(shoulderL);

    CABalljoint* elbowL = new CABalljoint(0.30f, "elbow_l");
    elbowL->initialize(vulkan);
    shoulderL->anadirHijo(elbowL);

    CABalljoint* wristL = new CABalljoint(0.20f, "wrist_l");
    wristL->initialize(vulkan);
    elbowL->anadirHijo(wristL);

    CABalljoint* clavicleR = new CABalljoint(0.25f, "clavicle_r");
    clavicleR->initialize(vulkan);
    clavicleR->setLocation(glm::vec3(0.05f, 0.0f, -0.05f));
    clavicleR->setOrientation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    spine->anadirHijo(clavicleR);

    CABalljoint* shoulderR = new CABalljoint(0.35f, "shoulder_r");
    shoulderR->initialize(vulkan);
    clavicleR->anadirHijo(shoulderR);

    CABalljoint* elbowR = new CABalljoint(0.30f, "elbow_r");
    elbowR->initialize(vulkan);
    shoulderR->anadirHijo(elbowR);

    CABalljoint* wristR = new CABalljoint(0.20f, "wrist_r");
    wristR->initialize(vulkan);
    elbowR->anadirHijo(wristR);

    CABalljoint* hipL = new CABalljoint(0.2f, "hip_l");
    hipL->initialize(vulkan);
    hipL->setLocation(glm::vec3(0.05f, -0.05f, 0.0f));
    hipL->setOrientation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* legL = new CABalljoint(0.5f, "leg_l");
    legL->initialize(vulkan);
    hipL->anadirHijo(legL);

    CABalljoint* kneeL = new CABalljoint(0.4f, "knee_l");
    kneeL->initialize(vulkan);
    legL->anadirHijo(kneeL);

    CABalljoint* ankleL = new CABalljoint(0.25f, "ankle_l");
    ankleL->initialize(vulkan);
    kneeL->anadirHijo(ankleL);

    CABalljoint* hipR = new CABalljoint(0.2f, "hip_r");
    hipR->initialize(vulkan);
    hipR->setLocation(glm::vec3(-0.05f, -0.05f, 0.0f));
    hipR->setOrientation(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* legR = new CABalljoint(0.5f, "leg_r");
    legR->initialize(vulkan);
    legR->setPose(90.0f, 0.0f, 0.0f);
    hipR->anadirHijo(legR);

    CABalljoint* kneeR = new CABalljoint(0.4f, "knee_r");
    kneeR->initialize(vulkan);
    legR->anadirHijo(kneeR);

    CABalljoint* ankleR = new CABalljoint(0.25f, "ankle_r");
    ankleR->initialize(vulkan);
    kneeR->anadirHijo(ankleR);

    this->articulaciones.push_back(pelvis);
    this->articulaciones.push_back(hipL);
    this->articulaciones.push_back(hipR);
}


CASkeleton::~CASkeleton()
{
    articulaciones.clear();
}


void CASkeleton::initialize(CAVulkanState* vulkan)
{
    location = glm::mat4(1.0f);

    /*
    for (int i = 0; i < articulaciones.size(); i++) {
        articulaciones[i]->initialize(vulkan);
    }
    */

    size_t transformBufferSize = sizeof(CATransform);
    vulkan->createUniformBuffer(transformBufferSize, &transformBuffer);

    size_t lightBufferSize = sizeof(CALight);
    vulkan->createUniformBuffer(lightBufferSize, &lightBuffer);

    size_t materialBufferSize = sizeof(CAMaterial);
    vulkan->createUniformBuffer(materialBufferSize, &materialBuffer);


    CAUniformBuffer* buffers[] = { &transformBuffer, &lightBuffer, &materialBuffer };
    size_t sizes[] = { transformBufferSize, lightBufferSize, materialBufferSize };

    vulkan->createDescriptorSets(&descriptorPool, &descriptorSets, buffers, sizes, 3);
}

void CASkeleton::finalize(CAVulkanState* vulkan)
{
    for (int i = 0; i < articulaciones.size(); i++) {
        articulaciones[i]->initialize(vulkan);
    }

    articulaciones.clear();

    vulkan->destroyUniformBuffer(transformBuffer);
    vulkan->destroyUniformBuffer(lightBuffer);
    vulkan->destroyUniformBuffer(materialBuffer);
    vulkan->destroyDescriptorSets(descriptorPool, descriptorSets);
}

void CASkeleton::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan->getPipelineLayout(), 0, 1, &descriptorSets[index], 0, nullptr);

    for (int i = 0; i < articulaciones.size(); i++) {
        articulaciones[i]->addCommands(vulkan, commandBuffer, index);
    }
}

void CASkeleton::updateUniformBuffers(CAVulkanState* vulkan, glm::mat4 view, glm::mat4 projection)
{
    CATransform transform;
    transform.MVP = projection * view * location;
    transform.ModelViewMatrix = view * location;
    transform.ViewMatrix = view;

    vulkan->updateUniformBuffer(sizeof(CATransform), &transform, transformBuffer);
    vulkan->updateUniformBuffer(sizeof(CALight), &light, lightBuffer);
    vulkan->updateUniformBuffer(sizeof(CAMaterial), &material, materialBuffer);

    for (int i = 0; i < articulaciones.size(); i++) {
        articulaciones[i]->updateUniformBuffers(vulkan, view, projection);
    }
}

void CASkeleton::setLight(CALight l)
{
    this->light = l;
    for (int i = 0; i < articulaciones.size(); i++) {
        articulaciones[i]->setLight(l);
    }
}

void CASkeleton::setMaterial(CAMaterial m)
{
    this->material = m;
}

void CASkeleton::resetLocation()
{
    location = glm::mat4(1.0f);
}

void CASkeleton::setLocation(glm::mat4 m)
{
    location = glm::mat4(m);
}

void CASkeleton::translate(glm::vec3 t)
{
    location = glm::translate(location, t);
}

void CASkeleton::rotate(float angle, glm::vec3 axis)
{
    location = glm::rotate(location, glm::radians(angle), axis);
}