#pragma once
#include "_asert.h"

struct sItem //表示一个道具
{
	int m_Type;
	int m_ID;
	string m_Name;
	ulong m_SmallHead; //头像
	ulong m_BigHead;
	int m_Price = 0;//价格

	string m_Text; //描述
	int m_UseType;
	void SetLv(int lv){ m_lv = lv; }
	int GetLv(){ return m_lv; }
private:
	int m_lv;
};


struct sJiaJuData
{
	int num;
	vector<ulong> m_data;
};


enum ItemProPerty
{
	enum_hp,
	enum_hphurt,
	enum_mp
};


enum eFaBao
{
	eFaBao0曼陀罗,
	eFaBao1干将莫邪,
	eFaBao2罗汉珠,
	eFaBao3赤焰,
	eFaBao4万鬼幡,
	eFaBao5惊魂铃,
	eFaBao6混元伞,
	eFaBao7无魂傀儡,
	eFaBao8乾坤玄火塔,
	eFaBao9普渡,
	eFaBao10缩地尺,
	eFaBao11月光宝盒,
	eFaBao12红色导标旗,
	eFaBao13蓝色导标旗,
	eFaBao14白色导标旗,
	eFaBao15绿色导标旗,
	eFaBao16隐蛊,
	eFaBao17周杰伦手办,
	eFaBao18时之环,
	eFaBao19通灵宝玉,
	eFaBao20聚宝盆,
	eFaBao21碧玉葫芦,
	eFaBao22神木宝鼎,
	eFaBao23八咫镜,
	eFaBao24嗜血幡,
	eFaBao25金甲仙衣,
	eFaBao26降魔斗篷,
	eFaBao27九幽,
	eFaBao28救命毫毛,
	eFaBao29镇海珠,
	eFaBao30五火神焰印,
	eFaBao31忘情,
	eFaBao32慈悲,
	eFaBao33梦蝶,
	eFaBao15黄色导标旗
};

enum eProPerty
{
	eProPerty伤害,
	eProPerty命中,
	eProPerty命率,
	eProPerty防御,
	eProPerty魔法,
	eProPerty灵力,
	eProPerty速度,
	eProPerty气血,
	eProPerty力量,
	eProPerty敏捷,
	eProPerty体质,
	eProPerty魔力,
	eProPerty耐力,
	eProPerty水抗,
	eProPerty火抗,
	eProPerty土抗,
	eProPerty雷抗,
	eProPerty躲避,
	eProPerty法伤,
	eProPerty法防,
	eProPerty法结,
	eProPerty物结,
	eProPerty回复,
	eProPerty愤怒
};

