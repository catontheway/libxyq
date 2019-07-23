#include "_global.h"

void cTaskJuQing::UpdateJob2(string text)
{
	UpdateJob(text, "主线");
}

void cTaskJuQing::UpdateJob2(int id)
{
	if (id == -1)
		g_pMainState->m_Job.ReMoveJob(this);
	else
		UpdateJob2(m_Textlist[id]);
}


void cTaskJuQing::RemoveNpc(int id, bool needfind /*= false*/)
{
	g_pMainState->m_Map.RemoveNpc(m_Textlist[id], needfind);
}



void cTaskJuQing::TalkList(int textid, int nextname, int nextmap, int jobtext, int ret, int dialogret)
{
	AddTriggerDialog2(textid, dialogret);
	if (nextname > -1)
		AddTriggerObj2(nextname, nextmap, ret);
	UpdateJob2(jobtext);
}


void cTaskJuQing::SetDialogList(int id)
{
	g_pMainState->SetDialogList(g_pMainState->FindObjByName(m_Textlist[id]));
}




void cTaskJuQing::AddChannel2(int id)
{
	AddChannel(m_Textlist[id]);
}

void cTaskJuQing::AddTriggerObj2(int name, int mapname, int ret, bool bHuChi)
{
	if (name == -1)
		RemoveTriggerObj();
	else
		AddTriggerObj(m_Textlist[name], m_Textlist[mapname], ret, bHuChi);
}

void cTaskJuQing::AddTriggerDialog2(int id, int ret)
{
//	AddTriggerDialog(SetUpPathJuQing(m_Textlist[0]), id, ret);
}

void cTaskJuQing::Un邀请(string name)
{
	g_pMainState->m_Friend.UnInvite(name);
}

// void cTaskJuQing::FollowLvForTask(int id, int lv)
// {
// 	g_pMainState->m_FightList[id].m_pData->FollowLvForObj(lv);
// }




void cTaskJuQing::SetChapter(int chapter)
{
	if (chapter == m_Chapter)return;
	m_Chapter = chapter;
	m_bInit = false;
	Init();
}

void cTaskJuQing::Save(ofstream& File)
{
	File << "\n";
	File << m_Chapter << " ";
}

void cTaskJuQing::Load(ifstream& File)
{
	File >> m_Chapter;
	m_bInit = false;
	//	m_bInit2 = false;
	Init();
}

std::string cTaskJuQing::SetUpPathJuQing(string str)
{
	string path1/* = g_pathData*/;
	//	path1 += "任务//";
	path1 += m_AutoPath;
	path1 += "//";
	path1 += str;
	path1 += ".txt";
	// 	if (m_AutoPath == "剧情")
	// 	{
	// 		return g_strJuqingPath + str + ".txt";
	// 	}
	return path1;
}

cPropertyData* cTaskJuQing::AddPetEnemy2(int hp, ePetID id, int lv, int name /*= -1*/, bool bOur /*= false*/, int pos)
{
	cPropertyData* p;
	int k = AddPetEnemy(id, lv, name, bOur, pos);
	g_pMainState->m_FightWorkList[k].m_pObj->GetPropertyData(p);
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


// sAddPoint cTaskJuQing::getAddPointFromMenpai(eMengPai e)
// {
// 	sAddPoint a;
// 	switch (e)
// 	{
// 	case eMP_无:
// 	case eMP_大唐官府:
// 	case eMP_狮驼岭:
// 		a = g_addPointAtk;
// 		break;
// 	case eMP_方寸山:
// 	case eMP_天宫:
// 		a.Set(0, 0, 3, 0, 2);
// 		break;
// 	case eMP_魔王寨:
// 	case eMP_东海龙宫:
// 		a = g_addPointMag;
// 		break;
// 	case eMP_五庄观:
// 		a.Set(3, 0, 0, 0, 2);
// 		break;
// 	case eMP_化生寺:
// 	case eMP_盘丝岭:
// 	case eMP_阴曹地府:
// 	case eMP_女儿村:
// 	case eMP_普陀山:
// 		a.Set(0, 3, 0, 0, 2);
// 		break;
// 	default:
// 		break;
// 	}
// 	return a;
// }
// 
// eMengPai cTaskJuQing::getMenPaiFromRand()
// {
// 	eMengPai mp = eMengPai(rand() % 12);
// 	if (mp == eMP_女儿村 || mp == eMP_阴曹地府 || mp == eMP_盘丝岭)
// 	{
// 		mp = eMengPai(rand() % 12);
// 	}
// 	return mp;
// }

cPropertyData* cTaskJuQing::Add变身Enemy2(int hp, ePetID id, int lv, eMengPai mp, int name /*= -1*/, bool bOur /*= false*/, int pos)
{
	cPropertyData* p;
	mp = (eMengPai)cct::getMenpai(mp);
// 	if (mp == eMP_随机)
// 	{
// 		mp = getMenPaiFromRand();
// 	}
// 	m_AddPoint = getAddPointFromMenpai(mp);
	int k = AddPCPetEnemy(id, lv, mp, name, bOur, pos);
	if (k == -1)return 0;
	g_pMainState->m_FightWorkList[k].m_pObj->GetPropertyData(p);
// 	if (!p->m_JinJieNum.m_JinJieNum)
// 	{
// 		p->SetJinJie(ccm::get()->getJinjie(lv));
// 	}
	if (hp > 0)
	{
		p->HPMax.AddDataAdd(hp);
		p->FillHpMp();
	}
	return p;
}

cPropertyData* cTaskJuQing::AddPCEnemy2(int hp, int id, sZiZhi* zz, int lv, eMengPai mp, int name /*= -1*/, int weapontype /*= -1*/, int weaponid /*= -1*/, bool bOur /*= false*/, int pos)
{
	int i = AddPCEnemy(id, zz, lv, mp, name, weapontype, weaponid, bOur, pos);
	cPropertyData* p = g_pMainState->m_FightWorkList[i].m_pObj->getPropertyData();
	if (hp > 0)
	{
		p->HPMax.SetData(hp);
		p->FillHpMp();
	}
	return p;
// 	cPropertyData* p;
// 	mp = (eMengPai)cct::getMenpai(mp);
// 	if (mp == eMP_随机)
// 	{
// 		mp = getMenPaiFromRand();
// 	}
// 	m_AddPoint = getAddPointFromMenpai(mp);
	if (weapontype < 0 || weaponid < 0)
	{
		int typelist[2];
		GetWeaponType((id >= 2000) ? (id - 2000) : id, typelist[0], typelist[1]);
		weapontype = typelist[rand() % 2];
		if (typelist[1] == -1)
			weapontype = typelist[0];
		weaponid = g_pMainState->m_ItemManage.GetIDByLv(weapontype, lv);
	}
	int k = AddPCEnemy(id, zz, lv, mp, name, weapontype, weaponid, bOur, pos);

	g_pMainState->m_FightWorkList[k].m_pObj->GetPropertyData(p);

	if (hp > 0)
	{
		p->HPMax.SetData(hp);
		p->FillHpMp();
	}
	return p;
}



void cTaskJuQing::AddTag(int str, int time/*=500*/)
{
	g_pMainState->m_Tags.Add(m_Textlist[str], time);
}

void cTaskJuQing::LockMap(int name/*=-1*/)
{
	switch (name)
	{
	case -1:
		g_pMainState->m_Map.SetLock("");
		break;
	case 0:
	case 1:
		g_pMainState->m_Map.SetLock(name);
		break;
	default:
		g_pMainState->m_Map.SetLock(m_Textlist[name]);
		break;
	}

}

void cTaskJuQing::AddRangeMap(int mapname, int x, int y, int range, int ret)
{
	sTriggerRange data;
	data.Set(m_Textlist[mapname], x, y, range, this, ret);
	g_pMainState->m_Map.AddTriggerRange(data);
}

sItem2* cTaskJuQing::FindItem(int Type, int id)
{
	for (int i = 0; i < 60; i++)
	{
		sItem2* pItem = &g_pCharacter->m_PcData.m_Items[i];
		if (pItem->m_Num)
			if (pItem->GetID() == id)
				if (pItem->GetType() == Type)
					return pItem;
	}
	return 0;
}

void cTaskJuQing::AddFriend(int i)
{
	g_pMainState->m_Friend.AddFriend(m_Textlist[i]);
}

void cTaskJuQing::AddTriggerObjMap2(int name, int mapname, int modeid, int x, int y, int direction, int ret /*= -1*/, int jinjie)
{

	sTaskMapObj obj;
	obj.m_pTask = this;
	obj.m_Stage = ret;
	obj.m_Npc.Set(m_Textlist[name], m_Textlist[mapname], modeid, x, y, direction, jinjie);
	AddTriggerObjMap(&obj);
}



void cTaskJuQing::Select(int title, int name, int cancelret, int select0, int ret0, int select1, int ret1, int select2, int ret2, int select3, int ret3)
{
	if (select3 > -1)
	{
		g_pMainState->m_TriggerDialog.AddSelect(this, m_Textlist[title], m_Textlist[name], cancelret,
			m_Textlist[select0], ret0,
			m_Textlist[select1], ret1,
			m_Textlist[select2], ret2,
			m_Textlist[select3], ret3
			);
	}
	else
		if (select2 > -1)
		{
		g_pMainState->m_TriggerDialog.AddSelect(this, m_Textlist[title], m_Textlist[name], cancelret,
			m_Textlist[select0], ret0,
			m_Textlist[select1], ret1,
			m_Textlist[select2], ret2
			);
		}
		else
		{
			g_pMainState->m_TriggerDialog.AddSelect(this, m_Textlist[title], m_Textlist[name], cancelret,
				m_Textlist[select0], ret0,
				m_Textlist[select1], ret1
				);
		}
	g_pMainState->m_Dialog.m_bRetSelect = true;
}

cPropertyData* cTaskJuQing::GetPetData(int id)
{
	cPropertyData* p;
	g_pMainState->m_FightWorkList[id].m_pObj->GetPropertyData(p);
	return p;
}

int cTaskJuQing::GetCharacterID(string name)
{
	for (int i = 0; i < 5; i++)
	{
		if (g_pMainState->m_FightWorkList[i].m_pObj->m_TrueName.GetString() == name)
		{
			return i;
		}
	}
	return -1;
}

void cTaskJuQing::Invite(string name, int fighterid)
{
	g_pMainState->m_Friend.Invite(name, fighterid);
}

int cTaskJuQing::AddPetEnemy(ePetID id, int lv, int name/*=""*/, bool bOur, int pos)
{
	string namet;
	if (name == -1)namet = "";
	else namet = m_Textlist[name];
	return g_pMainState->AddEnemy(id, lv, namet, &m_AddPoint/*, -1*/, pos, bOur)->m_IDinFightWorkList;
}

int cTaskJuQing::AddPCPetEnemy(ePetID id, int lv, eMengPai mp, int name /*= ""*/, bool bOur, int pos)
{
	string namet;
	if (name == -1)namet = "";
	else namet = m_Textlist[name];
	return g_pMainState->AddEnemy(id, lv, mp, namet, &m_AddPoint, -1, bOur, pos)->m_IDinFightWorkList;
}

int cTaskJuQing::AddPCEnemy(int id, sZiZhi* zz, int lv, eMengPai mp, int name /*= ""*/, int weapontype, int weaponid, bool bOur, int pos)
{
	string namet;
	if (name == -1)namet = "";
	else namet = m_Textlist[name];
	int wlv = -1;
	if (weaponid >= 0 && weapontype >= 0)
	{
		wlv = g_pMainState->m_ItemManage.GetlvByID(weapontype, weaponid);
	}
	return g_pMainState->AddEnemy(id, lv, mp, namet, &m_AddPoint, /*zz, 0, -1, -1*/wlv, pos, bOur)->m_IDinFightWorkList;
// 	if (weaponid == -1)
// 	{
// 
// 	}
// 	else
// 	{
// 		sItem2 item;
// 		item.Set(weapontype, weaponid);
// 		return g_pMainState->AddPCEnemy(namet, id, lv, &m_AddPoint, zz, mp, &item, -1, -1, pos, bOur);
// 	}
}



void cTaskJuQing::Init()
{
	if (m_Chapter == -1)return;
	if (m_bInit)return;
	m_bInit = true;
	return;
	ifstream File;
	string data;
	File.open(SetUpPathJuQing("index"));
	if (!File)
		ERRBOX;
	for (int i = 0; i <= m_Chapter; i++)
	{
		getline(File, data);
	}
	File.close();
	//}
	File.open(SetUpPathJuQing(data));
	if (!File)
		ERRBOX;
	int num;
	File >> num;
	getline(File, data);
	m_Textlist.resize(num);
	for (int i = 0; i < num; i++)
	{
		getline(File, data);
		m_Textlist[i] = data;
	}
	File.close();
	//	if (m_type != TASK_TYPE_ZHUXIAN)
	{
		m_AddPoint.Set(4, 0, 0, 1, 0);
		return;
	}
	// 	if(m_Chapter == 0)
	// 	{
	// 		m_Textlist[1] = "宠物仙子";
	// 		m_Textlist[10] = "我这里出售各种召唤兽,这次就免费送你吧,你已经5级了,现在东海湾的怪已经不是你的对手了,去东海海底练级吧";
	// 		m_Textlist[68] = toString("升到%d级", 25);
	// 	}
	// 	else if (m_Chapter == 5)
	// 	{
	// 
	// 	}
	// 	
}