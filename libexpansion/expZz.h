#pragma once
#include "expEasy.h"

class expZz : public expEasy
{
public:
	CREATE_FUNC(expZz);
	static expZz* createWm() { CREATE(expZz, true); }
protected:
	bool init(bool iswm = false);
	cNode* createHead(const txtAction::sAction& act, const std::string& name = "");
	cNode* initDrag(int tag, int tag2 = cTagNone);

	struct sName { std::string name; eMod begin, end; };
	std::vector<sName> _names;

	bool _iswm;
};