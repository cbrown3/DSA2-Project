#include "Node.h"


Node::~Node()
{
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}

	for (int i = 0; i < modelList.size(); i++)
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
	nodeMin = vector3(a_parentMin.x / 2, a_parentMin.y / 2, a_parentMin.z / 2);
	nodeMax = vector3(a_parentMax.x / 2, a_parentMax.y / 2, a_parentMax.z / 2);

	active = true;
}

Node::Node(Node* parent)
{
	children = std::vector<Node*>();
	modelList = std::vector<String*>();

	//take the parent's center and make the node from it
	nodeCenter = parent->nodeCenter;
	nodeMin = parent->nodeMin;
	nodeMax = parent->nodeMax;

	this->parent = parent;

	active = true;
}

void Node::PlaceInTree(vector3 center) {
	nodeCenter = center;
	nodeMin = vector3(nodeMin.x / 2, nodeMin.y / 2, nodeMin.z / 2);
	nodeMax = vector3(nodeMax.x / 2, nodeMax.y / 2, nodeMax.z / 2);
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

Node::Node(vector3 a_center)
{
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

Node * Node::getParent()
{
	return parent;
}

void Node::addChild(Node* node)
{
	children.push_back(node);
}

std::vector<String*> Node::getModels() {
	return modelList;
}

std::vector<Node*> Node::getChildren() {
	return this->children;
}
void Node::updateModelList()
{
	vector<String*> possibleModels = parent->getModels();
	vector<String*> containedModels = vector<String*>();

	for (int i = 0; i < possibleModels.size(); i++) {
		//check if each model is contained in node 
		BoundingObjectClass* model = m_pBomMngr->GetBoundingObject(*possibleModels[i]);
		bool isColliding = true;

		//check model aabb collisions with octant
		vector3 max = model->GetAABBMax();
		vector3 min = model->GetAABBMin();

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

	//deactivate if no models in node
	if (modelList.size() == 0) active = false;
}

bool Node::IsActive() {
	return active;
}

bool Node::hasChildren()
{
	if (children.size() > 0) return true;
	else return false;
}

void Node::deleteChildren() //Michael's code
{
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
}
