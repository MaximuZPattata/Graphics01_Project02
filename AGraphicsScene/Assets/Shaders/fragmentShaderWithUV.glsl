// Fragment shader
#version 420

in vec4 colour;
in vec4 vertexWorldPos;	
in vec4 vertexWorldNormal;	
in vec2 textureCoords;

out vec4 outputColour;		// To the frame buffer (aka screen)

uniform bool bDoNotLight;		// If true, then passes the colour without calculating lighting
uniform bool bUseManualColour;	// If this is true, then use manualColourRGBA for the colour
uniform bool bUseTextureColour; //If true, doesn't use texture colors	
uniform bool bUseHeightMap;
uniform bool bDiscardBlackInHeightMap;
uniform bool bDiscardColoredAreasInHeightMap;
uniform bool bUseDiscardMaskTexture;
uniform bool bUseTextureMixRatio;
uniform bool bApplySkyBox;

uniform vec4 eyeLocation;
uniform vec4 manualColourRGBA;	
uniform vec4 textureMixRatio_0_3;

uniform float alphaTransparency;

uniform sampler2D texture_00; //x,y or s,t or u,v
uniform sampler2D texture_01;
uniform sampler2D texture_02;
uniform sampler2D texture_03;
uniform sampler2D textureAdder;
uniform sampler2D heightMapSampler;
uniform sampler2D maskSampler;

uniform samplerCube cubeMapSampler;

struct sLight
{
	vec4 position;			
	vec4 diffuse;	// Colour of the light (used for diffuse)
	vec4 specular;	// rgb = highlight colour, w = power
	vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	vec4 direction;	// Spot, directional lights
	vec4 param1;	// x = lightType(0 = pointlight | 1 = spot light | 2 = directional light), y = inner angle, z = outer angle, w = TBD
	vec4 param2;	// x = 0 for off, 1 for on
};

const int POINT_LIGHT_TYPE = 0;
const int SPOT_LIGHT_TYPE = 1;
const int DIRECTIONAL_LIGHT_TYPE = 2;
const int NUMBEROFLIGHTS = 15;

uniform sLight theLights[NUMBEROFLIGHTS];  	

vec4 calculateLightContrib( vec3 vertexMaterialColour, vec3 vertexNormal, vec3 vertexWorldPos, vec4 vertexSpecular );

void main()
{

// Discard colored or uncolored areas in Height Map
	if ( bUseHeightMap && (bDiscardBlackInHeightMap || bDiscardColoredAreasInHeightMap))
	{
		// Range of 0 to 1
		float height = texture( heightMapSampler, textureCoords.st ).r;
		
		if(bDiscardColoredAreasInHeightMap)
		{
			if ( height > 0.005f )
			{
				discard;
			}
		}
		else
		{
			if ( height <= 0.005f )
			{
				discard;
			}
		}
	}
	
// Use Discard Mask Texture
	if (bUseDiscardMaskTexture)
	{
		float maskValue = texture(maskSampler, textureCoords.st ).r;
		
		if( maskValue < 0.1f )
		{
			discard;
		}
	}
	
	// Add CubeMap 
	if(bApplySkyBox)
	{
		vec4 skyBoxColour = texture(cubeMapSampler, vertexWorldNormal.xyz).rgba;
		outputColour.rgb = skyBoxColour.rgb;
		outputColour.a = 1.0f;
		return;
	}
	
	// Add textures
	vec4 textureColour;
	
	if(bUseTextureMixRatio)
	{
		textureColour = texture(texture_00, textureCoords.st).rgba * textureMixRatio_0_3.x + texture(texture_01, textureCoords.st).rgba * textureMixRatio_0_3.y
									+ texture(texture_02, textureCoords.st).rgba * textureMixRatio_0_3.z + texture(texture_03, textureCoords.st).rgba * textureMixRatio_0_3.w;
	}
	else
	{
		textureColour = texture(textureAdder, textureCoords.st).rgba;
	}
		
	vec4 vertexRGBA = colour; //By default, uses model vertex color
	
	if(bUseTextureColour)
	{
		vertexRGBA = textureColour; //Uses texture color 
	}
	
	if (bUseManualColour)
	{	
		vertexRGBA = manualColourRGBA; //Uses manual color
	}
	
	if ( bDoNotLight )
	{
		outputColour = vertexRGBA;
		return;
	}
	
	vec4 vertexSpecular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 vertexColourLit = calculateLightContrib( vertexRGBA.rgb, vertexWorldNormal.xyz, 
	                                              vertexWorldPos.xyz, vertexSpecular );

	outputColour.rgb = vertexColourLit.rgb;
	outputColour.rgb *= 1.35f;
	
	//outputColour.a = 1.0f;
	outputColour.a = alphaTransparency;
}

vec4 calculateLightContrib( vec3 vertexMaterialColour, vec3 vertexNormal, 
                            vec3 vertexWorldPos, vec4 vertexSpecular )
{
	vec3 norm = normalize(vertexNormal);
	
	vec4 finalObjectColour = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	
	for ( int index = 0; index < NUMBEROFLIGHTS; index++ )
	{	
		if ( theLights[index].param2.x == 0.0f )
		{
			continue;
		}
		
		int intLightType = int(theLights[index].param1.x);
		
		if ( intLightType == DIRECTIONAL_LIGHT_TYPE )		// = 2
		{
			vec3 lightContrib = theLights[index].diffuse.rgb;
			
			float dotProduct = dot( -theLights[index].direction.xyz,  
									   normalize(norm.xyz) );	// -1 to 1

			dotProduct = max( 0.0f, dotProduct );		// 0 to 1
		
			lightContrib *= dotProduct;		
			
			finalObjectColour.rgb += (vertexMaterialColour.rgb * theLights[index].diffuse.rgb * lightContrib); 

			return finalObjectColour;		
		}
		
		vec3 vLightToVertex = theLights[index].position.xyz - vertexWorldPos.xyz;
		float distanceToLight = length(vLightToVertex);	
		vec3 lightVector = normalize(vLightToVertex);
		float dotProduct = dot(lightVector, vertexNormal.xyz);	 
		
		dotProduct = max( 0.0f, dotProduct );	
		
		vec3 lightDiffuseContrib = dotProduct * theLights[index].diffuse.rgb;
			
		// Specular 
		vec3 lightSpecularContrib = vec3(0.0f);
			
		vec3 reflectVector = reflect( -lightVector, normalize(norm.xyz) );

		vec3 eyeVector = normalize(eyeLocation.xyz - vertexWorldPos.xyz);

		// To simplify, we are NOT using the light specular value, just the object’s.
		float objectSpecularPower = vertexSpecular.w; 
		
		lightSpecularContrib = pow( max(0.0f, dot( eyeVector, reflectVector) ), objectSpecularPower )
			                   * theLights[index].specular.rgb;
							   
		// Attenuation
		float attenuation = 1.0f / 
				( theLights[index].atten.x + 										
				  theLights[index].atten.y * distanceToLight +						
				  theLights[index].atten.z * distanceToLight*distanceToLight );  	
				  
		// total light contribution is Diffuse + Specular
		lightDiffuseContrib *= attenuation;
		lightSpecularContrib *= attenuation;
		
		if ( intLightType == SPOT_LIGHT_TYPE )		// = 1
		{	
			vec3 vertexToLight = vertexWorldPos.xyz - theLights[index].position.xyz;

			vertexToLight = normalize(vertexToLight);

			float currentLightRayAngle
					= dot( vertexToLight.xyz, theLights[index].direction.xyz );
					
			currentLightRayAngle = max(0.0f, currentLightRayAngle);

			float outerConeAngleCos = cos(radians(theLights[index].param1.z));
			float innerConeAngleCos = cos(radians(theLights[index].param1.y));
							
			if ( currentLightRayAngle < outerConeAngleCos )
			{
				lightDiffuseContrib = vec3(0.0f, 0.0f, 0.0f);
				lightSpecularContrib = vec3(0.0f, 0.0f, 0.0f);
			}
			else if ( currentLightRayAngle < innerConeAngleCos )
			{
				float penumbraRatio = (currentLightRayAngle - outerConeAngleCos) / 
									  (innerConeAngleCos - outerConeAngleCos);
									  
				lightDiffuseContrib *= penumbraRatio;
				lightSpecularContrib *= penumbraRatio;
			}
						
		}// if ( intLightType == 1 )
		
		
					
		finalObjectColour.rgb += (vertexMaterialColour.rgb * lightDiffuseContrib.rgb)
								  + (vertexSpecular.rgb  * lightSpecularContrib.rgb );

	}
	
	finalObjectColour.a = 1.0f;
	
	return finalObjectColour;
}
	