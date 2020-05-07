#pragma once
#include <string>
#include "DnaTree.h"
namespace dna
{
	void addReads(std::string seq, std::string weights, DnaTree* tree);
	void readFastQ(std::string  fileName, DnaTree* tree);
	Base** fragmenter(std::vector<Base>);
	void execute(std::string filename,bool timed = false);
}
