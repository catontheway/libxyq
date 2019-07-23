#include "_global.h"
#include "_txt.h"


bool cAI::runPoxueRuodianPosui3000()
{
	if (isAtkFromPoint(m_pUserData))
	{
		if (isCanSpec())
		{
			for (int skill : {3034, 3035, 3040})
			{
				if (Cost(m_UserID, skill))
				{
					auto ts = findTarget(skill);
					if (ts.size())
					{
						UseSkill(3034, ts);
						return true;
					}
				}
			}
		}
	}
	return false;
}


bool cAI::runUnSeal3000(bool isSelf)
{
	if (isCanSpec())
	{
		int k;
		auto ts = findTarget(3010, k);
		if (k > 0)
		{
			if (isSelf)
			{
				forv(ts, i)
				{
					if (ts[i] == m_UserID)
					{
						swap(ts[i], ts[0]);
						break;
					}
				}
			}
			bool is47 = Cost(m_UserID, 3047) && ts.front() == m_UserID;
			bool is10 = Cost(m_UserID, 3010);
			bool is11 = Cost(m_UserID, 3011);
			bool is12 = Cost(m_UserID, 3012);
			bool is13 = Cost(m_UserID, 3013);
			auto t2s = findOwners(m_UserID);
			if (k == 1 || !(is12 || is13))
			{
				if (is47)
				{
					UseSkill(3047, ts);
					return true;
				}
				if (is10)
				{
					UseSkill(3010, ts);
					return true;
				}
				if (is11)
				{
					UseSkill(3011, ts);
					return true;
				}
			}
			else
			{
				if (is13)
				{
					UseSkill(3013, t2s);
					return true;
				}
				if (is12)
				{
					UseSkill(3012, t2s);
					return true;
				}
				if (is47)
				{
					UseSkill(3047, ts);
					return true;
				}
				if (is10)
				{
					UseSkill(3010, ts);
					return true;
				}
				if (is11)
				{
					UseSkill(3011, ts);
					return true;
				}
			}
		}

	}
	return false;
}


bool cAI::runResurgence3000()
{
	if (!isCanSpec())
	{
		return false;
	}

	bool is08 = Cost(m_UserID, 3008);
	bool is09 = Cost(m_UserID, 3009);
	bool is48 = Cost(m_UserID, 3048);
	if (!is09 && !is08 && !is48)
	{
		return false;
	}
	auto ts = findTarget(3008);
	if (ts.empty())
	{
		return false;
	}
	if (ts.size() == 1 || !is48)
	{
		if (is09)
		{
			UseSkill(3009, ts);
			return true;
		}
		if (is08)
		{
			UseSkill(3008, ts);
			return true;
		}
	}

	if (is48)
	{
		UseSkill(3048, findOwners(m_UserID, eFindType::Relifeable));
		return true;
	}
	if (is09)
	{
		UseSkill(3009, ts);
		return true;
	}
	if (is08)
	{
		UseSkill(3008, ts);
		return true;
	}
	return false;
}


bool cAI::runCure3000()
{
	if (!isCanSpec())
	{
		return false;
	}
	int ss[] = { 3000, 3001, 3002, 3005, 3006, 3007 };
	vector<int> bs;

	bool isOk = false;
	for (int skill : ss)
	{
		bs.push_back(Cost(m_UserID, skill));
		if (bs.back())
		{
			isOk = true;
		}
	}
	if (!isOk)
	{
		return false;
	}



	auto ts = findOwners(m_UserID, eFindType::Hp30);
	if (ts.empty())
	{
		return false;
	}

	if (bs[3] || bs[4] && !(bs[0] || bs[1] || bs[2] || bs[5]))
	{
		if (std::find(ts.begin(), ts.end(), m_UserID) != ts.end())
		{
			for (int i = 4; i >= 3; --i)
			{
				if (bs[i])
				{
					UseSkill(ss[i], { m_UserID });
					return true;
				}
			}
		}
	}

	if (ts.size() <= 2 || !bs[5])
	{
		for (int i = 2; i >= 0; --i)
		{
			if (bs[i])
			{
				UseSkill(ss[i], ts);
				return true;
			}
		}
	}

	if (bs[5])
	{
		UseSkill(ss[5], findOthers(m_UserID));
		return true;
	}

	for (int i = 2; i >= 0; --i)
	{
		if (bs[i])
		{
			UseSkill(ss[i], ts);
			return true;
		}
	}

	return false;
}


bool cAI::RunLH()
{
	if (!isCanSpec())
	{
		return false;
	}

	auto ts = findOthers(m_UserID, eFindType::MpMag, 
	[&](int i)
	{
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag();
		SetUser(uOld);
		return b;
	});
	if (ts.size() < 2)
	{
		return false;
	}

	bool is24 = Cost(m_UserID, 3024);
	bool is25 = Cost(m_UserID, 3025);
	bool is47 = Cost(m_UserID, 3047);

	if (!is24 && !is25 && !is47)
	{
		return false;
	}

	if (is24 && !is25)
	{
		if (!isStateDMag(m_pUser))
		{
			UseSkill(3024, { m_UserID });
			return true;
		}
	}

	if (is47 && !is25)
	{
		if (!isStateDMag(m_pUser))
		{
			UseSkill(3047, { m_UserID });
			return true;
		}
	}

	if (is25)
	{
		ts = findOwners(m_UserID);
		if (ts.size() > 1)
		{
			UseSkill(3025, findOwners(m_UserID));
			return true;
		}
	}

	if (!isStateDMag(m_pUser))
	{
		if (is24)
		{
			UseSkill(3024, { m_UserID });
			return true;
		}
		if (is47)
		{
			UseSkill(3047, { m_UserID });
			return true;
		}
	}

	return false;
}

