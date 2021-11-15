#include "FileOpener.h"

FileOpener::FileOpener()
{

}
FileOpener::~FileOpener()
{

}

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

void FileOpener::open_file_castle(string fileName)
{
	ifstream inFile(fileName);
	if (!inFile) {
		throw string("Invalid input in file " + fileName + " at line 0.\n");
	}
	vector<string> tokens;
	string str_line;
	string delimiter = ",";
	int cnt = 0;
	while (getline(inFile, str_line)) {
		tokens = split(str_line, ",");
		if (tokens.size()!= 4) //check the input line if there are 3 parmaters 
			throw string("Invalid input in file " + fileName + " at line" + to_string(cnt) + ".\n");
		if (has_any_digits(tokens[0]) || !has_only_letters(tokens[0]))//check the name
			throw string("Invalid name in file " + fileName + " at line " + to_string(cnt) + ".\n");
		try{
			Coordinate location(tokens[1],tokens[2]);
			int stock = get_number_from_string(tokens[3]);
			string temp = tokens[0];
			vector<string> stocktemp;
			stocktemp.push_back(tokens[3]);
			shared_ptr<Zone> temp2 = af.createZone(ZoneFactory::TYPE::CASTLE, temp, location, stocktemp);
			zones.push_back(temp2);
		}
		catch (string e)
		{
			throw string(e + " at line " + to_string(cnt) + ".\n");
		}
		cnt++;
	}

}

void FileOpener::open_file_farm(string fileName)
{
	ifstream inFile(fileName);
	if (!inFile) {
		throw string("Invalid input in file " + fileName + " at line 0.\n");
	}
	vector<string> tokens;
	string str_line;
	string delimiter = ",";
	int cnt = 0;
	while (getline(inFile, str_line)) {
		tokens = split(str_line, ",");
		if (tokens.size() != 5) //check the input line if there are 3 parmaters 
			throw string("Invalid input in file " + fileName + " at line" + to_string(cnt) + ".\n");
		if (has_any_digits(tokens[0]) || !has_only_letters(tokens[0]))//check the name
			throw string("Invalid name in file " + fileName + " at line " + to_string(cnt) + ".\n");
		try {
			Coordinate location(tokens[1], tokens[2]);
			int stock = get_number_from_string(tokens[3]);
			int product = get_number_from_string(tokens[4]);
			string temp = tokens[0];
			vector<string> stocktemp;
			stocktemp.push_back(tokens[3]);
			stocktemp.push_back(tokens[4]);
			shared_ptr<Zone> temp2 = af.createZone(ZoneFactory::TYPE::FARM, temp, location, stocktemp);
			zones.push_back(temp2);
		}
		catch (string e)
		{
			throw string(e + " at line " + to_string(cnt) + ".\n");
		}
		cnt++;
	}
}



shared_ptr<Zone> FileOpener::findCastle(string findis) {
	for (unsigned int i = 0; i < zones.size(); i++) {
		if (zones[i]->getName() == findis) return zones[i];
	}
	throw string("Castle is not stored .\n");
}

shared_ptr<Zone> FileOpener::findFarm(string findis)
{
	for (unsigned int i = 0; i < zones.size(); i++) {
		if (zones[i]->getName() == findis) return zones[i];
	}
	throw string("farm is not stored .\n");
}

int FileOpener::get_number_from_string(string str)
{
	string temp = " ";
	if (str[0] != temp[0])
		throw string("Invalid number");
	str.erase(str.begin());
	bool check =  all_of(begin(str), end(str),
		[](char c) { return isdigit(c); });
	if (check)
		return stoi(str);
	else
		throw string("Invlid number");
}

bool FileOpener::has_only_letters(string str)
{
	return all_of(begin(str), end(str),
		[](char c) { return isalpha(c); });
}


