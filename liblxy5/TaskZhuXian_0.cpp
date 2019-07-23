#include "_global.h"

bool TaskZhuXian::Process0(int stage)
{
	static string s_jobTitle = "商人的鬼魂";
	int next = stage + 1;
	switch (stage)
	{
	case -1: break;
	case 0:
		if (!g_pMainState->m_Job.CheckHaveJob(TASK_TYPE_ZHUXIAN))
		{
			sTaskMapObj st;
			st.m_Npc.Set("雷黑子", "建邺城", 1023, 68, 11, 1);
			st.m_pTask = this;
			st.m_Stage = next;
			AddTriggerObjMap(&st);
// 			AddNpcOne(&st, true);
// 			AddTriggerObj("雷黑子", "建邺城", 1);
// 			AddJob(s_jobTitle, "#R雷黑子#R有困难, 去看看吧\n#R建邺城#R");
		}
		break;
	case 1:
		g_pMainState->m_TriggerDialog.AddSelect(this, "商人鬼魂剧情又打不过,帮帮我吧#15", next);
		break;
	case 2:
		
		AddTriggerObj("商人的鬼魂", "沉船底舱", next + 1);
		AddJob(s_jobTitle, "东海湾->\n东海海底->\n沉船->\n沉船底舱->\n#R商人的鬼魂#R" + g_strNeedBattle);

		g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("雷黑子");
		g_pMainState->m_TriggerDialog.AddSelect(this, "我定了位置, 要不咱直接飞过去? ", next);

		RemoveTriggerObjMap(68, 11);
		g_pMainState->m_Map.RemoveNpc("雷黑子");
		break;
	case 3:
		g_pMainState->m_Map.LoadMap(17, 17, "沉船底舱");
		break;
	case 4:
		if (g_pMainState->m_InterfaceTeam.getLeaveBegin() > 1)
		{
			g_pHeroObj->say("别组队#24不然雷黑子加不了队");
			break;
		}
		{
			auto& xs = g_pMainState->m_pFightState->m_战斗坐标xs;
			auto& ys = g_pMainState->m_pFightState->m_战斗坐标ys;
			swap(xs[0], xs[1]);
			swap(xs[5], xs[6]);
			swap(ys[0], ys[1]);
			swap(ys[5], ys[6]);

			auto pc = g_pMainState->AddEnemy(e小毛头, 9, eMP_凌波城, "雷黑子", nullptr, -1, -1, true);
 			pc->apply();
 			pc->FillHpMp();
			pc->LiveMp += 64;
			pc->m_Controler.Set(0);
			pc->getObj()->say(g_pHeroObj->getPcData()->m_Name + ", 谢谢你的帮忙, 我中单我先上了#92");
			g_pMainState->setNowSelect("雷黑子", g_pMainState->m_pNpcList[/*10*/23].m_dialog);


			pc = g_pMainState->AddEnemy(e啸天犬, 5, eMP_无底洞, "大黄", nullptr, -1, -1, true);
 			pc->apply();
 			pc->FillHpMp();
			pc->LiveMp += 64;
			pc->m_Controler.Set(0);

			pc = g_pMainState->AddEnemy(e啸天犬, 5, eMP_神木林, "旺财", nullptr, -1, -1, true);
 			pc->apply();
 			pc->FillHpMp();
			pc->LiveMp += 64;
			pc->m_Controler.Set(0);

			sAddPoint ap;
			ap.Set(3, 0, 0, 2, 0);
			auto p = g_pMainState->AddEnemy(e啸天犬, 15, "狗子", &ap, -1, true);
			p->AddSkill(ePS_剑荡四方);
			p->LiveMp += 64;
			p->m_Controler.Set(0);
			p->SuckBloodRate.d1 += 100;
			p->SuckBloodPercent.d1 += 10;
			p->SetJinJie(2);
			p->getObj()->say("按V指挥集火点杀吧~嗷呜~");


			p = g_pMainState->AddEnemy(e僵尸, 15, "商人的鬼魂");
			p->HPMax.SetData(2000);
			p->FillHpMp();
			p->AddSkill(ePS_吸血);
			p->AddSkill(ePS_反击);
			p->CriRate.d2 += 99;
			p->DmgPercentOfFix.d2 += 50;

// 			static bool isSay = false;
// 			if (!isSay)
// 			{
// 				isSay = true;
// 				g_pMainState->m_Channel.AddNewString("尽量不要点临时队员的头像,可能出错", "提示");
// 			}

			for (int i = 0; i < 9; ++i)
			{
				g_pMainState->AddEnemy(rand() % 100 < 50 ? e虾兵 : e蟹将, 8 + rand() % 7);
			}
			g_pMainState->m_FightWorkList[rand() % 9 + 11].m_pObj->say("黑子你又来送经验#114");
		}

		g_pHeroObj->saySkill("   #24");

		g_StateType = STATE_FIGHT;

		AddTriggerFightEscape(next);
		AddTriggerFightFalse(next);
		AddTriggerFightSuccess(next + 1);
		break;
	case 6:
		RemoveTriggerObj();
		g_pMainState->awardk(10, 5, true);
		g_pMainState->awardEquip(20);
		AddTriggerDialogList({ "我继续跑剧情了, 以后有什么事尽管找我, 我罩着你#1", "#24去吧" }, next);
	case 5:
		g_pMainState->m_InterfaceTeam.update(false, 1);
		{
			auto& xs = g_pMainState->m_pFightState->m_战斗坐标xs;
			auto& ys = g_pMainState->m_pFightState->m_战斗坐标ys;
			swap(xs[0], xs[1]);
			swap(xs[5], xs[6]);
			swap(ys[0], ys[1]);
			swap(ys[5], ys[6]);
		}
		clearSay();
		break;
	case 7:
		g_pMainState->m_Job.ReMoveJob(this);
		break;
#if 0
	case 106://奸商
		AddTriggerDialog2(17, 107); break;
	case 107:
		Select(54, 57, -1, 55, -1, 56, 109); break;
	case 109:
		AddTriggerDialog2(18, 110);
		break;
	case 110:

	{
		SetINT(12, 3);
		cPet* Pet4 = 0;
		sAddPoint addpoint;
		addpoint.Set(4, 0, 0, 1, 0);
		g_pMainState->AutoPet(Pet4, e泡泡, 100, 14, addpoint);
//		g_pMainState->GivePcAPet(0, Pet4);
		RemoveTriggerObjMap(106);
		RemoveNpc(53, true);
	}
		break;
	case 0:
		ccm::get()->init();
		return true;
	case 36:
		for (int i = 0; i < 3; i++)
		{
			AddFriend(48 + i);
		}
		TalkList(20, 66, 67, 43, 38, 34);
		break;
	case 34:
	{
		Un邀请("神天兵");
		Un邀请("虎子");
		g_pMainState->m_Friend.Invite("燕子");
		g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect, 1);
		//			int id;
		for (int i = 2; i >= 0; --i)
		{
			AutoGetPet(m_Textlist[48 + i]/*, 0*/);
			g_pMainState->m_Friend.Invite(m_Textlist[48 + i]);
		}
		// 			g_pMainState->m_Friend.UnInvite("燕子");
		// 			id = g_pMainState->m_Friend.FindFriend("燕子");
		// 			g_pMainState->m_Friend.m_FriendList[id].m_dataFileName = "燕子2";
		// 			if (id > -1)
		// 			{
		// 				g_pMainState->m_Friend.Invite("燕子");
		// 			}
		g_pMainState->m_Friend.Invite("燕子");
		g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect, 1);
		RemoveTriggerObjMap();
		RemoveNpc(40, true);

	}
		break;

	case 38:
		AddTriggerDialog2(25);
		UpdateJob2(68);
		SetJiangLi(30, 1, 0, 50, 200, 200);
//		AddTriggerLv(37, ccm::get()->lv大雁塔触发);
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
	case 10086:
	{
		g_pMainState->m_DialogList.clear();
		AddChannel(m_Textlist[2]);

		AddTriggerFightStart(6);
		AddTriggerFightSuccess(105);

		sNpc npc;
		npc.Set("燕子", "东海海底", 2002, 14, 53, 0);
		AddTriggerObjMap(&npc, 4);
		//		g_pMainState->m_Dialog.Talk(m_Textlist[10], m_Textlist[1], 0xB0212A04);
		UpdateJob2(10);
	}
		break;
	case 101://宠物仙子
	{
		g_pMainState->m_DialogList.clear();
		NowNpcTalk(m_Textlist[20]);
		AddChannel(m_Textlist[2]);
		UpdateJob2(20);
		AddTriggerObj(m_Textlist[3], m_Textlist[4], 1);
		cPet* Pet4 = 0;
		sAddPoint p;
		p.Set(4, 0, 0, 1, 0);
		g_pMainState->AutoPet(Pet4, 120, 100, 10, p);
//		g_pMainState->GivePcAPet(0, Pet4);
	}
		return true;
	case 1: //找到兵铁铺
	{
		NowNpcTalk(m_Textlist[5]);
		SetJiangLiItem(0, 7);
		AddTriggerObj(m_Textlist[6], m_Textlist[7], 2);
		UpdateJob2(5);
		AddChannel(m_Textlist[46]);
	}
		return true;
	case 2://找到装备鉴定商
	{
		cObj* pob = g_pMainState->FindObjByName(m_Textlist[6]);
		pob->Talk(m_Textlist[8]);
		for (int i = 0; i < 60; i++)
		{
			if (g_pCharacter->m_PcData.m_Items[i].GetNum())
				if (g_pCharacter->m_PcData.m_Items[i].GetType() == eWeaponType棒)
				{
				g_pMainState->m_ItemManage.AutoItemProperty(&g_pCharacter->m_PcData.m_Items[i]);
				break;
				}
		}
		AddChannel(m_Textlist[9]);
		RemoveTriggerObj();
		AddTriggerLv(3, 5);
		UpdateJob2(9);
		AddTriggerFightStart(6);
		AddTriggerFightSuccess(105);
	}
		return true;
	case 3: //燕子出现
	{
		sNpc npc;
		npc.Set("燕子", "东海海底", 2002, 14, 53, 0);
		AddTriggerObjMap(&npc, 4);
		g_pMainState->m_Dialog.Talk(m_Textlist[10], m_Textlist[1], 0xB0212A04);
		UpdateJob2(10);
	}
		return true;
	case 4: AddTriggerDialog2(0, 5); break;
	case 5:
	{

		AddTag(11);
		RemoveNpc(40, true);
		//			g_pMainState->m_Friend.AddFriend("燕子");
		//给燕子买个BB
		AutoGetPet("燕子"/*,0*/);
		g_pMainState->m_Friend.Invite("燕子");
		RemoveTriggerObjMap();
		AddTriggerFightSuccess(7);
		g_pMainState->FindObj();

		AddTriggerDialog2(21, -5);
		//			g_pMainState->LockLv(15);
	}
		return true;
	case -5:
		AddChannel(m_Textlist[47]);
		return true;
	case 6:
	{
		g_pMainState->m_TriggerFightStart.ReMove(this);
		AddTag(12);
		AddChannel(m_Textlist[12]);
	}
		return true;
	case 7:AddTriggerDialog2(1, 8); break;
	case 8:
	{
		AddTriggerObj(m_Textlist[15], m_Textlist[16], 9);
		UpdateJob2(14);
	}
		return true;
	case 9:

	{
		AddTriggerDialog2(2, 10);
	}
		return true;
	case 10:

	{
		sNpc npc;
		npc.Set(m_Textlist[53], m_Textlist[7], 2009, 110, 54, 1);
		AddTriggerObjMap(&npc, 106, false);

		//AddTriggerObjMap(&npc, 4);
		UpdateJob2(19);
		AddTriggerObjMap(m_Textlist[7], 11, false);
	}
		return true;
	case 11:
		AddTriggerDialog2(3, 12);
		break;
	case 12:
		RemoveTriggerObjMap(11);
		UpdateJob2(17);
		AddTriggerObjMap(m_Textlist[18], 13, false);
		return true;
	case 13:AddTriggerDialog2(4, -14); break;
	case -14:

	{
		AddTriggerFightFalse(-15);//
		AddTriggerFightEscape(-15);//
	}
	case 14://进入BOSS战
	{
		//			m_AddPoint = g_addPointAtk;
		cPropertyData* petdata = AddPetEnemy2(3000, e僵尸, 30, 58);
		petdata->AddSkill(ePS_高级连击);
		petdata->AddSkill(ePS_吸血);
		petdata->AddSkill(ePS_高级反击);
		petdata->CounterRate.d1 = 50;
		petdata->ComboRate.d1 = 100;
		petdata->Pierce刺穿.d1 = 10;

		int id;
		for (int i = 0; i < 9; i++)
		{
			id = rand() % 2;
			if (id)id = 20;
			else id = 21;
			AddPetEnemy2(500, (ePetID)id, 20);
		}
		g_pMainState->m_Mp3.Load("战斗BOSS");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(15);
		AddTriggerDialog2(22, -1);
	}
		return true;
	case -15:

	{
		RemoveTriggerObjMap();
		AddTriggerObj("商人的鬼魂", m_Textlist[18], 14); break;//战斗失败
	}
		break;
	case 15://商人的鬼魂奖励

	{
		SetJiangLi2(20000, 3000, 20000, 20000, true);
		SetJiangLiItem(1, 21);
		SetJiangLiItem(0, 23, 30);
		RemoveTriggerObjMap();
		AddTriggerDialog2(5, 16);
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
		UpdateJob2(29);
		RemoveTriggerObj();
		// 			g_pCharacter->m_PCData.AddHpZZ(100);
		// 			g_pCharacter->m_PCData.AddAtkZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
	}
		return true;
	case 16://县令
		AddTag(44);
		AddTriggerObj2(15, 16, 17);
		return true;
	case 17:
		RemoveTriggerObj();
		if (!CheckINT(12, 3))
			AddTriggerDialog2(6, 18);
		else
			AddTriggerDialog2(19, 18);
		return true;
	case 18://商人的鬼魂结束

	{
		AddTag(22);
		UpdateJob2(28);
		AddTriggerObjMap(m_Textlist[23], 19);
		g_pMainState->LockLv(25);
		g_pMainState->m_Map.SetLock();
		sNpc npc;
		npc.Set(m_Textlist[52], m_Textlist[7], 2011, 92, 49, 1);
		AddTriggerObjMap(&npc, -18);
		AddTriggerDialog2(23);
	}
		return true;
	case -18:TalkList(16, -1, -1, -1, -1); break;
	case 19:AddTriggerDialog2(7, 20);
		RemoveTriggerObjMap();
		break;
	case 20://

	{
		g_pMainState->m_Friend.UnInvite("燕子");
		AddTriggerObjMap2(48, 23, 2007, 473, 26, 3, -20);
		UpdateJob2(69);
		g_pMainState->m_Map.ShadowNpc(m_Textlist[27], false, false);
	}
		return true;
	case -20:
		TalkList(26, 27, 23, 26, 23);
		RemoveTriggerObjMap();
		g_pMainState->m_Map.ShadowNpc(m_Textlist[27], true, true);
		return true;
	case 23:AddTriggerDialog2(9, 24); break;
	case 24:

	{
		RemoveTriggerObj();
		g_pMainState->m_Map.LoadMap(12, 10, "盘丝洞");
		g_pMainState->m_Tags.Add("可以去任何门派拜师");
		//	AddTriggerObj(m_Textlist[30], m_Textlist[31], 25);
		//	UpdateJob2(51);
		//	return true;
		//case 25://拜师
		//	AddTag(32);
		//	g_pMainState->m_Channel.AddNewString(m_Textlist[33]);
		//	g_pCharacter->m_PCData.m_MengPaiID = 6;
		LockMap();
		LockMap(false);
		/*	SetJiangLiItem(0, 27, 30);
		SetJiangLiItem(12, 28, 3);
		AddChannel(m_Textlist[45]);*/
		g_pMainState->m_FangWu.SetGuiMo(0);
		UpdateJob2(37);

		sTaskMapObj npc;
		npc = g_pMainState->m_Friend.m_FriendList[g_pMainState->m_Friend.FindFriend("燕子")];
		npc.m_Npc.m_mapname = "长安城";
		npc.m_pTask = this;
		npc.m_Stage = 36;
		npc.m_Npc.Set(444, 245);
		AddTriggerObjMap(&npc);
		LockMap();
	}
		break;
#endif
	default:
		ERRBOX;
		return true;
	}
	return true;
}


