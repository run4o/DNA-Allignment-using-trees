#include <iostream>
#include <fstream>
#include "DnaTree.h"
#include "Utilities.h"
#include "Base.h"
#include <time.h>

void dna::addReads(std::string seq, std::string weights, DnaTree* tree)
{
	std::vector<int> readW;
	std::vector<Base> readB;

	for (int i = 0; i < seq.length(); i++)
	{
		char b = seq[i];
		switch (b)
		{
		case 'A':
			readB.push_back(Base::A);
			break;
		case 'T':
			readB.push_back(Base::T);
			break;
		case 'G':
			readB.push_back(Base::G);
			break;
		case 'C':
			readB.push_back(Base::C);
			break;
		default:
			break;
		}
		readW.push_back(weights[i] - '!');
	}
	readB.push_back(Base::END);
	readW.push_back(-1);
	tree->addFragment(readB, readW);
	readB.clear();
	readW.clear();
}

void dna::readFastQ(std::string fileName, DnaTree* tree)
{
	//quality graph output
	std::ofstream output;
	output.open("quality.dis");

	//input file
	std::fstream input;
	input.open(fileName);

	//info prints
	int inputNumber = 0;
	std::string line;
	if (input.is_open())
	{
		std::cout << "\r        reading " << inputNumber;
		inputNumber++;

		while (input.eof() == false)
		{
			std::cout << "\r        reading " << inputNumber;
			inputNumber++;

			// saving seq_id
			getline(input, line);
			std::string seqID = line;
			//saving the seq.
			getline(input, line);
			std::string seq = line;
			//eating the "+"
			getline(input, line);
			//saving the weights
			getline(input, line);
			std::string weights = line;

			addReads(seq, weights, tree);
			output << weights;
		}

		input.close();
		output.close();
	}
	else {
#pragma warning "make it throw exception";
		std::cout << "File Not Found" << std::endl;
	}
}

Base** dna::fragmenter(std::vector<Base> bases)
{
	int size = bases.size();
	Base** data = new Base * [size];
	for (int i = 0; i < size; i++)
	{
		data[i] = new Base[size - i + 1];
		for (int j = 0; j < size - i; j++)
		{
			data[i][j] = bases[i + j];
		}
		data[i][size - i] = END;
	}

	return data;
};

void dna::execute(std::string filename, bool timed)
{
	//creating timer
	time_t delta;
	time_t start;
	time(&delta);
	time(&start);
	time_t current;
	//creating tree
	DnaTree* tree = new DnaTree();

	std::cout << "reading file\n";
	dna::readFastQ(filename, tree);
	if (timed)
	{
		time(&current);
		std::cout << "\r                     ";
		std::cout << "\r" << current - start << " seconds \n";
		start = current;
	}

	std::cout << "\nprinting\n";
	tree->print("out.txt");
	if (timed)
	{
		time(&current);
		std::cout << current - start << " seconds \n";
		start = current;
	}

	std::cout << "finding path\n";
	tree->findPath();
	if (timed)
	{
		time(&current);
		std::cout << current - start << " seconds \n";
		start = current;
	}

	std::cout << "\ncollecting data\n";
	tree->saveDistribution();
	if (timed)
	{
		time(&current);
		std::cout << current - start << " seconds \n";
		start = current;
	}

	if (timed)
	{
		time(&current);
		std::cout << "        Total run time: " << current - delta << "\n";
	}
	std::cout << "\nLaunching GUI\n";
	system("FYP.jar");
}

