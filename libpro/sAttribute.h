#pragma once

// 三相数据
struct int3
{
	// 原始
	int ori;
	// 百分比 (比如:强身/冥思)
	int per;
	// 附加 (比如: 强壮)
	int add;

	int3();
	operator int();
	operator const int() const;

	void reset();
	// per不变
	void reset(int add);
};

// 基本属性
struct sAttribute
{
	// 气血上限
	int3 hpMax;
	// 魔法上限
	int3 mpMax;

	// 面板 命中
	int3 hit;
	// 面板 伤害
	int3 atk;
	// 面板 防御
	int3 def;
	// 面板 灵力
	int3 mana;
	// 面板 速度
	int3 speed;
	// 面板 躲避
	int3 evade;

	sAttribute();

	void reset();

	// 	bool correct(bool correcthp);
// 
// 	bool fillhpmp();
// 
// 	int addhp(int h, int per = 0);
// 
// 	bool addhp2(int h, int per = 0);
// 
// 	int addhphp2(int h, int h2);
// 
// 	bool addmp(int m, int per = 0);
// 
// 	bool addap(int a, int per = 0);
// 
// 	int relife(int h, int per = 0);
// 
// 	int relife2(int h, int h2, int per = 0, int per2 = 0);


	static const int cHp100 = 100, cMp80 = 80, cAp150 = 150, cHit40 = 40;
};


