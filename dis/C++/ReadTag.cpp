#include "ReadTag.h"

ReadTag::ReadTag()
{
	readID = currentReadID;
	readNumber = currentReadNumber++;
}

int ReadTag::getReadID()
{
	return readID;
}

int ReadTag::getReadNumber()
{
	return readNumber;
}

void ReadTag::endRead()
{
	currentReadID += 1;
	currentReadNumber = 1;
}
