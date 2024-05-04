#include "cCubeMap.h"

//--------------------------------------Set Functions--------------------------------------------------

void cCubeMap::AddMeshModelName(std::string modelName)
{
	meshModelName = modelName;
}

void cCubeMap::AddSkyBoxName(std::string skyBoxName)
{
	cubeMapName = skyBoxName;
}

void cCubeMap::AddSkyBoxTextureUnit(int skyBoxTextureUnit)
{
	cubeMapTextureUnit = skyBoxTextureUnit;
}
void cCubeMap::AddSkyBoxFilePaths(std::string filePathPosX, std::string filePathNegX, std::string filePathPosY, std::string filePathNegY,
	std::string filePathPosZ, std::string filePathNegZ)
{
	cubeMapPosXPath = filePathPosX;
	cubeMapNegXPath = filePathNegX;
	cubeMapPosYPath = filePathPosY;
	cubeMapNegYPath = filePathNegY;
	cubeMapPosZPath = filePathPosZ;
	cubeMapNegZPath = filePathNegZ;
}

//--------------------------------------Get Functions--------------------------------------------------

int cCubeMap::GetSkyBoxTextureUnit()
{
	return cubeMapTextureUnit;
}

std::string cCubeMap::GetMeshModelName()
{
	return meshModelName;
}

std::string cCubeMap::GetSkyBoxName()
{
	return cubeMapName;
}

std::string cCubeMap::GetSkyBoxPosXPath()
{
	return cubeMapPosXPath;
}

std::string cCubeMap::GetSkyBoxPosYPath()
{
	return cubeMapPosYPath;
}

std::string cCubeMap::GetSkyBoxPosZPath()
{
	return cubeMapPosZPath;
}

std::string cCubeMap::GetSkyBoxNegXPath()
{
	return cubeMapNegXPath;
}

std::string cCubeMap::GetSkyBoxNegYPath()
{
	return cubeMapNegYPath;
}

std::string cCubeMap::GetSkyBoxNegZPath()
{
	return cubeMapNegZPath;
}