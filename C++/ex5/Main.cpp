#include <iostream>
#include "Simulator.h"

int main(int argc, char **argv)
{
	if (argc != 3) {
			cout << "ERROR: not enough argument inputs in main\n";
			exit(1);
	}
	Simulator(argc,argv);
	return 0;
}