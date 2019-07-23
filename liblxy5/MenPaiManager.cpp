#include "_global.h"
#include "_txt.h"

//#define ccc_checkwas

static int getTargetNum(eSkill e)
{
	switch (e)
	{
	case eSkill::二龙戏珠:
	case eSkill::炼气化神:
	case eSkill::烟雨剑法:
	case eSkill::普渡众生:
	case eSkill::断岳势:
	case eSkill::摧心术:
		return 2;
	case eSkill::碎甲符:
	case eSkill::落雷符:
	case eSkill::天雷斩:
	case eSkill::雷霆万钧:
	case eSkill::飘渺式:
	case eSkill::天罗地网:
	case eSkill::天崩地裂:
	case eSkill::浪涌:
	case eSkill::惊涛怒:
	case eSkill::地涌金莲:
		return 3;
	case eSkill::横扫千军:
	case eSkill::破釜沉舟:
		return 4;
	case eSkill::日光华:
	case eSkill::靛沧海:
	case eSkill::巨岩破:
	case eSkill::苍茫树:
	case eSkill::地裂火:
	case eSkill::灵动九天:
	case eSkill::夺命咒:
	case eSkill::明光宝烛:
	case eSkill::金身舍利:
	case eSkill::密润:
		return 5;
	case eSkill::达摩护体:
	case eSkill::金刚护法:
	case eSkill::韦陀护法:
	case eSkill::金刚护体:
	case eSkill::一苇渡江:
	case eSkill::推气过宫:
	case eSkill::妙手回春:
	case eSkill::救死扶伤:
	case eSkill::生命之泉:
	case eSkill::飞砂走石:
	case eSkill::鹰击:
	case eSkill::连环击:
	case eSkill::翻江搅海:
	case eSkill::落叶萧萧:
		return 6;
	case eSkill::唧唧歪歪:
	case eSkill::雨落寒沙:
	case eSkill::龙卷雨击:
	case eSkill::阎罗令:
	case eSkill::幽冥鬼眼:
		return 7;
	case eSkill::龙吟:
		return 10;
	}
	return 1;
}

bool cMengPaiManager::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
// 	ifstream File;
// 	ostringstream oss;
// 	oss << g_pathData << "技能//师门技能.txt";
// 	// 	oss.str("");
// 	// 	oss << g_strSkillPath << "师门技能.txt";
// 	File.open(oss.str());
// 	int dustbin;
// 	File >> dustbin;
// 	if (dustbin != c_SkillNum)ERRBOX;
// 	for (int i = 0; i < c_SkillNum; i++)
// 	{
// 		sSkill& skill = m_SkillList[i];
// 		File >> skill.m_Id;
// 		File >> skill.m_Name;
// 		File >> skill.m_BigHead;
// 		File >> skill.m_SmallHead;
// 		File >> skill.m_SkillType;
// 		File >> skill.m_EffectType;
// 		File >> skill.m_Owner;
// 
// 		File >> skill.m_TargetNum;
// 		File >> skill.m_TargetNumOffset;
// 		File >> skill.m_MagicID;
// 		File >> skill.m_MagicPos;
// 		File >> skill.m_Text;
// 		File >> skill.m_tCost;
// 		/*	getline(File, skill.m_Text);
// 		getline(File, skill.m_Text);
// 		if (7 != skill.m_SkillType)
// 		getline(File, skill.m_tCost);*/
// 
// 		cct::get()->pushMpSkillHead(string("师门技能_") + skill.m_Name + "大", skill.m_BigHead);
// 		cct::get()->pushMpSkillHead(string("师门技能_") + skill.m_Name + "小", skill.m_SmallHead);
// 		cct::get()->pushMpSkill(string("师门技能_") + skill.m_Name + "动画", skill.m_MagicID);
// 	}
// 	File.close();
// 
// 
// 	oss.str("");
// 	oss << g_pathData << "技能//师门技能声音.txt";
// 	// 	oss.str("");
// 	// 	oss << g_strSkillPath << "师门技能声音.txt";
// 	File.open(oss.str());
// 	if (!File)
// 	{
// 		ERRBOX;
// 		File.close();
// 	}
// 	int soundnum;
// 	File >> soundnum;
// 	int soundid;
// 	string soundname;
// 	for (int i = 0; i < soundnum; i++)
// 	{
// 		File >> soundid;
// 		File >> soundname;
// 		File >> m_SkillList[i].m_Sound;
// 		cct::get()->pushMpSkillHead(string("师门技能声音_") + soundname, m_SkillList[i].m_Sound);
// 	}
// 	File.close();

	cWasFile was;
	const auto& sms = ctt::getSkills();
	forv(sms, k)
	{
		const auto& sm = sms[k];
		if ((int)sm.e >= c_SkillNum)
		{
			continue;
		}
		
		auto& s = m_SkillList[(int)sm.e];
		s.m_Id = (int)sm.e;
		s.m_Name = sm.name;
		s.m_BigHead = sm.big ? sm.big : 0xADEE4E4D;
		s.m_SmallHead = sm.small ? sm.small : 0x73C1B59D;
		s.m_SkillType = (int)sm.useType;
		s.m_EffectType = (int)sm.buffType;
		s.m_Owner = 0;
		s.m_TargetNum = getTargetNum(sm.e);
		s.m_TargetNumOffset = 0;
		s.m_MagicID = sm.uAct;
		s.m_MagicPos = sm.positiony;
		s.m_Cost = sm.costvalue;
		s.m_Text = sm.desc;
		s.m_tCostHpMp = s.m_tCost = sm.descCost;
		s.m_State = sm.state;
		s.m_Sound = sm.sound;

#ifdef ccc_checkwas
		was.Load(s.m_BigHead);
		was.Load(s.m_SmallHead);
		was.Load(s.m_MagicID);
		was.Load(s.m_Sound);
		was.Load(s.m_State);
#endif
	}



// 	oss.str("");
// 	oss << g_pathData << "技能//门派.txt";
// 	// 	oss.str("");
// 	// 	oss << g_strSkillPath << "门派.txt";
// 	File.open(oss.str());
// 	File >> dustbin;
// 	if (dustbin != c_NumMengPai)
// 	{
// 		ERRBOX;
// 		return false;
// 	}
// 	for (int i = 0; i < c_NumMengPai; i++)
// 	{
// 		File >> m_MengPai[i].m_ID;
// 		File >> m_MengPai[i].m_Name; //门派名
// 		File >> m_MengPai[i].m_ShiFuName;
// 		File >> m_MengPai[i].m_XunLuoMapName;
// 		File >> m_MengPai[i].m_ShiFuMap;
// 		for (int j = 0; j < 7; j++) //主技能
// 		{
// 			cZhuJiNeng&  zskill = m_MengPai[i].m_MainSkill[j];
// 			File >> zskill.m_ID;
// 			File >> zskill.m_Name;
// 			File >> zskill.m_BigHead;
// 			File >> zskill.m_SmallHead;
// 
// 			if (0 == zskill.m_BigHead)zskill.m_BigHead = 3416022732;
// 			if (0 == zskill.m_SmallHead)zskill.m_SmallHead = 3416022732;
// 			File >> zskill.m_NumSkillInclude;
// 
// 			cct::get()->pushMpHead(toString("门派%d_", i) + zskill.m_Name + "大", zskill.m_BigHead);
// 			cct::get()->pushMpHead(toString("门派%d_", i) + zskill.m_Name + "小", zskill.m_SmallHead);
// 
// 			for (int k = 0; k < zskill.m_NumSkillInclude; k++)//包含技能
// 			{
// 				File >> zskill.m_SkillIncludeID[k];
// 				File >> zskill.m_Limit技能解锁[k];
// 			}
// 			getline(File, zskill.m_Text);
// 			getline(File, zskill.m_Text);
// 			getline(File, zskill.m_Text2);
// 		}
// 	}
// 	File.close();

	const auto& mps = ctt::getMenpais();
	forv (mps, k)
	{
		const auto& mp = mps[k];
		auto& m = m_MengPai[k];
		m.m_ID = (int)mp.e;
		m.m_Name = mp.name; //门派名
		m.m_ShiFuName = mp.masterName;
		m.m_XunLuoMapName = mp.map;
		m.m_ShiFuMap = mp.masterMap;

		for (int i = 0; i < 7; ++i) //主技能
		{
			cZhuJiNeng&  zskill = m.m_MainSkill[i];
			const auto& z = mp.mains[i];
			zskill.m_ID = z.id;
			zskill.m_Name = z.name;
			zskill.m_BigHead = z.big;
			zskill.m_SmallHead = z.small;

			if (0 == zskill.m_BigHead)zskill.m_BigHead = 3416022732;
			if (0 == zskill.m_SmallHead)zskill.m_SmallHead = 3416022732;
			zskill.m_NumSkillInclude = z.skills.size();

			for (int j = 0; j < zskill.m_NumSkillInclude; j++)//包含技能
			{
				zskill.m_SkillIncludeID[j] = (int)z.skills[j].skill;
				zskill.m_Limit技能解锁[j] = (int)z.skills[j].lock;
			}
// 			getline(File, zskill.m_Text);
// 			getline(File, zskill.m_Text);
// 			getline(File, zskill.m_Text2);

#ifdef ccc_checkwas
			was.Load(zskill.m_BigHead);
			was.Load(zskill.m_SmallHead);
#endif
		}
	}

	return true;
}

cMengPai* cMengPaiManager::GetMengPai(cCharacter* pc)
{
	return GetMengPai(pc->m_PcData.m_MengPaiID);
}

#if 0
void cMengPaiManager::lvUpMainSkill(cPcData& pcDate, int lv, int ID, bool isHero /* = false */)
{
	if (ID > 7 || ID < 0)return;
	if (pcDate.m_MengPaiID < 0 || pcDate.m_MengPaiID>= c_NumMengPai)return;
	cZhuJiNeng* pZhuJiNeng = &m_MengPai[pcDate.m_MengPaiID].m_MainSkill[ID];
	int& skilllv = pcDate.m_MengPaiSkillLvs[ID];
	int prelv = skilllv;
	int nextlv = prelv + lv;
	if (!ID && !isHero)
	{
		switch (pcDate.m_MengPaiID)
		{
		case 0://大唐
			//		switch (ID)
			//		{
			// 		case 0:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 1:pcDate.AddSpdZZ(lv);break;
			// 		case 2:pcDate.AddHpZZ(7 * lv); break;
			// 		case 3:pcDate.AddAvoidZZ(lv); break;
			// 		case 4:
			// 			pcDate.AddGrowing(-prelv/10);
			// 			pcDate.AddGrowing(nextlv /10); 
			// 			break;
			// 		case 5:pcDate.AddDefZZ(3 * lv); break;
			// 		case 6:pcDate.AddMagZZ(2 * lv); break;
			//		}
			// 			pcDate.m_Spurting.d1 -= prelv / 10;
			// 			pcDate.m_Spurting.d1 += nextlv / 10;
			pcDate.Pierce刺穿.d1 -= prelv / 13;
			pcDate.Pierce刺穿.d1 += nextlv / 13;
			break;
		case 1://化生
			//		switch (ID)
			//		{
			// 		case 0:pcDate.AddSpdZZ( lv); break;
			// 		case 1:pcDate.AddAtkZZ( lv); break;
			// 		case 2:pcDate.AddMagZZ(3 * lv); break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv /10);
			// 			pcDate.AddGrowing(nextlv /10);
			// 			break;
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:pcDate.AddHpZZ(10 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ( lv); break;
			//		}

			pcDate.CriRateOfCure.d1 -= prelv / 10;
			pcDate.CriRateOfCure.d1 += nextlv / 10;
			break;
		case 2://女儿
			//		switch (ID)
			//		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:pcDate.AddAvoidZZ(3 * lv); break;
			// 		case 2:pcDate.AddDefZZ(2 * lv); break;
			// 		case 3:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 4:
			// 			pcDate.AddHpZZ(5 * lv);
			pcDate.Speed.AddDataAddPercent(-prelv / 20);
			pcDate.Speed.AddDataAddPercent(nextlv / 20);
			// 			break;
			// 		case 5:pcDate.AddMagZZ(2 * lv); break;
			// 		case 6:pcDate.AddSpdZZ(3 * lv); break;
			//		}
			break;
		case 3://方寸
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddDefZZ(lv); break;
			// 		case 1:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.ghostSpecial.d1 -= prelv / 4;
			pcDate.ghostSpecial.d1 += nextlv / 4;
			// 			break;
			// 		case 2:
			// 			pcDate.AddMagZZ(lv); 
			pcDate.MonsterSpecial.d1 -= prelv / 4;
			pcDate.MonsterSpecial.d1 += nextlv / 4;
			// 			break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 4:pcDate.AddHpZZ(7 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}
			break;
		case 4:  //狮驼
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddDefZZ(lv); break;
			// 		case 1:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 2:pcDate.AddHpZZ(10 * lv); break;
			// 		case 3:pcDate.AddMagZZ(3 * lv); break;
			// 		case 4:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 5:pcDate.AddAvoidZZ(lv); break;
			// 		case 6:pcDate.AddSpdZZ(lv); break;
			// 		}
			pcDate.SuckBloodPercent.d1 -= prelv / 20;
			pcDate.SuckBloodPercent.d1 += nextlv / 20;
			break;
		case 5://魔王
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			pcDate.CriRateOfMagic.d1 -= prelv / 15;
			pcDate.CriRateOfMagic.d1 += nextlv / 15;
			// 			break;
			// 		case 1:pcDate.AddMagZZ(5 * lv); break;
			// 		case 2:
			// 			pcDate.AddSpdZZ(-prelv / 2);
			// 			pcDate.AddSpdZZ(nextlv/2); 
			pcDate.MagicFire.d2 -= prelv / 10;
			pcDate.MagicFire.d2 += nextlv / 10;
			// 			break;
			// 		case 3:
			// 			pcDate.AddAtkZZ(2 * lv); 
			pcDate.MagicFire.d1 -= prelv / 10;
			pcDate.MagicFire.d1 += nextlv / 10;
			// 			break;
			// 		case 4:
			// 			pcDate.AddHpZZ(9 * lv);
			// 			break;
			// 		case 5:
			// 			pcDate.AddDefZZ(lv);
			pcDate.CounterRate.d1 -= prelv / 5;
			pcDate.CounterRate.d1 += nextlv / 5;
			// 			break;
			// 		case 6:
			// 			pcDate.AddAvoidZZ(-prelv / 2);
			// 			pcDate.AddAvoidZZ(nextlv/2); 
			// 			break;
			// 		}
			break;
		case 6://盘丝
			// 			switch (ID)
			// 			{
			// 			case 0:
			// 				pcDate.AddDefZZ(2* lv); 
			pcDate.DmgPercentOfArm.d2 -= prelv / 4;
			pcDate.DmgPercentOfArm.d2 += nextlv / 4;
			// 				break;
			// 			case 1: pcDate.AddMagZZ(4 * lv); break;
			// 			case 2:pcDate.AddHpZZ(7 * lv); break;
			// 			case 3:
			// 				pcDate.AddGrowing(-prelv / 10);
			// 				pcDate.AddGrowing(nextlv / 10);
			// 				break;
			// 			case 4:
			// 				pcDate.AddAtkZZ(3 * lv); break;	
			// 				break;
			// 			case 5:pcDate.AddAvoidZZ(3 * lv); break;
			// 			case 6:pcDate.AddSpdZZ(2* lv); break;
			// 			}
			break;
		case 7://地府
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			pcDate.HitRateOfSeal.d2 -= prelv / 10;
			pcDate.HitRateOfSeal.d2 += nextlv / 10;
			// 			break;
			// 		case 1:pcDate.AddAtkZZ(3 * lv); break;
			// 		case 2:pcDate.AddSpdZZ(1 * lv); break;
			// 		case 3:
			// 			pcDate.AddHpZZ(10 * lv); 
			//			pcDate.nightLv -= prelv / 10;
			//			pcDate.nightLv += nextlv / 10;
			// 			break;
			// 		case 4:pcDate.AddMagZZ(3 * lv); break;
			// 		case 5:
			// 			pcDate.AddDefZZ( lv);
			//			pcDate.poisonRate.d1 -= prelv / 10;//毒率
			//			pcDate.poisonRate.d1 += nextlv / 10;//毒率
			// 			break;
			// 		case 6:pcDate.AddAvoidZZ(lv); break;
			// 		}

			pcDate.DmgPercentOfFix.d1 -= prelv / 10;
			pcDate.DmgPercentOfFix.d1 += nextlv / 10;
			break;
		case 8://龙宫
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:
			// 			pcDate.AddMagZZ(5 * lv); 
			pcDate.MagicWater.d2 -= prelv / 10;
			pcDate.MagicWater.d2 += nextlv / 10;
			// 			break;
			// 		case 2:pcDate.AddHpZZ(5* lv); break;
			// 		case 3:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.MagicWater.d1 -= prelv / 10;
			pcDate.MagicWater.d1 += nextlv / 10;

			pcDate.Pierce刺穿OfMagic.d1 -= prelv / 13;
			pcDate.Pierce刺穿OfMagic.d1 += nextlv / 13;

			pcDate.CriRateOfMagic.d1 -= prelv / 40;
			pcDate.CriRateOfMagic.d1 += nextlv / 40;

			// 			break;		
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:pcDate.AddAvoidZZ(-prelv/2); 
			// 			pcDate.AddAvoidZZ(nextlv / 2); break;
			// 		case 6:pcDate.AddSpdZZ(-prelv/2); 
			// 			pcDate.AddSpdZZ(nextlv/ 2); break;
			// 		}
			break;
		case 9://五庄
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 2:pcDate.AddHpZZ(6 * lv); break;
			// 		case 3:pcDate.AddMagZZ(2 * lv); break;
			// 		case 4:pcDate.AddDefZZ(2 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}

			pcDate.ParryRate.d1 -= prelv / 10;
			pcDate.ParryRate.d1 += nextlv / 10;
			break;
		case 10://普陀
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddMagZZ(3 * lv); break;
			// 		case 1:pcDate.AddHpZZ(6 * lv); break;
			// 		case 2:pcDate.AddSpdZZ(lv); break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:
			// 			if (1)
		{
			//				pcDate.AddAtkZZ(lv);
			int data = prelv / 20;
			pcDate.MagicFire.d2 -= data; //火
			pcDate.MagicSoil.d2 -= data; //土
			pcDate.MagicWater.d2 -= data;  //水
			pcDate.MagicThunder.d2 -= data;//雷
			data = nextlv / 20;
			pcDate.MagicFire.d2 += data; //火
			pcDate.MagicSoil.d2 += data; //土
			pcDate.MagicWater.d2 += data;  //水
			pcDate.MagicThunder.d2 += data;//雷
		}

			pcDate.DmgPercentOfCure.d1 -= prelv / 10;
			pcDate.DmgPercentOfCure.d1 += nextlv / 10;

			// 			break;
			// 		case 6:pcDate.AddAvoidZZ(lv); break;
			// 		}
			break;
		case 11://天宫
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.MonsterSpecial.d1 -= prelv / 4;
			pcDate.MonsterSpecial.d1 += nextlv / 4;

			pcDate.HitRate.d2 -= prelv / 8;
			pcDate.HitRate.d2 += nextlv / 8;
			// 			break;
			// 		case 1:pcDate.AddHpZZ(6 * lv); break;
			// 		case 2:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 3:pcDate.AddDefZZ(2 * lv); break;
			// 		case 4:pcDate.AddMagZZ(2 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}
			break;
		default:
			ERRBOX;
			return;
		}
	}
	skilllv += lv;
	//	if (lv>0)
	for (int i = 0; i < pZhuJiNeng->m_NumSkillInclude; i++)
	{
		if (isHero || prelv < pZhuJiNeng->m_Limit技能解锁[i])
			if (skilllv >= pZhuJiNeng->m_Limit技能解锁[i])
			{
			//存在检测
			for (int j = 0; j < pcDate.m_SkillEnablelist.size(); j++)
			{
				if (pcDate.m_SkillEnablelist[j]->m_Id == pZhuJiNeng->m_SkillIncludeID[i])
					return;
			}
				sSkill* pSkill = &m_SkillList[pZhuJiNeng->m_SkillIncludeID[i]];
				pcDate.m_SkillEnablelist.push_back(pSkill);

			}
	}
}

#endif