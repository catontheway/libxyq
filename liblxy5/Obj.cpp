#include "_global.h"


bool cObj::AddState(sBuff buf)
{
	//重复时更新状态
	if (m_StateList.size())
		for (list<sBuff>::iterator it = m_StateList.begin(); it != m_StateList.end(); it++)
		{
		if (it->ID == buf.ID)
		{
			it->remainingTimes = buf.remainingTimes;
			return true;
		}
		}
	// 狼: 为什么...5? 为什么? 你告诉我为什么要去掉状态?
// 	if (m_StateList.size() == 5)
// 	{
// 		list<sBuff>::iterator it = m_StateList.begin();
// 		g_pMainState->m_SkillManager.SetDateBuffDown(it);// it->targetID, it->ID);
// 		m_StateList.pop_front();
// 	}
	m_StateList.push_back(buf);
	list<sBuff>::iterator it;
	if (m_StateList.size() == 1)
	{
		it = m_StateList.begin();
	}
	else
	{
		it = m_StateList.end();
		it--;
	}
	it->data.Load(buf.MagicID);
	it->data.m_NeedShow = true;
	it->data.m_Picture.m_FrameGap = 5;
	MoveMagicSuffer();
	return true;
}


bool cObj::ReMoveStateID(int id)
{
	for (list<sBuff>::iterator Iterator = m_StateList.begin(); Iterator != m_StateList.end();)
	{
		if (Iterator->ID == id)
		{
			list<sBuff>::iterator it2 = Iterator;
			Iterator++;
			g_pMainState->m_SkillManager.SetDateBuffDown(it2);// it2->targetID, it2->ID);
			it2->data.Free();
			m_StateList.erase(it2);
			return true;
		}
		else Iterator++;
	}
	return false;
}


bool cObj::ReMoveState(eBuffType Type)
{
	for (list<sBuff>::iterator Iterator = m_StateList.begin(); Iterator != m_StateList.end();)
	{
		if (Iterator->EffectType == Type)
		{
			list<sBuff>::iterator it2 = Iterator;
			Iterator++;
			g_pMainState->m_SkillManager.SetDateBuffDown(it2);//it2->targetID, it2->ID);
			it2->data.Free();
			m_StateList.erase(it2);
			continue;
		}
		else
			Iterator++;
	}
	return true;
}


void cObj::ClearState()
{
	//BUFF显示
	for (list<sBuff>::iterator it = m_StateList.begin(); it != m_StateList.end(); it++)
	{
		g_pMainState->m_SkillManager.SetDateBuffDown(it);// id, it->ID);
		it->data.Free();
	}
	m_StateList.clear();
}


cObj::cObj()
{
	m_MagicSuffer.m_FrameGap = 6;
	m_MagicSuffer.m_NeedShow = false;
	m_MagicCri.m_FrameGap = 1;
	m_MagicCri.m_NeedShow = false;
	m_bCheckWall = false;
	m_Shadow.m_bStatic = true;
	m_ShowTime = 0;
	m_bShake = false;
	m_bShakeFor抖动 = false;
	m_AutoRun = false;
	m_pIndex = 0;
	m_IndexType = 0;
	m_NowPos = -1;
	m_PrePos = -1;
	m_AstartPathIndex = -2;
	m_moveSpeed = g_GlobalValues[7];
	for (int i = 0; i < 6; i++)
	{
		m_ContextList.m_TextLineList[i].m_line.SetColor(RGB(255, 255, 255));
		m_ContextList.m_TextLineList[i].m_line.m_hFont = 0;
	}
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_Picture.m_StepUpdate = 0;
		m_data[i].m_Picture.now_frame = 0;
		m_data[i].m_NeedShow = false;
	}

	for (int i = 0; i < 4; i++)
	{
		m_pShowData[i] = &m_data[i];
	}
}



void cObj::Free()
{
	for (int i = 0; i < 6; i++)
	{
		m_data[i].Free();
	}
	m_PrePos = -1;
	m_NowPos = -1;
	FreeData();
	m_Script.Free();
	m_AstartPathVecs.clear();
	m_ScriptSelect = 0;
	SetShake(false);//
}

cObj::~cObj()
{
	Free();
}

bool cObj::Show(cCanvas* pCanvas)
{
	if (!m_pIndex)return true;
	for (int i = 1; i < 4; i++)
	{
		m_pShowData[i]->m_Picture.now_frame = m_pShowData[0]->m_Picture.now_frame;
		m_pShowData[i]->m_Picture.m_StepUpdate = m_pShowData[0]->m_Picture.m_StepUpdate;
		m_pShowData[i]->m_bMove = m_pShowData[0]->m_Picture.m_bMove;
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_pShowData[i]->m_NeedShow)
			if (m_pShowData[i]->m_NowID)
			{
			m_pShowData[i]->m_Picture.Spr.m_Bottom = GetY();
			pCanvas->Add(m_pShowData[i], 0);
			}

	}
	if (m_MagicEffect.m_pFile)
	{
		pCanvas->Add(&m_MagicEffect, 0);
		if (m_MagicEffect.now_frame == m_MagicEffect.m_pFile->GetMaxFrame() - 1)
		{
			m_MagicEffect.m_pFile = 0;
		}
	}
	//显示名字			
	if (m_bNeedShowName)
	{
		g_pMainState->m_Canvas.Add(&m_TrueName);
		if (g_StateType != STATE_FIGHT)
		{
			g_pMainState->m_Canvas.Add(&m_Name称谓);
		}
// 		else
// 		{
// 			g_pMainState->m_Canvas.Add(&m_ConductFire);
// 			g_pMainState->m_Canvas.Add(&m_ConductSeal);
// 		}
	}
	//显示对话
	if (m_ShowTime > 0)
	{
		if (g_pMainState->m_Map.m_pMap->m_bMove)
		{
			MoveDialog();
		}
		ShowFaceText(pCanvas);
	}
	return true;
}
bool cObj::ShowFaceText(cCanvas* pCanvas)
{
	//时间流逝
	if (1 > m_ShowTime)
		return true;
	m_ShowTime -= 1;
	if (1 > m_ShowTime)
	{
		if (!g_pMainState->GetLockMouse())
		{
			if (g_StateType != STATE_FIGHT)
			{
				m_ShowTime += 10;
			}
		}
		else
		{
			if (g_pMainState->m_TriggerDialog.m_datalist[1].m_Nowtext > -1)
				g_pMainState->m_TriggerDialog.Process(1);
			return true;
		}
	}
	////显示背景
	for (int i = 0; i < 2; i++)
		pCanvas->Add(&m_FaceTextBackp[i], 1);
	//显示文本	
	m_ContextList.Show(pCanvas);

	return true;
}


bool cObj::ShowOnScreen(cCanvas* pCanvas)
{
	if (!m_pIndex)return true;

	for (list<sBuff>::iterator it = m_StateList.begin(); it != m_StateList.end(); it++)
	{
		if (it->MagicID)
			if (it->bBuffup == false)
			{
			pCanvas->Add(&it->data, 1);
			}
	}
	if (!m_bMagicSufferUp)
		if (m_MagicSuffer.m_NeedShow)
		{
		pCanvas->Add(&m_MagicSuffer, 1);
		if (m_MagicSuffer.now_frame == m_MagicSuffer.m_pFile->GetMaxFrame() - 2)
		{
			m_MagicSuffer.m_NeedShow = false;
		}
		}

	Shake();
	for (int i = 1; i < 4; i++)
	{
		m_pShowData[i]->m_Picture.now_frame = m_pShowData[0]->m_Picture.now_frame;
		m_pShowData[i]->m_Picture.m_StepUpdate = m_pShowData[0]->m_Picture.m_StepUpdate;
		m_pShowData[i]->m_Picture.m_bMove = m_pShowData[0]->m_Picture.m_bMove;
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_pShowData[i]->m_NeedShow)
			if (m_pShowData[i]->m_NowID)
			{
				if (m_bGhost)
				{
					int time1 = g_pMainState->m_InterfaceDoor.m_TimeShiCheng.ss;
					time1 = time1 % 8;
					if (0 == time1)
					{
						for (int i1 = 0; i1 < 4; i1++)
						{
							m_Ghost[i1][1].SetXY(GetX(), GetY());
						}
					}
					else
						if (4 == time1)
						{
							for (int i1 = 0; i1 < 4; i1++)
							{
								m_Ghost[i1][0].SetXY(GetX(), GetY());
							}
						}

					for (int j = 0; j < 2; j++)
					{
						pCanvas->Add(&m_Ghost[i][j], 1);
					}
				}
				pCanvas->Add(m_pShowData[i], 1);
			}

	}

	if (m_MagicEffect.m_pFile)
	{
		pCanvas->Add(&m_MagicEffect, 1);
		if (m_MagicEffect.now_frame == m_MagicEffect.m_pFile->m_Picture.Spr.GetMaxFrame() - 1)
			m_MagicEffect.m_pFile = 0;
	}
	//显示名字			
	if (m_bNeedShowName)
	{
		g_pMainState->m_Canvas.Add(&m_TrueName);
		if (g_StateType != STATE_FIGHT)
		{
			g_pMainState->m_Canvas.Add(&m_Name称谓);
		}
		else
		{
			g_pMainState->m_Canvas.Add(&m_ConductFire);
			g_pMainState->m_Canvas.Add(&m_ConductSeal);
		}
	}


	//BUFF显示
	if (m_StateList.size())
		for (list<sBuff>::iterator it = m_StateList.begin(); it != m_StateList.end(); it++)
		{
		if (it->MagicID)
			if (it->bBuffup == true)
			{
			pCanvas->Add(&it->data, 1);
			}
		}


	if (m_bMagicSufferUp)
		if (m_MagicSuffer.m_NeedShow)
		{
		pCanvas->Add(&m_MagicSuffer, 1);
		if (m_MagicSuffer.GetFrame() == m_MagicSuffer.m_pFile->GetMaxFrame() - 2)
		{
			m_MagicSuffer.m_NeedShow = false;
		}
		}
	//显示对话
	if (m_ShowTime > 0)
	{
		ShowFaceText(pCanvas);
	}
	return true;
}

void cObj::SufferBack(float speed, int sufferDirection)
{
	//	float jj = speed / 2;
	if (sufferDirection == 1)
	{
		m_yPos += speed / 2;
		m_xPos -= speed;
	}
	else
		if (sufferDirection == 3)
		{
		m_yPos += speed / 2;
		m_xPos += speed;
		}
		else
			if (sufferDirection == 7)
			{
		m_yPos -= speed / 2;
		m_xPos -= speed;
			}
			else
				if (sufferDirection == 9)
				{
		m_yPos -= speed / 2;
		m_xPos += speed;
				}
				else
				{
					speed = (speed)*1.5f;
					if (sufferDirection == 8)
						m_yPos -= speed;
					else
						if (sufferDirection == 2)
							m_yPos += speed;
						else
							if (sufferDirection == 4)
								m_xPos -= speed;
							else
								if (sufferDirection == 6)
									m_xPos += speed;
				}
	if (m_bNeedShowName)
	{
		MoveName();
	}
	m_MagicEffect.SetXY(GetX(), GetY());
	m_MagicEffect.m_bMove = true;
	for (int i = 0; i < 3; i++)
	{
		m_pShowData[i]->SetXY((int)m_xPos, (int)m_yPos);
	}
	m_Shadow.SetXY((int)m_xPos, m_Shadow.GetY() + ((int)m_xPos - m_Shadow.GetX()) / 2);
}

bool cObj::Set(int POS_X, bool bCircle)
{
	if (m_NowPos == POS_X)return true;

	m_NowShowData = !m_NowShowData;
	for (int i = 0; i < 4; i++)
	{
		m_pShowData[i] = &m_data[4 * m_NowShowData + i];
		m_pShowData[i]->SetXY((int)m_xPos, (int)m_yPos);
		m_pShowData[i]->m_bCircle = bCircle;
	}
	if (m_PrePos == POS_X)
	{
		swap(m_NowPos, m_PrePos);
	}
	else
	{
		m_PrePos = m_NowPos;
		m_NowPos = POS_X;
	}
	vector<ulong> data;
	GetID(POS_X, data);

	array<sChangeColorData*, 4> pranse;
	forr (pranse, i)
		pranse[i] = 0;
	switch (m_IndexType)
	{
	case  INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* pc = (cCharacter*)m_pIndex;
			pc->GetRanse(POS_X, pranse);
		}
		break;
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* pc = (cPet*)m_pIndex;
			pc->GetRanse(pranse);
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_NeedShow = false;
	}

	for (int i = 0; i < data.size(); i++)
	{
		if (0 == data[i])continue;
		m_pShowData[i]->m_NeedShow = true;
		m_pShowData[i]->Load(data[i], pranse[i]);
		if (m_pShowData[0]->GetDirectionNum() == 4)
		{
			if ((m_direction % 2) == 0)
				SetDirection(Direction8To4(m_direction));
		}
	}
	//数字越小,越快
	switch (POS_X)
	{
	case  POS_WALK:
		if (m_pShowData[0]->GetDirectionNum() == 8)
		{
			SetSpeed(4);
		}
		else
		{
			SetSpeed(6 - 1);
		}
		break;
	case POS_ATTACK:
	case POS_ATTACK2:
		SetSpeed(5);
		break;
	case POS_MAGIC:
		SetSpeed(4);
		break;
	case POS_FIGHT_STAND:
		SetSpeed(6);
		break;
	case POS_RETURN:
	case POS_RUN:
		SetSpeed(2);
		break;
	default:
		SetSpeed(8 - 3);
		break;
	}
	// 狼: 为什么要分身？是分身么？
	if (m_bGhost)
	{
		for (int i = 0; i < 4; i++)
		{
			m_Ghost[i][0].Set(m_pShowData[i]);
			m_Ghost[i][1].Set(m_pShowData[i]);
		}
	}
	Move2();
	return true;
}

bool cObj::Move()
{
	if (-2 == m_AstartPathIndex)return false;
	float   oldx = m_xPos;
	float   oldy = m_yPos;
	int xDis = abs((int)(m_xPos - m_xTarget));
	int yDis = abs((int)(m_yPos - m_yTarget));
	m_moveSpeed = cct::getINT(7);
	//如果到达最终目标,停止
	if (xDis < m_moveSpeed && yDis < m_moveSpeed)
	{
		if (m_AstartPathIndex == -1)
		{
			Stand();
		}
		else
			if (m_AstartPathIndex == -3)
			{
			Stand();
			}
		return false;   //已经在目的地了
	}
	int Direction = -1;
	if (4 == m_pShowData[0]->GetDirectionNum())
		Direction = GetDirection4((int)m_xPos, (int)m_yPos, (int)m_xTarget, (int)m_yTarget);
	else
		Direction = GetDirection8Ex(m_direction, (int)m_xPos, (int)m_yPos, (int)m_xTarget, (int)m_yTarget);
	SetDirection(Direction);
//	SetDirection(10);

	CoutPoint((float)m_moveSpeed, m_xPos, m_yPos, m_xTarget, m_yTarget, m_xPos, m_yPos);

	//如果前方是障碍,中断
	if (m_bCheckWall)
		if (m_AstartPathIndex < 0)
			if (g_pMainState->m_Map.m_pBmp->isFold((int)m_xPos, (int)m_yPos))
			{
		Set(POS_STAND);
		m_AstartPathIndex = -2;
		m_xPos = oldx;
		m_yPos = oldy;
		return false;
			}
	Set(POS_WALK);
	for (int i = 0; i < 4; i++)
	{
		m_pShowData[i]->m_Picture.m_x = (int)m_xPos;
		m_pShowData[i]->m_Picture.m_y = (int)m_yPos;
		m_pShowData[i]->m_bMove = true;
	}
	MoveShadow();
	if (m_MagicEffect.m_NeedShow)
	{
		m_MagicEffect.m_x = (int)m_xPos;
		m_MagicEffect.m_y = (int)m_yPos;
		m_MagicEffect.m_bMove = true;
	}
	//移动对话
	if (m_ShowTime > 0)
	{
		MoveDialog();
	}

	//移动名字
	if (m_bNeedShowName)
	{
		MoveName();
	}
	MoveMagicSuffer();

	if (m_MagicSuffer.m_NeedShow)
	{
		MoveMagicSufferID();
	}

	if (this == g_pHeroObj && g_pMainState->_wasHeadTop.m_NowID && g_StateType != STATE_FIGHT)
	{
		g_pMainState->_wasHeadTop.SetXY(GetX(), GetY() /*+ m_pShowData[0]->GetyOffset()*/ - m_pShowData[0]->GetShowHeight() - g_pMainState->_wasHeadHigh - 20);
	}

	if (m_Foot2 >= 0 && g_StateType != STATE_FIGHT)
	{
		if (m_Foot2s.empty())
		{
			m_Foot2s.resize(3);
		}
		static int x = 0;
		if (((++x) % 60) == 59)
		{
			x = 0;
		}
	}
	return true;
}

void cObj::Stand()
{
	m_xTarget = m_xPos;
	m_yTarget = m_yPos;
	Set(POS_STAND);
	m_AstartPathIndex = -2;
}

void cObj::SetShine(bool needshine)
{
	for (int i = 0; i < 8; i++)
		m_data[i].SetShine(needshine);
}

bool cObj::isPointOn(int x, int y)
{
	if (!m_pIndex)return false;

	RECT rect;
	for (int i = 0; i < 4; i++)
	{
		if (m_pShowData[i]->m_NowID)
		{
			CPicture& pic = m_pShowData[i]->m_Picture;
			int a = pic.getFrameIdx();
			rect.left = pic.m_x - pic.Spr.m_pDataOffsetList[a].FramX;
			rect.top = pic.m_y - pic.Spr.m_pDataOffsetList[a].FramY;
			rect.bottom = rect.top + pic.m_Height;
			rect.right = rect.left + pic.m_Width;
			if (isOn(x, y, rect))
			{
				int xOffset = x - rect.left;
				int yOffset = y - rect.top;
				if (0 != pic.Spr.lpAlpha[a][xOffset + yOffset*pic.m_Width])
					return true;
			}
		}
	}
	return false;
}

void cObj::GetID(int POS_X, vector<ulong>& out)
{
	if (!m_pIndex)return;
	if (m_IndexType == INDEXTYEP_CHARACTER)
	{
		cCharacter* p = (cCharacter*)m_pIndex;
		p->GetID(POS_X, out);
		return;
	}
	if (m_IndexType == INDEXTYEP_NPC)
	{
		cNpc* p = (cNpc*)m_pIndex;
		p->GetID(POS_X, out);
		return;
	}
	if (m_IndexType == INDEXTYEP_PET)
	{
		cPet* p = (cPet*)m_pIndex;
		p->GetID(POS_X, out);
		return;
	}

}

ulong cObj::GetID(int POS_X)
{
	vector<ulong> out;
	GetID(POS_X, out);
	if (out.size())
		return out[0];
	return 0;
}

void cObj::SetDataType(int Type)
{
	FreeData();
	m_IndexType = Type;
	switch (Type)
	{
	case 100:
		if (1)
		{
			cCharacter* p = new cCharacter;
			m_pIndex = p;
			p->m_PcData.m_IDinFightWorkList = m_IDInFightlist;
		}
		break;
	case 101:
		if (1)
		{
			cPet* p = new cPet;
			m_pIndex = p;
			p->m_PetData.m_IDinFightWorkList = m_IDInFightlist;
		}
		break;
	case 102:
		if (1)
		{
			cNpc* p = new cNpc;
			m_pIndex = p;
		}
		break;
	default:
		ERRBOX;
		break;
	}
}

void cObj::FreeData()
{
	switch (m_IndexType)
	{
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* p = (cCharacter*)m_pIndex;
			SAFE_DELETE(p);
			m_pIndex = 0;
		}
		break;
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* p = (cPet*)m_pIndex;
			SAFE_DELETE(p);
			m_pIndex = 0;
		}
		break;
	case INDEXTYEP_NPC:
		if (1)
		{
			cNpc* p = (cNpc*)m_pIndex;
			SAFE_DELETE(p);
			m_pIndex = 0;
		}
		break;
	default:
		break;
	}
	m_IndexType = 0;
}



bool cObj::SetMagicEffectFromItem(cWasFile* MagicEffect, int Pos, int Speed)
{
	// 用的都是-10, 都是useItem
	if (!MagicEffect)return false;
	m_MagicEffect.Set(MagicEffect);
	m_MagicEffect.m_NeedShow = true;

	m_MagicEffect.m_FrameGap = Speed;


	m_MagicEffect.SetX(GetX());

#if 1
	m_MagicEffect.SetY(GetY());
#else
	if (Pos == 10)
	{
		m_MagicEffect.SetY(GetTopY());
		////////////////////////////////////////////////////////////////////////// 呵呵哒 动画总是有点偏上
		//		m_MagicEffect.SetY((GetY() + GetTopY()) / 2);
		m_MagicEffect.SetY(GetY() - 105);
	}
	else
		if (Pos == -10)
		{
		m_MagicEffect.SetY(GetY());
		}
		else
		{
			//		m_MagicEffect.SetY((GetY() + GetTopY()) / 2 - 30 * m_MagicSufferPos);
			m_MagicSuffer.SetY(GetY() - 40 - 30 * m_MagicSufferPos);
		}
#endif

	return true;
}



// bool cObj::CanEquip(int Equiptype, int lv, int Pos)
// {
// 
// 	if (m_IndexType == INDEXTYEP_CHARACTER)
// 	{
// 		cCharacter* pC = (cCharacter*)m_pIndex;
// 		return pC->CanEquip(Equiptype, lv, Pos);
// 	}
// 	else
// 	{
// 		//还没写
// 		ERRBOX;
// 	}
// 	return false;
// }

const sFightPoint* cObj::GetFightPoint()
{
	switch (m_IndexType)
	{
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* p = (cCharacter*)m_pIndex;
			return p->GetFightPoint();
		}
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* p = (cPet*)m_pIndex;
			return p->GetFightPoint();
		}
	default:
		break;
	}
	return 0;
}

bool cObj::Shake()
{
	if (!m_bShake && !m_bShakeFor抖动)return true;

	if (m_bShaketime < 6)
		SetX(GetX() - 1);
	else
		SetX(GetX() + 1);

	m_bShaketime += 1;
	m_bShaketime %= 12;
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_bMove = true;
	}
	return true;
}

void cObj::SetDirection(int direction)
{
	m_direction = direction;
	for (int i = 0; i < 8; i++)
		m_data[i].SetDirection(direction);

}

bool cObj::SetShadow(int iShadow)
{
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_Picture.m_bShadow = iShadow;
	}
	return true;
}

bool cObj::SetTwinkle(bool b)
{
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_Picture.m_bTwinkle = b;
	}
	return true;
}

// INT64* cObj::GetExp()
// {
// 	cPropertyData* p;
// 	GetPropertyData(p);
// 	if (p)return &p->m_EXP;
// 	ERRBOX;
// 	return 0;
// }
// 
// INT64* cObj::GetExpMax()
// {
// 	cPropertyData* p;
// 	GetPropertyData(p);
// 	if (p)return &p->m_ExpTotal;
// 	ERRBOX;
// 	return 0;
// }

bool cObj::SetGhost(bool b)
{
	m_bGhost = b;
	if (b)
	{
		for (int i = 0; i < 3; i++)
		{
			m_Ghost[i][0].Set(m_pShowData[i]);
			m_Ghost[i][1].Set(m_pShowData[i]);
		}

		for (int j = 0; j < 3; j++)
			for (int i = 0; i < 2; i++)
			{
			m_Ghost[j][i].m_x = (int)m_xPos;
			m_Ghost[j][i].m_y = (int)m_yPos;
			m_Ghost[j][i].m_direction = m_direction;
			}
	}
	return true;
}

std::string cObj::GetName()
{
	switch (m_IndexType)
	{
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* p = (cPet*)m_pIndex;
			return p->GetData()->m_Name;
		}
		break;
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* p = (cCharacter*)m_pIndex;
			return p->GetData()->m_Name;
		}
		break;
	default:
		ERRBOX;
		break;
	}
	return 0;
}

int cObj::GetModeID()
{
	switch (m_IndexType)
	{
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* p = (cPet*)m_pIndex;
			return p->GetData()->m_ID;
		}
		break;
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* p = (cCharacter*)m_pIndex;
			return p->GetData()->m_ID + 2000;
		}
		break;
	case INDEXTYEP_NPC:
		if (1)
		{
			cNpc* p = (cNpc*)m_pIndex;
			return p->m_pNpcData->m_ModeId;
		}
		break;
	default:
		ERRBOX;
		break;
	}
	return 0;
}

// bool cObj::AddZZ(int num, PropertyType typpe)
// {
// 	cPropertyData* pData = 0;
// 
// 	switch (m_IndexType)
// 	{
// 	case INDEXTYEP_CHARACTER:
// 		if (1)
// 		{
// 			cCharacter* p = (cCharacter*)m_pIndex;
// 			pData = (&p->m_PcData);
// 		}
// 		break;
// 	case INDEXTYEP_PET:
// 		if (1)
// 		{
// 			cPet* p = (cPet*)m_pIndex;
// 			pData = &p->m_PetData;
// 		}
// 		break;
// 	default:
// 		ERRBOX;
// 		return false;
// 	}
// 	switch (typpe)
// 	{
// 	case	typeAtkZZ:pData->AddAtkZZ(num); break;
// 	case	typeDefZZ:pData->AddDefZZ(num); break;
// 	case	typeHPZZ:pData->AddHpZZ(num); break;
// 	case	typeMagZZ:pData->AddMagZZ(num); break;
// 	case	typeSpdZZ:pData->AddSpdZZ(num); break;
// 	case	typeAvoidZZ:pData->AddAvoidZZ(num); break;
// 	}
// 	return true;
// }

void cObj::SetX(int x)
{
	if (((int)m_xPos) == x)return;
	m_xPos = (float)x;
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_Picture.m_x = x;
		m_data[i].m_bMove = true;
	}
	m_MagicEffect.m_x = (int)m_xPos;
	m_MagicEffect.m_bMove = true;


	if (m_bNeedShowName)
	{
		MoveName();
	}

}
void cObj::SetY(int y)
{
	if ((int)m_yPos == y)return;
	if (!g_pMainState)
	{
		ERRBOX;
		return;
	}
	m_yPos = (float)y;
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_Picture.m_y = y;
		m_data[i].m_bMove = true;
	}

	m_MagicEffect.m_y = (int)m_yPos;
	m_MagicEffect.m_bMove = true;
	if (m_bNeedShowName)
	{
		//显示名字			
		MoveName();
	}
}

void cObj::SetPos(float x, float y)
{
	if (!g_pMainState)
	{
		MessageBoxA(0, "ERR", "SetX", MB_OK);
		return;
	}
	if (m_xPos == x&&m_yPos == y)return;
	m_xPos = x;
	m_yPos = y;
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_Picture.m_x = (int)x;
		m_data[i].m_Picture.m_y = (int)y;
		m_data[i].m_bMove = true;
	}
	m_MagicEffect.m_x = (int)m_xPos;
	m_MagicEffect.m_y = (int)m_yPos;
	m_MagicEffect.m_bMove = true;
	MoveShadow();
	if (m_bNeedShowName)
	{
		//显示名字			
		MoveName();
	}

}

int cObj::GetTopY()
{
	int y = GetY();
	int y1;
	for (int i = 0; i < 4; i++)
	{
		if (0 == m_pShowData[i]->m_NeedShow)
		{
			continue;
		}
		int a = m_pShowData[i]->m_Picture.getFrameIdx();
		y1 = GetY() - m_pShowData[i]->m_Picture.Spr.m_pDataOffsetList[a].FramY;
		if (y > y1)
		{
			y = y1;
		}
	}
	return y;
}
int cObj::GetTopY2()
{
	return GetY() - 80;
}
void cObj::Init()
{
	m_TaskTrigger.m_Stage = -1;
	m_Shadow.Set(&g_pMainState->m_Shadow);
	m_FaceTextBackp.resize(2);
	for (int i = 0; i < 2; i++)
	{
		m_FaceTextBackp[i].Set(&g_pMainState->m_FaceTextBack);
		m_FaceTextBackp[i].m_bShadow = 60;
	};
	m_HpLinep.Set(&g_pMainState->m_HpLine);
	m_HpEmptyLinep.Set(&g_pMainState->m_HpEmptyLine);
	m_HpLinep.m_bStatic = true;
	m_HpEmptyLinep.m_bStatic = true;



	m_TrueName.m_hFont = g_pMainState->m_hFont[0];
	m_Name称谓.m_hFont = g_pMainState->m_hFont[0];

	m_TrueName.m_bShowOnScreen = false;
	m_Name称谓.m_bShowOnScreen = false;
	m_TrueName.SetStyle(1);
	m_Name称谓.SetStyle(1);

	m_ConductFire.m_hFont = g_pMainState->m_hFont[5];
	m_ConductSeal.m_hFont = g_pMainState->m_hFont[5];
	m_ConductFire.SetStyle(1);
	m_ConductSeal.SetStyle(1);
	m_ConductFire.m_NeedShow = false;
	m_ConductSeal.m_NeedShow = false;

	m_ConductFire.SetColor(RGB(0xFF, 0xFF, 0));
	m_ConductFire.SetBackColor(RGB(0, 0, 0));
	m_ConductFire.SetString("集火");

	m_ConductSeal.SetColor(RGB(0xFF, 0xFF, 0));
	m_ConductSeal.SetBackColor(RGB(0, 0, 0));
	m_ConductSeal.SetString("封印");



	m_bGhost = false;
	for (int i = 0; i < 3; i++)
	{
		m_Ghost[i][0].m_bStatic = true;
		m_Ghost[i][1].m_bStatic = true;
		m_Ghost[i][0].m_bShadow = 60;
		m_Ghost[i][1].m_bShadow = 60;
	}
}

void cObj::MoveDialog()
{
	if (0 == m_ShowTime)return;
	int xscr = m_Shadow.GetX() - g_pMainState->m_FaceTextBack.GetWidth() / 2;
	int top = GetTopY2();
	int ystart = GetTopY2() - m_ContextList.m_Height;
	if (g_StateType == STATE_MAIN)
	{
		xscr -= g_pMainState->m_Map.m_pMap->GetXCenter() - g_half320;
		ystart -= g_pMainState->m_Map.m_pMap->GetYCenter() - g_half240;
	}
	for (int i = 0; i < 2; i++)
		m_FaceTextBackp[i].SetX(xscr);


	int maxheitht = m_FaceTextBackp[0].m_pFile->GetHeight();
	m_ContextList.SetPos(xscr + 3, ystart);
	int ystartback = ystart; //最高点
	int HeightContext = m_ContextList.m_Height + 5;

	m_FaceTextBackp[0].SetyOffset(maxheitht - HeightContext / 2);
	if (m_FaceTextBackp[0].GetyOffset() < 30)m_FaceTextBackp[0].SetyOffset(30);
	m_FaceTextBackp[0].SetY(ystartback);

	m_FaceTextBackp[1].SetyOffset2(maxheitht - (HeightContext - m_FaceTextBackp[0].GetShowHeight()));
	m_FaceTextBackp[1].SetyOffset(m_FaceTextBackp[1].GetyOffset2());

	m_FaceTextBackp[1].SetY(ystartback + m_FaceTextBackp[0].GetShowHeight());
	m_FaceTextBackp[0].m_bMove = true;
	m_FaceTextBackp[1].m_bMove = true;
}

void cObj::MoveName()
{
	//显示名字			
	int l = GetX() - m_TrueName.m_Width / 2;
	int t = GetY() + 10;
	int t1 = GetY() - 30;
	int l2 = GetX() - 12;
	if (g_StateType != STATE_FIGHT)
	{
		t += 18;
	}
	if (l == m_TrueName.GetX() && t == m_TrueName.GetY())return;
	m_TrueName.SetXY(l, t);
	m_TrueName.m_bMove = true;

	m_Name称谓.SetXY(GetX() - m_Name称谓.m_Width / 2, t - 18);
	m_Name称谓.m_bMove = true;

	m_ConductFire.SetXY(l2, t1);
	m_ConductFire.m_bMove = true;
	m_ConductSeal.SetXY(l2, t1 + 14);
	m_ConductSeal.m_bMove = true;
}

void cObj::MoveHpLine()
{
	if (!m_HpEmptyLinep.m_pFile)return;
	m_HpEmptyLinep.m_x = GetX() - m_HpEmptyLinep.m_pFile->GetWidth() / 2;//m_HpEmptyLinep.m_pFile->GetWidth()/2;
	m_HpEmptyLinep.m_y = GetTopY() - 8;
	////////////////////////////////////////////////////////////////////////// 呵呵哒 血条位置
//	m_HpEmptyLinep.m_y = GetY() - 105;

	m_HpLinep.m_x = m_HpEmptyLinep.m_x + 1;
	if (m_HpEmptyLinep.m_y < 0)	m_HpEmptyLinep.m_y = 0;
	m_HpLinep.m_y = m_HpEmptyLinep.m_y + 1;

	m_HpEmptyLinep.m_bMove = true;
}

void cObj::UpdateHpLine()
{
	cPropertyData* pTargetdata;
	GetPropertyData(pTargetdata);
	int percent;
	int hpMax = pTargetdata->HPMax.GetData();
	int& hpnow = pTargetdata->m_HP;
	if (hpMax)
		percent = (hpnow * 36) / hpMax;
	else
		percent = 0;
	if (m_HpLinep.GetxOffset() != 36 - percent)
	{
		if (0 == percent)percent = 1;
		m_HpLinep.SetxOffset(36 - percent);
		m_HpLinep.m_bMove = true;
	}
}

void cObj::GetPropertyData(cPropertyData*& p)
{
	switch (m_IndexType)
	{
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* ppc = (cCharacter*)m_pIndex;
			p = (cPropertyData*)&ppc->m_PcData;
		}
		break;
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* ppet = (cPet*)m_pIndex;
			p = (cPropertyData*)&ppet->m_PetData;
		}
		break;
	default:
		p = 0;
		break;
	}
}

cPetData* cObj::getPetData()
{
	switch (m_IndexType)
	{
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* ppet = (cPet*)m_pIndex;
			return &ppet->m_PetData;
		}
	}
	return nullptr;
}

cPcData* cObj::getPcData()
{
	switch (m_IndexType)
	{
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* ppc = (cCharacter*)m_pIndex;
			return &ppc->m_PcData;
		}
	}
	return nullptr;
}



void cObj::SetSound(int POS_X, bool bPlay)
{
	ulong id = GetSound(POS_X);
	if (!id)return;
	switch (POS_X)
	{
	case POS_SUFFER:
	case POS_SOUNDSUFFER:
		m_WavSuffer.LoadWav(id, 0, bPlay);
		break;
	case POS_ATTACK:
	case POS_SOUNDATTACK:
		m_WavAtk.LoadWav(id, 0, bPlay);
		break;
	case POS_ATTACK2:
	case POS_SOUNDATTACK2:
		m_WavAtk2.LoadWav(id, 0, bPlay);
		break;
	case POS_DEF:
	case POS_SOUNDDEF:
		m_WavDef.LoadWav(id, 0, bPlay);
		break;
	default:
		m_Wav.LoadWav(id, 0, bPlay);
		break;
	}


}
void cObj::PlayWav(int POS_X)
{
	switch (POS_X)
	{
	case POS_SUFFER:
		m_WavSuffer.PlayWav();
		break;
	case POS_ATTACK:
		m_WavAtk.PlayWav();
		break;
	case POS_ATTACK2:
		m_WavAtk2.PlayWav();
		break;
	case POS_DEF:
		m_WavDef.PlayWav();
		break;
	default:
		m_Wav.PlayWav();
		break;
	}
}

void cObj::SetMagicSound(int SkillID, int position)
{
	if (SkillID == -1)
	{
		m_MagicWav.Free();
		return;
	}
	sSkill* pSkill = g_pMainState->m_SkillManager.GetSkill(SkillID);
	if (!pSkill)return;
	ulong id = pSkill->m_Sound;
	if (id)
	{
		m_MagicWav.LoadWav(id, position);
	}
}

ulong cObj::GetSound(int POS)
{
	int  soundpos = POS;
	switch (POS)
	{
	case POS_ATTACK:soundpos = POS_SOUNDATTACK; break;
	case POS_DEAD:	soundpos = POS_SOUNDDEAD;		break;
	case POS_DEF:	soundpos = POS_SOUNDDEF;			break;
	case POS_ATTACK2:soundpos = POS_SOUNDATTACK2;	break;
	case POS_MAGIC:	soundpos = POS_SOUNDMAGIC;		break;
	case POS_SUFFER:soundpos = POS_SOUNDSUFFER; break;
	case POS_SOUNDATTACK:
	case POS_SOUNDDEAD:
	case POS_SOUNDDEF:
	case POS_SOUNDATTACK2:
	case POS_SOUNDMAGIC:
	case POS_SOUNDSUFFER:
		break;
	default:
		return 0;
	}
	return GetID(soundpos);
}

void cObj::SetSpeed(int k)
{
	for (int i = 0; i < 6; i++)
		m_data[i].m_Picture.m_FrameGap = k;
}

bool cObj::SetMagiSufferID(ulong MagicID, int MagicPos, cWasFile* pFile, bool up)
{
	if (!MagicID)
	{
		m_MagicSuffer.m_NeedShow = false;
		return true;
	}
	m_MagicSufferPos = MagicPos;
	m_bMagicSufferUp = up;
	if (!pFile)ERRBOX;
	if (pFile->m_NowID == MagicID)
	{
		//如果是同一图像
		pFile->m_Picture.SetFrame帧(0);
	}
	pFile->Load(MagicID);
	m_MagicSuffer.Set(pFile);
	m_MagicSuffer.m_NeedShow = true;
	MoveMagicSufferID();
	return true;
}

void cObj::MoveMagicSufferID()
{
	if (!m_MagicSuffer.m_NeedShow)return;
	m_MagicSuffer.SetX(GetX());

	if (m_MagicSufferPos == 10)
	{
		m_MagicSuffer.SetY(GetTopY() - 20);
//		m_MagicSuffer.SetY((GetY() + GetTopY()) / 2);
//		m_MagicSuffer.SetY(GetY() - 105);
	}
	else if (m_MagicSufferPos == -10)
	{
		m_MagicSuffer.SetY(GetY());
	}
	else if (m_MagicSufferPos == 0)
	{
		m_MagicSuffer.SetY((GetY() + GetTopY()) / 2);
	}
	else 
	{
//		m_MagicSuffer.SetY((GetY() + GetTopY()) / 2 - 10 * m_MagicSufferPos);
		m_MagicSuffer.SetY(GetY() - 10 * m_MagicSufferPos);
	}
}

bool cObj::SetMagicCri(cWasFile* pFile)
{
	if (!pFile)return false;
	if (pFile->m_NowID == 0xDAD8AC20)
	{
		//如果是同一图像
		pFile->m_Picture.SetFrame帧(0);
	}
	pFile->Load(0xDAD8AC20);
	m_MagicCri.Set(pFile);
	m_MagicCri.m_NeedShow = true;
	MoveMagicCri();
	return true;
}

void cObj::MoveMagicCri()
{
	if (m_MagicCri.m_NeedShow)
	{
		m_MagicCri.SetX(GetX());
		m_MagicCri.SetY((GetY() + GetTopY()) / 2);
	}
}

void cObj::showMagicCri(cCanvas* pCanvas)
{
	if (m_MagicCri.m_NeedShow)
	{
		pCanvas->Add(&m_MagicCri, 1);
		if (m_MagicCri.now_frame == m_MagicCri.m_pFile->GetMaxFrame() - 2)
		{
			m_MagicCri.m_NeedShow = false;
		}
	}
}

void cObj::MoveMagicSuffer()
{
	for (list<sBuff>::iterator it = m_StateList.begin(); it != m_StateList.end(); it++)
	{
		if (it->MagicID)
		{
			it->data.SetX(GetX());
			if (it->bufPos == 10)
			{
				it->data.SetY(GetTopY() - 20);
			}
			else if (it->bufPos == -10)
			{
				it->data.SetY(GetY());
			}
			else if (it->bufPos == 0)
			{
				it->data.SetY((GetY() + GetTopY()) / 2);
			}
			else
			{
				it->data.SetY(GetY() - 10 * (it->bufPos));
			}
		}
	}
}

int cObj::GetSkillLv(int skillid)
{
	if (m_IndexType == INDEXTYEP_CHARACTER)
	{
		cCharacter* p = (cCharacter*)m_pIndex;
		return p->GetSkillLv(skillid, &g_pMainState->m_SkillManager);
	}
	else if (m_IndexType == INDEXTYEP_PET)
	{
		cPet* p = (cPet*)m_pIndex;
		return p->m_PetData.m_Lv;
	}
	return 0;
}

void cObj::SetXY(int x, int y)
{
	if (GetX() == x&&GetY() == y)return;
	m_xPos = (float)x;
	m_yPos = (float)y;
	for (int i = 0; i < 8; i++)
	{
		m_data[i].m_Picture.SetXY(x, y);
		m_data[i].m_bMove = true;
	}
	m_MagicEffect.SetXY(GetX(), GetY());
	m_MagicEffect.m_bMove = true;

	if (m_bNeedShowName)
	{
		MoveName();
	}
}

void cObj::AutoData(int modeid, sItem2* pWeapon /* = 0 */, int petid /* = -1 */, string name /* = "" */)
{
	SetDataType(INDEXTYEP_CHARACTER);
	cCharacter* pc = (cCharacter*)m_pIndex;
	pc->SetData(&g_pMainState->m_pCharacterDataList[cct::getModel(modeid)]);
	if (name.empty())
	{
		name = pc->GetData()->m_Name;
	}

	m_TrueName.SetColor(RGB(0, 255, 0));
	m_TrueName.SetBackColor(RGB(0, 0, 0));
	m_TrueName.SetString(name);
	
	m_Name称谓.SetColor(RGB(0, 128, 255));
	m_Name称谓.SetBackColor(RGB(0, 0, 0));
	m_Name称谓.SetString(name);

	if (petid >= 0)
	{
		pc->UseCard(petid);
	}
	else if (pWeapon)
	{
		pc->m_PcData.m_Equips[2].Set(pWeapon->GetType(), pWeapon->GetID(), false);
		pc->m_PcData.m_pCharacterData2 = 0;
	}
	pc->m_PcData.m_Controler.Set();
}

void cObj::AutoData(int modeid, string name /* = "" */)
{
	SetDataType(INDEXTYEP_PET);
	cPet* p = (cPet*)m_pIndex;
	p->SetData(g_pMainState->m_PetDataManager.GetPetData(cct::getModel(modeid)));
	if (name.empty())
	{
		name = p->GetData()->m_Name;
	}
	m_TrueName.SetColor(RGB(0, 255, 0));
	m_TrueName.SetBackColor(RGB(0, 0, 0));
	m_TrueName.SetString(name);

// 	m_Name称谓.SetColor(RGB(0, 128, 255));
// 	m_Name称谓.SetBackColor(RGB(0, 0, 0));
// 	m_Name称谓.SetString(name);

	p->m_PetData.m_Controler.Set();
}

// void cObj::ResetIndex()
// {
// 	switch (m_IndexType)
// 	{
// 	case INDEXTYEP_CHARACTER:
// 		if (1)
// 		{
// 			cCharacter* pc = (cCharacter*)m_pIndex;
// 			pc->m_PcData.Reset();
// 		}
// 		break;
// 	case INDEXTYEP_PET:
// 		if (1)
// 		{
// 			cPet* pet = (cPet*)m_pIndex;
// 			pet->m_PetData.Reset();
// 		}
// 		break;
// 	default:
// 		break;
// 	}
// }

void cObj::Talk(string context, bool needret)
{
	if (g_pMainState->m_TriggerDialog.m_datalist[0].m_Nowtext > -1)
	{
		//先把对话链取消
		g_pMainState->m_Dialog.Close();
	}
	g_pMainState->m_Dialog.Reset();
	g_pMainState->m_Dialog.SetObj(this);
	if (!needret)
		g_pMainState->m_Dialog.m_pObj = 0;
	g_pMainState->m_Dialog.SetString(context);
	g_pMainState->m_Dialog.OnOff(true);
}

void cObj::Talk(string context, cTaskFather* pTask, int stage, string select1 /*= ""*/, string select2 /*= ""*/, string select3 /*= ""*/, string select4 /*= ""*/)
{
	g_pMainState->m_Dialog.Reset();
	g_pMainState->m_Dialog.SetObj(this);
	g_pMainState->m_Dialog.SetString(context, select1, select2, select3, select4);
	g_pMainState->m_Dialog.SetTrigger(pTask, stage, stage, stage, stage);
	g_pMainState->m_Dialog.OnOff(true);
}
void cObj::Answer(cTaskFather* pTask, int stage)
{
	g_pMainState->m_Dialog.Reset();
	g_pMainState->m_Dialog.SetObj(this);
	g_pMainState->m_Dialog.Question();
	g_pMainState->m_Dialog.SetTrigger(pTask, stage, stage, stage, stage);
	g_pMainState->m_Dialog.OnOff(true);
}



void cObj::saySkill(string text, int time /* = 180 */)
{
	m_ContextList.SetFaceText("   " + text, g_pMainState->m_hFont[0], 114);
	m_ShowTime = time;
	MoveDialog();
}


void cObj::say(string text, int time /* = 0x8FF */)
{
	m_ContextList.SetFaceText(text, g_pMainState->m_hFont[0], 114);
	m_ShowTime = time;
	MoveDialog();
}


void cObj::MoveShadow()
{
	m_Shadow.SetXY((int)m_xPos, (int)m_yPos);
	m_Foot.SetXY((int)m_xPos, (int)m_yPos);
}

bool cObj::CheckHaveState(int skillid)
{
	for (list<sBuff>::iterator it = m_StateList.begin(); it != m_StateList.end(); it++)
	{
		if (it->ID == skillid)
			return true;
	}
	return false;
}

void cObj::Move2()
{
	MoveHpLine();
	MoveDialog();
	MoveMagicSuffer();
	MoveMagicSufferID();
	MoveShadow();
}

void cObj::Reset()
{ //删除角色的动作
	m_NowPos = -1;
	m_PrePos = -1;
	for (int i = 0; i < 8; i++)
	{
		m_data[i].Free();
	}
}



void cObj::SetFrame(int fram)
{
	for (int i = 0; i < 3; i++)
	{
		if (m_pShowData[i]->m_NeedShow)
			m_pShowData[i]->SetFrame(fram);

	}
}

// 
// sNameSexRace* cObj::GetObjFather()
// {
// 	sNameSexRace* p;
// 	switch (m_IndexType)
// 	{
// 	case INDEXTYEP_PET:
// 		if (1)
// 		{
// 			cPet* pet = (cPet*)m_pIndex;
// 			p = pet->GetData();
// 			return p;
// 		}
// 		break;
// 	case INDEXTYEP_CHARACTER:
// 		if (1)
// 		{
// 			cCharacter* pet = (cCharacter*)m_pIndex;
// 			p = pet->GetData();
// 			return p;
// 		}
// 		break;
// 	}
// 	return 0;
// }
// 
// bool cObj::GetSex()
// {
// 	return GetObjFather()->m_bSex;
// }

void cObj::SetShow(bool Needshow)
{
	m_NeedShowShadow = Needshow;
}

bool cObj::GetShow()
{
	return m_NeedShowShadow;
}


//  void cObj::FollowLvForObj(int lv)
// {
// 	switch (m_IndexType)
// 	{
// 	case INDEXTYEP_CHARACTER:
// 		if (1)
// 		{
// 			cCharacter* pc = (cCharacter*)m_pIndex;
// 			pc->m_PCData.Followlv(lv, true, true, true);
// 		}
// 		break;
// 	case INDEXTYEP_PET:
// 		if (1)
// 		{
// 			cPet* pet = (cPet*)m_pIndex;
// 			pet->m_PetDataZZ.Followlv(lv, true, true, true);
// 		}
// 		break;
// 	default:
// 		ERRBOX;
// 		break;
// 	}
// }

void cObj::SetShake(bool shake)
{
	m_bShake = shake;
}

void cObj::SetShakeFor抖动(bool shake)
{
	m_bShakeFor抖动 = shake;
}

void cObj::AutoFightDirection(int id)
{
	if (id < 10)
		SetDirection(7);
	else
		SetDirection(3);
}

void cObj::SetWeapon强制换模型_不动数据_可能未鉴定(int type, int id)
{
	if (m_IndexType == INDEXTYEP_CHARACTER)
	{
		cCharacter* pc = (cCharacter*)m_pIndex;
		pc->m_PcData.m_Equips[2].Set(type, id, false);
		pc->m_PcData.m_Equips[2].m_Num = 1;
		pc->m_PcData.m_pCharacterData2 = 0;
	}
}

// void cObj::LoadCharacter(string name, string path)
// {
// 	SetDataType(INDEXTYEP_CHARACTER);
// 	cCharacter* pc = (cCharacter*)m_pIndex;
// 	cPcData& pcd = pc->m_PcData;
// 	pcd.Read(name, path);
// 
// 	pc->SetData(&g_pMainState->m_pCharacterDataList[pc->m_PcData.modeid]);
// 	m_TrueName.SetColor(RGB(0, 255, 0));
// 	m_TrueName.SetString(pc->m_PcData.m_Name);
// }

