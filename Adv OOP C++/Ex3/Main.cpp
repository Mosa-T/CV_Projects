#include <iostream>
#include <string>
#include "Init.h"

int main(int argc, char *argv[])
{
	try{
		init(argc, argv);
		Model::get_Instance().ResetInstance();
		View::get_Instance().ResetInstance();
		Controller::get_Instance().ResetInstance();
	}
	catch (string e)
	{
		std::cout << e << std::endl;
		exit(1);
	}
	return 0;
}