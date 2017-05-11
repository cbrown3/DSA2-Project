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
	//Load a model onto the Mesh manager

	//m_pMeshMngr->LoadModel("gym.fbx", "World");

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
		vector3 pos = vector3(rand() % 10-5, 0, rand() % 10-5);
		GameObject* temp = new GameObject("substitute.fbx", "substitute_"+ID, pos);
		gameObjectList.push_back(temp);
		ID++;
	}

#pragma endregion

	/*GAMEOBJECT SYSTEM*/
	Player = GameObject(currentModel.path, currentModel.name);
	World = GameObject("gym.fbx", "World");
	Cow = GameObject("Minecraft\\Cow.bto", "Cow", vector3(2.5f, 0.0f, 0.0f));

}

void AppClass::Update(void)
{


	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	Player.Update();
	Cow.Update();
	World.Update();

#pragma region Collision Resolution
	if (renderBox)
	{
		if (Player.GetCollider()->IsColliding(Cow.GetCollider()))
		{
			Player.GetCollider()->DisplayOriented(RERED);
			Cow.GetCollider()->DisplayOriented(RERED);
		}
		else
		{
			Player.GetCollider()->DisplayOriented(REGREEN);
			Cow.GetCollider()->DisplayOriented(REGREEN);
		}
	}

	if (renderAlligned)
	{
		if (Player.GetCollider()->IsColliding(Cow.GetCollider()))
		{
			Player.GetCollider()->DisplayReAlligned(RERED);
			Cow.GetCollider()->DisplayReAlligned(RERED);
		}
		else
		{
			Player.GetCollider()->DisplayReAlligned(REGREEN);
			Cow.GetCollider()->DisplayReAlligned(REGREEN);
		}
	}

#pragma endregion


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
	m_pMeshMngr->AddInstanceToRenderList(Cow.GetName());

#pragma region danielle_additions

	//add all models to render list
	for (int i = 0; i < gameObjectList.size(); i++) {
		gameObjectList[i]->Update();
		//FOR NOW: COLLIDER IS YELLOW
		if (renderBox) gameObjectList[i]->GetCollider()->DisplayOriented(REYELLOW);
		if (renderAlligned) gameObjectList[i]->GetCollider()->DisplayReAlligned(REYELLOW);
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
	m_pMeshMngr->PrintLine("                 Up/Down: Move Model Forward/Backward");
	m_pMeshMngr->Print("Current Player Model: " + currentModel.name);
	m_pMeshMngr->PrintLine("          Left/Right: Move Model Left/Right");
	m_pMeshMngr->Print("Shift + Up/Down: Move Model Up/Down");
	m_pMeshMngr->PrintLine("           Number Keys: Change Model");
	m_pMeshMngr->Print("Hold RMB: Rotate Camera");

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
	for (int i = 0; i < gameObjectList.size(); i++) {
		delete gameObjectList[i];
	}
}
#pragma region danielle_additions

//update the players current model
void AppClass::UpdateCurrentModel() {
	Player.SetModel(currentModel.name);
}

//cycle through models to place
void AppClass::CycleModels() {
	modelIndex++; modelIndex = modelIndex % 4;
	currentModel = MODELS[modelIndex];
	UpdateCurrentModel();
}

//spawn a model instance
void AppClass::SpawnModel(vector3 position) {
	String nm = currentModel.name + "_";
	GameObject* temp = new GameObject(currentModel.path, nm + std::to_string(ID), position);
	
	if (gameObjectList.size() > 50) gameObjectList.pop_back();
	gameObjectList.push_back(temp);
	ID++;
}

//clear all model instances 
void AppClass::ClearModels() {
	for (int i = 0; i < gameObjectList.size(); i++) {
		delete gameObjectList[i];
	}
	gameObjectList.clear();
}
#pragma endregion