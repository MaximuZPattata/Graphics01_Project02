// Vertex shader
#version 420

uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matModel;			
uniform mat4 matModel_IT;		// Inverse transpose of the model matrix

in vec4 vCol;		
in vec4 vPos;		
in vec4 vNormal;	
in vec2 vTextureCoords;

out vec4 colour;
out vec4 vertexWorldPos;	
out vec4 vertexWorldNormal;
out vec2 textureCoords;

uniform bool bUseHeightMap;
uniform bool bDiscardColoredAreasInHeightMap;

uniform sampler2D heightMapSampler;
uniform float heightScale;
uniform vec2 UVOffset;

void main()
{
	vec4 vertexModelPos = vPos;
	
	vec2 UVFinal = vTextureCoords.st;
	
	if(bUseHeightMap)
	{
		UVFinal += UVOffset.yx;
		
		float height = texture( heightMapSampler, UVFinal.st ).r;
		
		//To scale blacked areas
		if(bDiscardColoredAreasInHeightMap)
		{
			height = (height < 0.005f) ? 1.0 : 0.0;
		}
		
		vertexModelPos.y += ( height * heightScale );
	}

	mat4 matMVP = matProjection * matView * matModel;
	gl_Position = matMVP * vec4(vertexModelPos.xyz, 1.0);
	
	// Rotate the normal by the inverse transpose of the model matrix
	vertexWorldNormal = matModel_IT * vec4(vNormal.xyz, 1.0f);
	vertexWorldNormal.xyz = normalize(vertexWorldNormal.xyz);
	vertexWorldNormal.w = 1.0f;
	
	vertexWorldPos = matModel * vec4( vertexModelPos.xyz, 1.0f);
	
	colour = vCol;
	
	textureCoords = UVFinal;
}

