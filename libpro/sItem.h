#pragma once
#include "_inc.h"

// 物品
class sItem
{
public:
	// 类型
	bool setIcon(eIcon type, int id);
	// 图标数据
	const txtIcon::sIcon* getIcon()const{ return _icon; }
	// 数据(特技特效,双加,指数下限0，指数上限100)
	bool setData(bool effect_ex3, bool add2, int eMin, int eMax);
	// 数据(宝图/导标旗专用)
	bool setData(const std::string& mapname, int x, int y);
	// 类型
	eIcon getType()const{ return _type; }
	// id
	int getId()const{ return _id; }
	// 价格
	void setPrice(int price){ _price = price; }
	// 价格
	int getPrice()const{ return _price; }
	// 加
	bool add(int count = 1);
	// 减
	bool sub(int count = 1);
	// 清空
	void clear(){ _num = 0; }
	// 无效
	bool isValid()const;
	// 数量
	int getCount()const{ return _num; }
	// 描述
	void toDesc(sDescs& descs)const;
	// 记载地名的
	bool is宝图or导标(bool checkValid = true)const;
	// 消耗品
	bool isConsumables(bool checkValid = true) const;
	// 可叠加
	bool isOverly(bool checkValid = true) const;
	// 宝宝物品
	bool isPetOnly(bool checkValid = true) const;
	// 武器/防具/宝宝装备
	bool isEquip(bool checkValid = true)const;
	// 武器
	bool isWeapon(bool checkValid = true)const;
	// 防具
	bool isArmor(bool checkValid = true)const;
	// 宝宝装备
	bool isEquipBaby(bool checkValid = true)const;
	// 头盔/发钗
	bool isHelmet(bool checkValid = true)const;
	// 项链
	bool isNeck(bool checkValid = true)const;
	// 盔甲/衣裙
	bool isClothes(bool checkValid = true)const;
	// 腰带
	bool isBelt(bool checkValid = true)const;
	// 鞋子
	bool isShoe(bool checkValid = true)const;
	// 切换武器(更换人物模型用)
	bool switchWeapon(eMod master);
	// 切换防具(更换人物模型用)
	bool switchArmor(bool boy);
	// 存档
	void save()const;
	// 读档
	void load();
	// 对比
	bool operator!=(const sItem& it)const;
	bool operator==(const sItem& it)const;
private:
	eIcon _type;
	int _id;
	int _num = 0;
	int _price = 0;
	std::string _str;
	uint _head;
	u64 _pro;
	const txtIcon::sIcon* _icon = nullptr;
	friend class cEquip;
	friend struct sBags;
public:
	static const int c20 = 20, c60 = 60;
};
typedef std::vector<sItem> sItems;