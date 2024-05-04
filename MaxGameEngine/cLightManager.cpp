#include "cLightManager.h"
#include <sstream>

cLight::cLight()
{
	this->position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->atten = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); // x = constant, y = linear, z = quadratic, w = DistanceCutOff
	this->direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f); // Spot, directional lights(Default is stright down)
	this->param1 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // x = lightType(0 = pointlight | 1 = spot light | 2 = directional light), y = inner angle, z = outer angle, w = TBD
	this->param2 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // x = 0 for off, 1 for on

	this->position_UL = -1;
	this->diffuse_UL = -1;
	this->specular_UL = -1;
	this->atten_UL = -1;
	this->direction_UL = -1;
	this->param1_UL = -1;
	this->param2_UL = -1;
}

void cLight::TurnOn(void)
{
	// x = 0 for off, 1 for on
	this->param2.x = 1.0f;
	return;
}

void cLight::TurnOff(void)
{
	// x = 0 for off, 1 for on
	this->param2.x = 0.0f;
	return;
}

void cLightManager::SetUniformLocations(GLuint shaderID, int lightId)
{
	//        vec4 position;	// Position of the light
	std::string lightAttributes = "theLights[" + std::to_string(lightId) + "].position";
	const GLchar* glLightAttributes = lightAttributes.c_str();

	this->theLights[lightId].position_UL = glGetUniformLocation(shaderID, glLightAttributes);

	//        vec4 diffuse;	// Colour of the light (used for diffuse)
	lightAttributes = "theLights[" + std::to_string(lightId) + "].diffuse";
	glLightAttributes = lightAttributes.c_str();

	this->theLights[lightId].diffuse_UL = glGetUniformLocation(shaderID, glLightAttributes);

	//        vec4 specular;	// rgb = highlight colour, w = power
	lightAttributes = "theLights[" + std::to_string(lightId) + "].specular";
	glLightAttributes = lightAttributes.c_str();

	this->theLights[lightId].specular_UL = glGetUniformLocation(shaderID, glLightAttributes);
	
	//        vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	lightAttributes = "theLights[" + std::to_string(lightId) + "].atten";
	glLightAttributes = lightAttributes.c_str();

	this->theLights[lightId].atten_UL = glGetUniformLocation(shaderID, glLightAttributes);
	
	//        vec4 direction;	// Spot, directional lights
	lightAttributes = "theLights[" + std::to_string(lightId) + "].direction";
	glLightAttributes = lightAttributes.c_str();

	this->theLights[lightId].direction_UL = glGetUniformLocation(shaderID, glLightAttributes);
	
	//        vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
	lightAttributes = "theLights[" + std::to_string(lightId) + "].param1";
	glLightAttributes = lightAttributes.c_str();

	this->theLights[lightId].param1_UL = glGetUniformLocation(shaderID, glLightAttributes);
	
	//        vec4 param2;	// x = 0 for off, 1 for on
	lightAttributes = "theLights[" + std::to_string(lightId) + "].param2";
	glLightAttributes = lightAttributes.c_str();

	this->theLights[lightId].param2_UL = glGetUniformLocation(shaderID, glLightAttributes);

	return;
}

void cLightManager::UpdateUniformValues(GLuint shaderID)
{
	for (unsigned int index = 0; index != cLightManager::NUMBER_OF_LIGHTS_IM_USING; index++)
	{
		glUniform4f(theLights[index].position_UL,
			theLights[index].position.x,
			theLights[index].position.y,
			theLights[index].position.z,
			theLights[index].position.w);

		glUniform4f(theLights[index].diffuse_UL,
			theLights[index].diffuse.x,
			theLights[index].diffuse.y,
			theLights[index].diffuse.z,
			theLights[index].diffuse.w);

		glUniform4f(theLights[index].specular_UL,
			theLights[index].specular.x,
			theLights[index].specular.y,
			theLights[index].specular.z,
			theLights[index].specular.w);

		glUniform4f(theLights[index].atten_UL,
			theLights[index].atten.x,
			theLights[index].atten.y,
			theLights[index].atten.z,
			theLights[index].atten.w);

		glUniform4f(theLights[index].direction_UL,
			theLights[index].direction.x,
			theLights[index].direction.y,
			theLights[index].direction.z,
			theLights[index].direction.w);

		glUniform4f(theLights[index].param1_UL,
			theLights[index].param1.x,
			theLights[index].param1.y,
			theLights[index].param1.z,
			theLights[index].param1.w);

		glUniform4f(theLights[index].param2_UL,
			theLights[index].param2.x,
			theLights[index].param2.y,
			theLights[index].param2.z,
			theLights[index].param2.w);
	}

	return;
}


cLightManager::cLightManager()
{
}