#pragma once

#include "RE\ReEngAppClass.h"
using std::vector;

class Node
{
	Node* parent;
	vector<Node*> children; //children nodes

	vector<String*> modelList; //list of names of all models in node
	BOManagerSingleton* m_pBomMngr;

	vector3 nodeCenter;
	vector3 nodeMin;
	vector3 nodeMax;

public:

	//creates node from center
	Node(vector3 a_parentMin, vector3 a_parentMax, vector3 a_center);

	//sets center of node
	void setCenter(vector3 a_center);

	//sets max of node
	void setMax(vector3 a_max);

	//sets min of node
	void setMin(vector3 a_min);

	Node(vector3 a_center);

	//gets center of node
	vector3 getCenter();

	//gets min of node
	vector3 getMin();

	//gets max of node
	vector3 getMax();

	//set the children nodes
	void setChildren(Node* nodes);

	void addChild(Node * node);

	void updateModelList();

	//check if node has children
	bool hasChildren();

	//destructor
	~Node();
};

