#pragma once
#include <map>
class AllignTag
{
private:
	int id;
	std::map<int, int> overlap;
	std::map<int, AllignTag*> next;

public:
	AllignTag();
	AllignTag* getNext();
	int getID();
	void setID(int);
	void setNext(AllignTag*, int);
	int getOverlap();
	void setOverlap(int, int);
};
