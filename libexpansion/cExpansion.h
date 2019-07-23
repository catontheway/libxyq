#pragma once
#include "expEasy.h"

class expStock: public expEasy
{
public:
	CREATE_FUNC(expStock);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);
};

class expTalk : public expEasy
{
public:
	CREATE_FUNC(expTalk);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);
};

class cExp : public expEasy
{
public:
	CREATE_FUNC(cExp);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);
};


class cExpansion : public Scene
{
public:
	CREATE_FUNC(cExpansion);

protected:
	bool init();

	cButton* onButton(const std::string& name, const std::function<Scene*()>& onScene);
	cButton* onButtonEasy(const std::string& name, const txtEasy::sTable& txts);
	void onRank();

	Director* _director = nullptr;
	std::vector<cButton*> _buttons;
	int _y;
	expRank _r;
	static const int cx, cy;
};