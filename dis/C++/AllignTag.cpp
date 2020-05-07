#include "AllignTag.h"
#include <iostream>
AllignTag::AllignTag()
{
	id = -1;
}

AllignTag* AllignTag::getNext()
{
	if (next.size() > 0) {
		AllignTag* tag;
		std::map<int, AllignTag*>::iterator it;
		it = next.begin();
		tag = it->second;
		return tag;
	}
	else return new AllignTag();
}

int AllignTag::getID() {
	return id;
}

void AllignTag::setID(int i)
{
	id = i;
}

void AllignTag::setNext(AllignTag* nxt, int gap)
{
	next.insert_or_assign(gap, nxt);
}

int AllignTag::getOverlap()
{
	if (next.size() > 0) {
		int c;
		std::map<int, int>::iterator it;
		it = overlap.begin();
		c = it->second;
		return c;
	}
	else return 0;
}

void AllignTag::setOverlap(int c, int gap)
{
	overlap.insert_or_assign(gap, c);
}
