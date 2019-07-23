#pragma once

enum class ePoint
{
	// 强制按加点排列, 因为要参与索引计算
	None = -1,
	// 体力
	body ,
	// 魔力
	mag,
	// 力量
	str,
	// 耐力
	dex,
	// 敏捷
	agi,
	// 剩余
	remain,
};


// 属性点
struct sPoint
{
	// 体力
	int body;
	// 魔力
	int mag;
	// 力量
	int str;
	// 耐力
	int dex;
	// 敏捷
	int agi;
	// 剩余
	int remain;

	sPoint();
	// 清零
	bool reset(int initPoint = 0);
	// 取点
	int& get(ePoint e);
	// 检查(等级)
	bool check(int lv)const;
	// 加点
	bool add(ePoint e, bool onlyCheck);
	// 减点
	bool sub(ePoint e, bool onlyCheck);
	// 升级
	void lvup(int per = 1);
	// 降级
	bool lvdown(bool onlyCheck, int per = 1);

	// 不加remian
	void operator+=(const sPoint& point);
	// 不加remian
	sPoint operator+(const sPoint& point) const ;
	// 不加remian
	void operator+=(int point);
	// 不加remian
	sPoint operator+(int point) const;


	void save() const;
	void load();

	static const int c10 = 10;
};