#pragma once
#include "uiPad.h"

// 技能学习
class uiLearn : public uiPad
{
public:
	typedef std::vector<txtIcon::sIcon> sIcons;
	static uiLearn* createBangpai() { CREATE(uiLearn, true); }

	static uiLearn* createMenpai() { CREATE(uiLearn, false); }
protected:

	bool init(bool isBangpai);

public:
	void doClose();

	void load(const sIcons& icons, const std::vector<int>& skilvs, u64 exp, u64 money);

	void load(sRole& role);

	bool learn(int skilv, int ilv);

	void updateLabel(int skilv);

	void updateLabel(int index, int skilv);

protected:
	int _skiMax, _isLearned = false;
	u64 _exp = 0, _money = 0, _expOri = 0, _moneyOri = 0;
	cLabel *_labelNeedExp, *_labelNeedMoney, *_labelExp, *_labelMoney;

	int _select = -1;
	std::vector<int> _skilvs, _skilvOris;
	sIcons _icons;
//	std::vector<std::string> _descs;
//	std::vector<cSprite*> _sprites;
	Node* _nodeLoad = nullptr;
	std::vector<cLabel*> _labelLvs;
	cText* _textDesc = nullptr;
	cSprite* _spriteSelect = nullptr;

public:
	// 学费
//	std::function<u64(int)> onExp, onMoney;
	std::function<void(const std::vector<int>&, u64, u64)> onLearn = nullptr;
};
