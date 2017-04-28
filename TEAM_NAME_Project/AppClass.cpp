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
	//m_pMeshMngr->LoadModel("Zelda\\MasterSword.bto", "Sword");
	//m_pMeshMngr->LoadModel("Zelda\\HylianShield.bto", "Shield");
	m_pMeshMngr->LoadModel("Minecraft\\Cow.bto", "Cow");
	m_pMeshMngr->LoadModel("orangeSet.obj", "Shield");
	m_pMeshMngr->LoadModel("board.obj", "Sword");

	//create a list of models to load
	//modelNames = new String[10];

	//set the model names in the array
	//modelNames[0] = "Sword";
	//modelNames[1] = "Shield";


	//set intial current model
	currentModel = "Sword";
	m_pBoundingObjectMngr = MyBoundingObjectManager::GetInstance();
	m_pBoundingObjectMngr->AddObject(m_pMeshMngr->GetVertexList("Cow"), "Cow");
	m_pBoundingObjectMngr->AddObject(m_pMeshMngr->GetVertexList("Sword"), "Sword");
	m_pBoundingObjectMngr->AddObject(m_pMeshMngr->GetVertexList("Shield"), "Shield");

	//creating bounding spheres for a placeholder model, the sword, the shield, and the cow
	m_pBSCow = m_pBoundingObjectMngr->GetBoundingObject(0);
	m_pBSMain = m_pBoundingObjectMngr->GetBoundingObject(1);
	m_pBSword = m_pBoundingObjectMngr->GetBoundingObject(1);
	m_pBShield = m_pBoundingObjectMngr->GetBoundingObject(2);

	matrix4 m4Position2 = glm::translate(vector3(2.5, 0.0, 0.0));
	m_pMeshMngr->SetModelMatrix(m4Position2, "Cow");
	m_pBoundingObjectMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Cow"), "Cow");


}

void AppClass::Update(void)
{
	//if the current model is the sword, make the main/placeholder model equal the correct model being selected.
	if (currentModel == "Sword")
	{
		m_pBSMain = m_pBSword;

		if (renderBox)
		{
			if (m_pBSMain->IsColliding(m_pBSCow))
			{
				m_pBoundingObjectMngr->DisplayOriented(m_pBoundingObjectMngr->GetIndex("Sword"), RERED);
			}
			else
			{
				m_pBoundingObjectMngr->DisplayOriented(m_pBoundingObjectMngr->GetIndex("Sword"), REGREEN);
			}
		}

		if (renderAlligned)
		{
			if (m_pBSMain->IsColliding(m_pBSCow))
			{
				m_pBoundingObjectMngr->DisplayReAlligned(m_pBoundingObjectMngr->GetIndex("Sword"), RERED);
			}
			else
			{
				m_pBoundingObjectMngr->DisplayReAlligned(m_pBoundingObjectMngr->GetIndex("Sword"), REGREEN);
			}
		}

		if (renderSphere)
		{
			if (m_pBSMain->IsColliding(m_pBSCow))
			{
				m_pBoundingObjectMngr->DisplaySphere(m_pBoundingObjectMngr->GetIndex("Sword"), RERED);
			}
			else
			{
				m_pBoundingObjectMngr->DisplaySphere(m_pBoundingObjectMngr->GetIndex("Sword"), REGREEN);
			}
		}
	}
	else if (currentModel == "Shield")
	{
		m_pBSMain = m_pBShield;

		if (renderBox)
		{
			if (m_pBSMain->IsColliding(m_pBSCow))
			{
				m_pBoundingObjectMngr->DisplayOriented(m_pBoundingObjectMngr->GetIndex("Shield"), RERED);
			}
			else
			{
				m_pBoundingObjectMngr->DisplayOriented(m_pBoundingObjectMngr->GetIndex("Shield"), REGREEN);
			}
		}

		if (renderAlligned)
		{
			if (m_pBSMain->IsColliding(m_pBSCow))
			{
				m_pBoundingObjectMngr->DisplayReAlligned(m_pBoundingObjectMngr->GetIndex("Shield"), RERED);
			}
			else
			{
				m_pBoundingObjectMngr->DisplayReAlligned(m_pBoundingObjectMngr->GetIndex("Shield"), REGREEN);
			}
		}

		if (renderSphere)
		{
			if (m_pBSMain->IsColliding(m_pBSCow))
			{
				m_pBoundingObjectMngr->DisplaySphere(m_pBoundingObjectMngr->GetIndex("Shield"), RERED);
			}
			else
			{
				m_pBoundingObjectMngr->DisplaySphere(m_pBoundingObjectMngr->GetIndex("Shield"), REGREEN);
			}
		}
	}

	m_pBoundingObjectMngr->DisplayReAlligned(m_pBoundingObjectMngr->GetIndex("Cow"), REGREEN);

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	m_pBoundingObjectMngr->Update();

	//camera follows player
	m_pCameraMngr->SetTarget(m_pBSMain->GetCenterGlobal(), -1);

	//collision resolution
	if (m_pBSCow->IsColliding(m_pBSMain))
	{
		m_pBoundingObjectMngr->DisplayReAlligned(m_pBoundingObjectMngr->GetIndex("Cow"), RERED);
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

	//set the translate to create the transform matrix
	matrix4 m4Transform = glm::translate(m_v3Position) * ToMatrix4(m_qArcBall);
	m_pMeshMngr->SetModelMatrix(m4Transform, currentModel); //set the matrix to the model
	m_pBSMain->SetModelMatrix(m_pMeshMngr->GetModelMatrix(currentModel));
		

	m_pMeshMngr->SetModelMatrix(mTranslation, "Cow");
	m_pBSCow->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Cow"));

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
	m_pBoundingObjectMngr->ReleaseInstance();
	super::Release(); //release the memory of the inherited fields
}