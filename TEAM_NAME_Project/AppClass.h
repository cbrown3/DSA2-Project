/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09 (Last Modified on: 15/11)
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingSphereClass.h"
#include "MyBoundingBoxClass.h"
#include "MyBoundingObjectManager.h"
#include "RigidBody.h"
#include "GameObject.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

static int ID;

struct MODEL {
	String name;
	String path;

	MODEL() {
		name = "none"; path = "none";
	}

	MODEL(String path, String name) {
		this->name = name;
		this->path = path;
		ModelManagerSingleton::GetInstance()->LoadModel(path, name);
	}

	void setModel(String path, String name) {
		this->name = name;
		this->path = path;
	}
};


class AppClass : public ReEngAppClass
{
	bool renderCollision;
	bool renderBox;
	bool renderAlligned;
	bool renderSphere;
	vector3 m_v3Position;
	float mass;
	RigidBody rBody;
	quaternion orientation;
	GameObject Player;
	GameObject World;

	enum MODELNAMES { ninja, substitute, snail, bus};
	std::vector<MODEL> MODELS;
	MODEL  currentModel;
	int modelIndex;

	std::vector<GameObject*> gameObjectList;
public:
	typedef ReEngAppClass super;
	/*
	USAGE: Constructor
	ARGUMENTS: 
	- HINSTANCE hInstance -> Instance of the window
	- LPWSTR lpCmdLine -> Command line
	- int nCmdShow -> Number or arguments
	- bool a_bConsole = false -> create command window flag
	OUTPUT: ---
	*/
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void) { Release(); }
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
	/*
	USAGE: Initialize ReEng variables necessary to create the window
	ARGUMENTS: String a_sWindowName -> Name of the window
	OUTPUT: ---
	*/
	virtual void InitWindow(String a_sWindowName) final;
	/*
	USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitVariables(void) final;
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void) final;
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Display(void) final;
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessKeyboard(void) final;
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void) final;
	/*
	USAGE: Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Release(void) final;
	void UpdateCurrentModel();
	void CycleModels();
	void SpawnModel(vector3 position);
	void ClearModels();
};
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
#endif //__APPLICATION_H_
