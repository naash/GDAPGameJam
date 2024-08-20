#include "global.h"
#include "master.h"

void resizeCallback(int Width, int Height)
{
	::g_screenWidth = Width;	// CurrentWidth = Width;
	::g_screenHeight = Height;	// CurrentHeight = Height;

	glViewport(0, 0, ::g_screenWidth, ::g_screenHeight);

	


	 //Resize
//Simple Frame Buffer ......................................................................................................
	 // Create the actual offscreen texture
	::g_FrameBufferHeight = static_cast<float>(::g_screenHeight);
	::g_FrameBufferWidth = static_cast<float>(::g_screenWidth);



	//glGenFramebuffers(1, &FrameBufferBasic );
	glBindFramebuffer( GL_FRAMEBUFFER, FrameBufferBasic );


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

	// Create the texture to write the "colour" stuff to 
	glBindTexture( GL_TEXTURE_2D, 0);
	glGenTextures( 1, &colorTextureID );
	glBindTexture( GL_TEXTURE_2D, colorTextureID );
	// Should really be a square, and a power of 2
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGB32F, g_FrameBufferWidth, g_FrameBufferHeight, 0, GL_RGBA, GL_FLOAT, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	
	glBindTexture( GL_TEXTURE_2D, 0);
	//// Create the depth texture we are going to write to (we'll need that as well)
	glGenTextures( 1, &depthTextureID );
	glBindTexture( GL_TEXTURE_2D, depthTextureID );
	glTexImage2D(GL_TEXTURE_2D,0, GL_DEPTH_COMPONENT, g_FrameBufferWidth, g_FrameBufferHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// Attach the colour and depth textures to the frame buffer object
	
	
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ::colorTextureID, 0 );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ::depthTextureID, 0 );

	  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
       std::cout<<"Problem with frame buffer"<<std::endl;



	//............................................Frame Buffer for Shadows.........................................................................
	  //............................Shadow Buffer
	glBindFramebuffer( GL_FRAMEBUFFER, FrameBufferShadow );

	glBindTexture( GL_TEXTURE_2D, 0);
	//// Create the depth texture we are going to write to (we'll need that as well)
	glGenTextures( 1, &shadowTextureID );
	glBindTexture( GL_TEXTURE_2D, shadowTextureID );
	glTexImage2D(GL_TEXTURE_2D,0, GL_DEPTH_COMPONENT32, g_FrameBufferWidth , g_FrameBufferHeight , 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	 glDrawBuffer(GL_NONE);

	//glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ::colorShTextureID, 0 );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ::shadowTextureID, 0 );

	  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
       std::cout<<"Problem with frame buffer"<<std::endl;


	  //Simple Frame Buffer ......................................................................................................
	 // Create the actual offscreen texture
	::g_FrameBufferHeight = static_cast<float>(::g_screenHeight);
	::g_FrameBufferWidth = static_cast<float>(::g_screenWidth);



	//glGenFramebuffers(1, &FrameBufferBasic );
	glBindFramebuffer( GL_FRAMEBUFFER, FrameBufferReflection );


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

	// Create the texture to write the "colour" stuff to 
	glBindTexture( GL_TEXTURE_2D, 0);
	glGenTextures( 1, &colorTextureRID );
	glBindTexture( GL_TEXTURE_2D, colorTextureRID );
	// Should really be a square, and a power of 2
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGB32F, g_FrameBufferWidth, g_FrameBufferHeight, 0, GL_RGBA, GL_FLOAT, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	
	glBindTexture( GL_TEXTURE_2D, 0);
	//// Create the depth texture we are going to write to (we'll need that as well)
	glGenTextures( 1, &depthTextureRID );
	glBindTexture( GL_TEXTURE_2D, depthTextureRID );
	glTexImage2D(GL_TEXTURE_2D,0, GL_DEPTH_COMPONENT, g_FrameBufferWidth, g_FrameBufferHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// Attach the colour and depth textures to the frame buffer object
	
	
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ::colorTextureRID, 0 );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ::depthTextureRID, 0 );

	  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
       std::cout<<"Problem with frame buffer"<<std::endl;



	//............................................Frame Buffer for Shadows.........................................................................


	  glBindFramebuffer( GL_FRAMEBUFFER, 0);

	//	system("pause");
	//............................................................................................................................................

	return;

}


