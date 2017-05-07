#include "Node.h"


Node::~Node()
{
	for (int i = 0; i < children.size; i++)
	{
		delete children[i];
	}

	for (int i = 0; i < modelList.size; i++)
	{
		delete modelList[i];
	}
}

Node::Node(vector3 a_center)
{
	children = std::vector<Node*>();
	modelList = std::vector<String*>();

	nodeCenter = vector3(0, 0, 0);
	nodeCenter = vector3(0, 0, 0);
	nodeCenter = vector3(0, 0, 0);
}

void Node::setCenter()
{
}

vector3 Node::getCenter()
{
	return nodeCenter;
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

bool Node::hasChildren()
{
	if (children == nullptr) return false;
	else return true;
}
