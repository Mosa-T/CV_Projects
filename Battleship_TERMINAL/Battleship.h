#pragma once
#ifndef _BATTLESHIP_H_
#define _BATTLESHIP_H_


#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iomanip>
#include <map>
#include <utility>
#include <iterator>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include "Ships.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "packets.h"
#include <pthread.h>
#include <errno.h>

using namespace std;

class Battleship {
private:
	int dim;
	vector<std::pair<string, char>> friendly_ships_coord;
	vector<std::pair<string, char>> sea_targets;
	Ships ship_sets;
public:
	Battleship(int dim);
	Battleship(){};
	void restart();
	void draw_grid();
	bool check_coords(string s,vector<string> vc_temp,int i,vector<string> vc);
	void set_ships();
	int attacked_square(string grid_coord);
	bool did_i_lose();
	void start();
	void turn_handle(int sock);
	void error(const char * str);
	void mark_hit(string grid_coord);
};




#endif
