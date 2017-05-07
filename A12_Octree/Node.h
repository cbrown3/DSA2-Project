#pragma once

#include "RE\ReEngAppClass.h"

using std::vector;

class Node
{
	Node* parent; //parent node
	Node* children; //children nodes

	BOManagerSingleton* m_pBomMngr;
	vector<String> modelList; //list of names of all models in node
	int modelCount; //ammount of models in node

public:

	//constructors
	Node() {
		parent = nullptr;
		children = nullptr;
		modelList = vector<String>();
		modelCount = 0;
	};

	Node(Node* parent) {
		this->parent = parent;
		children = nullptr;
		modelList = vector<String>();
		modelCount = 0;
	}

	Node(Node* parent, Node* children) {
		this->parent = parent;
		this->children = children;
		modelList = vector<String>();
		modelCount = 0;
	}

	//set the parent node
	void setParent(Node* parent) {
		if (this->parent != nullptr) {
			delete this->parent;
			this->parent = parent;
		}
		else this->parent = parent;
	}

	//set the children nodes
	void setChildren(Node* nodes) {
		if (children != nullptr) {
			delete[] children;
			children = nodes;
		}
		else children = nodes;
	}

	void updateModelList() {
		vector<String> possibleModels = parent->modelList;
		
		vector<String> containedModels = vector<String>();

		for (int i = 0; i < possibleModels.size(); i++) {
			//check if each model is contained in node 
			BoundingObjectClass* model = m_pBomMngr->GetBoundingObject(possibleModels[i]);
			bool isColliding = true;

			//check aabb collisions with octant

			vector3 max = model->GetAABBMax;
			vector3 min = model->GetAABBMin;

			//check top
			//if ()


				//check bottom

				//check left

				//check right

				if (isColliding) containedModels.push_back(possibleModels[i]);
		}


		modelList = containedModels;
	}

	//get current number of models in node
	int getModelCount() { return modelCount; }

	//check if node has children
	bool hasChildren() { 
		if (children == nullptr) return false;
		else return true;
	}

	//destructor
	~Node() {
		SafeDelete(parent);
		delete [] children;
	};
};

