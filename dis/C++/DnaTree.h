#pragma once

#include "FormalDeclarations.h"
#include <fstream>
#include <vector>
#include <ostream>
#include <iostream>
#include <string>
#include "AllignTag.h"
#include "Node.h"
#include "ReadTag.h"
#include "Base.h"

class DnaTree
{
private:
	std::vector<ReadTag*> reads;
	Node* root;
	void print(Node*, int, Base, std::ostream&);
	void saveDistribution(std::ofstream&, Node*, int);
	void findPath(std::ofstream&, Node*);
	void followPath(std::ofstream&, Node*, int, ReadTag*, bool, int, int);
	void followPath(std::ofstream&, int);
	void followTag(std::ofstream&, ReadTag*);
	void reallign();
	void printChain(AllignTag*);
	void printTag(AllignTag*, bool, Node*, std::string);
public:
	DnaTree();
	void addFragment(std::vector<Base> bases, std::vector<int>);
	void findPath();
	void print();
	void print(std::string);
	void saveDistribution();
};
