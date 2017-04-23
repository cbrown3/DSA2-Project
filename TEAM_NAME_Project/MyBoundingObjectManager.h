#pragma once
#include "RE\ReEng.h"
#include "MyBoundingBoxClass.h"


/*
singleton manager for bounding objects
*/
class MyBoundingObjectManager
{
	uint m_nObjectCount = 0;
	static MyBoundingObjectManager* m_pInstance; // instance pointer
	std::vector<MyBoundingBoxClass*> m_nBoxes; //list of bounding objects
	MeshManagerSingleton* m_pMeshMngr = nullptr;
	std::vector<std::vector<int>> m_CollidingIndices; // list of list colliding indicies
	std::map<String, uint> m_mapIndex;

private:
	//constructor
	MyBoundingObjectManager()
	{
		Init();
	}
	//copy constructor
	MyBoundingObjectManager(MyBoundingObjectManager const& other) {};
	//copy assignment operator
	MyBoundingObjectManager& operator=(MyBoundingObjectManager const& other) { return *this; };
	//destructor
	~MyBoundingObjectManager() { Release(); };

	//clear the manager data
	void Release()
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

	void Init()
	{
		m_pMeshMngr = MeshManagerSingleton::GetInstance();
		m_nObjectCount = 0;
	};

	void CheckCollisions()
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

public:
	//get or crreate instance of the manager
	static MyBoundingObjectManager* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new MyBoundingObjectManager();

		return m_pInstance;
	};

	//clear/reser instance of the manager
	static void ReleaseInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	};

	void AddObject(std::vector<vector3> a_Vertex, String a_Name)
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

	void AddObject(String a_Name)
	{
		std::vector<vector3> vertex = m_pMeshMngr->GetVertexList(a_Name);
		AddObject(vertex, a_Name);
		SetModelMatrix(m_pMeshMngr->GetModelMatrix(a_Name), a_Name);
	};

	void SetModelMatrix(matrix4 a_ModelMatrix, String a_Index)
	{
		int nIndex = this->GetIndex(a_Index);
		if (nIndex < 0)
			return;

		m_nBoxes[nIndex]->SetModelMatrix(a_ModelMatrix);
	};

	void DisplaySphere(int a_Index, vector3 a_v3Color = REDEFAULT)
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

	void DisplaySphere(String a_Name = "ALL", vector3 a_v3Color = REDEFAULT)
	{
		int nIndex = GetIndex(a_Name);
		DisplaySphere(nIndex, a_v3Color);
	};

	void DisplayOriented(int a_Index, vector3 a_v3Color = REDEFAULT)
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

	void DisplayOriented(String a_Name = "ALL", vector3 a_v3Color = REDEFAULT)
	{
		int nIndex = GetIndex(a_Name);
		DisplayOriented(nIndex, a_v3Color);
	};

	void DisplayReAlligned(int a_Index, vector3 a_v3Color = REDEFAULT)
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

	void DisplayReAlligned(String a_Name = "ALL", vector3 a_v3Color = REDEFAULT)
	{
		int nIndex = GetIndex(a_Name);
		DisplayReAlligned(nIndex, a_v3Color);
	};

	std::vector<int> GetCollidingVector(String a_Index)
	{
		int nIndex = GetIndex(a_Index);
		if (nIndex < 0)
		{
			std::vector<int> empty;
			return empty;
		}
		return GetCollidingVector(static_cast<uint>(nIndex));
	};

	std::vector<int> GetCollidingVector(uint a_Index)
	{
		if (a_Index >= m_nObjectCount)
		{
			std::vector<int> empty;
			return empty;
		}
		return m_CollidingIndices[a_Index];
	};

	int GetIndex(String a_Index)
	{
		auto var = m_mapIndex.find(a_Index);

		if (var == m_mapIndex.end())
			return -1;
		return var->second;
	};

	MyBoundingBoxClass* GetBoundingObject(uint a_Index)
	{
		if (a_Index < m_nObjectCount)
			return m_nBoxes[a_Index];

		return nullptr;
	};

	MyBoundingBoxClass* GetBoundingObject(String a_Index)
	{
		int nIndex = GetIndex(a_Index);
		return GetBoundingObject(nIndex);
	};

	void Update()
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			m_CollidingIndices[nObject].clear();
		}
		CheckCollisions();
	};


	void RederOptions(int RenderArgs)
	{
		if (RenderArgs > m_nBoxes.size()) return;

		switch (RenderArgs)
		{
		case 0:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
			}
			break;
		case 1:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[0]->RenderSphere(true);
			}
			break;
		case 2:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[1]->RenderSphere(true);
			}
			break;
		case 3:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[2]->RenderSphere(true);
			}
			break;
		case 4:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[3]->RenderSphere(true);
			}
			break;
		case 5:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[4]->RenderSphere(true);
			}
			break;
		case 6:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[5]->RenderSphere(true);
			}
			break;
		case 7:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[6]->RenderSphere(true);
			}
			break;
		case 8:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[7]->RenderSphere(true);
			}
			break;
		case 9:
			for (int i = 0; i < m_nBoxes.size(); i++)
			{
				m_nBoxes[i]->RenderSphere(false);
				m_nBoxes[8]->RenderSphere(true);
			}
			break;
		default:
			break;
		}
	};
};

