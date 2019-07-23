#include "_global.h"
#include "_txt.h"


//#define ccc_checkwas

bool ItemManager::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_MagicAddHP.Load(0x77D2082D);
	m_MagicAddMP.Load(0x3E912705);
	m_MagicAddHPMP.Load(0x808CEB72);

	cWasFile was;

	sItem it;
	it.m_Price = 100;
	const auto& ts = ctt::getItems();
	for (const auto& t : ts)
	{
		it.m_Type = (int)t.e;
		it.m_ID = t.id;
		it.m_Name = t.name;
		it.m_SmallHead = t.small;
		it.m_BigHead = t.big;
		it.m_Text = t.desc;
		if (t.e == ctt::eItem::法宝f)
		{
			it.m_UseType = 7;
		}
		if ((t.e <= ctt::eItem::法杖f || (t.e >= ctt::eItem::巨剑j && t.e <= ctt::eItem::伞伞s)) && it.m_ID >= 9 && it.m_ID <= 14)
		{
		//	it.m_ID = (it.m_ID + 2 * (it.m_ID - 9));
		//	it.SetLv(it.m_ID);
			m_ItemList[it.m_Type].push_back(it);
		//	++it.m_ID;
			m_ItemList[it.m_Type].push_back(it);
		//	++it.m_ID;
			m_ItemList[it.m_Type].push_back(it);
		}
// 		else if (t.e == ctt::eItem::护腕h || t.e == ctt::eItem::项圈x || t.e == ctt::eItem::护甲h)
// 		{
// 			if (it.m_ID == 0)
// 			{
// 				continue;
// 			}
// 			else if (it.m_ID == )
// 			{
// 				it.m_ID = it.m_ID - 1;
// 			}
// 		}
		else 
		{
			if (t.e == ctt::eItem::卡片k)
			{
				int size = m_ItemList[it.m_Type].size();
				if (size == (int)eModel::大象dx/* || size == (int)eModel::小象xx*/)
				{
					it.m_SmallHead = 0xD5D3D1A7;
// 					if (size == (int)eModel::小象xx)
// 					{
// 						it.m_BigHead = m_ItemList[it.m_Type][(int)eModel::大象dx].m_BigHead;
// 					}
				}
				else if (size == (int)eModel::善财童子sc)
				{
					it.m_SmallHead = 0x404532E8;
				}
				else if (size == (int)eModel::腾蛇ts)
				{
					it.m_SmallHead = 0x66E05E50;
				}
				else if (size == (int)eModel::小白泽xb)
				{
//					it.m_SmallHead = m_ItemList[it.m_Type][(int)eModel::白泽bz].m_SmallHead;
					it.m_BigHead = m_ItemList[it.m_Type][(int)eModel::白泽bz].m_BigHead;
				}
				else if (size == (int)eModel::小泡泡xp)
				{
//					it.m_SmallHead = m_ItemList[it.m_Type][(int)eModel::泡泡pp].m_SmallHead;
					it.m_BigHead = m_ItemList[it.m_Type][(int)eModel::泡泡pp].m_BigHead;
				}
			}
			m_ItemList[it.m_Type].push_back(it);
			if (t.e == ctt::eItem::卡片k && m_ItemList[it.m_Type].size() == c_PetNumber - 2)
			{
			}
		}


#ifdef ccc_checkwas
		was.Load(it.m_SmallHead);
		was.Load(it.m_BigHead);
#endif
	}



	for (const auto& fb : { 4, 11, 12, 13, 14, 15, 16, 34 })
	{
		m_ItemList[(int)ctt::eItem::法宝f][fb].m_UseType = 0;
	}

	const auto& ws = ctt::getWeapons();
	const auto& tiggerDie = ctt::getWeapon斧钺虎子死亡s();
	for (const auto& w : ws)
	{
		int i = -1;
		for (const auto& a : w.actions)
		{
			int type = (int)w.e;
			if (type >= 42)
			{
				type -= 27;
			}
			if (m_pWeaponList2[type][++i].empty())
			{
				m_pWeaponList2[type][i].resize(2);
			}
			auto& data = m_pWeaponList2[type][i][0];
			auto& data2 = m_pWeaponList2[type][i][1];
			data.m_attack = a.action.atk;
			data.m_attack2 = a.action.atk/*2*/;
			data.m_defend = a.action.def;
			data.m_dead = a.action.dead;
			data.m_fstand = a.action.await;
			data.m_magic = a.action.maigc;
			data.m_return = a.action.back;
			data.m_run = a.action.go;
			data.m_stand = a.action.stand;
			data.m_walk = a.action.walk;
			data.m_suffer = a.action.atkd;
			data.Master = (int)a.role;
			data.MasterPos = (int)a.actionsIndex;

			if (type < 15)
			{

				data2.m_attack = a.action2.atk;
				data2.m_attack2 = a.action2.atk/*2*/;
				data2.m_defend = a.action2.def;
				if (cct::getINT(6) && w.e == ctt::eItem::斧钺f)
				{
					data2.m_dead = tiggerDie[i];
				}
				else
				{
					data2.m_dead = a.action2.dead;
				}
				data2.m_fstand = a.action2.await;
				data2.m_magic = a.action2.maigc;
				data2.m_return = a.action2.back;
				data2.m_run = a.action2.go;
				data2.m_stand = a.action2.stand;
				data2.m_walk = a.action2.walk;
				data2.m_suffer = a.action2.atkd;
				data2.Master = (int)a.role2;
				data2.MasterPos = (int)a.actionsIndex2;
			}
			else
			{
				if (type == 15)
				{
					swap(data.m_magic, data.m_attack);
				}
				data2 = data;
				
#ifdef ccc_checkwas
				was.Load(data.m_attack);
				was.Load(data.m_attack2);
				was.Load(data.m_defend);
				was.Load(data.m_dead);
				was.Load(data.m_fstand);
				was.Load(data.m_magic);
				was.Load(data.m_return);
				was.Load(data.m_run);
				was.Load(data.m_stand);
				was.Load(data.m_walk);
				was.Load(data.m_suffer);

				was.Load(data2.m_attack);
				was.Load(data2.m_attack2);
				was.Load(data2.m_defend);
				was.Load(data2.m_dead);
				was.Load(data2.m_fstand);
				was.Load(data2.m_magic);
				was.Load(data2.m_return);
				was.Load(data2.m_run);
				was.Load(data2.m_stand);
				was.Load(data2.m_walk);
				was.Load(data2.m_suffer);
#endif
			}
		}
	}

	// 装备等级
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < m_ItemList[i].size(); j++)
		{
			m_ItemList[i][j].m_ID = j;
			m_ItemList[i][j].SetLv(GetlvByID(i, j));
		}
	}
	for (int i = 32; i <= 34; i++)
	{
		for (int j = 0; j < m_ItemList[i].size(); j++)
		{
			m_ItemList[i][j].m_ID = j;
			if (j == 0)
			{
				m_ItemList[i][j].SetLv(m_ItemList[i].size() * 10 - 5);
				m_ItemList[i][j].m_Text = "狼宝特供";
			}
			else
			{
				m_ItemList[i][j].SetLv(j * 10 - 5);
			}
		}
	}
	for (int i = 42; i <= 44; i++)
	{
		for (int j = 0; j < m_ItemList[i].size(); j++)
		{
			m_ItemList[i][j].m_ID = j;
			m_ItemList[i][j].SetLv(GetlvByID(i, j));
		}
	}


	const auto& zqzs = ctt::getZqzss();
	const auto& cTable = ctt::getColors();
	forv(zqzs, k)
	{
		auto& t = zqzs[k];
		it.m_Type = (int)ctt::eItem::坐饰z;
		it.m_ID = t.id;
		it.m_Name = t.name;
		it.m_SmallHead = t.small;
		it.m_BigHead = t.big;
		m_ItemList[it.m_Type].push_back(it);

		auto& zs = m_ZuoQiZhuangShiList[k];
		zs.NodeStand = t.stand;
		zs.NodeWalk = t.walk;
		zs.m_ColorID = t.color;
		const auto& iter = cTable.find(zs.m_ColorID);
		if (iter != cTable.end())
		{
			zs.m_ColorID = iter->second;
		}

#ifdef ccc_checkwas
		was.Load(it.m_SmallHead);
		was.Load(it.m_BigHead);
		was.Load(zs.NodeStand);
		was.Load(zs.NodeWalk);
		was.Load(zs.m_ColorID);
#endif
		forv(zs.Stand, i)
		{
			zs.Stand[i] = 0;
			zs.Walk[i] = 0;
		}

		forv(t.masters, i)
		{
			const auto& m = t.masters[i];
			zs.Stand[(int)m.master] = m.stand;
			zs.Walk[(int)m.master] = m.walk;

#ifdef ccc_checkWas
			was.Load(m.stand);
			was.Load(m.walk);
#endif
		}
	}

	//家园的资源,暂时不用
	sJiaJuData data;
	const auto& jjs = ctt::getJiajus();
	forv(jjs, k)
	{
		const auto& jj = jjs[k];
		it.m_Type = (int)jj.type;
		it.m_ID = jj.id;
		it.m_Name = jj.desc;
		it.m_SmallHead = jj.small;
		it.m_BigHead = jj.big;
		it.SetLv(0);
		if (it.m_Name == "草编地毯" || it.m_Name == "白鹤展翅帘" || it.m_Name == "兽皮地毯" || it.m_Name == "麻布地毯" || 
			it.m_Name == "夕阳山水图" || it.m_Name == "猛虎坐山图" || it.m_Name == "海之珠贝图" || it.m_Name == "黄缎锦边帘" || 
			it.m_Name == "波斯地毯" || it.m_Name == "白虎皮毯" || it.m_Name == "凤凰傲意图" || it.m_Name == "海之彩鱼毯" || 
			it.m_Name == "玲珑兔粉缎帘")
		{
			it.SetLv(1);
		}
		else if (it.m_Name == "踏春图")
		{
			it.SetLv(2);
		}
		else if (it.m_Name == "漆花地板" || it.m_Name == "桦木地板" || it.m_Name == "红木地板" || 
			it.m_Name == "海之蔚蓝石砖" || it.m_Name == "玲珑兔梦幻家园")
		{
			it.SetLv(3);
		}
		else if (it.m_Name == "花开富贵门" || it.m_Name == "玲珑兔美梦屏风")
		{
			it.SetLv(4);
		}
		else if (it.m_Name == "海之七色门")
		{
			it.SetLv(5);
		}
		it.m_Text = jj.name;
		m_ItemList[it.m_Type].push_back(it);

#ifdef ccc_checkwas
		was.Load(it.m_SmallHead);
		was.Load(it.m_BigHead);
#endif
		const auto& js = jj.uids;
		data.num = js.size();
		data.m_data.clear();
		forv(js, i)
		{
			data.m_data.push_back(js[i]);
#ifdef ccc_checkwas
			was.Load(js[i]);
#endif
		}
		m_JiaJuData[it.m_Type - (int)ctt::eItem::一家y].push_back(data);
	}


#if 0

	cct::get()->pushWdf("吃药红", 0x77D2082D);
	cct::get()->pushWdf("吃药蓝", 0x3E912705);
	cct::get()->pushWdf("吃药紫", 0x808CEB72);

	string myWeaponPath = g_pathData + "武器//";
	string myEquipPath = g_pathData + "装备//";
#pragma omp parallel sections
	{
#pragma omp  section
		{
			ifstream File;
			int id, num;
			ostringstream oss;
			oss << myWeaponPath << "武器.txt";
			File.open(oss.str());
			int typenum;
			File >> typenum;
			vector<string> weaponNames = { "剑", "刀", "枪", "锤", "斧", "扇",
				"爪", "棒", "飘带", "鞭", "环", "双剑", "珠", "弓", "杖" };
			for (int j = 0; j < typenum; j++)
			{
				File >> id;
				File >> num;
				string dustbin;
				for (int i = 0; i < 11; i++)
				{
					vector<sWeaponData>& data = m_pWeaponList2[j][i];
					data.resize(num);
					for (int k = 0; k < num; k++)
					{
						cct::get()->strDescTemp = weaponNames[j] + toString("%d_%d_", i, k);
						data[k].Read(File);
						if (k < 2 || (k == 2 && cct::get()->isPushRole15))
						{
							// 		vector<string> weaponAtcs = { "攻", "防", "死", "战", "法", "转",
							// 			"跑", "站", "受", "走", "" };
							cct::get()->pushWeapon(cct::get()->strDescTemp + "攻", data[k].m_attack);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "防", data[k].m_defend);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "死", data[k].m_dead);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "战", data[k].m_fstand);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "法", data[k].m_magic);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "转", data[k].m_return);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "跑", data[k].m_run);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "站", data[k].m_stand);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "受", data[k].m_suffer);
							cct::get()->pushWeapon(cct::get()->strDescTemp + "走", data[k].m_walk);
						}
						if (k == 0)getline(File, dustbin);//备注
					}
				}
			}
			File.close();
			oss.str("");
			oss << myWeaponPath << "剑.txt";
			cct::get()->strDescTemp = "剑";
			LoadItem1(oss.str());
		}

#pragma omp  section
		{
			ostringstream oss;
			oss << myWeaponPath << "刀.txt";
			cct::get()->strDescTemp = "刀";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "枪.txt";
			cct::get()->strDescTemp = "枪";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "锤.txt";
			cct::get()->strDescTemp = "锤";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "斧.txt";
			cct::get()->strDescTemp = "斧";
			LoadItem1(oss.str());
			oss.str("");
		}
#pragma omp  section
		{
			ostringstream oss;
			oss << myWeaponPath << "扇.txt";
			cct::get()->strDescTemp = "扇";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "爪.txt";
			cct::get()->strDescTemp = "爪";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "棒.txt";
			cct::get()->strDescTemp = "棒";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "飘带.txt";
			cct::get()->strDescTemp = "飘带";
			LoadItem1(oss.str());
		}
#pragma omp  section
		{
			ostringstream oss;
			oss << myWeaponPath << "鞭.txt";
			cct::get()->strDescTemp = "鞭";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "环.txt";
			cct::get()->strDescTemp = "环";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "双剑.txt";
			cct::get()->strDescTemp = "双剑";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "珠.txt";
			cct::get()->strDescTemp = "珠";
			LoadItem1(oss.str());
		}
#pragma omp  section
		{
			ostringstream oss;
			oss << myWeaponPath << "弓.txt";
			cct::get()->strDescTemp = "弓";
			LoadItem1(oss.str());
			oss.str("");
			oss << myWeaponPath << "杖.txt";
			cct::get()->strDescTemp = "杖";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表//坐骑装饰.txt";
			//			cct::get()->strDescTemp = "坐骑装饰";
			LoadZuoqiZhuangShi(oss.str());
			oss.str("");
			oss << myEquipPath << "头盔.txt";
			cct::get()->strDescTemp = "头盔";
			LoadItem1(oss.str());
			oss.str("");
			oss << myEquipPath << "发钗.txt";
			cct::get()->strDescTemp = "发钗";
			LoadItem1(oss.str());
			oss.str("");

		}
#pragma omp  section
		{
			ostringstream oss;
			oss << myEquipPath << "铠甲.txt";
			cct::get()->strDescTemp = "铠甲";
			LoadItem1(oss.str());
			oss.str("");
			oss << myEquipPath << "女衣.txt";
			cct::get()->strDescTemp = "女衣";
			LoadItem1(oss.str());
			oss.str("");
			oss << myEquipPath << "项链.txt";
			cct::get()->strDescTemp = "项链";
			LoadItem1(oss.str());
			oss.str("");
			oss << myEquipPath << "腰带.txt";
			cct::get()->strDescTemp = "腰带";
			LoadItem1(oss.str());
		}
#pragma omp  section
		{
			ostringstream oss;
			oss << myEquipPath << "鞋.txt";
			cct::get()->strDescTemp = "鞋";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\药品.txt";
			cct::get()->strDescTemp = "药品";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\烹饪.txt";
			cct::get()->strDescTemp = "烹饪";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\法宝.txt";
			//			cct::get()->strDescTemp = "法宝";
			LoadFaBao(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\兽决.txt";
			//			cct::get()->strDescTemp = "兽决";
			LoadShouJue(oss.str());
		}
#pragma omp  section
		{
			ostringstream oss;
			oss << g_pathData << "道具列表\\暗器.txt";
			cct::get()->strDescTemp = "暗器";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\变身卡.txt";
			cct::get()->strDescTemp = "变身卡";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\道具.txt";
			cct::get()->strDescTemp = "道具";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\不可叠加道具.txt";
			cct::get()->strDescTemp = "不可叠";
			LoadItem1(oss.str());
		}
#pragma omp  section
		{
			ostringstream oss;
			oss << g_pathData << "道具列表\\花.txt";
			cct::get()->strDescTemp = "花";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\宝石.txt";
			cct::get()->strDescTemp = "宝石";
			LoadItem1(oss.str());
			oss.str("");
			oss << myEquipPath << "召唤兽护腕.txt";
			cct::get()->strDescTemp = "护腕";
			LoadItem1(oss.str());
			oss.str("");
			oss << myEquipPath << "召唤兽铠甲.txt";
			cct::get()->strDescTemp = "BB甲";
			LoadItem1(oss.str());
		}
#pragma omp  section
		{
			ostringstream oss;
			oss << myEquipPath << "召唤兽项圈.txt";
			cct::get()->strDescTemp = "项圈";
			LoadItem1(oss.str());
			// 			oss.str("");
			// 			oss << g_strDataPath << "数据//武器//杖.txt";
			// 			cct::get()->strDescTemp = "杖";
			// 			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\乐器.txt";
			cct::get()->strDescTemp = "乐器";
			LoadItem1(oss.str());
			oss.str("");
			oss << g_pathData << "道具列表\\家具.txt";
			//			cct::get()->strDescTemp = "家具";
			LoadJiaJu(oss.str());
		}
#pragma omp  section
	{
		ifstream File;
		int num;
		ostringstream oss;
		oss << g_pathData << "道具列表\\兽决定义.txt";
		File.open(oss.str());
		int ID;
		File >> num;
		for (int i = 0; i < num; i++)
		{
			File >> ID;
			m_LShouJueList.push_back(ID);
		}
		File >> num;
		for (int i = 0; i < num; i++)
		{
			File >> ID;
			m_HShouJueList.push_back(ID);
		}
		File.close();
	}
#pragma omp  section
		{
			ifstream File;
			int num, ID;
			ostringstream oss;
			oss << g_pathData << "道具列表\\物品类型名.txt";
			File.open(oss.str());
			if (!File)ERRBOX;
			File >> num;
			string name;
			for (int i = 0; i < num; i++)
			{
				File >> ID;
				File >> name;
				m_ItemTypeName.push_back(name);
			}
			File.close();
			oss.str("");
			oss << g_pathData << "道具列表\\符石.txt";
			File.open(oss.str());
			if (!File)ERRBOX;
			int type;
			File >> type;
			ulong smallhead, bighead;
			vector<sItem>& list = m_ItemList[type];
			File >> bighead;
			File >> smallhead;
			File >> name;
			File >> num;
			list.resize(num);
			for (int i = 0; i < num; i++)
			{
				File >> list[i].m_ID;
				File >> ID;//无用
				File >> list[i].m_Price;
				list[i].m_Name = name;
				File >> list[i].m_Text;
				list[i].m_Type = type;
				list[i].m_BigHead = bighead;
				list[i].m_SmallHead = smallhead;
			}
			cct::get()->pushItemHead("符石大", bighead);
			cct::get()->pushItemHead("符石小", smallhead);
			File.close();
		}
	}

	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < m_ItemList[i].size(); j++)
		{
			m_ItemList[i][j].SetLv(GetlvByID(i, j));
		}
	}

#endif

	return true;
}


//读取坐骑装饰
bool ItemManager::LoadZuoqiZhuangShi(string path)
{
	ifstream File;
	File.open(path);
	if (!File)return false;
	int num;
	string dustbin;
	File >> num;
	sItem item;
	item.m_Type = 31;
	if (num != 24)return false;
	for (int i = 0; i < num; i++)
	{
		item.m_Price = 1000000;
		File >> item.m_ID;
		File >> item.m_Name;
		File >> item.m_SmallHead;
		File >> item.m_BigHead;
		m_ItemList[31].push_back(item);
		File >> m_ZuoQiZhuangShiList[i].NodeStand;
		File >> m_ZuoQiZhuangShiList[i].NodeWalk;
		File >> m_ZuoQiZhuangShiList[i].m_ColorID;
		ccm::get()->pushZuoqiHead(item.m_Name + "(坐骑装饰大)", item.m_BigHead);
		ccm::get()->pushZuoqiHead(item.m_Name + "(坐骑装饰小)", item.m_SmallHead);
		ccm::get()->pushZuoqi(item.m_Name + "(坐骑装饰站)", m_ZuoQiZhuangShiList[i].NodeStand);
		ccm::get()->pushZuoqi(item.m_Name + "(坐骑装饰走)", m_ZuoQiZhuangShiList[i].NodeWalk);
		forv(m_ZuoQiZhuangShiList[i].Stand, j)
		{
			File >> dustbin;
			File >> m_ZuoQiZhuangShiList[i].Stand[j];
			File >> m_ZuoQiZhuangShiList[i].Walk[j];
// 			if (j == 14 && !cct::get()->isPushRole15)
// 			{
// 				continue;
// 			}
			ccm::get()->pushZuoqi(item.m_Name + toString("(坐骑装饰_角色%d_站)", j), m_ZuoQiZhuangShiList[i].Stand[j]);
			ccm::get()->pushZuoqi(item.m_Name + toString("(坐骑装饰_角色%d_走)", j), m_ZuoQiZhuangShiList[i].Walk[j]);
		}
	}
	File.close();
	return true;
}


bool ItemManager::LoadItem1(string path)
{
	ifstream File;
	File.open(path);
	int type;
	File >> type;

	int num;
	File >> num;
	vector<sItem>& item = m_ItemList[type];
	item.resize(num);

	string tex;
	for (int i = 0; i < num; i++)
	{
		item[i].m_Type = type;
		File >> item[i].m_ID;
		File >> item[i].m_Name;
		File >> item[i].m_SmallHead;
		File >> item[i].m_BigHead;
		File >> item[i].m_Price;
		getline(File, item[i].m_Text);
		getline(File, item[i].m_Text);

		ccm::get()->pushItemHead(item[i].m_Name + "大(" + ccm::get()->strDescTemp + ")", item[i].m_BigHead);
		ccm::get()->pushItemHead(item[i].m_Name + "小(" + ccm::get()->strDescTemp + ")", item[i].m_SmallHead);
	}
	File.close();
	if (type == 0)
	{
		std::swap(item[12], item[15]);
		std::swap(item[12].m_ID, item[15].m_ID);

		std::swap(item[13], item[16]);
		std::swap(item[13].m_ID, item[16].m_ID);

		std::swap(item[14], item[17]);
		std::swap(item[14].m_ID, item[17].m_ID);
	}
// 	else if (type == 22)
// 	{
// 		item[17].m_Text = "HP+2000,疗伤+2000";
// 		item[18].m_Text = "HP+3000";
// 		item[43].m_Text = "MP+1000";
// 	}
	return true;
}

bool ItemManager::LoadFaBao(string path)
{
	ifstream File;
	File.open(path);
	int type;
	File >> type;
	int num;
	File >> num;
	sItem item;
	for (int i = 0; i < num; i++)
	{
		item.m_Type = type;
		File >> item.m_ID;
		File >> item.m_Name;
		//File >> item.m_Lv;
		File >> item.m_SmallHead;
		File >> item.m_BigHead;
		File >> item.m_UseType;
		File >> item.m_Price;
		getline(File, item.m_Text);
		getline(File, item.m_Text);
		m_ItemList[type].push_back(item);
		ccm::get()->pushItemHead(item.m_Name + "(法宝大)", item.m_BigHead);
		ccm::get()->pushItemHead(item.m_Name + "(法宝小)", item.m_SmallHead);
	}
	File.close();
	item.m_ID = num;
	item.m_Name = "黄色导标旗";
	item.m_SmallHead = 1084205009;
	item.m_BigHead = 1030021222;
	item.m_UseType = m_ItemList[type][12].m_UseType;
	item.m_Price = m_ItemList[type][12].m_Price;
	item.m_Text = "境外导标旗";
	m_ItemList[type].push_back(item);
	ccm::get()->pushItemHead(item.m_Name + "(法宝大)", item.m_BigHead);
	ccm::get()->pushItemHead(item.m_Name + "(法宝小)", item.m_SmallHead);

	return true;
}


bool ItemManager::LoadShouJue(string path)
{
	ifstream File;
	File.open(path);
	string name = "魔兽要决";
	int type;
	File >> type;
	int num;
	File >> num;
	ulong head[2];
	string text;
	File >> head[0];
	File >> head[1];
	ccm::get()->pushItemHead("兽决大", head[1]);
	ccm::get()->pushItemHead("兽决小", head[0]);
	File >> text;
	text += "(包含技能:";
	sItem item;
	for (int i = 0; i < num; i++)
	{
		item.m_Type = type;
		File >> item.m_ID;
		File >> item.m_Name;
		if (item.m_ID == 77)
		{
			item.m_Name = "盾气";
		}
		else if (item.m_ID == 78)
		{
			item.m_Name = "高级盾气";
		}
		else if (item.m_ID == 81)
		{
			item.m_Name = "风华合纵";
		}
		else if (item.m_ID == 96)
		{
			item.m_Name = "剑荡四方";
		}
		//File >> item.m_Lv;
		item.m_SmallHead = head[0];
		item.m_BigHead = head[1];
		File >> item.m_Price;
		//		item.m_Price /= 10;
		item.m_Text = text;
		item.m_Text += item.m_Name;
		item.m_Text += ")";
		item.m_Name = name;
		m_ItemList[type].push_back(item);
	}
	File.close();
	vector<string> names = { "须弥真言", "从天而降", "月光" };
	vector<int> prices = { 50000000, 10000000, 50000000 };
	for (int i = 0; i < 3; ++i)
	{
		item.m_Type = type;
		item.m_ID = i + num;
		item.m_Name = names[i];
		item.m_SmallHead = head[0];
		item.m_BigHead = head[1];
		item.m_Price = prices[i];
		item.m_Text = text;
		item.m_Text += item.m_Name;
		item.m_Text += ")";
		item.m_Name = name;
		m_ItemList[type].push_back(item);
	}
	return true;
}



bool ItemManager::LoadWeapon(string path)
{
	ifstream File;
	File.open(path);
	int type;
	File >> type;
	int num;
	File >> num;
	sItem item;
	int weaponlv;
	for (int i = 0; i < num; i++)
	{
		item.m_Type = type;
		File >> item.m_ID;
		File >> item.m_Name;

		File >> weaponlv;
		item.SetLv(weaponlv);
		File >> item.m_SmallHead;
		File >> item.m_BigHead;
		getline(File, item.m_Text);
		getline(File, item.m_Text);

		//int k = 0;
		//if (i >= 9)k = i - 6;    //
		//else if (i < 3)k = 0;  //0-20级的武器造型一样
		//else if (i < 6)k = 1;  //30-50级的武器造型一样
		//else if (i < 9)k = 2;  //60-80
		////int WeaponOffset = m_pWeaponList[0].Type * 11 + k;
		//m_pWeaponList[type].data[i].m_pData[0] = &m_pWeaponList2[k + type * 11];
		//m_pWeaponList[type].data[i].m_pData[1] = &m_pWeaponList2[k + type * 11 + 165];
	}
	File.close();
	return true;
}



bool ItemManager::LoadJiaJu(string path)
{
	ifstream File;
	File.open(path);
	LoadJiaJuCube(File, 35);
	LoadJiaJuCube(File, 36);
	LoadJiaJuCube(File, 37);
	LoadJiaJuCube(File, 38);
	File.close();
	return true;
}

void ItemManager::LoadJiaJuCube(ifstream& File, int type)
{
	int lv;
	int num;
	sItem item;

	File >> lv;
	File >> num;
	int jiajulv;
	for (int i = 0; i < num; i++)
	{
		item.m_Type = type;
		item.m_ID = i;
		File >> item.m_Name;
		File >> item.m_SmallHead;
		File >> item.m_BigHead;
		File >> jiajulv;
		item.SetLv(jiajulv);//记录家具的类型
		File >> item.m_Price;

		switch (lv)
		{
		case 1:
			item.m_Text = "一级家具"; break;
		case 2:
			item.m_Text = "二级家具"; break;
		case 3:
			item.m_Text = "三级家具"; break;
		case 4:
			item.m_Text = "四级家具"; break;
		default:
			ERRBOX;
			break;
		}
		ccm::get()->pushHomeHead(item.m_Name + "_" + item.m_Text + "大", item.m_BigHead);
		ccm::get()->pushHomeHead(item.m_Name + "_" + item.m_Text + "小", item.m_SmallHead);
		m_ItemList[type].push_back(item);
		//下面是家园的资源,暂时不用
		sJiaJuData data;
		ulong PicID;
		File >> data.num;

		for (int j = 0; j < data.num; j++)
		{
			File >> PicID;
			data.m_data.push_back(PicID);
			ccm::get()->pushHome(item.m_Name + "_" + item.m_Text + toString("%d", j), PicID);
		}
		m_JiaJuData[lv - 1].push_back(data);
	}
}
