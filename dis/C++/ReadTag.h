#pragma once
#include <vector>
#include "FormalDeclarations.h"
// ReadTag globals
static int currentReadID = 1;
static int currentReadNumber = 1;

class ReadTag
{
private:
	unsigned int readID;
	unsigned int readNumber;
public:
	ReadTag();
	int getReadID();
	int getReadNumber();
	static void endRead();
};