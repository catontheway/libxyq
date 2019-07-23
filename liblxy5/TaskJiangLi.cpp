#include "_global.h"

void cTaskJiangLi::AutoGetJiangLi()
{
	if (!m_List.size())return;
	int rat = rand() % 100;
	if (rat < m_MoenyRate)
	{
		SetJiangLi(m_Moneytime, true, 100, 0, 0, 0);
		return;
	}
	rat -= m_MoenyRate;
	if (rat < m_ExpRate)
	{
		SetJiangLi(m_Exptime, true, 0, 0, 100);
		return;
	}
	rat -= m_ExpRate;
	for (int i = 0; i < m_List.size(); i++)
	{
		if (rat < m_List[i].m_Rate)
		{
			if (m_List[i].m_rand > 1)
			{
				switch (m_List[i].m_Type)
				{
				case 40://µÍÊÞ¾ö
					if (m_List[i].m_rand == 5)
					{
						SetJiangLiItem(g_pMainState->m_ItemManage.m_LShouJueList[rand() % 43], m_List[i].m_Type);
					}
					else //¸ßÊÞ¾ö
					{
						SetJiangLiItem(g_pMainState->m_ItemManage.m_HShouJueList[rand() % 43], m_List[i].m_Type);
					}
					break;
				default:
					SetJiangLiItem(m_List[i].m_Id + rand() % m_List[i].m_rand, m_List[i].m_Type);
					break;
				}

			}
			else
				SetJiangLiItem(m_List[i].m_Id, m_List[i].m_Type);
			return;
		}
		rat -= m_List[i].m_Rate;
	}

}

void cTaskJiangLi::Add(int id, int type, int rate, int ran/*=1*/)
{
	sJiangLiList list;
	list.m_Id = id;
	list.m_rand = ran;
	list.m_Rate = rate;
	list.m_Type = type;
	m_List.push_back(list);
}
