#include "_global.h"


bool ItemManager::SetItemDescribe(int x, int y, cDescribe& pDescribe, sItem2* pItem)
{
	if (!pItem|| !pItem->GetNum() || !pItem->m_pItemData)
	{
		if (pDescribe.m_NeedShow)
			pDescribe.OnOff(false);
		return false;
	}

	m_Color[2] = RGB(250, 250, 0);
	m_Color[0] = RGB(250, 250, 0);
	m_Color[1] = RGB(220, 220, 220);
	for (int i = 3; i < m_text.size(); i++)
	{
		m_Color[i] = RGB(0, 255, 0);
	}

	ostringstream oss;
	m_text[0] = pItem->GetName();
	m_text[1] = pItem->GetText();
	m_numtext = 2;
	if (cct::isEquip(pItem) || cct::isEquipBB(pItem))
	{
		// \n
		m_text[2] = "等级 " + toString("%d", pItem->m_pItemData->GetLv());
		m_numtext = 3;
		makePropStringEquip(pItem);
		pDescribe.Set(x + 25, y + 25, pItem->m_pItemData->m_BigHead, m_numtext, &m_text[0], &m_Color[0]);
		pDescribe.OnOff(true);
		return true;
	}
	int itemtype = pItem->GetType();
	switch (itemtype)
	{
	case 22:
	case 23:
	case 24:
	case 25:
	case 27:
		break;
	case 28:
		if (1)
		{
			switch (pItem->GetID())
			{
			case 0://
				ERRBOX;
				break;
			case 6://藏宝图
				if (1)
				{
					if (pItem->m_Property.empty() || pItem->m_Property[0] < 0)
					{
						m_text[2] = "这张宝图已经报废";
						break;
					}
					m_numtext += 1;
					oss.str("");
				//	oss << "上面记写着地点:\n";
					oss << g_pMainState->m_TaskBaoTu.m_MapNameList[pItem->m_Property[0]] << " ";


					oss << pItem->m_Property[1] << " ";
					oss << pItem->m_Property[2];
					m_text[2] = oss.str();
				}
				break;
			case 7:
				if (pItem->m_Property.empty())
				{
					break;
				}
				m_numtext += 1;
				oss.str("");
				oss << "等级:";
				oss << pItem->m_Property[0];
				m_text[2] = oss.str();
				break;
			case 8:
				if (pItem->m_Property.empty())
				{
					break;
				}
				m_numtext += 2 - 1;
// 				oss.str("");
// 				oss << "类型:";
// 				oss << g_pMainState->m_ItemManage.m_ItemTypeName[pItem->m_Property[0]];
// 				m_text[2] = oss.str();
				oss.str("");
				oss << "等级:";
				oss << pItem->m_Property[0];
				m_text[/*3*/2] = oss.str();
				break;
			case 9://这个目前没有被使用
				if (!pItem->m_Property.empty())
				{
					m_numtext += 2;
					oss.str("");
					oss << "现在有";
					oss << pItem->m_Property[0];
					oss << "钱";
					m_text[2] = oss.str();
					oss.str("");
					oss.str("");
					oss << "目标";
					oss << pItem->m_Property[1];
					oss << "钱";
					m_text[3] = oss.str();
				}
			default:
				break;
			}

		}
		break;
	case 31:
		if (1)
		{
			oss.str("");
			oss << "可以给";
			oss << g_pMainState->m_ZuoQi.m_ZuoQi[pItem->GetID() / 3].Name;
			oss << "装备";
			m_text[1] = oss.str();
		}
		break;
// 	case 32:
// 	case 33:
// 	case 34:
// 		if (1)
// 		{
// 			oss.str("");
// 			oss << "等级 ";
// 			oss << pItem->m_pItemData->m_ID * 10 + 5;
// 			m_text[m_numtext] = oss.str();
// 			oss.str("");
// 			m_numtext += 1;
// 			if (pItem->m_Property.size() == 0)
// 			{
// 				oss.str("");
// 				oss << "未鉴定";
// 				m_text[m_numtext] = oss.str();
// 				m_numtext += 1;
// 			}
// 			else
// 			{
// 				MakePropString2(pItem);
// 			}
// 
// 		}
// 		break;
// 	case 0:
// 	case 1:
// 	case 2:
// 	case 3:
// 	case 4:
// 	case 5:
// 	case 6:
// 	case 7:
// 	case 8:
// 	case 9:
// 	case 10:
// 	case 11:
// 	case 12:
// 	case 13:
// 	case 14:
// 		if (1)
// 		{
// 			oss.str("");
// 			oss << "等级 ";
// 			oss << pItem->m_pItemData->GetLv();
// 			m_text[m_numtext] = oss.str();
// 			oss.str("");
// 			m_numtext += 1;
// 			if (pItem->m_Property.size() == 0)
// 			{
// 				oss.str("");
// 				oss << "未鉴定";
// 				m_text[m_numtext] = oss.str();
// 				m_numtext += 1;
// 			}
// 			else
// 			{
// 				MakePropString2(pItem);
// 			}
// 		}
// 		break;
// 	case 15:
// 	case 16:
// 	case 17:
// 	case 18:
// 	case 19:
// 	case 20:
// 	case 21:
// 		if (1)
// 		{
// 			oss.str("");
// 			oss << "等级 ";
// 			oss << pItem->m_pItemData->GetLv();
// 			m_text[m_numtext] = oss.str();
// 			oss.str("");
// 			m_numtext += 1;
// 			if (pItem->m_Property.size() == 0)
// 			{
// 				oss.str("");
// 				oss << "未鉴定";
// 				m_text[m_numtext] = oss.str();
// 				m_numtext += 1;
// 			}
// 			else
// 			{
// 				MakePropString2(pItem);
// 			}
// 		}
// 		break;
// 	default:
// 		break;
	}
	pDescribe.Set(x + 25, y + 25, pItem->m_pItemData->m_BigHead, m_numtext, &m_text[0], &m_Color[0]);
	pDescribe.OnOff(true);
	return true;
}






std::string ItemManager::MakePropString(vector<int>& prop, int pos)
{
	string str;
	switch (prop[pos])
	{
	case eProPerty伤害:str = "伤害 "; break;
	case eProPerty命中:str = "命中 "; break;
	case eProPerty防御:str = "防御 "; break;
	case eProPerty魔法:str = "魔法 "; break;
	case eProPerty灵力:str = "灵力 "; break;
	case eProPerty速度:str = "速度 "; break;
	case eProPerty气血:str = "气血 "; break;
	case eProPerty力量:str = "力量 "; break;
	case eProPerty敏捷:str = "敏捷 "; break;
	case eProPerty体质:str = "体质 "; break;
	case eProPerty魔力:str = "魔力 "; break;
	case eProPerty耐力:str = "耐力 "; break;
	case eProPerty火抗:str = "火抗 "; break;
	case eProPerty雷抗:str = "雷抗 "; break;
	case eProPerty土抗:str = "土抗 "; break;
	case eProPerty水抗:str = "水抗 "; break;
	case eProPerty躲避: str = "躲避"; break;
	case eProPerty法伤:str = "法伤 "; break;
	case eProPerty法防:str = "法防 "; break;
	case eProPerty法结:str = "法术结果 "; break;
	case eProPerty物结:str = "物理结果 "; break;
	case eProPerty回复:str = "气血回复 "; break;
	case eProPerty愤怒:str = "愤怒 "; break;
	case eProPerty命率:str = "命中率 "; break;
	default:
		return str;
	}
	ostringstream oss;
	if (prop[pos + 1] > 0)
	{
		oss << "+";
	}
	oss << prop[pos + 1];
	str += oss.str();
	return str;
}


std::string ItemManager::getProPertyString(int prop)
{
	switch (prop)
	{
	case eProPerty伤害: return "伤害";
	case eProPerty命中: return "命中";
	case eProPerty防御: return "防御";
	case eProPerty魔法: return "魔法";
	case eProPerty灵力: return "灵力";
	case eProPerty速度: return "速度";
	case eProPerty气血: return "气血";
	case eProPerty力量: return "力量";
	case eProPerty敏捷: return "敏捷";
	case eProPerty体质: return "体质";
	case eProPerty魔力: return "魔力";
	case eProPerty耐力: return "耐力";
	case eProPerty火抗: return "火抗";
	case eProPerty雷抗: return "雷抗";
	case eProPerty土抗: return "土抗";
	case eProPerty水抗: return "水抗";
	case eProPerty躲避: return "躲避";
	case eProPerty法伤: return "法伤";
	case eProPerty法防: return "法防";
	case eProPerty法结: return "法术结果";
	case eProPerty物结: return "物理结果";
	case eProPerty回复: return "气血回复";
	case eProPerty愤怒: return "愤怒";
	case eProPerty命率: return "命中率";
	}
	return "error";
}




void ItemManager::MakePropString2(sItem2* item)
{
	int pos = 5;
	vector<int>& prop = item->m_Property;
	ostringstream oss;

	//基本属性
	m_Color[m_numtext] = RGB(255, 255, 0);
	int num;
	switch (item->GetType())
	{
// 		17  铠甲
// 			18  女衣
// 			19  项链
	case 17://有1个基本属性
	case 18:
	case 19:
		if (1)
		{
			m_text[m_numtext] = MakePropString(prop, pos + 1);

			m_numtext += 1;
			num = prop[pos] - 1;
			pos += 3;
		}
		break;
	default: //有2个基本属性
		m_text[m_numtext] = MakePropString(prop, pos + 1);
		m_text[m_numtext] += "\n";
		m_text[m_numtext] += MakePropString(prop, pos + 3);
		m_numtext += 1;
		num = prop[pos] - 2;
		pos += 5;
		break;
	}

	//强化等级
	oss.str("");
	oss << "锻炼等级: ";
	oss << item->m_Property[0];
	m_Color[m_numtext] = RGB(255, 255, 0);
	m_text[m_numtext] = oss.str();
	m_numtext += 1;

	//特技
	if (item->m_Property[1] > -1)
	{
		m_Color[m_numtext] = RGB(126, 255, 126);
		oss.str("");
		oss << "特技:";
		oss << g_pMainState->m_SkillManager.GetSpecialSkill(item->m_Property[1])->m_Name;
		m_text[m_numtext] = oss.str();
		m_numtext += 1;
	}
	if (item->m_Property[2] > -1)
	{
		m_Color[m_numtext] = RGB(126, 126, 255);
		oss.str("");
		oss << "特效:";
		oss << g_pMainState->m_SkillManager.GetSpecialSkill2(item->m_Property[2])->m_Text;
		m_text[m_numtext] = oss.str();
		m_numtext += 1;
	}
	if (item->m_Property[3] > -1)
	{
		m_Color[m_numtext] = RGB(126, 126, 255);
		oss.str("");
		oss << "特效:";
		oss << g_pMainState->m_SkillManager.GetSpecialSkill2(item->m_Property[3])->m_Text;
		m_text[m_numtext] = oss.str();
		m_numtext += 1;
	}
	if (item->m_Property[4] > -1)
	{
		m_Color[m_numtext] = RGB(126, 126, 255);
		oss.str("");
		oss << "特效:";
		oss << g_pMainState->m_SkillManager.GetSpecialSkill2(item->m_Property[4])->m_Text;
		m_text[m_numtext] = oss.str();
		m_numtext += 1;
	}


	//额外属性
	m_Color[m_numtext] = RGB(0, 255, 0);
	for (int i = 0; i < num; i++)
	{
		if (i % 2 == 0)
		{
			m_text[m_numtext] = MakePropString(prop, pos + i * 2);
		}
		else
		{
			m_text[m_numtext] += "\n";
			m_text[m_numtext] += MakePropString(prop, pos + i * 2);
			m_numtext += 1;
		}
	}
	if (num % 2 == 1)
	{
		m_numtext += 1;
	}

}



void ItemManager::makePropStringEquip(sItem2* item)
{
	const auto& props = item->m_Property;
	string str;
	if (cct::isEquipBB(item))
	{
		str.clear();
		// 基本 2-9
		for (int i = 2; i < 10; i += 2)
		{
			if (props.size() > i && props[i] >= 0)
			{
				str += getProPertyString(props[i]) + toString("+%d ", props[i + 1]);
			}
		}
		if (!str.empty())
		{
			str.pop_back();
		//	str += "\n";
			m_Color[m_numtext] = RGB(255, 255, 0);
			m_text[m_numtext] = str;
			++m_numtext;
		}
		// 0 锻炼
		// 1 石头
		if (props.size() > 0 && props[0] >= 0)
		{
			m_Color[m_numtext] = RGB(255, 255, 0);
			// \n
			m_text[m_numtext] = toString("镶嵌等级: %d", props[0]);
			++m_numtext;
		}
		// 其他
		str.clear();
		if (props.size() > 11 && props[10] >= 0)
		{
			// \n
			m_Color[m_numtext] = RGB(255, 255, 255);
			m_text[m_numtext] = "镶嵌效果: " + getProPertyString(props[10]) + toString("+%d", props[11]);
			++m_numtext;
		}
		// 符石
		str.clear();
		if (props.size() > 15 && props[15] >= 0)
		{
			// \n
			m_Color[m_numtext] = RGB(126, 126, 255);
			m_text[m_numtext] = "追加法术: " + g_pMainState->m_SkillManager.GetSkill(props[15])->m_Name;
			++m_numtext;
		}

		return;
	}
	str.clear();
	// 基本 2-5
	for (int i = 2; i <= 5; i += 2)
	{
		if (props.size() > i && props[i] >= 0)
		{
			str += getProPertyString(props[i]) + toString("+%d ", props[i + 1]);
		}
	}
	if (!str.empty())
	{
		str.pop_back();
		// \n
//		str += "\n";
		m_Color[m_numtext] = RGB(255, 255, 0);
		m_text[m_numtext] = str;
		++m_numtext;
	}
	// 0 锻炼
	// 1 石头
	if (props[0] >= 0 && props[1] >= 0)
	{
		m_Color[m_numtext] = RGB(255, 255, 0);
		// \n
		m_text[m_numtext] = toString("锻炼等级: %d %s", props[0], m_ItemList[29][props[1]].m_Name.c_str());
		++m_numtext;
	}

	// 双加 6-9
	str.clear();
	for (int i = 6; i <= 9; i += 2)
	{
		if (props.size() > i && props[i] >= 0)
		{
			str += getProPertyString(props[i]) + toString("+%d ", props[i + 1]);
		}
	}
	if (!str.empty())
	{
		// 宝石属性 10-11
		if (props.size() > 10 && props[10] >= 0)
		{
			str += getProPertyString(props[10]) + toString("+%d", props[11]);
		}
		else
		{
			str.pop_back();
		}
		// \n
//		str += "\n";
		m_Color[m_numtext] = RGB(0, 255, 0);
		m_text[m_numtext] = str;
		++m_numtext;
	}
	else if (props.size() > 10 && props[10] >= 0)
	{
		// 宝石属性 10-11
		m_Color[m_numtext] = RGB(0, 255, 0);
		// \n
		m_text[m_numtext] = getProPertyString(props[10]) + toString("+%d", props[11]);
		++m_numtext;
	}
	// 特技 12
	if (props.size() > 12 && props[12] >= 0)
	{
		m_Color[m_numtext] = RGB(126, 126, 255);
		// \n
		m_text[m_numtext] = "特技: " + g_pMainState->m_SkillManager.GetSpecialSkill(props[12])->m_Name/* + "\n"*/;
		++m_numtext;
	}
	// 是否无级别 13
	if (props.size() > 13 && props[13] >= 0)
	{
		m_Color[m_numtext] = RGB(126, 126, 255);
		m_text[m_numtext] = "特效: 无级别限制";
		// 是否神佑/愤怒 14
		if (props[14] >= 0)
		{
			// \n
			m_text[m_numtext] += (cct::isWeapon(item)) ? " 神佑" : " 愤怒";
		}
		++m_numtext;
	}
	else if (props.size() > 14 && props[14] >= 0)
	{
		// 是否神佑/愤怒 14
		m_Color[m_numtext] = RGB(126, 126, 255);
		m_text[m_numtext] = "特效:";
		// \n
		m_text[m_numtext] += (cct::isWeapon(item)) ? " 神佑" : " 愤怒";
		++m_numtext;
	}
	// 符石 15
	if (!cct::isWeapon(item) && props.size() > 15 && props[15] >= 0)
	{
		m_Color[m_numtext] = RGB(126, 126, 255);
		m_text[m_numtext] = "附加状态: " + g_pMainState->m_SkillManager.GetSkill(props[15])->m_Name;
		++m_numtext;
	}
	// 临时(额外) 16-
	str.clear();
	for (int i = 16; i < props.size(); i += 2)
	{
		if (props[i] >= 0)
		{
			str += "临时" + getProPertyString(props[i]) + toString(" %d\n", props[i + 1]);
		}
	}
	if (!str.empty())
	{
		str.pop_back();
	}
	if (!str.empty())
	{
		m_Color[m_numtext] = RGB(0, 255, 0);
		m_text[m_numtext] = str;
		++m_numtext;
		m_Color[m_numtext] = RGB(255, 255, 255);
		m_text[m_numtext] = "浪西游 强化打造";
		++m_numtext;
	}
}

