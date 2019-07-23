#include "global.h"
#if ccc_date
void cItem::AutoItemProperty(sItem2* item, int Luck, int dustbin)
{
	////////////////////////////////////////////////////////////////////////// 呵呵哒
	g_pMainState->m_InterfaceDoor.m_TimeShiCheng.UpdateTime();
	if (Luck < 10)Luck = 10;
	if (Luck > 1000)Luck = 1000;
	item->m_Property.clear();
	item->m_strProperty = "";
	vector<int>& property = item->m_Property;
	property.clear();

	int stone = dustbin % 10;
	int skillSpecialID = (dustbin / 10) - 1;
	switch (item->GetType())
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		// 武器
		if (1)
		{
			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.UpdateTime();
			int lv = item->m_pItemData->GetLv();
			int Offset = lv / 10;


			property.push_back(Offset);//强化等级
// 			if (0==rand()%10)
// 				property.push_back(rand()%36);
// 			else 	
// 				property.push_back(-1);
			property.push_back(skillSpecialID);
			property.push_back(-1);
			property.push_back(-1);
			property.push_back(-1);
			// 			int extranum = rand() % 10;
			// 			if (extranum > 2)
			// 				extranum = 0;
			// 
			// 			property.push_back(extranum+2);
			property.push_back(4);
			property.push_back(eProPerty伤害);
			//			property.push_back((15 + Offset * 40)+(40*rand()%(1000+Luck))/2000 );
			property.push_back(37 + Offset * 40/* + 200*/);// 注意getEquipAtk一致
			property.push_back(eProPerty命中);
			property.push_back(57 + Offset * 45 + 600);
			// 			property.push_back(eProPerty气血);
			// 			property.push_back(400);
			property.push_back(eProPerty魔法);
			property.push_back(400);
			property.push_back(eProPerty防御);
			property.push_back(200);
			//			property.push_back((10 + Offset * 35) + (35 * rand() % (1000 + Luck)) / 2000);
			//			AutoItemProperty装备(property, extranum, Luck, Offset);

		}
		break;
		//装备
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:

	{
		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.UpdateTime();
		int lv;
		lv = item->m_pItemData->GetLv();//  GetlvByID(item->m_pItemData->m_Type, item->m_pItemData->m_ID);

		int Offset = lv / 10;
		property.push_back(Offset);//强化等级

		//// 得到特技的几率
		//int special, special2;
		//if (rand() % (15 - Luck / 100) == 0)
		//	special = rand() % 50;
		//else special = -1;
		//if (rand() % (15 - Luck / 100) == 0)
		//	special2 = 50 + rand() % 8;
		//else  special2 = -1;
		//property.push_back(special);
		//property.push_back(special2);

// 			if (0 == rand() % 10)
// 				property.push_back(rand() % 36);
// 			else 	property.push_back(-1);
		property.push_back(skillSpecialID);
		property.push_back(-1);
		property.push_back(-1);
		property.push_back(-1);
		// 			int extranum=0;
		// 			if (18 == item->GetType())
		// 			{
		// 				int extranum = rand() % 10;
		// 				if (extranum > 2)extranum = 0;
		// 			}

		switch (item->GetType())
		{
		case 15:  //头
		case 16:
			//				property.push_back(extranum+2);
			property.push_back(3);
			if (stone)
			{
				property.push_back(eProPerty防御);
				//				property.push_back((5 + Offset * 5) + (5 * (rand() % (100 + Luck / 10))) / 100);
				property.push_back(3 + Offset * 7 + 60);
				property.push_back(eProPerty魔法);
				//				property.push_back((5 + Offset * 10) + (10 * (rand() % (100 + Luck / 10))) / 100);
				property.push_back(32 + Offset * 12);
				property.push_back(eProPerty伤害);
				property.push_back(60 + Offset * 8);
			}
			else
			{
				property.push_back(eProPerty防御);
				property.push_back(3 + Offset * 7 + Offset * 12 + 60);
				property.push_back(eProPerty魔法);
				property.push_back(32 + Offset * 12);
				property.push_back(eProPerty伤害);
				property.push_back(60);
				}
			break;
		case 17:   //衣
		case 18:
			//				property.push_back(extranum+1);
			if (stone == 1)
			{
				property.push_back(3);
				property.push_back(eProPerty防御);
				//				property.push_back((10 + Offset * 15) + (15 * (rand() % (100 + Luck / 10))) / 100);
				property.push_back(20 + Offset * 20);
				property.push_back(eProPerty灵力);
				property.push_back(6 * Offset + 28);

			}
			else if (stone == 0)
			{
				property.push_back(3);
				property.push_back(eProPerty防御);
				property.push_back(20 + Offset * (20 + 12));
				property.push_back(eProPerty灵力);
				property.push_back(28);
			}
			else if (stone == 2)
			{
				property.push_back(4);
				property.push_back(eProPerty防御);
				property.push_back(20 + Offset * 20);
				property.push_back(eProPerty灵力);
				property.push_back(28);
				property.push_back(eProPerty气血);
				property.push_back(Offset * 40);
			}
			else
			{
				property.push_back(1);
			}
			property.push_back(eProPerty魔法);
			property.push_back(160);

			break;
		case 19:  //项链
//				property.push_back(extranum+1);
			property.push_back(2);
			property.push_back(eProPerty灵力);
			//				property.push_back((5 + Offset * 12) + (12 * (rand() % (100 + Luck / 10))) / 100);
			property.push_back(11 + Offset * (16 + 6));
			property.push_back(eProPerty气血);
			property.push_back(240);
			break;
		case 20: //腰带
//				property.push_back(extranum+2);
			if (stone)
			{
				property.push_back(3);
				property.push_back(eProPerty防御);
				//				property.push_back((5 + Offset * 5) + (5 * (rand() % (100 + Luck / 10))) / 100);
				property.push_back(3 + Offset * 7);
				property.push_back(eProPerty气血);
				//				property.push_back((10 + Offset * 20) + (20 * (rand() % (100 + Luck / 10))) / 100);
				property.push_back(33 + Offset * (26 + 25)); // 25是武器的临时符
				property.push_back(eProPerty速度);
				property.push_back(Offset * 8);
			}
			else
			{
				property.push_back(2);
				property.push_back(eProPerty防御);
				property.push_back(3 + Offset * 7);
				property.push_back(eProPerty气血);
				property.push_back(33 + Offset * (26 + 40 + 25));
			}
			break;
		case 21: //鞋
//				property.push_back(extranum+2);

			if (stone == 0)
			{
				// 速度
				property.push_back(2);
				property.push_back(eProPerty防御);
				property.push_back(3 + Offset * 7);
				property.push_back(eProPerty速度);
				property.push_back(3 + Offset * (3 + 8 + 18));
			}
			else if (stone == 1)
			{
				// 伤害
				property.push_back(3);
				property.push_back(eProPerty防御);
				property.push_back(3 + Offset * 7);
				property.push_back(eProPerty速度);
				property.push_back(2 + Offset * 3 + 60);
				property.push_back(eProPerty伤害);
				property.push_back(Offset * 25);

			}
			else if (stone == 2)
			{
				// 灵力
				property.push_back(3);
				property.push_back(eProPerty防御);
				property.push_back(3 + Offset * 7);
				property.push_back(eProPerty速度);
				property.push_back(2 + Offset * 3 + 60);
				property.push_back(eProPerty灵力);
				property.push_back(Offset * 25);
			}
			// 				else if (stone == 3)
			// 				{
			// 					// 气血
			// 					property.push_back(3);
			// 					property.push_back(eProPerty防御);
			// 					property.push_back(3 + Offset * 7);
			// 					property.push_back(eProPerty速度);
			// 					property.push_back(2 + Offset * 3 + 60);
			// 					property.push_back(eProPerty气血);
			// 					property.push_back(80 + Offset * 80/*145*/);
			// 				}
			//				property.push_back(eProPerty防御);
			//				property.push_back((5 + Offset * 5) + (5 * (rand() % (100 + Luck / 10))) / 100);
			//				property.push_back(eProPerty速度);
			//				property.push_back((5 + Offset * 3) + (3 * (rand() % (100 + Luck / 10))) / 100);
			break;
			}
		//			AutoItemProperty装备(property, extranum, Luck, Offset);

		}
	break;
	case 32:
	case 33:
	case 34:
	{
		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.UpdateTime();
		int Offset = item->m_pItemData->m_ID + 1;
		property.push_back(Offset);//强化等级

		//// 得到特效的几率
		//int special2;
		//if (rand() % (15 - Luck / 100) == 0)
		//	special2 = 50 + rand() % 8;
		//else  special2 = -1;
		//property.push_back(-1);
		//property.push_back(special2);
		property.push_back(-1);
		property.push_back(-1);
		property.push_back(-1);
		property.push_back(-1);
		// 			int extranum = 0;
		// 			if (18 == item->GetType())
		// 			{
		// 				int extranum = rand() % 10;
		// 				if (extranum > 2)extranum = 0;
		// 			}
		// 			property.push_back(extranum + 2);
		property.push_back(3);
		switch (item->GetType())
		{
		case 32://护腕 命中

			property.push_back(eProPerty命中);
			property.push_back(15 + Offset * 50 + (50 * (rand() % (100 + Luck / 10))) / 100);
			property.push_back(eProPerty气血);
			property.push_back(Offset * 10);
			if (stone)
			{
				property.push_back(eProPerty灵力);
				property.push_back(Offset * (2 + 4));

			}
			else
			{
				property.push_back(eProPerty伤害);
				//					property.push_back(5 + Offset * 20 + (20 * (rand() % (100 + Luck / 10))) / 100);
				property.push_back(Offset * (3 + 10));
			}

			break;
		case 33://项圈 速度	
			property.push_back(eProPerty气血);
			property.push_back(Offset * 10);
			if (stone)
			{
				property.push_back(eProPerty灵力);
				property.push_back(Offset * (2));

			}
			else
			{
				property.push_back(eProPerty伤害);
				property.push_back(Offset * (3));
			}
			property.push_back(eProPerty速度);
			//				property.push_back(3 + Offset * 4 + (4 * (rand() % (100 + Luck / 10))) / 100);
			property.push_back(Offset * (5 + 6));

			// 				property.push_back(eProPerty灵力);
			// 				property.push_back(2 + Offset * 3 + (3 * (rand() % (100 + Luck / 10))) / 100);
			break;
		case 34://铠甲 防
			property.push_back(eProPerty防御);
			//				property.push_back(10 + Offset * 15 + (15 * (rand() % (100 + Luck / 10))) / 100);
			property.push_back(Offset * 10);

			property.push_back(eProPerty气血);
			//				property.push_back(30 + Offset * 50 + (50 * (rand() % (100 + Luck / 10))) / 100);
			property.push_back(Offset * (10 + 30));
			if (stone)
			{
				property.push_back(eProPerty灵力);
				property.push_back(Offset * (2));

			}
			else
			{
				property.push_back(eProPerty伤害);
				property.push_back(Offset * (3));
			}
			break;
		}
		//			AutoItemProperty装备(property, extranum, Luck, Offset);
	}
	break;
	case 24://法宝
		property.push_back(0);
		break;
	case 27:
		break;
	case 28: //不可叠加道具
		switch (item->GetID())
		{
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			property.push_back(20);
			break;
		case 6:

		{
			int xbaotu, ybaotu;
			int mapid = rand() % g_pMainState->m_TaskBaoTu.m_MapNameList.size();
			property.push_back(mapid);;
			g_pMainState->m_Map.AutoGetPos(xbaotu, ybaotu, g_pMainState->m_TaskBaoTu.m_MapNameList[mapid]);
			property.push_back(xbaotu);
			property.push_back(ybaotu);
			property.push_back(xbaotu * 20);
			property.push_back(g_pMainState->m_Map.m_BmpTest.GetHeight() - ybaotu * 20);

		}
		break;
		case 8:  //制造书
			if (1)
			{
				int equiptype = rand() % 22;
				if (equiptype == 13)equiptype = rand() % 13;
				int equipid = (rand() % 8) * 10;
				property.push_back(equiptype);
				property.push_back(equipid);
			}
			break;
		default:
			break;
		}
		break;
	case 31:
		if (1)
		{
			property.push_back(0);//坐骑装饰染色
		}
		break;
	default:
		return;
		break;
	}
}


void cItem::AutoItemProperty鉴定(sItem2* item, int Luck)
{
	if (item->GetType() > 21)
	{
		return AutoItemProperty(item, Luck, 0);
	}
	if (Luck < 10)Luck = 10;
	if (Luck > 1000)Luck = 1000;
	item->m_Property.clear();
	item->m_strProperty = "";
	vector<int>& property = item->m_Property;
	property.clear();
	switch (item->GetType())
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		if (1)
		{
			int lv = item->m_pItemData->GetLv();
			int Offset = lv / 10;


			property.push_back(0);//强化等级
			property.push_back(rand() % 36);
			property.push_back(-1);
			property.push_back(-1);
			property.push_back(-1);
			int extranum = 0;
			//			extranum = rand() % 10;
			// 			if (extranum > 2)extranum = 0;
			// 			extranum = 2;

			property.push_back(extranum + 2);
			property.push_back(eProPerty伤害);
			property.push_back((15 + Offset * 40) + (40 * rand() % (1000 + Luck)) / 1000);
			property.push_back(eProPerty命中);
			property.push_back((10 + Offset * 35) + (55 * rand() % (1000 + Luck)) / 1000);
			AutoItemProperty2(property, extranum, Luck, Offset);
		}
		break;
		//装备
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	{
		int lv;
		lv = item->m_pItemData->GetLv();//  GetlvByID(item->m_pItemData->m_Type, item->m_pItemData->m_ID);

		int Offset = lv / 10;
		property.push_back(0);//强化等级

		//// 得到特技的几率
		//int special, special2;
		//if (rand() % (15 - Luck / 100) == 0)
		//	special = rand() % 50;
		//else special = -1;
		//if (rand() % (15 - Luck / 100) == 0)
		//	special2 = 50 + rand() % 8;
		//else  special2 = -1;
		//property.push_back(special);
		//property.push_back(special2);

		property.push_back(rand() % 36);
		property.push_back(-1);
		property.push_back(-1);
		property.push_back(-1);
		int extranum = 0;
		// 		if (18 == item->GetType() || 17 == item->GetType())
		// 		{
		// 			extranum = rand() % 10;
		// 			if (extranum > 2)extranum = 0;
		// 			extranum = 2;
		// 		}

		switch (item->GetType())
		{
		case 15:  //头
		case 16:
			property.push_back(extranum + 2);
			property.push_back(eProPerty防御);
			property.push_back((5 + Offset * 5) + (5 * (rand() % (100 + Luck / 10))) / 50);
			property.push_back(eProPerty魔法);
			property.push_back((5 + Offset * 10) + (10 * (rand() % (100 + Luck / 10))) / 50);
			break;
		case 17:   //衣
		case 18:
			property.push_back(extranum + 1);
			property.push_back(eProPerty防御);
			property.push_back((10 + Offset * 15) + (15 * (rand() % (100 + Luck / 10))) / 50);
			break;
		case 19:  //项链
			property.push_back(extranum + 1);
			property.push_back(eProPerty灵力);
			property.push_back((5 + Offset * 12) + (12 * (rand() % (100 + Luck / 10))) / 50);
			break;
		case 20: //腰带
			property.push_back(extranum + 2);
			property.push_back(eProPerty防御);
			property.push_back((5 + Offset * 5) + (5 * (rand() % (100 + Luck / 10))) / 50);
			property.push_back(eProPerty气血);
			property.push_back((10 + Offset * 20) + (20 * (rand() % (100 + Luck / 10))) / 50);
			break;
		case 21: //鞋
			property.push_back(extranum + 2);
			property.push_back(eProPerty防御);
			property.push_back((5 + Offset * 5) + (5 * (rand() % (100 + Luck / 10))) / 50);
			property.push_back(eProPerty速度);
			property.push_back((5 + Offset * 3) + (3 * (rand() % (100 + Luck / 10))) / 50);
			break;
		}
		AutoItemProperty2(property, extranum, Luck, Offset);

	}
	break;
	}
}



#endif