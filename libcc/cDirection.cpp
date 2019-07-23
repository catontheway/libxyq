#include "cDirection.h"
#include <vector>

int cDirection::getDirection4(const  cocos2d::Vec2& v)
{
	// 注意不是笛卡尔坐标系
	if (v.x < 0)
	{
		if (v.y < 0)
		{
			return  eDirection::LU;
		}
		else
		{
			return eDirection::LD;
		}
	}
	else
	{
		if (v.y < 0)
		{
			return  eDirection::RU;
		}
		else
		{
			return eDirection::RD;
		}
	}
	return 0;
}


int cDirection::getDirection4(int direction8)
{
	switch (direction8)
	{
	case eDirection::D: return eDirection::LD;
	case eDirection::L: return eDirection::RD;
//    case 5: return eDirection::RU;
	case eDirection::R: return eDirection::RD;
	case eDirection::U: return eDirection::LU;
	}
	return 0;
}



int cDirection::getDirection8(int pred, const  cocos2d::Vec2& v)
{
	float a = atan2(v.y, v.x);

	if (a > 0)
	{
		if (a < 0.2618)
		{
			return eDirection::R;
		}
		else
		{
			if (a < 0.5236)
			{
				if (pred == eDirection::R || pred == eDirection::RD)
				{
					return pred;
				}
				else
				{
					if (a < 0.3927)
					{
						return eDirection::R;
					}
					else
					{
						return eDirection::RD;
					}
				}
			}
			else if (a < 1.0472)
			{
				return eDirection::RD;
			}
			else if (a < 1.3089)
			{
				if (pred == eDirection::D || pred == eDirection::RD)
				{
					return pred;
				}
				else
				{
					if (a < 1.178)
					{
						return eDirection::R;
					}
					else
					{
						return eDirection::RD;
					}
				}
			}
			else if (a < 1.8326)
			{
				return eDirection::D;
			}
			else if (a < 2.0944)
			{
				if (pred == eDirection::D || pred == eDirection::LD)
				{
					return pred;
				}
				else
				{
					if (a < 1.9635)
					{
						return eDirection::D;
					}
					else
					{
						return eDirection::LD;
					}
				}
			}
			else if (a < 2.618)
			{
				return eDirection::LD;
			}
			else  if (a < 2.8798)
			{
				if (pred == eDirection::L || pred == eDirection::LD)
				{
					return pred;
				}
				else
				{
					if (a < 2.7489)
					{
						return eDirection::LD;
					}
					else
					{
						return eDirection::L;
					}
				}
			}
			else
			{
				return eDirection::L;
			}
		}
	}
	else
	{   // left
		if (a > -0.2618)
		{
			return eDirection::R;
		}
		else
		{
			if (a > -0.5236)
			{
				if (pred == eDirection::R || pred == eDirection::RU)
				{
					return pred;
				}
				else
				{
					if (a > -0.3927)
					{
						return eDirection::R;
					}
					else
					{
						return eDirection::RU;
					}
				}
			}
			else if (a > -1.0472)
			{
				return eDirection::RU;
			}
			else if (a > -1.3089)
			{
				if (pred == eDirection::RU || pred == eDirection::U)
				{
					return pred;
				}
				else
				{
					if (a > -1.178)
					{
						return eDirection::RU;
					}
					else
					{
						return eDirection::U;
					}
				}
			}
			else if (a > -1.8326)
			{
				return eDirection::U;
			}
			else if (a > -2.0944)
			{
				if (pred == eDirection::U || pred == eDirection::LU)
				{
				}
				else
				{
					if (a > -1.9635)
					{
						return eDirection::U;
					}
					else
					{
						return eDirection::LU;
					}
				}
			}
			else if (a > -2.618)
			{
				return eDirection::LU;
			}
			else  if (a > -2.8798)
			{
				if (pred == eDirection::LU || pred == eDirection::L)
				{
					return pred;
				}
				else
				{
					if (a > -2.7489)
					{
						return eDirection::LU;
					}
					else
					{
						return eDirection::L;
					}
				}
			}
			else
			{
				return eDirection::L;
			}
		}
	}
	return pred;

	a = v.getAngle();
	a = /*CC_RADIANS_TO_DEGREES(a)*/(a * 57.29577951f) + 180;
	a = std::min(359, (int)a);
	static std::vector<int> s_directionRs =
	{
		eDirection::L, eDirection::LU, eDirection::U, eDirection::RU,
		eDirection::R, eDirection::RD, eDirection::D, eDirection::LD,
	};
	return s_directionRs[a / 45];
}


int cDirection::getDirectionR(int direction)
{
	switch (direction)
	{
	case eDirection::LD:
		return eDirection::RU;
	case eDirection::RD:
		return eDirection::LU;
	case eDirection::LU:
		return eDirection::RD;
	case eDirection::RU:
		return eDirection::LD;
	case eDirection::D:
		return eDirection::U;
	case eDirection::L:
		return eDirection::R;
	case eDirection::U:
		return eDirection::D;
	case eDirection::R:
		return eDirection::L;
	}
	return 0;
}


int cDirection::getDirectionRound8(int directionLast, bool isNextOrPre)
{
	static std::vector<int> s_directions =
	{
		eDirection::U, eDirection::RU, eDirection::R, eDirection::RD,
		eDirection::D, eDirection::LD, eDirection::L, eDirection::LU,
	};
	int idx = -1;
	for (int k = s_directions.size() - 1; k >= 0; --k)
	{
		if (s_directions[k] == directionLast)
		{
			idx = k;
			break;
		}
	}
	if (idx == -1)
	{
		return 0;
	}

	static int size = s_directions.size();
	if (isNextOrPre)
	{
		if ((++idx == size))
		{
			idx = 0;
		}
	}
	else if ((--idx) < 0)
	{
		idx = size - 1;
	}
	return s_directions[idx];
}



int cDirection::getDirectionRound4(int directionLast, bool isNextOrPre)
{
	static std::vector<int> s_directions =
	{
		eDirection::RU, eDirection::RD, eDirection::LD, eDirection::LU,
	};
	int idx = -1;
	for (int k = s_directions.size() - 1; k >= 0; --k)
	{
		if (s_directions[k] == directionLast)
		{
			idx = k;
			break;
		}
	}
	if (idx == -1)
	{
		return 0;
	}

	static int size = s_directions.size();
	if (isNextOrPre)
	{
		if ((++idx == size))
		{
			idx = 0;
		}
	}
	else if ((--idx) < 0)
	{
		idx = size - 1;
	}
	return s_directions[idx];
}

