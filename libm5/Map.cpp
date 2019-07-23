#include "Global.h"

using namespace std;
BOOL cBmp5::Load(CHAR* Name)
{
	std::ifstream ifile;
	int mapid = cMap::toMapid(Name, ifile);
	if (mapid == 0)
	{
		ifile.close();
		return FALSE;
	}
	ifile.close();
	return Load(mapid);
}

bool cBmp5::Load(int mapid)
{
	if (mapid == oldid)
	{
		return true;
	}
	Free();
	_cache = cMapReader::getInstance()->getCache(cGame::getInstance()->getMap(), mapid);
	_cache.pMap->loadObstacles();
	m_Width = _cache.pMap->info.mw;
	m_Height = _cache.pMap->info.mh;
	_ow = _cache.pMap->info.bw * cMapReader::c16;
	return true;
}

BOOL cBmp5::isOk20(int x20, int y20)
{
//	y20 = _cache.pMap->info.bh * cMapReader::c12 - 1 - y20;
	y20 = _cache.pMap->info.mh / cMapReader::c20 - 1 - y20;
	return !_cache.pMap->isObstacle(x20, y20);
}


BOOL cBmp5::isOk(int x, int y)
{
	return !_cache.pMap->isObstacle(x / cMapReader::c20, y / cMapReader::c20);
}

cBmp5::~cBmp5()
{
	Free();
}

BOOL cBmp5::Free()
{
	cMapReader::getInstance()->freeCache(_cache);
	return TRUE;
}



int cMap::toMapid(const std::string& mapname, std::ifstream& ifile)
{
	if (ifile.is_open())
	{
		ifile.close();
	}
	ifile.open(g_ScenePath + mapname + ".txt");
	if (!ifile.is_open())
	{
		return 0;
	}
	int value;
	ifile >> value;
	return value;
}


const char* cMap::toMap(const std::string& filename)
{
	std::ifstream ifile(filename, std::ios::binary | std::ios::in);
	if (!ifile.is_open())
	{
		return false;
	}
	ifile.seekg(0, std::ios::end);
	int size = ifile.tellg();
	auto ptr = new char[size];
	ifile.seekg(std::ios::beg);
	ifile.read(ptr, size);
	ifile.close();
	return ptr;
}


//////////////////////////////////////////////////////////////////////////
cMap::cMap()
{
	m_WidthNum = 0;
	m_HeightNum = 0;
	m_Width = 0;
	m_Height = 0;
}


cMap::~cMap()
{
	Free();
}


BOOL cMap::Load(CHAR* name, int mapid)
{
	m_MapID = mapid;
	g_pMainState->m_Canvas.m_Time = 0;
//	Free();

	_cache = cMapReader::getInstance()->getCache(cGame::getInstance()->getMap(), mapid);
	cMapRender::getInstance()->onSize(g_640, g_480);
	cMapRender::getInstance()->setMap(_cache.pMap);
	_cache.pMap->loadMask();
	const auto& info = _cache.pMap->info;
	m_Width = info.mw;
	m_Height = info.mh;
	m_WidthNum = info.bw;
	m_HeightNum = info.bh;
	m_NumBlock = m_WidthNum * m_HeightNum;

	return TRUE;
}


BOOL cMap::Follow(cObj* pObj)
{
	int iSpeed = 5;
	int xHero, yHero;
	xHero = pObj->GetX();
	yHero = pObj->GetY();
	m_bMove = FALSE;

	if (m_LockMap)
	{
		if (abs(m_xLock - m_xCenter) < iSpeed && abs(m_yLock - m_yCenter) < iSpeed)
			return TRUE;
		float dust1, dust2;
		dust1 = (float)(m_yLock - m_yCenter);
		dust2 = (float)(m_xLock - m_xCenter);
		float angel = atan2(dust1, dust2);

		int yMove1 = (int)(iSpeed * sin(angel));
		int xMove1 = (int)(iSpeed * cos(angel));
		xMove(xMove1);
		yMove(yMove1);

		m_bMove = TRUE;
	}
	else if (m_ReturnMap)
	{
		if (abs(xHero - m_xCenter) < 10 && abs(yHero - m_yCenter) < 10)
		{
			m_ReturnMap = FALSE;
			return TRUE;
		}
		float dus1, dus2;
		dus1 = (float)(yHero - m_yCenter);
		dus2 = (float)(xHero - m_xCenter);
		float angel = atan2(dus1, dus2);
		int yMove1 = (int)(iSpeed * sin(angel));
		int xMove1 = (int)(iSpeed * cos(angel));
		xMove(xMove1);
		yMove(yMove1);
		m_bMove = TRUE;
	}
	else
	{
		if (GetXCenter() != pObj->GetX() || GetYCenter() != pObj->GetY())
		{
			m_bMove = TRUE;
			m_xCenter = pObj->m_xPos;
			m_yCenter = pObj->m_yPos;
			g_pMainState->m_Canvas.SetRedrawAll(FALSE);
		}
	}
	if (!m_bMove)
	{
		return TRUE;
	}
	if (m_Width > g_640)
	{
		if (m_xCenter < g_320)m_xCenter = g_320;
		float w = (float)m_Width - g_320 - 1;
		if (m_xCenter > w) m_xCenter = w;
	}
	else
	{
		m_xCenter = m_Width / 2;
	}
	if (m_Height > g_480)
	{
		if (m_yCenter < g_240)m_yCenter = g_240;
		float h = (float)m_Height - g_240 - 1;
		if (m_yCenter > h) m_yCenter = h;
	}
	else
	{
		m_yCenter = m_Height / 2;
	}


	m_xCenterOffset = GetXCenter() % 320;
	m_yCenterOffset = GetYCenter() % 240;

	_vMap.x = m_xCenter - g_320;
	_vMap.y = m_yCenter - g_240;
	// cMapRender::getInstance()->step(_vMap, true);
	//如果X Y方向上都发生了改变
	if (m_xCenterNum != (GetXCenter() / 320) || m_yCenterNum != (GetYCenter() / 240))
	{
		MoveMap();
	}
	else
	{
		if (g_pMainState->m_FangWu.GetMapName() == g_pMainState->m_Map.m_MapName && g_pMainState->m_Map.m_numofJianZhu > 0)
		{
			g_pMainState->FindObj();
		}
	}

	return TRUE;
}

BOOL cMap::SetCenter(float xHero, float yHero)
{
	m_xCenter = xHero;
	m_yCenter = yHero;
	if (xHero < g_320 * 1.0f)
		m_xCenter = g_320 * 1.0f;
	else
		if (xHero > float(m_Width - g_320 - 1))
			m_xCenter = (float)(m_Width - g_320 - 1);
	if (yHero < g_240 * 1.0f)
		m_yCenter = g_240 * 1.0f;
	else
		if (yHero > (float)(m_Height - g_240 - 1))
			m_yCenter = (float)(m_Height - g_240 - 1);

	_vMap.x = m_xCenter - g_320;
	_vMap.y = m_yCenter - g_240;
	// cMapRender::getInstance()->step(_vMap, true);
	return TRUE;
}


void cMap::xMove(int x)
{
	if (0 == x)return;
	if (x > 0)
	{
		if (x * m_AddSpeed > m_xPreSpeed)
		{
			m_xPreSpeed += 1;
			m_xCenter += m_xPreSpeed / m_AddSpeed;
		}
		else  m_xCenter += x;
	}
	else
	{
		if (x * m_AddSpeed < m_xPreSpeed)
		{
			m_xPreSpeed -= 1;
			m_xCenter += m_xPreSpeed / m_AddSpeed;
		}
		else  m_xCenter += x;
	}
}

void cMap::yMove(int y)
{
	if (y > 0)
	{
		if (y * m_AddSpeed > m_yPreSpeed)
		{
			m_yPreSpeed += 1;
			m_yCenter += m_yPreSpeed / m_AddSpeed;
		}
		else  m_yCenter += y;
	}
	else
	{
		if (y * m_AddSpeed < m_yPreSpeed)
		{
			m_yPreSpeed -= 1;
			m_yCenter += m_yPreSpeed / m_AddSpeed;
		}
		else  m_yCenter += y;
	}
}



void cMap::CountMaskList()
{
}


BOOL cMap::MoveMap()
{
	g_pMainState->FindObj();

	m_xCenterNum = GetXCenter() / 320;
	m_yCenterNum = GetYCenter() / 240;
	CountMaskList();
	return TRUE;
}



void cMap::Free()
{
	cMapRender::getInstance()->setMap(nullptr);
	cMapReader::getInstance()->freeCache(_cache);
	_cache.pMap = nullptr;
}


BOOL cMap::Show(BYTE* pPic, RECT rect)
{
	if (!_cache.isValid())
	{
		return FALSE;
	}

 	cMapRender::getInstance()->step(cocos2d::Vec2(m_xCenter, m_yCenter), true);
	auto canvas = cWindSoul::getInstance()->getCanvas(eCanvas::nor);
	cMapRender::getInstance()->draw(canvas, _vMap);

	return TRUE;
}


void cMap::showMask()
{
	if (!_cache.isValid())
	{
		return;
	}
	auto canvas = cWindSoul::getInstance()->getCanvas(eCanvas::nor);
	cMapRender::getInstance()->drawMask(canvas, _vMap);
}


//////////////////////////////////////////////////////////////////////////
BOOL cMyMap::LoadMap(long x, long y, const CHAR* Name, BOOL bFly)
{
	if (bFly)
	{
		if (g_pMainState->m_GlobalButton[10])
		{
			g_pMainState->m_Tags.Add("当前无法飞行");
			return TRUE;
		}
	}
	if (m_LockList.size())
	{
		for (int i = 0; i < m_LockList.size();i++)
			if (0 == m_LockList[i].compare(Name))return TRUE;
	}
	if (g_StateType != STATE_MAIN)return FALSE;

	g_pMainState->m_InterfaceSmallMap.OnOff(FALSE);
	g_pMainState->m_Dialog.Close();
	g_pMainState->m_TaskNormal.m_pNpc = 0;
	if (g_pMainState->m_pNowSelect)
	{
		g_pMainState->m_pNowSelect->SetShine(FALSE);
		g_pMainState->m_pNowSelect = 0;
	}
	for (int i = 1; i < MAX_OBJ_NUM; i++)
	{
		g_pMainState->m_pObj[i] = 0;
	}
	string prename = m_MapName;
	m_MapName = Name;

	ifstream file;
	int MapNumber = cMap::toMapid(m_MapName, file);

	if (MapNumber <=0 || MapNumber > 2000)
	{
		ERRBOX;
	}
	if (prename != m_MapName)
	{
		Free(); //在释放之前先要得到新地图的名字	

		m_pMap->Load((CHAR*)m_MapName.c_str(), MapNumber);
		m_pBmp->Load(MapNumber);
		g_pMainState->m_FindPt.ResetMap(m_pMap->_cache.pMap);

	}
	
	m_pMap->SetCenter((float)x * 20, (float)m_pMap->m_Height - y * 20);
	for (int i = 0; i < 5; i++)
	{
		if (g_pMainState->m_FightList[i].isLive)
		{
			g_pMainState->m_FightList[i].m_pData->SetPos(x * 20, m_pMap->m_Height - y * 20);
			g_pMainState->m_FightList[i].m_pData->Stand();
			g_pMainState->m_FightList[i].m_pData->MoveDialog();
		}
	}
	m_pMap->m_xCenterNum = m_pMap->GetXCenter() / 320;
	m_pMap->m_yCenterNum = m_pMap->GetYCenter() / 240;
	m_pMap->m_xCenterOffset = m_pMap->GetXCenter() % 320;
	m_pMap->m_yCenterOffset = m_pMap->GetYCenter() % 240;
	m_pMap->MoveMap();
	if (prename != m_MapName)
	{
		file >> g_pMainState->m_MusicName;
		if (prename != m_MapName)
			g_pMainState->m_Mp3.Load(g_pMainState->m_MusicName);
		//小地图
		DWORD smallmapid;
		file >> smallmapid;
		
		if (smallmapid)
		{
			if (prename != m_MapName)
			{
				m_SmallMap.loadSmap(smallmapid);//小地图ID
				float w11 = (float)m_pMap->m_Width;
				float w22 = (float)(m_SmallMap.m_Picture.m_Width - 36);
				m_bili = w11 / w22;
				//调整图片位置
				m_SmallMap.m_Picture.m_x = g_320 - m_SmallMap.m_Picture.m_Width / 2;
				m_SmallMap.m_Picture.m_y = g_240 - m_SmallMap.m_Picture.m_Height / 2;
			}
		}
		else m_bili = 0;
		int numofnpc;
		file >> numofnpc;    //读取NPC数
	
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
			//读取名字
			file >> name1;
			
			file >> modid;
			//设置NPC位置
			file >> x;
			file >> y;
			//读取脚本
			file >> script;
			if (script == "单")
			{
				file>> m_pNpc[m_numberOfNpc]->m_ScriptOneType;
				file >> m_pNpc[m_numberOfNpc]->m_ScriptOneId;
				if (m_pNpc[m_numberOfNpc]->m_ScriptOneType == 1013)//宝箱
				{
					int baoxiangid;
					int baoxiangindex;
					g_pMainState->m_ZhiXian.GetBaoXiangID(m_pNpc[m_numberOfNpc]->m_ScriptOneId, baoxiangid, baoxiangindex);
					if (CheckINT(baoxiangid, baoxiangindex))
					{
						string dustbin;
						getline(file, dustbin);
						continue;
					}
				}
			}
			file >> direction;
			int weapontype = -1;
			int	weaponid = -1;
			if (modid >= 2000||modid<1000)
			{
				if (modid < 1000)
				{
					file >> jinjie.m_PositionID;
					ranse.Read(modid, file, jinjie.m_PositionID);
					
					AddNpc(name1, modid, x, y, direction, 0, script, FALSE, FALSE, -1, -1, &ranse,jinjie.m_PositionID);
				}
				else
				{
					
					file >> weapontype;
					file >> weaponid;
					ranse.Read(modid, file, jinjie.m_PositionID);
					AddNpc(name1, modid, x, y, direction, 0, script, FALSE, FALSE, weapontype, weaponid, &ranse);
				}
			}
			else
			{

				AddNpc(name1, modid, x, y, direction, 0, script, FALSE, FALSE);
			}

		}
		_isAddNormalNpc = false;
#if ccc_date
		if (MapNumber == 1197 || MapNumber == 1511)
		{
			MyTest::getInstance()->PKNpc();
		}
#endif
		//读取建筑数
		file >> m_numofJianZhu;

		for (int i = 0; i < m_numofJianZhu; i++)
		{
			int xpos, ypos;
			file >> m_JianZhuID[i];
			file >> xpos;
			file >> ypos;

			xpos *= 20;
			ypos = m_pMap->m_Height - ypos * 20;


			m_pJianZhu[i]->SetXY(xpos, ypos);
			file >> m_pJianZhu[i]->m_ShowOnce;
			file >> m_pJianZhu[i]->m_PosType;

		}
		//读取传送点
		file >> m_numberOfTransmit;
	
		m_pTransmit = new sTransmit[m_numberOfTransmit];
		for (int i = 0; i < m_numberOfTransmit; i++)
		{
			file >> m_pTransmit[i].m_x;
			file >> m_pTransmit[i].m_y;
			file >> m_pTransmit[i].name;
			file >> m_pTransmit[i].m_xTarget;
			file >> m_pTransmit[i].m_yTarget;
			file >> m_pTransmit[i].m_range;
			if (m_bili > 0)
			{
				g_pMainState->m_InterfaceSmallMap.addNpc(m_pTransmit[i].name, m_pTransmit[i].m_x * 20 / m_bili, 
					(m_pMap->m_Height - m_pTransmit[i].m_y * 20) / m_bili, RGB(0, 0xFF, 0));
			}

// 			if (m_pTransmit[i].m_range>100)
// 			{
// 				ERRBOX;
// 				return FALSE;
// 			}


			m_pTransmit[i].m_x *= 20;
			m_pTransmit[i].m_y *= 20;
			m_pTransmit[i].m_range *= 20;
			m_pTransmit[i].m_y = m_pMap->m_Height - m_pTransmit[i].m_y;

			if (0)
			{
				m_JianZhuID[m_numofJianZhu] = 0x7F4CBC8C;
				m_pJianZhu[m_numofJianZhu]->SetXY(m_pTransmit[i].m_x, m_pTransmit[i].m_y);
				m_pJianZhu[m_numofJianZhu]->m_ShowOnce = FALSE;
				m_pJianZhu[m_numofJianZhu]->m_PosType = 0;
				m_numofJianZhu += 1;
			}
			else
			{
				m_pTransmit[i].m_range = 0;

				cObj* target = m_pNpc[m_numberOfNpc];
				m_numberOfNpc += 1;

				target->SetDataType(INDEXTYEP_NPC);
				cNpc* pNpc = (cNpc*)target->m_pIndex;
				static sNpcData* s_npcData = new sNpcData();
				s_npcData->m_stand = 0x7596D42B;
				pNpc->m_pNpcData = s_npcData;
			//	g_pMainState->FindData(target, 1145);
				target->SetXY(m_pTransmit[i].m_x, m_pTransmit[i].m_y);
				target->SetTrueName(m_pTransmit[i].name);
				target->m_TrueName.SetColor(RGB(0xFF, 0xFF, 0));
				target->m_TrueName.SetXCenter(m_pTransmit[i].m_x);
			//	target->m_Shadow.m_NeedShow = false;

				target->SetTarget(m_pTransmit[i].m_x, m_pTransmit[i].m_y);
				target->m_time = -2;

				target->InitScript("transmit" + m_pTransmit[i].name);
				target->MoveName();

				target->m_Script.m_DialogueStyle = m_pTransmit[i].m_yTarget * 0xFFFF + m_pTransmit[i].m_xTarget;
				if (1)
				{
					if (abs(target->GetX() - g_pMainState->m_Map.m_pMap->m_xCenter) < g_320)
						if (abs(target->GetY() - g_pMainState->m_Map.m_pMap->m_yCenter) < g_240)
							g_pMainState->FindObj();
				}
			}

		}
		//场景类型
		file >> m_MapType; //场景类型
		
		switch (m_MapType)
		{
		case 1:
		case 2://明雷场景
			if (1)
			{
				file >> m_NumOfEmemyType;
				for (int i = 0; i < m_NumOfEmemyType; i++)
				{
					file >> m_EnemyList[i];
				}
				file >> m_EnemyLv;
				file >> m_Weaponlv;
				file >> m_WeaponRate;
				switch (m_MapType)
				{
				case 1:
					if (m_EnemyLv+5<g_pCharacter->m_PCData.m_LV)
						g_pMainState->m_InterfaceDoor.SetTrigger(&g_pMainState->m_TaskNormal, 1,600); //遇怪开关
					else
						g_pMainState->m_InterfaceDoor.SetTrigger(&g_pMainState->m_TaskNormal, 1, 400); //遇怪开关
					break;
				case 2://
					if (1)
					{
						g_pMainState->m_InterfaceDoor.SetTrigger(&g_pMainState->m_TaskNormal, 3); //遇怪开关
						int num;
						file >> num;//怪物的数量
						for (int i = 0; i < num; i++)
						{
							sPetData* petdata = g_pMainState->m_PetDataManager.GetPetData(m_EnemyList[rand() % m_NumOfEmemyType]);
							int xpos, ypos;
							g_pMainState->m_Map.AutoGetPos(xpos, ypos, m_MapName);
							AddNpc(petdata->m_Name, petdata->m_ID, xpos, ypos, Direction8To4(rand() % 10), 0, "", 3, FALSE);
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
		g_pMainState->m_TriggerObjMap.Process();
	}
	file.close();

	m_MapNumber=MapNumber;
	
	g_pMainState->m_Canvas.SetRedrawAll();
	g_pMainState->m_InterfaceDoor.SetName(m_MapName);

	g_pMainState->m_InterfaceDoor.UpdatePos(g_pHeroObj);
	
	m_pMap->CountMaskList();

	
	g_pMainState->FindObj();
	return TRUE;
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
	File <<"\n"<< m_LockList.size()<<" ";
	for (int i = 0; i < m_LockList.size(); i++)
		File << m_LockList[i]<<" ";
	File << m_RangeTriggerList.size() << " ";
	for (int i = 0; i < m_RangeTriggerList.size(); i++)
		m_RangeTriggerList[i].Save(File);
}

cMyMap::cMyMap()
{
	m_pMap = new cMap();
	m_pBmp = new cBmp5();
	m_pTransmit = 0;
}



cMyMap::~cMyMap()
{
	Free();
	SAFE_DELETE(m_pBmp);
	SAFE_DELETE(m_pMap);
	if (m_pNpc.size())
	for (int i = 0; i < MAX_NPC_NUM; i++)
	{
		SAFE_DELETE(m_pNpc[i]);
		SAFE_DELETE(m_pJianZhu[i]);
	}
}

BOOL cMyMap::CheckAlong(int xPos, int yPos, int xTarget, int yTarget)
{
	float xPos2 = (float)xPos;
	float yPos2 = (float)yPos;
	float dus1 =(float)( yTarget - yPos);
	float dus2 =(float)( xTarget - xPos);
	float angel = atan2(dus1 , dus2);
	float yMove = 5 * sin(angel);
	float xMove = 5 * cos(angel);
	while (true)
	{
		if (abs(xPos2 - xTarget) < 5 && abs(yPos2 - yTarget) < 5)return TRUE;
		xPos2 += xMove;
		yPos2 += yMove;
		int dus3, dus4;
		dus3 = (int )xPos2;
		dus4 = (int)yPos2;
		if (m_pBmp->isOk/*20*/(dus3/* / 20*/,dus4/* / 20*/))return FALSE;
	}
	return FALSE;
}

BOOL cMyMap::Free()
{
	m_pMap->Free();
	SAFE_DELETE_ARRAY(m_pTransmit);
	for (int i = 0; i < m_numberOfNpc; i++)
	{
		m_pNpc[i]->Free();
		m_pJianZhu[i]->Free();
	}
	m_numberOfNpc = 0;
	return TRUE;
}

BOOL cMyMap::Init()
{
	if (m_bInit)return TRUE;
	m_bInit = TRUE;
	m_pNpc.resize(MAX_NPC_NUM);
	m_pJianZhu.resize(MAX_NPC_NUM);
	m_JianZhuID.resize(MAX_NPC_NUM);
	
	for (int i = 0; i < MAX_NPC_NUM; i++)
	{
		m_pNpc[i] = new cObj;
		m_pNpc[i]->Init();
		m_pNpc[i]->m_bCheckWall = TRUE;
		m_pNpc[i]->m_TrueName.m_hFont = g_pMainState->m_hFont[0];

		m_pJianZhu[i] = new CWFile;
	}
	


	return TRUE;
}

void cMyMap::AddNpc(string name, int id, int x, int y, int direction, cTaskFather* p /*= 0*/, string path,
	int stage, BOOL NeedFind, int weapontype, int weaponid, sChangeColorData2* ranse,int positionID)
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
	target->SetTarget(x, y);
	target->MoveName();
	target->MoveShadow();
	target->m_time = -2;
	
	target->SetDirection(direction);
	target->m_TaskTrigger.m_pTask = p;
	target->m_TaskTrigger.m_Stage = stage;
	
	
	if (weapontype >-1)
	{
		cCharacter* pc = (cCharacter*)target->m_pIndex;
		pc->m_PCData.m_Equip[2].Set(weapontype, weaponid);
		pc->m_PCData.m_Equip[2].m_Num = 1;
	}
	
	if (id >= 2000 || id<1000)
	{
		if (ranse)
		{
			if (ranse->m_ranse[0].partnum)
			{
				cPetData* pc;
				target->GetDateP(pc);
				pc->m_RanSe = *ranse;
				target->Set(POS_STAND);
			}
		}

		cPetData* pPet;
		target->GetDateP(pPet);
		pPet->m_JinJieNum.m_PositionID = positionID;
		pPet->m_JinJieNum.m_JinJieNum = positionID;
	}
	
	if (NeedFind)
	{
		if (abs(target->GetX() - g_pMainState->m_Map.m_pMap->m_xCenter) > g_320)return;
		if (abs(target->GetY() - g_pMainState->m_Map.m_pMap->m_yCenter) > g_240)return;
		g_pMainState->FindObj();
	}

	if (m_bili > 0)
	{
		g_pMainState->m_InterfaceSmallMap.addNpc(name, x / m_bili, y / m_bili, RGB(0xFF, 0xFF, _isAddNormalNpc ? 0xFF : 0));
	}
}


void cMyMap::AddNpc(sNpc* npc, cTaskFather* p /*= 0*/, string scriptname /*= ""*/, int stage /*= 0*/, BOOL NeedFind)
{
	if (npc->m_direction<0 || npc->m_direction>9)npc->AutoDirection4();
	AddNpc(npc->m_name, npc->m_modeid, npc->m_x, npc->m_y, npc->m_direction,
		p, scriptname, stage, NeedFind, npc->weapontype, npc->weaponid, &npc->m_Ranse,npc->m_JinJieID.m_PositionID);
}

void cMyMap::AddNpc(sMapObjTrigger* data, BOOL needfind )
{
	AddNpc(&data->m_Npc, data->m_pTask, "无", data->m_Stage, needfind);
}

void cMyMap::RemoveNpc(int xPos, int yPos, string name, BOOL NeedFind)
{
	for (int i = 0; i< m_numberOfNpc; i++)
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

void cMyMap::RemoveNpc(string name, BOOL NeedFind)
{
	for (int i = m_numberOfNpc - 1; i > -1; i--)
	{
		if (0 == name.compare(m_pNpc[i]->m_TrueName.GetString()))
		{
			RemoveNpc(i,NeedFind);
			return;
		}
	}
}
void cMyMap::ShadowNpc(string name, BOOL NeedShow, BOOL NeedFind)
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
void cMyMap::RemoveNpc(int id, BOOL NeedFind)
{
	m_pNpc[id]->Reset();
	swap(m_pNpc[id], m_pNpc[m_numberOfNpc - 1]);
	m_numberOfNpc -= 1;
	if (NeedFind)
	g_pMainState->FindObj();
}

void cMyMap::RemoveNpc(cObj* pObj, BOOL Needfind)
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
	//计算NPC的位置
	if (m_BmpTest.oldmap != mapname)
	{
		ostringstream oss;
		oss.str("");
		oss << g_ScenePath << mapname << ".txt";
		string txtpath = oss.str();
		ifstream   file;
		file.open(txtpath.c_str());
		if (!file)ERRBOX;
		int MapNumber;
		file >> MapNumber;    //读取地图编号
		file.close();
		oss.str("");
		oss << MapNumber;
		string  path1 = oss.str();
		oss.str("");

		m_BmpTest.Load(MapNumber/*(CHAR*)path1.c_str()*/);
	}
	int width = m_BmpTest.GetWidth() / cMapReader::c20;
	int height = m_BmpTest.GetHeight() / cMapReader::c20;
	do 
	{
		xout = (rand() % (width - cMapReader::c16 * 2)) + cMapReader::c16;
		yout = (rand() % (height - cMapReader::c12 * 2)) + cMapReader::c12;

	} while (!m_BmpTest.isOk20(xout, yout));

// 	xout = rand() % width;
// 	yout = rand() % height;
// 	while (!m_BmpTest.isOk20(xout, yout))
// 	{
// 		xout = rand() % width;
// 		yout = rand() % height;
// 	}
// 	yout = m_BmpTest.GetHeight() / 20 - yout;
// 	if (xout < 15)xout = 15;
// 	if (yout >(m_BmpTest.GetHeight() / 20) - 20)
// 	{
// 		yout = (m_BmpTest.GetHeight() / 20) - 20;
// 	}
}

void cMyMap::AddNpcSmall(string name, int id, int x, int y, int direction, cTaskFather* p /*= 0*/, string scriptname /*= ""*/, int stage /*= 0*/, BOOL NeedFind)
{
	x = x * 20;
	y = m_pMap->m_Height - y * 20;
	AddNpc(name, id, x, y, direction, p, scriptname, stage,NeedFind);
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
				DWORD id = data.m_data[direction * 3 + i];
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
				DWORD id = data.m_data[6+ i];
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
				DWORD id = data.m_data[i];
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
			DWORD id = data.m_data[direction];
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
		if (x==jiaju->m_xPos)
		if (y == jiaju->m_yPos )
		{
			swap(m_pJianZhu[i], m_pJianZhu[m_numofJianZhu-1]);
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
		if (m_pTransmit[i].Check(xC,yC))
		{
			LoadMap(m_pTransmit[i].m_xTarget, m_pTransmit[i].m_yTarget, (char*)m_pTransmit[i].name.c_str(),FALSE);
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

void cMyMap::SetLock(BOOL b)
{
	g_pMainState->m_GlobalButton[10] = b; 
}

void cMyMap::AddTriggerRange(sTriggerRange& data)
{
	m_RangeTriggerList.push_back(data);
}





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
	BOOL live;
	File >> live;
	if (!live)return;

	File >> m_range ;
	File >> m_x ;
	File >> m_y ;
	int type;
	File >>type;
	m_p= g_pMainState->FindTaskByID(type);
	File >> m_ret ;
	File >> m_name;
}

void sTriggerRange::Set(string name, int x, int y, int range, cTaskFather* p, int ret)
{
	m_name = name;
	m_range=range*20;
	m_x =x*20;
	m_y =g_pMainState->m_Map.m_pMap->m_Height - m_y * 20;
	m_p = p;
	m_ret=ret;
}

BOOL sRangeTr::Check(int x, int y)
{
	if (abs(x - m_x) < m_range&&abs(y - m_y) < m_range)
	{
		if (m_name == "")return TRUE;
		if (m_name==g_pMainState->m_Map.m_MapName)
			return TRUE;
		return FALSE;
	}
	return FALSE;
}
