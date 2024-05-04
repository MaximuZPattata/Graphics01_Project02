#ifndef _cPhysics_HG_
#define _cPhysics_HG_

#include "sPhysicsProperties.h"
#include "cMesh.h"
#include "cVAOManager.h"	
#include <vector>

class cPhysics
{
public:

	cPhysics();

	~cPhysics();

	void setVAOManager(cVAOManager* pTheMeshManager);

	bool CheckForPlaneCollision(sModelDrawInfo* drawInfo, cMesh* groundMesh, sPhysicsProperties* spherePhysicalProps);

	bool CheckForSphereCollision(sPhysicsProperties* sphere1PhysicalProps, sPhysicsProperties* sphere2PhysicalProps);

	void PlaneCollisionResponse(sPhysicsProperties* physicsModel, double deltaTime);

	void SphereCollisionResponse(sPhysicsProperties* firstSphereModel, sPhysicsProperties* secondSphereModel);

	void EulerForwardIntegration(sPhysicsProperties* physicsModel, double deltaTime);

private:

	cVAOManager* m_pMeshManager = NULL;

	glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);

};

#endif 