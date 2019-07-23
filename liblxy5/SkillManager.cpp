#include "_global.h"
#include "_txt.h"

//#define  ccc_checkwas

static int getTargetNum(eSkill e)
{
	switch (e)
	{
	case eSkill::破血狂攻:
		return 2;
	case eSkill::奔雷咒:
	case eSkill::泰山压顶:
	case eSkill::水漫金山:
	case eSkill::地狱烈火:
	case eSkill::剑荡四方:
		return 3;
	case eSkill::月光:
		return 4;
	case eSkill::天降灵葫:
		return 5;
	case eSkill::吸星大法xx:
		return 9;
	case eSkill::四海升平:
	case eSkill::玉清诀:
	case eSkill::晶清诀:
	case eSkill::绝幻魔音:
	case eSkill::魔兽之印:
	case eSkill::圣灵之甲:
	case eSkill::啸风诀:
	case eSkill::罗汉金钟:
	case eSkill::河东狮吼:
	case eSkill::碎甲术:
	case eSkill::停陷术:
	case eSkill::慈航普渡:
		return 10;
	}
	return 1;
}


bool cSkillManager::Init()
{
	m_MengPaiManager.Init();
	if (m_bInit)return true;
	m_bInit = true;
// 	ifstream File;
// 	ostringstream oss;
// 	oss << g_pathData << "技能//召唤兽技能.txt";
// // 	oss.str("");
// // 	oss << g_strSkillPath << "召唤兽技能.txt";
// 	File.open(oss.str());
// 	if (!File)ERRBOX;
// 	int dustbin;
// 	string dustbin2str;
// 	File >> dustbin;
// 	if (c_NumPetSkill != dustbin)ERRBOX;
// 	for (int i = 0; i < c_NumPetSkill; i++)
// 	{
// 		sSkill& skill = m_PetSkillList[i];
// 		File >> skill.m_Id;
// 		File >> skill.m_Name;
// 		File >> skill.m_BigHead;
// 		File >> skill.m_SmallHead;
// 		File >> skill.m_SkillType;
// 		cct::get()->pushBabySkillHead(string("BB技能_") + skill.m_Name + "大", skill.m_BigHead);
// 		cct::get()->pushBabySkillHead(string("BB技能_") + skill.m_Name + "小", skill.m_SmallHead);
// 		if (skill.m_SkillType == 7)
// 		{
// 
// 			File >> skill.m_NumUnCompatible;
// 			for (int j = 0; j < skill.m_NumUnCompatible; j++)
// 			{
// 				int uncompatibleid;
// 				File >> uncompatibleid;
// 				skill.m_UnCompatible.push_back(uncompatibleid);
// 			}
// 		}
// 		else
// 		{
// 			skill.m_NumUnCompatible = 0;
// 			File >> skill.m_Sound;
// 
// 
// 			File >> skill.m_EffectType;
// 			File >> skill.m_MagicID;
// 			File >> skill.m_MagicPos;
// 			File >> skill.m_TargetNum;
// 			File >> skill.m_TargetNumOffset;
// 
// 			if (skill.m_Sound > 0)
// 			{
// 				cct::get()->pushBabySkillHead(string("BB技能_") + skill.m_Name + "声音", skill.m_Sound);
// 			}
// 			cct::get()->pushBabySkill(string("BB技能_") + skill.m_Name + "动画", skill.m_MagicID);
// 			
// 		}
// 		File >> skill.m_Text;
// 		if (7 != skill.m_SkillType)
// 			File >> skill.m_tCost;
// 		//读取召唤兽技能声音,比如雷击,泰山压顶等
// 		
// 		
// 	}
// 	File.close();

	cWasFile was;
	const auto& ps = ctt::getSkillPassives();
	forv(ps, k)
	{
		const auto& p = ps[k];
		auto& skill = m_PetSkillList[(int)p.e - c_2000];
		skill.m_Id = (int)p.e - c_2000;
		skill.m_Name = p.name;
		skill.m_BigHead = p.big;
		skill.m_SmallHead = p.small;
		skill.m_SkillType = 7;
		skill.m_NumUnCompatible = p.covers.size();
		for (int i = 0; i < skill.m_NumUnCompatible; ++i)
		{
			skill.m_UnCompatible.push_back((int)p.covers[i] - c_2000);
		}
		skill.m_Text = p.desc;

#ifdef ccc_checkwas
		was.Load(skill.m_SmallHead);
		was.Load(skill.m_BigHead);
#endif
	}


// 	oss.str("");
// 	oss << g_pathData << "技能//辅助技能.txt";
// // 	oss.str("");
// // 	oss << g_strSkillPath << "辅助技能.txt";
// 	File.open(oss.str());
// 	if (!File)ERRBOX;
// 	File >> dustbin;
// 	if (c_NumFuZhu != dustbin)
// 	{
// 		ERRBOX;
// 	}
// 	for (int i = 0; i < c_NumFuZhu; i++)
// 	{
// 		sSkill& skill = m_FuZhuSkillList[i];
// 		File >> skill.m_Id;
// 		File >> skill.m_Name;
// 		File >> skill.m_BigHead;
// 		File >> skill.m_SmallHead;
// 		getline(File, skill.m_Text);
// 		getline(File, skill.m_Text);
// 		cct::get()->pushFuzhuSkillHead(string("辅助技能_") + skill.m_Name + "大", skill.m_BigHead);
// 		cct::get()->pushFuzhuSkillHead(string("辅助技能_") + skill.m_Name + "小", skill.m_SmallHead);
// 	}
// 	File.close();

	const auto& fzs = ctt::getSkillFuzhus();
	forv(fzs, k)
	{
		if (k >= c_NumFuZhu)
		{
			continue;
		}
		sSkill& skill = m_FuZhuSkillList[k];
		const auto& fz = fzs[k];
		skill.m_Id = (int)fz.e;
		skill.m_Name = fz.name;
		skill.m_BigHead = fz.big;
		skill.m_SmallHead = fz.small;
		skill.m_Text = fz.desc;
#ifdef ccc_checkwas
		was.Load(skill.m_SmallHead);
		was.Load(skill.m_BigHead);
#endif
	}


// 	oss.str("");
// 	oss << g_pathData << "技能//特技.txt";
// // 	oss.str("");
// // 	oss << g_strSkillPath << "特技.txt";
// 	File.open(oss.str());
// 	if (!File)ERRBOX;
// 
// 	File >> dustbin;
// 	m_SpecialSkill.resize(dustbin);
// 	for (int i = 0; i < dustbin; i++)
// 	{
// 		sSkill& skill = m_SpecialSkill[i];
// 		File >> skill.m_Id;
// 		File >> skill.m_Name;
// 		File >> skill.m_BigHead;
// 		File >> skill.m_SmallHead;
// 		File >> skill.m_Cost;
// 		oss.str("");
// 		oss << skill.m_Cost;
// 		skill.m_tCost = oss.str();
// 		File >> skill.m_SkillType;
// 		File >> skill.m_MagicID;
// 		File >> skill.m_MagicPos;
// 		File >> skill.m_TargetNum;
// 		skill.m_TargetNumOffset = 0;
// 		getline(File, skill.m_Text);
// 		if (skill.m_Id == 25)
// 		{
// 			// 罗汉 增益
// 			skill.m_EffectType = 1;
// 		}
// 
// 		cct::get()->pushSpecialSkillHead(string("特技_") + skill.m_Name + "大", skill.m_BigHead);
// 		cct::get()->pushSpecialSkillHead(string("特技_") + skill.m_Name + "小", skill.m_SmallHead);
// 		cct::get()->pushSpecialSkill(string("特技_") + skill.m_Name + "动画", skill.m_MagicID);
// 	}
// 	File.close();

	auto cb = [](string& cost, const string& costhpmp, int costvalue)
	{
		if (costhpmp.find("CostHpMax") != string::npos)
		{
			cost = toString("%d%%最大气血", costvalue);
		}
		else if (costhpmp.find("CostHpFix") != string::npos)
		{
			cost = toString("%d气血", costvalue);
		}
		else if (costhpmp.find("CostHp") != string::npos)
		{
			cost = toString("%d%%当前气血", costvalue);
		}
		else if (costhpmp.find("CostLv") != string::npos)
		{
			cost = toString("(等级+%d)魔法", costvalue);
		}
		else if (costhpmp.find("MPS") != string::npos)
		{
			cost = toString("(%d*人数)魔法", costvalue);
		}
		else if (costvalue > 0)
		{
			cost = toString("%d魔法", costvalue);
		}
		else cost = "无";
	};

	for (int i = 0; i < c_SkillNum; ++i)
	{
		sSkill* ss = GetSkill(i);
		cb(ss->m_tCost, ss->m_tCostHpMp, ss->m_Cost);
		if (ss->m_Id == (int)eSkill::断岳势 || ss->m_Id == (int)eSkill::惊涛怒)
		{
			ss->m_tCost += ",1点战意";
		}
		else if (ss->m_Id == (int)eSkill::天崩地裂)
		{
			ss->m_tCost += ",2点战意";
		}
		else if (ss->m_Id == (int)eSkill::翻江搅海)
		{
			ss->m_tCost += ",3点战意";
		}
	}


	const auto& tskills = ctt::getSkills();
	m_SpecialSkill.resize(50);
	forv(tskills, k)
	{
		const auto& ts = tskills[k];
		int id = (int)ts.e;
		if (id < 1000)
		{
			continue;
		}
		sSkill& skill = (id >= c_3000) ? m_SpecialSkill[id - c_3000] : m_PetSkillList[id - c_2000];
//		if (id >= c_3000)
		{
// 			sSkill& skill = m_SpecialSkill[id - c_3000];
// 			skill.m_Id = id - c_3000;
// 			skill.m_Name = ts.name;
// 			skill.m_BigHead = ts.big;
// 			skill.m_SmallHead = ts.small;
// 			skill.m_Cost = ts.costvalue;
// 			skill.m_tCostHpMp = skill.m_tCost = ts.descCost;
// 			skill.m_SkillType = ts.useType;
// 			skill.m_MagicID = ts.uAct;
// 			skill.m_MagicPos = ts.positiony;
// 			skill.m_TargetNum = getTargetNum(ts.e);
// 			skill.m_TargetNumOffset = 0;
// 			skill.m_Text = ts.desc;
// 			cb(skill.m_tCost, skill.m_tCostHpMp, skill.m_Cost);
// 		}
// 		else if (id >= c_2000)
// 		{
// 			sSkill& skill = m_PetSkillList[id - c_2000];
			skill.m_Id = (int)ts.e - c_2000;
			skill.m_Name = ts.name;
			skill.m_BigHead = ts.big ? ts.big : 0xADEE4E4D;
			skill.m_SmallHead = ts.small;
			skill.m_SkillType = ts.useType;
			
			skill.m_NumUnCompatible = 0;
			skill.m_State = ts.state;
			skill.m_Sound = ts.sound;


			skill.m_EffectType = (int)ts.buffType;
			skill.m_MagicID = ts.uAct;
			skill.m_MagicPos = ts.positiony;
			skill.m_Cost = ts.costvalue;
			skill.m_TargetNum = getTargetNum(ts.e);;
			skill.m_TargetNumOffset = 0;

			skill.m_Text = ts.desc;
			skill.m_tCostHpMp = skill.m_tCost = ts.descCost;

			if (id >= c_3000)
			{
				skill.m_tCost = toString("%d愤怒", ts.costvalue);
			}
			else
			{
				cb(skill.m_tCost, skill.m_tCostHpMp, ts.costvalue);
				if (ts.e == eSkill::力劈华山 || ts.e == eSkill::无畏布施)
				{
					skill.m_tCost = toString("(等级/2+%d)魔法", ts.costvalue);
				}
				else if (ts.e == eSkill::天降灵葫)
				{
					skill.m_tCost = toString("(等级/3+%d)魔法", ts.costvalue);
				}
			}


#ifdef ccc_checkwas
			was.Load(skill.m_SmallHead);
			was.Load(skill.m_BigHead);
			was.Load(skill.m_MagicID);
			was.Load(skill.m_State);
			was.Load(skill.m_Sound);
#endif
		}
	}

// 	oss.str("");
// 	oss << g_pathData << "道具列表\\符石.txt";
// 	File.open(oss.str());
// 	if (!File)ERRBOX;
// 
// 	File >> dustbin;
// 	string name;
// 	ulong smallhead, bighead;
// 	int num;
// 	File >> bighead;
// 	File >> smallhead;
// 	File >> name;
// 	File >> num;
// 	cct::get()->pushItemHead("符石大", bighead);
// 	cct::get()->pushItemHead("符石小", smallhead);
// 	m_SpecialSkill2.resize(num);
// 	for (int i = 0; i < num; i++)
// 	{
// 		sSkill& skill = m_SpecialSkill2[i];
// 		File>> skill.m_Id;
// 		File >> skill.m_Cost;
// 		File >> dustbin;
// 		 skill.m_Name=name;
// 		File >> skill.m_Text;
// 		skill.m_BigHead = bighead;
// 		skill.m_SmallHead = smallhead;
// 		skill.m_SkillType = 7;
// 	}
// 	File.close();
// 	oss.str("");
// 	oss << g_pathData << "技能\\特技声音.txt";
// // 	oss.str("");
// // 	oss << g_strSkillPath << "特技声音.txt";
// 	File.open(oss.str());
// 	if (!File)ERRBOX;
// 	int soundnum;
// 	File >> soundnum;
// 	int soundid;
// 	string soundname;
// 	for (int i = 0; i < soundnum; i++)
// 	{
// 		File >> soundid;
// 		File >> soundname;
// 		File >> m_SpecialSkill[i].m_Sound;
// 		cct::get()->pushSpecialSkillHead(string("特技声音_") + soundname, m_SpecialSkill[i].m_Sound);
// 	}
// 	File.close();

	return true;
}


sSkill* cSkillManager::GetSkill(int ID)
{
	if (ID<1000)
		return &m_MengPaiManager.m_SkillList[ID]; 
	if (ID < 2000)//1000-2000之间的不是技能
		return 0;
	if (ID < 3000)
		return GetPetSkill(ID - 2000);
	return GetSpecialSkill(ID - 3000);
}


void cSkillManager::SetMengPaiSkill(cDescribe& describe, int id)
{
	if (id < 0)return;
	sSkill& Skill = m_MengPaiManager.m_SkillList[id];
	string text[3];
	text[0] = Skill.m_Name;
	text[1] = Skill.m_Text;
	ostringstream oss;
	oss << "消耗:";
	oss << Skill.m_tCost;
	text[2] = oss.str();
	describe.Set(g_xMouse, g_yMouse, Skill.m_BigHead, 3, text);
}



int cSkillManager::GetTargetID(int UserID, int TargetID, int Num)
{
	return g_pMainState->m_AI.find溅射暗器(UserID, TargetID, Num, true + 2);
}


bool cSkillManager::SetDamage(int HP, int Who)
{
	if (0 == HP)return true;
	if (99999 < HP)HP = 99999;
	else if (-99999 > HP)HP = -99999;
	sFightWork* pUserList = &g_pMainState->m_FightWorkList[Who];
	int color = 0;
	if (HP > 0)
	{
		color = 1;
	}
	else
	{
		HP = -HP;
	}
	for (int i = 0; i < 5; i++)
	{
		if (color == 1)
			pUserList->m_Damage[i].Set(&g_pMainState->m_FNumRed);
		else
			pUserList->m_Damage[i].Set(&g_pMainState->m_FNumGreen);
	}
	ostringstream oss;
	int num = 0;
	oss.str("");
	oss << HP;
	string str2 = oss.str();
	pUserList->m_DamageNum = str2.length();
	switch (pUserList->m_DamageNum)
	{
	case 5:
		num = HP / 10000;
		pUserList->m_Damage[4].SetFrame帧(num);
		HP -= num * 10000;
	case 4:
		num = HP / 1000;
		pUserList->m_Damage[3].SetFrame帧(num);
		HP -= num * 1000;
	case 3:
		num = HP / 100;
		pUserList->m_Damage[2].SetFrame帧(num);
		HP -= num * 100;
	case 2:
		num = HP / 10;
		pUserList->m_Damage[1].SetFrame帧(num);
		HP -= num * 10;
	case 1:
		num = HP;
		pUserList->m_Damage[0].SetFrame帧(num);
		break;
	}


	int width = 0;
	for (int i = 0; i < pUserList->m_DamageNum; i++)
	{
		width += pUserList->m_Damage[i].m_Width;
	}
	//这里取阴影的中心,否则某些角色(比如巫蛮儿- -!!!)攻击时如果被震,数字会和怪的数字接上
	int xpos = pUserList->m_pObj->GetShadow()->GetX() - width / 2;

	////////////////////////////////////////////////////////////////////////// 呵呵哒 飙伤害位置
	int ypos = (pUserList->m_pObj->GetY() + pUserList->m_pObj->GetTopY()) / 2 - 10;

	for (int i = pUserList->m_DamageNum - 1; i > -1; i--)
	{
		pUserList->m_DamageTime[i] = 20 - i * 4;
		pUserList->m_Damage[i].SetShowHeight(1);
		pUserList->m_Damage[i].SetXY(xpos, ypos);
		pUserList->m_Damage[i].m_NeedShow = true;
		xpos += pUserList->m_Damage[i].m_Width;
	}

	g_pMainState->m_FightWorkList[Who].m_pObj->UpdateHpLine();
	return true;
}



bool cSkillManager::Cost(int userid, int skill, int num, bool bCost)
{
	int sid = skill;
	if (skill == 1010)
	{
		sid = 0;
	}
	else if (skill == 1017)
	{
		sid = 7;
	}
	else if (skill == 1095)
	{
		sid = 2095;
	}
	else if (skill >= 1000 && skill < 2000)
	{
		return true;
	}
	auto obj = g_pMainState->m_FightWorkList[userid].m_pObj;
	// 变身
	switch (skill)
	{
	case 135:
	case 136:
	{	
		int start = userid / 10;
		int em = 0;
		int wd = 0;
// 		g_pMainState->m_FightWorkTemps[start]._moon < 0;
// 		if (!isOk)
// 		{
// 			return false;
// 		}
// 		isOk = false;
		start *= 10;
		int end = start + 5;
		for (int i = start; i < end; ++i)
		{
			const auto& list = g_pMainState->m_FightWorkList[g_pMainState->m_InterfaceTeam.GetTeamTurn(i)];
			if (!list.isExist)
			{
				++em;
			}
			else
			{
				const auto& name = list.m_pObj->m_TrueName.GetString();
				if (name == GetSkill(135)->m_Name || name == GetSkill(136)->m_Name)
				{
					++wd;
				}
			}
		}
		if (em == 0 || wd > 0)
		{
			return false;
		}
		
	}
		break;
	case 141:
	case 142:
	case 143:
	case 148:
		if (!obj->CheckHaveState(145))
		{
			return false;
		}
	case 2101:
		if (obj->CheckHaveState(1998))
		{
			return false;
		}
	}

	const auto& s = GetSkill(sid);
	auto data = obj->getPropertyData();
	
	string cost = s->m_tCostHpMp;
	bool costMp = true;
	int& zy = data->m_FightData.zhanyi;
	int z = 0;

	if (skill == 168 || skill == 171)
	{
		z = 1;
	}
	else if (skill == 169)
	{
		z = 2;
	}
	else if (skill == 172)
	{
		z = 3;
	}
	

	int v = s->m_Cost;
	if (skill >= 3000)
	{
		v = v * (100 - data->CpSavePercent) / 100;
		if (data->m_CP >= v)
		{
			if (bCost)
			{
				AddCp(userid, -v);
			}
			return true;
		}
		return false;
	}
	// 无畏布施
	if (skill == ePS_力劈华山 + 2000 || skill == ePS_迷你空间震 + 2000)
	{
		v = data->m_Lv / 2 + v;
	}
	// 天降灵葫
	else if (skill == ePS_大蛇破坏光线 + 2000)
	{
		v = data->m_Lv / 3 + v;
	}
	else if (cost.find("CostHpMax") != string::npos)
	{
		costMp = false;
		v = data->HPMax.GetData() * v / 100;
	}
	else if (cost.find("CostHpFix") != string::npos)
	{
		costMp = false;
	}
	else if (cost.find("CostHp") != string::npos)
	{
		costMp = false;
		v = data->m_HP * v / 100;
	}
	else if (cost.find("CostLv") != string::npos)
	{
		v = data->m_Lv + v;
	}
	else if (cost.find("MPS") != string::npos)
	{
		v = v * num;
	}

	if (costMp)
	{
		v = v * (100 - data->MpSavePercent) / 100;
		if (data->m_MP > 0/*>= v*/ && zy >= z)
		{
			if (bCost)
			{
				v = min(v, data->m_MP);
				AddMp(userid, -v);
				zy -= z;

			}
			return true;
		}
		return false;
	}

	if (skill == 189)
	{
		// 地涌金莲
		int vm = 50 * (100 - data->MpSavePercent) / 100;
		if (data->m_MP > 0 && data->m_HP >= v)
		{
			if (bCost)
			{
				AddHp(userid, -v);
				SetDamage(v, userid);

				vm = min(vm, data->m_MP);
				AddMp(userid, -vm);
			}
			return true;
		}
		return false;
	}

	if (data->m_HP >= v)
	{
		if (bCost/* && skill != 0 && skill != 7*/)
		{
			AddHp(userid, -v);
			SetDamage(v, userid);
		}
		return true;
	}

	return false;
}



sItem2* cSkillManager::GetItem(int UserID)
{
	int k = UserID;
	if (g_pMainState->m_FightWorkList[k].m_pObj->m_IndexType != INDEXTYEP_CHARACTER)
	{
		k -= 5;
		if (g_pMainState->m_FightWorkList[k].m_pObj->m_IndexType != INDEXTYEP_CHARACTER)
			return 0;
	}
	cCharacter* pc = (cCharacter*)m_pFightState->m_pFightWorkList[k]->m_pObj->m_pIndex;
	return &pc->m_PcData.m_Items[m_pFightState->m_pFightWorkList[UserID]->m_ItemSelectID];
}




#if 0

bool cSkillManager::Cost(int& outhp, int Skilllv, int sSkillID, int UserID, int num, bool bCost)
{
	//return true;//bug
	cObj* pObj = g_pMainState->m_FightWorkList[UserID].m_pObj;
	cPropertyData* pUserData;
	pObj->GetPropertyData(pUserData);

	int hp = pUserData->m_HP;
	int hpmax = pUserData->HPMax.GetData();
	int mp = pUserData->m_MP;
	//	int mpmax = pUserData->m_MPMax.GetData();
	int cp = pUserData->m_CP;
	int hpsub = 0;
	int mpsub = 0;
	int cpsub = 0;

	if (!bCost)
	{
		switch (sSkillID)
		{
		case  0://横扫

		{
			if (hp > (hpmax / 10))return true;
			else return false;
		}
			break;
		case 97: // 烟雨

		{
			if (hp > (hpmax / 10))return true;
			else return false;
		}
			break;
		case 141:  //狮驼的技能
		case 142:
		case 143:
		case 148:

		{
			if (!pObj->CheckHaveState(145))
				return false;
		}
			break;
		}
	}
	if (sSkillID >= 3000)
	{
		cpsub = GetSpecialSkill(sSkillID - 3000)->m_Cost;
	}
	else
		switch (sSkillID)
	{
		case 0:hpsub = hp / 20; break;
		case 1:hpsub = 0; break;
		case 1010:
			hpsub = hp / 20; break;
		case 3:hpsub = hp / 20; break;
		case 6:mpsub = 50; break;
			//	case 7:hpsub = hp / 20; break;
		case 1017:hpsub = hp / 20; break;
		case 11:mpsub = 30; break;
		case 13:mpsub = 30; break;
		case 14:mpsub = 40; break;
		case 15:mpsub = 40; break;
		case 16:mpsub = 40; break;
		case 17:mpsub = 60; break;
		case 18:mpsub = 60; break;
		case 19:mpsub = 40; break;
		case 20:mpsub = 60; break;
		case 21:mpsub = 60; break;
		case 22:mpsub = 20; break;
		case 23:hpsub = 20; break;
		case 25:mpsub = hp / 20; break;
		case 26:mpsub = 50;	break;
		case 27:mpsub = 100; break;
		case 28:mpsub = 30 * num; break;
		case 31:mpsub = 20 * num; break;
		case 33:mpsub = 40; break;
		case 34:mpsub = 40; break;
		case 35:mpsub = 30 * num; break;
		case 36:mpsub = 40; break;
		case 37:mpsub = 150; break;
		case 38:mpsub = 50; break;
		case 39:mpsub = 40; break;
		case 40:mpsub = 100; break;
		case 41:mpsub = 40; break;
		case 42:mpsub = 150; break;
		case 43:mpsub = 30; break;
		case 44:mpsub = hp / 20; break;
		case 45:mpsub = 150;/* hp -= 1000*/; break;
		case 46:mpsub = 150; break;
		case 49:mpsub = 100; break;
		case 50:mpsub = 50; break;
		case 54:mpsub = 50; break;
		case 58:mpsub = hp / 20; break;
		case 59:mpsub = 60 * num; break;
		case 61:mpsub = 5; break;
		case 63:mpsub = 50; break;
		case 67:mpsub = 50; break;
		case 68:mpsub = 50; break;
		case 69:mpsub = 50; break;
		case 70:mpsub = hp / 20; break;
		case 71:mpsub = 30 * num; break;
		case 72:mpsub = 50; break;
		case 74:mpsub = 35 * num; break;
		case 76:mpsub = 50; break;
		case 77:mpsub = 80; break;
		case 79:mpsub = 50; break;
		case 80:mpsub = 20 * num; break;
		case 83:mpsub = hp / 20; break;
		case 84:mpsub = 50; break;
		case 88:mpsub = 100; break;
		case 89:mpsub = 50; break;
		case 90:mpsub = 30; break;
		case 91:mpsub = 35 * num; break;
		case 93:hpsub = hp / 20; break;
		case 94:hpsub = 30; break;
		case 97:mpsub = 50; break;
		case 98:mpsub = 30 * num; break;
		case 102:mpsub = 50; break;
		case 103:mpsub = 50; break;
		case 104:mpsub = 150; break;
		case 105://普陀五行法术
		case 106:
		case 107:
		case 108:
		case 109:mpsub = 50; break;
		case 110:hpsub = hp / 20; break;
		case 112:mpsub = 100; break;
		case 113:mpsub = 80;
		case 115:mpsub = 10; break;
		case 116:mpsub = 20 * num; break;
		case 117:mpsub = 30; break;
		case 120:mpsub = 50 * num; break;
		case 122:mpsub = 40; break;
		case 123:mpsub = 150; break;
		case 124:hpsub = hp * 5 / 100; break;
		case 125:mpsub = 150; break;
		case 126:mpsub = 80 * num; break;
		case 127:mpsub = 80; break;
		case 129:mpsub = 50; break;
		case 131:mpsub = 30 * num; break;
		case 132:mpsub = 60; break;
		case 135:mpsub = 50; break;
		case 136:mpsub = 100; break;
		case 141:mpsub = 30; break;
		case 142:mpsub = 30 * num; break;
		case 143:mpsub = 30; break;
		case 144:mpsub = 40; break;
		case 145:mpsub = 20; break;
		case 148:mpsub = 150; break;
		case 149:hpsub = hp / 20; break;
		case 150:mpsub = 30; break;
		case 152:mpsub = 50; break;
		case 154:mpsub = 40; break;
		case 155:mpsub = 40; break;
		case 156:mpsub = 35; break;
		case 159:mpsub = 40; break;
		case 160:mpsub = 50; break;
		case 161:mpsub = 60; break;
		case 162:mpsub = 30 * num; break;
		case 163:mpsub = hp / 20; break;
		case 164:mpsub = 60; break;
		case 166:mpsub = 80; break;
		case 167:mpsub = 50; break;
			//四法
		case 2084: mpsub = 30 * num; break;
		case 2085: mpsub = 30 * num; break;
		case 2086: mpsub = 30 * num; break;
		case 2087: mpsub = 30 * num; break;
		case 2088: mpsub = 30 * num; break;
		case 2089: mpsub = 30 * num; break;
		case 2090: mpsub = 30 * num; break;
		case 2091: mpsub = 30 * num; break;
			//
		case 2092: mpsub = pUserData->m_Lv / 2 + 10; break;
		case 2095: mpsub = pUserData->m_Lv / 2 + 50; break;
		case 2093:
		case 2094:
		case 2097:
		case 2098:
		case 2099:
		case 2100:
		case 2101:
		case 2105:mpsub = mpsub = pUserData->m_Lv + 10; break;
		case 2102:mpsub = mpsub = pUserData->m_Lv + 100; break;
		case 2096:hpsub = hp / 10; break;
		default:
			return true;
	}
	if (bCost)
	{
		if (hp < hpsub)return false;

		if (mpsub && pUserData->MpSavePercent > 0)
		{
			mpsub = mpsub * (100 - pUserData->MpSavePercent) / 100;
			if (mpsub < 1)
				mpsub = 1;
		}
		if (mp < mpsub)return false;
		if (cp < cpsub)return false;
		if (hpsub)
		{
			// 			hpsub = hpsub*(100 + pUserData->mpsavepercent) / 100;
			// 			if (hpsub < 1)hpsub = 1;
			AddHp(UserID, -hpsub);
			SetDamage(hpsub, UserID);
		}
		if (mpsub)
		{
			// 			if (pUserData->mpsavepercent > 0)
			// 			{
			// 				mpsub = mpsub*(100 + pUserData->mpsavepercent) / 100;
			// 				if (mpsub < 1)mpsub = 1;
			// 			}
			AddMp(UserID, -mpsub);
		}
		if (cpsub)
		{
			AddCp(UserID, -cpsub);
		}
	}
	else
	{
		if (hp < hpsub)return false;
		if (mp < mpsub)return false;
		if (cp < cpsub)return false;
	}
	return true;
}





bool cSkillManager::SetPetSkill1(cPropertyData* pPetDate, int ID, int lv)
{
	switch (ID)
	{
	case 0://反击
		pPetDate->CounterRate.d1 += lv * 30;
		break;
	case 1://高级反击
		pPetDate->CounterRate.d1 += lv * 45;
		break;
	case 2://反震
		pPetDate->StabRate.d1 += lv * 30;
		pPetDate->StabPercent.d1 += lv * 30;
		break;
	case 3://高级反震
		pPetDate->StabRate.d1 += lv * 30;
		pPetDate->StabPercent.d1 += lv * 50;
		break;
	case 4://吸血
		pPetDate->SuckBloodPercent.d1 += lv * 20;
		break;
	case 5://高级吸血
		pPetDate->SuckBloodPercent.d1 += lv * 35;
		break;
	case 6://连击
		pPetDate->ComboRate.d1 += lv * 15;
		break;
	case 7://高级连击
		pPetDate->ComboRate.d1 += lv * 30;
		break;
	case 8://飞行
		pPetDate->HitRate.d1 += lv * 10;
		pPetDate->HitRate.d2 += lv * 10;
		pPetDate->DmgPercentOfArm.d2 -= lv * 50;
		break;
	case 9://高级飞行
		pPetDate->HitRate.d1 += lv * 20;
		pPetDate->HitRate.d2 += lv * 20;
		pPetDate->DmgPercentOfArm.d2 -= lv * 20;
		break;
	case 10://夜战
		//		pPetDate->m_Spurting.d2 += 20;
		pPetDate->DmgPercent.d1 += lv * 5;
		//		pPetDate->nightLv += lv *10;
		break;
	case 11://高级夜战
		//		pPetDate->m_Spurting.d2 += 30;
		pPetDate->DmgPercent.d1 += lv * 10;
		//		pPetDate->nightLv += lv * 20;
		break;
	case 12://隐身
		// 		pPetDate->m_HitRate.d2 += lv*15;
		// 		pPetDate->m_MagicHitRate.d2 += lv * 15;
		// 		pPetDate->m_SealRate.d2 += lv * 15;
		// 		pPetDate->poisonRate.d2 += lv * 15;
		pPetDate->StartMagic.d1 = lv > 0 ? 123 : 0;
		break;
	case 13://高级隐身
		// 		pPetDate->m_HitRate.d2 += lv * 25;
		// 		pPetDate->m_MagicHitRate.d2 += lv * 25;
		// 		pPetDate->m_SealRate.d2 += lv * 25;
		// 		pPetDate->poisonRate.d2 += lv * 25;
		pPetDate->StartMagic.d1 = lv > 0 ? 123 : 0;
		break;
	case 14://感知
		// 		pPetDate->m_HitRate.d1 += lv * 35;
		// 		pPetDate->m_MagicHitRate.d1 += lv * 35;
		// 		pPetDate->poisonRate.d1 += lv * 35;
		pPetDate->PeopleSpecial.d1 += 100;
		break;
	case 15://高级感知
		pPetDate->HitRate.d1 += lv * 25;
		// 		pPetDate->m_MagicHitRate.d1 += lv * 65;
		// 		pPetDate->poisonRate.d1 += lv * 65;
		pPetDate->PeopleSpecial.d1 += 100;
		break;
	case 16://再生
		pPetDate->LiveHp += lv * 10;
		break;
	case 17://高级再生
		pPetDate->LiveHp += lv * 20;
		break;
	case 18://冥思
		pPetDate->LiveMp += lv * 5;
		break;
	case 19://高级冥思
		pPetDate->LiveMp += lv * 10;
		break;
	case 20://慧根
		pPetDate->MpSavePercent += lv * 25;
		break;
	case 21://高级慧根
		pPetDate->MpSavePercent += lv * 50;
		break;
	case 22://不幸
		//		pPetDate->m_CriRate.d2   -= lv*10;
		pPetDate->CriRate.d2 -= lv * 10;
		break;
	case 23://必杀
		pPetDate->CriRate.d1 += lv * 10;
		break;
	case 24://高级必杀
		pPetDate->CriRate.d1 += lv * 20;
		break;
	case 25://幸运
		pPetDate->CriRate.d2 += lv * 60;
		//		pPetDate->m_MagicCriRate.d2 -= lv * 60;
		break;
	case 26://高级幸运
		pPetDate->CriRate.d2 += lv * 200;
		//		pPetDate->m_MagicCriRate.d2 -= lv * 20;
		break;
	case 27://神迹
		pPetDate->LiveRestoreRate += lv * 60;
		break;
	case 28://高级神迹
		pPetDate->LiveRestoreRate += lv * 200;
		break;
	case 29://招架
		pPetDate->ParryRate.d1 += lv * 10;
		break;
	case 30://高级招架
		pPetDate->ParryRate.d1 += lv * 20;
		break;
	case 31://永恒
		pPetDate->BuffedTiemsAdd += lv * 1;
		break;
	case 32://高级永恒
		pPetDate->BuffedTiemsAdd += lv * 2;
		break;
	case 33://敏捷
		pPetDate->Speed.AddDataAddPercent(lv * 10);
		break;
	case 34://高级敏捷
		pPetDate->Speed.AddDataAddPercent(lv * 20);
		break;
	case 35://强力
		pPetDate->Atk.AddDataAddPercent(lv * 5);
		break;
	case 36://高级强力
		pPetDate->Atk.AddDataAddPercent(lv * 10);
		break;
	case 37://防御
		pPetDate->Def.AddDataAddPercent(lv * 5);
		break;
	case 38://高级防御
		pPetDate->Def.AddDataAddPercent(lv * 10);
		break;
	case 39://偷袭  
		pPetDate->StabRate.d2 += lv * 50;//反震免疫率
		pPetDate->CounterRate.d2 += lv * 50;//反击免疫率
		pPetDate->ParryRate.d2 += lv * 50;//反格档
		break;
	case 40://高级偷袭
		pPetDate->StabRate.d2 += lv * 100;//反震免疫率
		pPetDate->CounterRate.d2 += lv * 100;
		pPetDate->ParryRate.d2 += lv * 100;
		break;
	case 41://毒
		pPetDate->HitRateOfPoison.d1 += lv * 10;
		break;
	case 42://高级毒
		pPetDate->HitRateOfPoison.d1 += lv * 20;
		break;
	case 43://驱鬼
		pPetDate->ghostSpecial.d1 += lv * 50;
		break;
	case 44://高级驱鬼
		pPetDate->ghostSpecial.d1 += lv * 100;
		break;
	case 45://鬼魂术
		//		pPetDate->m_DamagePercent.d2 += lv*20;
		pPetDate->m_Race += lv * 1020;
		// 		if (lv > 0)
		// 		{
		// 			pPetDate->m_race += 1020;
		// 		}
		// 		else
		// 		{
		// 			pPetDate->m_race -= 1020;
		// 		}
		break;
	case 46://高级鬼魂术
		pPetDate->m_Race += lv * 1020;
		//		pPetDate->m_DamagePercent.d2 += lv*30;
		// 		if (lv > 0)
		// 		{
		// 			pPetDate->m_race += 1020;
		// 		}
		// 		else
		// 		{
		// 			pPetDate->m_race -= 1020;
		// 		}
		break;
	case 47://魔之心
		pPetDate->DmgPercentOfMagic.d1 += lv * 10;
		break;
	case 48://高级魔之心
		pPetDate->DmgPercentOfMagic.d1 += lv * 20;
		break;
	case 49://神佑
		pPetDate->RelifeRate.d1 += lv * 20;
		break;
	case 50://高级神佑
		pPetDate->RelifeRate.d1 += lv * 35;
		break;
	case 51://精神集中
		pPetDate->HitRateOfSeal.d2 += lv * 10;
		break;
	case 52://高级精神集中
		pPetDate->HitRateOfSeal.d2 += lv * 20;
		break;
	case 53://否定信仰
		pPetDate->RelifeRate.d2 += lv * 20;
		break;
	case 54://高级否定信仰
		pPetDate->RelifeRate.d2 += lv * 30;
		break;
	case 55://法术连击
		pPetDate->ComboRateOfMagic.d1 += lv * 20;
		break;
	case 56://高级法术连击
		pPetDate->ComboRateOfMagic.d1 += lv * 30;
		break;
	case 57://法术暴击
		pPetDate->CriRateOfMagic.d1 += lv * 10;
		break;
	case 58://高级法术暴击
		pPetDate->CriRateOfMagic.d1 += lv * 15;
		break;
	case 59://法术波动
		pPetDate->MagicWavePercent += lv * 20;
		break;
	case 60://高级法术波动
		pPetDate->MagicWavePercent += lv * 35;
		break;
	case 61://迟钝
		//		pPetDate->m_DEF.AddDataAddPercent(lv * 20);
		pPetDate->Speed.AddDataAddPercent(-lv * 50);
		//		pPetDate->m_HitRate.d2 -= lv * 20;
		//		pPetDate->m_ParryRate.d1 -= lv * 40;
		break;
	case 62://弱点火
		pPetDate->MagicFire.d2 -= lv * 30; //火	
		break;
	case 63://弱点水
		pPetDate->MagicWater.d2 -= lv * 30;  //水
		break;
	case 64://弱点土
		pPetDate->MagicSoil.d2 -= lv * 30; //土
		break;
	case 65://弱点雷
		pPetDate->MagicThunder.d2 -= lv * 30;//雷
		break;
	case 66://雷属性吸收
		pPetDate->MagicThunder.d2 += lv * 20;//雷
		break;
	case 67://高级雷属性吸收
		pPetDate->MagicThunder.d2 += lv * 30;//雷
		break;
	case 68://土属性吸收
		pPetDate->MagicSoil.d2 += lv * 20; //土
		break;
	case 69://高级土属性吸收
		pPetDate->MagicSoil.d2 += lv * 30; //土
		break;
	case 70://火属性吸收
		pPetDate->MagicFire.d2 += lv * 20; //火
		break;
	case 71://高级火属性吸收
		pPetDate->MagicFire.d2 += lv * 30; //火
		break;
	case 72://水属性吸收
		pPetDate->MagicWater.d2 += lv * 20;  //水
		break;
	case 73://高级水属性吸收
		pPetDate->MagicWater.d2 += lv * 30;  //水
		break;
	case 74://移花接木 
		pPetDate->DmgPercentOfArm.d2 += lv * 95;
		break;
	case 75://风刃
		pPetDate->Spurting.d1 += lv * 15;
		break;
	case 76://嗜血追击
		pPetDate->ShiXueAdd += lv * 5;
		break;
	case 77://龙鳞防御(盾气)
		//		pPetDate->m_DamageAddMagicLv.d2 += lv * 2;//法术伤害结果
		// 		pPetDate->m_DamageAddLv.d2	+= lv * 2;  //物理伤害结果
		// 		pPetDate->m_DamageAddPercentMagic2.d2 += 10;
		// 		pPetDate->m_MagicWater.d2 += lv*20;  //水
		break;
	case 78://龙鳞守护(高级盾气)
		//		pPetDate->m_DamageAddMagicLv.d2 += lv * 3;//法术伤害结果
		// 		pPetDate->m_DamageAddLv.d2 += lv * 3;  //物理伤害结果
		// 		pPetDate->m_DamageAddPercentMagic2.d2 += 15;
		// 		pPetDate->m_MagicWater.d2 += lv * 30;  //水
		break;
	case 79://法术抵抗
		pPetDate->DmgPercentOfMagic.d2 += lv * 15;
		break;
	case 80://高级法术抵抗
		pPetDate->DmgPercentOfMagic.d2 += lv * 25;
		break;
	case 81://直死(合纵，小风华)
		//		pPetDate->m_Pierce.d1 += 20;//无视防御率
		//		pPetDate->m_PierceMagic.d1+=30; //无视灵力率
		pPetDate->ComboNumUp += lv * 1;
		//		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 82://风华武圣
		pPetDate->ComboNumUp += lv * 3;
		//		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 83://法术反弹
		pPetDate->StabRateOfMagic.d1 += lv * 35;//法术反震率
		pPetDate->StabPercentOfMagic.d1 += lv * 30;//法术反震伤害率
		break;
	}
	return true;
}


bool cSkillManager::ReMoveMainSkill(int targetID, int MainSkillID)
{
	if (INDEXTYEP_CHARACTER != g_pMainState->m_FightList[targetID].m_pData->m_IndexType)return false;
	cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[targetID].m_pData->m_pIndex;
	//cPCData& pcDate = pc->m_PCData;
	sSkill* pSkill = &m_MengPaiManager.m_SkillList[MainSkillID];
	//int num = pc->m_PCData.m_SkillEnablelist.size();

	for (vector<sSkill*>::iterator Iterator = pc->m_PcData.m_SkillEnablelist.begin(); Iterator != pc->m_PcData.m_SkillEnablelist.end();)
	{
		if (pSkill->m_Id == (*Iterator)->m_Id)
		{
			pc->m_PcData.m_SkillEnablelist.erase(Iterator);
			return true;
		}
		Iterator++;
	}
	return true;
}


bool cSkillManager::SetMainSkill(int targetID, int MainSkillID)
{
	if (INDEXTYEP_CHARACTER != g_pMainState->m_FightList[targetID].m_pData->m_IndexType)return false;
	cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[targetID].m_pData->m_pIndex;
	//cPCData& pcDate = pc->m_PCData;
	sSkill* pSkill = &m_MengPaiManager.m_SkillList[MainSkillID];
	//是否已经有了
	int num = pc->m_PcData.m_SkillEnablelist.size();
	for (int i = 0; i < num; i++)
	{
		if (pSkill->m_Id == pc->m_PcData.m_SkillEnablelist[i]->m_Id)
			return true;
	}

	pc->m_PcData.m_SkillEnablelist.push_back(pSkill);

	return true;
}

//                                   角色ID        技能ID		打书位置
int cSkillManager::SetPetSkill(cPropertyData* pTarget, int PetSkillID, int Pos)
{
	//先确保不重复
	for (int i = 0; i < pTarget->m_NumofBBSkill; i++)
	{
		if (PetSkillID == pTarget->m_petSkills[i]->m_Id)return i;
	}
	sSkill* pPetSkill = GetPetSkill(PetSkillID);
	for (int k = 0; k < pPetSkill->m_NumUnCompatible; k++)//要打的书有几个不兼容的技能
	{
		for (int i = 0; i < pTarget->m_NumofBBSkill; i++)
		{//同样的技能不能存在,不能共存的技能也不能存在
			if ((pPetSkill->m_UnCompatible[k] == pTarget->m_petSkills[i]->m_Id))
			{
				if (Pos == i)continue;
				return i;
			}
		}
	}
	//替换还是增加
	if (Pos < pTarget->m_NumofBBSkill)
	{
		SetPetSkill1(pTarget, pTarget->m_petSkills[Pos]->m_Id, -1);
		pTarget->m_petSkills[Pos] = pPetSkill;
	}
	else
	{
		pTarget->m_petSkills[pTarget->m_NumofBBSkill] = pPetSkill;
		pTarget->m_NumofBBSkill += 1;
	}
	SetPetSkill1(pTarget, PetSkillID);
	return -1;
}


void cSkillManager::lvUpFuZhuSkill(int targetID, int FuZhuSkillID, int lv)
{
	cPropertyData* petDate;
	g_pMainState->m_FightList[targetID].m_pData->GetPropertyData(petDate);
	petDate->lvUpFuZhuSkill(lv, FuZhuSkillID);
}


void cSkillManager::SetSpecialSkill2(int targetID, int SkillID, int Setup)
{
	cPropertyData* pcDate;
	g_pMainState->m_FightList[targetID].m_pData->GetPropertyData(pcDate);
	SetSpecialSkill2(pcDate, SkillID, Setup);
}


void cSkillManager::SetSpecialSkill2(cPropertyData* p, int SkillID, int Setup)
{//符石效果 
	vector<int> values =
	{
		5,/*气血上限 + 8 %					*/
		8,/*魔法上限 + 8 %					*/
		2,/*再生能力 + 2					*/
		1,/*冥思能力 + 1					*/
		1,/*每回合 + 1愤怒					*/
		5,/*溅射防御 + 5 %					*/
		5,/*状态恢复率 + 5 %				*/
		2,/*异常抵抗 + 2 %					*/
		5,/*法术波动率 + 5 %				*/
		20,/*连击下限 + 1, 防御 - 10 %		*/
		2,/*连击伤害 + 5 %					*/
		1,/*部分状态持续时间 + 1;			*/
		2,/*伤害 + 2 %						*/
		4,/*命中 + 4 %						*/
		2,/*防御 + 2 %						*/
		2,/*灵力 + 2 %						*/
		2,/*速度 + 2 %						*/
		3,/*躲闪 + 3 %						*/
		1,/*神佑率 + 1 %					*/
		5,/*防止神佑率 + 5 %				*/
		2,/*必杀率 + 2 %					*/
		2,/*防止必杀率 + 2 %				*/
		2,/*法暴率 + 2 %					*/
		2,/*防止法暴率 + 2 %				*/
		3,/*治疗率 + 3 %					*/
		3,/*被治疗率 + 3 %					*/
		5,/*必杀伤害 + 10 %				*/
		2,/*连击率 + 2 % ;					*/
		2,/*法术连击率 + 2 %				*/
		3,/*无视防御 + 3 %					*/
		3,/*无视灵力 + 3 %					*/
		1,/*命中率 + 2 %					*/
		1,/*回避率 + 2 %					*/
		2,/*法术命中率 + 2 %				*/
		2,/*法术回避率 + 2 %				*/
		1,/*封印命中率 + 1 %				*/
		1,/*抗封 + 1 %						*/
		2,/*毒率 + 2 %						*/
		10,/*抗毒 + 10 %					*/
		1,/*固定伤害 + 1 %					*/
		1,/*固定伤害防御率 + 1 %			*/
		1,/*法术伤害 + 1 %					*/
		1,/*法术防御 + 1 %					*/
		1,/*物理伤害 + 1 %					*/
		1,/*物理防御 + 1 %					*/
		1,/*暗器伤害 + 1 %					*/
		1,/*暗器防御 + 1 %					*/
		10,/*毒伤害 + 15 %					*/
		10,/*毒伤害 - 15 %					*/
		2,/*反震率 + 2 %					*/
		3,/*反震回避率 + 3 %				*/
		3,/*反震伤害 + 3 %					*/
		3,/*反震伤害防御 + 3 %				*/
		2,/*法术反弹率 + 2 %				*/
		3,/*法术反弹回避率 + 3 %			*/
		3,/*法术反弹伤害 + 3 %				*/
		3,/*法术反弹防御 + 3 %				*/
		2,/*吸血率 + 2 %					*/
		5,/*吸血防御 + 5 %					*/
		5,/*火伤 + 5 %						*/
		5,/*火防 + 5 %						*/
		5,/*水伤 + 5 %						*/
		5,/*水防 + 5 %						*/
		5,/*土伤 + 5 %						*/
		5,/*土防 + 5 %						*/
		5,/*雷伤 + 5 %						*/
		5,/*雷防 + 5 %						*/
		5,/*对鬼伤害 + 5 %					*/
		5,/*对人伤害 + 5 %					*/
		5,/*对妖伤害 + 5 %					*/
		5,/*对仙伤害 + 5 %					*/
		5,/*对机械伤害 + 5 %				*/
		2,/*物理攻击致伤率 + 2 %			*/
		5,/*受到物理攻击防止致伤 + 5 %		*/
		2,/*法术攻击致伤率 + 2 %			*/
		5,/*受到法术攻击防止致伤 + 5 %		*/
		2,/*物理攻击降低对手MP + 2 %		*/
		5,/*防止降低MP + 5 %				*/
		1,/*物理攻击吸收目标1攻			*/
		1,/*物理攻击吸收目标1防			*/
		1,/*物理攻击吸收目标1速			*/
		1,/*物理攻击吸收目标1灵			*/
		2,/*物理攻击吸收目标2命中			*/
		3,/*普通攻击溅射率 + 3 %			*/
		1,/*物理攻击降低对手愤怒 + 1		*/
		1,/*防止物理攻击降低愤怒 + 1		*/
		1,/* 开场附加变身					*/
		1,/* 开场附加逆鳞					*/
		1,/* 开场附加定心术				*/
	};

	if (SkillID == -1)return;
	int k = 1;
	int num = m_SpecialSkill2[SkillID].m_Cost;
	num = values[SkillID];
	if (!(1 == Setup))
	{
		k = -1;
		num = -num;
	}
	switch (SkillID)
	{
	case 0:p->HPMax.AddDataAddPercent(num);
		if (g_pCharacter)
			if (p->m_Name == g_pCharacter->m_PcData.m_Name)g_pMainState->m_PCHead.UpdatePcHp(); return;
	case 1:p->MPMax.AddDataAddPercent(num);
		if (g_pCharacter)
			if (p->m_Name == g_pCharacter->m_PcData.m_Name)g_pMainState->m_PCHead.UpdatePcMp(); return;
	case 2:p->LiveHp += num; return;
	case 3:p->LiveMp += num; return;
	case 4:p->LiveCp += num; return;
	case 5:
		p->Spurting.d2 += num;
		/*p->nightLv += num; */return;
	case 6:p->LiveRestoreRate += num; return;
	case 7:p->HitRateOfSeal.d2 += num; return;
	case 8:p->MagicWavePercent += num; return;
	case 9:p->ComboNumDown += k; p->Def.AddDataAddPercent(-num); return;
	case 10:p->ShiXueAdd += num; return;
	case 11:p->BuffedTiemsAdd += num; return;
	case 12:p->Atk.AddDataAddPercent(num); return;
	case 13:p->Hit.AddDataAddPercent(num); return;
	case 14:p->Def.AddDataAddPercent(num); return;
	case 15:p->Mana.AddDataAddPercent(num); return;
	case 16:p->Speed.AddDataAddPercent(num); return;
	case 17:p->Evade.AddDataAddPercent(num); return;
	case 18:p->RelifeRate.d1 += num; return;//神估
	case 19:p->RelifeRate.d2 += num; return;
	case 20:p->CriRate.d1 += num; return;
	case 21:p->CriRate.d2 += num; return;
	case 22:p->CriRateOfMagic.d1 += num; return;
	case 23:p->CriRateOfMagic.d2 += num; return;
	case 24:p->CriRateOfCure.d1 += num; return;
	case 25:p->CriRateOfCure.d2 += num; return;
	case 26:p->CriDmgPercent.d1 += num; return;
	case 27:p->ComboRate.d1 += num; return;
	case 28:p->ComboRateOfMagic.d1 += num; return;
	case 29:p->Pierce刺穿.d1 += num; return;
	case 30:p->Pierce刺穿OfMagic.d1 += num; return;
	case 31:p->HitRate.d1 += num; return;
	case 32:p->HitRate.d2 += num; return;
	case 33:p->HitRateosMagic.d1 += num; return;
	case 34:p->HitRateosMagic.d2 += num; return;
	case 35:p->HitRateOfSeal.d1 += num; return;
	case 36:p->HitRateOfSeal.d2 += num; return;
	case 37:p->HitRateOfPoison.d1 += num; return;
	case 38:p->HitRateOfPoison.d2 += num; return;
	case 39:p->DmgPercentOfFix.d1 += num; return;
	case 40:p->DmgPercentOfFix.d2 += num; return;
	case 41:p->DmgPercentOfMagic.d1 += num; return;
	case 42:p->DmgPercentOfMagic.d2 += num; return;
	case 43:p->DmgPercent.d1 += num; return;
	case 44:p->DmgPercent.d2 += num; return;
	case 45:p->DmgPercentOfArm.d1 += num; return;
	case 46:p->DmgPercentOfArm.d2 += num; return;
	case 47:p->DmgPercentOfPoison.d1 += num; return;
	case 48:p->DmgPercentOfPoison.d2 += num; return;
	case 49:p->StabRate.d1 += num; return;
	case 50:p->StabRate.d2 += num; return;
	case 51:p->StabPercent.d1 += num; return;
	case 52:p->StabPercent.d2 += num; return;
	case 53:p->StabRateOfMagic.d1 += num; return;
	case 54:p->StabRateOfMagic.d2 += num; return;
	case 55:p->StabPercentOfMagic.d1 += num; return;
	case 56:p->StabPercentOfMagic.d2 += num; return;
	case 57:p->SuckBloodPercent.d1 += num; return;
	case 58:p->SuckBloodPercent.d2 += num; return;
	case 59:p->MagicFire.d1 += num; return;
	case 60:p->MagicFire.d2 += num; return;
	case 61:p->MagicSoil.d1 += num; return;
	case 62:p->MagicSoil.d2 += num; return;
	case 63:p->MagicWater.d1 += num; return;
	case 64:p->MagicWater.d2 += num; return;
	case 65:p->MagicThunder.d1 += num; return;
	case 66:p->MagicThunder.d2 += num; return;
	case 67:p->ghostSpecial.d1 += num; return;
	case 68:p->PeopleSpecial.d1 += num; return;
	case 69:p->MonsterSpecial.d1 += num; return;
	case 70:p->ImmortalSpecial.d1 += num; return;
	case 71:p->machineSpecial.d1 += num; return;
	case 72:p->m_AtkDownHPHurt.d1 += num; return;
	case 73:p->m_AtkDownHPHurt.d2 += num; return;
	case 74:p->m_MagDownHPHurt.d1 += num; return;
	case 75:p->m_MagDownHPHurt.d2 += num; return;
	case 76:p->m_AtkDownMP.d1 += num; return;
	case 77:p->m_AtkDownMP.d2 += num; return;
	case 78:p->m_AtkDownAtk.d1 += num; return;
	case 79:p->m_AtkDownDef.d1 += num; return;
	case 80:p->m_AtkDownSpd.d1 += num; return;
	case 81:p->m_AtkDownWakan.d1 += num; return;
	case 82:p->m_AtkDownHit.d1 += num; return;
	case 83:p->Spurting.d1 += num; return;
	case 84:p->m_AtkDownCP.d1 += num; return;
	case 85:p->m_AtkDownCP.d2 += num; return;
	case 86:if (num == 1) p->StartMagic.d1 = 145; else p->StartMagic.d1 = 0; return; /// 逆鳞 变身 定心
	case 87:if (num == 1) p->StartMagic.d1 = 81; else p->StartMagic.d1 = 0; return;
	case 88:if (num == 1) p->StartMagic.d1 = 147; else p->StartMagic.d1 = 0; return;
	}
}


void cSkillManager::lvUpMainSkill(cPcData& pcDate, int lv, int ID, bool isHero /* = false */)
{
	//	if (!lv)return;
	m_MengPaiManager.lvUpMainSkill(pcDate, lv, ID, isHero);
}


















bool cSkillManager::isIDLive(int ID, int& Num)
{
	if (m_pFightState->m_pList[ID]->isExist)
	{
		if (Num == 0)return true;
		Num -= 1;
	}
	return false;
}



int cSkillManager::GetLiveNum(bool our)
{
	int k = 0;
	if (our)
	{
		for (int i = 10; i < 20; i++)
		{
			if (m_pFightState->m_pList[i]->isExist)
				k += 1;
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (m_pFightState->m_pList[i]->isExist)
				k += 1;
		}
	}
	return k;
}




// 无视
bool cSkillManager::Use1002防御(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sBuff buf;
	buf.remainingTimes = 1;
	SetDateBuffUp(UserID, UserID, Skilllv, buf, Skilllv);
	m_pFightState->m_pList[UserID]->m_work.pop_back();
	return true;
}


// 无视
bool cSkillManager::Use7破釜沉舟(int Skilllv, int sSkillID, int UserID, int TargetID)
{//破釜沉舟
	sFightList* pUserList = m_pFightState->m_pList[UserID];
	cObj* pUser = pUserList->m_pData;
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:
		//存在检测
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage = 1;
		return true;
	case 1:
		if (WaitForMagicPoint(UserID))
		{
			pUserList->m_MaxTargetNum = 0;//最多攻击3个目标
			cPropertyData* pPet;
			pUser->GetPropertyData(pPet);
			int num = 3 + pPet->TargetNumAdd;
			for (int i = 0; i < num; i++)
			{
				pUserList->targetlist[i] = GetTargetID(UserID, TargetID, i);
				int id = pUserList->targetlist[i];
				if (UserID == id)continue;
				if (id == -1)break;
				pUserList->m_MaxTargetNum += 1;
			}
			int nowtarget;
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				nowtarget = pUserList->targetlist[i];
				m_pFightState->m_pList[nowtarget]->SetMagiSufferID(0x1EE9406C, 0, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID]);
				m_pFightState->m_pList[nowtarget]->m_pData->m_MagicSuffer.m_FrameGap = GetSpeed(sSkillID);
				m_pFightState->SetMagicSuffer(nowtarget, pUser->GetDirection());
			}
			pUserList->m_NowTarget = -1;
			stage = 21;
		}
		return true;
	case 21://伤害判定
		if (m_pFightState->m_pList[TargetID]->m_pData->m_MagicSuffer.GetFrame() == m_pFightState->m_pList[TargetID]->m_pData->m_MagicSuffer.m_pFile->GetMaxFrame() - 15)
		{
			int nowtarget;
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				nowtarget = pUserList->targetlist[i];
				m_pFightState->SetSuffer(nowtarget, pUser->GetDirection(), UserID);
				EffectSkill(Skilllv, sSkillID, UserID, nowtarget);

				m_pFightState->SwitchMagicSuffer(nowtarget);
				m_pFightState->m_pList[nowtarget]->SetMagiSufferID(0, 1, 0);
			}
			pUserList->NextTarget(m_pFightState, sSkillID);
			stage = 2;
		}
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUser->Set(POS_FIGHT_STAND);
		}
		return true;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);

			if (g_pMainState->m_FightList[UserID].m_NowTargetID > -1)
			{

			}
		}
		return true;
	case 20:
		return	StageWaitSleep(20, UserID, 3);
	case 3:
		if (g_pMainState->m_FightList[pUserList->m_NowTargetID].CheckDie())
		{
			stage = 7;
			int hpout;

			sBuff buf;
			buf.ID = 1;
			SetDateBuffUp(UserID, UserID, sSkillID, buf, Skilllv);

			Cost(hpout, Skilllv, sSkillID, UserID, 1, true);
			return true;
		}
		if (m_pFightState->Approach(UserID, pUserList->m_NowTargetID))
		{
			stage += 1;
		}
		return true;


	case 4:

	{
		int pos;
		if (rand() % 2)
			pos = POS_ATTACK2;
		else
			pos = POS_ATTACK;
		pUser->Set(pos);
		pUser->SetSound(pos);
		stage = 120;
	}
	case 120:
		if (m_pFightState->WorkAttack(UserID))
		{
			g_pMainState->m_FightList[TargetID].m_work.clear();
			stage = 5;
		}
		return true;
	case 5:  //攻击判定

	{

		m_pFightState->SetSuffer(pUserList->m_NowTargetID, pUser->GetDirection(), UserID);
		//150%的伤害
		EffectSkill(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID);
		m_pFightState->m_pList[pUserList->m_NowTargetID]->SetMagiSufferID(0x1D3FF13C, 1, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID]);


		if (pUserList->NextTarget(m_pFightState, sSkillID))
		{
			stage = 20;
		}
		else
		{
			sBuff buf;
			buf.ID = 1;
			SetDateBuffUp(UserID, UserID, sSkillID, buf, Skilllv);
			int outhp;
			Cost(outhp, Skilllv, sSkillID, UserID, 3, true);
			stage = 7;
		}


		stage = 2;
	}
		return  true;
	case 7:
		return StageWaitReturn(UserID, -1);
	}
	return true;
}






#endif