#pragma once
#include "_txtinc.h"

enum class eProPerty
{
	None = -1,
	伤害,
	命中,
	命率,
	防御,
	魔法,
	灵力,
	速度,
	气血,
	力量,
	敏捷,
	体质,
	魔力,
	耐力,
	水抗,
	火抗,
	土抗,
	雷抗,
	躲避,
	法伤,
	法防,
	法结,
	物结,
	回复,
	愤怒
};


enum class eStone
{
	光芒石,
	黑宝石,
	红玛瑙,
	舍利子,
	神秘石,
	太阳石,
	月亮石,
	翡翠石,
	精魄灵石_速度,
	精魄灵石_灵力,
	精魄灵石_防御,
	精魄灵石_躲避,
	精魄灵石_伤害,
	精魄灵石_气血,
	红宝石,
	黄宝石,
	蓝宝石,
	绿宝石,
};


ccc_txt_class_begin(txtStone);

struct sStone
{
	eProPerty pro = eProPerty::None;
	int value = 0;
	bool isVaild()const{ return pro != eProPerty::None && value > 0; }
	std::string toString(const std::string& str = " ")const;
};

static std::string toString(eProPerty pro);

friend class txtIcon;
ccc_txt_class_end(eStone, sStone);