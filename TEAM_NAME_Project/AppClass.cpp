#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Team Name Project");
}

void AppClass::InitVariables(void)
{
	//Set the camera position in orthographic position
	m_pCameraMngr->SetCameraMode(CAMPERSP);
	m_pCameraMngr->MoveVertical(4.0, -1);
	//Load a model onto the Mesh manager
	m_pMeshMngr->LoadModel("ninja.fbx", "Ninja");
	m_pMeshMngr->LoadModel("substitute.fbx", "Substitute");
	m_pMeshMngr->LoadModel("Minecraft\\Cow.bto", "Cow");
	m_pMeshMngr->LoadModel("Chess\\pawn(orange).obj", "Pawn");
	m_pMeshMngr->LoadModel("gym.fbx", "World");

	/*GAMEOBJECT SYSTEM*/
	Player = GameObject("ninja.fbx", "Main");
	World = GameObject("world.fbx", "World");
	Cow = GameObject("Minecraft\\Cow.bto", "Cow", vector3(2.5f, 0.0f, 0.0f));

	//set intial current model
	currentModel = "Ninja";
	//m_pBoundingObjectMngr = MyBoundingObjectManager::GetInstance();
	//m_pBoundingObjectMngr->AddObject(m_pMeshMngr->GetVertexList("Cow"), "Cow");
	//m_pBoundingObjectMngr->AddObject(m_pMeshMngr->GetVertexList("Sword"), "Sword");
	//m_pBoundingObjectMngr->AddObject(m_pMeshMngr->GetVertexList("Shield"), "Shield");

	//creating bounding spheres for a placeholder model, the sword, the shield, and the cow
	//m_pBSCow = m_pBoundingObjectMngr->GetBoundingObject(0);
	//m_pBSMain = m_pBoundingObjectMngr->GetBoundingObject(1);
	//m_pBSword = m_pBoundingObjectMngr->GetBoundingObject(1);
	//m_pBShield = m_pBoundingObjectMngr->GetBoundingObject(2);

	//matrix4 m4Position2 = glm::translate(vector3(2.5, 0.0, 0.0));
	//m_pMeshMngr->SetModelMatrix(m4Position2, "Cow");
	//m_pBoundingObjectMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Cow"), "Cow");


}

void AppClass::Update(void)
{
	Player.Update();
	Cow.Update();
	World.Update();

	//if the current model is the sword, make the main/placeholder model equal the correct model being selected.
	if (currentModel == "Ninja")
	{
		Player = GameObject("ninja.fbx", "Ninja", Player.GetPosition());
	}
	else if (currentModel == "Substitute")
	{
		Player = GameObject("substitute.fbx", "Substitute", Player.GetPosition());
	}

	if (renderBox)
	{
		if (Player.GetCollider()->IsColliding(Cow.GetCollider()))
		{
			Player.GetCollider()->DisplayOriented(RERED);
		}
		else
		{
			Player.GetCollider()->DisplayOriented(REGREEN);
		}
	}

	if (renderAlligned)
	{
		if (Player.GetCollider()->IsColliding(Cow.GetCollider()))
		{
			Player.GetCollider()->DisplayReAlligned(RERED);
		}
		else
		{
			Player.GetCollider()->DisplayReAlligned(REGREEN);
		}
	}

	if (renderSphere)
	{
		if (Player.GetCollider()->IsColliding(Cow.GetCollider()))
		{
			Player.GetCollider()->DisplaySphere(RERED);
		}
		else
		{
			Player.GetCollider()->DisplaySphere(REGREEN);
		}
	}

	Cow.GetCollider()->DisplayReAlligned(REGREEN);

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//camera follows player
	//m_pCameraMngr->SetTarget(m_pBSMain->GetCenterGlobal(), -1);

	//collision resolution
	if (Cow.GetCollider()->IsColliding(Player.GetCollider()))
	{
		Cow.GetCollider()->DisplayReAlligned(RERED);
	}

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	ToMatrix4( m_qArcBall);

	//Object Movement
	static float fTimer = 0.0f;
	static int nClock = m_pSystem->GenClock();
	float fDeltaTime = static_cast<float>(m_pSystem->LapClock(nClock));
	fTimer += fDeltaTime;
	static vector3 v3Start = vector3(3.0, 0.0, 0.0);
	static vector3 v3End = vector3(5.0, 0.0, 0.0);
	float fPercentage = MapValue(fTimer, 0.0f, 3.0f, 0.0f, 1.0f);
	vector3 v3Current = glm::lerp(v3Start, v3End, fPercentage);
	matrix4 mTranslation = glm::translate(v3Current);
	/*
	//set the translate to create the transform matrix
	matrix4 m4Transform = glm::translate(m_v3Position) * ToMatrix4(m_qArcBall);
	m_pMeshMngr->SetModelMatrix(m4Transform, currentModel); //set the matrix to the model
		

	m_pMeshMngr->SetModelMatrix(mTranslation, "Cow");
	m_pBSCow->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Cow"));

	if (fPercentage > 1.0f)
	{
		fTimer = 0.0f;
		std::swap(v3Start, v3End);
	}
	*/
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();

	m_pMeshMngr->AddInstanceToRenderList(Player.GetName());
	m_pMeshMngr->AddInstanceToRenderList(World.GetName());
	m_pMeshMngr->AddInstanceToRenderList(Cow.GetName());

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->Print(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("          Up/Down: Move Model Forward/Backward");
	m_pMeshMngr->PrintLine("Left/Right: Move Model Left/Right");
	m_pMeshMngr->Print("          Shift + Up/Down: Move Model Up/Down");
	m_pMeshMngr->PrintLine("Number Keys: Change Model");
	m_pMeshMngr->Print("          Hold RMB: Rotate Camera");
	m_pMeshMngr->PrintLine("WASD: Move Camera");
	m_pMeshMngr->Print("          Shift + WASD: Move Camera Fast");
	m_pMeshMngr->PrintLine("Current Player Model: " + currentModel);

	/*
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	*/
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
	m_pBoundingObjectMngr->ReleaseInstance();
	super::Release(); //release the memory of the inherited fields
}