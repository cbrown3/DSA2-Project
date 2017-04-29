#include "GameObject.h"



GameObject::GameObject()
{
}

GameObject::GameObject(String filePath, String name)
{
}

GameObject::GameObject(String filePath, String name, vector3 position)
{
}

void GameObject::translate(vector3 translation)
{
}

void GameObject::scale(vector3 scale)
{
}

void GameObject::rotate(quaternion rotation)
{
}

void GameObject::calcTransformMatrix()
{
}

void GameObject::Update()
{
}

void GameObject::SetMatrix()
{
}

matrix4 GameObject::GetTransformMatrix()
{
	return matrix4();
}

vector3 GameObject::GetPosition()
{
	return vector3();
}

quaternion GameObject::GetRotation()
{
	return quaternion();
}

MyBoundingBoxClass GameObject::GetCollider()
{
	return MyBoundingBoxClass();
}

RigidBody GameObject::GetRigidBody()
{
	return RigidBody();
}

String GameObject::GetName()
{
	return String();
}


GameObject::~GameObject()
{
}
