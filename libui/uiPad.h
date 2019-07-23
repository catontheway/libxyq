#pragma once
#include "_inc.h"

class uiPad : public cSprite
{
public:
	static uiPad* create(ulong uid, bool close = true) { CREATE(uiPad, uid, close); }

	static cSprite* createSpriteClick(const Size& size, const std::string& text = "");

	virtual bool init(ulong uid, bool close);

	virtual void setContentSize(const Size& contentSize);

	virtual void setContentSize(float w, float h) { setContentSize(Size(w, h)); }

	virtual void setVisible(bool visible);

	virtual void doEvent(bool left, bool up, int keepTimes);

	virtual void reorder();

	virtual void setTitle(const std::string& title);

	// 输出化关闭按钮(点击回调)
	virtual void initClose(const cButton::sClick& cb);

	virtual void doClose();

	void resetButtonTitlePosition();

	void setRemoveOnClose(bool remove) { _isRemoveOnColse = remove; }

	void setCloseRup(bool hiden) { _isCloseRup = hiden; }

	void setAilgn(eAilgn e);

	bool switchVisible();
protected:
	cButtonClose* _btnClose = nullptr;
	cLabel* _labelTitle = nullptr;
	bool _isRemoveOnColse;
	bool _isCloseRup;
public:
	static const int cClosex = 8, cClosey = 6;
};