/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __MYBOUNDINGBOXCLASS_H_
#define __MYBOUNDINGBOXCLASS_H_

#include "RE\ReEng.h"


//System Class
class MyBoundingBoxClass
{
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the box Class

	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the box Class

	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides

public:
	/*
	 MyBoundingBoxClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyBoundingBoxClass(std::vector<vector3> a_lVectorList);
	/*
	 MyBoundingBoxClass
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyBoundingBoxClass(MyBoundingBoxClass const& other);
	/*
	 operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyBoundingBoxClass& operator=(MyBoundingBoxClass const& other);
	/*
	 ~MyBoundingBoxClass
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyBoundingBoxClass(void);

	/*
	 Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(MyBoundingBoxClass& other);

	/*
	 SetToWorldMatrix
	USAGE: Sets the Bounding Box into world coordinates
	ARGUMENTS:
	matrix4 a_m4ToWorld -> Model to World matrix
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	 GetToWorldMatrix
	USAGE: Gets the Bounding Box into world coordinates
	ARGUMENTS:---
	OUTPUT: matrix4 -> Model to World matrix
	*/
	matrix4 GetModelMatrix(void);

	/*
	 GetCenter
	USAGE: Gets the Bounding Box's center in local coordinates
	ARGUMENTS: ---
	OUTPUT: vector3 -> Center's of the box in local coordinates
	*/
	vector3 GetCenterLocal(void);

	/*
	 GetCenterGlobal
	USAGE: Gets the Bounding Box's center in global coordinates
	ARGUMENTS: ---
	OUTPUT: vector3 -> Center's of the box in global coordinates
	*/
	vector3 GetCenterGlobal(void);

	/*
	 GetHalfWidth
	USAGE: Gets the Bounding Box sizes for all sides (divided in half)
	ARGUMENTS: ---
	OUTPUT: vector3 -> HalfWidth Vector
	*/
	vector3 GetHalfWidth(void);

	/*
	 GetHalfWidthG
	USAGE: Gets the Bounding Box sizes for all sides (divided in half) reoriented
	ARGUMENTS: ---
	OUTPUT: vector3 -> HalfWidth Vector
	*/
	vector3 GetHalfWidthG(void);

	/*
	 IsColliding
	USAGE: Asks if there is a collision with another Bounding Box Object
	ARGUMENTS:
	MyBoundingBoxClass* const a_pOther -> Other object to check collision with
	OUTPUT: bool -> check of the collision
	*/
	bool IsColliding(MyBoundingBoxClass* const a_pOther);

private:
	/*
	 Release
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	 Init
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

#endif //__MYBOUNDINGBOXCLASS_H__