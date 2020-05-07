#pragma once
class Weight
{
private:
	char w;
public:
	Weight(int set) : w(set) {}
	void set(int);
	int get();
};