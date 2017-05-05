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
}

OcTreeClass::OcTreeClass(std::vector<Node*> parents)
{
}

OcTreeClass::OcTreeClass(std::vector<Node*> parents, std::vector<Node*> children)
{
}

OcTreeClass::~OcTreeClass()
{
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

Node* OcTreeClass::GetChild(uint a_nChild)
{
	return nullptr;
}

OcTreeClass * OcTreeClass::GetSelf()
{
	return this;
}

void OcTreeClass::KillBranches()
{
}

void OcTreeClass::AssignIDtoBO()
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