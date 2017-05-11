#include "GameObject.h"



GameObject::GameObject()
{
	name = "name";
	collider = nullptr;

	rigidBody = RigidBody();

	position = vector3();
	size = vector3(1.0f, 1.0f, 1.0f);
	rotation = vector3();
	transformMatrix = IDENTITY_M4;
}

GameObject::GameObject(String filePath, String name)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->LoadModel(filePath, name);

	this->name = name;
	collider = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList(name));

	rigidBody = RigidBody();

	position = rigidBody.state.position; //Position is held by the states position
	size = vector3(1.0f, 1.0f, 1.0f);
	rotation = glm::vec3(rigidBody.state.orientation.x, rigidBody.state.orientation.y, rigidBody.state.orientation.z);
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
	//transformMatrix = glm::translate(position) * glm::scale(size) * glm::rotate(0.0f, rotation);
	transformMatrix = IDENTITY_M4;
}

GameObject::GameObject(String filePath, String name, vector3 position, vector3 rotation)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->LoadModel(filePath, name);

	this->name = name;
	collider = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList(name));

	rigidBody = RigidBody();

	this->position = position;
	this->size = vector3(1.0f, 1.0f, 1.0f);
	this->rotation = rotation;
	//transformMatrix = glm::translate(position) * glm::scale(size) * glm::rotate(0.0f, rotation);
	transformMatrix = IDENTITY_M4;
}

void GameObject::translate(vector3 translation)
{
	rigidBody.state.position += translation;
	position += translation;
}

void GameObject::scale(vector3 scale)
{
	this->size+= scale;
}

void GameObject::rotate(vector3 rotation)
{
	rigidBody.state.orientation.x += rotation.x;
	rigidBody.state.orientation.y += rotation.y;
	rigidBody.state.orientation.z += rotation.z;
	this->rotation += rotation;

	//maybe make separate method that will rotate this way? 
	//glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
}

#pragma region Josh_McMahan_Additions_April_30th
void GameObject::RigidTrans(vector3 ForceArg) //Takes in a force and applies it to the velocity. Should apply to the acceleration but this is rough code that NEEDS TO BE FIXED!!! - Josh
{
	rigidBody.state.velocity += ForceArg; //Ugh, should be affecting the momentum - Josh
}

void GameObject::RigidRotate(vector3 RotationArg) //Takes in a Roation arg that is essentially a force and applies it to the object's orientation. Need to be better by affecting inertia and such. - Josh
{
	rigidBody.state.angularVelocity += RotationArg; //Fix to make better later - Josh (MAKE A QUAT LATER PLZ)
}
#pragma endregion

void GameObject::calcTransformMatrix()
{
	//scale, rotate, translate
	transformMatrix = IDENTITY_M4;

	//scale
	transformMatrix = glm::scale(transformMatrix, size);
	
	//get quaternion from rotation vector
	//quaternion rot = glm::quat(rotation);
	//transformMatrix *= ToMatrix4(rot); //rotate

	//just use the vector for rotation
	transformMatrix *= glm::yawPitchRoll(rotation.x, rotation.y, rotation.z);

	//tralnslate
	transformMatrix = glm::translate(transformMatrix, position); 
}

void GameObject::Update()
{
	if(position.y>0)
	RigidTrans(vector3(0.0f, -0.01f, 0.0f));
	else position.y = 0;

	translate(rigidBody.state.velocity);
	rotate(rigidBody.state.angularVelocity);
	
	rigidBody.state.slowDown();
	rigidBody.state.continueToRotate();

	calcTransformMatrix();
	SetMatrix();

	collider->SetModelMatrix(transformMatrix);
}

void GameObject::SetMatrix()
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->SetModelMatrix(transformMatrix, name);
}

matrix4 GameObject::GetTransformMatrix()
{
	return transformMatrix;
}

vector3 GameObject::GetPosition()
{
	return position;
}

vector3 GameObject::GetRotation()
{
	return rotation;
}

MyBoundingBoxClass* GameObject::GetCollider()
{
	return collider;
}

void GameObject::SetModel(String modelName) {

	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	this->name = modelName;
	collider = new MyBoundingBoxClass(m_pMeshMngr->GetVertexList(name));

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
