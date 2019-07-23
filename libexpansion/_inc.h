#pragma once
#include "../libutil/_util.h"
#include "../libpro/sMod.h"
#include "../libtxt/_txt.h"

static inline std::string getIconName(eIcon e)
{
	switch (e)
	{
// 	case eIcon::eIcon0:
// 		
// 	case eIcon::equip0:
// 		
// 	case eIcon::eWeapon0:
// 		
	case eIcon::剑剑j: return " 剑 ";
	case eIcon::刀刀d: return " 刀 ";
	case eIcon::枪枪q: return " 枪 ";
	case eIcon::锤子c: return "锤子";
	case eIcon::斧钺f: return "斧钺";
	case eIcon::扇子s: return " 扇 ";
	case eIcon::爪子z: return "刺爪";
	case eIcon::棒槌b: return "棒槌";
	case eIcon::飘带p: return "飘带";
	case eIcon::鞭子b: return " 鞭 ";
	case eIcon::环圈h: return "环圈";
	case eIcon::双剑s: return "双剑";
	case eIcon::宝珠b: return "宝珠";
	case eIcon::弓弩g: return "弓弩";
	case eIcon::法杖f: return "法杖";
	case eIcon::巨剑j: return "巨剑";
	case eIcon::灯笼d: return "灯笼";
	case eIcon::伞伞s: return " 伞 ";
		
// 	case eIcon::eWeaponEnd:
// 		
// 	case eIcon::equipArmor0:
		
	case eIcon::头盔t: return "头盔";
	case eIcon::发钗f: return "发钗";
	case eIcon::铠甲k: return "铠甲";
	case eIcon::布裙b: return "布裙";
	case eIcon::项链x: return "项链";
	case eIcon::腰带y: return "腰带";
	case eIcon::鞋子x: return "鞋子";

// 	case eIcon::equipArmorEnd:
// 		
// 	case eIcon::equipBaby0:
		
	case eIcon::护腕h: return "护腕";
	case eIcon::项圈x: return "项圈";
	case eIcon::护甲h: return "护甲";

// 	case eIcon::equipBabyEnd:
// 		
// 	case eIcon::equipEnd:
		
	case eIcon::药品y: return "药品";
	case eIcon::烹饪p: return "烹饪";
	case eIcon::法宝f: return "法宝";
	case eIcon::暗器a: return "暗器";
	case eIcon::跑商p: return "跑商";
	case eIcon::五宝w: return "五宝";
	case eIcon::染色r: return "染色";
	case eIcon::强化q: return "强化石";
	case eIcon::鬼谷g: return "鬼谷子";
	case eIcon::元宵y: return "元宵";
	case eIcon::书书s: return "制造指";
	case eIcon::铁铁t: return "百炼精";
	case eIcon::打造d: return "打造";
	case eIcon::导标d: return "导标旗";
	case eIcon::旗子q: return "合成旗";
	case eIcon::宝图b: return "藏宝图";
	case eIcon::福寿f: return "福寿";
	case eIcon::杂货z: return "杂货";
	case eIcon::修炼x: return "修炼";
	case eIcon::宝宝b: return "宝宝";
	case eIcon::师门s: return "师门";
	case eIcon::任务r: return "任务";
	case eIcon::道具d: return "道具";
	case eIcon::宝石b: return "宝石";
	case eIcon::花卉h: return "花卉";
	case eIcon::乐器y: return "乐器";
	case eIcon::坐饰z: return "坐骑装饰";
	case eIcon::一家y: return "一级家具";
	case eIcon::二家e: return "二级家具";
	case eIcon::三家s: return "三级家具";
	case eIcon::四家s: return "四级家具";

// 	case eIcon::eMenpai0:
// 		
	case eIcon::大唐d: return "大唐官府";
	case eIcon::化生h: return "化生寺";
	case eIcon::女儿n: return "女儿村";
	case eIcon::方寸f: return "方寸山";
	case eIcon::狮驼s: return "狮驼岭";
	case eIcon::魔王m: return "魔王寨";
	case eIcon::盘丝p: return "盘丝洞";
	case eIcon::地府d: return "阴曹地府";
	case eIcon::龙宫l: return "东海龙宫";
	case eIcon::五庄w: return "五庄观";
	case eIcon::普陀p: return "普陀山";
	case eIcon::天宫t: return "天宫";
	case eIcon::凌波l: return "凌波城";
	case eIcon::无底w: return "无底洞";
	case eIcon::神木s: return "神木林";
// 		
// 	case eIcon::eMenpaiEnd:
// 		
	case eIcon::技能j: return "技能";
	case eIcon::兽决s: return "魔兽要诀";
	case eIcon::符石f: return "符石";	
	case eIcon::初丹c: return "初级内丹";
	case eIcon::高丹g: return "高级内丹";
	case eIcon::卡片k: return "变身卡";
	case eIcon::追加z: return "追加符石";
	case eIcon::状态z: return "状态符石";
//	case eIcon::eIconEnd:	
	default: return "???";
	}
}


static inline const std::vector<eAct>& getActGroup(bool atk2)
{
	static std::vector<eAct> as = { eAct::Stand, eAct::Walk, eAct::Fight, eAct::Go, eAct::Atk, eAct::Magic, eAct::Def, eAct::Suffer, eAct::Dead, eAct::Back };
	static std::vector<eAct> as2 = { eAct::Stand, eAct::Walk, eAct::Fight, eAct::Go, eAct::Atk, eAct::Atk2, eAct::Magic, eAct::Def, eAct::Suffer, eAct::Dead, eAct::Back };
	return atk2 ? as2 : as;
}

static inline const std::vector<std::string>& getActNames(bool atk2)
{
	static std::vector<std::string>  names = { "站立","行走", "战斗","冲锋","攻击","施法","防御","被打","死亡","返回", };
	static std::vector<std::string>  names2 = { "站立","行走", "战斗","冲锋","攻击","攻击2","施法","防御","被打","死亡","返回", };
	return atk2 ? names2 : names;
}

