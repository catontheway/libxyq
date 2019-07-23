#include "_global.h"

void cCharacter::GetID(int Pos, vector<ulong>& out)
{
	 // 大头像
	if (18 != Pos)
	{
// 		if (m_PcData.m_bUseCard)//角色处于变身状态的话
// 		{
// 		if (m_PcData.m_pCardPetData)
// 		{
// 			if (m_PcData.m_JinJieNum.m_index > 0)
// 				m_PcData.m_pCardPetData->propertyData.m_JinJieNum = m_PcData.m_JinJieNum;
// 			if (20 == Pos)
// 				return m_PcData.m_pCardPetData->GetID(18, out);
// 			else
// 				return m_PcData.m_pCardPetData->GetID(Pos, out);
// 		}
// 		}
		if (m_PcData.m_CardPetID >= 0)//角色处于变身状态的话
		{
			// 小头像
			return g_pMainState->m_PetDataManager.GetPetData(m_PcData.m_CardPetID)->GetID(m_PcData.m_JinJieNum.m_index, Pos == 20 ? 18 : Pos, out);
		}
	}
	if (m_PcData.m_pCharacterData2)
	{
		ulong testid;
		testid = m_PcData.m_pCharacterData2->m_Sound.GetSoundID(Pos == POS_SOUNDATTACK2 ? POS_SOUNDATTACK : Pos);
		if (testid)
		{
			out.resize(1);
			out[0] = testid;
			return;
		}
	}
	int m_bDuJie = 2;
	int m_faceMood = 0;
	switch (Pos)
	{
	case POS_DIALOG:
	case POS_SMALLHEAD:
	case POS_BIGHEAD:
		{
			if (m_PcData.m_Lv <= cct::LvFor飞升)
			{
				/*m_PcData.*/m_bDuJie = 0;
			}
			else if (m_PcData.m_Lv <= cct::LvFor渡劫)
			{
				/*m_PcData.*/m_bDuJie = 1;
			}
// 			else
// 			{
// 				m_PcData.m_bDuJie = 2;
// 			}
		}
		break;
	}
	switch (Pos)
	{
	case POS_STAND:
	case POS_WALK:
		if (m_PcData.m_bOnZuoQi)
		{
			if (m_PcData.m_ZuoQi.m_pZuoQi)
			{
				return m_PcData.m_ZuoQi.GetID(Pos, out);
			}
		}
		break;
	case POS_ANGRY:
		out.resize(1);
		out[0] = m_pCharacterData->m_posangry;
		return;
	case POS_SIT:
		out.resize(1);
		out[0] = m_pCharacterData->m_possit;
		return;
	case POS_BOW:
		out.resize(1);
		out[0] = m_pCharacterData->m_posbow;
		return;
	case POS_CRY:
		out.resize(1);
		out[0] = m_pCharacterData->m_poscry;
		break;
	case POS_GREET:
		out.resize(1);
		out[0] = m_pCharacterData->m_posgreet;
		return;
	case POS_DIALOG:
		out.resize(1);
		out[0] = m_pCharacterData->m_Head[/*m_PcData.*/m_bDuJie].m_dialog;
		return;
	case POS_SMALLHEAD:
		out.resize(1);
		out[0] = m_pCharacterData->m_Head[/*m_PcData.*/m_bDuJie].m_HeadMoods[/*m_PcData.*/m_faceMood].m_smallhead;
		return;
	case POS_BIGHEAD:
		out.resize(1);
		out[0] = m_pCharacterData->m_Head[/*m_PcData.*/m_bDuJie].m_HeadMoods[/*m_PcData.*/m_faceMood].m_bighead;
		return;
	}


	if (!m_PcData.m_pCharacterData2)
	{
		if (m_PcData.m_Equips[2].GetNum())
		{
			//设置武器
			m_PcData.m_pWeaponData2 = g_pMainState->m_ItemManage.GetWeaponList(m_PcData.modeid, m_PcData.m_Equips[2].GetID(), m_PcData.m_Equips[2].GetType());
			//通过武器决定角色的造型...合理吧
			if (m_PcData.m_pWeaponData2)
			{
				m_PcData.m_pCharacterData2 = &m_pCharacterData->m_Pos[m_PcData.m_pWeaponData2->MasterPos];
			}
			else
			{
				m_PcData.m_pCharacterData2 = &m_pCharacterData->m_Pos[0];
			}
		}
		else
		{
			m_PcData.m_pCharacterData2 = &m_pCharacterData->m_Pos[0];
		}
	}
	if (m_PcData.m_pWeaponData2)
	{
		out.resize(2);
		out[0] = m_PcData.m_pCharacterData2->GetID(Pos);
		out[1] = m_PcData.m_pWeaponData2->GetID(Pos);
	}
	else
	{
		out.resize(1);
		out[0] = m_PcData.m_pCharacterData2->GetID(Pos);
	}
}

// 
// bool cCharacter::CanEquip(int EquipType, int EquipLv, int Pos)
// {
// 	if (m_PcData.m_Lv < EquipLv)return false;
// 	if (Pos != -1)
// 	{
// 		if (Pos < 6)
// 		{
// 			if (EquipType < 15)
// 			{
// 				if (Pos != 2)
// 					return false;
// 			}
// 			switch (EquipType)
// 			{
// 			case 15://头盔
// 			case 16:
// 				if (Pos != 0)return false;
// 				break;
// 			case 17://衣服
// 			case 18:
// 				if (Pos != 3)return false;
// 				break;
// 			case 19://项链
// 				if (Pos != 1)return false;
// 				break;
// 			case 20://腰带
// 				if (Pos != 4)return false;
// 				break;
// 			case 21://鞋
// 				if (Pos != 5)return false;
// 				break;
// 			}
// 		}
// 	}
// 	return m_pCharacterData->CanEquip(EquipType);
// }
//



const sFightPoint* cCharacter::GetFightPoint()
{
	// m_bUseCard
	if (m_PcData.m_CardPetID >= 0)
	{
		return &g_pMainState->m_PetDataManager.GetPetData(m_PcData.m_CardPetID)->m_FightPoint[m_PcData.m_JinJieNum.GetBJinJie() ? 1 : 0];
		//		return m_PcData.m_pCardPetData->GetFightPoint();
	}
	if (!m_PcData.m_pCharacterData2)
	{
		if (m_PcData.m_Equips[2].GetNum())
		{
			//设置武器
			m_PcData.m_pWeaponData2 = g_pMainState->m_ItemManage.GetWeaponList(m_PcData.modeid, m_PcData.m_Equips[2].GetID(), m_PcData.m_Equips[2].GetType());
			//通过武器决定角色的造型...合理吧
			m_PcData.m_pCharacterData2 = &m_pCharacterData->m_Pos[m_PcData.m_pWeaponData2->MasterPos];
		}
		else
		{
			m_PcData.m_pCharacterData2 = &m_pCharacterData->m_Pos[0];
		}
	}
	return &m_PcData.m_pCharacterData2->m_Offset;
}


bool cCharacter::AddMoney(int xianjin, int chubei, int cunyin)
{
	return m_PcData.AddMoney(xianjin, chubei, cunyin);
}


int cCharacter::GetSkillLv(int id, cSkillManager* p)
{
	if (id < 1000) //只有师门技能
	{
		sSkill* pSkill = p->GetSkill(id);
		return m_PcData.m_MengPaiSkillLvs[pSkill->m_Owner];
	}
	else return m_PcData.m_Lv;
}

//染色
void cCharacter::GetRanse(int Pos, array<sChangeColorData*, 4>& pChangeColor)
{
	forr (pChangeColor, i)
	{
		pChangeColor[i] = 0;
	}
//	if (m_PcData.m_bUseCard)//角色处于变身状态的话)
	if (m_PcData.m_CardPetID >= 0)
	{
		forr(pChangeColor, i)
		{
			pChangeColor[i] = &m_PcData./*m_pCardPetData->propertyData.*/m_RanSe.m_ranse[i];
		}
		return;
	}
	//坐骑
	if (m_PcData.m_bOnZuoQi)
		if (m_PcData.m_ZuoQi.m_pZuoQi)
		{
		if (Pos == POS_STAND || Pos == POS_WALK)
		{
			pChangeColor[0] = &m_PcData.m_ZuoQiRanSe;
			pChangeColor[1] = &m_PcData.m_RanSe.m_ranse[0];
			if (m_PcData.m_ZuoQi.m_ZhuangShi.GetNum())
			{
				pChangeColor[2] = &m_PcData.m_ZhuangShiRanSe;
			}
			return;
		}

		}
	pChangeColor[0] = &m_PcData.m_RanSe.m_ranse[0];

}

// void cCharacter::AutoPCData(string name, int modeid, sAddPoint* addpoint, sZiZhi* zizhi, eMengPai mengpaid, int petid)
// {
// 	if (modeid >= 2000)
// 		modeid -= 2000;
// 	m_PcData.AutoPCData(name, modeid, addpoint, zizhi, mengpaid, petid);
// 	m_pCharacterData = &g_pMainState->m_pCharacterDataList[modeid];
// 	m_PcData.m_Race = m_pCharacterData->m_Autorace;
// }

void cCharacter::Talk(string str)
{
	g_pMainState->m_Dialog.Reset();
	ulong head;
	head = GetID(POS_DIALOG);
	g_pMainState->m_Dialog.SetHead(head);
	g_pMainState->m_Dialog.SetString(str);
	g_pMainState->m_Dialog.OnOff(true);
}


void cCharacter::Free()
{
	//删掉召唤兽
	for (int i = 0; i < m_PcData.m_NumofBB; i++)
	{
		SAFE_DELETE(m_PcData.m_pPets[i]);
	}

// 	if (m_PcData.m_bUseCard)
// 		if (m_PcData.m_CardPetID)
// 		{
// 		SAFE_DELETE(m_PcData.m_pCardPetData);
// 		}
}


// 
// int cCharacter::GetRace()
// {
// 	if (m_PcData.m_Race < 0)
// 		m_PcData.m_Race = m_pCharacterData->m_Autorace;
// 	return m_PcData.m_Race;
// }

void cCharacter::SetData(sCharacterData* data)
{
// 	if (m_PcData.m_Race == -1)
// 		m_PcData.m_Race = data->m_Autorace;
	m_pCharacterData = data;
	m_PcData.modeid = data->m_ID;
	m_PcData.m_pCharacterData2 = 0;
	m_PcData.m_pWeaponData2 = 0;
}


void cCharacter::UseCard(int id)
{
	if (id == -1)
	{
//		SAFE_DELETE(m_PcData.m_pCardPetData);
//		m_PcData.m_bUseCard = false;
		m_PcData.m_CardPetID = -1;
	}
	else
	{
		if (m_PcData.m_CardPetID == id)
		{
			int jj = m_PcData.m_JinJieNum.m_JinJieNum;
			if (jj > 2)
			{
				m_PcData.m_JinJieNum.m_JinJieNum = 0;
				m_PcData.m_JinJieNum.m_index = 0;
				UseCard(-1);
				g_pMainState->m_PCHead.UpDateHead();
				return;
			}
			m_PcData.SetJinJie(1);
// 			m_PcData.m_pCardPetData->propertyData.m_JinJieNum.m_index = m_PcData.m_JinJieNum.m_index;
// 			m_PcData.m_pCardPetData->propertyData.m_JinJieNum = m_PcData.m_JinJieNum;
			g_pMainState->m_PCHead.UpDateHead();
			return;
		}
// 		if (0 == m_PcData.m_pCardPetData)
// 		{
// 			m_PcData.m_pCardPetData = new cPet;
// 		}
// 		m_PcData.m_bUseCard = true;
		m_PcData.m_CardPetID = id;
//		m_PcData.m_pCardPetData->SetData(g_pMainState->m_PetDataManager.GetPetData(id));
		m_PcData.SetJinJie(0);
//		m_PcData.m_pCardPetData->propertyData.m_JinJieNum.m_index = m_PcData.m_JinJieNum.m_index;
//		m_PcData.m_pCardPetData->propertyData.m_JinJieNum = m_PcData.m_JinJieNum;
	}
	g_pMainState->m_PCHead.UpDateHead();
}





void cCharacter::changeModel(int id)
{
	if (id == m_pCharacterData->m_ID)
	{
		return;
	}
	SetData(&g_pMainState->m_pCharacterDataList[id]);

	g_pMainState->m_PCHead.UpDateHead();

	cPcData* data = &m_PcData;
	forv(data->m_Equips, i)
	{
		auto& p = data->m_Equips[i].m_pItemData;
		if (!p)
		{
			continue;
		}
		int& t = p->m_Type;
		if (!data->CanEquip(t))
		{
			if (t == 15)
			{
				p = g_pMainState->m_ItemManage.GetItem(16, p->m_ID);
			}
			else if (t == 16)
			{
				p = g_pMainState->m_ItemManage.GetItem(15, p->m_ID);
			}
			else if (t == 17)
			{
				p = g_pMainState->m_ItemManage.GetItem(18, p->m_ID);
			}
			else if (t == 18)
			{
				p = g_pMainState->m_ItemManage.GetItem(17, p->m_ID);
			}
			else
			{
				int typelist[2];
				GetWeaponType(id, typelist[0], typelist[1]);
				int k = typelist[rand() % 2];
				if (typelist[1] == -1)
				{
					k = typelist[0];
				}
				p = g_pMainState->m_ItemManage.GetItem(k, p->m_ID);
			}
		}
	}

	if (1)
	{
		auto &pc = *data;
		int i = 0;
		sChangeColorData &rs = pc.m_RanSe.m_ranse[i];
		//		rs.Read(File, mn.mode, sChangeColorData::ePc, i);
		rs.partnum = 4;
		ulong color = g_pMainState->m_pCharacterDataList[pc.modeid].m_ColorID;
		if (color == 0)
		{
			color = 0x1657;
		}
		g_pMainState->m_ColorManage.Set(color);
		for (int k = 0; k < rs.partnum; ++k)
		{
			rs.SetColorChange(k, 0);
			g_pMainState->m_ColorManage.GetColorMatrix(
				k,
				rs.GetColorChange(k),
				rs.m_colormatrix[k]);
		}
		pc.m_ZuoQi.m_ownerID = pc.modeid;
	}

	m_PcData.getObj()->Reset();
	m_PcData.getObj()->Set(POS_STAND);
}
