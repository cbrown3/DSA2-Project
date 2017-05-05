#include "OcTreeClass.h"


OcTreeClass::OcTreeClass(uint a_nMaxLevel, uint a_nIdealBOCount)
{
}

OcTreeClass::OcTreeClass(vector3 a_v3Center, float a_fSize)
{
}

OcTreeClass::OcTreeClass(OcTreeClass const & other)
{
}

OcTreeClass & OcTreeClass::operator=(OcTreeClass const & other)
{
	// TODO: insert return statement here
}

OcTreeClass::~OcTreeClass()
{
}

void OcTreeClass::Swap(OcTreeClass & other)
{
}

float OcTreeClass::GetSize(void)
{
	return 0.0f;
}

vector3 OcTreeClass::GetCenterGlobal(void)
{
	return vector3();
}

vector3 OcTreeClass::GetMinGlobal(void)
{
	return vector3();
}

vector3 OcTreeClass::GetMaxGlobal(void)
{
	return vector3();
}

bool OcTreeClass::IsColliding(uint a_nBOIndex)
{
	return false;
}

void OcTreeClass::Display(uint a_nIndex, vector3 a_v3Color)
{
}

void OcTreeClass::Display(vector3 a_v3Color)
{
}

void OcTreeClass::DisplayLeafs(vector3 a_v3Color)
{
}

void OcTreeClass::ClearBOList(void)
{
}

void OcTreeClass::Subdivide(void)
{
}

OcTreeClass * OcTreeClass::GetChild(uint a_nChild)
{
	return nullptr;
}

OcTreeClass * OcTreeClass::GetParent(void)
{
	return nullptr;
}

bool OcTreeClass::IsLeaf(void)
{
	return false;
}

bool OcTreeClass::ContainsMoreThan(uint a_nBOs)
{
	return false;
}

void OcTreeClass::KillBranches(void)
{
}

void OcTreeClass::ConstructTree(uint a_nMaxLevel)
{
}

void OcTreeClass::AssignIDtoBO(void)
{
}

void OcTreeClass::CheckCollisions(int a_nBODisplay)
{
}

void OcTreeClass::Release(void)
{
}

void OcTreeClass::Init(void)
{
}

void OcTreeClass::TraverseForCollisions(int a_nBODisplay)
{
}

void OcTreeClass::ConstructList(void)
{
}
