#include "sModelDrawInfo.h"

unsigned int sModelDrawInfo::m_nextUniqueID = sModelDrawInfo::FIRST_UNIQUE_ID;

sModelDrawInfo::sModelDrawInfo()
{
	this->VAO_ID = 0;

	this->VertexBufferID = 0;
	this->VertexBuffer_Start_Index = 0;
	this->numberOfVertices = 0;

	this->IndexBufferID = 0;
	this->IndexBuffer_Start_Index = 0;
	this->numberOfIndices = 0;
	this->numberOfTriangles = 0;

	this->pVertices = 0;
	this->pIndices = 0;

	this->maxExtents_XYZ = glm::vec3(0.0f);
	this->minExtents_XYZ = glm::vec3(0.0f);
	this->deltaExtents_XYZ = glm::vec3(0.0f);

	this->maxExtent = 0.0f;

	this->m_UniqueID = sModelDrawInfo::m_nextUniqueID;
	sModelDrawInfo::m_nextUniqueID++;

	return;
}

unsigned int sModelDrawInfo::getUniqueID(void)
{
	return this->m_UniqueID;
}

void sModelDrawInfo::calcExtents(void)
{
	if (this->pVertices == NULL)
	{
		return;
	}

	sVertex* pCurrentVert = &(this->pVertices[0]);

	this->minExtents_XYZ.x = pCurrentVert->x;
	this->minExtents_XYZ.y = pCurrentVert->y;
	this->minExtents_XYZ.z = pCurrentVert->z;

	this->maxExtents_XYZ.x = pCurrentVert->x;
	this->maxExtents_XYZ.y = pCurrentVert->y;
	this->maxExtents_XYZ.z = pCurrentVert->z;

	for (unsigned int vertIndex = 0; vertIndex != this->numberOfVertices; vertIndex++)
	{
		sVertex* pCurrentVert = &(this->pVertices[vertIndex]);

		if (pCurrentVert->x < this->minExtents_XYZ.x) { this->minExtents_XYZ.x = pCurrentVert->x; }
		if (pCurrentVert->y < this->minExtents_XYZ.y) { this->minExtents_XYZ.y = pCurrentVert->y; }
		if (pCurrentVert->z < this->minExtents_XYZ.z) { this->minExtents_XYZ.z = pCurrentVert->z; }

		if (pCurrentVert->x > this->maxExtents_XYZ.x) { this->maxExtents_XYZ.x = pCurrentVert->x; }
		if (pCurrentVert->y > this->maxExtents_XYZ.y) { this->maxExtents_XYZ.y = pCurrentVert->y; }
		if (pCurrentVert->z > this->maxExtents_XYZ.z) { this->maxExtents_XYZ.z = pCurrentVert->z; }

	}

	this->deltaExtents_XYZ.x = this->maxExtents_XYZ.x - this->minExtents_XYZ.x;
	this->deltaExtents_XYZ.y = this->maxExtents_XYZ.y - this->minExtents_XYZ.y;
	this->deltaExtents_XYZ.z = this->maxExtents_XYZ.z - this->minExtents_XYZ.z;

	this->maxExtent = this->deltaExtents_XYZ.x;
	if (this->maxExtent < this->deltaExtents_XYZ.y) { this->maxExtent = this->deltaExtents_XYZ.y; }
	if (this->maxExtent < this->deltaExtents_XYZ.z) { this->maxExtent = this->deltaExtents_XYZ.z; }

	return;
}
