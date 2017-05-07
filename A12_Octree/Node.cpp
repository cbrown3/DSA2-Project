#include "Node.h"



Node::Node()
{
	parent = nullptr;
	children = nullptr;
	modelList = nullptr;
	modelCount = 0;
}

Node::~Node()
{
	SafeDelete(parent);
	delete[] children;
}

Node::Node(vector3 a_center)
{
}

void Node::setCenter()
{
}

void Node::setParent(Node * parent)
{
	if (this->parent != nullptr) {
		delete this->parent;
		this->parent = parent;
	}
	else this->parent = parent;
}

void Node::setChildren(Node * nodes)
{
	if (children != nullptr) {
		delete[] children;
		children = nodes;
	}
	else children = nodes;
}

void Node::updateModelList()
{
}

int Node::getModelCount()
{
	return modelCount;
}

bool Node::hasChildren()
{
	if (children == nullptr) return false;
	else return true;
}
