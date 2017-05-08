#include "OcTreeClass.h"


OcTreeClass::OcTreeClass()//Chris
{
	m_pBOMngr = BOManagerSingleton::GetInstance();
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	octantCenter = vector3(0, 0, 0);
	octantMin = vector3(-70, -70, -70);
	octantMax = vector3(70, 70, 70);

	childrenNodes = std::vector<Node*>();

	idList = std::vector<int>();

	octreeNode = new Node(octantMin, octantMax, octantCenter);

	for (int i = 0; i < m_m4OctantList.size; i++)
	{
		glm::mat4 baseMat = glm::translate(GetChild(i)->getCenter()) * glm::scale(vector3(1, 1, 1) * 2.0f);

		m_m4OctantList[i] = baseMat;
	}

#pragma region danielle_additions
	activeNodes = std::vector<Node*>();

	//build tree
	Subdivide(octreeNode);

	//subdivide layer1 endpoints
	std::vector<Node*> layer1 = octreeNode->getChildren();
	for (int i = 0; i < layer1.size(); i++) {
		if (!layer1[i]->hasChildren)
			Subdivide(layer1[i]);
	}

	//re-calculate tree 
	UpdateModelLists(octreeNode);

	//check collisions [show colliding bounding boxes if bool is true]
	CheckCollisions(m_bVisible);

#pragma endregion
}

void OcTreeClass::Subdivide(Node* root) //danielle
{
	
	//*assuming octree is square
	float halfWidth = root->getMin.x;
	vector3 origin = root->getCenter();

	//[z+]____M  [z-]____M     z
	//  |1_|2_|    |5_|6_|     | / y
	//  |3_|4_|    |7_|8_|	   |/___x
	// m          m

	//make all the children nodes
	Node* node1 = new Node(root);
	node1->PlaceInTree( vector3( origin.x - halfWidth, origin.y - halfWidth, origin.z + halfWidth) );

	Node* node2 = new Node(root);
	node2->PlaceInTree(vector3(origin.x + halfWidth, origin.y - halfWidth, origin.z + halfWidth));

	Node* node3 = new Node(root);
	node3->PlaceInTree(vector3(origin.x - halfWidth, origin.y + halfWidth, origin.z + halfWidth));

	Node* node4 = new Node(root);
	node4->PlaceInTree(vector3(origin.x + halfWidth, origin.y + halfWidth, origin.z + halfWidth));


	Node* node5 = new Node(root);
	node5->PlaceInTree(vector3(origin.x - halfWidth, origin.y - halfWidth, origin.z - halfWidth));

	Node* node6 = new Node(root);
	node6->PlaceInTree(vector3(origin.x + halfWidth, origin.y - halfWidth, origin.z - halfWidth));

	Node* node7 = new Node(root);
	node7->PlaceInTree(vector3(origin.x - halfWidth, origin.y + halfWidth, origin.z - halfWidth));

	Node* node8 = new Node(root);
	node8->PlaceInTree(vector3(origin.x + halfWidth, origin.y + halfWidth, origin.z - halfWidth));

	//add children to root
	root->addChild(node1);
	root->addChild(node2);
	root->addChild(node3);
	root->addChild(node4);
	root->addChild(node5);
	root->addChild(node6);
	root->addChild(node7);
	root->addChild(node8);
}

OcTreeClass::~OcTreeClass()//Danielle
{
	m_pBOMngr->ReleaseInstance();
	m_pMeshMngr->ReleaseInstance();
	for (int i = 0; i < childrenNodes.size(); i++) {
		delete childrenNodes[i];
	}
	delete octreeNode;

	delete this;
}

void OcTreeClass::ToggleVisibility() //Josh
{
	if (m_bVisible)
	{
		m_bVisible = false;
	}
	if (!m_bVisible)
	{
		m_bVisible = true;
	}
}

void OcTreeClass::CalculateOcTree() //Josh
{
	glm::vec3 halfCenter(octantCenter.x / 2, octantCenter.y / 2, octantCenter.z / 2);
	glm::vec3 fourthCenter(octantCenter.x / 4, octantCenter.y / 4, octantCenter.z / 4);


	//[z+]____M  [z-]____M     z
	//  |1_|2_|    |5_|6_|     | / y
	//  |3_|4_|    |7_|8_|	   |/___x
	// m          m

	//top half of cube
	glm::vec3 p_point1 = vector3(halfCenter.x, halfCenter.y * 3, halfCenter.z * 3);
	glm::vec3 p_point2 = vector3(halfCenter.x * 3, halfCenter.y * 3, halfCenter.z * 3);
	glm::vec3 p_point3 = vector3(halfCenter.x, halfCenter.y, halfCenter.z * 3);
	glm::vec3 p_point4 = vector3(halfCenter.x * 3, halfCenter.y, halfCenter.z * 3);

	//bottom half of cube
	glm::vec3 p_point5 = vector3(halfCenter.x, halfCenter.y * 3, halfCenter.z);
	glm::vec3 p_point6 = vector3(halfCenter.x * 3, halfCenter.y * 3, halfCenter.z);
	glm::vec3 p_point7 = vector3(halfCenter.x, halfCenter.y, halfCenter.z);
	glm::vec3 p_point8 = vector3(halfCenter.x * 3, halfCenter.y, halfCenter.z);

	octreeNode->addChild(new Node(octantMin, octantMax, p_point1));
	octreeNode->addChild(new Node(octantMin, octantMax, p_point2));
	octreeNode->addChild(new Node(octantMin, octantMax, p_point3));
	octreeNode->addChild(new Node(octantMin, octantMax, p_point4));
	octreeNode->addChild(new Node(octantMin, octantMax, p_point5));
	octreeNode->addChild(new Node(octantMin, octantMax, p_point6));
	octreeNode->addChild(new Node(octantMin, octantMax, p_point7));
	octreeNode->addChild(new Node(octantMin, octantMax, p_point8));
}

vector3 OcTreeClass::GetOctantMin() //Josh
{
	return octantMin;
}

vector3 OcTreeClass::GetOctantMax() //Josh
{
	return octantMax;
}

vector3 OcTreeClass::GetOctantCenter() //Josh
{
	return octantCenter;
}

void OcTreeClass::Display(vector3 a_v3Color) //Josh
{
	if (m_bVisible)
	{
		for (int i = 0; i < m_m4OctantList.size; i++)
		{
			m_pMeshMngr->AddCubeToRenderList(m_m4OctantList.at(i), a_v3Color, WIRE);
			m_pMeshMngr->AddCubeToRenderList(m_m4OctantList[i], a_v3Color, WIRE);
		}
	}
	if (!m_bVisible)
	{
		m_pMeshMngr->ClearRenderList(); //Not what is needed, but clears everything. Need to clear one thing at a time.
	}
}

void OcTreeClass::ClearBOList()//Danielle
{
	m_pBOMngr->ReleaseInstance();
}

Node* OcTreeClass::GetChild(uint a_nChild) //Josh
{
	return childrenNodes[a_nChild];
}

OcTreeClass * OcTreeClass::GetSelf()
{
	return this;
}

void OcTreeClass::KillBranches(Node* target)
{
	target->deleteChildren(); //Michael's code
}


//recurse through tree and update model lists and active node list
void OcTreeClass::UpdateModelLists(Node* root) //danielle
{
	
	//update model lists
	root->updateModelList();

	//check if at end of branch
	if (root->getChildren().size() == 0) {
		//if it has models in it add to active list
		if (root->IsActive()) activeNodes.push_back(root);
	}

	//else check all children nodes
	else {
		for (int i = 0; i < root->getChildren().size(); i++) {
			UpdateModelLists(root->getChildren[i]);
		}
	}
}

//calculate all model collisions in active nodes [show colliding bounding boxes if bool is true]
void OcTreeClass::CheckCollisions(bool showCollision) //danielle
{
	vector<String*> models;
	BoundingObjectClass* model;
	BoundingObjectClass* otherModel;
	vector3 max;
	vector3 min;

	vector3 otherMax;
	vector3 otherMin;

	//check collisions in calculated active nodes
	for (int i = 0; i < activeNodes.size(); i++) {

		//for each endnode with models check collisions
		if (activeNodes[i]->IsActive && !activeNodes[i]->hasChildren) {
			
			models = activeNodes[i]->getParent()->getModels();

			//check collisions for contained models
			for (int j = 0; j < models.size(); j++) {
				//check if each model is collising 
				model = m_pBOMngr->GetBoundingObject(*models[i]);
				
				for (int k = j; k < models.size(); k++) {
					otherModel = m_pBOMngr->GetBoundingObject(*models[k]);

					bool isColliding = true;

					//check model aabb collisions with other model
					max = model->GetAABBMax;
					min = model->GetAABBMin;

					otherMin = otherModel->GetAABBMin;
					otherMax = otherModel->GetAABBMax;

					//Check for X
					if (max.x < otherMin.x)
						isColliding = false;
					else if (min.x > otherMax.x)
						isColliding = false;

					//Check for Y
					else if (max.y < otherMin.y)
						isColliding = false;
					else if (min.y > otherMax.y)
						isColliding = false;

					//Check for Z
					else if (max.z < otherMin.z)
						isColliding = false;
					else if (min.z > otherMax.z)
						isColliding = false;

					//if is colliding show collision
					if (isColliding && showCollision) {
						model->SetVisibleAABB(true);
					}
				} //check agains other models
			} //check each model
		} //check each node
	}
}

void OcTreeClass::Release() //Michael's code
{
	for (int i = 0; i < childrenNodes.size; i++) {
		delete childrenNodes[i];
	}
	for (int i = 0; i < activeNodes.size(); i++) {
		delete activeNodes[i]
	} //danielle

	delete octreeNode;
	m_pBOMngr->ReleaseInstance();
	m_pMeshMngr->ReleaseInstance();
}

void OcTreeClass::TraverseForCollisions(bool showCollision)
{
}