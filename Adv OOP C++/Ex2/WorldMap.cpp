#include "WorldMap.h"


WorldMap::WorldMap(string fileName) {
	try {
		file.initOpenFile(fileName, stationGraph,stationGraphRev);
	}
	catch (string e)
	{
		cout << e;
		exit(1);
	}
}

string WorldMap::isSetOutPutFile(vector<string> args)
{
	for (vector<string>::iterator t = args.begin(); t != args.end(); ++t)
	{
		if (*t == "-o")
		{
			if (++t != args.end())
			{
				return *t;
			}
			else throw "after setting flag '-o' need to come filepath";
		}
	}
	return "";
}

string WorldMap::isSetConfigFile(vector<string> args)
{
	for (vector<string>::iterator t = args.begin(); t != args.end(); ++t)
	{
		if (*t == "-p")
		{

			if (++t != args.end())
			{
				return *t;
			}
			else throw "after setting flag '-p' need to come filepath";
		}
	}
	return "";
}

WorldMap::WorldMap(int argc, char* argv[])
{
	times = WaitingTimes();
	string setOutput_file = "output.dat";
	string setConfig_file = "";
	of_file_string = setOutput_file;
	string fileName;
	string current_exec_name = argv[0]; 
	vector<std::string> all_args;
	if (argc > 1) {
		all_args.assign(argv + 1, argv + argc);
	}
	
	bool dataFile = true;
	auto args_size = all_args.size();
	for (int i = 0; i < args_size; i++)
	{
		if (i == 0 && all_args[i] != "-i")
			throw "invlid first argument in command line must be '-i'";
		else if ( all_args[i] == "-i")
		{
			try {
				i++;
				while (all_args[i] != "-c" && all_args[i] != "-o") {
					file.initOpenFile(all_args.at(i++), stationGraph,stationGraphRev);
					if (i >= args_size)
						break;
				}
			}
			catch (string ex)
			{
				cout << ex;
				exit(1);
			}
		}
		if (i < argc-1) {
			if (all_args[i] == "-c")
			{
				dataFile = false;
				if (i + 1 == args_size)
					throw "Error: after flag '-c' must come file config";
				else
				{
					setConfig_file = all_args.at(++i);
					times = FileOpener::openfileConfig(setConfig_file);
					continue;
				}
			}
			if (all_args[i] == "-o")
			{
				dataFile = false;
				if (i + 1 == args_size)
					throw "Eror: after flag '-o' must come file output";
				else
				{
					setOutput_file = all_args.at(++i);
					of_file_string = setOutput_file;
				}
			}
		}
	}
}

WorldMap::WorldMap()
{

}

void WorldMap::run()
{
	string str;
	vector<string> tokens;
	while (true)
	{
		std::getline(std::cin, str);
		tokens = split(str, " ");
		if (str == "exit") {
			exit(1);
		}
		switch (tokens.size())
		{
		case (1):
			if (tokens.at(0) == "print") {
				printGraphs();
			}
			else cout << "USAGE : 'load', <file> *or*\n<node>, 'outbound' / 'inbound'*or*" << endl << "<node>, 'uniExpress', <node>*or*" << endl << "'multiExpress' <node>*or*" << endl << "'exit' *to terminate*" << endl;
			break;
		case(2):
			if (tokens.at(0) == "load") {

				try {
					file.initOpenFile(tokens.at(1), stationGraph,stationGraphRev);
					cout << "Update was successful." << endl;
				}
				catch (string e)
				{
					cout << e;
				}
			}
			else if (tokens.at(0) == "inbound") {
				try {
					getInbound(tokens[1],0);
				}
				catch (string e)
				{
					cout << e;
				}
			}
			else if (tokens.at(0) == "outbound") {
				try {
					getOutbound(tokens[1]);
				}
				catch (string e)
				{
					cout << e;
				}
			}
			else {
				cout << "USAGE : 'load', <file> *or*\n<node>, 'outbound' / 'inbound'*or*" << endl << "<node>, 'uniExpress', <node>*or*" << endl << "'multiExpress' <node>*or*" << endl << "'exit' *to terminate*" << endl;
			}
			break;

		case(3):
			if (tokens.at(0) == "uniExpress") {
				try {
					uniExpress(tokens[1], tokens[2]);
				}
				catch (string e) {
					cout << e;
				}
			}
			else if (tokens.at(0) == "multiExpress") {
				multiExpress(tokens[1], tokens[2]);
			}
			break;

		default: cout << "USAGE : 'load', <file> *or*\n<node>, 'outbound' / 'inbound'*or*" << endl << "<node>, 'uniExpress', <node>*or*" << endl << "'multiExpress' <node>*or*" << endl << "'exit' *to terminate*" << endl;
		}
	}
}


vector<string> WorldMap::split(const string& str, const string& delim)
{
	vector<string> tokens;
	std::size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}


void WorldMap::printGraphs()
{
	ofstream of_file(of_file_string);
	shared_ptr<Station> temp = stationGraph[0];
	if (of_file.is_open()) {

		int sg_size = stationGraph.size();
		for (int i = 0; i < sg_size; i++)
		{
			temp = stationGraph[i];
			of_file << temp->getName() << ": " << endl;
			do
			{
				of_file << temp->to_string() << endl;
				temp = temp->getNext();
			} while (temp != nullptr);
			of_file << endl << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			
		}
		of_file.close();
	}
}

void WorldMap::printType(VehicleType a) {
	switch (a) {
	case 0: cout << "Bus:	";
	case 1: cout << "Tram:	"; break;
	case 2: cout << "Sprinter:	"; break;
	case 3: cout << "Rail:	"; break;
	}
}


vector<shared_ptr<Station>> WorldMap::getReversedGraph(vector<shared_ptr<Station>> original)
{
	auto cpy = original; 
	vector<shared_ptr<Station>>  revGraph(original.size());
	for (int i = 0; i < revGraph.size(); i++)
	{
		revGraph[i] = make_shared<Station>( original[i]);
		revGraph[i]->setNext(nullptr);
	}
	for (int i = 0; i < original.size(); i++)
	{
		auto temp = make_shared<Station>( original[i]);
		temp = temp->getNext();
		vector<Station> sources;
		while (temp != nullptr)
		{
			sources.push_back(shared_ptr<Station>(temp));
			temp = temp->getNext();
		}
		for (int k = 0; k < sources.size(); k++)
		{
			auto j = getIndexGivenName(revGraph, sources[k].getName());
			
				auto temp2 = revGraph[j];
				if (!findLocation(temp2, revGraph[j]->getName()))
					break;
				while (temp2->getNext() != nullptr ) {
					if (!findLocation(temp2, original[i]->getName()))
						temp2 = temp2->getNext();
				}
				temp2->setNext(original[i]);
			
		}
	}

	return revGraph;
}

shared_ptr<Station> WorldMap::findLocation(shared_ptr<Station> a, string name) {
	while (a != nullptr) {
		if (a->getName() == name)
			break;
		a = a->getNext();
	}
	return a;
}

int WorldMap::getIndexGivenName(vector<shared_ptr<Station>> a, string name) {
	for (unsigned int i = 0; i < a.size(); i++) {
		if (a[i]->getName() == name)
			return i;
	}
}



bool WorldMap::doesContainVehcileTypeRev(VehicleType type, vector<Vehicle> cars)
{
	for (int i = 0; i < cars.size(); i++)
	{
		if (type == cars.at(i).getType())
			return true;
	}
	return false;
}


bool containsRev(vector<string> v, string t)
{
	if (std::find(v.begin(), v.end(), t) != v.end())
	{
		return true;
	}
	return false;
}





vector<string> WorldMap::getallConectedViaTypeVehicleRev(vector<string> need_to_check, VehicleType typeV, vector<string> checked)
{
	for (int i = 0; i < need_to_check.size(); i++)
	{
		auto j = getIndexGivenNameInStationGraphRev(need_to_check[i]);
		auto temp = stationGraphRev[j];
		checked.push_back(temp->getName());
		temp = temp->getNext();
		while (temp != nullptr && doesContainVehcileTypeRev(typeV, temp->getVehicles()))
		{
			if (!containsRev(checked, temp->getName()))
				need_to_check.push_back(temp->getName());
			temp = temp->getNext();
		}
	}
	checked.erase(checked.begin());
	return checked;
}

int WorldMap::getIndexGivenNameInStationGraphRev(string name) {
	for (unsigned int i = 0; i < stationGraphRev.size(); i++)
	{
		if ((stationGraphRev)[i]->getName() == name)
		{
			return i;
		}
	}
	return -1;
}




void WorldMap::getInbound(string name,int i)
{
	vector<string> buses;
	vector<string> trams;
	vector<string> sprinters;
	vector<string> rails;

	shared_ptr<Station> temp;
	bool exist = false;
	int index = getIndexGivenNameInStationGraphRev(name);
	if (index > -1)
	{
		vector<string> need_to_check;
		need_to_check.push_back(name);
		vector<string> empty;
		buses = getallConectedViaTypeVehicleRev(need_to_check, Bus, empty);
		trams = getallConectedViaTypeVehicleRev(need_to_check, Tram, empty);
		sprinters = getallConectedViaTypeVehicleRev(need_to_check, Sprinter, empty);
		rails = getallConectedViaTypeVehicleRev(need_to_check, Rail, empty);
	}
	else
		throw string(name + " does not exist in the database.\n");

	printAllInBound(buses, trams, sprinters, rails);
}


void WorldMap::printAllInBound(vector<string> bus, vector<string> trams, vector<string> sprinters, vector<string> rails)
{

	if (bus.size() == 0)
		cout << "bus: no inbound travel" << endl;
	else
	{
		cout << "bus: ";
		for (auto i = bus.begin(); i != bus.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
	if (trams.size() == 0)
		cout << "tram: no inbound travel" << endl;
	else
	{
		cout << "tram: ";
		for (auto i = trams.begin(); i != trams.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
	if (sprinters.size() == 0)
		cout << "sprinter: no inbound travel" << endl;
	else
	{
		cout << "sprinter: ";
		for (auto i = sprinters.begin(); i != sprinters.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
	if (rails.size() == 0)
		cout << "rail: no inbound travel" << endl;
	else
	{
		cout << "rail: ";
		for (auto i = rails.begin(); i != rails.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
}







void WorldMap::printAllOutBound(vector<string> bus, vector<string> trams, vector<string> sprinters, vector<string> rails)
{
	if (bus.size() == 0)
		cout << "bus: no outbound travel" << endl;
	else
	{
		cout << "bus: ";
		for (auto i = bus.begin(); i != bus.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
	if (trams.size() == 0)
		cout << "tram: no outbound travel" << endl;
	else
	{
		cout << "tram: ";
		for (auto i = trams.begin(); i != trams.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
	if (sprinters.size() == 0)
		cout << "sprinter: no outbound travel" << endl;
	else
	{
		cout << "sprinter: ";
		for (auto i = sprinters.begin(); i != sprinters.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
	if (rails.size() == 0)
		cout << "rail: no outbound travel" << endl;
	else
	{
		cout << "rail: ";
		for (auto i = rails.begin(); i != rails.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
}



bool WorldMap::doesContainVehcileType(VehicleType type, vector<Vehicle> cars)
{
	for (int i = 0; i < cars.size(); i++)
	{
		if (type == cars.at(i).getType())
			return true;
	}
	return false;
}


bool contains(vector<string> v, string t)
{
	if (std::find(v.begin(), v.end(), t) != v.end())
	{
		return true;
	}
	return false;
}

vector<string> WorldMap::getallConectedViaTypeVehicle(vector<string> need_to_check, VehicleType typeV, vector<string> checked)
{
	for (int i = 0; i < need_to_check.size(); i++)
	{
		auto j = getIndexGivenNameInStationGraph(need_to_check[i]);
		auto temp = stationGraph[j];
		checked.push_back(temp->getName());
		temp = temp->getNext();
		while (temp != nullptr && doesContainVehcileType(typeV, temp->getVehicles()))
		{
			if (!contains(checked, temp->getName()))
				need_to_check.push_back(temp->getName());
			temp = temp->getNext();
		}
	}
	checked.erase(checked.begin());
	return checked;
}



void WorldMap::getOutbound(string name)
{
	vector<string> buses;
	vector<string> trams;
	vector<string> sprinters;
	vector<string> rails;

	shared_ptr<Station> temp;
	bool exist = false;
	int index = getIndexGivenNameInStationGraph(name);
	if (index > -1)
	{
		vector<string> need_to_check;
		need_to_check.push_back(name);
		vector<string> empty;
		buses = getallConectedViaTypeVehicle(need_to_check, Bus, empty);
		trams = getallConectedViaTypeVehicle(need_to_check, Tram, empty);
		sprinters = getallConectedViaTypeVehicle(need_to_check, Sprinter, empty);
		rails = getallConectedViaTypeVehicle(need_to_check, Rail, empty);
	}
	else
		throw string(name + " does not exist in the database.\n");

	printAllOutBound(buses, trams, sprinters, rails);
}







int WorldMap::getIndexGivenNameInStationGraph(string name) {
	for (unsigned int i = 0; i < stationGraph.size(); i++)
	{
		if ((stationGraph)[i]->getName() == name)
		{
			return i;
		}
	}
	return -1;
}



bool WorldMap::findName(vector<Station> a, string name) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i].getName() == name)
			return true;
	}
	return false;
}



StationType WorldMap::getStationTypeFromString(string name)
{
	if (name.empty())
		throw "Error : name of station cannot be empty ";
	if (name.length() > 2)
	{
		if (name.substr(0, 1) == "IC")
		{
			return Intercity;
		}
		else if (name.substr(0, 1) == "CS")
		{
			return Centraal;
		}
	}
	else
	{
		return Stad;
	}
}

bool WorldMap::doesContainVehcileTypeName(string name, vector<Vehicle> cars)
{
	for (int i = 0; i < cars.size(); i++)
	{
		if (name == cars.at(i).getName())
			return true;
	}
	return false;
}

void WorldMap::uniExpress(string source, string dest) {
	int busess = -1;
	int tramss = -1;
	int sprinterss = -1;
	int railss = -1;
	int index = getIndexGivenNameInStationGraph(dest);
	int index2 = getIndexGivenNameInStationGraph(source);
	if (index > -1 && index2 > -1)
	{
 		 busess = getShortestRouteGivenVehicle(source, dest, Bus);
		 tramss = getShortestRouteGivenVehicle(source, dest, Tram);
		 sprinterss = getShortestRouteGivenVehicle(source, dest, Sprinter);
		 railss = getShortestRouteGivenVehicle(source, dest, Rail);
	}
	else
		throw string(dest + " does not exist in the database.\n");

	printUniExpress(busess, tramss, sprinterss, railss);
}

void WorldMap::printUniExpress(int bus, int trams, int sprinters, int rails) {
	if (bus == INT_MAX || bus <= 0)
		cout << "bus: route unavailable" << endl;
	else
	{
		cout << "bus:	" << bus << endl;
		
	}
	if (trams == INT_MAX || trams <= 0 )
		cout << "tram: route unavailable" << endl;
	else
	{
		cout << "tram:	" << trams << endl;

	}
	if (sprinters == INT_MAX || sprinters <= 0)
		cout << "sprinter: route unavailable" << endl;
	else
	{
		cout << "sprinter:	" << sprinters << endl;

		
	}
	if (rails == INT_MAX || rails <= 0)
		cout << "rail: route unavailable" << endl;
	else
	{
		cout << "rail:	" << rails << endl;

		
	}
}



vector<vector<int>> WorldMap::getGraphGivenType(vector<shared_ptr<Station>> origin, VehicleType type)
{
	vector<vector<int>> graph(origin.size(), vector<int>(origin.size(), 0));

	
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			graph[i][j] = neighborNode(i, j, type);
		}
	}
	
	return graph;
}

int WorldMap::neighborNode(int i, int j, VehicleType type)
{
	if (i > stationGraph.size() || j > stationGraph.size())
		throw "ERROR : indexs larger than size of station graph";
	string target_name = givenIndexReturnName(j);
	auto temp = stationGraph[i];
	temp = temp->getNext();
	while (temp != nullptr)
	{
		if (temp->getName() == target_name)
		{
			if (doesContainVehcileType(type, temp->getVehicles()))
			{
				return getShortestDurationGivenTypeNVehicles(type, temp->getVehicles());
			}
			return 0; 
		}
		temp = temp->getNext();
	}
	return 0;
}

int WorldMap::getShortestDurationGivenTypeNVehicles(VehicleType type, vector<Vehicle> vehicles)
{
	bool shortestfound = false;
	int lowest;
	for (int i = 0; i < vehicles.size(); i++)
	{
		if (type == vehicles[i].getType())
		{
			if (shortestfound)
			{
				if (lowest > vehicles[i].getDuartion())
				{
					lowest = vehicles[i].getDuartion();
				}
			}
			else
			{
				lowest = vehicles[i].getDuartion();
				shortestfound = true;
			}
		}
	}
	return lowest;
}




string WorldMap::givenIndexReturnName(int i)
{
	if (i < stationGraph.size())
	{
		return stationGraph[i]->getName();
	}
	else
		throw "ERROR : index larger than size of station graph";
}



int WorldMap::minDistance(vector<int> dist, vector<bool> sptSet, int V)
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}

vector<int> WorldMap::dijkstra(vector<vector<int>> graph, int src)
{
	auto V = graph.size();
	vector<int> dist(graph.size());
	vector<bool> sptSet(graph.size());
	
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;
	dist[src] = 0;
	for (int count = 0; count < V ; count++) {
		int u = minDistance(dist, sptSet, V);
		sptSet[u] = true;
		for (int v = 0; v < V -1; v++)
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	return dist;
}

int WorldMap::getShortestRouteGivenVehicle(string source, string target, VehicleType type)
{
	auto graph = getGraphGivenType(stationGraph, type);
	vector<int> distances = dijkstra(graph, getIndexGivenNameInStationGraph(source));
	return distances[getIndexGivenNameInStationGraph(target)];
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WorldMap::multiExpress(string source, string dest) {
	int theBest = -1;
	int index = getIndexGivenNameInStationGraph(dest);
	int index2 = getIndexGivenNameInStationGraph(source);
	if (index > -1 && index2 > -1)
	{
		theBest = getShortestRouteMult(source,dest,Bus);
		auto theBestRail = getShortestRouteMult(source, dest, Rail);
		auto theBestTram = getShortestRouteMult(source, dest, Tram);
		auto theBestSpritner = getShortestRouteMult(source, dest, Sprinter); 

		if (theBest > theBestRail)
			theBest = theBestRail;
		if (theBest > theBestSpritner)
			theBest = theBestSpritner;
		if (theBest > theBestTram)
			theBest = theBestTram;
		auto type1 = stationGraph[index]->getType();
		auto type2 = stationGraph[index2]->getType();
		if (theBest - times.getWaitingTime(type1) - times.getWaitingTime(type2) > 0)
		{
			theBest = theBest - times.getWaitingTime(type1) - times.getWaitingTime(type2);
		}
		
	}
	else
		throw string(dest + " does not exist in the database.\n");
	printUniExpress(theBest);
}


void WorldMap::printUniExpress(int theBest) {
	if (theBest > 0)
		cout << theBest << endl;
	else
		cout << "Invalid route" <<endl;
}






int WorldMap::getShortestRouteGivenVehicleMult(string source, string target,VehicleType type)
{
	auto graph = getGraphGivenTypeMult(stationGraph,type);
	vector<int> distances = dijkstra(graph, getIndexGivenNameInStationGraph(source));
	return distances[getIndexGivenNameInStationGraph(target)];
}





vector<vector<int>> WorldMap::getGraphGivenTypeMult(vector<shared_ptr<Station>> origin, VehicleType type)
{
	vector<vector<int>> graph(origin.size(), vector<int>(origin.size(), 0));

	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			graph[i][j] = neighborNodeMult(i, j,  type);
		}
	}
	return graph;
}

int WorldMap::neighborNodeMult(int i, int j, VehicleType type) {
	if (i > stationGraph.size() || j > stationGraph.size())
		throw "ERROR : indexs larger than size of station graph";
	string target_name = givenIndexReturnName(j);
	auto temp = stationGraph[i];
	temp = temp->getNext();
	while (temp != nullptr)
	{
		if (temp->getName() == "peepee" || temp->getName() == "ICpeepee")
			cout << "Reached peepe";
		if (temp->getName() == target_name)
		{
				return getShortestDurationGivenTypeNVehiclesMult(type, temp->getVehicles(), temp->getType());
		}
		
		temp = temp->getNext();
	}
	return 0;
}

int WorldMap::getShortestRouteMult(string source,string target,VehicleType type)
{
	auto graph = getGraphGivenTypeMult(stationGraph, type);
	vector<int> distances = dijkstra(graph, getIndexGivenNameInStationGraph(source));
	return distances[getIndexGivenNameInStationGraph(target)];
}




int WorldMap::getShortestDurationGivenTypeNVehiclesMult(VehicleType type, vector<Vehicle> vehicles,StationType statType)
{
	bool shortestfound = false;
	int lowest;
	for (int i = 0; i < vehicles.size(); i++)
	{
		if (type == vehicles[i].getType())
		{
			if (shortestfound)
			{
				if (lowest > vehicles[i].getDuartion())
				{
					lowest = vehicles[i].getDuartion();
				}
			}
			else
			{
				lowest = vehicles[i].getDuartion();
				shortestfound = true;
			}
		}
		else {
			int a = times.getWaitingTime(statType) + vehicles[i].getDuartion();
			if (!shortestfound)
			{
				lowest = a;
				shortestfound = true;
			}
			else if (shortestfound && lowest > a)
				lowest = a;
		}
	}
	return lowest;
}