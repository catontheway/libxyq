#pragma once
#include "_inc.h"

// Buff
struct sBuff
{
	eSki ski;
	int time;
	int skilv;
//	int user;
//	int target;
};

// 技能
struct sSki
{
	// 数据(技能)
	bool setData(eSki e);
	// 数据
	const txtSkill::sSkill* getData()const{ return _data; }
	// 图标数据
	const txtIcon::sIcon* getIcon()const{ return _icon; }
	// 技能编号
	eSki getSki()const { return _e; }
	// 描述
	bool toDescs(sDescs& descs)const;
	// 有效
	bool isValid()const;
	// 被动
	bool isEd()const;
	// 门派技能
	bool isMenpai()const;
	// 回师门技能(水遁之类的)
	bool isF1()const;
	// 宝宝技能
	bool isPet()const;
	// 特技
	bool isSpecial()const;
	// 等级
	int getLv()const { return _lv; }
	void setLv(int lv) { _lv = lv; }
	// 秒几
	int getTargetsMax()const{ return _targetsMax; }

	static const int cGap = 10;
	static const int c180 = 180;
	static const int c160 = 160;

	// 学习经验
	static int getExp(int lv);
	// 学习金钱
	static int getMoney(int lv);
private:
	int _lv = cGap;
	int _targetsMax;
	eSki _e = eSki::eSkiNone;
	const txtIcon::sIcon* _icon = nullptr;
	const txtSkill::sSkill* _data = nullptr;
};

typedef std::vector<eSki> seSkis;
typedef std::vector<sSki> sSkis;