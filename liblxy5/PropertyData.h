#pragma once
#include "IntData.h"
#include "PointZZXL.h"

struct sPropertyData
{
	int  m_Lv = 0;
	sBBXiuLian m_XiuLian;
	int PointStr2 = 0;
	int PointDex2 = 0;
	int PointMag2 = 0;
	int PointBody2 = 0;
	int PointAgi2 = 0;
	sPropertyData(){ Reset(true, true, true); }

	int PointStr;
	int PointDex;
	int PointMag;
	int PointBody;
	int PointAgi;
	int PointRemain = 0;

	sInt3 HPMax;
	sInt3 MPMax;
	sInt3 Atk;   //伤害
	sInt3 Hit;   //命中
	sInt3 Def;   //防御
	sInt3 Mana;  //灵力
	sInt3 Speed; //速度
	sInt3 Evade; //躲闪

	int LiveHp = 0; //再生
	int LiveMp = 0; //冥思
	int LiveCp = 0; //愤怒
	int LiveRestoreRate = 0; //状态恢复率
	int LiveRelifeRate = 0; // 救命毫毛

	int MpSavePercent = 0; //慧根	
	int CpSavePercent = 0; //愤怒	

	int  MagicWavePercent = 0;  //法术波动

	int BuffedTiemsAdd = 0; //永恒加
	int TargetNumAdd = 0;//法术作用对像增加

	int ComboNumDown = 1;//连击下限
	int ComboNumUp = 2; //连击上限
//	int ShiXueAdd = 0; // 连击伤害增加

	int Cp1 = 0; // 临时愤怒
	int StartMagic = -1;//开场法术
	int EndMagic = -1;//开场法术

	sInt2 RelifeRate;//神估
	sInt2 RelifePercent;//神估
	//金甲仙衣和降魔斗篷效果
	sInt2 ParryRate;
	sInt2 ParryRateOfMaigc;

	sInt2 CriRate; //物理
	sInt2 CriRateOfMagic; //法术
	sInt2 CriRateOfCure; //治疗
	sInt2 CriDmgPercent; //必杀伤害提升

	sInt2 ComboRate;  //连击率
	sInt2 ComboRateOfMagic; //法连率

	sInt2 Pierce刺穿;//无视防御率
	sInt2 Pierce刺穿OfMagic; //无视灵力率

	sInt2 HitRate;  //物理
	sInt2 HitRateOfMagic;//法术
	sInt2 HitRateOfSeal;//封印
	sInt2 HitRateOfPoison; //毒
	//伤害加成  防御加成
	sInt2 DmgPercentOfFix;//固定
	sInt2 DmgPercentOfMagic;//法术
	sInt2 DmgPercent;//物理
	sInt2 DmgPercentOfArm; //暗器
	sInt2 DmgPercentOfPoison; //毒
	sInt2 DmgPercentOfCure;//治疗
	//伤害修正
	sInt2 DmgAdd;//物理伤害结果增加
	sInt2 DmgAddOfMagic;//伤害结果增加
	sInt2 DmgAddOfCure;//治疗效果增加
	// 反击
	sInt2 CounterRate;
	sInt2 CounterPercent;
	// 吸血率
	sInt2 SuckBloodRate;
	sInt2 SuckBloodPercent;
	//反震
	sInt2 StabRate;
	sInt2 StabRateOfMagic;    //法术反弹伤害
	sInt2 StabPercent;
	sInt2 StabPercentOfMagic; //法术反弹率

	sInt2 Spurting;//溅射;

	//法术属性伤害, 0-100
	sInt2 MagicFire; //火
	sInt2 MagicSoil; //土
	sInt2 MagicWater;  //水
	sInt2 MagicThunder;//雷

	sInt2 Hide;
	sInt2 Ghost;


	void applyPoint(const sZiZhi* zz);
	void applyXL();
	void applyFZ(int lv, int id);
	void applyEquip(const vector<int>& props);
	void applyMP(int lv);
	void applyFabao(int e);
	void applyPetSkill(int e);
	void Reset(bool relv, bool repoint, bool reXL);
};