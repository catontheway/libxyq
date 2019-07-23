#include "_global.h"
#include "_txt.h"

static ulong getPetShi(int zq, int pos)
{
	if (zq < 8)
	{
		return 0;
	}
	if (pos != POS_STAND && pos != POS_WALK)
	{
		return 0;
	}
	const auto& zqs = ctt::getZqs();
	if (zqs[zq].color)
	{
		return (pos == POS_STAND) ? zqs[zq].color : zqs[zq].color2;
	}
	return 0;
}

void sZuoQi2::GetID(int Pos, vector<ulong>& out, bool haveChar /*= true*/)
{
	int num = 1;
	if (haveChar)num += 1;
	if (m_ZhuangShi.GetNum())num += 1;
	out.resize(num);
	switch (Pos)
	{
	case POS_STAND:
		if (1)
		{
			out[0] = m_pZuoQi->nodeStand;
			if (haveChar)
			{
				out[1] = m_pZuoQi->CharStand[m_ownerID];
				if (m_ZhuangShi.GetNum())
				{
					out[2] = g_pMainState->m_ItemManage.m_ZuoQiZhuangShiList[m_ZhuangShi.GetID()].Stand[m_ownerID];
				}
				else
				{
					int uid = getPetShi(m_pZuoQi->ID, POS_STAND);
					if (uid)
					{
						out.push_back(uid);
					}
				}
					
			}
			else
			{
				if (m_ZhuangShi.GetNum())
				{
					out[1] = g_pMainState->m_ItemManage.m_ZuoQiZhuangShiList[m_ZhuangShi.GetID()].NodeStand;
				}
				else
				{
					int uid = getPetShi(m_pZuoQi->ID, POS_STAND);
					if (uid)
					{
						out.push_back(uid);
					}
				}
			}
		}
		return;
	case POS_WALK:
		if (1)
		{
			out[0] = m_pZuoQi->nodeWalk;
			if (haveChar)
			{
				out[1] = m_pZuoQi->CharWalk[m_ownerID];
				if (m_ZhuangShi.GetNum())
				{
					out[2] = g_pMainState->m_ItemManage.m_ZuoQiZhuangShiList[m_ZhuangShi.GetID()].Walk[m_ownerID];
				}
				else
				{
					int uid = getPetShi(m_pZuoQi->ID, POS_WALK);
					if (uid)
					{
						out.push_back(uid);
					}
				}

			}
			else
			{
				if (m_ZhuangShi.GetNum())
				{

					out[1] = g_pMainState->m_ItemManage.m_ZuoQiZhuangShiList[m_ZhuangShi.GetID()].NodeWalk;
				}
				else
				{
					int uid = getPetShi(m_pZuoQi->ID, POS_WALK);
					if (uid)
					{
						out.push_back(uid);
					}
				}
			}
		}
		return;
	default:
		break;
	}
	return;
}








