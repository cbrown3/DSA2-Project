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
	Node(vector3 a_center);

	//sets center of node
	void setCenter();

	//gets center of node
	vector3 getCenter();

	//set the children nodes
	void setChildren(Node* nodes);

	void updateModelList();

	//check if node has children
	bool hasChildren();

	//destructor
	~Node();
};

