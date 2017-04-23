#pragma once
#include "RE\ReEng.h"
#include "MyBoundingBoxClass.h"


/*
singleton manager for bounding objects
*/
class MyBoundingObjectManager
{

	static MyBoundingObjectManager* m_pInstance; // instance pointer
	std::vector<MyBoundingBoxClass*> boxes; //list of bounding objects
	std::vector<String> names; // corresponding names of the objects


private:
	//constructor
	MyBoundingObjectManager() { m_pInstance = nullptr;  };
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

	void ChangeVisible(String args)
	{
		for (int i = 0; i < names.size(); i++)
		{
			if (names[i] == args)
			{
				boxes[i];
			}
		}
	};

	void SetColor(String args, vector3 ColorArgs)
	{
		for (int i = 0; i < names.size(); i++)
		{
			if (names[i] == args)
			{
				boxes[i]->SetColor(ColorArgs);
			}
		}
	};

	void RederOptions(int RenderArgs)
	{
		if (RenderArgs > boxes.size()) return;

		switch (RenderArgs)
		{
		case 0:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
			}
			break;
		case 1:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[0]->RenderSphere(true);
			}
			break;
		case 2:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[1]->RenderSphere(true);
			}
			break;
		case 3:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[2]->RenderSphere(true);
			}
			break;
		case 4:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[3]->RenderSphere(true);
			}
			break;
		case 5:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[4]->RenderSphere(true);
			}
			break;
		case 6:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[5]->RenderSphere(true);
			}
			break;
		case 7:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[6]->RenderSphere(true);
			}
			break;
		case 8:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[7]->RenderSphere(true);
			}
			break;
		case 9:
			for (int i = 0; i < boxes.size(); i++)
			{
				boxes[i]->RenderSphere(false);
				boxes[8]->RenderSphere(true);
			}
			break;
		default:
			break;
		}
	};

	void CheckCollisions()
	{
		for (int i = 0; i < boxes.size(); i++)
		{
			for (int j = 1; j < boxes.size(); j++)
			{
				if (j > boxes.size())
				{
					j = 0;
				}
				boxes[i]->IsColliding(boxes[j]);
			}
		}
	};

	//Is handelded in the IsColliding Method
	//void DoCollisions()
	//{
	//
	//};

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
		boxes.push_back(a_newBox);
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
