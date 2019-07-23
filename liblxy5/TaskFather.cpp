#include "_global.h"

void cTaskFather::SetNpc(sTaskMapObj& data, int ret, string name, string map, int modeid, int x, int y, int direction/*=-1*/)
{
	data.m_Npc.Reset();
	data.m_Npc.Set(name, map, modeid, x, y, direction);
	data.m_Stage = ret;
	data.m_pTask = this;
}


bool cTaskFather::CheckNpc(string mapname, string npcname)
{
	if (!g_pMainState->m_Map.m_MapName.compare(mapname))
	{
		//if (!g_pMainState->m_pNowSelect->m_TrueName.GetString().compare(npcname))
		return true;
	}
	return false;
}

// void cTaskFather::AddTriggerDialog(string path, int id, int ret)
// {
// 	g_pMainState->m_TriggerDialog.AddTask(path, id, this, ret);
// }

void cTaskFather::AddTriggerDialogList(vector<string> talklist, int ret)
{
	bool ifirst = false;
	if (talklist.front().empty())
	{
		ifirst = true;
		talklist.erase(talklist.begin());
	}
	if (g_pMainState->m_pNowSelect)
	{
		int size = talklist.size();
		if ((ifirst && size > 1) || (!ifirst && size > 2))
		{
			g_pMainState->setNowSelect();
		}
	}
	vector<sTalkList> dialogList;
	string name;
	if (g_pMainState->m_pNowSelect)
	{
//		name = g_pMainState->m_pNowSelect->GetName();
		name = g_pMainState->m_pNowSelect->m_TrueName.GetString();
	}
	else// if (g_pMainState->m_pNowSelectName.size())
	{
		name = g_pMainState->m_pNowSelectName;
	}
	string iname = g_pHeroObj->m_TrueName.GetString();
	string str;
	forv(talklist, i)
	{
		if (ifirst)
		{
			str = (i % 2) ? name : iname;
		}
		else
		{
			str = (i % 2) ? iname : name;
		}
		dialogList.push_back({ talklist[i], str });
	}
	g_pMainState->m_TriggerDialog.AddTask(this, dialogList, ret);
}

void cTaskFather::AddTriggerObjMap(string mapname, int ret, bool bHuChi)
{
	g_pMainState->m_TriggerObjMap.AddTask(this, ret, mapname, bHuChi);
}

void cTaskFather::AddTriggerObjMap(sNpc* npc, int ret, bool bHuChi)
{
	g_pMainState->m_TriggerObjMap.AddTask(this, ret, *npc, bHuChi);
	if (npc->m_mapname == g_pMainState->m_Map.m_MapName)
	{
		auto& list = g_pMainState->m_TriggerObjMap.m_datalist;
		for (int i = list.size() - 1; i >= 0; --i)
		{
			const auto& np = list[i].m_Npc;
			if (0 == (np.m_name).compare(npc->m_name) && np.m_x == npc->m_x && np.m_y == npc->m_y)
			{
				g_pMainState->m_Map.AddNpc(&list[i]);
				g_pMainState->FindObj();
				return;
			}
		}
		for (int i = list.size() - 1; i >= 0; --i)
		{
			const auto& np = list[i].m_Npc;
			if (0 == (np.m_name).compare(npc->m_name))
			{
				g_pMainState->m_Map.AddNpc(&list[i]);
				g_pMainState->FindObj();
				return;
			}
		}
	}
}

void cTaskFather::AddTriggerObjMap(sTaskMapObj* data)
{
	g_pMainState->m_TriggerObjMap.AddTask(*data);
}



void cTaskFather::AddTriggerObj(sNpc* npc, int ret)
{
	g_pMainState->m_TriggerObj.AddTask(npc->m_name, npc->m_mapname, this, ret);
}

void cTaskFather::AddTriggerObj(string name, string map, int ret, bool bHuChi)
{
	g_pMainState->m_TriggerObj.AddTask(name, map, this, ret, bHuChi);
}

void cTaskFather::AddTriggerObj(string name)
{
	g_pMainState->m_TriggerObj.AddTask(name, g_pMainState->m_Map.m_MapName, this, _next, true);
}


void cTaskFather::AddNpcOne(sTaskMapObj* data, bool needfind)
{
	g_pMainState->m_Map.AddNpc(data, needfind);
}



void cTaskFather::SetJiangLi(int time, int needtag /*= false*/, int money /*= 100*/, int chubei /*= 0*/, int exp /*= 100*/, int expbb /*= 0*/)
{ // chubei 表示金钱有多少是储备金 当chubei为100时  所有的现金都会变成储备金
	int herolv = g_pCharacter->m_PcData.m_Lv;
	if (herolv < 1)herolv = 1;
	if (herolv > 200)herolv = 200;
	int  exp2, expbb2;
	int money2, chubei2;
	if (money)
	{
		money2 = 30 * time* herolv*(money + rand() % 5) / 100;
	}
	else money2 = 0;
	if (chubei)
	{
		chubei2 = money2*chubei / 100;
		money2 -= chubei2;
	}
	else chubei2 = 0;
	if (exp)
	{
		exp2 = 200 * time* herolv*(exp + rand() % 5) / 100;
	}
	else exp2 = 0;


	if (expbb)
	{
		int bblv = g_pCharacter->m_PcData.m_Lv;
		expbb2 = 200 * time* bblv*(expbb + rand() % 5) / 100;
	}
	else expbb2 = 0;
	g_pMainState->award(exp2, expbb2, money2, true/*, chubei2, bool(needtag)*/);
}
void cTaskFather::SetJiangLi2(int exp, int money/*=0*/, int chubei/*=0*/, int petexp/*=0*/, bool needtag/*=true*/)
{
	g_pMainState->award(exp, petexp, money, true/*, chubei, needtag*/);
}
void cTaskFather::SetJiangLiItem(int id, int type, int num /*= 1*/)
{
	g_pMainState->awardItem(type, id, num, true);
	return;
	sItem2 item;
	item.m_Num = num;
	item.Set(type, id);
	g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
	g_pMainState->m_Tags.GetItem(item.GetName());
}

void cTaskFather::AddTriggerGive(string name, int type, int id, int ret, bool bHuChi)
{
	g_pMainState->m_TriggerGive.AddTask(name, id, type, this, ret, bHuChi);
}

void cTaskFather::AddTag(string text, int time /*= 500*/)
{
	g_pMainState->m_Tags.Add(text, time);
}

void cTaskFather::getTag(string text, int time /*= 500*/)
{
	g_pMainState->m_Tags.Add(text + " +1", time);
}

void cTaskFather::lostTag(string text, int time /*= 500*/)
{
	g_pMainState->m_Tags.Add(text + " -1", time);
}

void cTaskFather::AddTriggerFightTurn(int ret)
{
	g_pMainState->m_TriggerFightTurn.AddTask(this, ret);
}
void cTaskFather::AddTriggerFightSuccess(int ret)
{
	g_pMainState->m_TriggerFightSuccess.AddTask(this, ret);
}
void cTaskFather::AddTriggerFightFalse(int ret)
{
	g_pMainState->m_TriggerFightFail.AddTask(this, ret);
}

void cTaskFather::AddTriggerFightEscape(int ret)
{
	g_pMainState->m_TriggerFightEscape.AddTask(this, ret);
}

void cTaskFather::UpdateJob(string context, string title, int time, int ret)
{
	sJob job;
	job.m_Context = context;
	job.m_pTask = this;
	job.m_Stage = ret;
	job.m_Time = time;
	job.m_Title = title;
	g_pMainState->m_Job.AddaJob(job);
}
void cTaskFather::UpdateJob(string context, string title)
{
	sJob job;
	job.m_Context = context;
	job.m_pTask = this;
	job.m_Stage = -1;
	job.m_Time = 0;
	job.m_Title = title;
	g_pMainState->m_Job.AddaJob(job);
}
void cTaskFather::RemoveTriggerObj()
{
	return g_pMainState->m_TriggerObj.ReMove(this);
}

void cTaskFather::RemoveTriggerGive()
{
	return g_pMainState->m_TriggerGive.ReMove(this);
}

void cTaskFather::RemoveTriggerObjMap(int ret)
{
	g_pMainState->m_TriggerObjMap.ReMove(this, ret);
}

void cTaskFather::RemoveTriggerObjMap(int x, int y)
{
	g_pMainState->m_TriggerObjMap.ReMove(this, x, y);
}

void cTaskFather::AddTriggerLv(int ret, int num)
{
	g_pMainState->m_Triggerlv.AddTask(this, ret, num);
}

void cTaskFather::AddTriggerTalkList(string path, int id, int ret)
{
	g_pMainState->m_TriggerDialog.AddTask(path, id, this, ret);
}

void cTaskFather::AddTriggerFightStart(int ret)
{
	g_pMainState->m_TriggerFightStart.AddTask(this, ret);
}

void cTaskFather::UnInviteAll()
{
	for (int i = 1; i < 5; i++)
	{
		g_pMainState->m_Friend.UnInvite(i);
	}
}

void cTaskFather::AddChannel(string text, string name, int channel)
{
	g_pMainState->m_Channel.AddNewString(text, name, channel);
}

void cTaskFather::NowNpcTalk(string text)
{
	g_pMainState->m_pNowSelect->Talk(text);
}

void cTaskFather::RemoveTriggerSuccess()
{
	g_pMainState->m_TriggerFightSuccess.ReMove(this);
}
void cTaskFather::RemoveTriggerFalse()
{
	g_pMainState->m_TriggerFightFail.ReMove(this);
}
void cTaskFather::RemoveTriggerEscape()
{
	g_pMainState->m_TriggerFightEscape.ReMove(this);
}

void cTaskFather::DialogTalkObj(string text, cObj* p)
{
	g_pMainState->m_Dialog.TalkObj(text, p);
}

void cTaskFather::DialogTalkNObj(string text)
{
	g_pMainState->m_Dialog.TalkNObj(text);
}

// void cTaskFather::FollowLvForTask(int id, int lv)
// {
// 	g_pMainState->m_FightList[id].m_pData->FollowLvForObj(lv);
// }

bool cTaskFather::CheckHeroMoney(int money, bool bTag)
{//检测角色是否有足够的钱
	if (g_pCharacter->m_PcData.m_Money[0] + g_pCharacter->m_PcData.m_Money[2] < money)
	{
		if (bTag)
		{
			ostringstream oss;
			oss << "金钱低于" << money << "两";
			g_pMainState->m_Tags.Add(oss.str());
		}
		return false;
	}
	return true;
}

void cTaskFather::GetPet(string name, sShangPinPet* pet, int stronglv)
{
	int teamid = -1;
	for (int i = 0; i < 5; i++)
	{
		if (g_pMainState->m_FightWorkList[i].m_pObj->m_TrueName.GetString() == name)
		{
			teamid = i;
			break;
		}
	}
	int friendid = g_pMainState->m_Friend.FindFriend(name);
	if (friendid > -1)
	{
		sFriendList& lis = g_pMainState->m_Friend.m_FriendList[friendid];
		if (lis.m_BBList.size() > 7)return;
		lis.m_BBList.push_back(*pet);
		lis.m_FightBB = lis.m_BBList.size() - 1;
	}
	if (teamid > -1)
	{
		cPet* pet2;
		pet2 = new cPet;
		pet2->Set(pet, stronglv);
//		g_pMainState->GivePcAPet(teamid, pet2);
	}
}

void cTaskFather::GetPet2(sShangPinPet* pet, int stronglv)
{
	cPet* pet2;
	pet2 = new cPet;
	pet2->Set(pet, stronglv);
//	g_pMainState->GivePcAPet(g_pMainState->m_HeroID, pet2);
	g_pCharacter->m_PcData.AddPet(pet2);
}

void cTaskFather::SetMusic(string name /*= ""*/)
{
	return;
	if (name == "")
	{
		name = "战斗BOSS";
	}
	g_pMainState->m_Mp3.Load(name);
}

void cTaskFather::AutoGetPet(string name, int id, int id1, int id2, int id3)
{
	int idd = g_pMainState->m_Friend.FindFriend(name);
	sFriendList* plist = &g_pMainState->m_Friend.m_FriendList[idd];
	sShangPinPet item;
	item.LoadEasy(id);
	plist->m_BBList.push_back(item);
	if (id1 > -1)
	{
		item.LoadEasy(id1);
		plist->m_BBList.push_back(item);
	}
	if (id2 > -1)
	{
		item.LoadEasy(id2);
		plist->m_BBList.push_back(item);
	}
	if (id3 > -1)
	{
		item.LoadEasy(id3);
		plist->m_BBList.push_back(item);
	}
	if (plist->m_BBList.size())
	{
		plist->m_FightBB = plist->m_BBList.size() - 1;
	}
}

cPropertyData* cTaskFather::AddPetEnemyF(int hp, ePetID id, int lv, string name, bool bOur /*= false*/, int pos)
{
	if (lv < 0) lv = g_pCharacter->m_PcData.m_Lv;
//	cPropertyData* p;
	auto p = g_pMainState->AddEnemy(id, lv, name, nullptr/*, -1*/, pos, bOur);
//	g_pMainState->m_FightWorkList[k].m_pObj->GetPropertyData(p);
// 	if (!p->m_JinJieNum.m_JinJieNum)
// 	{
// 		p->SetJinJie(ccm::get()->getJinjie(lv));
// 	}
	if (hp > 0)
	{
		p->HPMax.SetData(hp);
		p->FillHpMp();
	}
	return p;
}

cPropertyData* cTaskFather::Add变身EnemyF(int hp, ePetID id, int lv, eMengPai mp, string name /*= ""*/, bool bOur /*= 0*/, int pos /*= -1*/)
{
//	cPropertyData* p;
	if (lv < 0) lv = g_pCharacter->m_PcData.m_Lv;
	mp = (eMengPai)cct::getMenpai(mp);
// 	if (mp == eMP_随机)
// 	{
// 		mp = g_pMainState->m_ZhuXian.getMenPaiFromRand();
// 	}
	auto p = g_pMainState->AddEnemy(id, lv, mp, name, nullptr, -1, bOur, pos);
//	if (k == -1)return 0;
//	g_pMainState->m_FightWorkList[k].m_pObj->GetPropertyData(p);
// 	if (!p->m_JinJieNum.m_JinJieNum)
// 	{
// 		p->SetJinJie(ccm::get()->getJinjie(lv));
// 	}
	if (hp > 0 && p)
	{
		p->HPMax.SetData(hp);
		p->FillHpMp();
	}
	return p;
}

cPropertyData* cTaskFather::AddPCEnemyF(int hp, int id, sZiZhi* zz, int lv, eMengPai mp, string name /*= -1*/, int weapontype /*= -1*/, int weaponid /*= -1*/, bool bOur /*= false*/, int pos)
{
//	cPropertyData* p;
	sItem2 item;
	sItem2* pitem = 0;
	if (weaponid < 0)
	{
		int typelist[2];
		GetWeaponType((id >= 2000) ? (id - 2000) : id, typelist[0], typelist[1]);
		weapontype = typelist[rand() % 2];
		if (typelist[1] == -1)
			weapontype = typelist[0];
		weaponid = g_pMainState->m_ItemManage.GetIDByLv(weapontype, lv);
	}
	item.m_Num = 1;
	item.Set(weapontype, weaponid);
	pitem = &item;

	if (lv < 0) lv = g_pCharacter->m_PcData.m_Lv;
	mp = (eMengPai)cct::getMenpai(mp);
// 	if (mp == eMP_随机)
// 	{
// 		mp = g_pMainState->m_ZhuXian.getMenPaiFromRand();
// 	}
	auto p  = g_pMainState->AddEnemy(id, lv, mp,name,  /*&g_pMainState->m_ZhuXian.getAddPointFromMenpai(mp), zz, pitem, -1, */ nullptr, -1, pos, bOur);
//	if (k < 0)return 0;
//	g_pMainState->m_FightWorkList[k].m_pObj->GetPropertyData(p);
	if (hp > 0 && p)
	{
		p->HPMax.SetData(hp);
		p->FillHpMp();
	}
	return p;
}



cPetData* cTaskFather::AddEnemy(int hp, int modeid, int lv, string name /*= ""*/, sAddPoint* ap /*= nullptr*/, int pos /*= -1*/, bool our /*= false*/)
{
	auto p = g_pMainState->AddEnemy(modeid, lv, name, ap, pos, our);
	if (hp > 0)
	{
		p->HPMax.SetData(hp);
		p->FillHpMp();
	}
	return p;
}

cPcData* cTaskFather::AddEnemy(int hp, int modeid, int lv, eMengPai mengpaid, string name /*= ""*/, sAddPoint* addpoint /*= nullptr*/, int weaponLv /*= -1*/, int pos /*= -1*/, bool our /*= false*/)
{
	auto p = g_pMainState->AddEnemy(modeid, lv, mengpaid, name, addpoint, weaponLv, pos, our);
	if (hp > 0)
	{
		p->HPMax.SetData(hp);
		p->FillHpMp();
	}
	return p;
}




void cTaskFather::RemoveTriggerObjMap2(cObj* pObj)
{
	int x = pObj->GetX() / 20;
	int y = (g_pMainState->m_Map.m_pMap->m_Height - pObj->GetY()) / 20;
	RemoveTriggerObjMap(x, y);
}

void cTaskFather::AddJob(string title, string text)
{
	sJob job;
	job.m_Title = title;
	job.m_Context = text;
	job.m_pTask = this;
	g_pMainState->m_Job.AddaJob(job);
}

void cTaskFather::readyFightAndSucces()
{
	g_StateType = STATE_FIGHT;
	AddTriggerFightSuccess(_next);
}

void cTaskFather::clearSay(bool onlyEnemy /* = true */)
{
	for (int i = 10; i < 20; ++i)
	{
		if (g_pMainState->m_FightWorkList[i].m_pObj)
		{
			g_pMainState->m_FightWorkList[i].m_pObj->m_ShowTime = 0;
		}
	}
	if (onlyEnemy)
	{
		return;
	}
	for (int i = 0; i < 10; ++i)
	{
		if (g_pMainState->m_FightWorkList[i].m_pObj)
		{
			g_pMainState->m_FightWorkList[i].m_pObj->m_ShowTime = 0;
		}
	}
}
