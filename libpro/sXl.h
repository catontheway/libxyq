#pragma once
#include <array>


// 不用联合体,存档会自己截断
struct sXl
{
	static const int c4 = 4;
	std::array<int, c4> lvs;

	sXl();

	void reset();
	// 升级
	bool lvup(int idx);
	// 降级, 退还经验
	bool lvdown(int idx, bool onlyCheck);
	// 
	void set(int atk, int def, int mag, int dmag);
		
	void set(int a, int d);

	void set(int v);

	void setA(int a);
	void setA(int atk, int mag);

	void setD(int d);
	void setD(int def, int dmag);

	void save()const;
	void load();

	static int getExp(int lv);
	// 取当前人物等级的修炼上限
	static int getLv(int lv);
	static const int c25 = 25, c2000 = 2000;
};

