
#version 430 core

// in and out mean vertex buffer
layout(location=0) in vec4 in_Position;  
layout(location=1) in vec4 in_Color;	// We'll only use vec3 of the normal
layout(location=2) in vec4 in_Normal;	// We'll only use vec3 of the normal
layout(location=3) in vec4 in_Tex_UV;	//Textures
  


// Values that stay constant for the whole mesh.
uniform mat4 depthMVP;
 
void main(){

	gl_Position =  depthMVP * in_Position;
 
}