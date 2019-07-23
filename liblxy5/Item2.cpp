#include "_global.h"


int sItem2::GetType()
{
	if (!m_pItemData)return -1;
	return m_pItemData->m_Type;
}

int sItem2::GetID()
{
	return m_pItemData->m_ID;
}

std::string sItem2::GetName()
{
	return m_pItemData->m_Name;
}

std::string sItem2::GetText()
{
	return m_pItemData->m_Text;
}

void sItem2::Set(int type, int id, bool needclear)
{
	if (needclear)m_Property.clear();
	m_pItemData = g_pMainState->m_ItemManage.GetItem(type, id);

}

void sItem2::SaveCode(sOstream& File)
{
	File << g_strSpace << m_Num << g_strSpace;
	if (m_Num > 0)
	{
		File << m_pItemData->m_Type << g_strSpace;
		File << m_pItemData->m_ID << g_strSpace;
		int lv = m_pItemData->GetLv();
		if ((m_pItemData->m_Type == 28 && m_pItemData->m_ID >= 12 && m_pItemData->m_ID <= 16) || 
			(m_pItemData->m_Type == 24 && m_pItemData->m_ID == 11))
		{
			// 旗子 月光
			File << (m_strProperty.empty() ? 0 : 1) << g_strSpace;
			if (m_strProperty.size())
			{
				File << m_strProperty << g_strSpace;
			}
		}
// 		else if (cct::isWeapon(m_pItemData) && lv >= 90 && lv <= 140)
// 		{
// 			File << lv << g_strSpace;
// 		}
		File << m_Property.size() << g_strSpace;
		for (int i = 0; i < m_Property.size(); i++)
		{
			File << m_Property[i] << g_strSpace;
		}
	}
}




static vector<int> s_stone_pros = { eProPerty气血, eProPerty速度, eProPerty命中, eProPerty火抗, eProPerty雷抗, eProPerty水抗, eProPerty土抗,
eProPerty灵力, eProPerty躲避, eProPerty伤害, eProPerty防御, eProPerty速度, eProPerty灵力, eProPerty防御, eProPerty躲避, eProPerty伤害, eProPerty气血 };
static vector<int> s_stoneValues = { 40, 8, 25, 2, 2, 2, 2, 6, 40, 8, 12, 6, 4, 8, 30, 10, 30 };
static int getEquipBase(int lv, eProPerty e)
{
	if (lv < 10)
	{
		// AutoItemProperty 最小
		lv = 10;
	}
	switch (e)
	{
	case eProPerty伤害:
		// 武器
		return 10 + lv * 3 + lv / 5 + lv * 6 / 5;
		// 临时
		return lv;
		// 宝宝
		return 10 + lv / 2;
		break;
	case eProPerty命中:
		// 武器
		return 10 + lv * 7 / 2 + lv / 6 + lv;
		// 临时
		return lv;
		break;
	case eProPerty命率:
		return 4 + lv / 8 + lv / 20;
		break;
	case eProPerty防御:
		// 装备
		return 5 + lv / 3 + lv / 14 + lv / 5;
		// 衣服
		return 10 + lv * 5 / 3 + lv / 5 + lv / 2;
		// 临时 
		return lv;
		// 宝宝
		return 8 + lv * 3 / 5 + lv / 6;
		break;
	case eProPerty魔法:
		// 头盔
		return 5 + lv + lv / 10 + lv / 3;
		// 临时
		return lv * 2;
		// 宝宝
		return 30 + lv * 3 / 2;
		break;
	case eProPerty灵力:
		// 项链
		return 5 + lv * 6 / 5 + lv / 9 + lv * 2 / 5;
		// 宝宝
		return 4 + lv / 4;
		break;
	case eProPerty速度:
		// 临时
		return (lv + (160 - lv) / 2) / 5;
		// 宝宝
		return 4 + lv / 5 + lv / 10;
		break;
	case eProPerty气血:
		// 腰带
		return 10 + lv * 2 + lv / 5 + lv * 2 / 3;
		// 临时
		return lv * 2;
		// 宝宝
		return 30 + lv * 3 / 2;
		break;
	case eProPerty力量:
	case eProPerty体质:
	case eProPerty敏捷:
	case eProPerty魔力:
	case eProPerty耐力:
		// 双加
		return 3 + lv / 5;
		// 鞋子
		return 5 + lv / 3 + lv / 17 + lv / 10;
		// 临时
		return lv / 5;
// 	case eProPerty水抗:
// 	case eProPerty火抗:
// 	case eProPerty土抗:
// 	case eProPerty雷抗:
// 		return slv * 2;
// 	case eProPerty躲避:
// 		return slv * 40;
// 		break;
	case eProPerty法伤:
	case eProPerty法防:
	case eProPerty法结:
	case eProPerty物结:
	case eProPerty回复:
		return (lv + (160 - lv) / 2) * 3 / 10;
	case eProPerty愤怒:
		return (lv + (160 - lv) / 2) / 5;
	}
	return 0;
}

static int getEquipTemp(int lv, eProPerty e)
{
	if (lv < 10)
	{
		lv = 10;
	}
	switch (e)
	{
	case eProPerty伤害:
		// 临时
	case eProPerty命中:
		// 临时
	case eProPerty防御:
		// 临时 
		return lv + (160 - lv) / 2;
	case eProPerty魔法:
		// 临时
		return (lv + (160 - lv) / 2) * 2;
	case eProPerty速度:
		// 临时
		return (lv + (160 - lv) / 2) / 5;
	case eProPerty气血:
		// 临时
		return (lv + (160 - lv) / 2) * 2;
	case eProPerty力量:
	case eProPerty体质:
	case eProPerty敏捷:
	case eProPerty魔力:
	case eProPerty耐力:
		// 临时
		return (lv + (160 - lv) / 2) / 5;
	default:
		return getEquipBase(lv, e);
	}
	return 0;
}

static int getEquipBB(int lv, eProPerty e)
{
	if (lv < 10)
	{
		lv = 10;
	}
	switch (e)
	{
	case eProPerty伤害:
		// 宝宝
		return 10 + lv / 2;
	case eProPerty防御:
		// 宝宝
		return 8 + lv * 3 / 5 + lv / 6;
	case eProPerty魔法:
		// 宝宝
		return 30 + lv * 3 / 2;
	case eProPerty灵力:
		// 宝宝
		return 4 + lv / 4;
	case eProPerty速度:
		// 宝宝
		return 4 + lv / 5 + lv / 10;
	case eProPerty气血:
		// 宝宝
		return 30 + lv * 3 / 2;
	default:
		return getEquipBase(lv, e);
	}
	return 0;
}


void sItem2::LoadCode(sIstream& File)
{
	File >> m_Num;
	if (m_Num > 0)
	{
		int type, id;
		File >> type;
		File >> id;
		m_pItemData = g_pMainState->m_ItemManage.GetItem(type, id);

		if ((type == 28 && id >= 12 && id <= 16) || (type == 24 && id == 11))
		{
			int havestring;
			File >> havestring;
			if (havestring)
			{
				File >> m_strProperty;
			}
			else
			{
				m_strProperty = "";
			}
		}
//		else if (isWeapon(m_pItemData) && )
		int propnum;
		File >> propnum;
		if (propnum > 0)
		{
			m_Property.resize(propnum);
			for (int k = 0; k < m_Property.size(); k++)
			{
				File >> m_Property[k];
			}
		}
	}
	if (m_Num < 1)
	{
		return;
	}
	
	bool isEB = cct::isEquipBB(m_pItemData);
	if (!cct::isEquip(m_pItemData) && !isEB)
	{
		return;
	}
	
	/*const */auto& ps = m_Property;
	if (ps.size() < 12)
	{
//		ERRBOX2(1);
		m_Num = 0;
		return;
	}

	if (ps[0] * ps[1] < 0)
	{
		// 强化
		ERRBOX2(2);
	}
	if (ps[10] * ps[11] < 0)
	{
		// 镶嵌
		ERRBOX2(3);
	}

	int lv = m_pItemData->GetLv();
	if (cct::isWJB(this))
	{
		if (ps[0] > cct::MaxStoneWJB)
		{
			// 宝石编号
			ERRBOX2(4);
		}
	}
	else
	{
		if (ps[0] > lv / 10)
		{
			// 修复旧存档 无级别宝石等级
			ps[0] = lv / 10;
			// 宝石编号
			// ERRBOX2(5);
		}
	}

	if (isEB)
	{
		for (int i = 2; i <= 9; i += 2)
		{
			if (ps[i] < 0)
			{
				continue;
			}
			if (ps[i + 1] > getEquipBB(lv, (eProPerty)ps[i]) + 10)
			{
				// 宝宝属性
				ERRBOX2(6);
			}
		}
		return;
	}

	bool isE = cct::isEquipButWeapon(m_pItemData);
	bool isC = GetType() == 17 || GetType() == 18;
	bool isS = GetType() == 21;

	int i;
	auto cb = [&](int v)
	{
		int p = ps[i + 1];
		if (ps[0] > 0)
		{
			if (ps[i] == s_stone_pros[ps[1]])
			{
				p -= ps[0] * s_stoneValues[ps[1]];
			}
		}
		if (p > v + 10)
		{
			ccc_msgbox("读档出错<item>");
			g_StateType = 0;
		}
	};

	for (i = 2; i <= 5; i += 2)
	{
		if (isC && ps[i] == eProPerty::eProPerty防御)
		{
			cb(10 + lv * 5 / 3 + lv / 5 + lv / 2);
		}
		else if (isS && ps[i] == eProPerty::eProPerty敏捷)
		{
			cb(5 + lv / 3 + lv / 17 + lv / 10);
		}
		else if (ps[i] >= 0)
		{
			cb(getEquipBase(lv, (eProPerty)ps[i]));
		}
	}

	for (i = 6; i <= 9; i += 2)
	{
		if (ps[i] < 0)
		{
			continue;
		}
		cb(getEquipBase(lv, (eProPerty)ps[i]));
	}

	for (i = 16; i < ps.size(); i += 2)
	{
		cb(getEquipTemp(lv, (eProPerty)ps[i]));
	}

	if (cct::isWJB(this))
	{
		if (m_Property[0] >= 0 && m_Property[1] >= 0)
		{
			g_pMainState->m_ItemManage.SetUpBaoShi(m_Property, m_Property[1], -m_Property[0], false);
			lv = m_pItemData->GetLv() / 10;
			g_pMainState->m_ItemManage.SetUpBaoShi(m_Property, m_Property[1], m_Property[0] = lv, false);
		}
	}
}



void sItem2::Save(ofstream& File)
{
	File << g_strSpace << m_Num << g_strSpace;
	if (m_Num > 0)
	{
		File << m_pItemData->m_Type << g_strSpace;
		File << m_pItemData->m_ID << g_strSpace;
		File << (m_strProperty.empty() ? 0 : 1) << g_strSpace;
		if (m_strProperty.size())
		{
			File << m_strProperty << g_strSpace;
		}
		File << m_Property.size() << g_strSpace;
		for (int i = 0; i < m_Property.size(); i++)
		{
			File << m_Property[i] << g_strSpace;
		}
	}
}

void sItem2::Load(ifstream& File)
{
	File >> m_Num;
	if (m_Num > 0)
	{
		int type, id;
		File >> type;
		File >> id;
		m_pItemData = g_pMainState->m_ItemManage.GetItem(type, id);

		int havestring;
		File >> havestring;
		if (havestring)
		{
			File >> m_strProperty;
		}
		else
		{
			m_strProperty = "";
		}
		int propnum;
		File >> propnum;
		if (propnum > 0)
		{
			m_Property.resize(propnum);
			for (int i = 0; i < m_Property.size(); i++)
			{
				File >> m_Property[i];
			}
		}
	}
}