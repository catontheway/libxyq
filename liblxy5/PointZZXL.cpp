#include "PointZZXL.h"
#include "MyMath.h"

void sAddPoint::Save(ofstream& File)
{
	//加点
	File << g_strSpace;
	File << str << g_strSpace;
	File << dex << g_strSpace;
	File << body << g_strSpace;
	File << mag << g_strSpace;
	File << agi << g_strSpace;
	File << remain << g_strSpace;
}

void sAddPoint::Load(ifstream& File)
{
	File >> str;
	File >> dex;
	File >> body;
	File >> mag;
	File >> agi;
	File >> remain;
	if (str + dex + mag + body + agi > 5)
	{
		ERRBOX2(0);
	}
}






void sZiZhi::Save(sOstream& File)
{
	File << g_strSpace;
	File << atk << g_strSpace;
	File << def << g_strSpace;
	File << hp << g_strSpace;
	File << mag << g_strSpace;
	File << speed << g_strSpace;
	File << avoid << g_strSpace;
	File << grow << g_strSpace;
}

void sZiZhi::Load(sIstream& File)
{
	File >> atk;
	File >> def;
	File >> hp;
	File >> mag;
	File >> speed;
	File >> avoid;
	File >> grow;

	atk = min(atk, 1800);
	def = min(def, 1800);
	hp = min(hp, 8000);
	mag = min(mag, 4000);
	speed = min(speed, 2000);
	avoid = min(avoid, 2000);
	grow = min(grow, 130);
}






int sBBXiuLian::AddExp(int maxlv, int num, eXiuLian type)
{
	int* Skilllv = 0;
	int* SkillExp = 0;
	switch (type)
	{
	case eXLATK:
		Skilllv = &atk;
		SkillExp = &atkExp;
		break;
	case eXLDEF:
		Skilllv = &def;
		SkillExp = &defExp;
		break;
	case eXLMAG:
		Skilllv = &mag;
		SkillExp = &magExp;
		break;
	case eXLDMAG:
		Skilllv = &dmag;
		SkillExp = &dmagExp;
		break;
	}
// 	int maxlv = lv - 20;
// 	if (maxlv < 0)maxlv = 0;
// 	maxlv /= 5;
// 	if (maxlv > 30)maxlv = 30;
	if (*Skilllv >= maxlv)
	{
		//当前等级的最大修炼等级
		return 0;
	}
	int maxexp = GetXiuLIanExp(*Skilllv + 1);
	*SkillExp += num;
	if (*SkillExp >= maxexp)
	{
		AddXiuLianLv(1, type);
		*SkillExp -= maxexp;
		return 2;
	}
	return 1;
}

void sBBXiuLian::AddXiuLianLv(int num, eXiuLian type)
{
	switch (type)
	{
	case eXLATK:
		atk += num;
		break;
	case eXLDEF:
		def += num;
		break;
	case eXLMAG:
		mag += num;
		break;
	case eXLDMAG:
		dmag += num;
		break;
	}
}



void sBBXiuLian::lvdown(int lv)
{
	while (atk > lv)
	{
		atkExp += GetXiuLIanExp(atk);
		--atk;
	}
	while (def > lv)
	{
		defExp += GetXiuLIanExp(def);
		--def;
	}
	while (mag > lv)
	{
	//	magExp += GetXiuLIanExp(mag);
		--mag;
	}
	while (dmag > lv)
	{
	//	dmagExp += GetXiuLIanExp(dmag);
		--dmag;
	}
}



void sBBXiuLian::Save(sOstream& File)
{
	//修炼
	File << g_strSpace;
	File << atk << g_strSpace;
	File << def << g_strSpace;
	File << mag << g_strSpace;
	File << dmag << g_strSpace;

	File << atkExp << g_strSpace;
	File << defExp << g_strSpace;
	File << magExp << g_strSpace;
	File << dmagExp << g_strEnter;
}

void sBBXiuLian::Load(sIstream& File)
{
	//修炼
	File >> atk;
	File >> def;
	File >> mag;
	File >> dmag;

	File >> atkExp;
	File >> defExp;
	File >> magExp;
	File >> dmagExp;
}

