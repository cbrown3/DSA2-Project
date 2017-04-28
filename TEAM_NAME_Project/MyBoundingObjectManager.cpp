#pragma once
#include "MyBoundingObjectManager.h"

MyBoundingObjectManager* MyBoundingObjectManager::m_pInstance = nullptr;

//constructor
MyBoundingObjectManager::MyBoundingObjectManager()
{
	Init();
}
//copy constructor
MyBoundingObjectManager::MyBoundingObjectManager(MyBoundingObjectManager const& other)
{

}
//copy assignment operator
MyBoundingObjectManager& MyBoundingObjectManager::operator=(MyBoundingObjectManager const& other)
{
	return *this;
}
//destructor
MyBoundingObjectManager::~MyBoundingObjectManager()
{
	Release(); 
}

//clear the manager data
void MyBoundingObjectManager::Release()
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		if (m_nBoxes[nObject] != nullptr)
		{
			delete m_nBoxes[nObject];
			m_nBoxes[nObject] = nullptr;
		}
		m_CollidingIndices[nObject].clear();
	}
	m_nBoxes.clear();
	m_CollidingIndices.clear();
};

void MyBoundingObjectManager::Init()
{
	//m_pInstance = GetInstance();
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_nObjectCount = 0;
	m_nBoxes = std::vector<MyBoundingBoxClass*>();
	m_CollidingIndices = std::vector<std::vector<int>>();
	m_mapIndex = std::map<String, uint>();
};

void MyBoundingObjectManager::CheckCollisions()
{
	for (uint nObjectA = 0; nObjectA < m_nObjectCount - 1; nObjectA++)
	{
		for (uint nObjectB = nObjectA + 1; nObjectB < m_nObjectCount; nObjectB++)
		{
			if (m_nBoxes[nObjectA]->IsColliding(m_nBoxes[nObjectB]))
			{
				m_CollidingIndices[nObjectA].push_back(nObjectB);
				m_CollidingIndices[nObjectB].push_back(nObjectA);
			}
		}
	}
};

MyBoundingObjectManager* MyBoundingObjectManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new MyBoundingObjectManager();

	return m_pInstance;
};

//clear/reser instance of the manager
void MyBoundingObjectManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
};

void MyBoundingObjectManager::AddObject(std::vector<vector3> a_Vertex, String a_Name)
{
	MyBoundingBoxClass* pBox = new MyBoundingBoxClass(a_Vertex);
	if (pBox != nullptr)
	{
		m_nBoxes.push_back(pBox);
		m_mapIndex[a_Name] = m_nObjectCount;
	}
	m_nObjectCount = m_nBoxes.size();
	std::vector<int> lVector;
	m_CollidingIndices.push_back(lVector);
};

void MyBoundingObjectManager::AddObject(String a_Name)
{
	std::vector<vector3> vertex = m_pMeshMngr->GetVertexList(a_Name);
	AddObject(vertex, a_Name);
	SetModelMatrix(m_pMeshMngr->GetModelMatrix(a_Name), a_Name);
};

void MyBoundingObjectManager::SetModelMatrix(matrix4 a_ModelMatrix, String a_Index)
{
	int nIndex = this->GetIndex(a_Index);
	if (nIndex < 0)
		return;

	m_nBoxes[nIndex]->SetModelMatrix(a_ModelMatrix);
};

void MyBoundingObjectManager::DisplaySphere(int a_Index, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_Index >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_Index >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_CollidingIndices[a_Index].size() > 0)
				v3Color = RERED;
		}
		m_nBoxes[a_Index]->DisplaySphere(v3Color);
		v3Color = a_v3Color;
	}
	else //all objects sent
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_CollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_nBoxes[nObject]->DisplaySphere(v3Color);
			v3Color = a_v3Color;
		}
	}
};

void MyBoundingObjectManager::DisplaySphere(String a_Name, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_Name);
	DisplaySphere(nIndex, a_v3Color);
};

void MyBoundingObjectManager::DisplayOriented(int a_Index, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_Index >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_Index >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_CollidingIndices[a_Index].size() > 0)
				v3Color = RERED;
		}
		m_nBoxes[a_Index]->DisplayOriented(v3Color);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_CollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_nBoxes[nObject]->DisplayOriented(v3Color);
			v3Color = a_v3Color;
		}
	}
};

void MyBoundingObjectManager::DisplayOriented(String a_Name, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_Name);
	DisplayOriented(nIndex, a_v3Color);
};

void MyBoundingObjectManager::DisplayReAlligned(int a_Index, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_Index >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists we are talking about a single asset
	if (a_Index >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_CollidingIndices[a_Index].size() > 0)
				v3Color = RERED;
		}
		m_nBoxes[a_Index]->DisplayReAlligned(v3Color);
	}
	else //we want to render all of them
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_CollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_nBoxes[nObject]->DisplayReAlligned(v3Color);
			v3Color = a_v3Color;
		}
	}
};

void MyBoundingObjectManager::DisplayReAlligned(String a_Name, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_Name);
	DisplayReAlligned(nIndex, a_v3Color);
};

std::vector<int> MyBoundingObjectManager::GetCollidingVector(String a_Index)
{
	int nIndex = GetIndex(a_Index);
	if (nIndex < 0)
	{
		std::vector<int> empty;
		return empty;
	}
	return GetCollidingVector(static_cast<uint>(nIndex));
};

std::vector<int> MyBoundingObjectManager::GetCollidingVector(uint a_Index)
{
	if (a_Index >= m_nObjectCount)
	{
		std::vector<int> empty;
		return empty;
	}
	return m_CollidingIndices[a_Index];
};

int MyBoundingObjectManager::GetIndex(String a_Index)
{
	auto var = m_mapIndex.find(a_Index);

	if (var == m_mapIndex.end())
		return -1;
	return var->second;
};

MyBoundingBoxClass* MyBoundingObjectManager::GetBoundingObject(uint a_Index)
{
	if (a_Index < m_nObjectCount)
		return m_nBoxes[a_Index];

	return nullptr;
};

MyBoundingBoxClass* MyBoundingObjectManager::GetBoundingObject(String a_Index)
{
	int nIndex = GetIndex(a_Index);
	return GetBoundingObject(nIndex);
};

void MyBoundingObjectManager::Update()
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		m_CollidingIndices[nObject].clear();
	}
	CheckCollisions();
};