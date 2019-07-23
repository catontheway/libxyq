#include "_global.h"

bool ItemManager::UseItem22Ò©Æ·(sItem2* pItem, int ObjId)
{
	bool success = false;
	m_bAddHp = false;
	m_bAddMp = false;
	m_bAddCp = false;
	m_bToAll = false;
	switch (pItem->GetID())
	{
	case 0:	//Í¬ÐÄÈâ¸¬  
		success = AddFunc(&ItemManager::AddHp, 100, ObjId/*, 10000*/);
		break;
	case 1://ËÄÒ¶»¨   
		success = AddHp(40, ObjId);
		break;
	case 2://ÌìÇàµØ°×
		success = AddHp(80, ObjId);
		break;
	case 3://ÈË²Î
		success = AddHpHurt(20, ObjId) && AddHp(80, ObjId);
		break;
	case 4://ÑªÉ«²è»¨
		success = AddHp(150, ObjId);
		break;
	case 5://ÐÜµ¨
		success = AddHp(200, ObjId);
		break;
	case 6://Áò»Ç²Ý
		success = AddHp(250, ObjId);
		break;
	case 7://ÑªÉºº÷
		success = AddMp(100, ObjId);
		break;
	case 8://µØÓüÁéÖ¥
		success = AddMp(100, ObjId);
		break;
	case 9://ÁúÖ®ÐÄÐ¼
		success = AddHp(300, ObjId);
		break;
	case 10://½ð´´Ò©
		success = AddHp(400, ObjId);
		break;
	case 11://ºìÑ©É¢
		success = removeBuff(eBuffType¶¾, ObjId, true) && AddHp(400, ObjId);
		break;
	case 12://°Ë½ÇÁ«Ò¶
//		success = AddFunc(&ItemManager::AddHp, 100, ObjId);
		success = AddHpHurt(15, ObjId) && AddHp(60, ObjId);
		break;
	case 13://ÆßÒ¶Á«
//		success = AddFunc(&ItemManager::AddHp, 150, ObjId);
		success = AddHp(60, ObjId);
		break;
	case 14://Â¹È×
//		success = AddFunc(&ItemManager::AddHp, 300, ObjId);
		success = AddHp(150, ObjId);
		break;
	case 15://·ï»ËÎ²
		success = AddHp(250, ObjId);
//		success = AddFunc(&ItemManager::AddHp, 600, ObjId);
		break;
	case 16://»ð·ïÖ®¾¦
//		success = AddFunc(&ItemManager::AddHp, 1000, ObjId);
		success = AddHp(300, ObjId);
		break;
	case 17://Ð¡»¹µ¤
//		success = AddAll(&cItem::AddHp, 2000, ObjId);
		success = AddHpHurt(400, ObjId) && AddHp(400, ObjId);
		break;
	case 18://½ðÏãÓñ
//		success = AddAll(&cItem::AddHp, 5000, ObjId);
		success = AddHp(800, ObjId);
		break;
	case 19://·ðÊÖ
		success = AddMp(20, ObjId);
		break;
	case 20://Ðý¸´»¨
		success = AddMp(20, ObjId);
		break;
	case 21://ÏãÒ¶
		success = AddMp(30, ObjId);
		break;
	case 22://ÂüÙ¢ÂÞ»¨
		success = AddMp(50, ObjId);
		break;
	case 23://ÌìÁúË®
		success = AddMp(150, ObjId);
		break;
	case 24://²Í·çÒûÂ¶
		success = AddMp(100, ObjId);
		break;
	case 25://·çË®»ìÔªµ¤
		success = AddMp(300, ObjId);
		break;
	case 26://×Ïµ¤ÂÞ
//		success = AddFunc(&ItemManager::AddMp, 20, ObjId);
		success = AddMp(20, ObjId);
		break;
	case 27://ÁúÐë²Ý
//		success = AddFunc(&ItemManager::AddMp, 50, ObjId);
		success = AddMp(30, ObjId);
		break;
	case 28://°×Óñ¹ÇÍ·
//		success = AddFunc(&ItemManager::AddMp, 100, ObjId);
		success = AddMp(40, ObjId);
		break;
	case 29://¶¡ÏãË®
//		success = AddFunc(&ItemManager::AddMp, 200, ObjId);
		success = AddMp(75, ObjId);
		break;
	case 30://ÔÂÐÇ×Ó
//		success = AddFunc(&ItemManager::AddMp, 300, ObjId);
		success = AddMp(75, ObjId);
		break;
	case 31://÷êÏã
//		success = AddFunc(&ItemManager::AddMp, 400, ObjId);
		success = AddMp(100, ObjId);
		break;
	case 32://ÏÉºüÏÑ
//		success = AddFunc(&ItemManager::AddMp, 600, ObjId);
		success = AddMp(150, ObjId);
		break;
	case 33://¶¨ÉñÏã
//		success = AddFunc(&ItemManager::AddMp, 1000, ObjId);
		success = AddMp(350, ObjId);
		break;
	case 34://²Ý¹û
		success = AddHpHurt(10, ObjId);
		break;
	case 35://¾ÅÏã³æ
		success = AddHpHurt(15, ObjId);
		break;
	case 36://Ë®»ÆÁ«
		success = AddHpHurt(20, ObjId);
		break;
	case 37://É½Ò©
		success = AddHpHurt(10, ObjId) && AddHp(40, ObjId);
		break;
	case 38://ÁéÖ¬
//		success = AddFunc(&ItemManager::AddHpHurt, 100, ObjId);
		success = AddMp(40, ObjId);
		break;
	case 39://×ÏÊ¯Ó¢
//		success = AddFunc(&ItemManager::AddHpHurt, 500, ObjId);
		success = AddMp(100, ObjId);
		break;
	case 40://ÔÂ¼û²Ý
// 		success = AddHpHurt(50, ObjId);
// 		AddHp(100, ObjId);
		success = AddHp(40, ObjId) && AddMp(30, ObjId);
		break;
	case 41://°×Â¶ÎªËª
// 		success = AddHpHurt(200, ObjId);
// 		AddHp(500, ObjId);
		success = AddMp(100, ObjId);
		break;
	case 42://¿×È¸ºì
// 		success = AddHpHurt(400, ObjId);
// 		AddHp(1000, ObjId);
		success = AddMp(150, ObjId);
		break;
	case 43://ÉßÐ«ÃÀÈË
// 		success = AddHpHurt(1000, ObjId);
// 		AddHp(3000,ObjId);
		success = AddMp(/*pItem->m_pItemData->GetLv() * 5 + 100*/500, ObjId);
		break;
	case 44://·ð¹âÉáÀû×Ó
		success = relife(1, ObjId);
		if (success)
		{
			AddHpHurt(150, ObjId);
		}
		break;
	case 45://¾Å×ª»Ø»êµ¤
//		success = Resurgence(30, ObjId, 10000);
//		success = relife(pItem->m_pItemData->GetLv() * 12 + 150, ObjId);
		success = relife(1, ObjId);
		if (success)
		{
			AddHpHurt(200, ObjId);
			AddHp(200, ObjId);
		}
		break;
	case 46://°ÙÉ«»¨
//		success = removeBuff(eBuffType¶¾, ObjId, true);
		success = AddMp(30, ObjId);
		break;
	case 47://ÁùµÀÂÖ»Ø
		success = AddHp(200, ObjId/*, 10000*/);
		break;
	case 48://Ç§Äê±£ÐÄµ¤
		success = AddHpHurt(400, ObjId) && AddHp(400, ObjId/*, 10000*/);
		break;
	case 49://ÎåÁúµ¤

	{
		success = true;
		removeBuff(eBuffType·âÓ¡, ObjId, true);
//		removeBuff(eBuffType¸ºÃæ, ObjId, true);
//		removeBuff(eBuffType¶¾, ObjId, true);
		AddHp(/*1 + pItem->m_pItemData->GetLv() * 3*/100, ObjId/*, 10000*/);
	}
		break;
	case 50://¸£ÁéÉ³
		success = true;
// 		AddFunc(&ItemManager::removeBuff, eBuffType¶¾, ObjId, true);//È«Ìå½â¶¾
// 		AddFunc(&ItemManager::removeBuff, eBuffType·âÓ¡, ObjId, true);//È«Ìå½â·â
		AddFunc(&ItemManager::AddHp, 150, ObjId);
		break;
	case 51://ÎåÎ¶Â¶
		success = true;

// 		AddFunc(&ItemManager::relife, 10000, ObjId, false);//È«Ìå¸´»î
// 		AddFunc(&ItemManager::removeBuff, eBuffType¶¾, ObjId, true);//È«Ìå½â¶¾
		AddFunc(&ItemManager::AddMp, 40, ObjId);
		break;
	case 52://ÉñÏÉÒû (³¬ÉñË®)

	{
		success = true;
// 		relife(1, ObjId);
// 		AddHpHurt(100, ObjId, 10000);
// 		AddHp(100, ObjId, 10000);
// 		AddMp(100, ObjId, 10000);
// 		AddCp(100, ObjId, 10000);
// 		removeBuff(eBuffType¶¾, ObjId, true);
// 		removeBuff(eBuffType·âÓ¡, ObjId, true);
// 		removeBuff(eBuffType¸ºÃæ, ObjId, true);
// 		sBuff buf;
// 		buf.remainingTimes = 10;
// 
// 		g_pMainState->m_SkillManager.SetDateBuffUp(ObjId, ObjId, 2093, buf);
		AddFunc(&ItemManager::AddCp, 15, ObjId);
	}
		break;
	case 53://ÖÒÒåÈâ¸¬
//		success = AddHp(100, ObjId, 10000);
		success = true;
		AddFunc(&ItemManager::AddHpHurt, 150, ObjId);
		AddFunc(&ItemManager::AddHp, 150, ObjId);
		break;
	case 54://ÕäÂ¶¾Æ
		success = AddCp(/*1 + pItem->m_pItemData->GetLv() / 2*/15, ObjId);
		break;
	case 55://°ÙÎ¶¾Æ
		success = AddCp(20, ObjId, false);
		break;
	case 56://Éßµ¨¾Æ
		success = AddCp(25, ObjId, false);
		break;
	case 57://×íÉúÃÎËÀ
		success = AddCp(30, ObjId, false);
		break;
	case 58://ÓñÂ¶¸þ
		success = true;
// 		AddHpHurt(100, ObjId, 10000);
// 		AddHp(100, ObjId, 10000);
// 		AddMp(100, ObjId, 10000);
		AddFunc(&ItemManager::AddMp, 60, ObjId);
		break;
	case 59://°ËÕäÓñÒº
		success = true;
// 		AddFunc(&ItemManager::AddHpHurt, 50, ObjId, 10000);
// 		AddFunc(&ItemManager::AddHp, 50, ObjId, 10000);
		AddFunc(&ItemManager::AddCp, 10, ObjId/*, 10000*/);
		break;
	case 60://Ç§½ðÂ¶
		success = true;
//		AddFunc(&ItemManager::relife, 1000, ObjId, false);//È«Ìå¸´»î
		AddFunc(&ItemManager::AddMp, 80, ObjId);
		break;
	default:
		ERRBOX;
		break;
	}

	if (0 == success)return false;
	if (pItem->m_Num > 0)
	{
		--pItem->m_Num;
	}

	if (g_StateType == STATE_MAIN)
		if (ObjId % 5 == g_pMainState->m_HeroID)
		{
		g_pHeroObj->m_Wav.Free();
		g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
		}
	return true;
}


bool ItemManager::UseItem23Åëâ¿(sItem2* pItem, int ObjId)
{
	if (g_StateType == STATE_FIGHT)return true;
	bool success;
	m_bAddHp = false;
	m_bAddMp = false;
	m_bAddCp = false;
	switch (pItem->GetID())
	{
	case 0:	//°ü×Ó 
		success = AddHp(300, ObjId);
		break;
	case 1://¿¾Ñ¼   
		success = AddHp(1000, ObjId);
		break;
	case 2://¶¹Õ«
		success = AddHp(3000, ObjId);
		break;
	case 3://³¤ÊÙÃæ
		success = AddHp(5000, ObjId);
		break;
	case 4://Å®¶ùºì
		success = AddHpHurt(200, ObjId);
		break;
	case 5://»¢¹Ç¾Æ
		success = AddHpHurt(500, ObjId);
		break;
	case 6://Ã·»¨¾Æ
		success = AddHpHurt(1000, ObjId);
		break;
	case 7://·ðÌøÇ½
		success = AddMp(500, ObjId);
		break;
	case 8://ôä´ä¶¹¸¯
		success = AddMp(2000, ObjId);
		break;
	case 9://ÁúÖ®ÐÄÐ¼
		success = AddHp(3500, ObjId);
		break;
	default:
		return false;
		break;
	}
	if (0 == success)return false;
	pItem->m_Num -= 1;

	if (g_StateType == STATE_MAIN)
		if (ObjId % 5 == g_pMainState->m_HeroID)
		{
		g_pHeroObj->m_Wav.Free();
		g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
		}
	return true;
}



int ItemManager::GetCheapestItemÓÒ¼ü¼ÓÑª(int CharID, ItemProPerty Type)
{
	cCharacter* pChar = (cCharacter*)g_pMainState->m_FightWorkList[CharID].m_pObj->m_pIndex;
	sItem* pItem;
	int cost = 100000;
	int retId = -1;
	switch (Type)
	{
	case enum_hp:
		if (1)
		{
			for (int i = 0; i < 20; i++)
			{
				if (0 == pChar->m_PcData.m_Items[i].GetNum())continue;
				if (pChar->m_PcData.m_Items[i].GetType() == 23)
				{
					pItem = pChar->m_PcData.m_Items[i].m_pItemData;
					switch (pItem->m_ID)
					{
					case 0:
						return i;
					case 1:
						if (cost > 10)
						{
							cost = 1;
							retId = i;
						}
						break;
					case 2:
						if (cost > 20)
						{
							cost = 2;
							retId = i;
						}
						break;
					case 3:
						if (cost > 30)
						{
							cost = 1;
							retId = 3;
						}
						break;
					}
				}
				else
					if (pChar->m_PcData.m_Items[i].GetType() == 22)
					{
					pItem = pChar->m_PcData.m_Items[i].m_pItemData;
					switch (pItem->m_ID)
					{
					case 1://ËÄÒ¶»¨
						if (cost > 1)
						{
							cost = 1;
							retId = i;
						}
						break;
					case 2:
						if (cost > 2)
						{
							cost = 2;
							retId = i;
						}
						break;
					case 3:
						if (cost > 3)
						{
							cost = 3;
							retId = i;
						}
						break;
					case 4:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 5:
						if (cost > 12)
						{
							cost = 12;
							retId = i;
						}
						break;
					case 6:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 7:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 8:
						if (cost > 21)
						{
							cost = 21;
							retId = i;
						}
						break;
					case 9:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 10:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 11:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 12:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 13:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 15:
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 40://ÔÂ¼û²Ý
						if (cost > 15)
						{
							cost = 15;
							retId = i;
						}
						break;
					case 41:
						if (cost > 16)
						{
							cost = 16;
							retId = i;
						}
						break;
					case 42:
						if (cost > 17)
						{
							cost = 17;
							retId = i;
						}
						break;
					case 47: //ÁùµÀÂÖ»Ø 30%
						if (cost > 30)
						{
							cost = 30;
							retId = i;
						}
						break;
					}
					}
			}
		}
		break;
	case enum_hphurt:
		if (1)
		{
			for (int i = 0; i < 20; i++)
			{
				if (0 == pChar->m_PcData.m_Items[i].GetNum())continue;
				if (pChar->m_PcData.m_Items[i].GetType() == 23)
				{
					pItem = pChar->m_PcData.m_Items[i].m_pItemData;
					switch (pItem->m_ID)
					{
					case 4:   //Å®¶ùºì
						return i;
						break;
					case 5:   //»¢¹Ç¾Æ
						if (cost > 2)
						{
							cost = 2;
							retId = i;
						}
						break;
					case 6:   //Ã·»¨¾Æ
						if (cost > 16)
						{
							cost = 16;
							retId = i;
						}
						break;
					default:
						break;
					}
				}
				else
					if (pChar->m_PcData.m_Items[i].GetType() == 23)
					{
					pItem = pChar->m_PcData.m_Items[i].m_pItemData;
					switch (pItem->m_ID)
					{
					case 34:   //²Ý¹û
						if (cost > 1)
						{
							cost = 1;
							retId = i;
						}
						break;
					case 35:   //¾ÅÏã³æ
						if (cost > 2)
						{
							cost = 2;
							retId = i;
						}
						break;
					case 36:   //²Ý¹û
						if (cost > 3)
						{
							cost = 3;
							retId = i;
						}
						break;
					case 37:   //É½Ò©
						if (cost > 41)
						{
							cost = 11;
							retId = i;
						}
						break;
					case 38:   //ÁéÖ¬ È«Ìå
						if (cost > 5)
						{
							cost = 5;
							retId = i;
						}
						break;
					case 39:   //×ÏÊ¯Ó¢
						if (cost > 31)
						{
							cost = 31;
							retId = i;
						}
						break;
					case 40:   //ÔÂ¼û²Ý
						if (cost > 4)
						{
							cost = 4;
							retId = i;
						}
						break;
					case 41:   //Ã·»¨¾Æ
						if (cost > 11)
						{
							cost = 11;
							retId = i;
						}
						break;
					}
					}
			}
		}
		break;
	case enum_mp:
		for (int i = 0; i < 20; i++)
		{
			if (0 == pChar->m_PcData.m_Items[i].GetNum())continue;
			if (pChar->m_PcData.m_Items[i].GetType() == 23)
			{
				pItem = pChar->m_PcData.m_Items[i].m_pItemData;
				switch (pItem->m_ID)
				{
				case 7:   //·ðÌøÇ½
					if (cost > 2)
					{
						cost = 2;
						retId = i;
					}
					break;
				case 8:   //ôä´ä¶¹¸¯
					if (cost > 10)
					{
						cost = 10;
						retId = i;
					}
					break;
				default:
					break;
				}
			}
			else
				if (pChar->m_PcData.m_Items[i].GetType() == 22)
				{
				pItem = pChar->m_PcData.m_Items[i].m_pItemData;
				switch (pItem->m_ID)
				{
				case 19:   //·ðÊÖ
					return i;
					break;
				case 20:   //Ðý¸´»¨
					if (cost > 1)
					{
						cost = 1;
						retId = i;
					}
					break;
				case 21:   //ÏãÒ¶
					if (cost > 2)
					{
						cost = 2;
						retId = i;
					}
					break;
				case 22:   //ÂüÙ¢ÂÞ»¨
					if (cost > 3)
					{
						cost = 3;
						retId = i;
					}
					break;
				case 23:   //ÌìÁúË®
					if (cost > 11)
					{
						cost = 11;
						retId = i;
					}
					break;
				case 24:   //²Í·çÒûÂ¶
					if (cost > 12)
					{
						cost = 12;
						retId = i;
					}
					break;
				case 26:   //×Ïµ¤ÂÞ È«Ìå
					if (cost > 5)
					{
						cost = 30;
						retId = i;
					}
					break;
				case 27:   //ÁúÐë
					if (cost > 6)
					{
						cost = 6;
						retId = i;
					}
					break;
				case 28:   //°×Óñ¹ÇÍ·
					if (cost > 16)
					{
						cost = 16;
						retId = i;
					}
					break;
				case 29:   //¶¡ÏãË®
					if (cost > 17)
					{
						cost = 17;
						retId = i;
					}
					break;
				case 30:   //ÔÂÐÇ×Ó
					if (cost > 26)
					{
						cost = 26;
						retId = i;
					}
					break;
				case 31:   //÷êÏã
					if (cost > 27)
					{
						cost = 27;
						retId = i;
					}
					break;
				case 32:   //ÏÉºüÏÑ
					if (cost > 28)
					{
						cost = 28;
						retId = i;
					}
					break;
				default:
					break;
				}
				}
		}
		break;
	default:
		MessageBoxA(0, "Î´ÉèÖÃÑ°ÕÒÀàÐÍ", "GetCheapestItem", MB_OK);
		break;
	}
	return retId;
}




bool ItemManager::AddHp(int Num, int TargetID, int Percent)
{
	cPropertyData* pPetData;
	g_pMainState->m_FightWorkList[TargetID].m_pObj->GetPropertyData(pPetData);
	return AddHp(Num, pPetData, Percent);
}


bool ItemManager::AddHp(int Num, cPropertyData* pdata, int Percent)
{
	m_bAddHp = true;
	if (g_StateType == STATE_FIGHT)
		if (0 == pdata->m_HP)return false;//ËÀÍöÊ±²»ÄÜ¼ÓÑª
	int& Hp = pdata->m_HP;
	int HpHurtMax = pdata->m_HP2;
	int HpMax = pdata->HPMax.GetData();
	if (Hp == HpMax)return false;//·ÀÖ¹ÂúÑª
	int add = Num;
	if (Percent)
	{
		add = HpMax * add / 100;
		if (add > Num * Percent)
			add = Num * Percent;
	}
	m_hp = add;
	Hp += add;
	//¼ÓÑª²»ÄÜ³¬¹ý×î´óÆøÑª
	if (Hp < 0)Hp = 0;
	else if (Hp > HpHurtMax)Hp = HpHurtMax;
	return true;
}


bool ItemManager::AddHpHurt(int Num, int TargetID, int Percent)
{
	cPropertyData* pPetData;
	g_pMainState->m_FightWorkList[TargetID].m_pObj->GetPropertyData(pPetData);
	return AddHpHurt(Num, pPetData, Percent);
}


bool ItemManager::AddHpHurt(int Num, cPropertyData* pPetData, int Percent)
{
	if (0 == pPetData->m_HP)return false;//ËÀÍöÊ±²»ÄÜ¼ÓÑª
	int& HpHurtMax = pPetData->m_HP2;
	int HpMax = pPetData->HPMax.GetData();
	if (HpHurtMax == HpMax)return false;
	int add = Num;
	if (Percent)
	{
		add = HpMax * add / 100;
		if (add > Num * Percent)
			add = Num * Percent;
	}
	HpHurtMax += add;
	if (HpHurtMax < 0)HpHurtMax = 0;
	else if (HpHurtMax > HpMax)HpHurtMax = HpMax;
	return true;
}


bool ItemManager::AddMp(int Num, int TargetID, int Percent)
{
	m_bAddMp = true;
	cObj* pObj = g_pMainState->m_FightWorkList[TargetID].m_pObj;
	cPropertyData* pPetData;
	pObj->GetPropertyData(pPetData);
	if (g_StateType != STATE_MAIN)
		if (0 == pPetData->m_HP)return false;//ËÀÍöÊ±²»ÄÜ¼ÓÑª
	int& Mp = pPetData->m_MP;
	int MpMax = pPetData->MPMax.GetData();
	if (Mp == MpMax)return false;
	int add = Num;
	if (Percent)
	{
		add = MpMax*add / 100;
		if (add > Num*Percent)
			add = Num*Percent;
	}
	Mp += add;
	if (Mp < 0)Mp = 0;
	else if (Mp > MpMax)Mp = MpMax;
	return true;
}


bool ItemManager::AddCp(int Num, int TargetID, int Percent)
{
	cObj* pObj = g_pMainState->m_FightWorkList[TargetID].m_pObj;
	cPropertyData* pPetData;
	pObj->GetPropertyData(pPetData);
	if (0 == pPetData->m_HP)return false;//ËÀÍöÊ±²»ÄÜ¼ÓÑª
	int& Cp = pPetData->m_CP;
	int add = Num;
	if (Percent)add = 150;
	Cp += add;
	if (Cp < 0)Cp = 0;
	else if (Cp > 150)Cp = 150;
	return  true;
}



bool ItemManager::AddFunc(bool(ItemManager::*AddSomething)(int, int, int), int Num, int TargetID, int Percent)
{
	m_bToAll = true;
	bool sucess = false;
	if (TargetID < 10)
	{
		for (int i = 0; i < 10; i++)
		{
			if (g_pMainState->m_FightWorkList[i].isExist)
				if ((this->*AddSomething)(Num, i, Percent)){ sucess = true; };
		}
	}
	else
	{
		for (int i = 10; i < 20; i++)
		{
			if (g_pMainState->m_FightWorkList[i].isExist)
				if ((this->*AddSomething)(Num, i, Percent)){ sucess = true; };
		}
	}
	return sucess;
}




bool ItemManager::relife(int Num, int TargetID, int Percent)
{
	cObj* pObj = g_pMainState->m_FightWorkList[TargetID].m_pObj;
	if (pObj->CheckHaveState(129) || pObj->CheckHaveState(2094))
	{
		return false;
	}
	pObj->SetStatic(false);
	pObj->Set(POS_FIGHT_STAND);
	g_pMainState->m_FightWorkList[TargetID].SetDie(false);
	cPropertyData* pPet;
	pObj->GetPropertyData(pPet);
	if (pPet->m_HP < 1)
	{
		pPet->m_HP = 1;
	}
	AddHpHurt(Num, TargetID, Percent);
	AddHp(Num, TargetID, Percent);
	pObj->MoveShadow();
	return true;
}


