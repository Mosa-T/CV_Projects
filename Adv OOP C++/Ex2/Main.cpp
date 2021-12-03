#include <iostream>
#include <string>
#include "WorldMap.h"

using namespace std;


int main(int argc, char *argv[])
{
	
	try{
		WorldMap wm(argc, argv);
		wm.run();
	}
	catch (string e){
		cout << e;
		return 0;
	}
	return 0;
}


