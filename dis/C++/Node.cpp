#include "Node.h"
Node::Node()
{
	branches = new Node * [BASE_COUNT];
	for (int i = 0; i < BASE_COUNT; i++)
	{
		branches[i] = nullptr;
	}
}

Node* Node::addBranch(Base base)
{
	if (!hasBase(base))
	{
		branches[base] = new Node();
	}
	return branches[base];
}

Node* Node::getBranch(Base base)
{
	if (this == nullptr)
	{
		return nullptr;
	}
	return branches[base];
}

bool Node::hasBase(Base base)
{
	if (branches[base])
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Node::attachTag(ReadTag* tag)
{
	endTag.push_back(tag);
}

void Node::addWeight(int weight) {
	weights.push_back(Weight(weight));
}

int Node::avrWeight()
{
	if (weights.size() == 0) return -1;
	int sum = 0;
	for (int i = 0; i < weights.size(); i++)
	{
		sum += weights.at(i).get();
	}
	return sum / weights.size();
}

std::vector<ReadTag*> Node::getTags()
{
	return endTag;
}

std::vector<Weight> Node::getWeights()
{
	return weights;
}