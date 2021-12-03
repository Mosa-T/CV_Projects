#include "WaitingTimes.h"



WaitingTimes::WaitingTimes(vector<string> data)
{
	setDefWaitingTimes();
	vector<string> tokens;
	for (int i = 0; i < data.size(); i++)
	{
		tokens = split(data[i], "	");
		if (tokens.size() == 2)
		{
			setWaitingTime(tokens[0], tokens[1]);
		}
		else
		{
			throw "ERROR: config file is in wrong format";
		}
	}
}

void WaitingTimes::setDefWaitingTimes()
{
	bus = 1;
	tram = 2;
	sprinter = 3;
	rail = 5;
	intercity = 15;
	centraal = 10;
	stad = 5;
}


void WaitingTimes::setWaitingTime(string type, string time)
{
	if (type == "bus")
	{
		int bus = atoi(time.c_str());
		if (bus < 0)
			throw "ERROR : waiting time cannot be negative in config file";
	}
	else if (type == "tram")
	{
		int tram = atoi(time.c_str());
		if (tram < 0)
			throw "ERROR : waiting time cannot be negative in config file";
	}
	else if (type == "sprinter")
	{
		int sprinter = atoi(time.c_str());
		if (sprinter < 0)
			throw "ERROR : waiting time cannot be negative in config file";
	}
	else if (type == "rail")
	{
		int rail = atoi(time.c_str());
		if (rail < 0)
			throw "ERROR : waiting time cannot be negative in config file";
	}
	else if (type == "intercity")
	{
		int intercity = atoi(time.c_str());
		if (intercity < 0)
			throw "ERROR : waiting time cannot be negative in config file";

	}
	else if (type == "centraal")
	{
		int centraal = atoi(time.c_str());
		if (centraal < 0)
			throw "ERROR : waiting time cannot be negative in config file";
	}
	else if (type == "stad")
	{
		int stad = atoi(time.c_str());
		if (stad < 0)
			throw "ERROR : waiting time cannot be negative in config file";
	}
	else
	{
		throw "Error : type in config is not recognized";
	}
}

int WaitingTimes::getWaitingTime(VehicleType type)
{
	if (type == Bus)
	{
		return bus;
	}
	else if (type == Rail)
		return rail;
	else if (type == Tram)
		return tram;
	else
		return sprinter;

}

int WaitingTimes::getWaitingTime(StationType type)
{
	if (type == Intercity)
		return intercity;
	else if (type == Centraal)
		return centraal;
	else
		return stad;
}

vector<string> WaitingTimes::split(const string& str, const string& delim)// return without copying..removed a &
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