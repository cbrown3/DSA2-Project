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

public:

	OcTreeClass();

	OcTreeClass(std::vector<Node*> parents);

	OcTreeClass(std::vector<Node*> parents, std::vector<Node*> children);

	~OcTreeClass();

private:

	void Init();

	void TraverseForCollisions(bool showCollision);

	void Release();

	void ToggleVisibility();

	void Recalculate();

	vector3 GetOctantMin();

	vector3 GetOctantMax();

	vector3 GetOctantCenter();

	void Display(vector3 a_v3Color);

	bool IsColliding(std::vector<Node*> nodeList);

	Node* GetChild(uint a_nChild);

	OcTreeClass* GetSelf();

	void ClearBOList();

	void KillBranches();

	void AssignIDtoBO();

	void CheckCollisions(bool showCollision);
};