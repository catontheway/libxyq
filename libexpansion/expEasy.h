#pragma once
#include "expRank.h"

class expEasy : public Scene
{
public:
	static expEasy* createEasy(const std::string& title, const txtEasy::sTable& table) { CREATE_INIT(expEasy, initEasy, title, table); }
	static cSprite* createSpriteWithName(ulong uid, const std::string& text = "", eFont efont = eFont::smal, const s565& color = s565::YELLOW);
	static cSprite* createSpriteWithName(ulong uid, const std::string& text, const s565& color);
protected:
	expEasy();

	bool init(const std::string& title = "");


	cButton* initButton(const std::string& text, bool end = false);

	cButton* initButton(const std::string& text, const std::map<int, std::string>& texts, bool end = false);

	void initButton();

	void onButton(int tag, const std::map<int, std::string>& texts);

	bool initEasy(const std::string& title, const txtEasy::sTable& table);

	static const int cTagNone = -1;
	virtual cNode* initDrag(int tag, int tag2 = cTagNone) { return nullptr; }
	
	bool init(cNode* nodeDrag);

	void update(float delta);

	cNode* _nodeDrag = nullptr;
	cNode* _nodeButtonDrag = nullptr;
	cButton* _button = nullptr;
	cLabel* _labelTitle = nullptr;
	std::vector<cNode*> _button2s;

// 	bool _isScheduled = false;
// 	bool _isScheduledButton = false;

	int _btny = 0, _btny2 = 0, _vsWidth, _wButBtn = 0, _btnw = 0, _btnh = 0, _tag = -1;
	const int c10 = expRank::c10, cHead = 32;
};
