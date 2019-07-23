#include "_global.h"


bool ItemManager::UseItem24法宝(sItem2* pItem, int ObjId)
{
	if (g_StateType == STATE_FIGHT)return true;
	cObj* pTarget = g_pMainState->m_FightWorkList[ObjId].m_pObj;
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
	g_pMainState->m_InterfaceItem.m_Describe.OnOff(false);
	switch (pItem->GetID())
	{
	case 4://万鬼幡
		if (1)
		{
			g_pMainState->m_InterfaceDoor.SetHalf();
		}
		break;
	case 11:
		g_pMainState->m_InterfaceItem.InitMode(6);
		break;
	case 12://去CA
	case 13://去AL
	case 14://去CS
	case 15://去ZZ
	case 34://去境外
		g_pMainState->m_InterfaceItem.InitMode(pItem->GetID());
		break;
	case 16://隐蛊
		if (1)
		{
			if (2 == g_pMainState->m_InterfaceDoor.m_AvoidFight)
			{
				g_pMainState->m_InterfaceDoor.m_AvoidFight = 0;
				g_pMainState->m_Tags.Add("你进入了正常状态");
			}
			else
			{

				g_pMainState->m_InterfaceDoor.m_AvoidFight = 2;
				g_pMainState->m_Tags.Add("你进入了隐形状态");
			}
			
		}
		break;
	default:
		break;
	}


	return true;
}

bool ItemManager::UseItem26(sItem2* pCard, int ObjId)
{
	if (ObjId < 0)return false;
	cObj* pObj = g_pMainState->m_FightWorkList[ObjId].m_pObj;
	cCharacter*  pc = (cCharacter*)pObj->m_pIndex;
	pc->UseCard(pCard->GetID());
	if (pObj->GetDirection() % 2 == 0)
		pObj->SetDirection(pObj->GetDirection() + 1);
	pObj->Reset();
	pObj->Set(POS_STAND);
	g_pMainState->m_PCHead.UpDateHead();
	pCard->m_Num -= 1;
	return true;
}

static bool isNeed66(cPet* pet)
{
	int tlv = pet->GetData()->m_LvTake;
	int dlv = tlv + cct::LvGapFromRoleAndBaby;
	return pet->m_PetData.m_Lv > dlv;
}

static vector<int> getEquip66s(cPet* pet)
{
	int tlv = pet->GetData()->m_LvTake;
	int dlv = tlv + cct::LvGapFromRoleAndBaby;
	const auto& es = pet->m_PetData.m_Equips;
	vector<int> idxs;
	forr (es, i)
	{
		if (es[i].m_Num == 0)
		{
			continue;
		}
		if (es[i].m_pItemData->GetLv() > dlv)
		{
			idxs.push_back(i);
		}
	}
	return idxs;
}

static int getPackEmptysCount()
{
	const cPcData& pc = g_pCharacter->m_PcData;
	int c = 0;
	const auto& its = pc.m_Items;
	forr(its, i)
	{
		if (its[i].m_Num == 0)
		{
			++c;
		}
	}
	return c;
}


static int getPet66(bool checkEquip)
{
	const auto& ps = g_pCharacter->m_PcData.m_pPets;
	forv(ps, i)
	{
		if (!ps[i])
		{
			continue;
		}
		if (!isNeed66(ps[i]))
		{
			continue;
		}
		if (!checkEquip)
		{
			return i;
		}
		if (getPackEmptysCount() >= getEquip66s(ps[i]).size())
		{
			return i;
		}
	}
	return -1;
}

static bool use66(cPet* pet)
{
	int dlv = pet->GetData()->m_LvTake + cct::LvGapFromRoleAndBaby;
	auto& p = pet->m_PetData;

	const auto& es = getEquip66s(pet);
	forr(es, i)
	{
		auto& e = pet->m_PetData.m_Equips[es[i]];
		g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &e);
		e.m_Num = 0;
	}

	bool isdown = false;
	while (p.m_Lv > dlv)
	{
		if (p.lvdown())
		{
			isdown = true;
		}
		else
		{
			break;
		}
	}
	return isdown;
}


bool ItemManager::UseItem27道具(sItem2* pItem, int ObjId,  int* num)
{
	if (g_StateType == STATE_FIGHT)return true;
	switch (pItem->GetID())
	{
	case 0://飞行符
		g_pMainState->m_InterfaceItem.InitMode(1);
		g_pMainState->m_InterfaceItem.pItemnum = num;
		break;
	case 1://摄妖香
		g_pMainState->m_InterfaceDoor.m_AvoidFight = true;
		(*num) -= 1;
		return true;
	case 2://洞冥草
		g_pMainState->m_InterfaceDoor.m_AvoidFight = false;
		(*num) -= 1;
		return true;
	case 3:// 金柳露
	{
		int fid = g_pCharacter->m_PcData.m_FightPetID;
		if (fid < 0)
		{
			return true;
		}
		auto& pets = g_pCharacter->m_PcData.m_pPets;
		if (!isNeed66(pets[fid]))
		{
			return true;
		}
		if (getPackEmptysCount() < getEquip66s(pets[fid]).size())
		{
			return true;
		}

		use66(pets[fid]);
		(*num) -= 1;
		g_pMainState->m_Tags.Add(pItem->GetName() + "生效");
		return true;
	}
	case 4:
	{
		int fid = g_pCharacter->m_PcData.m_FightPetID;
		auto& pets = g_pCharacter->m_PcData.m_pPets;
		if (fid < 0 || !isNeed66(pets[fid]) || getPackEmptysCount() < getEquip66s(pets[fid]).size())
		{
			fid = getPet66(true);
		}
		if (fid < 0)
		{
			return true;
		}

		use66(pets[fid]);
		(*num) -= 1;
		if (fid == g_pCharacter->m_PcData.m_FightPetID)
		{
			g_pMainState->m_Tags.Add(pItem->GetName() + "生效");
		}
		else
		{
			g_pMainState->m_Tags.Add(pItem->GetName() + toString("生效于第%d只召唤兽", fid + 1));
		}
		return true;
	}
	case 5:
	{
		bool isok = false;
		bool isTotal = true;
		const auto& ps = g_pCharacter->m_PcData.m_pPets;
		forv(ps, i)
		{
			if (!ps[i])
			{
				continue;
			}
			if (!isNeed66(ps[i]))
			{
				continue;
			}
			if (getPackEmptysCount() >= getEquip66s(ps[i]).size())
			{
				use66(ps[i]);
				isok = true;
			}
			else
			{
				isTotal = false;
			}
		}
		if (!isok)
		{
			return true;
		}

		(*num) -= 1;
		if (isTotal)
		{
			g_pMainState->m_Tags.Add(pItem->GetName() + "生效");
		}
		else
		{
			g_pMainState->m_Tags.Add(pItem->GetName() + "生效(背包空间不足,仅部分生效)");
		}
		return true;
	}

	case 36://碧藕
		{
			if (!g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5].isExist)return true;
			cPropertyData* data;
			g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5].m_pObj->GetPropertyData(data);
			if (data->m_Lv == cct::MaxBabyLv)
			{
				return true;
			}
			data->m_EXP += 10000;// GetCharacterExp(data->m_Lv + 1);
			(*num) -= 1;
		}
		return true;
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
	case 50:
	case 51:
		if (0==(g_GlobalValues[1] & (1 << (pItem->GetID() - 42))))
		{
			g_GlobalValues[1] |= (1 << (pItem->GetID() - 42));
			(*num) -= 1;
		}
		return true;
	case 55: // 天眼BUG
		g_pMainState->m_Tags.Add("天眼有问题,暂时屏蔽功能");
		return true;
		if (g_pMainState->m_Job.CheckHaveJob(40))
		{
			//g_pMainState->m_TaskZhuaGui.UpdateZGJob(true);
			*num -= 1;
			ostringstream oss;
			oss << "找到,名字:" << g_pMainState->m_TaskZhuaGui.m_Ghost.m_name;
			oss << " 坐标X:";
			oss << g_pMainState->m_TaskZhuaGui.m_Ghost.m_x << " Y:";
			oss << g_pMainState->m_TaskZhuaGui.m_Ghost.m_y;
			g_pMainState->m_Channel.AddNewString(oss.str());

			return true;
		}
		if (g_pMainState->m_Job.CheckHaveJob(50))
		{
			if (1 == g_pMainState->m_TaskFB.m_List2.size())
			{
				ostringstream oss;
				oss << "找到,名字:" << g_pMainState->m_TaskFB.m_List2[0].m_Npc.m_name;
				oss << " 坐标X:";
				oss << g_pMainState->m_TaskFB.m_List2[0].m_Npc.m_x << " Y:";
				oss << g_pMainState->m_TaskFB.m_List2[0].m_Npc.m_y;
				g_pMainState->m_Channel.AddNewString(oss.str());
			}
			if (g_pMainState->m_TaskFB.m_List.size() < 3)
			{
				if (g_pMainState->m_TriggerObj.m_datalist.size())
				{
					ostringstream oss;
					oss << "找到,名字:" << g_pMainState->m_TaskFB.m_List[0].m_Npc.m_name;
					oss << " 坐标X:";
					oss << g_pMainState->m_TaskFB.m_List[0].m_Npc.m_x << " Y:";
					oss << g_pMainState->m_TaskFB.m_List[0].m_Npc.m_y;
					g_pMainState->m_Channel.AddNewString(oss.str());
				}
			}
			*num -= 1;
			return true;
		}
		else if (g_pMainState->m_TriggerObj.m_datalist.size())
		{
			if (g_pMainState->m_TriggerObj.m_datalist.size() > 3)return true;
			ostringstream oss;
			oss << "找到,名字:" << g_pMainState->m_TriggerObj.m_datalist[0].m_name;
			oss << " 所在地图:" << g_pMainState->m_TriggerObj.m_datalist[0].m_mapname;
			g_pMainState->m_Channel.AddNewString(oss.str());
			*num -= 1;
			return true;
		}
		break;
	case 59:
		(*num) -= 1;
		g_pMainState->m_InterfaceJianDing.SetMode(0);
		g_pMainState->m_InterfaceJianDing.OnOff(true);
		return true;
	case 60:
	case 61:
	case 62:
	case 63:
		if (1)
		{
// 			(*num) -= 1;
// 			g_pMainState->m_Tags.Add("便宜没好货");
// 			return true;
			eXiuLian xl;
			switch (pItem->GetID())
			{
			case 60:xl = eXLATK; break;
			case 61:xl = eXLDEF; break;
			case 62:xl = eXLMAG; break;
			default:xl = eXLDMAG; break;
			}
			int succ = g_pCharacter->m_PcData.m_XiuLianBB.AddExp(cct::getCurrMaxXiulianLv(g_pCharacter->m_PcData.m_Lv), 100, xl);
			if (succ == 0)
			{
				g_pMainState->m_Tags.Add("修炼已满");
				return true;
			}
			if (succ == 1 && g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5].isExist)
			{
				cPropertyData* pPet;
				g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5].m_pObj->GetPropertyData(pPet);	
				pPet->m_XiuLian = g_pCharacter->m_PcData.m_XiuLianBB;
			}
			(*num) -= 1;
		}
		return true;
	case 64:
	case 65:
	case 66:
	case 67:
		if (1)
		{
// 			(*num) -= 1;
// 			g_pMainState->m_Tags.Add("便宜没好货");
// 			return true;
			eXiuLian xl;
			switch (pItem->GetID())
			{
			case 64:xl = eXLATK; break;
			case 65:xl = eXLDEF; break;
			case 66:xl = eXLMAG; break;
			default:xl = eXLDMAG; break;
			}
			int succ = g_pCharacter->m_PcData.m_XiuLian.AddExp(cct::getCurrMaxXiulianLv(g_pCharacter->m_PcData.m_Lv), 100, xl);
			if (succ == 0)
			{
				g_pMainState->m_Tags.Add("修炼已满");
				return true;
			}
			(*num) -= 1;
		}
		return true;
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
		if (1)
		{
			if (!g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5].isExist)return true;
			cPetData* pPet;
			g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5].m_pObj->GetPropertyData((cPropertyData*&)pPet);
			int add;
			switch (pItem->GetID())
			{
			case 68:
				if (1800 > pPet->m_ZiZhi.atk)
				{
					add = (1800 - pPet->m_ZiZhi.atk) / 10;
					if (add > 50)add = 50;
					if (add < 10)add = 10;
					pPet->m_ZiZhi.atk += 1; // add;
					(*num) -= 1;
				}
				break;
			case 69:
				if (1800 > pPet->m_ZiZhi.def)
				{
					add = (1800 - pPet->m_ZiZhi.def) / 10;
					if (add > 50)add = 50;
					if (add < 10)add = 10;
					pPet->m_ZiZhi.def += 1; // add;
					(*num) -= 1;
				}
				break;
			case 70:
				if (6400 > pPet->m_ZiZhi.hp)
				{
					add = (6400 - pPet->m_ZiZhi.hp) / 20;
					if (add > 160)add = 160;
					if (add < 20)add = 20;
					pPet->m_ZiZhi.hp += 1; // add;
					(*num) -= 1;
				}
				break;
			case 71:
				if (4000 > pPet->m_ZiZhi.mag)
				{
					add = (3600 - pPet->m_ZiZhi.mag) / 20;
					if (add > 80)add = 80;
					if (add < 10)add = 10;
					pPet->m_ZiZhi.mag += 1; // add;
					(*num) -= 1;
				}
				break;
			case 72:
				if (2000 > pPet->m_ZiZhi.speed)
				{
					add = (1800 - pPet->m_ZiZhi.speed) / 10;
					if (add > 50)add = 50;
					if (add < 10)add = 10;
					pPet->m_ZiZhi.speed += 1; // add;
					(*num) -= 1;
				}
				break;
			case 73:
				if (2000>pPet->m_ZiZhi.avoid)
				{
					add = (2000 - pPet->m_ZiZhi.avoid) / 15;
					if (add > 50)add = 50;
					if (add < 10)add = 10;
					pPet->m_ZiZhi.avoid += 1; // add;
					(*num) -= 1;
				}
				break;
			case 74:
				if (130 > pPet->m_ZiZhi.grow)
				{
// 					add = (145 - pPet->m_ZiZhi.grow) / 10;
// 					if (add > 3)add = 3;
// 					if (add < 1)add = 1;
					pPet->m_ZiZhi.grow += 1 - 1;
					(*num) -= 1;
				}
				break;
			}
			
		}
		return true;
	}
	return false;
}


bool ItemManager::UseItem28(sItem2* pItem2, int ObjId)
{
	sItem* pItem = pItem2->m_pItemData;
	switch (pItem->m_ID)
	{
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		if (1)
		{
			m_pNowItem = pItem2;
			if (!pItem2->m_Property.size())
			{
				AutoItemProperty(pItem2);
			}
			if (1 == pItem2->m_Property.size())
			{
				pItem2->m_Property.push_back(g_pMainState->m_InterfaceDoor.m_HeroX);
				pItem2->m_Property.push_back(g_pMainState->m_InterfaceDoor.m_HeroY);
				pItem2->m_strProperty = g_pMainState->m_Map.m_MapName;
				g_pMainState->m_Tags.Add("在当前位置定了旗子");
			}
			else
			{
				ostringstream oss;
				oss << "要去" << pItem2->m_strProperty << "X:" << pItem2->m_Property[1] << " Y:" << pItem2->m_Property[2] << " 吗?";
				oss << "还剩" << pItem2->m_Property[0] << "次";
				g_pMainState->m_TriggerDialog.AddSelect(&g_pMainState->m_TaskNormal, oss.str(), g_pCharacter->m_PcData.m_Name, -1, "传送", 14, "定点", 15);
			}
		}
		return true;
	case 6://宝图
		if (1)
		{
			cObj* pUser = g_pHeroObj;
			cCharacter* pc = (cCharacter*)pUser->m_pIndex;
			ostringstream oss;
			if (0 != g_pMainState->m_Map.m_MapName.compare(g_pMainState->m_TaskBaoTu.m_MapNameList[pItem2->m_Property[0]]))
			{
				g_pMainState->m_Tags.Add("不在此地图...");
				return true;
			}
			if (abs(pUser->GetX() - pItem2->m_Property[3]) > 100)
			{
				g_pMainState->m_Tags.Add("不在这附近...");
				return true;
			}
			if (abs(pUser->GetY() - pItem2->m_Property[4]) > 100)
			{
				g_pMainState->m_Tags.Add("不在这附近...");
				return true;
			}

			--pItem2->m_Num;

			int r = rand() % 100;
			if(r < 10)
			{
				g_pMainState->m_TaskBaoTu.Process(6);
			}
			else if(r < 50)
			{
				if (!g_pMainState->awardBookIron(150))
				{
					g_pMainState->awardShouJue1();
				}
			}
			else if(r < 90)
			{
				g_pMainState->awardShouJue12();
			}
			else
			{
				g_pMainState->award5bao();
			}

#if 0
				int rat = rand() % 100;
				int itemrat[10];
				itemrat[0] = 0;//得钱率
				itemrat[1] = 40;//挖塌率 // 书铁
				itemrat[2] = 10;// 10;//出怪率
				itemrat[3] = 0;// 10;//符石率 
				itemrat[4] = 40;// 5;//兽决率
				itemrat[5] = 0;// 10;//得环率
				itemrat[6] = 10;// 3;//五宝率
				itemrat[7] = 0;// 10;//66
				itemrat[8] = 0;//挖伤率
				itemrat[9] = 0;// 10;//宝石

				int lvMin = g_pMainState->getMinLv();
				int lvMax = 80;
				if (lvMin >= (lvMax + 10) )
				{
					itemrat[4] += itemrat[1];
					itemrat[1] = 0;
				}
				lvMin = lvMin / 10 * 10;

				pItem2->m_Num -= 1;
				//其它情况 
				if (rat < itemrat[0])//10%几率得钱
				{
					int money = pc->m_PcData.m_Lv * 100 + 5000;
					oss.str("");
					oss << "你得到了";
					oss << money;
					oss << "钱";
					pc->AddMoney(money, 0);
					g_pMainState->m_Tags.Add(oss.str());
					g_pMainState->m_InterfaceItem.SetXianJin(g_pMainState->m_InterfaceItem.m_bXianJin);
					return true;
				}

				sItem2 item;
				item.m_Num = 1;

				rat -= itemrat[0];
				if (rat < itemrat[1])// 10% 挖塌 // 书铁
				{
					/*	g_pMainState->m_Tags.Add("你挖塌了妖怪的家");
					oss.str("");
					oss << pUser->m_TrueName.GetString();
					oss << "挖宝时不小心挖塌了妖怪的房子,一群妖怪正在各处闹事#15";
					g_pMainState->m_Channel.AddNewString(oss.str());
					g_pMainState->m_Channel.AddNewString("挖了半天什么都没挖到...");*/
					g_pMainState->m_Tags.Add("你好像挖到了什么");

					item.Set(28, (rand() % 100 < 50) ? 7 : 8);
					item.m_Property.resize(1);
					int& lv = item.m_Property[0];
					lv = lvMin + (rand() % (lvMax - lvMin + 1));
					lv = lv / 10 * 10;
					if (lv < lvMax && (rand() % 100 < 20))
					{
						lv += 10;
					}
					g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
					return true;
				}
				rat -= itemrat[1];
				if (rat < itemrat[2])// 10% 出怪率
				{
					g_pMainState->m_Tags.Add("你挖出了一个箱子,但从箱子里跑出个妖怪");
					g_pMainState->m_TaskBaoTu.Process(6);
					return true;
				}
				rat -= itemrat[2];

				if (rat < itemrat[3])//符石
				{
					item.Set(41, rand() % 78);
					g_pMainState->m_Tags.Add("你得到了符石");
					g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
					return true;
				}
				rat -= itemrat[3];
				if (rat < itemrat[4]) //3%几率得兽决
				{
					vector<int> sks = { 1, 3, 9, 11, 15, 17, 19, 21, 26, 30, 32, 34, 36, 38, 42, 44, 52, 54, 60, 22, 67, 69, 71, 73 };
					vector<int> sk2s = { 5, 7, 13, 24, 28, 40, 46, 48, 50, 56, 58, 78, 80, 82, 75, 76, 83, 103, 106 };
					int idx = sks.size() / 2;
					forr(sk2s, i)
					{
						sks.insert(sks.begin() + idx, sk2s[i]);
					}
//					item.Set(40, g_pMainState->m_ItemManage.m_LShouJueList[rand() % g_pMainState->m_ItemManage.m_LShouJueList.size()]);
					item.Set(40, sks[rand() % sks.size()]);
					g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
					g_pMainState->m_Tags.Add("你好像挖到了什么");
					return true;
				}
				rat -= itemrat[4];
				if (rat < itemrat[5])//7%几率得环
				{
					int type = rand() % 22;
					if (type == 13)type = rand() % 13;
					int lv = (5 + rand() % 3) * 10;  //50-70装备
					int id = GetIDByLv(type, lv);
					item.Set(type, id);
					g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
					g_pMainState->m_Tags.Add("你得到了妖怪遗留的宝贝");
					return true;
				}
				rat -= itemrat[5];
				if (rat < itemrat[6])//5%几率出五宝
				{
					g_pMainState->m_Tags.Add("你好像挖到了什么");
					g_pMainState->award5bao();
					return true;
				}
				rat -= itemrat[6];
				if (rat < itemrat[7])//得66
				{
					g_pMainState->m_Tags.Add("你得到了传说中的金柳露");
					item.Set(27, 3 + rand() % 3);
					g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
					return true;
				}
				rat -= itemrat[7];
				if (rat < itemrat[8])//伤
				{
					g_pMainState->m_Tags.Add("你挖出了瘴气,处于濒死状态");
					pc->m_PcData.m_HP = 1;
					pc->m_PcData.m_MP = 1;
					g_pMainState->m_PCHead.UpdatePcHp();
					g_pMainState->m_PCHead.UpdatePcMp();
					return true;
				}
				rat -= itemrat[8];
				if (rat < itemrat[9])//宝石
				{
					item.Set(29, rand() % 17);
					g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
					g_pMainState->m_Tags.Add("你挖到了宝石");
					return true;
				}
				else  //什么都没挖到
				{
					g_pMainState->m_Tags.Add("挖了半天什么都没挖到");

					return true;
				}
					}
#endif
		}
		break;
	case 19:
		if (1)
		{
			ERRBOX;
		}
		break;
	case 20:
		ERRBOX;
		break;
	case 21://四门挖宝
		if (1)
		{
			g_pMainState->m_TaskFB.ProcessSM(8);
			return false;
		}
	default:
		break;
	}
	return false;
}






bool ItemManager::UseItem(sItem2* pItem, int ObjId,  int* num)
{
	if (pItem->GetNum() < 1)
		return false;
	switch (pItem->GetType())
	{
	case 22:
		if(!UseItem22药品(pItem, ObjId))return false;
		break;
	case 23:
		if(!UseItem23烹饪(pItem, ObjId))return false;
		break;
	case 24:
		return UseItem24法宝(pItem, ObjId);
	case 25:
		return false;
	case 27:
		return UseItem27道具(pItem, ObjId, num);
	default:
		return false;
		break;
	}
	cObj* pObj;
	if (ObjId == g_pMainState->m_HeroID)
	{
		if (m_bAddHp)
		{
			g_pMainState->m_PCHead.UpdatePcHp();
			g_pMainState->m_State.UpDateHp();
		}
		if (m_bAddMp)
		{
			g_pMainState->m_PCHead.UpdatePcMp();
			g_pMainState->m_State.UpDateMp();
		}
		if (m_bAddCp)
		{
			g_pMainState->m_PCHead.UpdatePcCp();
			g_pMainState->m_State.UpDateCp();
		}
	}
	else
	if (ObjId == g_pMainState->m_HeroID + 5)
	{
		if (m_bAddHp)
		{
			g_pMainState->m_PCHead.UpdatePetHp();
		}
		if (m_bAddMp)
		{
			g_pMainState->m_PCHead.UpdatePetMp();
		}
	}
	if (g_StateType == STATE_FIGHT)
	if (m_bToAll)
	{
		int start, end;
		if (ObjId < 10)
		{
			start = 0;
		}
		else start = 10;
		end = start + 10;
		for (int i = 0; i < 10; i++)
		{
			if (!g_pMainState->m_FightWorkList[i].isExist)continue;
			pObj = g_pMainState->m_FightWorkList[i].m_pObj;
			if (m_bAddHp&&m_bAddMp)
			{
				pObj->SetMagicEffectFromItem(&m_MagicAddHPMP, -10);
				g_pMainState->m_SkillManager.SetDamage(-g_pMainState->m_ItemManage.m_hp, i);
			}
			else
			if (m_bAddHp)
			{
				pObj->SetMagicEffectFromItem(&m_MagicAddHP, -10);
				g_pMainState->m_SkillManager.SetDamage(-g_pMainState->m_ItemManage.m_hp, i);
			}
			else
			if (m_bAddMp)
			{
				pObj->SetMagicEffectFromItem(&m_MagicAddMP, -10);
			}
			else return true;
		}
		return true;
	}
	if (g_StateType == STATE_MAIN)
		ObjId = ObjId % 5;
	pObj = g_pMainState->m_FightWorkList[ObjId].m_pObj;
	if (m_bAddHp&&m_bAddMp)
	{
		pObj->SetMagicEffectFromItem(&m_MagicAddHPMP, -10);
		if (g_StateType == STATE_FIGHT)
			g_pMainState->m_SkillManager.SetDamage(-g_pMainState->m_ItemManage.m_hp, ObjId);
	}
	else
	if (m_bAddHp)
	{
		pObj->SetMagicEffectFromItem(&m_MagicAddHP, -10);
		if (g_StateType == STATE_FIGHT)
			g_pMainState->m_SkillManager.SetDamage(-g_pMainState->m_ItemManage.m_hp, ObjId);
	}
	else
	if (m_bAddMp)
	{
		pObj->SetMagicEffectFromItem(&m_MagicAddMP, -10);
	}


	return true;
}


bool ItemManager::removeBuff(int Type, int TargetID, int ReMoveAll)
{ 
	bool success=false;
	if (ReMoveAll)
	{
		success= Detoxify1(Type, TargetID);
	}
	else
	{
		while (Detoxify1(Type, TargetID))
		{
			success = true;
		}
		return true;
	}
	return success;
}


bool ItemManager::Detoxify1(int Type, int TargetID)
{
	cObj* p1 = g_pMainState->m_FightWorkList[TargetID].m_pObj;
	sBuff buf;
	if (p1->m_StateList.size())
	for (list<sBuff>::iterator Iterator = p1->m_StateList.begin(); Iterator != p1->m_StateList.end();)
	{
		if (Type == (int)Iterator->EffectType)
		{
			list<sBuff>::iterator it2 = Iterator;
			Iterator++;
			g_pMainState->m_SkillManager.SetDateBuffDown(it2);//it2->targetID, it2->ID);
			it2->data.Free();
			p1->m_StateList.erase(it2);
			return true;
		}
		else
			Iterator++;
	}
	return false;
}


int ItemManager::GetIDByLv(int type, int lv)
{
	if (type >= 32 && type <= 34)
	{
		if (lv >= 165)
		{
			return 0;
		}
		if (lv < 5)
		{
			return 1;
		}
		return (lv - 5) / 10 + 1;
	}

	if (lv > 160)lv = 160;
	lv /= 10;
	if (type < 15 || (type >= 42 && type <= 44)) //武器
	{
		if (lv < 9)return lv;
		if (lv < 12)return 9 + (rand() % 3) * 3 + (lv - 9);
		if (lv < 15)return 18 + (rand() % 3) * 3 + (lv - 12);
		if (lv == 15)return 27;
		return 28;
	}
	if (type ==19|| type==20)//装备
	{
		if (lv == 3)return 3 + rand() % 2;
		if (lv == 4)return 5 + rand() % 2;
		if (lv == 5)return 7 + rand() % 2;
		if (lv == 6)return 9 + rand() % 2;
		if (lv == 7)return 11 + rand() % 2;
		if (lv == 8)return 13 + rand() % 2;
		if(lv>8) return lv + 6;
	}
	return lv;
 }


int ItemManager::GetlvByID(int type, int id)
{
	if (type >= 42 && type <= 44) //武器
	{
		if (id < 9)return id * 10;
		if (id < 18)return (9 + id % 3) * 10;
		if (id < 27)return (12 + id % 3) * 10;
		if (id == 27)return 150;
		else return 160;
	}
	else if (type < 15) //武器
	{
		if (id < 9)return id * 10;
		if (id < 18)return (9 + id % 3)*10 ;
		if (id < 27)return (12 + id % 3) * 10;
		if (id == 27)return 150;
		else return 160;
	}
	if (type == 19 || type == 20)//装备
	{
		if (id < 3)return id * 10;
		else if (id < 15)
			return ((id - 3) / 2 + 3) * 10;
		else return (id - 6) * 10;
	}
	return id * 10;
}



sWeaponData* ItemManager::GetWeaponList(int charid, int weaponid, int type)
{
	int trueid;
	//0-20 30-50 60-80 等等是一个造型
	if (weaponid<27)trueid = weaponid / 3;
	else trueid = weaponid - 18;

	if (type >= eWeaponType巨剑)
	{
		type -= 27;
	}
	vector<sWeaponData>& list=	 g_pMainState->m_ItemManage.m_pWeaponList2[type][trueid];
	for (int i = 0; i < list.size(); i++)
	{
		if (charid == list[i].Master)
			return  &list[i];
	}
	return 0;
}




void ItemManager::GetIDlistByLv(vector<int>& outlist, int type, int lv)
{
	if (lv>160)lv = 160;
	lv /= 10;
	if (type < 15 || (type >= 42 && type <= 44)) //武器
	{
		if (lv < 9)
		{
			outlist.push_back(lv);
			return;
		}
		if (lv < 12)
		{
			outlist.push_back(lv);
			outlist.push_back(lv+3);
			outlist.push_back(lv+6);
			return;
		}
		if (lv < 15)
		{
			outlist.push_back(lv+6);
			outlist.push_back(lv + 9);
			outlist.push_back(lv + 12);
			return;
		}
		if (lv == 15)
		{
			outlist.push_back(27);
			return;
		}
		outlist.push_back(28);
		return;
	}
	if (type == 19 || type == 20)//装备
	{
		if (lv == 3)
		{
			outlist.push_back(3);
			outlist.push_back(4);
			return;
		}
		if (lv == 4)
		{
			outlist.push_back(5);
			outlist.push_back(6);
			return; 
		}
		if (lv == 5)
		{
			outlist.push_back(7);
			outlist.push_back(8);
			return;
		}
		if (lv == 6)
		{
			outlist.push_back(9);
			outlist.push_back(10);
			return;
		}
		if (lv == 7)
		{
			outlist.push_back(11);
			outlist.push_back(12);
			return;
		}
		if (lv == 8)
		{
			outlist.push_back(13);
			outlist.push_back(14);
			return;
		}
		if (lv > 8)
		{
			outlist.push_back(lv+6);
			return;
		}
	}
	outlist.push_back(lv);
	return;
}




bool ItemManager::FillProperty(int CharID, ItemProPerty type)
{
	int * dada1 = 0;
	int * dada2 = 0;

	cObj* pUser = g_pMainState->m_FightWorkList[CharID].m_pObj;
	cPropertyData* pPetData;
	pUser->GetPropertyData(pPetData);
	switch (type)
	{
	case enum_hp:
		dada1 = &pPetData->m_HP;   //hp
		dada2 = &pPetData->m_HP2; //伤
		break;
	case enum_hphurt:
		dada1 = &pPetData->m_HP2;         //hp
		dada2 = pPetData->HPMax.GetDatap();
		break;
	case enum_mp:
		dada1 = &pPetData->m_MP;
		dada2 = pPetData->MPMax.GetDatap();
		break;
	default:
		ERRBOX;
		break;
	}

	cCharacter* pCharOwner;
	int charid2 = CharID % 5;

	pCharOwner = (cCharacter*)g_pMainState->m_FightWorkList[CharID % 5].m_pObj->m_pIndex;
	int dustbin = 0;
	int* numItem = &dustbin;
	sItem2* Item = 0;
	while (*dada1 < *dada2)
	{
		if (!(*numItem))
		{
			int id3 = GetCheapestItem右键加血(charid2, type);
			if (id3 == -1)return true;
			Item = &pCharOwner->m_PcData.m_Items[id3];
			numItem = &Item->m_Num;

		}
		if (Item)
		{
			UseItem(Item, CharID, 0);
		}
	}

	return true;
}




bool ItemManager::XiangQian(sItem2& equip, sItem2& gem)
{
	if (gem.GetType() != 29)return false;
	switch (equip.GetType())
	{
	case 15://头盔
	case 16:
		switch (gem.GetID())
		{
		case 10://月亮
		case 9://太阳
		case 2://玛瑙
			break;
		default:return false;
		}
		break;
	case 17:
	case 18:
		switch (gem.GetID())
		{
		case 10://月亮
//		case 0://光芒
		case 7://舍利
			break;
		default:return false;
		}
		break;
	case 19://项链
		switch (gem.GetID())
		{
// 		case 3://红宝石
// 		case 4://黄宝石
// 		case 5://蓝宝石
// 		case 6://绿宝石
		case 7://舍利
			break;
		default:return false;
		}
		break;
	case 20://腰带
		switch (gem.GetID())
		{
		case 1://黑宝石
		case 0://光芒
			break;
		default:return false;
		}
		break;
	case 21://鞋
		switch (gem.GetID())
		{
// 		case 3://红宝石
// 		case 4://黄宝石
// 		case 5://蓝宝石
// 		case 6://绿宝石
 		case 8://神密
		case 1://黑宝石
			break;
		default:return false;
		}
		break;
	case 32://护腕
		switch (gem.GetID())
		{
		case 12:
		case 15:
			break;
		default:return false;
		}
		break;
	case 33://项圈
		switch (gem.GetID())
		{
		case 11:
		case 14:
			break;
		default:return false;
		}
		break;
	case 34://铠甲
		switch (gem.GetID())
		{
		case 13:
		case 16:
			break;
		default:return false;
		}
		break;
	default:
		if (cct::isWeapon(&equip))
		{
			// 武器
			switch (gem.GetID())
			{
			case 9:
			case 8:
			case 2:
				break;
			default:return false;
			}
		}
		else return false;
		break;
	}

	bool isBB = cct::isEquipBB(&equip);
	auto& pro = equip.m_Property;
	int lv = pro[0];
	if (pro.size() > 1 && lv > 0 && pro[1] >= 0)
	{
		SetUpBaoShi(pro, pro[1], -lv, isBB);
	}

	lv = equip.m_pItemData->GetLv() / 10;
#if 0
	if (cct::isWJB(&equip))
	{
		// 无级别
		lv = cct::MaxStoneWJB;
	}
#endif
	if (lv < 1)
	{
		pro[0] =  pro[1] = -1;
		return false;
	}
	//宝石效果
	pro[0] = lv;
	pro[1] = gem.GetID();
	SetUpBaoShi(pro, pro[1], lv, isBB);
	return true;
}

bool ItemManager::UseJiaJu(sItem2* pItem)
{
	string mapname = g_pMainState->m_Map.m_MapName;
	string mapnameneed = g_pMainState->m_FangWu.GetMapName();
	if (0 != mapname.compare(mapnameneed))return true;

	if (pItem->m_pItemData->GetLv() == 3)
	{
		g_pMainState->m_FangWu.m_DiBan = *pItem;
		cObj* obj = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj;
		int xold = obj->GetX();
		int yold = obj->GetY();

		g_pMainState->m_FangWu.GoIn();
		for (int i = 0; i < 5; i++)
		{
			if (g_pMainState->m_FightWorkList[i].isExist)
			g_pMainState->m_FightWorkList[i].m_pObj->SetXY(xold, yold);
		}
		pItem->m_Num = 0;
		g_pMainState->m_FangWu.CheckHuanJin();
		return true;
	}

	g_pMainState->m_UseJiaJu.SetJiaJu(pItem);
	return true;
}





