#include "OcTreeClass.h"


OcTreeClass::OcTreeClass()
{
	m_pBOMngr = BOManagerSingleton::GetInstance();
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	octantCenter = vector3(0, 0, 0);
	octantMin = vector3(-70, -70, -70);
	octantMax = vector3(70, 70, 70);

	childrenNodes = std::vector<Node*>();

	idList = std::vector<int>();

	octreeNode = new Node(vector3(0, 0, 0), vector3(0, 0, 0), vector3(0, 0, 0));

	for (int i = 0; i < m_m4OctantList.size; i++)
	{
		glm::mat4 baseMat = glm::translate(GetChild(i)->getCenter()) * glm::scale(vector3(1, 1, 1) * 2.0f);

		m_m4OctantList[i] = baseMat;
	}
}

OcTreeClass::~OcTreeClass()
{
	delete this;
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

void OcTreeClass::CalculateOcTree() //Josh
{
	glm::vec3 halfCenter(octantCenter.x / 2, octantCenter.y / 2, octantCenter.z / 2);
	glm::vec3 fourthCenter(octantCenter.x / 4, octantCenter.y / 4, octantCenter.z / 4);

	glm::vec3 point1 = octantCenter - halfCenter;
	glm::vec3 point2 = octantCenter - fourthCenter;

	glm::vec3 point3 = octantCenter + halfCenter;
	glm::vec3 point4 = octantCenter + fourthCenter;
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
			m_pMeshMngr->AddCubeToRenderList(m_m4OctantList.at(i), a_v3Color, WIRE);
			m_pMeshMngr->AddCubeToRenderList(m_m4OctantList[i], a_v3Color, WIRE);
		}
	}
	if (!m_bVisible)
	{
		m_pMeshMngr->ClearRenderList(); //Not what is needed, but clears everything. Need to clear one thing at a time.
	}
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

void OcTreeClass::KillBranches(Node* target)
{
	target->setChildren(nullptr); //Michael's code
}

void OcTreeClass::CheckCollisions(bool showCollision)
{
}

void OcTreeClass::Release() //Michael's code
{
	for (int i = 0; i < childrenNodes.size; i++) {
		delete childrenNodes[i];
	}
	delete octreeNode;
	m_pBOMngr->ReleaseInstance();
	m_pMeshMngr->ReleaseInstance();
}

void OcTreeClass::TraverseForCollisions(bool showCollision)
{
}