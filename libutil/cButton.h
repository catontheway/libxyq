#pragma once
#include "cSprite.h"
#include "cLabel.h"

enum class eAilgn { Left, Mid, Right };

class cLabelInner
{
protected:
	void setState(eMouseState state);
public:
	void setColor(uchar r, uchar g, uchar b);
	void setColor(const s565& color);

	void setString(const std::string& text);

	const std::string& getString();

protected:
	void setAilgn(eAilgn e, const Size& contentSize);

protected:
	cLabel* _label = nullptr;
	s565 _color;
	Vec2 _vLabel;
};

class cButton : public cSprite,  public cLabelInner
{
public:
	static cButton* create(ulong uid, const std::string& text = "", eFont e = eFont::nor){ CREATE(cButton, uid, text, e); }
	static cButton* create(ulong uid, eFont e) { CREATE(cButton, uid, "", e); }
	static cButton* create1(const std::string& text = ""){ CREATE(cButton, ccu::uBtn1, text, eFont::nor); }
	static cButton* create2(const std::string& text = ""){ CREATE(cButton, ccu::uBtn2, text, eFont::nor); }
	static cButton* create4(const std::string& text = ""){ CREATE(cButton, ccu::uBtn4, text, eFont::nor); }
protected:
	bool init(ulong uid, const std::string& text, eFont e);

	void setState(eMouseState state);

public:
	void setAilgn(eAilgn e);
};


class cButtonClose : public cSprite
{
public:
	CREATE_FUNC(cButtonClose);

protected:
	bool init();

	bool isSnatched(const Vec2& v);

	void setState(eMouseState state);
	
};