#pragma once
#include "_inc.h"

// 默认战斗点击无效
class cDialog : public cNode
{
public:
	struct sHeadName
	{
		ulong head = cSp::c0;
		std::string name;
	};
	typedef std::function<void(int)> CB;
	CREATE_FUNC(cDialog);
protected:
	virtual bool init();

public:
	void setClose(bool closeOnClickPad);
	void setCancel(bool cancel);

	void load(ulong head, const std::string& name, const std::string& text, const std::vector<std::string>& selects = {}, const CB& cb = nullptr);
	void load(const sHeadName& headName, const std::string& text, const std::vector<std::string>& selects = {}, const CB& cb = nullptr);

protected:
	Vec2 _vDialog, _vText;
	Size _sizeDialog;
	bool _isCloseOnClickPad = true;
	bool _isCancelLast = false;

	cSprite* _spriteDialog = nullptr;
	cSprite* _spriteHead = nullptr;
	cSprite* _spriteName = nullptr;
	cLabel* _labelName;
	cText* _text = nullptr;

	std::vector<cNode*> _buttons;
};