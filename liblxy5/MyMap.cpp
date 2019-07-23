#include "_global.h"
#include "_txt.h"
#include "../libutil/cFolder.h"

//#define ccc_checkwas

void sTriggerRange::Save(ofstream& File)
{
	if (!m_p)
	{
		File << 0;
		return;
	}
	else File << 1 << " ";
	File << m_range << " ";
	File << m_x << " ";
	File << m_y << " ";
	File << m_p->m_type << " ";
	File << m_ret << " ";
	File << m_name << " ";
}

void sTriggerRange::Load(ifstream& File)
{
	bool live;
	File >> live;
	if (!live)return;

	File >> m_range;
	File >> m_x;
	File >> m_y;
	int type;
	File >> type;
	m_p = g_pMainState->FindTaskByID(type);
	File >> m_ret;
	File >> m_name;
}

void sTriggerRange::Set(string name, int x, int y, int range, cTaskFather* p, int ret)
{
	m_name = name;
	m_range = range * 20;
	m_x = x * 20;
	m_y = g_pMainState->m_Map.m_pMap->m_Height - m_y * 20;
	m_p = p;
	m_ret = ret;
}

bool sRangeTr::Check(int x, int y)
{
	if (abs(x - m_x) < m_range&&abs(y - m_y) < m_range)
	{
		if (m_name == "")return true;
		if (m_name == g_pMainState->m_Map.m_MapName)
			return true;
		return false;
	}
	return false;
}


static std::string getMapName(int mapid)
{
	std::string name = toString("%d.map", mapid);
	auto fol = cFolder::getInstance();
	auto root = fol->getRoot();
	const auto& folders = fol->getMaps().at(eMapType::iter);
	for (const auto& folder : folders)
	{
		static std::ifstream ifile;
		ifile.open(root + folder + name, std::ios::binary);
		if (ifile.is_open())
		{
			ifile.close();
			return root + folder + name;
		}
	}
	// 引用,所以也要常驻周期
	static std::string s_strEmpty;
	return s_strEmpty;
}


bool cMyMap::LoadMap(long x, long y, const char* Name, bool bFly)
{
	if (bFly)
	{
		if (g_GlobalValues[10])
		{
			g_pMainState->m_Tags.Add("当前无法飞行");
			return true;
		}
	}
	if (m_LockList.size())
	{
		for (int i = 0; i < m_LockList.size(); i++)
			if (0 == m_LockList[i].compare(Name))return true;
	}
	if (g_StateType != STATE_MAIN)
		return false;
	while (!m_pMap->m_bLoadReady2)
	{
		Sleep(1);
		//		m_pMap->_mySleep->sleep(1);
	}
	g_pMainState->m_InterfaceSmallMap.OnOff(false);
	g_pMainState->m_Dialog.Close();
	g_pMainState->m_TaskNormal.m_pNpc = 0;
	if (g_pMainState->m_pNowSelect)
	{
		g_pMainState->m_pNowSelect->SetShine(false);
		g_pMainState->m_pNowSelect = 0;
	}
	for (int i = 1; i < MAX_OBJ_NUM; i++)
	{
		g_pMainState->m_pObj[i] = 0;
	}
	string prename = m_MapName;
	m_MapName = Name;
#define ctt_txt2
#ifdef ctt_txt2
#ifdef ccc_checkwas
	static bool s_once = true;
	static cWasFile was;
	if (s_once)
	{
		s_once = false;
		const auto& ms = ctt::getMaps();
		for(const auto& m : ms)
		{
			was.LoadMap(m.uid);
		}
	}
#endif
	const auto& mp = ctt::getMap(Name);
	if (!mp)
#else
	ostringstream oss;
	oss << g_pathSceneTxt << Name << ".txt";
	string txtpath = oss.str();
	oss.str("");
	ifstream  file;
	file.open(txtpath.c_str());//,ios::binary|ios::in);
	if (!file)
#endif
	{
		m_MapName = prename;
		return false;
	}
	int MapNumber;
#ifdef ctt_txt2
	const auto& m = *mp;
	MapNumber = m.id;
	if(m_MapName == "赤水洲")
	{
		if (rand() % 100 < 50)
		{
			MapNumber = 1259;
		}
	}
#else
	file >> MapNumber;    //读取地图编号
#endif
	if (MapNumber < 0 || MapNumber > 2000)
	{
		ERRBOX;
		asert(false, "地图编号出错(%d.map)", MapNumber);
	}
	if (prename != m_MapName)
	{
		Free(); //在释放之前先要得到新地图的名字

		
		string youPath = getMapName(MapNumber); // g_pathMap + toString("%d.map", MapNumber);
		m_pMap->Load((char*)youPath.c_str(), MapNumber);
		m_pBmp->Load((char*)youPath.c_str()/*(char*)path1.c_str()*/);
		g_pMainState->m_FindPt.setDataByMap(this);

	}

	m_pMap->SetCenter((float)x * 20, (float)m_pMap->m_Height - y * 20);
	for (int i = 0; i < 5; i++)
	{
		if (g_pMainState->m_FightWorkList[i].isExist)
		{
			g_pMainState->m_FightWorkList[i].m_pObj->SetPos(x * 20, m_pMap->m_Height - y * 20);
			g_pMainState->m_FightWorkList[i].m_pObj->Stand();
			g_pMainState->m_FightWorkList[i].m_pObj->MoveDialog();
		}
	}
	m_pMap->m_xCenterNum = m_pMap->GetXCenter() / 320;
	m_pMap->m_yCenterNum = m_pMap->GetYCenter() / 240;
	m_pMap->m_xCenterOffset = m_pMap->GetXCenter() % 320;
	m_pMap->m_yCenterOffset = m_pMap->GetYCenter() % 240;
	m_pMap->MoveMap();
	if (prename != m_MapName)
	{
#ifdef ctt_txt2
		g_pMainState->m_MusicName = m.music;
#else
		file >> g_pMainState->m_MusicName;
#endif
		if (prename != m_MapName)
		{
// 			if (m_MapName == "建邺城")
// 			{
// 				_cwfileWav.LoadWav(1761009057);
// 			}
// 			else
			{
				g_pMainState->m_Mp3.Load(g_pMainState->m_MusicName);
			}
		}
		//小地图
		ulong smallmapid;
#ifdef ctt_txt2
		smallmapid = m.uid;
#else
		file >> smallmapid;
#endif
		if (smallmapid)
		{
			if (prename != m_MapName)
			{
				m_SmallMap.LoadMap(smallmapid);//小地图ID
				float w11 = (float)m_pMap->m_Width;
				float w22 = (float)(m_SmallMap.m_Picture.m_Width - 36);
				m_bili = w11 / w22;
				//调整图片位置
				m_SmallMap.m_Picture.m_x = g_half320 - m_SmallMap.m_Picture.m_Width / 2;
				m_SmallMap.m_Picture.m_y = g_half240 - m_SmallMap.m_Picture.m_Height / 2;
			}
		}
		else m_bili = 0;
		int numofnpc;
#ifdef ctt_txt2
		numofnpc = m.npcs.size();
#else
		file >> numofnpc;    //读取NPC数
#endif

//#define ctt_txt
		string log, log2;
#ifdef ctt_txt
		log = "{%d,0x%08X,\"%s\", \"%s\",";
		if (numofnpc == 0)
		{
			log += "{},";
		}
		ccc_log(log.c_str(), MapNumber, smallmapid, Name, g_pMainState->m_MusicName.c_str());
#endif
		string name1;
		int x, y;
		string script;
		int direction;
		int modid;
		m_numberOfNpc = 0;
		sChangeColorData2 ranse;
		cJinJieNum jinjie;

		_isAddNormalNpc = true;
		g_pMainState->m_InterfaceSmallMap.clear();
		for (int i = 0; i < numofnpc; i++)
		{
#ifdef ctt_txt2
			name1 = m.npcs[i].name;
			modid = m.npcs[i].id;
			x = m.npcs[i].x;
			y = m.npcs[i].y;
			script = m.npcs[i].script;
#else
			//读取名字
			file >> name1;

			file >> modid;
			//设置NPC位置
			file >> x;
			file >> y;

			// 			if (name1 == "帮派竞赛主持人")
			// 			{
			// 				name1 = "擂台主持人";
			// 				x = 415;
			// 				y = 107;
			// 			}

			//读取脚本
			file >> script;
#endif
			if (script == "单")
			{
#ifdef ctt_txt2
				m_pNpc[m_numberOfNpc]->m_ScriptOneType = m.npcs[i].oneType;
				m_pNpc[m_numberOfNpc]->m_ScriptOneId = m.npcs[i].oneId;
#else
				file >> m_pNpc[m_numberOfNpc]->m_ScriptOneType;
				file >> m_pNpc[m_numberOfNpc]->m_ScriptOneId;
#endif
				if (m_pNpc[m_numberOfNpc]->m_ScriptOneType == 1013)//宝箱
				{
					int baoxiangid;
					int baoxiangindex;
					g_pMainState->m_ZhiXian.GetBaoXiangID(m_pNpc[m_numberOfNpc]->m_ScriptOneId, baoxiangid, baoxiangindex);
					if (CheckINT(baoxiangid, baoxiangindex))
					{
						string dustbin;
#ifdef ctt_txt2
#else
						getline(file, dustbin);
#endif
						continue;
					}
				}
			}
			else if (script == "兑换神兽")
			{
				m_pNpc[m_numberOfNpc]->m_ScriptOneType = m.npcs[i].oneType;
				m_pNpc[m_numberOfNpc]->m_ScriptOneId = m.npcs[i].oneId;
			}
#ifdef ctt_txt2
			direction = m.npcs[i].direction;
#else
			file >> direction;
#endif
			int weapontype = -1;
			int	weaponid = -1;
			bool is1135 = false;
			if ((m_MapName == "长安城" || m_MapName == "金銮殿") && modid == 1135)
			{
				modid = 2001 + rand() % (g_pMainState->m_pCharacterDataList.size() - 1);
				is1135 = true;
			}
			if (modid >= 2000 || modid < 1000)
			{
				if (modid < 1000)
				{
#ifdef ctt_txt2
					jinjie.m_index = m.npcs[i].jinjie;

					sPetData* pPet = g_pMainState->m_PetDataManager.GetPetData(modid);
					vector<int>& lis = pPet->m_ComponentTable[jinjie.m_index];
					for (int k = 0; k < 4; k++)
					{
						if (k < lis.size())
						{
							ranse.m_ranse[k].partnum = m.npcs[i].ranse[k].size();
							ulong color = g_pMainState->m_PetDataManager.GetPetData(modid)->m_ModelActs[jinjie.m_index].m_ColorID;
							if (color == 0)
							{
								color = 0x1657;
							}
							g_pMainState->m_ColorManage.Set(color);
							for (int i = 0; i < ranse.m_ranse[k].partnum; i++)
							{
								g_pMainState->m_ColorManage.GetColorMatrix(i, ranse.m_ranse[k].m_colorchange[i], ranse.m_ranse[k].m_colormatrix[i]);
							}
						}
					}

#else
					file >> jinjie.m_index;
					ranse.Read(modid, file, jinjie.m_index);
#endif
					AddNpc(name1, modid, x, y, direction, 0, script, false, false, -1, -1, &ranse, jinjie.m_index);
				}
				else
				{
#ifdef ctt_txt2
					weapontype = m.npcs[i].wType;
					weaponid = m.npcs[i].wId;
					if (is1135 && weapontype == -1 && weaponid == -1)
					{
						int typelist[2];
						GetWeaponType(modid - 2000, typelist[0], typelist[1]);
						weapontype = typelist[rand() % 2];
						weaponid = g_pMainState->m_ItemManage.m_ItemList[weapontype].size();
						weaponid = (weaponid / 2) + rand() % (weaponid / 2);
					}

					for (int k = 0; k < 4; k++)
					{
						ranse.m_ranse[k].partnum = m.npcs[i].ranse[k].size();
						ulong color = color = g_pMainState->m_pCharacterDataList[modid - 2000].m_ColorID;
						if (color == 0)
						{
							color = 0x1657;
						}
						g_pMainState->m_ColorManage.Set(color);
						for (int i = 0; i < ranse.m_ranse[k].partnum; i++)
						{
							g_pMainState->m_ColorManage.GetColorMatrix(i, ranse.m_ranse[k].m_colorchange[i], ranse.m_ranse[k].m_colormatrix[i]);
						}
				}
#else
					file >> weapontype;
					file >> weaponid;
					ranse.Read(modid, file, jinjie.m_index);
#endif
					AddNpc(name1, modid, x, y, direction, 0, script, false, false, weapontype, weaponid, &ranse);
				}
			}
			else
			{

				AddNpc(name1, modid, x, y, direction, 0, script, false, false);
			}

#ifdef ctt_txt
			const auto& npc = m_pNpc[m_numberOfNpc - 1];
			log2 = "{%d,%d, %d, %d, \"%s\", \"%s\", %d, %d,%d,%d,%d,";
			log = log2;
			if (i == 0)
			{
				log = "{" + log2;
			}
			ccc_log(log.c_str(),
				modid, x, y, direction, name1.c_str(), script.c_str(), 
				npc->m_ScriptOneType, npc->m_ScriptOneId, 
				jinjie.m_index, weapontype, weaponid);
			log = "{";
			for (int k = 0; k < 4; ++k)
			{

				log2 = "{";
				for (int j = 0; j < ranse.m_ranse[k].partnum; ++j)
				{
					log += toString("%d,", ranse.m_ranse[0].m_colorchange[k]);
				}
				if (log2.size() > 1)
				{
					log2.pop_back();
				}
				log2 += "},";
				log += log2;
			}
			log.pop_back();
			if (i == numofnpc - 1)
			{
				log += "}}},";
			}
			else
			{
				log += "}},";
			}
			ccc_log("%s", log.c_str());
#endif
		}
		if (m_MapName == "英雄大会")
		{
			ccm::get()->PKNpc(1);
		}
		else if (m_MapName == "帮派竞赛")
		{
			ccm::get()->PKNpc(0);
		}
		else
		{
			g_pMainState->_taskFengYao.Process(0);
			const auto& mps = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai;
			for (int im = 0; im < c_MenPaiNumber; ++im)
			{
				if (m_MapName == mps[im].m_XunLuoMapName)
				{
					static vector<int> s_xys = 
					{
						97, 36,
						50, 31,
						20, 120, // NE
						100, 120, // FC
						108, 21, // ST
						81, 65, // MW
						174, 118, // PS
						39, 58, // DF
						84, 44, // LG
						43, 28, // WZ
						25, 46, // PT
						160, 53, // TG
						57, 107, // LB
						62, 45, // WD
						54, 71 // SM
					};

					int typelist[2];
					modid = g_pMainState->getModelFromMp(im);
					GetWeaponType(modid, typelist[0], typelist[1]);
					int weapontype = typelist[rand() % 2];
					int weaponid = g_pMainState->m_ItemManage.m_ItemList[weapontype].size();
					weaponid = (weaponid / 2) + rand() % (weaponid / 2);

					AddNpc("首席弟子", 2000 + modid, s_xys[im * 2], s_xys[im * 2 + 1], 5, 0, "", false, false, weapontype, weaponid, nullptr);
					m_pNpc[m_numberOfNpc - 1]->m_bHaveScript = false;

					break;
				}
			}
		}


		_isAddNormalNpc = false;
// 		else if (m_MapName == "我的庭院")
// 		{
// 			for (int iNpc = 136; iNpc <= 142; ++iNpc)
// 			{
// 				const auto& n = g_pMainState->m_pNpcList[iNpc];
// 				for (int kkk = 0; kkk < 5; ++kkk)
// 				{
// 					AutoGetPos(x, y, m_MapName);
// 					AddNpc(n.m_name, iNpc + 1000, x, y, rand() % 4);
// 				}
// 			}
// 		}
		//读取建筑数
#ifdef ctt_txt2
		m_numofJianZhu = m.jianzhus.size();
#else
		file >> m_numofJianZhu;
#endif
#ifdef ctt_txt
		log = "{";
#endif
		for (int i = 0; i < m_numofJianZhu; i++)
		{
			int xpos, ypos;
#ifdef ctt_txt2
			m_JianZhuID[i] = m.jianzhus[i].uid;
			xpos = m.jianzhus[i].x;
			ypos = m.jianzhus[i].y;
#else
			file >> m_JianZhuID[i];
			file >> xpos;
			file >> ypos;
#endif
#ifdef ctt_txt
			log2 += toString("{0x%08X, %d, %d, ",m_JianZhuID[i], xpos, ypos);
#endif
			xpos *= 20;
			ypos = m_pMap->m_Height - ypos * 20;


			m_pJianZhu[i]->SetXY(xpos, ypos);
#ifdef ctt_txt2
			m_pJianZhu[i]->m_ShowOnce = m.jianzhus[i].showOnce;
			m_pJianZhu[i]->m_PosType = m.jianzhus[i].posType;
#else
			file >> m_pJianZhu[i]->m_ShowOnce;
			file >> m_pJianZhu[i]->m_PosType;
#endif
#ifdef ctt_txt
			log2 += toString("%d, %d},",m_pJianZhu[i]->m_ShowOnce, m_pJianZhu[i]->m_PosType);
#endif
		}


#ifdef ctt_txt
		if (log.size() > 1)
		{
			log.pop_back();
		}
		log += "},";
		ccc_log("%s", log.c_str());
#endif
		//读取传送点
#ifdef ctt_txt2
		m_numberOfTransmit = m.transmits.size();
#else
		file >> m_numberOfTransmit;
#endif
		m_pTransmit = new sTransmit[m_numberOfTransmit];

#ifdef ctt_txt
		log = "{";
#endif
		for (int i = 0; i < m_numberOfTransmit; i++)
		{
#ifdef ctt_txt2
			m_pTransmit[i].m_x = m.transmits[i].x;
			m_pTransmit[i].m_y = m.transmits[i].y;
			m_pTransmit[i].name = m.transmits[i].name;
			m_pTransmit[i].m_xTarget = m.transmits[i].tx;
			m_pTransmit[i].m_yTarget = m.transmits[i].ty;
			m_pTransmit[i].m_range = m.transmits[i].range;

#else
			file >> m_pTransmit[i].m_x;
			file >> m_pTransmit[i].m_y;
			file >> m_pTransmit[i].name;
			file >> m_pTransmit[i].m_xTarget;
			file >> m_pTransmit[i].m_yTarget;
			file >> m_pTransmit[i].m_range;
#endif
#ifdef ctt_txt
			log += toString("{%d, %d, \"%s\", %d, %d, %d},", m_pTransmit[i].m_x, m_pTransmit[i].m_y,
				m_pTransmit[i].name.c_str(), m_pTransmit[i].m_xTarget, m_pTransmit[i].m_yTarget, m_pTransmit[i].m_range);
#endif
// 			if (m_pTransmit[i].m_range > 100)
// 			{
// 				ERRBOX;
// 				asert(false, "传送范围过大(%d)", m_pTransmit[i].m_range);
// 				return false;
// 			}

			if (m_bili > 0)
			{
				g_pMainState->m_InterfaceSmallMap.addNpc(m_pTransmit[i].name, m_pTransmit[i].m_x * 20 / m_bili,
					(m_pMap->m_Height - m_pTransmit[i].m_y * 20) / m_bili, RGB(0, 0xFF, 0));
			}

			m_pTransmit[i].m_x *= 20;
			m_pTransmit[i].m_y *= 20;
			m_pTransmit[i].m_range *= 20;
			m_pTransmit[i].m_y = m_pMap->m_Height - m_pTransmit[i].m_y;


			if (0)
			{
				m_JianZhuID[m_numofJianZhu] = 0x7F4CBC8C;
				m_pJianZhu[m_numofJianZhu]->SetXY(m_pTransmit[i].m_x, m_pTransmit[i].m_y);
				m_pJianZhu[m_numofJianZhu]->m_ShowOnce = false;
				m_pJianZhu[m_numofJianZhu]->m_PosType = 0;
				m_numofJianZhu += 1;
			}
			else
			{
				m_pTransmit[i].m_range = 0;

				cObj* target = m_pNpc[m_numberOfNpc];
				m_numberOfNpc += 1;
				g_pMainState->FindData(target, 1145);
				target->SetXY(m_pTransmit[i].m_x, m_pTransmit[i].m_y);
				target->SetTrueName("");
//				target->m_Shadow.m_NeedShow = false;

				target->setNextTargetOnAstart(m_pTransmit[i].m_x, m_pTransmit[i].m_y);
				target->m_AstartPathIndex = -2;

				target->InitScript("transmit" + m_pTransmit[i].name);
				
				target->m_Script.m_DialogueStyle = m_pTransmit[i].m_yTarget * 0xFFFF + m_pTransmit[i].m_xTarget;
				if (1)
				{
					if (abs(target->GetX() - g_pMainState->m_Map.m_pMap->m_xCenter) < g_half320)
						if (abs(target->GetY() - g_pMainState->m_Map.m_pMap->m_yCenter) < g_half240)
							g_pMainState->FindObj();
				}
			}

		}

#ifdef ctt_txt
		if (log.size() > 1)
		{
			log.pop_back();
		}
		log += "},";
		ccc_log("%s", log.c_str());
#endif
		//场景类型
#ifdef ctt_txt2
		m_MapType = m.mapType;
#else
		file >> m_MapType; //场景类型
#endif
		int bingrae = 0;
		switch (m_MapType)
		{
		case 1:
		case 2://明雷场景
			if (1)
			{
#ifdef ctt_txt2
				m_NumOfEmemyType = m.enemyTypes.size();
				for (int i = 0; i < m_NumOfEmemyType; i++)
				{
					m_EnemyList[i] = m.enemyTypes[i];
				}
				m_EnemyLv = m.enemyLv;
				m_Weaponlv = m.weaponLv;
				m_WeaponRate = m.weaponRate;
#else
				file >> m_NumOfEmemyType;
				for (int i = 0; i < m_NumOfEmemyType; i++)
				{
					file >> m_EnemyList[i];
				}
				file >> m_EnemyLv;
				file >> m_Weaponlv;
				file >> m_WeaponRate;
#endif
				switch (m_MapType)
				{
				case 1:
					if (m_EnemyLv + 5 < g_pCharacter->m_PcData.m_Lv)
						g_pMainState->m_InterfaceDoor.SetTrigger(&g_pMainState->m_TaskNormal, 1, 300); //遇怪开关
					else
						g_pMainState->m_InterfaceDoor.SetTrigger(&g_pMainState->m_TaskNormal, 1, 200); //遇怪开关
					break;
				case 2://
					if (1)
					{
						g_pMainState->m_InterfaceDoor.SetTrigger(&g_pMainState->m_TaskNormal, 3); //遇怪开关
#ifdef ctt_txt2
						bingrae = m.bingrae;
#else
						file >> bingrae;//怪物的数量
#endif
						for (int i = 0; i < bingrae; i++)
						{
							sPetData* petdata = g_pMainState->m_PetDataManager.GetPetData(m_EnemyList[rand() % m_NumOfEmemyType]);
							int xpos, ypos;
							g_pMainState->m_Map.AutoGetPos(xpos, ypos, m_MapName);
							AddNpc(petdata->m_Name, petdata->m_ID, xpos, ypos, Direction8To4(rand() % 10), 0, "", 3, false);
						}
					}
					break;
				}
			}
			break;
		default:
			g_pMainState->m_InterfaceDoor.SetTrigger(0);
			break;

		}
#ifdef ctt_txt
		log = toString("%d, %d, %d,%d,%d, {", m_MapType, m_EnemyLv, m_Weaponlv, m_WeaponRate, bingrae);
		for (int i = 0; i < m_NumOfEmemyType; i++)
		{
			log += toString("%d,", m_EnemyList[i]);
		}
		if (m_NumOfEmemyType > 0)
		{
			log.pop_back();
		}
		log += "}},";
		ccc_log("%s", log.c_str());
#endif
		g_pMainState->m_TriggerObjMap.Process();
	}
#ifdef ctt_txt2
#else
	file.close();
#endif

	m_MapNumber = MapNumber;

	g_pMainState->m_Canvas.SetRedrawAll();
	g_pMainState->m_InterfaceDoor.SetName(m_MapName);

	g_pMainState->m_InterfaceDoor.UpdatePos(g_pHeroObj);

	m_pMap->CountMaskList();


	g_pMainState->FindObj();
	return true;
}

void cMyMap::LoadMap(ifstream& File)
{
	int num;
	File >> num;
	m_LockList.resize(num);
	for (int i = 0; i < num; i++)
		File >> m_LockList[i];
	File >> num;
	m_RangeTriggerList.resize(num);
	for (int i = 0; i < m_RangeTriggerList.size(); i++)
		m_RangeTriggerList[i].Load(File);
}

void cMyMap::Save(ofstream& File)
{
	File << "\n" << m_LockList.size() << " ";
	for (int i = 0; i < m_LockList.size(); i++)
		File << m_LockList[i] << " ";
	File << m_RangeTriggerList.size() << " ";
	for (int i = 0; i < m_RangeTriggerList.size(); i++)
		m_RangeTriggerList[i].Save(File);
}

cMyMap::cMyMap()
{
	m_pMap = new cMap();
	m_pBmp = new cBmp();
	m_pTransmit = 0;
}



cMyMap::~cMyMap()
{
	Free();
	SAFE_DELETE(m_pBmp);
	SAFE_DELETE(m_pMap);
	if (m_pNpc.size())
	{
		for (int i = 0; i < MAX_NPC_NUM; i++)
		{
			SAFE_DELETE(m_pNpc[i]);
			SAFE_DELETE(m_pJianZhu[i]);
		}
	}
	_cwfileWav.Free();
}

bool cMyMap::CheckAlong(int xPos, int yPos, int xTarget, int yTarget)
{
	float xPos2 = (float)xPos;
	float yPos2 = (float)yPos;
	float dus1 = (float)(yTarget - yPos);
	float dus2 = (float)(xTarget - xPos);
	float angel = atan2(dus1, dus2);
	float yMove = 5 * sin(angel);
	float xMove = 5 * cos(angel);
	while (true)
	{
		if (abs(xPos2 - xTarget) < 5 && abs(yPos2 - yTarget) < 5)return true;
		xPos2 += xMove;
		yPos2 += yMove;
		int dus3, dus4;
		dus3 = (int)xPos2;
		dus4 = (int)yPos2;
		if (m_pBmp->isFold(dus3, dus4))return false;
	}
	return false;
}

bool cMyMap::Free()
{
	m_pMap->Free();
	SAFE_DELETE_ARRAY(m_pTransmit);
	for (int i = 0; i < m_numberOfNpc; i++)
	{
		m_pNpc[i]->Free();
		m_pJianZhu[i]->Free();
	}
	m_numberOfNpc = 0;
	return true;
}

bool cMyMap::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_pNpc.resize(MAX_NPC_NUM);
	m_pJianZhu.resize(MAX_NPC_NUM);
	m_JianZhuID.resize(MAX_NPC_NUM);

	for (int i = 0; i < MAX_NPC_NUM; i++)
	{
		m_pNpc[i] = new cObj;
		m_pNpc[i]->Init();
		m_pNpc[i]->m_bCheckWall = true;
		m_pNpc[i]->m_TrueName.m_hFont = g_pMainState->m_hFont[0];

		m_pJianZhu[i] = new cWasFile;
	}



	return true;
}

void cMyMap::AddNpc(string name, int id, int x, int y, int direction, cTaskFather* p /*= 0*/, string path,
	int stage, bool NeedFind, int weapontype, int weaponid, sChangeColorData2* ranse, int positionID)
{
	//设置NPC位置
	x *= 20;
	y = m_pMap->m_Height - y * 20;

	cObj* target = m_pNpc[m_numberOfNpc];
	m_numberOfNpc += 1;
	target->InitScript(path);
	//读取名字
	target->m_TrueName.SetColor(RGB(224, 212, 40)); //NPC名字的颜色
	target->m_TrueName.SetString(name);   //名字
	//读取NPC模型
	g_pMainState->FindData(target, id);

	target->SetXY(x, y);
	target->setNextTargetOnAstart(x, y);
	target->MoveName();
	target->MoveShadow();
	target->m_AstartPathIndex = -2;

	target->SetDirection(direction);
	target->m_TaskTrigger.m_pTask = p;
	target->m_TaskTrigger.m_Stage = stage;


	if (weapontype > -1)
	{
		cCharacter* pc = (cCharacter*)target->m_pIndex;
		pc->m_PcData.m_Equips[2].Set(weapontype, weaponid);
		pc->m_PcData.m_Equips[2].m_Num = 1;
	}

	if (id >= 2000 || id < 1000)
	{
		if (ranse)
		{
			if (ranse->m_ranse[0].partnum)
			{
				cPropertyData* pc;
				target->GetPropertyData(pc);
				pc->m_RanSe = *ranse;
				target->Set(POS_STAND);
			}
		}

		cPropertyData* pPet;
		target->GetPropertyData(pPet);
		pPet->m_JinJieNum.m_index = positionID;
		pPet->m_JinJieNum.m_JinJieNum = positionID;
	}

	if (NeedFind)
	{
		if (abs(target->GetX() - g_pMainState->m_Map.m_pMap->m_xCenter) > g_half320)return;
		if (abs(target->GetY() - g_pMainState->m_Map.m_pMap->m_yCenter) > g_half240)return;
		g_pMainState->FindObj();
	}

	if (m_bili > 0 && name != "远古妖王" && (m_MapName != "长安城" || (id >= 1000 && id < 2000)))
	{
		g_pMainState->m_InterfaceSmallMap.addNpc(name, x / m_bili, y / m_bili, RGB(0xFF, 0xFF, _isAddNormalNpc ? 0xFF : 0));
	}
}

void cMyMap::AddNpc(sNpc* npc, cTaskFather* p /*= 0*/, string scriptname /*= ""*/, int stage /*= 0*/, bool NeedFind)
{
	if (npc->m_direction < 0 || npc->m_direction>9)npc->AutoDirection4();
	AddNpc(npc->m_name, npc->m_modeid, npc->m_x, npc->m_y, npc->m_direction,
		p, scriptname, stage, NeedFind, npc->weapontype, npc->weaponid, &npc->m_Ranse, npc->m_JinJieID.m_index);
}

void cMyMap::AddNpc(sTaskMapObj* data, bool needfind)
{
	AddNpc(&data->m_Npc, data->m_pTask, "无", data->m_Stage, needfind);
}

void cMyMap::RemoveNpc(int xPos, int yPos, string name, bool NeedFind)
{
	for (int i = 0; i < m_numberOfNpc; i++)
	{
		if (xPos != m_pNpc[i]->GetX())continue;
		if (yPos != m_pNpc[i]->GetY())continue;
		if (name.size()>1)
		{
			if (0 == name.compare(m_pNpc[i]->m_TrueName.GetString()))
			{
				RemoveNpc(i, NeedFind);
				return;
			}
		}
		else
		{
			RemoveNpc(i, NeedFind);
			return;
		}
	}
}

void cMyMap::RemoveNpc(string name, bool NeedFind)
{
	for (int i = m_numberOfNpc - 1; i > -1; i--)
	{
		if (0 == name.compare(m_pNpc[i]->m_TrueName.GetString()))
		{
			RemoveNpc(i, NeedFind);
			return;
		}
	}
}
void cMyMap::ShadowNpc(string name, bool NeedShow, bool NeedFind)
{
	for (int i = m_numberOfNpc - 1; i > -1; i--)
	{
		if (0 == name.compare(m_pNpc[i]->m_TrueName.GetString()))
		{
			m_pNpc[i]->SetShow(NeedShow);
		}
	}
	if (NeedFind)
		g_pMainState->FindObj();
}
void cMyMap::RemoveNpc(int id, bool NeedFind)
{
	m_pNpc[id]->Reset();
	swap(m_pNpc[id], m_pNpc[m_numberOfNpc - 1]);
	m_numberOfNpc -= 1;
	if (NeedFind)
		g_pMainState->FindObj();
}

void cMyMap::RemoveNpc(cObj* pObj, bool Needfind)
{
	for (int i = 0; i < m_numberOfNpc; i++)
	{
		if (m_pNpc[i] == pObj)
		{
			RemoveNpc(i, Needfind);
			return;
		}
	}
}




void cMyMap::AutoGetPos(int& xout, int& yout, string mapname)
{
	if (mapname.empty())
	{
		mapname = m_MapName;
	}
	//计算NPC的位置
	if (m_BmpTest.oldmap != mapname)
	{
// 		ostringstream oss;
// 		oss.str("");
// 		oss << g_pathSceneTxt << mapname << ".txt";
// 		string txtpath = oss.str();
// 		ifstream   file;
// 		file.open(txtpath.c_str());
// 		if (!file)ERRBOX;
// 		int MapNumber;
// 		file >> MapNumber;    //读取地图编号
// 		file.close();

		string youPath = getMapName(ctt::getMap(mapname)->id);  // g_pathMap + toString("%d.map", /*MapNumber*/ctt::getMap(mapname)->id);
		// 		ifstream file2(youPath);
		// 		Q_ASSERT((bool)file2, "%s", youPath.c_str());
		// 		file2.close();
		m_BmpTest.Load((char*)youPath.c_str());
		m_BmpTest.oldmap = mapname;
	}

	int width = m_BmpTest.GetWidth() / 20;
	int height = m_BmpTest.GetHeight() / 20;
	int w = g_half320 / 20;
	int h = g_half240 / 20;
	do 
	{
		xout = w + rand() % (width - w * 2 - 1);
		yout = h + rand() % (height - h * 2 - 1);

	} while (m_BmpTest.isFold(xout * 20, yout * 20));
// 	xout = rand() % width;
// 	yout = rand() % height;
// 	while (m_BmpTest.isFold(xout * 20, yout * 20))
// 	{
// 		xout = rand() % width;
// 		yout = rand() % height;
// 	}
 	yout = height - yout;
// 	if (xout < 15)xout = 15;
// 	if (yout > height - 20)
// 	{
// 		yout = height - 20;
// 	}
}

void cMyMap::AddNpcSmall(string name, int id, int x, int y, int direction, cTaskFather* p /*= 0*/, string scriptname /*= ""*/, int stage /*= 0*/, bool NeedFind)
{
	x = x * 20;
	y = m_pMap->m_Height - y * 20;
	AddNpc(name, id, x, y, direction, p, scriptname, stage, NeedFind);
}

void cMyMap::AddJiaJu(sJiaJu* jiaju)
{
	int direction = jiaju->m_Direction;
	sJiaJuData& data = g_pMainState->m_ItemManage.m_JiaJuData[jiaju->m_JiaJu.GetType() - 35][jiaju->m_JiaJu.GetID()];

	int pos;
	switch (jiaju->m_JiaJu.m_pItemData->GetLv())
	{
	case 1:
	case 2:
		pos = 0;
		break;
	default:
		pos = 1;
		break;
	}
	int x = jiaju->m_xPos;
	int y = jiaju->m_yPos;

	switch (jiaju->m_JiaJu.m_pItemData->GetLv())
	{
	case 4:
		if (1)
		{
			for (int i = 0; i < 3; i++)
			{
				ulong id = data.m_data[direction * 3 + i];
				m_JianZhuID[m_numofJianZhu] = id;
				m_pJianZhu[m_numofJianZhu]->SetXY(x, y);
				m_pJianZhu[m_numofJianZhu]->m_PosType = pos;
				m_numofJianZhu += 1;
			}
		}
		break;
	case 5:
		if (jiaju->m_Direction)
		{
			for (int i = 0; i < 5; i++)
			{
				ulong id = data.m_data[6 + i];
				m_JianZhuID[m_numofJianZhu] = id;
				m_pJianZhu[m_numofJianZhu]->SetXY(x, y);
				m_pJianZhu[m_numofJianZhu]->m_PosType = pos;
				m_numofJianZhu += 1;
			}
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				ulong id = data.m_data[i];
				m_JianZhuID[m_numofJianZhu] = id;
				m_pJianZhu[m_numofJianZhu]->SetXY(x, y);
				m_pJianZhu[m_numofJianZhu]->m_PosType = pos;
				m_numofJianZhu += 1;
			}
		}
		break;
	default:
		if (1)
		{
			ulong id = data.m_data[direction];
			m_JianZhuID[m_numofJianZhu] = id;
			m_pJianZhu[m_numofJianZhu]->SetXY(x, y);
			m_pJianZhu[m_numofJianZhu]->m_PosType = pos;
			m_numofJianZhu += 1;
		}
		break;
	}
}

void cMyMap::RemoveJiaJu(sJiaJu* jiaju)
{
	//sJiaJuData& data = g_pMainState->m_ItemManage.m_JiaJuData[jiaju->m_JiaJu.GetType() - 35][jiaju->m_JiaJu.GetID()];


	for (int i = 0; i < m_pJianZhu.size(); i++)
	{
		int x = m_pJianZhu[i]->GetX();
		int y = m_pJianZhu[i]->GetY();
		if (x == jiaju->m_xPos)
			if (y == jiaju->m_yPos)
			{
			swap(m_pJianZhu[i], m_pJianZhu[m_numofJianZhu - 1]);
			swap(m_JianZhuID[i], m_JianZhuID[m_numofJianZhu - 1]);
			m_numofJianZhu -= 1;
			}
	}
}

void cMyMap::CheckChuanSong()
{
	int xC = g_pHeroObj->GetX();
	int yC = g_pHeroObj->GetY();
	//检测角色是否到传送点
	for (int i = 0; i < m_numberOfTransmit; i++)
	{
		if (m_pTransmit[i].Check(xC, yC))
		{
			LoadMap(m_pTransmit[i].m_xTarget, m_pTransmit[i].m_yTarget, (char*)m_pTransmit[i].name.c_str(), false);
			return;
		}
	}
	for (int i = 0; i < m_RangeTriggerList.size(); i++)
	{
		if (m_RangeTriggerList[i].Check(xC, yC))
		{
			cTaskFather* p = m_RangeTriggerList[i].m_p;
			int ret = m_RangeTriggerList[i].m_ret;
			m_RangeTriggerList.erase(m_RangeTriggerList.begin() + i);
			p->Process(ret);
		}
	}
}

void cMyMap::RemoveAllNpc()
{
	for (int i = 0; i < m_numberOfNpc; i++)
	{
		m_pNpc[i]->Free();
	}
	m_numberOfNpc = 0;
}

void cMyMap::SetLock(string mapname /*= ""*/)
{
	if (mapname == "")
	{
		m_LockList.clear();
	}
	else
	{
		m_LockList.push_back(mapname);
	}
}

void cMyMap::SetLock(int b)
{
	g_GlobalValues[10] = b;
}

void cMyMap::AddTriggerRange(sTriggerRange& data)
{
	m_RangeTriggerList.push_back(data);
}
