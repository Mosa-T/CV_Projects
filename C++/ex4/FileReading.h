#ifndef FILEREADING_H_
#define FILEREADING_H_

#include <iostream>
#include <string>
#include <fstream>
#include "CGPoints.h"
using namespace std;




class FileReading {
public:
	double *teams; //every row's first two are the positions, two right after are speed componets for one player
	char *playerTypes;
	int playerSize;
	CGPoints targetPoint;
	int iterations;
	string line;
	~FileReading() { 
		delete teams;
		teams = NULL;
		//delete playerTypes; 
		playerTypes = NULL;
	}
	 FileReading(char *config, char *init) {

		double targetPointX, targetPointY;
		ifstream fileConfig(config);
		int numberOfLines=0;
		fileConfig >> targetPointX;
		fileConfig >> targetPointY;
		fileConfig >> iterations;
		targetPoint.SetPoint(targetPointX, targetPointY);
		fileConfig.close();
		ifstream fileInit(init);
		ifstream fileInit2(init);
		std::getline(fileInit, line);
		playerSize = atoi(line.c_str());
		this->teams = new double[playerSize*4]; //array to fill with each player's pos and speed,we know the length of each row and the number of plays.
		this->playerTypes = new char[playerSize]; //Saves the first letter of each row
		int count=0;
		while (std::getline(fileInit, line)) {
			++numberOfLines;
			for (int j = 0; j < (int)line.size();j++) {
				if (line[j] == ' ' || line[j] == '\n')
					count++;
			}
			if (count != 4) {
				std::cout<<"ERROR: Invalid input." << endl;
				std::exit(1);
			}
			count = 0;
		}
		if (numberOfLines != playerSize) {
			std::cout << "ERROR: Invalid input." << endl;
			std::exit(1);
		}
		count = 4;
		int j = 0;
		fileInit2 >> teams[0];
		for (int i = 0; i < playerSize*5; i++) {
			if (count == 4 && j < playerSize) {
				fileInit2 >> playerTypes[j++];
				count = 0;
			}
			fileInit2 >> teams[i];
			count++;
		}
		fileInit.close();
	}

	 double *GetTeams() {
		 return teams;
	 }

	 char *getPlayerTypes() {
		 return playerTypes;
	 }

	 void error() {
		 std::cout << "ERROR: Invalid input." << endl;
		 std::exit(1);
	 }
};

#endif 