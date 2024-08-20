// This shader is from the OpenGL Programming Guide, 8th edition, pg 377-378

#version 430 core

// in and out mean vertex buffer
layout(location=0) in vec4 in_Position;  
layout(location=1) in vec4 in_Color;	// We'll only use vec3 of the normal
layout(location=2) in vec4 in_Normal;	// We'll only use vec3 of the normal
layout(location=3) in vec4 in_Tex_UV;	//Textures
  


uniform mat4 WorldMatrix;    		// aka ModelMatrix
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform float waveFactor;
		


/*

GLSL conversion of Michael Horsch water demo

http://www.bonzaisoftware.com/wfs.html



Converted by Mars_999

8/20/2005

*/

out vec4 waterTex0;

out vec4 waterTex1;

out vec4 waterTex2;

out vec4 waterTex3;

out vec4 waterTex4;

smooth out vec4 ex_Tex_UV;




uniform vec4 viewpos, lightpos;

uniform float time, time2;

//unit 0 = water_reflection

//unit 1 = water_refraction

//unit 2 = water_normalmap

//unit 3 = water_dudvmap

//unit 4 = water_depthmap



void main(void)

{

    vec4 mpos, temp;

    vec4 tangent = vec4(1.0, 0.0, 0.0, 0.0);

    vec4 norm = vec4(0.0, 1.0, 0.0, 0.0);

    vec4 binormal = vec4(0.0, 0.0, 1.0, 0.0);

   

   
   mat4 MVMatrix = ViewMatrix * WorldMatrix;
	mat4 MVPMatrix = ProjectionMatrix * MVMatrix;
   
   
  
       

    temp = viewpos - in_Position;

    waterTex4.x = dot(temp, tangent);

    waterTex4.y = dot(temp, binormal);

    waterTex4.z = dot(temp, norm);

    waterTex4.w = 0.0;

    

    temp = lightpos - in_Position;

     waterTex0.x = dot(temp, tangent);

    waterTex0.y = dot(temp, binormal);

    waterTex0.z = dot(temp, norm);

    waterTex0.w = 0.0;

    

    mpos = MVPMatrix * in_Position;



    vec4 t1 = vec4(0.0, -time, 0.0,0.0);

    vec4 t2 = vec4(0.0, -time2, 0.0,0.0);

    

    waterTex1 = in_Tex_UV + t1;

    waterTex2 = in_Tex_UV + t2;

  

    waterTex3 = mpos;

	//gl_Position = mpos;
	
    // gl_Position is a built-in variable

	vec4 newPos = vec4(in_Position) +t1;
	
	
	gl_Position = MVPMatrix * newPos;
	ex_Tex_UV = in_Tex_UV;
}
