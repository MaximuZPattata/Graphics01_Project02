#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>

struct sVertex
{
	float x, y, z, w;		//vPos	
	float r, g, b, a;		//vCol	
	float nx, ny, nz, nw;	//vNormal	
	float u, v;				//vTextureCoords
};

struct sModelDrawInfo
{
	sModelDrawInfo();

	std::string meshFileName;

	std::string friendlyName;

	unsigned int VAO_ID;

	unsigned int VertexBufferID;
	unsigned int VertexBuffer_Start_Index;
	unsigned int numberOfVertices;

	unsigned int IndexBufferID;
	unsigned int IndexBuffer_Start_Index;
	unsigned int numberOfIndices;
	unsigned int numberOfTriangles;

	unsigned int* pIndices;
	float maxExtent;

	sVertex* pVertices;

	glm::vec3 maxExtents_XYZ;
	glm::vec3 minExtents_XYZ;
	glm::vec3 deltaExtents_XYZ;

	void calcExtents(void);
	unsigned int getUniqueID(void);

private:

	unsigned int m_UniqueID;
	static const unsigned int FIRST_UNIQUE_ID = 1;
	static unsigned int m_nextUniqueID;
};
