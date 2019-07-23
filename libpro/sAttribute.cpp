#include "sAttribute.h"
#include "_inc.h"

int3::int3()
{
	reset();
}

int3::operator int()
{
	return std::max(0, ori) * std::max(0, per) / 100 + std::max(0, add);
}

int3::operator const int() const
{
	return std::max(0, ori) * std::max(0, per) / 100 + std::max(0, add);
}

void int3::reset()
{
	ori = add = 0;
	per = 100;
}

void int3::reset(int _add)
{
	add = _add;
	ori = 0;
}



//////////////////////////////////////////////////////////////////////////
sAttribute::sAttribute()
{
	reset();
}

void sAttribute::reset()
{
	hpMax.reset();
	mpMax.reset();

	// 面板 命中
	hit.reset();
	// 面板 伤害
	atk.reset();
	// 面板 防御
	def.reset();
	// 面板 灵力
	mana.reset();
	// 面板 速度
	speed.reset();
	// 面板 躲避
	evade.reset();

	hpMax.ori = cHp100;
	mpMax.ori = cMp80;
	hit.ori = cHit40;
}


// 
// bool sAttribute::correct(bool correcthp)
// {
// 	if (hp2 > Hp)
// 	{
// 		hp2 = Hp;
// 	}
// 	if (mp > Mp)
// 	{
// 		mp = Mp;
// 	}
// 	if (ap > cAp150)
// 	{
// 		ap = cAp150;
// 	}
// 	if (correcthp && hp > hp2)
// 	{
// 		hp = hp2;
// 	}
// 	return true;
// }
// 
// bool sAttribute::fillhpmp()
// {
// 	hp = hp2 = Hp;
// 	mp = Mp;
// 	return true;
// }
// 
// int sAttribute::addhp(int h, int per /*= 0*/)
// {
// 	if (hp <= 0)
// 	{
// 		return 0;
// 	}
// 	if (per != 0)
// 	{
// 	//	h = std::min(Hp * per / 100, h * per);
// 		per = Hp * per / 100;
// 		h = h * per;
// 		if (h > per)
// 		{
// 			h = per;
// 		}
// 	}
// 
// 	hp += h;
// 	if (hp > Hp)
// 	{
// 		h -= hp - Hp;
// 		hp = Hp;
// 	}
// 	return h;
// }
// 
// bool sAttribute::addhp2(int h, int per /*= 0*/)
// {
// 	if (hp <= 0)
// 	{
// 		return false;
// 	}
// 	if (per == 0)
// 	{
// 		hp2 += h;
// 	}
// 	else
// 	{
// 	//	hp2 += std::min(Hp * per / 100, h * per);
// 		per = Hp * per / 100;
// 		h = h * per;
// 		if (h > per)
// 		{
// 			h = per;
// 		}
// 		hp2 += h;
// 	}
// 
// 	if (hp2 > Hp)
// 	{
// 		hp2 = Hp;
// 	}
// 	return true;
// }
// 
// int sAttribute::addhphp2(int h, int h2)
// {
// 	if (hp <= 0)
// 	{
// 		return false;
// 	}
// 	hp += h;
// 	hp2 += h2;
// 
// 	if (hp > Hp)
// 	{
// 		h -= hp - Hp;
// 		hp = Hp;
// 	}
// 
// 	if (hp2 > Hp)
// 	{
// 		hp2 = Hp;
// 	}
// 	return h;
// }
// 
// bool sAttribute::addmp(int m, int per /*= 0*/)
// {
// 	if (hp <= 0)
// 	{
// 		return false;
// 	}
// 	if (per == 0)
// 	{
// 		mp += m;
// 	}
// 	else
// 	{
// 	//	mp += std::min(Mp * per / 100, m * per);
// 		per = Mp * per / 100;
// 		m = m * per;
// 		if (m > per)
// 		{
// 			m = per;
// 		}
// 		mp += m;
// 	}
// 
// 	if (mp > Mp)
// 	{
// 		mp = Mp;
// 	}
// 	return true;
// }
// 
// bool sAttribute::addap(int a, int per /*= 0*/)
// {
// 	if (hp <= 0)
// 	{
// 		return false;
// 	}
// 	if (per == 0)
// 	{
// 		ap += a;
// 	}
// 	else
// 	{
// 	//	ap += std::min(ccd::proAp150 * per / 100, a * per);
// 		per = cAp150 * per / 100;
// 		a = a * per;
// 		if (a > per)
// 		{
// 			a = per;
// 		}
// 		ap += a;
// 	}
// 
// 	if (ap > cAp150)
// 	{
// 		ap = cAp150;
// 	}
// 	return true;
// }
// 
// int sAttribute::relife2(int h, int h2, int per /* = 0 */, int per2 /* = 0 */)
// {
// 	if (per == 0)
// 	{
// 		hp = h;
// 	}
// 	else
// 	{
// 	//	h = hp = std::min(Hp * per / 100, h * per);
// 		per = Hp * per / 100;
// 		h = h * per;
// 		if (h > per)
// 		{
// 			h = per;
// 		}
// 		hp = h;
// 	}
// 
// 	if (hp > Hp)
// 	{
// 		h = Hp;
// 		hp = Hp;
// 	}
// 
// 	if (per2 == 0)
// 	{
// 		hp2 += h2;
// 	}
// 	else
// 	{
// 	//	hp2 += std::min(Hp * per2 / 100, h2 * per);
// 		per2 = Hp * per2 / 100;
// 		h2 = h2 * per;
// 		if (h2 > per)
// 		{
// 			h2 = per;
// 		}
// 		hp2 += h2;
// 	}
// 
// 	if (hp2 > Hp)
// 	{
// 		hp2 = Hp;
// 	}
// 	return h;
// }
// 
// int sAttribute::relife(int h, int per /*= 0*/)
// {
// 	return relife2(h, h, per, per);
// }
