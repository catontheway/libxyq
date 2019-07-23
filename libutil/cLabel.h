#pragma once
#include "cNode.h"

class cLabel : public cNode
{
public:
	static cLabel* create(const std::string& text = "", eFont e = eFont::nor){ CREATE(cLabel, text, e); }

protected:
	bool init(const std::string& text, eFont e);

	bool isValid() const;
public:
	void setColor(const s565& color);
	void setColor(uchar r, uchar g, uchar b);

	void setBack(bool back){ _isBack = back; }

	virtual void setString(int i, bool moneyColor = false);
	virtual void setString(const u64& u, bool moneyColor = false);
	virtual void setString(const std::string& text);
	const std::string& getString()const;
	u64 getNumber() { return _number; }
protected:
	void draw(cCanvas* canvas, const uint32_t& flags);

	bool _isBack = false;
	cFont* _fnt;
public:
	u64 _number;
	s565 _color;
};




class cLabelNO : public cLabel
{
public:
	static cLabelNO* create(u64 number, u64 numberMax = 0xFFFFFFFFFFFFFFFF) { CREATE(cLabelNO, number, numberMax); }

protected:
	bool init(u64 number, u64 numberMax);

	bool isSnatched(const Vec2& v);

public:
	void setString(u64 number, bool moneyColor = false);

	void add();

	u64 getMax() { return _max; }
protected:
	void update(float delta);

	u64 _max;
	cLabel* _labelCursor = nullptr;
public:
	std::function<void(cLabelNO*)> onNO = nullptr;
};