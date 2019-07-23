#include "_global.h"
#include "_txt.h"


bool cInterFaceBuy::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_NumBuy.SetMaxNum(99);
	m_Describe.Init();
	m_PriceTotal = 0;
	m_SelectMark.Load(0x10921CA7);
	m_TrueSelect = -1;
	m_Button.Load(0x35A981D3);
	m_Button.SetStatic(true);
	m_MouseOnMark.Load(0x6F88F494);
	m_MouseOnMark.m_NeedShow = false;
	m_Back.Load(3929029437);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;


	/*for (int i = 0; i < 4; i++)
	{
	m_Text[i].SetStyle(2);
	}*/
	m_Text[4].SetColor(RGB(240, 240, 240));
	m_Text[4].SetString("确定");
	m_Text[1].SetColor(0);

	m_Text[5].SetColor(RGB(240, 240, 240));
	m_Text[5].SetString("购买");

	UpdateText();
	Move(200 + g_half320 - 320, 30 + g_half240 - 240);

	m_Left.Load(0xB05126E8);
	m_Left.SetStatic(true);
	m_Right.Load(0x26066130);
	m_Right.SetStatic(true);

	return true;
}

bool cInterFaceBuy::Show(cCanvas* pCanvas)
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
	forv (m_Text, i)
	{
		if (i == 1)continue;
		pCanvas->Add(&m_Text[i]);
	}
	m_NumBuy.Show(pCanvas);
	pCanvas->Add(&m_Left, 1);
	pCanvas->Add(&m_Right, 1);
	return true;
}

bool cInterFaceBuy::ProcessInput()
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

	if (m_Describe.m_NeedShow)
		m_Describe.OnOff(false);
	if (m_bMoveMode)//移动
	{
		m_Select = 106;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}

	if (!isInRect(g_xMouse, g_yMouse, &m_Back))return true;

	if (isOn(g_xMouse, g_yMouse, m_Rect))
	{
		m_Select = (g_xMouse - m_Rect.left) / 51 + 5 * ((g_yMouse - m_Rect.top) / 51);
		if (m_Select < m_ItemNum)
		{
			g_pMainState->m_ItemManage.SetItemDescribe(g_xMouse, g_yMouse, m_Describe, &m_Item[m_Select + m_page * 20]);
			m_MouseOnMark.m_NeedShow = true;
			m_MouseOnMark.SetXY(m_ItemHead[m_Select].GetX(), m_ItemHead[m_Select].GetY());
			if (CheckL())return true;
		}
	}
	if (CheckOn(&m_Left, 102))return true;
	if (CheckOn(&m_Right, 103))return true;
	//取消按钮
	if (CheckOn(&m_Cancel, 100))return true;
	//确定按钮
	if (CheckOn(&m_Button, 101))return true;
	m_Select = 0;
	if (CheckRB())return true;
	//准备移动
	m_Select = 107;
	CheckL();
	return true;
}

bool cInterFaceBuy::Set(sItem2& item, int rate)
{
	m_pricerate.push_back(rate);
	if (cct::isEquip(&item) || cct::isEquipBB(&item))
	{
		g_pMainState->m_ItemManage.AutoItemProperty(&item);
	}
	m_Item.push_back(item);
	return true;
}



bool cInterFaceBuy::Move(int x, int y)
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
	m_Rect.top = 40 + m_yPos;
	m_Rect.right = m_Rect.left + 255;
	m_Rect.bottom = m_Rect.top + 204;
	for (int i = 0; i < 20; i++)
	{
		int xNum = i % 5;
		int yNum = i / 5;
		m_ItemHead[i].SetXY(xNum * 51 + m_Rect.left, yNum * 51 + m_Rect.top);
	}
	if (m_TrueSelect>-1)
		m_SelectMark.m_Picture.SetXY(m_ItemHead[m_TrueSelect].GetX(), m_ItemHead[m_TrueSelect].GetY());

	m_Left.SetXY(m_xPos + 20, m_yPos + 252);
	m_Right.SetXY(m_xPos + 70, m_yPos + 252);

	return true;
}

bool cInterFaceBuy::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
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
			if (m_NumBuy.m_num > 0 && g_pCharacter->AddMoney(-m_PriceTotal, 0))
			{
				m_Item[m_TrueSelect2].m_Num = m_NumBuy.m_num;
				if (!g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &m_Item[m_TrueSelect2]))
				{
					g_pCharacter->AddMoney(m_PriceTotal, 0);
					return true;
				}
//				m_Item[m_TrueSelect2].m_Property.clear();
				UpdateText();
				ostringstream oss;
				oss << "购买";
				oss << m_NumBuy.m_num;
				oss << "个";
				oss << m_Item[m_TrueSelect2].GetName();
				oss << "共花费";
				oss << m_PriceTotal;
				oss << "两";
				g_pMainState->m_Tags.Add(oss.str());
			}
			else
			{
				g_pMainState->m_Tags.Add("盘缠不足");
				return true;
			}
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
				m_TrueSelect2 = m_TrueSelect + m_page * 20;
				m_NumBuy.SetNum(1);
				m_NumBuy.SetActive(true);
			}
			CoutTotal();
			m_SelectMark.m_Picture.SetXY(m_ItemHead[m_TrueSelect].GetX(), m_ItemHead[m_TrueSelect].GetY());
		}
		break;
	}
	return true;
}

void cInterFaceBuy::OnOff(bool bshow)
{
	if (m_NeedShow == bshow)return;
	g_pMainState->InterfaceSetShow(this, bshow);
	if (m_NeedShow)
	{
		Init();
		Update();
	}
	else
	{
		g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
		m_Describe.OnOff(false);
		cct::autoSave();
	}
}

void cInterFaceBuy::UpdateText()
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
		int select = m_TrueSelect + m_page * 20;
		price = m_pricerate[m_TrueSelect]; // m_Item[select].m_pItemData->m_Price;
// 		if (m_pricerate[m_TrueSelect] != 100)
// 		{
// 			INT64 num1 = price;
// 			INT64 num2 = m_pricerate[m_TrueSelect];
// 			num1 = num2*num1 / 100;
// 			price = (int)num1;
// 		}
	}

	m_Text[0].SetColor(GetPriceColor(price));
	oss << price;
	m_Text[0].SetString(oss.str());


	oss.str("");
	m_Text[2].SetColor(GetPriceColor(m_PriceTotal));
	oss << m_PriceTotal;
	m_Text[2].SetString(oss.str());


	oss.str("");
	m_Text[3].SetColor(GetPriceColor(g_pCharacter->m_PcData.m_Money[0]));
	oss << g_pCharacter->m_PcData.m_Money[0];
	m_Text[3].SetString(oss.str());

}

bool cInterFaceBuy::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		break;
	default:
		break;
	}
	return true;
}

void cInterFaceBuy::CoutTotal()
{
	if (-1 == m_TrueSelect)return;
	int select = m_TrueSelect + m_page * 20;
	INT64 money = g_pCharacter->m_PcData.m_Money[0];
	int price = m_pricerate[select];// m_Item[select].m_pItemData->m_Price;

// 	if (m_pricerate[select] != 100)
// 	{
// 		INT64 num1 = price;
// 		INT64 num2 = m_pricerate[select];
// 		num1 = num2*num1 / 100;
// 		price = (int)num1;
// 	}
	m_PriceTotal = m_NumBuy.m_num*price;
	if (m_PriceTotal > money)
	{
		m_NumBuy.SetNum((money / price));
		m_PriceTotal = (m_NumBuy.m_num*price);
	}
	UpdateText();
}

void cInterFaceBuy::AddPage()
{

	if (m_Item.size() > 20 * (m_page + 1))
	{
		m_page += 1;

		Update();
	}
}
void cInterFaceBuy::SubPage()
{

	if (m_page>0)
	{
		m_page -= 1;
		Update();
	}
}
void cInterFaceBuy::Update()
{
	m_ItemNum = m_Item.size() - m_page * 20;
	if (m_ItemNum > 20)m_ItemNum = 20;
	int k = m_page * 20;
	m_TrueSelect = -1;
	m_TrueSelect2 = -1;
	for (int i = 0; i < m_ItemNum; i++)
	{
		m_ItemHead[i].Load(m_Item[k + i].m_pItemData->m_SmallHead);
	}
	UpdateText();
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
	m_Describe.OnOff(false);

}

void cInterFaceBuy::Reset()
{
	m_ItemNum = 0;
	m_Item.clear();
	m_pricerate.clear();
	m_page = 0;
}

void cInterFaceBuy::Open(int id)
{
	sItem2 item;
	item.m_Num = 1;
	Reset();

	if (id < 20)
	{
		vector<int> ids = { 44, 43, 42 };
		for (int i = 14; i >= 0; --i)
		{
			ids.push_back(i);
		}

		forr(ids, i)
		{
			item.Set(ids[i], g_pMainState->m_ItemManage.GetIDByLv(ids[i], id * 10));
			item.m_pItemData->SetLv(id * 10);
			Set(item, max((id * id * 2000), 500));
		}
	}
	else if (id < 40)
	{

		vector<int> ids = { 34, 33, 32 };
		if (id >= 25)
		{
			ids.clear();
		}
		for (int i = 21; i >= 15; --i)
		{
			ids.push_back(i);
		}

		int price;
		forr(ids, i)
		{
			int id2 = id - 20;
			bool is2 = false;
			if (ids[i] >= 32)
			{
				id2 = id2 + 1;
			}
			else if (ids[i] == 19 || ids[i] == 20)
			{
				if (id2 >= 3 && id2 < 9)
				{
					id2 = (id2 - 3) * 2 + 3;
					is2 = true;
				}
				else if (id2 >= 9)
				{
					id2 = id2 + 6;
				}
			}
			item.Set(ids[i],  id2);
			price = id - 20;
			price = price * price * 2000;
			price = max(price, 500);
			Set(item, price);
			if (is2)
			{
				item.Set(ids[i], id2 + 1);
				Set(item, price);
			}
		}
	}
	else if (id >= 50 && id <= 59)
	{
		set<int> ids = { (int)eModel::剑灵jl, (int)eModel::无痕wh };
		auto shop = ctt::getShops().at(47);
		forr(shop, i)
		{
			ids.insert(shop[i].id);
		}
		shop = ctt::getShops().at(48);
		forr(shop, i)
		{
			ids.insert(shop[i].id);
		}
		shop = ctt::getShops().at(49);
		forr(shop, i)
		{
			ids.insert(shop[i].id);
		}

		vector<int> lvs = { 0, 0, 115, 115, 5, 15, 25, 45, 55, 75, 85, 105, 
			125, 135, 145, 165, 175, 175, 175, 175 };
		// 50 神兽变身卡 0
		// 51 NPC变身卡 115

		const auto& ps = g_pMainState->m_PetDataManager.m_PetList;
		int size = g_pMainState->m_ItemManage.m_ItemList[26].size();
		int lv1 = lvs[(id - 50) * 2];
		int lv2 = lvs[(id - 50) * 2 + 1];
		for (int i = 0; i < size; ++i)
		{
			int pid = ps[i].m_ID;
			if (ids.find(pid) != ids.end())
			{
				continue;
			}
			int lv = ps[i].m_LvTake;
			if (lv >=  lv1 && lv <= lv2)
			{
				item.Set(26, pid);
				if (lv == 0 || lv == 115)
				{
					lv = 30000;
				}
				else
				{
					lv = (lv * lv) + (lv * 80) + 5000;
				}
				Set(item, lv);
			}
		}
	}
	else if (id == 77 || id == 78)
	{
		// 符石
		const auto& ss = g_pMainState->m_ItemManage.m_ItemList[41];
		int k = ctt::getSkillStarts().size();
		forv(ss, i)
		{
			if ((id == 77 && i < k) || (id == 78 && i >= k))
			{
				item.m_pItemData = (sItem*)&ss[i];
				Set(item, 100000);
			}
		}
	}
	else 
	{
		const auto& shop = ctt::getShops().at(id);
		forv(shop, i)
		{
			item.Set(shop[i].type, shop[i].id);
			if (id == 70 && i >= shop.size() - 2)
			{
				// 书 铁
				item.m_Property.resize(1);
#if defined(_DEBUG)
				item.m_Property[0] = 160;
#else
				item.m_Property[0] = 50;
#endif
			}
			Set(item, shop[i].price);
#if defined(_DEBUG)
			if (id != 70 || i != shop.size() - 1)
			{
				continue;
			}
			for (int k = 60; k <= 150; k += 10)
			{
				item.m_Property.resize(1);
				item.m_Property[0] = k;
				Set(item, 1024);
			}
#endif
		}
	}



	OnOff(true);
	return;


	bool s_bool = true;
	if (s_bool)
	{
		s_bool = false;
		for (int i = 0; i <= 101; ++i)
		{
			ifstream f(/*g_pathData + */toString("商店/%d.txt", i));
			if (f.is_open())
			{
				string str = toString("{%d, {", i);
				ccc_log("{%d, {", i);
				int num, Type, id2, pricerate;
				f >> num;
				for (int i = 0; i < num; i++)
				{
					f >> Type;
					f >> id2;
					f >> pricerate;
					str += toString("{%d, %d, %d},", Type, id2, pricerate);
					ccc_log("{%d, %d, %d},", Type, id2, pricerate);
				}
				str.pop_back();
				str += "}},";
//				Q_LOG(str.c_str());
				ccc_log("}},\n\n\n\n");
			}
			f.close();
		}
	}
	ostringstream oss;
//	oss << g_pathData << "商店\\";
	oss << id;
	oss << ".txt";
	ifstream File;
	File.open(oss.str());
	if (!File.is_open())ERRBOX;
	int num;
	File >> num;
	int Type, id2, pricerate;
//	sItem2 item;
	item.m_Num = 1;
	Reset();
	for (int i = 0; i < num; i++)
	{
		File >> Type;
		File >> id2;
		File >> pricerate;
		item.Set(Type, id2);
		Set(item, pricerate);
// 		m_pricerate.push_back(pricerate);
// 		m_Item.push_back(item);
	}
// 	vector<int> ids = { 1, 5, 7, 9, 11, 13, 24, 36, 40, 42, 75, 76, 82, 92, 93, 94, 95, 96, 98, 99, 100, 102, 104,
// 		48, 56, 58, 60, 85, 87, 89, 91, 101, 103, 105,
// 		3, 15, 17, 19, 21, 26, 28, 30, 32, 34, 38, 44, 46, 50, 52, 54, 67, 69, 71, 73, 74, 78, 80, 83, 97 };
// 	if (id == 95)
// 	{
// 		Reset();
// 		forv(ids, i)
// 		{
// 			item.Set(40, ids[i]);
// 			Set(item, 10);
// 		}
// 
// 	}
// 	else if (id == 96)
// 	{
// 		item.Set(24, 34);
// 		Set(item, m_pricerate[9]);
// 		item.Set(24, 18);
// 		Set(item, m_pricerate[9]);
// 		item.Set(24, 25);
// 		Set(item, m_pricerate[9]);
// 	}
	OnOff(true);
}