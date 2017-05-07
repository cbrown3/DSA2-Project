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

void Node::setChildren(Node* nodes)
{

}

void Node::addChild(Node* node) {
	children.push_back(node);
}

void Node::updateModelList()
{
	vector<String*> possibleModels = parent->modelList;
	vector<String*> containedModels = vector<String*>();

	for (int i = 0; i < possibleModels.size(); i++) {
		//check if each model is contained in node 
		BoundingObjectClass* model = m_pBomMngr->GetBoundingObject(*possibleModels[i]);
		bool isColliding = true;

		//check model aabb collisions with octant
		vector3 max = model->GetAABBMax;
		vector3 min = model->GetAABBMin;

		//Check for X
		if (max.x < nodeMin.x)
			isColliding = false;
		else if (min.x > nodeMax.x)
			isColliding = false;

		//Check for Y
		else if (max.y < nodeMin.y)
			isColliding = false;
		else if (min.y > nodeMax.y)
			isColliding = false;

		//Check for Z
		else if (max.z < nodeMin.z)
			isColliding = false;
		else if (min.z > nodeMax.z)
			isColliding = false;

		//if is colliding add to node model list
		if (isColliding) containedModels.push_back(possibleModels[i]);
	}

	modelList = containedModels;
}

bool Node::hasChildren()
{
	if (children.size > 0) return true;
	else return false;
}
