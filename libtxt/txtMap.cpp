#include "txtMap.h"

ccc_txt_instance_cpp(txtMap);

void txtMap::init(const std::string& mapname, int mapid, ulong uid, const std::string& music)
{
	_tables.insert(std::make_pair(mapname, _mapEmpty));
	_map = &_tables.at(mapname);
	_map->mapid = mapid;
	_map->uid = uid;
	_map->music = music;
}


void txtMap::insert(int x, int y, const std::string& mapname, int tx, int ty)
{
	_transMit.x = x;
	_transMit.y = y;
	_transMit.name = mapname;
	_transMit.tx = tx;
	_transMit.ty = ty;
	_map->transmits.push_back(_transMit);
}

void txtMap::insert(eMod e, int x, int y, eD direction, const std::string& name /*= ""*/, const std::string& script /*= ""*/, const std::string& appellation /*= ""*/)
{
	_npc.mod = e;
	_npc.x = x;
	_npc.y = y;
	_npc.direction = direction;
	_npc.name = name;
	_npc.script = script;
	_npc.appellation = appellation;
	_map->npcs.push_back(_npc);
}


const char* txtMap::_地图传送 = "地图传送";
const char* txtMap::_驿站老板 = "驿站老板";
const char* txtMap::_驿站酆都 = "驿站老板_酆都";

const char* txtMap::_门派传送弟子 = "门派传送弟子";
const char* txtMap::_门派传送人 = "门派传送人";
const char* txtMap::_门派师父 = "门派师父";

const char* txtMap::_帮派传送 = "帮派传送";
const char* txtMap::_帮派修炼指导师 = "帮派修炼指导师";
const char* txtMap::_帮派福利总管 = "帮派福利总管";

const char* txtMap::_系统商店 = "系统商店";
const char* txtMap::_专卖店 = "专卖店";
const char* txtMap::_系统装扮坐骑 = "系统装扮坐骑";
const char* txtMap::_系统装扮炫光 = "系统装扮炫光";
const char* txtMap::_系统装扮足迹 = "系统装扮足迹";
const char* txtMap::_系统装扮令牌 = "系统装扮令牌";
const char* txtMap::_系统装扮祥瑞 = "系统装扮祥瑞";
const char* txtMap::_系统装扮染色 = "系统装扮染色";

const char* txtMap::_仓库管理员 = "仓库管理员";
const char* txtMap::_打造镶嵌分解 = "打造镶嵌分解";
const char* txtMap::_角色转换 = "角色转换";
const char* txtMap::_打宝图 = "打宝图";

const char* txtMap::_超级巫医 = "超级巫医";
const char* txtMap::_钱庄老板 = "钱庄老板";
const char* txtMap::_陈长寿 = "陈长寿";
const char* txtMap::_建房吏 = "建房吏";
const char* txtMap::_钟馗捉鬼 = "钟馗捉鬼";
const char* txtMap::_装备鉴定商 = "装备鉴定商";
const char* txtMap::_装备收购商 = "装备收购商";

const char* txtMap::_我的庭院管家 = "我的庭院管家";
const char* txtMap::_大唐国境土地 = "大唐国境土地";

static std::string script传送(const std::string& mapname, int x, int y)
{
	return txtMap::_地图传送 + toString("_%s_%d_%d", mapname.c_str(), x, y);
}
static std::string script驿站(const std::string& mapname, int x, int y)
{
	return txtMap::_驿站老板 + toString("_%s_%d_%d", mapname.c_str(), x, y);
}
static std::string script驿站(int x, int y)
{
	return txtMap::_驿站老板 + toString("_长安城_%d_%d", x, y);
}
static std::string script商店(const std::string& script)
{
	return std::string(txtMap::_系统商店) + "_" + script;
}
static std::string script专卖(const std::string& script)
{
	return std::string(txtMap::_专卖店) + "_" + script;
}


void txtMap::initCA()
{
	init("长安城", 1001, 0xCEBC4615, "");
	insert(537, 114, "长安民居1", 12, 11);
	insert(506, 108, "长安民居3", 32, 10);
	insert(516, 238, "平安福寿店", 20, 12);
	insert(513, 3, "江南野外", 27, 102);
	insert(448, 247, "大雁塔一层", 40, 20);
	insert(474, 248, "大雁塔一层", 100, 20);
	insert(5, 4, "大唐国境", 327, 140);
	insert(10, 64, "长安衙门", 39, 9);
	insert(43, 64, "衙门地牢", 20, 13);
	insert(86, 80, "秦琼府", 47, 10);
	insert(161, 140, "丞相府", 54, 21);
	insert(98, 234, "金銮殿", 95, 20);
	insert(202, 256, "皇宫厢房", 16, 9);
	insert(279, 203, "国子监书库", 50, 17);
	insert(288, 61, "长乐赌坊", 28, 10);
	insert(245, 47, "清音坊", 27, 7);
	insert(217, 36, "留香阁", 48, 9);
	insert(342, 30, "福隆当铺", 35, 7);
	insert(367, 41, "张记布庄", 25, 12);
	insert(439, 63, "云来酒店", 11, 14);
	insert(478, 43, "万胜武器店", 17, 9);
	insert(411, 21, "锦绣饰品", 35, 9);
	insert(369, 6, "长安民居2", 26, 8);
	insert(522, 76, "书香斋", 19, 12);
	insert(486, 100, "冯记铁铺", 23, 14);
	insert(384, 124, "镇远武馆", 12, 9);
	insert(536, 134, "南北杂货店", 15, 10);
	insert(523, 155, "长风镖局", 18, 14);
	insert(486, 159, "回春堂药店", 11, 11);
	insert(463, 168, "长安酒店1楼", 16, 9);
	insert(468, 183, "长安酒店2楼", 13, 16);
	insert(475, 180, "长安酒店2楼", 23, 12);
	insert(514, 197, "广源钱庄", 15, 11);
	insert(547, 192, "长安民居4", 24, 19);
	insert(308, 275, "大唐官府", 154, 10);
	insert(510, 276, "化生寺", 11, 10);
	insert(eMod::马副将, 193, 174, eD::RD);
	insert(eMod::张老财, 250, 27, eD::RD);
	insert(eMod::王大嫂, 386, 50, eD::RD, "王夫人");
	insert(eMod::小宝, 445, 143, eD::RD, "红线童子");
	insert(eMod::e护卫, 106, 66, eD::RD, "秦府守卫");
	insert(eMod::小宝, 144, 4, eD::LD, "大宝");
	insert(eMod::小宝, 490, 190, eD::LD, "二宝");
	insert(eMod::小宝, 310, 120, eD::LD);
	insert(eMod::穷汉, 304, 53, eD::RD);
	insert(eMod::马副将, 161, 190, eD::RD, "李将军");
	insert(eMod::e护卫, 50, 37, eD::RD, "长安府守卫");
	insert(eMod::e护卫, 63, 44, eD::RD, "长安府守卫");
	insert(eMod::守门天将, 102, 227, eD::RD, "御林军左统领");
	insert(eMod::守门天将, 110, 230, eD::RD, "御林军右统领");
	insert(eMod::太上老君, 173, 14, eD::LD, "袁守诚", _角色转换);
	insert(eMod::柳飞絮, 5, 147, eD::RD, "赵美人");
	insert(eMod::周猎户, 384, 270, eD::RD, "帮派传送", _帮派传送);
	insert(eMod::火焰山土地, 380, 264, eD::RD, "帮派药房", script传送("帮派药房", 15, 8));
	insert(eMod::周猎户, 418, 115, eD::LD, "兰虎");
	insert(eMod::超级巫医, 527, 188, eD::LD, "", _超级巫医);
	insert(eMod::赵捕头, 38, 60, eD::LD, "建房吏", _建房吏);
	insert(eMod::轿夫, 521, 129, eD::LD, "", script传送("我的庭院", 18, 9));
	insert(eMod::小桃红, 277, 104, eD::LD, "怜儿姑娘");
	insert(eMod::孟大娘, 288, 17, eD::RU, "配色师", _系统装扮染色);
	insert(eMod::月老, 434, 140, eD::RD);
	insert(eMod::守门天将, 372, 116, eD::LD, "帮派竞赛主持人", script传送("帮派竞赛", 20, 86));
	insert(eMod::守门天将, 111, 112, eD::RD, "英雄大会主持人", script传送("英雄大会", 27, 21));
	insert(eMod::太上老君, 349, 73, eD::LD, "圣山传送人", script传送("战神山", 116, 49));
	insert(eMod::袁天罡, 357, 245, eD::RD);
	insert(eMod::孟大娘, 175, 31, eD::LD, "珍品商人", script商店("特产"));
	insert(eMod::仓库管理员, 326, 18, eD::RD, "商会总管", script商店("商会"));
	insert(eMod::吹牛王, 469, 203, eD::LD, "装备收购商", _装备收购商);
	insert(eMod::吹牛王, 459, 15, eD::RU, "装备收购商", _装备收购商);
	insert(eMod::吹牛王, 420, 247, eD::LD, "装备鉴定商", _装备鉴定商);
	insert(eMod::宝石商人, 499, 141, eD::LD, "", script商店("宝石"));
	insert(eMod::吹牛王, 438, 55, eD::LD, "装备鉴定商", _装备鉴定商);
	insert(eMod::罗道人, 257, 38, eD::RD, "", script商店("罗道人"));
	insert(eMod::罗道人, 496, 72, eD::RD, "", script商店("罗道人"));
	insert(eMod::生肖鼠, 482, 31, eD::LD, "门派传送人");
	insert(eMod::驿站老板, 280, 43, eD::LD, "", _驿站酆都);
	insert(eMod::eJueSe剑侠客, 418, 106, eD::RD, "影子", "擂台影子");
	insert(eMod::当铺老板, 302, 109, eD::LD, "长安商人", script商店("特产"));
	insert(eMod::当铺老板, 350, 144, eD::LD, "长安特产商人", script商店("特产"));
	insert(eMod::剑侠客, 201, 168, eD::RD, "合成旗专卖店", script专卖("合成旗"));
	insert(eMod::剑侠客, 196, 162, eD::RD, "变身卡");
	insert(eMod::剑侠客, 202, 160, eD::RD, "生肖变身卡");
	insert(eMod::剑侠客, 207, 166, eD::RD, "师傅变身卡");
	insert(eMod::剑侠客, 210, 169, eD::RD, "神兽变身卡");
	insert(eMod::剑侠客, 216, 175, eD::RD, "变身卡115");
	insert(eMod::剑侠客, 220, 165, eD::RD, "变身卡5");
	insert(eMod::剑侠客, 213, 163, eD::RD, "变身卡25");
	insert(eMod::剑侠客, 224, 171, eD::RD, "变身卡55");
	insert(eMod::剑侠客, 216, 156, eD::RD, "变身卡85");
	insert(eMod::剑侠客, 224, 158, eD::RD, "变身卡125");
	insert(eMod::剑侠客, 230, 166, eD::RD, "变身卡145");
	insert(eMod::剑侠客, 231, 157, eD::RD, "变身卡175");
	insert(eMod::剑侠客, 296, 19, eD::RD, "染色专卖店");
	insert(eMod::剑侠客, 262, 31, eD::RD, "兽诀专卖店");
	insert(eMod::剑侠客, 270, 31, eD::RD, "兽诀专卖店");
	insert(eMod::剑侠客, 280, 34, eD::RD, "兽诀专卖店");
	insert(eMod::剑侠客, 274, 39, eD::RD, "天眼专卖店");
	insert(eMod::剑侠客, 511, 124, eD::RD, "家具专卖店");
	insert(eMod::剑侠客, 517, 123, eD::RD, "家具专卖店");
	insert(eMod::剑侠客, 523, 123, eD::RD, "家具专卖店");
	insert(eMod::剑侠客, 527, 128, eD::RD, "家具专卖店");
	insert(eMod::剑侠客, 324, 8, eD::RD, "60武器");
	insert(eMod::剑侠客, 333, 16, eD::RD, "70武器");
	insert(eMod::剑侠客, 346, 21, eD::RD, "80武器");
	insert(eMod::剑侠客, 318, 12, eD::RD, "50环");
	insert(eMod::剑侠客, 332, 10, eD::RD, "60环");
	insert(eMod::剑侠客, 337, 14, eD::RD, "70环");
	insert(eMod::剑侠客, 343, 16, eD::RD, "80环");
	insert(eMod::剑侠客, 433, 90, eD::RD, "90武器");
	insert(eMod::剑侠客, 440, 93, eD::RD, "100武器");
	insert(eMod::剑侠客, 446, 96, eD::RD, "110武器");
	insert(eMod::剑侠客, 458, 85, eD::RD, "120武器");
	insert(eMod::剑侠客, 451, 99, eD::RD, "130武器");
	insert(eMod::剑侠客, 445, 111, eD::RD, "140武器");
	insert(eMod::剑侠客, 455, 109, eD::RD, "150武器");
	insert(eMod::剑侠客, 466, 112, eD::RD, "160武器");
	insert(eMod::剑侠客, 424, 92, eD::RD, "90国标");
	insert(eMod::剑侠客, 429, 95, eD::RD, "100国标");
	insert(eMod::剑侠客, 436, 97, eD::RD, "110国标");
	insert(eMod::剑侠客, 454, 91, eD::RD, "120国标");
	insert(eMod::剑侠客, 456, 95, eD::RD, "130国标");
	insert(eMod::剑侠客, 445, 103, eD::RD, "140国标");
	insert(eMod::剑侠客, 435, 113, eD::RD, "150国标");
	insert(eMod::剑侠客, 459, 114, eD::RD, "160国标");
	insert(eMod::剑侠客, 363, 82, eD::RD, "鉴定符专卖店");
	insert(eMod::剑侠客, 155, 205, eD::RD, "道具专卖店");
	insert(eMod::剑侠客, 503, 136, eD::RD, "状态符石");
	insert(eMod::剑侠客, 497, 131, eD::RD, "追加符石");
	insert(eMod::仓库管理员, 220, 130, eD::RD, "", _仓库管理员);
	insert(eMod::仓库管理员, 348, 244, eD::RD, "", _仓库管理员);
	insert(eMod::马副将, 107, 200, eD::RD, "门派闯关使者", "门派闯关使者");
	insert(eMod::e兔子怪, 207, 124, eD::RD, "节日奖励使者");
	insert(eMod::e超级神牛, 347, 231, eD::RD);
	insert(eMod::e超级神虎, 353, 227, eD::RD);
	insert(eMod::e超级神兔, 359, 225, eD::RD);
	insert(eMod::e超级神龙, 381, 228, eD::RD);
	insert(eMod::e超级神蛇, 377, 222, eD::RD);
	insert(eMod::e超级神马, 384, 217, eD::RD);
	insert(eMod::e超级神羊, 391, 212, eD::RD);
	insert(eMod::e超级神猴, 396, 207, eD::RD);
	insert(eMod::e超级神鸡, 403, 211, eD::RD);
	insert(eMod::e超级土地公公, 398, 213, eD::RD);
	insert(eMod::e小泡泡, 410, 213, eD::RD);
	insert(eMod::e小象, 386, 224, eD::RD);
	insert(eMod::e小白泽, 370, 228, eD::RD);
	insert(eMod::e超级六耳猕猴, 377, 233, eD::RD);
	insert(eMod::e超级麒麟, 403, 217, eD::RD);
	insert(eMod::e超级青鸾, 397, 222, eD::RD);
	insert(eMod::e超级灵狐, 391, 229, eD::RD);
	insert(eMod::e超级孔雀, 393, 234, eD::RD);
	insert(eMod::e超级玉兔, 387, 238, eD::RD);
	insert(eMod::e超级海豚, 382, 242, eD::RD);
	insert(eMod::e超级筋斗云, 376, 246, eD::RD);
	insert(eMod::e超级人参娃娃, 389, 204, eD::RD);
	insert(eMod::e超级灵鹿, 416, 216, eD::RD);
	insert(eMod::e超级大鹏, 373, 241, eD::RD);
	insert(eMod::e超级赤焰兽, 360, 234, eD::RD);
	insert(eMod::e超级白泽, 360, 249, eD::RD);
	insert(eMod::e超级大象, 365, 242, eD::RD);
	insert(eMod::e超级金猴, 370, 250, eD::RD);
	insert(eMod::e超级大熊猫, 337, 233, eD::RD);
	insert(eMod::e超级泡泡, 408, 207, eD::RD);


	init("金銮殿", 1044, 0x00000000, "");
	insert(102, 18, "长安城", 106, 229);
	insert(eMod::李世民, 46, 48, eD::RD);
	insert(eMod::魏征, 69, 42, eD::LD);
	insert(eMod::剑侠客, 90, 19, eD::R, "文解元");
	insert(eMod::剑侠客, 86, 21, eD::R, "文举人");
	insert(eMod::剑侠客, 82, 23, eD::R, "文会元");
	insert(eMod::剑侠客, 78, 25, eD::R, "文贡士");
	insert(eMod::剑侠客, 74, 27, eD::R, "文进士");
	insert(eMod::剑侠客, 70, 29, eD::R, "文探花");
	insert(eMod::剑侠客, 66, 31, eD::R, "文榜眼");
	insert(eMod::剑侠客, 62, 33, eD::R, "文状元");
	insert(eMod::剑侠客, 101, 24, eD::LD, "武解元");
	insert(eMod::剑侠客, 97, 26, eD::LD, "武举人");
	insert(eMod::剑侠客, 93, 28, eD::LD, "武会元");
	insert(eMod::剑侠客, 89, 30, eD::LD, "武贡士");
	insert(eMod::剑侠客, 85, 32, eD::LD, "武进士");
	insert(eMod::剑侠客, 81, 34, eD::LD, "武探花");
	insert(eMod::剑侠客, 77, 36, eD::LD, "武榜眼");
	insert(eMod::剑侠客, 73, 38, eD::LD, "武状元");


	init("皇宫厢房", 1046, 0x00000000, "");
	insert(11, 8, "长安城", 193, 246);

	////////////////////////////////////////////////////////////////////////// 商业
	init("冯记铁铺", 1025, 0x00000000, "");
	insert(16, 13, "长安城", 482, 93);
	insert(eMod::冯铁匠, 29, 17, eD::LD, "", _打造镶嵌分解);
	insert(eMod::铁匠, 25, 20, eD::LD, "伙计");

	init("福隆当铺", 1014, 0x00000000, "");
	insert(39, 8, "长安城", 345, 26);
	insert(eMod::当铺老板, 9, 11, eD::RD);

	init("广源钱庄", 1013, 0x00000000, "");
	insert(12, 10, "长安城", 511, 192);
	insert(eMod::宝石商人, 26, 15, eD::LD, "钱庄老板", _钱庄老板);

	init("回春堂药店", 1016, 0x00000000, "");
	insert(9, 10, "长安城", 480, 153);
	insert(eMod::药店老板, 16, 19, eD::LD, "", script商店("1级药品"));


	init("锦绣饰品", 1017, 0x00000000, "");
	insert(38, 9, "长安城", 414, 18);
	insert(eMod::许大娘, 20, 20, eD::RD, "饰品店老板", script商店("坐骑装饰"));


	init("南北杂货店", 1015, 0x00000000, "");
	insert(12, 9, "长安城", 530, 131);
	insert(eMod::超级巫医, 18, 17, eD::LD, "杂货店老板", script商店("杂货店"));

	init("平安福寿店", 1021, 0x00000000, "");
	insert(16, 12, "长安城", 511, 234);
	insert(eMod::老孙头, 30, 20, eD::LD, "福寿店老板", script商店("福寿店"));


	init("清音坊", 1018, 0x00000000, "");
	insert(31, 7, "长安城", 251, 43);
	insert(eMod::乐器店老板, 17, 14, eD::RD, "", script商店("乐器"));

	init("万胜武器店", 1020, 0x00000000, "");
	insert(12, 7, "长安城", 471, 38);
	insert(eMod::周猎户, 20, 16, eD::LD, "武器店老板", script商店("武器_20"));
	insert(eMod::老孙头, 12, 13, eD::RD, "武器店掌柜", script商店("武器_50"));

	init("张记布庄", 1022, 0x00000000, "");
	insert(33, 10, "长安城", 371, 37);
	insert(eMod::服装店老板, 38, 16, eD::RD, "服装店伙计", script商店("装备_10"));
	insert(eMod::服装店老板, 10, 12, eD::RU, "", script商店("装备_20"));

	init("云来酒店", 1030, 0x00000000, "");
	insert(9, 14, "长安城", 433, 57);
	insert(eMod::酒店老板, 19, 24, eD::RD, "", script商店("烹饪"));

	//////////////////////////////////////////////////////////////////////////
	init("长安酒店1楼", 1028, 0x00000000, "");
	insert(12, 8, "长安城", 458, 162);
	insert(34, 35, "长安酒店2楼", 44, 29);
	insert(eMod::小二, 24, 16, eD::RD, "店小二", "店小二打宝图");
	insert(eMod::酒店老板, 44, 22, eD::LD, "酒楼老板", "住店");

	init("长安酒店2楼", 1029, 0x00000000, "");
	insert(37, 32, "长安酒店1楼", 29, 28);
	insert(21, 11, "长安城", 468, 178);
	insert(11, 16, "长安城", 468, 178);

	init("长风镖局", 1024, 0x00000000, "");
	insert(7, 19, "长安城", 517, 147);
	insert(eMod::e镖头, 34, 16, eD::LD, "郑镖头", script商店("鬼谷子"));

	init("长乐赌坊", 1034, 0x00000000, "");
	insert(32, 9, "长安城", 292, 57);
	insert(eMod::赌霸天, 13, 10, eD::RD);

	init("国子监书库", 1026, 0x00000000, "");
	insert(60, 19, "长安城", 285, 197);
	insert(eMod::教书先生, 25, 36, eD::RD, "吴举人");


	init("留香阁", 1033, 0x00000000, "");
	insert(51, 9, "长安城", 221, 33);
	insert(22, 39, "怜香轩", 29, 8);
	insert(7, 32, "惜玉轩", 27, 9);
	insert(eMod::陈妈妈, 35, 20, eD::LD);
	insert(eMod::乐器店老板, 40, 10, eD::RU, "罗百万");


	init("惜玉轩", 1032, 0x00000000, "");
	insert(32, 8, "留香阁", 12, 30);
	insert(eMod::小桃红, 16, 18, eD::RD, "小惜玉");

	init("怜香轩", 1031, 0x00000000, "");
	insert(32, 8, "留香阁", 24, 36);
	insert(eMod::小桃红, 19, 15, eD::RD, "小怜香");


	init("秦琼府", 1057, 0x00000000, "");
	insert(52, 9, "长安城", 91, 74);
	insert(15, 28, "秦府内室", 32, 10);
	insert(eMod::秦琼, 25, 20, eD::RD);

	init("秦府内室", 1056, 0x00000000, "");
	insert(34, 10, "秦琼府", 17, 22);
	insert(eMod::程夫人, 22, 18, eD::RD, "秦夫人");


	init("书香斋", 1019, 0x00000000, "");
	insert(14, 11, "长安城", 515, 70);
	insert(eMod::颜如羽, 19, 20, eD::LD);


	init("镇远武馆", 1023, 0x00000000, "");
	insert(9, 8, "长安城", 379, 119);
	insert(eMod::周猎户, 24, 13, eD::LD, "王武");


	init("丞相府", 1049, 0x00000000, "");
	insert(63, 12, "长安城", 164, 134);
	insert(eMod::魏征, 31, 27, eD::RD, "殷丞相");
	insert(eMod::程夫人, 14, 19, eD::RU, "殷夫人");



	init("长安衙门", 1050, 0x00000000, "");
	insert(42, 8, "长安城", 15, 61);
	insert(eMod::简师爷, 12, 20, eD::RD, "罗师爷");
	insert(eMod::赵捕头, 20, 21, eD::RD, "捕头李");
	insert(eMod::赵捕头, 27, 20, eD::LD, "衙役");
	insert(eMod::赵捕头, 32, 17, eD::LD, "衙役");
	insert(eMod::赵捕头, 21, 14, eD::RU, "衙役");
	insert(eMod::赵捕头, 17, 16, eD::RU, "衙役");

	init("衙门地牢", 1051, 0x00000000, "");
	insert(16, 12, "长安城", 40, 60);

	////////////////////////////////////////////////////////////////////////// 民宅
	init("长安民居1", 1035, 0x00000000, "");
	insert(9, 10, "长安城", 530, 108);

	init("长安民居2", 1036, 0x00000000, "");
	insert(31, 8, "长安城", 377, 2);
	insert(eMod::许大娘, 20, 13, eD::LD, "赵姨娘");

	init("长安民居3", 1037, 0x00000000, "");
	insert(37, 9, "长安城", 511, 104);

	init("长安民居4", 1038, 0x00000000, "");
	insert(22, 13, "长安城", 539, 185);
	insert(eMod::e强盗, 10, 25, eD::LD, "紫衣盗");
};


void txtMap::initJY()
{
	init("建邺城", 1501, 0xA0CD8BBA, "");
	insert(242, 131, "东海湾", 11, 84);
	insert(277, 25, "东海湾", 12, 8);
	insert(10, 3, "江南野外", 149, 55);
	insert(77, 14, "建邺兵铁铺", 12, 6);
	insert(257, 90, "建邺民居", 15, 7);
	insert(5, 84, "建邺民居2", 27, 9);
	insert(116, 131, "东升货栈", 26, 6);
	insert(235, 80, "万宇钱庄", 18, 8);
	insert(244, 23, "建邺民居1", 27, 8);
	insert(218, 9, "回春堂分店", 24, 7);
	insert(172, 37, "李积布庄", 13, 7);
	insert(130, 42, "合生记", 15, 5);
	insert(147, 85, "建邺衙门", 13, 9);
	insert(eMod::赵元宝, 86, 114, eD::LD, "戏班老板");
	insert(eMod::教书先生, 78, 89, eD::LD);
	insert(eMod::吹牛王, 90, 111, eD::LD);
	insert(eMod::小木匠, 87, 73, eD::LD, "张来福");
	insert(eMod::赵捕头, 117, 71, eD::LD);
	insert(eMod::小二, 32, 86, eD::LD, "管家");
	insert(eMod::老孙头, 223, 132, eD::LD);
	insert(eMod::赵元宝, 228, 64, eD::LD);
	insert(eMod::柳飞絮, 207, 36, eD::LD, "小花");
	insert(eMod::招罗弟, 220, 113, eD::RU, "罗招弟");
	insert(eMod::e慧海, 9, 55, eD::RD, "迎客僧");
	insert(eMod::罗道人, 230, 109, eD::RU, "牛大胆");
	insert(eMod::王大嫂, 141, 132, eD::LD);
	insert(eMod::周猎户, 19, 91, eD::RD, "符全");
	insert(eMod::吹牛王, 51, 30, eD::RD, "老胡");
	insert(eMod::刘老爹, 39, 24, eD::RD);
	insert(eMod::周猎户, 52, 49, eD::LD, "马全有");
	insert(eMod::e马面, 202, 46, eD::LD, "勾魂马面");
	insert(eMod::柳飞絮, 63, 115, eD::LD, "宠物仙子");
	insert(eMod::药店老板, 219, 123, eD::LD, "陈长寿", _陈长寿);
	insert(eMod::超级巫医, 213, 97, eD::LD, "", _超级巫医);
	insert(eMod::超级巫医, 104, 55, eD::LD, "", _超级巫医);
	insert(eMod::吹牛王, 243, 116, eD::LD, "装备收购商", _装备收购商);
	insert(eMod::吹牛王, 250, 115, eD::LD, "装备鉴定人", _装备鉴定商);
	insert(eMod::海产收购商, 231, 130, eD::LD);
	insert(eMod::招罗弟, 105, 106, eD::LD, "飞儿", script商店("包子"));
	insert(eMod::剑侠客, 58, 26, eD::RD, "杂货摊位", script专卖("杂货摊位"));
	insert(eMod::剑侠客, 51, 25, eD::RD, "宝宝装备", script专卖("宝宝装备_55"));
	insert(eMod::剑侠客, 63, 28, eD::RD, "宝宝装备", script专卖("宝宝装备_115"));
	insert(eMod::仓库管理员, 55, 31, eD::RD, "", _仓库管理员);

	init("建邺兵铁铺", 1502, 0x00000000, "");
	insert(9, 6, "建邺城", 71, 10);
	insert(eMod::冯铁匠, 10, 10, eD::RD, "兵铁铺老板", script商店("武器_10"));
	insert(eMod::铁匠, 7, 8, eD::RD, "兵铁铺伙计", script商店("武器_0"));

	init("建邺民居", 1525, 0x00000000, "");
	insert(10, 6, "建邺城", 258, 83);

	init("建邺民居1", 1526, 0x00000000, "");
	insert(31, 8, "建邺城", 248, 18);
	insert(eMod::周猎户, 25, 13, eD::LD);

	init("建邺民居2", 1527, 0x00000000, "");
	insert(33, 9, "建邺城", 10, 79);
	insert(5, 17, "建邺民居内室", 37, 13);

	init("建邺民居内室", 1534, 0x00000000, "");
	insert(43, 12, "建邺民居2", 10, 10);
	insert(eMod::张老财, 12, 9, eD::RD, "李善人");

	init("建邺衙门", 1537, 0x00000000, "");
	insert(12, 9, "建邺城", 143, 80);
	insert(eMod::赵捕头, 18, 16, eD::RD, "衙役");
	insert(eMod::赵捕头, 25, 20, eD::RD, "衙役");
	insert(eMod::赵捕头, 26, 12, eD::LU, "衙役");
	insert(eMod::赵捕头, 34, 16, eD::LU, "衙役");
	insert(eMod::简师爷, 27, 21, eD::RD);
	insert(eMod::颜如羽, 30, 20, eD::LD, "建邺县令");


	init("东升货栈", 1505, 0x00000000, "");
	insert(30, 4, "建邺城", 121, 126);
	insert(eMod::超级巫医, 36, 14, eD::LD, "杂货店老板", script商店("杂货店"));


	init("合生记", 1523, 0x00000000, "");
	insert(10, 5, "建邺城", 121, 42);
	insert(eMod::当铺老板, 24, 10, eD::LD);

	init("回春堂分店", 1504, 0x00000000, "");
	insert(29, 5, "建邺城", 219, 3);
	insert(eMod::药店老板, 23, 12, eD::LD, "", script商店("1级药品"));

	init("李积布庄", 1503, 0x00000000, "");
	insert(10, 6, "建邺城", 167, 32);
	insert(eMod::服装店老板, 16, 14, eD::LD, "", script商店("装备_0"));

	init("万宇钱庄", 1524, 0x00000000, "");
	insert(15, 7, "建邺城", 235, 74);
	insert(eMod::宝石商人, 30, 14, eD::LD, "钱庄老板", _钱庄老板);

}



void txtMap::initAL()
{
	init("傲来国", 1092, 0xAEAEAF33, "");
	insert(3, 144, "女儿村", 119, 12);
	insert(189, 75, "傲来国民居1", 29, 7);
	insert(75, 110, "傲来国民居2", 28, 9);
	insert(31, 74, "傲来国服饰店", 37, 7);
	insert(56, 40, "傲来国药店", 33, 10);
	insert(18, 30, "傲来国民居3", 12, 9);
	insert(99, 18, "傲来国杂货店", 25, 8);
	insert(133, 43, "傲来国武器店", 10, 9);
	insert(105, 60, "傲来国钱庄", 44, 6);
	insert(140, 108, "傲来国圣殿", 14, 14);
	insert(151, 69, "傲来国当铺", 16, 6);
	insert(181, 29, "傲来国客栈", 37, 5);
	insert(215, 144, "花果山", 19, 14);
	insert(eMod::仓库管理员, 146, 101, eD::LD, "", _仓库管理员);
	insert(eMod::驿站老板, 173, 11, eD::LD, "", script驿站("东海湾", 65, 20));
	insert(eMod::驿站老板, 57, 99, eD::LD, "", _驿站老板);
	insert(eMod::孟大娘, 58, 118, eD::LD, "傲来珍品商人", script商店("编号_65"));
	insert(eMod::超级巫医, 38, 27, eD::RD, "", _超级巫医);
	insert(eMod::e巨力神猿, 195, 131, eD::RD, "金毛猿");
	insert(eMod::e巨力神猿, 44, 105, eD::LD, "红毛猿");
	insert(eMod::e蝴蝶仙子, 60, 54, eD::LD, "蝴蝶妹妹");
	insert(eMod::e兔子怪, 133, 129, eD::LD, "偷偷怪");
	insert(eMod::当铺老板, 183, 105, eD::LD, "傲来商人", script商店("特产"));
	insert(eMod::宝石商人, 90, 106, eD::LD, "傲来货商", script商店("特产"));
	insert(eMod::当铺老板, 48, 33, eD::RD, "傲来特产商人", script商店("特产"));
	insert(eMod::e红萼仙子, 22, 98, eD::RD, "仙岛引路使", script传送("蓬莱仙岛", 9, 37));
	insert(eMod::海产收购商, 186, 66, eD::RD, "捕鱼人");
	insert(eMod::剑侠客, 121, 93, eD::RD, "五宝专卖店", script专卖("五宝"));
	insert(eMod::剑侠客, 132, 95, eD::RD, "强化石专卖店", script专卖("五宝"));

	init("傲来国当铺", 1094, 0x00000000, "");
	insert(13, 5, "傲来国", 149, 63);
	insert(eMod::当铺老板, 31, 8, eD::LD);

	init("傲来国服饰店", 1095, 0x00000000, "");
	insert(40, 7, "傲来国", 37, 69);
	insert(eMod::服装店老板, 16, 17, eD::RD, "牛师傅", script商店("装备_30"));

	init("傲来国客栈", 1093, 0x00000000, "");
	insert(41, 5, "傲来国", 185, 27);
	insert(31, 34, "傲来客栈二楼", 29, 8);
	insert(eMod::酒店老板, 18, 15, eD::RD, "王福来");
	insert(eMod::颜如羽, 43, 19, eD::RD, "慕容先生");

	init("傲来国民居1", 1098, 0x00000000, "");
	insert(33, 7, "傲来国", 190, 73);
	insert(eMod::张老头, 25, 11, eD::RD);

	init("傲来国民居2", 1106, 0x00000000, "");
	insert(25, 7, "傲来国", 71, 107);

	init("傲来国民居3", 1107, 0x00000000, "");
	insert(9, 7, "傲来国", 17, 21);
	insert(eMod::赵元宝, 15, 13, eD::LD, "文老伯");

	init("傲来国钱庄", 1099, 0x00000000, "");
	insert(48, 6, "傲来国", 110, 56);
	insert(eMod::宝石商人, 16, 17, eD::RD, "钱庄老板", _钱庄老板);

	init("傲来国圣殿", 1100, 0x00000000, "");
	insert(16, 11, "傲来国", 136, 103);
	insert(eMod::小桃红, 28, 17, eD::RU, "小紫");

	init("傲来国武器店", 1101, 0x00000000, "");
	insert(8, 9, "傲来国", 128, 39);
	insert(eMod::周猎户, 12, 15, eD::LD, "杜天", script商店("武器_30"));

	init("傲来国药店", 1104, 0x00000000, "");
	insert(38, 8, "傲来国", 62, 38);
	insert(eMod::药店老板, 12, 14, eD::RD, "沈妙衣", script商店("1级药品"));

	init("傲来国杂货店", 1105, 0x00000000, "");
	insert(29, 6, "傲来国", 103, 17);
	insert(eMod::超级巫医, 18, 15, eD::RD, "杂货店老板", script商店("杂货店"));

	init("傲来客栈二楼", 1535, 0x00000000, "");
	insert(33, 7, "傲来国客栈", 36, 25);


}




void txtMap::initCS()
{
	init("长寿村", 1070, 0xA4EA11C8, "");
	insert(18, 39, "村长家", 27, 8);
	insert(82, 29, "长寿村药店", 23, 8);
	insert(136, 54, "长寿村杂货店", 13, 6);
	insert(148, 3, "长寿郊外", 152, 152);
	insert(84, 73, "长寿村服装店", 13, 9);
	insert(72, 112, "长寿村武器店", 23, 7);
	insert(108, 149, "长寿村酒馆", 19, 6);
	insert(151, 146, "长寿村民居1", 14, 10);
	insert(144, 96, "长寿村钱庄", 24, 7);
	insert(129, 185, "长寿村神庙", 11, 6);
	insert(112, 208, "方寸山", 15, 36);
	insert(23, 182, "长寿村民居", 34, 11);
	insert(16, 128, "长寿村当铺", 14, 7);
	insert(97, 144, "长寿酒店上房", 27, 8);
	insert(eMod::太白金星, 53, 18, eD::LD);
	insert(eMod::张老头, 81, 129, eD::LD, "毛驴张");
	insert(eMod::超级巫医, 124, 114, eD::RD, "", _超级巫医);
	insert(eMod::教书先生, 46, 156, eD::LU, "钟书生");
	insert(eMod::e慧海, 136, 67, eD::LD, "慧觉和尚");
	insert(eMod::刘老爹, 101, 38, eD::RD, "海老先生");
	insert(eMod::柳飞絮, 24, 106, eD::RD, "凤凰姑娘");
	insert(eMod::e蝴蝶仙子, 50, 135, eD::RD, "蝴蝶女");
	insert(eMod::许大娘, 80, 65, eD::RD);
	insert(eMod::张老财, 136, 84, eD::LD, "钱老板");
	insert(eMod::小桃红, 78, 172, eD::LD, "许姑娘");
	insert(eMod::南极仙翁, 110, 189, eD::RD);
	insert(eMod::婆婆, 43, 71, eD::LD, "马婆婆", "领养男孩");
	insert(eMod::刘老爹, 40, 75, eD::LD, "马爷爷", "领养女孩");
	insert(eMod::刘老爹, 121, 174, eD::LD, "蔡爷爷");
	insert(eMod::海产收购商, 90, 108, eD::LD, "捕鱼人");
	insert(eMod::当铺老板, 104, 60, eD::LD, "长寿商人", script商店("特产"));
	insert(eMod::当铺老板, 130, 41, eD::LD, "长寿特产商人", script商店("特产"));
	insert(eMod::剑侠客, 110, 52, eD::RD, "元宵专卖店");
	insert(eMod::剑侠客, 116, 54, eD::RD, "修炼专卖店");
	insert(eMod::剑侠客, 114, 49, eD::RD, "金柳露专卖店");
	insert(eMod::仓库管理员, 112, 62, eD::RD, "", _仓库管理员);

	init("长寿村当铺", 1072, 0x00000000, "");
	insert(18, 6, "长寿村", 22, 122);
	insert(eMod::当铺老板, 20, 13, eD::RD);

	init("长寿村服装店", 1083, 0x00000000, "");
	insert(10, 9, "长寿村", 88, 68);
	insert(eMod::服装店老板, 23, 7, eD::LD, "裁缝张", script商店("装备_40"));

	init("长寿村酒馆", 1075, 0x00000000, "");
	insert(23, 5, "长寿村", 110, 141);
	insert(eMod::酒店老板, 10, 9, eD::RD, "酒楼老板");

	init("长寿村民居", 1079, 0x00000000, "");
	insert(40, 9, "长寿村", 27, 175);
	insert(eMod::教书先生, 28, 12, eD::LD, "茶客");
	insert(eMod::小二, 24, 15, eD::RD, "茶小二");

	init("长寿村民居1", 1078, 0x00000000, "");
	insert(9, 9, "长寿村", 145, 141);
	insert(eMod::鲁成, 17, 11, eD::LD);

	init("长寿村钱庄", 1081, 0x00000000, "");
	insert(20, 9, "长寿村", 145, 89);
	insert(eMod::宝石商人, 22, 12, eD::LD, "钱庄老板", _钱庄老板);

	init("长寿村神庙", 1082, 0x00000000, "");
	insert(8, 5, "长寿村", 132, 178);

	init("长寿村武器店", 1085, 0x00000000, "");
	insert(28, 6, "长寿村", 69, 102);
	insert(eMod::轿夫, 14, 10, eD::RD, "武器店老板", script商店("武器_40"));

	init("长寿村药店", 1077, 0x00000000, "");
	insert(28, 7, "长寿村", 80, 21);
	insert(eMod::药店老板, 14, 10, eD::RD, "", script商店("1级药品"));

	init("长寿村杂货店", 1087, 0x00000000, "");
	insert(10, 5, "长寿村", 138, 48);
	insert(eMod::超级巫医, 24, 14, eD::LD, "杂货店老板", script商店("杂货店"));

	init("村长家", 1080, 0x00000000, "");
	insert(31, 8, "长寿村", 20, 35);
	insert(eMod::刘老爹, 11, 14, eD::RD, "长寿村村长");

	init("长寿酒店上房", 1536, 0x00000000, "");
	insert(31, 9, "长寿村", 100, 141);


}



void txtMap::initCity()
{
	init("宝象国", 1226, 0x46BE840D, "");
	insert(4, 4, "麒麟山", 49, 4);
	insert(123, 117, "解阳山", 89, 5);
	insert(2, 110, "宝象国皇宫", 64, 14);
	insert(153, 8, "碗子山", 13, 8);
	insert(3, 60, "丝绸之路", 390, 87);
	insert(eMod::驿站老板, 141, 93, eD::RD);
	insert(eMod::香料店老板, 71, 56, eD::RD, "队长令牌", _系统装扮令牌);
	insert(eMod::香料店老板, 48, 39, eD::RD, "足迹", _系统装扮炫光);
	insert(eMod::香料店老板, 23, 26, eD::RD, "祥瑞", _系统装扮祥瑞);
	insert(eMod::香料店老板, 116, 42, eD::RD, "花店老板", script商店("花"));
	insert(eMod::药店老板, 147, 51, eD::D, "", script商店("2级药品"));
	insert(eMod::香料店老板, 85, 22, eD::RD, "足迹", _系统装扮足迹);

	init("宝象国皇宫", 1227, 0x00000000, "");
	insert(71, 13, "宝象国", 11, 101);
	insert(eMod::宝象国国王, 33, 34, eD::RD);

	init("西梁女国", 1040, 0xFE7FC64D, "");
	insert(150, 9, "子母河底", 11, 16);
	insert(22, 20, "丝绸之路", 459, 7);
	insert(eMod::婆婆, 90, 88, eD::RD, "慕容婆婆");
	insert(eMod::香料店老板, 38, 97, eD::RD, "西门将军");
	insert(eMod::香料店老板, 59, 20, eD::RD, "宁小倩");
	insert(eMod::上官丞相, 64, 17, eD::LU);
	insert(eMod::西梁女国国王, 21, 103, eD::RD);
	insert(eMod::西梁女兵, 63, 13, eD::LU);
	insert(eMod::西梁女兵, 69, 17, eD::LU);
	insert(eMod::西梁女兵, 130, 18, eD::RD);
	insert(eMod::西梁女兵, 143, 24, eD::RD);
	insert(eMod::驿站老板, 23, 54, eD::RD, "", script驿站("朱紫国", 140, 94));
	insert(eMod::西梁女兵, 13, 99, eD::RD);
	insert(eMod::西梁女兵, 27, 106, eD::RD);
	insert(eMod::太白金星, 124, 62, eD::RD, "马真人");
	insert(eMod::香料店老板, 135, 61, eD::LD, "药店老板", script商店("2级药品"));

	init("朱紫国", 1208, 0x5524B32A, "");
	insert(14, 99, "麒麟山", 163, 6);
	insert(5, 5, "大唐境外", 7, 62);
	insert(148, 100, "朱紫皇宫", 31, 17);
	insert(143, 4, "丝绸之路", 296, 75);
	insert(eMod::朱紫校尉, 139, 99, eD::LD);
	insert(eMod::朱紫校尉, 22, 4, eD::LD, "朱紫侍卫");
	insert(eMod::朱紫校尉, 8, 11, eD::LD, "朱紫侍卫");
	insert(eMod::吹牛王, 127, 23, eD::LD, "药店伙计", script商店("2级药品"));
	insert(eMod::小二, 34, 38, eD::LD, "酒店伙计", script商店("烹饪"));
	insert(eMod::超级巫医, 8, 88, eD::LD, "", _超级巫医);
	insert(eMod::刘老爹, 74, 14, eD::LD, "申太公", script传送("仙缘洞天", 212, 80));
	insert(eMod::王大嫂, 97, 7, eD::LU, "端木娘子");
	insert(eMod::小桃红, 150, 6, eD::LD, "豆蔻囡囡");
	insert(eMod::雷黑子, 153, 4, eD::LU, "小囝囝");
	insert(eMod::仓库管理员, 126, 90, eD::RD, "", _仓库管理员);
	insert(eMod::驿站老板, 20, 64, eD::RD, "", script驿站("西梁女国", 15, 11));

	init("朱紫皇宫", 1209, 0x00000000, "");
	insert(27, 15, "朱紫国", 144, 96);
	insert(eMod::宝象国国王, 67, 34, eD::LD, "朱紫国王");
	insert(eMod::阿米国师, 55, 34, eD::RD);

}



void txtMap::initMenpai()
{
	////////////////////////////////////////////////////////////////////////// 化生
	init("化生寺", 1002, 0xD48EE39D, "");
	insert(4, 4, "长安城", 505, 272);
	insert(57, 39, "大雄宝殿", 20, 12);
	insert(93, 57, "藏经阁", 10, 13);
	insert(eMod::空慈方丈, 118, 80, eD::LD);
	insert(eMod::空慈方丈, 58, 9, eD::LD, "空善大师");
	insert(eMod::e慧海, 63, 28, eD::LD, "接引僧", _门派传送弟子);
	insert(eMod::e慧海, 42, 38, eD::LD, "慧海");
	insert(eMod::e慧海, 115, 51, eD::LD, "慧静");
	insert(eMod::e慧海, 16, 46, eD::RD, "慧悲");
	insert(eMod::e慧海, 32, 15, eD::LD, "疥癞和尚");

	init("藏经阁", 1043, 0x00000000, "");
	insert(13, 9, "化生寺", 86, 49);
	insert(eMod::e空度禅师, 17, 16, eD::LD, "空度禅师", _门派师父);

	init("大雄宝殿", 1528, 0x00000000, "");
	insert(17, 12, "化生寺", 50, 32);
	insert(eMod::e慧海, 13, 15, eD::RD, "慧明");
	insert(eMod::e空度禅师, 27, 18, eD::RU, "法明长老");

	////////////////////////////////////////////////////////////////////////// 普陀
	init("普陀山", 1140, 0xE1BC6C78, "");
	insert(8, 64, "潮音洞", 50, 10);
	insert(eMod::柳飞絮, 87, 10, eD::RD, "引路仙女", script传送("大唐国境", 222, 61));
	insert(eMod::e黑熊精, 26, 27, eD::RD, "黑熊怪");
	insert(eMod::e小龙女, 15, 40, eD::LD, "龙女宝宝");
	insert(eMod::柳飞絮, 25, 53, eD::RD, "接引仙女", _门派传送弟子);
	insert(eMod::e黑熊, 58, 63, eD::RD, "小熊怪");

	init("潮音洞", 1141, 0x00000000, "");
	insert(58, 5, "普陀山", 13, 55);
	insert(eMod::e观音姐姐, 11, 36, eD::RD, "观音姐姐", _门派师父);
	insert(eMod::柳飞絮, 20, 15, eD::RD, "青莲仙女");

	////////////////////////////////////////////////////////////////////////// 大唐
	init("大唐官府", 1198, 0x20705313, "");
	insert(161, 7, "长安城", 319, 269);
	insert(78, 48, "程咬金府", 34, 9);
	insert(99, 86, "程府内室2", 12, 11);
	insert(eMod::e护卫, 121, 22, eD::RD, "程府守卫");
	insert(eMod::e护卫, 129, 26, eD::RD, "程府守卫");
	insert(eMod::e护卫, 90, 8, eD::RD, "程府守卫");
	insert(eMod::e护卫, 156, 41, eD::RD, "程府守卫");
	insert(eMod::程夫人, 24, 79, eD::RD);
	insert(eMod::小桃红, 19, 76, eD::RU, "丫鬟");
	insert(eMod::e护卫, 73, 43, eD::RD, "传送兵", _门派传送弟子);

	init("程咬金府", 1054, 0x00000000, "");
	insert(42, 5, "大唐官府", 84, 43);
	insert(34, 20, "程府内室", 17, 10);
	insert(eMod::e程咬金, 18, 18, eD::RD, "程咬金", _门派师父);

	init("程府内室", 1052, 0x00000000, "");
	insert(12, 7, "程咬金府", 32, 13);

	init("程府内室2", 1035, 0x00000000, "");
	insert(9, 10, "大唐官府", 90, 79);

	////////////////////////////////////////////////////////////////////////// 地府
	init("阴曹地府", 1122, 0x9AFBFBC8, "");
	insert(147, 4, "大唐国境", 44, 322);
	insert(28, 70, "森罗殿", 41, 13);
	insert(36, 112, "地狱迷宫一层", 12, 56);
	insert(105, 54, "轮回司", 29, 11);
	insert(eMod::婆婆, 96, 24, eD::RD, "孟婆");
	insert(eMod::e牛头, 96, 103, eD::LD, "牛头");
	insert(eMod::e马面, 19, 33, eD::LD, "马面");
	insert(eMod::e僵尸, 27, 58, eD::RD, "地遁鬼", _门派传送弟子);
	insert(eMod::e兔子怪, 15, 12, eD::RU, "追梦鬼");
	insert(eMod::钟馗, 45, 49, eD::RD, "", _钟馗捉鬼);
	insert(eMod::当铺老板, 69, 45, eD::LD, "地府商人", "商店系统_特产");
	insert(eMod::当铺老板, 82, 8, eD::LD, "地府特产商人", "商店系统_特产");

	init("森罗殿", 1123, 0x00000000, "");
	insert(55, 5, "阴曹地府", 35, 63);
	insert(24, 35, "地藏王府", 28, 11);
	insert(eMod::e转轮王, 23, 18, eD::RD, "阎罗王");
	insert(eMod::e转轮王, 27, 16, eD::RD, "转轮王");
	insert(eMod::e转轮王, 31, 14, eD::RD, "秦广王");
	insert(eMod::e转轮王, 35, 12, eD::RD, "初江王");
	insert(eMod::e转轮王, 39, 10, eD::RD, "宋帝王");
	insert(eMod::e转轮王, 32, 23, eD::RD, "卞城王");
	insert(eMod::e转轮王, 36, 21, eD::RD, "平等王");
	insert(eMod::e转轮王, 40, 19, eD::RD, "泰山王");
	insert(eMod::e转轮王, 44, 17, eD::RD, "都市王");
	insert(eMod::e转轮王, 48, 15, eD::RD, "杵官王");
	insert(eMod::崔判官, 17, 24, eD::RD);

	init("地藏王府", 1124, 0x00000000, "");
	insert(41, 9, "森罗殿", 30, 27);
	insert(eMod::e地藏王, 21, 14, eD::RD, "地藏王", _门派师父);

	init("轮回司", 1125, 0x00000000, "");
	insert(29, 7, "阴曹地府", 109, 47);
	insert(eMod::黑无常, 36, 10, eD::LD, "", "黑无常");
	insert(eMod::白无常, 23, 10, eD::RD, "", script传送("长安城", 355, 247));


	////////////////////////////////////////////////////////////////////////// 方寸
	init("方寸山", 1135, 0xB23B05EC, "");
	insert(5, 37, "长寿村", 107, 195);
	insert(130, 137, "灵台宫", 24, 15);
	insert(eMod::清风, 120, 136, eD::LD, "接引道童", _门派传送弟子);
	insert(eMod::罗道人, 65, 46, eD::LD, "觉明");
	insert(eMod::小桃红, 34, 95, eD::LD, "灵儿");

	init("灵台宫", 1137, 0x00000000, "");
	insert(18, 14, "方寸山", 119, 128);
	insert(eMod::e菩提祖师, 46, 26, eD::LD, "菩提祖师", _门派师父);


	////////////////////////////////////////////////////////////////////////// 凌波
	init("凌波城", 1150, 0x4B8C7EC9, "");
	insert(5, 65, "大唐国境", 175, 262);
	insert(eMod::e二郎神, 71, 123, eD::LD, "二郎神", _门派师父);
	insert(eMod::e天兵, 37, 97, eD::LD, "门派传送", _门派传送弟子);

	////////////////////////////////////////////////////////////////////////// 天宫
	init("天宫", 1111, 0x80B40884, "");
	insert(46, 161, "月宫", 109, 15);
	insert(144, 65, "凌宵宝殿", 68, 14);
	insert(23, 27, "兜率宫", 37, 11);
	insert(3, 68, "蟠桃园", 134, 11);
	insert(eMod::e天将, 239, 18, eD::RD, "守门天将", script传送("长寿郊外", 20, 55));
	insert(eMod::e天将, 230, 13, eD::RD, "守门天将", script传送("长寿郊外", 20, 55));
	insert(eMod::e芙蓉仙子, 162, 66, eD::RD, "接引仙子", _门派传送弟子);
	insert(eMod::柳飞絮, 100, 25, eD::RD, "素衣仙女");
	insert(eMod::e天兵, 101, 63, eD::RD, "顺风耳");
	insert(eMod::守门天将, 229, 141, eD::RD, "天牢守卫");
	insert(eMod::守门天将, 170, 140, eD::RD, "水兵统领");
	insert(eMod::e风伯, 18, 129, eD::RD, "大力神灵");
	insert(eMod::清风, 21, 23, eD::RD, "守门道童");
	insert(eMod::清风, 29, 27, eD::RD, "守门道童");

	init("凌宵宝殿", 1112, 0x00000000, "");
	insert(83, 14, "天宫", 149, 60);
	insert(eMod::玉皇大帝, 25, 46, eD::RD);
	insert(eMod::王母娘娘, 28, 47, eD::RD);
	insert(eMod::e李靖, 28, 28, eD::RD, "李靖", _门派师父);
	insert(eMod::杨戟, 51, 23, eD::RD, "杨戬");
	insert(eMod::哪吒, 64, 30, eD::RD, "哪咤");

	init("兜率宫", 1113, 0x00000000, "");
	insert(44, 9, "天宫", 33, 17);
	insert(eMod::太上老君, 19, 20, eD::RD);
	insert(eMod::罗道人, 31, 10, eD::LD, "炼丹道士", script商店("法宝"));

	////////////////////////////////////////////////////////////////////////// 无底洞
	init("无底洞", 1139, 0xA38F3971, "");
	insert(85, 126, "碗子山", 41, 15);
	insert(60, 53, "琉璃殿", 17, 15);
	insert(eMod::e鼠先锋, 52, 49, eD::LD, "传送小妖", _门派传送弟子);

	init("琉璃殿", 1156, 0x00000000, "");
	insert(7, 11, "无底洞", 57, 46);
	insert(eMod::e地涌夫人, 47, 29, eD::LD, "地涌夫人", _门派师父);

	////////////////////////////////////////////////////////////////////////// 龙宫
	init("龙宫", 1116, 0x207DAB6D, "");
	insert(211, 108, "海底迷宫一层", 16, 12);
	insert(131, 64, "水晶宫", 37, 14);
	insert(113, 64, "水晶宫", 17, 12);
	insert(4, 7, "东海湾", 102, 87);
	insert(eMod::e虾兵, 113, 55, eD::LD, "龙宫传送人", _门派传送弟子);
	insert(eMod::百晓星君, 20, 64, eD::LD, "万圣公主");
	insert(eMod::e蛤蟆精, 148, 57, eD::RD, "蛤蟆头领");
	insert(eMod::e小龙女, 97, 72, eD::LD, "小龙女");
	insert(eMod::e龟丞相, 53, 98, eD::LD, "龟太尉");
	insert(eMod::e龟丞相, 98, 58, eD::LD, "龟千岁");
	insert(eMod::e虾兵, 195, 28, eD::RD, "虾将军");
	insert(eMod::e蟹将, 32, 16, eD::LD, "蟹将军");
	insert(eMod::e蛤蟆精, 196, 99, eD::RU, "蛤蟆勇士");

	init("水晶宫", 1117, 0x00000000, "");
	insert(53, 8, "龙宫", 136, 61);
	insert(15, 8, "龙宫", 109, 60);
	insert(eMod::e东海龙王, 34, 20, eD::LD, "东海龙王", _门派师父);

	////////////////////////////////////////////////////////////////////////// 魔王
	init("魔王寨", 1512, 0x3436B7ED, "");
	insert(13, 12, "大唐境外", 55, 113);
	insert(93, 74, "魔王居", 19, 11);
	insert(eMod::e牛妖, 23, 27, eD::LD, "守门牛妖");
	insert(eMod::e牛妖, 38, 21, eD::LD, "守门牛妖");
	insert(eMod::e牛妖, 87, 72, eD::LD, "引路小妖", _门派传送弟子);

	init("魔王居", 1145, 0x00000000, "");
	insert(7, 4, "魔王寨", 83, 66);
	insert(eMod::e牛魔王, 31, 16, eD::LD, "牛魔王", _门派师父);
	insert(eMod::e九头精怪, 17, 15, eD::RD, "九头精怪");


	////////////////////////////////////////////////////////////////////////// 女儿
	init("女儿村", 1142, 0xCA5082AD, "");
	insert(126, 9, "傲来国", 10, 137);
	insert(34, 26, "女儿村民居", 18, 12);
	insert(13, 126, "女儿村村长家", 30, 12);
	insert(eMod::小桃红, 21, 125, eD::RD, "传送女使", _门派传送弟子);
	insert(eMod::柳飞絮, 27, 53, eD::RD, "", script商店("暗器"));
	insert(eMod::翠花, 75, 45, eD::RD);
	insert(eMod::王大嫂, 105, 86, eD::D, "栗栗娘");
	insert(eMod::小宝, 82, 70, eD::LD, "绿儿");
	insert(eMod::陈妈妈, 59, 70, eD::RD, "红娘");

	init("女儿村村长家", 1143, 0x00000000, "");
	insert(38, 11, "女儿村", 18, 122);
	insert(eMod::e孙婆婆, 21, 17, eD::RD, "孙婆婆", _门派师父);

	init("女儿村民居", 1529, 0x00000000, "");
	insert(14, 11, "女儿村", 30, 22);

	////////////////////////////////////////////////////////////////////////// 盘丝
	init("盘丝岭", 1513, 0xDE4D90EE, "");
	insert(188, 4, "大唐境外", 538, 104);
	insert(189, 128, "盘丝洞", 18, 10);
	insert(eMod::e蝴蝶仙子, 180, 127, eD::LD, "引路小妖", _门派传送弟子);
	insert(eMod::e树怪, 173, 123, eD::LD, "看门小妖");
	insert(eMod::e树怪, 185, 116, eD::LD, "看门小妖");
	insert(eMod::e芙蓉仙子, 111, 49, eD::RD, "女妖");
	insert(eMod::e如意仙子, 72, 72, eD::LD, "金琉璃");
	insert(eMod::小桃红, 77, 73, eD::LD, "栗栗儿");

	init("盘丝洞", 1144, 0x00000000, "");
	insert(13, 5, "盘丝岭", 181, 121);
	insert(eMod::春三十娘, 25, 22, eD::RD);
	insert(eMod::e白晶晶, 33, 46, eD::LD, "白晶晶", _门派师父);


	////////////////////////////////////////////////////////////////////////// 五庄
	init("五庄观", 1146, 0x0C524261, "");
	insert(6, 6, "大唐境外", 626, 65);
	insert(60, 39, "乾坤殿", 20, 10);
	insert(eMod::罗道人, 63, 37, eD::LD, "接引道人", _门派传送弟子);
	insert(eMod::清风, 50, 37, eD::LD);
	insert(eMod::清风, 60, 33, eD::LD, "明月");

	init("乾坤殿", 1147, 0x00000000, "");
	insert(14, 8, "五庄观", 51, 33);
	insert(eMod::e镇元大仙, 27, 13, eD::LD, "镇元大仙", _门派师父);

	////////////////////////////////////////////////////////////////////////// 神木
	init("神木林", 1138, 0x44FDBD2D, "");
	insert(66, 16, "战神山", 17, 40);
	insert(48, 82, "神木屋", 41, 15);
	insert(11, 101, "神木药房", 28, 11);
	insert(eMod::满天星, 37, 135, eD::L);
	insert(eMod::满天星, 46, 71, eD::L, "传送使者", _门派传送弟子);

	init("神木屋", 1154, 0x00000000, "");
	insert(48, 11, "神木林", 50, 79);
	insert(eMod::e巫奎虎, 33, 18, eD::RD, "巫奎虎", _门派师父);

	init("神木药房", 1155, 0x00000000, "");
	insert(35, 9, "神木林", 11, 95);
	////////////////////////////////////////////////////////////////////////// 狮驼
	init("狮驼岭", 1131, 0x614B45F3, "");
	insert(125, 95, "大唐境外", 14, 52);
	insert(28, 87, "大象洞", 20, 8);
	insert(16, 43, "老雕洞", 8, 6);
	insert(116, 28, "狮王洞", 37, 16);
	insert(eMod::e雷鸟人, 120, 22, eD::LD, "传送妖精", _门派传送弟子);
	insert(eMod::e雷鸟人, 112, 92, eD::LD, "守山小妖");
	insert(eMod::e雷鸟人, 120, 83, eD::LD, "守山小妖");

	init("狮王洞", 1134, 0x00000000, "");
	insert(40, 16, "狮驼岭", 112, 24);
	insert(eMod::e大大王, 30, 21, eD::RD, "大大王", _门派师父);

	init("大象洞", 1132, 0x00000000, "");
	insert(29, 4, "狮驼岭", 22, 78);
	insert(eMod::二大王, 25, 17, eD::LD);

	init("老雕洞", 1133, 0x00000000, "");
	insert(5, 5, "狮驼岭", 13, 39);
	insert(eMod::三大王, 22, 14, eD::LD);

	////////////////////////////////////////////////////////////////////////// 女魃墓
	init("女魃墓", 1249, 0x00000000, "");
	insert(48, 106, "赤水洲", 96, 71);

	init("幻境花果山", 1251, 0x00000000, "");
	insert(eMod::e孙悟空, 90, 105, eD::LD);
	insert(18, 15, "花果山", 133, 14);

	init("天机城", 1250, 0x00000000, "");
	insert(20, 14, "大唐境外", 190, 7);
	insert(74, 118, "机枢馆", 21, 16);
	insert(136, 115, "天机堂", 50, 20);
	insert(153, 81, "万卷阁", 23, 13);

	init("机枢馆", 1257, 0x00000000, "");
	insert(7, 8, "天机城", 69, 114);

	init("天机堂", 1253, 0x00000000, "");
	insert(eMod::班主, 59, 24, eD::LD);
	insert(40, 16, "天机城", 130, 110);
	insert(88, 15, "万卷阁", 35, 18);

	init("万卷阁", 1256, 0x00000000, "");
	insert(36, 20, "天机堂", 76, 21);
	insert(13, 7, "天机城", 149, 79);
}



void txtMap::initMaze()
{
	init("大雁塔一层", 1004, 0xB522C713, "大雁塔1");
	insert(30, 17, "长安城", 440, 240);
	insert(107, 17, "长安城", 481, 242);
	insert(68, 74, "大雁塔二层", 60, 60);
	insert(eMod::超级巫医, 64, 27, eD::LD, "", _超级巫医);

	init("大雁塔二层", 1005, 0xB56504B2, "大雁塔2");
	insert(65, 63, "大雁塔一层", 74, 65);
	insert(78, 16, "大雁塔三层", 64, 16);
	insert(eMod::e僵尸, 85, 60, eD::RD, "梦之魅");

	init("大雁塔三层", 1006, 0x43471CC3, "大雁塔1");
	insert(70, 14, "大雁塔二层", 73, 9);
	insert(75, 77, "大雁塔四层", 55, 59);
	insert(eMod::超级巫医, 67, 35, eD::LD, "", _超级巫医);

	init("大雁塔四层", 1007, 0xDBF85229, "大雁塔2");
	insert(64, 60, "大雁塔三层", 65, 62);
	insert(100, 63, "大雁塔五层", 94, 50);
	insert(eMod::e蛤蟆精, 133, 39, eD::LD, "奔波儿灞");

	init("大雁塔五层", 1008, 0x070872BE, "大雁塔1");
	insert(98, 55, "大雁塔四层", 108, 53);
	insert(13, 51, "大雁塔六层", 23, 45);
	insert(eMod::超级巫医, 68, 38, eD::LD, "", _超级巫医);


	init("大雁塔六层", 1090, 0x3A2C78B5, "大雁塔2");
	insert(16, 44, "大雁塔五层", 20, 41);
	insert(59, 54, "大雁塔七层", 30, 21);

	init("大雁塔七层", 1009, 0xAAE2D167, "大雁塔1");
	insert(37, 26, "大雁塔六层", 71, 39);
	insert(eMod::朱紫校尉, 32, 30, eD::RD, "镇塔之神");


	//////////////////////////////////////////////////////////////////////////
	init("海底迷宫一层", 1118, 0xD558F867, "海底迷宫");
	insert(7, 5, "龙宫", 191, 96);
	insert(12, 45, "海底迷宫三层", 49, 14);
	insert(61, 42, "海底迷宫二层", 20, 10);

	init("海底迷宫二层", 1119, 0xA70FCC68, "");
	insert(11, 3, "海底迷宫一层", 52, 33);
	insert(57, 43, "海底迷宫五层", 27, 10);
	insert(eMod::e巡游天神, 24, 20, eD::LD, "海夜叉");
	insert(eMod::超级巫医, 37, 31, eD::LD, "", _超级巫医);

	init("海底迷宫三层", 1120, 0xF8D4D447, "");
	insert(56, 7, "海底迷宫一层", 15, 37);
	insert(60, 44, "海底迷宫四层", 14, 11);
	insert(eMod::e天兵, 35, 15, eD::LD, "风波神");

	init("海底迷宫四层", 1121, 0x49AC5547, "");
	insert(5, 4, "海底迷宫三层", 50, 35);
	insert(57, 4, "海底迷宫五层", 14, 36);
	insert(eMod::e虾兵, 36, 37, eD::LD, "虾兵");

	init("海底迷宫五层", 1532, 0x6B2B2EA7, "");
	insert(20, 5, "海底迷宫二层", 46, 34);
	insert(2, 43, "海底迷宫四层", 48, 11);
	insert(eMod::小白龙, 54, 38, eD::RD);


	//////////////////////////////////////////////////////////////////////////
	init("地狱迷宫一层", 1127, 0x6AFF3A47, "地狱迷宫");
	insert(2, 62, "阴曹地府", 31, 104);
	insert(7, 6, "地狱迷宫二层", 110, 79);
	insert(eMod::e巡游天神, 52, 62, eD::LD, "幽冥鬼");

	init("地狱迷宫二层", 1129, 0x15118E61, "地狱迷宫2");
	insert(114, 84, "地狱迷宫一层", 13, 9);
	insert(118, 36, "地狱迷宫三层", 16, 63);
	insert(118, 6, "地狱迷宫三层", 18, 37);
	insert(eMod::e野鬼, 47, 27, eD::LD, "吊死鬼");

	init("地狱迷宫三层", 1128, 0xC97CEECD, "地狱迷宫");
	insert(2, 63, "地狱迷宫二层", 102, 35);
	insert(2, 33, "地狱迷宫二层", 102, 8);
	insert(117, 4, "地狱迷宫四层", 18, 77);
	insert(eMod::e野鬼, 40, 45, eD::LD, "无名野鬼", "无名野鬼");
	insert(eMod::超级巫医, 70, 70, eD::RD, "", _超级巫医);

	init("地狱迷宫四层", 1130, 0xC9E935A3, "地狱迷宫2");
	insert(5, 83, "地狱迷宫三层", 102, 9);
	insert(108, 67, "无名鬼城", 26, 10);
	insert(eMod::e白晶晶, 63, 66, eD::RD, "白晶晶的鬼魂");
	insert(eMod::e野鬼, 92, 58, eD::LD, "千年怨鬼");


	//////////////////////////////////////////////////////////////////////////

	init("龙窟一层", 1177, 0x3EA72B1F, "龙窟");
	insert(153, 3, "北俱芦洲", 13, 80);
	insert(10, 71, "龙窟二层", 127, 23);

	init("龙窟二层", 1178, 0xFF998899, "龙窟2");
	insert(132, 24, "龙窟一层", 20, 66);
	insert(20, 6, "龙窟三层", 10, 68);
	insert(eMod::e蛟龙, 113, 30, eD::RD, "龙神");


	init("龙窟三层", 1179, 0x296F3D1B, "龙窟");
	insert(134, 25, "龙窟四层", 14, 6);
	insert(11, 79, "龙窟二层", 26, 9);
	insert(eMod::超级巫医, 48, 15, eD::RD, "", _超级巫医);

	init("龙窟四层", 1180, 0x22D0EB49, "龙窟2");
	insert(3, 8, "龙窟三层", 126, 30);
	insert(121, 29, "龙窟五层", 124, 61);

	init("龙窟五层", 1181, 0x674490C6, "龙窟");
	insert(133, 65, "龙窟四层", 129, 22);
	insert(54, 10, "龙窟六层", 89, 13);


	init("龙窟六层", 1182, 0xD2575ED4, "龙窟2");
	insert(80, 17, "龙窟五层", 42, 12);
	insert(121, 63, "龙窟七层", 9, 70);
	insert(eMod::超级巫医, 46, 38, eD::LD, "", _超级巫医);

	init("龙窟七层", 1183, 0xEADE2B36, "龙窟");
	insert(6, 78, "龙窟六层", 109, 63);


	//////////////////////////////////////////////////////////////////////////
	init("凤巢一层", 1186, 0x53EC9A6E, "凤巢");
	insert(80, 69, "北俱芦洲", 83, 145);
	insert(45, 4, "凤巢二层", 36, 60);
	insert(eMod::超级巫医, 88, 43, eD::RD, "辛发明");

	init("凤巢二层", 1187, 0x88247560, "凤巢2");
	insert(46, 69, "凤巢一层", 48, 6);
	insert(125, 46, "凤巢三层", 19, 53);

	init("凤巢三层", 1188, 0x5258A786, "凤巢");
	insert(9, 59, "凤巢二层", 116, 49);
	insert(125, 5, "凤巢四层", 21, 54);
	insert(eMod::超级巫医, 26, 31, eD::LD, "", _超级巫医);

	init("凤巢四层", 1189, 0x0F326E75, "凤巢2");
	insert(11, 60, "凤巢三层", 116, 8);
	insert(76, 70, "凤巢五层", 84, 13);

	init("凤巢五层", 1190, 0x2FC18B92, "凤巢");
	insert(75, 4, "凤巢四层", 70, 63);
	insert(116, 69, "凤巢六层", 15, 14);

	init("凤巢六层", 1191, 0x950C1B87, "凤巢2");
	insert(2, 2, "凤巢五层", 111, 63);
	insert(126, 48, "凤巢七层", 9, 40);
	insert(eMod::超级巫医, 90, 57, eD::LD, "", _超级巫医);

	init("凤巢七层", 1192, 0xA2C1DE00, "凤巢");
	insert(2, 36, "凤巢六层", 121, 41);
}



void txtMap::initHome()
{
	init("我的庭院", 1447, 0xF601DC89, "家");
	insert(9, 4, "长安城", 518, 124);
	insert(eMod::管家, 32, 20, eD::LD, "仆人", _我的庭院管家);

	//////////////////////////////////////////////////////////////////////////
	init("普通民宅0", 1401, 0x00000000, "");
	insert(10, 7, "长安城", 518, 127);

	init("普通民宅1", 1404, 0x00000000, "");
	insert(10, 7, "长安城", 518, 127);

	init("普通民宅2", 1407, 0x00000000, "");
	insert(10, 7, "长安城", 518, 127);

	init("普通民宅3", 1410, 0x00000000, "");
	insert(10, 7, "长安城", 518, 127);

	init("普通民宅4", 1413, 0x00000000, "");
	insert(10, 7, "长安城", 518, 127);

	init("普通民宅5", 1416, 0x00000000, "");
	insert(10, 7, "长安城", 518, 127);

	init("普通民宅6", 1333, 0x00000000, "");
	insert(10, 7, "长安城", 518, 127);

	//////////////////////////////////////////////////////////////////////////
	init("顶级豪宅0", 1403, 0x00000000, "");
	insert(22, 17, "长安城", 518, 127);

	init("顶级豪宅1", 1406, 0x00000000, "");
	insert(22, 17, "长安城", 518, 127);

	init("顶级豪宅10", 1320, 0x00000000, "");
	insert(45, 9, "长安城", 518, 127);

	init("顶级豪宅11", 1321, 0x00000000, "");
	insert(45, 9, "长安城", 518, 127);

	init("顶级豪宅12", 1322, 0x00000000, "");
	insert(45, 9, "长安城", 518, 127);

	init("顶级豪宅13", 1323, 0x00000000, "");
	insert(45, 9, "长安城", 518, 127);

	init("顶级豪宅14", 1324, 0x00000000, "");
	insert(45, 9, "长安城", 518, 127);

	init("顶级豪宅15", 1325, 0x00000000, "");
	insert(45, 9, "长安城", 518, 127);

	init("顶级豪宅16", 1326, 0x00000000, "");
	insert(45, 9, "长安城", 518, 127);

	init("顶级豪宅2", 1409, 0x00000000, "");
	insert(22, 17, "长安城", 518, 127);

	init("顶级豪宅3", 1412, 0x00000000, "");
	insert(22, 17, "长安城", 518, 127);

	init("顶级豪宅4", 1415, 0x00000000, "");
	insert(22, 17, "长安城", 518, 127);

	init("顶级豪宅5", 1418, 0x00000000, "");
	insert(22, 17, "长安城", 518, 127);

	init("顶级豪宅6", 1332, 0x00000000, "");
	insert(21, 16, "长安城", 518, 127);

	//////////////////////////////////////////////////////////////////////////
	init("高级华宅0", 1402, 0x00000000, "");
	insert(14, 11, "长安城", 518, 127);

	init("高级华宅1", 1405, 0x00000000, "");
	insert(14, 11, "长安城", 518, 127);

	init("高级华宅10", 1310, 0x00000000, "");
	insert(19, 11, "长安城", 518, 127);

	init("高级华宅11", 1311, 0x00000000, "");
	insert(19, 11, "长安城", 518, 127);

	init("高级华宅12", 1312, 0x00000000, "");
	insert(19, 11, "长安城", 518, 127);

	init("高级华宅13", 1313, 0x00000000, "");
	insert(19, 11, "长安城", 518, 127);

	init("高级华宅14", 1314, 0x00000000, "");
	insert(19, 11, "长安城", 518, 127);

	init("高级华宅15", 1315, 0x00000000, "");
	insert(19, 11, "长安城", 518, 127);

	init("高级华宅16", 1316, 0x00000000, "");
	insert(19, 11, "长安城", 518, 127);

	init("高级华宅2", 1408, 0x00000000, "");
	insert(14, 11, "长安城", 518, 127);

	init("高级华宅3", 1411, 0x00000000, "");
	insert(14, 11, "长安城", 518, 127);

	init("高级华宅4", 1414, 0x00000000, "");
	insert(14, 11, "长安城", 518, 127);

	init("高级华宅5", 1417, 0x00000000, "");
	insert(14, 11, "长安城", 518, 127);

	init("高级华宅6", 1331, 0x00000000, "");
	insert(14, 11, "长安城", 518, 127);
}



void txtMap::initField()
{
	init("北俱芦洲", 1174, 0xC4523BAE, "");
	insert(7, 85, "龙窟一层", 153, 9);
	insert(78, 154, "凤巢一层", 75, 64);
	insert(eMod::火焰山土地, 195, 105, eD::LD, "北俱芦洲土地", script传送("花果山", 30, 99));
	insert(eMod::e兔子怪, 198, 9, eD::RD, "地遁鬼", script传送("长寿郊外", 60, 67));
	insert(eMod::驿站老板, 47, 119, eD::LD, "", _驿站老板);
	insert(eMod::宝石商人, 168, 39, eD::LD, "北俱商人", script商店("特产"));
	insert(eMod::超级巫医, 161, 118, eD::LD, "北俱货商", script商店("特产"));
	insert(eMod::仓库管理员, 106, 110, eD::LD, "江湖奸商", script商店("3级药品"));
	insert(eMod::e小龙女, 131, 93, eD::LD, "龙女妹妹");
	insert(eMod::e雷鸟人, 67, 140, eD::LD, "雷鸟精");
	insert(eMod::e山贼, 34, 30, eD::LD, "莽汉");
	insert(eMod::e星灵仙子, 204, 133, eD::LD, "青琉璃");
	insert(eMod::e地狱战神, 132, 40, eD::LD, "翻天怪");
	insert(eMod::e白熊, 182, 74, eD::LD, "白熊怪");
	insert(eMod::超级巫医, 32, 49, eD::LD, "", _超级巫医);
	insert(eMod::e净瓶女娲, 14, 156, eD::RD, "传送女娲", script传送("女娲神迹", 49, 38));

	////////////////////////////////////////////////////////////////////////// 比丘国
	init("比丘国", 1232, 0x33B4D62D, "");
	insert(39, 92, "柳林坡", 17, 4);
	insert(9, 58, "丝绸之路", 344, 12);

	init("波月洞", 1229, 0x9D88ED61, "");
	insert(11, 129, "碗子山", 57, 170);

	init("长寿郊外", 1091, 0x2691C760, "");
	insert(158, 162, "长寿村", 140, 9);
	insert(20, 89, "柳林坡", 135, 26);
	insert(16, 35, "丝绸之路", 592, 83);
	insert(eMod::驿站老板, 60, 67, eD::LD, "", script驿站("北俱芦洲", 195, 5));
	insert(eMod::火焰山土地, 96, 12, eD::LD, "西牛贺州土地", script传送("大唐境外", 51, 15));
	insert(eMod::e天将, 21, 58, eD::RD, "天将", script传送("天宫", 236, 16));
	insert(eMod::罗道人, 182, 14, eD::LD, "鬼谷道士");
	insert(eMod::百晓星君, 180, 60, eD::LD, "铁扇公主");
	insert(eMod::小二, 44, 130, eD::LD, "路人甲");
	insert(eMod::e龙龟, 88, 83, eD::LD, "驼背大鼋");

	////////////////////////////////////////////////////////////////////////// 国境
	init("大唐国境", 1110, 0x481296D9, "");
	insert(338, 147, "长安城", 18, 9);
	insert(7, 79, "大唐境外", 630, 97);
	insert(49, 330, "阴曹地府", 136, 9);
	insert(316, 301, "江州衙门", 17, 9);
	insert(227, 287, "江州民居2", 24, 10);
	insert(302, 257, "江州民居3", 24, 10);
	insert(120, 189, "金山寺", 33, 8);
	insert(262, 301, "江州民居1", 17, 9);
	insert(eMod::驿站老板, 87, 250, eD::RD, "", script驿站("长安城", 273, 39));
	insert(eMod::赵捕头, 332, 30, eD::RD, "牢房守卫", script传送("牢房", 32, 14));
	insert(eMod::柳飞絮, 220, 62, eD::RD, "接引仙女", script传送("普陀山", 75, 17));
	insert(eMod::e护卫, 295, 288, eD::LD, "衙门守卫");
	insert(eMod::e护卫, 300, 285, eD::LD, "衙门守卫");
	insert(eMod::e黑山老妖, 98, 285, eD::RD, "黑山老妖");
	insert(eMod::教书先生, 310, 220, eD::LD, "吴文彩");
	insert(eMod::刘老爹, 260, 238, eD::RD, "吴老爹");
	insert(eMod::小桃红, 166, 304, eD::LD, "小芸芸");
	insert(eMod::e慧海, 178, 90, eD::LD, "者释和尚");
	insert(eMod::e慧海, 187, 152, eD::RD, "业释和尚");
	insert(eMod::e慧海, 138, 177, eD::RD, "海释和尚");
	insert(eMod::樵夫, 88, 220, eD::LD, "大生");
	insert(eMod::e星灵仙子, 40, 160, eD::LD, "白琉璃");
	insert(eMod::婆婆, 252, 303, eD::LD, "刘母");
	insert(eMod::e虾兵, 242, 262, eD::RD, "虾兵");
	insert(eMod::海产收购商, 151, 255, eD::RD, "渔翁");
	insert(eMod::小二, 66, 69, eD::LD, "", "卖烹饪");
	insert(eMod::婆婆, 24, 29, eD::RD);
	insert(eMod::王大嫂, 301, 301, eD::LD, "殷温娇");
	insert(eMod::e雨师, 41, 239, eD::RD, "山神");
	insert(eMod::超级巫医, 54, 75, eD::LD, "", _超级巫医);
	insert(eMod::火焰山土地, 173, 262, eD::R, "大唐国境土地", _大唐国境土地);

	init("江州民居1", 1149, 0x00000000, "");
	insert(23, 6, "大唐国境", 260, 297);

	init("江州民居2", 1167, 0x00000000, "");
	insert(28, 9, "大唐国境", 231, 283);
	insert(eMod::小桃红, 12, 10, eD::RD, "文秀");

	init("江州民居3", 1167, 0x00000000, "");
	insert(28, 9, "大唐国境", 307, 252);

	init("江州衙门", 1168, 0x00000000, "");
	insert(12, 8, "大唐国境", 308, 293);
	insert(eMod::e护卫, 23, 17, eD::LD, "刘洪");
	insert(eMod::赵捕头, 16, 13, eD::RD, "衙役");
	insert(eMod::赵捕头, 13, 12, eD::RD, "衙役");
	insert(eMod::赵捕头, 23, 7, eD::LU, "衙役");
	insert(eMod::赵捕头, 26, 9, eD::LU, "衙役");

	init("金山寺", 1153, 0x00000000, "");
	insert(40, 7, "大唐国境", 127, 182);
	insert(eMod::唐僧, 14, 13, eD::RD, "玄奘");
	insert(eMod::e雨师, 35, 12, eD::LD, "酒肉和尚");

	init("牢房", 1175, 0x00000000, "");
	insert(27, 13, "大唐国境", 333, 27);


	////////////////////////////////////////////////////////////////////////// 境外
	init("大唐境外", 1173, 0x52CA91A8, "");
	insert(637, 109, "大唐国境", 17, 72);
	insert(527, 117, "盘丝岭", 180, 12);
	insert(632, 76, "五庄观", 17, 15);
	insert(7, 49, "狮驼岭", 118, 90);
	insert(54, 117, "魔王寨", 24, 19);
	insert(406, 57, "高老庄大厅", 23, 16);
	insert(454, 100, "高小姐闺房", 14, 6);
	insert(7, 23, "碗子山", 75, 9);
	insert(eMod::eJueSe逍遥生, 233, 7, eD::LD, "白衣人");
	insert(eMod::e赌徒, 352, 3, eD::RU, "白鹿精");
	insert(eMod::e狐狸精, 349, 5, eD::RU, "玉面狐狸");
	insert(eMod::马副将, 592, 17, eD::RD, "刘洪");
	insert(eMod::e强盗, 587, 20, eD::LD, "李彪");
	insert(eMod::e强盗, 608, 58, eD::LD, "二当家");
	insert(eMod::至尊宝, 140, 60, eD::LD);
	insert(eMod::火焰山土地, 537, 88, eD::LD, "土地公公");
	insert(eMod::e猪八戒, 633, 5, eD::LD, "天蓬元帅");
	insert(eMod::e天兵, 322, 72, eD::LD, "姚太尉");
	insert(eMod::e星灵仙子, 317, 71, eD::RD, "阿紫");
	insert(eMod::e天兵, 234, 57, eD::LD, "天兵飞剑");
	insert(eMod::e沙和尚, 245, 64, eD::LD, "卷帘大将");
	insert(eMod::周猎户, 208, 102, eD::LD, "张猎户");
	insert(eMod::e山贼, 94, 90, eD::LD, "山贼头子");
	insert(eMod::e护卫, 544, 55, eD::RD, "1号烽火台");
	insert(eMod::e护卫, 572, 43, eD::LD, "2号烽火台");
	insert(eMod::e护卫, 614, 81, eD::LD, "3号烽火台");
	insert(eMod::e蛤蟆精, 557, 53, eD::LD, "蛤蟆怪");
	insert(eMod::e空度禅师, 350, 30, eD::RD, "云游僧");
	insert(eMod::百晓星君, 322, 98, eD::LD, "水云仙");
	insert(eMod::e野猪, 483, 7, eD::LD, "野猪王");
	insert(eMod::e骷髅怪, 576, 24, eD::LD, "偷尸鬼");
	insert(eMod::e牛妖, 87, 77, eD::LD, "牛将军");
	insert(eMod::e野鬼, 602, 102, eD::LD, "冤魂");
	insert(eMod::e强盗, 562, 85, eD::LD, "强盗头子");
	insert(eMod::驿站老板, 205, 27, eD::LD, "", _驿站老板);
	insert(eMod::驿站老板, 8, 66, eD::LD, "", script驿站("朱紫国", 13, 7));
	insert(eMod::超级巫医, 408, 13, eD::LD, "", _超级巫医);
	insert(eMod::小桃红, 559, 104, eD::LD, "少女");
	insert(eMod::婆婆, 536, 30, eD::LD, "老太婆");
	insert(eMod::刘老爹, 554, 10, eD::LD, "老太爷");
	insert(eMod::火焰山土地, 238, 112, eD::LD, "", script传送("墨家村", 72, 6));
	insert(eMod::e兔子怪, 282, 5, eD::LU, "云里雾");
	insert(eMod::火焰山土地, 52, 16, eD::LD, "南赡部州土地", script传送("长寿郊外", 89, 15));
	insert(eMod::空慈方丈, 16, 106, eD::LD, "灵山接引僧", script传送("小西天", 90, 20));
	insert(eMod::花儿, 190, 10, eD::LD, "幻影哒哒", script传送("天机城", 31, 22));

	init("高老庄大厅", 1170, 0x00000000, "");
	insert(16, 14, "大唐境外", 397, 49);
	insert(eMod::刘老爹, 30, 20, eD::LD, "高老先生");

	init("高小姐闺房", 1171, 0x00000000, "");
	insert(9, 6, "大唐境外", 445, 93);
	insert(eMod::小桃红, 13, 9, eD::LU, "高翠兰");

	////////////////////////////////////////////////////////////////////////// 东海湾
	init("东海湾", 1506, 0x3303D9A1, "");
	insert(2, 84, "建邺城", 237, 126);
	insert(4, 8, "建邺城", 271, 28);
	insert(95, 7, "东海海底", 10, 50);
	insert(9, 115, "桃源村", 19, 9);
	insert(eMod::赵元宝, 60, 48, eD::RD, "牛二");
	insert(eMod::柳飞絮, 53, 84, eD::RD, "楚恋依");
	insert(eMod::e虾兵, 109, 90, eD::LD, "老虾", script传送("龙宫", 21, 12));
	insert(eMod::驿站老板, 62, 19, eD::RD, "船夫", script传送("傲来国", 166, 16));
	insert(eMod::e狐狸精, 88, 106, eD::LD, "玉面公主");
	insert(eMod::张老头, 85, 33, eD::LD, "林老汉", script传送("东海岩洞", 15, 10));


	init("东海岩洞", 1126, 0x63033A32, "");
	insert(10, 19, "东海湾", 86, 30);
	insert(17, 38, "地狱迷宫四层", 99, 58);

	init("东海海底", 1507, 0xC8748621, "");
	insert(12, 62, "东海湾", 84, 15);
	insert(88, 60, "沉船", 29, 61);

	init("沉船", 1508, 0x905A7A55, "");
	insert(24, 66, "东海海底", 81, 53);
	insert(72, 11, "沉船底舱", 16, 16);


	init("沉船底舱", 1509, 0x00000000, "");
	insert(11, 23, "沉船", 66, 15);
	insert(eMod::e野鬼, 23, 13, eD::LU, "商人的鬼魂");


	////////////////////////////////////////////////////////////////////////// 花果山
	init("花果山", 1514, 0x30CBF5F6, "");
	insert(6, 11, "傲来国", 212, 139);
	insert(65, 74, "水帘洞", 19, 16);
	insert(145, 12, "幻境水帘洞", 22, 15);
	insert(eMod::火焰山土地, 28, 98, eD::LD, "花果山土地", script传送("北俱芦洲", 195, 105));
	insert(eMod::e巨力神猿, 37, 45, eD::LD, "老马猴");
	insert(eMod::e长眉灵猴, 133, 78, eD::LD, "侯医仙");
	insert(eMod::e巨力神猿, 100, 5, eD::LD, "马猴", script传送("海底迷宫一层", 30, 26));
	insert(eMod::e孙悟空, 78, 110, eD::RD, "美猴王");

	init("水帘洞", 1103, 0x00000000, "");
	insert(5, 18, "花果山", 54, 68);
	insert(eMod::e孙悟空, 70, 49, eD::LD, "美猴王");


	////////////////////////////////////////////////////////////////////////// 江南野外
	init("江南野外", 1193, 0x242616F7, "");
	insert(153, 54, "建邺城", 19, 8);
	insert(19, 111, "长安城", 503, 7);
	insert(eMod::仓库管理员, 103, 95, eD::LD, "江湖奸商", script商店("3级药品"));
	insert(eMod::小桃红, 22, 90, eD::LU, "罗纤纤");
	insert(eMod::小桃红, 32, 21, eD::RD, "卵二姐");
	insert(eMod::樵夫, 133, 22, eD::LD);

	////////////////////////////////////////////////////////////////////////// 谢阳山
	init("解阳山", 1042, 0x1DF0967E, "");
	insert(97, 5, "宝象国", 113, 106);
	insert(7, 10, "子母河底", 77, 82);
	insert(eMod::超级巫医, 56, 52, eD::RD, "", _超级巫医);
	insert(eMod::婆婆, 55, 8, eD::LD, "路人老婆婆");
	insert(eMod::罗道人, 52, 81, eD::LD, "守门道人");
	insert(eMod::罗道人, 107, 69, eD::RD, "守泉道人");
	insert(eMod::e机关兽, 42, 87, eD::RD, "后院机关兽");

	////////////////////////////////////////////////////////////////////////// 凌云渡
	init("凌云渡", 1920, 0x397AD647, "");
	insert(112, 8, "丝绸之路", 18, 10);

	////////////////////////////////////////////////////////////////////////// 柳林坡
	init("柳林坡", 1233, 0xB654F9E7, "");
	insert(6, 3, "比丘国", 40, 80);
	insert(134, 21, "长寿郊外", 30, 90);


	////////////////////////////////////////////////////////////////////////// 墨家村
	init("墨家禁地", 1221, 0x2611E02E, "");
	insert(24, 114, "墨家村", 43, 154);

	////////////////////////////////////////////////////////////////////////// 女娲
	init("女娲神迹", 1201, 0x78D6FD06, "");
	insert(40, 32, "北俱芦洲", 12, 156);
	insert(eMod::e律法女娲, 45, 36, eD::LD, "神殿守护者");
	insert(eMod::超级巫医, 88, 58, eD::LD, "", _超级巫医);

	////////////////////////////////////////////////////////////////////////// 蓬莱
	init("蓬莱仙岛", 1207, 0xC27C1229, "");
	insert(9, 45, "傲来国", 25, 97);
	insert(36, 43, "大蛇洞", 20, 20);
	insert(eMod::福星, 46, 129, eD::LD);
	insert(eMod::禄星, 34, 127, eD::RU);
	insert(eMod::e红萼仙子, 79, 12, eD::LD, "桃花令使");
	insert(eMod::清风, 157, 116, eD::LD, "道童");
	insert(eMod::清风, 79, 116, eD::LD, "琴童");
	insert(eMod::超级巫医, 137, 64, eD::LD, "", _超级巫医);


	init("大蛇洞", 1234, 0xB28AB6EF, "");
	insert(39, 30, "蓬莱仙岛", 29, 38);

	////////////////////////////////////////////////////////////////////////// 丝绸之路
	init("丝绸之路", 1235, 0xB496D4E2, "");
	insert(391, 90, "宝象国", 13, 70);
	insert(456, 2, "西梁女国", 30, 12);
	insert(597, 88, "长寿郊外", 24, 31);
	insert(302, 86, "朱紫国", 135, 7);
	insert(156, 80, "须弥东界", 65, 14);
	insert(14, 7, "凌云渡", 104, 12);
	insert(348, 5, "比丘国", 20, 57);

	////////////////////////////////////////////////////////////////////////// 碗子山
	init("碗子山", 1228, 0x8996BDDE, "");
	insert(64, 174, "波月洞", 19, 124);
	insert(4, 9, "宝象国", 148, 9);
	insert(91, 9, "大唐境外", 13, 20);
	insert(eMod::火焰山土地, 24, 15, eD::R, "土地", script传送("无底洞", 80, 122));

	////////////////////////////////////////////////////////////////////////// 小西天
	init("小西天", 1203, 0xF0CE9045, "");
	insert(24, 220, "小雷音寺", 166, 13);
	insert(eMod::e大力金刚, 28, 206, eD::RD, "守门金刚");
	insert(eMod::e大力金刚, 41, 214, eD::RD, "守门金刚");
	insert(eMod::小西天长和尚, 75, 17, eD::LD, "灵山老僧", script传送("大唐境外", 17, 103));


	init("小雷音寺", 1204, 0xC8011EF1, "");
	insert(176, 5, "小西天", 32, 211);
	insert(eMod::小西天长和尚, 62, 99, eD::RU, "阿傩");
	insert(eMod::小西天长和尚, 80, 109, eD::LD, "迦叶");
	insert(eMod::e金身罗汉, 134, 33, eD::RU, "护法罗汉");
	insert(eMod::e金身罗汉, 152, 42, eD::LD, "护法罗汉");
	insert(eMod::e大力金刚, 151, 17, eD::RD, "护法金刚");
	insert(eMod::e大力金刚, 169, 25, eD::RD, "护法金刚");


	////////////////////////////////////////////////////////////////////////// 须弥东界
	init("须弥东界", 1242, 0x5434F561, "");
	insert(58, 3, "丝绸之路", 168, 78);

	////////////////////////////////////////////////////////////////////////// 月宫
	init("月宫", 1114, 0x6B7904C6, "");
	insert(121, 10, "天宫", 60, 153);
	insert(103, 61, "广寒宫", 17, 10);
	insert(eMod::樵夫, 9, 34, eD::LD, "吴刚");
	insert(eMod::柳飞絮, 105, 57, eD::LD, "月香侍女");
	insert(eMod::e天兵, 101, 55, eD::RU, "康太尉");

	init("广寒宫", 1531, 0x00000000, "");
	insert(14, 10, "月宫", 96, 57);
	insert(eMod::嫦娥, 31, 18, eD::LD);

	////////////////////////////////////////////////////////////////////////// 子母河
	init("子母河底", 1041, 0xADBB5864, "");
	insert(73, 91, "解阳山", 12, 6);
	insert(15, 10, "西梁女国", 140, 18);
	insert(eMod::超级巫医, 36, 31, eD::RD, "", _超级巫医);
	insert(eMod::e蚌精, 103, 43, eD::LU, "美美");
	insert(eMod::e蚌精, 100, 51, eD::RD, "珍珍");
	insert(eMod::e蚌精, 102, 67, eD::RD, "珠珠");
	insert(eMod::上官丞相, 118, 53, eD::LD, "姜国师");

	////////////////////////////////////////////////////////////////////////// 蟠桃园
	init("蟠桃园", 1231, 0x5B4018EF, "");
	insert(143, 6, "天宫", 8, 71);

	////////////////////////////////////////////////////////////////////////// 麒麟山
	init("麒麟山", 1210, 0x279AF873, "");
	insert(17, 126, "太岁府", 54, 4);
	insert(176, 5, "朱紫国", 21, 91);
	insert(61, 4, "宝象国", 12, 8);
	insert(eMod::e野猪精, 111, 109, eD::LD, "有来有去");
	insert(eMod::超级巫医, 99, 62, eD::LD, "", _超级巫医);

	init("太岁府", 1211, 0x370E2580, "");
	insert(58, 4, "麒麟山", 22, 121);
	insert(eMod::e貔貅, 43, 77, eD::LD, "赛太岁");
	insert(eMod::金圣宫, 25, 69, eD::RD);


	////////////////////////////////////////////////////////////////////////// 无名鬼城
	init("无名鬼城", 1202, 0x3FCA8C5A, "地狱迷宫5");
	insert(12, 6, "地狱迷宫四层", 101, 60);
	insert(eMod::超级巫医, 65, 100, eD::LD, "", _超级巫医);
}




txtMap::txtMap()
{
	initCA();
	initJY();
	initAL();
	initCS();
	initCity();
	initMenpai();
	initMaze();
	initHome();
	initField();

	////////////////////////////////////////////////////////////////////////// 帮派
	init("白虎堂", 1814, 0x00000000, "帮派");
	insert(13, 10, "长安城", 386, 266);
	insert(eMod::周猎户, 24, 15, eD::LD, "白虎堂总管");

	init("朱雀堂", 1874, 0x00000000, "帮派");
	insert(14, 11, "长安城", 390, 260);
	insert(eMod::周猎户, 39, 24, eD::LD, "朱雀堂总管");

	init("青龙堂", 1865, 0x00000000, "帮派");
	insert(30, 8, "长安城", 390, 260);
	insert(eMod::周猎户, 20, 13, eD::RD, "青龙堂总管");


	init("玄武堂", 1845, 0x00000000, "帮派");
	insert(29, 9, "长安城", 390, 260);
	insert(eMod::周猎户, 16, 13, eD::RD, "玄武堂总管");

	init("帮派药房", 1854, 0x00000000, "");
	insert(12, 7, "长安城", 386, 266);
	insert(eMod::轿夫, 15, 13, eD::RD, "修炼指导师", _帮派修炼指导师);
	insert(eMod::当铺老板, 23, 10, eD::LD, "福利总管", _帮派福利总管);

	////////////////////////////////////////////////////////////////////////// 帮战
	init("帮派竞赛", 1511, 0xB9E253E6, "帮战入场");
	insert(eMod::守门天将, 16, 90, eD::RD, "帮派竞赛主持人", "帮派竞赛_离开场地");

	////////////////////////////////////////////////////////////////////////// 墨家村
	init("墨家村", 1218, 0xD20E78BF, "");
	insert(32, 116, "墨家民居", 19, 21);
	insert(85, 106, "墨家民居", 62, 10);
	insert(80, 45, "墨家民居2", 15, 13);
	insert(88, 8, "大唐境外", 235, 110);
	insert(50, 161, "墨家禁地", 21, 105);
	insert(eMod::巨子, 34, 152, eD::LD);
	insert(eMod::小笛, 75, 34, eD::LD);
	insert(eMod::莫夫人, 74, 80, eD::LD);
	insert(eMod::莫爷爷, 37, 109, eD::LD);

	init("墨家民居", 1219, 0x00000000, "");
	insert(10, 17, "墨家村", 25, 108);
	insert(58, 6, "墨家村", 78, 95);

	init("墨家民居2", 1220, 0x00000000, "");
	insert(7, 14, "墨家村", 70, 44);

	////////////////////////////////////////////////////////////////////////// 桃源村
	init("桃源村", 1003, 0x1F812A17, "");
	insert(162, 52, "桃源村村长家", 17, 9);
	insert(17, 4, "东海湾", 17, 112);
	insert(eMod::药店老板, 136, 50, eD::LD, "玄大夫");
	insert(eMod::颜如羽, 125, 50, eD::LD, "雨画师");

	init("桃源村村长家", 1012, 0x00000000, "");
	insert(11, 7, "桃源村", 160, 46);
	insert(eMod::刘老爹, 20, 11, eD::LD, "桃源村长");

	////////////////////////////////////////////////////////////////////////// 仙缘洞天
	init("仙缘洞天", 1216, 0x184AA512, "");
	insert(222, 76, "朱紫国", 74, 14);
	insert(eMod::e大大王, 23, 58, eD::LD, "百兽王", _系统装扮坐骑);
	insert(eMod::e凤凰, 148, 90, eD::LD, "御兽仙");

	////////////////////////////////////////////////////////////////////////// 战神山
	init("战神山", 1205, 0xCB3B68B8, "");
	insert(126, 42, "长安城", 349, 73);
	insert(11, 45, "神木林", 55, 21);
	insert(eMod::e蚩尤, 59, 99, eD::RD, "蚩尤");


	////////////////////////////////////////////////////////////////////////// 赤水洲
	// 1259
	init("赤水洲", 1258, 0x00000000, "");
	insert(102, 80, "女魃墓", 50, 100);
	insert(156, 11, "大唐国境", 180, 260);


	////////////////////////////////////////////////////////////////////////// 其他
	init("独家小院", 1446, 0x8FA4C62A, "");
	insert(72, 60, "顶级豪宅10", 50, 10);


	////////////////////////////////////////////////////////////////////////// 任务或副本
	init("英雄大会", 1197, 0x00000000, "比武场");
	insert(eMod::朱紫校尉, 15, 18, eD::RD, "传送人", "英雄大会_离开场地");

}

