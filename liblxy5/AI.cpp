#include "_global.h"
#include "_txt.h"

// 随机选择目标
// SelectType 是法术的类型
// 0 平时自己
// 1 平时己方
// 2 战斗自己
// 3 战斗己方
// 4 战斗敌方
// 5 平时战斗自己
// 6 平时战斗己方
// 7 被动
// 8 未
// 9 战斗己方but自己

int cAI::find追击反间月光(int userID, int SelectType, bool isCheckPeopleSpecial)
{
	auto ts = findSkillType2(userID, SelectType);
	if (ts.empty())
	{
		return -1;
	}
	int idlist[10];
	int existNum = ts.size();
	for (int i = 0; i < existNum; ++i)
	{
		idlist[i] = ts[i];
	}
	g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();

	vector<int> conducts;
	if (isSkillSeal(g_pMainState->m_FightWorkList[userID].m_SkillSelect.SkillID))
	{
		for (int i = 0; i < existNum; ++i)
		{
			if (g_pMainState->m_FightWorkList[i].m_pObj->m_ConductSeal.m_NeedShow)
			{
				conducts.push_back(i);
			}
		}
	}
	else
	{
		for (int i = 0; i < existNum; ++i)
		{
			if (g_pMainState->m_FightWorkList[i].m_pObj->m_ConductFire.m_NeedShow)
			{
				conducts.push_back(i);
			}
		}
	}
	if (conducts.size() > 0)
	{
		return conducts[rand() % conducts.size()];
	}

	return idlist[rand() % existNum];
}


vector<int> cAI::findSkillType2(int userID, int SelectType)
{
	//查找所有可选的ID
	int k = 10;
	switch (SelectType)
	{
	case 2: //只能对自己使用的法术
	case 5:
		return{ userID };
	case 3: //只能对我方使用的法术ww
	case 6:
		if (userID < 10)k = 0;
		break;
	case 4: //对敌人使用
		if (userID > 9)	k = 0;
		break;
	}
	int existNum = 0;
	int idlist[10];
	sFightWork* pList;
	int i2;
	cPropertyData *data = nullptr;
	g_pMainState->m_FightWorkList[userID].m_pObj->GetPropertyData(data);
	int peopleSpecail = 0;//data->PeopleSpecial.d1;
	for (int i = 0; i < 10; i++)
	{
		i2 = i + k;
		if (i2 == userID)
		{
			if (SelectType == 3 || SelectType == 6)
			{
				continue;
			}
		}
		//目标是否存在
		if (userID != i2)
		{
			pList = &g_pMainState->m_FightWorkList[i2];
			if (pList->isExist)
			{
				//目标是否活着
				if (!pList->CheckDie())
				{
					if (See(userID, i2))
					{
						idlist[existNum] = i2;
						existNum += 1;
					}
				}
			}
		}
	}
	//
	if (SelectType == 3 || SelectType == 6)
	{
		if (0 == existNum)
			return{ userID };
	}
	else if (0 == existNum)
		return vector<int>();

	vector<int> ts;
	for (int i = 0; i < existNum; ++i)
	{
		ts.push_back(idlist[i]);
	}
	return ts;
}


vector<int> cAI::findSkillType(int user, int skill)
{
	int ty = 4;
	if (skill > 1000 && skill < 2000)
	{
		return vector<int>();
	}
	if (skill != 1000)
	{
		ty = g_pMainState->m_SkillManager.GetSkill(skill)->m_SkillType;
	}
	return findSkillType2(user, ty);
}


int cAI::find空位(int ID, int Num, int bLive)
{
	if (Num < 0 || Num >19)
	{
		ERRBOX(Num);
		return -1;
	}
	int start, end;
	if (ID < 10)start = 0;
	else start = 10;
	end = start + 10;
	for (int i = start; i < end; i++)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[i];
		switch (bLive)
		{
		case 0://只找空位
			if (!list.isExist)return i;
			break;
		case 1://只找活物
			if ((0 == list.isExist) || list.CheckDie())
			{
			}
			else return i;
			break;
		case 2://只要存在就行
			if (list.isExist)
			{
				return i;
			}
			break;
		}
	}
	return -1;
}


int cAI::find溅射暗器(int usetId, int ID, int idx,int bLive)
{
	if (idx < 0 || idx > 19)
	{
		ERRBOX(idx);
		return -1;
	}
	int start, end;
	if (ID < 10)start = 0;
	else start = 10;
	end =start+ 10;

	int xpos = g_pMainState->m_pFightState->m_战斗坐标xs[ID];
	int ypos = g_pMainState->m_pFightState->m_战斗坐标ys[ID];
	int gaplist[10];
	int idlist[10];
	for (int i = 0; i < 10; i++)
	{
		idlist[i] = start + i;
	}
	int startgap = 0;
	cPropertyData *data = nullptr;
	g_pMainState->m_FightWorkList[usetId].m_pObj->GetPropertyData(data);
	int peopleSpecail = data->Hide.d2;
	for (int i = start; i < end; i++)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[i];
		switch (bLive)
		{
		case 0://只找空位
			if (list.isExist)
			{
				gaplist[startgap] = 999999;
				startgap += 1;	
				continue;
			}
			break;
		case 1://只找活物
			if ((0 == list.isExist) || list.CheckDie())
			{
				gaplist[startgap] = 999999;
				startgap += 1;
				continue;
			}
			break;
		case 2://只要存在就行
			if (!list.isExist)
			{
				gaplist[startgap] = 999999;
				startgap += 1;
				continue;
			}
			break;
		case 3: // 看得见的活物
			if ((0 == list.isExist) || list.CheckDie())
			{
				gaplist[startgap] = 999999;
				startgap += 1;
				continue;
			}
			cPropertyData *data2 = nullptr;
			g_pMainState->m_FightWorkList[i].m_pObj->GetPropertyData(data2);
			if (!peopleSpecail && data2->Hide.d1)
			{
				gaplist[startgap] = 999999;
				startgap += 1;
				continue;
			}
			break;
		}
		
		int xpos2 = g_pMainState->m_pFightState->m_战斗坐标xs[i];
		int ypos2 = g_pMainState->m_pFightState->m_战斗坐标ys[i];
		gaplist[startgap] = abs(xpos - xpos2) + ((abs(ypos - ypos2))<<1);
		startgap += 1;
	}
	int pa, pb;
	for (int a = 0; a < startgap-1; a++)
	for (int b = a + 1; b<startgap; b++)
	{
		pa = gaplist[a];
		pb = gaplist[b];
		if (pa>pb)//前数大于后数
		{
			swap(gaplist[a], gaplist[b]);
			swap(idlist[a], idlist[b]);
		}
	}//排序结果，当前位置Y小的在前。
	if (999999 == gaplist[idx])
		return -1;
	return idlist[idx];
}


void cAI::Escape(int userID)
{
// 	if (cct::get()->isForceEspace)
// 	{
// 		g_pMainState->m_pFightState->m_bEscape = true;
// 		return;
// 	}

	sFightWork& list = g_pMainState->m_FightWorkList[userID];
	list.m_WorkType = WORKTYPE_MAGIC;
	list.m_SkillSelect.SkillLv = 0;
	list.m_SkillSelect.SkillID = 1006;
	list.targetID = userID;
	list.m_SkillSelect.TargetID = userID;
}


void cAI::defense(int userID)
{
	if (!g_pMainState->m_FightWorkList[userID].isExist)return;
	cPropertyData* petdata;
	g_pMainState->m_FightWorkList[userID].m_pObj->GetPropertyData(petdata);
	if (petdata->m_FightData.cannotAll)return;
//	g_pMainState->m_AI.m_FightTarget[userID] = userID;
	sBuff buf;
	buf.remainingTimes = 1;
	g_pMainState->m_SkillManager.SetDateBuffUp(userID, userID, 1002, buf);
	g_pMainState->m_FightWorkList[userID].m_WorkType = -2;
}

void cAI::SetUser(int userid)
{
	if (m_UserID == userid)return;
	m_UserID = userid;
	pUserList = &g_pMainState->m_FightWorkList[userid];
	m_pUser = g_pMainState->m_FightWorkList[userid].m_pObj;
	if (m_pUser->m_IndexType==INDEXTYEP_CHARACTER)
		m_pUserPc=(cCharacter*)m_pUser->m_pIndex;
	else 
		m_pUserPc = 0;
	m_pUser->GetPropertyData(m_pUserData);
} 


bool cAI::Cost(int skillid)
{
	//检察一个技能是否可用,比如法术,MP不够,则返回0
//	int dubstbin;
// 	int skilllv = m_pUserData->m_Lv;
// 	if (skillid < 1000)
// 	{
// 		sSkill *skill = g_pMainState->m_SkillManager.GetMengPaiSkill(skillid);
// 		skilllv = m_pUserPc->m_PcData.m_MengPaiSkillLvs[skill->m_Owner];
// 	}
//	return g_pMainState->m_SkillManager.Cost(dubstbin, skilllv, skillid, m_UserID, 5, false);
	return g_pMainState->m_SkillManager.Cost(m_UserID, skillid, 1, false);
}


bool cAI::Cost(int user, int skill)
{
	if (skill >= 3000)
	{
		const auto& pc = ((cCharacter*)g_pMainState->m_FightWorkList[user].m_pObj->m_pIndex)->m_PcData;
		bool isFound = false;
		for (int i = 0; i < pc.m_NumofSpecial; ++i)
		{
			if (pc.m_SpecialSkillList[i] == skill - 3000)
			{
				isFound = true;
				break;
			}
		}
		if (!isFound)
		{
			return false;
		}
	}
	else if (skill >= 2000)
	{
		if (!g_pMainState->m_FightWorkList[user].m_pObj->getPropertyData()->isHadPetSkill(skill))
		{
			return false;
		}
	}

	return Cost(skill);
}


bool cAI::isHadPetSkill(cPropertyData *data, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills)
{
// 	if (!g_pMainState->m_FightList[userID].isExist)return false;
// 	cPetData *data = nullptr;
// 	g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
	if (!data)return false;
	vector<sSkill*> skills;
	for (int j = 0; j < data->m_NumofBBSkill; j++)
	{
		skills.push_back(data->m_petSkills[j]);
		continue;
		sSkill *skill = data->m_petSkills[j];
		int id = skill->m_Id;
		switch (skill->m_SkillType)
		{
		case 4:
			if (id == 92 || id == 93 || id == 94 || id == 95 || id == 96 || id == 98 || id == 99 || id == 100 || id == 102)
			{
				pSkills.push_back(id + 2000);
			}
			else if (g_pMainState->m_SkillManager.GetPetSkill(id)->m_TargetNum > 1)
			{
				m2Skills.push_back(id + 2000);
			}
			else
			{
				mSkills.push_back(id + 2000);
			}
			break;
		case 7:
			break;
		default:
			buffSkills.push_back(id + 2000);
			break;
		}
	}
	return isHadPetSkill(skills, buffSkills, pSkills, mSkills, m2Skills);
}

bool cAI::isHadPetSkill(const vector<sSkill*> &skills, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills)
{
	for (const auto &skill : skills)
	{
//		sSkill *skill = data->m_pPetSkill[j];
		int id = skill->m_Id + c_2000;
		switch (id)
		{
		case (int)eSkillPassive::吸血xx:
		case (int)eSkillPassive::高级吸血xx:
		case (int)eSkillPassive::连击lj:
		case (int)eSkillPassive::高级连击lj:
		case (int)eSkillPassive::必杀bs:
		case (int)eSkillPassive::高级必杀bs:
		case (int)eSkillPassive::强力ql:
		case (int)eSkillPassive::高级强力ql:
		case (int)eSkillPassive::偷袭tx:
		case (int)eSkillPassive::高级偷袭tx:
		case (int)eSkillPassive::合纵hz:
		case (int)eSkillPassive::高级合纵hz:
		case (int)eSkillPassive::嗜血追击sx:
		case (int)eSkillPassive::苍穹怒击cq:

		case (int)eSkill::善恶有报:
		case (int)eSkill::壁垒击破:
		case (int)eSkill::惊心一剑:
		case (int)eSkill::死亡召唤:
		case (int)eSkill::力劈华山:
		case (int)eSkill::剑荡四方:
			pSkills.push_back(id);
			break;
		case (int)eSkill::雷击:
		case (int)eSkill::落岩:
		case (int)eSkill::水攻:
		case (int)eSkill::烈火:
			mSkills.push_back(id);
			break;

		case (int)eSkill::奔雷咒:
		case (int)eSkill::泰山压顶:
		case (int)eSkill::水漫金山:
		case (int)eSkill::地狱烈火:
		case (int)eSkill::天降灵葫:
		case (int)eSkill::月光:
			m2Skills.push_back(id);
			break;

//		case (int)eSkill::夜舞倾城:
//		case (int)eSkill::法术防御:
		case (int)eSkillPassive::魔之心mz:
		case (int)eSkillPassive::高级魔之心mz:
		case (int)eSkillPassive::法术连击fs:
		case (int)eSkillPassive::高级法术连击fs:
		case (int)eSkillPassive::法术暴击fs:
		case (int)eSkillPassive::高级法术暴击fs:
		case (int)eSkillPassive::法术波动fs:
		case (int)eSkillPassive::高级法术波动fs:
		case (int)eSkillPassive::灵能激发ln:
		case (int)eSkillPassive::须弥真言xm:
		case (int)eSkillPassive::龙魂lh:
			buffSkills.push_back(id);
			break;
		}
// 		switch (skill->m_SkillType)
// 		{
// 		case 4:
// 			if (id == 92 || id == 93 || id == 94 || id == 95 || id == 96 || id == 98 || id == 99 || id == 100 || id == 102)
// 			{
// 				pSkills.push_back(id + 2000);
// 			}
// 			else if (g_pMainState->m_SkillManager.GetPetSkill(id)->m_TargetNum > 1)
// 			{
// 				m2Skills.push_back(id + 2000);
// 			}
// 			else
// 			{
// 				mSkills.push_back(id + 2000);
// 			}
// 			break;
// 		case 7:continue;
// 		default:
// 			buffSkills.push_back(id + 2000);
// 			break;
// 		}
	}



	for (const auto &skill : skills)
	{
		int id = skill->m_Id + c_2000;
		switch (id)
		{
		case (int)eSkill::善恶有报:
		case (int)eSkill::壁垒击破:
		case (int)eSkill::惊心一剑:
		case (int)eSkill::死亡召唤:
		case (int)eSkill::力劈华山:
		case (int)eSkill::剑荡四方:
			return true;
		}
	}
	return false;
}


bool cAI::Summon()
{
	cPcData& pc = m_pUserPc->m_PcData;
	if (m_UserID % 10 >= 5)
	{
		return false;
	}
	if (g_pMainState->m_FightWorkList[m_UserID + 5].isExist)
	{
		return false;
	}
	for (int j = 0; j < m_pUserPc->m_PcData.m_NumofBB; ++j)
	{
		cPet* pet = m_pUserPc->m_PcData.m_pPets[j];
		cPetData& pd = pet->m_PetData;
		if (pd._owerIdx < 0)
		{
			continue;
		}
		if (pd._owerIdx == pc.m_FightPetID)
		{
			continue;
		}
		if (pd.m_Lv > pc.m_Lv + cct::LvGapFromRoleAndBaby)
		{
			continue;
		}
		if (pet->GetData()->m_LvTake > pc.m_Lv)
		{
			continue;
		}

		g_pMainState->m_FightWorkList[m_UserID].m_SkillSelect.SkillID = 1004;
		g_pMainState->m_FightWorkList[m_UserID].m_SkillSelect.TargetID = /*g_pMainState->m_FightWorkList[m_UserID].m_FriendListid*/m_UserID + 5;
		g_pMainState->m_FightWorkList[m_UserID].m_SkillSelect.SkillLv = j;
		g_pMainState->m_FightWorkList[m_UserID].m_WorkType = WORKTYPE_SUMMON;
		((cCharacter*)g_pMainState->m_FightWorkList[m_UserID].m_pObj->getPropertyData())->m_PcData.m_pPets[j]->m_PetData._owerIdx = -1;
		return true;
	}
	return false;
}


int cAI::finds(bool CheckDie, bool bCheckWork, vector<POINT>& out, eEnemyType type, int userid, int data, int data2)
{
	out.clear();
	int ret=0;
	vector<POINT> out2;
	cPropertyData* pPet;
	POINT pt;
	cCharacter* pc;
	int randstart, randend;
	if (userid<10)randstart = 0; else randstart = 10;
	randend = randstart + 10;
	for (int i = randstart; i < randend; i++)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[i];

		if (list.m_pObj->m_IndexType == INDEXTYEP_CHARACTER)pc = (cCharacter*)list.m_pObj->m_pIndex;
		else pc = 0;
		if (!list.isExist)continue;
		list.m_pObj->GetPropertyData(pPet);
		if (bCheckWork)if (list.m_WorkType!=-1)continue;
		if (CheckDie)if (pPet->m_HP < 1)continue;
		
		if (-1 < data)
		if (list.m_pObj->CheckHaveState(data))
			continue;
		if (-1 < data2)
		if (list.m_pObj->CheckHaveState(data2))
			continue;
			switch (type)
			{
// 			case cAttackAI::eET攻宠:
// 				if (pc)continue;
			case cAI::eET上金刚33:
//				if (pPet->m_AddPoint.atk >= 1)//加了1力以上的定义为物理系
				if( (!pc && pPet->PointStr > pPet->m_Lv) || (pc && 
					pc->m_PcData.m_MengPaiID != eMP_方寸山 && 
					pc->m_PcData.m_MengPaiID != eMP_化生寺 &&
					pc->m_PcData.m_MengPaiID != eMP_普陀山 &&
					pc->m_PcData.m_MengPaiID != eMP_东海龙宫 &&
					pc->m_PcData.m_MengPaiID != eMP_魔王寨))
				{

					pt.x = i;
					pt.y = pPet->Atk.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._turnOfSpeed;
					out2.push_back(pt);
				}
				break;

			case cAI::eET上灵动112:
				if (!pc && pPet->PointMag > pPet->m_Lv)
				{
					pt.x = i;
					pt.y = pPet->Mana.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else if (pc && pc->m_PcData.m_MengPaiID != eMP_大唐官府 &&
					pc->m_PcData.m_MengPaiID != eMP_女儿村 &&
					pc->m_PcData.m_MengPaiID != eMP_普陀山 &&
					pc->m_PcData.m_MengPaiID != eMP_五庄观 &&
					pc->m_PcData.m_MengPaiID != eMP_阴曹地府 && 
					pc->m_PcData.m_MengPaiID != eMP_狮驼岭)
				{
					pt.x = i;
					pt.y = pPet->Mana.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._turnOfSpeed;
					out2.push_back(pt);
				}
				break;

			case cAI::eET封印对象:
// 					eMP_大唐官府,
// 					eMP_化生寺,
// 					eMP_女儿村,
// 					eMP_方寸山,
// 					eMP_狮驼岭,
// 					eMP_魔王寨,
// 					eMP_盘丝岭,
// 					eMP_阴曹地府,
// 					eMP_东海龙宫,
// 					eMP_五庄观,
// 					eMP_普陀山,
// 					eMP_天宫,
				if (pc && (pc->m_PcData.m_MengPaiID == eMP_方寸山 ||
					pc->m_PcData.m_MengPaiID == eMP_女儿村 ||
					pc->m_PcData.m_MengPaiID == eMP_盘丝岭 ||
					pc->m_PcData.m_MengPaiID == eMP_五庄观 ||
					pc->m_PcData.m_MengPaiID == eMP_天宫))
				{
					pt.x = i;
					pt.y = 20 - list._turnOfSpeed;
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._turnOfSpeed;
					out2.push_back(pt);
				}
				break;

// 			case cAttackAI::eET法宠:
// 				if (pc)continue;
			case cAI::eET速度最快2:
// 				if (pPet->m_AddPoint.mp >= 1)//加了1魔以上的定义为法系
// 				if ((!pc && pPet->m_ProPertyMag > pPet->m_Lv) || 
// 					(pc
// 					pc->m_PCData.m_MengPaiID != eMP_大唐官府 &&
// 					pc->m_PCData.m_MengPaiID != eMP_女儿村 &&
// 					pc->m_PCData.m_MengPaiID != eMP_普陀山 &&
// 					pc->m_PCData.m_MengPaiID != eMP_五庄观 &&
// 					pc->m_PCData.m_MengPaiID != eMP_阴曹地府 && 
// 					pc->m_PCData.m_MengPaiID != eMP_狮驼岭))
// 				if (!pc)
// 				{
// 					continue;
// 				}
				pt.x = i;
				pt.y = list._turnOfSpeed; // pPet->m_SPD.GetData();
				out.push_back(pt);
				ret += 1;
				break;
			case cAI::eET可封系:
				if (!pc)continue;
				if (pPet->m_FightData.cannotMagic)continue;
				switch (pc->m_PcData.m_MengPaiID)
				{
				case eMP_女儿村:
				case eMP_方寸山:
				case eMP_盘丝岭:
				case eMP_五庄观:
				case eMP_天宫:
					pt.x = i;
					pt.y = list._turnOfSpeed;
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAI::eET可法系:
				if (pPet->m_FightData.cannotMagic)continue;
				if ((pc && (pc->m_PcData.m_MengPaiID == eMP_东海龙宫 || pc->m_PcData.m_MengPaiID == eMP_魔王寨)) ||
					(!pc && pPet->PointMag > pPet->m_Lv * 3))
				{
					pt.x = i;
					pt.y = pPet->Mana.GetData();
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAI::eET可物理系:
				if (pPet->m_FightData.cannotMagic && pPet->m_FightData.cannotSpesialSkill)continue;
				if ((pc && (pc->m_PcData.m_MengPaiID == eMP_大唐官府 || pc->m_PcData.m_MengPaiID == eMP_狮驼岭)) ||
					(!pc && pPet->PointStr > pPet->m_Lv * 3))
				{
					pt.x = i;
					pt.y = pPet->Mana.GetData();
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAI::eET血最少:
				if (pPet->m_HP < 1)
					pt.y = 100;
				else
				{
					pt.y = (100 * pPet->m_HP) / pPet->HPMax.GetData();
					if (pt.y < m_HPLimit)ret += 1;
					pt.y = -pt.y;
				}
				pt.x = i;
				out.push_back(pt);
				break;
// 			case cAttackAI::eET需要蓝系:
// 				if (pc)
// 				{
// 					switch (pc->m_PCData.m_MengPaiID)
// 					{
// 					case eMP_大唐官府:continue;
// 					case eMP_东海龙宫:continue;
// 					case eMP_魔王寨:continue;
// 					default:
// 						pt.y = -(100 * pc->m_PCData.m_MP) / pc->m_PCData.m_MPMax.GetData();
// 						pt.x = i;
// 						out.push_back(pt);
// 						break;
// 					}
// 				}
// 				break;
			case cAI::eET医疗系:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
				if (!pc)continue;
				if (pc->m_PcData.m_HP < 1)continue;
				switch (pc->m_PcData.m_MengPaiID)
				{
//				case eMP_五庄观:
				case eMP_化生寺:
				case eMP_普陀山:
				case eMP_阴曹地府:
					pt.y = list._turnOfSpeed; // pPet->m_SPD.GetData();
					pt.x = i;
					out.push_back(pt);
					ret += 1;
					break;	
				}
				break;
// 			case cAttackAI::eET血宠:
// 				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
// 				if (pc)continue;		
// 				if (pPet->m_ProPertyHP > pPet->m_Lv * 2)
// 				{
// 					pt.x = i;
// 					pt.y = list._speedOfBattle; // pPet->m_SPD.GetData();
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET中死亡对象:
// 				if (!pc)continue;
// 				if (list.m_pData->CheckHaveState(2094) || list.m_pData->CheckHaveState(129))
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}	
// 				break;
			case cAI::eET防最低:
				pt.x = i;
				pt.y = -pPet->Def.GetData();
				out.push_back(pt);
				ret += 1;
				break;
			case cAI::eET灵最低:
				pt.x = i;
				pt.y = -pPet->Mana.GetData();
				out.push_back(pt);
				ret += 1;
				break;
// 			case cAttackAI::eET被封物理:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotAttack && !pc->m_PCData.PeopleSpecial.d2)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET被封法术:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotMagic)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET被禁疗:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotAddHP)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
			case cAI::eET无召唤兽:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
				if (i > 14)continue;
				if (!pc)continue;
				if (!g_pMainState->m_FightWorkList[i + 5].isExist)
				{
					for (int i2 = 0; i2 < pc->m_PcData.m_NumofBB; i2++)
					if (pc->m_PcData.m_pPets[i2]->m_PetData.m_HP > 1)
					{
						pt.x = i;
						pt.y = 1;
						out.push_back(pt);
						ret += 1;
					}
				}
				break;
			case cAI::eET人物死亡:
				if (!pc)continue;
				if (0 == pPet->m_HP)
				{
					if (list.m_pObj->CheckHaveState(2094))continue;//死亡
					if (list.m_pObj->CheckHaveState(129))continue;//锢魂术
					pt.x = i;
					pt.y = 1;
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAI::eET速度最快:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
// 				if (pc)
// 				{
// 					switch (pc->m_PCData.m_MengPaiID)
// 					{
// 					case eMP_化生寺:
// 					case eMP_阴曹地府:
// 					case eMP_普陀山:
// 						pt.y = pPet->m_SPD.GetData() * 5 / 4;
// 						break;
// 					case eMP_五庄观:
// 					case eMP_女儿村:
// 					case eMP_方寸山:
// 					case eMP_盘丝岭:
// 					case eMP_天宫:
// 						pt.y = pPet->m_SPD.GetData() * 6 / 4;
// 						break;
// 					default:
// 						pt.y = pPet->m_SPD.GetData() * 4 / 4;
// 						break;
// 
// 					}
// 				}
// 				else
// 				{
// 					pt.y = pPet->m_SPD.GetData() * 7 / 4;
// 				}

				pt.x = i;
				pt.y = list._turnOfSpeed;
				out.push_back(pt);
				ret += 1;
				break;
			case eET加血:
				if (list.CheckDie())continue;
				if (pPet->m_FightData.cannotAll)continue;
				if (pPet->Hide.d1)continue;
				if (pc)
				{
					switch (pc->m_PcData.m_MengPaiID)
					{
					case eMP_化生寺:
					case eMP_阴曹地府:
					case eMP_普陀山:
						pt.y = 10;			
						break;
					case eMP_五庄观:
						pt.y = 9;
						break;
					case eMP_女儿村:
					case eMP_方寸山:
					case eMP_盘丝岭:
					case eMP_天宫:
						pt.y = 5;
						break;
					default:
						pt.y = 4;
						break;

					}
				}
				else
				{
					pt.y = 5 + pPet->PointBody / (pPet->m_Lv + 1);
// 					if (pPet->m_ProPertyMag / pPet->m_Lv > pPet->m_ProPertyAtk / pPet->m_Lv)
// 					{
// 						pt.y = 14 - pPet->m_ProPertyMag / pPet->m_Lv;
// 					}
// 					else
// 					{
// 						pt.y = 14 - pPet->m_ProPertyAtk / pPet->m_Lv;
// 					}
				}
				pt.x = i;
				out.push_back(pt);
				ret += 1;
				break;
// 			case eET解封:
// 				if (list.CheckDie())break;
// 				if (pPet->m_FightProperty.cannotAll)break;
// 				if (pc)
// 				{
// 					pt.y = 1;
// 				}
// 				else
// 				{
// 					pt.y = 2 + pPet->m_ProPertyHP / (pPet->m_Lv + 1);
// 
// 					if (pPet->m_AddPoint.mp > 0 || pPet->m_AddPoint.atk > 0)
// 					{
// 						if (pPet->m_AddPoint.mp > 2 || pPet->m_AddPoint.atk > 2)
// 						{
// 							if (pPet->m_AddPoint.mp > 4 || pPet->m_AddPoint.atk > 4)
// 							{
// 								pt.y = 5;
// 							}
// 							else
// 							{
// 								pt.y = 4;
// 							}
// 						}
// 						else
// 						{
// 							pt.y = 3;
// 						}
// 						out.push_back(pt);
// 					}
// 					else
// 					{
// 						pt.y = 2;
// 					}
// 					break;
// 				}
// 				pt.x = i;
// 				out.push_back(pt);
// 				ret += 1;
// 				break;

			case cAI::eET佛法无边46:
				if (pc && (pc->m_PcData.m_MengPaiID == eMP_东海龙宫 || pc->m_PcData.m_MengPaiID == eMP_魔王寨))
				{
					pt.x = i;
					pt.y = pPet->Mana.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;

			case cAI::eET颠倒五行113:
				if (pc)
				{
					pt.x = i;
					pt.y = 0xffff - pPet->Mana.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAI::eET力劈华山95:
				{
					pt.x = i;
					pt.y = 0xffff - pPet->Atk.GetData() - pPet->Def.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAI::eET壁垒击破99:
				{
					pt.x = i;
					pt.y = pPet->ParryRate.d1;
					if (pt.y > 100)
					{
						pt.y = 100;
					}
					pt.y = pt.y * 10 + 0xffff - pPet->Def.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAI::eET锢魂术129:
				if (!pPet->m_Controler.GetFly())
				{
					int r = pPet->m_HP * 100 / pPet->HPMax.GetData();
					if (r < 20)
					{
						pt.x = i;
						pt.y = 100 - r;
						out.push_back(pt);
						ret += 1;
					}
				}
				break;

			case cAI::eET魂飞魄散127:
				if (pc)
				{
					int r = pPet->m_HP * 100 / pPet->HPMax.GetData();
					bool isok = false;
					for (std::list<sBuff>::iterator Iterator = list.m_pObj->m_StateList.begin(); Iterator != list.m_pObj->m_StateList.end();)
					{
						if (Iterator->remainingTimes > 2)
						{
							int id = Iterator->ID;
							if (id == 26 || id == 49 || id == 112 || id == 113 || id == 120 || id == 133)
							{
								isok = true;
							}
							if (id == 102 && r < 80)
							{
								isok = true;
							}
						}
						++Iterator;
					}
					
					if (isok)
					{
						pt.x = i;
						pt.y = 100 - r;
						out.push_back(pt);
						ret += 1;
					}
				}
				else
				{
					pt.x = i;
					pt.y = list._turnOfSpeed;
					out2.push_back(pt);
//					ret += 1;
				}
				break;
			case cAI::eET黄泉之息126:
				if (pc)
				{			
					pt.x = i;
					pt.y = list._turnOfSpeed;
					out.push_back(pt);
					ret += 1;
				}
				break;

			case cAI::eET反间6:
				if (!pPet->m_FightData.cannotAll && 
					!pPet->m_FightData.cannotAttack && 
					!pPet->m_FightData.cannotMagic &&
					!pPet->m_FightData.chaos混乱反间)
				{
					pt.x = i;
					pt.y = pPet->Atk.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;


			case cAI::eET鬼眼120:
				if (!pPet->Hide.d2)
				{
					pt.x = i;
					pt.y = list._turnOfSpeed;
					out.push_back(pt);
					ret += 1;
				}
				break;

			default:ERRBOX(0);
				return -1;
				}
		
	}
	if (out.size()>1)
	{//把最大的数排到最前面
		for (int i = 0; i < out.size()-1;i++)
		for (int j = i+1; j < out.size(); j++)
		{
			if (out[i].y < out[j].y)
			{
				swap(out[i].x, out[j].x);
				swap(out[i].y, out[j].y);
			}
		}
	}
	if (out2.size())
	{
		forv(out2, i)
		{
			out.push_back(out2[i]);
			if (type != eET上金刚33 && type != eET上灵动112 && type != eET魂飞魄散127)
			{
				++ret;
			}
		}
	}
	return ret;
}
