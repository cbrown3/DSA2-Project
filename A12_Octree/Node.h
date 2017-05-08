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

	bool active;
public:

	//creates node from center
	Node(vector3 a_parentMin, vector3 a_parentMax, vector3 a_center);

	Node(Node * parent);

	void PlaceInTree(vector3 center);

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

	Node * getParent();

	//add the children nodes
	void addChild(Node * node);

	std::vector<String*> getModels();

	std::vector<Node*> getChildren();

	void updateModelList();

	bool IsActive();

	//check if node has children
	bool hasChildren();

	//deletes all of the children
	void deleteChildren();

	//destructor
	~Node();
};

