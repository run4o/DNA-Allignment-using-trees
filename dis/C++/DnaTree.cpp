#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 
#include "DnaTree.h";
#include "Utilities.h"
#include "AllignTag.h"
#include "Weight.h"
#include "Base.h"
#include "Node.h"

void DnaTree::addFragment(std::vector<Base> bases, std::vector<int> weights)
{
	Base** fragments = dna::fragmenter(bases);

	for (int i = 0; i < bases.size() - 1; i++)
	{
		Node* current = root;
		int j = 0;
		while (fragments[i][j] != END)
		{
			current = current->addBranch(fragments[i][j]);
			current->addWeight(weights.at(j));
			j++;
		}
		ReadTag* tag = new ReadTag();
		current->attachTag(tag);
		reads.push_back(tag);
		delete[] fragments[i];
	}
	ReadTag::endRead();
	delete fragments;
}

DnaTree::DnaTree()
{
	root = new Node();
}

std::string spaces(int level)
{
	std::string spaces = "";
	for (int i = 0; i < level; i++)
	{
		spaces += "  ";
	}
	return spaces;
}

void printTags(Node* node, std::ostream& out)
{
	std::vector<ReadTag*> tags = node->getTags();

	for (int i = 0; i < tags.size(); i++)
	{
		out << "(" << tags.at(i)->getReadID() << "-" << tags.at(i)->getReadNumber() << ")";
	}
}

void DnaTree::print()
{
	std::ostream& output = std::cout;
	print(root, 0, BASE_COUNT, output);
}

void DnaTree::print(std::string file) {
	std::ofstream output;
	output.open(file);
	print(root, 0, BASE_COUNT, output);
	output.close();

}

void DnaTree::saveDistribution(std::ofstream& out, Node* current, int level)
{
	if (!current->hasBase(A) && !current->hasBase(T) && !current->hasBase(G) && !current->hasBase(C)) {
		out << level << " ";
	}
	if (current->hasBase(A)) saveDistribution(out, current->getBranch(A), level + 1);
	if (current->hasBase(T)) saveDistribution(out, current->getBranch(T), level + 1);
	if (current->hasBase(G)) saveDistribution(out, current->getBranch(G), level + 1);
	if (current->hasBase(C)) saveDistribution(out, current->getBranch(C), level + 1);
}

void DnaTree::saveDistribution()
{
	std::ofstream output;
	output.open("distribution.dis");
	saveDistribution(output, root, 0);
	output.close();
}

void DnaTree::print(Node* node, int level, Base currentBase, std::ostream& out)
{
	switch (currentBase)
	{
	case A:
		out << "A:";
		//out << node->avrWeight();
		printTags(node, out);
		break;
	case T:
		out << "T:";
		//out << node->avrWeight();
		printTags(node, out);
		break;
	case G:
		out << "G:";
		//out << node->avrWeight();
		printTags(node, out);
		break;
	case C:
		out << "C:";
		//out << node->avrWeight();
		printTags(node, out);
		break;
	default:
		break;
	}
	bool branched = false;
	if (node->hasBase(A) == true)
	{
		if (branched) out << '\n' << spaces(level);
		print(node->getBranch(A), level + 1, A, out);
		branched = true;
	}
	if (node->hasBase(T) == true)
	{
		if (branched) out << '\n' << spaces(level);
		print(node->getBranch(T), level + 1, T, out);
		branched = true;
	}
	if (node->hasBase(G) == true)
	{
		if (branched)out << '\n' << spaces(level);
		print(node->getBranch(G), level + 1, G, out);
		branched = true;
	}
	if (node->hasBase(C) == true)
	{
		if (branched) out << '\n' << spaces(level);
		print(node->getBranch(C), level + 1, C, out);
		branched = true;
	}
}

bool* found;
int haveFound = 0;
void DnaTree::findPath(std::ofstream& out, Node* current)
{
	if (current->getTags().size() > 0)
	{
		for (int i = 0; i < current->getTags().size(); i++)
		{
			if (!found[current->getTags()[i]->getReadID()])
			{
				std::cout << "\r finding path: " << haveFound++ << " of " << reads[reads.size() - 1]->getReadID();
				out << current->getTags().at(i)->getReadID() << " ";
				followTag(out, current->getTags()[i]);
				found[current->getTags()[i]->getReadID()] = true;
				out << "\n";
			}
		}
	}
	if (current->hasBase(A)) findPath(out, current->getBranch(A));
	if (current->hasBase(T)) findPath(out, current->getBranch(T));
	if (current->hasBase(G)) findPath(out, current->getBranch(G));
	if (current->hasBase(C)) findPath(out, current->getBranch(C));

}

bool done = false;
void DnaTree::followPath(std::ofstream& out, int id)
{
	done = false;
	followPath(out, root, id, nullptr, false, 0, 0);
}

void DnaTree::followPath(std::ofstream& out, Node* current, int id, ReadTag* prev, bool hasPrev, int level, int gap)
{
	if (!done) {
		if (current->getTags().size() > 0)
		{
			for (int i = 0; i < current->getTags().size(); i++)
			{
				if (reads[id]->getReadID() == current->getTags()[i]->getReadID() && reads[id]->getReadNumber() == current->getTags()[i]->getReadNumber())
				{
					done = true;
					if (hasPrev)
					{
						out << prev->getReadID() << " " << level << " " << level - gap;
					}
					else
					{
						out << "-1 -1 -1";
					}
				}
				else
				{
					hasPrev = true;
					gap = level;
					prev = current->getTags()[i];
				}
			}
		}
		if (current->hasBase(A))
		{
			followPath(out, current->getBranch(A), id, prev, hasPrev, level + 1, gap);
		}
		if (current->hasBase(T))
		{
			followPath(out, current->getBranch(T), id, prev, hasPrev, level + 1, gap);
		}
		if (current->hasBase(G))
		{
			followPath(out, current->getBranch(G), id, prev, hasPrev, level + 1, gap);
		}
		if (current->hasBase(C))
		{
			followPath(out, current->getBranch(C), id, prev, hasPrev, level + 1, gap);
		}
	}
}

void DnaTree::followTag(std::ofstream& out, ReadTag* tag)
{
	int id = -1;
	for (int i = 0; i < reads.size(); i++)
	{
		if (reads[i]->getReadID() == tag->getReadID() && reads[i]->getReadNumber() == 1)
		{
			id = i;
			break;
		}
	}
	if (id >= 0) {
		followPath(out, id);
	}
}

void DnaTree::findPath()
{
	found = new bool[reads[reads.size() - 1]->getReadID()];
	for (int i = 0; i < reads[reads.size() - 1]->getReadID() + 1; i++)
	{
		found[i] = false;
	}
	std::ofstream output;
	output.open("path.txt");
	findPath(output, root);
	output.close();
	reallign();
}

void DnaTree::reallign()
{
	std::map<int, AllignTag*> map;

	for (int i = 0; i < reads[reads.size() - 1]->getReadID(); i++)
	{
		AllignTag* tag = new AllignTag();
		tag->setID(i + 1);
		map.insert_or_assign(i + 1, tag);
	}

	std::ifstream path;
	path.open("path.txt");
	std::stringstream ss;
	std::string line;
	while (getline(path, line))
	{
		ss << line;
		int node, prev, level, gap;
		ss >> node >> prev >> level >> gap;
		if (prev != -1) {
			map[prev]->setNext(map[node], gap);
			map[prev]->setOverlap(level - gap, gap);
		}
		ss.clear();
	}
	path.close();

	std::map<int, AllignTag*>::iterator it;
	AllignTag* first = nullptr;
	int longest = 0;
	for (it = map.begin(); it != map.end(); it++)
	{
		int chain = 1;
		AllignTag* tag = it->second;
		AllignTag* start = tag;
		bool hasNext = true;
		std::vector<bool> elements(reads[reads.size() - 1]->getReadID(), false);
		elements[tag->getID() - 1] = true;
		while (hasNext)
		{
			AllignTag* next = tag->getNext();
			if (next->getID() == -1 || next->getID() == 0)
			{
				hasNext = false;
				if (chain > longest)
				{
					first = start;
					longest = chain;
				}
			}
			else if (elements[next->getID() - 1] == true)
			{
				hasNext = false;
				if (chain > longest)
				{
					first = start;
					longest = chain;
				}
			}
			else {
				elements[next->getID() - 1] = true;
				tag = next;
				chain++;
			}
		}
	}
	printChain(first);
}

std::string nextRead = "";
void DnaTree::printTag(AllignTag* tag, bool done, Node* current, std::string chain)
{
	if (!done)
	{
		if (current->getTags().size() > 0)
		{
			for (int i = 0; i < current->getTags().size(); i++)
			{
				if (tag->getID() == current->getTags()[i]->getReadID() && current->getTags()[i]->getReadNumber() == 1)
				{
					nextRead = chain;
				}
			}
		}
		if (current->hasBase(A))
		{
			printTag(tag, done, current->getBranch(Base::A), chain + "A");
		}
		if (current->hasBase(T))
		{
			printTag(tag, done, current->getBranch(Base::T), chain + "T");
		}
		if (current->hasBase(G))
		{
			printTag(tag, done, current->getBranch(Base::G), chain + "G");
		}
		if (current->hasBase(C))
		{
			printTag(tag, done, current->getBranch(Base::C), chain + "C");
		}
	}
}

void DnaTree::printChain(AllignTag* tag)
{
	std::ofstream out;
	out.open("sequence.txt");
	int i = 0;
	bool hasNext = true;
	std::vector<bool> test(reads[reads.size() - 1]->getReadID(), false);
	test[tag->getID() - 1] = true;
	int overlap = 0;
	while (hasNext) {
		AllignTag* next = tag->getNext();
		printTag(tag, false, root, "");
		out << nextRead.substr(overlap);
		overlap = tag->getOverlap();
		if (next->getID() == -1 || next->getID() == 0)
		{
			hasNext = false;
		}
		else if (test[next->getID() - 1] == true)
		{
			hasNext = false;
		}
		else
		{
			test[next->getID() - 1] = true;
			tag = next;
		}
	}
	std::cout << "\n";
}
