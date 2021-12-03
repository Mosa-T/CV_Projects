#include <iostream>

#include "Simulator.h"


int main(int argc, char *argv[])
{
	if (argc != 3) {
		cout << "ERROR: Invalid arguments." << endl;
		exit(1);
	}
	
	Simulator simulator;
	try{
		simulator.init(argv[1], argv[2]);
		simulator.run();
	}
	catch (const char* e) {
		cout << e << endl;
		exit(1);
	}
	return 0;
}