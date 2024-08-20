#include "global.h"


void closeCallback()
{
	// We get rid of all the shaders. 
	//	Note that we do this in (sort of) the reverse order that we created them.
	// (We don't *really* have to do that, but
  //glDetachShader( g_ShaderProgram_ID, g_VertexShader_ID );		// glDetachShader(g_ShaderIds[0], g_ShaderIds[1]);
  //glDetachShader( g_ShaderProgram_ID, g_FragmentShader_ID );	// glDetachShader(g_ShaderIds[0], g_ShaderIds[2]);

  //glDeleteShader( g_VertexShader_ID );		// glDeleteShader(g_ShaderIds[1]);
  //glDeleteShader( g_FragmentShader_ID );	// glDeleteShader(g_ShaderIds[2]);

  //glDeleteProgram( g_ShaderProgram_ID );	// glDeleteProgram(g_ShaderIds[0]);
  //ExitOnGLError("ERROR: Could not destroy the shaders");

  //
  //g_pModelLoader->ShutDown();

  ExitOnGLError("ERROR: Could not destroy the buffer objects");
}