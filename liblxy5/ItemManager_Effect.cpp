#include "_global.h"

// 
// void ItemManager::SetFabaoEffect(cPcData& data, int leveup, eFaBao ID)
// {
// 	int add = leveup;
// 	switch (ID)
// 	{
// 	case eFaBao0曼陀罗:
// 		data.DmgPercentOfPoison.d1 += 20 * add;
// 		break;
// 	case eFaBao1干将莫邪:
// 		data.DmgAdd.d1 += 200 * add;
// 		break;
// 	case eFaBao2罗汉珠:
// 		data.MpSavePercent += 25 * add;
// 		break;
// 	case eFaBao3赤焰:
// 		data.LiveMp += 30 * add;
// 		break;
// 	case eFaBao4万鬼幡:
// 		break;
// 	case eFaBao5惊魂铃:
// 		data.ghostSpecial.d1 += 20 * add;
// 		break;
// 	case eFaBao6混元伞:
// 		data.StabRateOfMagic.d1 += 100 * add;    //法术反弹伤害
// 		data.StabPercentOfMagic.d1 += 5 * add; //法术反弹率
// 		break;
// 	case eFaBao7无魂傀儡:
// 		data.Spurting.d1 += 15 * add;
// //		data.m_DamageAdd.d2 += 100 * add;
// 		break;
// 	case eFaBao8乾坤玄火塔:
// 		data.LiveCp += 7 * add;
// 		break;
// 	case eFaBao9普渡:
// 		data.MagicFire.d1 += 10 * add;
// 		data.MagicWater.d1 += 10 * add;
// 		data.MagicSoil.d1 += 10 * add;
// 		data.MagicThunder.d1 += 10 * add;
// //		data.m_MagicNumAdd += add;
// 		break;
// 	case eFaBao10缩地尺:
// 		g_pMainState->m_GlobalButton[13] += 50 * add;
// 		break;
// 	case eFaBao11月光宝盒:
// 		break;
// 	case eFaBao12红色导标旗:
// 		break;
// 	case eFaBao13蓝色导标旗:
// 		break;
// 	case eFaBao14白色导标旗:
// 		break;
// 	case eFaBao15绿色导标旗:
// 		break;
// 	case eFaBao15黄色导标旗:
// 		break;
// 	case eFaBao16隐蛊:
// 		break;
// 	case eFaBao17周杰伦手办:
// //		data.m_Popularity += 100 * add;
// 		data.Speed.AddDataAdd(50 * add);
// 		break;
// 	case eFaBao18时之环:
// //		data.m_SPD.AddDataAdd(1000 * add);
// 		data.RelifeRate.d1 += 10 * add;
// 		break;
// 	case eFaBao19通灵宝玉:
// 		g_pMainState->m_GlobalButton[14] += 20 * add;
// 		break;
// 	case eFaBao20聚宝盆:
// 		g_pMainState->m_GlobalButton[15] += 20 * add;
// 		break;
// 	case eFaBao21碧玉葫芦:
// 		data.DmgPercentOfCure.d1 += 20 * add;
// 		break;
// 	case eFaBao22神木宝鼎:
// 		data.DmgPercentOfCure.d2 += 20 * add;
// 		break;
// 	case eFaBao23八咫镜:
// 		data.StabRate.d1 += 100 * add;
// 		data.StabPercent.d1 += 5 * add;
// 		break;
// 	case eFaBao24嗜血幡:
// 		data.ComboNumUp += add;
// 		data.ComboRate.d1 += 30 * add;
// 		break;
// 	case eFaBao25金甲仙衣:
// 		data.ParryRate.d1 += 20 * add;
// 		break;
// 	case eFaBao26降魔斗篷:
// 		data.ParryRateOfMaigc.d1 += 20 * add;
// 		break;
// 	case eFaBao27九幽:
// 		data.DmgPercentOfCure.d1 = add;
// 		break;
// 	case eFaBao28救命毫毛:
// //		data.GoldLivePercent.d1 += 5 * add;
// 		data.LiveRelifeRate += 5 * add;
// 		break;
// 	case eFaBao29镇海珠:
// 		data.Pierce刺穿OfMagic.d1 += 5 * add;
// 		break;
// 	case eFaBao30五火神焰印:
// 		data.CriRateOfMagic.d1 += 5 * add;
// 		break;
// 	case eFaBao31忘情:
// 		data.m_AtkDownMP.d1 += 1 * add;
// 		break;
// 	case eFaBao32慈悲:
// 		data.CriRateOfCure.d1 += 20 * add;
// 		break;
// 	case eFaBao33梦蝶:
// //		data.m_Spurting.d2 += 15 * add;
// //		data.nightLv += 10 * add;
// 		break;
// 	default:
// 		ERRBOX;
// 		break;
// 	}
// }
// 
// 



void ItemManager::SetUpQiangHua(vector<int>& prop,int protype, int num, bool isBB)
{ //
	if (num < 0)
	{
		if (prop[10] == protype)
		{
			prop[10] = prop[11] = -1;
			return;
		}

		for (int i = 2; i < 10; i += 2)
		{
			if (prop[i] == protype)
			{
				prop[i + 1] += num;
				return;
			}
		}
		return;
	}

	if (!isBB)
	{
		for (int i = 2; i < 10; i += 2)
		{
			if (prop[i] == protype)
			{
				prop[i + 1] += num;
				return;
			}
		}
	}
	prop[10] = protype;
	prop[11] = num;
	return;

	int i = 0;
	int startpos = 5;
	for (; i < prop[startpos]; i++)
	{
		if (protype == prop[startpos + 1 + i * 2])
		{
			prop[startpos + 2 + i * 2] += num;
			break;
		}
	}
	if (i == prop[startpos])
	{
		prop.push_back(protype);
		prop.push_back(num);
		prop[startpos] += 1;
	}

}



static vector<int> s_stone_pros = { eProPerty气血, eProPerty速度, eProPerty命中, eProPerty火抗, eProPerty雷抗, eProPerty水抗, eProPerty土抗,
eProPerty灵力, eProPerty躲避, eProPerty伤害, eProPerty防御, eProPerty速度, eProPerty灵力, eProPerty防御, eProPerty躲避, eProPerty伤害, eProPerty气血 };
static vector<int> s_stoneValues = { 40, 8, 25, 2, 2, 2, 2, 6, 40, 8, 12, 6, 4, 8, 30, 10, 30 };
void ItemManager::SetUpBaoShi(vector<int>& pro, int baoshiid, int lv, bool isBB)
{
	SetUpQiangHua(pro, s_stone_pros[baoshiid], s_stoneValues[baoshiid] * lv, isBB);
	return;
	switch (baoshiid)
	{
	case 0:SetUpQiangHua(pro, eProPerty气血, 40 * lv, isBB); return;
	case 1:SetUpQiangHua(pro, eProPerty速度, 8 * lv, isBB); return;
	case 2:
		SetUpQiangHua(pro, eProPerty命中, 25 * lv, isBB);
//		SetUpQiangHua(pro, eProPerty伤害, 7 * m_bSetup);
		return;
	case 3:SetUpQiangHua(pro, eProPerty火抗, 2 * lv, isBB); return;
	case 4:SetUpQiangHua(pro, eProPerty雷抗, 2 * lv, isBB); return;
	case 5:SetUpQiangHua(pro, eProPerty水抗, 2 * lv, isBB); return;
	case 6:SetUpQiangHua(pro, eProPerty土抗, 2 * lv, isBB); return;
	case 7:SetUpQiangHua(pro, eProPerty灵力, 6 * lv, isBB); return;
	case 8:SetUpQiangHua(pro, eProPerty躲避, 40 * lv, isBB); return;
	case 9:SetUpQiangHua(pro, eProPerty伤害, 8 * lv, isBB); return;
	case 10:SetUpQiangHua(pro, eProPerty防御, 12 * lv, isBB); return;
	case 11:SetUpQiangHua(pro, eProPerty速度, 6 * lv, isBB); return;
	case 12:SetUpQiangHua(pro, eProPerty灵力, 4 * lv, isBB); return;
	case 13:SetUpQiangHua(pro, eProPerty防御, 8 * lv, isBB); return;
	case 14:SetUpQiangHua(pro, eProPerty躲避, 30 * lv, isBB); return;
	case 15:SetUpQiangHua(pro, eProPerty伤害, 10 * lv, isBB); return;
	case 16:SetUpQiangHua(pro, eProPerty气血, 30 * lv, isBB); return;
	}
}


// 
// void ItemManager::AutoFuShi(sItem2* item, int lv, eMengPai mengpaiid)
// {
// 	//	if (lv < 60)return;
// 	//	if (item->m_Property.size() < 5)return;
// 	//	else if (lv > 59)
// 	{
// 		if (item->GetType() < 15)
// 		{
// 			switch (mengpaiid)
// 			{
// 			case eMP_狮驼岭:
// 				item->m_Property[2] = 86;
// 				break;
// 			default:
// 				//				item->m_Property[2] = 14;
// 				break;
// 			}
// 		}
// 		else
// 		{
// 			//			item->m_Property[2] = 14;
// 		}
// 
// 	}
// 	// 	if (lv > 89)
// 	// 	{
// 	// 		item->m_Property[3] = 0;
// 	// 	}
// 	// 	if (lv>119)
// 	// 	{
// 	// 		item->m_Property[4] = 16;
// 	// 	}
// }

