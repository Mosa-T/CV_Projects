#include "FileOpener.h"

vector<string> FileOpener::split(const string& str, const string& delim)// return without copying..removed a &
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

bool FileOpener::has_any_digits(const string& s)
{
	if (s.empty()) return false;

	std::size_t start = 0;
	if (start == s.length())
		return false;

	return s.find_first_not_of("0123456789", start) == std::string::npos;
}



VehicleType  FileOpener::getVehicleTypeFromFileName(string filename)
{
	string s2 = "bus";
	if (filename.find("bus") != std::string::npos) {
		return Bus;
	}
	if (filename.find("tram") != std::string::npos) {
		return Tram;
	}
	if (filename.find("sprinter") != std::string::npos) {
		return Sprinter;
	}
	if (filename.find("rail") != std::string::npos) {
		return Rail;
	}
	throw "Error filename must contatin one of these : bus,tram,sprinter,rail";
}

StationType FileOpener::getStationTypeFromString(string name)
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


void FileOpener::initOpenFile(string fileName, vector<shared_ptr<Station>>& stationGraph, vector<shared_ptr<Station>>& stationGraphRev)
{
	this->stationGraph = &stationGraph;
	this->stationGraphRev = &stationGraphRev;
	ifstream inFile(fileName);
	vector<string> tokens;
	if (!inFile) {
		throw string("Invalid input in file " + fileName + " at line 0.\n");
	}
	VehicleType typeVec = getVehicleTypeFromFileName(fileName);
	int cnt = 0;
	string str_line;
	string delimiter = "	";

	while (getline(inFile, str_line)) {//new node from the bus to somewhere
		tokens = split(str_line, "	");
		if (tokens.size() == 3)
		{
			string source_name;
			string target_name;
			if (tokens[0].size() > 32 || tokens[0].size() < 0)
			{
				throw string("Invalid input at line" + to_string(cnt) + "in file:" + fileName + ".\n");
			}
			else {
				source_name = move(tokens[0]);
				target_name = move(tokens[1]);
			}
			try {
				StationType sourceStationType = getStationTypeFromString(source_name);
				StationType targetStationType = getStationTypeFromString(target_name);
				int durationBetween = atoi(tokens[2].c_str());

				if (getIndexGivenNameInStationGraph(source_name) == -1)//source_name not in graph
				{
					auto target = shared_ptr<Station>(new Station(target_name, targetStationType, nullptr));

					if (getIndexGivenNameInStationGraph(target->getName()) == -1)//traget_name is not inside
					{
						target->addVehicle(Vehicle(typeVec, durationBetween, fileName));
						origin = shared_ptr<Station>(new Station(source_name, sourceStationType, target));
						origin->addVehicle(Vehicle(typeVec, 0, fileName)); //newly added
						stationGraph.push_back(origin);

						auto a = shared_ptr<Station>(new Station(target_name, targetStationType, nullptr));
						a->addVehicle(Vehicle(typeVec, 0, fileName));
						stationGraph.push_back(shared_ptr<Station>(a));
					}
					else//target name inside already just connect the target to the source_name
					{
						target->addVehicle(Vehicle(typeVec, durationBetween, (fileName)));
						origin = shared_ptr<Station>(new Station(source_name, sourceStationType, target));
						origin->addVehicle(Vehicle(typeVec, 0, fileName)); //newly added
						stationGraph.push_back(origin);
					}
				}
				else//source_name exists
				{
					
					int index = getIndexGivenNameInStationGraph(source_name);
					auto target = shared_ptr<Station>(new Station(target_name, targetStationType, nullptr));
					target->addVehicle(Vehicle(typeVec, durationBetween, fileName));
					setIntoStationGraphGivenName(source_name, target);
					if (getIndexGivenNameInStationGraph(target->getName()) == -1)// target is not in graph then add to graph as source
					{
						auto a = shared_ptr<Station>(new Station(target_name, targetStationType, nullptr));
						a->addVehicle(Vehicle(typeVec, 0, fileName));
						stationGraph.push_back(a);

					}
					
				}

				/*BUILD REV*/
				if (getIndexGivenNameInStationGraphRev(target_name) == -1)//source_name not in graph
				{
					auto targetRev = shared_ptr<Station>(new Station(source_name, sourceStationType, nullptr));
					if (getIndexGivenNameInStationGraphRev(targetRev->getName()) == -1)//traget_name is not inside
					{
						targetRev->addVehicle(Vehicle(typeVec, durationBetween, fileName));
						originRev = shared_ptr<Station>(new Station(target_name, targetStationType, targetRev));
						stationGraphRev.push_back(originRev);
						stationGraphRev.push_back(shared_ptr<Station>(new Station(source_name, sourceStationType, nullptr)));

					}
					else//target name inside already just connect the target to the source_name
					{
						targetRev->addVehicle(Vehicle(typeVec, durationBetween, (fileName)));
						originRev = shared_ptr<Station>(new Station(target_name, targetStationType, targetRev));
						stationGraphRev.push_back(originRev);
					}
				}
				else//source_name exists
				{
					int index = getIndexGivenNameInStationGraphRev(target_name);
					auto targetRev = shared_ptr<Station>(new Station(source_name, sourceStationType, nullptr));
					targetRev->addVehicle(Vehicle(typeVec, durationBetween, fileName));
					setIntoStationGraphGivenNameRev(target_name, targetRev);
					if (getIndexGivenNameInStationGraphRev(targetRev->getName()) == -1)// target is not in graph then add to graph as source
					{
						stationGraphRev.push_back(shared_ptr<Station>(new Station(source_name, sourceStationType, nullptr)));
					}
				}

			}
			catch (string e)
			{
				string err(e);
				err = err + "at line 0\n";
				throw err;
			}
		}
		else {
			throw string("Invalid input at line" + to_string(cnt) + ".\n");
		}
		cnt++;
	}
	origin = nullptr;
	inFile.close();
}




int FileOpener::getIndexGivenNameInStationGraph(string name)
{
	for (unsigned int i = 0; i < stationGraph->size(); i++)
	{
		if ((*stationGraph)[i]->getName() == name)
		{
			return i;
		}
	}
	return -1;
}


int FileOpener::getIndexGivenNameInStationGraphRev(string name)
{
	for (unsigned int i = 0; i < stationGraphRev->size(); i++)
	{
		if ((*stationGraphRev)[i]->getName() == name)
		{
			return i;
		}
	}
	return -1;
}

void FileOpener::setIntoStationGraphGivenName(string whereTo, shared_ptr<Station> obj)//obj = B
{
	bool exist = false;
	int index = getIndexGivenNameInStationGraph(whereTo);
	if (index > -1)
	{
		shared_ptr<Station> temp = stationGraph->at(index);
		while (temp->getNext() != nullptr)
		{
			if (temp->getNext()->getName() == obj->getName())
			{
				exist = true;
				break;
			}
			temp = temp->getNext();

		}
		if (exist) //already connected A to B 
		{
			auto list = obj->getVehicles();
			for (int i = 0; i < list.size(); i++)
			{
				temp->getNext()->addVehicle(list[i]);
			}
		}
		else {
			temp->setNext(obj);
		}
		return;
	}
	throw string("ERROR! this shouldn't happen");
}


void FileOpener::setIntoStationGraphGivenNameRev(string whereTo, shared_ptr<Station> obj)//obj = B
{
	bool exist = false;
	int index = getIndexGivenNameInStationGraphRev(whereTo);
	if (index > -1)
	{
		shared_ptr<Station> temp = stationGraphRev->at(index);
		while (temp->getNext() != nullptr)
		{
			if (temp->getNext()->getName() == obj->getName())
			{
				exist = true;
				break;
			}
			temp = temp->getNext();
		}
		if (exist)
		{
			auto list = obj->getVehicles();
			for (int i = 0; i < list.size(); i++)
			{
				temp->getNext()->addVehicle(list[i]);
			}
		}
		else {
			temp->setNext(obj);
		}
		return;
	}
	throw string("ERROR! this shouldn't happen");
}

WaitingTimes FileOpener::openfileConfig(string fileName)
{
	ifstream inFile(fileName);
	vector<string> tokens;
	if (!inFile) {
		throw string("Invalid input in file " + fileName + " at line 0.\n");
	}
	int cnt = 0;
	string str_line;
	string delimiter = "	";

	vector<string> lines;
	
	while (getline(inFile, str_line)) {//new node from the bus to somewhere
		lines.push_back(str_line);
	}
	return WaitingTimes(lines);
}