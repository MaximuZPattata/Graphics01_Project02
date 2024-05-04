#include "sPhysicsProperties.h"



sPhysicsProperties::sPhysicsProperties(std::string meshType)
{
    if (meshType == "Sphere")
        sphereProps = new sSpherePhysicsProperties();
}

sPhysicsProperties::~sPhysicsProperties()
{
    delete sphereProps;
}

sSpherePhysicsProperties::sSpherePhysicsProperties()
{
    this->closestTriangleVertices[0] = glm::vec3(0.0f);
    this->closestTriangleVertices[1] = glm::vec3(0.0f);
    this->closestTriangleVertices[2] = glm::vec3(0.0f);

    this->velocity = glm::vec3(0.0f);
    this->acceleration = glm::vec3(0.0f);
    this->inverse_mass = 1.0 / 10.0;
}
