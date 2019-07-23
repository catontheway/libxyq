#include "_global.h"

bool cTaskBaotu::Process(int stage)
{
	if (!m_bInit)Init();
	switch (stage)
	{
	case 0:
	{
		g_pMainState->m_Dialog.Reset();
		g_pMainState->m_Dialog.SetObj("店小二");
		m_Robber.m_name = AutoMakeName();
		m_Robber.m_mapname = m_MapNameList[rand() % m_MapNameList.size()];
		m_Robber.m_modeid = e山贼;
		g_pMainState->m_Map.AutoGetPos(m_Robber.m_x, m_Robber.m_y, m_Robber.m_mapname);

		auto cbText = [&](string b_y)
		{
			ostringstream oss("");
			oss << "#R贼王";
			oss << m_Robber.m_name;
			oss << "#R";
			oss << ((b_y == "#B") ?  "\n" : " 经过人肉搜索 ");
			oss << "#R" << m_Robber.m_mapname;
			oss << "#R " + b_y;
			oss << m_Robber.m_x;
			oss << " ";
			oss << m_Robber.m_y;
			oss << b_y;
			return oss.str();
		};
		g_pMainState->m_Dialog.SetString(cbText("#Y"));
		g_pMainState->m_Dialog.OnOff(true);
		cObj* pObj = g_pMainState->FindObjByName("店小二");
		pObj->m_AutoRun = false;

		sJob job;
		job.m_Context = cbText("#B");
		job.m_Title = "藏宝图";
		job.m_Time = 40;
		job.m_pTask = this;
		g_pMainState->m_Job.AddaJob(job);
		g_pMainState->m_TriggerObjMap.AddTask(this, 1, m_Robber);
		return true;
	}
		break;
	case 1:
	{
 		g_pMainState->AddEnemy(m_Robber.m_modeid, g_pMainState->getMaxLv(), eMP_随机, m_Robber.m_name);
		int num = g_pMainState->AtutoGetEnemyNum(2, 5);
		for (int i = 1; i < num; i++)
		{
			g_pMainState->AddEnemy(e强盗, g_pMainState->getAvgLv(), eMP_随机, "帮凶");

		}
		AddTriggerFightSuccess(3);
		g_StateType = STATE_FIGHT;
// 		cPropertyData* pPetdata;
// 		g_pMainState->m_FightWorkList[id].m_pObj->GetPropertyData(pPetdata);
// 		pPetdata->m_Controler.Set();
// 		SetMusic();
		return true;
	}
		break;
	case 3:

	{
		if (rand() % 100 < 0/*0 == rand()%10*/)
		{
			string nowname = m_Robber.m_name;
			m_Robber.m_name = AutoMakeName();

			m_Robber.m_mapname = m_MapNameList[rand() % m_MapNameList.size()];
			g_pMainState->m_Map.AutoGetPos(m_Robber.m_x, m_Robber.m_y, m_Robber.m_mapname);
			ostringstream oss;
			oss << "别打了,我只是个小喽啰,我们老大在#R";
			oss << m_Robber.m_mapname;
			oss << "#R " << "#R" << m_Robber.m_x << " " << m_Robber.m_y << "#R";
			g_pMainState->FindObjByName(nowname)->Talk(oss.str());
			g_pMainState->m_Dialog.m_pObj = 0;
			g_pMainState->m_Map.RemoveNpc(nowname);
			m_Robber.m_modeid = 8;
			g_pMainState->m_TriggerObjMap.AddTask(this, 4, m_Robber);

			sJob job;
			job.m_Context = oss.str();
			job.m_Title = "打宝图";
			job.m_Time = 40;
			job.m_pTask = this;
			g_pMainState->m_Job.AddaJob(job);
		}
		else
		{
			g_pMainState->m_Map.RemoveNpc(m_Robber.m_name);
			g_pMainState->m_TriggerObjMap.ReMove(this);
			g_pMainState->m_Job.ReMoveJob(this);
			if (1 || rand() % 100 < 80)
			{
				//得宝图
				sItem2 item;
				item.Set(28, 6);
				item.m_Num = 1;
				g_pMainState->m_ItemManage.AutoItemProperty(&item);
			//	for (int i = 0; i < 18; ++i)
				{ 
					g_pMainState->awardItem(item, false);
				}
			}
			g_pMainState->awardklv(30, 10);

		}
// 		sFightWork& lis = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID + 5];
// 		INT64 petexp = 0;
// 		int money = g_pCharacter->m_PcData.m_Lv * 10 + 2000 + rand() % 1000;
// 		if (lis.isExist&&!lis.CheckDie())
// 		{
// 			cPropertyData* petdata;
// 			lis.m_pObj->GetPropertyData(petdata);
// 			petexp = GetNormalFightExp(g_pCharacter->m_PcData.m_Lv, g_pCharacter->m_PcData.m_Lv);
// 		}
// 		SetJiangLi2(0, money, 0, (int)petexp);
		return true;
	}
		break;
	case 4:
	{
		cPropertyData* pPet;
		pPet = Add变身EnemyF(g_pCharacter->m_PcData.m_Lv * 120, (ePetID)m_Robber.m_modeid, g_pCharacter->m_PcData.m_Lv, eMP_随机, m_Robber.m_name);
		pPet->ComboRate.d1 += 50;
		for (int i = 0; i < 4; i++)
		{
			pPet = Add变身EnemyF(g_pCharacter->m_PcData.m_Lv * 80, e强盗, g_pCharacter->m_PcData.m_Lv);
			pPet->HitRate.d2 += 20;
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(5);
		return true;
	}
		break;
	case 5:

	{
		g_pMainState->m_Map.RemoveNpc(m_Robber.m_name);
		g_pMainState->m_TriggerObjMap.ReMove(this);
		g_pMainState->m_Job.ReMoveJob(this);
		//得五宝
		SetJiangLiItem(6 + rand() % 5, 27);
		SetJiangLi(3, true, 100, 0, 100, 200);
	}
		break;
	case 6:
	{
		g_pMainState->m_Tags.Add("你挖出了一个箱子,但从箱子里跑出个妖怪");
		int lv = g_pCharacter->m_PcData.m_Lv;
		string name = "远古";
		int petid = cct::getPetModel(45, 105);
		name += g_pMainState->m_PetDataManager.GetPetData(petid)->m_Name;
// 		int enemynum = g_pMainState->AtutoGetEnemyNum() - 1;
// 		cPropertyData* pPet = Add变身EnemyF(lv * 80, petid, -1, eMP_随机, name);
// 		pPet->AddSkill(ePS_高级反震);
// 		for (int i = 0; i < enemynum; i++)
// 		{
// 			Add变身EnemyF(lv * 40, (ePetID)(rand() % 40));
// 		}
// 		AddTriggerFightSuccess(7);


		auto p = g_pMainState->AddEnemy(petid, g_pMainState->getAvgLv() + 5, eMP_随机, name);
//		p->m_Name = "远古" + p->m_Name;
//		g_pMainState->m_FightWorkList[p->m_IDinFightWorkList].m_pObj->SetTrueName(p->m_Name);
		int num = g_pMainState->AtutoGetEnemyNum(2, 5);
		for (int i = 1; i < num; i++)
		{
			petid = cct::getPetModel();
			name = g_pMainState->m_PetDataManager.GetPetData(petid)->m_Name + "喽啰";
			auto p2 = g_pMainState->AddEnemy(petid, g_pMainState->getAvgLv(), eMP_随机, name);
//			p2->m_Name += "喽啰";
//			g_pMainState->m_FightWorkList[p2->m_IDinFightWorkList].m_pObj->SetTrueName(p2->m_Name);
		}
		AddTriggerFightSuccess(7);
		g_StateType = STATE_FIGHT;

	}
		break;
	case 7:
	{
		g_pCharacter->m_PcData.AddMoney(200000);
		g_pMainState->m_Tags.GetMoneyAndExp(200000);
// 		SetJiangLi(2, 1, 50, 0, 100, 200);
// 		if (0 == rand() % 10)
// 		{
// 			SetJiangLiItem(20, 24);
// 		}
	}
	default:
		break;
	}
	return false;
}

void cTaskBaotu::Init()
{
	if (m_bInit)return;
	m_bInit = true;
	//读取名字列表
	m_Firstname = { "赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "蒋", "沈", "韩", "杨", "朱", "秦", "尤", "许", "何", "吕", "施", "张", "孔", "曹", "严", "华", "金", "魏", "陶", "姜", "戚", "谢", "邹", "喻", "柏", "水", "窦", "章", "云", "苏", "潘", "葛", "奚", "范", "彭", "郎", "鲁", "韦", "昌", "马", "苗", "凤", "花", "方", "俞", "任", "袁", "柳", "酆", "鲍", "史", "唐", "费", "廉", "岑", "薛", "雷", "贺", "倪", "汤", "滕", "殷", "罗", "毕", "郝", "邬", "安", "常", "乐", "于", "时", "傅", "皮", "卞", "齐", "康", "伍", "余", "元", "卜", "顾", "孟", "平", "黄", "和", "穆", "萧", "尹", "司马", "诸葛", "夏候", "董", "林", "舒" };
	m_Secondname = { "一", "二", "三", "四", "五", "六", "七", "八", "九", "明", "融", "原", "白", "甫", "居", "易", "禹锡", "商隐", "牧", "贺", "九龄", "之涣", "勃", "甫松", "珣", "煜", "适", "维", "长卿", "愈", "况", "益", "仲淹", "阳修", "游", "弃疾", "飞", "始皇", "鞅", "安石", "不韦", "元璋", "操", "匡胤", "政", "邦", "亮", "世民", "居正", "宗元", "渊明", "宗元", "迁", "光", "天祥", "相如", "邦", "桓", "启", "世民", "渊", "匡胤", "元璋", "刚", "大", "虎", "仁", "春冬", "佳伟", "冬", "伟青", "良", "大郎", "二郎", "杰伦", "强", "超", "春铃", "俊杰", "彪", "忠", "帝", "尚", "轩", "文昂", "旭立", "芸", "河", "嘉", "存瑞" };
	m_MapNameList = cct::getFields();
// 	ifstream File;
// 	ostringstream oss;
// 	oss << g_pathData << "强盗名字.txt";
// 	File.open(oss.str());
// 	int num;
// 	File >> num;
// 	string data;
// 	string str;
// 	for (int i = 0; i < num; i++)
// 	{
// 		File >> data;
// 		m_Firstname.push_back(data);
// 		str += "\"" + data + "\",";
// 	}
// 	Q_LOG("%s", str.c_str());
// 	str = "";
// 	File >> num;
// 	for (int i = 0; i < num; i++)
// 	{
// 		File >> data;
// 		m_Secondname.push_back(data);
// 		str += "\"" + data + "\",";
// 	}
// 	File.close();
// 	Q_LOG("%s", str.c_str());
// 	oss.str("");
// 	oss << g_pathData << "强盗地点.txt";
// 	File.open(oss.str());
// 	File >> num;
// 	data = "";
// 	for (int i = 0; i < num; i++)
// 	{
// 		File >> str;
// 		m_MapNameList.push_back(str);
// 		data += "\"" + str + "\",";
// 	}
// 	File.close();
// 	Q_LOG("%s", data.c_str());
	m_type = 30;
}

std::string cTaskBaotu::AutoMakeName()
{
	string str;
	str = m_Firstname[rand() % m_Firstname.size()];
	str += m_Secondname[rand() % m_Secondname.size()];
	return str;
}

