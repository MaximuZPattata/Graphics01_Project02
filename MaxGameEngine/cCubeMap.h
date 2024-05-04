#pragma once
#include <string>

class cCubeMap
{
private:
	
	std::string meshModelName;
	std::string cubeMapName;

	int cubeMapTextureUnit;

	std::string cubeMapPosXPath;
	std::string cubeMapNegXPath;
	std::string cubeMapPosYPath;
	std::string cubeMapNegYPath;
	std::string cubeMapPosZPath;
	std::string cubeMapNegZPath;

public:

	void AddMeshModelName(std::string modelName);
	void AddSkyBoxName(std::string skyBoxName);
	void AddSkyBoxTextureUnit(int skyBoxTextureUnit);
	void AddSkyBoxFilePaths(std::string filePathPosX, std::string filePathNegX, std::string filePathPosY, std::string filePathNegY,
		std::string filePathPosZ, std::string filePathNegZ);

	int GetSkyBoxTextureUnit();
	std::string GetMeshModelName();
	std::string GetSkyBoxName();
	std::string GetSkyBoxPosXPath();
	std::string GetSkyBoxPosYPath();
	std::string GetSkyBoxPosZPath();
	std::string GetSkyBoxNegXPath();
	std::string GetSkyBoxNegYPath();
	std::string GetSkyBoxNegZPath();
};

