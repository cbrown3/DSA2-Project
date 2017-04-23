#include "MyBoundingBoxClass.h"

void MyBoundingBoxClass::Init()
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3CenterLocal = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3CenterGlobal = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);

	m_fRadius = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

void MyBoundingBoxClass::Swap(MyBoundingBoxClass & other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3CenterLocal, other.m_v3CenterLocal);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterGlobal, other.m_v3CenterGlobal);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}

void MyBoundingBoxClass::Release()
{
}

MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList)
{
	Init();

	uint nVertexCount = vertexList.size();

	if (nVertexCount == 0)
		return;

	m_v3Max = m_v3Min = vertexList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > vertexList[nVertex].x) //If min is larger than current
			m_v3Min.x = vertexList[nVertex].x;
		else if (m_v3Max.x < vertexList[nVertex].x)//if max is smaller than current
			m_v3Max.x = vertexList[nVertex].x;

		if (m_v3Min.y > vertexList[nVertex].y) //If min is larger than current
			m_v3Min.y = vertexList[nVertex].y;
		else if (m_v3Max.y < vertexList[nVertex].y)//if max is smaller than current
			m_v3Max.y = vertexList[nVertex].y;

		if (m_v3Min.z > vertexList[nVertex].z) //If min is larger than current
			m_v3Min.z = vertexList[nVertex].z;
		else if (m_v3Max.z < vertexList[nVertex].z)//if max is smaller than current
			m_v3Max.z = vertexList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3CenterLocal = (m_v3Min + m_v3Max) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterLocal, m_v3Max);

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterGlobal = m_v3CenterLocal;
	m_v3HalfWidthG = m_v3HalfWidth;

}

MyBoundingBoxClass::MyBoundingBoxClass(MyBoundingBoxClass const & other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3CenterLocal = other.m_v3CenterLocal;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterGlobal = other.m_v3CenterGlobal;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;

	m_fRadius = other.m_fRadius;

	m_pMeshMngr = other.m_pMeshMngr;
}

MyBoundingBoxClass & MyBoundingBoxClass::operator=(MyBoundingBoxClass const & other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBoundingBoxClass temp(other);
		Swap(temp);
	}
	return *this;
}

MyBoundingBoxClass::~MyBoundingBoxClass() { Release(); }

//Accessors
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the Object
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		v3Corner[nVertex] = vector3(m_m4ToWorld * vector4(v3Corner[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxG = m_v3MinG = v3Corner[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinG.x > v3Corner[nVertex].x) //If min is larger than current
			m_v3MinG.x = v3Corner[nVertex].x;
		else if (m_v3MaxG.x < v3Corner[nVertex].x)//if max is smaller than current
			m_v3MaxG.x = v3Corner[nVertex].x;

		if (m_v3MinG.y > v3Corner[nVertex].y) //If min is larger than current
			m_v3MinG.y = v3Corner[nVertex].y;
		else if (m_v3MaxG.y < v3Corner[nVertex].y)//if max is smaller than current
			m_v3MaxG.y = v3Corner[nVertex].y;

		if (m_v3MinG.z > v3Corner[nVertex].z) //If min is larger than current
			m_v3MinG.z = v3Corner[nVertex].z;
		else if (m_v3MaxG.z < v3Corner[nVertex].z)//if max is smaller than current
			m_v3MaxG.z = v3Corner[nVertex].z;
	}
	m_v3CenterGlobal = (m_v3MinG + m_v3MaxG) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthG = (m_v3MaxG - m_v3MinG) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3MaxG);
}

vector3 MyBoundingBoxClass::GetHalfWidthG() { return vector3(); }
vector3 MyBoundingBoxClass::GetMin() { return vector3(); }
vector3 MyBoundingBoxClass::GetMax() { return vector3(); }
vector3 MyBoundingBoxClass::GetMinG() { return vector3(); }
vector3 MyBoundingBoxClass::GetMaxG() { return vector3(); }
vector3 MyBoundingBoxClass::GetCenterLocal() { return m_v3CenterLocal; }
vector3 MyBoundingBoxClass::GetCenterGlobal() { return m_v3CenterGlobal; }
vector3 MyBoundingBoxClass::GetHalfWidth() { return m_v3HalfWidth; }
float MyBoundingBoxClass::GetRadius() { return m_fRadius; }
matrix4 MyBoundingBoxClass::GetModelMatrix() { return m_m4ToWorld; }

void MyBoundingBoxClass::DisplaySphere(vector3 a_v3Color)
{
	m_pMeshMngr->AddSphereToRenderList(glm::translate(m_m4ToWorld, m_v3CenterLocal) *
		glm::scale(vector3(m_fRadius * 2.0f)), a_v3Color, WIRE);
}

void MyBoundingBoxClass::DisplayOriented(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, m_v3CenterLocal) *
		glm::scale(m_v3HalfWidth * 2.0f), a_v3Color, WIRE);
}

void MyBoundingBoxClass::DisplayReAlligned(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, m_v3CenterGlobal) *
		glm::scale(m_v3HalfWidthG * 2.0f), a_v3Color, WIRE);
}

bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* a_other)
{
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_other->m_m4ToWorld * vector4(a_other->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_other->m_m4ToWorld * vector4(a_other->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For Objects we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	//first check the bounding sphere, if that is not colliding we can guarantee that there are no collision
	if ((m_fRadius + a_other->m_fRadius) < glm::distance(m_v3CenterGlobal, a_other->m_v3CenterGlobal))
		return false;

	//If the distance was smaller it might be colliding
	//we will use the ReAligned box for the second check, notice that as long as one check return true they are 
	//not colliding thus else statements.

	//Check for X
	if (m_v3MaxG.x < a_other->m_v3MinG.x)
		return false;
	else if (m_v3MinG.x > a_other->m_v3MaxG.x)
		return false;

	//Check for Y
	else if (m_v3MaxG.y < a_other->m_v3MinG.y)
		return false;
	else if (m_v3MinG.y > a_other->m_v3MaxG.y)
		return false;

	//Check for Z
	else if (m_v3MaxG.z < a_other->m_v3MinG.z)
		return false;
	else if (m_v3MinG.z > a_other->m_v3MaxG.z)
		return false;

	return true;
}
