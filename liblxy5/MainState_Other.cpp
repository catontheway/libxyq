#include "_global.h"



int CMainState::ReadInt(char*& point)
{
	char Line[256];
	for (int i = 0; i < 256; i++)
	{
		if (point[0] == '\r' || point[0] == '\n')
		{
			Line[i] = 0;
			point += 2;
			break;
		}
		Line[i] = point[0];
		point++;

	}

	return  atoi(Line);

}



bool CMainState::ReadName(char*& point, char*& pName)
{
	char Line[256];
	int i;
	for (i = 0; i < 256; i++)
	{
		if (point[0] == '\r' || point[0] == '\n')
		{
			Line[i] = 0;
			point += 2;
			break;
		}
		Line[i] = point[0];
		point++;

	}
	pName = new char[i + 1];
	strcpy(pName, Line);
	return true;
}



ulong CMainState::Readulong(char*& point)
{
	char Line[256];
	for (int i = 0; i < 256; i++)
	{
		if (point[0] == '\r' || point[0] == '\n')
		{
			Line[i] = 0;
			point += 2;
			break;
		}
		Line[i] = point[0];
		point++;
	}
	return strtoul(Line, 0, 16);

}



bool CMainState::LoadCharacterData(int model, string name /* = "" */)
{
	auto& fters = m_Friend._friends;
	int charactID = fters.size();
	if (charactID == 5)
	{
		return false;
	}
// 	int charactID = 0;
// 	for (; charactID < 5; ++charactID)
// 	{
// 		if (!m_FightWorkList[charactID].isExist)
// 		{
// 			break;
// 		}
// 	}
// 	if (charactID == 5)
// 	{
// 		return false;
// 	}
// 	m_FightWorkList[charactID].isExist = true;
	cObj* pObj = m_FightWorkList[charactID].m_pObj;
	cFriend::sFriend fr;
	fr.obj = pObj;
	fters.push_back(fr);
// 	cObj* pObj = fters.back();
// 	pObj->Init();
// 	pObj->m_TrueName.m_bShowOnScreen = false;

	pObj->AutoData(model, nullptr, -1, name);
	pObj->Set(POS_STAND);
	pObj->getPropertyData()->m_Name = pObj->GetName();
//	pObj->getPropertyData()->m_Controler.Set(0, 0);
	pObj->getPropertyData()->PointRemain = cct::PointRemian;
	cPcData* pc = pObj->getPcData();
//	pObj->GetPropertyData(pc);
//	pc->apply();
//	pc->FillHpMp();
	pc->m_Controler.Set(0, 0);
// 	m_pFightState->m_FightMenu.SetControl(charactID, true);
// 	m_pFightState->m_FightMenu.SetControl(charactID + 5, true);
	if (charactID == 0)
	{
// 		m_FightWorkList[charactID].isExist = true;
// 		if (m_FightWorkList[charactID].m_pObj)
// 		{
// 			delete m_FightWorkList[charactID].m_pObj;
// 		}
// 		m_FightWorkList[charactID].m_pObj = pObj;
		SetCharacter(charactID);
//		m_InterfaceTeam.m_LeaveBegin = 1;
	}
// 	else
// 	{
// 		pObj->SetShow(false);
// 	}

	return true;
}



// 
// bool CMainState::LoadCharacterData2(int charactID, string Path)
// {
// 
// 	cObj* pObj = m_FightWorkList[charactID].m_pObj;
// 	LoadCharacterData2(pObj, Path);
// 	m_FightWorkList[charactID].isExist = true;
// 	return true;
// }
// 
// 
// 
// bool CMainState::LoadCharacterData2(cObj*& pObj, string Path)
// {
// 	ostringstream oss;
// 	oss << g_pathFriend;
// 	//	oss << "队友//";
// 	pObj->LoadCharacter(Path, oss.str());
// 	pObj->Set(POS_STAND);
// 	return true;
// }
// 



int CMainState::ReadTaskFightIndex(string Path)
{
	ostringstream oss;
	oss << Path << "\\index.txt";
	ifstream File;
	File.open(oss.str());
	if (!File)ERRBOX;
	int maxnum, minnum, soundnum;

	File >> minnum;
	File >> maxnum;
	File >> soundnum;
	string soundname;
	soundnum = rand() % soundnum + 1;
	for (int i = 0; i < soundnum; i++)
	{
		File >> soundname;
	}
	m_Mp3.Load(soundname);
	int num;
	num = AtutoGetEnemyNum();
	if (num < minnum)num = minnum;
	if (num > maxnum)num = maxnum;
	return num;
}




void CMainState::UpDateInput()
{
	Keyboard.Acquire(true);   // Read keyboard
	Keyboard.Read();
	Mouse.Acquire(true);   // Read keyboard
	Mouse.Read();
	g_xMouse = Mouse.GetXPos();
	g_yMouse = Mouse.GetYPos();
}




// void CMainState::SaveGlobal(sOstream& File)
// {
// 	File << g_strEnter; // "\nGlobal\n";
// 	for (int i = 0; i < c_GlobalButtonNum; i++)
// 	{
// 		File << g_GlobalValues[i] << g_strSpace;
// //		if (i == 30) File << g_strEnter;
// 	}
// }
// 
// void CMainState::LoadGlobal(sIstream& File)
// {
// 	string dustbin;
// 	File >> dustbin;
// //	if (dustbin.compare("Global"))ERRBOX;
// 	g_GlobalValues.resize(c_GlobalButtonNum);
// 	for (int i = 0; i < c_GlobalButtonNum; i++)
// 	{
// 		File >> g_GlobalValues[i];
// 	}
// }










// 
// 
// int CMainState::AddPCEnemy(string name, int modeid, int lv, sAddPoint* addpoint, sZiZhi* zizhi, eMengPai mengpaid, sItem2* pWeapon, int petid, int stronglv, int pos, bool our)
// {
// 	if (petid >= 0)
// 	{
// 		modeid = petid;
// 	}
// 	int wlv = -1;
// 	if (pWeapon)
// 	{
// 		wlv = pWeapon->m_pItemData->GetLv();
// 	}
// 	return AddEnemy(modeid, lv, mengpaid, name, addpoint/*, pWeapon, petid*/, wlv, pos, our);
// 	//sFightList* plist = 0;
// 	int id;
// 	if (-1 == pos)
// 	{
// 		int start;
// 		if (our)
// 			start = 0;
// 		else
// 			start = 10;
// 		id = m_AI.find空位(start, 0, 0); //GetIdle(start);
// 	}
// 	else id = pos;
// 	if (id == -1)return -1;
// 	m_FightWorkList[id].isExist = true;
// // 	m_FightWorkList[id].m_pObj->AutoPCData(name, modeid, addpoint, zizhi, mengpaid, 0, petid, stronglv);
// // 
// // 	//	FollowLv(id,lv);
// // 	cPcData &pc = ((cCharacter*)m_FightWorkList[id].m_pObj->m_pIndex)->m_PcData;
// // 	pc.FollowlvAddPoint(lv, false, true, false);
// // 	if (rand() % 100 < 50)
// // 	{
// // 		pc.FollowShoe();
// // 	}
// 
// 	if (pWeapon)
// 	{
// 		m_FightWorkList[id].m_pObj->SetWeapon强制换模型_不动数据_可能未鉴定(pWeapon->GetType(), pWeapon->GetID());
// 		if (modeid >= 2000)
// 		{
// 			//			pc.m_pWeaponData2 = g_pMainState->m_ItemManage.GetWeaponList(modeid - 2000, pc.m_Equip[2].GetID(), pc.m_Equip[2].GetType());
// 			//			((cCharacter*)m_FightList[id].m_pData->m_pIndex)->GetFightOffset();
// 		}
// 
// 		//		((cCharacter*)m_FightList[id].m_pData->m_pIndex)->m_PCData.m_pWeaponData2 = nullptr;
// 	}
// 	return id;
// }
// 
// 
// 
// int CMainState::AddPCEnemy(sTaskMapObj* pdata, int lv, sAddPoint* addpoint, sZiZhi* zizhi, eMengPai mengpaid, int stronglv /*= 50*/, int pos /*= -1*/, bool out /*= false*/)
// {
// 	return AddEnemy(pdata->m_Npc.m_modeid, lv, mengpaid, pdata->m_Npc.m_name, addpoint, -1, pos, out);
// 
// 	sItem2* pWeapon = 0;
// 	if (pdata->m_Npc.m_modeid >= 2000)
// 	{
// 		if (pdata->m_Npc.weapontype > -1)
// 		{//武器
// 			sItem2 weapon;
// 			weapon.m_Num = 1;
// 			weapon.Set(pdata->m_Npc.weapontype, pdata->m_Npc.weaponid);
// 			pWeapon = &weapon;
// 		}
// //		return AddEnemy(pdata->m_Npc.m_name, pdata->m_Npc.m_modeid, lv, addpoint, mengpaid, pWeapon, -1, pos, out);
// //		plist->m_pObj->AutoPCData(pdata->m_Npc.m_name, pdata->m_Npc.m_modeid - 2000, addpoint, zizhi, mengpaid, pWeapon, -1, stronglv);
// //		((cCharacter*)plist->m_pData->m_pIndex)->m_PCData.m_pWeaponData2 = nullptr;
// 
// 	}
// 	else
// 	{
// //		return AddEnemy(pdata->m_Npc.m_name, pdata->m_Npc.m_modeid, lv, addpoint, pos, out);
// //		plist->m_pObj->AutoPCData(pdata->m_Npc.m_name, 0, addpoint, zizhi, mengpaid, 0, pdata->m_Npc.m_modeid, stronglv);
// 	}
// //	g_pMainState->FollowLv(id,lv);
// // 	((cCharacter*)m_FightWorkList[id].m_pObj->m_pIndex)->m_PcData.FollowlvAddPoint(lv, false, true, false);
// // 	if (rand() % 100 < 50)
// // 	{
// // 		((cCharacter*)m_FightWorkList[id].m_pObj->m_pIndex)->m_PcData.FollowShoe();
// // 	}
// 
// 	
// 
// 	sFightWork* plist = 0;
// 	int id;
// 	if (-1 == pos)
// 	{
// 		int start;
// 		if (out)
// 			start = 0;
// 		else
// 			start = 10;
// 		id = m_AI.find空位(start, 0, 0); //GetIdle(start);
// 	}
// 	else id = pos;
// 	if (id == -1)return false;
// 	m_FightWorkList[id].isExist = true;
// 	plist = &m_FightWorkList[id];
// //	sItem2* pWeapon = 0;
// // 	if (pdata->m_Npc.m_modeid >= 2000)
// // 	{
// // 		if (pdata->m_Npc.weapontype > -1)
// // 		{//武器
// // 			sItem2 weapon;
// // 			weapon.m_Num = 1;
// // 			weapon.Set(pdata->m_Npc.weapontype, pdata->m_Npc.weaponid);
// // 			pWeapon = &weapon;
// // 		}
// // 		plist->m_pObj->AutoPCData(pdata->m_Npc.m_name, pdata->m_Npc.m_modeid - 2000, addpoint, zizhi, mengpaid, pWeapon, -1, stronglv);
// // 		//		((cCharacter*)plist->m_pData->m_pIndex)->m_PCData.m_pWeaponData2 = nullptr;
// // 
// // 	}
// // 	else
// // 	{
// // 		plist->m_pObj->AutoPCData(pdata->m_Npc.m_name, 0, addpoint, zizhi, mengpaid, 0, pdata->m_Npc.m_modeid, stronglv);
// // 	}
// // 	//	g_pMainState->FollowLv(id,lv);
// // 	((cCharacter*)m_FightWorkList[id].m_pObj->m_pIndex)->m_PcData.FollowlvAddPoint(lv, false, true, false);
// // 	if (rand() % 100 < 50)
// // 	{
// // 		((cCharacter*)m_FightWorkList[id].m_pObj->m_pIndex)->m_PcData.FollowShoe();
// // 	}
// 	return id;
// }
// 
// 
// 
// int CMainState::AddPetEnemy(string name, int modeid, int lv, sAddPoint* addpoint, int stronglv, int pos /*= -1*/, bool our)
// {
// 	return AddEnemy(modeid, lv, name, addpoint, pos, our);
// 	sFightWork* plist = 0;
// 	int start;
// 	if (-1 == pos)
// 	{
// 		if (our)
// 			start = 0;
// 		else
// 			start = 10;
// 	}
// 	else start = pos;
// 	int id = -1;
// 	for (int i = start; i < start + 10; i++)
// 	{
// 		if (!m_FightWorkList[i].isExist)
// 		{
// 			id = i;
// 			break;
// 		}
// 	}
// 	if (id == -1)return id;
// 	m_FightWorkList[id].isExist = true;
// //	plist = &m_FightWorkList[id];
// // 	plist->m_pObj->AutoPetData(name, modeid, stronglv, addpoint, true);
// // 	cPropertyData *data = nullptr;
// // 	plist->m_pObj->GetPropertyData(data);
// // 	asert(data, "怪物初始化出错");
// // 	data->m_AddPoint = getAddpointFromPet(data);
// // 	data->Followlv(lv, true, true, true);
// 	return id;
// }
//
// int CMainState::AddPC(
// 	string name,
// 	int modeid,
// 	int lv,
// 	sAddPoint* addpoint,
// 	sZiZhi* zizhi,
// 	eMengPai mengpaid,
// 	sItem2* pWeapon,
// 	int petid,
// 	int stronglv ,
// 	int pos )
// {
// 	return AddPCEnemy( name,  modeid,  lv,  addpoint,  zizhi,  mengpaid /*= eMP_无*/,  pWeapon /*= 0*/ ,petid,stronglv, pos, true);
// }
//
// int CMainState::AddPet(string name, int modeid, int lv, sAddPoint* addpoint, int stronglv, int Pos /*= -1*/)
// {
// 	return AddPetEnemy(name, modeid, lv, addpoint, stronglv, Pos, true);
// }
// 
// 
// 
// 
//
// int CMainState::AddPetEnemy2(int modeid, int lv/*=-1*/, sAddPoint* addpoint/*=0*/, int stronglv/*=-1*/, int Pos /*= -1*/, bool out /*= false*/)
// {
// 	if (-1 == lv)lv = g_pCharacter->m_PcData.m_Lv;
// 	return AddPetEnemy(g_pMainState->m_PetDataManager.GetPetData(modeid)->m_Name, modeid, lv, addpoint,stronglv, Pos, out);
// }
//
// void CMainState::FollowLv(int id,int lv/*=-1*/)
// {
// 	m_FightList[id].m_pData->FollowLvForObj(lv);
// }
// 
// 
// 
// 
// 
// int CMainState::AddPCPetEnemy(ePetID modeid, int lv, sAddPoint* addpoint, eMengPai mengpaid, string name, int stronglv /*= -1*/, bool bOur, int pos /*= -1*/)
// { 
// 	//召唤兽造型的有门派敌人
// 	return AddEnemy(modeid, lv, mengpaid, name, addpoint, -1, pos, bOur);
// 	sZiZhi m_ZiZhi;
// 	sPetData* pData = g_pMainState->m_PetDataManager.GetPetData(modeid);
// //	m_ZiZhi.Set(pData->m_ZiZhi, stronglv, pData->m_LvTake);
// 	m_ZiZhi = pData->m_ZiZhi;
// 	if (name == "")name = pData->m_Name;
// 	int id = AddPCEnemy(name, 0, lv, addpoint, &m_ZiZhi, mengpaid, 0, modeid, stronglv, pos, bOur);
// 	if (id == -1)return -1;
// 	cObj* pObj = g_pMainState->m_FightWorkList[id].m_pObj;
// 	cPropertyData* pPetdata;
// 	pObj->GetPropertyData(pPetdata);
// //	pPetdata->AutoGetSkill(modeid);
// 	return id;
// }
// 
// 
// 
// int CMainState::AddPCPet(ePetID modeid, int lv, sAddPoint* addpoint, eMengPai mengpaid, string name, int stronglv /*= -1*/, bool bOur, int pos /*= -1*/)
// { 
// 	return AddEnemy(modeid, lv, mengpaid, name, addpoint, -1, pos, bOur);
// 	//召唤兽造型的有门派友军
// 	sZiZhi m_ZiZhi;
// 	sPetData* pData = g_pMainState->m_PetDataManager.GetPetData(modeid);
// //	m_ZiZhi.Set(pData->m_ZiZhi, stronglv, pData->m_LvTake);
// 	m_ZiZhi = pData->m_ZiZhi;
// 	if (name == "")name = pData->m_Name;
// 	return AddPCEnemy(name, 0, lv, addpoint, &m_ZiZhi, mengpaid, 0, modeid, stronglv, pos, bOur);
// }
