#pragma once
#include "RE\ReEng.h"
#include "MyBoundingBoxClass.h"


/*
singleton manager for bounding objects
*/
class MyBoundingObjectManager
{

	static MyBoundingObjectManager* m_pInstance; // instance pointer
	std::vector<MyBoundingBoxClass> boxes; //list of bounding objects
	std::vector<String> names; // corresponding names of the objects


private:
	//constructor
	MyBoundingObjectManager();
	//copy constructor
	MyBoundingObjectManager(MyBoundingObjectManager const& other) {};
	//copy assignment operator
	MyBoundingObjectManager& operator=(MyBoundingObjectManager const& other) {};

	//destructor
	~MyBoundingObjectManager() { Release(); }

	//clear the manager data
	void Release()
	{
		boxes.clear();
		names.clear();
	}

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

	//add a new bounding object to data
	void addBoundingBox(MyBoundingBoxClass* a_newBox, String a_name)
	{
		boxes.push_back(*a_newBox);
		names.push_back(a_name);
	};
	////get a listed bounding object by name
	//MyBoundingBoxClass* GetBox(String a_name)
	//{
	//	for (int i = 0; i < names.size(); i++)
	//	{
	//		if (names[i] == a_name)
	//		{
	//			return &boxes[i];
	//		}
	//	}
	//
	//	return nullptr;
	//}
};
