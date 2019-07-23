#pragma once
#include "_asert.h"

struct sAddPoint
{
	void Save(ofstream& File);
	void Load(ifstream& File);
	int str = 5;
	int dex = 0;
	int body = 0;
	int mag = 0;
	int agi = 0;
	int remain = 0;
	void Set(int str2, int dex2, int mag2, int body2, int agi2)
	{
		str = str2;
		dex = dex2;
		body = body2;
		mag = mag2;
		agi = agi2;
	}
	void operator=(sAddPoint& target)
	{
		str = target.str;
		dex = target.dex;
		body = target.body;
		mag = target.mag;
		agi = target.agi;
		remain = target.remain;
	}
};



struct sZiZhi
{
	//资质
	int atk = 0;
	int def = 0;
	int mag = 0;
	int hp = 0;
	int speed = 0;
	int avoid = 0;
	int grow = 0;
	void Save(sOstream& File);
	void Load(sIstream& File);
	void Set(int atk2, int def2, int mag2, int hp2, int spd, int avoid2, int grow2)
	{
		atk = atk2;
		def = def2;
		hp = hp2;
		mag = mag2;
		avoid = avoid2;
		speed = spd;
		grow = grow2;
	}
	//成长
// 	void Set(sZiZhi& zishi, int strong, int takeLv)
// 	{
// 		int ZiZhiOffset = 100 + (takeLv*strong) / 100;
// 		atk = zishi.atk + rand() % (ZiZhiOffset);
// 		def = zishi.def + rand() % (ZiZhiOffset);
// 		mag = zishi.mag + rand() % (2 * (ZiZhiOffset));
// 		hp = zishi.hp + rand() % (4 * (ZiZhiOffset));
// 		speed = zishi.speed + rand() % (ZiZhiOffset);
// 		avoid = zishi.avoid + rand() % (ZiZhiOffset);
// 		grow = zishi.grow + rand() % ((ZiZhiOffset) >> 2);
// 
// 		speed = zishi.speed /** 6 / 5*/ + rand() % (ZiZhiOffset);
//		m_Growing = 142 + (rand() % 3) - (rand() % 3);
//		Set(1600, 1600, 3200, 6400, m_SPDZZ, 1600, m_Growing);
//	}

	void operator=(sZiZhi& zizhi)
	{
		//资质
		atk = zizhi.atk;
		def = zizhi.def;
		mag = zizhi.mag;
		hp = zizhi.hp;
		speed = zizhi.speed;
		avoid = zizhi.avoid;
		grow = zizhi.grow;
	}
};




enum eXiuLian
{
	eXLATK,
	eXLDEF,
	eXLMAG,
	eXLDMAG,
};
struct sBBXiuLian
{
	void Reset()
	{
		atk = 0;
		def = 0;
		mag = 0;
		dmag = 0;
		atkExp = 0;
		defExp = 0;
		magExp = 0;
		dmagExp = 0;
	}
	int& GetAtk(){ return atk; }
	int& GetDef(){ return def; }
	int& GetMag(){ return mag; }
	int& GetDMag(){ return dmag; }
	int& GetAtkExp(){ return atkExp; }
	int& GetDefExp(){ return defExp; }
	int& GetMagExp(){ return magExp; }
	int& GetDMagExp(){ return dmagExp; }
	void AddXiuLianLv(int num, eXiuLian type);
	int AddExp(int lv, int num, eXiuLian type);//0 修炼没有增加 1 经验提升了 2 等级提升了
	void lvdown(int lv);
	void Set(int _atk, int _def, int _mag, int _dmag)
	{
		atk = _atk;
		def = _def;
		mag = _mag;
		dmag = _dmag;
	}
	void Save(sOstream& File);
	void Load(sIstream& File);
	void operator=(sBBXiuLian& data)
	{
		atk = data.atk;
		def = data.def;
		mag = data.mag;
		dmag = data.dmag;
		atkExp = data.atkExp;
		defExp = data.defExp;
		magExp = data.magExp;
		dmagExp = data.dmagExp;
	}
private:
	int  atk;
	int  def;
	int  mag;
	int  dmag;
	//修炼经验
	int  atkExp;
	int  defExp;
	int  magExp;
	int  dmagExp;
};

