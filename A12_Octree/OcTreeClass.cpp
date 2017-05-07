#include "OcTreeClass.h"


OcTreeClass::OcTreeClass(OcTreeClass const & other)
{
}

OcTreeClass & OcTreeClass::operator=(OcTreeClass const & other)
{
	// TODO: insert return statement here
}

OcTreeClass::OcTreeClass()
{
	m_pBOMngr = BOManagerSingleton::GetInstance();
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	octantCenter = vector3(0, 0, 0);
	octantMin = vector3(-70, -70, -70);
	octantMax = vector3(70, 70, 70);

	childrenNodes = std::vector<Node*>();

	idList = std::vector<int>();

	octreeNode = new Node();
}

OcTreeClass::OcTreeClass(std::vector<Node*> parents)
{
}

OcTreeClass::OcTreeClass(std::vector<Node*> parents, std::vector<Node*> children)
{
}

OcTreeClass::~OcTreeClass()
{
	delete this;
}

void OcTreeClass::ToggleVisibility()
{
}

void OcTreeClass::Recalculate()
{
}

vector3 OcTreeClass::GetOctantMin()
{
	return vector3();
}

vector3 OcTreeClass::GetOctantMax()
{
	return vector3();
}

vector3 OcTreeClass::GetOctantCenter()
{
	return vector3();
}

void OcTreeClass::Display(vector3 a_v3Color)
{
}

bool OcTreeClass::IsColliding(std::vector<Node*> nodeList)
{
	return false;
}

void OcTreeClass::ClearBOList()
{
}

OcTreeClass * OcTreeClass::GetSelf()
{
	return this;
}

void OcTreeClass::KillBranches()
{
}

void OcTreeClass::CheckCollisions(bool showCollision)
{
}

void OcTreeClass::Release()
{
}

void OcTreeClass::Init()
{
}

void OcTreeClass::TraverseForCollisions(bool showCollision)
{
}