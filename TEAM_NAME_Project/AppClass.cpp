#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Team Name Project");
}

void AppClass::InitVariables(void)
{
	//Set the camera position in orthographic position
	m_pCameraMngr->SetCameraMode(CAMROTHOY);
	//Load a model onto the Mesh manager
	m_pMeshMngr->LoadModel("Zelda\\MasterSword.bto", "Sword");
	m_pMeshMngr->LoadModel("Zelda\\HylianShield.bto", "Shield");
	m_pMeshMngr->LoadModel("Minecraft\\Cow.obj", "Cow");

	//m_pBoundingObjectMngr = MyBoundingObjectManager::GetInstance();

	//create a list of models to load
	//modelNames = new String[10];

	//set the model names in the array
	//modelNames[0] = "Sword";
	//modelNames[1] = "Shield";


	//set intial current model
	currentModel = "Sword";

	//creating bounding spheres for a placeholder model, the sword, the shield, and the cow
	m_pBS0 = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList(currentModel));
	m_pBS0a = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList("Sword"));
	m_pBS0b = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList("Shield"));
	m_pBS1 = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList("Cow"));

	matrix4 m4Position2 = glm::translate(vector3(2.5, 0.0, 0.0));
	m_pMeshMngr->SetModelMatrix(m4Position2, "Cow");
	
	//m_pBoundingObjectMngr->addBoundingBox(m_pBS0, "Empty");
	//m_pBoundingObjectMngr->addBoundingBox(m_pBS0a, "Sword");
	//m_pBoundingObjectMngr->addBoundingBox(m_pBS0b, "Shield");
	//m_pBoundingObjectMngr->addBoundingBox(m_pBS1, "Cow");

	//for now while the manager is not working
	index = 0;
	modelNames = std::vector<String>();
	boundingBoxes = std::vector<MyBoundingBoxClass>();

}

void AppClass::Update(void)
{
	//if the current model is the sword, make the main/placeholder model equal the correct model being selected.
	if (currentModel == "Sword")
	{
		m_pBS0 = m_pBS0a;
	}
	else if (currentModel == "Shield")
	{
		m_pBS0 = m_pBS0b;
	}


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
	m_pMeshMngr->SetModelMatrix(m4Transform, currentModel); //set the matrix to the model
	m_pBS0->SetModelMatrix(m_pMeshMngr->GetModelMatrix(currentModel));
	m_pBS0->ReAlignAxis(m_pMeshMngr->GetModelMatrix(currentModel)); //recalculate the axis aligned bounding box
	m_pBS0->RenderSphere(renderBox);//render the bounding sphere
		

	m_pMeshMngr->SetModelMatrix(mTranslation, "Cow");
	m_pBS1->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Cow"));
	m_pBS1->RenderSphere(renderBox);

	m_pBS0->SetColliding(false);
	m_pBS1->SetColliding(false);

	if (m_pBS0->IsColliding(m_pBS1))
	{
		m_pBS0->SetColliding(true);
		m_pBS1->SetColliding(true);
	}

	if (fPercentage > 1.0f)
	{
		fTimer = 0.0f;
		std::swap(v3Start, v3End);
	}

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();

	m_pMeshMngr->AddInstanceToRenderList(currentModel);
	m_pMeshMngr->AddInstanceToRenderList("Cow");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

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
	SafeDelete(m_pBS0);
	SafeDelete(m_pBS1);
	super::Release(); //release the memory of the inherited fields
}