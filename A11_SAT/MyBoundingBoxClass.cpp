#include "MyBoundingBoxClass.h"
//  MyBoundingBoxClass
void MyBoundingBoxClass::Init(void)
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

	rotationAxes = std::vector<vector3>();

	rotationAxes.push_back(vector3(1.0f, 0.0f, 0.0f));
	rotationAxes.push_back(vector3(0.0f, 1.0f, 0.0f));
	rotationAxes.push_back(vector3(0.0f, 0.0f, 1.0f));
}
void MyBoundingBoxClass::Swap(MyBoundingBoxClass& other)
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
}
void MyBoundingBoxClass::Release(void)
{

}
//The big 3
MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> a_lVectorList)
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

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;
	
}
MyBoundingBoxClass::MyBoundingBoxClass(MyBoundingBoxClass const& other)
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
}
MyBoundingBoxClass& MyBoundingBoxClass::operator=(MyBoundingBoxClass const& other)
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
MyBoundingBoxClass::~MyBoundingBoxClass(){ Release(); };
//Accessors
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the box
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
}
matrix4 MyBoundingBoxClass::GetModelMatrix(void){ return m_m4ToWorld; }
vector3 MyBoundingBoxClass::GetCenterLocal(void){ return m_v3Center; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void){ return m_v3CenterG; }
vector3 MyBoundingBoxClass::GetHalfWidth(void){ return m_v3HalfWidth; }
vector3 MyBoundingBoxClass::GetHalfWidthG(void){ return m_v3HalfWidthG; }
void MyBoundingBoxClass::SetRotationAxes(std::vector<vector3> rotAxes)
{
	rotationAxes = rotAxes;
}
std::vector<vector3> MyBoundingBoxClass::GetRotationAxes(){ return rotationAxes; }
//--- Non Standard Singleton Methods
bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For boxes we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	bool bColliding = true;
	
	//Check for X
	if (m_v3MaxG.x < a_pOther->m_v3MinG.x)
		bColliding = false;
	if (m_v3MinG.x > a_pOther->m_v3MaxG.x)
		bColliding = false;

	//Check for Y
	if (m_v3MaxG.y < a_pOther->m_v3MinG.y)
		bColliding = false;
	if (m_v3MinG.y > a_pOther->m_v3MaxG.y)
		bColliding = false;

	//Check for Z
	if (m_v3MaxG.z < a_pOther->m_v3MinG.z)
		bColliding = false;
	if (m_v3MinG.z > a_pOther->m_v3MaxG.z)
		bColliding = false;


	/*SAT - Separating Axis Theroem*/

	//Calculate the vertex that makes the box
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);

	vector3 o_v3Corner[8];
	o_v3Corner[0] = vector3(a_pOther->m_v3Min.x, a_pOther->m_v3Min.y, a_pOther->m_v3Min.z);
	o_v3Corner[1] = vector3(a_pOther->m_v3Max.x, a_pOther->m_v3Min.y, a_pOther->m_v3Min.z);
	o_v3Corner[2] = vector3(a_pOther->m_v3Min.x, a_pOther->m_v3Max.y, a_pOther->m_v3Min.z);
	o_v3Corner[3] = vector3(a_pOther->m_v3Max.x, a_pOther->m_v3Max.y, a_pOther->m_v3Min.z);

	o_v3Corner[4] = vector3(a_pOther->m_v3Min.x, a_pOther->m_v3Min.y, a_pOther->m_v3Max.z);
	o_v3Corner[5] = vector3(a_pOther->m_v3Max.x, a_pOther->m_v3Min.y, a_pOther->m_v3Max.z);
	o_v3Corner[6] = vector3(a_pOther->m_v3Min.x, a_pOther->m_v3Max.y, a_pOther->m_v3Max.z);
	o_v3Corner[7] = vector3(a_pOther->m_v3Max.x, a_pOther->m_v3Max.y, a_pOther->m_v3Max.z);

	//create edges for each box

	vector3 v3Edge[12];

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

	vector3 o_v3Edge[12];

	o_v3Edge[0] = o_v3Corner[0] - o_v3Corner[1];
	o_v3Edge[1] = o_v3Corner[0] - o_v3Corner[2];
	o_v3Edge[2] = o_v3Corner[0] - o_v3Corner[4];
	o_v3Edge[3] = o_v3Corner[1] - o_v3Corner[3];
	o_v3Edge[4] = o_v3Corner[1] - o_v3Corner[5];
	o_v3Edge[5] = o_v3Corner[2] - o_v3Corner[3];
	o_v3Edge[6] = o_v3Corner[2] - o_v3Corner[6];
	o_v3Edge[7] = o_v3Corner[3] - o_v3Corner[7];
	o_v3Edge[8] = o_v3Corner[4] - o_v3Corner[5];
	o_v3Edge[9] = o_v3Corner[4] - o_v3Corner[6];
	o_v3Edge[10] = o_v3Corner[5] - o_v3Corner[7];
	o_v3Edge[11] = o_v3Corner[6] - o_v3Corner[7];

	vector3 normalEdges[12]; //An array of all of the normalized edges.
	vector3 o_normalEdges[12];
	for (int i = 0; i < 24; i++) {
		normalEdges[i] = glm::normalize(v3Edge[i]);
		o_normalEdges[i] = glm::normalize(o_v3Edge[i]);
	}

	vector3 crossProducts[12];

	for (int i = 0; i < 12; i++)
	{
		crossProducts[i] = glm::cross(normalEdges[i], o_normalEdges[i]);
	}



	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			crossProducts[i] = glm::cross(v3Corner[i], normalEdges[j]);
			o_crossProducts[i] = glm::cross(o_v3Corner[i], o_normalEdges[j]);
		}
	}

	vector3 v3MinCP;
	vector3 v3MaxCP;
	vector3 v3MinOCP;
	vector3 v3MaxOCP;

	for (int i = 0; i < 96; i++)
	{
		if (i == 95)
		{
			return;
		}
		if (crossProducts[i].x > crossProducts[i + 1].x && crossProducts[i].y > crossProducts[i + 1].y && crossProducts[i].z > crossProducts[i + 1].z)
		{
			v3MaxCP = crossProducts[i];
		}
		if (crossProducts[i].x < crossProducts[i + 1].x && crossProducts[i].y < crossProducts[i + 1].y && crossProducts[i].z < crossProducts[i + 1].z)
		{
			v3MinCP = crossProducts[i];
		}
	}

	for (int i = 0; i < 96; i++)
	{
		if (i == 95)
		{
			return;
		}
		if (o_crossProducts[i].x > o_crossProducts[i + 1].x && o_crossProducts[i].y > o_crossProducts[i + 1].y && o_crossProducts[i].z > o_crossProducts[i + 1].z)
		{
			v3MaxOCP = o_crossProducts[i];
		}
		if (o_crossProducts[i].x < o_crossProducts[i + 1].x && o_crossProducts[i].y < o_crossProducts[i + 1].y && o_crossProducts[i].z < o_crossProducts[i + 1].z)
		{
			v3MinOCP = o_crossProducts[i];
		}
	}

	//Check for X
	if (v3MaxCP.x < v3MinOCP.x)
		bColliding = false;
	if (v3MinCP.x > v3MaxOCP.x)
		bColliding = false;

	//Check for Y
	if (v3MaxCP.y < v3MinOCP.y)
		bColliding = false;
	if (v3MinCP.y > v3MaxOCP.y)
		bColliding = false;

	//Check for Z
	if (v3MaxCP.z < v3MinOCP.z)
		bColliding = false;
	if (v3MinCP.z > v3MaxOCP.z)
		bColliding = false;*/

	return bColliding;
}

int MyBoundingBoxClass::TestSAT(MyBoundingBoxClass *& a, MyBoundingBoxClass *& b)
{
	float ra, rb;
	matrix3 R, AbsR;
	vector3 trans;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; i++)
		{
			R[i][j] = glm::dot(a->rotationAxes[i], b->rotationAxes[j]);
			//compute translation vector t
			trans = b->GetCenterLocal() - a->GetCenterLocal();

			trans = vector3(glm::dot(trans, a->rotationAxes[0]),
				glm::dot(trans, a->rotationAxes[1]), glm::dot(trans, a->rotationAxes[2]));
		}
	}

	//compute common subexpressions
	//add an epsilon term to counterract errors when 2 edges are parallel
	//and their cross product is near null
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			AbsR[i][j] = glm::abs(R[i][j]);
		}
	}

	//test axes for a
	for (int i = 0; i < 3; i++)
	{
		ra = a->GetHalfWidth()[i];
		rb = b->GetHalfWidth()[0] * AbsR[i][0] +
			b->GetHalfWidth()[1] * AbsR[i][1] +
			b->GetHalfWidth()[2] * AbsR[i][2];

		if (glm::abs(trans[i]) > ra + rb) return 0;
	}

	//test axes for b
	for (int i = 0; i < 3; i++)
	{
		ra = b->GetHalfWidth()[0] * AbsR[0][i] +
			b->GetHalfWidth()[1] * AbsR[1][i] +
			b->GetHalfWidth()[2] * AbsR[2][i];
		rb = a->GetHalfWidth()[i];

		if (glm::abs(trans[0] * R[0][i] +
			trans[1] * R[1][i] + trans[2] * R[2][i]) > ra + rb) return 0;
	}

	//testing cross product of Ax and Bx
	ra = a->GetHalfWidth()[1] * AbsR[2][0] + a->GetHalfWidth()[2] * AbsR[1][0];
	rb = b->GetHalfWidth()[1] * AbsR[0][2] + b->GetHalfWidth()[2] * AbsR[0][1];
	if (glm::abs(trans[2] * R[1][0] - trans[1] * R[2][0]) > ra + rb) return 0;

	//testing cross product of Ax and By
	ra = a->GetHalfWidth()[1] * AbsR[2][1] + a->GetHalfWidth()[2] * AbsR[1][1];
	rb = b->GetHalfWidth()[0] * AbsR[0][2] + b->GetHalfWidth()[2] * AbsR[0][0];
	if (glm::abs(trans[2] * R[1][1] - trans[1] * R[2][1]) > ra + rb) return 0;

	//testing cross product of Ax and Bz
	ra = a->GetHalfWidth()[1] * AbsR[2][2] + a->GetHalfWidth()[2] * AbsR[1][2];
	rb = b->GetHalfWidth()[0] * AbsR[0][1] + b->GetHalfWidth()[1] * AbsR[0][0];
	if (glm::abs(trans[2] * R[1][2] - trans[1] * R[2][2]) > ra + rb) return 0;

	//testing cross product of Ay and Bx
	ra = a->GetHalfWidth()[0] * AbsR[2][0] + a->GetHalfWidth()[2] * AbsR[0][0];
	rb = b->GetHalfWidth()[1] * AbsR[1][2] + b->GetHalfWidth()[2] * AbsR[1][1];
	if (glm::abs(trans[0] * R[2][0] - trans[2] * R[0][0]) > ra + rb) return 0;

	//testing cross product of Ay and By
	ra = a->GetHalfWidth()[0] * AbsR[2][1] + a->GetHalfWidth()[2] * AbsR[0][1];
	rb = b->GetHalfWidth()[0] * AbsR[1][2] + b->GetHalfWidth()[2] * AbsR[1][0];
	if (glm::abs(trans[0] * R[2][1] - trans[2] * R[0][1]) > ra + rb) return 0;

	//testing cross product of Ay and Bz
	ra = a->GetHalfWidth()[0] * AbsR[2][2] + a->GetHalfWidth()[2] * AbsR[0][2];
	rb = b->GetHalfWidth()[0] * AbsR[1][1] + b->GetHalfWidth()[1] * AbsR[1][0];
	if (glm::abs(trans[0] * R[2][2] - trans[2] * R[0][2]) > ra + rb) return 0;

	//testing cross product of Az and Bx
	ra = a->GetHalfWidth()[0] * AbsR[1][0] + a->GetHalfWidth()[1] * AbsR[0][0];
	rb = b->GetHalfWidth()[1] * AbsR[2][2] + b->GetHalfWidth()[2] * AbsR[2][1];
	if (glm::abs(trans[1] * R[0][0] - trans[0] * R[1][0]) > ra + rb) return 0;

	//testing cross product of Az and By
	ra = a->GetHalfWidth()[0] * AbsR[1][1] + a->GetHalfWidth()[1] * AbsR[0][1];
	rb = b->GetHalfWidth()[0] * AbsR[2][2] + b->GetHalfWidth()[2] * AbsR[2][0];
	if (glm::abs(trans[1] * R[0][1] - trans[0] * R[1][1]) > ra + rb) return 0;

	//testing cross product of Az and Bz
	ra = a->GetHalfWidth()[0] * AbsR[1][2] + a->GetHalfWidth()[1] * AbsR[0][2];
	rb = b->GetHalfWidth()[0] * AbsR[2][1] + b->GetHalfWidth()[1] * AbsR[2][0];
	if (glm::abs(trans[1] * R[0][2] - trans[0] * R[1][2]) > ra + rb) return 0;

	return 1;
}

