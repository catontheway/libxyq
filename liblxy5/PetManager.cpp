#include "_global.h"
#include "_txt.h"

bool cPetManager::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
// 	int dustbin;
// 	int dustbin2;
// 	ifstream File;
// 	ostringstream oss;
// 	oss << g_pathData << "召唤兽//召唤兽新.txt";
// 	File.open(oss.str());
// 	File >> dustbin;
// 
// 	if (c_PetNumber != dustbin)
// 	{
// 		MessageBoxA(0, "加载召唤兽列表错误", "cPetManager:Init", MB_OK);
// 		return false;
// 	}
// 	for (int i = 0; i < c_PetNumber; i++)
// 	{
// 		cct::get()->strDescTemp = toString("召唤兽(编号%d)", i);
// 		m_PetList[i].Read2(File);
// 	}
// 	File.close();

	auto cb = [](ulong& u1, ulong& u2)
	{
		if (!u1 && u2)
		{
			u1 = u2;
		}
		else if (!u2 && u1)
		{
			u2 = u1;
		}
	};

	const auto& ps = ctt::getPets();
	const auto& cTable = ctt::getColors();
	forv(ps, k)
	{
		if (k >= c_PetNumber)
		{
			continue;
		}
		const auto& p = ps[k];
		auto& pet = m_PetList[k];

		pet.m_ID = (int)p.e;
		pet.m_Name = p.name;
		pet.m_Autorace = 0;
		pet.m_bSex = 0;



		pet.m_ID = (int)p.e;
		pet.m_smallhead[0] = p.small;
		pet.m_bighead[0] = p.big;
		pet.m_dialoghead[0] = p.dialog;
		pet.m_smallhead[1] = p.small2;
		pet.m_bighead[1] = p.big2;
		pet.m_dialoghead[1] = p.dialog2;

// 		cWasFile was;
// 		was.Load(pet.m_smallhead[0]);
// 		was.Load(pet.m_bighead[0]);
// 		was.Load(pet.m_dialoghead[0]);
// 		was.Load(pet.m_smallhead[1]);
// 		was.Load(pet.m_bighead[1]);
// 		was.Load(pet.m_dialoghead[1]);

		if (!pet.m_smallhead[0] && !pet.m_bighead[0]/* && !pet.m_smallhead[1] && !pet.m_bighead[1]*/)
		{
			pet.m_smallhead[0] = pet.m_smallhead[1] = 0x42475124;//0x42475124;//4050677707;
//			pet.m_bighead[0] = pet.m_bighead[1] = 0xADEE4E4D;//55973808;
		}

		cb(pet.m_smallhead[0], pet.m_bighead[0]);
		cb(pet.m_smallhead[0], pet.m_smallhead[1]);
		cb(pet.m_bighead[0], pet.m_bighead[1]);
		cb(pet.m_dialoghead[0], pet.m_dialoghead[1]);

		for (int i = 0; i < 4; i++)
		{
			pet.m_ComponentTable[i] = p.parts[i];
		}
		pet.m_ModelActs.resize(p.actions.size());
		forv(pet.m_ModelActs, i)
		{
			
			pet.m_ModelActs[i].m_ColorID = p.actions[i].color;
			const auto& it = cTable.find(pet.m_ModelActs[i].m_ColorID);
			if (it != cTable.end())
			{
				pet.m_ModelActs[i].m_ColorID = it->second;
			}

			const auto& a = p.actions[i].action;
			pet.m_ModelActs[i].m_attack = a.atk;
			pet.m_ModelActs[i].m_attack2 = a.atk2 ? a.atk2 : a.atk;
			pet.m_ModelActs[i].m_dead = a.dead;
			pet.m_ModelActs[i].m_defend = a.def;
			pet.m_ModelActs[i].m_stand = a.stand;
			pet.m_ModelActs[i].m_fstand = a.await;
			pet.m_ModelActs[i].m_magic = a.maigc;
			pet.m_ModelActs[i].m_return = a.back;
			pet.m_ModelActs[i].m_run = a.go;
			pet.m_ModelActs[i].m_suffer = a.atkd;
			pet.m_ModelActs[i].m_walk = a.walk;



// 			was.Load(pet.m_ModelActs[i].m_attack);
// 			was.Load(pet.m_ModelActs[i].m_attack2);
// 			was.Load(pet.m_ModelActs[i].m_defend);
// 			was.Load(pet.m_ModelActs[i].m_dead);
// 			was.Load(pet.m_ModelActs[i].m_fstand);
// 			was.Load(pet.m_ModelActs[i].m_magic);
// 			was.Load(pet.m_ModelActs[i].m_return);
// 			was.Load(pet.m_ModelActs[i].m_run);
// 			was.Load(pet.m_ModelActs[i].m_stand);
// 			was.Load(pet.m_ModelActs[i].m_walk);
// 			was.Load(pet.m_ModelActs[i].m_suffer);
		}

		
		pet.m_FightPoint[0].m_xOff = p.point1.offx;
		if (pet.m_FightPoint[0].m_xOff > 80)
		{
			pet.m_FightPoint[0].m_xOff = pet.m_FightPoint[0].m_xOff * 2 / 3;
		}
		pet.m_FightPoint[0].m_yOff = pet.m_FightPoint[0].m_xOff >> 1;
		pet.m_FightPoint[0].m_Point[0] = p.point1.atk1;
		pet.m_FightPoint[0].m_Point[1] = p.point1.atk2;
		pet.m_FightPoint[0].m_Point2[0] = p.point1.atk3;
		pet.m_FightPoint[0].m_Point2[1] = p.point1.atk4;
		pet.m_FightPoint[0].m_MagicPoint = p.point1.magic;

// 		auto &o = m_PetList[i].m_FightPoint[0];
// 		if (i == 84)
// 		{
// 			o.m_Point[0] = o.m_Point[1] = 5;
// 		}
// 		else if (i == 94)
// 		{
// 			o.m_Point[0] = o.m_Point[1] = 10;
// 			o.m_Point2[0] = o.m_Point2[1] = 10;
// 		}
// 		else if (i == 150)
// 		{
// 			o.m_Point[0] = o.m_Point[1] = 8;
// 		}

		pet.m_FightPoint[1].m_xOff = p.point2.offx;
		pet.m_FightPoint[1].m_yOff = pet.m_FightPoint[0].m_xOff >> 1;
		pet.m_FightPoint[1].m_Point[0] = p.point2.atk1;
		pet.m_FightPoint[1].m_Point[1] = p.point2.atk2;
		pet.m_FightPoint[1].m_Point2[0] = p.point2.atk3;
		pet.m_FightPoint[1].m_Point2[1] = p.point2.atk4;
		pet.m_FightPoint[1].m_MagicPoint = p.point2.magic;
// 		if (pet.m_ID == 49)
// 		{
// 			std::swap(pet.m_ModelActs[2].m_fstand, pet.m_ModelActs[3].m_fstand);
// 		}



		pet.m_Sound[0].m_soundsuffer = p.sound1.atkd;
		pet.m_Sound[0].m_soundmajic = p.sound1.magic;
		pet.m_Sound[0].m_soundattack = p.sound1.atk;
		pet.m_Sound[0].m_sounddefend = p.sound1.def;
		pet.m_Sound[0].m_soundattack2 = p.sound1.atk2;
		pet.m_Sound[0].m_sounddead = p.sound1.dead;

		pet.m_Sound[1].m_soundsuffer = p.sound2.atkd;
		pet.m_Sound[1].m_soundmajic = p.sound2.magic;
		pet.m_Sound[1].m_soundattack = p.sound2.atk;
		pet.m_Sound[1].m_sounddefend = p.sound2.def;
		pet.m_Sound[1].m_soundattack2 = p.sound2.atk2;
		pet.m_Sound[1].m_sounddead = p.sound2.dead;


// 		was.Load(pet.m_Sound[0].m_soundsuffer);
// 		was.Load(pet.m_Sound[0].m_soundmajic);
// 		was.Load(pet.m_Sound[0].m_soundattack);
// 		was.Load(pet.m_Sound[0].m_sounddefend);
// 		was.Load(pet.m_Sound[0].m_soundattack2);
// 		was.Load(pet.m_Sound[0].m_sounddead);
// 
// 		was.Load(pet.m_Sound[1].m_soundsuffer);
// 		was.Load(pet.m_Sound[1].m_soundmajic);
// 		was.Load(pet.m_Sound[1].m_soundattack);
// 		was.Load(pet.m_Sound[1].m_sounddefend);
// 		was.Load(pet.m_Sound[1].m_soundattack2);
// 		was.Load(pet.m_Sound[1].m_sounddead);
	}


//	ifstream File2;
// 	oss.str("");
// 	oss << g_pathData << "召唤兽//召唤兽战斗偏移表.txt";
// 	File2.open(oss.str());
//	oss.str("");
//	oss << g_pathData << "召唤兽//召唤兽.txt";
// 	oss << g_pathData << "召唤兽.txt";
// 	File.open(oss.str());
// 	File >> dustbin;
//	File2 >> dustbin2;
// 	if (dustbin2 != dustbin)
// 	{
// 		ERRBOX;
// 		return false;
// 	}
//	string dustbinstring;
//	if (c_PetNumber != dustbin)return false;
//	bool offsetnum;
	sZiZhi zzSS, zzNpc;
	zzSS.Set(1400, 1400, 2500, 4500, 1200, 1200, 125);
	zzNpc.Set(1400, 1400, 2700, 4800, 1200, 1200, 125);
	const auto& zs = ctt::getPetZZs();
	auto cb2 = [&](int i, const ctt::sPetZZ& z)
	{
		m_PetList[i].m_addPointType = z.ap;
		m_PetList[i].m_ZiZhi.atk = z.atk;
		m_PetList[i].m_ZiZhi.def = z.def;
		m_PetList[i].m_ZiZhi.hp = z.hp;
		m_PetList[i].m_ZiZhi.mag = z.mp;
		m_PetList[i].m_ZiZhi.speed = z.spd;
		m_PetList[i].m_ZiZhi.avoid = z.evo;
		m_PetList[i].m_ZiZhi.grow = z.gro;
		m_PetList[i].m_SkillNum = z.skills.size();
		for (int j = 0; j < m_PetList[i].m_SkillNum; j++)
		{
			if (z.skills[j] == 10086)
			{
				m_PetList[i].m_pPetSkill[j] = g_pMainState->m_SkillManager.GetPetSkill(84 + 2 * (rand() % 4));
				continue;
			}
			m_PetList[i].m_pPetSkill[j] = g_pMainState->m_SkillManager.GetPetSkill(z.skills[j]);

		}
	};

	auto cb3 = [&](int i, eModel e)
	{
		const auto& z = zs.at(e);
		cb2(i, z);
	};

	for (int i = 0; i < c_PetNumber; i++)
	{
//
// 		m_PetList[i].m_FightPoint[0].ReadPet(File2);
// 		// 恰好没有offsetnum
// 		auto &o = m_PetList[i].m_FightPoint[0];
// 		if (i == 84)
// 		{
// 			o.m_Point[0] = o.m_Point[1] = 5;
// 		}
// 		else if (i == 94)
// 		{
// 			o.m_Point[0] = o.m_Point[1] = 10;
// 			o.m_Point2[0] = o.m_Point2[1] = 10;
// 		}
// 		else if (i == 150)
// 		{
// 			o.m_Point[0] = o.m_Point[1] = 8;
// 		}
// 		File2 >> offsetnum;
// 		getline(File2, dustbinstring);
// 		if (offsetnum)
// 		{
// 			m_PetList[i].m_FightPoint[1].ReadPet(File2);
// 		}
// 		else
// 		{
// 			m_PetList[i].m_FightPoint[1] = m_PetList[i].m_FightPoint[0];
// 		}

		if (i == (int)eModel::小泡泡xp)
		{
			cb3(i, eModel::超级泡泡cj);
		}
		else if (i == (int)eModel::小象xx)
		{
			cb3(i, eModel::大象dx);
		}
		else if (i == (int)eModel::小白泽xb)
		{
			cb3(i, eModel::白泽bz);
		}
		else 
		{
			const auto& z = zs.at(ps[i].e);
			m_PetList[i].m_LvTake = z.lv; //携带等级
			cb2(i, z);
			if (ps[i].e >= eModel::小毛头xm && ps[i].e <= eModel::小魔头xm || ps[i].e == eModel::无痕wh || ps[i].e == eModel::剑灵jl || z.lv == 115)
			{
				m_PetList[i].m_ZiZhi = zzNpc;
			}
			else if (z.lv == 0)
			{
				m_PetList[i].m_ZiZhi = zzSS;
			}
		}
// 		else
// 		{
// 			File >> m_PetList[i].m_ID;
// 			File >> m_PetList[i].m_Name;
// 			File >> m_PetList[i].m_Autorace;
// 			File >> m_PetList[i].m_bSex;
// 			File >> m_PetList[i].m_LvTake; //携带等级
// 
// 			File >> m_PetList[i].m_ZiZhi.atk;
// 			File >> m_PetList[i].m_ZiZhi.def;
// 			File >> m_PetList[i].m_ZiZhi.hp;
// 			File >> m_PetList[i].m_ZiZhi.mag;
// 			File >> m_PetList[i].m_ZiZhi.speed;
// 			File >> m_PetList[i].m_ZiZhi.avoid;
// 			File >> m_PetList[i].m_ZiZhi.grow;
// 			File >> m_PetList[i].m_SkillNum;
// 		}



// 		if (m_PetList[i].m_LvTake >= 85)
// 		{
// 			int per = (m_PetList[i].m_LvTake + 5) / 10;
// 			int &atk = m_PetList[i].m_ZiZhi.atk;
// 			int &def = m_PetList[i].m_ZiZhi.def;
// 			int &hp = m_PetList[i].m_ZiZhi.hp;
// 			int atk2 = 900 + 38 * per;
// 			int def2 = 500 + 60 * per;
// 			int hp2 = 1000 + 333 * per;
// 			if (atk < atk2) atk = atk2;
// 			if (def < def2) def = def2;
// 			if (hp < hp2) hp = hp2;
// 		}
// 
// 
// 
// 		if (i == e大海龟) // 大海龟
// 		{
// 			m_PetList[i].m_LvTake = 5;
// 		}
// 		else if (i == e花妖) // 花妖 15
// 		{
// 			m_PetList[i].m_LvTake = 15;
// 		}
// 		else if (i == e超级人参娃娃 || (i >= e超级泡泡 && i <= e小魔头) || i == e超级神龙 || i == e腾蛇 || (i >= e超级玉兔 && i <= e超级麒麟) || i == e超级神羊 || i == e六耳猕猴)
// 		{
// 			m_PetList[i].m_LvTake = 0;
// 			m_PetList[i].m_ZiZhi.atk = 1500;
// 			m_PetList[i].m_ZiZhi.def = 1500;
// 			m_PetList[i].m_ZiZhi.hp = 7750;
// 			m_PetList[i].m_ZiZhi.mag = 2750;
// 			m_PetList[i].m_ZiZhi.speed = 1450;
// 		}

// 		const auto& z = m_PetList[i].m_ZiZhi;
// 		string str = "{eModel::" + ctt::getName((eModel)m_PetList[i].m_ID) + ",{";
// 		str += toString("%d,%d,%d,%d,%d,%d,%d,%d,{", m_PetList[i].m_LvTake, z.atk, z.def, z.hp, z.mag, z.speed, z.avoid, z.grow);
// 
// 		for (int j = 0; j < m_PetList[i].m_SkillNum; j++)
// 		{
// 			File >> dustbin;
// 			m_PetList[i].m_pPetSkill[j] = g_pMainState->m_SkillManager.GetPetSkill(dustbin);
// 			str += toString("%d,", dustbin);
// 		}
// 		if (m_PetList[i].m_SkillNum > 0)
// 		{
// 			str.pop_back();
// 		}
// 		str += "}}},";
// 		Q_LOG(str.c_str());

// 		if (i == e超级灵鹿)
// 		{
// 			vector<int> ss = { 48, 50, 56, 58, 60, 85, 87, 89, 91, 103, 105 };
// 			m_PetList[i].m_SkillNum = ss.size();
// 			forv(ss, j)
// 			{
// 				m_PetList[i].m_pPetSkill[j] = g_pMainState->m_SkillManager.GetPetSkill(ss[j]);
// 			}
// 		}
// 		else if (i == e超级神兔 || i == e超级玉兔)
// 		{
// 			m_PetList[i].m_SkillNum = 4;
// 			m_PetList[i].m_pPetSkill[0] = g_pMainState->m_SkillManager.GetPetSkill(48);
// 			m_PetList[i].m_pPetSkill[1] = g_pMainState->m_SkillManager.GetPetSkill(58);
// 			m_PetList[i].m_pPetSkill[2] = g_pMainState->m_SkillManager.GetPetSkill(103);
// 			m_PetList[i].m_pPetSkill[3] = g_pMainState->m_SkillManager.GetPetSkill(105);
// 		}
		// 		else if (i == e火星人)
		// 		{
		// 			m_PetList[i].m_LvLimit = 0;
		// 			m_PetList[i].m_ZiZhi.m_ATKZZ = 1700;
		// 			m_PetList[i].m_ZiZhi.m_HPZZ = 5850;
		// 			vector<int> ss = { 5, 19, 24, 50, 92, 93, 94, 95, 96, 97, 98, 99, 100, 102 };
		// 			m_PetList[i].m_SkillNum = ss.size();
		// 			forv(ss, j)
		// 			{
		// 				m_PetList[i].m_pPetSkill[j] = g_pMainState->m_SkillManager.GetPetSkill(ss[j]);
		// 			}
		// 		}


	}
//	File.close();
//	File2.close();
//
// 	oss.str("");
// 	oss << g_pathData << "召唤兽//召唤兽声音.txt";
// 	File.open(oss.str());
// 
// 	int numsound;
// 	File >> numsound;
// 	for (int i = 0; i < numsound; i++)
// 	{
// 		cct::get()->strDescTemp = toString("召唤兽声音(编号%d)", i);
// 		m_PetList[i].ReadSound(File);
// 		getline(File, dustbinstring);
// 	}
// 	File.close();



// 	for (auto i : cct::get()->newBabys)
// 	{
// 		File.open(g_pathNewBaby + toString("%d.txt", i));
// 		if (!File)
// 		{
// 			File.close();
// 			continue;
// 		}
// 		Init(i, File);
// 		File.close();
// 	}

	return true;
}


void cPetManager::Init(int i, ifstream &File)
{
	m_PetList[i].m_ID = i;
	File >> m_PetList[i].m_Name;
	File >> m_PetList[i].m_Autorace;
	File >> m_PetList[i].m_bSex;
	File >> m_PetList[i].m_LvTake; //携带等级

	File >> m_PetList[i].m_ZiZhi.atk;
	File >> m_PetList[i].m_ZiZhi.def;
	File >> m_PetList[i].m_ZiZhi.hp;
	File >> m_PetList[i].m_ZiZhi.mag;
	File >> m_PetList[i].m_ZiZhi.speed;
	File >> m_PetList[i].m_ZiZhi.avoid;
	File >> m_PetList[i].m_ZiZhi.grow;
	File >> m_PetList[i].m_SkillNum;
	int dustbin;
	for (int j = 0; j < m_PetList[i].m_SkillNum; j++)
	{
		File >> dustbin;
		m_PetList[i].m_pPetSkill[j] = g_pMainState->m_SkillManager.GetPetSkill(dustbin);
	}
	string temp;
	getline(File, temp);
	// 偏移
	m_PetList[i].m_FightPoint[0].ReadPet(File);
	File >> dustbin;
	getline(File, temp);
	if (dustbin)
	{
		m_PetList[i].m_FightPoint[1].ReadPet(File);
		getline(File, temp);
	}
	else
	{
		m_PetList[i].m_FightPoint[1] = m_PetList[i].m_FightPoint[0];
	}
	// 声音
	m_PetList[i].ReadSound(File);
	getline(File, temp);

	// 新
	File >> m_PetList[i].m_smallhead[0];
	File >> m_PetList[i].m_bighead[0];
	File >> m_PetList[i].m_dialoghead[0];
	File >> m_PetList[i].m_smallhead[1];
	if (0 == m_PetList[i].m_smallhead[1])
	{
		m_PetList[i].m_smallhead[1] = m_PetList[i].m_smallhead[0];
		m_PetList[i].m_bighead[1] = m_PetList[i].m_bighead[0];
		m_PetList[i].m_dialoghead[1] = m_PetList[i].m_dialoghead[0];
	}
	else
	{
		File >> m_PetList[i].m_bighead[1];
		File >> m_PetList[i].m_dialoghead[1];
	}
	for (int k = 0; k < 4; k++)
	{
		File >> dustbin;
		m_PetList[i].m_ComponentTable[k].resize(dustbin);
		for (int j = 0; j < m_PetList[i].m_ComponentTable[k].size(); j++)
			File >> m_PetList[i].m_ComponentTable[k][j];
	}
	File >> dustbin;
	m_PetList[i].m_ModelActs.resize(dustbin);
	for (int k = 0; k < dustbin; k++)
	{
		m_PetList[i].m_ModelActs[k].Read(File);
	}
}


void cPetManager::GetLimitList(int lv, vector<int>& idlist, int stronglv)
{
	//0级就大海龟 其它都是稀有召唤兽
	if (lv < 5)return  idlist.push_back(1);
	idlist.clear();
	int maxn, minn;
	maxn = lv + 1;
	minn = lv - 50 + stronglv / 5;
	if (minn < 1)minn = 1;
	for (int i = 0; i < c_PetNumber; i++)
	{
		// 狼: 子犯大神真任性, 金身罗汉说不要就不要.. - -
		if (m_PetList[i].m_LvTake < maxn&&m_PetList[i].m_LvTake>minn)
		{
			if (m_PetList[i].m_ID == 92)
				continue;//金身罗汉太难看,不要
			idlist.push_back(i);
		}
	}

}