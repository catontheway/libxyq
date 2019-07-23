#include "_global.h"



// bool CMainState::GivePcAPet(int charID, cPet* pPet, bool setfight)
// {
// 	if (m_FightWorkList[charID].m_pObj->GetDataType() != INDEXTYEP_CHARACTER)return false;
// 	cCharacter* pPcData = (cCharacter*)m_FightWorkList[charID].m_pObj->m_pIndex;
// 	if (pPcData->m_PcData.m_NumofBB == pPcData->m_PcData.m_pPets.size())return false;
// 	pPcData->m_PcData.AddPet(pPet);
// 	if (setfight)
// 	{
// 		SetFightPet(charID, pPcData->m_PcData.m_NumofBB - 1);
// 	}
// 	return true;
// }





//设置出战召唤兽
bool CMainState::SetFightPet(int ID, int PetID, bool blimit)
{
	if ((ID + 5) % 10 < 5)
		return false;
	cObj* pPcObj = m_FightWorkList[ID].m_pObj;
	cCharacter* pc = (cCharacter*)pPcObj->m_pIndex;
	cPet* pet = 0;
	cPropertyData* pPcData;
	pPcObj->GetPropertyData(pPcData);
	cObj* pPetObj = m_FightWorkList[ID + 5].m_pObj;
	if (pc->m_PcData.m_FightPetID == PetID)
		return true;
	if (pPetObj->GetDataType() == INDEXTYEP_CHARACTER)
	{ 
		//位置被别人占用了,无法召唤
		return false;
	}
	if (m_FightWorkList[ID].m_FriendListid > -1)
	{//同步
		int flistid = m_FightWorkList[ID].m_FriendListid;
		if (flistid < g_pMainState->m_Friend.m_FriendList.size())
			g_pMainState->m_Friend.m_FriendList[flistid].m_FightBB = PetID;
	}

	if (PetID == -1)//当ID为-1时表时 召还
	{
		//清除修炼 ,因为BB参战时的属性会受人物影响
		if (pPetObj->GetDataType() == INDEXTYEP_PET)
		{
			pet = (cPet*)pPetObj->m_pIndex;
			if (pet)
			{
				if (!pet->m_PetData.m_Controler.CheckBB())
				{
					return false;//位置被别人占用了,无法召还
				}
				if (g_StateType == STATE_FIGHT)
				{
					g_pMainState->m_pFightState->BackFromFight(ID + 5);
				}
				pet->m_PetData.m_XiuLian.Reset();
			}
		}
		
		pPetObj->m_pIndex = 0;
		pPetObj->m_IndexType = 0;
		pPetObj->Free();
		m_FightWorkList[ID + 5].isExist = false;
		pc->m_PcData.m_FightPetID = -1;
		pc->m_PcData.m_Controler.SetHaveBB(false);
	}
	else     //设置参战
	{
		if (PetID < 0)return false;
		if (PetID >= pc->m_PcData.m_NumofBB)return false;
		pet = pc->m_PcData.m_pPets[PetID];

		if (blimit)
		{
			if (pet->GetData()->m_LvTake > pc->m_PcData.m_Lv)return false;
			if (pet->m_PetData.m_Lv > pc->m_PcData.m_Lv + cct::LvGapFromRoleAndBaby)return false;
		}
		//先召还
		if (pc->m_PcData.m_FightPetID > -1)
			SetFightPet(ID, -1);
		if (m_FightWorkList[ID].m_FriendListid > -1)
		{//同步
			int flistid = m_FightWorkList[ID].m_FriendListid;
			if (flistid < g_pMainState->m_Friend.m_FriendList.size())
				g_pMainState->m_Friend.m_FriendList[flistid].m_FightBB = PetID;
		}
		g_pMainState->m_FightWorkList[ID + 5].isExist = true;
		//设置修炼
		pet->m_PetData.m_XiuLian = pc->m_PcData.m_XiuLianBB;
		pet->m_PetData.applyXL();

		pPetObj->m_pIndex = pet;
		pPetObj->m_IndexType = INDEXTYEP_PET;
		if (g_StateType == STATE_FIGHT)
		{
			g_pMainState->m_pFightState->PrePareToFight(ID + 5);
		}

		if (!pc->m_PcData.m_pPets[PetID]->GetData())
			pc->m_PcData.m_pPets[PetID]->SetData(g_pMainState->m_PetDataManager.GetPetData(pc->m_PcData.m_pPets[PetID]->m_PetData.modeid));

		pPetObj->m_TrueName.m_hFont = m_hFont[0];
		pPetObj->m_TrueName.SetString(pc->m_PcData.m_pPets[PetID]->m_PetData.m_Name);
		pc->m_PcData.m_FightPetID = PetID;

		cPropertyData* pPetData;
		pPetObj->GetPropertyData(pPetData);

		//设置它的归属 ,这样系统才知道当战斗时玩家有没有权力控制它
		pPetData->m_Controler.Set(pPetData->m_Controler.GetFly(), /*(ID < 5) ? */0 /*: (pPetData->m_Controler.GetDel())*/, 1/*(ID < 5)*/);
		pc->m_PcData.m_Controler.SetHaveBB(true);
		m_pFightState->m_FightMenu.SetControl(ID + 5, m_pFightState->m_FightMenu.CheckControl(ID));
	}
	g_pMainState->m_PCHead.Init();
	//通知改变头像
	if (ID == m_HeroID)
	{
		if (-1 == PetID)
		{
			m_PCHead.m_pPet = 0;
			m_PCHead.SetPetHead(0);
		}
		else
		{
			m_PCHead.m_pPet = pc->m_PcData.m_pPets[PetID];
			m_PCHead.SetPetHead(m_PCHead.m_pPet->GetID(POS_SMALLHEAD));
		}

		m_PCHead.UpdatePet();
	}
	m_PCHead.UpDateHead();
	return true;
}




int CMainState::getAvgLv()
{
	cPropertyData* pPetData;
	set<int> lvs;
	int lvmax = 0;
	int lvmin = cct::MaxRoleLv;
	for (int i = 0; i < 5; i++)
	{
		if (m_FightWorkList[i].isExist)
		{
			m_FightWorkList[i].m_pObj->GetPropertyData(pPetData);
			lvs.insert(pPetData->m_Lv);
			if (lvmax < pPetData->m_Lv)
			{
				lvmax = pPetData->m_Lv;
			}
			if (lvmin > pPetData->m_Lv)
			{
				lvmin = pPetData->m_Lv;
			}
		}
	}
	lvmin = (lvmin + lvmax) / 2;
	int lv = 0;
	for (const auto& l : lvs)
	{
		lv += l;
	}
	lv /= lvs.size(); // g_pMainState->GetPCFightNum();
	lv = max(lv, lvmin);
	vector<int> lv2s(lvs.begin(), lvs.end());
	lvmin = lv2s.size();
	if (lvmin > 2)
	{
		if (lvmin % 2)
		{
			lvmin = (lv2s[lvmin / 2] + lv2s[lvmin / 2 + 1]) / 2;
		}
		else
		{
			lvmin = (lv2s[(lvmin - 1) / 2] + lv2s[(lvmin - 1) / 2 + 1]) / 2;
		}
		lv = max(lv, lvmin);
	}
	lv = (lv + lvmax) / 2;
	return lv;
}


int CMainState::getMaxLv()
{
	cPropertyData* pPetData;
	int lvmax = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_FightWorkList[i].isExist)
		{
			m_FightWorkList[i].m_pObj->GetPropertyData(pPetData);
			if (lvmax < pPetData->m_Lv)
			{
				lvmax = pPetData->m_Lv;
			}
		}
	//	else break;
	}
	return lvmax;
}


int CMainState::getMinLv()
{
	cPropertyData* pPetData;
	int lvmin = cct::MaxRoleLv;
	for (int i = 0; i < 5; i++)
	{
		if (m_FightWorkList[i].isExist)
		{
			m_FightWorkList[i].m_pObj->GetPropertyData(pPetData);
			if (lvmin > pPetData->m_Lv)
			{
				lvmin = pPetData->m_Lv;
			}
		}
	//	else break;
	}
	return lvmin;
}




void CMainState::SetCharacter(int ID)
{
// 	if (!m_FightWorkList[ID].isExist)
// 	{
// 		return;
// 	}
// 	m_HeroID = ID;
	g_pHeroObj = m_FightWorkList[m_HeroID].m_pObj;
	g_pHeroObj->m_bCheckWall = true;//主角走路要进行碰撞检测
	g_pCharacter = (cCharacter*)g_pHeroObj->m_pIndex;
// 	for (int i = 0; i < 20; i++)
// 	{
// 		m_pFightState->m_FightMenu.SetControl(i, false);
// 	}
	INT64 money = 0;
	forr (m_Friend._friends, i)
	{
//		if (m_FightWorkList[i].isExist)
		{
			cPcData* c = m_Friend._friends[i].obj->getPcData();
			if (!c)
			{
				continue;
			}
//			cPcData* c = m_FightWorkList[i].m_pObj->getPcData();
//			m_FightWorkList[i].m_pObj->GetPropertyData(c);
			auto& ms = c->m_Money;
			forr(ms, k)
			{
				money += ms[k];
				ms[k] = 0;
			}
		}
	}
	g_pCharacter->m_PcData.m_Money[0] = money;
//	g_pCharacter->m_PcData.m_IDinFightWorkList = g_pHeroObj->m_IDInFightlist = m_HeroID;
//	g_pCharacter->m_PcData.m_Controler.Set(0, 0);
	m_PCHead.SetPcID(m_HeroID);
}



int CMainState::AtutoGetEnemyNum(int nmin /* = 1 */, int nmax /* = 10 */)
{
	int our = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_FightWorkList[i].isExist)our += 1;
	}
	int EnemyNum = our - 2 + rand() % (our + 3);
	if (EnemyNum > nmax)EnemyNum = nmax;
	if (EnemyNum < nmin)EnemyNum = nmin;
	return EnemyNum;
}



int CMainState::GetLiveNum(int start, int end)
{
	int num = 0;
	for (int i = start; i < end; i++)
	{
		if (m_FightWorkList[i].isExist)
		{
// 			if (i % 10 != 0)
// 			{
// 				// 日月乾坤
// 				if (m_FightWorkList[i].m_pObj->CheckHaveState(89))
// 				{
// 					continue;
// 				}
// 			}

			if (!m_FightWorkList[i].CheckDie())
			{
				++num;
			}
		}
	}
	return num;
}






void CMainState::awardItem(sItem2& item, bool m_bNeedTag)
{
	m_InterfaceItem.GetItem(m_HeroID, &item);
	ostringstream oss;
	oss << item.GetName() << " +1";
	m_Tags.Add(oss.str());
	if (m_bNeedTag)
	{
		m_Channel.AddNewString(oss.str());
	}
}


void CMainState::awardItem(int type, int id, int num /*= 1*/, bool m_bNeedTag /*= false*/)
{
	sItem2 item;
	item.m_Num = num;
	item.Set(type, id);
	awardItem(item, m_bNeedTag);
}

void CMainState::awardEquip(int lv)
{
	sItem2 item;
	item.m_Num = 1;
	int type = 15 + rand() % 7;
	if (rand() % 100 < 17)
	{
		type = rand() % 15;
		if (rand() % 100 < 20)
		{
			type = rand() % 3 + 42;
		}
	}
	item.Set(type, g_pMainState->m_ItemManage.GetIDByLv(type, lv));
	g_pMainState->m_ItemManage.AutoItemProperty(&item, false);
	awardItem(item, true);
}


void CMainState::award5bao()
{
	awardItem(27, 6 + rand() % 5, true);
}



void CMainState::awardBook(int lv)
{
	sItem2 item;
	item.m_Num = 1;
	item.Set(28, 8);
	item.m_Property.resize(1);
	item.m_Property[0] = lv;
	awardItem(item, true);
}


void CMainState::awardIron(int lv)
{
	sItem2 item;
	item.m_Num = 1;
	item.Set(28, 7);
	item.m_Property.resize(1);
	item.m_Property[0] = lv;
	awardItem(item, true);
}

bool CMainState::awardBookIron(int maxlv)
{
	int lvMin = g_pMainState->getMinLv();
	lvMin = lvMin / 10 * 10;
	lvMin = max(lvMin, 60);
	////////////////////////////////////////////////////////////////////////// 先限制150铁
	maxlv = min(150, maxlv);
	//////////////////////////////////////////////////////////////////////////
	if (lvMin > maxlv)
	{
		return false;
	}
	
	int lv = lvMin + (rand() % (maxlv - lvMin + 1));
	lv = lv / 10 * 10;
	if (rand() % 100 < 50)
	{
		if (lv < maxlv)
		{
			lv += 10;
		}
		awardIron(lv);
	}
	else
	{
		awardBook(lv);
	}
	return true;
}

void CMainState::awardShouJue1()
{
	static vector<int> sks = { 1, 3, 9, 11, 15, 17, 19, 21, 26, 28, 30, 32, 34, 36, 38, 42, 44, 52, 54, 60, 22, 67, 69, 71, 73, 82 };
	awardItem(40, sks[rand() % sks.size()], true);
}

void CMainState::awardShouJue2()
{
	vector<int> sk2s = { 5, 7, 13, 24, 28, 40, 46, 48, 50, 56, 58, 78, 80, 82, 75, 76, 83, 94, 95, 97, 98, 101, 103, 106 };
	awardItem(40, sk2s[rand() % sk2s.size()], true);
}


void CMainState::awardShouJue3()
{
	vector<int> sk3s = { 96, 100, 104, 107, 108, 109, 102, 105 };
	awardItem(40, sk3s[rand() % sk3s.size()], true);
}



void CMainState::awardShouJue12()
{
	static vector<int> sks =
	{ 
		1, 3, 9, 11, 15, 17, 19, 21, 26, 28, 30, 32, 34,

		5, 7, 13, 24, 28, 40, 46, 48, 50, 56, 58, 78, 80, 82, 75, 76, 83, 94, 95, 97, 98, 101, 103, 106,

		36, 38, 42, 44, 52, 54, 60, 22, 67, 69, 71, 73, 82
	};
	awardItem(40, sks[rand() % sks.size()], true);
}

void CMainState::awardShouJue23()
{
	vector<int> sk2s = 
	{ 
		96, 100, 104, 107, 
		5, 7, 13, 24, 28, 40, 46, 48, 50, 56, 58, 78, 80, 82, 75, 76, 83, 94, 95, 97, 98, 101, 103, 106,
		108, 109, 102, 105,
	};
	awardItem(40, sk2s[rand() % sk2s.size()], true);
}

void CMainState::award125(int r, int maxbookironlv)
{
	if (rand() % 100 > r)
	{
		return;
	}
	r = rand() % 100;
	if (r < 40)
	{
		if (!g_pMainState->awardBookIron(maxbookironlv))
		{
			g_pMainState->awardShouJue1();
		}
	}
	else if (r < 80)
	{
		g_pMainState->awardShouJue12();
	}
	else
	{
		g_pMainState->award5bao();
	}
}


void CMainState::award(int exp, int expbb /* = 0 */, int money /* = 0 */, bool onlyHero /* = false */)
{
	for (int i = m_Friend._friends.size() - 1; i >= 0; --i)
	{
		if (onlyHero && i != m_HeroID)
		{
			continue;
		}
		cPcData* pc = &((cCharacter*)m_Friend._friends[i].obj->m_pIndex)->m_PcData;
		pc->AddExp(exp, expbb);
		if (i == m_HeroID)
		{
			pc->AddMoney(money);
			m_Tags.GetMoneyAndExp(money, exp, 0, expbb, true);
			m_PCHead.UpdatePcExp();
			if (pc->m_FightPetID >= 0)
			{
				m_PCHead.UpdatePetExp();
			}
		}
	}

// 	if (exp)//加成
// 	{
// 		int exprate = g_GlobalValues[14];
// 		exp += exprate * exp / 100;
// 	}
// 	if (expbb)
// 	{
// 		int exprate = g_GlobalValues[14];
// 		expbb += expbb*exprate / 100;
// 	}
// 	if (money)//加成
// 	{
// 		int moneyrate = g_GlobalValues[15];
// 		money += money*moneyrate / 100;
// 	}
// 	cPcData& data = g_pCharacter->m_PcData;
// 	data.AddMoney((int)money, (int)chubeimoney);
// 	data.AddExp(exp, expbb);
// 	m_Tags.GetMoneyAndExp((int)money, exp, (int)chubeimoney, expbb, bNeedTag);
// 
// 	ostringstream oss;
// 	//计算并显示奖励
// 	if (exp)
// 	{
// 		g_pMainState->m_PCHead.UpdatePcExp();
// 	}
// 	if (expbb)
// 	{
// 		if (data.m_FightPetID > -1)
// 		{
// 			g_pMainState->m_PCHead.UpdatePetExp();
// 		}
// 	}
}


void CMainState::awardk(int exp, int money /* = 0 */, bool onlyHero /* = false */)
{
	award(exp * 1000, exp * 1000, money * 1000, onlyHero);
}


void CMainState::awardklv(int exp, int money /* = 0 */, bool onlyHero /* = false */)
{
	int lv = onlyHero ? g_pCharacter->m_PcData.m_Lv : getMaxLv();
	int e, eb, m;
//	for (int i = 0; i < 5; ++i)
	for(int i = m_Friend._friends.size() - 1; i >= 0; --i)
	{
		if (onlyHero && i != m_HeroID)
		{
			break;
		}
// 		if (!m_FightWorkList[i].isExist)
// 		{
// 			continue;
// 		}
// 		cPcData* pc = m_FightWorkList[i].m_pObj->getPcData();
		cPcData* pc = &((cCharacter*)m_Friend._friends[i].obj->m_pIndex)->m_PcData;
		e = 0;
		if (exp)
		{
			e = (exp * 1000 * lv / cct::MaxRoleLv + 8192) * (pc->m_bDuJie + 100) / 100;
		eb = e;
		}
		m = 0;
		if (money)
		{
			m = (money * 1000 * lv / cct::MaxRoleLv + 1024) * (pc->m_faceMood + 100) / 100;
		}

		pc->AddExp(e, e);
		if (i == m_HeroID)
		{
			pc->AddMoney(m);
			m_Tags.GetMoneyAndExp(m, e, 0, e, true);
			m_PCHead.UpdatePcExp();
			if (pc->m_FightPetID >= 0)
			{
				m_PCHead.UpdatePetExp();
			}
		}

	}
// 	if (exp)//加成
// 	{
// 		int exprate = g_GlobalValues[14];
// 		exp += exprate * exp / 100;
// 	}
// 	if (expbb)
// 	{
// 		int exprate = g_GlobalValues[14];
// 		expbb += expbb*exprate / 100;
// 	}
// 	if (money)//加成
// 	{
// 		int moneyrate = g_GlobalValues[15];
// 		money += money*moneyrate / 100;
// 	}
// 	cPcData& data = g_pCharacter->m_PcData;
// 	data.AddMoney((int)money, (int)chubeimoney);
// 	data.AddExp(exp, expbb);
// 	m_Tags.GetMoneyAndExp((int)money, exp, (int)chubeimoney, expbb, bNeedTag);
// 
// 	ostringstream oss;
// 	//计算并显示奖励
// 	if (exp)
// 	{
// 		g_pMainState->m_PCHead.UpdatePcExp();
// 	}
// 	if (expbb)
// 	{
// 		if (data.m_FightPetID > -1)
// 		{
// 			g_pMainState->m_PCHead.UpdatePetExp();
// 		}
// 	}
}




void CMainState::dialogHead(ulong uid, string name, string text)
{
	auto& d = m_Dialog;
	d.Reset();
	g_pMainState->m_Dialog.m_pObj = nullptr;
	d.m_ContextList.m_Name.SetString(name);
	d.m_ContextList.m_Name.UpdateXCenter();
	d.SetHead(uid);
	d.SetString(text);
	d.OnOff(true);
}

void CMainState::dialog(int mid, string name, string text)
{
	ulong uid = 0;
	if (mid < 1000)
	{
		uid = g_pMainState->m_PetDataManager.m_PetList[mid].GetID(0, POS_DIALOG);
	}
	else if (mid < 2000)
	{
		uid = g_pMainState->m_pNpcList[mid - 1000].m_dialog;
	}
	else
	{
		uid = g_pMainState->m_pCharacterDataList[mid - 2000].m_Head[2].m_dialog;
	}
	dialogHead(uid, name, text);
}

void CMainState::dialog(int mid, string text)
{
	ulong uid = 0;
	string name;
	if (mid < 1000)
	{
		uid = g_pMainState->m_PetDataManager.m_PetList[mid].GetID(0, POS_DIALOG);
		name = g_pMainState->m_PetDataManager.m_PetList[mid].m_Name;
	}
	else if (mid < 2000)
	{
		uid = g_pMainState->m_pNpcList[mid - 1000].m_dialog;
		name = g_pMainState->m_pNpcList[mid - 1000].m_name;
	}
	else
	{
		uid = g_pMainState->m_pCharacterDataList[mid - 2000].m_Head[2].m_dialog;
		name = g_pMainState->m_pCharacterDataList[mid - 2000].m_Name;
	}
}

void CMainState::dialog(string text)
{
	if (m_pNowSelect)
	{
		m_pNowSelect->Talk(text);
	}
	else
	{
		dialogHead(m_pNowSelectHead, m_pNowSelectName, text);
	}
}




void CMainState::LockLv(int b /*= 0*/)
{
	g_GlobalValues[2] = b;
	return;
	if (b)
	{
		char str[64];
		sprintf(str, "等级上限解锁为%d级", b);
		m_Channel.AddNewString(str);
	}
}


int CMainState::GetLockLv上限()
{
	return g_GlobalValues[2];
}




void CMainState::SetRanse(int i, int d0, int d1, int d2, int d3, int part/*=0*/)
{
	cPropertyData* pData;
	m_FightWorkList[i].m_pObj->GetPropertyData(pData);
	pData->m_RanSe.m_ranse[part].Set(d0, d1, d2, d3);
	switch (m_FightWorkList[i].m_pObj->m_IndexType)
	{
	case INDEXTYEP_CHARACTER:
		m_ColorManage.Give2(&pData->m_RanSe.m_ranse[part], pData->modeid + 2000);
		return;
	case INDEXTYEP_PET:
		m_ColorManage.Give2(&pData->m_RanSe.m_ranse[part], pData->modeid);
		return;
	default:
		return;
	};
}




int CMainState::CheckInTeam(string name)
{
	for (int i = 0; i < 5; i++)
	{
		if (!m_FightWorkList[i].isExist)continue;
		cObj *obj = m_FightWorkList[i].m_pObj;
		if (obj->m_TrueName.GetString() == name)
		{
			return i;
		}
	}
	return -1;
}
