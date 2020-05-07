#pragma once
#include "DnaTree.h"
#include "Weight.h"
#include "Base.h"
#include "ReadTag.h"

class Node
{
private:
	std::vector<ReadTag*> endTag;
	std::vector<Weight> weights;
	Node** branches;
public:
	Node();
	Node* addBranch(Base);
	Node* getBranch(Base);
	bool hasBase(Base);
	void attachTag(ReadTag*);
	void addWeight(int weight);
	int avrWeight();
	std::vector<ReadTag*> getTags();
	std::vector<Weight> getWeights();
};

