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
	MyBoundingObjectManager();
	//copy constructor
	MyBoundingObjectManager(MyBoundingObjectManager const& other);
	//copy assignment operator
	MyBoundingObjectManager& operator=(MyBoundingObjectManager const& other);
	//destructor
	~MyBoundingObjectManager();

	//clear the manager data
	void Release();

	void Init();

	void CheckCollisions();

public:
	//get or crreate instance of the manager
	static MyBoundingObjectManager* GetInstance();

	//clear/reser instance of the manager
	static void ReleaseInstance();

	void AddObject(std::vector<vector3> a_Vertex, String a_Name);

	void AddObject(String a_Name);

	void SetModelMatrix(matrix4 a_ModelMatrix, String a_Index);

	void DisplaySphere(int a_Index, vector3 a_v3Color = REDEFAULT);

	void DisplaySphere(String a_Name = "ALL", vector3 a_v3Color = REDEFAULT);

	void DisplayOriented(int a_Index, vector3 a_v3Color = REDEFAULT);

	void DisplayOriented(String a_Name = "ALL", vector3 a_v3Color = REDEFAULT);

	void DisplayReAlligned(int a_Index, vector3 a_v3Color = REDEFAULT);

	void DisplayReAlligned(String a_Name = "ALL", vector3 a_v3Color = REDEFAULT);

	std::vector<int> GetCollidingVector(String a_Index);

	std::vector<int> GetCollidingVector(uint a_Index);

	int GetIndex(String a_Index);

	MyBoundingBoxClass* GetBoundingObject(uint a_Index);

	MyBoundingBoxClass* GetBoundingObject(String a_Index);

	void Update();

};

