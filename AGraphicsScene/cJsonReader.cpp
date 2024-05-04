#include "pch.h"
#include "cJsonReader.h"

rapidjson::Document cJsonReader::ReadFile(std::string fileName)
{
	using namespace rapidjson;

	Document docReadObj;
	char readBuffer[65536];
	FILE* filePointer = 0; // Initializing filePointer to read from opened file
	errno_t errorChecker;

	docReadObj.SetObject(); // docReadObj initialized to parse JSON data

	errorChecker = fopen_s(&filePointer, fileName.c_str(), "rb");

	if (errorChecker != 0)
	{
		std::cout << "Error while reading the file - " << fileName << std::endl;
		return NULL;
	}

	FileReadStream inputStream(filePointer, readBuffer, sizeof(readBuffer));

	// Parses JSON data from inputStream onto docReadObj 
	docReadObj.ParseStream(inputStream);

	fclose(filePointer);

	return docReadObj;
}

bool cJsonReader::ReadScene(const std::string& filePath, std::vector <sModelDetailsFromFile>& differentModelDetails, sCubeMapDetailsFromFile& cubeMapDetails,
	std::vector<sPhysicsDetailsFromFile>& differentPhysicsDetails, std::vector<sLightDetailsFromFile>& differentLightDetails, sCameraDetailsFromFile& camDetails)
{
	using namespace rapidjson;

	Document docObj;

	docObj.SetObject();
	docObj = ReadFile(filePath);

	if (docObj.HasParseError())
	{
		std::cerr << "Failed to parse JSON." << std::endl;
		return false;
	}

	const char* propertyName;

	propertyName = "ModelProperties";

	if (docObj.HasMember(propertyName))
	{
		const Value& modelArray = docObj[propertyName];

		//-------------------------Model Details------------------------------------------

		for (SizeType modelIndex = 0; modelIndex < modelArray.Size(); modelIndex++)
		{
			const Value& modelDetails = modelArray[modelIndex];

			sModelDetailsFromFile newModelDetails;

			newModelDetails.modelName = modelDetails["ModelName"].GetString();
			newModelDetails.modelFilePath = modelDetails["FilePath"].GetString();
			newModelDetails.modelScaleValue = modelDetails["Scale"].GetFloat();
			newModelDetails.meshLightsOn = modelDetails["bMeshLightsOn"].GetBool();
			newModelDetails.wireframeModeOn = modelDetails["bWireframeModeOn"].GetBool();
			newModelDetails.manualColors = modelDetails["bUseManualColors"].GetBool();
			newModelDetails.useTextures = modelDetails["bUseTextures"].GetBool();
			newModelDetails.isSkyBox = modelDetails["bIsSkyBox"].GetBool();
			newModelDetails.modelPosition.x = modelDetails["Position"][0].GetFloat();
			newModelDetails.modelPosition.y = modelDetails["Position"][1].GetFloat();
			newModelDetails.modelPosition.z = modelDetails["Position"][2].GetFloat();
			newModelDetails.modelOrientation.x = modelDetails["Rotation"][0].GetFloat();
			newModelDetails.modelOrientation.y = modelDetails["Rotation"][1].GetFloat();
			newModelDetails.modelOrientation.z = modelDetails["Rotation"][2].GetFloat();

			if (!newModelDetails.isSkyBox)
			{
				if (newModelDetails.manualColors)
				{
					newModelDetails.modelColorRGB.r = modelDetails["Color"][0].GetFloat();
					newModelDetails.modelColorRGB.g = modelDetails["Color"][1].GetFloat();
					newModelDetails.modelColorRGB.b = modelDetails["Color"][2].GetFloat();
				}

				if (newModelDetails.useTextures)
				{
					for (SizeType textureIndex = 0; textureIndex < modelDetails["TextureDetails"].Size(); textureIndex++)
					{
						const Value& textureDetails = modelDetails["TextureDetails"][textureIndex];

						newModelDetails.blendTexture.push_back(textureDetails["bTextureBlend"].GetBool());
						newModelDetails.useDiscardMaskTexture.push_back(textureDetails["bUseDiscardMask"].GetBool());
						newModelDetails.textureFilePathList.push_back(textureDetails["TexturePath"].GetString());
						newModelDetails.textureNameList.push_back(textureDetails["TextureName"].GetString());

						if (newModelDetails.blendTexture[textureIndex])
							newModelDetails.textureRatiosList.push_back(textureDetails["TextureRatio"].GetFloat());
						if (newModelDetails.useDiscardMaskTexture[textureIndex])
							newModelDetails.discardMaskTextureFilePath.push_back(textureDetails["DiscardMaskTexturePath"].GetString());
					}
				}
			}

			differentModelDetails.push_back(newModelDetails);
		}
	}

	propertyName = "LightProperties";

	if (docObj.HasMember(propertyName))
	{
		const Value& lightingArray = docObj[propertyName];

		//-------------------------Light Details------------------------------------------

		for (SizeType lightingIndex = 0; lightingIndex < lightingArray.Size(); lightingIndex++)
		{
			const Value& lightDetails = lightingArray[lightingIndex];

			sLightDetailsFromFile newLightDetails;

			newLightDetails.lightId = lightDetails["LightId"].GetInt();
			newLightDetails.lightOn = lightDetails["bLightOn"].GetBool();
			newLightDetails.lightType = lightDetails["LightType"].GetFloat();
			newLightDetails.linearAttenuation = lightDetails["LinearAttenuation"].GetFloat();
			newLightDetails.quadraticAttenuation = lightDetails["QuadraticAttenuation"].GetFloat();
			newLightDetails.innerAngle = lightDetails["InnerAngle"].GetFloat();
			newLightDetails.outerAngle = lightDetails["OuterAngle"].GetFloat();
			newLightDetails.lightPosition.x = lightDetails["LightPosition"][0].GetFloat();
			newLightDetails.lightPosition.y = lightDetails["LightPosition"][1].GetFloat();
			newLightDetails.lightPosition.z = lightDetails["LightPosition"][2].GetFloat();
			newLightDetails.lightColorRGB.r = lightDetails["LightColor"][0].GetFloat();
			newLightDetails.lightColorRGB.g = lightDetails["LightColor"][1].GetFloat();
			newLightDetails.lightColorRGB.b = lightDetails["LightColor"][2].GetFloat();
			newLightDetails.lightDirection.x = lightDetails["LightDirection"][0].GetFloat();
			newLightDetails.lightDirection.y = lightDetails["LightDirection"][1].GetFloat();
			newLightDetails.lightDirection.z = lightDetails["LightDirection"][2].GetFloat();

			differentLightDetails.push_back(newLightDetails);
		}
	}

	propertyName = "PhysicalProperties";

	if (docObj.HasMember(propertyName))
	{
		const Value& physicsArray = docObj[propertyName];

		//------------------------Physics Details------------------------------------------

		for (SizeType physicsIndex = 0; physicsIndex < physicsArray.Size(); physicsIndex++)
		{
			const Value& physicsDetails = physicsArray[physicsIndex];

			sPhysicsDetailsFromFile newPhysicsDetails;

			newPhysicsDetails.modelName = physicsDetails["ModelName"].GetString();
			newPhysicsDetails.modelRadius = physicsDetails["Radius"].GetFloat();
			newPhysicsDetails.modelMass = physicsDetails["Mass"].GetFloat();
			newPhysicsDetails.randomVelocity = physicsDetails["bRandomVelocity"].GetBool();
			newPhysicsDetails.modelVelocity.x = physicsDetails["Velocity"][0].GetFloat();
			newPhysicsDetails.modelVelocity.y = physicsDetails["Velocity"][1].GetFloat();
			newPhysicsDetails.modelVelocity.z = physicsDetails["Velocity"][2].GetFloat();
			newPhysicsDetails.modelAcceleration.x = physicsDetails["Acceleration"][0].GetFloat();
			newPhysicsDetails.modelAcceleration.y = physicsDetails["Acceleration"][1].GetFloat();
			newPhysicsDetails.modelAcceleration.z = physicsDetails["Acceleration"][2].GetFloat();

			differentPhysicsDetails.push_back(newPhysicsDetails);
		}
	}

	propertyName = "CameraProperties";

	if (docObj.HasMember(propertyName))
	{
		const Value& cameraInfo = docObj[propertyName];

		//------------------------Camera Details-------------------------------------------

		camDetails.initialCameraPosition.x = cameraInfo["CameraPosition"][0].GetFloat();
		camDetails.initialCameraPosition.y = cameraInfo["CameraPosition"][1].GetFloat();
		camDetails.initialCameraPosition.z = cameraInfo["CameraPosition"][2].GetFloat();
	}

	propertyName = "CubeMapProperties";

	if (docObj.HasMember(propertyName))
	{
		const Value& cubeMapInfo = docObj[propertyName];

		//-----------------------Cube Map Details------------------------------------------

		cubeMapDetails.cubeMapName = cubeMapInfo["MapName"].GetString();

		const Value& filePathDetails = cubeMapInfo["MapTexturePath"];

		cubeMapDetails.filePathPosX = filePathDetails["RightTexture"].GetString();
		cubeMapDetails.filePathNegX = filePathDetails["LeftTexture"].GetString();
		cubeMapDetails.filePathPosY = filePathDetails["TopTexture"].GetString();
		cubeMapDetails.filePathNegY = filePathDetails["DownTexture"].GetString();
		cubeMapDetails.filePathPosZ = filePathDetails["FrontTexture"].GetString();
		cubeMapDetails.filePathNegZ = filePathDetails["BackTexture"].GetString();
	}

	return true;
}

