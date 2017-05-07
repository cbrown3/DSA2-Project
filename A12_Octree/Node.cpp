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

Node::Node(vector3 a_parentMin, vector3 a_parentMax, vector3 a_center)
{
	children = std::vector<Node*>();
	modelList = std::vector<String*>();

	//take the parent's center and make the node from it
	nodeCenter = a_center;
	nodeMin = a_parentMin;
	nodeMax = a_parentMax;
}

void Node::setCenter(vector3 a_center)
{
	nodeCenter = a_center;
}

void Node::setMax(vector3 a_max)
{
	nodeMax = a_max;
}

void Node::setMin(vector3 a_min)
{
	nodeMin = a_min;
}

vector3 Node::getCenter()
{
	return nodeCenter;
}

vector3 Node::getMin()
{
	return nodeMin;
}

vector3 Node::getMax()
{
	return nodeMax;
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
