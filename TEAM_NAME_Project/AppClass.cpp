#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Team Name Project");
}


void AppClass::InitVariables(void)
{
	ID = 0;
	//Set the camera position in orthographic position
	m_pCameraMngr->SetCameraMode(CAMPERSP);
	m_pCameraMngr->MoveVertical(4.0, -1);

#pragma region danielle_additions

	//preload all the models bases used
	MODELS = std::vector<MODEL>();
	MODELS.push_back(MODEL("ninja.fbx", "ninja"));
	MODELS.push_back(MODEL("substitute.fbx", "substitute"));
	MODELS.push_back(MODEL("snail.fbx", "snail"));
	MODELS.push_back(MODEL("bus.fbx", "bus"));

	//set starting model
	modelIndex = MODELNAMES::ninja;
	currentModel = MODELS[modelIndex];

	//create gameobect list for all spawned models
	gameObjectList = std::vector<GameObject*>();

	for (int i = 0; i < 10; i++) {
		vector3 pos = vector3((rand() % 20)-10, 0, (rand() % 20)-10);
		GameObject* temp = new GameObject("substitute.fbx", "substitute_"+ID, pos);
		gameObjectList.push_back(temp);
		ID++;
	}

#pragma endregion

	/*GAMEOBJECT SYSTEM*/
	Player = GameObject(currentModel.path, currentModel.name);
	World = GameObject("gym.fbx", "World");

}

void AppClass::Update(void)
{


	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	Player.Update();
	World.Update();

	//camera follows player
	//m_pCameraMngr->SetTarget(m_pBSMain->GetCenterGlobal(), -1);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	ToMatrix4(m_qArcBall);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();

	m_pMeshMngr->AddInstanceToRenderList(Player.GetName());
	m_pMeshMngr->AddInstanceToRenderList(World.GetName());

#pragma region danielle_additions

	//add all models to render list
	for (int i = 0; i < gameObjectList.size(); i++) {
		
		//check collisions with player
		if (Player.GetCollider()->IsColliding(gameObjectList[i]->GetCollider()))
		{
			Player.GetCollider()->DisplayOriented(RERED);
			gameObjectList[i]->GetCollider()->DisplayOriented(RERED);
			gameObjectList[i]->RigidTrans(Player.rigidBody.state.velocity*0.2f);
		}
		else
		{
			Player.GetCollider()->DisplayOriented(REGREEN);
			gameObjectList[i]->GetCollider()->DisplayOriented(REGREEN);
		}

		//check collisions with others
		for (int j = i+1; j < gameObjectList.size(); j++) {
			if (gameObjectList[j]->GetCollider()->IsColliding(gameObjectList[i]->GetCollider()))
			{
				gameObjectList[i]->GetCollider()->DisplayOriented(RERED);
				gameObjectList[j]->GetCollider()->DisplayOriented(RERED);
				gameObjectList[i]->RigidTrans(gameObjectList[j]->rigidBody.state.velocity*0.2f);
			}
			else
			{
				gameObjectList[i]->GetCollider()->DisplayOriented(REGREEN);
				gameObjectList[j]->GetCollider()->DisplayOriented(REGREEN);
			}
		}


		gameObjectList[i]->Update();

		//add to render
		m_pMeshMngr->AddInstanceToRenderList(gameObjectList[i]->GetName());
	}
#pragma endregion

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->Print(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("                  Up/Down: Move Model Forward/Backward", REBLUE);
	m_pMeshMngr->Print("Current Player Model: " + currentModel.name, REBLUE);
	m_pMeshMngr->PrintLine("            Left/Right: Move Model Left/Right", REBLUE);
	m_pMeshMngr->Print("Space: Jump", REBLUE);
	m_pMeshMngr->PrintLine("                                 I/O: Switch Between BO Boxes", REBLUE);
	m_pMeshMngr->Print("Tab: Change Model", REBLUE);
	m_pMeshMngr->PrintLine("                                  Enter: Spawn in Model", REBLUE);
	m_pMeshMngr->Print("Backspace: Clear Models", REBLUE);
	m_pMeshMngr->PrintLine("                          Hold RMB: Rotate Camera", REBLUE);

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
	super::Release(); //release the memory of the inherited fields
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		delete gameObjectList[i];
	}
}
#pragma region danielle_additions

//update the players current model
void AppClass::UpdateCurrentModel()
{
	Player.SetModel(currentModel.name);
}

//cycle through models to place
void AppClass::CycleModels()
{
	modelIndex++; modelIndex = modelIndex % 4;
	currentModel = MODELS[modelIndex];
	UpdateCurrentModel();
}

//spawn a model instance
void AppClass::SpawnModel(vector3 position)
{
	String nm = currentModel.name + "_";
	GameObject* temp = new GameObject(currentModel.path, nm + std::to_string(ID), position);
	
	if (gameObjectList.size() > 150) ClearModels();
	gameObjectList.push_back(temp);
	ID++;
}

//clear all model instances 
void AppClass::ClearModels()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		delete gameObjectList[i];
	}
	gameObjectList.clear();
}
#pragma endregion