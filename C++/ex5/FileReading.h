#ifndef FILEREADING_H_
#define FILEREADING_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

#include "Element.h"
using namespace std;




class FileReading {
public:
	vector<Element> vectors;
	unsigned int vecNum, vecSize, targetSize, iterations;
	~FileReading() {}
	FileReading() {}



	FileReading(char *fileName) {
		ifstream inFile(fileName);
		if (!inFile) {
			string s_temp = "ERROR: ";
			s_temp.append(fileName);
			s_temp.append(" does not exist or cannot be opened\n");
			throw s_temp;
		}
		string str_line;
		int cnt = 0;
		while (getline(inFile, str_line))
		{
			std::vector<float> v;
			// Build an istream that holds the input string
			std::istringstream iss(str_line);
			std::copy(std::istream_iterator<float>(iss),
				std::istream_iterator<float>(),
				std::back_inserter(v));
			if (cnt == 0)
			{
				if (v.size() != 4 || v[1] < v[2])
				{ ///////// throw here exception, passing first line arguement wrong
					string s_temp = "ERROR: simulation definition in ";
					s_temp.append(fileName);
					s_temp.append(" is invalid\n");
					throw s_temp;
					//throw "ERROR: simulation definition in <input> is invalid\n";	
				}
				vecNum = v[0];
				vecSize = v[1];
				targetSize = v[2];
				iterations = v[3];
				vectors = vector<Element>(vecNum); 
			}
			else if (v.size() !=  vecSize)
			{
				/////////////// size of cordiantes passing too few or long throw exception here
				string s_temp = "ERROR: population definition in ";
				s_temp.append(fileName);
				s_temp.append(" at line ");
				stringstream out;
				out << cnt+1; //cnt ignores the first row so need to add a +1
				s_temp.append(out.str());
				s_temp.append(" is invalid\n");
				throw s_temp;
			}
			else if (cnt != 0) {
				vectors[cnt - 1].SetM(targetSize); // this might be inside when creating vectors in line 51
				vectors[cnt - 1].SetX(v);
			}
			cnt++;
		}
	}
};

#endif 