// This shader is from the OpenGL Programming Guide, 8th edition, pg 377-378

#version 430 core

// in and out mean vertex buffer
layout(location=0) in vec4 in_Position;  
layout(location=1) in vec4 in_Normal;	// We'll only use vec3 of the normal
layout(location=2) in vec4 in_Tex_UV;	//Textures
  


uniform mat4 WorldMatrix;    		// aka ModelMatrix
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;


		
smooth out vec4 ex_Position;
smooth out vec3 ex_Normal;			// Note Normal is a vec3
smooth out vec4 ex_Tex_UV;         // Texture 


void main(void)
{	
	mat4 MVMatrix = ViewMatrix * WorldMatrix;
	mat4 MVPMatrix = ProjectionMatrix * MVMatrix;

	// gl_Position is a built-in variable

	
	gl_Position = MVPMatrix * in_Position;

	
	
	ex_Position = WorldMatrix * in_Position;	
			
	ex_Normal = vec3(in_Normal);
	ex_Tex_UV = in_Tex_UV;


}