#include "_global.h"



bool cInterfaceDialog::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;

	m_NameBack.Load(0x2EFADFA5);
	ccm::get()->pushWdf("对话面板名字", 0x2EFADFA5);
	m_SelectT.resize(4);
	for (int i = 0; i < 4; i++)
	{
		m_SelectT[i].SetColor(RGB(255, 0, 0));
		m_SelectT[i].m_x = 0;
	}
	m_NowMouseOnSelect = -1;

	m_NameBack.m_Picture.m_x = 80 + g_half320 - 320;
	m_NameBack.m_Picture.m_y = 220 + g_half240 - 240;
	m_ContextList.m_Name.SetXY(m_NameBack.m_Picture.m_x, m_NameBack.m_Picture.m_y);

	m_DialogBack.Load(0x73D983B7);
	ccm::get()->pushWdf("对话面板", 0x73D983B7);
	m_DialogBack.m_bMove = true;
	m_DialogBack.m_Picture.m_x = g_half320 - m_DialogBack.m_Picture.m_Width / 2;
	m_DialogBack.m_Picture.m_y = g_half240;
	for (int i = 0; i < 10; i++)
	{
		m_ContextList.m_TextLineList[i].m_line.m_hFont = g_pMainState->m_hFont[0];
		m_ContextList.m_TextLineList[i].m_line.SetColor(RGB(255, 255, 255));
	}
	m_ContextList.m_Name.SetColor(RGB(240, 240, 240));
	m_ContextList.m_Name.SetXCenter(m_NameBack.GetX() + m_NameBack.GetWidth() / 2);

	m_Cancel.SetXY(m_DialogBack.GetX() + m_DialogBack.GetWidth() - 20, m_DialogBack.GetY() + 3);
	return true;
}

bool cInterfaceDialog::Free()
{
	m_DialogBack.Free();
	return true;
}

void cInterfaceDialog::SetObj(string name)
{
	cObj* pObj = g_pMainState->FindObjByName(name);
	SetObj(pObj);

}
void cInterfaceDialog::SetObj(cObj* pObj)
{
	m_pObj = pObj;
	if (!pObj)
	{
		m_Head.Load(0);
		m_ContextList.m_Name.SetString("");
		return;
	}
	if (m_ContextList.m_Name.GetString() != pObj->m_TrueName.GetString())
	{
		m_ContextList.m_Name.SetString(pObj->m_TrueName.GetString());
		m_ContextList.m_Name.UpdateXCenter();
	}
	SetHead(m_pObj->GetID(POS_DIALOG));
}

bool cInterfaceDialog::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Head, 1);
	pCanvas->Add(&m_DialogBack, 1, true);

	if (m_ContextList.m_Name.GetString().size()>0)
	{
		pCanvas->Add(&m_NameBack, 1);
		pCanvas->Add(&m_ContextList.m_Name);
	}
	pCanvas->Add(&m_Cancel, 1);
	//显示对话	
	for (int i = 0; i < m_ContextList.m_LineNum; i++)
	{
		if (1 == m_ContextList.m_LineNum && 0 == m_ContextList.m_TextLineList[i].m_NumFace)
		{
			pCanvas->Add(&m_ContextList.m_TextLineList[i].m_line);
		}
		else
		{
			pCanvas->Add(&m_ContextList.m_TextLineList[i].m_line);
			//如果有表情,先显示表情
			for (int j = 0; j < m_ContextList.m_TextLineList[i].m_NumFace; j++)
			{
				pCanvas->Add(&m_ContextList.m_TextLineList[i].m_Face[j], 1);
			}
		}
	}

	switch (m_NumOfSelect)
	{
	case 4:
		pCanvas->Add(&m_SelectT[3]);
	case 3:
		pCanvas->Add(&m_SelectT[2]);
	case 2:
		pCanvas->Add(&m_SelectT[1]);
	case 1:
		pCanvas->Add(&m_SelectT[0]);
		break;
	}

	return true;
}

bool cInterfaceDialog::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	cInputDevice& Mouse = g_pMainState->Mouse;
	m_retSelect = -1;
	m_Select = -1;
	g_pMainState->m_Cursor.m_FollowMode = false;
	ResetButton();

	if (m_NowMouseOnSelect > -1)
	{
		if (m_NowMouseOnSelect<m_SelectT.size())
			m_SelectT[m_NowMouseOnSelect].SetColor(RGB(255, 0, 0));
		m_NowMouseOnSelect = -1;
	}

	g_pMainState->SetMouseOnMap(false);
	if (!isOn(g_xMouse, g_yMouse, m_DialogBack.m_PreShowRect))
	{
		Mouse.SetLock(MOUSE_LBUTTON); //对话时不允许其它鼠标操作
		if (m_NowMouseOnSelect > -1)//把之前的字的颜色换回来
		{
			if (m_NowMouseOnSelect<m_SelectT.size())
				m_SelectT[m_NowMouseOnSelect].SetColor(RGB(255, 0, 0));
			m_NowMouseOnSelect = -1;
		}
		return  true;
	}
	if (CheckOn(&m_Cancel, 4))return true;

	if (m_NumOfSelect)
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			if (isOn(g_xMouse, g_yMouse, m_SelectT[i].m_PreShowRect))
			{
				m_Select = 0;
				m_NowMouseOnSelect = i;
				m_SelectT[m_NowMouseOnSelect].SetColor(RGB(255, 255, 255));
				if (CheckL())return true;
				break;
			}
		}

	}
	else
	{
		m_Select = 1;
		CheckL();
	}
	return true;
}

void cInterfaceDialog::SetString(string str, string select1, string select2, string select3, string select4)
{
	if (str.size())
		m_ContextList.SetFaceText(str, g_pMainState->m_hFont[0], 470);

	m_NumOfSelect = 2;
	if ("" != select4)	m_NumOfSelect = 4;
	else
		if ("" != select3)	m_NumOfSelect = 3;
		else
			if ("" != select2)	m_NumOfSelect = 2;
			else
				if ("" != select1)	m_NumOfSelect = 1;
				else m_NumOfSelect = 0;
				switch (m_NumOfSelect)
				{
				case 4:
					m_SelectT[3].SetString(select4);
				case 3:
					m_SelectT[2].SetString(select3);
				case 2:
					m_SelectT[1].SetString(select2);
				case 1:
					m_SelectT[0].SetString(select1);
					break;
				}
				int xstart = m_DialogBack.GetX() + 10;
				m_ContextList.SetPos(xstart, m_DialogBack.GetY() + 25);
				int h = m_ContextList.m_Height;
				switch (m_NumOfSelect)
				{
				case 1:
					m_SelectT[0].SetXY(xstart, m_DialogBack.GetY() + 35 + h);
					break;
				case 2:
					for (int i = 0; i < m_NumOfSelect; i++)
					{
						m_SelectT[i].SetXY(xstart, m_DialogBack.GetY() + 35 + h);
						h += m_SelectT[i].GetHeight() + 20;
					}
					break;
				case 3:
					for (int i = 0; i < m_NumOfSelect; i++)
					{
						m_SelectT[i].SetXY(xstart, m_DialogBack.GetY() + 35 + h);
						h += m_SelectT[i].GetHeight() + 15;
					}
					break;
				case 4:
					for (int i = 0; i < m_NumOfSelect; i++)
					{
						m_SelectT[i].SetXY(xstart, m_DialogBack.GetY() + 35 + h);
						h += m_SelectT[i].GetHeight() + 10;
					}
					break;
				}

				return;
}

void cInterfaceDialog::SetPet(cPet* p)
{
	ulong idlist = p->GetID(POS_DIALOG);
	if (idlist)
	{
		g_pMainState->m_Dialog.m_Head.Load(idlist);
	}
	m_ContextList.m_Name.SetString(p->m_PetData.m_Name);
	if (idlist)
	{
		int a = m_Head.m_Picture.getFrameIdx();
		m_Head.m_Picture.m_x = g_half320 - m_DialogBack.m_Picture.m_Width / 2 + m_Head.m_Picture.Spr.m_pDataOffsetList[a].FramX;
		m_Head.m_Picture.m_y = g_half240 - m_Head.m_Picture.m_Height + m_Head.m_Picture.Spr.m_pDataOffsetList[a].FramY;
	}
}

bool cInterfaceDialog::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	if (m_bRetSelect)
	{
		if (m_Select == 4)
			m_NowMouseOnSelect = 4;
		if (m_NowMouseOnSelect > -1)
		{
			OnOff(false);
			m_bRetSelect = false;
			m_retSelect = m_NowMouseOnSelect;

			if (m_pTask)
			{
				cTaskFather* pTaskFather = m_pTask;
				m_pTask = 0;
				if (m_retSelect > 4)m_retSelect = 4;
				pTaskFather->Process(m_retstage[m_retSelect]);
			}
			return true;
		}
	}
	switch (m_Select)
	{
	case 0://选择
		if (-1 < m_NowMouseOnSelect)
		{
			if (m_NumOfSelect)
				m_pObj->m_ScriptSelect = m_NowMouseOnSelect;
			m_NumOfSelect = 0;
			OnOff(false);
			if (m_pObj)
			{
				m_pObj->m_Script.Process(m_pObj);
			}
		}
		return true;
	case 1://点在其它位置
		if (0 == m_NumOfSelect)
		{
			OnOff(false);
			if (!g_pMainState->m_TriggerDialog.m_datalist.size())return false;
			if (g_pMainState->m_TriggerDialog.m_datalist[0].m_Nowtext > -1)
			{
				return g_pMainState->m_TriggerDialog.Process();
			}
			else
				if (m_pObj)
				{
				m_pObj->m_Script.Process(m_pObj);
				}

		}
		return true;
	case 4://取消
		Close(); break;
	default:
		ERRBOX;
		break;
	}
	return true;

}

void cInterfaceDialog::OnOff(bool bShow)
{
	if (m_NeedShow == bShow)return;
	g_pMainState->InterfaceSetShow(this, bShow);
	if (m_NeedShow)
	{
		Init();
		if (!m_Reset)ERRBOX;
		if (m_NowMouseOnSelect>-1 && m_NowMouseOnSelect<4) m_SelectT[m_NowMouseOnSelect].SetColor(RGB(255, 0, 0));
		m_NowMouseOnSelect = -1;
		m_Cancel.SetFrame帧(0);
	}
	else m_Reset = false;
	g_pMainState->m_Canvas.SetRedraw(m_DialogBack.m_PreShowRect);
	g_pMainState->m_Canvas.SetRedraw(m_Head.m_PreShowRect);
}

void cInterfaceDialog::Reset()
{
	m_retSelect = -1;
	m_NumOfSelect = 0;
	//m_pObj = 0;
	m_pTask = 0;
	m_bRetSelect = false;
	m_Reset = true;
	//m_Head.Free();
	//m_ContextList.m_Name.SetString("");
}

void cInterfaceDialog::SetTrigger(cTaskFather* pTask, int defaultret, int stage0, int stage1, int stage2, int stage3)
{
	m_pTask = pTask;
	m_retstage[4] = defaultret;

	/*if (stage0 == -1)
	{
	m_retstage[0] = defaultret;
	m_retstage[1] = defaultret;
	m_retstage[2] = defaultret;
	m_retstage[3] = defaultret;
	}
	else*/
	{
		m_retstage[0] = stage0;
		m_retstage[1] = stage1;
		m_retstage[2] = stage2;
		m_retstage[3] = stage3;
	}
	m_bRetSelect = true;
}

void cInterfaceDialog::SetHead(ulong head)
{
	if (!head)
	{
		m_Head.m_NeedShow = false;
		return;
	}
	m_Head.Load(head);
	m_Head.m_NeedShow = true;
	m_Head.m_Picture.m_x = g_half320 - m_DialogBack.m_Picture.m_Width / 2 + m_Head.m_Picture.Spr.m_pDataOffsetList[0].FramX;
	m_Head.m_Picture.m_y = g_half240 - m_Head.m_Picture.m_Height + m_Head.m_Picture.Spr.m_pDataOffsetList[0].FramY;
}

void cInterfaceDialog::Talk(string context, string name, ulong head)
{
	Reset();
	m_ContextList.m_Name.SetString(name);
	SetString(context);
	SetHead(head);
	OnOff(true);
}

void cInterfaceDialog::Talk(sTalkList* talk)
{
	Reset();
	cObj* pObj = 0;
	SetString(talk->context);
	m_ContextList.m_Name.SetString(talk->name);
	if (talk->name == "")
	{
		if (g_pMainState->m_pNowSelectName.size())
		{
			m_ContextList.m_Name.SetString(g_pMainState->m_pNowSelectName);
		}
		SetHead(0);
		OnOff(true);
		return;
	}
	pObj = g_pMainState->FindObjByName(talk->name);
	if (pObj)
	{
		SetHead(pObj->GetID(POS_DIALOG));
	}
	else
	{
		//队友头像
		for (uint i = 0; i < 5; i++)
		{
			if (g_pMainState->m_FightWorkList[i].isExist)
			{
				string name = g_pMainState->m_FightWorkList[i].m_pObj->m_TrueName.GetString();
				if (name == talk->name)
				{
					SetHead(g_pMainState->m_FightWorkList[i].m_pObj->GetID(POS_DIALOG));
					OnOff(true);
					return;
				}
			}
		}
		//好友头像
		for (uint i = 0; i < g_pMainState->m_Friend.m_FriendList.size(); i++)
		{
			sFriendList& list = g_pMainState->m_Friend.m_FriendList[i];
			if (list.m_Name == talk->name)
			{
				SetHead(list.GetDialogHead());
				OnOff(true);
				return;
			}
		}
		//程序加的头像
		for (uint i = 0; i < g_pMainState->m_DialogList.size(); i++)
		{
			if (g_pMainState->m_DialogList[i].name == talk->name)
			{
				SetHead(g_pMainState->m_DialogList[i].idlist);
				OnOff(true);
				return;
			}
		}
		SetHead(0);
	}

	if (!m_Head.m_NeedShow)
	{
		if (g_pMainState->m_pNowSelectHead)
		{
			SetHead(g_pMainState->m_pNowSelectHead);
		}
	}

	OnOff(true);
}



void cInterfaceDialog::Reset2()
{
	m_bRetSelect = false;
	m_Reset = true;
}

void cInterfaceDialog::Close()
{
	if (!m_NeedShow)return;
	if (m_pObj)
		m_pObj->m_Script.m_NowScript = 0;
	OnOff(false);
	if (0 == g_pMainState->m_TriggerDialog.m_datalist.size())return;
	if (g_pMainState->m_TriggerDialog.m_datalist[0].m_Nowtext > -1)
	{
		g_pMainState->m_TriggerDialog.Process(0, true);
	}
}

void cInterfaceDialog::InitQuestion()
{
	if (m_bInitQuestion)return;
	m_bInitQuestion = true;

	ifstream File;
	ostringstream oss;
//	oss << g_pathData << "题库.txt";
	File.open(oss.str());
	int num;
	File >> num;
	m_PoemList.resize(num);
	for (int i = 0; i < num; i++)
	{
		m_PoemList[i].Read(File);
	}
	File.close();
}

void cInterfaceDialog::Question()
{
	InitQuestion();
	GetQuestion(m_Question);
	switch (m_Question.select.size())
	{
	case 1:
		SetString(m_Question.title, m_Question.select[0]);
		break;
	case 2:
		SetString(m_Question.title, m_Question.select[0], m_Question.select[1]);
		break;
	case 3:
		SetString(m_Question.title, m_Question.select[0], m_Question.select[1], m_Question.select[2]);
		break;
	case 4:
		SetString(m_Question.title, m_Question.select[0], m_Question.select[1], m_Question.select[2], m_Question.select[3]);
		break;
	}

}

std::string cInterfaceDialog::GetTrueSelect()
{
	ostringstream oss;
	oss << "正确答案是#R";
	oss << m_Question.select[m_Question.answer];
	oss << "#R";
	return oss.str();
}

void cInterfaceDialog::GetQuestion(sQuestion& quest, int selectnum)
{
	quest.answer = 0;
	quest.select.resize(selectnum);

	InitQuestion();
	int poemid = rand() % m_PoemList.size();
	sPoem& po = m_PoemList[poemid];
	sPoem* pPo;
	int type = rand() % 3;
	ostringstream oss;
	switch (type)
	{
	case 0://求标题
		if (1)
		{

			int contextid = rand() % po.m_context.size();
			contextid -= 2;
			if (contextid < 0)contextid = 0;

			oss << "#G" << po.m_context[contextid] << "," << po.m_context[contextid + 1] << "#G出自哪首诗?";
			quest.title = oss.str();
			quest.select[0] = po.m_title;
			if (selectnum>1)
				while (1)
				{
				AutoGetPoem(pPo);
				if (pPo->m_title != quest.select[0])
				{
					quest.select[1] = pPo->m_title;
					break;
				}
				}
			if (selectnum>2)
				while (1)
				{
				AutoGetPoem(pPo);
				if (pPo->m_title != quest.select[0])
					if (pPo->m_title != quest.select[1])
					{
					quest.select[2] = pPo->m_title;
					break;
					}
				}
			if (selectnum>3)
				while (1)
				{
				AutoGetPoem(pPo);
				if (pPo->m_title != quest.select[0])
					if (pPo->m_title != quest.select[1])
						if (pPo->m_title != quest.select[2])
						{
					quest.select[3] = pPo->m_title;
					break;
						}
				}
		}
		break;
	case 1:
		if (1)
		{
			//if (rand() % 2)
			{
				int contextid = rand() % po.m_context.size();
				contextid -= 2;
				if (contextid < 0)contextid = 0;
				oss << "#G" << po.m_context[contextid] << "," << po.m_context[contextid + 1] << "#G的作者是谁?";
				quest.title = oss.str();
			}
			/*else
			{
			oss << po.m_title << "的作者是谁?";
			quest.title = oss.str();
			}*/

			quest.select[0] = po.m_name;
			if (selectnum>1)
				while (1)
				{
				AutoGetPoem(pPo);
				if (pPo->m_name != quest.select[0])
				{
					quest.select[1] = pPo->m_name;
					break;
				}
				}
			if (selectnum>2)
				while (1)
				{
				AutoGetPoem(pPo);
				if (pPo->m_name != quest.select[0])
					if (pPo->m_name != quest.select[1])
					{
					quest.select[2] = pPo->m_name;
					break;
					}
				}
			if (selectnum>3)
				while (1)
				{
				AutoGetPoem(pPo);
				if (pPo->m_name != quest.select[0])
					if (pPo->m_name != quest.select[1])
						if (pPo->m_name != quest.select[2])
						{
					quest.select[3] = pPo->m_name;
					break;
						}
				}

		}
		break;
	case 2://
		if (1)
		{
			int contextid = rand() % po.m_context.size();
			if (po.m_context.size() < 3)ERRBOX;//诗句数不能小于3
			contextid -= 2;
			if (contextid < 0)contextid = 0;

			oss << "#G" << po.m_context[contextid] << "," << po.m_context[contextid + 1] << "#G下一句是什么?";
			contextid += 2;


			quest.title = oss.str();
			quest.select[0] = po.m_context[contextid];

			if (selectnum > 1)
			{
				AutoGetPoem(pPo);
				quest.select[1] = pPo->m_context[rand() % (pPo->m_context.size())];
			}
			if (selectnum > 2)
			{
				AutoGetPoem(pPo);
				quest.select[2] = pPo->m_context[rand() % (pPo->m_context.size())];
			}
			if (selectnum > 3)
			{
				AutoGetPoem(pPo);
				quest.select[3] = pPo->m_context[rand() % (pPo->m_context.size())];

			}

		}
		break;
	default:
		ERRBOX;
		break;
	}
	quest.Auto();
}

void cInterfaceDialog::AutoGetPoem(sPoem*& out)
{
	out = &m_PoemList[rand() % m_PoemList.size()];
}

void cInterfaceDialog::TalkNObj(string context)
{//
	Reset();
	SetString(context);
	OnOff(true);
}

void cInterfaceDialog::TalkObj(string context, cObj* p)
{//

	Reset();
	if (p)
	{
		SetObj(p);
	}
	SetString(context);
	OnOff(true);
}

