#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Element.h"
#include "Sorting.h"
#include "FileReading.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Simulator
{
private:
	vector<Element> *elements;
	int sizeOfarray;
	int sizeOfele;
	int itrations;
	int sizeTargets;
	float GenrateRandom();
	vector<float> GetRandomVector();
	FileReading *fReading;
	void PrintTargtes(string fileName)const;
	void BuildCpyElements();
	void PopHalfoftheElements();
public:
	Simulator(int argc, char **argv);
	virtual~Simulator();

};

#endif