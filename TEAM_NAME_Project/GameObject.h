#pragma once

#include "RE\ReEngAppClass.h"
#include "RigidBody.h"
#include "MyBoundingBoxClass.h"

class GameObject
{
	String name;
	MyBoundingBoxClass collider;
	RigidBody rigidBody;

	vector3 position;
	vector3 scale;
	quaternion rotation;
	matrix4 transformMatrix;

public:
	GameObject();
	GameObject(String name);
	GameObject(String name, vector3 position);

	void translate(vector3 translation);
	void scale(vector3 scale);
	void rotate(quaternion rotation);
	void calcTransformMatrix(); //calculate transform matrix based on pos and rot

	void Update(); //for physics
	void SetMatrix(); //apply transformation on model

	matrix4 GetTransformMatrix();
	vector3 GetPosition();
	quaternion GetRotation();

	MyBoundingBoxClass GetCollider();
	RigidBody GetRigidBody();
	String GetName();


	~GameObject();
};

