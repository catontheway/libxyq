#include "_global.h"


bool cTaskNormal::Process(int stage)
{
	cPropertyData* pUserData;
	cObj* pUser = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj;
	pUser->GetPropertyData(pUserData);
	switch (stage)
	{
	case -1:break;
	case 1: // 暗雷遇怪
	case 3: // 明雷遇怪
		if (!g_pMainState->ReadyToFight())
		{
			AddTriggerFightTurn(11);
		}
		AddTriggerFightSuccess(4);
		break;
	case 11:
		if (g_pMainState->m_pFightState->_turn > 0)
		{
			auto& list = g_pMainState->m_FightWorkList[10];
			if (list.isExist && !(list.CheckDie()) && list.m_pObj->m_TrueName.GetString() == "狡猾的貔貅")
			{
				int cid;
				int count = 0;
				do
				{
					int bbmode = g_pMainState->m_Map.m_EnemyList[rand() % g_pMainState->m_Map.m_NumOfEmemyType];
					sPetData* pm = g_pMainState->m_PetDataManager.GetPetData(bbmode);
					auto ppp = g_pMainState->AddEnemy(bbmode, g_pMainState->m_Map.m_EnemyLv + rand() % 5, pm->m_Name, nullptr, -1, false);
					if (!ppp)
					{
						break;
					}
					cid = ppp->m_IDinFightWorkList;
					++count;
					++g_pMainState->m_Map.m_EnemyNum;
					auto& list = g_pMainState->m_FightWorkList[cid];
					ppp->setPointAfterLv(g_pMainState->getAddpointFromPet(ppp, true), false);
					g_pMainState->m_pFightState->PrePareToFight(cid);
					ppp->FillHpMp();
					list.m_pObj->SetXY(g_pMainState->m_pFightState->m_战斗坐标xs[cid], g_pMainState->m_pFightState->m_战斗坐标ys[cid]);
					list.m_pObj->MoveShadow();
					list.m_pObj->MoveDialog();
					list.m_pObj->MoveHpLine();
					list.m_pObj->UpdateHpLine();
					list.m_pObj->MoveName();
					g_pMainState->FindObj();
				} while (true);
				if (count > 0)
				{
					list.m_pObj->saySkill(" 召唤");
				}
			}
		}
		break;
	case 4://奖励
	{
		if (m_pNpc)
		{
			g_pMainState->m_Map.RemoveNpc(m_pNpc, true);
			m_pNpc = 0;
		}
		//计算并显示奖励
		int fightnum = g_pMainState->m_Map.m_EnemyNum;// g_pMainState->GetLiveNum(0, 5);
		fightnum = max(10, fightnum);
		int ExpSuccess = GetNormalFightExp(pUserData->m_Lv, g_pMainState->m_Map.m_EnemyLv, fightnum);
		int ExpSuccessBB = GetNormalFightExp(g_pMainState->m_Map.m_EnemyLv, g_pMainState->m_Map.m_EnemyLv, fightnum);
//		int money = g_pMainState->m_Map.m_EnemyLv*(fightnum + 3) * 3;
// 		if (g_pCharacter->m_PcData.m_FightPetID == -1)
// 			ExpSuccessBB = 0;
//		g_pMainState->award1000(ExpSuccess, ExpSuccessBB, money, 0, false);
		g_pMainState->award(ExpSuccess, ExpSuccessBB);
		//m_WeaponRate几率得到装备
		if (rand() % 100 < 0)// g_pMainState->m_Map.m_WeaponRate)
		{
			int type = rand() % 22;
			if (type == 13)type = rand() % 13;
			int itemid = g_pMainState->m_ItemManage.GetIDByLv(type, g_pMainState->m_Map.m_Weaponlv * 10);
			sItem2 item;
			item.m_Num = 1;
			item.Set(type, itemid);
			g_pMainState->awardItem(item);
		}
		if (g_pMainState->_guaji)
		{
			cct::autoSave();
		}
		return true;
	}
		break;
	case 5://门派传送人
		if (!g_pMainState->m_Dialog.m_retSelect)
		{

			cMyMap& map = g_pMainState->m_Map;
			switch (g_pCharacter->m_PcData.m_MengPaiID)
			{
			case 0:map.LoadMap(151, 10, "大唐官府"); break;
			case 1:map.LoadMap(88, 49, "化生寺"); break;
			case 2:map.LoadMap(20, 98, "女儿村"); break;
			case 3:map.LoadMap(104, 121, "方寸山"); break;
			case 4:map.LoadMap(103, 16, "狮驼岭"); break;
			case 5:map.LoadMap(73, 60, "魔王寨"); break;
			case 6:map.LoadMap(175, 113, "盘丝岭"); break;
			case 7:map.LoadMap(37, 60, "阴曹地府"); break;
			case 8:map.LoadMap(79, 40, "龙宫"); break;
			case 9:map.LoadMap(28, 18, "五庄观"); break;
			case 10:map.LoadMap(16, 55, "普陀山"); break;
			case 11:map.LoadMap(159, 55, "天宫"); break;
			}
		}
		break;
	case 6:
	{
		if (g_pMainState->m_Dialog.m_retSelect == 5)
			return true;
		cMyMap& map = g_pMainState->m_Map;
		const auto& id = g_pCharacter->GetData()->m_ID;
		if (id == eJueSe::eJuSe剑侠客 || id == eJueSe::eJuSe逍遥生 || id == eJueSe::eJuSe英女侠 || id == eJueSe::eJuSe巫蛮儿 || id == eJueSe::eJuSe飞燕女)
		{
			switch (g_pMainState->m_Dialog.m_retSelect)
			{
			case 0:map.LoadMap(151, 10, "大唐官府"); break;
			case 1:map.LoadMap(88, 49, "化生寺"); break;
			case 2:map.LoadMap(20, 98, "女儿村"); break;
			case 3:map.LoadMap(104, 121, "方寸山"); break;
			}
		}
		else if (id == eJueSe::eJuSe骨精灵 || id == eJueSe::eJuSe狐美人 || id == eJueSe::eJuSe虎头怪 || id == eJueSe::eJuSe巨魔王 || id == eJueSe::eJuSe杀破狼)
		{
			switch (g_pMainState->m_Dialog.m_retSelect)
			{
			case 0:map.LoadMap(103, 16, "狮驼岭"); break;
			case 1:map.LoadMap(73, 60, "魔王寨"); break;
			case 2:map.LoadMap(175, 113, "盘丝岭"); break;
			case 3:map.LoadMap(37, 60, "阴曹地府"); break;
			}
		}
		else if (id == eJueSe::eJuSe龙太子 || id == eJueSe::eJuSe神天兵 || id == eJueSe::eJuSe舞天姬 || id == eJueSe::eJuSe玄彩蛾 || id == eJueSe::eJuSe羽灵神)
		{
			switch (g_pMainState->m_Dialog.m_retSelect)
			{
			case 0:map.LoadMap(79, 40, "龙宫"); break;
			case 1:map.LoadMap(28, 18, "五庄观"); break;
			case 2:map.LoadMap(16, 55, "普陀山"); break;
			case 3:map.LoadMap(159, 55, "天宫"); break;
			}
		}
	}
		break;
	case 7:
		if (g_pMainState->m_Dialog.m_retSelect == 0)
		{
			g_pMainState->m_Map.LoadMap(476, 30, "长安城");
			return true;
		}
		break;
	case 8://管家  // 休息
		g_pCharacter->m_PcData.FillHpMp();
		break;
	case 118:
	{

		g_pMainState->m_FangWu.GetBB();
	}
		break;
	case 119:

	{
		g_pMainState->m_FangWu.Move(g_pHeroObj->GetX(), g_pHeroObj->GetY(), g_pMainState->m_Dialog.m_pObj);
	}
		break;
	case 120:
		g_pMainState->m_FangWu.RemovePreJiaJu();
		break;
	case 9://镇宅兽

	{
		cObj* pObj = g_pMainState->m_pNowSelect;
		g_pMainState->m_Dialog.Reset();
		g_pMainState->m_Dialog.SetObj(pObj);
		g_pMainState->m_Dialog.SetString("主人,请问有什么吩咐?", "休息", "到这里来", "放生");
		g_pMainState->m_Dialog.SetTrigger(this, 10, 8, 10, 10, 10);
		g_pMainState->m_Dialog.OnOff(true);
	}
		break;
	case 10:
		switch (g_pMainState->m_Dialog.m_retSelect)
		{
		case 0:
			g_pCharacter->m_PcData.FillHpMp();
			break;
		case 1:
			g_pMainState->m_FangWu.Move(g_pHeroObj->GetX(), g_pHeroObj->GetY(), g_pMainState->m_Dialog.m_pObj);
			break;
		case 2:

		{
//			g_pCharacter->m_PcData.m_Money[0] -= 100000;
			g_pMainState->m_FangWu.RemoveBB(g_pMainState->m_Dialog.m_pObj);
			cObj* pObj = g_pMainState->m_Dialog.m_pObj;
			g_pMainState->m_Dialog.m_pObj->Talk("放生了镇宅兽");
			g_pMainState->m_Map.RemoveNpc(pObj->GetX(), pObj->GetY(), "", 1);
		}
			break;
		}
		break;
	case 12://南极仙翁
	{
		g_pMainState->m_TaskBangPai.Process(2);
		break;

		int lv = g_GlobalValues[3];
		if (lv > 4){ g_pMainState->m_pNowSelect->Talk("我已经没什么可以帮你的了"); return true; }
		ostringstream oss;
		oss << "当前仙灵店铺等级为";
		oss << lv;
		oss << "到下一个级别需要";
		oss << lv + 1;
		oss << "百万两,需要吗?";
		g_pMainState->m_TriggerDialog.AddSelect(this, oss.str(), g_pMainState->m_pNowSelect->m_TrueName.GetString(), -1, "是", 13, "否", -1);
	}
		break;
	case 13:
	{
		int moneyneed = (g_GlobalValues[3] + 1) * 1000000;
		if (g_pCharacter->m_PcData.AddMoney(0, -moneyneed, 0, false))
		{
			g_GlobalValues[3] += 1;
			ostringstream oss;
			oss << "你的仙灵店铺达到了" << g_GlobalValues[3] << "级!#88";

			g_pMainState->m_Dialog.TalkObj(oss.str());
		}
		else
		{
			g_pMainState->m_Dialog.TalkObj("你的钱不够#3");
		}
	}
		break;
	case 14:
	{
		// 飞行棋
		if (!g_pMainState->m_ItemManage.m_pNowItem)return false;
		sItem2* pi = g_pMainState->m_ItemManage.m_pNowItem;
		pi->m_Property[0] -= 1;
		if (0 == pi->m_Property[0])pi->m_Num = 0;
		g_pMainState->m_Map.LoadMap(pi->m_Property[1], pi->m_Property[2], pi->m_strProperty.c_str(), 1);
	}
		break;
	case 15:

	{
		if (!g_pMainState->m_ItemManage.m_pNowItem)return false;
		sItem2* pi = g_pMainState->m_ItemManage.m_pNowItem;
		pi->m_Property[1] = g_pMainState->m_InterfaceDoor.m_HeroX;
		pi->m_Property[2] = g_pMainState->m_InterfaceDoor.m_HeroY;
		pi->m_strProperty = g_pMainState->m_Map.m_MapName;
		g_pMainState->m_Tags.Add("在当前位置定了旗子");
	}
		break;
	default:
		break;
	}
	return false;
}


static std::vector<std::string> split(const std::string &str, const std::string &delim)
{
	std::vector< std::string > ret;

	size_t last = 0;
	size_t index = str.find_first_of(delim, last);

	if (index == std::string::npos)
	{
		ret.push_back(str);
		return ret;
	}

	while (index != std::string::npos)
	{
		ret.push_back(str.substr(last, index - last));
		last = index + 1;
		index = str.find_first_of(delim, last);
	}

	if (index - last > 0)
	{
		ret.push_back(str.substr(last, index - last));
	}

	return ret;
}
static std::string replace(std::string str, std::string to_replace, std::string replace)
{
	std::string::size_type pos = 0;
	std::string::size_type srcLen = to_replace.size();
	std::string::size_type desLen = replace.size();
	pos = str.find(to_replace, pos);
	while ((pos != std::string::npos))
	{
		str.replace(pos, srcLen, replace);
		pos = str.find(to_replace, (pos + desLen));
	}
	return str;
}

#if 0
vector<string> s_news;

const std::string& cTaskNormal::getNews()
{
	if (s_news.empty())
	{
		CWdf wdf;
		wdf.Open((g_pathWdf + "对话.wdf").c_str());
		std::ifstream& file = *wdf.GetFileHandle();
		string str;
		for (int i = 0; i < wdf.m_Number; ++i)
		{
			const auto& idx = wdf.m_pIndex[i];
			file.seekg(idx.offset, ios::beg);
			char* data = new char[idx.size];
			file.read(data, idx.size);
			str = data;
			delete[] data;
			auto strs = split(str, "N P");
			for (auto s : strs)
			{
				s = replace(s, "\r\n", "");
				s = replace(s, "\n", "");
				if (s.empty())
				{
					continue;
				}
				s_news.push_back(s);
			}
		}


		CWdf wdf2;
		wdf2.Open((g_pathWdf + "新闻.wdf").c_str());
		std::ifstream& file2 = *wdf2.GetFileHandle();
//		string str;
		for (int i = 0; i < wdf2.m_Number; ++i)
		{
			const auto& idx = wdf2.m_pIndex[i];
			file2.seekg(idx.offset, ios::beg);
			char* data = new char[idx.size];
			file2.read(data, idx.size);
			str = data;
			delete[] data;
			auto strs = split(str, "\r\n");
			for (auto s : strs)
			{
				s = replace(s, "\n", "");
				if (s.empty())
				{
					continue;
				}
				s_news.push_back(s);
			}
		}
		s_news.push_back("告诉你一个秘密,其实更新的只有表哥一个人,真正的表弟只在旁边一边玩QQ飞车,一边看着表哥开着两个QQ扯淡...");
	}
	return s_news[rand() % s_news.size()];
}

#endif