#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bounding Object Manager"); // Window Name 

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	m_bArcBallZ = false;

	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");
	m_pMeshMngr->LoadModel("Minecraft\\Cow.obj", "Cow");

	m_pBOMngr = MyBOManager::GetInstance();
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Steve"), "Steve");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Creeper"), "Creeper");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Cow"), "Cow");
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();
	ArcBallZ();

	//Object Movement
	static float fTimer = 0.0f;
	static int nClock = m_pSystem->GenClock();
	float fDeltaTime = static_cast<float>(m_pSystem->LapClock(nClock));
	fTimer += fDeltaTime;
	static vector3 v3Start = vector3(2.5f, 0.0f, 0.0f);
	static vector3 v3End = vector3(5.0, 0.0, 0.0);
	float fPercentage = MapValue(fTimer, 0.0f, 3.0f, 0.0f, 1.0f);
	m_v3O2 = glm::lerp(v3Start, v3End, fPercentage);
	matrix4 mTranslation = glm::translate(m_v3O2);

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O3), "Cow");

	//Set the model matrix to the Bounding Object
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"), "Steve");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Creeper"), "Creeper");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Cow"), "Cow");

	m_pBOMngr->Update();//Update collision detection
	
	//m_pBOMngr->DisplaySphere(-1, REWHITE);
	m_pBOMngr->DisplayReAlligned();
	m_pBOMngr->DisplayOriented(-1, REWHITE);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	if (fPercentage > 1.0f)
	{
		fTimer = 0.0f;
		std::swap(v3Start, v3End);
	}

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	std::vector<int> list = m_pBOMngr->GetCollidingVector(0);
	m_pMeshMngr->Print("Object 0 colliding with: ", REBLUE);
	for (uint n = 0; n < list.size(); n++)
	{
		m_pMeshMngr->Print(std::to_string(list[n]) + " ", REYELLOW);
	}
	m_pMeshMngr->PrintLine(" ");
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	MyBOManager::ReleaseInstance();
}

void AppClass::ArcBallZ(float a_fSensitivity)
{
	//If the arcball is not enabled return
	if (!m_bArcBallZ)
		return;

	//static quaternion qArcBall;
	UINT	MouseX, MouseY;		// Coordinates for the mouse

	//Calculate the position of the mouse and store it
	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;

	if (MouseLastX != 0 && MouseLastY != 0)
	{
		//Calculate the difference in position and update the quaternion orientation based on it
		float DeltaMouse;
		if (MouseX < MouseLastX)
		{
			DeltaMouse = static_cast<float>(MouseLastX - MouseX);
			m_qArcBall = quaternion(vector3(0.0f, 0.0f, glm::radians(a_fSensitivity * DeltaMouse))) * m_qArcBall;
		}
		else if (MouseX > MouseLastX)
		{
			DeltaMouse = static_cast<float>(MouseX - MouseLastX);
			m_qArcBall = quaternion(vector3(0.0f, 0.0f, glm::radians(-a_fSensitivity * DeltaMouse))) * m_qArcBall;
		}
	}
	SetCursorPos(MouseLastX, MouseLastY);
}