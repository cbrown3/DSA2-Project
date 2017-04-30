#pragma once

#include "RE\ReEngAppClass.h"
#include "RigidBody.h"
#include "MyBoundingObjectManager.h"

class GameObject
{
	MeshManagerSingleton* m_pMeshMngr;
	String name;
	String filePath;
	MyBoundingBoxClass* collider;
	RigidBody rigidBody;
	
	vector3 position;
	vector3 size;
	vector3 rotation;
	matrix4 transformMatrix;

public:
	GameObject();
	GameObject(String filePath, String name);
	GameObject(String filePath, String name, vector3 position);

	void translate(vector3 translation);
	void scale(vector3 size);
	void rotate(vector3 rotation);
	void calcTransformMatrix(); //calculate transform matrix based on pos and rot

	void Update(); //for physics
	void SetMatrix(); //apply transformation on model

	matrix4 GetTransformMatrix();
	vector3 GetPosition();
	vector3 GetRotation();

	MyBoundingBoxClass* GetCollider();
	RigidBody GetRigidBody();
	String GetName();


	~GameObject();
};

