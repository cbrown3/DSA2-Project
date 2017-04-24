#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E13 - MyBoundingSphereClass"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");

	m_pBB1 = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList("Steve"));
	m_pBB2 = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList("Creeper"));
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

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");

	m_pBB1->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"));
	m_pBB2->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Creeper"));

	//Add a representation of the Spheres to the render list
	vector3 v3Color = REWHITE;
	if (m_pBB1->IsColliding(m_pBB2))
		v3Color = RERED;

	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_pBB1->GetCenterGlobal()) * glm::scale(m_pBB1->GetHalfWidthG() * 2.0f), v3Color, WIRE);
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_pBB2->GetCenterGlobal()) * glm::scale(m_pBB2->GetHalfWidthG() * 2.0f), v3Color, WIRE);

	m_pMeshMngr->AddCubeToRenderList(m_pBB1->GetModelMatrix() * glm::translate(IDENTITY_M4, m_pBB1->GetCenterLocal()) * glm::scale(m_pBB1->GetHalfWidth() * 2.0f), v3Color, WIRE);
	m_pMeshMngr->AddCubeToRenderList(m_pBB2->GetModelMatrix() * glm::translate(IDENTITY_M4, m_pBB2->GetCenterLocal()) * glm::scale(m_pBB2->GetHalfWidth() * 2.0f), v3Color, WIRE);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
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
	SafeDelete(m_pBB1);
	SafeDelete(m_pBB2);
}