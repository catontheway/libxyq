#include "PropertyData.h"
#include "Item.h"
#include "cct.h"

void sPropertyData::applyPoint(const sZiZhi* zz)
{
	int lv = m_Lv;
	int atk, def, hp, mana, mp, speed, evade, hit;
	if (zz)
	{
		atk = lv * zz->atk * (1400 + 10 * zz->grow) / 750000;
		atk += PointStr * zz->grow / 100;

		def = (lv * zz->def) * 19 / 7500;
		def += (PointDex * zz->grow * 4) / 300;

		hp = (lv * zz->hp) / 1000;
		hp += PointBody * zz->grow * 6 / 100;

		mana = lv* (zz->mag + 1640) * (zz->grow + 100) / 75000;
		mana += PointBody * 3 + PointMag * 7 + PointStr * 4 + PointDex * 2;
		mana /= 10;

		mp = lv * zz->mag / 500 + zz->grow * PointMag * 3 / 100;

		speed = zz->speed * PointAgi / 1000;
		evade = zz->avoid * PointAgi / 300;

		hit = atk / 2;
		hit += PointStr * 5 / 2;
	}
	else
	{
		atk = PointStr/* * 7 / 9*/;
		def = PointDex * 5 / 3;
		hp = 100 + PointBody * 5;
		mana = PointMag * 7 + PointBody * 3 + PointStr * 4 + PointDex * 2;
		mana /= 10;
		mp = 80 + PointMag * 3;
		speed = PointAgi * 7 + PointBody + PointStr + PointDex;
		speed /= 10;
		evade = PointAgi;
		hit = PointStr * 7 / 3;
	}

	PointStr2 = 0;
	PointAgi2 = 0;
	PointBody2 = 0;
	PointMag2 = 0;
	PointDex2 = 0;
	Atk.Reset();
	Atk.SetDataOriginal(atk);
	Def.Reset();
	Def.SetDataOriginal(def);
	HPMax.Reset();
	HPMax.SetDataOriginal(hp);
	Mana.Reset();
	Mana.SetDataOriginal(mana);
	MPMax.Reset();
	MPMax.SetDataOriginal(mp);
	Speed.Reset();
	Speed.SetDataOriginal(speed);
	Evade.Reset();
	Evade.SetDataOriginal(evade);
	Hit.Reset();
	Hit.SetDataOriginal(hit);
}


void sPropertyData::applyXL()
{
	auto xl = m_XiuLian;
	DmgPercent.d1 += xl.GetAtk() * 2;
	DmgAdd.d1 += xl.GetAtk() * 5;
	DmgPercent.d2 += xl.GetDef() * 2;
	DmgAdd.d2 += xl.GetDef() * 5;

	DmgPercentOfMagic.d1 += xl.GetMag() * 2;
	DmgAddOfMagic.d1 += xl.GetMag() * 5;
	DmgPercentOfMagic.d2 += xl.GetDMag() * 2;
	DmgAddOfMagic.d2 += xl.GetDMag() * 5;
}



void sPropertyData::applyFZ(int lv, int id)
{
	if (id == 0)
	{
		HPMax.AddDataAdd(lv * 5);
	}
	else if (id == 1)
	{
		HPMax.AddDataAddPercent(lv);
	}
	else if (id == 2)
	{
		MPMax.AddDataAddPercent(lv);
	}
	else if (id == 3)
	{
		DmgPercentOfArm.d1 += lv;
	}
}


void sPropertyData::applyEquip(const vector<int>& props)
{
	bool isPoint = false;
	sPropertyData* data = this;
	int add = 1;
	for (int i = 2; i < props.size(); i += 2)
	{
		switch (props[i])
		{
		case eProPerty伤害: data->Atk.AddDataOriginal(props[i + 1] * add); break;
		case eProPerty命中: data->Hit.AddDataOriginal(props[i + 1] * add); data->Atk.AddDataOriginal(props[i + 1] * add / 3); break;
		case eProPerty防御: data->Def.AddDataOriginal(props[i + 1] * add); break;
		case eProPerty魔法: data->MPMax.AddDataOriginal(props[i + 1] * add); break;
		case eProPerty灵力: data->Mana.AddDataOriginal(props[i + 1] * add); break;
		case eProPerty速度: data->Speed.AddDataOriginal(props[i + 1] * add); break;
		case eProPerty气血: data->HPMax.AddDataOriginal(props[i + 1] * add); break;
		case eProPerty力量: data->PointStr2 += props[i + 1] * add; isPoint = true;  break;
		case eProPerty敏捷: data->PointAgi2 += props[i + 1] * add; isPoint = true; break;
		case eProPerty体质: data->PointBody2 += props[i + 1] * add; isPoint = true; break;
		case eProPerty魔力: data->PointMag2 += props[i + 1] * add; isPoint = true; break;
		case eProPerty耐力: data->PointDex2 += props[i + 1] * add; isPoint = true; break;
		case eProPerty火抗: data->MagicFire.d2 += props[i + 1]; break;
		case eProPerty雷抗: data->MagicThunder.d2 += props[i + 1]; break;
		case eProPerty土抗: data->MagicSoil.d2 += props[i + 1]; break;
		case eProPerty水抗: data->MagicWater.d2 += props[i + 1]; break;
		case eProPerty躲避: data->Evade.AddDataOriginal(props[i + 1] * add); break;
		case eProPerty法伤: data->DmgAddOfMagic.d1 += props[i + 1] * 2; break;
		case eProPerty法防: data->DmgAddOfMagic.d2 += props[i + 1] * 2; break;
		case eProPerty法结: data->DmgAddOfMagic.d1 += props[i + 1] * 2; break;
		case eProPerty物结: data->DmgAdd.d1 += props[i + 1] * 2; break;
		case eProPerty回复: data->DmgAddOfCure.d2 += props[i + 1]; break;
		case eProPerty愤怒: data->Cp1 += props[i + 1]; break;
		case eProPerty命率: data->HitRate.d1 += props[i + 1]; break;
		}
	}

	if (isPoint)
	{
		int atk = PointStr2 * 7 / 9;
		int def = PointDex2 * 5 / 3;
		int hp = 100 + PointBody2 * 5;
		int mana = PointMag2 * 7 + PointBody2 * 3 + PointStr2 * 4 + PointDex2 * 2;
		mana /= 10;
		int mp = 80 + PointMag2 * 3;
		int speed = PointAgi2 * 7 + PointBody2 + PointStr2 + PointDex2;
		speed /= 10;
		int evade = PointAgi2;
		int hit = PointStr2 * 7 / 3;

		Atk.AddDataOriginal(atk);
		Def.AddDataOriginal(def);
		HPMax.AddDataOriginal(hp);
		Mana.AddDataOriginal(mana);
		MPMax.AddDataOriginal(mp);
		Speed.AddDataOriginal(speed);
		Evade.AddDataOriginal(evade);
		Hit.AddDataOriginal(hit);
	}

}


void sPropertyData::applyMP(int lv)
{
	float atk = 0, def = 0, mana = 0, evade = 0;
	for (int i = lv; i > 0; --i)
	{
		atk += 1.5f + 0.02f * i;
		def += 1 + 0.02f * i;
		mana += 0.5f + 0.01 * i;
		evade += 2 + 0.02f * i;
	}
	Atk.AddDataOriginal(atk);
	Def.AddDataOriginal(def);
	Mana.AddDataOriginal(mana);
	Evade.AddDataOriginal(evade);
}


void sPropertyData::applyFabao(int e)
{
	int lv = m_Lv;
	sPropertyData* data = this;
	int add = 1;
	switch (e)
	{
	case eFaBao0曼陀罗:
		data->DmgPercentOfPoison.d1 += 5 * add;
		break;
	case eFaBao1干将莫邪:
		data->DmgAdd.d1 += 50 * add;
		break;
	case eFaBao2罗汉珠:
		data->MpSavePercent += 10 * add;
		break;
	case eFaBao3赤焰:
		data->LiveMp += 10 * add;
		break;
	case eFaBao4万鬼幡:
		break;
	case eFaBao5惊魂铃:
		data->Ghost.d2 += 10 * add;
		break;
	case eFaBao6混元伞:
		data->StabRateOfMagic.d1 += 20 * add;  //法术反弹伤害
		data->StabPercentOfMagic.d1 += 5 * add; //法术反弹率
		break;
	case eFaBao7无魂傀儡:
//		data.Spurting.d1 += 15 * add;
//		data.m_DamageAdd.d2 += 100 * add;
		break;
	case eFaBao8乾坤玄火塔:
		data->LiveCp += 2 * add;
		break;
	case eFaBao9普渡:
		data->MagicFire.d1 += 5 * add;
		data->MagicWater.d1 += 5 * add;
		data->MagicSoil.d1 += 5 * add;
		data->MagicThunder.d1 += 5 * add;
		break;
	case eFaBao10缩地尺:
//		g_pMainState->m_GlobalButton[13] += 50 * add;
		break;
	case eFaBao11月光宝盒:
		break;
	case eFaBao12红色导标旗:
		break;
	case eFaBao13蓝色导标旗:
		break;
	case eFaBao14白色导标旗:
		break;
	case eFaBao15绿色导标旗:
		break;
	case eFaBao15黄色导标旗:
		break;
	case eFaBao16隐蛊:
		break;
	case eFaBao17周杰伦手办:
		data->Speed.AddDataAdd(30 * add);
		break;
	case eFaBao18时之环:
		data->RelifeRate.d1 += 5 * add;
		break;
	case eFaBao19通灵宝玉:
//		g_GlobalValues[14] += 5 * add;
		break;
	case eFaBao20聚宝盆:
//		g_GlobalValues[15] += 5 * add;
		break;
	case eFaBao21碧玉葫芦:
		data->DmgAddOfCure.d1 += 64 * add;
		break;
	case eFaBao22神木宝鼎:
		data->DmgAddOfCure.d2 += 64 * add;
		break;
	case eFaBao23八咫镜:
		data->StabRate.d1 += 20 * add;
		data->StabPercent.d1 += 5 * add;
		break;
	case eFaBao24嗜血幡:
		data->SuckBloodRate.d1 += 5 * add;
		data->SuckBloodPercent.d1 += 5 * add;
		break;
	case eFaBao25金甲仙衣:
		data->ParryRate.d1 += 5 * add;
		break;
	case eFaBao26降魔斗篷:
		data->ParryRateOfMaigc.d1 += 5 * add;
		break;
	case eFaBao27九幽:
		data->DmgPercentOfCure.d1 += 2 * add;
		data->DmgPercentOfCure.d2 += 2 * add;
		break;
	case eFaBao28救命毫毛:
		data->LiveRelifeRate += 5 * add;
		break;
	case eFaBao29镇海珠:
		data->Pierce刺穿OfMagic.d1 += 2 * add;
		break;
	case eFaBao30五火神焰印:
		data->CriRateOfMagic.d1 += 5 * add;
		break;
	case eFaBao31忘情:
//		data.m_AtkDownMP.d1 += 1 * add;
		break;
	case eFaBao32慈悲:
		data->CriRateOfCure.d1 += 5 * add;
		break;
	case eFaBao33梦蝶:
//		data.m_Spurting.d2 += 15 * add;
//		data.nightLv += 10 * add;
		break;
	default:
		ERRBOX;
		break;
	}
}


void sPropertyData::applyPetSkill(int e)
{
	int lv = m_Lv;
	sPropertyData* pPetDate = this;
	int add = 1;
	switch (e)
	{
	case 0://反击
		pPetDate->CounterRate.d1 += add * 30;
		pPetDate->CounterPercent.d1 += add * 50;
		break;
	case 1://高级反击
		pPetDate->CounterRate.d1 += add * 30;
		pPetDate->CounterPercent.d1 += add * 100;
		break;
	case 2://反震
		pPetDate->StabRate.d1 += add * 30;
		pPetDate->StabPercent.d1 += add * 25;
		break;
	case 3://高级反震
		pPetDate->StabRate.d1 += add * 30;
		pPetDate->StabPercent.d1 += add * 50;
		break;
	case 4://吸血
		pPetDate->SuckBloodRate.d1 += add * 100;
		pPetDate->SuckBloodPercent.d1 += add * 20;
		break;
	case 5://高级吸血
		pPetDate->SuckBloodRate.d1 += add * 100;
		pPetDate->SuckBloodPercent.d1 += add * 35;
		break;
	case 6://连击
		pPetDate->ComboRate.d1 += add * 45;
		pPetDate->DmgPercent.d1 -= 25;
		break;
	case 7://高级连击
		pPetDate->ComboRate.d1 += add * 60;
		pPetDate->DmgPercent.d1 -= 20;
		break;
	case 8://飞行
		pPetDate->HitRate.d1 += add * 10;
		pPetDate->HitRate.d2 += add * 10;
		pPetDate->DmgPercentOfArm.d2 -= add * 50;
		break;
	case 9://高级飞行
		pPetDate->HitRate.d1 += add * 20;
		pPetDate->HitRate.d2 += add * 20;
		pPetDate->DmgPercentOfArm.d2 -= add * 20;
		break;
	case 10://夜战
//		pPetDate->m_Spurting.d2 += 20;
		pPetDate->DmgPercent.d1 += add * 5;
//		pPetDate->nightLv += lv *10;
		break;
	case 11://高级夜战
//		pPetDate->m_Spurting.d2 += 30;
		pPetDate->DmgPercent.d1 += add * 10;
//		pPetDate->nightLv += lv * 20;
		break;
	case 12://隐身
		pPetDate->Hide.d1 += add * 2;
		pPetDate->DmgPercent.d1 -= 20;
		break;
	case 13://高级隐身
		pPetDate->Hide.d1 += add * 5;
		pPetDate->DmgPercent.d1 -= 20;
		break;
	case 14://感知
		pPetDate->Hide.d2 += add * 0xFF;
		break;
	case 15://高级感知
		pPetDate->Hide.d2 += add * 0xFF;
		pPetDate->HitRate.d1 += add * 20;
		break;
	case 16://再生
		pPetDate->LiveHp += add * lv;
		break;
	case 17://高级再生
		pPetDate->LiveHp += add * lv * 2;
		break;
	case 18://冥思
		pPetDate->LiveMp += add * lv / 4;
		break;
	case 19://高级冥思
		pPetDate->LiveMp += add * lv / 2;
		break;
	case 20://慧根
		pPetDate->MpSavePercent += add * 25;
		break;
	case 21://高级慧根
		pPetDate->MpSavePercent += add * 50;
		break;
	case 22://不幸 高级迟钝
//		pPetDate->m_CriRate.d2   -= lv*10;
//		pPetDate->CriRate.d2 -= add * 10;
		pPetDate->Speed.AddDataAddPercent(-add * 80);
		break;
	case 23://必杀
		pPetDate->CriRate.d1 += add * 10;
		break;
	case 24://高级必杀
		pPetDate->CriRate.d1 += add * 20;
		break;
	case 25://幸运
		pPetDate->CriRate.d2 += add * 0xFF;
		break;
	case 26://高级幸运
		pPetDate->CriRate.d2 += add * 0xFF;
		pPetDate->HitRateOfMagic.d2 += add * 10;
		break;
	case 27://神迹
		pPetDate->LiveRestoreRate += add * 100;
		break;
	case 28://高级神迹
		pPetDate->HitRateOfSeal.d2 += 0xFF;
		pPetDate->HitRateOfPoison.d2 += 0xFF;
		break;
	case 29://招架
		pPetDate->HitRate.d2 += add * 10;
		break;
	case 30://高级招架
		pPetDate->HitRate.d2 += add * 20;
		break;
	case 31://永恒
		pPetDate->BuffedTiemsAdd += add * 3;
		break;
	case 32://高级永恒
		pPetDate->BuffedTiemsAdd += add * 6;
		break;
	case 33://敏捷
		pPetDate->Speed.AddDataAddPercent(add * 10);
		break;
	case 34://高级敏捷
		pPetDate->Speed.AddDataAddPercent(add * 20);
		break;
	case 35://强力
		pPetDate->Atk.AddDataAdd(add * lv / 2);
		break;
	case 36://高级强力
		pPetDate->Atk.AddDataAdd(add * lv);
		break;
	case 37://防御
		pPetDate->Def.AddDataAdd(add * lv / 2);
		break;
	case 38://高级防御
		pPetDate->Def.AddDataAdd(add * lv);
		break;
	case 39://偷袭  
		pPetDate->StabRate.d2 += add * 64;//反震免疫率
		pPetDate->CounterRate.d2 += add * 0xFF;//反击免疫率
		break;
	case 40://高级偷袭
		pPetDate->StabRate.d2 += add * 0xFF;//反震免疫率
		pPetDate->CounterRate.d2 += add * 0xFF;//反击免疫率
		break;
	case 41://毒
		pPetDate->HitRateOfPoison.d1 += add * 10;
		break;
	case 42://高级毒
		pPetDate->HitRateOfPoison.d1 += add * 20;
		break;
	case 43://驱鬼
		pPetDate->Ghost.d2 += add * 50;
		break;
	case 44://高级驱鬼
		pPetDate->Ghost.d2 += add * 100;
		break;
	case 45://鬼魂术
		pPetDate->Ghost.d1 += add * 7;
		break;
	case 46://高级鬼魂术
		pPetDate->Ghost.d1 += add * 5;
		break;
	case 47://魔之心
		pPetDate->DmgPercentOfMagic.d1 += add * 10;
		break;
	case 48://高级魔之心
		pPetDate->DmgPercentOfMagic.d1 += add * 20;
		break;
	case 49://神佑
		pPetDate->RelifeRate.d1 += add * 20;
		pPetDate->RelifePercent.d1 += add * 50;
		break;
	case 50://高级神佑
		pPetDate->RelifeRate.d1 += add * 30;
		pPetDate->RelifePercent.d1 += add * 100;
		break;
	case 51://精神集中
		pPetDate->HitRateOfSeal.d2 += add * 10;
		break;
	case 52://高级精神集中
		pPetDate->HitRateOfSeal.d2 += add * 20;
		break;
	case 53://否定信仰
		pPetDate->RelifeRate.d2 += add * 15;
		break;
	case 54://高级否定信仰
		pPetDate->RelifeRate.d2 += add * 25;
		break;
	case 55://法术连击
		pPetDate->ComboRateOfMagic.d1 += add * 15;
		break;
	case 56://高级法术连击
		pPetDate->ComboRateOfMagic.d1 += add * 25;
		break;
	case 57://法术暴击
		pPetDate->CriRateOfMagic.d1 += add * 10;
		break;
	case 58://高级法术暴击
		pPetDate->CriRateOfMagic.d1 += add * 15;
		break;
	case 59://法术波动
		pPetDate->MagicWavePercent += add * 10;
		break;
	case 60://高级法术波动
		pPetDate->MagicWavePercent += add * 20;
		break;
	case 61://迟钝
		pPetDate->Speed.AddDataAddPercent(-add * 50);
		break;
	case 62://弱点火
		pPetDate->MagicFire.d2 -= add * 50; //火	
		break;
	case 63://弱点水
		pPetDate->MagicWater.d2 -= add * 50;  //水
		break;
	case 64://弱点土
		pPetDate->MagicSoil.d2 -= add * 50; //土
		break;
	case 65://弱点雷
		pPetDate->MagicThunder.d2 -= add * 50;//雷
		break;
	case 66://雷属性吸收
		pPetDate->MagicThunder.d2 += add * 20;//雷
		break;
	case 67://高级雷属性吸收
		pPetDate->MagicThunder.d2 += add * 30;//雷
		break;
	case 68://土属性吸收
		pPetDate->MagicSoil.d2 += add * 20; //土
		break;
	case 69://高级土属性吸收
		pPetDate->MagicSoil.d2 += add * 30; //土
		break;
	case 70://火属性吸收
		pPetDate->MagicFire.d2 += add * 20; //火
		break;
	case 71://高级火属性吸收
		pPetDate->MagicFire.d2 += add * 30; //火
		break;
	case 72://水属性吸收
		pPetDate->MagicWater.d2 += add * 20;  //水
		break;
	case 73://高级水属性吸收
		pPetDate->MagicWater.d2 += add * 30;  //水
		break;
	case 74://移花接木 
		pPetDate->DmgPercentOfArm.d2 += add * 99;
		break;
	case 75://风刃(灵能激发)
//		pPetDate->Spurting.d1 += add * 15;
		break;
// 	case 76://嗜血追击
// 		pPetDate->ShiXueAdd += add * 0xF;
// 		break;
//	case 77://龙鳞防御(盾气)
//		pPetDate->m_DamageAddMagicLv.d2 += lv * 2;//法术伤害结果
// 		pPetDate->m_DamageAddLv.d2	+= lv * 2;  //物理伤害结果
// 		pPetDate->m_DamageAddPercentMagic2.d2 += 10;
// 		pPetDate->m_MagicWater.d2 += lv*20;  //水
//		break;
//	case 78://龙鳞守护(高级盾气)
//		pPetDate->m_DamageAddMagicLv.d2 += lv * 3;//法术伤害结果
// 		pPetDate->m_DamageAddLv.d2 += lv * 3;  //物理伤害结果
// 		pPetDate->m_DamageAddPercentMagic2.d2 += 15;
// 		pPetDate->m_MagicWater.d2 += lv * 30;  //水
//		break;
	case 79://法术抵抗
		pPetDate->DmgPercentOfMagic.d2 += add * 15;
		break;
	case 80://高级法术抵抗
		pPetDate->DmgPercentOfMagic.d2 += add * 25;
		break;
	case 81://直死(合纵，小风华)
		pPetDate->Pierce刺穿.d1 += 4;//无视防御率
//		pPetDate->m_PierceMagic.d1+=30; //无视灵力率
//		pPetDate->ComboNumUp += add * 1;
		//		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 82://风华武圣(高级合纵)
		pPetDate->Pierce刺穿.d1 += 8;//无视防御率
//		pPetDate->ComboNumUp += add * 3;
//		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 83://法术反弹,法力陷阱
		pPetDate->StabRateOfMagic.d1 += add * 30;//法术反震率
		pPetDate->StabPercentOfMagic.d1 += add * 25;//法术反震伤害率
		break;
	case 96: // 神马
		break;
	case 100:// 苍穹
		break;
	case 103:// 须弥
		pPetDate->DmgAddOfMagic.d1 += add * PointMag * 2 / 5;
		break;
	case 104:// 从天
		break;
	case 106:// 灵山禅语
		pPetDate->DmgAddOfMagic.d2 += add * PointMag;
		{
			int mana = lv * (2500 + 1640) * (120 + 100) / 75000;
			mana += PointBody * 3 + PointMag * 7 + PointStr * 4 + PointDex * 2;
			mana /= 10;
			pPetDate->DmgAddOfMagic.d1 -= mana;
		}
		break;
	case 107:// 千钧一怒
		break;
	case 108:// 龙魂
		break;
	case 109:// 大块朵硕
		break;
	}
}

void sPropertyData::Reset(bool relv, bool repoint, bool reXL)
{
	if (relv)
	{
		m_Lv = 0;
		repoint = true;
	}
	if (reXL)
	{
		m_XiuLian.Reset();
	}


	PointStr2 = 0;
	PointDex2 = 0;
	PointMag2 = 0;
	PointBody2 = 0;
	PointAgi2 = 0;


	if (repoint)
	{
		PointStr = cct::MinPoint + m_Lv;
		PointDex = cct::MinPoint + m_Lv;
		PointMag = cct::MinPoint + m_Lv;
		PointBody = cct::MinPoint + m_Lv;
		PointAgi = cct::MinPoint + m_Lv;
		PointRemain = m_Lv * 5;
	}


	HPMax.Reset();
	MPMax.Reset();
	Atk.Reset();   //伤害
	Hit.Reset();   //命中
	Def.Reset();   //防御
	Mana.Reset();  //灵力
	Speed.Reset(); //速度
	Evade.Reset(); //躲闪

	LiveHp = 0; //再生
	LiveMp = 0; //冥思
	LiveCp = 0; //愤怒
	LiveRestoreRate = 0; //状态恢复率
	LiveRelifeRate = 0;

	MpSavePercent = 0; //慧根	
	CpSavePercent = 0; //愤怒	

	MagicWavePercent = 0;  //法术波动

	BuffedTiemsAdd = 0; //永恒加
	TargetNumAdd = 0;//法术作用对像增加

	ComboNumDown = 1;//连击下限
	ComboNumUp = 2; //连击上限
//	ShiXueAdd = 0; //连击伤害增加

	Cp1 = 0;
	StartMagic = -1;//开场法术
	EndMagic = -1;

	RelifeRate.Reset();//神估
	//金甲仙衣和降魔斗篷效果
	RelifePercent.Reset();
	ParryRate.Reset();
	ParryRateOfMaigc.Reset();

	CriRate.Reset(); //物理
	CriRate.d1 = 5;
	CriRateOfMagic.Reset(); //法术
	CriRateOfMagic.d1 = 3;
	CriRateOfCure.Reset(); //治疗
	CriDmgPercent.Reset(); //必杀伤害提升

	ComboRate.Reset();  //连击率
	ComboRateOfMagic.Reset(); //法连率

	Pierce刺穿.Reset();//无视防御率
	Pierce刺穿OfMagic.Reset(); //无视灵力率

	HitRate.Reset();  //物理
	HitRateOfMagic.Reset();//法术
	HitRateOfSeal.Reset();//封印
	HitRateOfPoison.Reset(); //毒
			//伤害加成  防御加成
	DmgPercentOfFix.Reset();//固定
	DmgPercentOfMagic.Reset();//法术
	DmgPercent.Reset();//物理
	DmgPercentOfArm.Reset(); //暗器
	DmgPercentOfPoison.Reset(); //毒
	DmgPercentOfCure.Reset();//治疗
	//伤害修正
	DmgAdd.Reset();//物理伤害结果增加
	DmgAddOfMagic.Reset();//伤害结果增加
	DmgAddOfCure.Reset();//治疗效果增加
	// 反击
	CounterRate.Reset();
	CounterPercent.Reset();
	// 吸血率
	SuckBloodRate.Reset();
	SuckBloodPercent.Reset();
	//反震
	StabRate.Reset();
	StabRateOfMagic.Reset();    //法术反弹伤害
	StabPercent.Reset();
	StabPercentOfMagic.Reset(); //法术反弹率

	Spurting.Reset();//溅射;

	//法术属性伤害, 0-100
	MagicFire.Reset(); //火
	MagicSoil.Reset(); //土
	MagicWater.Reset();  //水
	MagicThunder.Reset();//雷

	Hide.Reset();
	Ghost.Reset();
}