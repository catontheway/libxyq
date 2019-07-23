#include "sItem.h"
#include "cEquip.h"

bool sItem::setIcon(eIcon icon, int id)
{
	const auto& tables = txtIcon::getInstance()->getTables();
	const auto& it = tables.find(icon);
	if (it == tables.end())
	{
		return false;
	}
	const auto& it2 = it->second.find(id);
	if (it2 == it->second.end())
	{
		return false;
	}
	_type = icon;
	_id = id;
	_icon = &it2->second;
	_num = 1;
	_price = _icon->price;
	return true;
}


bool sItem::setData(bool effect_ex3, bool add2, int eMin, int eMax)
{
	if (!isValid() || !isEquip())
	{
		return false;
	}
	cEquip::fill(*this, effect_ex3, add2, eMin, eMax);
	return true;
}


bool sItem::setData(const std::string& mapname, int x, int y)
{
	if (!isValid())
	{
		return false;
	}
	if (getType() != eIcon::宝图b && getType() != eIcon::导标d)
	{
		return false;
	}
	const auto& maps = txtMap::getInstance()->getTables();
	if (maps.find(mapname) == maps.end())
	{
		return false;
	}
	_str = mapname;
	_head = x;
	_pro = y;
	return true;
}

bool sItem::add(int count /*= 1*/)
{
	if (!isValid())
	{
		return false;
	}
	++_num;
	return true;
}

bool sItem::sub(int count /*= 1*/)
{
	if (!isValid())
	{
		return false;
	}
	// 非消耗品
	if (isConsumables() && _num <= 1)
	{
		return false;
	}
	--_num;
	return true;
}

bool sItem::isValid()const
{
	return _num > 0 && _icon != nullptr;
}

void sItem::toDesc(sDescs& descs)const
{
	descs.clear();
	if (!isValid())
	{
		return;
	}
	sDesc d;
	descs.clear();

// 	d.text = _icon->name;
// 	d.color = s565::YELLOW;
// 	descs.push(d);
	descs.uhead = _icon->big;
	descs.name = _icon->name;

	d.text = _icon->desc;
	d.color = s565::WHITE;
	descs.push(d);

	if (isEquip())
	{
		d.text = "等级 " + cc::toString(cEquip::getLv(*this));
		d.color = s565::YELLOW;
		descs.push(d);

		cEquip::apply(*this, descs);
		return;
	}

	if (is宝图or导标() && !_str.empty())
	{
		d.text = _str + " " + cc::toString(_head) + " " + cc::toString(_pro);
		d.color = s565::YELLOW;
		descs.push(d);
	}
}

bool sItem::is宝图or导标(bool checkValid /* = true */) const 
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return (_type == eIcon::导标d || _type == eIcon::宝图b);
}

bool sItem::isConsumables(bool checkValid /* = true */) const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return !(_type == eIcon::旗子q || _type == eIcon::导标d || _type == eIcon::卡片k);
}

bool sItem::isOverly(bool checkValid /* = true */) const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return !(is宝图or导标(false) || cEquip::isEquip(_type) || _type == eIcon::坐饰z);
}

bool sItem::isPetOnly(bool checkValid /*= true*/) const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isEquipBaby(_type) ||
		_type == eIcon::染色r ||
		_type == eIcon::元宵y ||
		_type == eIcon::宝宝b ||
		_type == eIcon::兽决s ||
		_type == eIcon::初丹c ||
		_type == eIcon::高丹g;
}

bool sItem::isEquip(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isEquip(_type);
}

bool sItem::isWeapon(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isWeapon(_type);
}

bool sItem::isArmor(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isArmor(_type);
}

bool sItem::isEquipBaby(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isEquipBaby(_type);
}

bool sItem::isHelmet(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isHelmet(_type);
}

bool sItem::isNeck(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isNeck(_type);
}

bool sItem::isClothes(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isClothes(_type);
}

bool sItem::isBelt(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isBelt(_type);
}

bool sItem::isShoe(bool checkValid /* = true */)const
{
	if (checkValid && !isValid())
	{
		return false;
	}
	return cEquip::isShoe(_type);
}

bool sItem::switchWeapon(eMod master)
{
	if (!isValid())
	{
		return false;
	}
	if (!txtMod::isRole(master))
	{
		return false;
	}
	const auto& wlist = txtWeapon::getInstance()->getWeaponLists().at(master);
	if (ccc_find(wlist, _type))
	{
		return true;
	}
	setIcon(wlist.at(cc::random(0U, wlist.size() - 1)), _id);
	return true;
}

bool sItem::switchArmor(bool boy)
{
	if (!isValid())
	{
		return false;
	}
	if (isHelmet())
	{
		setIcon(boy ? eIcon::头盔t : eIcon::发钗f, _id);
		return true;
	}
	if (isClothes())
	{
		setIcon(boy ? eIcon::铠甲k : eIcon::布裙b, _id);
		return true;
	}
	return false;
}


void sItem::save()const
{
	sStream& sav = *cSave::getSave();
	if (!isValid())
	{
		sav << 0 << s_space;
		return;
	}
	sav << _num << s_space << (int)_type << s_space << _id << s_space;
//	sav->save(_price);
	if (is宝图or导标())
	{
		if (_str.empty())
		{
			sav << "无" << s_space;
		}
		else
		{
			sav << _str << s_space << _head << s_space << _pro << s_space;
		}
	}
	else if (isEquip())
	{
		sav << _head << s_space << _pro << s_space;
	}
}

void sItem::load()
{
	sStream& load = *cSave::getLoad();
	load >> _num;
	if (_num == 0)
	{
		return;
	}
	int type;
	load >> type >> _id; // >> _price;
	_type = (eIcon)type;
	setIcon(_type, _id);
	if (is宝图or导标())
	{
		load >> _str;
		if (_str == "无")
		{
			_str.clear();
		}
		else
		{
			load >> _head >> _pro;
		}
	}
	else if (isEquip())
	{
		load >> _head >> _pro;
	}
}


bool sItem::operator!=(const sItem& it) const
{
	return !(_type == it._type && _id == it._id);
}


bool sItem::operator==(const sItem& it) const
{
	return _type == it._type && _id == it._id;
}



#if 0
// 记得更新血条, 播放加血动画
static bool use25medicine(sAttribute& data, int id)
{
	// 前后hpmpap对比,播放动画
	switch (id)
	{
	case 0:	//同心肉脯
	//  success = AddFunc(&ItemManager::AddHp, 100, ObjId/*, 10000*/);

		return data.addhp(100);
	case 1://四叶花   
		return data.addhp(40);
	case 2://天青地白
		return data.addhp(80);
	case 3://人参
		return data.addhphp2(80, 20);
	case 4://血色茶花
		return data.addhp(150);
	case 5://熊胆
		return data.addhp(200);
	case 6://硫磺草
		return data.addhp(250);
	case 7://血珊瑚
		return data.addmp(100);
	case 8://地狱灵芝
		return data.addmp(100);
	case 9://龙之心屑
		return data.addhp(300);
	case 10://金创药
		return data.addhp(400);
	case 11://红雪散
	//	success = removeBuff(eBuffType毒, ObjId, true) && AddHp(400, ObjId);
		return data.addhp(400);
	case 12://八角莲叶
		return data.addhp2(60, 15);
	case 13://七叶莲
		return data.addhp(60);
	case 14://鹿茸
		return data.addhp(150);
	case 15://凤凰尾
		return data.addhp(250);
	case 16://火凤之睛
		return data.addhp(300);
	case 17://小还丹
		return data.addhphp2(400, 400);
	case 18://金香玉
		return data.addhp(800);
	case 19://佛手
		return data.addmp(20);
	case 20://旋复花
		return data.addmp(20);
	case 21://香叶
		return data.addmp(30);
	case 22://曼佗罗花
		return data.addmp(50);
	case 23://天龙水
		return data.addmp(150);
	case 24://餐风饮露
		return data.addmp(100);
	case 25://风水混元丹
		return data.addmp(300);
	case 26://紫丹罗
		return data.addmp(20);
	case 27://龙须草
		return data.addmp(30);
	case 28://白玉骨头
		return data.addmp(40);
	case 29://丁香水
		return data.addmp(75);
	case 30://月星子
		return data.addmp(75);
	case 31://麝香
		return data.addmp(100);
	case 32://仙狐涎
		return data.addmp(150);
	case 33://定神香
		return data.addmp(350);
	case 34://草果
		return data.addhp2(10);
	case 35://九香虫
		return data.addhp2(15);
	case 36://水黄莲
		return data.addhp2(20);
	case 37://山药
		return data.addhphp2(40, 10);
	case 38://灵脂
		return data.addmp(40);
	case 39://紫石英
		return data.addmp(100);
	case 40://月见草
		data.addhp(40);
		return data.addmp(30);
	case 41://白露为霜
		return data.addmp(100);
	case 42://孔雀红
		return data.addmp(100);
	case 43://蛇蝎美人
		return data.addmp(500);
	case 44://佛光舍利子
		return data.relife2(1, 150);
	case 45://九转回魂丹
		return data.relife(200);
	case 46://百色花
		return data.addmp(30);
	case 47://六道轮回
		return data.addhp(200);
	case 48://千年保心丹
		return data.addhphp2(400, 400);
	case 49://五龙丹
	//	removeBuff(eBuffType封印, ObjId, true);
		return data.addhp(10);
	case 50://福灵沙
	//  AddFunc(&ItemManager::AddHp, 150, ObjId);
		return data.addhp(150);
	case 51://五味露
	//  AddFunc(&ItemManager::AddMp, 40, ObjId);
		return data.addmp(40);
	case 52://神仙饮 (超神水)
	//  AddFunc(&ItemManager::AddCp, 15, ObjId);
		return data.addap(15);
	case 53://忠义肉脯
	//	AddFunc(&ItemManager::AddHpHurt, 150, ObjId);
	//	AddFunc(&ItemManager::AddHp, 150, ObjId);
		return data.addhphp2(150, 150);
		break;
	case 54://珍露酒
		return data.addap(15);
	case 55://百味酒
		return data.addap(20);
	case 56://蛇胆酒
		return data.addap(25);
	case 57://醉生梦死
		return data.addap(30);
	case 58://玉露羹
	//  AddFunc(&ItemManager::AddMp, 60, ObjId)
		return data.addmp(60);
	case 59://八珍玉液
	//	AddFunc(&ItemManager::AddCp, 10, ObjId/*, 10000*/);
		return data.addap(10);
	case 60://千金露
	//	AddFunc(&ItemManager::AddMp, 80, ObjId);
		return data.addap(80);
	}
	return false;
}

// 记得更新血条
static bool use26pengren(sAttribute& data, int id)
{
	switch (id)
	{
	case 0:	//包子 
		return data.addhp(150);
	case 1://烤鸭   
		return data.addhp(300);
	case 2://豆斋
	//	success = AddHp(3000, ObjId);
		break;
	case 3://长寿面
	//	success = AddHp(5000, ObjId);
		break;
	case 4://女儿红
		return data.addap(10);
	case 5://虎骨酒
		return data.addap(20);
	case 6://梅花酒
		return data.addap(30);
	case 7://佛跳墙
		return data.addmp(300);
	case 8://翡翠豆腐
		return data.addmp(500);
	}
	return false;
}

static bool use27fabao(int id)
{
	switch (id)
	{
	case 11: // 月光
		return true;
	case 12://去CA
	case 13://去AL
	case 14://去CS
	case 15://去ZZ
	case 34://去境外
		return true;
	case 16: //隐盅
		return true;
	}
	return false;
}

// use26卡片


static bool use30daoju(int id)
{
	switch (id)
	{
	case 0://飞行符
		return true;
	case 1://摄妖香
		return true;
	case 2://洞冥草
		return true;
	case 3:// 金柳露
	case 4:
	case 5:
		return true;
	case 36://碧藕
		return true;
	case 42: // 阵书
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
	case 50:
	case 51:
		if (0 == (ccc_cfg(1) & (1 << (id - 42))))
		{
			ccc_cfg(1) |= (1 << (id - 42));
			return true;
		}
		break;
	case 55: // 天眼BUG
		return true;
	case 59: // 神兵鉴赏
		return true;
	case 60: // 修炼果
	case 61:
	case 62:
	case 63:
		return true;
	case 64: // 九转金丹
	case 65:
	case 66:
	case 67:
		return true;
	case 68: // 元宵
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
		return true;
	}
	return false;
}

static bool use31diejia(int id)
{
	switch (id)
	{
	case 12: // 飞行棋
	case 13:
	case 14:
	case 15:
	case 16:
		return true;
	case 6://宝图
		return true;
	case 21: // 四门挖宝
		return true;
	}
	return false;
}

// use家具

#endif