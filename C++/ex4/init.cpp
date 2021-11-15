
#include "init.h"

init::init(int argc,char** argv)
{
	char* inputFileConfig = argv[1]; char* inputFileInit = argv[2];
	//Check input.
	if (argc != 3) {
		std::cout << "ERROR: Invalid input." << endl; 
		std::exit(1);
	}
	if (!inputFileConfig) {
		std::cout << "ERROR: Invalid input." << endl;
		std::exit(1);
	}
	if (!inputFileInit) {
		std::cout << "ERROR: Invalid input." << endl;
		std::exit(1);
	}
	//Checks input and stores it into arrays.
	FileReading reader(inputFileConfig, inputFileInit);
	double posX, posY;
	std::vector<double> v;
	char type;
	int j = 0;
	Field field(reader.targetPoint, reader.playerSize); //create field where players will be, set target point.
	//fill the field with players.
	for (int i = 0; i < reader.playerSize * 4; i++) {
		type = reader.getPlayerTypes()[j++];
		posX = reader.GetTeams()[i++];
		posY = reader.GetTeams()[i++];
		v.push_back(reader.GetTeams()[i++]);
		v.push_back(reader.GetTeams()[i]);
		field.setPlayer(*(new CGPoints(posX, posY)), v, type);
		v.clear();
	}
	
	int a = 0;
	//simulate a match.
	while (a < reader.iterations) {
		field.updateStats();
		a++;
		if ((int)field.getGlobalBest().GetX() == (int)reader.targetPoint.GetX() && (int)field.getGlobalBest().GetY() == (int)reader.targetPoint.GetY())
			break;
	}
	cout << a << endl; //Number of iterations.
	field.printAll(); //print the stats of players at the end of the match.
}

