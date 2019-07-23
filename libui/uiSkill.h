#pragma once
#include "uiPad.h"

// 人物技能
class uiSkill : public uiPad
{
public:
	CREATE_FUNC(uiSkill);
	bool init();
	// 载入(人物数据)
	void load(sRole& role);
	void doHide();
	void showMain(int k);
	cSprite* createSprite(ulong uid, const std::string& desc, const std::function<void()>& onClickEx = nullptr);
	Node* createMain(int tag);
	Node* createSpecial();
	void loadXL(int select);
	void learnXL(bool isbb, int select4);

	void showXLbutton(bool show);
	void doClose();

	sRole _role;
	sXl _xlOri, _xlbbOri;
	u64 _moneyOri;

	// 存放主技能相关的节点
	Node* _nodeMain = nullptr;
	cButton* _buttonMain = nullptr;
	// 存放辅助相关的节点
	Node* _nodeFuzhu = nullptr;
	cButton* _buttonFuzu = nullptr;
	// 存放修炼相关的节点
	Node* _nodeXl = nullptr;
	cButton* _buttonXl = nullptr;
	// 奇经八脉
	cButton* _buttonQj8m = nullptr;
	// 描述
	cText* _textDesc = nullptr;

// 	// 修炼选择
	cSprite* _spriteXLselece = nullptr;
	cSprite* _spriteSelect = nullptr;

	bool _isLearned = false;
	int _xiulianSelect = -1;
	cButton* _buttonLearnXl = nullptr;

public:
	// 钱差
	std::function<void(const sXl&, const sXl&, u64)> onXL = nullptr;
	// 
	std::function<void()> onQj8m = nullptr;
};