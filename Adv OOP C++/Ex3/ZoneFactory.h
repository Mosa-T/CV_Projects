#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Castle.h"
#include "Farm.h"
#include <memory>
using namespace std;

class ZoneFactory
{
public:
	ZoneFactory() {}
	ZoneFactory& operator=(const ZoneFactory& rhs);
	ZoneFactory(const ZoneFactory& rhs);
	enum TYPE
	{
		CASTLE, FARM
	};
	template <typename T, typename U,typename V>
	shared_ptr<Zone> createZone(const ZoneFactory::TYPE& _enumType, T _parmater,U _parm2,vector<V> _parm3)
	{
		shared_ptr<Zone> pAgent = nullptr;
		switch (_enumType)
		{
		case ZoneFactory::CASTLE:
		{
			pAgent = make_shared<Castle>(_parmater,_parm2,_parm3);
			break;
		}
		case ZoneFactory::FARM:
		{
			pAgent = make_shared<Farm>(_parmater, _parm2, _parm3);
			break;
		}
		default:
			return pAgent;
		}
		return pAgent;
	}
};

