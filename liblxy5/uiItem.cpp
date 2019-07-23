#include "_global.h"
#include "_txt.h"


bool cInterfaceItem::Init()
{
	if (m_bInit)return true;
	m_bInit = true;

	m_EquipBackP.resize(6);
	m_PetEquipBackP.resize(3);
	m_ItemHead.resize(20);
	m_EquipHead.resize(6);//角色和召唤兽装备
	m_PetEquipHead.resize(3);

	m_Obj.Init();
	m_Obj.m_IndexType = INDEXTYEP_PET;
	m_MousePosBack.Load(0x354CD2EB);
	m_MousePosBack.SetStatic(1);
	m_MousePos.SetColor(RGB(0, 0, 0));
	m_MousePos.SetXY(700, 500);
	m_MousePos.m_hFont = g_pMainState->m_hFont[5];
	//
	m_PathPoint.Load(0x146BB550);
	forr(m_PathPointp, i)
	{
		m_PathPointp[i].Set(&m_PathPoint);
		m_PathPointp[i].m_bStatic = true;
	}

	static vector<vector<vector<int>>> s_xys =
	{
		{ { 197, 171 }, { 219, 122 }, { 18, 9 }, { 281, 39 }, { 329, 17 }, { 472, 38 }, { 503, 7 }, 
		{ 518, 72 }, { 329, 17 }, { 459, 164 }, { 321, 267 }, { 388, 266 }, { 438, 240 }, 
		{ 500, 270 }, { 510, 190 }, { 520, 150 }, { 520, 124 }, { 285, 199 }, { 360, 244 }, 
		{ 488, 238 }, { 484, 94 }, { 443, 133 }, { 413, 106 }, { 446, 93 }, { 366, 133 },
		{ 304, 113 }, { 362, 79 }, { 188, 14 }, { 412, 240 }, { 350, 170 }, { 255, 154 },
		{ 167, 134 }, { 122, 104 }, { 177, 89 }, { 90, 74 }, { 47, 96 }, { 84, 32 },
		{ 20, 59 }, { 225, 232 }, { 22, 144 }, { 153, 193 }, { 112, 200 }, { 106, 228 } },


		{ { 32, 70 }, { 24, 96 }, { 13, 137 }, { 48, 28 }, { 205, 135 }, { 190, 65 }, { 167, 17 }, 
		{ 129, 41 }, { 135, 95 }, { 70, 95 }, { 125, 125 }, { 2000, 105 } },


		{ { 107, 195 }, { 47, 158 }, { 22, 109 }, { 21, 26 }, { 78, 24 }, { 140, 9 }, { 108, 59 }, 
		{ 118, 111 }, { 135, 160 }, { 40, 65 } },


		{ { 9, 5 }, { 22, 90 }, { 74, 98 }, { 91, 55 }, { 145, 10 }, { 142, 95 }, { 45, 70 }, 
		{ 40, 35 }, { 105, 110 }, { 155, 60 }, { 185, 45 }, { 75, 10 } },


		{ { 20, 101 }, { 56, 112 }, { 15, 54 }, { 135, 60 }, { 235, 109 }, { 241, 60 }, { 318, 75 },
		{ 353, 6 }, { 450, 95 }, { 586, 16 }, { 626, 5 }, { 532, 81 }, { 528, 112 }, { 633, 101 },
		{ 626, 65 }, { 135, 95 }, { 140, 24 }, { 240, 11 }, { 318, 111 }, { 377, 97 }, { 394, 47 }, 
		{ 500, 36 }, { 467, 8 }, { 575, 75 }, { 596, 33 }, { 45, 11 } },
	};
	static vector<string> s_names = { "长安城", "傲来国", "长寿村", "朱紫国", "大唐境外" };
	static vector<int> s_highs = { 5600, 3020, 4200, 2400, 2400 };
	static vector<ulong> s_smaps = { 3468445205, 2930683699, 2766803400, 1428468522, 1389007272 };
	int x2, y2;
	float fx2, fy2;
	for (int i = 0; i < 5; ++i)
	{
		m_sMapSelect[i].m_Name = s_names[i];
		m_sMapSelect[i].m_Height = s_highs[i];
		m_sMapSelect[i].m_SmallMap = s_smaps[i];
		m_MapBack.LoadMap(m_sMapSelect[i].m_SmallMap);
		m_sMapSelect[i].m_bili = ((float)m_sMapSelect[i].m_Height) / ((float)m_MapBack.GetHeight() - 36);
		m_sMapSelect[i].m_num = s_xys[i].size();
		for (int j = 0; j < m_sMapSelect[i].m_num; j++)
		{
			x2 = s_xys[i][j][0];
			y2 = s_xys[i][j][1];
			m_sMapSelect[i].m_xorg.push_back(x2);
			m_sMapSelect[i].m_yorg.push_back(y2);
			x2 *= 20;
			y2 *= 20;
			y2 = m_sMapSelect[i].m_Height - y2;
			fx2 = (float)x2;
			fy2 = (float)y2;
			fx2 /= m_sMapSelect[i].m_bili;
			fy2 /= m_sMapSelect[i].m_bili;
			x2 = (int)fx2;
			y2 = (int)fy2;
			x2 += 18;
			y2 += 18;
			m_sMapSelect[i].m_x.push_back(x2);
			m_sMapSelect[i].m_y.push_back(y2);
		}
	}


// 	ifstream File;
// 	ostringstream oss;
// 	oss << g_pathData;
// //	oss << "道具列表\\导标旗坐标.txt";
// 	oss << "导标旗坐标.txt";
// 	File.open(oss.str());
// 	if (!File)ERRBOX;
// 	int x2, y2;
// 	float fx2, fy2;
// 	ifstream File0;
// 	string s = g_pathData + "_境外导标旗.txt";
// 	File0.open(s);
// 	if (!File0)ERRBOX;
// 	for (int i = 0; i < 5; i++)
// 	{
// 		ifstream &File2 = (i == 4) ? File0 : File;
// 		File2 >> m_sMapSelect[i].m_Name;
// 		File2 >> m_sMapSelect[i].m_Height;
// 		File2 >> m_sMapSelect[i].m_SmallMap;
// 		m_MapBack.Load(m_sMapSelect[i].m_SmallMap);
// 		m_sMapSelect[i].m_bili = ((float)m_sMapSelect[i].m_Height) / ((float)m_MapBack.GetHeight() - 36);
// 		File2 >> m_sMapSelect[i].m_num;
// 		for (int j = 0; j < m_sMapSelect[i].m_num; j++)
// 		{
// 			File2 >> x2;
// 			File2 >> y2;
// 			m_sMapSelect[i].m_xorg.push_back(x2);
// 			m_sMapSelect[i].m_yorg.push_back(y2);
// 			x2 *= 20;
// 			y2 *= 20;
// 			y2 = m_sMapSelect[i].m_Height - y2;
// 			fx2 = (float)x2;
// 			fy2 = (float)y2;
// 			fx2 /= m_sMapSelect[i].m_bili;
// 			fy2 /= m_sMapSelect[i].m_bili;
// 			x2 = (int)fx2;
// 			y2 = (int)fy2;
// 			x2 += 18;
// 			y2 += 18;
// 			m_sMapSelect[i].m_x.push_back(x2);
// 			m_sMapSelect[i].m_y.push_back(y2);
// 		}
// 	}
// 	File.close();
// 
// 	for (int i = 0; i < 5; ++i)
// 	{
// 		s = "";
// 		for (int k = 0; k < m_sMapSelect[i].m_xorg.size(); ++k)
// 		{
// 			s += toString("{%d,%d},", m_sMapSelect[i].m_xorg[k], m_sMapSelect[i].m_yorg[k]);
// 		}
// 		Q_LOG("%s", s.c_str());
// 	}


	//飞行符地图
	m_Describe.Init();
	m_WorldMap.Load(0x516749F4);
	m_WorldMap.SetStatic(true);
	m_WorldMap.m_Picture.m_x = g_half320 - m_WorldMap.m_Picture.m_Width / 2;
	m_WorldMap.m_Picture.m_y = g_half240 - m_WorldMap.m_Picture.m_Height / 2;
	m_MapSelect.SetStatic(true);
	m_MapID[0] = 0xC5C5FE46;//长寿
	m_MapID[1] = 0x3D561594;//建邺
	m_MapID[2] = 0xDB61AD29;//长安
	m_MapID[3] = 0x6BD8F1C8;//AL
	m_MapID[4] = 0x29622DDB;//西凉女国
	m_MapID[5] = 0x491E6B4C;//宝象
	m_MapID[6] = 0x549B2B83;//朱紫国
	//CS
	m_MapRect[0].left = 209;
	m_MapRect[0].top = 18;
	m_MapRect[0].right = 272;
	m_MapRect[0].bottom = 65;
	//JY
	m_MapRect[1].left = 424;
	m_MapRect[1].top = 190;
	m_MapRect[1].right = 476;
	m_MapRect[1].bottom = 238;
	//CA
	m_MapRect[2].left = 377;
	m_MapRect[2].top = 84;
	m_MapRect[2].right = 487;
	m_MapRect[2].bottom = 174;
	//AL
	m_MapRect[3].left = 574;
	m_MapRect[3].top = 245;
	m_MapRect[3].right = 621;
	m_MapRect[3].bottom = 290;
	//XL
	m_MapRect[4].left = 204;
	m_MapRect[4].top = 87;
	m_MapRect[4].right = 236;
	m_MapRect[4].bottom = 120;
	//BX
	m_MapRect[5].left = 187;
	m_MapRect[5].top = 161;
	m_MapRect[5].right = 257;
	m_MapRect[5].bottom = 205;

	//ZZ
	m_MapRect[6].left = 251;
	m_MapRect[6].top = 225;
	m_MapRect[6].right = 314;
	m_MapRect[6].bottom = 270;


	m_NumMapSelect = -1;

	m_EquipBack.Load(0xA393A808);
	m_EquipBack.SetStatic(true);
	for (int i = 0; i < 6; i++)
	{
		m_EquipBackP[i].Set(&m_EquipBack);
	}
	for (int i = 0; i < 3; i++)
	{
		m_PetEquipBackP[i].Set(&m_EquipBack);
	}
	m_bXianJin = true;
	m_XianJin.Load(0x79D01E0E);
	m_XianJin.SetStatic(true);
	m_SwapMode = false;

	//召唤兽装备
	m_PetHeadback.Load(0x9B1DB10D);
//	m_ButtonPetMode.Set(&m_XianJin);
//	m_ButtonPetMode.m_bStatic = true;
//	m_ButtonPetMode.Load(m_Mode == 2 ? 0x94989763 : 0xB5531AC0);
	m_ButtonPetMode.SetStatic(true);
	m_tButtonPetMode.SetColor(RGB(255, 255, 255));
	m_tButtonPetMode.SetString("法宝");
	m_Obj.m_TrueName.SetColor(RGB(255, 255, 255));
	//

	m_Select = 1;
	m_Item.Load(2198359531);
	m_PetID = 0x9B1DB10D;
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_ZuoQiB.Load(0x79D01E0E);
	m_ZuoQiB.SetStatic(true);
	m_ZuoQiZhuangShiB.Load(0x79D01E0E);
	m_ZuoQiZhuangShiB.SetStatic(true);
	m_ItemButton.Load(0x63CC8A23);
	m_ItemButton.SetStatic(true);
	m_ItemButton2.Load(0x00D13BBF);
	m_ItemButton2.SetStatic(true);
	m_ItemButton3.Load(0x00D13BBF);
	m_ItemButton3.SetStatic(true);	
	m_ItemButton4.Load(0x00D13BBF);
	m_ItemButton4.SetStatic(true);
	m_FabaoButton.Load(/*0x18C30C41*/g_pMainState->m_Button2.m_NowID);
	m_FabaoButton.SetStatic(true);
	m_FabaoID = 0x323E2BCD;
	m_BackID = 1261107812;
	m_ZuoQiID = 0xA7CE2F61;
	m_Headback.Load(m_BackID);
	m_BigHead.m_NeedShow = true;


	m_SelectMark.Load(0x10921CA7);
	m_SelectMark.m_NeedShow = false;
	m_MouseOnMark.Load(0x6F88F494);
	m_MouseOnMark.m_NeedShow = false;

	for (int i = 0; i < 20; i++)
	{
		m_TItemNum[i].SetColor(RGB(255, 255, 255));
		m_TItemNum[i].SetStyle(2);
		m_TItemNum[i].SetBackColor(RGB(0, 0, 0));
	}

	m_TZhuangShi.SetString("装饰");
	m_TZhuangShi.SetColor(RGB(240, 240, 240));
	m_TZuoQi.SetColor(RGB(240, 240, 240));
	m_TZuoQi.SetString("祥瑞");


	m_TCunYingN.SetColor(RGB(0, 0, 0));
	m_TXianJinN.SetColor(RGB(0, 0, 0));
	m_TXianJin.SetColor(RGB(240, 240, 240));

	m_ItemButton.SetFrame(1);
	Move(0, g_half240 - 240);
	return true;
}

bool cInterfaceItem::Show(cCanvas* pCanvas)
{

	switch (m_Mode)
	{
	case 0:
	case 2:
		break;
	case 1:
		return ShowSelectMap();
	case 6:
		return true;
	default:
		return ShowSelectMap2();
	}
	pCanvas->Add(&m_Item, 1, true);
	pCanvas->Add(&m_Cancel, 1);

	if (m_Mode == 0)
	{
		pCanvas->Add(&m_Headback, 1, 1);
		pCanvas->Add(&m_XianJin, 1);
		pCanvas->Add(&m_TXianJin);
		pCanvas->Add(&m_TCunYingN);
		pCanvas->Add(&m_TXianJinN);
		pCanvas->Add(&m_BigBigHead, 1);
	}
	else
	{
		pCanvas->Add(&m_PetHeadback, 1, 1);
		pCanvas->Add(m_Obj.GetShadow(), 1);
		m_Obj.ShowOnScreen(pCanvas);
		g_pMainState->m_Canvas.Add(&m_PetName);
	}
	if (m_ButtonPetMode.m_NeedShow)
	{
		pCanvas->Add(&m_ButtonPetMode, 1);
//		pCanvas->Add(&m_tButtonPetMode);
	}

	pCanvas->Add(&m_ItemButton, 1);
	pCanvas->Add(&m_ItemButton2, 1);
	pCanvas->Add(&m_ItemButton3, 1);
	pCanvas->Add(&m_ItemButton4, 1);
	pCanvas->Add(&m_FabaoButton, 1);
	pCanvas->Add(&m_tButtonPetMode);


	if (m_ZuoQiB.m_NeedShow)
	{
		pCanvas->Add(&m_ZuoQiB, 1);
		pCanvas->Add(&m_TZuoQi);

		if (m_ZuoQiZhuangShiB.m_NeedShow)
		{
			pCanvas->Add(&m_ZuoQiZhuangShiB, 1);
			pCanvas->Add(&m_TZhuangShi);
		}
	}
	cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
	ostringstream oss;
	int trueid;


	if (m_SwapMode)
	{
		if (m_Mode == 2)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == m_SwapID - 12000)continue;
				if (pPet->m_PetData.m_Equips[i].GetNum())
				{
					pCanvas->Add(&m_PetEquipBackP[i], 1);
					pCanvas->Add(&m_PetEquipHead[i], 1);
				}
			}
		}
		else
			for (int i = 0; i < 6; i++)
			{
			if (i == m_SwapID - 10000)continue;
			if (p->m_PcData.m_Equips[i].GetNum())
			{
				pCanvas->Add(&m_EquipBackP[i], 1);
				pCanvas->Add(&m_EquipHead[i], 1);
			}
			}
		if (m_ItemPage * 20 < p->m_PcData.m_Items.size())
		{
			for (int i = 0; i < 20; i++)
			{
				trueid = i + m_ItemPage * 20;
				if (trueid == m_SwapID)
				{
					continue;
				}
				if (p->m_PcData.m_Items[trueid].GetNum() > 0)
				{
					pCanvas->Add(&m_ItemHead[i], 1);
				}
				if (p->m_PcData.m_Items[trueid].GetNum() > 1)
				{
					pCanvas->Add(&m_TItemNum[i]);
				}
			}
		}
		else
		{
			for (int i = 0; i < 20; i++)
			{
				trueid = i;
				if (trueid == m_SwapID - p->m_PcData.m_Items.size())
				{
					continue;
				}
				if (p->m_PcData.m_Fabaos[trueid].GetNum() > 0)
				{
					pCanvas->Add(&m_ItemHead[i], 1);
				}
				if (p->m_PcData.m_Fabaos[trueid].GetNum() > 1)
				{
					pCanvas->Add(&m_TItemNum[i]);
				}
			}
		}
	}
	else
	{
		if (m_Mode == 2)
		{
			for (int i = 0; i < 3; i++)
			{
				if (pPet->m_PetData.m_Equips[i].GetNum())
				{
					pCanvas->Add(&m_PetEquipBackP[i], 1);
					pCanvas->Add(&m_PetEquipHead[i], 1);
				}
			}
		}
		else
			for (int i = 0; i < 6; i++)
			{
			if (p->m_PcData.m_Equips[i].GetNum())
			{
				pCanvas->Add(&m_EquipBackP[i], 1);
				pCanvas->Add(&m_EquipHead[i], 1);
			}
			}
		if (m_ItemPage * 20 < p->m_PcData.m_Items.size())
		{
			for (int i = 0; i < 20; i++)
			{
				trueid = i + m_ItemPage * 20;
				if (p->m_PcData.m_Items[trueid].GetNum())
				{
					pCanvas->Add(&m_ItemHead[i], 1);
				}
				if (p->m_PcData.m_Items[trueid].GetNum() > 1)
				{
					pCanvas->Add(&m_TItemNum[i]);
				}
			}
		}
		else
		{
			for (int i = 0; i < 20; i++)
			{
				trueid = i;
				if (p->m_PcData.m_Fabaos[trueid].GetNum())
				{
					pCanvas->Add(&m_ItemHead[i], 1);
				}
				if (p->m_PcData.m_Fabaos[trueid].GetNum() > 1)
				{
					pCanvas->Add(&m_TItemNum[i]);
				}
			}
		}

	}
	//}
	pCanvas->Add(&m_MouseOnMark, 1);

	if (m_SwapMode)
	{
		pCanvas->Add(&m_SelectMark, 1);
		pCanvas->Add(&m_SwapItemSelect, 1);
	}

	return true;

}

bool cInterfaceItem::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	ResetButton();
	m_Select = -1;
	m_NowSelect = -1;
	if (m_Describe.m_NeedShow)
	{
		m_Describe.OnOff(false);
	}
	cObj* pUser = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj;
	cCharacter* pc = (cCharacter*)pUser->m_pIndex;
	switch (m_Mode) //飞行符
	{
	case 0:
		break;
	case 2:
		break;
	case 1:
		return ProcessSelectMap();
	case 6:
		if (1)
		{
			int i;//寻找月光宝盒的位置
			sItem2* pItem = 0;
			for (i = 0; i < pc->m_PcData.m_Items.size(); i++)
			{
				if (pc->m_PcData.m_Items[i].GetType() == 24)
				{
					pItem = &pc->m_PcData.m_Items[i];
					if (11 == pItem->m_pItemData->m_ID)
					{
						break;
					}
				}
			}
			if (i == pc->m_PcData.m_Items.size())return false;
// 			for (i = 0; i < pc->m_PcData.m_Fabaos.size(); i++)
// 			{
// 				if (pc->m_PcData.m_Fabaos[i].GetType() == 24)
// 				{
// 					pItem = &pc->m_PcData.m_Fabaos[i];
// 					if (11 == pItem->m_pItemData->m_ID)
// 					{
// 						break;
// 					}
// 				}
// 			}
// 			if (i == pc->m_PcData.m_Fabaos.size())return false;
			switch (g_pMainState->m_Dialog.m_retSelect)
			{
			case 0:
				if (1)
				{
					InitMode(0);
					g_pMainState->m_Map.LoadMap(pItem->m_Property[1],
						pItem->m_Property[2],
						(char*)pItem->m_strProperty.c_str(), true);
					OnOff(false);
				}
				break;
			case 1:
				if (1)
				{
					pItem->m_strProperty = g_pMainState->m_Map.m_MapName;
					int xpos = pUser->GetX() / 20;
					int ypos = (g_pMainState->m_Map.m_pMap->m_Height - pUser->GetY()) / 20;
					if (pItem->m_Property.size() == 1)
					{
						pItem->m_Property.push_back(xpos);
						pItem->m_Property.push_back(ypos);
					}
					else
					{
						pItem->m_Property[1] = (xpos);
						pItem->m_Property[2] = (ypos);
					}
					g_pMainState->m_Tags.Add("你在当前位置定了坐标");
					InitMode(0);
				}
				break;
			default:
				m_Mode = 0;
				OnOff(false);
				break;
			}
		}
		return true;
	default:
		return ProcessSelectMap2();
	}

	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}
	if (m_SwapMode)
	{
		g_pMainState->SetMouseOnMap(false);
		m_SwapItemSelect.SetXY(g_xMouse - 25, g_yMouse - 25);
	}

	if (isInRect(g_xMouse, g_yMouse, &m_Item))
	{
		g_pMainState->SetMouseOnMap(false);


		if (CheckOn(&m_Cancel, 1))return true;
		if (CheckOn(&m_XianJin, 2))return true;


		if (0 == m_FabaoButton.GetNowFrame())
			if (CheckOn(&m_FabaoButton, 3))return true;

		if (0 == m_ItemButton.GetNowFrame())
			if (CheckOn(&m_ItemButton, 4))return true;

		if (m_ZuoQiB.m_NeedShow)
			if (CheckOn(&m_ZuoQiB, 11))return true;
		if (m_ButtonPetMode.m_NeedShow)
			if (CheckOn(&m_ButtonPetMode, 14))return true;
		if (m_ZuoQiZhuangShiB.m_NeedShow)
			if (CheckOn(&m_ZuoQiZhuangShiB, 12))return true;


		if (0 == m_ItemButton2.GetNowFrame())
			if (CheckOn(&m_ItemButton2, 5))
				return true;

		if (0 == m_ItemButton3.GetNowFrame())
			if (CheckOn(&m_ItemButton3, 10010))
				return true;

		if (0 == m_ItemButton4.GetNowFrame())
			if (CheckOn(&m_ItemButton4, 10086))
				return true;

		if (m_Mode == 2)
		{
			if (isOn(g_xMouse, g_yMouse, m_rectPetEquip))
			{
				m_NowSelect = (g_xMouse - m_rectPetEquip.left) / 55 + ((g_yMouse - m_rectPetEquip.top) / 55) * 2;
				m_MouseOnMark.SetXY(m_PetEquipHead[m_NowSelect].GetX(), m_PetEquipHead[m_NowSelect].GetY());
				m_NowSelect += 12000;
			}
		}
		else
			if (isOn(g_xMouse, g_yMouse, m_rectEquip))
			{
			m_NowSelect = (g_xMouse - m_rectEquip.left) / 55 + ((g_yMouse - m_rectEquip.top) / 55) * 2;

			m_MouseOnMark.SetXY(m_EquipHead[m_NowSelect].GetX(), m_EquipHead[m_NowSelect].GetY());
			m_NowSelect += 10000;

			}

		if (isOn(g_xMouse, g_yMouse, m_rectItem))
		{
			m_NowSelect = (g_xMouse - m_rectItem.left) / 51 + ((g_yMouse - m_rectItem.top) / 51) * 5;
			m_MouseOnMark.SetXY(m_ItemHead[m_NowSelect].GetX(), m_ItemHead[m_NowSelect].GetY());

			m_NowSelect += m_ItemPage * 20;
		}

		if (m_NowSelect>-1)
		{
			sItem2* pItem = pc->m_PcData.GetItem(m_NowSelect);
			m_MouseOnMark.m_NeedShow = true;

			if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
			{
				g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
				cCharacter* pc = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;

				if (!m_SwapMode)
				{
					if (pItem->GetNum())
					{
						m_SelectMark.m_NeedShow = true;
						m_SwapItemSelect.Load(pItem->m_pItemData->m_SmallHead);

						if (m_NowSelect < 10000)
						{
							m_SwapItemSelect.SetXY(g_xMouse - 25, g_yMouse - 25);
							m_SelectMark.SetXY(m_ItemHead[m_NowSelect - m_ItemPage * 20].GetX(),
								m_ItemHead[m_NowSelect - m_ItemPage * 20].GetY());

						}
						else  if (m_NowSelect < 12000)
						{
							m_SelectMark.SetXY(m_EquipHead[m_NowSelect - 10000].GetX(),
								m_EquipHead[m_NowSelect - 10000].GetY());

						}
						else
						{
							m_SelectMark.SetXY(m_PetEquipHead[m_NowSelect - 12000].GetX(),
								m_PetEquipHead[m_NowSelect - 12000].GetY());
						}
						m_SwapID = m_NowSelect;
						m_SwapMode = true;
						m_MouseOnMark.m_NeedShow = false;
					}

				}
				else
				{
					if (m_SwapID == m_NowSelect)
					{
						m_SwapID = -1;
						m_SwapMode = false;
						m_SelectMark.m_NeedShow = false;
						return true;
					}
					else
					{
						if (m_NowSelect >= 12000)
						{
							if (m_SwapID >= 10000)
							{
								m_SwapID = -1;
								m_SwapMode = false;
								m_SelectMark.m_NeedShow = false;
								return true;
							}
							else
								if (UseItem(m_SwapID, g_pMainState->m_HeroID))
								{
								m_SwapID = -1;
								m_SwapMode = false;
								m_SelectMark.m_NeedShow = false;
								return true;
								}
						}
						else
							if (m_NowSelect >= 10000)//装备
							{
								if (m_SwapID >= 10000)
								{
									m_SwapID = -1;
									m_SwapMode = false;
									m_SelectMark.m_NeedShow = false;
									return true;
								}
								else
									if (pc->m_PcData.GetItem(m_SwapID)->/*m_Items[m_SwapID].*/GetType() < 22) //装备
									{
										if ( (m_SwapID, g_pMainState->m_HeroID))
										{
											m_SwapID = -1;
											m_SwapMode = false;
											m_SelectMark.m_NeedShow = false;
											return true;
										}
									}
							}
							else 
							{
								if (m_SwapID > 10000 || (m_SwapID / 20 == m_NowSelect / 20)/* || m_NowSelect < 0*/)
								{
									if (!SwapItem(m_SwapID, m_NowSelect))return true;
									if (m_SwapID > 10000)
									{
										g_pMainState->m_State.UpDatePcDate();
									}
									m_SwapID = -1;
									m_SwapMode = false;
								}
								m_SelectMark.m_NeedShow = false;
							}

					}
					return true;
				}
			}
			//设置物品信息
			if (m_SwapMode == false)
			{
				UpDateItemDate(m_Describe);
			}
		}
		else
		{
			m_MouseOnMark.m_NeedShow = false;
			//准备移动
			m_Select = 7;
			if (CheckL())return true;
			if (g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))
			{
				g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
				OnOff(false);
			}
		}
		//使用道具
		m_Select = 0;
		CheckRB();
	}
	else
	{
		if (m_SwapMode)
		{
			if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
			{
				//cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData->m_pIndex;
				g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
				if (m_Select == -1)
				{
					SwapItem(m_SwapID, m_Select);
					m_SwapMode = false;
					m_SwapID = -1;
					m_SelectMark.m_NeedShow = false;
				}

			}
		}
		else
		{
			if (m_Describe.m_NeedShow)m_Describe.OnOff(false);
		}
	}
	return true;
}

bool cInterfaceItem::Add(int Pos, cPcData& pcData, sItem2* item)
{
	Init();
	sItem2* pItem;
	if (Pos >= pcData.m_Items.size() && item->GetType() != 24)
	{
		return false;
	}
// 	if (item->GetType() == 24)//法宝
// 	{
// 		for (int i = 0; i < 60; i++)
// 		{
// 			pItem = pcData.GetItem(i);
// 			if ((*pItem) == (*item))
// 				return false;
// 		}
// 		if (Pos <= 46)
// 		{
// 			g_pMainState->m_ItemManage.SetFabaoEffect(pcData, 1, (eFaBao)item->GetID());
// 		}
// 		else
// 		{
// 			g_pMainState->m_Tags.Add("法宝无效");
// 		}
// 	}

	pItem = pcData.GetItem(Pos);
	(*pItem) = (*item);

	if (pcData.m_IDinFightWorkList == g_pMainState->m_HeroID)
	{
		int headpos = Pos - m_ItemPage * 20;
		if (headpos <  20 && headpos >-1)
		{
			m_ItemHead[headpos].Load(pItem->m_pItemData->m_SmallHead);
		}
	}
	return true;
}

//在空白处加东西
bool cInterfaceItem::Add(int Pos, int CharID, sItem2* item)
{
	cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[CharID].m_pObj->m_pIndex;
	return Add(Pos, p->m_PcData, item);
}



int  cInterfaceItem::FindIdle(int StartPos, int EndPos, int PcID)
{
	cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[PcID].m_pObj->m_pIndex;
	return FindIdle(StartPos, EndPos, p->m_PcData);
}

int cInterfaceItem::FindIdle(int StartPos /*= 0*/, int EndPos /*= 60*/, cPcData& pcdata)
{
	for (int i = StartPos; i < EndPos; i++)
	{
		if (i >= pcdata.m_Items.size())
		{
			if (!pcdata.m_Fabaos[i - pcdata.m_Items.size()].GetNum())
				return i;
		}
		else
		{
			if (!pcdata.m_Items[i].GetNum())
				return i;
		}

	}
	return -1;
}

int cInterfaceItem::FindSame(int itemID, int itemType, int StartPos /*= 9*/, int EndPos /*= 28*/, int PcID /*= 2*/)
{
	cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[PcID].m_pObj->m_pIndex;
	for (int i = StartPos; i < EndPos; i++)
	{
		if (i < p->m_PcData.m_Items.size())
		{
			if (p->m_PcData.m_Items[i].m_Num)
				switch (p->m_PcData.m_Items[i].GetType())
			{
				case 22:
				case 23:
				case 25:
				case 27:
					if (1)  //只有道具可以叠加
					{
						sItem2* p2 = &p->m_PcData.m_Items[i];
						if (p2->GetID() == itemID)
							if (p2->GetType() == itemType)
								if (p2->GetNum() < 30)
								{
							return i;
								}
					}
			}
		}
		else
		{
			sItem2* p2 = &p->m_PcData.m_Items[i - p->m_PcData.m_Items.size()];
			if (p2->GetID() == itemID)
				if (p2->GetType() == itemType)
					if (p2->GetNum() == 1)
					{
				return i;
					}
		}

	}
	return -1;
}

bool cInterfaceItem::GetItem(int CharID, sItem2* pItem)
{
	if (!pItem)return false;
	if ((!pItem->m_Property.size()) && pItem->GetType()>21 && pItem->GetType()<32)
		g_pMainState->m_ItemManage.AutoItemProperty(pItem);
	int i;
	int itemType = pItem->GetType();
	int itemID = pItem->GetID();
	//	int num = pItem->GetNum();


	cct::autoSave();
	switch (itemType)
	{
		//可叠加道具
	case 22:
	case 23:
	case 25:
	case 26:
	case 27:
	case 29:
	case 40:
//	case 41:
		if (1)
		{
			i = FindSame(itemID, itemType, 0, 80, CharID);
			if (i > -1)
			{
				Overlay(i, CharID, pItem);
				return true;
			}
			else
			{
				i = FindIdle(0, 80, CharID);
				if (i > -1)
				{
					Add(i, CharID, pItem);
					return true;
				}
			}
		}
		break;
	case 24://法宝
		if (1)
		{
			bool isSame = false;
			cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[CharID].m_pObj->m_pIndex;
// 			for (int i = 0; i < 60; ++i)
// 			{
// 				if (p->m_PcData.m_Items[i].m_Num &&
// 					p->m_PcData.m_Items[i].GetType() == 24 &&
// 					p->m_PcData.m_Items[i].GetID() == itemID)
// 				{
// 					isSame = true;
// 					break;
// 				}
// 			}
			for (int i = 0; i < 20; ++i)
			{
				if (p->m_PcData.m_Fabaos[i].m_Num &&
					p->m_PcData.m_Fabaos[i].GetType() == 24 &&
					p->m_PcData.m_Fabaos[i].GetID() == itemID)
				{
					isSame = true;
					break;
				}
			}
			if (isSame)
			{
				g_pMainState->m_Tags.Add("此法宝已存在");
			}
			else if (itemID >= 11 && itemID <= 16 || itemID == 34)
			{
				int i = FindIdle(0, p->m_PcData.m_Items.size(), CharID);
				if (i > -1)
				{
					Add(i, CharID, pItem);
					return true;
				}
			}
			else 
			{
				int i = 0;
				for (; i < p->m_PcData.m_Fabaos.size(); ++i)
				{
					if (p->m_PcData.m_Fabaos[i].m_Num == 0)
					{
						break;
					}
				}
				if (i < p->m_PcData.m_Fabaos.size())
				{
					p->m_PcData.m_Fabaos[i] = *pItem;
					if (m_ItemPage >= p->m_PcData.m_Items.size())
					{
						m_ItemHead[i].Load(pItem->m_pItemData->m_SmallHead);
					}
					return true;
				}

			}
		}
		break;
	default:
		if (1) //不可叠加
		{
			int num = pItem->GetNum();
			pItem->m_Num = 1;
			for (int i = 0; i < num; i++)
			{
				int idle = FindIdle(0, 80, CharID);
				if (idle > -1)
				{
					Add(idle, CharID, pItem);
				}
				else
				{
					g_pMainState->m_Tags.Add("包裹已满");
					break;
				}
			}
			return true;
		}
		break;
	}

	return false;
}

bool cInterfaceItem::Overlay(int Pos, int CharID, sItem2* item)
{
	cCharacter* pc = (cCharacter*)g_pMainState->m_FightWorkList[CharID].m_pObj->m_pIndex;
	sItem2* pitem2 = pc->m_PcData.GetItem(Pos);
	pitem2->m_Num += item->GetNum();
	if (pitem2->GetNum() > 29)
	{
		int k = pitem2->GetNum() - 30;
		pitem2->m_Num = 30;
		int newPos = FindIdle(0, pc->m_PcData.m_Items.size(), CharID);
		int prenum = item->m_Num;
		item->m_Num = k;
		if (newPos > 0)
		{
			Add(newPos, CharID, item);
		}
		item->m_Num = prenum;
	}

	int trueid = Pos - m_ItemPage * 20;
	if (trueid<0 || trueid>19)return true;
	sItem2* pItem = pc->m_PcData.GetItem(Pos); // &pc->m_PcData.m_Items[Pos];
	if (pItem->GetNum() > 1)
	{
		ostringstream oss;
		oss.str("");
		oss << pItem->GetNum();
		m_TItemNum[trueid].SetString(oss.str());
	}
	return true;
}

bool cInterfaceItem::SwapItem(const int ID, const int IDTarget, cPcData* pcdata)
{
	if (ID == IDTarget)return true;
//	if (ID > 60 && IDTarget > 60)return true;//防止"身的装备"交换
	if (ID >= 100 && IDTarget >= 100)return true;//防止"身的装备"交换
	if (!pcdata)
	{
		pcdata = &g_pCharacter->m_PcData;
	}
	if (!(ID >= pcdata->m_Items.size() && ID < pcdata->m_Items.size() + pcdata->m_Fabaos.size()) && 
		(IDTarget >= pcdata->m_Items.size() && IDTarget < pcdata->m_Items.size() + pcdata->m_Fabaos.size()))
	{
		return false;
	}
	if ((ID >= pcdata->m_Items.size() && ID < pcdata->m_Items.size() + pcdata->m_Fabaos.size()) &&
		!(IDTarget >= pcdata->m_Items.size() && IDTarget < pcdata->m_Items.size() + pcdata->m_Fabaos.size()))
	{
		return false;
	}
	if (-1 == IDTarget)  //删除物品
	{
		if (ID >= 12000)
		{
			sItem2& Item = pcdata->m_pPets[pcdata->m_FightPetID]->m_PetData.m_Equips[ID - 12000];
//			pcdata->m_pPets[pcdata->m_FightPetID]->m_PetData.UnPetEquip(ID - 12000);
			sItem2 dustbin;
			Item.Swap(dustbin);
		}
		else
		{
			if (ID == 11000)
			{
				sItem2& Item = pcdata->m_ZuoQi.m_ZhuangShi;
				sItem2 dustbin;
				Item.Swap(dustbin);
			}
			else
			{
				if (ID >= 10000)//直接扔装备
				{
					sItem2& Item = pcdata->m_Equips[ID - 10000];
					pcdata->UnEquip(ID - 10000);
					sItem2 dustbin;
					Item.Swap(dustbin);
				}
				else
				{
// 					if (pcdata->m_Items[ID].GetType() == 24)
// 					{
// 						if (ID <= 46)
// 						{
// 							g_pMainState->m_ItemManage.SetFabaoEffect(*pcdata, -1, (eFaBao)pcdata->m_Items[ID].GetID());
// 						}
// 						else
// 						{
// 							g_pMainState->m_Tags.Add("法宝无效");
// 						}
// 					}
					sItem2& Item = ID >= pcdata->m_Items.size() ? pcdata->m_Fabaos[ID - pcdata->m_Items.size()] : pcdata->m_Items[ID];
					sItem2 dustbin;
					Item.Swap(dustbin);
				}
			}
		}
		return true;
	}

	if (ID >= 12000)
	{
		sItem2& Item = pcdata->m_pPets[pcdata->m_FightPetID]->m_PetData.m_Equips[ID - 12000];
//		pcdata->m_pPets[pcdata->m_FightPetID]->m_PetData.UnPetEquip(ID - 12000);
		Item.Swap(pcdata->m_Items[IDTarget]);
//		pcdata->m_pPets[pcdata->m_FightPetID]->m_PetData.PetEquip(ID - 12000);


	}
	else
		if (ID == 11000)
		{
		pcdata->m_ZuoQi.m_ZhuangShi.Swap(pcdata->m_Items[IDTarget]);
		}
		else
			if (ID >= 10000)
			{
		if (IDTarget >= 10000)return true;
		sItem2& itemtarget = pcdata->m_Items[IDTarget];
		pcdata->UnEquip(ID);
		pcdata->Equip(itemtarget);
		pcdata->m_Equips[ID - 10000].Swap(pcdata->m_Items[IDTarget]);
			}
			else
				if (IDTarget >= 12000)
				{
		if (-1 == pcdata->m_FightPetID)
		{
			if (!pcdata)
				g_pMainState->m_Tags.Add("无出战召唤兽");
			return true;
		}
		cPropertyData* pdata = &pcdata->m_pPets[pcdata->m_FightPetID]->m_PetData;
		sItem2& Item = pdata->m_Equips[IDTarget - 12000];
//		pdata->UnPetEquip(IDTarget - 12000);
		Item.Swap(pcdata->m_Items[ID]);
//		pdata->PetEquip(IDTarget - 12000);
				}
				else
					if (IDTarget == 11000)
					{
		pcdata->m_ZuoQi.m_ZhuangShi.Swap(pcdata->m_Items[ID]);
					}
					else
						if (IDTarget >= 10000)
						{
		pcdata->UnEquip(IDTarget - 10000);
		sItem2 itemtarget = pcdata->m_Items[ID];
		if (pcdata->Equip(itemtarget))
			pcdata->m_Equips[IDTarget - 10000].Swap(pcdata->m_Items[ID]);

						}
						else
						{
							sItem2* pItem = pcdata->GetItem(ID);
							sItem2* pItemtarget = pcdata->GetItem(IDTarget);
							int& numtarget = pItemtarget->m_Num;
							{
								int& numuser = pItem->m_Num;
								//叠加道具
								if (pItemtarget->GetNum())
									if (pItem->GetID() == pItemtarget->GetID() && pItem->GetType() == pItemtarget->GetType())
									{
									switch (pItemtarget->GetType())
									{
									case 22:
									case 23:
									case 25:
									case 27:
									case 29:
									case 30:
										if (1)
										{
											if (numtarget< 29)
											{
												numtarget += numuser;
												if (numtarget>29)
												{
													numuser = numtarget - 30;
													numtarget = 30;
												}
												else numuser = 0;
											}
										}
										return true;
									}
									}
							}
//							pcdata->m_Items[ID].Swap(pcdata->m_Items[IDTarget]);
							pcdata->GetItem(ID)->Swap(*pcdata->GetItem(IDTarget));
						}
	if (pcdata->m_Name != g_pCharacter->m_PcData.m_Name)return true;
	LoadSmallMap(ID);
	LoadSmallMap(IDTarget);
	UpdateItemNum(ID);
	UpdateItemNum(IDTarget);
	return true;
}

bool cInterfaceItem::LoadSmallMap(int ID)
{
	if (ID<1000)
		if (ID - m_ItemPage * 20 > 19 || ID - m_ItemPage * 20<0)return true;
	cCharacter* p = g_pCharacter;
	sItem2* pItem = p->m_PcData.GetItem(ID);
	if (0 == pItem->GetNum())return true;
	if (ID >= 12000)
	{
		m_PetEquipHead[ID - 12000].Load(g_pMainState->m_ItemManage.GetItem(pItem->GetType(), pItem->GetID())->m_SmallHead);
		return true;
	}
	if (ID == 11000)return true;
	if (ID < 10000)
	{
		if (ID<m_ItemPage * 20)return true;
		if (ID>m_ItemPage * 20 + 20)return true;
		if (pItem->m_Num)
			m_ItemHead[ID - m_ItemPage * 20].Load(pItem->m_pItemData->m_SmallHead);

	}
	else
	{
		ID -= 10000;
		if (pItem->m_Num)
			m_EquipHead[ID].Load(pItem->m_pItemData->m_SmallHead);
	}

	return true;
}
bool cInterfaceItem::UseItem(int ID, cPcData& pcData)
{
	return UseItem(ID, pcData.m_IDinFightWorkList);
}
bool cInterfaceItem::UseItem(int ID, int UserID)
{
	if (UserID < 0)return false;
	cCharacter* p;
	if (g_pMainState->m_FightWorkList[UserID].m_pObj->m_IndexType == INDEXTYEP_CHARACTER)
	{
		p = (cCharacter*)g_pMainState->m_FightWorkList[UserID].m_pObj->m_pIndex;
	}
	else
		return true;

	sItem2* item;
	item = p->m_PcData.GetItem(ID);
	if (item->GetNum() < 1)return false;
	if (item->GetType() < 0)return false;
	switch (item->GetType())
	{
	case 22:
		if (1)
		{
			g_pMainState->m_ItemManage.UseItem22药品(item, UserID);
			break;
		}
	case 23:
		if (1)
		{
			g_pMainState->m_ItemManage.UseItem23烹饪(item, UserID);

			break;
		}
	case 24:
		if (1)
		{
			g_pMainState->m_ItemManage.UseItem24法宝(item, UserID);
			break;
		}
	case 25:return false;//暗器无法使用
	case 26://变身卡
		if (1)
		{
			g_pMainState->m_ItemManage.UseItem26(item, UserID);
			break;
		}
	case 27:
		if (1)
		{
			g_pMainState->m_ItemManage.UseItem27道具(item, UserID, &p->m_PcData.m_Items[ID].m_Num);
		}
		break;
	case 28://不可叠加道具
		if (1)
		{
			g_pMainState->m_ItemManage.UseItem28(item, UserID);
		}
		break;
	case 31://坐骑装饰
		if (1)
		{
			if (p->m_PcData.m_Items[ID].GetID() < 24)
			{
				if (ID == 11000)
				{

					SwapItem(ID, FindIdle(0, 80, UserID), &p->m_PcData);
					SetEquipZuoQiZhuangShi(false);
				}
				else
				{
					sItem2& m_Item = p->m_PcData.m_Items[ID];
					if (p->m_PcData.m_ZuoQi.m_pZuoQi->ID != m_Item.GetID() / 3)return false;//无法装备坐骑	
					p->m_PcData.m_ZuoQi.m_ZhuangShi.Swap(m_Item);
					SetEquipZuoQiZhuangShi(true);
				}
				p->m_PcData.getObj()->Reset();
				p->m_PcData.getObj()->Set(POS_STAND);
			//	g_pMainState->m_FightWorkList[p->m_PcData.m_IDinFightWorkList].m_pObj->Reset();
			//	g_pMainState->m_FightWorkList[p->m_PcData.m_IDinFightWorkList].m_pObj->Set(POS_STAND);
			}
		}
		break;
		//武器
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
	case 42:
	case 43:
	case 44:
		if (1)
		{
			if (ID == 10002)
			{
				int targetid = FindIdle(0, p->m_PcData.m_Items.size(), UserID);
				if (targetid == -1)return false;
				SwapItem(ID, targetid, &p->m_PcData);
			}
			else
			{
				////////////////////////////////////////////////////////////////////////// 呵呵哒 未鉴定
				if (!item->m_Property.size())
				{
					g_pMainState->m_Tags.Add("未鉴定");
					return true;
				}
				sItem2& it = /*&*/*p->m_PcData.GetItem(ID)/*m_Items[ID]*/;
				if (!p->m_PcData.CanEquip(it))
				{
					g_pMainState->m_Tags.Add("无法装备");
					return true;
				}
				if (!p->m_PcData.CanEquip(it.GetType()))
				{
					int typelist[2];
					GetWeaponType(p->m_PcData.modeid, typelist[0], typelist[1]);
					int k = typelist[rand() % 2];
					if (typelist[1] == -1)
					{
						k = typelist[0];
					}
					it.m_pItemData = g_pMainState->m_ItemManage.GetItem(k, it.GetID());
				}
				SwapItem(ID, 10002, &p->m_PcData);
			}

			p->m_PcData.getObj()->Reset();
			p->m_PcData.getObj()->Set(POS_STAND);
		//	g_pMainState->m_FightWorkList[p->m_PcData.m_IDinFightWorkList].m_pObj->Reset();
		//	g_pMainState->m_FightWorkList[p->m_PcData.m_IDinFightWorkList].m_pObj->Set(POS_STAND);
			g_pMainState->m_PCHead.UpdatePcHp();
			g_pMainState->m_PCHead.UpdatePcMp();
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
		if (1)
		{

			int targetid = 0;
			if (ID >= 10000)
			{
				targetid = FindIdle(0, 80, UserID);
				if (targetid == -1)return false;
			}
			else
			{
// 				if (p->m_PcData.m_Lv < g_pMainState->m_ItemManage.GetlvByID(p->m_PcData.m_Items[ID].GetType(), p->m_PcData.m_Items[ID].GetID()))
// 				{
// 					g_pMainState->m_Tags.Add("角色等级不够");
// 					return true;
// 				}
				////////////////////////////////////////////////////////////////////////// 呵呵哒 未鉴定
				if (!item->m_Property.size())
				{
					g_pMainState->m_Tags.Add("未鉴定");
					return true;
				}
				if (!p->m_PcData.CanEquip(*item))
				{
					g_pMainState->m_Tags.Add("无法装备");
					return true;
				}

				sItem2& it = /*&*/*p->m_PcData.GetItem(ID)/*m_Items[ID]*/;
				bool isUn = !p->m_PcData.CanEquip(it.GetType());
				switch (it.GetType())
				{
				case 15:
					if (isUn)
					{
						it.m_pItemData = g_pMainState->m_ItemManage.GetItem(16, it.GetID());
					}
					targetid = 0;
					break;
				case 16:
					if (isUn)
					{
						it.m_pItemData = g_pMainState->m_ItemManage.GetItem(15, it.GetID());
					}
					targetid = 0;
					break;
				case 17:
					if (isUn)
					{
						it.m_pItemData = g_pMainState->m_ItemManage.GetItem(18, it.GetID());
					}
					targetid = 3;
					break;
				case 18:
					if (isUn)
					{
						it.m_pItemData = g_pMainState->m_ItemManage.GetItem(17, it.GetID());
					}
					targetid = 3;
					break;
				case 19:
					targetid = 1;
					break;
				case 20:
					targetid = 4;
					break;
				case 21:
					targetid = 5;
					break;
				default:
					ERRBOX;
					break;
				}
				targetid += 10000;
			}
			SwapItem(ID, targetid, &p->m_PcData);
			g_pMainState->m_PCHead.UpdatePcHp();
			g_pMainState->m_PCHead.UpdatePcMp();
		}
		break;
	case 32:
	case 33:
	case 34:
		if (1)
		{
			if (!g_pMainState->m_FightWorkList[UserID + 5].isExist)return true;

			int targetid = 0;
			if (ID >= 12000)
			{//取下
				targetid = FindIdle(0, 80, UserID);
				if (targetid == -1)return false;
			}
			else
			{//装备
				////////////////////////////////////////////////////////////////////////// 呵呵哒 未鉴定
				if (!item->m_Property.size())
				{
					g_pMainState->m_Tags.Add("未鉴定");
					return true;
				}
				sItem2& it = /*&*/*p->m_PcData.GetItem(ID)/*m_Items[ID]*/;

				if (!it.m_Property.size())return true;

				cPropertyData* Pet;
				g_pMainState->m_FightWorkList[UserID + 5].m_pObj->GetPropertyData(Pet);
				if (Pet->m_Lv < it.m_pItemData->GetLv())
				{
					g_pMainState->m_Tags.Add("召唤兽等级不够");
					return true;
				}

				switch (it.GetType())
				{
				case 32:targetid = 0; break;
				case 33:targetid = 1; break;
				default:targetid = 2; break;
				}
				targetid += 12000;
			}
			SwapItem(ID, targetid, &p->m_PcData);
			g_pMainState->m_PCHead.UpdatePet();
		}
		break;
	case 35:
	case 36:
	case 37:
	case 38:
		g_pMainState->m_ItemManage.UseJiaJu(item);
		break;
	case 41: // 符石
		if (item->GetID() < ctt::getSkillStarts().size())
		{
			auto& es = p->m_PcData.m_Equips;
			int k  = 0;
			forr(es, i)
			{
				if (i == 2)
				{
					continue;
				}
				auto& e = es[i];
				if (e.m_Num < 1)
				{
					continue;
				}
				if (e.m_Property.size() <= 15)
				{
					continue;
				}
				e.m_Property[15] = item->m_pItemData->GetLv();
				++k;
			}
			if (k == 5)
			{
				g_pMainState->m_Tags.Add("人物套装生效");
			}
			else
			{
				g_pMainState->m_Tags.Add("未生效");
			}
		}
		else if (p->m_PcData.m_FightPetID >= 0)
		{
			auto& es = p->m_PcData.m_pPets[p->m_PcData.m_FightPetID]->m_PetData.m_Equips;
			int k = 0;
			forr(es, i)
			{
				auto& e = es[i];
				if (e.m_Num < 1)
				{
					continue;
				}
				if (e.m_Property.size() <= 15)
				{
					continue;
				}
				e.m_Property[15] = item->m_pItemData->GetLv();
				++k;
			}
			if (k == 3)
			{
				g_pMainState->m_Tags.Add("召唤兽套装生效");
			}
			else
			{
				g_pMainState->m_Tags.Add("未生效");
			}
		}
		item->m_Num = 0;
		break;
	default:
		break;
	}


	int trueid;
	sItem2* pItem = 0;
	if (ID < 100)
	{
		trueid = ID - m_ItemPage * 20;
		pItem = p->m_PcData.GetItem(ID);//&p->m_PcData.m_Items[ID];
	}
	else
		if (ID == 11000)
		{
		pItem = &p->m_PcData.m_ZuoQi.m_ZhuangShi;
		}
		else if (ID<11000)
		{
			trueid = ID - 10000;
			pItem = &p->m_PcData.m_Equips[trueid];
		}
		else if (ID >= 12000)
		{
			trueid = ID - 12000;
			pItem = &p->m_PcData.m_pPets[p->m_PcData.m_FightPetID]->m_PetData.m_Equips[ID - 12000];
		}
		else ERRBOX;

		if (pItem->GetNum() > 1)
		{
			UpdateItemNum(ID);
			/*	ostringstream oss;
			oss.str("");
			oss << pItem->GetNum();
			m_TItemNum[trueid].SetString(oss.str());*/
		}
		return true;
}



bool cInterfaceItem::UpDateItemDate(cDescribe& Describe)
{
	sItem2* pItem = g_pCharacter->m_PcData.GetItem(m_NowSelect);
	return UpDateItemDate(Describe, pItem);
}

bool cInterfaceItem::UpDateItemDate(cDescribe& Describe, sItem2* pItem)
{
	return g_pMainState->m_ItemManage.SetItemDescribe(
		g_xMouse, g_yMouse, Describe, pItem);
}

bool cInterfaceItem::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		m_Select = -1;
		return false;
	}
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	auto cbSwap = [&](int select)
	{
		sItem2* pItem = g_pCharacter->m_PcData.GetItem(m_SwapID);
		if (pItem->GetType() == 24 && select != 4)
		{
			return;
		}
		if (pItem->GetType() != 24 && select == 4)
		{
			return;
		}
		int id = FindIdle(select * 20, select * 20 + 20, g_pMainState->m_HeroID);
		if (id < 0)
		{
			return;
		}
		if (!SwapItem(m_SwapID, id))
			return;
		if (m_SwapID > 10000)
		{
			g_pMainState->m_State.UpDatePcDate();
		}
		m_SwapID = -1;
		m_SwapMode = false;
		m_SelectMark.m_NeedShow = false;
	};
	switch (m_Select)
	{
	case 1:
		OnOff(false);
		return true;
	case 2:

	{
		//	cCharacter* pC = (cCharacter*)g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData->m_pIndex;
		m_XianJin.SetFrame(1);
		m_bXianJin = !m_bXianJin;
		SetXianJin(m_bXianJin);
	}
		return true;
	case 3://法宝
		if (m_SwapMode)
		{
			cbSwap(4);
		}
		else
		{
			SetItemPage(4/*2*/);
			m_frampre = 0;
		}
		return true;
	case 4://道具
		if (m_SwapMode)
		{
			cbSwap(0);
		}
		else
		{
			SetItemPage(0);
			m_frampre = 0;
		}
		return true;
	case 10010://法宝
		if (m_SwapMode)
		{
			cbSwap(2);
		}
		else
		{
			SetItemPage(2/*3*/);
			m_frampre = 0;
		}
		return true;
	case 10086://道具
		if (m_SwapMode)
		{
			cbSwap(3);
		}
		else
		{
			SetItemPage(3/*4*/);
			m_frampre = 0;
		}
		return true;
	case 5://行囊
		if (m_SwapMode)
		{
			cbSwap(1);
		}
		else
		{
			SetItemPage(1);
			m_frampre = 0;
		}
		return true;
	case 6://移动
		if (1)
		{
			m_Sleeptime = 0;
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				Move(m_xPos + xDel, m_yPos + yDel);
			}
		}
		return true;
	case 7://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	case 11: //坐骑
		if (1)
		{
			int k = m_ZuoQiB.GetNowFrame();
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
			if (k == 2)//按下
			{
				m_ZuoQiB.SetFrame(1);
				pc->m_PcData.m_bOnZuoQi = true;

			}
			else //弹起
			{
				pc->m_PcData.m_bOnZuoQi = false;
				m_ZuoQiB.SetFrame(0);
			}
			m_frampre = 0;
			g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->Reset();
			g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->Set(POS_STAND);
		}
		return true;
	case 12: //装饰
		if (m_ZuoQiZhuangShiB.GetNowFrame() == 2)//按下
		{
			SetEquipZuoQiZhuangShi(false);
			UseItem(11000, g_pMainState->m_HeroID);
		}
		return true;
	case 14:
		if (m_Mode == 2)
		{
			m_Mode = 0;
//			m_ButtonPetMode.SetFrame帧(0);
			m_ButtonPetMode.Load(0x94989763);
		}
		else
		{
			m_Mode = 2;
//			m_ButtonPetMode.SetFrame帧(1);
			m_ButtonPetMode.Load(0xB5531AC0);
			m_framprep = 0;
		}
		UpdateData();
		break;
	default:
		break;
	}

	return true;
}

bool cInterfaceItem::SetItemPage(int page)
{
	if (m_ItemPage == page)return false;
	m_ItemPage = page;
	cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
	ostringstream oss;
	int trueid;
	if (page * 20 < p->m_PcData.m_Items.size())
	{
		for (int i = 0; i < 20; i++)
		{
			trueid = i + page * 20;
			sItem2* pItem = &p->m_PcData.m_Items[trueid];
			if (pItem->GetNum()>0)
			{
				m_ItemHead[i].Load(pItem->m_pItemData->m_SmallHead);
				if (pItem->GetNum() > 1)
				{
					oss.str("");
					oss << pItem->GetNum();
					m_TItemNum[i].SetString(oss.str());
					m_TItemNum[i].m_bMove = true;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			trueid = i;
			sItem2* pItem = &p->m_PcData.m_Fabaos[trueid];
			if (pItem->GetNum()>0)
			{
				m_ItemHead[i].Load(pItem->m_pItemData->m_SmallHead);
				if (pItem->GetNum() > 1)
				{
					oss.str("");
					oss << pItem->GetNum();
					m_TItemNum[i].SetString(oss.str());
					m_TItemNum[i].m_bMove = true;
				}
			}
		}
	}

	m_ItemButton.SetFrame(0);
	m_FabaoButton.SetFrame(0);
	m_ItemButton2.SetFrame(0);
	m_ItemButton3.SetFrame(0);
	m_ItemButton4.SetFrame(0);
	switch (page)
	{
	case 0:
		m_ItemButton.SetFrame(1);
		break;
	case 1:
		m_ItemButton2.SetFrame(1);
		break;
	case 2:
		m_ItemButton3.SetFrame(1);
		break;
	case 3:
		m_ItemButton4.SetFrame(1);
		break;
	case 4:
		m_FabaoButton.SetFrame(1);
		break;
	default:
		ERRBOX
			break;
	}
	m_FabaoButton.m_bMove = true;
	m_ItemButton.m_bMove = true;
	m_ItemButton2.m_bMove = true;
	m_ItemButton3.m_bMove = true;
	m_ItemButton4.m_bMove = true;

	g_pMainState->m_Canvas.SetRedraw(m_Item.m_PreShowRect);
	return true;
}

bool cInterfaceItem::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Item.m_bMove = true;
	m_Item.m_Picture.SetXY(x, y);

	m_TCunYingN.SetXY(m_xPos + 65, m_yPos + 178);
	//设置按钮的位置
	m_ItemButton.m_Picture.m_x = x + 10;
	m_ItemButton.m_Picture.m_y = y + 420;
	m_ItemButton2.m_Picture.m_x = x + 60;
	m_ItemButton2.m_Picture.m_y = y + 420;
	m_ItemButton3.m_Picture.m_x = x + 110;
	m_ItemButton3.m_Picture.m_y = y + 420;
	m_ItemButton4.m_Picture.m_x = x + 160;
	m_ItemButton4.m_Picture.m_y = y + 420;
	m_FabaoButton.m_Picture.m_x = x + 210;
	m_FabaoButton.m_Picture.m_y = y + 420;

	m_Cancel.m_x = x + 290;
	m_Cancel.m_y = y + 4;
	m_Headback.m_Picture.m_x = x - 1;
	m_Headback.m_Picture.m_y = y + 25;
	m_PetHeadback.SetXY(x, y + 25);

	m_XianJin.m_Picture.m_x = x + 7;
	m_XianJin.m_Picture.m_y = y + 150;

	m_ButtonPetMode.SetXY(x + 10, y + 30);
//	m_ButtonPetMode.SetXY(x + 260, y + 420);

	m_tButtonPetMode.SetXCenter(m_FabaoButton.GetX() + m_FabaoButton.GetShowWidth() / 2);
	m_tButtonPetMode.SetY(m_FabaoButton.GetY() + 3);
	m_tButtonPetMode.UpdateXCenter();

	m_ZuoQiB.SetXY(x + 260, y + 420);
	m_ZuoQiZhuangShiB.SetXY(x + 7, y + 173);
	//设置物品的位置
	for (int i = 0; i < 6; i++)
	{
		int xNum = i % 2;
		int yNum = i / 2;
		m_EquipHead[i].SetXY(xNum * 54 + 201 + m_xPos, yNum * 54 + 29 + m_yPos);
		m_EquipBackP[i].m_x = m_EquipHead[i].GetX();
		m_EquipBackP[i].m_y = m_EquipHead[i].GetY();

	}
	for (int i = 0; i < 3; i++)
	{
		m_PetEquipHead[i].SetXY(m_xPos + i * 54 + 10, m_yPos + 148);
		m_PetEquipBackP[i].m_x = m_PetEquipHead[i].GetX();
		m_PetEquipBackP[i].m_y = m_PetEquipHead[i].GetY();
	}
	m_rectPetEquip.left = m_PetEquipHead[0].GetX();
	m_rectPetEquip.right = m_PetEquipHead[2].GetX() + 54;
	m_rectPetEquip.top = m_PetEquipHead[0].GetY();
	m_rectPetEquip.bottom = m_PetEquipHead[0].GetY() + 54;
	for (int i = 0; i < 20; i++)
	{
		int xNum = i % 5;
		int yNum = i / 5;
		m_ItemHead[i].SetXY(m_xPos + xNum * 51 + 29, m_yPos + yNum * 51 + 200);
		m_TItemNum[i].SetXY(m_xPos + xNum * 51 + 31, m_yPos + yNum * 51 + 202);
	}
	//设置文字位置
	m_TXianJinN.SetXY(m_xPos + 65, m_yPos + 155);
	m_TXianJin.SetXY(m_xPos + 12, m_yPos + 152);
	m_TZuoQi.SetXCenter(m_ZuoQiB.GetCenter());
	m_TZuoQi.SetY(m_ZuoQiB.m_Picture.m_y + 2);
	m_TZuoQi.UpdateXCenter();

	m_TZhuangShi.SetXCenter(m_ZuoQiZhuangShiB.GetCenter());
	m_TZhuangShi.SetY(m_ZuoQiZhuangShiB.m_Picture.m_y + 2);
	m_TZhuangShi.UpdateXCenter();

	m_BigBigHead.m_Picture.m_x = m_xPos + 38;
	m_BigBigHead.m_Picture.m_y = m_yPos + 25;

	m_Obj.SetXY(
		m_xPos + 97,
		m_yPos + 118);
	m_Obj.MoveShadow();
	m_PetName.SetXY(
		m_xPos + 185,
		m_yPos + 53);

	m_rectEquip.left = m_xPos + 200;
	m_rectEquip.top = m_yPos + 30;
	m_rectEquip.right = m_rectEquip.left + 102;
	m_rectEquip.bottom = m_rectEquip.top + 152;

	m_rectItem.left = m_xPos + 25;
	m_rectItem.top = m_yPos + 200;
	m_rectItem.right = m_rectItem.left + 255;
	m_rectItem.bottom = m_rectItem.top + 203;
	return true;
}

void cInterfaceItem::SetHaveZuoQi(bool b)
{
	// 狼, 不要坐骑,换成祥瑞
//	b = false;
	m_bCharHaveZuoQi = b;
	m_ZuoQiB.m_NeedShow = b;
}

void cInterfaceItem::SetEquipZuoQiZhuangShi(bool b)
{
	m_ZuoQiZhuangShiB.m_NeedShow = b;
}

bool cInterfaceItem::CheckZuoQi(cPcData* pc /* = nullptr */)
{
	if (!pc)
	{
		pc = &g_pCharacter->m_PcData;
	}
//	cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
	if (pc->m_ZuoQi.m_pZuoQi)
	{
		SetHaveZuoQi(true);
		//是否有装饰
		if (pc->m_ZuoQi.m_ZhuangShi.GetNum())
			SetEquipZuoQiZhuangShi(true);
		else
			SetEquipZuoQiZhuangShi(false);
	}
	else
		SetHaveZuoQi(false);
	return true;
}

bool cInterfaceItem::SetXianJin(bool b)
{
	cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
	ostringstream oss;
	m_bXianJin = b;
	if (m_bXianJin)
	{
		oss << p->m_PcData.m_Money[0];
		g_pMainState->m_Canvas.SetRedraw(m_TXianJinN.m_PreShowRect);
		m_TXianJinN.SetString(oss.str());
		m_TXianJin.SetString("现金");

	}
	else
	{
		oss << p->m_PcData.m_Money[2];
		g_pMainState->m_Canvas.SetRedraw(m_TXianJinN.m_PreShowRect);
		m_TXianJinN.SetString(oss.str());
		m_TXianJin.SetString("储备");
	}
	return true;
}

bool cInterfaceItem::ProcessSelectMap()
{
	//0长寿
	//1建邺
	//2长安
	//3AL
	//4西凉女国
	//5宝象
	//6朱紫国
	m_Select = 2;
	if (CheckRB())return true;
	if (!isInRect(g_xMouse, g_yMouse, &m_WorldMap))
		return true;
	m_NumMapSelect = -1;
	int xMouse = g_xMouse - m_WorldMap.GetX();
	int yMouse = g_yMouse - m_WorldMap.GetY();
	for (int i = 0; i < 7; i++)
	{
		if (isOn(xMouse, yMouse, m_MapRect[i]))
		{
			m_NumMapSelect = i;
			m_MapSelect.Load(m_MapID[i]);
			m_MapSelect.m_Picture.m_x = m_MapRect[i].left + m_WorldMap.m_Picture.m_x;
			m_MapSelect.m_Picture.m_y = m_MapRect[i].top + m_WorldMap.m_Picture.m_y;
			m_MapSelect.m_bMove = true;
			break;
		}
	}
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
		if (m_NumMapSelect == -1)return true;

		m_Mode = false;
		g_pMainState->m_Canvas.SetRedraw(m_WorldMap.GetPicRange());

		g_pMainState->InterfaceSetShow(this, false);
		(*pItemnum) -= 1;
		switch (m_NumMapSelect)
		{
		case 0:
			return	g_pMainState->m_Map.LoadMap(107, 60, "长寿村");
		case 1:
			return	g_pMainState->m_Map.LoadMap(60, 27, "建邺城");
		case 2:
			return	g_pMainState->m_Map.LoadMap(355, 247, "长安城");
		case 3:
			return	g_pMainState->m_Map.LoadMap(127, 92, "傲来国");
		case 4:
			return	g_pMainState->m_Map.LoadMap(93, 31, "西梁女国");
		case 5:
			return	g_pMainState->m_Map.LoadMap(115, 72, "宝象国");
		case 6:
			return	g_pMainState->m_Map.LoadMap(143, 95, "朱紫国");
		}

	}
	return true;
}

bool cInterfaceItem::ShowSelectMap()
{
	g_pMainState->m_Canvas.Add(&m_WorldMap, 1, true);
	if (m_NumMapSelect>-1)
		g_pMainState->m_Canvas.Add(&m_MapSelect, 1);

	return true;
}

void cInterfaceItem::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	g_pMainState->m_Canvas.SetRedraw(m_Item.m_PreShowRect);
	if (m_Describe.m_NeedShow)m_Describe.OnOff(false);
	if (m_NeedShow)
	{
		Init();
		m_ButtonPetMode.Load(m_Mode == 2 ? 0xB5531AC0 : 0x94989763);
		m_Cancel.SetFrame帧(0);
		for (int i = 0; i < 20; i++)
		{
			int id = i + m_ItemPage * 20;
			LoadSmallMap(id);
			UpdateItemNum(id);
		}
		UpdateData();
		if (g_pCharacter->m_PcData.m_FightPetID < 0)
			m_ButtonPetMode.m_NeedShow = false;
		else m_ButtonPetMode.m_NeedShow = true;
		CheckZuoQi();
	}
	else
	{
		cct::autoSave();
	}
}

void cInterfaceItem::SetEquipSpecial2(sItem2& ProPerty, int ID)
{
	if (ID > 49)
	{
		if (ProPerty.m_Property.size()>6)
			ProPerty.m_Property[6] = ID;
		else ERRBOX;
	}
}

void cInterfaceItem::UpdateItemNum(int ID)
{
	if (ID >1000)return;
	ostringstream oss;

	cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
	sItem2* pItem;
	int trueid = ID - m_ItemPage * 20;
//	pItem = &p->m_PcData.m_Items[ID];
	if (trueid >= 20)return;
	if (trueid < 0)return;

	pItem = p->m_PcData.GetItem(ID);
	if (!pItem->GetNum())return;
	oss << pItem->GetNum();
	m_TItemNum[trueid].SetString(oss.str());
}

bool cInterfaceItem::ProcessSelectMap2()
{
	g_pMainState->SetMouseOnMap(false);
	m_Select = 2;
	CheckRB();
	if (g_pMainState->Mouse.GetXDelta() != 0 || g_pMainState->Mouse.GetYDelta() != 0)
	{
		UpdateMousePosBack();
	}
	//导标旗
	for (int i = 0; i < m_pMapSelect->m_num; i++)
	{
		if (isOn(g_xMouse, g_yMouse, m_PathPointp[i].m_PreShowRect))
		{
			if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
			{
				g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
				g_pMainState->m_Map.LoadMap(m_pMapSelect->m_xorg[i], m_pMapSelect->m_yorg[i], (char*)m_pMapSelect->m_Name.c_str());
				m_Mode = 0;
				g_pMainState->m_Canvas.SetRedraw(m_MapSelect.m_PreShowRect);
				OnOff(false);
				return true;
			}

		}
	}
	return true;
}

bool cInterfaceItem::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	m_Describe.OnOff(false);
	switch (m_Select)
	{
	case 0:
		if (1)
		{
			if (m_SwapMode)
			{
				m_SwapMode = false;
			}
			else
			{
				cCharacter* pc = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
				if (m_NowSelect > -1)
				{
					sItem2* pItem = pc->m_PcData.GetItem(m_NowSelect);
					if (pItem->GetNum())
					{
						if (m_Mode == 2)
						{
							UseItem(m_NowSelect, g_pMainState->m_HeroID);

							for (int i = 0; i < 3; i++)
							{
								sItem2& item = pPet->m_PetData.m_Equips[i];
								if (item.GetNum())
								{
									m_PetEquipHead[i].Load(g_pMainState->m_ItemManage.GetItem(item.GetType(), item.GetID())->m_SmallHead);
								}
							}


						}
						else
						{
							UseItem(m_NowSelect, g_pMainState->m_HeroID);
							if (g_pMainState->m_State.m_NeedShow)
								g_pMainState->m_State.UpDatePcDate();
						}
					}
				}
				else
				{
					OnOff(false);
				}
			}
			m_SwapID = -1;
		}
		break;
	case 1:
		g_pMainState->m_Canvas.SetRedrawAll();
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		g_pMainState->m_Canvas.SetRedraw(m_MapBack.m_PreShowRect);
		g_pMainState->m_Canvas.SetRedraw(m_Item.m_PreShowRect);
		m_Mode = 0;
		break;
	default:
		ERRBOX;
		break;
	}
	return true;
}

bool cInterfaceItem::ShowSelectMap2()
{
	g_pMainState->m_Canvas.Add(&m_MapBack, 1, 1);
	for (int i = 0; i < m_pMapSelect->m_num; i++)
	{
		g_pMainState->m_Canvas.Add(&m_PathPointp[i], 1);
	}
	if (m_MousePos.m_NeedShow)
	{
		g_pMainState->m_Canvas.Add(&m_MousePosBack, 1);
		g_pMainState->m_Canvas.Add(&m_MousePos);
	}
	return true;
}

void cInterfaceItem::InitMode(int id)
{
	m_Mode = id;
	g_pMainState->m_Canvas.SetRedraw(g_pMainState->m_InterfaceItem.m_Item.m_PreShowRect);
	switch (m_Mode)
	{
	case 0:
		return;
	case 1:
		g_pMainState->m_Canvas.SetRedrawAll(); return;
	case 12:
	case 13:
	case 14:
	case 15:
	case 34:
		m_pMapSelect = &m_sMapSelect[(m_Mode == 34 ? 16 : m_Mode) - 12];
		m_MapBack.LoadMap(m_pMapSelect->m_SmallMap);
		UpdateMousePosBack();
		break;
	case 6://月光
		if (1)
		{
			sItem2* pItem = nullptr;
			int i;//寻找月光宝盒的位置
			for (i = 0; i <g_pCharacter->m_PcData.m_Items.size(); i++)
			{
				pItem = &g_pCharacter->m_PcData.m_Items[i];
				if (pItem->GetType() == 24)
				{
					if (11 == pItem->GetID())
					{
						break;
					}
				}
				pItem = nullptr;
			}
// 			for (i = 0; i < g_pCharacter->m_PcData.m_Fabaos.size(); i++)
// 			{
// 				pItem = &g_pCharacter->m_PcData.m_Fabaos[i];
// 				if (pItem->GetType() == 24)
// 				{
// 					if (11 == pItem->GetID())
// 					{
// 						break;
// 					}
// 				}
// 			}
			if (0 == pItem) return/*ERRBOX*/;
			string str;
			if (pItem->m_Property.size() == 3)
			{
				ostringstream oss;
				oss << "是否要传送到#Y";
				oss << pItem->m_strProperty;
				oss << "#Y#R ";
				oss << pItem->m_Property[1];
				oss << " ";
				oss << pItem->m_Property[2];
				oss << "#R ?";
				str = oss.str();
				g_pMainState->m_Dialog.Reset();
				g_pMainState->m_Dialog.SetObj(g_pCharacter->m_PcData.m_Name);
				g_pMainState->m_Dialog.SetString(str, "传送", "在这里定坐标");
				g_pMainState->m_Dialog.OnOff(true);
				g_pMainState->m_Dialog.m_bRetSelect = true;
			}
			else
			{
				cObj* pUser = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj;
				pItem->m_strProperty = g_pMainState->m_Map.m_MapName;
				int xpos = pUser->GetX() / 20;
				int ypos = (g_pMainState->m_Map.m_pMap->m_Height - pUser->GetY()) / 20;
				pItem->m_Property.push_back(xpos);
				pItem->m_Property.push_back(ypos);
				g_pMainState->m_Tags.Add("你在当前位置定了坐标");
				InitMode(0);
			}
			return;
		}
		break;
	default:
		ERRBOX;
		break;
	}
	m_MapBack.SetXY(g_half320 - m_MapBack.GetWidth() / 2, g_half240 - m_MapBack.GetHeight() / 2);
	int num = m_pMapSelect->m_x.size();
	for (int i = 0; i < num; i++)
	{
		m_PathPointp[i].SetXY(m_MapBack.GetX() + m_pMapSelect->m_x[i], m_MapBack.GetY() + m_pMapSelect->m_y[i]);
	}
}

void cInterfaceItem::UpdateMousePosBack()
{
	m_MousePos.SetXY(g_xMouse - m_MousePosBack.m_Picture.m_Width / 2 + 10, g_yMouse - 15);
	m_MousePosBack.m_Picture.m_x = g_xMouse - m_MousePosBack.m_Picture.m_Width / 2;
	m_MousePosBack.m_Picture.m_y = g_yMouse - 20;
	int tx = (g_xMouse - m_MapBack.m_Picture.m_x - 18);
	int ty = (g_yMouse - m_MapBack.m_Picture.m_y - 18);
	tx = (int)(tx*m_pMapSelect->m_bili);
	ty = (int)(ty*m_pMapSelect->m_bili);
	ty = m_pMapSelect->m_Height - ty;
	tx /= 20;
	ty /= 20;
	ostringstream oss;
	oss << "X:";
	oss << tx;
	oss << " Y:";
	oss << ty;
	m_MousePos.SetString(oss.str());
}

void cInterfaceItem::SetEquipSpecial(sItem2& ProPerty, int ID)
{
	if (ID < 50)
	{
		if (ProPerty.m_Property.size()>5)
			ProPerty.m_Property[5] = ID; //设置特技
		else ERRBOX;
	}
}

void cInterfaceItem::UpdateData()
{
	if (m_Mode == 2)
	{
		if (g_pCharacter->m_PcData.m_FightPetID > -1)
		{
			pPet = g_pCharacter->m_PcData.m_pPets[g_pCharacter->m_PcData.m_FightPetID];
			m_Obj.m_pIndex = pPet;
			m_Obj.Reset();
			m_Obj.Set(POS_STAND);
			m_PetName.SetString(pPet->m_PetData.m_Name);
			for (int i = 0; i < 3; i++)
			{
				sItem2& item = pPet->m_PetData.m_Equips[i];
				if (item.GetNum())
				{
					m_PetEquipHead[i].Load(g_pMainState->m_ItemManage.GetItem(item.GetType(), item.GetID())->m_SmallHead);
				}
			}
		}
	}
	else
	{
		CheckZuoQi();
		for (int i = 10000; i < 10006; i++)
		{
			LoadSmallMap(i);
		}
		cCharacter* pc = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
		ostringstream oss;
		oss << pc->m_PcData.m_Money[1];//存银
		m_TCunYingN.SetString(oss.str());
		SetXianJin(m_bXianJin);
		m_BigBigHead.Load(pc->GetID(POS_BIGHEAD));
	}
	g_pMainState->m_Canvas.SetRedraw(m_Headback.m_PreShowRect);
}

cInterfaceItem::~cInterfaceItem()
{
	m_Obj.m_pIndex = 0;
	m_Obj.m_IndexType = 0;
}
