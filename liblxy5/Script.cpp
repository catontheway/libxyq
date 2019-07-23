#include "Script.h"
struct sActTemplate
{
	int id;
	string name;
	vector<int> types;
};

static vector<sActTemplate> s_actMap =
{
	{ 0, "独白 ~",
	{ SENTRYTYPE_STRING } },
	{ 1, "NPC是否选择 描述~ ",
	{ SENTRYTYPE_STRING } },
	{ 2, "双选择  谁~ 描述~ 选项1 ~ 选项2 ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING } },
	{ 3, "三选择 谁~ 描述~ 选项1 ~ 选项2 ~ 选项3 ~ ",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING } },
	{ 4, "四选择 谁~ 描述~ 选项1 ~ 选项2 ~ 选项3 ~ 选项4 ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING } },
	{ 5, "脚本结束",
	{} },
	{ 6, "case ~",
	{ SENTRYTYPE_INT } },
	{ 7, "break",
	{} },
	{ 8, "default",
	{} },
	{ 9, "地图转换 地图名~ X~ Y~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 10, "指针跳跃 跳到几号标签~ 向上 ~ ",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 11, "购买界面 类型~ 商品等级~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 12, "结束switch",
	{} },
	{ 13, "无人独白 ~",
	{ SENTRYTYPE_STRING } },
	{ 14, "黑幕开关 ~",
	{ SENTRYTYPE_BOOL } },
	{ 15, "吐槽 ~ 说 ~ 频道 ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_INT } },
	{ 16, "设置开关 哪个~  状态~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 17, "设置触发 地图 ~ 位置 ~  ~ 范围 ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 18, "设置任务 名字 ~  描述 ~ ",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING } },
	{ 19, "加载主角 名字 ~  用于加载的ID ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_INT } },
	{ 20, "角色入队 源ID  ~  目标ID ~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 21, "设置角色位置 ID ~  X ~ Y ~ 方向 ~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 22, "开启任务 脚本名 ~ ",
	{ SENTRYTYPE_STRING } },
	{ 23, "标签 ID ~ ",
	{ SENTRYTYPE_INT } },
	{ 24, "设置触发 地图 ~ 名字 ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING } },
	{ 25, "读取对话链 名字 ~ ID ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_INT } },
	{ 26, "锁定地图 是否锁定 ~ 锁定到哪 X~ Y~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 27, "等待 时间 ~",
	{ SENTRYTYPE_INT } },
	{ 28, "得到钱  现金 ~ 储备金 ~ 角色ID ~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 29, "得到经验 ~ 角色ID ~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 30, "检查金钱 现金 ~ 储备金 ~ 角色ID ~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 31, "得到物品 类型 ~ ID ~ 数量 ~  角色ID ~ 是否显示 ~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 32, "设置任务EX 名字 ~  描述 ~ 消失条件 ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_INT } },
	{ 33, "设置触发  地图 ~ 角色名字 ~ 得到物品 类型 ~ ID ~ 数量 ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 34, "设置触发  地图 ~ 角色名字 ~ 得到钱 ~ 得到经验 ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 35, "设置对话方式 0到4表示频道,-1表示主剧情对话 ~",
	{ SENTRYTYPE_INT } },
	{ 36, "设置触发 主角等级 ~",
	{ SENTRYTYPE_INT } },
	{ 37, "设置任务角色 任务名 ~ 角色文件名 ~  所在地图名 ~ 位置 ~ ~ 方向 ~ 位置ID ~",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_STRING, SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT, SENTRYTYPE_INT } },
	{ 38, "删除任务角色 任务名 ~ 角色文件名 ~  ",
	{ SENTRYTYPE_STRING, SENTRYTYPE_STRING } },
	{ 39, "进入任务战斗 敌人名 ~",
	{ SENTRYTYPE_STRING } },
	{ 40, "关闭",
	{} },
	{ 41, "检测开关~ 是否为~",
	{ SENTRYTYPE_INT, SENTRYTYPE_INT } },
};

bool cScript::LoadActionTemplate(string Path)
{
	if (m_ActionTemplateList.empty())
	{
		forv(s_actMap, k)
		{
			sActionTemplate ActionTempale1;
			ActionTempale1.Name = s_actMap[k].name;
			ActionTempale1.NumOfEntryUnoin = s_actMap[k].types.size();
			if (ActionTempale1.NumOfEntryUnoin)
			{
				ActionTempale1.pEntryUnoinsType = new int[ActionTempale1.NumOfEntryUnoin];
				forv(s_actMap[k].types, i)
				{
					ActionTempale1.pEntryUnoinsType[i] = s_actMap[k].types[i];
				}
			}
			m_ActionTemplateList.push_back(ActionTempale1);
		}
	}
	return true;
	// 狼: 读取行为模板
	ifstream file;
	file.open(Path);
	if (!file)return false;
	while (true)
	{
		sActionTemplate ActionTempale1;
		ActionTempale1.Name = "";
		//读取一条行为模板  
			getline(file, ActionTempale1.Name);
			if (ActionTempale1.Name.size()<2)
				getline(file, ActionTempale1.Name);
			if (ActionTempale1.Name.size() < 2)
			{
				file.close();
//				return true;
				break;
			}
		

		for (uint i = 0; i < ActionTempale1.Name.length(); i++)
		{
			if (ActionTempale1.Name[i] == '~')
			{
				ActionTempale1.NumOfEntryUnoin += 1;
			}
		}
		ActionTempale1.pEntryUnoinsType = new int[ActionTempale1.NumOfEntryUnoin];
		string text;
		for (int i = 0; i < ActionTempale1.NumOfEntryUnoin; i++)
		{
			file >> text;
			if (!text.compare("STRING"))
			{
				ActionTempale1.pEntryUnoinsType[i] = SENTRYTYPE_STRING;
			}
			else
			if (!text.compare("INT"))
			{
				ActionTempale1.pEntryUnoinsType[i] = SENTRYTYPE_INT;
			}
			else
			if (!text.compare("FLOAT"))
			{
				ActionTempale1.pEntryUnoinsType[i] = SENTRYTYPE_FLOAT;
			}
			else
			if (!text.compare("BOOL"))
			{
				ActionTempale1.pEntryUnoinsType[i] = SENTRYTYPE_BOOL;
			}

		}
		m_ActionTemplateList.push_back(ActionTempale1);
	}

	vector<string> tnames =
	{
		"SENTRYTYPE_NULL",
		"SENTRYTYPE_STRING",
		"SENTRYTYPE_INT",
		"SENTRYTYPE_FLOAT",
		"SENTRYTYPE_BOOL"
	};



	string str;
	forv(m_ActionTemplateList, k)
	{
		const auto& t = m_ActionTemplateList[k];
		ccc_log("{%d, \"%s\",", k, t.Name.c_str());
		str = "{";
		for (int i = 0; i < t.NumOfEntryUnoin; ++i)
		{
			str += tnames[t.pEntryUnoinsType[i]] + ",";
		}
		if (str.size() > 1)
		{
			str.pop_back();
		}
		str += "}},";
		ccc_log(str.c_str());
	}

	return true;
}

void cScript::Add(sAction& Action)
{
	m_ActionList.push_back(Action);
}

void cScript::Insert(sAction& Action, int Pos)
{
	if (m_ActionList.size() < (uint)Pos)
	{
		return;
	}
	list<sAction>::iterator it;
	it = GetIterator(Pos);
	m_ActionList.insert(it, Action);
}

void cScript::Up(int Pos)
{
	if (m_ActionList.size()-1 < (uint)Pos)
	{
		return;
	}
	list<sAction>::iterator it;
	list<sAction>::iterator it2;
	it = GetIterator(Pos);
	it2 = GetIterator(Pos - 1);
	swap(*it2, *it);
}

void cScript::Down(int Pos)
{
	Up(Pos+1);
}

list<sAction>::iterator cScript::GetIterator(int Pos)
{
	list<sAction>::iterator it;
	it = m_ActionList.begin();
	for (int i = 0; i < Pos; i++)
	{
		it++;
	}
	return it;
}

void cScript::Delete(int Pos)
{
	list<sAction>::iterator it;
	it=GetIterator(Pos);
	m_ActionList.erase(it);
}

bool cScript::LoadScript(string name)
{
	// TODO:  在此添加控件通知处理程序代码
	ifstream  File;
	File.open(name);
	if (!File)return false;
	m_ActionList.clear();
	while (true)
	{
		sAction  Action;
		File >> Action.ID;
		if (File.eof())
		{
			return true;
		}
		File >> Action.NumOfEntryUnion;
		Action.pEntryUnoins = new sEntryUnion[Action.NumOfEntryUnion];
		for (int k = 0; k < Action.NumOfEntryUnion; k++)
		{
			File >> Action.pEntryUnoins[k].Type;
			switch (Action.pEntryUnoins[k].Type)
			{
			case SENTRYTYPE_INT:
				File >> Action.pEntryUnoins[k].intData;
				break;
			case SENTRYTYPE_FLOAT:
				File >> Action.pEntryUnoins[k].floatData;
				break;
			case SENTRYTYPE_BOOL:
				File >> Action.pEntryUnoins[k].intData;
				break;
			case SENTRYTYPE_STRING:
				File >> Action.pEntryUnoins[k].stringData;
				break;
			default:
				MessageBoxA(0, "未知类型", "读取", MB_OK);
				break;
			}
		}
		m_ActionList.push_back(Action);
	}
	return true;
}

void cScript::Free()
{
	list<sAction>::iterator it = m_ActionList.begin();
	for (uint i = 0; i < m_ActionList.size(); i++)
	{
		it->Free();
		it++;
	}
	list<sAction>  dustbin;
	m_ActionList.swap(dustbin);

	
	for (uint i = 0; i < m_ActionTemplateList.size(); i++)
	{
		m_ActionTemplateList[i].Free();
	}
	vector<sActionTemplate> dustbin2;
	m_ActionTemplateList.swap(dustbin2);
}
