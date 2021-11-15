#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Agent.h"
#include "Thug.h"
#include "Peasant.h"
#include "Knight.h"
#include <memory>
using namespace std;

class AgentFactory
{
public:
	AgentFactory(){}
	AgentFactory& operator=(const AgentFactory& rhs);
	AgentFactory(const AgentFactory& rhs);
	enum TYPE
	{
		PEASANT, KNIGHT, THUG
	};
	template <typename T>
	shared_ptr<Agent> createVehicle(const AgentFactory::TYPE &_enumType, T _parmater)
	{
		shared_ptr<Agent> pAgent = nullptr;
		switch (_enumType)
		{
		case AgentFactory::PEASANT:
			{
				pAgent = make_shared<Peasant>(_parmater);
				break;
			}
		case AgentFactory::KNIGHT :
			{
				pAgent = make_shared<Knight>(_parmater);
				break;
			}
		case AgentFactory::THUG :
			{
			pAgent = make_shared<Thug>(_parmater);
				break;
			}
			default:
				return pAgent;
		}
		return pAgent;
	}
};

