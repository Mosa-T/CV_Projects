#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include "Element.h"
#include <iostream>

using namespace std;
template <class T>
class Sorting{
private:

public:
	//Gets vector of target vector, returns a vector with rankings of all target vectors.
	
	vector<int> static ParetoRanking(std::vector<vector<T> > m_array){
		vector<int> ranking(m_array.size());
		for (int i = 0; i < ranking.size(); i++)
		{
			ranking[i] = 0;
		}
		bool domi = false;
		bool atLeastOneIsLower = false;
		for (int i = 0; i < m_array.size(); i++)
		{
			for (int j = 0; j < m_array.size(); j++)
			{
				if (j != i)
				{
					domi = false;
					for (int k = 0; k < m_array[i].size(); k++)
					{
						if (m_array[i][k] < m_array[j][k])
							atLeastOneIsLower = true;
						if (m_array[i][k] <= m_array[j][k])
						{
							domi = true;
						}
						else
							domi = false;
					}
					if (domi == true && atLeastOneIsLower == true)
					{
						ranking[j] += 1;
					}
				}
			}
		}
		return ranking;
	}
	void static ElementsReordering(vector<Element> *elements)
	{
		int i, j;
		for (i = 0; i < elements->size()-1; i++)
		{
			for (j = 0; j < elements->size() - i - 1; j++)
			{
				if (elements->at(j).GetRank() > elements->at(j + 1).GetRank()) 
				{
					Element temp;
					temp = elements->at(j);
					elements->at(j) = elements->at(j + 1);
					elements->at(j + 1) = temp;
				}
			}
		}
	}
	void static ParetoSorting(vector<Element> *elements)
	{
		vector<vector<float> > targets;
		targets.resize(elements->size());
		for (int i = 0; i < elements->size(); i++)
		{
			targets[i] = elements->at(i).getF();
		}
		vector<int> ranks = ParetoRanking(targets);
		for (int i = 0; i < ranks.size(); i++)
		{
			elements->at(i).SetRank(ranks[i]);
		}
		ElementsReordering(elements);
	}
};




#endif