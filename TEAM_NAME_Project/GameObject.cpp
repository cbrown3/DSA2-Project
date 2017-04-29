#include "GameObject.h"



GameObject::GameObject(String filePath, String name)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->LoadModel(filePath, name);

	this->name = name;
	collider = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList(name));

	rigidBody = RigidBody();

	position = vector3();
	size = vector3(1.0f, 1.0f, 1.0f);
	rotation = vector3();
	transformMatrix = IDENTITY_M4;
}

GameObject::GameObject(String filePath, String name, vector3 position)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->LoadModel(filePath, name);

	this->name = name;
	collider = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList(name));

	rigidBody = RigidBody();

	this->position = position;
	size = vector3(1.0f, 1.0f, 1.0f);
	rotation = vector3();
	transformMatrix = IDENTITY_M4;
}

void GameObject::translate(vector3 translation)
{
	position += translation;
}

void GameObject::scale(vector3 scale)
{
	this->size+= scale;
}

void GameObject::rotate(vector3 rotation)
{
	this->rotation += rotation;

	//maybe make separate method that will rotate this way? 
	//glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
}

void GameObject::calcTransformMatrix()
{
	//scale, rotate, translate
	transformMatrix = IDENTITY_M4;

	//scale
	transformMatrix = glm::scale(transformMatrix, size);
	
	//get quaternion from rotation vector
	quaternion rot = glm::quat(rotation);
	transformMatrix *= ToMatrix4(rot); //rotate

	//tralnslate
	transformMatrix = glm::translate(transformMatrix, position); 
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
