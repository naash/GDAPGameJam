#include "global.h"
#include "fileDataLoader.h"



int main(int argc, char* argv[])
{

	timeFrames = 0.00f;

	std::cout<<"###############################################################"<<std::endl;
	std::cout<<"#######..........TROPICAL GO-KART JAMBOREE..............#######"<<std::endl;
	std::cout<<"###############################################################"<<std::endl;

	std::cout<<"Initializing Opengl...."<<std::endl;


	::OpenGL_Initialize( argc, argv, 1200, 800 );
	ModelData::textIndex = 0;
	//Create object

	::gameManager = new GameManager();



	glGenFramebuffers(1, &FrameBufferBasic);
	glGenFramebuffers(1, &FrameBufferShadow);
	glGenFramebuffers(1, &FrameBufferReflection);

	//Camera 
	g_pCamera1 = new CCamera();
	// Camera expects an IMediator*, so cast it as that
	//g_pCamera1->SetMediator( (IMediator*)g_pFactoryMediator );




	


	std::cout<<"Which mode do you want to play ?? "<<std::endl;
	std::cout<<"1 : Single Player "<<std::endl;
	std::cout<<"2 : Two Player    "<<std::endl;

	char a;
	std::cin>>a;



	std::cout<<"Player 1 controls -> arrow keys for direction and right alt for brakes"<<std::endl;

	if(a == '2')
	{
		::gameManager->isTwoPlayer = true;
		std::cout<<"Player 2 controls -> W,A,S,D keys for direction and left alt for brakes"<<std::endl;
		//Remove second car from the scene
		g_pCamera2 = new CCamera();


		std::cout<<"Creating Scene...."<<std::endl;
		boss.createScene(g_ShaderUniformVariables, 2);
		std::cout<<"Scene loaded...."<<std::endl;
		::myGlobalShader = boss.getShaders()["simple"];


		Vector3D playerPos = boss.getPlayerPos(playerIndex);

		g_pCamera1->eye = playerPos;
		g_pCamera1->eye.y += 4.0f;
		g_pCamera1->eye.x -= 5.0f;

		g_pCamera1->offset.x = -2.0f;
		g_pCamera1->offset.y = 2.0f;

		//g_pCamera1->target    Vector3D gets set to 0,0,0

		g_pCamera1->up.x = 0.0f;
		g_pCamera1->up.y = 1.0f;		

		playerPos = boss.getPlayerPos(playerIndex + 1);





		::g_SetShaderUniformVariables(myGlobalShader->getProgramID());





		g_pCamera2->eye = playerPos;
		g_pCamera2->eye.y += 4.0f;
		g_pCamera2->eye.x -= 5.0f;

		g_pCamera2->offset.x = -2.0f;
		g_pCamera2->offset.y = 2.0f;

		//g_pCamera1->target    Vector3D gets set to 0,0,0

		g_pCamera2->up.x = 0.0f;
		g_pCamera2->up.y = 1.0f;	
	}
	else
	{
		std::cout<<"Creating Scene...."<<std::endl;
		boss.createScene(g_ShaderUniformVariables, 1);
		std::cout<<"Scene loaded...."<<std::endl;
		::myGlobalShader = boss.getShaders()["simple"];


		Vector3D playerPos = boss.getPlayerPos(playerIndex);


		g_pCamera1->eye = playerPos;
		g_pCamera1->eye.y += 2.0f;
		g_pCamera1->eye.x -= 5.0f;

		g_pCamera1->offset.x = -5.0f;
		g_pCamera1->offset.y = 2.0f;

		//g_pCamera1->target    Vector3D gets set to 0,0,0

		g_pCamera1->up.x = 0.0f;
		g_pCamera1->up.y = 1.0f;	

		::g_SetShaderUniformVariables(myGlobalShader->getProgramID());
	}

	g_simTimer.Reset();
	g_simTimer.Start();		// Start "counting"s

	system("pause");

	::hudObject = new Hud();

	glutMainLoop();

	exit(EXIT_SUCCESS);


	return 0;
}

