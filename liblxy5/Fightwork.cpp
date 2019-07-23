#include "_global.h"


bool sFightWork::SetMagiSufferID(ulong MagicID, int MagicPos, cWasFile* pFile, bool up)
{
	return  m_pObj->SetMagiSufferID(MagicID, MagicPos, pFile, up);
}

bool sFightWork::ShowOnScreen(cCanvas* pCanvas)
{
	if (!isExist)return true;
	m_pObj->ShowOnScreen(pCanvas);

	return true;
}

bool sFightWork::ShowDamage(CMainState* p)//´ý¶¨
{
	if (m_DamageTime[0] > 70)
	{
		return true;
	}
	for (int i = 0; i <m_DamageNum; i++)
	{
		SetDamageRect(i);
		m_Damage[i].m_bMove = true;
		p->m_Canvas.Add(&m_Damage[i], 1);
		m_DamageTime[i] += 1;
	}
	return true;
}

bool sFightWork::SetDamageRect(int Num)
{
	int& time = m_DamageTime[Num];
	int speed = 4;
	if (time < 36)
	{
		if (time>29)
		{
			m_Damage[Num].m_y += speed;
		}
		else
			if (time > 25)
			{
			m_Damage[Num].m_y -= speed;
			}
			else
				if (time > 20)
				{
			m_Damage[Num].m_y -= speed;
			m_Damage[Num].SetShowHeight(m_Damage[Num].GetShowHeight() + speed);
				}
	}
	//int woff = 16;
	m_Damage[Num].m_bMove = true;

	/*m_Damage[Num].SetXY(pData->GetX() - Num*woff + (m_DamageNum/ 2) * woff - woff / 2
	,(pData->GetY() + pData->GetTopY())/2 + m_DamageYOffset[Num]+10);*/
	return true;
}

sFightWork::sFightWork()
{
	targetlist.resize(10);
	m_SleepTime = 0;
	m_DamageNum = 0;
	isExist = 0;
	m_pObj = 0;
	RestTarget();

	m_SkillPreSelect.SkillID = -1;
	for (int i = 0; i < 5; i++)
	{
		m_DamageTime[i] = 100;
		m_Damage[i].m_bStatic = true;
	}
}


bool sFightWork::Sleep(int Time, bool bStatic)
{
	if (bStatic)m_pObj->SetStatic(true);
	////////////////////////////////////////////////////////////////////////// ºÇºÇßÕ ¶¯»­Ö¡
	if (m_SleepTime >= Time)
	{
		if (bStatic)m_pObj->SetStatic(false);
		m_SleepTime = 0;
		return true;
	}
	m_SleepTime += 1;
	return false;
}


bool sFightWork::NextTarget(cFightState* pFightState, int sSkillID)
{
	bool bCheckDie = true;
	switch (sSkillID)
	{// ¾ÈÈË
	case 37:
	case 104:
	case 125:
	case 193:
	case 3008:
	case 3009:
	case 3048:
		bCheckDie = false;
	}


	m_NowTargetIdx += 1;
	if (m_NowTargetIdx == m_MaxTargetNum)
	{
		m_NowTargetID = -1;
		return false;
	}
	m_NowTargetID = targetlist[m_NowTargetIdx];
	if (-1 == m_NowTargetID)return false;
	if (pFightState->m_pFightWorkList[m_NowTargetID]->isExist)
	{
		if (bCheckDie)
		{
			cPropertyData* data;
			pFightState->m_pFightWorkList[m_NowTargetID]->m_pObj->GetPropertyData(data);
			if (data->m_HP > 0)
				return true;
		}
		else
			return true;
	}
	return NextTarget(pFightState, sSkillID);
}

bool sFightWork::DieFly()
{
	if (!m_bFlyInit)
		InitFly();
	int& stage = GetWork()->stage;
	if (stage == 0)
	{
		if (Sleep(5))
		{
			m_pObj->Set(POS_SUFFER);
			m_pObj->SetStatic(true);
			stage += 1;
		}
		else
			return true;
	}
	else
		if (stage == 1)
		{
		if (m_pObj->GetX() < 0)
		{
			if (m_DiePoint >0)
			{
				m_DiePoint -= 1;
				if (m_sufferDirection == 1)
				{
					m_sufferDirection = 3;
				}
				else
					if (m_sufferDirection == 7)
					{
					m_sufferDirection = 9;
					}
			}
		}
		else
			if (m_pObj->GetX() > g_640 - 10)
			{
			if (m_DiePoint > 0)
			{
				m_DiePoint -= 1;
				if (m_sufferDirection == 3)
				{
					m_sufferDirection = 1;
				}
				else
					if (m_sufferDirection == 9)
					{
					m_sufferDirection = 7;
					}
			}
			}
			else
				if (m_pObj->GetY() < 0)
				{
			if (m_DiePoint >0)
			{
				m_DiePoint -= 1;
				if (m_sufferDirection == 9)
				{
					m_sufferDirection = 3;
				}
				else
					if (m_sufferDirection == 7)
					{
					m_sufferDirection = 1;
					}
			}
				}
				else
					if (m_pObj->GetY() > g_480 - 10)
					{
			if (m_DiePoint > 0)
			{
				m_DiePoint -= 1;
				if (m_sufferDirection == 1)
				{
					m_sufferDirection = 7;
				}
				else
					if (m_sufferDirection == 3)
					{
					m_sufferDirection = 9;
					}

			}
					}
		int speed = 14;
		int speed2 = 7;
		switch (m_sufferDirection)
		{
		case 1:
			m_pObj->SetX(m_pObj->GetX() - speed);
			m_pObj->SetY(m_pObj->GetY() + speed2);
			break;
		case 3:
			m_pObj->SetX(m_pObj->GetX() + speed);
			m_pObj->SetY(m_pObj->GetY() + speed2);
			break;
		case 7:
			m_pObj->SetX(m_pObj->GetX() - speed);
			m_pObj->SetY(m_pObj->GetY() - speed2);
			break;
		case 9:
			m_pObj->SetX(m_pObj->GetX() + speed);
			m_pObj->SetY(m_pObj->GetY() - speed2);
			break;
		}
		Rotate();

		if (0 == m_DiePoint)
		{
			m_bFlyInit = false;
			m_pObj->SetStatic(false);
			m_work.clear();
			return false;
		}
		}
	m_pObj->MoveHpLine();
	m_pObj->MoveShadow();
	return true;
}

bool sFightWork::Rotate(int rotaterate)
{
	m_rotateRate += 1;
	m_rotateRate = m_rotateRate % rotaterate;
	if (m_rotateRate != 0)
		return true;
	/*bool bPet=true;
	if (pData->m_IndexType == INDEXTYEP_CHARACTER)
	{
	cCharacter* pc = (cCharacter*)pData->m_pIndex;
	if (!pc->m_PCData.m_bUseCard)
	{
	bPet = false;
	}
	}*/

	m_pObj->SetDirection(GetRotateDirection(m_pObj->GetDirection(), true));
	return true;
}

bool sFightWork::InitFly()
{
	m_DiePoint = 3;
	m_rotateRate = 0;
	m_bFlyInit = true;
	return true;
}

bool sFightWork::Free()
{

	m_work.clear();
	m_WorkType = -1;
	if (m_pObj)
	{
		m_pObj->Free();
	}
	isExist = false;
	m_bDie = false;
	m_bFlyInit = false;
	m_DiePoint = 0;
	return true;
}


const sFightPoint* sFightWork::GetFightPoint()
{
	switch (m_pObj->m_IndexType)
	{
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* pe = (cPet*)m_pObj->m_pIndex;
			return pe->GetFightPoint();
		}
		break;
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* pc = (cCharacter*)m_pObj->m_pIndex;
			return pc->GetFightPoint();
		}
	}
	return 0;
}

sFightWork::~sFightWork()
{
	Free();
	SAFE_DELETE(m_pObj);
}

bool sFightWork::Swap(sFightWork& fightlist)
{
	/*if (!isLive)
	{
	fightlist.m_id

	return true;
	}*/
	//if (!fightlist.isLive)return false;
	/*cPetData* pPetdata1;
	cPetData* pPetdata2;
	m_pData->GetDateP(pPetdata1);
	fightlist.m_pData->GetDateP(pPetdata2);*/
	//swap(pPetdata1->m_IDinFightList, pPetdata2->m_IDinFightList);
	swap(m_SkillPreSelect, fightlist.m_SkillPreSelect);
	swap(m_pObj, fightlist.m_pObj);
	swap(isExist, fightlist.isExist);
	swap(m_FriendListid, fightlist.m_FriendListid);
	return true;
}


void sFightWork::RestTarget()
{
	m_NowTargetIdx = -1;
	m_NowTargetID = -1;
	for (int i = 0; i < 10; i++)
		targetlist[i] = -1;
}

// void sFightWork::operator=(sFightWork& flist)
// {
// 	m_pObj = flist.m_pObj;
// }

void sFightWork::SetWork(int type, int state /* = 0 */)
{
	sWork work;
	work.type = type;
	work.stage = state;
//  m_work.clear();
	m_work.push_back(work);
}
void sFightWork::SetWorkFront(int type, int state /* = 0 */)
{
	sWork work;
	work.type = type;
	work.stage = state;
	m_work.insert(m_work.begin(), work);
	
}


