#pragma once
#include "_inc.h"

class cMap;
class cScript
{
public:
	static cScript* getInstance();

	bool run(cMap* map, ulong head, const std::string& name, const std::string& script);
	void run(sRole& role, ulong head, const std::string& name);
};







