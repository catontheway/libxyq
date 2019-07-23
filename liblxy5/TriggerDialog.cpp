#include "_global.h"

bool cTriggerDialog::AddTaskFB(string path, int id, cTaskFather* ptask, int stage)
{
	string path1/* = g_pathData*/;
	path1 += "副本//";
	path1 += path;
	path1 += "对话.txt";
	AddTask(path1, id, ptask, stage);
	return true;
}
bool cTriggerDialog::sDialogTrigger::AddTaskOriginal(int mode, cTaskFather* ptask, int stage, ifstream& File)
{
	m_Mode = mode;
	int textnum;
	File >> textnum;
	if (0 == textnum)return false;
	m_DialogList.resize(textnum);
	string dustbin;
	getline(File, dustbin);
	for (int i = 0; i < textnum; i++)
	{
		getline(File, m_DialogList[i].name);
		if (m_DialogList[i].name == "篮子" && 0)
			m_DialogList[i].name = g_pCharacter->m_PcData.m_Name;
		getline(File, m_DialogList[i].context);
	}
	m_pTask = ptask;
	m_Stage = stage;
	m_Nowtext = 0;
	return true;
}
bool cTriggerDialog::AddTask(string path, int id, cTaskFather* ptask, int stage)
{
	ifstream File;
	File.open(path);
	int tag;
	string name;
	string text;
	int textnum;
	File >> tag;
	while (tag != id)
	{
		File >> m_Mode;
		File >> textnum;

		getline(File, text);
		for (int i = 0; i < textnum; i++)
		{
			getline(File, name);
			getline(File, text);
		}
		File >> tag;
	}
	File >> m_Mode;
	switch (m_Mode)
	{
	case 1:
		m_datalist[0].AddTaskOriginal(m_Mode, ptask, stage, File);
		return Process(0);
	case 2:
		m_datalist[1].AddTaskOriginal(m_Mode, ptask, stage, File);
		return Process(1);
	default:
		ERRBOX;
		break;
	}
	return false;
}

bool cTriggerDialog::AddTask(cTaskFather* ptask, const vector<sTalkList>& dialogList, int stage /*= 0*/, int mode /*= 1*/)
{
	m_Mode = mode;
	auto& datalist = (mode == 1) ? m_datalist[0] : m_datalist[1];
	datalist.m_DialogList = dialogList;
	datalist.m_pTask = ptask;
	datalist.m_Stage = stage;
	datalist.m_Nowtext = 0;
	datalist.m_Mode = m_Mode;
	return Process(m_Mode - 1);
}

bool cTriggerDialog::sDialogTrigger::Process(bool skip /*= false*/)
{
	if (!m_pTask)
		return true;
	if (!skip)
	{
		if (m_Nowtext < m_DialogList.size())
		{
			if (1 == m_Mode) //1代表剧情对话
			{
				g_pMainState->m_Dialog.Talk(&m_DialogList[m_Nowtext]);
			}
			else
			{
				if (2 == m_Mode)//2代表普通对话
				{
					g_pMainState->m_Channel.AddNewString(m_DialogList[m_Nowtext].context, m_DialogList[m_Nowtext].name, 1);
				}
			}
			m_Nowtext += 1;
			return true;
		}
	}
	m_Nowtext = -1;
	cTaskFather* p = m_pTask;
	m_pTask = 0;
	m_DialogList.clear();
	p->Process(m_Stage);
	return false;
}
bool cTriggerDialog::Process(int id, bool skip)
{
	return m_datalist[id].Process(skip);
}

void cTriggerDialog::ReMove()
{
	m_datalist[0].m_pTask = 0;
	m_datalist[1].m_pTask = 0;
}

void cTriggerDialog::Save(ofstream& File)
{
	if (m_datalist[0].m_Nowtext > -1)
		g_pMainState->m_Dialog.Close();
	m_datalist[1].Save(File);
}
void cTriggerDialog::Load(ifstream& File)
{
	m_datalist[0].Reset();
	m_datalist[1].Load(File);
}

void cTriggerDialog::AddSelect(cTaskFather* p, string text, string name, int cancelret, string select0, int ret0, string select1, int ret1, string select2, int ret2, string select3, int ret3)
{
	cInterfaceDialog& d = g_pMainState->m_Dialog;
	d.Reset();
	d.SetObj(name);
	d.SetString(text, select0, select1, select2, select3);
	d.SetTrigger(p, cancelret, ret0, ret1, ret2, ret3);
	d.OnOff(true);
}

void cTriggerDialog::AddSelect(cTaskFather* p, string text, int ret0)
{
	cInterfaceDialog& d = g_pMainState->m_Dialog;
	d.Reset();
	d.SetObj(g_pMainState->m_pNowSelect);
	d.SetString(text, "确定", "取消");
	d.SetTrigger(p, -1, ret0, -1);
	d.OnOff(true);
}

cTriggerDialog::cTriggerDialog()
{
	m_datalist.resize(2);
}



void cTriggerDialog::sDialogTrigger::Save(ofstream& File)
{
	if (!m_pTask)
	{
		File << -1 << " ";
		return;
	}
	else
	{
		File << m_pTask->m_type << " ";
		File << m_Mode << " ";
		File << m_DialogList.size() << " ";
		for (int i = 0; i < m_DialogList.size(); i++)
		{
			m_DialogList[i].Save(File);
		}
	}
}

void cTriggerDialog::sDialogTrigger::Load(ifstream& File)
{
	Reset();
	int id;
	File >> id;
	if (-1 == id)return;
	m_pTask = g_pMainState->FindTaskByID(id);
	File >> m_Mode;
	int size;
	File >> size;
	if (!size)return;

	m_DialogList.resize(size);
	for (int i = 0; i < size; i++)
	{
		m_DialogList[i].Load(File);
	}
}


