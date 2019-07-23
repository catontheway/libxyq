#include "CharacterData.h"
#include "eObj.h"


void GetWeaponType(int modeid, int& out1, int & out2)
{
	switch (modeid)
	{
	case eJuSe剑侠客:
		out1 = eWeaponType刀;
		out2 = eWeaponType剑;
		break;
	case eJuSe逍遥生:
		out1 = eWeaponType剑;
		out2 = eWeaponType扇;
		break;
	case eJuSe飞燕女:
		out1 = eWeaponType环;
		out2 = eWeaponType双剑;
		break;
	case eJuSe英女侠:
		out1 = eWeaponType双剑;
		out2 = eWeaponType鞭;
		break;
	case eJuSe虎头怪:
		out1 = eWeaponType锤;
		out2 = eWeaponType斧;
		break;
	case eJuSe巨魔王:
		out1 = eWeaponType斧;
		out2 = eWeaponType刀;
		break;
	case eJuSe骨精灵:
		out1 = eWeaponType爪;
		out2 = eWeaponType棒;
		break;
	case eJuSe狐美人:
		out1 = eWeaponType鞭;
		out2 = eWeaponType爪;
		break;
	case eJuSe龙太子:
		out1 = eWeaponType扇;
		out2 = eWeaponType枪;
		break;
	case eJuSe神天兵:
		out1 = eWeaponType枪;
		out2 = eWeaponType锤;
		break;
	case eJuSe玄彩蛾:
		out1 = eWeaponType棒;
		out2 = eWeaponType飘带;
		break;
	case eJuSe舞天姬:
		out1 = eWeaponType飘带;
		out2 = eWeaponType环;
		break;
	case eJuSe巫蛮儿:
		out1 = eWeaponType珠;
		out2 = eWeaponType杖;
		break;
	case eJuSe羽灵神:
		out1 = eWeaponType杖;
		out2 = eWeaponType弓;
		break;
	case eJuSe杀破狼:
		out1 = eWeaponType弓;
		out2 = eWeaponType珠;
		break;
	case eJuSe偃无师:
		out1 = eWeaponType巨剑;
		out2 = eWeaponType巨剑;
		break;
	case eJuSe桃夭夭:
		out1 = eWeaponType灯笼;
		out2 = eWeaponType灯笼;
		break;
	case eJuSe鬼潇潇:
		out1 = eWeaponType伞;
		out2 = eWeaponType伞;
		break;
	}
}


ulong sModelSound::GetSoundID(int Pos)
{
	switch (Pos)
	{
	case  POS_SOUNDATTACK:	return m_soundattack;
	case  POS_SOUNDMAGIC:	return m_soundmajic;
	case  POS_SOUNDDEF:		return m_sounddefend;
	case  POS_SOUNDSUFFER:	return m_soundsuffer;
	case  POS_SOUNDDEAD:	return m_sounddead;
	case  POS_SOUNDATTACK2:	return m_soundattack2;
	}
	return 0;
}





ulong sModelAction::GetID(int posid)
{
	switch (posid)
	{
	case POS_STAND:return m_stand;
	case POS_WALK:return m_walk;
	case POS_FIGHT_STAND:return m_fstand;
	case POS_RUN:return m_run;
	case POS_ATTACK:return m_attack;
	case POS_ATTACK2:return m_attack2;
	case POS_MAGIC:
	{
		// 轮回境
		if (m_magic == 0xBF358FFE)
		{
			int r = rand() % 100;
			if (r < 35)
			{
				return 0x6C1BFD1F;
			}
			else if (r > 65)
			{
				return 0x22413486;
			}
		}
		return m_magic;
	}
	case POS_DEF:return m_defend;
	case POS_SUFFER:return m_suffer;
	case POS_DEAD:return m_dead;
	case POS_RETURN:return m_return;
	}
	return 0;
}




bool sCharacterData::CanEquip(int EquipType)
{
	bool bBoy = true;
	switch (m_ID)
	{
	case eJuSe剑侠客:
		if (EquipType == 0 || EquipType == 1)
			return true;
		break;
	case eJuSe逍遥生:
		if (EquipType == 0 || EquipType == 5)
			return true;
		break;
	case eJuSe飞燕女:
		bBoy = false;
		if (EquipType == 10 || EquipType == 11)
			return true;
		break;
	case eJuSe英女侠:
		bBoy = false;
		if (EquipType == 11 || EquipType == 9)
			return true;
		break;
	case eJuSe虎头怪:
		if (EquipType == 3 || EquipType == 4)
			return true;
		break;
	case eJuSe巨魔王:
		if (EquipType == 1 || EquipType == 4)
			return true;
		break;
	case eJuSe骨精灵:
		bBoy = false;
		if (EquipType == 6 || EquipType == 7)
			return true;
		break;
	case eJuSe狐美人:
		bBoy = false;
		if (EquipType == 9 || EquipType == 6)
			return true;
		break;
	case eJuSe龙太子:
		if (EquipType == 5 || EquipType == 2)
			return true;
		break;
	case eJuSe神天兵:
		if (EquipType == 2 || EquipType == 3)
			return true;
		break;
	case eJuSe玄彩蛾:
		bBoy = false;
		if (EquipType == 7 || EquipType == 8)
			return true;
		break;
	case eJuSe舞天姬:
		bBoy = false;
		if (EquipType == 8 || EquipType == 10)
			return true;
		break;
	case eJuSe巫蛮儿:
		bBoy = false;
		if (EquipType == 12 || EquipType == 14)
			return true;
		break;
	case eJuSe羽灵神:
		if (EquipType == 14 || EquipType == 13)
			return true;
		break;
	case eJuSe杀破狼:
		if (EquipType == 13 || EquipType == 12)
			return true;
		break;
	case eJuSe偃无师:
		if (EquipType == eWeaponType巨剑)
			return true;
		break;
	case eJuSe桃夭夭:
		bBoy = false;
		if (EquipType == eWeaponType灯笼)
			return true;
		break;
	case eJuSe鬼潇潇:
		bBoy = false;
		if (EquipType == eWeaponType伞)
			return true;
		break;
	default:
		bBoy = false;
		if (EquipType == 11 || EquipType == 9)
			return true;
	}

	switch (EquipType)
	{
	case 15:
		return bBoy;
	case 16:
		return !bBoy;
	case 17:
		return bBoy;
	case 18:
		return !bBoy;
	case 19:
		return true;
	case 20:
		return true;
	case 21:
		return true;
	}

	return false;
}
















void sPetData::Read2(ifstream& File)
{
	File >> m_ID;
	string dustbin;
	File >> dustbin;
	File >> m_smallhead[0];
	File >> m_bighead[0];
	File >> m_dialoghead[0];
	File >> m_smallhead[1];

	if (!m_smallhead[0] && m_bighead[0])
	{
		m_smallhead[0] = m_bighead[0];
	}
	else if (m_smallhead[0] && !m_bighead[0])
	{
		m_bighead[0] = m_smallhead[0];
	}

	if (0 == m_smallhead[1])
	{
		m_smallhead[1] = m_smallhead[0];
		m_bighead[1] = m_bighead[0];
		m_dialoghead[1] = m_dialoghead[0];
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "大", m_bighead[0]);
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "小", m_smallhead[0]);
	}
	else
	{
		File >> m_bighead[1];
		File >> m_dialoghead[1];
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "大0", m_bighead[0]);
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "小0", m_smallhead[0]);

		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "大1", m_bighead[1]);
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "小1", m_smallhead[1]);

		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "进阶对话", m_dialoghead[1]);
	}
	ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "对话", m_dialoghead[0]);



	if (!m_smallhead[1] && m_bighead[1])
	{
		m_smallhead[1] = m_bighead[1];
	}
	else if (m_smallhead[1] && !m_bighead[1])
	{
		m_bighead[1] = m_smallhead[1];
	}

	if (!m_smallhead[0] && !m_bighead[0] && !m_smallhead[1] && !m_bighead[1])
	{
		m_smallhead[0] = m_smallhead[1] = 4050677707;
		m_bighead[0] = m_bighead[1] = 55973808;
	}

	int num;
	for (int i = 0; i < 4; i++)
	{
		File >> num;
		m_ComponentTable[i].resize(num);
		for (int j = 0; j < m_ComponentTable[i].size(); j++)
			File >> m_ComponentTable[i][j];
	}
	File >> num;
	m_ModelActs.resize(num);
	for (int i = 0; i < num; i++)
	{
		m_ModelActs[i].Read(File);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "攻", m_ModelActs[i].m_attack);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "攻2", m_ModelActs[i].m_attack2);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "防", m_ModelActs[i].m_defend);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "死", m_ModelActs[i].m_dead);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "战", m_ModelActs[i].m_fstand);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "法", m_ModelActs[i].m_magic);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "转", m_ModelActs[i].m_return);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "跑", m_ModelActs[i].m_run);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "站", m_ModelActs[i].m_stand);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "受", m_ModelActs[i].m_suffer);
		ccm::get()->pushBaby(ccm::get()->strDescTemp + "走", m_ModelActs[i].m_walk);
	}
	if (m_ID == 49)
	{
		std::swap(m_ModelActs[2].m_fstand, m_ModelActs[3].m_fstand);
	}
}

void sPetData::GetID(int positionid, int Pos, vector<ulong>& out)
{
	ulong testid;
	bool bdujie = false;
	if (positionid > 1)bdujie = true;

	testid = m_Sound[bdujie].GetSoundID(Pos);

	if (testid)
	{
		out.resize(1);
		out[0] = testid;
		return;
	}
	switch (Pos)
	{
	case POS_DIALOG:
	case POS_SMALLHEAD:
	case POS_BIGHEAD:
		if (1)
		{
			out.resize(1);
			switch (Pos)
			{
			case POS_DIALOG: out[0] = m_dialoghead[bdujie];	return;
			case POS_SMALLHEAD:out[0] = m_smallhead[bdujie];	return;
			case POS_BIGHEAD:out[0] = m_bighead[bdujie];	return;
			}
			return;
		}
		break;
	}
	//得到数量
	int num = m_ComponentTable[positionid].size();
	out.resize(num);
	for (int i = 0; i < num; i++)
	{
		sModelAction& lit = m_ModelActs[m_ComponentTable[positionid][i]];
		out[i] = lit.GetID(Pos);
	}
}

ulong sPetData::GetID(int positionid, int Pos)
{
	vector<ulong> out;
	GetID(positionid, Pos, out);
	return out[0];
}

void sPetData::ReadSound(ifstream& File)
{
	bool haveJinJie;
	string dustbin;
	File >> haveJinJie;
	File >> m_Sound[0].m_soundsuffer;
	File >> m_Sound[0].m_soundmajic;
	File >> m_Sound[0].m_soundattack;
	File >> m_Sound[0].m_sounddefend;
	File >> m_Sound[0].m_soundattack2;
	File >> m_Sound[0].m_sounddead;
	ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "攻", m_Sound[0].m_soundattack);
	ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "攻2", m_Sound[0].m_soundattack2);
	ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "死", m_Sound[0].m_sounddead);
	ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "法", m_Sound[0].m_soundmajic);
	ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "受", m_Sound[0].m_soundsuffer);
	ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "防", m_Sound[0].m_sounddefend);
	if (haveJinJie)
	{
		getline(File, dustbin);
		File >> m_Sound[1].m_soundsuffer;
		File >> m_Sound[1].m_soundmajic;
		File >> m_Sound[1].m_soundattack;
		File >> m_Sound[1].m_sounddefend;
		File >> m_Sound[1].m_soundattack2;
		File >> m_Sound[1].m_sounddead;
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "(进阶)攻", m_Sound[1].m_soundattack);
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "(进阶)攻2", m_Sound[1].m_soundattack2);
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "(进阶)死", m_Sound[1].m_sounddead);
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "(进阶)法", m_Sound[1].m_soundmajic);
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "(进阶)受", m_Sound[1].m_soundsuffer);
		ccm::get()->pushBabyHead(ccm::get()->strDescTemp + "(进阶)防", m_Sound[1].m_sounddefend);
	}
	else
	{
		m_Sound[1].m_soundsuffer = m_Sound[0].m_soundsuffer;
		m_Sound[1].m_soundmajic = m_Sound[0].m_soundmajic;
		m_Sound[1].m_soundattack = m_Sound[0].m_soundattack;
		m_Sound[1].m_sounddefend = m_Sound[0].m_sounddefend;
		m_Sound[1].m_soundattack2 = m_Sound[0].m_soundattack2;
		m_Sound[1].m_sounddead = m_Sound[0].m_sounddead;
	}
}



