#include "_global.h"

bool cInterfaceJob::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Back.resize(2);
	for (int i = 0; i < 2; i++)
	{
		m_Back[i].Load(0xF151309F);// 788193189);
		ccm::get()->pushWdf("任务选择条", 0xF151309F);
		m_Back[i].SetFrame(1);
		m_Back[i].m_NeedShow = false;
		m_Back[i].m_isStatic = true;
	}
	m_gap = m_Back[0].m_Picture.m_Height;

	m_Job.Load(700775208);
	ccm::get()->pushWdf("任务面板", 700775208);
	m_Job.m_isStatic = true;
	m_Up.Load(149082521);
	ccm::get()->pushWdf("任务按钮上", 149082521);
	m_Up.m_isStatic = true;
	m_Down.Load(153189907);
	ccm::get()->pushWdf("任务按钮下", 153189907);
	m_Down.m_isStatic = true;
	m_Select = 0;
	m_Check = 0;
	m_Context.SetColor(RGB(0, 0, 0));
	Move(150 + g_half320 - 320, 130/* + g_half240 - 240*/);
	return true;

}
void cInterfaceJob::UpDatePageTitle()
{
	if (m_JobList.size() - m_Page * 8 > 0)
	{
		int num = m_JobList.size() - m_Page * 8;
		if (num > 8)num = 8;
		for (int i = 0; i < num; i++)
		{
			m_TitleList[i].SetString(m_JobList[i].m_Title);
		}
	}
}

void cInterfaceJob::SetSelect(int select)
{
	if (m_Check > -1)
		m_TitleList[m_Check].SetColor(0);
	if (0 > select)
	{
		m_Check = -1;
		return;
	}

	int trueselect = select + m_Page * 8;
	if (trueselect < m_JobList.size())
	{
		m_Check = select;
		m_TitleList[m_Check].SetColor(RGB(255, 0, 0));
		m_Context.SetFaceText(m_JobList[trueselect].m_Context, g_pMainState->m_hFont[0], 142);
		m_Context.SetPos(m_xPos + 196, m_yPos + 59);
	}
	else
	{
		SetSelect(m_JobList.size() - 1 - m_Page * 8);
	}
}

bool cInterfaceJob::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Job, 1, true);
	pCanvas->Add(&m_Back[0], 1);
	pCanvas->Add(&m_Back[1], 1);
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_Up, 1);
	pCanvas->Add(&m_Down, 1);
	int num = m_JobList.size() - m_Page * 8;
	if (num > 0)
	{
		if (num > 8)num = 8;
		for (int i = 0; i < num; i++)
		{
			pCanvas->Add(&m_TitleList[i], 1);
		}
		if (-1 < m_Check)
		{
			m_Context.Show(pCanvas);
		}
	}
	return true;
}





bool cInterfaceJob::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	m_Select = m_Check;
	ResetButton();

	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())
			m_bMoveMode = false;
		return true;
	}

	if (!isInRect(g_xMouse, g_yMouse, &m_Job))return true;
	g_pMainState->SetMouseOnMap(false);

	CheckOn(&m_Cancel, 100);
	CheckOn(&m_Up, -11);
	CheckOn(&m_Down, -12);
	m_Back[0].m_NeedShow = false;
	m_Back[1].m_NeedShow = false;
	int xstart = m_xPos + 15;
	int ystart = m_yPos + 60;
	if (g_xMouse > xstart && g_yMouse > ystart && g_xMouse < xstart + 150 && g_yMouse < ystart + 185)
	{
		m_Select = (g_yMouse - ystart) / m_gap;
		if (m_Select < m_JobList.size())
		{
			int ypos = ystart + m_gap*(m_Select);
			m_Back[0].SetY(ypos);
			m_Back[1].SetY(ypos);
			m_Back[0].m_NeedShow = true;
			m_Back[1].m_NeedShow = true;
			if (CheckL())return true;
		}
	}
	m_Select = 0;
	if (CheckRB())return true;

	//准备移动
	m_Select = 7;
	CheckL();
	return true;
}

bool cInterfaceJob::CheckL()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	}
	else return false;
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case -11:
		if (1)
		{
			m_Up.SetFrame(1);
			if (0 == m_Page)
			{
				m_Up.SetFrame(1);
				return true;
			}

			m_Page -= 1;
			UpDatePageTitle();
			m_Check = -1;
		}
		return true;
	case -12:
		if (1)
		{
			m_Down.SetFrame(1);
			if (m_JobList.size() - m_Page * 8 < 9)
			{
				return true;
			}

			m_Page += 1;
			UpDatePageTitle();
			m_Check = -1;
		}
		return true;
	case 6://移动
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
	case 7://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	case 100:
		if (1)
		{
			m_Cancel.SetFrame帧(1);
			OnOff(false);
		}
		return true;
	default:
		if (1)
		{
			SetSelect(m_Select);
		}
		return true;
	}

}

bool cInterfaceJob::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;

	m_Job.SetX(x);
	m_Job.SetY(y);


	m_Cancel.SetX(m_xPos + 350);
	m_Cancel.SetY(m_yPos + 5);

	int x1 = m_xPos + 165;
	m_Up.SetX(x1);
	m_Down.SetX(x1);
	m_Up.SetY(m_yPos + 40);
	m_Down.SetY(m_yPos + 240);

	m_Back[0].SetX(m_xPos + 14);
	m_Back[1].SetX(m_xPos + 68);
	//int ystart = m_yPos + 60;
	//int ypos = ystart + m_gap*(m_Check - 1);
	//m_Back[0].SetY(ypos);
	//m_Back[1].SetY(ypos);
	MoveContext(m_xPos, m_yPos);
	return true;
}

void cInterfaceJob::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	g_pMainState->m_Canvas.SetRedraw(m_Job.m_PreShowRect);
	if (NeedShow)
	{
		m_Page = 0;
		UpDatePageTitle();
		SetSelect(m_Check);
	}
}

bool cInterfaceJob::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		break;
	}
	return true;
}
bool cInterfaceJob::ReMoveJob(cTaskFather* p)
{
	for (int i = 0; i < m_JobList.size(); i++)
	{
		if (m_JobList[i].m_pTask->m_type == p->m_type)
		{
			m_JobList.erase(m_JobList.begin() + i);
			if (i == m_Check)
			{
				SetSelect(m_JobList.size() - 1);
			}
			break;
		}
	}
	return false;
}
bool cInterfaceJob::AddaJob(sJob& job, int huanshu)
{
	if (huanshu >= 0)
	{
		ostringstream oss;
		oss << job.m_Context;
		oss << "\n当前第#B ";
		oss << (huanshu + 1) << "#B 环";
		job.m_Context = oss.str();
	}
	for (int i = 0; i < m_JobList.size(); i++)
	{
		if (m_JobList[i].m_pTask->m_type == job.m_pTask->m_type || m_JobList[i].m_Title == job.m_Title)
		{
			if (job.m_Time > 0)
			{
				m_JobList[i].m_Time = job.m_Time;
			}
		//	if ("" == job.m_Context)job.m_Context = "无";
			m_JobList[i].m_Context = job.m_Context;
		//	if ("" == job.m_Title)job.m_Title = "无";
			m_JobList[i].m_Title = job.m_Title;
			m_TitleList[i].SetString(job.m_Title);
			return true;
		}
	}

	m_JobList.push_back(job);
	if (m_JobList.size() - m_Page * 8 < 9)
		m_TitleList[m_JobList.size() - m_Page * 8 - 1].SetString(job.m_Title);
	if (m_JobList.size() < 9)
		SetSelect(m_JobList.size() - 1);
	else
	{
		m_Page = m_JobList.size() / 8;
		UpDatePageTitle();
		SetSelect(m_JobList.size() - 1 - m_Page * 8);
	}
	return true;
}

bool cInterfaceJob::AddaJob(string title, string text, int huanshu /*= -1*/)
{
	return false;
	sJob job;
	job.m_Title = title;
	job.m_Context = text;
	return AddaJob(job, huanshu);
}



bool cInterfaceJob::updateJob(string title, string text, int huanshu /*= -1*/)
{
	return false;
	sJob job;
	job.m_Title = title;
	job.m_Context = text;
	return AddaJob(job, huanshu);
}


void cInterfaceJob::MoveContext(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		m_TitleList[i].SetXY(x + 18, y + 67 + i * 24);
	}
	m_Context.SetPos(x + 196, y + 59);
}

bool cInterfaceJob::CheckHaveJob(int ID)
{
	for (int i = 0; i < m_JobList.size(); i++)
	{
		if (m_JobList[i].m_pTask->m_type == ID)
			return true;
	}
	return false;
}

bool cInterfaceJob::CheckHaveJob(string title)
{
	for (int i = 0; i < m_JobList.size(); i++)
	{
		if (m_JobList[i].m_Title == title)
			return true;
	}
	return false;
}

void cInterfaceJob::Save(ofstream& File)
{
	File << "\n";
	CheckErr();
	File << m_JobList.size() << " ";
	if (!m_JobList.size())return;

	for (int i = 0; i < m_JobList.size(); i++)
	{
		File << "\n";
		sJob& job = m_JobList[i];
		File << job.m_Title << "\n";
		File << job.m_Context << "\n";
		File << job.m_Time << " ";
		File << job.m_pTask->m_type << " ";
		File << job.m_pTask->m_HuanShu << " ";
	}
	File << "0";
	File << "\n";
}

void cInterfaceJob::Load(ifstream& File)
{
	m_JobList.clear();
	int num;
	File >> num;
	if (!num)return;
	int type;
	//	int huanshu;
	string dustbin;
	m_JobList.resize(num);
	for (int i = 0; i < num; i++)
	{
		sJob& data = m_JobList[i];
		getline(File, data.m_Title);
		getline(File, data.m_Title);
		getline(File, data.m_Context);
		File >> data.m_Time;
		File >> type;
		data.m_pTask = g_pMainState->FindTaskByID(type);
		File >> data.m_pTask->m_HuanShu;
		if (m_JobList.size() - m_Page * 8 < 9)
			m_TitleList[m_JobList.size() - m_Page * 8 - 1].SetString(data.m_Title);
	}
	File >> num;
	if (0 != num)
		ERRBOX;
}


void cInterfaceJob::CheckErr()
{
	for (int i = 0; i < m_JobList.size(); i++)
	{
		if (m_JobList[i].m_Context == "" || m_JobList[i].m_Title == "")
		{
			m_JobList.erase(m_JobList.begin() + i);
			return CheckErr();
		}
	}
}


