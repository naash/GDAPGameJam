// This shader is from the OpenGL Programming Guide, 8th edition, page 378 - 379

// FRAGMENT shader for multiple lights

#version 430 core



//New
//Skymap
uniform samplerCube skyMapTexture;


smooth in vec4 ex_Position;
smooth in vec3 ex_Normal;			// Note Normal is a vec3
smooth in vec4 ex_Tex_UV;

out vec4 out_Color;		// If you don't say otherwise, this is the pixel colour



// FRAGMENT





void main(void)
{
	

		// Sky map is ONLY contribution from the cubemap texture

		out_Color = texture(skyMapTexture, ex_Normal.rgb);
		// Slightly brighten the image (because the room is so bright, yo!)
		float brighten = 1.0f;
		float gammaAdjust = 0.0f;
		out_Color += vec4( 0.0f, 0.0f, gammaAdjust, 1.0f );
		out_Color *= vec4( 0.0f, 0.0f, brighten, 1.0f );

	


	
}