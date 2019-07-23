#include "_global.h"

// 
// void uiBuyPet::refresh(int i)
// {
// 	m_ItemNum = i % 20;
// 	int model = i;//rand() % c_PetNumber;
// 	auto& pet = m_Item[i % 20] = new cPet;
// 	pet->SetData(g_pMainState->m_PetDataManager.GetPetData(ccm::getModel(model)));
// 	auto& p = pet->m_PetData;
// 	p.Load(model, true, true);
// 	p.SetJinJie(rand() % 4);
// 	
// // 	int n = -1;
// // 	forv(p.m_petSkills, k)
// // 	{
// // 		if (rand() % 100 < (5 + rand() % 30))
// // 		{
// // 			p.AddSkill(rand() % c_NumPetSkill, ++n);
// // 		}
// // 	}
// // 	auto& z = p.m_ZiZhi;
// // 	auto cb = [](int& zz, int percent)
// // 	{
// // 		zz = zz + rand() % (1 + zz * percent / 100) - rand() % (1 + zz * percent / 100);
// // 	};
// // 	for (int k = rand() % 0xFF; k >= 0; --k)
// // 	{
// // 		cb(z.atk, 4);
// // 		cb(z.def, 4);
// // 		cb(z.hp, 4);
// // 		cb(z.mag, 4);
// // 		cb(z.speed, 4);
// // 		cb(z.avoid, 4);
// // 		cb(z.grow, 1);
// // 	}
// 	while (p.m_Lv < 30)
// 	{
// 		p.m_EXP += GetPetExp(p.m_Lv + 1);
// 		p.lvup();
// 	}
// 	p.apply();
// 	p.FillHpMp();
// 
// 	int price = 30000;
// 	int price2 = 0;
// 	for (int i = 0; i < p.m_NumofBBSkill; ++i)
// 	{
// 		price += price / 2 + rand() % (price / 2);
// 		price2 += price;
// 	}
// 	Set(pet, price2);
// }
// 


bool uiBuyPet::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_NumBuy.SetMaxNum(1);
	m_PriceTotal = 0;
// 	m_Left.Load(0xB05126E8);
// 	m_Left.SetStatic(true);
// 	m_Right.Load(0x26066130);
// 	m_Right.SetStatic(true);

	m_SelectMark.Load(0x10921CA7);
	m_TrueSelect = -1;
	m_Button.Load(g_pMainState->m_Button2.m_NowID);
	m_Button.SetStatic(true);
	m_Button2.Load(g_pMainState->m_Button2.m_NowID);
	m_Button2.SetStatic(true);
	m_MouseOnMark.Load(0x6F88F494);
	m_MouseOnMark.m_NeedShow = false;
	m_Back.Load(3929029437);
	m_Back.SetShowHeight(275);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Text[4].SetColor(RGB(240, 240, 240));
	m_Text[4].SetString("取出");
	m_Text[1].SetColor(0);

	m_Text[5].SetColor(RGB(240, 240, 240));
	m_Text[5].SetString("召唤兽仓库");

	m_Text[2].SetColor(RGB(240, 240, 240));
	m_Text[2].SetString("放生");
// 	forr(m_Item, i)
// 	{
// 		m_Item[i] = nullptr;
// 		refresh(i);
// 	}
// 	int n = 160;
// 	for (int i = 0; i < 19; ++i)
// 	{
// 		m_Item[i] = nullptr;
// 		refresh(i + n);
// 	}

	Move(200 + g_half320 - 320, 30 + g_half240 - 240);
	return true;
}



bool uiBuyPet::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, true);

	for (int i = 0; i < m_Item.size(); i++)
	{
		pCanvas->Add(&m_ItemHead[i], 1);
	}
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_Button, 1);
	pCanvas->Add(&m_Button2, 1);

	if (m_Select > -1)
	{
		pCanvas->Add(&m_MouseOnMark, 1);
	}

	if (m_TrueSelect > -1)
	{
		pCanvas->Add(&m_SelectMark, 1);
	}
	for (int i = 4/*0*/; i < 6; i++)
	{
//		if (i == 1)continue;
		pCanvas->Add(&m_Text[i]);
	}

	pCanvas->Add(&m_Text[2]);

// 	m_NumBuy.Show(pCanvas);
// 	pCanvas->Add(&m_Left, 1);
// 	pCanvas->Add(&m_Right, 1);
	return true;
}

bool uiBuyPet::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	if (m_NumBuy.Process())
	{
		CoutTotal();
		return true;
	}
	m_MouseOnMark.m_NeedShow = false;
	g_pMainState->SetMouseOnMap(false);
	m_Select = -1;
	ResetButton();

	if (m_PriceTotal)
	{
		switch (g_pMainState->m_Dialog.m_retSelect)
		{
		case 0:
			m_PriceTotal = 0;
			if (0 == g_pMainState->m_Dialog.m_NowMouseOnSelect)
			{
				SAFE_DELETE(m_Item[m_TrueSelect]);
				m_Item.erase(m_Item.begin() + m_TrueSelect);
				initShow();
			}
			g_pMainState->m_Dialog.m_NeedShow = false;
			return true;
		default:
			m_PriceTotal = 0;
			return true;
		}
	}


	if (m_bMoveMode)//移动
	{
		m_Select = 106;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}

	if (!isInRect(g_xMouse, g_yMouse, &m_Back))return true;
// 	if (CheckOn(&m_Left, 102))return true;
// 	if (CheckOn(&m_Right, 103))return true;
	if (isOn(g_xMouse, g_yMouse, m_Rect))
	{
		m_Select = (g_xMouse - m_Rect.left) / 51 + 5 * ((g_yMouse - m_Rect.top) / 51);
		if (m_Select < m_Item.size())
		{
			m_MouseOnMark.m_NeedShow = true;
			m_MouseOnMark.SetXY(m_ItemHead[m_Select].GetX(), m_ItemHead[m_Select].GetY() - 7);
			if (CheckL())return true;
			if (CheckRB())return true;
		}
	}
	//取消按钮
	if (CheckOn(&m_Cancel, 100))return true;
	//确定按钮
	if (CheckOn(&m_Button, 101))return true;
	if (CheckOn(&m_Button2, 102))return true;
	m_Select = 100;
	if (CheckRB())return true;
	//准备移动
	m_Select = 107;
	CheckL();
	return true;
}

bool uiBuyPet::Set(cPet* item, int rate)
{
// 	if (m_Item.size() == m_ItemNum || m_ItemNum < 0)
// 		return false;
// 	m_pricerate[m_ItemNum] = rate;
// 	m_Item[m_ItemNum] = item;
// //	ulong headid = g_pMainState->m_PetDataManager.m_PetList[item.m_modeid].GetID(0, POS_BIGHEAD);
// 	m_ItemHead[m_ItemNum].Load(item->GetData()->m_bighead[item->m_PetData.m_JinJieNum.GetBJinJie()]);
// //	m_ItemNum += 1;
	return true;
}



bool uiBuyPet::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;

	m_Text[0].SetXY(m_xPos + 135, m_yPos + 287);
	RECT rect;
	rect.left = m_xPos + 135;
	rect.top = m_yPos + 310;
	rect.right = rect.left + 75;
	rect.bottom = rect.top + 18;
	m_NumBuy.Init(rect);
	m_Text[2].SetXY(m_xPos + 135, m_yPos + 333);
	m_Text[3].SetXY(m_xPos + 135, m_yPos + 356);

	m_Back.SetXY(x, y);
	m_Cancel.m_x = m_xPos + 256;
	m_Cancel.m_y = m_yPos + 10;
	m_Button.m_Picture.m_x = m_xPos + 131 - 65;
	m_Button.m_Picture.m_y = m_yPos + 392 - 130;

	m_Button2.m_Picture.m_x = m_xPos + 131 + 35;
	m_Button2.m_Picture.m_y = m_yPos + 392 - 130;

	m_Text[4].SetXCenter(m_Button.GetCenter());
	m_Text[4].SetY(m_Button.GetY() + 3);
	m_Text[4].UpdateXCenter();
	m_Text[5].SetXCenter(m_xPos + 140);
	m_Text[5].SetY(m_yPos + 10);
	m_Text[5].UpdateXCenter();

	m_Text[2].SetXCenter(m_Button2.GetCenter());
	m_Text[2].SetY(m_Button2.GetY() + 3);
	m_Text[2].UpdateXCenter();


	m_Rect.left = 15 + m_xPos;
	m_Rect.top = 48 + m_yPos;
	m_Rect.right = m_Rect.left + 255;
	m_Rect.bottom = m_Rect.top + 204;
	for (int i = 0; i < 20; i++)
	{
		int xNum = i % 5;
		int yNum = i / 5;
		m_ItemHead[i].SetXY(xNum * 51 + m_Rect.left, yNum * 51 + m_Rect.top);
	}
	if (m_TrueSelect>-1)
		m_SelectMark.m_Picture.SetXY(m_ItemHead[m_TrueSelect].GetX(), m_ItemHead[m_TrueSelect].GetY() - 7);

// 	m_Left.SetXY(m_xPos + 20, m_yPos + 252);
// 	m_Right.SetXY(m_xPos + 70, m_yPos + 252);

	return true;
}

bool uiBuyPet::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 106://移动
		if (1)
		{
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				Move(m_xPos + xDel, m_yPos + yDel);
			}
			m_Sleeptime = 0;
		}
		return true;
	case 107://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		m_Sleeptime = 0;
		return true;
	case 100:
		OnOff(false);
		break;
	case 101:
		if (1)
		{
			m_Button.SetFrame(1);
			if (m_NumBuy.m_num == 0)
				return true;

			if (m_TrueSelect < 0)return true;
			auto& pc = g_pCharacter->m_PcData;
			if (pc.m_NumofBB >= pc.m_pPets.size())
			{
				g_pMainState->m_Tags.Add("召唤兽已满");
				return true;
			}

// 			auto& money = pc.m_Money[0];
// 			if (money < m_PriceTotal)
// 			{
// 				g_pMainState->m_Tags.Add("盘缠不足");
// 				return true;
// 			}
// 			money -= m_PriceTotal;
			g_pMainState->m_Tags.Add("你取出了召唤兽");
//			m_Item[m_TrueSelect]->m_PetData.PointRemain += cct::point额外;
			pc.AddPet(m_Item[m_TrueSelect]);
			m_Item.erase(m_Item.begin() + m_TrueSelect);
			int pid = pc.m_FightPetID;
			pc.m_FightPetID = -1;
			g_pMainState->SetFightPet(g_pMainState->m_HeroID, pc.m_NumofBB - 1);
			g_pMainState->SetFightPet(g_pMainState->m_HeroID, pid);
			initShow();
		}
		break;
	case 102:
	{
		m_PriceTotal = 0;
		if (m_TrueSelect < 0)return true;
		m_PriceTotal = 1;
		g_pMainState->m_Dialog.Reset();
		g_pMainState->m_Dialog.SetPet(m_Item[m_TrueSelect]);
		g_pMainState->m_Dialog.SetString("是否放生?", "是", "否");
		g_pMainState->m_Dialog.OnOff(true);
		g_pMainState->m_Dialog.m_bRetSelect = true;
	}
		break;
// 	case 102://左
// 		if (1)
// 		{
// 			m_frampre->SetFrame(1);
// 			SubPage();
// 		}
// 		break;
// 	case 103://右
// 		if (1)
// 		{
// 			m_frampre->SetFrame(1);
// 			AddPage();
// 		}
// 		break;
	default:
		if (1)
		{
			// 狼: 该死的无符号
			if (m_TrueSelect >= (int)m_Item.size())
			{
				m_NumBuy.Reset();
				return true;
			}
			if (m_Select == m_TrueSelect)
			{
				m_NumBuy.SetNum(m_NumBuy.m_num + 1);
				m_NumBuy.SetActive(true);
			}
			else
			{
				m_TrueSelect = m_Select;
				m_NumBuy.SetNum(1);
				m_NumBuy.SetActive(true);
			}
			CoutTotal();
			m_SelectMark.m_Picture.SetXY(m_ItemHead[m_TrueSelect].GetX(), m_ItemHead[m_TrueSelect].GetY() - 7);
		}
		break;
	}
	return true;
}

// void uiBuyPet::OnOff(bool bshow)
// {
// 	if (m_NeedShow == bshow)return;
// 	g_pMainState->InterfaceSetShow(this, bshow);
// 	if (m_NeedShow)
// 	{
// 		Init();
// 		m_TrueSelect = -1;
// 		UpdateText();
// 		m_Sleeptime = 0;
// 	}
// 	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
// 
// }

void uiBuyPet::UpdateText()
{
	ostringstream  oss;
	int price;
	if (m_TrueSelect < 0)
	{
		m_NumBuy.Reset();
		m_PriceTotal = 0;
		price = 0;
	}
	else
	{
// 		price = m_Item[m_TrueSelect].m_price;
// 		if (m_pricerate[m_TrueSelect] != 100)
// 			price = price*m_pricerate[m_TrueSelect] / 100;
		price = m_pricerate[m_TrueSelect];
	}
	m_Text[0].SetString(price);
	m_Text[2].SetString(m_PriceTotal);
// 	if (m_plist)
// 		m_Text[3].SetString(m_plist->m_money);
// 	else  	
		m_Text[3].SetString(g_pCharacter->m_PcData.m_Money[0]);
}

bool uiBuyPet::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 100:
		OnOff(false);
		break;
	default:
		g_pMainState->m_ChaKan.Set(m_Item[m_Select]);
		g_pMainState->m_ChaKan.OnOff(true);
		break;
	}
	return true;
}

void uiBuyPet::CoutTotal()
{
	return;

	if (-1 == m_TrueSelect)ERRBOX;
	INT64 money;
// 	if (m_plist)
// 		money = m_plist->m_money;
//	else 
		money = g_pCharacter->m_PcData.m_Money[0];
//	int price = m_Item[m_TrueSelect].m_price;
	int price = m_pricerate[m_TrueSelect];
// 	if (m_pricerate[m_TrueSelect] != 100)
// 		price = price*m_pricerate[m_TrueSelect] / 100;
	m_PriceTotal = m_NumBuy.m_num*price;
	if (m_PriceTotal > money)
	{
		m_NumBuy.SetNum((money / price));
		m_PriceTotal = m_NumBuy.m_num*price;
	}
	UpdateText();
}

bool uiBuyPet::initShow()
{
	if (m_TrueSelect >= m_Item.size())
	{
		m_TrueSelect = -1;
	}
//	UpdateText();
	m_Sleeptime = 0;
	forv(m_Item, i)
	{
		m_ItemHead[i].Load(m_Item[i]->GetData()->m_bighead[m_Item[i]->m_PetData.m_JinJieNum.GetBJinJie()]);
	}
	for (int i = m_Item.size(); i < m_ItemHead.size(); ++i)
	{
		m_ItemHead[i].Load(0);
	}
	return true;
}

void uiBuyPet::addPet(cPet* p)
{
	if (m_Item.size() >= 20)
	{
		return;
	}
	m_Item.push_back(p);
	initShow();
}























void sShangPinPet::Read(ifstream& File)
{
	File >> m_modeid;
	File >> m_name;
	int skillnum;
	File >> skillnum;
	if (skillnum == -1)
	{
		sPetData* p = g_pMainState->m_PetDataManager.GetPetData(m_modeid);
		skillnum = p->m_SkillNum;
		m_skillid.resize(skillnum);
		for (int i = 0; i < skillnum; i++)
		{
			m_skillid[i] = p->m_pPetSkill[i]->m_Id;
		}
	}
	else
	{
		m_skillid.resize(skillnum);
		for (int i = 0; i < skillnum; i++)
		{
			File >> m_skillid[i];
		}
	}
	File >> m_price;
	int type;
	File >> type;
	switch (type)
	{
	case 0:m_addpoint.Set(4, 0, 0, 1, 0); break;
	case 1:m_addpoint.Set(0, 0, 4, 1, 0); break;
	case 2:m_addpoint.Set(0, 0, 0, 5, 0); break;
	default:ERRBOX;
	}
	sPetData& data = g_pMainState->m_PetDataManager.m_PetList[m_modeid];
//	m_zizhi.Set(data.m_ZiZhi, 50, data.m_LvTake);
	m_zizhi = data.m_ZiZhi;
	for (int i = 0; i < 4; i++)
		m_ranse.m_ranse[i].partnum = 0;

}
void sShangPinPet::Save(ofstream& File)
{
	File << " ";
	File << m_modeid << " ";
	File << m_name << " ";
	File << m_skillid.size() << " ";
	for (int i = 0; i < m_skillid.size(); i++)
	{
		File << m_skillid[i] << " ";
	}
	File << m_price << " ";
	m_addpoint.Save(File);
//	m_zizhi.Save(File);
	File << "0 ";// m_ranse.Save(File);
	File << "\n";
}
void sShangPinPet::Load(ifstream& File, int postion)
{
	File >> m_modeid;
	File >> m_name;
	int num;
	File >> num;
	m_skillid.resize(num);
	for (int i = 0; i < m_skillid.size(); i++)
	{
		File >> m_skillid[i];
	}
	File >> m_price;
	m_addpoint.Load(File);
//	m_zizhi.Load(File);
	m_ranse.Read(m_modeid, File, postion);
}



void sShangPinPet::Set(int modeid, sAddPoint* addpoint, int stronglv, bool needskill)
{
	if (!addpoint)
	{
		m_addpoint.Set(4, 0, 0, 1, 0);
	}
	else
		m_addpoint = *addpoint;
	sPetData* ppet = g_pMainState->m_PetDataManager.GetPetData(modeid);
//	m_zizhi.Set(ppet->m_ZiZhi, stronglv, ppet->m_LvTake);
	m_zizhi = ppet->m_ZiZhi;
	m_modeid = modeid;
	m_name = ppet->m_Name;
	m_price = 0;
	m_ranse.Reset();
	m_skillid.clear();
	if (needskill)
		for (int i = 0; i < ppet->m_SkillNum; i++)
			m_skillid.push_back(ppet->m_pPetSkill[i]->m_Id);
}

void sShangPinPet::AddSkill(int id)
{
	m_skillid.push_back(id);
}

void sShangPinPet::LoadEasy(int id, int strong)
{
//	*this = g_pMainState->m_InterFaceBuyPet.GetPet3(id);
//	m_zizhi.Set(m_zizhi, strong, g_pMainState->m_PetDataManager.GetPetData(m_modeid)->m_LvTake);
}




bool cInterFaceBuyPet::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_NumBuy.SetMaxNum(1);
	m_PriceTotal = 0;
	m_Left.Load(0xB05126E8);
	m_Left.SetStatic(true);
	m_Right.Load(0x26066130);
	m_Right.SetStatic(true);

	m_SelectMark.Load(0x10921CA7);
	m_TrueSelect = -1;
	m_Button.Load(0x35A981D3);
	m_Button.SetStatic(true);
	m_MouseOnMark.Load(0x6F88F494);
	m_MouseOnMark.m_NeedShow = false;
	m_Back.Load(3929029437);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Text[4].SetColor(RGB(240, 240, 240));
	m_Text[4].SetString("确定");
	m_Text[1].SetColor(0);

	m_Text[5].SetColor(RGB(240, 240, 240));
	m_Text[5].SetString("购买");

	ifstream file;
	ostringstream oss;
	// 	oss << g_strMyDataPath;
	// 	oss << "任务//召唤兽商店//召唤兽列表.txt";
//	oss << g_pathData;
	oss << "_召唤兽商店.txt";
	file.open(oss.str());
	int lvlimit, num;

	vector<int> id1s = { 84, 94, 95, 96, 97, 98/*, 100*/, 101, 102, 103, 104, 105, 106, 107, 123, 130, 149, 150, 151, 152, 153 };
	vector<string> name1s = { "人参娃娃", "超级泡泡", "大熊猫", "金猴", "大象", "白泽", /*"赤炎兽",*/ "大鹏", "善财童子", "筋斗云", "神牛", "神虎", "海豚", "神兔", "神龙", "腾蛇", "玉兔", "孔雀", "灵狐", "神蛇", "神马" };
	vector<int>id2s = { 154, 155, 158, 159, 108, 109, 110, 111, 112, 113 };
	vector<string> name2s = { "青鸾", "麒麟", "神羊", "六耳猕猴", "小毛头", "小丫丫", "小仙灵", "小仙女", "小精灵", "小魔头" };
	// 第二页倒一下
	auto ids = id1s;
	forv(id1s, i)ids.push_back(id1s[i]);
	forv(id2s, i)ids.push_back(id2s[i]);
	forv(id2s, i)ids.push_back(id2s[i]);
	std::swap(ids[20], ids[21]);

	auto names = name1s;
	forv(name1s, i)names.push_back(name1s[i]);
	forv(name2s, i)names.push_back(name2s[i]);
	forv(name2s, i)names.push_back(name2s[i]);
	std::swap(names[20], names[21]);

	for (int i = 0; i < 8; i++)
	{
		file >> lvlimit;
		file >> num;
		getline(file, string());
		vector<sShangPinPet>&  list = m_ShangPinList[i];
		list.resize(num);
		if (i == 0)
		{
			vector<int> skill1s;
			vector<int> skill2s;
			int skillnum1;
			int skillnum2;

			file >> skillnum1;
			skill1s.resize(skillnum1);
			for (int k = 0; k < skillnum1; ++k)file >> skill1s[k];

			file >> skillnum2;
			skill2s.resize(skillnum2);
			for (int k = 0; k < skillnum2; ++k)file >> skill2s[k];

			for (int k = 0; k < num; ++k)
			{
				bool isAtk = k < 20 || (k >= 40 && k < 50);
				auto &p = list[k];
				p.m_modeid = ids[k];
				p.m_name = names[k];
				p.m_skillid = isAtk ? skill1s : skill2s;
				if (isAtk && rand() % 100 < 20)
				{
					p.m_skillid.push_back(95);
				}
				else if (!isAtk)
				{
					p.m_skillid.push_back(85 + (rand() % 4) * 2);
				}
				p.m_price = 10000;
				if (isAtk)p.m_addpoint.Set(4, 0, 0, 1, 0);
				else p.m_addpoint.Set(0, 0, 4, 1, 0);

				sPetData& data = g_pMainState->m_PetDataManager.m_PetList[p.m_modeid];
//				p.m_zizhi.Set(data.m_ZiZhi, 50, data.m_LvTake);
				p.m_zizhi = data.m_ZiZhi;
				for (int r = 0; r < 4; ++r)
					p.m_ranse.m_ranse[i].partnum = 0;
			}
			continue;
		}
		for (int i2 = 0; i2 < num; i2++)
		{
			list[i2].Read(file);
			auto &eList = list[i2];
//			const auto &babys = ccm::get()->newBabys;
			set<int> babys;
			if (babys.find(eList.m_modeid) != babys.end())
			{
				const auto &newPet = g_pMainState->m_PetDataManager.m_PetList[eList.m_modeid];
				eList.m_name = newPet.m_Name;
				eList.m_skillid.clear();
				for (int k = 0; k < newPet.m_SkillNum; ++k)
				{
					eList.m_skillid.push_back(newPet.m_pPetSkill[k]->m_Id);
				}
				sZiZhi zz = newPet.m_ZiZhi;
//				eList.m_zizhi.Set(zz, 50, newPet.m_LvTake);
				eList.m_zizhi = zz;
				// 加点
// 				vector<sSkill*> skills;
// 				for (int j = 0; j < newPet.m_SkillNum; j++)
// 				{
// 					skills.push_back(newPet.m_pPetSkill[j]);
// 				}
				eList.m_addpoint = g_pMainState->getAddpointFromPet((cPetData*)&newPet, true);
			}
		}
	}
	file.close();

	Move(200, 30);
	return true;
}

bool cInterFaceBuyPet::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, true);

	for (int i = 0; i < m_ItemNum; i++)
	{
		pCanvas->Add(&m_ItemHead[i], 1);
	}
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_Button, 1);

	if (m_Select > -1)
	{
		pCanvas->Add(&m_MouseOnMark, 1);
	}

	if (m_TrueSelect>-1)
	{
		pCanvas->Add(&m_SelectMark, 1);
	}
	for (int i = 0; i < 6; i++)
	{
		if (i == 1)continue;
		pCanvas->Add(&m_Text[i]);
	}
	m_NumBuy.Show(pCanvas);
	pCanvas->Add(&m_Left, 1);
	pCanvas->Add(&m_Right, 1);
	return true;
}

bool cInterFaceBuyPet::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	if (m_NumBuy.Process())
	{
		CoutTotal();
		return true;
	}
	m_MouseOnMark.m_NeedShow = false;
	g_pMainState->SetMouseOnMap(false);
	m_Select = -1;
	ResetButton();

	if (m_bMoveMode)//移动
	{
		m_Select = 106;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}

	if (!isInRect(g_xMouse, g_yMouse, &m_Back))return true;
	if (CheckOn(&m_Left, 102))return true;
	if (CheckOn(&m_Right, 103))return true;
	if (isOn(g_xMouse, g_yMouse, m_Rect))
	{
		m_Select = (g_xMouse - m_Rect.left) / 51 + 5 * ((g_yMouse - m_Rect.top) / 51);
		if (m_Select < m_ItemNum)
		{
			m_MouseOnMark.m_NeedShow = true;
			m_MouseOnMark.SetXY(m_ItemHead[m_Select].GetX(), m_ItemHead[m_Select].GetY() - 7);
			if (CheckL())return true;
			if (CheckRB())return true;
		}
	}
	//取消按钮
	if (CheckOn(&m_Cancel, 100))return true;
	//确定按钮
	if (CheckOn(&m_Button, 101))return true;
	m_Select = 100;
	if (CheckRB())return true;
	//准备移动
	m_Select = 107;
	CheckL();
	return true;
}

bool cInterFaceBuyPet::Set(sShangPinPet& item, int rate)
{
	if (20 == m_ItemNum)return false;
	m_pricerate[m_ItemNum] = rate;
	m_Item[m_ItemNum] = item;
	ulong headid = g_pMainState->m_PetDataManager.m_PetList[item.m_modeid].GetID(0, POS_BIGHEAD);
	m_ItemHead[m_ItemNum].Load(headid);
	m_ItemNum += 1;
	return true;
}



bool cInterFaceBuyPet::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;

	m_Text[0].SetXY(m_xPos + 135, m_yPos + 287);
	RECT rect;
	rect.left = m_xPos + 135;
	rect.top = m_yPos + 310;
	rect.right = rect.left + 75;
	rect.bottom = rect.top + 18;
	m_NumBuy.Init(rect);
	m_Text[2].SetXY(m_xPos + 135, m_yPos + 333);
	m_Text[3].SetXY(m_xPos + 135, m_yPos + 356);

	m_Back.SetXY(x, y);
	m_Cancel.m_x = m_xPos + 256;
	m_Cancel.m_y = m_yPos + 10;
	m_Button.m_Picture.m_x = m_xPos + 131;
	m_Button.m_Picture.m_y = m_yPos + 392;
	m_Text[4].SetXCenter(m_Button.GetCenter());
	m_Text[4].SetY(m_Button.GetY() + 3);
	m_Text[4].UpdateXCenter();
	m_Text[5].SetXCenter(m_xPos + 140);
	m_Text[5].SetY(m_yPos + 10);
	m_Text[5].UpdateXCenter();
	m_Rect.left = 15 + m_xPos;
	m_Rect.top = 48 + m_yPos;
	m_Rect.right = m_Rect.left + 255;
	m_Rect.bottom = m_Rect.top + 204;
	for (int i = 0; i < 20; i++)
	{
		int xNum = i % 5;
		int yNum = i / 5;
		m_ItemHead[i].SetXY(xNum * 51 + m_Rect.left, yNum * 51 + m_Rect.top);
	}
	if (m_TrueSelect>-1)
		m_SelectMark.m_Picture.SetXY(m_ItemHead[m_TrueSelect].GetX(), m_ItemHead[m_TrueSelect].GetY() - 7);

	m_Left.SetXY(m_xPos + 20, m_yPos + 252);
	m_Right.SetXY(m_xPos + 70, m_yPos + 252);

	return true;
}

bool cInterFaceBuyPet::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 106://移动
		if (1)
		{
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				Move(m_xPos + xDel, m_yPos + yDel);
			}
			m_Sleeptime = 0;
		}
		return true;
	case 107://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		m_Sleeptime = 0;
		return true;
	case 100:
		OnOff(false);
		break;
	case 101:
		if (1)
		{
			m_Button.SetFrame(1);
			if (m_NumBuy.m_num == 0)return true;
		//	int stronglv;

			if (m_TrueSelect < 0)return true;
			if (m_plist)
			{
				if (m_plist->m_BBList.size() > 7)
				{
					g_pMainState->m_Tags.Add("召唤兽已满");
					return true;
				}
			}
			else
			{
				if (g_pCharacter->m_PcData.m_NumofBB > 7)
				{
					g_pMainState->m_Tags.Add("召唤兽已满");
					return true;
				}
			}
			INT64* money = &g_pCharacter->m_PcData.m_Money[0];
// 			if (!m_plist)
// 			{
// 				money = &g_pCharacter->m_PcData.m_Money[0];
// 				stronglv = g_pCharacter->m_PcData.m_StrongLv;
// 			}
// 			else
// 			{
// 				money = &m_plist->m_money;
// 				stronglv = m_plist->m_stronglv;
// 			}
			*money -= m_PriceTotal;
			if (*money < 0)
			{

				*money += m_PriceTotal;
				g_pMainState->m_Tags.Add("盘缠不足");
				return true;
			}
			sPetData* ppetdata2 = g_pMainState->m_PetDataManager.GetPetData(m_Item[m_TrueSelect].m_modeid);
//			m_Item[m_TrueSelect].m_zizhi.Set(ppetdata2->m_ZiZhi, stronglv, ppetdata2->m_LvTake);
			m_Item[m_TrueSelect].m_zizhi = ppetdata2->m_ZiZhi;
			UpdateText();
			ostringstream oss;
			oss << "购买";
			oss << m_NumBuy.m_num;
			oss << "只";
			oss << m_Item[m_TrueSelect].m_name;
			oss << "共花费";
			oss << m_PriceTotal;
			oss << "两";
			g_pMainState->m_Tags.Add(oss.str());


			if (m_plist)
			{
				m_plist->m_BBList.push_back(m_Item[m_TrueSelect]);
				m_plist->m_FightBB = m_plist->m_BBList.size() - 1;
				g_pMainState->m_Friend.m_friendqianghua.Update();
			}


			if ((!m_plist) || m_plist->CheckInTeam())
			{
				string objname;
				if (m_plist)
				{
					objname = m_plist->m_Name;
				}
				else
				{
					objname = g_pCharacter->m_PcData.m_Name;
				}
				int lv = g_pCharacter->m_PcData.m_Lv + cct::LvGapFromRoleAndBaby;
				if (lv > cct::MaxBabyLv)
				{
					lv = cct::MaxBabyLv;
				}
				updatePetsAfterBuy(objname, 0/*stronglv*/, lv);

			}
		}
		break;
	case 102://左
		if (1)
		{
			m_frampre->SetFrame(1);
			SubPage();
		}
		break;
	case 103://右
		if (1)
		{
			m_frampre->SetFrame(1);
			AddPage();
		}
		break;
	default:
		if (1)
		{
			if (m_TrueSelect >= m_ItemNum)
			{
				m_NumBuy.Reset();
				return true;
			}
			if (m_Select == m_TrueSelect)
			{
				m_NumBuy.SetNum(m_NumBuy.m_num + 1);
				m_NumBuy.SetActive(true);
			}
			else
			{
				m_TrueSelect = m_Select;
				m_NumBuy.SetNum(1);
				m_NumBuy.SetActive(true);
			}
			CoutTotal();
			m_SelectMark.m_Picture.SetXY(m_ItemHead[m_TrueSelect].GetX(), m_ItemHead[m_TrueSelect].GetY() - 7);
		}
		break;
	}
	return true;
}

void cInterFaceBuyPet::OnOff(bool bshow)
{
	if (m_NeedShow == bshow)return;
	g_pMainState->InterfaceSetShow(this, bshow);
	if (m_NeedShow)
	{
		Init();
		m_TrueSelect = -1;
		UpdateText();
		m_Sleeptime = 0;
	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);

}

void cInterFaceBuyPet::UpdateText()
{
	ostringstream  oss;
	int price;
	if (m_TrueSelect < 0)
	{
		m_NumBuy.Reset();
		m_PriceTotal = 0;
		price = 0;
	}
	else
	{
		price = m_Item[m_TrueSelect].m_price;
		if (m_pricerate[m_TrueSelect] != 100)
			price = price*m_pricerate[m_TrueSelect] / 100;
	}
	m_Text[0].SetString(price);
	m_Text[2].SetString(m_PriceTotal);
	if (m_plist)
		m_Text[3].SetString(m_plist->m_money);
	else  	m_Text[3].SetString(g_pCharacter->m_PcData.m_Money[0]);

}

bool cInterFaceBuyPet::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 100:
		OnOff(false);
		break;
	default:
//		g_pMainState->m_ChaKan.Set(m_Item[m_Select]);
		g_pMainState->m_ChaKan.OnOff(true);
		break;
	}
	return true;
}

void cInterFaceBuyPet::CoutTotal()
{
	if (-1 == m_TrueSelect)ERRBOX;
	INT64 money;
	if (m_plist)
		money = m_plist->m_money;
	else money = g_pCharacter->m_PcData.m_Money[0];
	int price = m_Item[m_TrueSelect].m_price;
	if (m_pricerate[m_TrueSelect] != 100)
		price = price*m_pricerate[m_TrueSelect] / 100;
	m_PriceTotal = m_NumBuy.m_num*price;
	if (m_PriceTotal > money)
	{
		m_NumBuy.SetNum((money / price));
		m_PriceTotal = m_NumBuy.m_num*price;
	}
	UpdateText();
}

void cInterFaceBuyPet::Init2(sFriendList* plist, uint page1, uint page2)
{
	Init();
	m_ItemNum = 0;
	m_plist = plist;
	m_page = page1;
	m_page2 = page2;
	m_TrueSelect = -1;
	vector<int> lvs = { 0, 5, 35, 75, 95, 105, 125, 155 };
	int lv = 0;
	for (int i = 7; i >= 0; --i)
	{
		if (g_pCharacter->m_PcData.m_Lv >= lvs[i])
		{
			lv = i;
			break;
		}
	}

	// 	uint lv = (g_pCharacter->m_PcData.m_Lv-5) / 10;
	// 	if (lv > 16)lv = 16;

	lv -= page2;
	vector<sShangPinPet>& list = m_ShangPinList[lv];
	for (int i = page1 * 20; i < list.size(); i++)
	{
		if (!Set(list[i], 100)) break;
	}
	UpdateText();
}

void cInterFaceBuyPet::AddPage()
{
	// 	uint lv = (g_pCharacter->m_PcData.m_Lv-5) / 10;
	// 	if (lv>16)lv = 16;
	// 	if (lv<0)lv = 0;

	vector<int> lvs = { 0, 5, 35, 75, 95, 105, 125, 155 };
	int lv = 0;
	for (int i = 7; i >= 0; --i)
	{
		if (g_pCharacter->m_PcData.m_Lv >= lvs[i])
		{
			lv = i;
			break;
		}
	}

	lv -= m_page2;
	vector<sShangPinPet>& list = m_ShangPinList[lv];
	if (list.size() - m_page * 20 > 20)
	{
		m_page += 1;
	}
	else
	{
		if (lv > 0)
			m_page2 += 1;
		else
			return;
	}
	Init2(m_plist, m_page, m_page2);

}
void cInterFaceBuyPet::SubPage()
{
	/*uint lv = (g_pCharacter->m_PcData.m_Lv+5) / 10;
	if (lv > 17)lv = 17;
	lv -= m_page2;
	vector<sShangPinPet>& list = m_ShangPinList[lv];	*/
	if (m_page > 0)
	{
		m_page -= 1;
	}
	else
	{
		if (m_page2 > 0)
			m_page2 -= 1;
		else
			return;
	}
	Init2(m_plist, m_page, m_page2);

}

void cInterFaceBuyPet::updatePetsAfterBuy(string name, int stronglv, int lv)
{
	for (int i = 0; i < 5; i++)
	{
		if (g_pMainState->m_FightWorkList[i].isExist)
		{
			cObj* obj = g_pMainState->m_FightWorkList[i].m_pObj;
			cCharacter* pc = (cCharacter*)obj->m_pIndex;
			if (0 == obj->m_TrueName.GetString().compare(name))
			{
				cPet* ppet = new cPet;
				ppet->Set(&m_Item[m_TrueSelect], stronglv);
// 				if (i != g_pMainState->m_HeroID)
// 				{
// 					ppet->m_PetData.Followlv(lv, true, true, true);
// 					int jinjienum = (g_pCharacter->m_PcData.m_Lv + 10) / 60;
// 					if (0/*g_pCharacter->m_PcData.m_Lv >= cct::get()->lv进阶*/)
// 						ppet->m_PetData.SetJinJie((pc->m_PcData.m_Lv + 10) / cct::get()->per进阶);
// 				}
// 				else
// 				{
// 					ppet->m_PetDataZZ.LeveUp(true, lv, false);
// 					int lvadd = ppet->m_PetDataZZ.m_Lv - ppet->m_PetDataZZ.m_FuZhuSkillLvList[0];
//  					for (int i = 0; i < 3; i++)
//  						ppet->m_PetDataZZ.lvUpFuZhuSkill(lvadd, i);
// 					ppet->m_PetDataZZ.FillHPMP();
// 				}
//				g_pMainState->GivePcAPet(i, ppet);
				pc->m_PcData.AddPet(ppet);
//				g_pMainState->SetFightPet(i, pc->m_PcData.m_NumofBB - 1);
			}
		}
	}
}

void cInterFaceBuyPet::Init3()
{
	if (m_bInit3)return;
	m_bInit3 = true;
	ifstream File;
	ostringstream oss;
//	oss << g_pathData;
	oss << "任务//召唤兽商店//隐藏召唤兽列表.txt";
	File.open(oss.str());
	int num;
	File >> num;
	m_ShangPinList3.resize(num);
	string dustbin;
	for (int i = 0; i < num; i++)
	{
		m_ShangPinList3[i].Read(File);
	}
	File.close();
}

sShangPinPet& cInterFaceBuyPet::GetPet3(int id)
{
	Init();
	return m_ShangPinList[0][id];
	Init3();
	return m_ShangPinList3[id];
}

