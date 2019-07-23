#include "sFormation.h"
#include "sPropertyInfo.h"
#include "_tostring.h"

sFormation::sFormation()
{

}

sFormation::sFormation(eFormation e_) :e(e_)
{
	std::vector<int> ixs{ 0, 1, -1, 2, -2 }, iys{ 0, -1, 1, -2, 2 };
	switch (e)
	{
// 	case normal:
// 		ixs = { 0, 1, -1, 2, -2 };
// 		ixs = { 0, -1, 1, -2, 2 };
// 		break;
	case land:
		ixs = { 0, -1, 1, -1, 1 };
		ixs = { 0, -1, -1, 1, 1 };
		break;
	case wind:
		ixs = { 0, 1, -1, 0, -2 };
		ixs = { 0, -1, 1, -2, 0 };
		break;
	case tiger:
		ixs = { 1, 1, -1, 1, -3 };
		ixs = { 1, -1, 1, -3, 1 };
		break;
	case dragon:
		ixs = { 0, 1, 1, -2, -1 };
		ixs = { 0, 1, -3, 0, -1 };
		break;
	case bird:
		ixs = { 0, 2, 0, 2, -2 };
		ixs = { 0, 0, 2, -2, 2 };
		break;
	case snake:
		ixs = { 0, -1, 1, -2, 1 };
		ixs = { 0, 1, -1, 0, 1 };
		break;
	case sky:
		ixs = { 1, 1, -1, 2, -2 };
		ixs = { 1, -1, 1, -2, 2 };
		break;
	case cloud:
		ixs = { 2, 1, -1, 2, -2 };
		ixs = { 2, -1, 1, -2, 2 };
		break;
	case thunder:
		ixs = { 1, 1, -1, -2, 0 };
		ixs = { 1, -1, 1, 0, -2 };
		break;
	case eagle:
		ixs = { 1, 1, -1, 0, 2 };
		ixs = { 1, -1, 1, 0, 2 };
		break;
	}
}


static std::string apply(sPropertyInfo* info, int3* speed, int dper, int d2per, int mper, int m2per, int sper)
{
	if (info != nullptr && speed != nullptr)
	{
		if (dper != 0)
		{
			info->damage.per.d1 += dper;
			info->damageMagic.per.d1 += dper;
		}
		if (d2per != 0)
		{
			info->damage.per.d2 += d2per;
			info->damageMagic.per.d2 += d2per;
		}
		if (mper != 0)
		{
			info->damageMagic.per.d1 += mper;
		}
		if (m2per != 0)
		{
			info->damageMagic.per.d2 += m2per;
		}
		if (sper != 0)
		{
			speed->per += sper;
		}
	}
	std::string str;
	if (dper != 0)
	{
		str += "伤害";
		str += ((dper > 0) ? "+" : "-");
		str += cpp::toString(std::abs(dper));
		str += "%,";
	}
	if (d2per != 0)
	{
		str += "防御";
		str += ((d2per > 0) ? "+" : "-");
		str += cpp::toString(std::abs(d2per));
		str += "%,";
	}
	if (mper != 0)
	{
		str += "法伤";
		str += ((mper > 0) ? "+" : "-");
		str += cpp::toString(std::abs(mper));
		str += "%,";
	}
	if (m2per != 0)
	{
		str += "法御";
		str += ((m2per > 0) ? "+" : "-");
		str += cpp::toString(std::abs(m2per));
		str += "%,";
	}
	if (sper != 0)
	{
		str += "速度";
		str += ((sper > 0) ? "+" : "-");
		str += cpp::toString(std::abs(sper));
		str += "%";
	}
	if (str.back() == ',')
	{
		str.pop_back();
	}
	return str;
}

std::string sFormation::apply(int idx, sPropertyInfo* info, int3* speed)
{
	if (e == normal || idx < 0 || idx >= c5)
	{
		return "";
	}

// 伤害%,防御%,速度%
#define ccc_formation_phy(_D_, _D2_, _S_)::apply(info, speed, (_D_), (_D2_), 0, 0, (_S_))
// 法伤%,法防%,速度%
#define ccc_formation_mag(_D_, _D2_, _S_)::apply(info, speed, 0, 0, (_D_), (_D2_), (_S_))
	if (e == sky)
	{
		return ccc_formation_phy(20, 0, -10);
	}
	if (e == bird)
	{
		return ccc_formation_phy(0, 0, 20);
	}
	switch (e)
	{
// 	case normal:
// 		break;
	case land:
		if (idx == 1)
		{
			return ccc_formation_phy(15, 0, 0);
		}
		if (idx == 4)
		{
			return ccc_formation_phy(0, 0, 10);
		}
		return ccc_formation_phy(0, 15, 0);
	case wind:
		if (idx == 0)
		{
			return ccc_formation_phy(20, 0, 0);
		}
		if (idx == 3 || idx == 4)
		{
			return ccc_formation_phy(0, 0, 10);
		}
		return ccc_formation_phy(10, 0, 0);
	case tiger:
		if (idx == 0)
		{
			return ccc_formation_phy(25, 0, 0);
		}
		if (idx == 1 || idx == 2)
		{
			return ccc_formation_phy(0, 10, 0);
		}
		return ccc_formation_phy(10, 0, 0);
	case dragon:
		if (idx == 0)
		{
			return ccc_formation_mag(0, 20, 0);
		}
		if (idx == 1)
		{
			return ccc_formation_phy(0, 20, 0);
		}
		if (idx == 2)
		{
			return ccc_formation_mag(30, 0, -30);
		}
		if (idx == 3)
		{
			return ccc_formation_phy(0, 0, 15);
		}
		return ccc_formation_phy(20, 0, 0);
// 	case bird:
// 		break;
	case snake:
		if (idx == 3 || idx == 4)
		{
			return ccc_formation_phy(10, 0, 0);
		}
		if (info != nullptr && speed != nullptr)
		{
			info->hitRateMagic.dper += 15;
		}
		return "法避+15%";
// 	case sky:
// 		break;
	case cloud:
		if (idx == 0)
		{
			return ccc_formation_phy(0, 40, -30);
		}
		if (idx == 1)
		{
			return ccc_formation_phy(0, 10, 0);
		}
		if (idx == 2)
		{
			return ccc_formation_phy(10, 0, 0);
		}
		return ccc_formation_phy(0, 10, 0);
	case thunder:
		if (idx == 3 || idx == 4)
		{
			return ccc_formation_phy(10, 0, 0);
		}
		if (info != nullptr && speed != nullptr)
		{
			info->damageFix.per.d1 += 20;
		}
		return "固伤+20%";
	case eagle:
		if (idx == 0)
		{
			return ccc_formation_phy(0, 10, 0);
		}
		if (idx == 1 || idx == 2)
		{
			return ccc_formation_phy(0, 0, 15);
		}
		if (idx == 3)
		{
			return ccc_formation_phy(15, 0, 0);
		}
		return ccc_formation_phy(10, 0, 0);
	}
#undef ccc_formation_phy
#undef ccc_formation_mag
	return "";
}



bool sFormation::apply(int idx, bool pet, bool enemy, int& x, int& y)
{
	return true;
}