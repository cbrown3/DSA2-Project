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
	//Extra Code that needs added.
	for (int i = 0; i < m_m4OctantList.size; i++)
	{
		//Commented out, theory code glm::mat4 baseMat = glm::translate(GetChild(i)->getCenter()) * glm::scale(vector3(1,1,1) * 2.0f); 

		//Commented out, theory code m_m4OctantList[i] = baseMat;
	}
}

OcTreeClass::OcTreeClass(std::vector<Node*> parents, std::vector<Node*> children)
{
}

OcTreeClass::~OcTreeClass()
{
}

void OcTreeClass::ToggleVisibility() //Josh
{
	if (m_bVisible)
	{
		m_bVisible = false;
	}
	if (!m_bVisible)
	{
		m_bVisible = true;
	}
}

void OcTreeClass::Recalculate()
{
}

vector3 OcTreeClass::GetOctantMin() //Josh
{
	return octantMin;
}

vector3 OcTreeClass::GetOctantMax() //Josh
{
	return octantMax;
}

vector3 OcTreeClass::GetOctantCenter() //Josh
{
	return octantCenter;
}

void OcTreeClass::Display(vector3 a_v3Color) //Josh
{
	if (m_bVisible)
	{
		for (int i = 0; i < m_m4OctantList.size; i++)
		{
			m_MeshMngr->AddCubeToRenderList(m_m4OctantList[i], a_v3Color, WIRE);
		}
	}
	if (!m_bVisible)
	{
		m_MeshMngr->ClearRenderList(); //Not what is needed, but clears everything. Need to clear one thing at a time.
	}
}

bool OcTreeClass::IsColliding(std::vector<Node*> nodeList)
{
	return false;
}

void OcTreeClass::ClearBOList()
{
}

Node* OcTreeClass::GetChild(uint a_nChild) //Josh
{
	return childrenNodes[a_nChild];
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