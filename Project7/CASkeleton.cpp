#include "CASkeleton.h"

#include <glm/gtc/matrix_transform.hpp>

CASkeleton::CASkeleton(std::string name, glm::vec3 offset_p, glm::vec3 eje_z, glm::vec3 eje_y, CAVulkanState* vulkan) {
    offset = offset_p;
    dir = glm::normalize(eje_z);
    up = glm::normalize(eje_y);
    right = glm::normalize(glm::cross(up, dir));
    this->location = glm::mat4(glm::vec4(right,0.0f), glm::vec4(up,0.0f), glm::vec4(dir,0.0f), glm::vec4(offset,1.0f));
    this->name = name;

    CABalljoint* pelvis = new CABalljoint(0.3f, "pelvis");
    pelvis->initialize(vulkan);
    pelvis->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    pelvis->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    CABalljoint* spine = new CABalljoint(0.4f, "spine");
    spine->initialize(vulkan);
    pelvis->anadirHijo(spine);
    spine->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    spine->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* neck = new CABalljoint(0.35f, "neck");
    neck->initialize(vulkan);
    spine->anadirHijo(neck);
    neck->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    neck->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* clavicleL = new CABalljoint(0.25f, "clavicle_l");
    clavicleL->initialize(vulkan);
    spine->anadirHijo(clavicleL);
    clavicleL->setLocation(glm::vec3(-0.05f, 0.0f, -0.05f));
    clavicleL->setOrientation(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* shoulderL = new CABalljoint(0.35f, "shoulder_l");
    shoulderL->initialize(vulkan);
    clavicleL->anadirHijo(shoulderL);
    shoulderL->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    shoulderL->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    CABalljoint* elbowL = new CABalljoint(0.30f, "elbow_l");
    elbowL->initialize(vulkan);
    shoulderL->anadirHijo(elbowL);
    elbowL->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    elbowL->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* wristL = new CABalljoint(0.20f, "wrist_l");
    wristL->initialize(vulkan);
    elbowL->anadirHijo(wristL);
    wristL->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    wristL->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* clavicleR = new CABalljoint(0.25f, "clavicle_r");
    clavicleR->initialize(vulkan);
    spine->anadirHijo(clavicleR);
    clavicleR->setLocation(glm::vec3(0.05f, 0.0f, -0.05f));
    clavicleR->setOrientation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* shoulderR = new CABalljoint(0.35f, "shoulder_r");
    shoulderR->initialize(vulkan);
    clavicleR->anadirHijo(shoulderR);
    shoulderR->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    shoulderR->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    CABalljoint* elbowR = new CABalljoint(0.30f, "elbow_r");
    elbowR->initialize(vulkan);
    shoulderR->anadirHijo(elbowR);
    elbowR->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    elbowR->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* wristR = new CABalljoint(0.20f, "wrist_r");
    wristR->initialize(vulkan);
    elbowR->anadirHijo(wristR);
    wristR->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    wristR->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* hipL = new CABalljoint(0.2f, "hip_l");
    hipL->initialize(vulkan);
    hipL->setLocation(glm::vec3(0.05f, -0.05f, 0.0f));
    hipL->setOrientation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* legL = new CABalljoint(0.5f, "leg_l");
    legL->initialize(vulkan);
    hipL->anadirHijo(legL);
    legL->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    legL->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    CABalljoint* kneeL = new CABalljoint(0.4f, "knee_l");
    kneeL->initialize(vulkan);
    legL->anadirHijo(kneeL);
    kneeL->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    kneeL->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* ankleL = new CABalljoint(0.25f, "ankle_l");
    ankleL->initialize(vulkan);
    kneeL->anadirHijo(ankleL);
    ankleL->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    ankleL->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    CABalljoint* hipR = new CABalljoint(0.2f, "hip_r");
    hipR->initialize(vulkan);
    hipR->setLocation(glm::vec3(-0.05f, -0.05f, 0.0f));
    hipR->setOrientation(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    CABalljoint* legR = new CABalljoint(0.5f, "leg_r");
    legR->initialize(vulkan);
    hipR->anadirHijo(legR);
    legR->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    legR->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    CABalljoint* kneeR = new CABalljoint(0.4f, "knee_r");
    kneeR->initialize(vulkan);
    legR->anadirHijo(kneeR);
    kneeR->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    kneeR->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
   // kneeR->setPose(90.0f, 0.0f, 0.0f);      //MOVER RODILLA HACIA ATRAS

    CABalljoint* ankleR = new CABalljoint(0.25f, "ankle_r");
    ankleR->initialize(vulkan);
    kneeR->anadirHijo(ankleR);
    ankleR->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
    ankleR->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    this->articulaciones.push_back(pelvis);
    this->articulaciones.push_back(hipL);
    this->articulaciones.push_back(hipR);

  
    for (int i = 0; i < articulaciones.size(); i++)
        articulaciones[i]->setParentLocation(location);

}


CASkeleton::~CASkeleton()
{
    articulaciones.clear();
}


void CASkeleton::initialize(CAVulkanState* vulkan)
{
   // location = glm::mat4(1.0f);

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

std::vector<CABalljoint*> CASkeleton::getHijos()
{
    return articulaciones;
}

void CASkeleton::resetLocation()
{
    location = glm::mat4(1.0f);
    
    for (int i = 0; i < articulaciones.size(); i++) 
        articulaciones[i]->setParentLocation(location);
}

void CASkeleton::setLocation(glm::mat4 m)
{
    location = glm::mat4(m);
    
    for (int i = 0; i < articulaciones.size(); i++)
        articulaciones[i]->setParentLocation(location);
}

void CASkeleton::translate(glm::vec3 t)
{
    location = glm::translate(location, t);
    
    for (int i = 0; i < articulaciones.size(); i++)
        articulaciones[i]->setParentLocation(location);
}

void CASkeleton::rotate(float angle, glm::vec3 axis)
{
    location = glm::rotate(location, glm::radians(angle), axis);
    
    for (int i = 0; i < articulaciones.size(); i++)
        articulaciones[i]->setParentLocation(location);
}