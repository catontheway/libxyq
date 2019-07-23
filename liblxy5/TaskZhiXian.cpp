#include "_global.h"


bool cTaskZhiXian::Process(int stage)
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


bool cTaskZhiXian::Process0(int stage)
{
	int r = rand() % 100;
	switch (stage)
	{
	case -1:return true;
// 	case 0://无名野鬼
// 	{
// 		return false;
// 		int& num = g_pMainState->m_GlobalButton[11];
// 		if (num & 0x01)return true;
// 		AddTriggerDialog2(0, 1);
// 	}
// 		break;
// 	case 1:
// 		Select(2, 1, -1, 3, 2, 4, -1); break;
// 	case 2:
// 
// 	{
// 		sItem2* pItem = FindItem(28, 23);
// 		if (pItem)
// 		{
// 			pItem->m_Num = 0;
// 			SetINT(11, 0);
// 			sShangPinPet pet;
// 			sAddPoint point;
// 			point.Set(0, 0, 4, 1, 0);
// 			pet.Set(e雾中仙, &point);
// 			pet.m_zizhi.mag = 4800;
// 			pet.m_zizhi.speed = 1700;
// 			pet.m_zizhi.hp = 9700;
// 			pet.m_zizhi.grow = 150;
// 			pet.AddSkill(ePS_奔雷咒);
// 			pet.AddSkill(ePS_雷击);
// 			pet.AddSkill(ePS_高级魔之心);
// 			pet.AddSkill(ePS_高级法术连击);
// 			pet.AddSkill(ePS_高级法术暴击);
// 			pet.AddSkill(ePS_高级再生);
// 			pet.AddSkill(ePS_高级精神集中);
// 			pet.AddSkill(ePS_高级神佑复生);
// 			pet.AddSkill(ePS_高级防御);
// 			pet.AddSkill(ePS_龙神守护);
// 			pet.AddSkill(ePS_高级敏捷);
// 			pet.AddSkill(ePS_高级招架);
// 			pet.AddSkill(ePS_高级飞行);
// //			pet.AddSkill(ePS_高级隐身);
// 			pet.AddSkill(ePS_高级慧根);
// 			pet.AddSkill(ePS_高级冥思);
// 			pet.AddSkill(ePS_移花接木);
// 			GetPet2(&pet, 100);
// 		}
// 	}
// 		break;
// 	case 3://李善人
// 		if (g_pCharacter->m_PcData.m_Money[0] < 2000)
// 		{
// 			AddTriggerDialog2(2);
// 			SetJiangLi2(0, 2000);
// 		}
// 		else AddTriggerDialog2(3);
// 		break;
 		////////////////////////////////////////////////////////////////////////// 这里对话要改成“打造”
	case 4:
	{
		g_pMainState->m_TriggerDialog.AddSelect(this, "只要有书铁,我可以帮你打造装备", 5);
		break;
		g_pMainState->m_TriggerDialog.AddSelect(this, "只要有书铁,我可以帮你打造装备", "冯铁匠", -1,
			"确定", 5,
			"取消", -1);
		break;
		Select(6, 5, -1, 3, 5, 4, -1); break;//打造
	}
	case 5:	
		// 狼：打造不要? 要
		g_pMainState->m_Dazao.m_MoneyNeed = 1;
		g_pMainState->m_Dazao.OnOff(true); 
		break;
	case 6:
//		if (g_pCharacter->m_PcData.m_BangPaiID == -1)
// 		{
// 			TalkList(4, -1, -1, -1, -1);
// 		}
//		else 
//		Select(8, 7, -1, 3, 7, 4, -1);
		g_pMainState->m_TriggerDialog.AddSelect(this, "我可以送你回帮派", 7);
		break;
		return true;
	case 7:
		g_pMainState->m_Map.LoadMap(124, 115, "帮派", 0);
		break;
// 	case 8://八岐大蛇
// 		if (!CheckINT(11, 1))
// 		{
// 			for (int i = 0; i < 5; i++)
// 			{
// 				auto p = AddPetEnemy2(99999, e超级神蛇, 169, 9);
// 				p->SetJinJie(3);
// 				p->Atk.AddDataAddPercent(35);
// 				p->CriRate.d1 += 30;
// 			}
// 			SetMusic(m_Textlist[9]);
// 			g_StateType = STATE_FIGHT;
// 			AddTriggerFightSuccess(9);
// 		}
// 		else AddTriggerDialog2(5);
// 		return true;
// 	case 9: //
// 	{
// 		SetJiangLi2(5000000, 300000, 500000, 1000000, true);
// 		SetJiangLiItem(23, 24);
// 		AddTriggerDialog2(5);
// 		SetINT(11, 1);
// 		g_pMainState->m_GlobalButton[14] += 200;
// 		g_pMainState->m_GlobalButton[15] += 200;
// // 		g_pCharacter->m_PCData.AddGrowing(5);
// // 		g_pCharacter->m_PCData.AddAtkZZ(100);
// // 		g_pCharacter->m_PCData.AddDefZZ(100);
// 	}
// 		return true;
	case 10:
		// 		if (g_pMainState->m_State.CheckAddPoint())
		// 		{
		// 			Select(12, 10, -1, 3, 12, 4, -1);
		// 		}
		// 		else
		// 		{
		// 			Select(11, 10, -1, 3, 11, 4, -1);
		// 		}
		g_pMainState->m_FangWu.SetGuiMo(1);
		g_pMainState->m_Tags.Add("房屋规模更改为1");
		return true;
	case 11:
		//		g_pMainState->m_State.switchAddPoint();
		g_pMainState->m_FangWu.SetGuiMo(2);
		g_pMainState->m_Tags.Add("房屋规模更改为2");
		return true;
	case 12:

	{
		//			g_pCharacter->m_PCData.ResetAddPoint(false);
		//			g_pMainState->m_State.switchAddPoint();
	}
		g_pMainState->m_FangWu.SetGuiMo(3);
		g_pMainState->m_Tags.Add("房屋规模更改为3");
		return true;
	case 13:
	{
// 		if (g_pMainState->m_FangWu.GetGuiMo() > 3)
// 		{
// 			AddTriggerDialog2(6);
// 			return true;
// 		}
// 		ostringstream oss;
// 		oss << "当前房屋规模为";
// 		oss << g_pMainState->m_FangWu.GetGuiMo();
// 		oss << "升级需要";
// 		oss << (g_pMainState->m_FangWu.GetGuiMo() + 1) * 200;
// 		oss << "万,需要吗?";
// 		g_pMainState->m_TriggerDialog.AddSelect(this, oss.str(), g_pMainState->m_pNowSelect->m_TrueName.GetString(), -1,
// 			m_Textlist[3], 14,
// 			m_Textlist[4], -1
// 			);

		g_pMainState->m_TriggerDialog.AddSelect(this, toString("当前房屋规模为: %d", g_pMainState->m_FangWu.GetGuiMo()), 
			g_pMainState->m_pNowSelect->m_TrueName.GetString(), -1,
			"更改规模为 1", 10,
			"更改规模为 2", 11,
			"更改规模为 3", 12,
			"更改规模为 4", 14);
	}
		return true;
	case 14:
		g_pMainState->m_FangWu.SetGuiMo(4);
		g_pMainState->m_Tags.Add("房屋规模更改为4");
		return true;
	case 15:
	      {
		
		
			  {//1
				  auto objSelect = g_pMainState->m_pNowSelect;
				  if (1)
				  {
					  auto pc = AddEnemy(150000, 2000+rand()%16, cct::MaxRoleLv, eMP_东海龙宫, "萌新草", nullptr, 160);
					  pc->AddSkill(ePS_高级法术连击);
					  pc->AddSkill(ePS_高级法术暴击);
					  pc->AddSkill(ePS_高级法术波动);
					  pc->AddSkill(ePS_高级魔之心);
					  pc->AddSkill(ePS_高级精神集中);
					  pc->AddSkill(ePS_神佑复生);
					  pc->AddSkill(ePS_高级再生);
					  pc->AddSkill(ePS_高级防御);
					  pc->AddSkill(ePS_高级幸运);
					  pc->AddSkill(ePS_高级敏捷);
 //					  pc->LiveRestoreRate += 50;
 					  pc->HitRateOfSeal.d2 += 30;
 					  pc->CounterRate.d1 += 100;
 					  pc->StabRate.d1 += 300;
 					  pc->StabPercent.d2 += 100;;
 					  pc->StabRateOfMagic.d1 += 100;
 					  pc->StabPercentOfMagic.d1 += 50;
					  pc->m_XiuLian.AddXiuLianLv(30, eXLMAG);
// 					  pc->Pierce刺穿.d2 += 120;
// 					  pc->DmgPercentOfMagic.d1 += 333;
// 					  pc->DmgPercentOfMagic.d2 += 333;
 					  pc->Pierce刺穿OfMagic.d1 += 50;
// 					  pc->Pierce刺穿OfMagic.d2 += 164;
// 					  pc->DmgPercent.d2 += 80;
// 					  pc->Pierce刺穿.d1 += 120;
// 					  pc->DmgPercent.d2 += 89;
					  g_pMainState->SetRanse(10, 5, 2, 1, 3);
					  pc->getObj()->say("#1少年，打赢我意想不到的收获哦#18");
					  g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
					  
				  }
				 
		{//2
			cPropertyData* Pet;
			Pet = AddEnemy(100000, 2000 + rand() % 16, 160, eMP_大唐官府, "萌新狼", nullptr, 160);
			Pet->m_XiuLian.AddXiuLianLv(30, eXLATK);
//			Pet->DmgPercent.d2 += 110;//攻击防御
			Pet->SuckBloodRate.d1 += 100;//吸血率
			Pet->SuckBloodPercent.d1 += 100;//吸血率
// 			Pet->DmgPercentOfMagic.d2 += 99;
 			Pet->Pierce刺穿.d1 += 80;
// 			Pet->DmgPercent.d2 += 59;
// 			Pet->Pierce刺穿.d2 += 59;
// 			Pet->DmgPercentOfMagic.d2 += 59;
// 			Pet->Pierce刺穿OfMagic.d2 += 59;
// 			Pet->DmgPercentOfFix.d2 -= 32;
			g_pMainState->SetRanse(11, 5, 2, 1, 3);
			g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
		}
	{//3
		cPropertyData* Pet;
		Pet = AddEnemy(100000, 2000 + rand() % 16, 160, eMP_化生寺, "萌新兔", nullptr, 160);
		Pet->m_XiuLian.AddXiuLianLv(30, eXLDEF);
//		Pet->DmgPercent.d2 += 110;
//		Pet->Pierce刺穿.d2 += 110;
//		Pet->DmgPercentOfMagic.d2 += 110;
//		Pet->Pierce刺穿OfMagic.d2 += 110;
//		Pet->DmgPercentOfFix.d2 -= 32;
		Pet->DmgPercentOfCure.d1 += 100;
		Pet->CriRateOfCure.d1 += 30;
		g_pMainState->SetRanse(12, 4, 2, 3, 3);
		g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
	}


	{//4
		cPropertyData* Pet;
		Pet = AddEnemy(100000, 2000 + rand() % 16, 160, eMP_凌波城, "萌新萌", nullptr, 160);
//		Pet->m_XiuLian.AddXiuLianLv(20, eXLATK);
//		Pet->DmgPercent.d2 += 140;//给怪物的防御和攻击
//	    Pet->MagicWater.d2 += 30;//水属性
		Pet->Pierce刺穿.d1 += 40;
//		Pet->DmgPercentOfMagic.d1 += 28;
//		Pet->DmgPercentOfMagic.d2 += 64;
//		Pet->Pierce刺穿OfMagic.d1 += 120;
//		Pet->Pierce刺穿OfMagic.d2 += 166;
		g_pMainState->SetRanse(13, 4, 2, 3, 3);
		g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
	}


	{//5
		auto pc = AddEnemy(100000, 2000 + rand() % 16, 160, eMP_五庄观, "呆萌如表弟", nullptr, 160);
//		pc->m_XiuLian.AddXiuLianLv(19, eXLATK);
		pc->AddSkill(ePS_高级鬼魂术);
		pc->HitRateOfSeal.d1 += 85;
		pc->HitRateOfSeal.d2 +=85;
//		pc->DmgPercentOfMagic.d2 += 99;//法抗
//		pc->Pierce刺穿OfMagic.d2 += 99;//法抗
		g_pMainState->SetRanse(14, 1, 2, 3, 3);
		pc->getObj()->say("#24");
		g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
	}
{//6
	auto pc = AddEnemy(90000, 2000 + rand() % 16, 150, eMP_凌波城, "天之蓝", nullptr, 160);
	pc->m_XiuLian.AddXiuLianLv(18, eXLATK);
	pc->_isWeakSeal = false;
	pc->DmgPercent.d2 += 35;//给怪物的防御和攻击
	pc->Pierce刺穿.d1 += 100;
	pc->HitRate.d2 += 50;
	pc->Evade.AddDataAddPercent(100);
	g_pMainState->SetRanse(15, 4, 2, 3, 3);
	pc->getObj()->say("无形之刃，最为致命。");
	g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
}
 {//7
	 auto pc = AddEnemy(90000, 2000 + rand() % 16, 150, eMP_盘丝岭, "海之魅", nullptr, 160);
	pc->m_XiuLian.AddXiuLianLv(18, eXLDMAG);
	pc->Pierce刺穿.d2 -= 99;
	pc->DmgPercent.d2 += 80;
// 	pc->DmgPercentOfMagic.d2 += 99;
// 	pc->DmgPercentOfMagic.d1 += 128;
// 	pc->DmgPercentOfMagic.d2 += 64;
// 	pc->DmgPercentOfMagic.d2 += 79;
	pc->Pierce刺穿OfMagic.d2 += 69;
	g_pMainState->SetRanse(16, 4, 2, 3, 3);
	pc->getObj()->say("我的剑刃不但准，而且狠！");
	g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
  }
	{//8
		auto pc = AddEnemy(90000, 2000 + rand() % 16, 150, eMP_狮驼岭, "人之初", nullptr, 160);
		pc->m_XiuLian.AddXiuLianLv(18, eXLATK);
		pc->AddSkill(ePS_高级必杀);
		pc->AddSkill(ePS_高级连击);
		pc->Pierce刺穿.d1 += 30;
		pc->DmgPercent.d2 += 80;
// 		pc->DmgPercentOfMagic.d2 += 99;
// 		pc->DmgPercentOfMagic.d1 += 128;
// 		pc->DmgPercentOfMagic.d2 += 64;
// 		pc->DmgPercentOfMagic.d2 += 79;
// 		pc->Pierce刺穿OfMagic.d2 += 69;
		g_pMainState->SetRanse(17, 4, 2, 3, 3);
		pc->getObj()->say("时间不站在你那边");
		g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
	}
	{//9
		auto pc = AddEnemy(90000, 2000 + rand() % 16, 150, eMP_普陀山, "疾风剑豪-亚索", nullptr, 160);
		pc->m_XiuLian.AddXiuLianLv(18, eXLDEF);
		pc->MagicWater.d2 += 100;
		pc->MagicFire.d2 += 100;
		pc->MagicSoil.d2 += 100;
		pc->MagicThunder.d2 += 100;
// 		pc->Pierce刺穿.d2 -= 50;
// 		pc->DmgAddOfCure.d2 += 120;
// 		pc->StabRateOfMagic.d1 += 110;
// 		pc->StabPercentOfMagic.d2 += 110;
// 		pc->DmgAddOfCure.d1 += 99;
// 		pc->DmgPercentOfMagic.d2 += 99;
// 		pc->DmgPercentOfMagic.d1 += 128;
// 		pc->DmgPercentOfMagic.d2 += 64;
// 		pc->DmgPercentOfMagic.d2 += 79;
// 		pc->Pierce刺穿OfMagic.d2 += 69;
		g_pMainState->SetRanse(18, 4, 2, 3, 3);
		pc->getObj()->say("面对疾风吧！");
		g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
	}


	{//10
		auto pc = AddEnemy(120000, 2000 + rand() % 16, 150, eMP_阴曹地府, "齐心", nullptr, 160);
		pc->LiveHp = 5000;//每回合回血
// 		pc->DmgPercent.d2 += 100;
// 		pc->Pierce刺穿.d2 -= 16;
		pc->Ghost.d1 += 5;
// 		pc->DmgPercentOfMagic.d2 += 99;
// 		pc->Pierce刺穿OfMagic.d2 += 89;
//		pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(30);
		g_pMainState->SetRanse(19, 4, 2, 3, 3);
		pc->getObj()->say("#17打赢奖高级书铁");
		g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);
	}

				  int c = 0;
				  for (int i = 10; i < 15; ++i)
				  {
					  if (g_pMainState->m_FightWorkList[i].isExist)
					  {
						  ++c;
					  }
				  }
				  if (c >= 3)
				  {
					
					  g_pMainState->m_InterfaceTeam.SetFormation(eFormation(1 + rand() % 10), true);
				  }


				 

				  g_StateType = STATE_FIGHT;
				  AddTriggerFightSuccess(16);
			  }
	     }
		return true;
		case 16:
			g_pMainState->awardBook(150);//书
			g_pMainState->awardIron(150);
			/////////////////////////////////////////////////////////////////////////////
			if (r < 10)//奖励代码段
			{

			if (r < 5)
			{
				g_pMainState->awardBook(100 + (rand() % 4 * 10));//书
				g_pMainState->awardItem(27, 42 + rand() % 9, 1, true);//阵书

			}
			else if (r > 5)
			{
				g_pMainState->awardIron(100 + (rand() % 4 * 10));//铁
				// g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石
			}
			else if (r <2)
			{
				g_pMainState->awardBook(150);//书
				g_pMainState->awardIron(150);//铁
				g_pMainState->awardk(666, 6666.666);//60W经验，100W钱
			}
			}
			else if (r < 20)
			{
				if (!g_pMainState->awardBookIron(10 * rand() % 16))
				{
					
					g_pMainState->awardShouJue1();
					g_pMainState->awardk(600, 1000);//60W经验，100W钱
				}
			}
			else if (r < 30)
			{
				g_pMainState->awardEquip(80);
				g_pMainState->awardItem(27, 42 + rand() % 9, 1, true);
				g_pMainState->awardk(600, 1000);//60W经验，100W钱
			}
			else if (r <90)
			{
				g_pMainState->awardk(600, 1000);//60W经验，100W钱
				g_pHeroObj->say("#15运气太差了");;
			}
			else if (r > 90)
			{
				g_pHeroObj->say("#15今天倒了血霉，啥也没得到");
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			return true;
 	case 17:
		
 	{
		
		auto pc = AddEnemy(100000, e蚩尤, 160, eMP_狮驼岭, "蚩尤");
		pc->LiveHp = 10000;//每回合回血高级再生
		pc->SetJinJie(3);
		g_pMainState->SetRanse(10, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->getObj()->say("#G感受绝望吧#18#G");
		pc->DmgPercent.d2 += 140;//给怪物的防御和攻击
		pc->Pierce刺穿.d1 += 120;
//		pc->DmgPercentOfMagic.d1 += 28;
		pc->DmgPercentOfMagic.d2 += 64;
//		pc->Pierce刺穿OfMagic.d1 += 120;
		pc->Pierce刺穿OfMagic.d2 += 166;



		pc = AddEnemy(90000, e持国巡守, 160, eMP_普陀山, "后土");
		pc->SetJinJie(3);
		g_pMainState->SetRanse(11, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
		pc->DmgPercent.d2 += 99;//物理
		pc->Pierce刺穿.d2 += 99;//物理
//		pc->DmgPercentOfMagic.d1 += 28;//灵力
		pc->DmgPercentOfMagic.d2 += 24;//灵力
		pc->Pierce刺穿OfMagic.d2 += 99;
		pc->DmgPercentOfFix.d2 -= 32;//怕固伤


		 pc = AddEnemy(90000, e毗舍童子, 160, eMP_化生寺, "搻兹");
		pc->SetJinJie(3);
		g_pMainState->SetRanse(12, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
//		pc->DmgPercentOfMagic.d1 += 30;//+灵力
		pc->DmgPercent.d2 += 100;//物抗
		pc->Pierce刺穿.d2 += 100;//物抗
		pc->DmgPercentOfMagic.d2 += 99;//法抗
		pc->Pierce刺穿OfMagic.d2 += 99;//法抗
		pc->DmgPercentOfFix.d2 -= 35;//怕固伤




		 pc = AddEnemy(90000, e蜃气妖, 160, eMP_阴曹地府, "奢比尸");
		
		pc->SetJinJie(3);
		g_pMainState->SetRanse(13, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
		pc->DmgPercent.d2 += 100;
		pc->Pierce刺穿.d2 -= 16;
		pc->Ghost.d1 += 5;
		pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(30);
		pc->applyXL();


		 pc = AddEnemy(60000, e真陀护法, 160, eMP_方寸山, "玄冥");
		pc->SetJinJie(3);
		g_pMainState->SetRanse(14, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->ParryRateOfMaigc.d1 += 5;
		pc->LiveHp = 5000;//每回合回血
		pc->_isWeakSeal = false;
		pc->DmgPercent.d2 += 50;
		pc->Pierce刺穿.d2 -= 100;
		pc->Pierce刺穿OfMagic.d2 -= 100;
		pc->HitRate.d2 += 50;
		pc->Evade.AddDataAddPercent(800);
		pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(25);
		pc->applyXL();

		 pc = AddEnemy(70000, e吸血鬼, 160, eMP_大唐官府, "天吴");//数据很好
		pc->SetJinJie(3);
		pc->CriRate.d1 += 20;
		g_pMainState->SetRanse(15, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
		pc->_isWeakSeal = false;
		pc->DmgPercent.d2 += 120;//给怪物的防御和攻击
		pc->Pierce刺穿.d1 += 100;
		pc->HitRate.d2 += 50;
		pc->Evade.AddDataAddPercent(100);
		pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(25);
		pc->applyXL();


		 pc = AddEnemy(70000, e巨力神猿, 160, eMP_大唐官府, "强良");
		pc->SetJinJie(3);
		g_pMainState->SetRanse(16, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
		pc->_isWeakSeal = false;
		pc->DmgPercent.d2 += 120;//给怪物的防御和攻击
		pc->Pierce刺穿.d1 += 110;
		pc->HitRate.d2 += 20;
		pc->Evade.AddDataAddPercent(30);
		pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(23);
		pc->applyXL();

		 pc = AddEnemy(70000, e雾中仙, 160, eMP_东海龙宫, "共工");
		pc->SetJinJie(3);
		pc->DmgAdd.d1 += 50;//每回合回血
		g_pMainState->SetRanse(17, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
		pc->Pierce刺穿.d2 -= 99;
		pc->DmgPercent.d2 += 80;
		pc->DmgPercentOfMagic.d2 += 99;
		pc->DmgPercentOfMagic.d1 += 128;
		pc->DmgPercentOfMagic.d2 += 64;
		pc->Pierce刺穿OfMagic.d1 += 20;
		pc->Pierce刺穿OfMagic.d2 += 64;

		pc = AddEnemy(60000, e雨师, 160, eMP_魔王寨, "祝融");
		pc->SetJinJie(3);
		g_pMainState->SetRanse(18, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->StabPercent.d1 += 50;//每回合回血
		pc->LiveHp = 5000;//每回合回血
		//pc->Pierce刺穿.d2 -= 50;
		pc->DmgPercentOfMagic.d2 += 69;
		pc->DmgPercentOfMagic.d1 += 128;
		pc->DmgPercentOfMagic.d2 += 64;
		pc->Pierce刺穿OfMagic.d1 += 20;
		pc->Pierce刺穿OfMagic.d2 += 64;

		pc = AddEnemy(60000, e律法女娲, 160, eMP_凌波城, "蓐收");
		pc->SetJinJie(3);
		g_pMainState->SetRanse(19, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->HitRate.d2 +=60 ;//每回合回血
		pc->LiveHp = 5000;//每回合回血
		pc->DmgPercent.d2 += 159;
		pc->Pierce刺穿.d1 += 60;
		pc->DmgPercentOfMagic.d2 += 99;
		pc->DmgPercentOfMagic.d2 += 34;//灵力
		pc->Pierce刺穿OfMagic.d2 += 39;
		pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(35);
		pc->applyXL();


		int c = 0;
		for (int i = 10; i < 15; ++i)
		{
			if (g_pMainState->m_FightWorkList[i].isExist)
			{
				++c;
			}
		}
		if (c >= 3)
		{
			g_pMainState->m_InterfaceTeam.SetFormation(eFormation(1 + rand() % 10), true);
		}
		g_StateType = STATE_FIGHT;
 
 		AddTriggerFightSuccess(37);//跳转蚩尤奖励
 	}
 		return true;
 	case 18:
	{//1
		auto objSelect = g_pMainState->m_pNowSelect;
		if (1)
		{
			auto pc = AddEnemy(100000, 镜主, 180, eMP_狮驼岭, "盘古", nullptr, 180);
			pc->m_XiuLian.AddXiuLianLv(30, eXLATK);
			g_pMainState->SetRanse(10, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
			//pc->getObj()->say("#17少年，打赢我意想不到的收获哦#24");
			pc->AddSkill(ePS_高级精神集中);
			pc->AddSkill(ePS_神佑复生);
			pc->AddSkill(ePS_高级再生);
			pc->AddSkill(ePS_高级防御);
			pc->AddSkill(ePS_高级幸运);
			pc->AddSkill(ePS_高级敏捷);
			pc->AddSkill(ePS_高级必杀);
			pc->AddSkill(ePS_高级夜战);
			pc->AddSkill(ePS_高级连击);
			pc->DmgPercent.d2 += 150;//给怪物的防御和攻击
			pc->Pierce刺穿.d1 += 130;
			pc->DmgPercentOfMagic.d1 += 38;
			pc->DmgPercentOfMagic.d2 += 74;
			pc->Pierce刺穿OfMagic.d1 += 130;
			pc->Pierce刺穿OfMagic.d2 += 176;
			g_pMainState->m_ColorManage.Give2(&pc->m_RanSe.m_ranse[0], pc->modeid);

		}

		{//2
			cPropertyData* Pet;
			Pet = AddEnemy(90000, e知了王, 160, eMP_天宫, "伏羲", nullptr, 160);
			Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
			Pet->_isWeakSeal = false;
			Pet->DmgPercent.d2 += 120;//给怪物的防御和攻击
			Pet->Pierce刺穿.d1 += 100;
			Pet->HitRate.d2 += 50;
			Pet->Evade.AddDataAddPercent(100);
			Pet->applyXL();
			//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
			g_pMainState->SetRanse(11, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
			g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
		}
		{//2
			cPropertyData* Pet;
			Pet = AddEnemy(90000, e灵符女娲, 160, eMP_魔王寨, "人王", nullptr, 160);
			Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
			//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
			Pet->DmgPercentOfMagic.d2 += 69;
			Pet->DmgPercentOfMagic.d1 += 128;
			Pet->DmgPercentOfMagic.d2 += 64;
			Pet->Pierce刺穿OfMagic.d1 += 20;
			Pet->Pierce刺穿OfMagic.d2 += 64;
			g_pMainState->SetRanse(12, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
			g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
		}
	{//2
		cPropertyData* Pet;
		Pet = AddEnemy(90000, e净瓶女娲, 160, eMP_普陀山, "女蜗", nullptr, 160);
		Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
		//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
		Pet->DmgPercent.d2 += 100;
		Pet->Pierce刺穿.d2 -= 16;
		Pet->Ghost.d1 += 5;
		Pet->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(30);
		g_pMainState->SetRanse(13, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
	}

{//2
	cPropertyData* Pet;
	Pet = AddEnemy(90000, e炎魔神, 160, eMP_魔王寨, "东王太一", nullptr, 160);
	Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
	//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
	Pet->Pierce刺穿.d2 -= 99;
	Pet->DmgPercent.d2 += 80;
	Pet->DmgPercentOfMagic.d2 += 99;
	Pet->DmgPercentOfMagic.d1 += 128;
	Pet->DmgPercentOfMagic.d2 += 64;
	Pet->Pierce刺穿OfMagic.d1 += 20;
	Pet->Pierce刺穿OfMagic.d2 += 64;
	g_pMainState->SetRanse(14, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
}
{//2
	cPropertyData* Pet;
	Pet = AddEnemy(90000, e大力金刚, 160, eMP_东海龙宫, "黄帝", nullptr, 160);
	Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
	//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
	Pet->Pierce刺穿.d2 -= 99;
	Pet->DmgPercent.d2 += 80;
	Pet->DmgPercentOfMagic.d2 += 99;
	Pet->DmgPercentOfMagic.d1 += 128;
	Pet->DmgPercentOfMagic.d2 += 64;
	Pet->Pierce刺穿OfMagic.d1 += 20;
	Pet->Pierce刺穿OfMagic.d2 += 64;
	g_pMainState->SetRanse(15, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
}
{//2
	cPropertyData* Pet;
	Pet = AddEnemy(90000, e大力金刚, 160, eMP_盘丝岭, "刑天", nullptr, 160);
	Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
	//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
	g_pMainState->SetRanse(16, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
	g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
}



		{//2
			cPropertyData* Pet;
			Pet = AddEnemy(90000, e大力金刚, 160, eMP_凌波城, "烛九阴", nullptr, 160);
			Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
			Pet->_isWeakSeal = false;
			Pet->DmgPercent.d2 += 120;//给怪物的防御和攻击
			Pet->Pierce刺穿.d1 += 100;
			Pet->HitRate.d2 += 50;
			Pet->Evade.AddDataAddPercent(100);
			Pet->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(25);
			Pet->applyXL();
			//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
			g_pMainState->SetRanse(17, rand() % 5);
			g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
		}
				{//2
					cPropertyData* Pet;
					Pet = AddEnemy(90000, e大力金刚, 160, eMP_化生寺, "六道仙人", nullptr, 160);
					Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
					//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
					Pet->DmgPercentOfMagic.d1 += 40;//+灵力
					Pet->DmgPercent.d2 += 110;//物抗
					Pet->Pierce刺穿.d2 += 110;//物抗
					Pet->DmgPercentOfMagic.d2 += 119;//法抗
					Pet->Pierce刺穿OfMagic.d2 += 119;//法抗
					Pet->DmgPercentOfFix.d2 -= 45;//怕固伤
					g_pMainState->SetRanse(18, rand() % 5, rand() % 5);
					g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
				}
				{//2
					cPropertyData* Pet;
					Pet = AddEnemy(90000, e大力金刚, 160, eMP_大唐官府, "昊天", nullptr, 160);
					Pet->m_XiuLian.AddXiuLianLv(25, eXLATK);
					//Pet->m_RanSe.m_ranse[1].Set(2, 3, 1, 3); //人物染色
					Pet->_isWeakSeal = false;
					Pet->DmgPercent.d2 += 120;//给怪物的防御和攻击
					Pet->Pierce刺穿.d1 += 100;
					Pet->HitRate.d2 += 50;
					Pet->Evade.AddDataAddPercent(100);
					Pet->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(25);
					Pet->applyXL();
					g_pMainState->SetRanse(19, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
					g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
				}
		g_pMainState->m_InterfaceTeam.SetFormation(tiger, true);//阵型代码
			SetMusic("长安城");
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(37);
		}
		return true;
 	case 19:

	{

		auto pc = AddEnemy(80000, 蜈蚣, 160, eMP_狮驼岭, "蜈蚣精");
		pc->LiveHp = 10000;//每回合回血高级再生
		pc->AddSkill(ePS_高级夜战);
		pc->AddSkill(ePS_高级精神集中);
		pc->AddSkill(ePS_神佑复生);
		pc->AddSkill(ePS_高级再生);
		pc->AddSkill(ePS_高级防御);
		pc->AddSkill(ePS_高级反击);
		pc->AddSkill(ePS_高级吸血);
		pc->AddSkill(ePS_高级感知);
		pc->AddSkill(ePS_弱点雷);
		pc->AddSkill(ePS_高级强力);
		pc->AddSkill(ePS_吸星大法);
		pc->AddSkill(ePS_嗜血追击);
		pc->AddSkill(ePS_高级幸运);
		pc->AddSkill(ePS_高级敏捷);
		pc->AddSkill(ePS_高级敏捷);
		pc->SetJinJie(3);
		pc->DmgPercent.d2 += 130;//给怪物的防御和攻击
		pc->Pierce刺穿.d1 += 120;
		pc->DmgPercentOfMagic.d1 += 38;
		pc->DmgPercentOfMagic.d2 += 74;
		pc->Pierce刺穿OfMagic.d1 += 130;
		pc->Pierce刺穿OfMagic.d2 += 176;
		g_pMainState->SetRanse(10, rand() % 5, rand() % 5, rand() % 5, rand() % 5);

		pc = AddEnemy(60000, e混沌兽, 160, eMP_普陀山, "义兄");
		pc->SetJinJie(3);
		pc->AddSkill(ePS_高级幸运);
		pc->AddSkill(ePS_高级敏捷);
		pc->DmgPercentOfMagic.d1 += 30;//+灵力
		pc->DmgPercent.d2 += 100;//物抗
		pc->Pierce刺穿.d2 += 100;//物抗
		pc->DmgPercentOfMagic.d2 += 99;//法抗
		pc->Pierce刺穿OfMagic.d2 += 99;//法抗
		pc->DmgPercentOfFix.d2 -= 35;//怕固伤
		g_pMainState->SetRanse(11, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
		pc = AddEnemy(60000, e混沌兽, 160, eMP_化生寺, "捣蛋妖");
		pc->SetJinJie(3);
		pc->AddSkill(ePS_高级再生);
		pc->AddSkill(ePS_高级防御);
		pc->DmgPercentOfMagic.d1 += 30;//+灵力
		pc->DmgPercent.d2 += 100;//物抗
		pc->Pierce刺穿.d2 += 100;//物抗
		pc->DmgPercentOfMagic.d2 += 99;//法抗
		pc->Pierce刺穿OfMagic.d2 += 99;//法抗
		pc->DmgPercentOfFix.d2 -= 35;//怕固伤
		g_pMainState->SetRanse(12, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
		pc = AddEnemy(60000, e混沌兽, 160, eMP_阴曹地府, "妖仙");
		pc->AddSkill(ePS_高级法术连击);
		pc->AddSkill(ePS_高级法术暴击);
		pc->Pierce刺穿.d2 -= 99;
		pc->DmgPercent.d2 += 80;
		pc->DmgPercentOfMagic.d2 += 99;
		pc->DmgPercentOfMagic.d1 += 128;
		pc->DmgPercentOfMagic.d2 += 64;
		pc->Pierce刺穿OfMagic.d1 += 20;
		pc->Pierce刺穿OfMagic.d2 += 64;
		pc->SetJinJie(3);
		g_pMainState->SetRanse(13, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->LiveHp = 5000;//每回合回血
		pc = AddEnemy(50000, e混沌兽, 160, eMP_方寸山, "捣蛋妖");
		pc->SetJinJie(3);
		pc->AddSkill(ePS_高级法术波动);
		pc->AddSkill(ePS_高级魔之心);
		pc->DmgPercent.d2 += 50;
		pc->Pierce刺穿.d2 -= 100;
		pc->Pierce刺穿OfMagic.d2 -= 100;
		pc->HitRate.d2 += 50;
		pc->Evade.AddDataAddPercent(800);
		pc->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(25);
		pc->applyXL();
		g_pMainState->SetRanse(14, rand() % 5, rand() % 5, rand() % 5, rand() % 5);
		pc->ParryRateOfMaigc.d1 += 5;
		
		int c = 0;
		for (int i = 10; i < 15; ++i)
		{
			if (g_pMainState->m_FightWorkList[i].isExist)
			{
				++c;
			}
		}
		if (c >= 3)
		{
			g_pMainState->m_InterfaceTeam.SetFormation(eFormation(1 + rand() % 10), true);
		}
		g_StateType = STATE_FIGHT;

		AddTriggerFightSuccess(37);//跳转蚩尤奖励
	}
		return true;

// //		return true;
// 	{
// 		if (g_pCharacter->m_PcData.m_FightPetID == -1)return true;
// 		cPropertyData& Pet = g_pCharacter->m_PcData.m_pPets[g_pCharacter->m_PcData.m_FightPetID]->m_PetData;
// 		ostringstream oss;
// 		switch (Pet.m_JinJieNum.m_JinJieNum)
// 		{
// 		case 0:
// 		case 1:
// 		case 2:
// 			oss << "你的出战召唤兽离下次进阶还需" << (Pet.m_JinJieNum.m_JinJieNum + 1) * 2000000 << "(明明可以免费自由进阶)";
// 			break;
// 		default:
// 			oss << "你的出战召唤兽已经无法再进阶了";
// 			break;
// 		}
// 		m_pObj = g_pMainState->m_pNowSelect;
// 		g_pMainState->m_TriggerDialog.AddSelect(this, oss.str(), m_pObj->m_TrueName.GetString(), -1,
// 			m_Textlist[3], 20,
// 			m_Textlist[4], -1);
// 	}
// 		break;
// 	case 20:
// 
// 	{
// 		if (g_pCharacter->m_PcData.m_FightPetID == -1)return true;
// 		cPropertyData& Pet = g_pCharacter->m_PcData.m_pPets[g_pCharacter->m_PcData.m_FightPetID]->m_PetData;
// 		if (g_pCharacter->m_PcData.AddMoney(-(Pet.m_JinJieNum.m_JinJieNum + 1) * 2000000, 0, 0, 0))
// 		{
// 			Pet.SetJinJie(1);
// 			m_pObj->Talk("进阶成功");
// 			g_pMainState->m_PCHead.UpdatePet();
// 		}
// 		else m_pObj->Talk("钱不够");
// 	}
 		break;
		
	case 21:
	{
		// 百兽王
// 		m_pObj = g_pMainState->m_pNowSelect;
// 		g_pMainState->m_TriggerDialog.AddSelect(this, "领取坐骑"/*m_Textlist[13]*/, m_pObj->m_TrueName.GetString(), -1,
// 			m_Textlist[3], 22,
// 			m_Textlist[4], -1);
		g_pMainState->m_TriggerDialog.AddSelect(this, "领取坐骑", 22);
	}
		break;
	case 22:
	{
		vector<int> lis;
		g_pMainState->m_ZuoQi.GetShiPei(lis, g_pCharacter->m_PcData.modeid);
		if (lis.size() && g_pCharacter->m_PcData.AddMoney(-10000, 0, 0, 0))
		{
			g_pMainState->m_ZuoQi.GetZuoQi(g_pCharacter->m_PcData, lis[rand() % lis.size()]);
			m_pObj->Talk("得到了坐骑");
		}
		else m_pObj->Talk("角色不符or钱不够");
	}
		break;
// 	case 23:
// 	{
// 		// 五宝
// 		bool bhave[5] = { 0 };
// 		for (int i = 0; i < 60; i++)
// 		{
// 			if (27 == g_pCharacter->m_PcData.m_Items[i].GetType())
// 			{
// 				switch (g_pCharacter->m_PcData.m_Items[i].GetID())
// 				{
// 				case 6:bhave[0] = true; break;
// 				case 7:bhave[1] = true; break;
// 				case 8:bhave[2] = true; break;
// 				case 9:bhave[3] = true; break;
// 				case 10:bhave[4] = true; break;
// 				default:break;
// 				}
// 			}
// 		}
// 		for (int i = 0; i < 5; i++)
// 		{
// 			if (!bhave[i])
// 			{
// 				AddTriggerDialog2(10);
// 				return true;
// 			}
// 		}
// 		for (int i = 0; i < 60; i++)
// 		{
// 			if (27 == g_pCharacter->m_PcData.m_Items[i].GetType())
// 			{
// 				switch (g_pCharacter->m_PcData.m_Items[i].GetID())
// 				{
// 				case 6:
// 					if (bhave[0])
// 					{
// 						bhave[0] = 0;
// 						g_pCharacter->m_PcData.m_Items[i].m_Num -= 1;
// 					}
// 					break;
// 				case 7:
// 					if (bhave[1])
// 					{
// 						bhave[1] = 0;
// 						g_pCharacter->m_PcData.m_Items[i].m_Num -= 1;
// 					}
// 					break;
// 				case 8:
// 					if (bhave[2])
// 					{
// 						bhave[2] = 0;
// 						g_pCharacter->m_PcData.m_Items[i].m_Num -= 1;
// 					}
// 					break;
// 				case 9:
// 					if (bhave[3])
// 					{
// 						bhave[3] = 0;
// 						g_pCharacter->m_PcData.m_Items[i].m_Num -= 1;
// 					}
// 					break;
// 				case 10:
// 					if (bhave[4])
// 					{
// 						bhave[4] = 0;
// 						g_pCharacter->m_PcData.m_Items[i].m_Num -= 1;
// 					}
// 					break;
// 				default:break;
// 				}
// 			}
// 		}
// 		SetJiangLiItem(23, 28);
// 	}
// 		break;
// 	case 24:Select(14, 15, -1, 3, 25, 4, -1); break;
// 	case 25:
// 		if (g_pCharacter->m_PcData.AddMoney(-1000000, 0, 0, false))
// 		{
// //			g_pCharacter->m_PcData.Add人气(10);
// 		}
// 		else g_pMainState->m_Tags.Add("钱不够");
// 		break;
// 	case 26:
// 	{
// 		int moneyneed;
// 		if (g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5].isExist)
// 		{
// 			cPet* Pet = (cPet*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5].m_pObj->m_pIndex;
// 			moneyneed = 10000 * (Pet->m_PetData.m_Lv/* - Pet->m_PetData.m_FuZhuSkillLvList[0]*/);
// 		}
// 		else moneyneed = -1;
// 		ostringstream oss;
// 		oss << m_Textlist[17];
// 		if (moneyneed > -1)
// 			oss << "(需要#R" << moneyneed << "#R钱)";
// 		else
// 			oss << "你现在没有出战召唤兽";
// 		g_pMainState->m_TriggerDialog.AddSelect(this, oss.str(), m_Textlist[16], -1,
// 			"强化", 27,
// 			m_Textlist[21], -1
// 			/*		m_Textlist[19], 28,
// 			m_Textlist[20], 29,
// 			m_Textlist[21], -1*/
// 			);
// 	}
// 		break;
// 	case 27:
// 	case 28:
// 	case 29:
// 		// 		if (g_pMainState->m_FightList[g_pMainState->m_HeroID + 5].isExist)
// 		// 		{
// 		// 			cPet* Pet = (cPet*)g_pMainState->m_FightList[g_pMainState->m_HeroID + 5].m_pData->m_pIndex;
// 		// 			int lvadd = Pet->m_PetDataZZ.m_Lv - Pet->m_PetDataZZ.m_FuZhuSkillLvList[0];
// 		// 			int moneyneed = 10000 * lvadd;
// 		// 			if (lvadd<1)
// 		// 			{
// 		// 				g_pMainState->m_Tags.Add("召唤兽需要升级才能继续强化");
// 		// 				return true;
// 		// 			}
// 		// 			if (g_pCharacter->m_PCData.AddMoney(-moneyneed, 0, 0, false))
// 		// 			{		
// 		//  				for (int i = 0; i < 3;i++)
// 		//  					Pet->m_PetDataZZ.lvUpFuZhuSkill(lvadd, i);
// 		// 			}
// 		// 			else g_pMainState->m_Tags.Add("钱不够");
// 		// 		}
// 		// 		else g_pMainState->m_Tags.Add("没有出战召唤兽");
// 		break;
//  	case 30:
// 		if (g_pCharacter->m_PcData.m_Lv < 60)
// 			g_pMainState->m_LearnBangPaiSkill.OnOff(true);
// 		else
// 			g_pMainState->m_pNowSelect->Talk("我只帮新人(60级以下的)");
// 		break;
	case 31:
		g_pMainState->_uiFoot2.OnOff(true);
		break;
	case 32:
		g_pMainState->_uiFoot.OnOff(true);
		break;
	case 33:
		g_pMainState->_uiXiangRui.OnOff(true);
		break;
	case 34:
		g_pMainState->_uiAnimalSign.OnOff(true);
		break;
	case 35:
		g_pMainState->_uiHeadTop.OnOff(true);
		break;
	case 36:
	{
		// 影子
		if (g_StateType != STATE_MAIN)return false;
		ccm::get()->PKinit();
		ccm::get()->PK();
		string musicname = "战斗比武";
		musicname += toString("%d", 2 + rand() % 4);
		g_pMainState->m_Mp3.Load(musicname);
		if (g_pMainState->m_InterfaceTeam.getLeaveBegin() >= 3)
		{
			g_pMainState->m_InterfaceTeam.SetFormation(g_pMainState->m_InterfaceTeam.m_eOurFormation, true);
		}
		AddTriggerFightSuccess(37);
//		AddTriggerFightFalse(37);
//		AddTriggerFightEscape(37);
		g_StateType = STATE_FIGHT_MUSIC;
	}
		break;
	case 37://心魔奖励
		if (r < 10)//奖励代码段
		{

			if (r < 5)
			{
				g_pMainState->awardBook(100 + (rand() % 4 * 10));//书
				g_pMainState->awardItem(27, 42 + rand() % 9, 1, true);//阵书

			}
			else if (r > 5)
			{
				g_pMainState->awardIron(100 + (rand() % 4 * 10));//铁
				// g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石
			}
			else if (r <2)
			{
				g_pMainState->awardBook(150);//书
				g_pMainState->awardIron(150);//铁
				g_pMainState->awardk(666, 6666.666);//60W经验，100W钱
			}
		}
		else if (r < 20)
		{
			if (!g_pMainState->awardBookIron(10 * rand() % 16))
			{
				
				g_pMainState->awardShouJue1();
				g_pMainState->awardItem(32 + rand() % 2, 7 + rand() % 4, 1, true);
				g_pMainState->awardk(600, 500);//60W经验，50W钱
			}
		}
		else if (r < 30)
		{
	
			g_pMainState->awardItem(27, 42 + rand() % 9, 1, true);
			g_pMainState->awardk(600, 1000);//60W经验，100W钱
		}
		else if (r <90)
		{
			g_pMainState->awardk(600, 1000);//60W经验，100W钱
			g_pHeroObj->say("#15运气太差了");;
		}
		else if (r > 90)
		{
			g_pHeroObj->say("#15今天倒了血霉，啥也没得到");
		}
		ccm::get()->PKover();
		break;
	case 38://心魔奖励
		ccm::get()->PKover();
		break;
	case 0:
	case 69:
	case 89:
	case 109:
	case 129:
	case 159:
	case cct::MaxRoleLv:
		g_pMainState->m_ZhiXian3.Process(stage);
		break;
	default:
// 		if (stage == 31)
// 		{
// 			g_pMainState->m_ZhiXian3.Process(0);
// 		}
// 		else if (stage >(1 << 24))
// 		{
// 			g_pMainState->m_ZhiXian3.Process(stage);
// 		}
// 		else
// 		{
// 			ERRBOX;
// 		}
//		g_pMainState->m_pNowSelect->Talk(g_pMainState->m_TaskNormal.getNews());
		break;
	}
	return true;
}



bool cTaskZhiXian::Process1(int stage)
{
//	g_pMainState->m_pNowSelect->Talk(g_pMainState->m_TaskNormal.getNews());
	return true;
	if (stage < 0)return true;
	AddTriggerDialog2(stage);
	return true;
}



bool cTaskZhiXian::Process2(int stage)
{
//	g_pMainState->m_pNowSelect->Talk(g_pMainState->m_TaskNormal.getNews());
	return true;
	if (stage < 0)return true;
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
				SetINT(12, 0);
				AddTriggerDialog2(-stage);
				SetJiangLiItem(4, 40);
			}
			else
			{
				AddTriggerDialog2(-stage - 100);
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
	return true;
}




bool cTaskZhiXian::Process3(int stage)
{
	g_pMainState->m_pNowSelect->Talk("空空如也");
	g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect, true);
	return true;
	//宝箱
	int baoxiangid;
	int baoxiangindex;
	GetBaoXiangID(stage, baoxiangid, baoxiangindex);
	SetINT(baoxiangid, baoxiangindex);
	// 100 + stage / 30;
	switch (stage)
	{
	case -1:
		return true;
		//东海海底
	case 0:SetJiangLiItem(0, 32); break;
	case 1:SetJiangLiItem(0, 33); break;
		//沉船
	case 2:SetJiangLiItem(0, 34); break;
		//东海岩洞
	case 3:SetJiangLiItem(2, 22, 10); break;
	case 4:SetJiangLiItem(0, 23, 30); break;
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
		SetJiangLi(1, 0, 0, 0, 100, 50); break;
	case 16:
		SetJiangLi2(500); break;
	case 17:
		SetJiangLiItem(3, 24);
		break;
	case 18:
		SetJiangLiItem(77, 40);
		break;
	default:
		break;
	}
	g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect, true);
	return true;
}



void cTaskZhiXian::GetBaoXiangID(int type, int& id, int& index)
{
	//宝箱对应的脚本号
	id = 100 + type / 30;
	index = type % 30;
}



bool cTaskZhiXian::Process4(int stage)
{
	if (stage == -1)return true;
	if (stage < 300)
	{//商店
		g_pMainState->m_InterFaceBuy.Open(stage);
		return true;
	}
	switch (stage)
	{
	case -1:return true;
	default:ERRBOX;
		break;

	}
	return true;
}




void cTaskZhiXian::ProcessSelect(int stage)
{
	m_pObj = g_pMainState->m_pNowSelect;
	g_pMainState->m_TriggerDialog.AddSelect(this, m_Textlist[stage], g_pMainState->m_pNowSelect->m_TrueName.GetString(), -1,
		"确定", stage,
		"取消", -1
		);
}



bool cTaskZhiXian::Process6(int stage)
{
	return true;
	switch (stage)
	{
	case -1:return true;
	case 0:Select(2, 1, -1, 3, 1, 4, 2, 5, 3); break;
	case 1:
	case 2:
	case 3:

	{
		// 			int& k = g_pMainState->m_GlobalButton[0];
		// 			switch (stage)
		// 			{
		// 			case 1:
		// 				if (k <= 50)g_pCharacter->m_PCData.GoldLivePercent.d1 -= 100;
		// 				k = 100; 
		// 				g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(true);
		// 				break;
		// 			case 2:
		// 				if (k<=50)g_pCharacter->m_PCData.GoldLivePercent.d1 -= 100;
		// 				k = 80; 	
		// 				g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(false);
		// 				break;
		// 			case 3:
		// 				if (k > 50)g_pCharacter->m_PCData.GoldLivePercent.d1 += 100;
		// 				k = 50;
		// 				g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(false);
		// 				break;
		// 			}
	}
		break;
	default:
		ERRBOX;
		break;
	}
	return true;
}




bool cTaskZhiXian3::Process(int stage)
{
	switch (stage)
	{
	case -1:
//		m_bPK = false;
		ccm::get()->PKover();
//		g_pMainState->m_InterfaceTeam.SetFormation(m_eOurFormation, true);
		if(1)
		{
			g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect, true);
		}
		if (0)
		{
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
				g_pMainState->m_FightWorkList[i].m_pObj = m_PreFighter[i];
				g_pMainState->m_FightWorkList[i].isExist = m_islive[i];
			}
			swap(m_prehard, g_GlobalValues[0]);


			g_pMainState->m_InterfaceTeam.SetFormation(m_eOurFormation, 0, true);
			g_pMainState->SetCharacter(g_pMainState->m_HeroID);
			g_pMainState->m_PCHead.UpDateHead();
			g_pMainState->FindObj();
		}
		break;
	default:
//		if (stage > (1 << 24))
		{
			if (g_StateType != STATE_MAIN)return false;
			ccm::get()->PKinit();
			ccm::get()->PK(stage);
			if (0)
			{
				string path1;
				ifstream File;

				int userid, enemyid;
				File >> userid;
				File >> enemyid;
				File.close();
				for (int i = 0; i < 10; i++)
				{
					m_PreFighter[i] = g_pMainState->m_FightWorkList[i].m_pObj;
					g_pMainState->m_FightWorkList[i].m_pObj = m_pFighter[i];
					m_islive[i] = g_pMainState->m_FightWorkList[i].isExist;
					g_pMainState->m_FightWorkList[i].isExist = true;
					g_pMainState->m_FightWorkList[i].m_SkillPreSelect.SkillID = -1;
				}


				swap(m_prehard, g_GlobalValues[0]);
				m_eOurFormation = g_pMainState->m_InterfaceTeam.m_eOurFormation;
				if (!LoadTeam(userid, path1, false))return false;
				if (!LoadTeam(enemyid, path1, true))return false;
			}

			int c = 0;
			for (int i = 10; i < 15; ++i)
			{
				if (g_pMainState->m_FightWorkList[i].isExist)
				{
					++c;
				}
			}
			if (c >= 3)
			{
				g_pMainState->m_InterfaceTeam.SetFormation(eFormation(1 + rand() % 10), true);
			}
			string musicname = "战斗比武";
			musicname += toString("%d", 2 + rand() % 4);
			g_pMainState->m_Mp3.Load(musicname);
			g_StateType = STATE_FIGHT_MUSIC;
			AddTriggerFightSuccess(-1);
			AddTriggerFightFalse(-1);
			AddTriggerFightEscape(-1);
		}
		break;
	}
	return true;
}



void cTaskZhiXian3::Init2()
{
	if (m_bInit2)return;
	m_bInit2 = true;
	for (int i = 0; i < 10; i++)
	{
		m_pFighter[i] = new cObj;
		m_pFighter[i]->Init();
		m_pFighter[i]->m_IDInFightlist = i;
	}
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
















bool cTaskZhiXian3::LoadTeam(int id, string path, bool bEnemy)

{
	int startid = 0;
	if (bEnemy)
	{
		startid = 10;
	}
// 	ifstream File;
// 	ostringstream oss;
// 	string name, path2, path3;
// 	for (int i = 0; i < 5; i++)
// 	{
// 		oss.str("");
// 		oss << path;
// 		oss << id << "\\";
// 		path2 = oss.str();
// 		oss.str("");
// 		oss << i;
// 		name = oss.str();
// 		if (!File)
// 		{
// 			Process(-1);
// 			return false;
// 		}
// 		g_pMainState->m_FightWorkList[startid + i].m_pObj->LoadCharacter(name, path2);
// 
// 		g_pMainState->m_FightWorkList[startid + i].isExist = true;
// 	}
// 	oss.str("");
// 	oss << path;
// 	oss << id << "\\index.txt";
// 	File.open(oss.str());
// 	if (!File)
// 	{
// 		Process(-1);
// 		return false;
// 	}
// 	//阵形
// 	int formation;
// 	File >> formation;
// 	g_pMainState->m_InterfaceTeam.SetFormation((eFormation)formation, bEnemy);
// 	string dustbin;
// 	getline(File, dustbin);
// 	//召唤兽
// 	cPet* pet;
// 	cCharacter* pc;
// 	ifstream File2;
// 	int num;
// 	for (int i = 0; i < 5; i++)
// 	{
// 		pc = (cCharacter*)g_pMainState->m_FightWorkList[startid + i].m_pObj->m_pIndex;
// 		File >> num;
// 		int weapontype;
// 		int weaponid = 0;
// 		File >> weapontype;
// 		if (weapontype > -1)
// 		{
// 			File >> weaponid;
// 		}
// 		string petfilename;
// 		int positonid;
// 		for (int i2 = 0; i2 < num; i2++)
// 		{
// 			File >> petfilename;
// 			File >> positonid;
// 			pet = new cPet;
// 			oss.str("");
// 			oss << path;
// 			oss << id << "\\";
// 			path2 = oss.str();
// 			pet->m_PetData.ReadPet(petfilename, path2);
// 			pet->SetData(g_pMainState->m_PetDataManager.GetPetData(pet->m_PetData.modeid));
// 			pet->m_PetData.Followlv(cct::get()->maxRoleLv + cct::get()->lvGapFromRoleAndBaby, true, true, true);
// 			pet->m_PetData.SetJinJie(3);
// 			pet->m_PetData.m_JinJieNum.m_index = positonid;
// 			pc->m_PcData.AddPet(pet);
// 			pet = 0;
// 		}
// 
// 		g_pMainState->SetFightPet(startid + i, 0, false);
// 		g_pMainState->m_FightWorkList[startid + i].isExist = true;
// 		pc->m_PcData.m_IDinFightWorkList = startid + i;
// 		pc->m_PcData.Followlv(cct::get()->maxRoleLv, false, true, true);
// 		if (weapontype > -1)
// 		{
// 			pc->m_PcData.m_Equip[2].Set(weapontype, weaponid, false);
// 			pc->m_PcData.m_pWeaponData2 = 0;
// 			pc->m_PcData.m_pCharacterData2 = 0;
// 		}
// 		g_pMainState->m_FightWorkList[startid + i].m_pObj->Reset();
// 		g_pMainState->m_FightWorkList[startid + i].m_pObj->Set(POS_FIGHT_STAND);
// 		g_pMainState->m_FightWorkList[startid + i + 5].m_pObj->Set(POS_FIGHT_STAND);
// 
// 
// 		if (bEnemy)
// 			pc->m_PcData.m_Controler.Set(false, false, false, true, false);
// 		else
// 			pc->m_PcData.m_Controler.Set(false, false, false, true, false);
// 
// 	}
// 
// 
// 	File.close();
	return true;
}





bool cTaskZhiXian2::Process(int stage)
{
	if (stage == -1)
	{
		return true;
	}
	if (stage < 1000)
	{
		g_pMainState->m_Dialog.Reset();
		g_pMainState->m_Dialog.SetObj(g_pMainState->m_pNowSelect);
		g_pMainState->m_Dialog.SetString("要我#109", "要", "不要");
		g_pMainState->m_Dialog.SetTrigger(this, -1, stage + 1000);
		g_pMainState->m_Dialog.OnOff(true);
		return true;
	}
	if (stage > 1000)
	{
		int sid = stage - 1000;
		if (g_pCharacter->m_PcData.m_NumofBB == g_pCharacter->m_PcData.m_pPets.size())
		{
			g_pMainState->dialog("召唤兽栏满了");
			return true;
		}

		cPet* pet = new cPet;
		pet->SetData(&g_pMainState->m_PetDataManager.m_PetList[sid]);
		auto& p = pet->m_PetData;
		p.Load(sid, true, true);
		p.PointRemain = cct::PointRemian;
		p.apply();
		p.FillHpMp();
		g_pCharacter->m_PcData.AddPet(pet);
		g_pMainState->m_Tags.Add(pet->GetData()->m_Name + " +1");
		return true;
	}
	////////////////////////////////////////////////////////////////////////// 呵呵哒 领悟技能
	return true;
	switch (g_pCharacter->m_PcData.m_MengPaiID)
	{
	case eMP_大唐官府:
		switch (stage)
		{
		case 100:
			g_pHeroObj->Talk("领悟了新技能");
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级必杀);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_风刃);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_直死);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级夜战);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术连击);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级幸运);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级招架);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级永恒);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级夜战);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级敏捷);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级否定信仰);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级幸运);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级神迹);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级必杀);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级反击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级反震);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级神迹);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级防御);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级敏捷);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术波动);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级魔之心);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术暴击);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_迷你空间震);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级鬼魂术);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级必杀);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_直死);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_风华武圣);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级防御);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级夜战);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级敏捷);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级招架);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级吸血);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级鬼魂术);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级法术抵抗);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级敏捷);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级强力);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级精神集中);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级神迹);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级魔之心);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_风华武圣);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_迷你空间震);
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
			return true;
		case 0:
			AddTriggerLv(1, 20);
			break;
		case 1:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_再生);
			AddTriggerLv(2, 40);
			break;
		case 2:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_偷袭);
			AddTriggerLv(3, 60);
			break;
		case 3:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_防御);
			AddTriggerLv(4, 80);
			break;
		case 4:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_夜战);
			AddTriggerLv(5, 100);
			break;
		case 5:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级魔之心);
			AddTriggerLv(6, 120);
			break;
		case 6:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_高级连击);
			AddTriggerLv(7, 140);
			break;
		case 7:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_风华武圣);
			AddTriggerLv(8, 160);
			break;
		case 8:
			Process(100);
			g_pCharacter->m_PcData.AddSkill(ePS_迷你空间震);
			break;
		default:ERRBOX;
			break;
		}
		break;

	}

	return true;
}

