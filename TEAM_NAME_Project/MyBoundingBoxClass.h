#pragma once
#include "RE\ReEng.h"
#include "RigidBody.h"

class MyBoundingBoxClass
{
	float m_fRadius = 0.0f; //radius of the box
	vector3 m_v3CenterLocal = vector3(0.0f); //center of the sphere in local space
	vector3 m_v3CenterGlobal = vector3(0.0f); //center of the sphere in global space
	matrix4 m_m4ToWorld = IDENTITY_M4; //matrix that takes you from local to global space
	MeshManagerSingleton* m_pMeshMngr = nullptr; //for drawing the sphere

	vector3 m_v3Max;
	vector3 m_v3Min;
	vector3 m_v3Size;

	vector3 m_v3HalfWidth;
	vector3 m_v3HalfWidthG;

	//global versions of the vectors
	vector3 m_v3MaxG;
	vector3 m_v3MinG;
	vector3 m_v3SizeG;

private:

	void Release();

	void Init();

public:
	MyBoundingBoxClass(std::vector<vector3> vertexList);
	MyBoundingBoxClass(MyBoundingBoxClass const& other);
	MyBoundingBoxClass& operator=(MyBoundingBoxClass const& other);
	~MyBoundingBoxClass();

	void Swap(MyBoundingBoxClass& other);

	void SetModelMatrix(matrix4 a_m4ToWorld);
	matrix4 GetModelMatrix();

	float GetRadius();

	vector3 GetCenterLocal();
	vector3 GetCenterGlobal();

	vector3 GetHalfWidth();
	vector3 GetHalfWidthG();

	vector3 GetMin();
	vector3 GetMax();
	vector3 GetMinG();
	vector3 GetMaxG();

	bool IsColliding(MyBoundingBoxClass* const a_pOther);

	void DisplaySphere(vector3 a_v3Color = REDEFAULT);
	void DisplayOriented(vector3 a_v3Color = REDEFAULT);
	void DisplayReAlligned(vector3 a_v3Color = REDEFAULT);
};