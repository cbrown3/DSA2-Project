#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bounding Spheres DEMO");
}

void AppClass::InitVariables(void)
{
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up
	//Load a model onto the Mesh manager
	m_pMeshMngr->LoadModel("Minecraft\\Zombie.obj", "Zombie");
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Cow.obj", "Cow");
	//creating bounding spheres for both models
	m_pBS0 = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList("Zombie"));
	m_pBS1 = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList("Steve"));
	m_pBS2 = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList("Cow"));

	matrix4 m4Position = glm::translate(vector3(3.0, 0.0, 0.0));
	m_pMeshMngr->SetModelMatrix(m4Position, "Steve");

	matrix4 m4Position2 = glm::translate(vector3(2.5, 2.0, 0.0));
	m_pMeshMngr->SetModelMatrix(m4Position2, "Cow");
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

	//Call the arcball method
	ArcBall();

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

	//set the translate to create the transform matrix
	matrix4 m4Transform = glm::translate(m_v3Position) * ToMatrix4(m_qArcBall);
	m_pMeshMngr->SetModelMatrix(m4Transform, "Zombie"); //set the matrix to the model
	m_pBS0->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Zombie"));
	m_pBS0->RenderSphere();//render the bounding sphere
		

	m_pMeshMngr->SetModelMatrix(mTranslation, "Steve");
	m_pBS1->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"));
	m_pBS1->RenderSphere();

	m_pBS2->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Cow"));
	m_pBS2->RenderSphere();

	m_pBS0->SetColliding(false);
	m_pBS1->SetColliding(false);
	m_pBS2->SetColliding(false);

	if (m_pBS0->IsColliding(m_pBS1))
	{
		m_pBS0->SetColliding(true);
		m_pBS1->SetColliding(true);
	}
	if (m_pBS0->IsColliding(m_pBS2))
	{
		m_pBS0->SetColliding(true);
		m_pBS2->SetColliding(true);
	}
	if (m_pBS1->IsColliding(m_pBS2))
	{
		m_pBS1->SetColliding(true);
		m_pBS2->SetColliding(true);
	}

	if (fPercentage > 1.0f)
	{
		fTimer = 0.0f;
		std::swap(v3Start, v3End);
	}

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Radius: ");
	m_pMeshMngr->PrintLine(std::to_string(m_pBS0->GetRadius()), RERED);
	m_pMeshMngr->Print("Center: (");
	m_pMeshMngr->Print(std::to_string(m_pBS0->GetCenterGlobal().x), RERED);
	m_pMeshMngr->Print(" , ");
	m_pMeshMngr->Print(std::to_string(m_pBS0->GetCenterGlobal().y), RERED);
	m_pMeshMngr->Print(" , ");
	m_pMeshMngr->Print(std::to_string(m_pBS0->GetCenterGlobal().z), RERED);
	m_pMeshMngr->PrintLine(")");

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
	SafeDelete(m_pBS0);
	SafeDelete(m_pBS1);
	SafeDelete(m_pBS2);
	super::Release(); //release the memory of the inherited fields
}