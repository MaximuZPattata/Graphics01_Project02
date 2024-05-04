#ifndef _cMesh_HG_
#define _cMesh_HG_

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <vector>

struct sMeshTexture
{
	bool bUseHeightMap = false;
	bool bDiscardBlackAreasInHeightMap = false;
	bool bDiscardColoredAreasInHeightMap = false;
	bool bUseDiscardMaskTexture = false;

	float heightMapScale = 0.0f;

	int textureUnit;
	int discardMaskTextureUnit;

	std::string texturePath;
	std::string textureName;
	std::string discardMaskTexturePath;

	glm::vec2 UVOffset = glm::vec2(0.0f, 0.0f);
};

struct sBlendedTextures
{
	std::vector <std::string> texturePathList;
	std::vector <std::string> textureNameList;
	float textureRatiosList[4];
	std::vector <int> textureUnit;
};


class cMesh 
{
private:	
	unsigned int m_UniqueID;
	static const unsigned int FIRST_UNIQUE_ID = 1000;
	static unsigned int m_nextUniqueID;

	glm::quat m_qOrientation;

public:
	cMesh();
	~cMesh();

	float alphaTransparency;

	bool bIsVisible;
	bool bIsWireframe;
	bool bDoNotLight;
	bool bUseManualColours;
	bool bUseTextures;
	bool bIsSkyBox;

	std::string meshName;
	std::string friendlyName;

	glm::vec3 drawPosition;
	glm::vec3 drawOrientation;
	glm::vec3 drawScale;

	glm::vec4 wholeObjectManualColourRGBA;

	unsigned int getUniqueID(void);

	void setUniformDrawScale(float scale);

	void setDrawPosition(const glm::vec3& newPosition);
	void setDrawOrientation(const glm::quat& newOrientation, glm::vec3 newAngles);
	
	glm::vec3 getDrawPosition(void);
	glm::vec3 getDrawOrientation(void);

	glm::quat get_qOrientation(void)
	{
		return this->m_qOrientation;
	}

	std::vector<cMesh*> mChildMeshesList;
	std::vector <sMeshTexture> mTextureDetailsList;

	sBlendedTextures mMixedTextures;
};

#endif

