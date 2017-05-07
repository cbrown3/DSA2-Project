#pragma once

#include "RE\ReEngAppClass.h"

class Node
{
	Node* parent; //parent node
	Node* children; //children nodes

	String* modelList; //list of names of all models in node
	int modelCount; //ammount of models in node
	int nodeId;

	vector3 nodeCenter;
	vector3 nodeMin;
	vector3 nodeMax;

public:

	//constructors
	Node();

	Node(vector3 a_center);

	void setCenter();

	//set the parent node
	void setParent(Node* parent);

	//set the children nodes
	void setChildren(Node* nodes);

	void updateModelList();

	//get current number of models in node
	int getModelCount();

	//check if node has children
	bool hasChildren();

	//destructor
	~Node();
};

