#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "Mers.h"
#include "Covid.h"
#include "Sars.h"
#include <algorithm>
#include <time.h>
class Simulator
{
private:
	string theApex;
	vector<Virus*> firstGen;
	vector<Virus*> mutations;
	Virus* apexVirusTarget;
	int maxRank;
	int maxItrations;
	int size;
	int sizefirstGens;
	void initFirstGen(string fgen);
	void updateRankings(); 
	void swapMutationSegments();
	void updateMutations();
	void finalize();
	void swapSegments(int i, int j, Virus* virus1, Virus* virus2);
public:
	void init(string config, string firstGen);
	void run();
	Simulator();
	Simulator(const Simulator &rhs);
	Simulator& operator=(const Simulator &rhs);
	~Simulator();
};