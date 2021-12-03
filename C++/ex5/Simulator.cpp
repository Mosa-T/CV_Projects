#include"Simulator.h"

float Simulator::GenrateRandom()
{
	float rand = ((((float)std::rand()) / RAND_MAX));
	return rand;
}


Simulator::~Simulator()
{
	if(fReading)
	delete fReading;
	if(elements)
	delete elements;
}

void Simulator::PrintTargtes(string fileName)const
{
	ofstream myfile;
	myfile.open(fileName.c_str());
	if (!myfile) {
		string s_temp = "ERROR: ";
		s_temp.append(fileName);
		s_temp.append(" does not exist or cannot be opened\n");
		throw s_temp;
	}
	for (unsigned int i = 0; i < elements->size(); i++)
	{
		for (int j = 0; j < elements->at(j).GetM(); j++)
		{
			myfile << round(1000000*elements->at(i).getF()[j])/1000000;
			if (j + 1 != elements->at(j).GetM())
			{
				myfile << " ";
			}
		}
		if (i + 1 != elements->size())
		{
			myfile << endl;
		}
	}
	myfile.close();

}

void Simulator::BuildCpyElements()
{
	int tempSize = elements->size();
	for (int i = 0; i < tempSize; i++)
	{
		Element temp = elements->at(i);
		elements->push_back(temp);
		vector<float> randomVector = GetRandomVector();
		vector<float> tempX;
		for (int j = 0; j < elements->at(i).GetN(); j++)// make new vector X add with random numbers
		{
			tempX.push_back(temp.getX()[j] + randomVector[j]);
		}
		elements->at(i + tempSize).SetX(tempX);
		tempX.clear();
		elements->at(i + tempSize).InitF();
	}
}

vector<float> Simulator::GetRandomVector()
{
	vector<float> temp(sizeOfele);
	for (int i = 0; i < sizeOfele; i++)
	{
		temp[i] = GenrateRandom();
	}
	return temp;
}


void Simulator::PopHalfoftheElements()
{
	int tempSize = elements->size();
	
	Element temp;
	int deleteTrickle;
	int rando;
	//for loop for when there are elements with same rank, takes two elements and randomzies which when will be "deleted"
	//the elements indexes are swapped in the vector for when the removing starts the one with the bigger index will be the first to be removed
	//this proecces goes on (if there are more than two with the same rank) untill the "losing" elements trickle down, down to the next in rankings, note that there is a possiblitiy that
	//same rankings will survive due to more than half lower ranks than the same ranking rank. 
	for (int j = 0; j < tempSize-1; j++) {
		if ((*elements)[j].GetRank() == (*elements)[j+1].GetRank()) {
		deleteTrickle = j;
		rando = (int)std::rand() % 101; //generate random number between 0 and 100
		//if the random number is below 50 (giving both elements a 50/50 chance) we swap between the elements, otherwise countine.
		if (rando < 50) { 
			temp = (*elements)[deleteTrickle];
			(*elements)[deleteTrickle] = (*elements)[j+1];
			(*elements)[j+1] = temp;
		}
		else
			continue;
		}
	}
	
	//removal of lowest ranks (as in with the biggest numbers)
	for (int i = 0; i < tempSize / 2; i++)
	{
		elements->pop_back();
	}
}

Simulator::Simulator(int argc, char **argv)
{
	try{
		fReading = NULL;
		elements = NULL;
		fReading = new FileReading(argv[1]);
		elements = new vector<Element>(fReading->vectors);
		sizeOfarray = fReading->vecNum;
		sizeOfele = fReading->vecSize;
		sizeTargets = fReading->targetSize;
		itrations = fReading->iterations;
		std::srand(std::time(NULL));
		for (unsigned int i = 0; i < elements->size(); i++) // inits all targets
		{
			elements->at(i).SetN(sizeOfele);
			elements->at(i).InitF();
		}
		for (int i = 0; i < itrations; i++){
			
			BuildCpyElements();
			Sorting<float>::ParetoSorting(elements);
			PopHalfoftheElements();
		}
		PrintTargtes(argv[2]);
	}
	catch (string err)
	{
		cout << err;
	}
}