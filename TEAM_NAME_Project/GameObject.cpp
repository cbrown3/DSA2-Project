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
	return transformMatrix;
}

vector3 GameObject::GetPosition()
{
	return position;
}

quaternion GameObject::GetRotation()
{
	return rotation;
}

MyBoundingBoxClass GameObject::GetCollider()
{
	return collider;
}

RigidBody GameObject::GetRigidBody()
{
	return rigidBody;
}

String GameObject::GetName()
{
	return name;
}


GameObject::~GameObject()
{
}
