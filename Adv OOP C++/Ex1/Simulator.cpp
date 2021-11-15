#include "Simulator.h"



Simulator::Simulator()
{
	apexVirusTarget = NULL;
	maxItrations = 0;
	maxRank = 0;
	size = 0;
	sizefirstGens = 0;
}

Simulator::~Simulator()
{
	for (unsigned int i = 0; i < firstGen.size(); i++)
	{
		delete firstGen[i];
		delete mutations[i];
	}
		delete apexVirusTarget;
}
Simulator::Simulator(const Simulator &rhs)
{
	maxItrations = rhs.maxItrations;
	firstGen = rhs.firstGen;
	mutations = rhs.mutations;
	apexVirusTarget = rhs.apexVirusTarget;
	size = rhs.size;
}
Simulator& Simulator::operator=(const Simulator &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	maxItrations = rhs.maxItrations;
	firstGen = rhs.firstGen;
	mutations = rhs.mutations;
	apexVirusTarget = rhs.apexVirusTarget;
	size = rhs.size;
	return *this;
}

void Simulator::init(string config, string firstGens)
{
	maxRank = 0;
	ifstream inFile(config.c_str());
	string line;
	if (!inFile)
	{
		throw "ERROR: Invalid file name.";
	}
	std::getline(inFile, line);
	size = atoi(line.c_str());
	if (size < 2 || 1000 < size)
		throw "ERROR: invalid population size.";
	std::getline(inFile, line);
	line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
	if(line.size() != size)
		throw "ERROR: invalid target seq.";
	for (unsigned p = 0; p < line.size(); p++) {
		if (line.at(p) == 'A' || line.at(p) == 'C' || line.at(p) == 'G' || line.at(p) == 'T')
			continue;
		else
			throw "ERROR: invalid strand given.";
	}
	apexVirusTarget = new Virus(line);
	if(!(std::getline(inFile, line).eof()))
		throw "ERROR: invalid input.";
	maxItrations = atoi(line.c_str());
	if (maxItrations > 1000000)
		throw "ERROR: exceeding maximum iterations allowed";
	initFirstGen(firstGens);
} 

void Simulator::initFirstGen(string fgen)
{
	ifstream inFile(fgen.c_str());
	string line;
	int cnt = 0;
	if (!inFile)
	{
		throw "ERROR: Invalid file name.";
	}
	while (getline(inFile, line))
	{
		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
		
		if (cnt == 0)
		{
			
			sizefirstGens = atoi(line.c_str());
			if (sizefirstGens > 10000 || sizefirstGens < 2)
			{
				throw "ERROR: Invalid population size input.";
			}
		}
		else if (line.size()-1 != size){
			throw "ERROR: Invalid strand length.";
		}
		else if (line.size()-1 == size)
		{
			for (unsigned p = 0; p < line.size()-1; p++) {
				if (line.substr(1, line.size()).at(p) == 'A' || line.substr(1, line.size()).at(p) == 'C' || line.substr(1, line.size()).at(p) == 'G' || line.substr(1, line.size()).at(p) == 'T')
					continue;
				else
					throw "ERROR: invalid strand given.";
			}
			switch (line.at(0)) {
			case 'c': firstGen.push_back(new Covid(line.substr(1, line.size()))); break;
			case 's': firstGen.push_back(new Sars(line.substr(1, line.size()))); break;
			case 'm': firstGen.push_back(new Mers(line.substr(1, line.size()))); break;
			default: throw "ERROR: invalid virus type";
			}
		}
		cnt++;
	}
	if (cnt != sizefirstGens+1 || firstGen.size() != sizefirstGens)
		throw "ERROR: Invalid number of first gen strands.";
	for (unsigned int i = 0; i < sizefirstGens; i++)
	{

		switch ((*firstGen[i]).getType()) {
		case 'm': mutations.push_back(new Mers(dynamic_cast<Mers&>(*firstGen[i]))); break;
		case 's': mutations.push_back(new Sars(dynamic_cast<Sars&>(*firstGen[i]))); break;
		case 'c': mutations.push_back(new Covid(dynamic_cast<Covid&>(*firstGen[i]))); break;
		}
	}
	
}

void Simulator::updateRankings() 
{
	int tempRank = 0;
	for (unsigned int i = 0; i < sizefirstGens; i++)
	{
		tempRank = (mutations[i]->updateStanding(apexVirusTarget->getStrand()));
		if (maxRank < tempRank)
		{
			maxRank = tempRank;
			theApex.clear();
			theApex.push_back(mutations[i]->getType());
			theApex = theApex + mutations[i]->getStrand();
		}
	}
}


void Simulator::updateMutations()
{
	for (unsigned int i = 0; i < sizefirstGens; i++)
	{
		mutations[i]->mutate();
	}
}



void Simulator::swapSegments(int i, int j, Virus* virus1, Virus* virus2)
{
	char c;
	for (i; i < j; i++)
	{
		c = (*virus1)[i];
		(*virus1)[i] = (*virus2)[i];
		(*virus2)[i] = c;
	}
}

void Simulator::swapMutationSegments() 
{
	int virusA;
	int virusB;
	int s;
	int t;
	do {
		virusA = rand() % sizefirstGens;
		virusB = rand() % sizefirstGens;
	} while (virusA == virusB);
	do {
		s = rand() % size;
		t = rand() % size;
	} while (s == t);

	if (s > t) {
		int temp = s;
		s = t;
		t = temp;
	}
	std::sort(mutations.begin(), mutations.end(), [](const Virus* lhs, const Virus* rhs) {return lhs->getRank() < rhs->getRank(); });
	mutations[0]->decRef();
	mutations[1]->decRef();
	switch ((*firstGen[virusA]).getType()) {
	case 'm': mutations[0] = (new Mers(dynamic_cast<Mers&>(*firstGen[virusA]))); break;
	case 's': mutations[0] = (new Sars(dynamic_cast<Sars&>(*firstGen[virusA]))); break;
	case 'c': mutations[0] = (new Covid(dynamic_cast<Covid&>(*firstGen[virusA]))); break;
	}
	switch ((*firstGen[virusB]).getType()) {
	case 'm': mutations[1] = (new Mers(dynamic_cast<Mers&>(*firstGen[virusB]))); break;
	case 's': mutations[1] = (new Sars(dynamic_cast<Sars&>(*firstGen[virusB]))); break;
	case 'c': mutations[1] = (new Covid(dynamic_cast<Covid&>(*firstGen[virusB]))); break;
	}
	swapSegments(s, t, mutations[0], mutations[1]);
}


void Simulator::run() 
{
	srand(time(NULL));
	updateRankings(); //do one ranking update to check in case the first generation of mutations already has a perfect score
	for (int i = 0; i < maxItrations || maxRank == size; i++)
	{
		if (maxRank == size) break;
		updateMutations(); //run the probabilities of each strand of virus individually
		updateRankings();  //update the rankings of the newly mutated viruses
		if (maxRank == size) break;
		swapMutationSegments(); //pick the two lowest ranking viruses, replace them with two first gen viruses with swapped segments between them two.
		updateRankings(); //recheck ranking in case the newly added viruses have prefect scores
		if (maxRank == size) break;
	}
	finalize(); //prints all the required printings
}




void Simulator::finalize()
{
	
	
	for (unsigned int i = 0; i < mutations.size(); i++) //print mutations
	{
		cout << (*(mutations[i])).getType() << " ";
		for (int j = 0; j < size; j++)
		{
			cout << (*(mutations[i]))[j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	for (unsigned int i = 0; i < firstGen.size(); i++) //Print first gen 
	{
		cout << (*(firstGen[i])).getType() << " ";
		for (int j = 0; j < size; j++)
		{
			cout << (*(firstGen[i]))[j] << " ";
		}
		cout << (*(firstGen[i])).getRefCnt() - 1 << endl;

	}
	cout << endl;
	
	for (unsigned int i = 0; i < theApex.size(); i++) //printg highest ranking
	{
		cout << (theApex.at(i)) << " ";
	}
	cout << endl;

	/*
	cout << maxRank << " " << endl << "  ";
	for (int i = 0; i < size + 0; i++)
	{
		cout << apexVirusTarget->getStrand().at(i) << " ";
	}
	*/
}