#pragma once
#include "_inc.h"

class uiChannelInner : public cLayer::cNodeInner
{
public:
	static uiChannelInner* create(eFont eFnt) { CREATE(uiChannelInner, eFnt); }

protected:
	bool init(eFont eFnt);

	void setRectWorld();

public:
	void add(eCanvas eCanv, eChannel e, const std::string& name, const std::string& text);


protected:
	eFont _eFont;
	std::vector<cText*> _texts;
};

// ÆµµÀ
class uiChannel : public cLayer
{
public:
	static uiChannel* create(eFont eFnt, eCanvas eCanv) { CREATE(uiChannel, eFnt, eCanv); }
	static cSprite* createSprite();
protected:
	bool init(eFont eFnt, eCanvas eCanv);

public:
	void add(eChannel e, const std::string& name, const std::string& text);

protected:
	eFont _eFont;
	eCanvas _eCanv;
};