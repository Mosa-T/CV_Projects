#pragma once
#include <iostream>
#include <string>
#include "Model.h"
#include "Controller.h" 

int init(int argc, char* argv[])
{
	try
	{
		Model::get_Instance().initModel(argc, argv);
		Controller::get_Instance().run();
	}
	catch (string e)
	{
		cout << e << endl;
		exit(1);
	}
	return 0;
}