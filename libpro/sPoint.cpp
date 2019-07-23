#include "sPoint.h"
#include "_inc.h"

sPoint::sPoint()
{
	reset();
}



bool sPoint::reset(int initPoint /* = 0 */)
{
	// 体力
	body = initPoint;
	// 魔力
	mag = initPoint;
	// 力量
	str = initPoint;
	// 耐力
	dex = initPoint;
	// 敏捷
	agi = initPoint;
	// 剩余
	remain = 0;
	return true;
}


int& sPoint::get(ePoint e)
{
//	int* p = nullptr;
	switch (e)
	{
	case ePoint::body:
		return body;
//		break;
	case ePoint::mag:
		return mag;
//		break;
	case ePoint::str:
		return str;
//		break;
	case ePoint::dex:
		return dex;
//		break;
	case ePoint::agi:
		return agi;
//		break;
//	default:
//		break;
	}
//	return p;
//	ccc_box(((int)e));
}


bool sPoint::check(int lv)const
{
	return body + mag + str + dex + agi + remain == (lv * 10);
}


bool sPoint::add(ePoint e, bool onlyCheck)
{
	if (remain <= 0)
	{
		return false;
	}
	if (onlyCheck)
	{
		return true;
	}
	int& p = get(e);
	++(p);
	--remain;
	return true;
}


bool sPoint::sub(ePoint e, bool onlyCheck)
{
	int& p = get(e);
// 	if (p == nullptr)
// 	{
// 		return false;
// 	}
	if ((p) <= 0)
	{
		return false;
	}
	if (onlyCheck)
	{
		return true;
	}
	--(p);
	++remain;
	return true;
}


void sPoint::lvup(int per /* = 1 */)
{
	body += per;
	mag += per;
	str += per;
	dex += per;
	agi += per;
	remain += 5 * per;
}

bool sPoint::lvdown(bool onlyCheck, int per /* = 1 */)
{
	if (body + mag + str + dex + agi + remain < (per * 10))
	{
		return false;
	}
	std::vector<int*> ps =
	{
		&body,
		&mag,
		&str,
		&dex,
		&agi
	};
	std::sort(ps.begin(), ps.end(), [](const int* a, const int* b){return (*a) < (*b); });
	if (*(ps.front()) < per)
	{
		return false;
	}
	if (onlyCheck)
	{
		return true;
	}
	body -= per;
	mag -= per;
	str -= per;
	dex -= per;
	agi -= per;

	per = per * 5;
	if (per > remain)
	{
		per -= remain;
		remain = 0;
	}
	else
	{
		remain -= per;
		return true;
	}

	int* point;
	while (per > 0)
	{
		point = ps.back();
		if (per > *point)
		{
			per -= *point;
			remain = 0;
		}
		else
		{
			*point -= per;
			return true;
		}
	}
	ccc_box(per);
}



void sPoint::operator+=(const sPoint& point)
{
	body += point.body;
	mag += point.mag;
	str += point.str;
	dex += point.dex;
	agi += point.agi;
}

sPoint sPoint::operator+(const sPoint& point) const 
{
	sPoint p;
	p.body = body + point.body;
	p.mag = mag + point.mag;
	p.str = str + point.str;
	p.dex = dex + point.dex;
	p.agi = agi + point.agi;
	return p;
}



void sPoint::operator+=(int point)
{
	body += point;
	mag += point;
	str += point;
	dex += point;
	agi += point;
}

sPoint sPoint::operator+(int point) const 
{
	sPoint p;
	p.body = body + point;
	p.mag = mag + point;
	p.str = str + point;
	p.dex = dex + point;
	p.agi = agi + point;
	return p;
}


void sPoint::save()const
{
	sStream& sav = *cSave::getSave();
	sav << str << s_space << dex << s_space << body << s_space << mag << s_space << agi << s_space << remain << s_space;
}


void sPoint::load()
{
	sStream& sav = *cSave::getLoad();
	sav >> str >> dex >> body >> mag >> agi >> remain;
}
