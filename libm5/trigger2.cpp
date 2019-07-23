#include "global.h"


BOOL cTaskZhuXian::Process(int stage)
{
	Init();
	switch (m_Chapter)
	{
	case 0:return Process0(stage);
	case 1:return Process1(stage);
	case 2:return Process2(stage);
	case 3:return Process3(stage);
	case 4:return Process4(stage);
	case 5:return Process5(stage);
	case 6:return Process6(stage);
	case 7:return Process7(stage);
	case 8:return Process8(stage);
	case 9:return Process9(stage);
	}
	ERRBOX;
	return FALSE;
}

BOOL cTaskZhuXian::Process0(int stage)
{
	switch (stage)
	{
	case -1:break;
	case 106://奸商
		AddTriggerDialog2(17, 107); break;
	case 107:
		Select(54, 57, -1, 55, -1, 56, 109); break;
	case 109:
		AddTriggerDialog2(18, 110);
		break;
	case 110:
		
		{
			SetINT(12,3);
			cPet* Pet4 = 0;
			sAddPoint addpoint;
			addpoint.Set(4, 0, 0, 1, 0);
			g_pMainState->MakeAPet(Pet4, e泡泡, 100, 14, addpoint);
			g_pMainState->GivePcAPet(0, Pet4);
			RemoveTriggerObjMap(106);
			RemoveNpc(53, TRUE);
		}
		break;
	case 0:
		
		{
			SetChapter(0);
			g_pMainState->m_GlobalButton[0] = 80;
			g_pMainState->m_GlobalButton[6] = 0;
			g_pMainState->m_GlobalButton[5] = 0;
			g_pMainState->m_GlobalButton[4] = 0;

			g_pMainState->LoadCharacterData2(g_pMainState->m_HeroID, "篮子");
			g_pMainState->SetCharacter(g_pMainState->m_HeroID);
			g_pCharacter->m_PCData.m_Controler.Set(0, 0);
			g_pHeroObj->Reset();
			g_pHeroObj->Set(POS_STAND);
			g_pCharacter->m_PCData.m_Money[0] = 2000 + 998000;
			g_pMainState->m_Map.LoadMap(34, 131, "建邺城", FALSE);

		
		
		//	g_pMainState->GivePcAPet(g_pMainState->m_HeroID,);
			//g_pCharacter->m_PCData.GetShangPinPet(6);
		//	g_pCharacter->m_PCData.m_MengPaiID = eMP_狮驼岭;
		//	g_pCharacter->m_PCData.Followlv(159);
		//	////g_pMainState->m_Friend.AddFriend("羽灵神");
		////	g_pCharacter->m_PCData.m_Money[0] = 200000000;
		//	g_pCharacter->m_PCData.modeid = eJuSe杀破狼;
		//	g_pHeroObj->Reset();
		//	g_pHeroObj->Set(POS_STAND);
		//	Invite("怀念");
			//Invite("羽灵神");
			//g_pMainState->m_Friend.AddFriend("敖白");
			///*int id = g_pMainState->m_Friend.FindFriend("小蛮");
			//g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "小蛮2";*/
			//Invite("敖白");
			//	g_pMainState->m_Friend.AddFriend("清风");
			//	
			//	int id = g_pMainState->m_Friend.FindFriend("清风");
			//	g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "清风2";
			//	Invite("清风");
			//	g_pMainState->m_Friend.AddFriend("怀念");
			//	Invite("怀念");
			//	SetJiangLi2(0, 9999999);
			//	SetChapter(9);
			//	Process9(1);
			//	return TRUE;
			/*for (int i = 6; i < 11; i++)
				SetJiangLiItem(i, 27);*/
			//g_pCharacter->m_PCData.GoldLivePercent.d1 = 100;

			//g_pMainState->m_Map.Load(521, 124, "长安城");
			//g_pMainState->m_Map.LoadMap(56, 44, "阴曹地府");
			//return Process9(0);

			/*sItem2 item;
			item.m_Num = 1;
			for (int i = 10; i < 20; i++)
			{
				item.Set(24, i);
				g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
			}*/
			/*SetChapter(5);
			Process5(17);
			return TRUE;*/
			g_pMainState->SetDialogList(m_Textlist[1], 0xB0212A04);
			TalkList(15, 21, 7, 38, 101); //梦幻精灵
			AddChannel(m_Textlist[38]);
			g_pMainState->m_ZhiXian2.Process(0);
#ifndef TESTDEBU
			g_pMainState->LockLv(7);			
			LockMap(59);
			LockMap(60);
			LockMap(61);
#endif
		}
		return TRUE;
	case 36:
		for (int i = 0; i < 3; i++)
		{
			AddFriend(48 + i);
		}
		TalkList(20, 66, 67, 43, 38, 34);
		break;
	case 34:
		{
			int id;
			for (int i = 0; i<3; i++)
			{
				AutoGetPet(m_Textlist[48 + i], 1);
				g_pMainState->m_Friend.Invite(m_Textlist[48 + i]);
				
			}
			id = g_pMainState->m_Friend.FindFriend("燕子");
			g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "燕子2";
			if (id > -1)g_pMainState->m_Friend.Invite("燕子");
			g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect, 1);
			RemoveTriggerObjMap();
			RemoveNpc(40, TRUE);
			
		}
		break;

	case 38:
			AddTriggerDialog2(25);
			UpdateJob2(68);
			SetJiangLi(30,1,0,50,200,200);
			AddTriggerLv(37, 35);
			RemoveTriggerObj();
			break;
	case 37:
		{	
			SetChapter(1);
			Process(0);
		}
		break;
	case 105:
		g_pMainState->m_TaskNormal.Process(4);
		g_pMainState->m_Channel.AddNewString(m_Textlist[39]);
		break;
	
	case 101://宠物仙子
		{
			g_pMainState->m_DialogList.clear();
			NowNpcTalk(m_Textlist[20]);
			AddChannel(m_Textlist[2]);
			UpdateJob2(20);
			AddTriggerObj(m_Textlist[3], m_Textlist[4], 1);
			cPet* Pet4 = 0;
			sAddPoint addpoint;
			addpoint.Set(4, 0, 0, 1, 0);
			g_pMainState->MakeAPet(Pet4, /*6*/e泡泡, 100, 10, addpoint);
			g_pMainState->GivePcAPet(0, Pet4);
		}
		return TRUE;
	case 1: //找到兵铁铺
		{
			NowNpcTalk(m_Textlist[5]);
			SetJiangLiItem(0, 7);
			AddTriggerObj(m_Textlist[6], m_Textlist[7], 2);
			UpdateJob2(5);
			AddChannel(m_Textlist[46]);
		}
		return TRUE;
	case 2://找到装备鉴定商
		{
			cObj* pob = g_pMainState->FindObjByName(m_Textlist[6]);
			pob->Talk(m_Textlist[8]);
			for (int i = 0; i < 60; i++)
			{
				if (g_pCharacter->m_PCData.m_Item[i].GetNum())
				if (g_pCharacter->m_PCData.m_Item[i].GetType() == eWeaponType棒)
				{
					g_pMainState->m_ItemManage.AutoItemProperty(&g_pCharacter->m_PCData.m_Item[i]);
					break;
				}
			}
			AddChannel(m_Textlist[9]);
			RemoveTriggerObj();
			AddTriggerLv(3, 3/*5*/);
			UpdateJob2(9);
			AddTriggerFightStart(6);
			AddTriggerFightSuccess(105);
		}
		return TRUE;
	case 3: //燕子出现
		{
			sNpc npc;
			npc.Set("燕子", "东海海底", 2002, 14, 53,0);
			AddTriggerObjMap(&npc, 4);
			g_pMainState->m_Dialog.Talk(m_Textlist[10], m_Textlist[1], 0xB0212A04);
			UpdateJob2(10);
		}
		return TRUE;
	case 4: AddTriggerDialog2(0, 5); break;
	case 5:
		{
			
			AddTag(11);
			RemoveNpc(40,TRUE);
			g_pMainState->m_Friend.AddFriend("燕子");
			//给燕子买个BB
			AutoGetPet("燕子",0);
			g_pMainState->m_Friend.Invite("燕子");
			RemoveTriggerObjMap();
			AddTriggerLv(7, 8);
			g_pMainState->FindObj();
			
			AddTriggerDialog2(21, -5);
			g_pMainState->LockLv(9);
		}
		return TRUE;
	case -5:
		AddChannel(m_Textlist[47]);
		return TRUE;
	case 6:
		{
			g_pMainState->m_TriggerFightStart.ReMove(this);
			AddTag(12);
			AddChannel(m_Textlist[12]);
		}
		return TRUE;
	case 7:AddTriggerDialog2( 1, 8); break;
	case 8:
		{
			AddTriggerObj(m_Textlist[15], m_Textlist[16], 9);
			UpdateJob2(14);
		}
		return TRUE;
	case 9:
		
		{
			AddTriggerDialog2( 2,10);
		}
		return TRUE;
	case 10:
		
		{
			sNpc npc;
			npc.Set(m_Textlist[53], m_Textlist[7], 2009, 110, 54, 1);
			AddTriggerObjMap(&npc, 106,FALSE);

			//AddTriggerObjMap(&npc, 4);
			UpdateJob2(19);
			AddTriggerObjMap(m_Textlist[7], 11,FALSE);
		}
		return TRUE;
	case 11:
		AddTriggerDialog2( 3, 12);
		break;
	case 12:
		RemoveTriggerObjMap(11);
		UpdateJob2(17);
		AddTriggerObjMap(m_Textlist[18],13,FALSE);
		return TRUE;
	case 13:AddTriggerDialog2(4, -14); break;
	case -14:
		
		{
			AddTriggerFightFalse(-15);//
			AddTriggerFightEscape(-15);//
		}
	case 14://进入BOSS战
		
		{
			cPetData* petdata = AddPetEnemy2(1000, e僵尸, 9, 58);
			petdata->AddSkill(ePS_高级连击);
			petdata->AddSkill(ePS_吸血);
			petdata->AddSkill(ePS_高级反击);
			petdata->m_CounterRate.d1 = 50;
			petdata->m_Combo.d1 = 100;
			petdata->m_Pierce.d1 = 10;
			
			int id;
			for (int i = 0; i < 5; i++)
			{
				id = rand() % 2;
				if (id)id = 20;
				else id = 21;
				AddPetEnemy((ePetID)id, 7); 
			}
			g_pMainState->m_Mp3.Load("战斗BOSS");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(15);		
			AddTriggerDialog2(22, -1);
		}
		return TRUE;
	case -15:
		
		{
			RemoveTriggerObjMap();
			AddTriggerObj("商人的鬼魂", m_Textlist[18], 14); break;//战斗失败
		}
		break;
	case 15://商人的鬼魂奖励
		
		{
			SetJiangLi2(20000, 3000, 20000, 20000, TRUE);
			SetJiangLiItem(1, 21);
			SetJiangLiItem(0, 23, 30);
			RemoveTriggerObjMap();
			AddTriggerDialog2( 5, 16);
			g_pMainState->m_GlobalButton[14]+= 200;
			g_pMainState->m_GlobalButton[15] += 200;
			UpdateJob2(29);
			RemoveTriggerObj();
			g_pCharacter->m_PCData.AddHpZZ(100);
			g_pCharacter->m_PCData.AddAtkZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
		}
		return TRUE;
	case 16://县令
		AddTag(44);
		AddTriggerObj2(15, 16, 17);
		return TRUE;
	case 17:
		RemoveTriggerObj();
		if (!CheckINT(12,3))
			AddTriggerDialog2( 6, 18);
		else
			AddTriggerDialog2( 19, 18);
		return TRUE;
	case 18://商人的鬼魂结束
		
		{
			AddTag(22);
			UpdateJob2(28);
			AddTriggerObjMap(m_Textlist[23], 19);
			g_pMainState->LockLv();
			g_pMainState->m_Map.SetLock();
			sNpc npc;
			npc.Set(m_Textlist[52], m_Textlist[7], 2011, 92, 49,1);
			AddTriggerObjMap(&npc, -18);
			AddTriggerDialog2(23);
		}
		return TRUE;
	case -18:TalkList(16,-1,-1,-1,-1); break;
	case 19:AddTriggerDialog2(7, 20); 
		RemoveTriggerObjMap();
		break;
	case 20://
		
		{
			g_pMainState->m_Friend.UnInvite("燕子");
			AddTriggerObjMap2(48, 23, 2007, 473, 26, 3, -20);
			UpdateJob2(69);
			g_pMainState->m_Map.ShadowNpc(m_Textlist[27], FALSE, FALSE);
		}
		return TRUE;
	case -20:
		TalkList(26, 27, 23, 26, 23);
		RemoveTriggerObjMap();
		g_pMainState->m_Map.ShadowNpc(m_Textlist[27], TRUE, TRUE);
		return TRUE;
	case 23:AddTriggerDialog2( 9, 24); break;
	case 24:
		{
			RemoveTriggerObj();
		g_pMainState->m_Map.LoadMap(12, 10, "盘丝洞");
		g_pMainState->m_Tags.Add("你也可以拜其他门派,点击左上角第三个小灯笼就可以满世界飞了");
		g_pMainState->m_Channel.addChat("你也可以拜其他门派,点击左上角第三个小灯笼就可以满世界飞了");
	//	AddTriggerObj(m_Textlist[30], m_Textlist[31], 25);
	//	UpdateJob2(51);
	//	return TRUE;
	//case 25://拜师
	//	AddTag(32);
	//	g_pMainState->m_Channel.AddNewString(m_Textlist[33]);
	//	g_pCharacter->m_PCData.m_MengPaiID = 6;
		LockMap();
		LockMap(FALSE);
	/*	SetJiangLiItem(0, 27, 30);
		SetJiangLiItem(12, 28, 3);
		AddChannel(m_Textlist[45]);*/
		g_pMainState->m_FangWu.SetGuiMo(0);
		UpdateJob2(37);
	
			sMapObjTrigger npc;
			npc = g_pMainState->m_Friend.m_FriendList[g_pMainState->m_Friend.FindFriend("燕子")];
			npc.m_Npc.m_mapname = "长安城";
			npc.m_pTask = this;
			npc.m_Stage = 36;
			npc.m_Npc.Set(444, 245);
			AddTriggerObjMap(&npc);
			LockMap();
		}
		break;
	default:
		ERRBOX;
		return TRUE;
	}
	return TRUE;
}

void cTaskJuQing::UpdateJob2(string text)
{
	UpdateJob(text, "主线");
}

void cTaskJuQing::UpdateJob2(int id)
{
	if (id == -1)
		g_pMainState->m_Job.ReMoveJob(this);
	else
		UpdateJob2(m_Textlist[id]);
}

BOOL cTaskZhuXian::Process1(int stage)
{
	switch (stage)
	{
	case -1:return TRUE;
	case 0:AddTriggerDialog2(0, 1); break;
	case 1://找南极仙翁
		UnInvite("怀念");
		UnInvite("敖白");
		UnInvite("紫菜");
		RemoveTriggerObj();
		UpdateJob2(1);
		AddTriggerObj2(2, 3, 2);
		g_pMainState->LockLv(36);
		g_pMainState->m_GlobalButton[4] = 1;
		break;
	case 2:AddTriggerDialog2(1, 3); break;
	case 3://找白鹿
		AddTriggerObj2(5, 4, 4);
		UpdateJob2(6);
		break;
	case 4:
		AddTriggerDialog2(2, 5); 
		break;
	case 5: //白鹿战斗
		
		{
			AddPCPetEnemy2(3500, e九色鹿, 25, eMP_大唐官府,5);
			AddPCPetEnemy2(3500, e狐狸精, 27, eMP_方寸山, 65);
			AddPetEnemy2(2000, e花妖, 28);
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(6);
		}
		return TRUE;
	case 6://白鹿奖励
		
		{
			SetJiangLi2(100000, 20000, 50000, 200000, TRUE);
			AddTriggerDialog2(3, 7);	
			g_pCharacter->m_PCData.AddDefZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(37);
		}
		return TRUE;
	case 7:
		
		{
			UpdateJob2(1);
			AddTriggerObj2(2, 3,8);			
		}
		break;
	case 8:
		AddTriggerDialog2(4, -1);
		AddTriggerObj2(7, 8, 9);
		UpdateJob2(9);
		g_pCharacter->AddMoney(0, -500);
		g_pMainState->m_GlobalButton[3] = 1;//学会仙灵
		break;
	case 9:
		AddTriggerDialog2(5, -1);
		AddTriggerObj2(10, 11, 10);
		UpdateJob2(15);
		break;
	case 10:AddTriggerDialog2(6, 11);
		AddTriggerObj2(10, 11, 11);
		break;
	case 11://酒肉1
		
		{
			AddPCPetEnemy2(4000, e雨师, 30, eMP_化生寺, 10);
			for (int i = 0; i < 4; i++) AddPetEnemy2(2500, e赌徒, 40);
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(12);
		}
		break;
	case 12:
		
		{
			AddTriggerObj2(12, 13, 13);
			AddTriggerDialog2(7, -1);
			SetJiangLi2(150000, 20000, 50000, 200000);
			UpdateJob2(14);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(38);
		}
		break;
	case 13:
		g_pMainState->m_Friend.AddFriend("清风");
		AddTriggerDialog2(8, -13);
		AddTriggerObj2(16, 17, 14);
		UpdateJob2(19);
		break;
	case -13:
		
		{
			g_pMainState->m_Friend.Invite("清风");
			RemoveTriggerObjMap();
		}
		break;
	case 14:AddTriggerDialog2(9, 15); break;//天将
	case 15: 
		
		{
			AddPCPetEnemy2(4500, e天将, 34, eMP_天宫, 16);
			for (int i = 0; i < 4; i++) AddPetEnemy2(2500, e天兵, 34);
			SetMusic("绯雪千夜");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(16);
			
		}
		break;
	case 16:
		AddTriggerObj2(20, 8, 17);
		AddTriggerDialog2(10, -1);
		SetJiangLi2(170000, 20000, 50000, 120000);
		UpdateJob2(18);
		g_pCharacter->m_PCData.AddDefZZ(50);
		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(39);
		break;
	case 17:
		AddTriggerDialog2(11, 19);
		break;
	case 19://白琉璃
		
		{
			AddPCPetEnemy2(4500, e星灵仙子, 39, eMP_阴曹地府, 20);
			for (int i = 0; i < 4; i++) AddPetEnemy2(2500, e花妖, 39);
			SetMusic();
			
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(20);

		}
		break;
	case 20:
		RemoveTriggerObj();
		AddTriggerGive(m_Textlist[12], 22, 44, 21);
		AddTriggerDialog2(12, -1);
		SetJiangLi2(200000, 50000, 50000, 100000);
		UpdateJob2(38);
		g_pCharacter->m_PCData.AddHpZZ(100);
		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(40);
		break;
	case 21:
		AddTriggerDialog2(13, -21);
		UpdateJob2(21);
		AddTriggerObj2(22,11,22);
		g_pMainState->m_Friend.AddFriend(m_Textlist[64]);
		break;
	case -21:g_pMainState->m_Friend.Invite(m_Textlist[64]);
		break;
	case 22:AddTriggerDialog2(14, 23);
		break;
	case 23://酒肉2
		
		{
			AddPCPetEnemy2(4500, e雨师, 45, eMP_化生寺, 10);
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 3)
				{
				case 0:petid = e赌徒;
					break;
				case 1:petid = e强盗;
					break;
				default:petid = e山贼;
					break;
				}
				AddPetEnemy2(3000, petid, 50);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(24);
		}
		break;
	case 24:
		TalkList(15, 23, 24, 39, 125);
		SetJiangLi2(220000, 20000, 50000, 250000);
		g_pCharacter->m_PCData.AddAtkZZ(50);
		g_pCharacter->m_PCData.AddHpZZ(100);
		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(42);
		break;
	case 125://青莲仙女
	
		{
			TalkList(49, 75, 76, 77, 126);
			sMapObjTrigger obj;
			obj.m_Npc.Set(m_Textlist[75], m_Textlist[76], e超级大熊猫, 84, 59);
			obj.m_Stage = 126;
			obj.m_pTask = this;
			AddTriggerObjMap(&obj);
		}
		break;
	case 126:
		
		{
			AddPCPetEnemy2(4500, e超级大熊猫, 40, eMP_狮驼岭);
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 3)
				{
				case 0:petid = e黑熊;
					break;
				case 1:petid = e白熊;
					break;
				default:petid = e黑熊精;
					break;
				}
				AddPetEnemy2(3000, petid, 39);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(127);
		}
		break;
	case 127:
		
		{
		SetJiangLi2(230000, 20000, 50000, 200000);
		AddTriggerObj2(23, 24, 25);
		UpdateJob2(39);
	
		RemoveTriggerObjMap();
		RemoveNpc(81,TRUE);
		g_pMainState->LockLv(43);
		g_pMainState->m_GlobalButton[14] += 200;
		g_pMainState->m_GlobalButton[15] += 200;
		g_pCharacter->m_PCData.AddAtkZZ(50);
		g_pCharacter->m_PCData.AddGrowing(1);
		AddChannel2(82);
		AddChannel2(83);
		sShangPinPet sppet;
		sppet.Set(e超级大熊猫, 0, 100, TRUE);
		GetPet(m_Textlist[64], &sppet, 100);
		}
		break;
	case 25://青莲仙女
		AddFriend(84);
		AddTriggerDialog2(16, -1);
		AddTriggerObj2(25, 26, 26);
		UpdateJob2(27);
		break;
	case 26://孟婆
		AddTriggerDialog2(17, -1);
		AddTriggerObj2(28, 29, 27);
		UpdateJob2(30);
		break;
	case 27://幽冥鬼
		AddTriggerDialog2(18, 28);
		break;
	case 28:
		
		{
			AddPCPetEnemy2(4500, e巡游天神, 41, eMP_阴曹地府, 28);
			for (int i = 0; i < 4; i++)
			{
				ePetID petid;
				switch (rand() % 4)
				{
				case 0:petid = e骷髅怪;
					break;
				case 1:petid = e马面;
					break;
				case 2:petid = e僵尸;
					break;
				default:petid = e牛头;
					break;
				}
				AddPCPetEnemy2(3000, petid, 40);
			}
			SetMusic();

			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(29);
		}
		break;
	case 29:
		TalkList(19, 31, 32, 33, 30);
	
		SetJiangLi2(250000, 50000, 50000, 250000);

		g_pCharacter->m_PCData.AddDefZZ(50);
		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(45);
		break;
	case 30://文秀
		AddTriggerObj2(28, 29, 31);
		AddTriggerDialog2(20, -30);	
		break;
	case -30:
		SetJiangLiItem(5, 18);
		UpdateJob2(30);
		break;
	case 31://幽冥鬼
		AddTriggerObj2(25, 26, 32);
		AddTriggerDialog2(21, -1);
		UpdateJob2(27);
		break;
	case 32://孟婆
		AddTriggerObj2(22, 11, 33);
		AddTriggerDialog2(22, -1);
		UpdateJob2(40);
		break;
	case 33://玄奘
		AddTriggerObj2(34, 8, 34);
		AddTriggerDialog2(23, -1);
		UpdateJob2(35);
		break;
	case 34://守卫
		AddTriggerDialog2(24, 35); break;
	case 35:
		
		{
			for (int i = 0; i < 5; i++)
			{
				AddPCPetEnemy2(4000, e护卫, 42, eMP_大唐官府,34);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(36);
		}
		break;
	case 36:
		AddTriggerObj2(36, 8, 37);
		AddTriggerDialog2(25, -1);
		SetJiangLi2(270000, 20000, 50000, 270000);
		UpdateJob2(37);
		g_pCharacter->m_PCData.AddHpZZ(100);
		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(46);
		break;
	case 37://殷温娇
		AddTriggerObj2(41, 8, 38);
		AddTriggerDialog2(26, -1);
		UpdateJob2(42);
		break;
	case 38:AddTriggerDialog2(27, 39);
		break;
	case 39://虾兵战斗
		
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(6000,e虾兵, 43, eMP_东海龙宫, 41);
			pPet->m_MagicWater.d2 += 20;
			for (int i = 0; i < 4; i++)
			{
				ePetID petid;
				switch (rand() % 4)
				{
				case 0:petid = e海星;
					break;
				case 1:petid = e章鱼;
					break;
				case 2:petid = e大海龟;
					break;
				default:petid = e海毛虫;
					break;
				}
				pPet= AddPCPetEnemy2(4000,petid, 40, (eMengPai)(rand() % 12));
				pPet->m_MagicWater.d2 += 10;
			}
			g_pMainState->m_Mp3.Load("战斗BOSS");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(40);
			AddTriggerDialog2(51);
		}
		break;
	case 40:
		AddTriggerObj2(44, 45, 41);
		SetJiangLi2(300000, 100000, 50000, 300000);
		UpdateJob2(43);
		g_pCharacter->m_PCData.AddMagZZ(100);
		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(47);
		break;
		//蟹将战斗
	case 41:AddTriggerDialog2(28, 42);
		break;
	case 42:
		
		{
			cPetData* pPet;
			 pPet= AddPCPetEnemy2(4500, e蟹将, 44, eMP_东海龙宫, 44);
			 pPet->m_MagicWater.d2 += 20;
			for (int i = 0; i < 4; i++)
			{
				ePetID petid;
				switch (rand() % 4)
				{
				case 0:petid = e海星;
					break;
				case 1:petid = e章鱼;
					break;
				case 2:petid = e虾兵;
					break;
				default:petid = e海毛虫;
					break;
				}
				AddPCPetEnemy2(3500, petid, 42, (eMengPai)(rand() % 12));
				pPet->m_MagicWater.d2 += 20;
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(43);
		}
		break;
	case 43:
		TalkList(29, 46, 45, 47, 44);
		SetJiangLi2(320000, 100000, 50000, 320000);
		g_pCharacter->m_PCData.AddMagZZ(100);
		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(48);
		break;	
	case 44://龟千岁
		TalkList(30, 36, 8, 37, 45);
		break;
	case 45://殷温娇
		TalkList(31, 49, 50, 48, 46);
		break;
	case 46://殷丞相
		TalkList(32, 52, 53, 51, 47);
		AddTriggerGive(m_Textlist[49] ,22,30, 49);
		break;
	case 47://江湖奸商
		AddTriggerDialog2(33, 48); break;
	case 48:
		RemoveTriggerObj();
		SetJiangLiItem(30, 22);
		g_pCharacter->m_PCData.m_Money[0] -= 50000;
		break;
	case 49://殷丞相
	
		{
			AddTriggerDialog2(34, -1);
			UpdateJob2(56);
			sNpc npc;
			npc.Set(m_Textlist[66], m_Textlist[8], 2012, 226, 190, 3);
			AddTriggerObjMap(&npc, 152);
			npc.Set(m_Textlist[67], m_Textlist[8], e山贼, 230, 186, 7);
			AddTriggerObjMap(&npc, 152, 0);
			npc.Set(m_Textlist[67], m_Textlist[8], e山贼, 233, 194, 1);
			AddTriggerObjMap(&npc, 152, 0);
			AddTriggerObjMap(m_Textlist[8], 151,0);
		}
		break;
	case 151:
		AddTriggerDialog2(44, -1);
		RemoveTriggerObjMap(151);
		UpdateJob2(68);
		break;
	case 152://山贼战斗
		AddTriggerDialog2(45, 153);
		break;
	case 153:
		
		{
			AddPCPetEnemy2(100000, e程咬金, 50, eMP_大唐官府,-1,TRUE);
			for (int i = 0; i < 10; i++)
			{
				ePetID petid;
				switch (rand() % 4)
				{
				case 0:petid = e山贼;
					break;
				default:petid = e强盗;
					break;
				}
				AddPCPetEnemy2(3000, petid, 19, (eMengPai)(rand() % 12));
			}
			SetMusic();

			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(154);
		}
		break;
	case 154:
		RemoveNpc(67);
		RemoveNpc(67,1);
		RemoveTriggerObjMap(-1);
		TalkList(46, 54, 55, 56, 50,155);
		SetJiangLi2(340000, 100000, 50000, 340000);
		g_pCharacter->m_PCData.AddGrowing(5);
		g_pMainState->LockLv(49);
		break;
	case 155:
		RemoveNpc(66,1);
		break;
	case 50://刘洪1
		AddTriggerDialog2(35, 51);
		break;
	case 51:
		{
			AddPCPetEnemy2(100000, e程咬金, 50, eMP_大唐官府, -1, TRUE);
			AddPCPetEnemy2(6000,e强盗, 45, eMP_大唐官府, 54);
			for (int i = 0; i < 7; i++)
			{
				ePetID petid;
				switch (rand() % 4)
				{
				case 0:petid = e山贼;
					break;
				case 1:petid = e护卫;
					break;
				case 2:petid = e赌徒;
					break;
				default:petid = e强盗;
					break;
				}
				AddPCPetEnemy2(3000, petid, 42, (eMengPai)(rand() % 12));
			}
			SetMusic();

			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(52);
		}
		break;
	case 52:
		{
			g_pMainState->SetDialogList(m_Textlist[69], g_pMainState->m_PetDataManager.GetPetData(e程咬金)->m_dialoghead[0]);
			TalkList(36, 54, 57, 58, 53);
		
			SetJiangLi2(350000, 100000, 50000, 350000);
			g_pCharacter->m_PCData.AddAtkZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(55);
		}
		break;
	case 53://刘洪2
		AddTriggerDialog2(37, 54);
		break;
	case 54:
		{
			cPetData* pPet;
			AddPCPetEnemy2(100000, e程咬金, 50, eMP_大唐官府, -1, TRUE);
			pPet= AddPCPetEnemy2(8000, e护卫, 46, eMP_大唐官府, 54);
			pPet->m_AtkDownHPHurt.d1 += 5;
			pPet= AddPCPetEnemy2(8000, e强盗, 46, eMP_阴曹地府, 59);
			pPet->AddSkill(ePS_鬼魂术);
			for (int i = 0; i < 5; i++)
			{
				ePetID petid;
				switch (rand() % 4)
				{
				case 0:petid = e骷髅怪;
					break;
				case 1:petid = e马面;
					break;
				case 2:petid = e僵尸;
					break;
				default:petid = e牛头;
					break;
				}
				AddPCPetEnemy2(4000, petid, 45);//(eMengPai)(rand() % 12));
			}
			SetMusic("OneLight");

			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(55);
		}
		break; 
	case 55:
		{
			AddTriggerDialog2(38, -57);
			AddPCPetEnemy2(100000, e程咬金, 50, eMP_大唐官府, -1, TRUE);
			cPetData* pPet= AddPCPetEnemy2(8000, e黑山老妖, 55, eMP_阴曹地府, 59);
			pPet->AddSkill(ePS_鬼魂术);
			pPet->m_SuckBloodRate.d1 += 10;
			pPet->SetJinJie(2);
			for (int i = 0; i < 8; i++)
			{
				ePetID petid;
				switch (rand() % 4)
				{
				case 0:petid = e黑山老妖;
					break;
				case 1:petid = e马面;
					break;
				case 2:petid = e僵尸;
					break;
				default:petid = e牛头;
					break;
				}
				AddPCPetEnemy2(4000, petid, 50, (eMengPai)(rand() % 12));
			}
			SetMusic("凶夢伝染");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(57);
			
		}
		break;
	case -57:
		AddTriggerDialog2(47);
		break;
	case 57:
		AddTriggerDialog2(39, -1);
		AddTriggerObj2(61, 8, 58);
		SetJiangLi2(400000, 100000, 50000, 400000);
		UpdateJob2(62);
		g_pCharacter->m_PCData.AddDefZZ(100);
		g_pCharacter->m_PCData.AddHpZZ(300);
		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(56);
		break;
	case 58://刘母
		AddTriggerDialog2(40, 59);
		g_pMainState->m_DialogList.clear();
		break;
	case 59:
		AddTriggerObj2(36, 8, 60);
		UpdateJob2(37);
		break;
	case 60://殷温娇
		AddTriggerDialog2(41, -1);
		AddTriggerObj2(22, 11, 61);
		UpdateJob2(63);
		break;
	case 61://玄奘
		TalkList(42, -1, -1, -1, -1,62); 
		break;
	case 62:
		SetJiangLiItem(6, 40);
		AddTriggerDialog2(48);
		Process2(0);
		break;
	default:
		ERRBOX;
		break;
	}
	return TRUE;
}

void cTaskJuQing::RemoveNpc(int id, BOOL needfind /*= FALSE*/)
{
	g_pMainState->m_Map.RemoveNpc(m_Textlist[id], needfind);
}



void cTaskJuQing::AddChannel2(int id)
{
	AddChannel(m_Textlist[id]);
}

void cTaskJuQing::AddTriggerObj2(int name, int mapname, int ret, BOOL bHuChi)
{
	if (name == -1)
		RemoveTriggerObj();
	else
		AddTriggerObj(m_Textlist[name], m_Textlist[mapname], ret,bHuChi);
}

void cTaskJuQing::AddTriggerDialog2(int id, int ret)
{
	AddTriggerDialog(SetUpPathJuQing(m_Textlist[0]), id, ret);
}

void cTaskJuQing::UnInvite(string dafilename)
{
	g_pMainState->m_Friend.UnInvite(dafilename);
}

void cTaskJuQing::FollowLv(int id, int lv)
{
	g_pMainState->m_FightList[id].m_pData->FollowLv(lv);
}

BOOL cTaskZhuXian::Process2(int stage)
{//四琉璃
	switch (stage)
	{
	case 0:
		SetChapter(2);
		g_pMainState->m_GlobalButton[5] = 2;
		AddTriggerDialog2(0,-1);
		AddTriggerObj2(1, 2, 1);
		UpdateJob2(16);
		break;
	case 1://卷帘大将
		AddTriggerDialog2(1, -1);
		AddTriggerObj2(3, 4, 2);
		UpdateJob2(15);
		break;
	case 2://粟粟娘
		AddTriggerDialog2(2, -1);
		AddTriggerObj2(5, 6, 3);
		UpdateJob2(17);
		break;
	case 3://女妖
		AddTriggerDialog2(3, 4);
		break;
	case 4: 
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(4500, e芙蓉仙子, 57, eMP_盘丝岭, 5);
			pPet->m_LiveHpLv += 10;
			pPet->m_Combo.d1 += 20;
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 3)
				{
				case 0:petid = e赌徒;
					break;
				case 1:petid = e强盗;
					break;
				default:petid = e山贼;
					break;
				}
				AddPetEnemy2(3000, petid, 60);
			}
			SetMusic("镜影命缘");

			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(5);
		}
		return TRUE;
	case 5:
		{
			SetJiangLi2(450000, 100000, 50000, 450000);
			AddTriggerDialog2(4, -1);
			AddTriggerObj2(7,6,6);
			UpdateJob2(18);
			g_pCharacter->m_PCData.AddDefZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(57);
		}
		return TRUE;
	case 6://金琉璃
		AddTriggerDialog2(5, 7);
		break;
	case 7:
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(6000, e如意仙子, 60, eMP_盘丝岭, 7);
			pPet->poisonRate.d1 += 20;
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 3)
				{
				case 0:petid = e蜘蛛精;
					break;
				case 1:petid = e狐狸精;
					break;
				default:petid = e蝴蝶仙子;
					break;
				}
				AddPetEnemy2(4000, petid, 64);
			}
			SetMusic("镜影命缘");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(8);
		}
		return TRUE;
	case 8:
		{
			g_pMainState->m_Friend.AddFriend(m_Textlist[28]);
			SetJiangLi2(480000, 100000, 50000, 480000);
			AddTriggerDialog2(6, 88);
			AddTriggerObj2(8, 4, 9);
			UpdateJob2(15);
			g_pCharacter->m_PCData.AddDefZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(59);
		}
		return TRUE;
	case 88:
		g_pMainState->m_Friend.Invite(m_Textlist[28]);
		AddChannel2(29);
		break;
	case 9://柳飞絮
		AddTriggerDialog2(7, -1);
		AddTriggerObj2(9, 10, 10);
		UpdateJob2(20);
		break;
	case 10://青琉璃
		AddTriggerDialog2(8, -1);
		AddTriggerObj2(26, 10, 11);
		UpdateJob2(21);
		break;
	case 11://翻天怪
		AddTriggerDialog2(9,12);
		break;
	case 12:
		{
			cPetData* p= AddPCPetEnemy2(15000, e地狱战神, 70, eMP_魔王寨, 26);
			p->m_StabRate.d1 = 100;
			p->m_StabDamageRate.d1 = 40;
			AddPetEnemy2(4000, e白熊, 65);
			AddPetEnemy2(4000, e古代瑞兽, 65);
			
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(13);
		}
		return TRUE;
	case 13:
		{
			SetJiangLi2(500000, 100000, 50000, 500000);
			AddTriggerDialog2(10, -1);
			AddTriggerObj2(9, 10, 14);
			UpdateJob2(22);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(60);
		}
		return TRUE;
	case 14://青琉璃
		AddTriggerDialog2(11, -1);
		AddTriggerObj2(11, 10, 15);
		AddTriggerGive(m_Textlist[9],22,30,17);
		UpdateJob2(23);
		break;
	case 15:AddTriggerDialog2(12, 16); break;
	case 16:
		SetJiangLiItem(30,22);
		SetJiangLi2(0, 40000);
		RemoveTriggerObj();
		AddTriggerDialog2(23, -1);
		break;
	case 17://青琉璃
		AddTriggerDialog2(13, -1);
		AddTriggerObj2(1, 2, 18);
		UpdateJob2(16);
		break;
	case 18://卷帘大将
		AddTriggerDialog2(14, -1);
		AddTriggerObj2(12, 2, 19);
		UpdateJob2(24);
		break;
	case 19://阿紫
		AddTriggerDialog2(15, -1);
		AddTriggerObj2(1, 2, 20);
		UpdateJob2(16);
		break;
	case 20://卷帘大将
		AddTriggerDialog2(16, -1);
		AddTriggerObj2(12, 2, 21);
		UpdateJob2(24);
		break;
	case 21://姚太尉
		AddTriggerDialog2(17, 22);
		break;
	case 22:
		{
			cPetData* ppet= AddPCPetEnemy2(8000, e天将, 70, eMP_天宫, 27);
			ppet->SetJinJie(2);
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 2)
				{
				case 0:petid = e天兵;
					break;
				default:petid = e天将;
					break;
				}
				AddPCPetEnemy2(6000, petid, 60, (eMengPai)(rand()%12));
			}
			SetMusic();	
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(23);
		}
		return TRUE;
	case 23:
		{
			SetJiangLi2(550000, 100000, 50000, 550000);
			AddTriggerDialog2(18, 123);
			AddTriggerObj2(1, 2, 24);
			UpdateJob2(16);
			g_pCharacter->m_PCData.AddAtkZZ(100);
			g_pCharacter->m_PCData.AddGrowing(2);
			g_pMainState->LockLv(61);
		}
		return TRUE;
	case 123:AddTriggerDialog2(24, -1); return TRUE;
	case 24://卷帘大将
		AddTriggerDialog2(19, -1);
		AddTriggerObj2(13, 14, 25);
		UpdateJob2(25);
		break;
	case 25://王母娘娘
		AddTriggerDialog2(20, 26);
		break;
	case 26:
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(8000, e超级孔雀, 75, eMP_天宫);
			pPet->comboNumDown += 1;
			ePetID petid;
			for (int i = 0; i < 6; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e凤凰;
					break;
				case 1:petid = e雨师;
					break;
				case 2:petid = e蛟龙;
					break;
				default:petid = e风伯;
					break;
				}
				AddPCPetEnemy2(6000, petid, 68);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(27);
		}
		return TRUE;
	case 27:
		{
			SetJiangLi2(550000, 100000, 50000, 550000);
			AddTriggerDialog2(21, -1);
			AddTriggerObj2(1, 2, 28);
			UpdateJob2(16);
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			g_pCharacter->m_PCData.AddDefZZ(100);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(62);
		}
		return TRUE;
	case 28://卷帘大将
		TalkList(22, -1, -1, 30, -1);
		{
			auto& zg = g_pMainState->m_TaskZhuaGui;
			zg.SetTrigger(this, /*9*/std::max(2, zg.m_HuanShu + 2), 29);
		}
		break;
	case 29://转到西梁女国剧情
		Process8(0);
		return TRUE;
	default:
		break;
	}
	return TRUE;
}

BOOL cTaskZhuXian::Process3(int stage)
{//小白龙
	switch (stage)
	{
	case 0:
		g_pMainState->m_GlobalButton[5] = 4;
		SetChapter(3);
		AddTriggerObj2(7, 8, 1);
		UpdateJob2(9);
		AddTriggerDialog2(1, -1);
		break;
	case 1://小白龙
		AddTriggerDialog2(2, 2);
		break;
	case 2://超级海豚
		{
			cPetData* petdata= AddPCPetEnemy2(16000, e超级海豚, 65, eMP_东海龙宫);
			petdata->m_MagicWater.d1 += 20;
			ePetID petid;
			for (int i = 0; i < 5; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e龟丞相; break;
				case 1:petid = e鲛人; break;
				case 2:petid = e蟹将; break;
				default:petid = e小龙女; break;
				}
				AddPCPetEnemy2(10000, petid, 60, (eMengPai)(rand() % 12));
			}
			SetMusic("Paranoia");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(5);
		}
		return TRUE;
	case 5:
		{
			SetJiangLi2(800000, 100000, 50000, 800000);	
			AddChannel2(27);
			AddChannel2(38);
			AddTriggerObj2(7, 8, 6);
		
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pCharacter->m_PCData.AddAvoidZZ(100);
			g_pCharacter->m_PCData.AddHpZZ(100);
			g_pMainState->LockLv(67);

			sShangPinPet sppet;
			sAddPoint addpoint;
			addpoint.Set(0, 0, 4, 1, 0);
			sppet.Set(e超级海豚,&addpoint,100,TRUE);
			GetPet(m_Textlist[35], &sppet, 100);
		}
		break;
	case 6://小白龙
		TalkList(0, 10, 11, 12, 7);
		break;
	case 7://塔塔之神
		AddTriggerDialog2(6, -1);
		AddTriggerObj2(13, 14, 8);
		UpdateJob2(15);
		break;
	case 8://奔波儿霸
		AddTriggerDialog2(7, -1);
		AddTriggerObj2(16, 17, 9);
		UpdateJob2(18);
		break;
	case 9://蟹将
		AddTriggerDialog2(8, 10);
		break;
	case 10://蟹将
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(16000, e蟹将, 69, eMP_东海龙宫);
			pPet->m_MagicWater.d2 += 20;
			ePetID petid;
			for (int i = 0; i < 6; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e蚌精; break;
				case 1:petid = e鲛人; break;
				case 2:petid = e蟹将; break;
				default:petid = e虾兵; break;
				}
				AddPCPetEnemy2(10000, petid, 62, (eMengPai)(rand() % 12));
			}
			SetMusic("魔方少女纹");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(11);
		}
		return TRUE;
	case 11:
		{
			SetJiangLi2(810000, 100000, 50000, 810000);
			AddTriggerDialog2(9, -1);
			AddTriggerObj2(19, 17, 12);
			UpdateJob2(20);
			g_pCharacter->m_PCData.AddMagZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(70);
		}
		return TRUE;
	case 12://万胜公主
		{
			AddTriggerDialog2(10, -1);
			AddTriggerObj2(21, 22, 13);
			UpdateJob2(23);
			
		}
		break;
	case 13://九头精怪
		g_pMainState->SetDialogListNpc(m_Textlist[19], 1001);
		AddTriggerDialog2(11, 14);
		break;
	case 14://
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(28000, e九头精怪, 70, eMP_狮驼岭,21);
			pPet->m_AtkDownHPHurt.d1 = 5;
			pPet= AddPCPetEnemy2(25000, e蚌精, 70, eMP_东海龙宫,19);
			pPet->m_MagicWater.d2 += 20;
			pPet->SetJinJie(3);
			ePetID petid;
			for (int i = 0; i < 8; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e牛妖; break;
				case 1:petid = e犀牛将军; break;
				case 2:petid = e犀牛将军人; break;
				default:petid = e野猪精; break;
				}
				AddPCPetEnemy2(12000, petid, 68);
			}
			SetMusic("redmoon");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(15);
		}
		return TRUE;
	case 15:
		{
			g_pMainState->ClearDialogList();
			SetJiangLi2(850000, 100000, 50000, 850000);
			
			AddTriggerDialog2(12, -1);
			AddTriggerObj2(24, 25, 16);
			UpdateJob2(26);
			g_pMainState->ClearDialogList();
			g_pCharacter->m_PCData.AddHpZZ(600);
			g_pCharacter->m_PCData.AddGrowing(2);
			g_pMainState->LockLv(73);
		}
		return TRUE;
	case 16://玉皇大帝
		AddTriggerDialog2(13, -1);
		AddTriggerObj2(7, 8, 17);
		UpdateJob2(9);
		break;
	case 17://小白龙
		TalkList(14, -1, -1, -1,-1, 18); 
		break;
	case 18:
		Process4(0);
		break;
	default:
		break;
	}
	return TRUE;
}

BOOL cTaskZhuXian::Process4(int stage)
{
	switch (stage)
	{
	case 0:
		g_pMainState->m_GlobalButton[5] = 6;
		SetChapter(4);
		TalkList(0, 1, 2, 3, 1,100);
		break;
	case 100:
		UnInvite(m_Textlist[44]);
		break;
	case 1:
		g_pMainState->m_DialogList.clear();
		TalkList(1,4,2,5,2);break;//猪八戒
	case 2:TalkList(2,6,7,8,3); break;//土地公公
	case 3:TalkList(3,9,10,11,4); break;//高翠兰
	case 4:TalkList(4,6,7,8, 5); break;//月老
	case 5:TalkList(5, 1, 2, 3, 6); break;//高翠兰
	case 6:TalkList(6, 4, 2, 5, 7); break;//猪八戒
	case 7:TalkList(7, 12, 13, 14, 8); break;//土地公公
	case 8:TalkList(8, 15, 13, 14, 9); break;//月香侍女
	case 9://康太尉
		AddTriggerDialog2(9, 10);
		break;
	case 10:
		{
			cPetData* ppet= AddPCPetEnemy2(20000, e巡游天神, 71, eMP_天宫, 15);	
			ppet->SetJinJie(2);
			 ppet = AddPCPetEnemy2(20000, e天兵, 71, eMP_天宫, 65);
			ppet->SetJinJie(2);
			 ppet = AddPCPetEnemy2(20000, e风伯, 71, eMP_天宫, 66);
			ppet->SetJinJie(2);
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e天将; break;
				case 1:petid = e天兵; break;
				case 2:petid = e雨师; break;
				default:petid = e风伯; break;
				}
				AddPCPetEnemy2(10000, petid, 70, (eMengPai)(rand() % 12));
			}
			SetMusic();
			
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(11);
		}
		return TRUE;
	case 11:
		{
			SetJiangLi2(900000, 100000, 100000, 900000);
			
			TalkList(10, 16, 17, 18, 12);
			g_pCharacter->m_PCData.AddAtkZZ(200);
			g_pCharacter->m_PCData.AddGrowing(5);
			g_pMainState->LockLv(75);
		}
		return TRUE;
	case 12:TalkList(11, 19, 20, 21, 13); break;//嫦娥
	case 13://杨戟
		AddTriggerDialog2(12, 14);
		break;
	case 14:
		{
			if (g_pMainState->m_GlobalButton[0]>50)
				AddTriggerDialog2(38);
			AddPCPetEnemy2(30000, e二郎神, 78, eMP_大唐官府);
			cPetData* pPet= AddPCPetEnemy2(20000, e啸天犬, 75, eMP_狮驼岭);
			pPet->m_SuckBloodRate.d1 += 10;
			pPet->SetJinJie(3);
			ePetID petid;
			for (int i = 0; i < 6; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e巡游天神; break;
				case 1:petid = e天将; break;
				case 2:petid = e雨师; break;
				default:petid = e风伯; break;
				}
				AddPCPetEnemy2(12000, petid, 70, (eMengPai)(rand() % 12));
			}
			SetMusic("stonecoldFictionJunction");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(15);
		}
		return TRUE;
	case 15:
		{
			SetJiangLi2(1000000, 150000, 150000, 1000000);
			
			TalkList(13, 22, 23, 24, 16);
			g_pCharacter->m_PCData.AddDefZZ(100);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(80);
		}
		return TRUE;
	case 16:TalkList(14, 16, 17, 18, 115); break;//慧觉
	case 115:
		{
			
			sMapObjTrigger obj;
			obj.m_Npc.Set(m_Textlist[52], m_Textlist[13], e超级神兔, 72, 72);
			obj.m_pTask = this;
			obj.m_Stage = -1;
			AddTriggerObjMap(&obj);
			TalkList(31, 52, 13, 53, 116); break;//嫦娥
		}
		break;
	case 116://超级神兔
		{
			AddTriggerDialog2(39);
			AddPCPetEnemy2(30000, e超级神兔, 80);
			for (int i = 0; i < 6; i++)
			{
				AddPCPetEnemy2(15000, e兔子怪, 78);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(118);
		}
		return TRUE;
	case 118:
		
		{
			RemoveTriggerObjMap();
			RemoveTriggerObj();
			RemoveNpc(52,TRUE);
			SetJiangLi2(1080000, 150000, 150000, 1080000);
			AddChannel2(67);
			TalkList(32, 16, 17, 18,17,-118);
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pCharacter->m_PCData.AddAvoidZZ(200);
			g_pCharacter->m_PCData.AddHpZZ(100);
			g_pMainState->LockLv(84);
	
			sShangPinPet sppet;
			sAddPoint addpoint;
			addpoint.Set(4, 0, 0, 1, 0);
			sppet.Set(e超级神兔, &addpoint, 100, TRUE);
			GetPet(m_Textlist[56], &sppet, 100);
		}
		break;
	case -118:
		AddTriggerDialog2(40);
		break;
	case 17:TalkList(15, 1, 2, 3, 18); break;//嫦娥
	case 18:TalkList(16, 4, 2, 5, 19); break;//天蓬元帅
	case 19:TalkList(17, 25, 26, 27, 20); break;//土地公公
	case 20:TalkList(18,28, 26, 29, 21); break;//春三十娘
	case 21:TalkList(19, 30, 2, 31, 22); break;//白晶晶
	case 22:TalkList(20, 32, 2, 33, 23); break;//至尊宝
	case 23:TalkList(21, 34, 35, 36, 24); break;//二当家
	case 24:TalkList(22, 37, 38, 39, 25); break;//江湖奸商
	case 25://龙神
	
		{
			sNpc npc;
			int x, y;
			g_pMainState->m_Map.AutoGetPos(x, y, m_Textlist[41]);
			npc.Set(m_Textlist[40], m_Textlist[41], 123, x, y,0);
			AddTriggerObjMap(&npc, -1);
			TalkList(23, 40, 41, 42, 26);
		}
		break;
	case 26://超级神龙
		AddTriggerDialog2(24, 27);
		break;
	case 27:
	
		{
			AddPCPetEnemy2(30000, e超级神龙, 85, eMP_魔王寨);
			for (int i = 0; i < 7; i++)
			{
				AddPCPetEnemy2(13000, e蛟龙, 78, (eMengPai)(rand() % 12));
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(28);
		}
		return TRUE;
	case 28:
		
		{
			SetJiangLi2(1120000, 200000, 200000, 1120000);
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			RemoveTriggerObjMap();
			TalkList(25, 37, 38, 39, 29);
			g_pCharacter->m_PCData.AddDefZZ(100);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(88);
		}
		return TRUE;
	case 29: TalkList(26, 59, 60, 58, 133);
		break;//龙神
	case 133://去地府找六道轮回
		g_pMainState->m_Friend.AddFriend(m_Textlist[61]);
		TalkList(33, -1, -1, 64, -1, 134);
		//AddRangeMap(63, 95, 57, 10, 135);
		break;
	case 134:
		Invite(m_Textlist[61]);
		AddTriggerObj2(62, 63, 135);
		break;
	case 135://千年怨鬼
		AddTriggerDialog2(34, 136);
		break;
	case 136:
		
		{
			cPetData* Pet= AddPCPetEnemy2(40000, e幽灵, 89, eMP_阴曹地府,62);
			Pet->AddSkill(ePS_反震);
			Pet->SetJinJie(3);
			ePetID petid;
			for (int i = 0; i < 8; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e僵尸; break;
				case 1:petid = e鬼将; break;
				case 2:petid = e吸血鬼; break;
				default:petid = e幽灵; break;
				}
				AddPCPetEnemy2(15000, petid, 87, (eMengPai)(rand() % 12));
			}
			SetMusic("OneLight");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(137);
			//AddTriggerFightEscape(-137);
		}
		return TRUE;
	//case -137:
	//	AddTriggerObj2(62, 63, 135);
	//	return TRUE;
	case 137:
		
		{
			SetJiangLi2(1200000, 200000, 200000, 1200000);
			
			RemoveTriggerObjMap();
			TalkList(35, 32, 2, 33, 138);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(90);
		}
		return TRUE;
	case 138:
		AddTriggerDialog2(36, 139);
		UpdateJob2(-1);
		return TRUE;
	case 139:
		g_pMainState->m_TaskFB.Start(3);
		g_pMainState->m_TaskFB.SetTask(this, 140);
		g_pMainState->m_TaskFB.Process(0);
		g_pMainState->m_TaskFB.Process(3);
		return TRUE;
	case 140:
		TalkList(37, 30, 2, 31, 30);
		return TRUE;
	case 30: TalkList(27, 28, 26, 29, 31);
		SetJiangLiItem(11,24);
		break;//至尊宝
	case 31:TalkList(28, 25, 26, 27, 32); break;//白晶晶
	case 32:TalkList(29, 1, 2, 3, 33); break;//春三十娘
	case 33:
		TalkList(30, -1, -1, -1, -1,34); 
		SetJiangLiItem(50,40);
	/*	SetChapter(5);
		AddTriggerLv(0, 105);*/
		break;//天蓬元帅
	case 34:
		Process5(0);
		break;
	default:
		break;
	}
	return TRUE;
}

void cTaskJuQing::TalkList(int textid, int nextname, int nextmap, int jobtext, int ret, int dialogret)
{
	AddTriggerDialog2(textid, dialogret);
	if (nextname > -1)
		AddTriggerObj2(nextname, nextmap, ret);
	UpdateJob2(jobtext);
}

BOOL cTaskZhuXian::Process5(int stage)
{
	int next = stage + 1;
	switch (stage)
	{
	case 0:
		g_pMainState->m_GlobalButton[6] = 8;
		g_pMainState->m_GlobalButton[5] = 7;
		SetChapter(5);
		AddTriggerObj2(8, 9, 1);
		UpdateJob2(10);
		break;
	case 1:
		AddTriggerDialog2(3, 3); //美猴王
		break;
	case 3:
		
		{
			AddPCPetEnemy2(15000, e雨师, 90, eMP_化生寺,26);
			AddPCPetEnemy2(20000, e沙和尚, 90, eMP_东海龙宫,28);
			AddPCPetEnemy2(20000, e猪八戒, 90, eMP_狮驼岭,27);
			ePetID petid;
			for (int i = 0; i < 3; i++)
			{
				switch (rand() % 3)
				{
				case 0:petid = e巨力神猿; break;
				case 1:petid = e长眉灵猴; break;
				default:petid = e超级金猴; break;
				}
				AddPCPetEnemy2(15000, petid, 80);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(11);
		}
		return TRUE;
	case 11:
		
		{
			SetJiangLi2(1250000, 250000, 250000, 1250000);
			
			AddTriggerDialog2(4, -11); //美猴王
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(95);
		}
		return TRUE;
	case -11:
		
		{
			AddPCPetEnemy2(50000, e孙悟空, 999, eMP_大唐官府);
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e巨力神猿; break;
				case 1:petid = e长眉灵猴; break;
				default:petid = e超级金猴; break;
				}
				AddPCPetEnemy2(25000, petid, 120);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-13);
			AddTriggerFightFalse(-13);
			AddTriggerFightEscape(-13);
		}
		return TRUE;
	case -13:
		
		{
			TalkList(5, 11, 12, 13, 12);
		}
		return TRUE;


	case 12:TalkList(6, 14, 15, 16, next); break;//观音姐姐
	case 13:TalkList(7, 8, 9, 10, next); break;//李靖
	case 14:TalkList(8, 8, 17, 10, next); break;//美猴王
	case 15:AddTriggerDialog2(9, next); break;//美猴王
	case 16:
		
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(40000, e孙悟空, 110, eMP_大唐官府);
			pPet->m_MagicFire.d2 += 20;
			ePetID petid;
			for (int i = 0; i < 2; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e巨力神猿; break;
				case 1:petid = e长眉灵猴; break;
				default:petid = e超级金猴; break;
				}
				AddPCPetEnemy2(25000, petid, 85, (eMengPai)(rand() % 12));
			}
			SetMusic("打不倒的空气人");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(17);
		}
		return TRUE;
	case 17:
		
		{
			SetJiangLi2(1300000, 250000, 250000, 1300000);
			
			TalkList(10, 14, 15, 16, next);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(98);
			AddChannel2(37);
			int xp, yp;
			for (int i = 0; i < 10; i++)
			{
				g_pMainState->m_Map.AutoGetPos(xp, yp, m_Textlist[36]);
				switch (rand() % 3)
				{
				case 0:
					AddTriggerObjMap2(35, 36, e鬼将,xp,yp,-1,-17);
					break;
				case 1:
					AddTriggerObjMap2(35, 36, e净瓶女娲, xp, yp, -1, -18);
					break;
				case 2:
					AddTriggerObjMap2(35, 36, e炎魔神, xp, yp, -1, -19);
					break;
				}	
			}
		}
		return TRUE;
	case -17:
		
		{
			m_pObj = g_pMainState->m_pNowSelect;
			int lv = g_pCharacter->m_PCData.m_LV;
			AddPCPetEnemy2(lv * 100, e鬼将, lv + 5, eMP_随机, 35);
			for (int i = 0; i < 7;i++)
			AddPCPetEnemy2(lv*80, (ePetID)(10+rand()%20),lv);
		
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-117);
		}
		return TRUE;
	case -18:
		
		{
			m_pObj = g_pMainState->m_pNowSelect;
			int lv = g_pCharacter->m_PCData.m_LV;
			AddPCPetEnemy2(lv * 100, e净瓶女娲, lv + 5, eMP_随机, 35);
			for (int i = 0; i < 7; i++)
				AddPCPetEnemy2(lv * 80, (ePetID)(10 + rand() % 20),lv);

			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-117);
		}
		return TRUE;//
	case -19://炎魔神
		
		{
			m_pObj = g_pMainState->m_pNowSelect;
			int lv = g_pCharacter->m_PCData.m_LV;
			cPetData* pPet;
			pPet= AddPCPetEnemy2(lv * 100, e炎魔神, lv + 5, eMP_魔王寨, 35);
			pPet->AddSkill(ePS_高级反震);
			for (int i = 0; i < 7; i++)
				AddPCPetEnemy2(lv * 80, (ePetID)(10 + rand() % 20),lv);

			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-117);
		}
		return TRUE;
	case -117:
		SetJiangLi2(100000, 50000, 50000, 100000);
		RemoveTriggerObjMap2(m_pObj);
		g_pMainState->m_Map.RemoveNpc(m_pObj, TRUE);
		return TRUE;
	case 18:TalkList(11, 18, 19, 20, next); break;//李靖
	case 19:TalkList(12, 11, 12, 13, next); break;//地藏王
	case 20:TalkList(13, 21, 22, 23, -20); break;//观音姐姐
	case -20:TalkList(14, 24, 22, 25, 21); break;//黑熊精
	case 21:AddTriggerDialog2(15, next); break;//小龙女
	case 22:
		
		{
			AddPCPetEnemy2(40000, e小龙女, 95, eMP_普陀山);
			ePetID petid;
			for (int i = 0; i < 7; i++)
			{
				switch (rand() % 2)
				{
				case 0:petid = e黑熊精; break;
				default:petid = e黑熊; break;
				}
				AddPCPetEnemy2(25000, petid, 90, (eMengPai)(rand() % 12));
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(23);
		}
		return TRUE;
	case 23:
		
		{
			
			SetJiangLi2(1320000, 250000, 250000, 1320000);
			
			TalkList(16, 8, 9, 10, next);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(99);
		}
		return TRUE;
	case 24:AddTriggerDialog2(17, next); break;//美猴王
	case 25:
		
		{
			AddPCPetEnemy2(30000, e六耳猕猴, 110, eMP_大唐官府);
			ePetID petid;
			for (int i = 0; i < 6; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e巨力神猿; break;
				case 1:petid = e长眉灵猴; break;
				default:petid = e超级金猴; break;
				}
				AddPCPetEnemy2(23000, petid, 100, (eMengPai)(rand() % 12));
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(26);
			
		}
		return TRUE;
	case 26:
		
		{
			RemoveTriggerObjMap();//妖王没了
			SetJiangLi2(1400000, 250000, 300000, 1400000);
			RemoveTriggerObj();
			TalkList(18,-1,-1,-1 ,-1,-26);
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			g_pCharacter->m_PCData.m_BangPaiID = 0;
			g_pCharacter->m_PCData.AddDefZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(105);
		}
		return TRUE;
	case -26:
		UnInvite("清风");
		AddFriend(32);
		g_pMainState->SetDialogListNpc(m_Textlist[31], 1081);
		TalkList(19, -1, -1, -1, -1, 28); break;//
		break;
	case 28:
		
		{
			g_pMainState->ClearDialogList();
			UnInvite("燕子");
			AddFriend(33);
			TalkList(20, -1, -1, -1, -1, -1);

			AutoGetPet(m_Textlist[33], 3);
			Invite(m_Textlist[33]);

			AutoGetPet(m_Textlist[32], 2);
			Invite(m_Textlist[32]);
			UnInvite("小蛮");
			AddFriend(34);
			AutoGetPet(m_Textlist[34], 4,5);
			Invite(m_Textlist[34]);

			g_pMainState->m_TaskFB.Start(0);
			g_pMainState->m_TaskFB.Process(0);
			g_pMainState->m_TaskFB.SetTask(this, 29);

		}
		break;
	case 29:
		g_pMainState->m_TaskFB.Start(1);
		g_pMainState->m_TaskFB.Process(0);
		g_pMainState->m_TaskFB.SetTask(this, 30);
		break;
	case 30:
		g_pMainState->m_TaskFB.Start(2);
		g_pMainState->m_TaskFB.Process(0);
		g_pMainState->m_TaskFB.SetTask(this, 31);
		break;
	case 31:
		Process6(0);
		break;
	}
	return TRUE;
}

BOOL cTaskZhuXian::Process6(int stage)
{
	int next = stage + 1;
	switch (stage)
	{
	case 0:
		g_pMainState->m_GlobalButton[5] = 8;
		SetChapter(6);
		g_pMainState->SetDialogListPet(m_Textlist[1],e猪八戒);
		TalkList(0, 2, 3, 4, next); break;//猪八戒
		break;
	case 1:
		g_pMainState->m_DialogList.clear();
		TalkList(1, 5, 26, 6, next); break;//云游僧
	case 2:TalkList(2, 9, 10, 11, next); break;//高老先生
	case 3:AddTriggerDialog2(3, next); break;//三大王
	case 4:
		
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(50000, e超级大鹏, 110, eMP_狮驼岭,9);
			pPet = AddPCPetEnemy2(50000, e超级麒麟, 110, eMP_狮驼岭, 28);
			pPet = AddPCPetEnemy2(50000, e超级大象, 110, eMP_狮驼岭, 29);
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 2)
				{
				case 0:petid = e雷鸟人; break;
				default:petid = e蝴蝶仙子; break;
				}
				AddPCPetEnemy2(25000, petid, 105);
			}
			g_pMainState->m_InterfaceTeam.SetFormation(sky, TRUE);
			SetMusic("Magia");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 5:
		
		{
			SetJiangLi2(1500000, 250000, 300000, 1500000);
			
			TalkList(4, 7, 3, 8, next);
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			g_pCharacter->m_PCData.AddHpZZ(500);
			g_pCharacter->m_PCData.AddSpdZZ(100);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(109);
		}
		return TRUE;
	case 6:TalkList(5, 12, 3, 13, next); break;//野猪王
	case 7:AddTriggerDialog2(6, next); break;//白衣人
	case 8:
		
		{
			sZiZhi zizhi;
			zizhi.Set(1400, 1200, 2000, 6000, 1200, 1200, 120);
			AddPCEnemy2(60000,1, &zizhi,106, eMP_方寸山,12);
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 2)
				{
				case 0:petid = e牛头; break;
					default:petid = e马面; break;
				}
				AddPCPetEnemy2(25000, petid, 100);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 9:
		{
			SetJiangLi2(1550000, 250000, 350000, 1550000);
			
			TalkList(7, 14, 15, 16, next);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(112);
		}
		return TRUE;
	case 10:TalkList(8, 12, 3, 13, next); break;//觉明
	case 11:TalkList(9, 2, 3, 4, next); break;//白衣人
	case 12:TalkList(10, 17, 3, 18, next); break;//云游僧
	case 13:AddTriggerDialog2(11, next); break;//少女
	case 14:
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(80000, e修罗傀儡妖, 110, eMP_盘丝岭,27);
			pPet->m_SuckBloodRate.d1 += 20;
			ePetID petid;
			for (int i = 0; i < 6; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e画魂; break;
				case 1:petid = e鬼将; break;
				case 2:petid = e吸血鬼; break;
				default:petid = e幽灵; break;
				}
				AddPCPetEnemy2(25000, petid, 100);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 15:
		{
			SetJiangLi2(1600000, 250000, 400000, 1600000);
			
			TalkList(12, 19, 20, 21, next);
			g_pCharacter->m_PCData.AddDefZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(118);
		}
		return TRUE;
	case 16:TalkList(13, 22, 3, 23, next); break;//李靖
	case 17:AddTriggerDialog2(14, next); break;//老太婆
	case 18:
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(90000, e孙婆婆, 118, eMP_盘丝岭,27);
			pPet->poisonRate.d1 += 50;
			pPet->m_SuckBloodRate.d1 += 20;
			ePetID petid;
			for (int i = 0; i < 7; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e画魂; break;
				case 1:petid = e鬼将; break;
				case 2:petid = e吸血鬼; break;
				default:petid = e幽灵; break;
				}
				AddPCPetEnemy2(25000, petid, 110);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 19:
		{
			SetJiangLi2(1700000, 250000, 400000, 1700000);
			
			TalkList(15, 19, 20, 21, next);
			g_pCharacter->m_PCData.AddDefZZ(100);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(125);
		}
		return TRUE;
	case 20:TalkList(16, 24, 3, 25, next); break;//李靖
	case 21:AddTriggerDialog2(17, next); break;//老太爷
	case 22:
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(100000, e白晶晶, 126, eMP_盘丝岭,27);
			pPet->m_SuckBloodRate.d1 += 20;
			pPet->m_AtkDownDef.d1 = 2;
			ePetID petid;
			for (int i = 0; i < 9; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e修罗傀儡妖; break;
				case 1:petid = e炎魔神; break;
				case 2:petid = e修罗傀儡鬼; break;
				default:petid = e蝎子精; break;
				}
				AddPCPetEnemy2(50000, petid, 120);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 23:
		{
			SetJiangLi2(1800000, 300000, 400000, 1800000);
			
			TalkList(18, 19, 20, 21, next);
			g_pCharacter->m_PCData.AddDefZZ(150);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(130);
		}
		return TRUE;
	case 24:TalkList(19, 5, 26, 6, next); break;//李靖
	case 25:	
		TalkList(20, -1, -1, -1,-1, next);
		break;
	case 26:
		Process7(0);
		break;//高老先生
	default:
		break;

	}
	return TRUE;
}

BOOL cTaskZhuXian::Process7(int stage)
{
	int next = stage + 1;
	switch (stage)
	{
	case -1:return TRUE;
	case 0:
		g_pMainState->m_GlobalButton[4] = 50;
		g_pMainState->m_GlobalButton[6] = 12;
		g_pMainState->m_GlobalButton[5] = 10;
		SetChapter(7);
		g_pMainState->SetDialogListPet(m_Textlist[1], e猪八戒);
		TalkList(0, 6, 3, 7, 3); break;
		break;
	case 3:
		g_pMainState->m_DialogList.clear();
		TalkList(3, 8, 3, 9, next); break;//火焰山土地
	case 4:TalkList(4, 10, 11, 12, next); break;//云里雾
	case 5:AddTriggerDialog2(5, 6); break;//铁扇公主
	case 6:
	{
		g_pMainState->m_Map.LoadMap(21, 46, m_Textlist[13].c_str(), 0);
		g_pHeroObj->Set(POS_DEAD,0);
		TalkList(6, 14, 15, 16, next); 
	
		
			AddTriggerObjMap2(35, 15, e观音姐姐, 14, 15, 3,7);
			AddTriggerObjMap2(33, 15, e空度禅师, 10, 14, 3,7);
			AddTriggerObjMap2(34, 15, e菩提祖师, 28, 8, 7,7);
		}
		break;//疥癞和尚
	case 7://镇元大仙
		if (CheckINT(12, 3))
		{
			g_pMainState->SetDialogListPC(m_Textlist[32], 9);
			AddTriggerDialog2(7, -7);
		}
		else
			AddTriggerDialog2(28, -7);
		break;
	case -7://超级泡泡
	
		{
			g_pMainState->ClearDialogList();
			cPetData* pPet;	
			pPet= AddPCPetEnemy2(50000, e镇元大仙, 129, eMP_五庄观);
			pPet->m_SealRate.d1 += 50;
			pPet=AddPCPetEnemy2(50000, e菩提祖师, 129, eMP_方寸山);
			pPet->m_SealRate.d1 += 50;
			pPet = AddPCPetEnemy2(50000, e空度禅师, 129, eMP_化生寺,33);
			pPet->m_DamageAddPercentCure.d1 += 50;
			pPet= AddPCPetEnemy2(50000, e观音姐姐, 129, eMP_普陀山);
			pPet->m_DamageAddPercentCure.d1 += 50;	
			if (CheckINT(12, 3))
			{
				AddPCEnemy2(50000, 9, 0, 120, eMP_五庄观, 32);
				
			}
			pPet = AddPetEnemy2(16000, e超级泡泡, 129);
			pPet->m_Combo.d1 += 50;
			pPet = AddPetEnemy2(16000, e超级人参娃娃, 129);
			pPet->m_Combo.d1 += 50;
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 3)
				{
				case 0:petid = e金身罗汉; break;
				case 1:petid = e灵符女娲; break;
				default:petid = e葫芦宝贝; break;
				}
				AddPCPetEnemy2(10000, petid, 60);
			}
			SetMusic("Lacrimosa");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-6);
		}
		return TRUE;
	case -6:
	
		{

			RemoveTriggerObjMap();
			g_pMainState->m_Map.RemoveAllNpc();
			SetJiangLi2(2000000, 500000, 500000, 2000000);
			
			TalkList(23,10,11,12,8);
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			g_pCharacter->m_PCData.GetShangPinPet(6);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pCharacter->m_PCData.AddHpZZ(800);
			g_pCharacter->m_PCData.AddAtkZZ(200);
			g_pCharacter->m_PCData.AddAvoidZZ(200);
			g_pMainState->LockLv(132);
		}
		return TRUE;
	
	case 8:AddTriggerDialog2(8, next); break;//铁扇公主
	case 9:
	
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(100000, e地涌夫人, 135, eMP_魔王寨, 10);
			pPet->m_DamagePercent.d2 += 10;
			ePetID petid;
			for (int i = 0; i < 7; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e红萼仙子; break;
				case 1:petid = e龙龟; break;
				case 2:petid = e修罗傀儡鬼; break;
				default:petid = e修罗傀儡妖; break;
				}
				AddPCPetEnemy2(50000, petid, 130);
			}
			SetMusic("镜影命缘");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 10:
		
		{
			SetJiangLi2(2100000, 500000, 500000, 2100000);
			
			TalkList(9, 6, 3, 7, next);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(135);
		}
		return TRUE;
	case 11:TalkList(10, 17, 18, 19, next); break;//土地公公
	case 12:AddTriggerDialog2(11, next); break;//铁扇公主
	case 13:
		
		{
			AddTriggerDialog2(29);
			AddPCPetEnemy2(100000, e超级神牛, 137, eMP_魔王寨, 10);
			AddPCEnemy2(60000, 2005, 0, 137, eMP_魔王寨,52);
			ePetID petid;
			for (int i = 0; i < 6; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e机关人; break;
				case 1:petid = e炎魔神; break;
				case 2:petid = e踏云兽; break;
				default:petid = e混沌兽; break;
				}
				AddPCPetEnemy2(50000, petid, 130);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 14:
	
		{

			SetJiangLi2(2200000, 9999999, 600000, 2200000);
			
			TalkList(12, 20, 21, 22, next);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(140);
		}
		return TRUE;
	case 15://觉岸
		
		{
			TalkList(13, 10, 11, 12, next);
			g_pCharacter->UseCard(133);
		}
		break;
	case 16:TalkList(14, 6, 3, 7, next); break;//铁扇公主
	case 17://火焰山土地
		
		{
			g_pCharacter->UseCard(-1);
			TalkList(15, 10, 11, 12, next); 
		}
		break;
	case 18:TalkList(16, 23, 3, 24, next); break;//铁扇公主
	case 19:TalkList(17, 25, 26, 27, next); break;//牛将军
	case 20:
		SetDialogList(25);
		TalkList(18, 17, 18, 19, next); break;//玉面公主
	case 21:AddTriggerDialog2(19, next); break;//牛魔王
	case 22:
		
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(100000, e牛魔王, 140, eMP_魔王寨);
			pPet->m_MagicFire.d2 += 30;
			pPet= AddPCPetEnemy2(80000, e狐狸精, 135, eMP_盘丝岭,25);
			pPet->AddSkill(ePS_法术连击);
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e炎魔神; break;
				case 1:petid = e踏云兽; break;
				case 2:petid = e葫芦宝贝; break;
				default:petid = e混沌兽; break;
				}
				AddPCPetEnemy2(50000, petid, 140);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 23:
		
		{	
			AddTriggerDialog2(20, next);
		}
		break;
	case 24:
		
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(150000, e超级灵狐, 150, eMP_盘丝岭, 25);
			pPet->AddSkill(ePS_高级法术连击);
			pPet=AddPCPetEnemy2(150000, e超级灵鹿, 150, eMP_大唐官府);
			pPet->AddSkill(ePS_高级鬼魂术);
			ePetID petid;
			for (int i = 0; i < 6; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e猫灵; break;
				case 1:petid = e狂豹; break;
				case 2:petid = e猫灵人; break;
				default:petid = e狂豹人; break;
				}
				AddPCPetEnemy2(80000, petid, 145);
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 25:
		
		{
			SetJiangLi2(2500000, 600000, 800000, 2500000);
			
			TalkList(21, 10, 11, 12, next);
			g_pMainState->ClearDialogList();
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			g_pCharacter->m_PCData.AddMagZZ(150);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pCharacter->m_PCData.AddHpZZ(500);
			g_pMainState->LockLv(155);
		}
		return TRUE;
	case 26:
		g_pMainState->SetDialogListPet(m_Textlist[1], e猪八戒);
		TalkList(22, -1, -1, -1, -1,-26); break;//铁扇公主
	case -26:
		g_pMainState->m_DialogList.clear();
		//Process9(0);
		g_pMainState->m_TaskHuoDong.Start(门派闯关);
		g_pMainState->m_TaskHuoDong.SetTrigger(this, 27, 1/*24*/);
		return TRUE;
	case 27:
		TalkList(24, 36, 37, 38, 28, -27);
		return TRUE;
	case -27:
	
		{
			int id;
			UnInvite(m_Textlist[39]);
			UnInvite(m_Textlist[40]);
			id = g_pMainState->m_Friend.FindFriend("燕子");
			g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "燕子3";
			id = g_pMainState->m_Friend.FindFriend("傻妞");
			g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "傻妞2";
			Invite(m_Textlist[41]);
			Invite(m_Textlist[42]);
		}
		return TRUE;
	case 28:
		
		{
			cPetData* pPet;
			pPet = AddPCPetEnemy2(200000, e蚩尤, 155, eMP_狮驼岭);
			pPet->restoreRate += 30;
			ePetID petid;
			for (int i = 0; i < 7; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e修罗傀儡鬼; break;
				case 1:petid = e持国巡守; break;
				case 2:petid = e毗舍童子; break;
				default:petid = e真陀护法; break;
				}
				AddPCPetEnemy2(100000, petid,150);
			}
			SetMusic("战斗比武2");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 29:
	
		{
			SetJiangLi2(2800000, 800000, 1000000, 2800000);
			
			TalkList(25, -1, -1, -1, -1,30);
			g_pCharacter->m_PCData.AddGrowing(5);
			g_pCharacter->m_PCData.AddAtkZZ(200);
			g_pCharacter->m_PCData.AddDefZZ(100);
			g_pCharacter->m_PCData.AddMagZZ(200);
			g_pCharacter->m_PCData.AddHpZZ(1000);
			g_pCharacter->m_PCData.AddSpdZZ(100);
			g_pCharacter->m_PCData.AddAvoidZZ(100);

			g_pMainState->LockLv(160);
		}
		return TRUE;
	case 30:
		
		{
			UnInvite(m_Textlist[41]);
			UnInvite(m_Textlist[42]);
			UnInvite(m_Textlist[43]);
			UnInvite(m_Textlist[44]);
			AddTriggerObjMap2(46, 45, 2000, 17, 13, 3);
			AddTriggerObjMap2(39, 45, 2010, 24, 12, 9);
			AddTriggerObjMap2(47, 45, 2001, 30, 10, 8);
			g_pMainState->m_Map.LoadMap(29, 12, m_Textlist[45].c_str(), 0);
			g_pHeroObj->Set(POS_DEAD, 0);
			TalkList(26,-1,-1,51,-1,31);
		}
		return TRUE;
	case 31:
	
		{
			g_pMainState->m_Map.RemoveAllNpc();
			RemoveTriggerObjMap();
			Invite(m_Textlist[46]);
			Invite(m_Textlist[47]);
			g_pMainState->FindObj();
			AddTriggerObjMap2(49, 50, 2013, 84, 37, 7,32);
			AddTriggerObjMap2(48, 50, 2008, 79, 41, 3,32);
		}
		return TRUE;
	case 32:
		
		{
			TalkList(27, -1, -1, -1, -1, 33);
			RemoveNpc(48);
			RemoveNpc(49, TRUE);
			int id = g_pMainState->m_Friend.FindFriend("清风");
			g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "清风2";
			Invite(m_Textlist[48]);
			Invite(m_Textlist[49]);
			g_pMainState->FindObj();
		}
		return TRUE;
	case 33:
		Process9(0);
		return TRUE;
	}
	return TRUE;
}

void cTaskJuQing::SetDialogList(int id)
{
	g_pMainState->SetDialogList(g_pMainState->FindObjByName(m_Textlist[id]));
}

BOOL cTaskZhuXian::Process8(int stage)
{
	int next = stage + 1;
	switch (stage)
	{
	case 0:
	
		{
			SetChapter(8);
			g_pMainState->m_GlobalButton[5] = 3;
			g_pMainState->SetDialogListPet(m_Textlist[1],e沙和尚);
			TalkList(0, 2, 3, 4, next); break;
		}
		break;
	case 1:
		g_pMainState->m_DialogList.clear();
		TalkList(2, 8, 9, 10, 3); break;//西门将军
	case 3:TalkList(3, 11, 9, 12, next); break;//姜国师
	case 4:AddTriggerDialog2(4, next); break;//美美
	case 5:
		
		{
			cPetData* pPet;
			pPet= AddPCPetEnemy2(15000, e蚌精, 65, eMP_东海龙宫,11);
			pPet->m_MagicWater.d2 += 20;
			for (int i = 0; i < 4; i++)
			{
				pPet= AddPCPetEnemy2(10000, e蚌精, 65);
				pPet->m_MagicWater.d2 += 20;
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 6:
		
		{
			SetJiangLi2(600000, 100000, 50000, 600000);
			
			sNpc npc;
			npc.Reset();
			npc.Set(m_Textlist[13], m_Textlist[14], 82, 41, 73,3);
			AddTriggerObjMap(&npc, -1);
			npc.Set(m_Textlist[16], m_Textlist[14], 1074, 32, 75,3);
			AddTriggerObjMap(&npc,-1,FALSE);
			TalkList(5, 13, 14, 15, next);
			AddTriggerObj2(8, 9, 106, FALSE);
			g_pCharacter->m_PCData.AddDefZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(64);
		}
		return TRUE;
	case 106:
		AddTriggerDialog2(16);
		return TRUE;
	case 7:AddTriggerDialog2(6, next); break;//蝎子精
	case 8:
	
		{
			UnInvite(m_Textlist[27]);
			cPetData* pPet;
			pPet= AddPCPetEnemy2(20000, e蝎子精, 66, eMP_女儿村);
			pPet->poisonRate.d1 += 20;
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand()%4)
				{
				case 0:petid = e犀牛将军; break;
				case 1:petid = e犀牛将军人; break;
				case 2:petid = e百足将军; break;
				default:petid = e野猪精; break;
				}
				AddPCPetEnemy2(10000, petid, 58, (eMengPai)(rand() % 12));
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 9:
		
		{
			RemoveNpc(13,TRUE);
			RemoveTriggerObjMap(7);
			SetJiangLi2(650000, 100000, 50000, 650000);
			
			sNpc npc;
			npc.Set(m_Textlist[13], m_Textlist[14], 82, 50, 50,0);
			TalkList(7, 16, 14, 17, next,109);
			g_pCharacter->m_PCData.AddHpZZ(300);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(65);
		}
		return TRUE;
	case 109:
		UnInvite(m_Textlist[28]);
		UnInvite(m_Textlist[29]);
		break;
	case 10:TalkList(8, 18, 6, 19, next); break;//玄奘
	case 11:	
		g_pMainState->SetDialogListNpc(m_Textlist[16],1074);
		TalkList(9, 20, 21, 22, next); 
		RemoveTriggerObjMap();
		break;//西梁女国国王
	case 12:
		g_pMainState->ClearDialogList();
		TalkList(10, 23, 24, 25, next); break;//月老
	case 13:
		Invite(m_Textlist[28]);
		Invite(m_Textlist[29]);
		Invite(m_Textlist[27]);
		TalkList(11, 20, 21, 22, next); 
		break;//青莲仙女
	case 14:AddTriggerDialog2(12, next); break;//玄藏幻影
	case 15:
		
		{
			AddTriggerDialog2(17);
			cPetData* pPet;
			 pPet= AddPCEnemy2(20000, 1, 0, 70, eMP_化生寺,26,0,6);
			 pPet->m_CureCriRate.d1 += 20;
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e蚌精; break;
				case 1:petid = e鲛人; break;
				case 2:petid = e碧水夜叉; break;
				default:petid = e蛟龙; break;
				}
				AddPCPetEnemy2(12000, petid, 68, (eMengPai)(rand() % 12));
			}
			SetMusic("白色相簿深爱");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 16:
		{
			SetJiangLi2(700000, 100000, 50000, 700000);
		
			TalkList(13, 18, 6, 19, next);
			g_pCharacter->m_PCData.AddSpdZZ(50);
			g_pCharacter->m_PCData.AddGrowing(1);
			g_pMainState->LockLv(66);
		}
		return TRUE;
	case 17:TalkList(14, 20, 21, 22, next); break;//西梁女国国王
	case 18:
		TalkList(15, -1, -1, -1, -1,19); 
		break;//月老
	case 19:
		g_pCharacter->m_PCData.AddGrowing(5);
		SetJiangLiItem(16, 24);
		return Process3(0);

	}
	return TRUE;
}

BOOL cTaskZhuXian::Process9(int stage)
{
	int next = stage + 1;
	switch (stage)
	{
	case 0:
		g_pMainState->m_GlobalButton[4] = 180;
		g_pMainState->m_GlobalButton[6] = 30;
		SetChapter(9);
		g_pMainState->m_GlobalButton[5] = 16;
		AddTriggerObj2(6,7,1);
		UpdateJob2(8);
		return TRUE;
	case 1:
		TalkList(4,-1,-1,-1,5,-1);
		SetJiangLi2(10000000, 1000000, 5000000);
		SetJiangLiItem(23,28);
		AddTriggerObjMap2(1, 4, e巫奎虎, 143, 83, 3, 2);
		AddTriggerObjMap2(3, 4, 2014, 149, 83, 2, 2);
		AddTriggerObjMap2(2, 4, 2012, 146, 87, 2, 2);
		UpdateJob2(5);
		return TRUE;
	case 2:
		AddTriggerDialog2(0, next);
		break;
	case 3://
		{
			cPetData* pPet;
			pPet = AddPCPetEnemy2(160000, e巫奎虎, 160, eMP_大唐官府);
			pPet->poisonRate.d1 = 100;
			pPet->poisonRate.d2 = 100;
			pPet->m_DamageAddPercentPoision.d1= 200;
			pPet->m_DamageAddPercentPoision.d2 = 200;
			AddFriend(3);
			Invite(m_Textlist[3], 11);
			pPet= AddPetEnemy2(120000, e超级白泽, 160);
			pPet->SetJinJie(3);
			pPet=AddPetEnemy2(120000, e超级赤焰兽, 160);
			pPet->SetJinJie(3);
			pPet = AddPetEnemy2(120000, e超级青鸾, 160);
			pPet->SetJinJie(3);
			ePetID petid;
			for (int i = 0; i < 3; i++)
			{
				switch (rand() % 4)
				{
				case 0:petid = e曼珠沙华; break;
				case 1:petid = e星灵仙子; break;
				case 2:petid = e如意仙子; break;
				default:petid = e巡游天神; break;
				}
				pPet=AddPCPetEnemy2(80000, petid, 155);
				pPet->SetJinJie(3);
			}
		
			SetMusic("满天");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(next);
		}
		return TRUE;
	case 4:
		
		{
			SetJiangLi2(3000000, 1000000, 1000000, 3000000);
		
			TalkList(1,-1,-1,-1,-1,5);
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
			g_pCharacter->m_PCData.AddSpdZZ(100);
			g_pCharacter->m_PCData.AddGrowing(2);
			if (CheckINT(11, 1))
			{
				g_pCharacter->m_PCData.GoldLivePercent.d1 += 100;
			}
			else
			{
				LockMap(32);
				LockMap(33);
				AddChannel2(27);
			}
			g_pMainState->LockLv(175);
		}
		return TRUE;
	case 5:
		UnInvite(m_Textlist[12]);
		UnInvite(m_Textlist[13]);
		Invite(m_Textlist[2]);
		Invite(m_Textlist[3]);
		RemoveTriggerObjMap();
		RemoveNpc(1);
		RemoveNpc(3);
		RemoveNpc(2,TRUE);
		g_pMainState->m_TaskFB.Start(4);
		g_pMainState->m_TaskFB.Process(0);
		g_pMainState->m_TaskFB.SetTask(this, 6);
		return TRUE;
	case 6:
		g_pMainState->SetDialogListPet(m_Textlist[14], e李靖);
		TalkList(2, -1, -1, 9,-1, -6);
	
		AddTriggerObjMap2(10, 11, e蚩尤, 151, 60, 3, 7,4);

		AddTriggerObjMap2(15, 11, e知了王, 153, 51, 3, 11, 3);
		AddTriggerObjMap2(15, 11, e狂豹人, 167, 59, 3, 12, 3);

		AddTriggerObjMap2(16, 11, e猫灵人, 176, 51, 3, 13, 3);
		AddTriggerObjMap2(16, 11, e鬼将, 162, 45, 3, 14, 3);

		/*AddTriggerObjMap2(17, 11, e修罗傀儡鬼, 175, 39, 3, 15, 3);
		AddTriggerObjMap2(17, 11, e修罗傀儡妖, 190, 45, 3, 16, 3);*/
		UpdateJob2(9);
		if (CheckINT(11, 1))
		{
			AddTriggerObjMap2(28,11,2007,160,54,1,7);	
			UpdateJob2(31);
		}
		return TRUE;
	case -6:
		if (CheckINT(11, 1))
		{
			TalkList(8, 29, 30, 9, -7);
			UpdateJob2(9);
		}
		return TRUE;
	case -7:
		for (int i = 0; i < 5; i++)
		{
			cPetData* pPet;
			g_pMainState->m_FightList[i].m_pData->GetDateP(pPet);
			pPet->AddSkill(ePS_龙神守护);
		}
		AddTriggerDialog2(9);
		RemoveTriggerObj();
		return TRUE;
	case 7:
		g_pMainState->ClearDialogList();
		AddTriggerDialog2(3, -8);
		break;
	case -8:
		if (CheckINT(11, 1))
		AddTriggerDialog2(6, 8);
		else Process9(8);
		break;
	case 8://最终BOSS
		{
			cPetData* pPet;

			if (CheckINT(11, 1))
			{
				sZiZhi zizhi;
				zizhi.Set(2000, 2000, 5000, 90000, 2000, 2000, 170);
				pPet= AddPCEnemy2(900000,2007,&zizhi,200,eMP_魔王寨,28,9,28);
				pPet->AddSkill(ePS_高级法术连击);
				pPet->AddSkill(ePS_高级法术暴击);
				pPet->AddSkill(ePS_高级法术波动);
				pPet->AddSkill(ePS_高级魔之心);
				pPet->AddSkill(ePS_高级精神集中);
				pPet->AddSkill(ePS_高级神佑复生);
				pPet->AddSkill(ePS_高级再生);
				pPet->AddSkill(ePS_高级防御);
				pPet->AddSkill(ePS_高级幸运);
				pPet->AddSkill(ePS_高级敏捷);
				pPet->GoldLivePercent.d1 += 990000;
				pPet->m_LiveHpLv += 10000;
			}
			pPet=AddPCPetEnemy2(180000, e蚩尤, 200, eMP_狮驼岭);
			pPet->restoreRate += 30;
			pPet->m_JinJieNum.m_PositionID = 3;
			pPet = AddPCPetEnemy2(150000, e蝎子精, 180, eMP_女儿村, 19);
			pPet->abnormalResist += 10;
			pPet->poisonRate.d1 += 50;
			pPet->m_DamageAddPercentPoision.d1 +=50;
			pPet->poisonRate.d2 += 50;
			pPet->m_JinJieNum.m_PositionID = 3;
			pPet = AddPCPetEnemy2(170000, e净瓶女娲, 175, eMP_普陀山,18);
			pPet->abnormalResist += 10;
			pPet->m_JinJieNum.m_PositionID = 3;
			pPet = AddPCPetEnemy2(160000, e吸血鬼, 175, eMP_阴曹地府, 21);
			pPet->m_SuckBloodRate.d1 += 20;
			pPet->m_SuckBloodRate.d2 += 50;
			pPet->abnormalResist += 10;
			pPet->m_JinJieNum.m_PositionID = 3;
			pPet = AddPCPetEnemy2(120000, e巨力神猿, 175, eMP_大唐官府, 20);
			pPet->abnormalResist += 10;
			pPet->m_AtkDownHPHurt.d1 += 10;
			pPet->m_JinJieNum.m_PositionID = 3;
			pPet = AddPCPetEnemy2(120000, e蛟龙, 175, eMP_天宫, 22);  
			pPet->m_DamagePercent.d2 += 20;
			pPet->abnormalResist += 10;
			pPet->m_JinJieNum.m_PositionID = 3;
			pPet = AddPCPetEnemy2(120000, e蚌精, 175, eMP_东海龙宫, 24);
			pPet->m_MagicWater.d2 += 30;
			pPet->m_MagicWater.d1 += 10;
			pPet->abnormalResist += 10;
			pPet->m_JinJieNum.m_PositionID = 3;
			pPet->m_Controler.Set(0);
			pPet = AddPCPetEnemy2(100000, e雨师, 175, eMP_化生寺, 23);
			pPet->m_MagicWater.d2 += 30;
			pPet->abnormalResist += 10;
			pPet->m_JinJieNum.m_PositionID = 3;
		
			pPet = AddPCPetEnemy2(100000, e雾中仙, 175, eMP_五庄观, 26);
			pPet->GoldLivePercent.d1 += 10;
			pPet->abnormalResist += 10;
			pPet->m_JinJieNum.m_PositionID = 3;
	
			if (CheckINT(11, 1))
			{
				AddTriggerFightTurn(-9);
				AddTriggerFightSuccess(9);
			}
			else
			{
				pPet = AddPCPetEnemy2(150000, e黑山老妖, 170, eMP_魔王寨, 25);
				pPet->abnormalResist += 10;
				pPet->m_LiveHpLv += 10;
				pPet->SetJinJie(3);
				pPet->m_Controler.Set(0);
				AddTriggerFightSuccess(next);
			}
			g_pMainState->m_InterfaceTeam.SetFormation(sky, TRUE);
			SetMusic("华夏萌战录");
			g_StateType = STATE_FIGHT;
		
		}
		return TRUE;
	case -9:
		{//只剩一个敌人,战斗结束
			int num = g_pMainState->GetLiveNum(10, 20);
			//cAttackAI& ai = g_pMainState->m_AI.m_AttackAI;
			if (num<2)
			{
				g_pMainState->m_pFightState->SuccessFight();
			}
		}
		return TRUE;
	case 9:
		g_pMainState->LockLv(180);
		if (CheckINT(11, 1))
		{
			TalkList(7, -1, -1, -1, -1, 10);
		}
		else
		TalkList(5, -1, -1, -1, -1, 10);
		return TRUE;
	case 10:
		return TRUE;
		g_StateType = STATE_EXT;
		return TRUE;
	case 11://知了王
		{
			cPetData* pPet;
			pPet = AddPCPetEnemy2(16000, e知了王, 180, eMP_天宫,15);
			pPet->m_CounterRate.d1 += 50;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e灵符女娲, 170, eMP_魔王寨);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e净瓶女娲, 170, eMP_普陀山);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e芙蓉仙子, 165);
			pPet->m_LiveHpLv += 10;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e星灵仙子, 165);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e律法女娲, 165);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e红萼仙子, 165);
			pPet->m_Combo.d1 += 40;
			pPet->comboNumUp += 5;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e蚌精, 165, eMP_东海龙宫);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e曼珠沙华, 165);
			pPet->m_LiveHpLv += 30;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e藤蔓妖花, 165);
			pPet->SetJinJie(3);
			g_pMainState->m_InterfaceTeam.SetFormation(bird, TRUE);
			SetMusic("仙剑4战斗BGM");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-11);
		}
		return TRUE;
	case -11:
		{
			SetJiangLi2(4000000, 1000000, 1000000, 3000000);
			
			g_pMainState->m_Map.RemoveNpc(153 * 20, g_pMainState->m_Map.m_pMap->m_Height - 51 * 20,  m_Textlist[15], TRUE);
			RemoveTriggerObjMap(11);
			g_pCharacter->m_PCData.AddGrowing(1);
		}
		return TRUE;
	case 12://狂豹人
		{
			cPetData* pPet;
			pPet = AddPCPetEnemy2(16000, e狂豹人, 175, eMP_大唐官府);
			pPet->m_CriRate.d1 += 30;
			pPet->m_CriAddPercent.d1 += 30;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e犀牛将军人, 170);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e狂豹, 170);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e犀牛将军, 165);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e毗舍童子, 165);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e混沌兽, 165);
			pPet->m_DamagePercent.d2 += 10;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e吸血鬼, 165);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e巡游天神, 166);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e真陀护法, 165);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e持国巡守, 166);
			pPet->SetJinJie(3);
			SetMusic("UnfathomedForce");
			g_pMainState->m_InterfaceTeam.SetFormation(eagle, TRUE);
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-12);
			
		}
		return TRUE;
	case -12:
		{
			SetJiangLi2(4000000, 1500000, 1500000, 3000000);
			
			g_pMainState->m_Map.RemoveNpc(167 * 20, g_pMainState->m_Map.m_pMap->m_Height - 59 * 20, m_Textlist[15], TRUE);
			RemoveTriggerObjMap(12);
			g_pCharacter->m_PCData.AddGrowing(1);
		}
		return TRUE;
	case 13://e猫灵人
		{
			cPetData* pPet;
			pPet = AddPCPetEnemy2(16000, e猫灵人, 170, eMP_大唐官府);
			pPet->m_SPD.AddDataAddPercent(30);
			pPet->m_AtkDownDef.d1 = 1;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e猫灵, 165);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e蝎子精, 160);
			pPet->poisonRate.d1 += 20;
			pPet->poisonRate.d2 += 20;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e鲛人, 160);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e雾中仙, 160);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e千年蛇魅, 160);
			pPet->poisonRate.d1 += 20;
			pPet->poisonRate.d2 += 20;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e腾蛇, 160);
			pPet->poisonRate.d1 += 20;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e噬天虎, 160);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e千年蛇魅, 160);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e鲛人, 160);
			pPet->SetJinJie(3);
			SetMusic();
			g_pMainState->m_InterfaceTeam.SetFormation(dragon, TRUE);
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-13);
		}
		return TRUE;
	case -13:
		{
			SetJiangLi2(3000000, 1500000, 1500000, 3000000);
		
			g_pMainState->m_Map.RemoveNpc(176 * 20, g_pMainState->m_Map.m_pMap->m_Height - 51 * 20, m_Textlist[16], TRUE);
			RemoveTriggerObjMap(13);
			g_pCharacter->m_PCData.AddGrowing(1);
		}
		return TRUE;
	case 14://e鬼将
		{
			cPetData* pPet;
			pPet = AddPCPetEnemy2(16000, e鬼将, 165, eMP_大唐官府);
			pPet->m_CriRate.d1 += 20;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e天将, 160);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e天兵, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e机关人, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e机关兽, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e机关鸟, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e巴蛇, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e踏云兽, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e龙龟, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e连弩车, 155);
			pPet->SetJinJie(3);
			SetMusic("stonecoldFictionJunction");
			g_StateType = STATE_FIGHT;
			g_pMainState->m_InterfaceTeam.SetFormation(wind, TRUE);
			AddTriggerFightSuccess(-14);
		}
		return TRUE;
	case -14:
		{
			SetJiangLi2(3000000, 1000000, 1000000, 3000000);
			
			g_pMainState->m_Map.RemoveNpc(162*20,g_pMainState->m_Map.m_pMap->m_Height- 45*20, m_Textlist[16], TRUE);
			RemoveTriggerObjMap(14);
			g_pCharacter->m_PCData.AddGrowing(1);
		}
		return TRUE;
	case 15://e修罗傀儡鬼
		{
			cPetData* pPet;
			pPet = AddPCPetEnemy2(16000, e修罗傀儡鬼, 160, eMP_大唐官府);
			pPet->m_SuckBloodRate.d1 += 20;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e古代瑞兽, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e蝴蝶仙子, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e凤凰, 155);
			pPet->m_MagicFire.d2 += 50;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e蛟龙, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e风伯, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e雨师, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e雷鸟人, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e百足将军, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e大力金刚, 155);
			pPet->m_DamagePercent.d2 += 20;
			pPet->SetJinJie(3);
			SetMusic("未来宇宙");
			g_pMainState->m_InterfaceTeam.SetFormation(land, TRUE);
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-15);
		}
		return TRUE;
	case -15:
		{
			SetJiangLi2(2500000, 1000000, 1000000, 2500000);
			
			g_pMainState->m_Map.RemoveNpc(175 * 20, g_pMainState->m_Map.m_pMap->m_Height - 39 * 20, m_Textlist[17], TRUE);
			RemoveTriggerObjMap(15);
			g_pCharacter->m_PCData.AddGrowing(1);
		}
		return TRUE;
	case 16://e修罗傀儡妖
	
		{
			cPetData* pPet;
			pPet = AddPCPetEnemy2(16000, e修罗傀儡妖, 160, eMP_大唐官府);
			pPet->m_LiveHpLv += 10;
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e蜃气妖, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e烟花占卜师, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e小仙女, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e善财童子, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e小毛头, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e小魔头, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e小精灵, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e小仙灵, 155);
			pPet->SetJinJie(3);
			pPet = AddPCPetEnemy2(16000, e小丫丫, 155);
			pPet->SetJinJie(3);
			SetMusic();
			g_pMainState->m_InterfaceTeam.SetFormation(tiger, TRUE);
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(-16);
		}
		return TRUE;
	case -16:
	
		{
			SetJiangLi2(2500000, 1000000, 1000000, 2500000);
			
			g_pMainState->m_Map.RemoveNpc(190 * 20, g_pMainState->m_Map.m_pMap->m_Height - 45 * 20, m_Textlist[17], TRUE);
			RemoveTriggerObjMap(16);
			g_pCharacter->m_PCData.AddGrowing(1);
		}
		return TRUE;
	case 100:
	{
		vector<ePetID> pets = { e蚩尤, e持国巡守, e毗舍童子, e蜃气妖, e真陀护法, e小毛头, e小魔头, e小精灵, e小丫丫, e小仙灵 };
		vector<eMengPai> es = { eMP_狮驼岭, eMP_普陀山, eMP_阴曹地府, eMP_化生寺, eMP_方寸山,
			eMP_大唐官府, eMP_东海龙宫, eMP_大唐官府, eMP_魔王寨, eMP_大唐官府 };
		ePetID pid;
		for (int i = 0; i < 10; ++i)
		{
			{
				pid = pets[i];
			}
			cPCData* pPet = (cPCData*)AddPCPetEnemy2((i ? 27000 : 47000), pid, 129, es[i]);
			pPet->m_JinJieNum.m_PositionID = 3;
			for (int k = 0; k < 7; ++k)
			{
				pPet->m_MengPaiSkillLV[k] = 250;
			}

			pPet->m_Controler.Set(0);
#if ccc_date
			pPet->FollowXiulian();
			pPet->m_MPMax.AddDataAddPercent(200);
			pPet->FollowEuip(true);
#endif

			pPet->m_LiveCp += 5 + rand() % 5;
			pPet->m_LiveHpLv += 600;
			if (i == 0)
			{
				pPet->m_CriRate.d1 += 20;
				pPet->m_StabRate.d1 += 20;
				pPet->m_SuckBloodRate.d1 += 20;
				pPet->m_CounterRate.d1 += 20;
			}
			else
			{
				pPet->restoreRate += 30;
				pPet->m_SealRate.d1 += 50;
			}
		}
		g_pMainState->m_InterfaceTeam.SetFormation(sky, TRUE);
		SetMusic();
		g_StateType = STATE_FIGHT;
	}
	break;
	}
	return TRUE;
}


void cTaskJuQing::Select(int title, int name, int cancelret, int select0, int ret0, int select1, int ret1, int select2, int ret2, int select3, int ret3)
{
	if (select3 > -1)
	{
		g_pMainState->m_TriggerDialog.AddSelect(this, m_Textlist[title], m_Textlist[name], cancelret,
			m_Textlist[select0], ret0,
			m_Textlist[select1], ret1,
			m_Textlist[select2], ret2,
			m_Textlist[select3], ret3
			);
	}
	else
	if (select2 > -1)
	{
		g_pMainState->m_TriggerDialog.AddSelect(this, m_Textlist[title], m_Textlist[name], cancelret,
			m_Textlist[select0], ret0,
			m_Textlist[select1], ret1,
			m_Textlist[select2], ret2
			);
	}
	else
	{
		g_pMainState->m_TriggerDialog.AddSelect(this, m_Textlist[title], m_Textlist[name], cancelret,
			m_Textlist[select0], ret0,
			m_Textlist[select1], ret1
			);
	}
	g_pMainState->m_Dialog.m_bRetSelect = TRUE;
}

cPetData* cTaskJuQing::GetPetData(int id)
{
	cPetData* p;
	g_pMainState->m_FightList[id].m_pData->GetDateP(p);
	return p;
}

int cTaskJuQing::GetCharacterID(string name)
{
	for (int i = 0; i < 5; i++)
	{
		if (g_pMainState->m_FightList[i].m_pData->m_TrueName.GetString() == name)
		{
			return i;
		}
	}
	return -1;
}

void cTaskJuQing::Invite(string datafielname,int fighterid)
{
	g_pMainState->m_Friend.Invite(datafielname,fighterid);
}

int cTaskJuQing::AddPetEnemy(ePetID id, int lv, int name/*=""*/, BOOL bOur, int pos)
{
	string namet;
	if (name == -1)namet = "";
	else namet = m_Textlist[name];
	return g_pMainState->AddPetEnemy(namet, id, lv, &m_AddPoint, -1, pos, bOur);
}

int cTaskJuQing::AddPCPetEnemy(ePetID id, int lv, eMengPai mp, int name /*= ""*/, BOOL bOur, int pos)
{
	string namet;
	if (name == -1)namet = "";
	else namet = m_Textlist[name];
	return g_pMainState->AddPCPetEnemy(id, lv, &m_AddPoint, mp, namet,-1, bOur,pos);
}

int cTaskJuQing::AddPCEnemy(int id, sZiZhi* zz, int lv, eMengPai mp, int name /*= ""*/, int weapontype, int weaponid, BOOL bOur, int pos)
{
	string namet;
	if (name == -1)namet = "";
	else namet = m_Textlist[name];
	if (weaponid == -1)
	{
		return g_pMainState->AddPCEnemy(namet, id, lv, &m_AddPoint, zz, mp, 0, -1, -1,  pos, bOur);
	}
	else
	{
		sItem2 item;
		item.Set(weapontype, weaponid);
		return g_pMainState->AddPCEnemy(namet, id, lv, &m_AddPoint, zz, mp, &item, -1, -1, pos, bOur);
	}
}



void cTaskJuQing::Init()
{
	if (m_Chapter == -1)return;
	if (m_bInit)return;
	m_bInit = TRUE;
	ifstream File;
	string data;
	File.open(SetUpPathJuQing("index"));
	if (!File)
		ERRBOX;
	for (int i = 0; i <= m_Chapter; i++)
	{
		getline(File, data);
	}
	File.close();
	//}
	File.open(SetUpPathJuQing(data));
	if (!File)
		ERRBOX;
	int num;
	File >> num;
	getline(File, data);
	m_Textlist.resize(num);
	for (int i = 0; i < num; i++)
	{
		getline(File, data); 
		m_Textlist[i]=data;
	}
	File.close();
	m_AddPoint.Set(4, 0, 0, 1, 0);
}



BOOL cTaskZhiXian::Process(int stage)
{
	
	switch (m_Chapter)
	{
	case 0:return Process0(stage);
	case 2:return Process2(stage);
	case 3:return Process3(stage);
	case 4:return Process4(stage);
	case 6:return Process6(stage);
	default:return Process1(stage);
	}
}

BOOL cTaskZhiXian::Process0(int stage)
{
//	int lv = g_pCharacter->m_PCData.m_LV;
	switch (stage)
	{
	case -1:return TRUE;
	case 0://无名野鬼
	
		{
			int& num = g_pMainState->m_GlobalButton[11];
			if (num & 0x01)return TRUE;
			AddTriggerDialog2(0, 1);
		}
		break;
	case 1:Select(2, 1, -1, 3, 2, 4, -1);break;
	case 2:
		
		{
			sItem2* pItem= FindItem(28, 23);
			if (pItem)
			{
				pItem->m_Num = 0;
				SetINT(11, 0);
				sShangPinPet pet;
				sAddPoint point;
				point.Set(0, 0, 4, 1, 0);
				pet.Set(e雾中仙, &point);
				pet.m_zizhi.m_MAGZZ = 5000;
				pet.m_zizhi.m_SPDZZ = 1700;
				pet.m_zizhi.m_HPZZ = 10000;
				pet.m_zizhi.m_Growing = 170;
				pet.AddSkill(ePS_奔雷咒);
				pet.AddSkill(ePS_雷击);
				pet.AddSkill(ePS_高级魔之心);
				pet.AddSkill(ePS_高级法术连击);
				pet.AddSkill(ePS_高级法术暴击);
				pet.AddSkill(ePS_高级再生);
				pet.AddSkill(ePS_高级精神集中);
				pet.AddSkill(ePS_高级神佑复生);
				pet.AddSkill(ePS_高级防御);
				pet.AddSkill(ePS_龙神守护);
				pet.AddSkill(ePS_高级敏捷);
				pet.AddSkill(ePS_高级招架);
				pet.AddSkill(ePS_高级飞行);
				pet.AddSkill(ePS_高级隐身);
				pet.AddSkill(ePS_高级慧根);
				pet.AddSkill(ePS_高级冥思);
				pet.AddSkill(ePS_移花接木);
				GetPet2(&pet, 100);
			}
		}
		break;
	case 3://李善人
		if (g_pCharacter->m_PCData.m_Money[0] < 2000)
		{
			AddTriggerDialog2(2);
			SetJiangLi2(0, 2000);
		}
		else AddTriggerDialog2(3);
		break;
	case 4:Select(6, 5, -1, 3, 5, 4, -1); break;//打造
	case 5:	g_pMainState->m_Dazao.OnOff(TRUE); break;
	case 6:
		if (g_pCharacter->m_PCData.m_BangPaiID == -1)
		{
			TalkList(4,-1,-1,-1,-1);
		}
		else Select(8,7,-1,3,7,4,-1);
		return TRUE;
	case 7:
		g_pMainState->m_Map.LoadMap(124, 115,"帮派", 0);
		break;
	case 8://八岐大蛇
		if (!CheckINT(11, 1))
		{
			for (int i = 0; i < 7; i++)
			{
				AddPetEnemy2(100000, e超级神蛇, 160, 9);
			}
			SetMusic(m_Textlist[9]);
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(9);
		}
		else AddTriggerDialog2(5);
		return TRUE;
	case 9: //
		
		{
			SetJiangLi2(5000000, 300000, 500000, 1000000, TRUE);
			SetJiangLiItem(23,24);
			AddTriggerDialog2(5);
			SetINT(11, 1);
			g_pMainState->m_GlobalButton[14] += 200;
			g_pMainState->m_GlobalButton[15] += 200;
#if ccc_m5
			g_pCharacter->m_PCData.AddGrowing(5);
			g_pCharacter->m_PCData.AddAtkZZ(100);
			g_pCharacter->m_PCData.AddDefZZ(100);
#endif
		}
		return TRUE;
	case 10:
#if ccc_m5
		if (g_pMainState->m_State.CheckAddPoint())
		{
			Select(12, 10, -1, 3, 12, 4, -1);
		}
		else
		{
			Select(11, 10, -1, 3, 11, 4, -1);
		}
#endif
		return TRUE;
	case 11:
#if ccc_m5
		g_pMainState->m_State.SetAddPoint();
#endif
		return TRUE;
	case 12:
#if ccc_m5
		{
			g_pCharacter->m_PCData.ResetAddPoint();
			g_pMainState->m_State.SetAddPoint();
		}
#endif
		return TRUE;
	case 13:
		
		{
			if (g_pMainState->m_FangWu.GetGuiMo() > 3)
			{
				AddTriggerDialog2(6);
				return TRUE;
			}
			ostringstream oss;
			oss << "当前房屋规模为";
			oss << g_pMainState->m_FangWu.GetGuiMo();
			oss << "升级需要";
			oss << (g_pMainState->m_FangWu.GetGuiMo()+1) * 200;
			oss << "万,需要吗?";
			g_pMainState->m_TriggerDialog.AddSelect(this, oss.str(), g_pMainState->m_pNowSelect->m_TrueName.GetString(), -1,
				m_Textlist[3], 14,
				m_Textlist[4], -1
				);
		}
		return TRUE;
	case 14:
		if (g_pCharacter->m_PCData.AddMoney(-(g_pMainState->m_FangWu.GetGuiMo() + 1) * 2000000,0,0,FALSE))
		{
			g_pMainState->m_FangWu.SetGuiMo(g_pMainState->m_FangWu.GetGuiMo() + 1);
		}
		else g_pMainState->m_pNowSelect->Talk("钱不够");
		return TRUE;
	case 15:
		if (!CheckINT(12, 5))
		{
			AddTriggerDialog2(7);
			SetINT(12, 4);
		}
		return TRUE;
	case 16:
		if (CheckINT(12, 4)&&(!CheckINT(12,5)))
		{
			AddTriggerDialog2(8,17);
		}
		return TRUE;
	case 17:
		
		{
			cPetData* pet;
			pet= AddPCPetEnemy2(20000, e赛太岁, 90);
			pet->ghostSpecial.d1 += 100;
			ePetID petid;
			for (int i = 0; i < 4; i++)
			{
				switch (rand() % 3)
				{
				case 0:petid = e百足将军; break;
				case 1:petid = e野猪精; break;
				default:petid = e锦毛貂精; break;
				}
				AddPCPetEnemy2(15000, petid, 85, (eMengPai)(rand() % 12));
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(18);
		}
		return TRUE;
	case 18:
		
		{
			SetJiangLi2(1250000, 250000, 250000, 1250000);
			AddTriggerDialog2(9); 
			SetJiangLiItem(44,40);
			SetJiangLiItem(25,24);
#if ccc_m5
			g_pCharacter->m_PCData.AddGrowing(1);
#endif
			SetINT(12,5);
		}
		return TRUE;
	case 19:
		
		{
			if (g_pCharacter->m_PCData.m_FightPetID == -1)return TRUE;
			cPetData& Pet = g_pCharacter->m_PCData.m_pPetDataList[g_pCharacter->m_PCData.m_FightPetID]->m_PetDataZZ;
			ostringstream oss;
			switch (Pet.m_JinJieNum.m_JinJieNum)
			{
			case 0:
			case 1:
			case 2:
				oss << "你的出战召唤兽离下次进阶还需" << (Pet.m_JinJieNum.m_JinJieNum+1)*2000000;
				break;
			default:
				oss << "你的出战召唤兽已经无法再进阶了";
				break;
			}
			m_pObj = g_pMainState->m_pNowSelect;
			g_pMainState->m_TriggerDialog.AddSelect(this, oss.str(), m_pObj->m_TrueName.GetString(), -1,
				m_Textlist[3], 20,
				m_Textlist[4], -1);
		}
		break;
	case 20:
		
		{
			if (g_pCharacter->m_PCData.m_FightPetID == -1)return TRUE;
			cPetData& Pet = g_pCharacter->m_PCData.m_pPetDataList[g_pCharacter->m_PCData.m_FightPetID]->m_PetDataZZ;
			if (g_pCharacter->m_PCData.AddMoney(-(Pet.m_JinJieNum.m_JinJieNum + 1) * 2000000,0,0,0))
			{
				Pet.SetJinJie(1);
				m_pObj->Talk("进阶成功");
				g_pMainState->m_PCHead.UpdatePet();
			}
			else m_pObj->Talk("钱不够");
		}
		break;
	case 21:
		
		{
			m_pObj = g_pMainState->m_pNowSelect;
			g_pMainState->m_TriggerDialog.AddSelect(this,m_Textlist[13], m_pObj->m_TrueName.GetString(), -1,
				m_Textlist[3], 22,
				m_Textlist[4], -1);
		}
		break;
	case 22:
		
		{
			if (g_pCharacter->m_PCData.AddMoney(-1000000, 0, 0, 0))
			{
				vector<int> lis;
				g_pMainState->m_ZuoQi.GetShiPei(lis, g_pCharacter->m_PCData.modeid);
				g_pMainState->m_ZuoQi.GetZuoQi(g_pCharacter->m_PCData, lis[rand()%lis.size()]);
				m_pObj->Talk("得到了坐骑");
			}
			else m_pObj->Talk("钱不够");
		}
		break;
	case 23:
		
		{
			BOOL bhave[5] = {0};
			for (int i = 0; i < 60; i++)
			{
				if (27 == g_pCharacter->m_PCData.m_Item[i].GetType())
				{
					switch (g_pCharacter->m_PCData.m_Item[i].GetID())
					{
					case 6:bhave[0] = TRUE; break;
					case 7:bhave[1] = TRUE; break;
					case 8:bhave[2] = TRUE; break;
					case 9:bhave[3] = TRUE; break;
					case 10:bhave[4] = TRUE; break;
					default:break;
					}
				}
			}
			for (int i = 0; i < 5; i++)
			{
				if (!bhave[i])
				{
					AddTriggerDialog2(10);
					return TRUE;
				}
			}
			for (int i = 0; i < 60; i++)
			{
				if (27 == g_pCharacter->m_PCData.m_Item[i].GetType())
				{
					switch (g_pCharacter->m_PCData.m_Item[i].GetID())
					{
					case 6:
						if (bhave[0])
						{
							bhave[0] = 0;
							g_pCharacter->m_PCData.m_Item[i].m_Num -= 1;
						}
						break;
					case 7:
						if (bhave[1])
						{
							bhave[1] = 0;
							g_pCharacter->m_PCData.m_Item[i].m_Num -= 1;
						}
						break;
					case 8:
						if (bhave[2])
						{
							bhave[2] = 0;
							g_pCharacter->m_PCData.m_Item[i].m_Num -= 1;
						}
						break;
					case 9:
						if (bhave[3])
						{
							bhave[3] = 0;
							g_pCharacter->m_PCData.m_Item[i].m_Num -= 1;
						}
						break;
					case 10:
						if (bhave[4])
						{
							bhave[4] = 0;
							g_pCharacter->m_PCData.m_Item[i].m_Num -= 1;
						}
						break;
					default:break;
					}
				}
			}
			SetJiangLiItem(23,28);
		}
		break;
	case 24:Select(14, 15, -1, 3, 25, 4, -1); break;
	case 25:
		if (g_pCharacter->m_PCData.AddMoney(-1000000, 0, 0, FALSE))
		{
			g_pCharacter->m_PCData.AddPopularity(10);
		}
		else g_pMainState->m_Tags.Add("钱不够");
		break;
	case 26:
		
		{
			int moneyneed;
			if (g_pMainState->m_FightList[g_pMainState->m_HeroID + 5].isLive)
			{
				cPet* Pet = (cPet*)g_pMainState->m_FightList[g_pMainState->m_HeroID + 5].m_pData->m_pIndex;
				moneyneed = 10000 * (Pet->m_PetDataZZ.m_LV - Pet->m_PetDataZZ.m_FuZhuSkillLvList[0]);
			}
			else moneyneed = -1;
			ostringstream oss;
			oss << m_Textlist[17];
			if (moneyneed > -1)
				oss << "(需要#R" << moneyneed << "#R钱)";
			else
				oss << "你现在没有出战召唤兽";
			g_pMainState->m_TriggerDialog.AddSelect(this, oss.str(), m_Textlist[16], -1,
				"强化", 27,
				m_Textlist[21], -1
		/*		m_Textlist[19], 28,
				m_Textlist[20], 29,
				m_Textlist[21], -1*/
				);
		}
		break;
	case 27:
	case 28:
	case 29:
#if ccc_m5
		if (g_pMainState->m_FightList[g_pMainState->m_HeroID + 5].isLive)
		{
			cPet* Pet = (cPet*)g_pMainState->m_FightList[g_pMainState->m_HeroID + 5].m_pData->m_pIndex;
			int lvadd = Pet->m_PetDataZZ.m_LV - Pet->m_PetDataZZ.m_FuZhuSkillLvList[0];
			int moneyneed = 10000 * lvadd;
			if (lvadd<1)
			{
				g_pMainState->m_Tags.Add("召唤兽需要升级才能继续强化");
				return TRUE;
			}
			if (g_pCharacter->m_PCData.AddMoney(-moneyneed, 0, 0, FALSE))
			{
			
				for (int i = 0; i < 3;i++)
					Pet->m_PetDataZZ.lvUpFuZhuSkill(lvadd, i);
			}
			else g_pMainState->m_Tags.Add("钱不够");
		}
		else g_pMainState->m_Tags.Add("没有出战召唤兽");
#endif
		break;
	case 30:
		if (g_pCharacter->m_PCData.m_LV < 60)
			g_pMainState->m_LearnBangPaiSkill.OnOff(TRUE);
		else
			g_pMainState->m_pNowSelect->Talk("我只帮新人(60级以下的)");
		break;
	default:
#if ccc_m5
		ERRBOX;
#else
		if (stage == 31)
		{
			g_pMainState->m_ZhiXian3.Process(0);
		}
		else if (stage >(1 << 24))
		{
			g_pMainState->m_ZhiXian3.Process(stage);
		}
		else
		{
			ERRBOX;
		}

#endif
		break;
	}
	return TRUE;
}

BOOL cTaskZhiXian::Process1(int stage)
{
	if (stage < 0)return TRUE;
	AddTriggerDialog2(stage);
	return TRUE;
}

BOOL cTaskZhiXian::Process2(int stage)
{
	if (stage < 0)return TRUE;
	switch (stage)
	{
	case 5:
		if (CheckINT(12, 0))
		{
			AddTriggerDialog2(-stage);
		}
		else
		{
			SetINT(12, 2);
			AddTriggerDialog2(stage);
		}
		break;
	case 6:
		if (CheckINT(12, 0))
		{
			AddTriggerDialog2(-stage);
		}
		else
		{
			SetINT(12, 1);
			AddTriggerDialog2(stage);
		}
		break;
	case 7:
		if (CheckINT(12, 1) && CheckINT(12, 2))
		{
			if (!CheckINT(12, 0))
			{
				SetINT(12,0);
				AddTriggerDialog2(-stage);
				SetJiangLiItem(4,40);
			}
			else
			{
				AddTriggerDialog2(-stage-100);
			}
		}
		else
		{		
			AddTriggerDialog2(stage);
		}
		break;
	default:
		AddTriggerDialog2(stage);
		break;
	}
	return TRUE;
}

BOOL cTaskZhiXian::Process3(int stage)
{//宝箱
	int baoxiangid;
	int baoxiangindex;
	GetBaoXiangID(stage, baoxiangid, baoxiangindex);
	SetINT(baoxiangid, baoxiangindex);
	switch (stage)
	{
	case -1:
		return TRUE;
		//东海海底
	case 0:SetJiangLiItem(0, 32); break;
	case 1:SetJiangLiItem(0, 33); break;
		//沉船
	case 2:SetJiangLiItem(0, 34); break;
		//东海岩洞
	case 3:SetJiangLiItem(2, 22,10); break;
	case 4:SetJiangLiItem(0, 23,30); break;
	case 5:SetJiangLiItem(10, 24); break;
		//建邺杂
	case 6:SetJiangLiItem(1, 27); SetJiangLiItem(2, 27); break;
		//
	case 7:SetJiangLiItem(0, 29); break;
	case 8:SetJiangLi2(0, 500000, 0, 0); break;
		//无名鬼城
	case 9:SetJiangLiItem(4, 24); break;
		//大雁塔
	case 10:SetJiangLiItem(59, 27); break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		SetJiangLi(1,0,0,0,100,50); break;
	case 16:
		SetJiangLi2(500); break;
	case 17:
		SetJiangLiItem(3,24);
		break;
	case 18:
		SetJiangLiItem(77, 40);
		break;
	default:
		break;
	}
	g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect, TRUE);
	return TRUE;
}

void cTaskZhiXian::GetBaoXiangID(int type, int& id, int& index)
{//宝箱对应的脚本号
	id = 100 + type / 30;
	index = type % 30;
}

BOOL cTaskZhiXian::Process4(int stage)
{
	if (stage == -1)return TRUE;
	if (stage < 300)
	{//商店
		g_pMainState->m_InterFaceBuy.Open(stage);
		return TRUE;
	}
	switch (stage)
	{
	case -1:return TRUE;
	default:ERRBOX;
		break;
		
	}
	return TRUE;
}
void cTaskZhiXian::ProcessSelect(int stage)
{
	m_pObj = g_pMainState->m_pNowSelect;
	g_pMainState->m_TriggerDialog.AddSelect(this, m_Textlist[stage], g_pMainState->m_pNowSelect->m_TrueName.GetString(), -1,
		"是", stage,
		"否", -1
		);
}

BOOL cTaskZhiXian::Process6(int stage)
{
	switch (stage)
	{
	case -1:return TRUE;
	case 0:Select(2, 1, -1, 3, 1, 4, 2, 5, 3);break;
	case 1:
	case 2:
	case 3:
#if ccc_m5
		{
			int& k = g_pMainState->m_GlobalButton[0];
			switch (stage)
			{
			case 1:
				if (k <= 50)g_pCharacter->m_PCData.GoldLivePercent.d1 -= 100;
				k = 100; 
				g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(TRUE);
				break;
			case 2:
				if (k<=50)g_pCharacter->m_PCData.GoldLivePercent.d1 -= 100;
				k = 80; 	
				g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(FALSE);
				break;
			case 3:
				if (k > 50)g_pCharacter->m_PCData.GoldLivePercent.d1 += 100;
				k = 50;
				g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(FALSE);
				break;
			}
		}
#endif
		break;
	default:
		ERRBOX;
		break;
	}
	return TRUE;
}

void cTaskJuQing::SetChapter(int chapter)
{
	if (chapter == m_Chapter)return;
	m_Chapter = chapter;
	m_bInit = FALSE;
	Init();
}

void cTaskJuQing::Save(ofstream& File)
{
	File << "\n";
	File << m_Chapter << " ";
}

void cTaskJuQing::Load(ifstream& File)
{
	File >> m_Chapter;
	m_bInit = FALSE;
//	m_bInit2 = FALSE;
	Init();
}

std::string cTaskJuQing::SetUpPathJuQing(string str)
{
	string path1 = g_strMediaPath;
#if ccc_m5
	path1+="任务//";
#endif
	path1 += m_AutoPath;
	path1 += "//";
	path1 += str;
	path1 += ".txt";
	return path1;
}

cPetData* cTaskJuQing::AddPetEnemy2(int hp, ePetID id, int lv, int name /*= -1*/, BOOL bOur /*= FALSE*/, int pos)
{
	cPetData* p;
	int k= AddPetEnemy(id, lv, name, bOur,pos);
	g_pMainState->m_FightList[k].m_pData->GetDateP(p);
#if ccc_date
	if (!p->m_JinJieNum.m_JinJieNum)
	{
		p->SetJinJie(MyTest::getInstance()->getJinjie(lv));
	}
#endif
	if (hp > 0)
	{
		p->m_HPMax.SetData(hp);
		p->FillHPMP();
	}
	return p;
}
#if ccc_date
sAddPoint cTaskJuQing::getAddPointFromMenpai(eMengPai e)
{
	sAddPoint a;
	switch (e)
	{
	case eMP_无:
	case eMP_大唐官府:
	case eMP_狮驼岭:
		a = g_addPointAtk;
		break;
	case eMP_方寸山:
	case eMP_天宫:
		a.Set(0, 0, 3, 0, 2);
		break;
	case eMP_魔王寨:
	case eMP_东海龙宫:
		a = g_addPointMag;
		break;
	case eMP_五庄观:
		a.Set(3, 0, 0, 0, 2);
		break;
	case eMP_化生寺:
	case eMP_盘丝岭:
	case eMP_阴曹地府:
	case eMP_女儿村:
	case eMP_普陀山:
		a.Set(0, 3, 0, 0, 2);
		break;
	default:
		break;
	}
	return a;
}

eMengPai cTaskJuQing::getMenPaiFromRand()
{
	eMengPai mp = eMengPai(rand() % 12);
	if (mp == eMP_女儿村 || mp == eMP_阴曹地府 || mp == eMP_盘丝岭)
	{
		mp = eMengPai(rand() % 12);
	}
	return mp;
}
#endif
cPetData* cTaskJuQing::AddPCPetEnemy2(int hp, ePetID id, int lv, eMengPai mp, int name /*= -1*/, BOOL bOur /*= FALSE*/, int pos)
{
	cPetData* p;
#if ccc_date
	if (mp == eMP_随机)
	{
		mp = getMenPaiFromRand();
	}
	m_AddPoint = getAddPointFromMenpai(mp);
#endif
	int k= AddPCPetEnemy(id, lv, mp, name, bOur,pos);
	if (k == -1)return 0;
	g_pMainState->m_FightList[k].m_pData->GetDateP(p);
#if ccc_date
	if (!p->m_JinJieNum.m_JinJieNum)
	{
		p->SetJinJie(MyTest::getInstance()->getJinjie(lv));
	}
#endif
	if (hp > 0)
	{
		p->m_HPMax.AddDataAdd(hp);
		p->FillHPMP();
	}
	return p;
}

cPetData* cTaskJuQing::AddPCEnemy2(int hp, int id, sZiZhi* zz, int lv, eMengPai mp, int name /*= -1*/, int weapontype /*= -1*/, int weaponid /*= -1*/, BOOL bOur /*= FALSE*/, int pos)
{
	cPetData* p;
#if ccc_date
	if (mp == eMP_随机)
	{
		mp = getMenPaiFromRand();
	}
	m_AddPoint = getAddPointFromMenpai(mp);
	if (weapontype < 0 || weaponid < 0)
	{
		int typelist[2];
		GetWeaponType((id >= 2000) ? (id - 2000) : id, typelist[0], typelist[1]);
		weapontype = typelist[rand() % 2];
		if (typelist[1] == -1)
			weapontype = typelist[0];
		weaponid = g_pMainState->m_ItemManage.GetIDByLv(weapontype, lv);
	}
#endif
	int k=AddPCEnemy(id, zz, lv, mp, name, weapontype, weaponid, bOur,pos);
	g_pMainState->m_FightList[k].m_pData->GetDateP(p);
	if (hp > 0)
	{
		p->m_HPMax.SetData(hp);
		p->FillHPMP();
	}
	return p;
}



void cTaskJuQing::AddTag(int str, int time/*=500*/)
{
	g_pMainState->m_Tags.Add(m_Textlist[str], time);
}

void cTaskJuQing::LockMap(int name/*=-1*/)
{
	switch (name)
	{
	case -1:
		g_pMainState->m_Map.SetLock("");
		break;
	case 0:
	case 1:
		g_pMainState->m_Map.SetLock(name);
		break;
	default:
		g_pMainState->m_Map.SetLock(m_Textlist[name]);
		break;
	}
	
}

void cTaskJuQing::AddRangeMap(int mapname, int x, int y, int range, int ret)
{
	sTriggerRange data;
	data.Set(m_Textlist[mapname], x, y, range, this, ret);
	g_pMainState->m_Map.AddTriggerRange(data);
}

sItem2* cTaskJuQing::FindItem(int Type, int id)
{
	for (int i = 0; i < 60; i++)
	{
		sItem2* pItem= &g_pCharacter->m_PCData.m_Item[i];
		if (pItem->m_Num)
		if (pItem->GetID()==id)
		if (pItem->GetType() == Type)
			return pItem;
	}
	return 0;
}

void cTaskJuQing::AddFriend(int i)
{
	g_pMainState->m_Friend.AddFriend(m_Textlist[i]);
}

void cTaskJuQing::AddTriggerObjMap2(int name, int mapname, int modeid, int x, int y, int direction, int ret /*= -1*/, int jinjie)
{
	
	sMapObjTrigger obj;
	obj.m_pTask = this;
	obj.m_Stage = ret;
	obj.m_Npc.Set(m_Textlist[name], m_Textlist[mapname], modeid, x, y, direction,jinjie);
	AddTriggerObjMap(&obj);
}





BOOL cTaskZhiXian2::Process(int stage)
{
#if ccc_date
	return TRUE;
#endif
	switch (g_pCharacter->m_PCData.m_MengPaiID)
	{
	case eMP_大唐官府:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级必杀);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_风刃);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_直死);
			break;
		default:ERRBOX;
			break;
		}
		break;
	case eMP_普陀山:
	case eMP_化生寺:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级夜战);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术连击);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级幸运);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级招架);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级永恒);
			break;
		default:ERRBOX;
			break;
		}
		break;
	case eMP_方寸山:
	case eMP_女儿村:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级夜战);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级敏捷);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级否定信仰);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级幸运);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级神迹);
			break;
		default:ERRBOX;
			break;
		}
		break;	
	case eMP_狮驼岭:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级必杀);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级反击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级反震);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级神迹);
			break;
		default:ERRBOX;
			break;
		}
		break;
	case eMP_魔王寨:
	case eMP_东海龙宫:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级防御);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级敏捷);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术波动);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级魔之心);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术暴击);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_迷你空间震);
			break;
		default:ERRBOX;
			break;
		}
		break;
	case eMP_盘丝岭:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级鬼魂术);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级必杀);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_直死);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_风华武圣);
			break;
		default:ERRBOX;
			break;
		}
		break;
	case eMP_阴曹地府:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级防御);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级夜战);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级敏捷);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级招架);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级吸血);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级鬼魂术);
			break;
		default:ERRBOX;
			break;
		}
		break;
	case eMP_五庄观:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级敏捷);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级强力);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级精神集中);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级神迹);
			break;
		default:ERRBOX;
			break;
		}
		break;
	case eMP_天宫:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级魔之心);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_风华武圣);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_迷你空间震);
			break;
		default:ERRBOX;
			break;
		}
		break;
	default:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return TRUE;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级魔之心);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_高级连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_风华武圣);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PCData.AddSkill(ePS_迷你空间震);
			break;
		default:ERRBOX;
			break;
		}
		break;
	
	}
	
	return TRUE;
}
BOOL cTaskZhiXian3::Process(int stage)
{
	switch (stage)
	{
	case 0:
	{
			  if (g_StateType != STATE_MAIN)return FALSE;
#if ccc_date
			  {
				  MyTest::getInstance()->PKinit();
				  MyTest::getInstance()->PK();
				  g_StateType = STATE_FIGHT;
				  string musicname = "战斗比武";
				  musicname += cc::toString(2 + rand() % 4);
				  SetMusic(musicname);
				  AddTriggerFightSuccess(-1);
				  AddTriggerFightFalse(-1);
				  AddTriggerFightEscape(-1);
				  break;
			  }
#endif
			  Init2();
			  ifstream File;
			  string path1 = g_strMediaPath;
			  path1 += "PK\\";
			  ostringstream oss;
			  oss << path1;
			  oss << "index.txt";
			  File.open(oss.str());
			  if (!File)return FALSE;
			  int userid, enemyid;
			  File >> userid;
			  File >> enemyid;
			  File.close();
			  for (int i = 0; i < 10; i++)
			  {
				  m_PreFighter[i] = g_pMainState->m_FightList[i].m_pData;
				  g_pMainState->m_FightList[i].m_pData = m_pFighter[i];
				  m_islive[i] = g_pMainState->m_FightList[i].isLive;
				  g_pMainState->m_FightList[i].isLive = TRUE;
				  g_pMainState->m_FightList[i].m_SkillPreSelect.SkillID = -1;
			  }


			  swap(m_prehard, g_pMainState->m_GlobalButton[0]);
			  m_eOurFormation = g_pMainState->m_InterfaceTeam.m_eOurFormation;
			  if (!LoadTeam(userid, path1, FALSE))return FALSE;
			  if (!LoadTeam(enemyid, path1, TRUE))return FALSE;
			  g_StateType = STATE_FIGHT;
			  string musicname;
			  switch (rand() % 3)
			  {
			  case 0:
				  musicname = "战斗_比武_DT";
				  break;
			  case 2:
				  musicname = "战斗比武";
				  break;
			  default:
				  musicname = "战斗比武2";
				  break;
			  }
			  SetMusic(musicname);
			  AddTriggerFightSuccess(-1);
			  AddTriggerFightFalse(-1);
			  AddTriggerFightEscape(-1);
			  g_pMainState->SetCharacter(g_pMainState->m_HeroID);
			  m_bPK = TRUE;

			  g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(TRUE);
	}
		break;
	case -1:
#if ccc_date
	MyTest::getInstance()->PKover();
	break;
#endif
		m_bPK = FALSE;
		for (int i = 0; i < 5; i++)
		{
			g_pMainState->SetFightPet(i, -1);
		}
		for (int i = 10; i < 15; i++)
		{
			g_pMainState->SetFightPet(i, -1);
		}
		for (int i = 0; i < 10; i++)
		{
			g_pMainState->m_FightList[i].m_pData = m_PreFighter[i];
			g_pMainState->m_FightList[i].isLive = m_islive[i];
		}
		swap(m_prehard, g_pMainState->m_GlobalButton[0]);
		if (100 == g_pMainState->m_GlobalButton[0])
		{
			g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(TRUE);
		}
		else g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(FALSE);

		g_pMainState->m_InterfaceTeam.SetFormation(m_eOurFormation, 0, TRUE);
		g_pMainState->SetCharacter(g_pMainState->m_HeroID);
		g_pMainState->m_PCHead.UpDateHead();
		g_pMainState->FindObj();
		break;
	default:
#if ccc_date
		if (stage > (1 << 24))
		{
			if (g_StateType != STATE_MAIN)return FALSE;
			MyTest::getInstance()->PKinit();
			MyTest::getInstance()->PK(stage);
			g_StateType = STATE_FIGHT;
			string musicname = "战斗比武";
			musicname += cc::toString(2 + rand() % 4);
			SetMusic(musicname);
			AddTriggerFightSuccess(-1);
			AddTriggerFightFalse(-1);
			AddTriggerFightEscape(-1);
		}
#endif
		break;
	}

	return TRUE;
}

void cTaskZhiXian3::Init2()
{
	if (m_bInit2)return;
	m_bInit2 = TRUE;
	for (int i = 0; i < 10; i++)
	{
		m_pFighter[i] = new cObj;
		m_pFighter[i]->Init();
		m_pFighter[i]->m_IDInFightlist = i;
	}
}

BOOL cTaskZhiXian3::LoadTeam(int id, string path, BOOL bEnemy)

{
	int startid = 0;
	if (bEnemy)
	{
		startid = 10;
	}
	ifstream File;
	ostringstream oss;
	string name, path2, path3;
	for (int i = 0; i < 5; i++)
	{
		oss.str("");
		oss << path;
		oss << id << "\\";
		path2 = oss.str();
		oss.str("");
		oss << i;
		name = oss.str();
		if (!File)
		{
			Process(-1);
			return FALSE;
		}
		g_pMainState->m_FightList[startid + i].m_pData->LoadCharacter(name, path2);

		g_pMainState->m_FightList[startid + i].isLive = TRUE;
	}
	oss.str("");
	oss << path;
	oss << id << "\\index.txt";
	File.open(oss.str());
	if (!File)
	{
		Process(-1);
		return FALSE;
	}
	//阵形
	int formation;
	File >> formation;
	g_pMainState->m_InterfaceTeam.SetFormation((eFormation)formation, bEnemy);
	string dustbin;
	getline(File, dustbin);
	//召唤兽
	cPet* pet;
	cCharacter* pc;
	ifstream File2;
	int num;
	for (int i = 0; i < 5; i++)
	{
		pc = (cCharacter*)g_pMainState->m_FightList[startid + i].m_pData->m_pIndex;
		File >> num;
		int weapontype;
		int weaponid = 0;
		File >> weapontype;
		if (weapontype>-1)
		{
			File >> weaponid;
		}
		string petfilename;
		int positonid;
		for (int i2 = 0; i2 < num; i2++)
		{
			File >> petfilename;
			File >> positonid;
			pet = new cPet;
			oss.str("");
			oss << path;
			oss << id << "\\";
			path2 = oss.str();
			pet->m_PetDataZZ.ReadPet(petfilename, path2);
			pet->SetData(g_pMainState->m_PetDataManager.GetPetData(pet->m_PetDataZZ.modeid));
#if ccc_m5
			pet->m_PetDataZZ.Followlv(175);
#else
			pet->m_PetDataZZ.Followlv(MyTest::getInstance()->maxRoleLv + MyTest::getInstance()->lvGapFromRoleAndBaby, true, true, true);
#endif
			pet->m_PetDataZZ.SetJinJie(3);
			pet->m_PetDataZZ.m_JinJieNum.m_PositionID = positonid;
			pc->m_PCData.GetPet(pet);
			pet = 0;
		}

		g_pMainState->SetFightPet(startid + i, 0, FALSE);
		g_pMainState->m_FightList[startid + i].isLive = TRUE;
		pc->m_PCData.m_IDinFightList = startid + i;
#if ccc_m5
		pc->m_PCData.Followlv(175);
#else
		pc->m_PCData.Followlv(MyTest::getInstance()->maxRoleLv, false, true, true);
#endif
		if (weapontype > -1)
		{
			pc->m_PCData.m_Equip[2].Set(weapontype, weaponid, FALSE);
			pc->m_PCData.m_pWeaponData2 = 0;
			pc->m_PCData.m_pCharacterData2 = 0;

		}
		g_pMainState->m_FightList[startid + i].m_pData->Reset();
		g_pMainState->m_FightList[startid + i].m_pData->Set(POS_FIGHT_STAND);
		g_pMainState->m_FightList[startid + i + 5].m_pData->Set(POS_FIGHT_STAND);


		if (bEnemy)
			pc->m_PCData.m_Controler.Set(FALSE, FALSE, FALSE, TRUE, FALSE);
		else
			pc->m_PCData.m_Controler.Set(FALSE, FALSE, FALSE, TRUE, FALSE);

	}


	File.close();
	return TRUE;
}

cTaskZhiXian3::~cTaskZhiXian3()
{
	if (!m_bInit2)return;
	for (int i = 0; i < 10; i++)
	{
		m_pFighter[i]->Free();
		SAFE_DELETE(m_pFighter[i]);
	}
}
