#include "MyBOClass.h"
//  MyBOClass
void MyBOClass::Init(void)
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3CenterG = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);

	m_fRadius = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}
void MyBOClass::Swap(MyBOClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}
void MyBOClass::Release(void) {/* No pointers allocated yet */ }
//The big 3
MyBOClass::MyBOClass(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;
}
MyBOClass::MyBOClass(MyBOClass const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;

	m_fRadius = other.m_fRadius;

	m_pMeshMngr = other.m_pMeshMngr;
}
MyBOClass& MyBOClass::operator=(MyBOClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBOClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBOClass::~MyBOClass() { Release(); };
//Accessors
void MyBOClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
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
	m_v3CenterG = (m_v3MinG + m_v3MaxG) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthG = (m_v3MaxG - m_v3MinG) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterG, m_v3MaxG);
}
float MyBOClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBOClass::GetModelMatrix(void) { return m_m4ToWorld; }
vector3 MyBOClass::GetCenterLocal(void) { return m_v3Center; }
vector3 MyBOClass::GetCenterGlobal(void) { return m_v3CenterG; }
vector3 MyBOClass::GetHalfWidth(void) { return m_v3HalfWidth; }
vector3 MyBOClass::GetHalfWidthG(void) { return m_v3HalfWidthG; }
vector3 MyBOClass::GetMin(void) { return m_v3Min; }
vector3 MyBOClass::GetMax(void) { return m_v3Max; }
vector3 MyBOClass::GetMinG(void) { return m_v3MinG; }
vector3 MyBOClass::GetMaxG(void) { return m_v3MaxG; }
//--- Non Standard Singleton Methods
void MyBOClass::DisplaySphere(vector3 a_v3Color)
{
	m_pMeshMngr->AddSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(vector3(m_fRadius * 2.0f)), a_v3Color, WIRE);
}
void MyBOClass::DisplayOriented(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(m_v3HalfWidth * 2.0f), a_v3Color, WIRE);
}
void MyBOClass::DisplayReAlligned(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, m_v3CenterG) *
		glm::scale(m_v3HalfWidthG * 2.0f), a_v3Color, WIRE);
}
vector3 MyBOClass::CrossProduct(vector3 a_vector1, vector3 a_vector2)
{
	vector3 result;
	result.x = (a_vector1.y * a_vector2.z) - (a_vector1.z * a_vector2.y);
	result.y = (a_vector1.z * a_vector2.x) - (a_vector1.x * a_vector2.z);
	result.z = (a_vector1.x * a_vector2.y) - (a_vector1.y * a_vector2.x);
	return result;
}
vector3 MyBOClass::Normalize(vector3 a_vector)
{
	vector3 result;
	float length = sqrt((a_vector.x * a_vector.x) + (a_vector.y * a_vector.y) + (a_vector.z * a_vector.z));
	if (length != 0) {
		result.x = a_vector.x / length;
		result.y = a_vector.y / length;
		result.z = a_vector.z / length;
	}
	return result;
}
bool MyBOClass::IsColliding(MyBOClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For Objects we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	//first check the bounding sphere, if that is not colliding we can guarantee that there are no collision
	/*if ((m_fRadius + a_pOther->m_fRadius) < glm::distance(m_v3CenterG, a_pOther->m_v3CenterG))
		return false;*/

	//If the distance was smaller it might be colliding
	//we will use the ReAligned box for the second check, notice that as long as one check return true they are 
	//not colliding thus else statements.

	//Note to self - this is where I should draw the planes for the SAT test.

	//Check for X
	/*if (m_v3MaxG.x < a_pOther->m_v3MinG.x) {
		m_pMeshMngr->AddPlaneToRenderList(m_m4ToWorld, RERED);
		return false;
	}
	else if (m_v3MinG.x > a_pOther->m_v3MaxG.x) {
		return false;
	}*/

	//Check for Y
	/*else if (m_v3MaxG.y < a_pOther->m_v3MinG.y) {
		return false;
	}
	else if (m_v3MinG.y > a_pOther->m_v3MaxG.y) {
		return false;
	}*/

	//Check for Z
	/*else if (m_v3MaxG.z < a_pOther->m_v3MinG.z) {
		return false;
	}
	else if (m_v3MinG.z > a_pOther->m_v3MaxG.z) {
		return false;
	}*/

	vector3 v3Corner[16];
	//This box's corners
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//The other box's corners
	v3Corner[8] = vector3(a_pOther->m_v3Min.x, a_pOther->m_v3Min.y, a_pOther->m_v3Min.z);
	v3Corner[9] = vector3(a_pOther->m_v3Max.x, a_pOther->m_v3Min.y, a_pOther->m_v3Min.z);
	v3Corner[10] = vector3(a_pOther->m_v3Min.x, a_pOther->m_v3Max.y, a_pOther->m_v3Min.z);
	v3Corner[11] = vector3(a_pOther->m_v3Max.x, a_pOther->m_v3Max.y, a_pOther->m_v3Min.z);
	
	v3Corner[12] = vector3(a_pOther->m_v3Min.x, a_pOther->m_v3Min.y, a_pOther->m_v3Max.z);
	v3Corner[13] = vector3(a_pOther->m_v3Max.x, a_pOther->m_v3Min.y, a_pOther->m_v3Max.z);
	v3Corner[14] = vector3(a_pOther->m_v3Min.x, a_pOther->m_v3Max.y, a_pOther->m_v3Max.z);
	v3Corner[15] = vector3(a_pOther->m_v3Max.x, a_pOther->m_v3Max.y, a_pOther->m_v3Max.z);

	vector3 v3Edge[24];
	//This box's edges
	v3Edge[0] = v3Corner[0] - v3Corner[1];
	v3Edge[1] = v3Corner[0] - v3Corner[2];
	v3Edge[2] = v3Corner[0] - v3Corner[4];
	v3Edge[3] = v3Corner[1] - v3Corner[3];
	v3Edge[4] = v3Corner[1] - v3Corner[5];
	v3Edge[5] = v3Corner[2] - v3Corner[3];
	v3Edge[6] = v3Corner[2] - v3Corner[6];
	v3Edge[7] = v3Corner[3] - v3Corner[7];
	v3Edge[8] = v3Corner[4] - v3Corner[5];
	v3Edge[9] = v3Corner[4] - v3Corner[6];
	v3Edge[10] = v3Corner[5] - v3Corner[7];
	v3Edge[11] = v3Corner[6] - v3Corner[7];
	//The other box's edges
	v3Edge[12] = v3Corner[8] - v3Corner[9];
	v3Edge[13] = v3Corner[8] - v3Corner[10];
	v3Edge[14] = v3Corner[8] - v3Corner[12];
	v3Edge[15] = v3Corner[9] - v3Corner[11];
	v3Edge[16] = v3Corner[9] - v3Corner[13];
	v3Edge[17] = v3Corner[10] - v3Corner[11];
	v3Edge[18] = v3Corner[10] - v3Corner[14];
	v3Edge[19] = v3Corner[11] - v3Corner[15];
	v3Edge[20] = v3Corner[12] - v3Corner[13];
	v3Edge[21] = v3Corner[12] - v3Corner[14];
	v3Edge[22] = v3Corner[13] - v3Corner[15];
	v3Edge[23] = v3Corner[14] - v3Corner[15];
	
	vector3 normalList[24];
	for (int i = 0; i < 24; i++) {
		normalList[i] = Normalize(v3Edge[i]);
	}

	for (int i = 0; i < 11; i++) {
		vector3 cross1 = CrossProduct(v3Edge[i], v3Edge[i + 1]);
		vector3 cross2 = CrossProduct(v3Edge[i + 12], v3Edge[i + 13]);
		if (cross1 != cross2) return false; //This obviously won't work, but here I will compare the two
		//cross products and if they don't overlap, I will return false.
	}

	vector3 cross1 = CrossProduct(v3Edge[11], v3Edge[0]);
	vector3 cross2 = CrossProduct(v3Edge[23], v3Edge[12]);
	if (cross1 != cross2) return false;

	return true;
}