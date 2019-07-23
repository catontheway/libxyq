#include "_global.h"

bool cct::isWeapon(const sItem* item)
{
	switch (item->m_Type)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 42:
	case 43:
	case 44:
		return true;
	}
	return false;
}

bool cct::isWeapon(const sItem2* item)
{
	return isWeapon(item->m_pItemData);
}

bool cct::isEquipButWeapon(const sItem* item)
{
	switch (item->m_Type)
	{
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		return true;
	}
	return false;
}

bool cct::isEquipButWeapon(const sItem2* item)
{
	return isEquipButWeapon(item->m_pItemData);
}

bool cct::isEquip(const sItem* item)
{
	return isWeapon(item) || isEquipButWeapon(item);
}

bool cct::isEquip(const sItem2* item)
{
	return isEquip(item->m_pItemData);
}

bool cct::isEquipBB(const sItem* item)
{
	switch (item->m_Type)
	{
	case 32:
	case 33:
	case 34:
		return true;
	}
	return false;
}

bool cct::isEquipBB(const sItem2* item)
{
	return isEquipBB(item->m_pItemData);
}


bool cct::isWJB(const sItem2* item)
{
	return item->m_Property.size() > 13 && item->m_Property[13] >= 0;
}


vector<int> cct::getSpecialSkills()
{
	static vector<int> skills;
	if (skills.empty())
	{
		for (int i = 0; i <= 13; ++i)
		{
			skills.push_back(i);
		}
		for (int i = 16; i <= 35; ++i)
		{
			skills.push_back(i);
		}
		skills.push_back(40);
		skills.push_back(47);
		skills.push_back(48);
	}
	return skills;
}

int cct::getModel(int model)
{
	// 角色2000
	if (model >= 2000) return model - 2000;
	// npc 1000
	if (model >= 1000) return model - 1000;
	// bb
	return model;
}

int cct::getMenpai(int mp)
{
	if (mp == eMP_随机)
	{
		int r = rand() % 100;
		if (r < 10)
		{
			mp = eMP_封系;
		}
		else if (r < 90)
		{
			mp = eMP_输出;
		}
		else
		{
			mp = eMP_辅助;
		}
	}
	if (mp == eMP_物理)
	{
		static vector<int> mps = { eMP_大唐官府, eMP_狮驼岭, eMP_凌波城 };
		return mps[rand() % mps.size()];
	}
	if (mp == eMP_法系)
	{
		static vector<int> mps = { eMP_东海龙宫, eMP_魔王寨, eMP_神木林 };
		return mps[rand() % mps.size()];
	}
	if (mp == eMP_输出)
	{
		static vector<int> mps = { eMP_大唐官府, eMP_东海龙宫, eMP_狮驼岭, eMP_魔王寨, eMP_凌波城, eMP_神木林 };
		return mps[rand() % mps.size()];
	}
	if (mp == eMP_辅助)
	{
		static vector<int> mps = { eMP_阴曹地府, eMP_化生寺, eMP_无底洞, eMP_普陀山 };
		mp = mps[rand() % mps.size()];
	}
	if (mp == eMP_封系)
	{
		static vector<int> mps = { eMP_女儿村, eMP_方寸山, eMP_盘丝岭, eMP_五庄观, eMP_天宫, eMP_无底洞 };
		return mps[rand() % mps.size()];
	}
	return mp;
	if (mp == eMP_随机)
	{
		static vector<int> mps = { eMP_女儿村, eMP_方寸山,
			eMP_大唐官府, eMP_东海龙宫, eMP_狮驼岭, eMP_魔王寨, eMP_凌波城, eMP_神木林,
			eMP_化生寺, eMP_阴曹地府, eMP_普陀山, eMP_无底洞,
			eMP_大唐官府, eMP_东海龙宫, eMP_狮驼岭, eMP_魔王寨, eMP_凌波城, eMP_神木林,
			eMP_大唐官府, eMP_东海龙宫, eMP_狮驼岭, eMP_魔王寨, eMP_凌波城, eMP_神木林,
			eMP_化生寺, eMP_阴曹地府, eMP_普陀山, eMP_无底洞,
			eMP_大唐官府, eMP_东海龙宫, eMP_狮驼岭, eMP_魔王寨, eMP_凌波城, eMP_神木林,
			eMP_大唐官府, eMP_东海龙宫, eMP_狮驼岭, eMP_魔王寨, eMP_凌波城, eMP_神木林,
			eMP_化生寺, eMP_阴曹地府, eMP_普陀山, eMP_无底洞,
			eMP_大唐官府, eMP_东海龙宫, eMP_狮驼岭, eMP_魔王寨, eMP_凌波城, eMP_神木林,
			eMP_五庄观, eMP_天宫, eMP_盘丝岭 };
		return mps[rand() % mps.size()];
		return (eMengPai)(rand() % c_MenPaiNumber);
	}
	return mp;
}

int cct::getCurrMaxXiulianLv(int pclv)
{
	if (pclv < 25)
	{
		return 0;
	}
	return min((pclv - 20) / 5, MaxXL);
}


void cct::setINT(int i, int v)
{
	g_GlobalValues[i] = v;
}

int cct::getINT(int i)
{
	return g_GlobalValues[i];
}

void cct::switchINT(int i)
{ 
	setINT(i, !getINT(i)); 
}

void cct::setDelta(ulong magic, int& delta)
{
	switch (magic)
	{
	case 0xF71DEAF7: // 31叽叽歪歪
	case 0x774B7CEF: // 132 三昧真火
		delta /= 2;
		break;
	case 0xC4FABE4C: // 107 巨岩破
	case 0x2DEE722A: // 108 苍茫树
		delta /= 3;
		break;
	default:
		if (delta <= 8)
		{
			delta = 1;
		}
		else if (delta <= 12)
		{
			delta = 2;
		}
		else
		{
			delta = 5;
		}
	}
}


void cct::setMagicPos(ulong magic, int& pos)
{
	switch (magic)
	{
	case 0xB073119D: // 14 催眠
	case 0x2406DA40: // 15 失心
	case 0x5BCBB64F: // 28 落雷

	case 0xF71DEAF7: // 31叽叽歪歪
		//	case 0x9E4E9755: // 35 护体

	case 0x2C2DA419: // 89 日月乾坤
	case 0x1CFE70FA: // 90 蓝灯
	case 0x7C7D67A6: // 91 红灯
	case 0x46038131: // 105 日光华
	case 0x2DEE722A: // 108 苍茫
	case 0x09CCB0F3: // 112 灵动
	case 0xD6BF55AD: // 115 自在心法
	case 0x2711A4A3: // 117 判官令
	case 0xB0FDC1B2: // 154 勾魂
	case 0x1C57DA8A: // 154 勾魂
	case 0x0E1DCDB9: // 187 明光宝 还是偏
	case 0xADF90980: // 201 炎护
	case 0x3200B6CC: // 2084 2085 雷击 
		pos = -10;
		break;
	case 0x0116C932: // 27 碎甲
	case 0x9A94D461: // 68 错乱
	case 0x6044E21A: // 五雷
		//	case 0xCEAF0E44: // 159 含情脉脉
		pos = 0;
		break;
	}
}


int cct::getPetModel(int lvTake1 /* = 0 */, int lvTake2 /* = 85 */, bool gadIf0 /* = false */)
{
	int m;
	int lv;
	do 
	{
		m = rand() % c_PetNumber;
		lv = g_pMainState->m_PetDataManager.GetPetData(m)->m_LvTake;
		if (lv == 115)
		{
			continue;
		}
		if (lv == 0 && !gadIf0 && !((m >= e小毛头 && m <= e小魔头) || m == e剑灵 || m == e无痕))
		{
			continue;
		}
		if (lv >= lvTake1 && lv <= lvTake2)
		{
			break;
		}

	} while (true);
	return m;
}


void cct::saveGlobal(sOstream& File)
{
	forr (g_GlobalValues, i)
	{
		File << g_GlobalValues[i] << g_strSpace;
	}
}

void cct::loadGlobal(sIstream& File)
{
	forr(g_GlobalValues, i)
	{
		File >> g_GlobalValues[i];
	}
}

void cct::autoSave()
{
	if (g_StateType == STATE_MAIN)
	{
		g_pMainState->m_InterfaceSystem.Save(0);
	}
}

static vector<string> s_fields =
{ "柳林坡", "北俱芦洲", "麒麟山", "丝绸之路", "大唐国境", "大唐境外", "长寿郊外", "小西天",
"女娲神迹", "月宫"/*, "蟠桃园"*/, "花果山", "墨家禁地", "比丘国", "波月洞",
"东海湾", "碗子山", "江南野外", "解阳山", "子母河底", "蓬莱仙岛", "须弥东界", "凌云渡"
};

const vector<string>& cct::getFields()
{
	return s_fields;
}

static vector<string> s_cities = { "建邺城", "傲来国", "长寿村", "西凉女国", "朱紫国", "宝象国", "墨家村", "仙缘洞天" };
const vector<string>& cct::getCitiesButCA()
{
	return s_cities;
}

