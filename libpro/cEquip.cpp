#include "cEquip.h"

static int ccc_rand(int a, int b)
{
	return cc::random(a, b);
}
static int ccc_rand()
{
	return cc::random(0, 99);
}


static int proTemp(eProPerty pro, int lv, int e)
{
	int r = (160 - lv) / 2;
	int pMax = 0;
	switch (pro)
	{
	case eProPerty::速度:
	case eProPerty::愤怒:
	case eProPerty::力量:
	case eProPerty::体质:
	case eProPerty::敏捷:
	case eProPerty::魔力:
	case eProPerty::耐力:
		pMax = 20;
		break;
	case eProPerty::回复:
		pMax = 30;
		break;
	case eProPerty::法伤:
	case eProPerty::法防:
	case eProPerty::法结:
	case eProPerty::物结:
		pMax = 60;
		break;
	case eProPerty::伤害:
	case eProPerty::命中:
	case eProPerty::防御:
		pMax = 100;
		break;
	case eProPerty::气血:
	case eProPerty::魔法:
		pMax = 200;
		break;
	default:
		return 0;
	}
	return (lv + r * e / 100) * pMax / 100;
}

static int proAtk(int lv, int e)
{
	int v = 10 + lv * 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 6) + (lv)* e / 100;
}

static int proHit(int lv, int e)
{
	int v = 10 + lv * 7 / 2;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 5) + (lv * 6 / 5) * e / 100;
}

static int proHitRate(int lv, int e)
{
	int v = 4 + lv / 8;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 20) * e / 100;
}

static int proDef(int lv, int e)
{
	int v = 5 + lv / 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 14) + (lv / 5) * e / 100;
}

static int proMp(int lv, int e)
{
	int v = 5 + lv;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 10) + (lv / 3) * e / 100;
}

static int proMana(int lv, int e)
{
	int v = 5 + lv * 6 / 5;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 9) + (lv * 2 / 5) * e / 100;
}

static int proHp(int lv, int e)
{
	int v = 10 + lv * 2;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 5) + (lv * 2 / 3) * e / 100;
}

static int proDef2(int lv, int e)
{
	int v = 10 + lv * 5 / 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 5) + (lv / 2) * e / 100;
}

static int proAgi(int lv, int e)
{
	int v = 5 + lv / 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 17) + (lv / 10) * e / 100;
}

static int proPointEx(int lv, int e)
{
	int v = 4 + lv / 8;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 10) * e / 100;
}

static int proArmor(eIcon type, eProPerty pro, int lv, int e)
{
	switch (pro)
	{
	case eProPerty::防御:
		return cEquip::isClothes(type) ? proDef2(lv, e) : proDef(lv, e);
	case eProPerty::魔法:
		return proMp(lv, e);
	case eProPerty::灵力:
		return proMana(lv, e);
	case eProPerty::气血:
		return proHp(lv, e);
	case eProPerty::敏捷:
		return cEquip::isShoe(type) ? proAgi(lv, e) : proPointEx(lv, e);
	case eProPerty::力量:
	case eProPerty::体质:
	case eProPerty::魔力:
	case eProPerty::耐力:
		return proPointEx(lv, e);
	}
	return 0;
}

static int proWeapon(eProPerty pro, int lv, int e)
{
	switch (pro)
	{
	case eProPerty::命中:
		return proHit(lv, e);
	case eProPerty::伤害:
		return proAtk(lv, e);
	case eProPerty::力量:
	case eProPerty::体质:
	case eProPerty::敏捷:
	case eProPerty::魔力:
	case eProPerty::耐力:
		return proPointEx(lv, e);
	}
	return 0;
}

static int proBabyAtk(int lv, int e)
{
	int v = 10 + lv / 6;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 7) * e / 100;
}

static int proBabyMana(int lv, int e)
{
	int v = 4 + lv / 8;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 10) * e / 100;
}

static int proBabyDef(int lv, int e)
{
	int v = 8 + lv * 3 / 5;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 6) * e / 100;
}

static int proBabyHpMp(int lv, int e)
{
	int v = 30 + lv / 3;
	if (e == 0)
	{
		return v;
	}
	return v + (lv)* e / 100;
}

static int proBabySpeed(int lv, int e)
{
	int v = 4 + lv / 5;
	if (e == 0)
	{
		return v;
	}
	return v + (lv / 10) * e / 100;
}

static int proBaby(eProPerty pro, int lv, int e)
{
	switch (pro)
	{
	case eProPerty::命率:
		return proHitRate(lv, e);
	case eProPerty::速度:
		return proBabySpeed(lv, e);
	case eProPerty::防御:
		return proBabyDef(lv, e);
	case eProPerty::伤害:
		return proBabyAtk(lv, e);
	case eProPerty::灵力:
		return proBabyMana(lv, e);
	case eProPerty::气血:
	case eProPerty::魔法:
		return proBabyHpMp(lv, e);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
bool cEquip::isEquip(eIcon _type)
{
	return _type >= eIcon::equip0 && _type <= eIcon::equipEnd;
}

bool cEquip::isEquip(eMod master, eIcon type)
{
	if (!isEquip(type))
	{
		return false;
	}
	if (isWeapon(type))
	{
		const auto& wlist = txtWeapon::getInstance()->getWeaponLists().at(master);
		return ccc_find(wlist, type);
	}
	bool isBoy = txtMod::isBoy(master);
	if (type == eIcon::头盔t || type == eIcon::铠甲k)
	{
		return isBoy;
	}
	if (type == eIcon::发钗f || type == eIcon::布裙b)
	{
		return !isBoy;
	}
	return true;
}

bool cEquip::isWeapon(eIcon _type)
{
	return _type >= eIcon::eWeapon0 && _type <= eIcon::eWeaponEnd;
}

bool cEquip::isArmor(eIcon _type)
{
	return _type >= eIcon::equipArmor0 && _type <= eIcon::equipArmorEnd;
}

bool cEquip::isEquipBaby(eIcon _type)
{
	return _type >= eIcon::equipBaby0 && _type <= eIcon::equipBabyEnd;
}

bool cEquip::isHelmet(eIcon _type)
{
	return (_type == eIcon::头盔t || _type == eIcon::发钗f);
}

bool cEquip::isNeck(eIcon _type)
{
	return (_type == eIcon::项链x);
}

bool cEquip::isClothes(eIcon _type)
{
	return (_type == eIcon::铠甲k || _type == eIcon::布裙b);
}

bool cEquip::isBelt(eIcon _type)
{
	return (_type == eIcon::腰带y);
}

bool cEquip::isShoe(eIcon _type)
{
	return (_type == eIcon::鞋子x);
}

//////////////////////////////////////////////////////////////////////////
#pragma pack (push)
#pragma pack (1)
union sProHead
{
	uint pro;
	struct
	{
		// 石头 +1
		uint stone : 5;
		// 双加 + 1
		uint ap1 : 3;
		uint ap2 : 3;
		// 神佑/愤怒
		uint gad : 1;
		// 简易精致
		uint easy : 1;
		// 无级别
		uint wjb : 1;
		// 特技 -eSpecial0 +1
		uint special : 6;
		// 符石 +1
		uint fushi : 5;
		// 追加 +1
		uint zhuijia : 7;
	};

	void apply(eIcon type, bool specialEffect)
	{
		// 石头 打造才有
		pro = 0;

		if (cEquip::isWeapon(type) || cEquip::isClothes(type))
		{
			// 双加
			std::vector<int> add2s = { 0, 1, 2, 3, 4 };
			int r = ccc_rand(0, 4);
			this->ap1 = add2s[r];
			add2s.erase(add2s.begin() + r);

			r = ccc_rand(0, 3);
			this->ap2 = add2s[r];
		}

		if (cEquip::isWeapon(type) || cEquip::isBelt(type))
		{
			// 神佑/愤怒
			if (specialEffect && ccc_rand() < 5)
			{
				this->gad = 1;
			}
		}
		if (specialEffect && !cEquip::isEquipBaby(type))
		{
			if (ccc_rand() < 5)
			{
				// 简易
				this->easy = 1;
			}
			else if (ccc_rand() < 2)
			{
				this->wjb = 1;
			}
			if (ccc_rand() < 20)
			{
				eSkill ski;
				auto& skis = txtIcon::getInstance()->getTables().at(eIcon::技能j);
				do 
				{
					ski = (eSkill)ccc_rand((int)eSkill::eSpecial0, (int)eSkill::eSpecialEnd);
					if (!skis.at((int)ski).desc.empty())
					{
						break;
					}
				} while (true);
				// 特技
				this->special = (int)ski - (int)eSkill::eSpecial0 + 1;
			}
		}

		if (!cEquip::isWeapon(type))
		{
			// 武器没有符石(镶嵌)
		}

	}

};
union sProWeapon
{
	u64 pro;
	struct
	{
		//
		u64 temp1 : 1;
		// 命中
		u64 hit : 7;
		// 伤害
		u64 atk : 7;
		// 双加
		u64 ap1 : 7;
		u64 ap2 : 7;

		// 临时气血
		u64 t_hp : 7;
		// 魔法
		u64 t_mp : 7;
		// 伤害
		u64 t_atk : 7;
		// 防御
		u64 t_def : 7;
		// 回复
		u64 t_restore : 7;
	};

	void apply(bool add2, int eMin, int eMax)
	{
		pro = 0;
		// 0 属于国标
		auto func = [=](){return ccc_rand(eMin, eMax); };
		// 命中
		hit = func();
		// 伤害
		atk = func();
		if (add2)
		{
			// 双加
			ap1 = func();
			ap2 = func();
		}

		return;
		// 临时气血
		t_hp = func();
		// 魔法
		t_mp = func();
		// 伤害
		t_atk = func();
		// 防御
		t_def = func();
		// 回复
		t_restore = func();
	}

	void add(int temp)
	{
		// 临时气血
		t_hp += temp;
		// 魔法
		t_mp += temp;
		// 伤害
		t_atk += temp;
		// 防御
		t_def += temp;
		// 回复
		t_restore += temp;
		correct();
	}

	void correct()
	{
		if (hit > 100)
		{
			hit = 100;
		//	return true;
		}
		// 伤害
		if (atk > 100)
		{
			atk = 100;
		//	return true;
		}
		// 双加
		if (ap1 > 100)
		{
			ap1 = 100;
		//	return true;
		}
		if (ap2 > 100)
		{
			ap2 = 100;
		//	return true;
		}

		// 临时气血
		if (t_hp > 100)
		{
			t_hp = 100;
		//	return true;
		};
		// 魔法
		if (t_mp > 100)
		{
			t_mp = 100;
		//	return true;
		}
		// 伤害
		if (t_atk > 100)
		{
			t_atk = 100;
		//	return true;
		}
		// 防御
		if (t_def > 100)
		{
			t_def = 100;
		//	return true;
		}
		// 回复
		if (t_restore > 100)
		{
			t_restore = 100;
		//	return true;
		}
	//	return false;
	}
};
union sProArmor
{
	u64 pro;
	struct
	{
		// 衣服双加
		u64 temp : 36;
		// 主属性
		u64 pro1 : 7;
		// (衣服双加)
		u64 pro2 : 7;
		// 临时
		u64 temp1 : 7;
		u64 temp2 : 7;
	};

	void apply(eIcon type, bool add2, int eMin, int eMax)
	{
		pro = 0;
		auto func = [=](){return ccc_rand(eMin, eMax); };
		if (add2 && cEquip::isClothes(type))
		{
			// 衣服双加
			temp = func();
		}
		// 灵力/防御
		pro1 = func();
		if (cEquip::isNeck(type) || (!add2 && cEquip::isClothes(type)))
		{
			// 项链和衣服双加
			return;
		}
		// 魔法/无/双加/气血/敏捷
		pro2 = func();
		return;
		// 命中/法伤/法防/物结/法结
		temp1 = func();
		// 耐力/体质/魔力/愤怒/速度
		temp2 = func();
	}

	void add(eIcon type, int _temp)
	{
		if (cEquip::isClothes(type))
		{
			// 衣服双加
			temp += _temp;
			pro2 += _temp;
		}
		// 命中/法伤/法防/物结/法结
		temp1 += _temp;
		// 耐力/体质/魔力/愤怒/速度
		temp2 += _temp;
		correct();
	}

	void correct()
	{
		if (temp > 100)
		{
			temp = 100;
		//	return true;
		}
		if (pro1 > 100)
		{
			pro1 = 100;
		//	return true;
		}
		if (pro2 > 100)
		{
			pro2 = 100;
		//	return true;
		}
		if (temp1 > 100)
		{
			temp1 = 100;
		}
		if (temp2 > 100)
		{
			temp2 = 100;
		//	return true;
		}
	//	return false;
	}
};
union sProBaby
{
	u64 pro;
	struct
	{
		uint temp;
		// 第一个附加伤害or灵力
		uint isAtk : 1;
		uint isAdd1 : 1;
		uint isAdd2 : 1;
		uint isAdd3 : 1;
		// 主属性
		uint pro1 : 7;
		// 附加 伤害/灵力
		uint add1 : 7;
		// 附加 气血
		uint add2 : 7;
		// 附加 魔法
		uint add3 : 7;
	};

	void apply(eIcon type, bool ex3, int eMin, int eMax)
	{
		pro = 0;
		isAtk = ccc_rand() < 50;
		isAdd1 = ccc_rand() < (ex3 ? 100 : 70);
		isAdd2 = ccc_rand() < (ex3 ? 100 : 50);
		isAdd3 = ccc_rand() < (ex3 ? 100 : 50);

		auto func = [=](){return ccc_rand(eMin, eMax); };
		// 命中率/速度/防御
		pro1 = func();
		if (isAdd1)
		{
			// 附加 伤害/灵力
			add1 = func();
		}
		if (isAdd2)
		{
			// 附加 气血
			add2 = func();
		}
		if (isAdd3)
		{
			// 附加 魔法
			add3 = func();
		}
	}

	void correct()
	{
		if (add1 > 100)
		{
			add1 = 100;
		}
		if (add2 > 100)
		{
			add2 = 100;
		}
		if (add3 > 100)
		{
			add3 = 100;
		}
	}
};
#pragma pack (pop)


//////////////////////////////////////////////////////////////////////////
bool cEquip::fill(sItem& equip, bool effect_or_ex3, bool add2, int eMin, int eMax)
{
	if (!equip.isEquip())
	{
		return false;
	}
	if (equip.isEquipBaby())
	{
		sProBaby baby;
		baby.apply(equip.getType(), effect_or_ex3, eMin, eMax);
		baby.correct();
		equip._pro = baby.pro;
		return true;
	}

	sProHead head;
	head.apply(equip.getType(), effect_or_ex3);
	equip._head = head.pro;

	if (equip.isWeapon())
	{
		sProWeapon w;
		w.apply(add2, eMin, eMax);
		w.correct();
		equip._pro = w.pro;
	}
	else if (equip.isArmor())
	{
		sProArmor e;
		e.apply(equip.getType(), add2, eMin, eMax);
		e.correct();
		equip._pro = e.pro;
	}

	return true;
}


bool cEquip::apply(const sItem& equip, sPropertys& pros)
{
	sProHead head;
	head.pro = equip._head;
	int lv = getLv(equip);
	if (equip.isEquipBaby())
	{
		sProBaby baby;
		baby.pro = equip._pro;
		baby.correct();
		pros.resize(5);

		auto type = equip.getType();
		// 0 主属性
		if (type == eIcon::护腕h)
		{
			pros[0].pro = eProPerty::命率;
		}
		else if (type == eIcon::项圈x)
		{
			pros[0].pro = eProPerty::速度;
		}
		else if (type == eIcon::护甲h)
		{
			pros[0].pro = eProPerty::防御;
		}

		pros[0].value = proBaby(pros[0].pro, lv, baby.pro1);
		// 123 附加
		if (baby.isAdd1)
		{
			// 附加 伤害/灵力
			if (baby.isAtk)
			{
				pros[1].pro = eProPerty::伤害;
			}
			else
			{
				pros[1].pro = eProPerty::灵力;
			}
			pros[1].value = proBaby(pros[1].pro, lv, baby.add1);
		}
		if (baby.isAdd2)
		{
			// 附加 气血
			pros[2].pro = eProPerty::气血;
			pros[2].value = proBaby(pros[2].pro, lv, baby.add2);
		}
		if (baby.isAdd3)
		{
			// 附加 魔法
			pros[3].pro = eProPerty::魔法;
			pros[3].value = proBaby(pros[3].pro, lv, baby.add3);
		}
		// 89 宝石(可能)
		if (head.stone > 0)
		{
			pros[4] = txtStone::getInstance()->getTables().at((eStone)(head.stone - 1));
			pros[4].value *= (lv / 10 + head.easy);
		}
		return true;
	}

	std::vector<eProPerty> s_add2s = { eProPerty::体质, eProPerty::魔力, eProPerty::力量, eProPerty::耐力, eProPerty::敏捷 };
	if (equip.isWeapon())
	{
		sProWeapon w;
		w.pro = equip._pro;
		w.correct();
		pros.resize(10);
		// 01 主属性
		pros[0].pro = eProPerty::命中;
		pros[0].value = proWeapon(pros[0].pro, lv, w.hit);
		pros[1].pro = eProPerty::伤害;
		pros[1].value = proWeapon(pros[1].pro, lv, w.atk);
		// 23 双加
		if (w.ap1 > 0)
		{
			pros[2].pro = s_add2s[head.ap1];
			pros[2].value = proWeapon(pros[2].pro, lv, w.ap1);
		}
		if (w.ap2 > 0)
		{
			pros[3].pro = s_add2s[head.ap2];
			pros[3].value = proWeapon(pros[3].pro, lv, w.ap2);
		}
		// 4 宝石(可能)
		if (head.stone > 0)
		{
			pros[4] = txtStone::getInstance()->getTables().at((eStone)(head.stone - 1));
			pros[4].value *= (lv / 10 + head.easy);
			for (int k = 0; k < 2; ++k)
			{
				if (pros[4].pro == pros[k].pro)
				{
					pros[k].value += pros[4].value;
					pros[4].pro = eProPerty::None;
					pros[4].value = 0;
					break;
				}
			}
		}
		// 5-... 临时
		if (w.t_hp > 0)
		{
			pros[5].pro = eProPerty::气血;
			pros[5].value = proTemp(pros[5].pro, lv, w.t_hp);
		}
		if (w.t_mp > 0)
		{
			pros[6].pro = eProPerty::魔法;
			pros[6].value = proTemp(pros[6].pro, lv, w.t_mp);
		}
		if (w.t_atk > 0)
		{
			pros[7].pro = eProPerty::伤害;
			pros[7].value = proTemp(pros[7].pro, lv, w.t_atk);
		}
		if (w.t_def)
		{
			pros[8].pro = eProPerty::防御;
			pros[8].value = proTemp(pros[8].pro, lv, w.t_def);
		}
		if (w.t_restore > 0)
		{
			pros[9].pro = eProPerty::回复;
			pros[9].value = proTemp(pros[9].pro, lv, w.t_restore);
		}
		return true;
	}
	sProArmor e;
	e.pro = equip._pro;
	e.correct();
	pros.resize(7);

	if (equip.isNeck())
	{
		pros[0].pro = eProPerty::灵力;
	}
	else
	{
		pros[0].pro = eProPerty::防御;
	}
	pros[0].value = proArmor(equip.getType(), pros[0].pro, lv, e.pro1);

	if (equip.isHelmet())
	{
		pros[1].pro = eProPerty::魔法;
	}
	else if (equip.isBelt())
	{
		pros[1].pro = eProPerty::气血;
	}
	else if (equip.isShoe())
	{
		pros[1].pro = eProPerty::敏捷;
	}

	if (equip.isClothes())
	{
		// 23 双加 
		if (e.temp > 0)
		{
			pros[2].pro = s_add2s[head.ap1];
			pros[2].value = proWeapon(pros[2].pro, lv, e.temp);
		}
		if (e.pro2 > 0)
		{
			pros[3].pro = s_add2s[head.ap2];
			pros[3].value = proWeapon(pros[3].pro, lv, e.pro2);
		}
	}
	else
	{
		pros[1].value = proArmor(equip.getType(), pros[1].pro, lv, e.pro2);
	}

	// 4 宝石(可能)
	if (head.stone > 0)
	{
		pros[4] = txtStone::getInstance()->getTables().at((eStone)(head.stone - 1));
		pros[4].value *= (lv / 10 + head.easy);
		for (int k = 0; k < 2; ++k)
		{
			if (pros[4].pro == pros[k].pro)
			{
				pros[k].value += pros[4].value;
				pros[4].pro = eProPerty::None;
				pros[4].value = 0;
				break;
			}
		}
	}

	// 5-... 临时
	if (equip.isHelmet())
	{
		pros[5].pro = eProPerty::命中;
		pros[6].pro = eProPerty::耐力;
	}
	else if (equip.isNeck())
	{
		pros[5].pro = eProPerty::法伤;
		pros[6].pro = eProPerty::体质;
	}
	else if (equip.isClothes())
	{
		pros[5].pro = eProPerty::法防;
		pros[6].pro = eProPerty::魔力;

	}
	else if (equip.isBelt())
	{
		pros[5].pro = eProPerty::物结;
		pros[6].pro = eProPerty::愤怒;
	}
	else if (equip.isShoe())
	{
		pros[5].pro = eProPerty::法结;
		pros[6].pro = eProPerty::速度;
	}
	if (e.temp1 > 0)
	{
		pros[5].value = proTemp(pros[5].pro, lv, e.temp1);
	}
	else
	{
		pros[5].pro = eProPerty::None;
	}
	if (e.temp2 > 0)
	{
		pros[6].value = proTemp(pros[6].pro, lv, e.temp2);
	}
	else
	{
		pros[6].pro = eProPerty::None;
	}

	return true;
}

static std::string getTaozhuangName(const sItem& equip)
{
	bool isZhuijia;
	eSkill ski = cEquip::getTaoZhuang(equip, isZhuijia);
	if (ski == eSkill::eSkiNone)
	{
		return "";
	}
	std::string str = isZhuijia ? "追加法术: " : "附加状态: ";
	str += txtIcon::getInstance()->getTables().at(eIcon::技能j).at((int)ski).name;
	return str;
}

bool cEquip::apply(const sItem& equip, sDescs& descs)
{
	sProHead head;
	head.pro = equip._head;
	int lv = getLv(equip);
	sDesc d;
//	descs.clear();
	sPropertys pros;
	apply(equip, pros);
	const auto icons = txtIcon::getInstance()->getTables();
	if (equip.isEquipBaby())
	{
		// 0 
		// 123 附加
		d.text.clear();
		for (int k = 0; k <= 3; ++k)
		{
			if (pros[k].isVaild())
			{
				d.text += pros[k].toString("+") + " ";
			}
		}
		if (!d.text.empty())
		{
			d.text.pop_back();
			d.color = s565::YELLOW;
			descs.push(d);
		}
		// 4 宝石
		if (pros[4].isVaild())
		{
			d.text = toString("镶嵌等级: %d", lv / 10);
			d.color = s565::YELLOW;
			descs.push(d);

			d.text = "镶嵌效果: " + pros[4].toString("+");
			d.color = s565::WHITE;
			descs.push(d);
		}

		d.text = getTaozhuangName(equip);
		if (!d.text.empty())
		{
			d.color = s565(0x80, 0x80, 0xFF);
			descs.push(d);
		}
		return true;
	}


	// 01
	d.text.clear();
	for (int k = 0; k <= 1; ++k)
	{
		if (pros[k].isVaild())
		{
			d.text += pros[k].toString("+") + " ";
		}
	}
	if (!d.text.empty())
	{
		d.text.pop_back();
		d.color = s565::YELLOW;
		descs.push(d);
	}
	if (head.stone > 0)
	{
		d.text = toString("锻炼等级: %d ", (lv / 10) + (head.easy)) + icons.at(eIcon::宝石b).at(head.stone - 1).name;
		d.color = s565::YELLOW;
		descs.push(d);
	}
	// 23 双加
	d.text.clear();
	for (int k = 2; k <= 3; ++k)
	{
		if (pros[k].isVaild())
		{
			d.text += pros[k].toString("+") + " ";
		}
	}
	if (!d.text.empty())
	{
		// 4 宝石
		if (pros[4].isVaild())
		{
			d.text += pros[4].toString("+") + " ";
		}
		else
		{
			d.text.pop_back();
		}
		d.color = s565::GREEN;
		descs.push(d);
	}
	else if (pros[4].isVaild())
	{
		// 89 宝石
		d.text += pros[4].toString("+") + " ";
		d.color = s565::GREEN;
		descs.push(d);
	}

	eSkill ski = getSpecial(equip);
	if (ski != eSkill::eSkiNone)
	{
		// 特技
		d.text = "特技: " + icons.at(eIcon::技能j).at((int)ski).name;
		d.color = s565(0x80, 0x80, 0xFF);
		descs.push(d);
	}
	if (head.gad != 0 || head.easy != 0 || head.wjb != 0)
	{
		d.text = "特效:";
		if (head.gad)
		{
			d.text += equip.isBelt() ? " 愤怒" : " 神佑";
		}
		if (head.easy)
		{
			d.text += " 简易 精致";
		}
		else if (head.wjb)
		{
			d.text += " 无级别限制";
		}
		d.color = s565(0x80, 0x80, 0xFF);
		descs.push(d);
	}
	d.text = getTaozhuangName(equip);
	if (!d.text.empty())
	{
		d.color = s565(0x80, 0x80, 0xFF);
		descs.push(d);
	}

	// 5....
	// d.text.clear();
	for (int i = 5; i < pros.size(); ++i)
	{
		if (pros[i].isVaild())
		{
			d.text = "临时" + pros[i].toString();
			d.color = s565::GREEN;
			descs.push(d);
		}
	}
	return true;
	// 强化打造
	d.text = "浪西游 强化打造";
	d.color = s565::WHITE;
	descs.push(d);
	return true;
}


int cEquip::getTakeLv(const sItem& equip)
{
	sProHead head;
	head.pro = equip._head;
	if (head.wjb)
	{
		return 0;
	}
	int lv = getLv(equip);
	if (head.easy)
	{
		return lv - 5;
	}
	return lv;
}


int cEquip::getLv(const sItem& equip)
{
	auto e = equip.getType();
	int id = equip.getId();
	if (isWeapon(e))
	{
		id = txtIcon::getInstance()->getWeaponLv1ById(id);
	}
	if (isNeck(e) || isBelt(e))
	{
		id = txtIcon::getInstance()->getNeckBeltLv1ById(id);
	}
	id = id * 10;
	if (equip.isEquipBaby())
	{
		id += 5;
	}
	return id;
}


bool cEquip::getId(eIcon type, int lv, std::vector<int>& weapons)
{
	if (!isEquip(type))
	{
		return false;
	}
	weapons.clear();
	if (isEquipBaby(type))
	{
		lv = std::min(c160 / 10, (lv - 5) / 10);
		weapons.push_back(lv);
		return true;
	}

	lv /= 10;
	weapons.clear();
	if (isWeapon(type))
	{
		if (lv < 9)
		{
			weapons.push_back(lv);
			return true;
		}
		if (lv <= 11)
		{
			lv = 9 + (lv - 9);
			weapons.push_back(lv + 0);
			weapons.push_back(lv + 3);
			weapons.push_back(lv + 6);
			return true;
		}
		if (lv <= 14)
		{
			lv = 18 + (lv - 12);
			weapons.push_back(lv + 0);
			weapons.push_back(lv + 3);
			weapons.push_back(lv + 6);
			return true;
		}
		if (lv == 15)
		{
			weapons.push_back(27);
			return true;
		}
		weapons.push_back(28);
		return true;
	}

	if (type == eIcon::项链x || type == eIcon::腰带y)
	{
		if (lv >= 3 && lv <= 8)
		{
			lv = 3 + (lv - 3) * 2;
			weapons.push_back(lv);
			weapons.push_back(lv + 1);
			return true;
		}
		if (lv > 8)
		{
			weapons.push_back(lv + 6);
			return true;
		}
	}
	weapons.push_back(lv);
	return true;
}


int cEquip::getId(eIcon type, int lv)
{
	std::vector<int> weapons;
	if (!getId(type, lv, weapons))
	{
		return c_1;
	}
	return weapons[ccc_rand(0, (int)weapons.size() - 1)];
}


int cEquip::getIdx(eIcon type)
{
	if (!isEquip(type))
	{
		return c_1;
	}
	if (isEquipBaby(type))
	{
		return (int)type - (int)eIcon::equipBaby0;
	}
	if (isHelmet(type))
	{
		return 0;
	}
	if (isNeck(type))
	{
		return 1;
	}
	if (isWeapon(type))
	{
		return 2;
	}
	if (isClothes(type))
	{
		return 3;
	}
	if (isBelt(type))
	{
		return 4;
	}
	return 5;
}


eIcon cEquip::getWeaponType(eMod master, int weaponlist_0_1)
{
	if (!txtMod::isRole(master))
	{
		ccc_box((int)master);
	}
	const auto& wlist = txtWeapon::getInstance()->getWeaponLists().at(master);
	weaponlist_0_1 = weaponlist_0_1 % wlist.size();
	return wlist.at(ccc_rand(0, weaponlist_0_1));
}


bool cEquip::setFushi(sItem& equip, const sItem& fushi)
{
	if (!equip.isValid() || !equip.isEquip() || equip.isWeapon() || (fushi.getType() != eIcon::状态z && fushi.getType() != eIcon::追加z))
	{
		return false;
	}
	sProHead head;
	head.pro = equip._head;
	if (fushi.getType() == eIcon::状态z)
	{
		head.fushi = fushi.getId() + 1;
		head.zhuijia = 0;
	}
	else if (fushi.getType() == eIcon::追加z)
	{
		head.zhuijia = fushi.getId() + 1;
		head.fushi = 0;
	}
	equip._head = head.pro;
	return true;
}


eSkill cEquip::getTaoZhuang(const sItem& equip, bool& isZhuijia)
{
	sProHead head;
	head.pro = equip._head;
	if (head.fushi == 0 && head.zhuijia == 0)
	{
		return eSkill::eSkiNone;
	}

	if (head.fushi == 0)
	{
		isZhuijia = true;
		const auto& zhuijias = txtSkill::getInstance()->getZhuijias();
		if (head.zhuijia > zhuijias.size())
		{
			return eSkill::eSkiNone;
		}
		return zhuijias.at(head.zhuijia - 1);
	}

	isZhuijia = false;
	const auto& fushis = txtSkill::getInstance()->getFushis();
	if (head.fushi > fushis.size())
	{
		return eSkill::eSkiNone;
	}
	return fushis.at(head.fushi - 1);
}


eSkill cEquip::getSpecial(const sItem& equip)
{
	sProHead head;
	head.pro = equip._head;
	if (head.special == 0)
	{
		return eSkill::eSkiNone;
	}
	return (eSkill)(head.special + (int)eSki::eSpecial0 - 1);
}


bool cEquip::isGodAngry(const sItem& item)
{
	sProHead head;
	head.pro = item._head;
	return head.gad;
}



bool cEquip::isStone(eIcon type, int _stone)
{
	eStone stone = (eStone)_stone;
	if (cEquip::isHelmet(type))
	{
		return stone == eStone::红玛瑙 || stone == eStone::太阳石 || stone == eStone::月亮石;
	}
	if (cEquip::isNeck(type))
	{
		return stone == eStone::舍利子;
	}
	if (cEquip::isWeapon(type))
	{
		return stone == eStone::红玛瑙 || stone == eStone::太阳石 || stone == eStone::神秘石;
	}
	if (cEquip::isClothes(type))
	{
		return stone == eStone::月亮石 || stone == eStone::舍利子 || stone == eStone::翡翠石;
	}
	if (isBelt(type))
	{
		return stone == eStone::黑宝石 || stone == eStone::光芒石;
	}
	if (isShoe(type))
	{
		return stone == eStone::黑宝石 || stone == eStone::神秘石;
	}

	if (type == eIcon::护腕h)
	{
		return stone == eStone::精魄灵石_伤害 || stone == eStone::精魄灵石_灵力;
	}
	if (type == eIcon::项圈x)
	{
		return stone == eStone::精魄灵石_速度 || stone == eStone::精魄灵石_躲避;
	}
	if (type == eIcon::护甲h)
	{
		return stone == eStone::精魄灵石_防御 || stone == eStone::精魄灵石_气血;
	}
	return false;
}


bool cEquip::setStone(sItem& equip, int stoneid)
{
	if (!isStone(equip.getType(), stoneid))
	{
		return false;
	}
	sProHead head;
	head.pro = equip._head;
	head.stone = stoneid + 1;
	equip._head = head.pro;
	return true;
}


bool cEquip::setTemp(sItem& equip, int temp)
{
	if (equip.isWeapon())
	{
		sProWeapon w;
		w.pro = equip._pro;
		w.add(temp);
		equip._pro = w.pro;
		return true;
	}
	if (equip.isArmor())
	{
		sProArmor a;
		a.pro = equip._pro;
		a.add(equip.getType(), temp);
		equip._pro = a.pro;
		return true;
	}
	return false;
}

