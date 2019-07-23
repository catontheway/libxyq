#pragma once
#include "_inc.h"

struct sZz
{
	// 资质 攻击/防御/速度/躲闪 
	static const int c1680 = 1680;
	// 资质 体力资质
	static const int c6880 = 6880;
	// 资质 法力资质
	static const int c3680 = 3680;
	// 资质 成长
	static const int c130 = 130;
	// 攻击资质
	int atk;
	// 防御资质
	int def;
	// 体力资质
	int hp;
	// 法力资质
	int mag;
	// 速度资质
	int speed;
	// 躲闪资质
	int evoid;
	// 成长
	int grow100;

	sZz();

	void reset();

	bool isValid();

	void correct();


	void operator=(const txtZz::sZz& zz);

	void save()const;
	void load();
};


