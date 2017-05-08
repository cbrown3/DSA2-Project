#pragma once

#include "RE\ReEngAppClass.h"
#include "Node.h"
#include "RE\Physics\BOManagerSingleton.h"namespace ReEng;

class OcTreeClass
{
	BOManagerSingleton* m_pBOMngr = nullptr;
	MeshManagerSingleton* m_pMeshMngr = nullptr;
	std::vector<Node*> childrenNodes; //holds subdivisions of the bounding (children of Nodes)
	std::vector<int> idList; //list of node ids

	vector3 octantMin;
	vector3 octantMax;
	vector3 octantCenter;

	Node* octreeNode;

	std::vector<Node*> activeNodes; //nodes to check for collisions [non-empty enpoint nodes]

#pragma region Josh_Additions
	bool m_bVisible;

	std::vector<glm::mat4> m_m4OctantList[32];

	std::vector<glm::mat4> m_m4OctantList;

	std::vector<glm::vec3> m_v3PointList = std::vector<glm::vec3>();

	std::vector<glm::mat4> m_m4OctantList;
#pragma endregion

public:

	OcTreeClass();

	void Subdivide(Node * root);

	~OcTreeClass();

private:

	void TraverseForCollisions(bool showCollision);

	void Release();

	void ToggleVisibility();

	void CalculateOcTree();

	vector3 GetOctantMin();

	vector3 GetOctantMax();

	vector3 GetOctantCenter();

	void Display(vector3 a_v3Color);

	Node* GetChild(uint a_nChild);

	OcTreeClass* GetSelf();

	void ClearBOList();

	void KillBranches(Node* target);

	void UpdateModelLists(Node * root);

	void CheckCollisions(bool showCollision);
};