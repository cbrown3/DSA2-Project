#pragma once

#include "RE\ReEngAppClass.h"

class Node
{
	Node* parent; //parent node
	Node* children; //children nodes

	String* modelList; //list of names of all models in node
	int modelCount; //ammount of models in node

public:

	//constructors
	Node() {
		parent = nullptr;
		children = nullptr;
		modelList = nullptr;
		modelCount = 0;
	};

	Node(Node* parent) {
		this->parent = parent;
		children = nullptr;
		modelList = nullptr;
		modelCount = 0;
	}

	Node(Node* parent, Node* children) {
		this->parent = parent;
		this->children = children;
		modelList = nullptr;
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

