#include "txtIcon.h"
#include "eMod.h"

#include "txtMedicine.h"
#include "txtStone.h"
#include "txtJiaju.h"
#include "txtSkill.h"
#include "txtPet.h"

ccc_txt_instance_cpp(txtIcon);


int txtIcon::getWeaponLv1ById(int id)
{
	if (id <= 8)
	{
		return id;
	}
	if (id <= 17)
	{
		return 9 + (id - 9) / 3;
	}
	if (id <= 26)
	{
		return 12 + (id - 18) / 3;
	}
	if (id == 27)
	{
		return 15;
	}
	return 16;
}


int txtIcon::getWeaponIdxById(int id)
{
	if (id <= 26)
	{
		return id / 3;
	}
	return id - 18;
}


int txtIcon::getNeckBeltLv1ById(int id)
{
	if (id < 3)
	{
	}
	else if (id < 15)
	{
		id = 3 + (id - 3) / 2;
	}
	else
	{
		id = id - 6;
	}
	return id;
}


txtIcon::txtIcon()
{
	sTable table;
	for (int e = (int)eIcon::eIcon0; e <= (int)eIcon::eIconEnd; ++e)
	{
		_tables.insert(std::make_pair((eIcon)e, table));
	}
	init();
}


void txtIcon::initIdx()
{
	_idx = -1;
}

void txtIcon::initTable(eIcon e)
{
	_table = &_tables.at(e);
}


void txtIcon::insert(ulong small, ulong big, int temp, const std::string& name, const std::string&  desc)
{
	_item.small = small;
	_item.big = big;
	_item.name = name;
	_item.desc = desc;
	_item.price = (temp == 0) ? c1000 : temp;
	_table->insert(std::make_pair(++_idx, _item));
}


void txtIcon::insertWeapon(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc)
{
	insert(small, big, temp, name, desc);
	// 暗夜 暗夜 暗夜 ...
	if (_idx >= 9 && _idx <= 24 && _idx % 3 == 0)
	{
		insert(small, big, temp, name, desc);
		insert(small, big, temp, name, desc);
	}
}


void txtIcon::insertJiaju(eIcon e, ulong small, ulong big, int temp, const std::string& name, const std::string& desc)
{
	insert(small, big, 0, desc, name);
	static txtJiaju::sJiaju jiaju;
	jiaju.lv = temp;
	txtJiaju::getInstance()->_tables.at(e).insert(std::make_pair(_idx, jiaju));
}

void txtIcon::insertJiaju(eIcon e, ulong small, ulong big, int temp, const std::string& name, const std::string& desc, const std::vector<ulong>& uids)
{
	insertJiaju(e, small, big, temp, name, desc);
	txtJiaju::getInstance()->_tables.at(e).at(_idx).uids = uids;
}

void txtIcon::insertJiaju1(ulong small, ulong big, int temp, const std::string& name, const std::string& desc)
{
	insertJiaju(eIcon::一家y, small, big, temp, name, desc);
}

void txtIcon::insertJiaju1(ulong small, ulong big, int temp, const std::string& name, const std::string& desc, const std::vector<ulong>& uids)
{
	insertJiaju(eIcon::一家y, small, big, temp, name, desc, uids);
}

void txtIcon::insertJiaju2(ulong small, ulong big, int temp, const std::string& name, const std::string& desc)
{
	insertJiaju(eIcon::二家e, small, big, temp, name, desc);
}

void txtIcon::insertJiaju2(ulong small, ulong big, int temp, const std::string& name, const std::string& desc, const std::vector<ulong>& uids)
{
	insertJiaju(eIcon::二家e, small, big, temp, name, desc, uids);
}

void txtIcon::insertJiaju3(ulong small, ulong big, int temp, const std::string& name, const std::string& desc)
{
	insertJiaju(eIcon::三家s, small, big, temp, name, desc);
}

void txtIcon::insertJiaju3(ulong small, ulong big, int temp, const std::string& name, const std::string& desc, const std::vector<ulong>& uids)
{
	insertJiaju(eIcon::三家s, small, big, temp, name, desc, uids);
}

void txtIcon::insertJiaju4(ulong small, ulong big, int temp, const std::string& name, const std::string& desc)
{
	insertJiaju(eIcon::四家s, small, big, temp, name, desc);
}

void txtIcon::insertJiaju4(ulong small, ulong big, int temp, const std::string& name, const std::string& desc, const std::vector<ulong>& uids)
{
	insertJiaju(eIcon::四家s, small, big, temp, name, desc, uids);
}



void txtIcon::insertMenpai(ulong small, ulong big, const std::string& name)
{
	insert(small, big, 0, name, "");
}



void txtIcon::insertSkill(ulong small, ulong big, eSkill e, const std::string& name, const std::string& desc, const std::string& emtpy /* = "" */)
{
	_item.small = small;
	_item.big = big;
	_item.name = name;
	_item.desc = desc;
	_item.price = (int)e;
	_table->insert(std::make_pair(_item.price, _item));
	txtSkill::getInstance()->insertCost(e, emtpy);
}



void txtIcon::insertCard(ulong small, ulong big, eMod e)
{
	const auto& pet = txtPet::getInstance()->getTables().at(e);
	if (small == 0)
	{
		small = 0x2E030271;
	}
	if (big == 0)
	{
		big = 0x8A3FAE92;
	}

	if (pet.heads.empty())
	{
		_item.small = /*(small == 0) ? 0x2E030271 :*/ small;
		_item.big = /*(big == 0) ? 0x8A3FAE92 :*/ big;
	}
	else
	{
		const auto& head1 = pet.heads.front();
		const auto& head2 = pet.heads.back();
		const auto& s1 = head1.at(eAct::Small);
		const auto& s2 = head2.at(eAct::Small);
		const auto& b1 = head1.at(eAct::Big);
		const auto& b2 = head2.at(eAct::Big);
		if (s2 > 0)
		{
			_item.big = s2;
		}
		else if (s1 > 0)
		{
			_item.big = s1;
		}
		else
		{
			_item.big = big;
		}

		if (b2 > 0)
		{
			_item.small = b2;
		}
		else if (b1 > 0)
		{
			_item.small = b1;
		}
		else
		{
			_item.small = small;
		}
	}
	_item.name = "变身卡";
	_item.desc = pet.name;
	_table->insert(std::make_pair((int)e, _item));
}



void txtIcon::initWeapon()
{
	initIdx();
	initTable(eIcon::剑剑j);
	insertWeapon(0x4B2CFFF0, 0xFA703674, 0, "青铜短剑", "青铜制成，上铸有简单的图案纹饰，初学者练习常用");
	insertWeapon(0xD7C9900A, 0x9A80EC6D, 0, "铁齿剑", "铁制的短剑，边缘带齿");
	insertWeapon(0x89A349EA, 0x070F7C34, 0, "吴越剑", "吴越之地产名剑，极其锐利");
	insertWeapon(0xEE21CDED, 0x5AD2FDAF, 0, "青锋剑", "剑长三尺，用起来方便灵活，是常用的兵器");
	insertWeapon(0xC0908502, 0xB8701E00, 0, "龙泉剑", "精铁铸造，又以龙泉之水淬制，上刻青龙。其利无比");
	insertWeapon(0x7A502ABD, 0x45FEC682, 0, "黄金剑", "真金铸脊，精钢淬锋，其光灿烂夺人眼，魔障远避不及");
	insertWeapon(0xC3114653, 0xA7025A68, 0, "游龙剑", "剑体九曲如龙形，覆鳞片，手弹其锋刃鸣如龙吟");
	insertWeapon(0x41B255E1, 0xAEB7FC97, 0, "北斗七星剑", "精炼白金之铁铸造，有北斗七星之纹饰");
	insertWeapon(0xDCE6182C, 0x81376F09, 0, "碧玉剑", "以寒冰碧玉制成,剑身如竹节,刚硬无比,难得的奇珍之物");
	insertWeapon(0x29F07659, 0xB80B9BB9, 0, "鱼肠", "上古名剑，细短柔软，可入鱼腹");
	insertWeapon(0x4990B38E, 0x4196C9AE, 0, "倚天", "剑身宽大，湛然如墨，骨锻其脊，血淬其锋，成绝世剑");
	insertWeapon(0x5CC10C8C, 0x215A249C, 0, "湛卢", "上古名剑，雾中山神铁所制，剑光如电，切金如泥");
	insertWeapon(0x65AD5663, 0xA82EC8F7, 0, "魏武青虹", "通体青亮如玉，长八尺有余，传说能在千里之外取人首级，吸血如虹。曾为魏王曹操配剑，曹死，遂失传。不知为何又重现江湖。");
	insertWeapon(0xA1B47E39, 0x33A4ABD5, 0, "灵犀神剑", "此剑长有七寸，有鼻有眼，与主人心有灵犀。平常藏于宝葫芦内，如果主人有令，则出三丈白光扣住敌人泥丸宫，斩仙魔鬼神怪如草不闻声。");
	insertWeapon(0x68401093, 0x769058EB, 0, "四法青云", "上有符印，分别为地，火，风，水四字。挥舞时候天昏地暗，火蛇狂舞，飞沙走石，龙腾海啸。");
	insertWeapon(0xAC6B67F6, 0x4CB1A575, 0, "冷霜九州", "通体洁白，冰晶雪魄，如淡烟璞玉，浑然天成。出则霜华满地，朔风回舞。其容清明，天高日晶；其气凛冽，砭人肌骨；其意萧条，山川寂寥。天下至寒至洁之物，惟赤子心可驭之。");
	insertWeapon(0x40E08E79, 0xB314A235, 0, "擒龙", "上古魔神所铸神兵，以之与八部天龙相抗。型如鱼骨，伸缩随心。刃翼可化出无数剑丝，其柔如春蚕吐丝，其韧如天地经纬，其锐如阴阳交融。");
	initIdx();
	initTable(eIcon::刀刀d);
	insertWeapon(0x4515D959, 0x1723C8E8, 0, "柳叶刀", "形如柳叶的细弯刀");
	insertWeapon(0x0AF4C698, 0xE7724956, 0, "苗刀", "苗疆常用的兵器，极细极尖锐");
	insertWeapon(0x8E41D7E9, 0xA4B97DC5, 0, "夜魔弯刀", "精钢制成的细弯刀，刀背密布细齿如夜魔之牙");
	insertWeapon(0x67D47D1B, 0xB906FBD0, 0, "金背大砍刀", "刀身挺直，以黄金镶背，刀道沉猛");
	insertWeapon(0x6680D572, 0xC354EF55, 0, "雁翅刀", "刀背布满粗大的锯齿，上挂银环，铿锵入耳如雁过九天");
	insertWeapon(0x47A33C00, 0xBE3A8136, 0, "破天宝刀", "刀光八面，劈风破天");
	insertWeapon(0x9E4C3BFD, 0x11A2B258, 0, "狼牙刀", "精钢打造，刀背密布狼牙锯齿");
	insertWeapon(0x27D9DEBA, 0xAF7F7EF9, 0, "龙鳞宝刀", "百练寒钢打造，以龙鳞装饰，身份的象征");
	insertWeapon(0x09B6C532, 0x10A2B56A, 0, "黑炎魔刀", "刀身透出森森鬼气，有着摄人心魄的魔力");
	insertWeapon(0x23FF2C01, 0x184466D1, 0, "冷月", "夜清冷，月露眉尖，笑引幽冥路");
	insertWeapon(0x74EDED5A, 0x094411C9, 0, "屠龙", "上古神兵，宝刀屠龙");
	insertWeapon(0x43D48B49, 0xEB99131E, 0, "血刃", "血红的刃，血红的光，以血洗天地");
	insertWeapon(0x0E64EB9F, 0x9685F062, 0, "偃月青龙", "此是三国时关公所用心爱配刀，传说刀柄乃青龙所化，刀身如半月，锋利无比，在百万军中取上将首级如探囊取物。关公死，刀柄不知去向，唯余此刀身");
	insertWeapon(0x1177A8DF, 0xB6F35D5E, 0, "晓风残月", "迅如晓风，刃如残月。此非中土大唐之物，乃是海外大食国宝刀。上面据说蛩伏着能实现愿望的神仙，如何召唤还是个秘密。传说是海外魔术师的发明。");
	insertWeapon(0x9FBE6EC2, 0x54FEC15B, 0, "斩妖泣血", "此刀乃是大唐名匠半生心血所沥而成的宝刀。传言他妻子被妖魔所害，所以将满腔愤怒与复仇欲望倾注于此刀之中，扬言谁能为他复仇，他便以此刀相赠。");
	insertWeapon(0x7801677F, 0x8D1421F8, 0, "业火三灾", "周身暗红，如浴血池，刃裂三线，引为三灾，中有赤瞳，勾人心火。敌心神既失，十方俱灭，惟余红莲：“汝一念起，业火炽然，非人燔汝，乃汝自燔。”");
	insertWeapon(0xD073B69A, 0xB44A9289, 0, "鸣鸿", "刀长三尺，与黄帝所配轩辕剑同炉而成，黄帝见其刀意过盛，恐反噬刀主，欲以轩辕剑毁之，此刀乃化玄红云鹊，穿霞而逝。");
	initIdx();
	initTable(eIcon::枪枪q);
	insertWeapon(0xB4C0875C, 0x2773559B, 0, "红缨枪", "白腊木制成的枪杆，柔韧有弹性");
	insertWeapon(0xECB9A5E2, 0x25B1C729, 0, "曲尖枪", "采用上等合木，枪尖九曲，是常用的兵器");
	insertWeapon(0x89FE6710, 0x3FC6E101, 0, "锯齿矛", "枪尖三陷三突，枪杆红绸缠绕，彩缨闪动令人眼花瞭乱");
	insertWeapon(0x944B634E, 0xE0B864AC, 0, "乌金三叉戟", "玄铁长枪，头部以乌金打造，气势如虹");
	insertWeapon(0x16C6CB63, 0x84EEA95C, 0, "火焰枪", "以火焰状的精铁代替枪缨，焰缘锋利无比");
	insertWeapon(0x41DC6B92, 0xB75EC89A, 0, "墨杆金钩", "乌金铁杆，枪尖粗大且制有金色的粗大倒钩，威猛无比");
	insertWeapon(0xF4E3B38B, 0x566E59C9, 0, "玄铁矛", "枪头玄铁制成，宽大沉重，可刺可砍，威势不可挡");
	insertWeapon(0xCD3D5EFE, 0x7F389033, 0, "金蛇信", "神木制杆，弯曲似蛇形，金枪透甲，腥红双叉似金蛇出信");
	insertWeapon(0x32DCD70B, 0x8DAE2408, 0, "丈八点钢矛", "通体百精纯钢，如天雷击落、蛟龙出海");
	insertWeapon(0x88EB5099, 0xF3859B91, 0, "暗夜", "通体乌黑,极细的枪尖无形中直抵咽喉,如暗夜中引魂之手");
	insertWeapon(0x58E84F3B, 0xE8872476, 0, "梨花", "锋刃五裂似梨花绽放,粉红的枪缨银白的枪,尽显潇洒风流");
	insertWeapon(0x5C995599, 0x6CF76490, 0, "霹雳", "以万古溶岩之火锤炼，枪杆似古树盘结，枪尖似雷霆霹雳");
	insertWeapon(0xD616FE3D, 0xD9F2160D, 0, "刑天之逆", "上古破坏神刑天出世之时，必应地上劫数。劫有五种，分为天兵火水土。此为他应兵劫出世所持之武器。形长两丈，刃如月牙，锋似寒星，身雕百龙蟠纹，挥舞只欲搅碎银汉，号为枪中霸君。");
	insertWeapon(0x58E503A5, 0x53A96316, 0, "五虎断魂", "出如虎奔，刺如虎爪，扫如虎尾，锁如虎噬，声如虎啸。使敌人魂断胆破，不战自溃。此谓之“五虎断魂。”有枪中王者之气。");
	insertWeapon(0xF46818B1, 0xE7D215B9, 0, "飞龙在天", "此枪掷出可在空中化为一条飞龙，从万丈高空中俯冲而下，将敌人撕成碎片。曾为文殊菩萨降妖密宝，如今幻化为一杆金龙宝枪。");
	insertWeapon(0x51FD7DFE, 0x3E0E55F0, 0, "天龙破城", "此戟以天外陨石炼九日九夜，雷生地底、天坠神龙乃成，西楚霸王项羽持之横行当世，睥睨天下英雄，故名“天龙破城”。戟尖如雪，齿如残阳，霸王既殁，佚于乌江，龙衔乃出。");
	insertWeapon(0x1A30A338, 0x079ABEF0, 0, "弑皇", "炎黄之战，杀怨之气俱归此兵。黄帝得胜，以此兵祭祀天地，誓曰:若治下三界失靖、四海不宁，则天下之人皆可持此兵取吾之首级！");
	initIdx();
	initTable(eIcon::锤子c);
	insertWeapon(0x2CEE4F98, 0xE7F5CE41, 0, "松木锤", "松木质轻，制成的锤主要作练习用");
	insertWeapon(0x98A216EE, 0x9FC965CC, 0, "镔铁锤", "镔铁打造的锤是价廉而常被采用的兵器");
	insertWeapon(0x8860CA14, 0x3937FBB5, 0, "八棱金瓜", "锤似金瓜，八棱突起，是实用的战锤");
	insertWeapon(0x224CB215, 0xD7688C47, 0, "狼牙锤", "锤面密布狼牙细齿，杀伤力不可小视");
	insertWeapon(0x7375F7C7, 0x98797EDE, 0, "烈焰锤", "锤面上制造了不少火焰波浪一般的锋刃，可怕的武器");
	insertWeapon(0xB083798F, 0x99F4BA0F, 0, "破甲战锤", "精钢打造的巨型战锤，上部粗大的尖齿，可破甲裂碑");
	insertWeapon(0x49874002, 0xE960DB71, 0, "震天锤", "寒钢制成的锤头巨大沉重，一击之下威势震天");
	insertWeapon(0xF51F4A99, 0x3A488284, 0, "巨灵神锤", "巨灵神所用神锤，锤似流星，非凡力可举，可挡十万天兵");
	insertWeapon(0x2A3E7CCD, 0x5DCB6420, 0, "天崩地裂", "静似天柱巍巍，动则天崩地裂");
	insertWeapon(0xFCFB1202, 0x3759FBFC, 0, "八卦", "八卦其间，太极天成，天地造化，混沌无常");
	insertWeapon(0x2BFA4A7B, 0x0180CBF4, 0, "鬼牙", "以万炼钢，合猛鬼牙，噬三界");
	insertWeapon(0xB5B520A1, 0xFF91F65A, 0, "雷神", "一击天地轰鸣，再击电光四起，三击万物俱灰");
	insertWeapon(0x456B1AC3, 0x8DCF1D25, 0, "混元金锤", "锤按六道之纹，柄接阴阳之气，持之者自有五行造化，诸天看护。");
	insertWeapon(0x803697D1, 0x19C58EB8, 0, "九瓣莲花", "此锤乃仙池中的一朵婷婷玉莲，花开九瓣，蕊露金蓬。不知道被谁采来，炼为兵器。虽然已过五百年，依然盛开如新发。");
	insertWeapon(0x40145F9D, 0xEB9D9A81, 0, "鬼王蚀日", "斩魔王之头为锤，隐隐发出邪气使日月无光。执此物则将与魔神签定契约，便能拥有魔王之怪力。");
	insertWeapon(0xC4C1179C, 0xEDC83DC1, 0, "狂澜碎岳", "此双锤乃水神共工掌中至宝，内收九曲黄河，出则天地齐喑，奔涛如雷。至其怒而触不周山，天柱折，地维绝，水潦尘埃俱归东南，双锤亦泯然其中，为黄帝所得。");
	// 无图
	insertWeapon(0xC4C1179C, 0xEDC83DC1, 0, "碎寂(无图)", "此锤乃盘古龙齿所化，外实中空，固若金汤。嘘为风雨，吹为雷电，舞之铿锵如鸣金铁，天下至阳至刚之物，邪魔宵小望之丧魂。");
	initIdx();
	initTable(eIcon::斧钺f);
	insertWeapon(0x47346EB2, 0x6CB3AF97, 0, "青铜斧", "以硬木和青铜制造的大斧，是常用的兵器");
	insertWeapon(0xAB6FB90E, 0x1E7FCF5D, 0, "开山斧", "铁铸的巨大战斧，沉重无比，力大者用以开石裂碑");
	insertWeapon(0x237C31DC, 0x36B42B1E, 0, "双面斧", "两面均制成半月状锋刃，双面制敌，力猛势强");
	insertWeapon(0x7C369410, 0x2A436917, 0, "双弦钺", "铁杆黝黑，银月如弦，舞动时眩人眼目");
	insertWeapon(0xFE6F55DE, 0x47A4C178, 0, "精钢禅钺", "精钢打造，环随舞动，铿锵入耳，震人心魄");
	insertWeapon(0x2FF648DB, 0xCEBCC875, 0, "黄金钺", "以华丽的黄金装饰,使其更加沉重威猛,金光起处血光飞溅");
	insertWeapon(0x4BA5B455, 0x89FD7995, 0, "乌金鬼头镰", "乌金打造的巨镰，透出森森鬼气，令人不寒而栗");
	insertWeapon(0x7D7D8675, 0x4F07DB2A, 0, "狂魔镰", "沉于万魔之地，染魔性，映魔心，挥之即魔瘴四起");
	insertWeapon(0x9E534FE2, 0xA6A9759A, 0, "恶龙之齿", "寒钢为柄，龙齿为刃，风过龙鸣，摄破敌胆");
	insertWeapon(0xBC4ED47B, 0xFD0F0F8E, 0, "破魄", "集艳日与阴月之精华，挥舞如日月同晖，中者形神俱灭");
	insertWeapon(0x2D6D80DE, 0x1CE23AB4, 0, "肃魂", "吸取无尽黑暗之气，肃清无规、无序、无章之魂");
	insertWeapon(0x33FFB254, 0xC205A64A, 0, "无敌", "斧杆以千年古木之根打造，盘桓虬曲");
	insertWeapon(0x6A2A5BD9, 0x151D1390, 0, "五丁开山", "上古蜀国有力士五人奉命凿通群山，见一大蛇尾在洞外，乃曳之出，其身长数十里，惊讶间，山崩，五丁与蛇俱死，遂化为神斧，执之者有开山之力。");
	insertWeapon(0x6AE62D28, 0xB6496E4F, 0, "元神禁锢", "为阴司轮转王用过之宝物。若地府中有鬼仙犯下大恶，即以此物拟其头，立将元神一吸而尽，再无转生可能。仔细看其刃缘，可照见无数痛苦鬼脸。");
	insertWeapon(0xB8BE33DB, 0x99412586, 0, "护法灭魔", "为佛门中护法之武器。柄乃是吴刚所伐月宫桂树之枝，鲁班雕刻。斧乃是老君以千年玄铁在八卦炉炼化而成，上有佛门梵文，妖怪见之退避三舍。");
	insertWeapon(0xDB68F9AF, 0x40229545, 0, "碧血干戚", "上古刑天与天帝争权，身首异处而壮志未陨。碧血零落、干缺戚残，后经无名氏冶于一炉，乃得神兵。长戚舞处，风云雷动，戚刃碧波流转，隐有巨盾透体而出，其鸣呜咽，如英雄泣。");
	insertWeapon(0xDD3E594B, 0x73EE03D7, 0, "裂天", "蚩尤随身魔武之一，取大荒四极异兽骨翼所制，形如巨镰，镰刃以海皇兽魂魄淬炼，隐然有嘶鸣之声。可裂天笞地，割风断雨。");
	initIdx();
	initTable(eIcon::扇子s);
	insertWeapon(0xD46B0AA6, 0x30BE3FE0, 0, "折扇", "普通的纸扇改装而成，可以此练习最基本的使扇方法");
	insertWeapon(0x11559F12, 0x56081ED7, 0, "铁骨扇", "铁制的扇骨会对敌人造成较大的威胁");
	insertWeapon(0x2C428B1A, 0x0C703039, 0, "精钢扇", "精钢制的扇骨，可以格挡锋利的兵器攻击");
	insertWeapon(0xE5672FA3, 0x9CFAE2F5, 0, "铁面扇", "连扇面也用铁片构成，更易格挡，晃动可出声，乱敌耳目");
	insertWeapon(0x2C461B5F, 0x39F30F5A, 0, "百折扇", "采用非常多的扇骨，扇面百折，非常坚固");
	insertWeapon(0x63F060CB, 0x0677BC6B, 0, "劈水扇", "挥舞之下可使狂风止，水断流");
	insertWeapon(0x62203F3C, 0x800BDB81, 0, "神火扇", "扇面用红绸制，此扇动则似神火四起，使敌人心不能宁");
	insertWeapon(0x46089506, 0x1BCA0906, 0, "阴风扇", "扇骨采玄冰制，阴风习习，让人不寒而粟");
	insertWeapon(0xE3400C46, 0x344100EB, 0, "风云雷电", "气势勇猛的大型折扇，扇开似风云突变，扇出似雷鸣电闪");
	insertWeapon(0x2F6ED2BD, 0x86D9D788, 0, "太极", "包容太极于其内，博采天地之灵气");
	insertWeapon(0xB5F645BD, 0x3571B70D, 0, "玉龙", "白玉制的扇骨，优雅灵巧，似白龙出海");
	insertWeapon(0x1ECE025B, 0x6BAEED5F, 0, "秋风", "一纸折扇，荡平天下事，一缕秋风，吹尽凡尘心");
	insertWeapon(0x32985958, 0x6A419161, 0, "画龙点睛", "本来是一把普通的折扇，只因张僧繇在上面画了条神龙，并点上了眼睛。此扇挥动的时候就隐隐有风雷之声，云雨之气，展开则有神龙奔出。");
	insertWeapon(0x8B0871B0, 0x72A7890D, 0, "秋水人家", "此扇面上不知何人所画的《秋水人家图》，出神入化，栩栩如生。更加奇异的是，展开居然可以进入其中，游山玩水，真是身临其境。看来上面有道家仙法无疑。");
	insertWeapon(0x512257F6, 0x56E6E9CA, 0, "逍遥江湖", "拿此扇行走江湖，有福祸凶吉可预先知晓。据说是钦天监台正先生袁天罡将他的奇门妙法写在上面，才使得此扇有逍遥的美名。");
	insertWeapon(0xD649DF86, 0xA27447BA, 0, "浩气长舒", "持之若登高望远，五湖四海俱在眼前。则不以物喜，不以己悲，心旷神怡，宠辱偕忘。有感浩然之气至大至刚，以直养而无害，充盈于天地之间。不亦快哉！不亦快哉！");
	insertWeapon(0x820FA440, 0x62561C26, 0, "星瀚", "三垣中坠，不知其故。展则漫天星辰失色，收则幽渺万籁无声。万顷星瀚，无始无终，无他无我，怎不使人目眩神驰？");
	initIdx();
	initTable(eIcon::爪子z);
	insertWeapon(0x0F0B87C0, 0xBFBC9604, 0, "铁爪", "镔铁制成的铁爪");
	insertWeapon(0xE0877204, 0x9798E279, 0, "天狼爪", "天山雪狼之爪，锐利无比");
	insertWeapon(0x1C400B14, 0xDD3935C6, 0, "幽冥鬼爪", "精钢打造，饰以冥文，透出森森鬼气");
	insertWeapon(0xCB4224A1, 0xA9856338, 0, "青龙牙", "龙牙状的尖刺，可以透入坚固的衣甲");
	insertWeapon(0xAF967654, 0xD266CDC9, 0, "勾魂爪", "状似银勾，夺命勾魂");
	insertWeapon(0xBFF8FEEE, 0x3DE6A666, 0, "玄冰刺", "吸玄冰阴寒之气，可以直透骨骸");
	insertWeapon(0x74489900, 0x18BB76AC, 0, "青刚刺", "寒刚玉所制，坚硬无比，可断金");
	insertWeapon(0x3D508D4D, 0x079BEA53, 0, "华光刺", "百炼纯钢打造，华光刺目");
	insertWeapon(0x069E329B, 0x462F3C4C, 0, "龙鳞刺", "金色似龙鳞的针刺");
	insertWeapon(0xC70C8B0D, 0x57B713CD, 0, "撕天", "天如幕，白光起，破九重天");
	insertWeapon(0xE4686241, 0xE5BCF143, 0, "毒牙", "恐惧，只有经历无尽虚空中袭来的毒牙才知其真意");
	insertWeapon(0xCE43D3D2, 0xCD2610C9, 0, "胭脂", "血红的颜色，胭脂的香气，将缤纷的灵魂凝结为黑白");
	insertWeapon(0x1778BE5F, 0xBD911862, 0, "九阴勾魂", "爪有九刺，阴寒冷酷，破颅勾魂，使正道名门闻名色变。为地藏王所得，将要销毁，不知何人盗出又重现江湖。");
	insertWeapon(0xD306DC84, 0x3AFDF972, 0, "贵霜之牙", "此物传说是天竺国千年神象之牙所雕刻而成，纯如傅霜，又有神象法力贯注其中，具有神秘的威力。");
	insertWeapon(0x7935A25A, 0x2A7CAA3A, 0, "雪蚕之刺", "此是昆仑山上雪蚕身上的毒毛，非常坚硬，穿犀牛皮如针穿薄纱，瞬间透入，刺中之后，使人身中热毒，如在灼热地狱之中。");
	insertWeapon(0xF541EB13, 0x73D90EAE, 0, "忘川三途", "忘川为生死界河，以善不善业为流水，水分三途，缓急不同。此爪凝三途之水，可证罪业，望之似缓，暗流甚疾。伤者不可骤脱，如坠地狱、饿鬼、畜生道。");
	insertWeapon(0xC8CE0A5C, 0xE481136D, 0, "离钩", "鸿蒙初辟之时，混沌之气混焉。后清浊渐离，有具神识之气胶而不舍，亦聚亦离，愁丝千丈，钩绊难舍，岁月风化遂成离钩。");
	initIdx();
	initTable(eIcon::棒槌b);
	insertWeapon(0xD96DA2AF, 0x1A91E959, 0, "细木棒", "看似细小却有不小的威力，可以当作兵器防身");
	insertWeapon(0x828C8992, 0x32B71DFB, 0, "金丝魔棒", "棒身缠以金丝，显得华丽");
	insertWeapon(0x66AAABEC, 0xF0FDCE22, 0, "玉如意", "细长的白玉棒，白玉使魔棒能力得到加强");
	insertWeapon(0xBDF61B3B, 0x7BAA9FA8, 0, "点金棒", "华丽的蛇形棒，相传作法之人常用其点石成金");
	insertWeapon(0x709C42D3, 0x2C2CD178, 0, "云龙棒", "棒身九曲，似云龙腾跃");
	insertWeapon(0xD9E425A6, 0x1D933E66, 0, "幽路引魂", "通体乌黑，引魂归冥");
	insertWeapon(0xCC46BE92, 0x69ED539B, 0, "满天星", "棒头细密的镶嵌了无数宝石，闪闪发光，似满天星辰");
	insertWeapon(0xCCAB8BD4, 0x3D8695AE, 0, "水晶棒", "通体以水晶制成，棒头镶嵌了纯净的水晶球，灵光闪闪");
	insertWeapon(0x5627348A, 0x149508BD, 0, "日月光华", "棒端有日月神珠，半黑半白，收太极其内，五行其间");
	insertWeapon(0xCBB9600B, 0x01F379BA, 0, "沧海", "静如海之渊深博从，动似海之激荡翻腾");
	insertWeapon(0xAEBF9A6E, 0x7C9A2B01, 0, "红莲", "碧杆红莲，阅众生相，度众生孽");
	insertWeapon(0x9AF7A9AC, 0x3C0511BC, 0, "盘龙", "身若九曲盘龙，口吞八卦金珠");
	insertWeapon(0x39C498CC, 0x5841B76B, 0, "降魔玉杵", "乃一块绝世好玉雕刻而成，杵头刻有仙家符咒。拿在手中，轻如鸿毛，打在人身上，重如泰山。");
	insertWeapon(0xD715A289, 0x7343D6DC, 0, "青藤玉树", "这是一件完美的艺术品，翡翠雕刻成的藤蔓缠绕在碧玉雕刻成的树干上，一朵红宝石雕刻成的鲜花正在怒放。有谁知道它还是一件仙家的妙宝，除魔的利器。");
	insertWeapon(0x2D364F04, 0x51646AEC, 0, "墨玉骷髅", "此魔棒上镶嵌着一个刻画精美的墨水晶骷髅，使它流露出神秘的死亡气息。看来这件兵器跟地府有很深的渊源。");
	insertWeapon(0x31A1E024, 0x01158BCC, 0, "丝萝乔木", "乃上古一对仙侣所化，丝萝出尘，花分五色；中为桐木，曾栖彩凤。千秋万载，其情不泯。湛湛然仙气缠绕，百邪不侵。后人赞曰：“醉向丝萝惊自醒，与君清耳听松湍。”");
	insertWeapon(0x1D6E08B8, 0xCC689690, 0, "醍醐", "盘古未分天地之时，混沌之中有异树焉。亿万年长成，亿万年花开，亿万年结果，果落则化为醍醐，持此杖者洞悉天地，与万物同息。");
	initIdx();
	initTable(eIcon::飘带p);
	insertWeapon(0x397A6BAF, 0x1572B635, 0, "五色缎带", "五色蚕丝织成的彩缎");
	insertWeapon(0xDE2BC89B, 0x6F96AC4F, 0, "幻彩银纱", "上等蚕丝与银丝混织成的纱带");
	insertWeapon(0xB7F52291, 0x04D7315A, 0, "金丝彩带", "金丝与彩缎编成的丝带");
	insertWeapon(0x051DAA24, 0xF25C5803, 0, "无极丝", "天地无极尽收于其间");
	insertWeapon(0x2F53A1FE, 0x0863F36E, 0, "天蚕丝带", "以名贵天蚕丝制成，可通生命之灵气");
	insertWeapon(0x085F35D4, 0xF0E30186, 0, "云龙绸带", "绸如云彩，龙隐其间");
	insertWeapon(0xFB55B1E2, 0x474E1622, 0, "七彩罗刹", "用各式丝绸编织而成的丝带");
	insertWeapon(0xA56391CE, 0x12E38410, 0, "缚神绫", "丝带可紧可松，传言可缚神灵");
	insertWeapon(0x306B5AF2, 0x0FA7C173, 0, "九天仙绫", "存于九天，吸日月玄灵");
	insertWeapon(0x43654288, 0xE9AD166A, 0, "彩虹", "以七彩天蚕丝制成，似天边彩虹");
	insertWeapon(0x5D671CD6, 0xA1AA6BF9, 0, "流云", "流光溢彩，似天边云彩幻生幻灭");
	insertWeapon(0xC011B909, 0x8E9005F7, 0, "碧波", "聚海之灵气，碧波起，天地清");
	insertWeapon(0x2409965D, 0x467A7DEF, 0, "秋水落霞", "“落霞与孤鹜齐飞，秋水共长天一色。”此带乃是天女掬长空之色，染落霞之艳织成。展开绚烂无比，使人俗念顿消，心无点尘。");
	insertWeapon(0x2B86C626, 0x7B20BB29, 0, "晃金仙绳", "此物可随主人意，捆住神仙魔怪，捆住之后，令其不能再施展变化之术。而且此绳坚韧异常，火烧刀砍不断。");
	insertWeapon(0x453F4C33, 0x55BECD78, 0, "此最相思", "“道是无情却有情，从来最苦是相思。”此物乃是太虚幻境警幻仙子敕令还情债之物。缠住之后，至死方休。尔虽有金石心，也顿为绕指柔，神仙也难逃此物。");
	insertWeapon(0xBA977FB7, 0x71D3B568, 0, "揽月摘星", "翩若惊鸿，婉若游龙，仿佛兮若轻云之蔽月，飘飖兮若流风之回雪。三垣为画布，此带为软毫，可清夜起舞，拟为漫天星宿平添花鸟虫鱼。");
	insertWeapon(0xCEC3F07C, 0xB90CDBE6, 0, "九霄", "九霄澄云所凝，诸天护佑，乾坤氤氲。形随意动，其高则冠盖乎九霄，其旷则笼罩乎八隅，祥瑞纷现，异香扑鼻。");
	initIdx();
	initTable(eIcon::鞭子b);
	insertWeapon(0x619D96BC, 0x2FA15D09, 0, "牛皮鞭", "用牛皮制的皮鞭，很容易得到的练习用品");
	insertWeapon(0x095025EB, 0xA5A9533C, 0, "牛筋鞭", "以上等牛筋制成，弹性极佳，抽之有破空之声");
	insertWeapon(0xBA1EEAE3, 0xBB448658, 0, "乌龙鞭", "以鲨鱼皮制成，表皮毛糙，极其坚韧");
	insertWeapon(0xC0AAC847, 0x87905DD7, 0, "钢结鞭", "以细钢环联结起一个个钢条，柔中带刚");
	insertWeapon(0xA5B9756D, 0x8F3DEC1A, 0, "蛇骨鞭", "结似蛇骨，环环相联，抖动时骨节相撞，噼啪作响");
	insertWeapon(0x1B90E6FA, 0x1C82F50B, 0, "玉竹金铃", "由玉制的竹节联结而成,节间缚着金铃,铃随鞭动,声声悦耳");
	insertWeapon(0x3959E1A8, 0x3B6C535B, 0, "青藤柳叶鞭", "采深山古藤制成，上缚柳叶刀片，刀光闪动，杀气逼人");
	insertWeapon(0x6E894417, 0xC0CED3A2, 0, "雷鸣嗜血鞭", "管节空洞，银钩闪闪，挥动时隐隐有风雷之音");
	insertWeapon(0x6182C9F2, 0x8AB6DF4B, 0, "混元金钩", "混元钢索之上缚有金钩，追命勾魂");
	insertWeapon(0x3EDB8A93, 0x894AD5CE, 0, "龙筋", "以恶龙之筋制成，挥舞若龙腾");
	insertWeapon(0xCEF75360, 0x4F61578E, 0, "百花", "龙藤塑其筋，百花其上，集仙灵之气，香飘四海");
	insertWeapon(0xC44A5FC1, 0x62CAE06A, 0, "吹雪", "鞭上石晶经千年生长，成雪花密布，映日月之光");
	insertWeapon(0x2B12494F, 0xDC82B518, 0, "游龙惊鸿", "此鞭舞动矫如游龙，翩若惊鸿，宛如活的一般。有人认为必然是因为仙家点化的功效。");
	insertWeapon(0x8B5224B1, 0xB8C6F8B9, 0, "仙人指路", "此鞭奇异之处在于打斗之时会自己寻找敌人弱点，或攻或守，或点或缠，如仙人指路飘忽不定，变化万端。又如灵蛇狂舞，使人眼花缭乱。");
	insertWeapon(0xCDB8515D, 0xD513997F, 0, "血之刺藤", "此鞭遍体生有倒刺，散发黑色邪气。传说打斗之时如巨蟒将敌人缠住，倒刺嵌入敌人体内，吸食其血肉。");
	insertWeapon(0x1931ABE1, 0xF9E833C4, 0, "牧云清歌", "此鞭具大神通，持之神虑清明，兼可驭使万物。素以苍穹为牧野，云霞为羔犊，驱鞭行于九天之上。清音四溢，如聆仙乐。");
	insertWeapon(0xE43C137D, 0x1F1D959B, 0, "霜陨", "昆仑之巅有涧曰冰溪，月华照则灿然如银，陨则凝霜聚雪。溪流九曲，矫然若蛟，后凝为软玉长鞭，姑射仙子倚为护身仙器。");
	initIdx();
	initTable(eIcon::环圈h);
	insertWeapon(0x0083B858, 0x1F608A99, 0, "黄铜圈", "黄铜制的环圈，握手处缚上丝线，是常用的兵器");
	insertWeapon(0x9BAF0A08, 0x1F3554C2, 0, "精钢日月圈", "精钢打造的圆环，外缘锋利");
	insertWeapon(0x9A4E0576, 0xEA136188, 0, "离情环", "乌金铁环，通体乌黑，似悠悠离情");
	insertWeapon(0x6A1A0F02, 0xAE5D50DF, 0, "金刺轮", "由多片精铁打造的极薄的锋刃组成，刃口白光闪闪");
	insertWeapon(0xDC4D3544, 0xCD3DBB3C, 0, "风火圈", "钢制的边缘有似火焰般的刀锋");
	insertWeapon(0x2949C51C, 0x24568920, 0, "赤炎环", "环边有锯齿，如太阳之火焰");
	insertWeapon(0xD5343644, 0xA5E9FF97, 0, "蛇形月", "划动时锋刃似盘卷的黑蛇，令人防不胜防");
	insertWeapon(0xDEB5166A, 0x601EFAE1, 0, "子母双月", "锋刃似弯月一般交错，可四面制敌");
	insertWeapon(0xF55DBFA6, 0x87B23BF7, 0, "斜月狼牙", "青玉制成，锋似狼牙");
	insertWeapon(0xA1A50B14, 0x38C280F3, 0, "如意", "白玉制成，光滑清丽，如意随心");
	insertWeapon(0x993EB125, 0x14334444, 0, "乾坤", "集天地乾坤之灵，可制万物");
	insertWeapon(0xD45008C2, 0xB0037FD8, 0, "月光", "清明无暇，似映月之光");
	insertWeapon(0x914931C5, 0xEBFAECC2, 0, "离情别恨", "乐莫乐兮新相知，悲莫悲兮生别离。这种感情是黯然消魂，永恨伤心的。所以有人制作了同心永结环，象征永不分离，在别离之后把玩，却更加伤感。");
	insertWeapon(0xAD5A158D, 0x62EF7ECA, 0, "金玉双环", "一为金环一为玉环，佩带起来铿锵作响，祥光袅绕。定然是受到福神的祝福，才能有这样的灵气。");
	insertWeapon(0x5788539F, 0x7A0BA596, 0, "九天金线", "此物套在手上，金光闪闪。圈飘金线，声音清越，守中有攻，刚柔并济。使敌人不知所措。");
	insertWeapon(0xB4F76303, 0xB91050BA, 0, "无关风月", "精玉双环，一名“离风”，一名“遮月”，舞之月影憧憧，别愁离绪，俱上心头，思之恻然。后人亦有诗云：人生自是有情痴，此恨不关风与月。");
	insertWeapon(0x5232CE82, 0x6316A455, 0, "朝夕", "此双环伴日月而生，沐浴光华，吞吐烟云，三清将其置于天穹之上，日夜吸纳诸天亿兆流光，朝夕霞雾源出于此。");
	initIdx();
	initTable(eIcon::双剑s);
	insertWeapon(0xBF76FEA3, 0x4F91A09A, 0, "双短剑", "青铜制的双短剑，制造简单，是练习常用的兵器");
	insertWeapon(0x45B93DE9, 0x87D2F501, 0, "镔铁双剑", "铁制双短剑，轻巧实用");
	insertWeapon(0x9971E216, 0xA03C7078, 0, "龙凤双剑", "双剑剑身一刻龙纹一刻凤饰，可同入一鞘");
	insertWeapon(0x4F398A42, 0x8438C5FE, 0, "竹节双剑", "精钢制成，剑身似竹节般伸长");
	insertWeapon(0x6D196F3D, 0x34CD8C35, 0, "狼牙双剑", "剑身向前方密布粗长的狼牙锯齿，令人胆寒");
	insertWeapon(0x2C37FC03, 0x68FC20D0, 0, "鱼骨双剑", "剑身似鱼骨，长满倒钩刺");
	insertWeapon(0x56F89322, 0x637FF159, 0, "赤焰双剑", "剑身赤红，齿如焰苗窜动，有一股刚烈之势");
	insertWeapon(0xE4FB266B, 0xCC599B35, 0, "墨玉双剑", "体采寒冰墨玉所制，暗光流动");
	insertWeapon(0x3903C91F, 0x15147143, 0, "梅花双剑", "千年古木所制，剑似梅枝");
	insertWeapon(0x8C2E662A, 0x92D21F0D, 0, "阴阳", "赤阳之铁成阳，玄冰之玉成阴，两仪相生，气韵非凡");
	insertWeapon(0x024BA3AD, 0x82320457, 0, "月光", "皎洁如白玉，清明如月光");
	insertWeapon(0xBE4D6372, 0x74405692, 0, "灵蛇", "采千年寒冰碧玉制成，通体碧绿，剑出似灵蛇出洞");
	insertWeapon(0x9F6A407F, 0x85AB6BB6, 0, "金龙双剪", "传说乃是一对金龙所化，头并头如剑，尾交尾如股。从半空中呼啸而下，一绞之力无人能挡。");
	insertWeapon(0x31D26320, 0x6DBE2388, 0, "连理双树", "一对痴情男女坟前精魂所化双树，攀枝连理，象征在世虽不能合枕，来世愿永无分离。以此木为剑，因至情贯其中，也可成绕指柔，也可以断金玉。");
	insertWeapon(0xFD9838FC, 0xCC7570D8, 0, "祖龙对剑", "三国时蜀帝刘备所用双剑。据说一为白龙所化，一为赤龙所化。白龙乃是秦皇，赤龙乃是汉祖。执之者当有九五之尊。");
	insertWeapon(0x7286299C, 0xC7A1153E, 0, "紫电青霜", "鸿蒙灵气之所钟，诸天精魄之所禳。异器天生，一派自然。紫电稚弱，性如婴孩，青霜老沉，俨如兄长。翛忽隐现，捷如流星，而啾啾呢喃，疑似紫燕青虬.");
	insertWeapon(0xD99398AA, 0x86DB08FD, 0, "浮犀", "九天玄女以夔牛之角所制双剑，锋锐无双，轻如无物。裁夔皮为鼓，助黄帝九击擒杀蚩尤。上书天书密咒，丹血为文，翠莹如碧。");
	initIdx();
	initTable(eIcon::宝珠b);
	insertWeapon(0x9B6F8E4F, 0xEBAE2F27, 0, "琉璃珠", "三色琉璃熔成的宝珠，轻盈剔透，适合新手携带。");
	insertWeapon(0x19545A75, 0x1ED2572C, 0, "水晶珠", "晶莹水晶打磨而成的水晶球，发出微微的光晕。");
	insertWeapon(0x9DE63984, 0x68D0AB22, 0, "珍宝珠", "东海海底方能寻得的巨大珍珠，光华缓缓流动，似是凝聚了海底之中游鱼的灵气。");
	insertWeapon(0xE3F2FCC8, 0xD1AD1C58, 0, "翡翠珠", "南蛮之地进献之翡翠，经能工巧匠九琢九磨，方成玲珑宝珠，通体翠绿凝碧，触手冰凉，仿似有仙气缭绕。");
	insertWeapon(0x0741D4A2, 0xE31123C5, 0, "莲华珠", "来自天竺佛国的灵巧宝珠，晶莹圆润，光华四溢，置于水中，可化作轻盈莲花，净水生香。");
	insertWeapon(0xE5CCAA29, 0x30893D44, 0, "夜灵珠", "白日之时看似平平无奇，置于灯火昏昏之处，方有幽光融融。其夜愈深，而光华愈明。");
	insertWeapon(0x49C1DCD8, 0x11A4CF70, 0, "如意宝珠", "琅嬛福地生香橼，百年方熟，熟而坠地，化为如意宝珠，鲜明莹洁，祥瑞兆也。");
	insertWeapon(0xE1028D58, 0x5E4586A2, 0, "沧海明珠", "东海之浪，西海之湍，南海之潮，北海之涌，凝为玲珑明珠，置于耳畔，可闻四海浪涛奔涌。");
	insertWeapon(0x0D1A31A8, 0x4F2619DF, 0, "无量玉璧", "奇珍璞玉，历神工鬼斧琢磨百年，方成无瑕白璧，明澈如镜，可见本心。心无旁骛，不惹尘埃。");
	insertWeapon(0xBA9A7ECF, 0x11A2D7CE, 0, "离火", "北地铁骨，质坚且寒，南疆离火，熔之成珠。铁骨灼灼，烈火熊熊，炽焰炎炎，刚猛之至。");
	insertWeapon(0xAA4C478C, 0xC9C775CA, 0, "飞星", "河汉渺渺，星华灿灿。流星坠地，而光华不灭，繁光云影，剔透灵动。");
	insertWeapon(0xE08E06D5, 0x2E46F689, 0, "月华", "芙蓉出水，风荷凌波。采月宫新荷之叶，凝流金月色之光，成琳琅花灯一盏，暖光融融，晴光皎皎。");
	insertWeapon(0xB6B6B46A, 0x10137391, 0, "回风舞雪", "洛水汤汤，钟灵毓秀。河洛之女，质比霜雪，态似惊鸿。一日，童心乍起，采河滨之蝶，沉水之冰，吟清歌而宝珠成，蝶舞之时，回风舞雪，琴音泠泠。");
	insertWeapon(0x5B985903, 0xA6319B57, 0, "紫金葫芦", "混沌初分，天开地辟，昆仑山脚下，生仙藤一缕，上结葫芦七枚，名曰紫金葫芦者，千年方得瓜熟蒂落，有吞吐万象之力。");
	insertWeapon(0xEBB497A1, 0xB4C393EE, 0, "裂云啸日", "烛龙之鳞，采璇玑之华，待千年。浴羲和之光，再千年。经九煅九灼，方熔为赤金之珠，其光煌煌，可照千里，其势熊熊，耀日贯虹。");
	insertWeapon(0xC1CB9186, 0xB9B58091, 0, "云雷万里", "北溟之鲲，化而为鹏，凌风而飞，翼若垂天之云，啸如雷霆之怒，水击三千，风驰如电。沉眠之时，化作神异之珠，聚风雷云电之力，有呼山啸海之能。");
	insertWeapon(0x4DB73A65, 0xF71E5F62, 0, "赤明", "鸿蒙初辟，首生盘古，垂死化身，齿骨为金石，精髓为珠玉，汗流为雨泽，呼啸为风雷，灵窍一点，聚天地浩气，化为宝珠“赤明”，虹霓为衣，金螭为息，吞云吐明，异光可传万里。");
	initIdx();
	initTable(eIcon::弓弩g);
	insertWeapon(0x41B2D367, 0x133E608F, 0, "硬木弓", "木头制成的短弓，质轻便携，很适合新手练习使用。");
	insertWeapon(0x6C23C13D, 0x81FFD69C, 0, "铁胆弓", "硬木制成的弓箭，背嵌铁条，射程很远。");
	insertWeapon(0x6C5260E4, 0x57E5E1DC, 0, "紫檀弓", "精致的紫楠木弓箭，云纹雕花流畅雅致。");
	insertWeapon(0x8650A79B, 0x41F987FC, 0, "宝雕长弓", "乌木长弓，弓身镌刻之宝雕，栩栩如生，振翅欲飞。");
	insertWeapon(0x0DF5E274, 0x2A1EFAF2, 0, "錾金宝弓", "黑檀宝弓，经巧匠之手精雕细錾，华贵不可方物。");
	insertWeapon(0xCA8212E7, 0x06590FE7, 0, "玉腰弯弓", "柘木宝弓嵌以碧绿美玉，质坚且韧，精准凌厉。");
	insertWeapon(0xF4060D55, 0x9D734C7A, 0, "连珠神弓", "玲珑连珠，发机如电，一发连五，绝无虚矢。");
	insertWeapon(0x54E5B6A0, 0xF527C861, 0, "游鱼戏珠", "弓箭之形仿若双鱼，共戏剔透宝珠。出箭之势，亦如游鱼嬉水，婉转灵动，让对手无从躲避。");
	insertWeapon(0x9E20BF15, 0xBE688888, 0, "灵犀望月", "天降奇石，锻为兵器，自生光华。美玉做灵犀之形，嵌于弓腰，祥瑞兆也。");
	insertWeapon(0xBC3AB157, 0x7533F133, 0, "非攻", "墨家机关之术神秘莫测，相传有采玉人偶得其残片，上记“非攻”弓弩，机括精妙，威力非常。遂寻美玉，勤琢磨，终得天下难见之绝品。");
	insertWeapon(0xE3E1B9B0, 0xE6E14F6A, 0, "幽篁", "潮音洞外梵音悠悠，云岚缭绕，幽篁万杆，满目翠色。林中紫竹既坚且韧，扣之琅然有金石声，金童子置之于老君炉中，锻成神弓，名曰“幽篁”。");
	insertWeapon(0x72747617, 0x3458C8F3, 0, "百鬼", "春秋时古墓中，青铜之樽，凝百鬼之魂，锻九千日，乃成。");
	insertWeapon(0xD61AC318, 0x38514961, 0, "冥火薄天", "幽冥之地，麒麟衔火而生，踏火而行，所经处金石皆熔，游九州聚天地精华，得遇有缘之士，乃化作良弓一柄，凌风驭火，箭矢如焰，有燎日之能。");
	insertWeapon(0xF5E28874, 0x21BC9299, 0, "龙鸣寒水", "云龙居寒水，可呼云雨，开江海，鸣动天地，腾云起风。此弩熔云龙之鳞，凝万年寒水之底，聚玄冰苦寒之气，千年方成，出矢如冰，霜寒雪冷。");
	insertWeapon(0x3F887D43, 0x1B0E29A4, 0, "太极流光", "天地之道，以阴阳二气造化万物，日月、风雨，刚柔、动静莫不合此道也。此番水火相逢，相生相克，有大神通。");
	insertWeapon(0x614BBFC4, 0xEFF9E2AE, 0, "九霄风雷", "灵凰栖九天，高飞穿云，清音裂石。妙手仙匠采灵凰之魄，河汉之星，云雷之怒，以九霄长风锻造千载而成此弓，箭簇既出，风雷声动，江海怒号。");
	insertWeapon(0x87FFC4D8, 0x5E404755, 0, "若木", "金乌栖若木，振翅日升，归巢日落，十鸟齐飞，则十日齐出，民不聊生。后羿采若木为弓，连射九日，凝金乌之魂于弓上，羲和光华，日夜不息。");
	initIdx();
	initTable(eIcon::法杖f);
	insertWeapon(0x0CC9E80F, 0x6620160B, 0, "曲柳杖", "说白了就是一根柳条...");
	insertWeapon(0x96263B85, 0xA77CD950, 0, "红木杖", "100%红木雕成,高硬度,高耐磨,并且自身散发出香味.");
	insertWeapon(0x76E8DB36, 0x4FA9B658, 0, "白椴杖", "用椴木精心雕凿而成的法杖，虽然硬度不及红木,但有极佳的韧性。");
	insertWeapon(0x005FCA79, 0xA3410B63, 0, "墨铁拐", "球墨铸铁制成的法杖,由于组织里的石墨以球形存在,其强度可以和中碳钢媲美!");
	insertWeapon(0xB8931FDA, 0x3E2E5C6E, 0, "玄铁牛角杖", "由极其稀有的钨钢制成,就算在1000度的环境下,依旧拥有极高的硬度.");
	insertWeapon(0xE571BB53, 0x7AB6F217, 0, "鹰眼法杖", "孤鹰展翅，划破长空，依照孤鹰之形打造的法杖，已经不是正常人类能理解的材料了。");
	insertWeapon(0xFA3EF70A, 0x54FC3093, 0, "腾云杖", "仙人踏云而至，有着祥云之形的云母石法杖，有着奇妙法力。");
	insertWeapon(0xB098CF62, 0x6491C11C, 0, "引魂杖", "点点萤光，引路幽魂，指引迷途幽魂的法杖，有着强大的法力。");
	insertWeapon(0x0FBD2462, 0x0C1C6129, 0, "碧玺杖", "碧霞莹莹，玉暖生烟，浑然天成的碧玉法杖，神妙异常。");
	insertWeapon(0x6CC0CCA6, 0x77670602, 0, "业焰", "取地狱燧石锻冶，燃万年业火之杖。“以业火乾枯，酬其宿债”，业焰之舞，焚尽世间罪孽。");
	insertWeapon(0xC72AF9EF, 0xCA0836FB, 0, "玉辉", "琉璃玉辉，星降人间，熠熠生辉的琉璃法杖，挥舞时如繁星落尽，蕴含无限灵力。");
	insertWeapon(0xF96BF48F, 0x3C320A37, 0, "鹿鸣", "牡鹿凄鸣，风云雷动，天下至寒之墨玉炼成鹿角之形，夹风雷之势，让敌人闻之色变。");
	insertWeapon(0xFAF674F6, 0xB3034039, 0, "庄周梦蝶", "“昔者庄周梦为蝴蝶，栩栩然蝴蝶也”梦中蝶舞花落，焉知人世几何，取冥府幽灯为首之杖，引路蝶翩然飞舞，如泣似诉，最善蛊惑人心。");
	insertWeapon(0xE122DAC7, 0x5B009969, 0, "凤翼流珠", "有凤来仪，为祥瑞之兆。炎帝融千金，取深海明珠，塑以凤凰振翅衔珠之形，炼得一杖，谓之光华灿烂，具百鸟朝凤皇者之气，深蕴妙法奥秘。");
	insertWeapon(0x5E7B5E65, 0xD9B5C967, 0, "雪蟒霜寒", "刘邦斩白蛇，取其精魄，封于至阴至寒之地，吸寒冰精华千年，蛇魄化杖，曰之“雪蟒霜寒”，阴鸷寒毒，唯奇人异士方可驾驭自如。");
	insertWeapon(0x33355BFC, 0xAD17AF09, 0, "碧海潮生", "应龙伏旱魃，寻深海冰晶，取潮涌奔腾之势，融白浪连山之气，吐龙息为灵珠，成龙神逐珠之形，终获一杖，名曰“碧海潮生”。");
	insertWeapon(0x609B96BB, 0x1CB08DEE, 0, "弦月", "盘古开天辟地之时，一外化陨铁落于不周山之巅，沐月华，吸星魄，尽得天地清明之气，化一杖，清辉万丈，疏影琉璃，曰之“弦月”。");
	initIdx();
	initTable(eIcon::巨剑j);
	insertWeapon(0xFB88103A, 0xCE44AF55, 0, "钝铁重剑", "废铁弃料打造的重剑，价格低廉，适宜新手");
	insertWeapon(0xD9AB10DD, 0x090CCA18, 0, "桃印铁刃", "常见铁剑，以桃木为剑柄");
	insertWeapon(0x5AEC04EE, 0xAA8F427F, 0, "赭石巨剑", "以赭石去杂质煅淬而成，色泽沉郁");
	insertWeapon(0x51105074, 0x976BFD27, 0, "璧玉长铗", "精铁重剑，剑身嵌美玉，碧波流光，颇有君子之风");
	insertWeapon(0x809D1FDD, 0xCC013376, 0, "青铜古剑", "青铜宝剑，古朴大气，然剑锋凌厉，不可小觑");
	insertWeapon(0xBD5C010E, 0xE8F34110, 0, "金错巨刃", "铁匠采丹阳铜矿冶炼锻造，剑身以镶金包裹，工艺精湛，灼灼夺目");
	insertWeapon(0x1F648228, 0x0B0AB6FB, 0, "惊涛雪", "铸剑师偶得深海晶石一块，冶炼成剑。挥斩之时，流光溢彩");
	insertWeapon(0x379213E4, 0xE98BD873, 0, "醉浮生", "浮生若梦，一醉解忧。以布裹之，掩锋芒，平杀气，大巧不工，颇具豪侠之意");
	insertWeapon(0x2E58E991, 0xE7692943, 0, "沉戟天戉", "原为沙场断戟，后经人收敛重铸，以缅忠魂。握之，勇武无惧");
	insertWeapon(0xEE633A71, 0x3ADE1603, 0, "昆吾", "前朝君主雄才大略，文治武功皆成鼎盛，有邦国朝献天降陨铁，以为祥瑞，遂寻当世铸剑高手，炼化成剑，彪炳功勋");
	insertWeapon(0x7B631424, 0x2952AF91, 0, "弦歌", "乐师师旷以剑为胆，棹伏羲木，铺天蚕丝，制成琴身重剑，以酬知己，友人闻弦歌而知雅意，奏高山流水，成一段佳话");
	insertWeapon(0x458E5B98, 0xF9D8AF7B, 0, "鸦九", "剑痴鸦九得欧冶子所遗铸剑秘法，铸长剑无名。因不舍爱剑磨损，剑成当日，即以冰匣封之。十余年后得人点拨开悟，欲拔剑出匣，然而冰匣早已与剑芯融为一体，不可分离，寻得熔岩炼化三年，方重铸此剑，剑身自此薄雾缭绕。");
	insertWeapon(0x5F69A15B, 0x60665CA2, 0, "秋水澄流", "泑山之畔盛产婴垣之玉，得蓐收赤足踏过而成金秋之色，胜碧玉琼瑶。有人界巧匠偶得之，不知何物，投剑炉一试，不想即刻炉毁剑成，更一日入秋，遂得此名");
	insertWeapon(0x6F6CAC00, 0x9B3ACC82, 0, "腾蛇郁刃", "中山之州有赤目飞蛇，乘雾游云，于柴桑之山嬉戏，疲乏后盘松石小憩，留蛇蜕一副，化为巨剑，此乃王道之剑");
	insertWeapon(0x84131194, 0xEDAE8F1A, 0, "墨骨枯麟", "东海龙冢有龙骨万千，尤以黑龙龙骨为尊，取其残骨，熔以业火，成墨骨重剑。弹触剑身，争鸣作响，似有龙吟");
	insertWeapon(0xF88C7462, 0x18605DF5, 0, "百辟镇魂", "千年以前，世间妖魔横行，有神将除妖邪，斩厉鬼，力竭而亡，然其精魂不灭，附于生前所用神兵重剑，继续护佑四方。此剑祭出，则正气浩然冲天，可诛邪平患，可定历熄灾");
	insertWeapon(0x14412394, 0x50C65EB2, 0, "长息", "洪水滔天，鲧窃帝之息壤以堙洪水，息壤生生不息，却于疏洪无益。帝令祝融取息壤，复命禹布土疏洪，以定九州。此时山川逼仄，水塞不出。禹借祝融火龙之力，熔炼息壤成重剑之体，以之开山疏浚，方江河倾泻，洪水东去");
	initIdx();
	initTable(eIcon::灯笼d);
	insertWeapon(0xC2554C5A, 0x053A2EC4, 0, "素纸灯", "轻巧的纸灯笼，最适合新手练习使用");
	insertWeapon(0x3EC471A0, 0xEA6DAE59, 0, "竹骨灯", "以竹骨扎成的灯笼，看起来精致又风雅");
	insertWeapon(0xC7DFDFEE, 0x38E5EA0B, 0, "红灯笼", "节日时方才悬挂起来的红灯笼，看到它就能感到喜庆的氛围");
	insertWeapon(0x97F6C50B, 0x97DB902B, 0, "鲤鱼灯", "仿照锦鲤的样子精致而成的花灯，说不定会和锦鲤一样带给人好运呢");
	insertWeapon(0xCD622A06, 0x7E3F070B, 0, "芙蓉花灯", "晶莹剔透的白瓷灯笼，更有名家所绘制之工笔芙蓉，美轮美奂");
	insertWeapon(0xB4FBA38A, 0xCE867B66, 0, "如意宫灯	", "宫廷巧匠耗费月余精制而成的宫灯，象征着平安吉祥，如意称心");
	insertWeapon(0x97987F5C, 0xA3B8F8E5, 0, "玲珑盏", "西域工匠以“费盎斯”工艺烧制的灯笼，其色流云漓彩，其质晶莹剔透，玲珑奇巧，引人注目");
	insertWeapon(0xD1839465, 0x9C3DDB33, 0, "玉兔盏", "白璧无瑕琢成团绒玉兔，碧玉青翠雕作剔透环佩，光润莹然，美不胜收");
	insertWeapon(0x06427E44, 0xF2575943, 0, "冰心盏", "北俱寒冰，澄澈剔透，经年不化。炽焰为刃，琢成玲珑灯盏，寒光为焰，凛风逼人");
	insertWeapon(0xA2DC05D6, 0x73DE6960, 0, "蟠龙", "风从龙出，云有龙息，夜放光华，金碧辉煌");
	insertWeapon(0x5470130D, 0x7B377B2F, 0, "云鹤", "饥餐瑶草，渴饮琼泉。朝飞阆苑，暮宿云烟。白鹤雪羽为灯盏，光耀如雪，不惹尘埃");
	insertWeapon(0xE61D828A, 0x03F289DB, 0, "风荷", "清莲出水，玉立亭亭。其灵性卓然者，化为灵仙，凡胎肉身，则凝为灯盏。含苞欲放，清芬十里");
	insertWeapon(0xD9D63E3A, 0x56ECB65C, 0, "金风玉露", "今日云軿渡鹊桥，应非脉脉与迢迢。灵鹊仙羽，织就金风，七夕月华，酿作玉露。皎皎华光，可照良人");
	// 无图
	insertWeapon(0x7DB16375, 0x17020397, 0, "凰火燎原(无图)", "凰与凤，生相伴，死同归。一方离世，则生者必引颈而鸣，唤涅槃之火，双双浴火重生。此火五百年不灭，奔腾炽烈，可焚八方");
	insertWeapon(0x7DB16375, 0x17020397, 0, "风露清愁", "三界之西，有湖曰灵，湖水乃天女眼泪所化，夜色深浓时，有溶溶光华。水滴如泪，泪干为夜明灵珠，风流蕴藉，清光泠泠");
	insertWeapon(0x71FEDD98, 0xEAEFA73D, 0, "夭桃秾李", "桃之夭夭，灼灼其华。烂漫春光，转瞬即逝。九重天上仙娥取之以为灯盏，光华所至处，枯木吐芽，桃李争芳");
	insertWeapon(0x889E6AB7, 0xFEEAD4B6, 0, "荒尘", "星河浩瀚，繁星若尘，亿万星尘聚沙为塔，是以沧海桑田，人世幻变，其光华永恒也");
	initIdx();
	initTable(eIcon::伞伞s);
	insertWeapon(0x75285B05, 0x63C38A86, 0, "油纸伞", "普通的油纸伞，美观轻巧，最适合新手使用");
	insertWeapon(0xABC1FF05, 0x1485AABF, 0, "红罗伞", "当下最时兴的雨伞样式，正红色的罗缎伞面看起来甚是喜庆");
	insertWeapon(0x7EB4CE4A, 0x28EEC31C, 0, "紫竹伞", "伞骨及伞柄皆是以紫竹制成，非常坚韧");
	insertWeapon(0x38E84E48, 0xA0A62144, 0, "锦绣帷", "巧手绣娘，择上品丝绸，飞针走线，历时年逾，方成此伞，设色精妙，光彩夺目");
	insertWeapon(0x898B70A3, 0xF2391CAB, 0, "幽兰帐", "本为一尺无暇素锦，不慎沾染墨痕，幸得雅士泼墨挥毫，绘幽兰一枝，其清俊姿态，栩栩如生，其清雅香气，扑鼻欲来");
	insertWeapon(0xD105662F, 0x38B4CA6B, 0, "琳琅盖", "般若经》中有七宝：乃金、银、琉璃、珊瑚、琥珀、砗磲、玛瑙。能工巧匠以金银为骨，饰以琉璃、珊瑚、砗磲之属，方成此伞");
	insertWeapon(0xFEBE2460, 0x24BD153A, 0, "孔雀羽", "西域巧匠，取珍禽孔雀之尾羽，以玄妙秘法织造而成，碧彩闪烁，金翠辉煌");
	insertWeapon(0xCC7106BF, 0x4FD7BCC4, 0, "金刚伞", "金刚怒目，降伏四魔。金刚伞以精钢百炼而成，铁骨钢叶，坚不可摧");
	insertWeapon(0xC0151FE6, 0x25E301EE, 0, "落梅伞", "北俱苦寒之地，生千年老梅，一甲子方开花一次，色若胭脂，香欺兰蕙。梅枝落雪上，苦心雕琢，方成此伞");
	insertWeapon(0xC1D8FB19, 0x5CBC9754, 0, "鬼骨", "昆山有玉，性阴厉，蓄百年煞气，幻为枯骨，谓之鬼玉。此玉为伞骨，伞下阴魂环绕，寒气森然");
	insertWeapon(0x9DF0BB9B, 0x32DC87DD, 0, "云梦", "高唐有梦，水阔花飞，梦有神女取巫山之风云为伞，谓之云梦");
	insertWeapon(0x28771B6D, 0x4FBB679F, 0, "枕霞", "瑶池有仙蝶，枕霞沐云而生，其态纤巧翩然，其色艳若丹霞，取其羽翼为伞，霞光云影，如在目前");
	insertWeapon(0x8E5D6A40, 0x45CB2F4A, 0, "碧火琉璃", "金蛇之鳞，可萃命魂之焰。以百枚金蛇之鳞，取百鬼命魂之火，成此伞。碧火幽幽，杀气腾腾，此伞过处，百鬼夜哭，绕梁不绝");
	insertWeapon(0xD189B9E5, 0x14945888, 0, "雪羽穿云", "昆仑山中，有仙禽雪鸢，振翅可穿云，歌有裂石音，灵气所钟，位列仙班，其羽裳化伞，持此者，身轻如燕，振翅可至九天");
	insertWeapon(0xEB48DDFB, 0x284DD72B, 0, "月影星痕", "汲天河之水，取星河之光，凝月华之露，锻千日，成此伞。其光灿然，其色清灵，伞起时，月华照人，清辉泻地");
	insertWeapon(0xE1EC0610, 0x2DF481E2, 0, "浮生归梦", "三生河畔，彼岸花开，殷红似火，灼灼其华。曼珠沙华一株，藏浮生忆念一世。幽梦为瓣，情丝若蕊，墨蝶翩翩，归梦何时？");
	insertWeapon(0x8020E83B, 0x4C2F3E26, 0, "晴雪", "燕山雪，大如席，有华胥之女幽娴姣丽，踏凌云风波，乘逐月之辇，辇有华盖，正是燕山晴雪，清光泠泠，不可逼视");
}


void txtIcon::initEquip()
{
	initIdx();
	initTable(eIcon::头盔t);
	insert(0xFAA7B82D, 0x0FE78372, 0, "方巾", "屌丝常戴的帽子");
	insert(0x7F0A0362, 0x6C180E40, 0, "布帽", "普通人使用的帽子");
	insert(0x60B8226E, 0x20787B2D, 0, "面具", "2B青年喜欢戴的\"帽子\".");
	insert(0x671F34DC, 0x94D9A3E0, 0, "纶巾", "文艺青年喜欢的帽子");
	insert(0x71540892, 0x48DA4E36, 0, "缨络丝带", "红色的缨络结成的丝带，可以起到防御的作用");
	insert(0x02E58635, 0x42795B75, 0, "羊角盔", "以羊角为装饰的盔，有非常强的防御力");
	insert(0x242AE31D, 0x968E1D79, 0, "水晶帽", "水晶制成的帽子，在炎热的夏季添一添,还有凉爽的感觉.");
	insert(0x4BDBC953, 0x69937480, 0, "乾坤帽", "天下名冠，暗藏乾坤玄机，有相当强的防御力");
	insert(0x28E006E4, 0x49BBBFA3, 0, "黑魔冠", "魔王妖王常戴的冠帽，有相当强的防御力");
	insert(0xFF6021EA, 0x542B1927, 0, "白玉龙冠", "高贵雅致的冠帽，镶有上等白玉精雕之飞龙图案");
	insert(0x049CC4E0, 0x80FCA5BF, 0, "水晶夔帽", "“其状如牛,苍色无角,一足能走,出入水即风雨,目光如日月,其声如雷,名曰夔。黄帝杀之,取皮以冒鼓,声闻五百里。”远古奇兽夔牛皮所制，千年不坏");
	insert(0x1CBCD901, 0x317D8219, 0, "翡翠曜冠", "相传为三清之一灵宝天尊佩戴过的帽冠。七颗翡翠分别代表“日、月、火、水、金、木、土”环绕在玉石宝珠上。");
	insert(0x43FE568B, 0x38859F13, 0, "金丝黑玉冠", "远古盘古开天辟地，混沌初开时凝结而成的玉石雕琢而成的冠帽，充满着神奇的灵气。");
	insert(0x2E6E179F, 0x0E7F8839, 0, "白玉琉璃冠", "太上老君曾佩戴过的冠帽，用仙界白玉与琉璃珠辅以天丝编织而成。");
	insert(0x89B17099, 0x07795BC4, 0, "兽鬼珐琅面", "上古神魔所戴，虽经几千年，面具独角四周仍散发着神奇的魔力。");
	insert(0x1AABE72F, 0xE6097140, 0, "紫金磐龙冠", "火神遗留之物。冠上用金雕琢为吉龙盘云，四周散发着神奇的力量。需要有一定修为之人方能佩戴。");
	insert(0xD4923813, 0x598DE214, 0, "浑天玄火盔", "黄帝征伐四方之时所配战盔，刀枪不入，水火不侵，瘟邪难近，更添无尽战意。");
	initIdx();
	initTable(eIcon::发钗f);
	insert(0x3BDF1975, 0x8B5E91E0, 0, "簪子", "女孩子们喜欢的簪子，可以起到防御作用");
	insert(0x1E5DB5FE, 0xD1C797EE, 0, "玉钗", "用玉制成的钗，可以起到防御作用");
	insert(0x8C42CAEE, 0xC8024791, 0, "梅花簪子", "因簪子外端有梅花形状而得名，可以起到防御作用");
	insert(0xDA2EDA34, 0x400EEB31, 0, "珍珠头带", "珍珠结成的头带，非常好看女性饰品，可以起到防御作用");
	insert(0x4DD76BD3, 0x4EE6CEC4, 0, "凤头钗", "雕刻着凤头的金钗，可以起到防御的作用");
	insert(0x18A14DF8, 0x2F9B6292, 0, "媚狐头饰", "狐眼嵌着宝石的狐头帽，魔女们喜爱的头饰");
	insert(0xE0C0EEAF, 0x1A200948, 0, "玉女发冠", "仙女常带的头环，有相当强的防御力");
	insert(0x9581C063, 0x325F3F92, 0, "魔女发冠", "魔女们常带的头环，可以起到非常强的防御作用");
	insert(0xBDB99660, 0x99370B3D, 0, "七彩花环", "用七彩神花编成的花环，可以起到极强防御的作用");
	insert(0x8D7CD7BE, 0xD6A259BA, 0, "凤翅金翎", "以凤翅和凤翎编织而成的金丝头环，有极强防御的作用");
	insert(0x052BEFCF, 0x02833D54, 0, "寒雉霜蚕", "由寒玉以及蚕丝编制而成，相传为七仙女常戴之物。");
	insert(0xC917A730, 0x9FEEE059, 0, "曜月嵌星", "瑶池圣母所戴之物。冠上镶有七星宝珠环绕在月光石周围形成七星曜月的图案。");
	insert(0xBC29F929, 0x96BDF0FF, 0, "郁金流苏簪", "白晶晶佩戴的发髻。白色玉石与金丝编织而成。");
	insert(0x287349C4, 0xC5F9B9F2, 0, "玉翼附蝉翎", "嫦娥仙女佩戴过的帽冠。将月宫中玉石经千年雕琢而成，羽翼薄如蝉翼。");
	insert(0x5E2FBF6E, 0x85A7A03E, 0, "鸾羽九凤冠", "九只五彩凤凰的羽翼与金丝编织而成的冠帽。");
	insert(0xE1DECF6D, 0xBA799178, 0, "金珰紫焰冠", "水神遗留之物。上古神兽凤凰羽翼制成的帽冠，四周散发着神奇的力量。需要有一定修为之人方能佩戴。");
	insert(0x7B0C2559, 0x15B5B742, 0, "乾元鸣凤冕", "有感于女娲造人之德，三界名匠合力铸造献上的帝王冠冕。五德齐聚，凤仪天下。");
	initIdx();
	initTable(eIcon::铠甲k);
	insert(0xA01DB489, 0x80E74115, 0, "布衣", "普通的布衣，可以起到防御的作用");
	insert(0x5D8703D4, 0xEEAA3C26, 0, "皮衣", "用兽皮制的皮衣，防御力较布衣要好的多");
	insert(0x175B2DD6, 0x87FB5568, 0, "鳞甲", "用铁鳞制成的铠甲，有相当的防御力");
	insert(0x7BDF36F9, 0xB09EECF3, 0, "锁子甲", "胸部是铁环，如铁锁加身，防御力相当不错");
	insert(0x8B60A48D, 0xF045EF07, 0, "紧身衣", "紧身的皮衣，非常轻便，有不错的防御力");
	insert(0x63B20034, 0x6F015575, 0, "钢甲", "用精钢制成的铠甲，防御能力较强");
	insert(0x829AF546, 0x52C4B2BC, 0, "夜魔披风", "来自阴间的披风，隐隐透出神秘的幽冥气息");
	insert(0x204AFD0B, 0x67D1D9D8, 0, "龙骨甲", "以龙骨制成的宝甲，有惊人的防御力");
	insert(0x6950C775, 0x7062D12D, 0, "死亡斗篷", "魔王妖王梦寐以求的防具，非常有价值");
	insert(0x69925162, 0x41EB9643, 0, "神谕披风", "受到神谕祝福的银色披风，带有灵动之气");
	insert(0x7B201B66, 0x93797ED4, 0, "珊瑚玉衣", "相传为龙王所用铠甲，穿上后能获得仙界的庇护。");
	insert(0x80476CF3, 0x6DA7E12C, 0, "金蚕披风", "由千年玉桑上的金蚕吐丝为材料缝制而成的衣甲，有极强的韧性。");
	insert(0xCD9C72AE, 0xEE067769, 0, "乾坤护心甲", "为道教流传的宝物，内有八卦乾坤玄机，能抵御极强的伤害。");
	insert(0xEC2D7BE8, 0x03A15051, 0, "蝉翼金丝甲", "月宫桂树上的灵蝉身上的蝉翼辅以金丝编织而成的铠甲。绝非寻常仙家之物。");
	insert(0x5AAEABD1, 0x144D9875, 0, "金丝鱼鳞甲", "水神遗留之物。时隔千年，依然充满着灵气。");
	insert(0x17DE920D, 0x03418C94, 0, "紫金磐龙甲", "相传为黄帝的遗物。紫金磐龙，四周散发着神奇的力量。");
	insert(0x6B75E4B8, 0xB5EE4134, 0, "混元一气甲", "混元一气所凝成的宝甲，至坚不摧之物，可与天地同寿。");
	initIdx();
	initTable(eIcon::布裙b);
	insert(0x8FF599B6, 0xF6A014A6, 0, "布裙", "普通的布裙，女子用，可以起到防御的作用");
	insert(0x68D837E6, 0x1AE20F9F, 0, "丝绸长裙", "用名贵丝绸制成的长裙，女子用，可以起到防御作用");
	insert(0xAC48363D, 0xCDE4D2F7, 0, "五彩裙", "五彩绵制成的裙子，可以起到一定的防御作用");
	insert(0xF1D98015, 0xA303B12A, 0, "龙鳞羽衣", "用龙鳞制成的羽衣，有相当的防御力");
	insert(0xDD135FAA, 0xE2AE6292, 0, "天香披肩", "瑶台玉女穿的披肩，有相当的防御力");
	insert(0x3B5D98BE, 0xF9A08BFA, 0, "金缕羽衣", "用金丝缝制的羽衣，可以起到一定的防御作用");
	insert(0xB3240E5A, 0x9EDD3359, 0, "霓裳羽衣", "非常美丽的羽衣，可以起到一定的防御作用");
	insert(0xC61085FC, 0x6991B7B9, 0, "流云素裙", "相传是织女用流云织成的裙子，有很非常的防御力");
	insert(0xF928862D, 0xF078EBEB, 0, "七宝天衣", "所谓天衣无缝，上有七宝华文，是可遇不可求的极品");
	insert(0x9D306336, 0x50AA1CF2, 0, "飞天羽衣", "相传以玉女飞天时所着衣装，受到天地精华的凝炼");
	insert(0x33D62B8D, 0x6D736993, 0, "穰花翠裙", "翠玉宝珠装饰而成的镶花裙，为王母娘娘赏赐之物。");
	insert(0x7DA318AA, 0x6608E536, 0, "金蚕丝裙", "由千年玉桑上的金蚕吐丝为材料缝制而成的衣甲，有极强的韧性。");
	insert(0xACBEAA37, 0x105370B9, 0, "紫香金乌裙", "汲取三界花魂而制成的裙子，穿上此裙香飘千里。");
	insert(0x75937D89, 0x92298C9B, 0, "碧霞彩云衣", "收集了天界的碧霞五彩祥云编织而成的彩云衣，相传七仙女下凡时就是穿的这件。");
	insert(0x363F6F77, 0xA41E7621, 0, "金丝蝉翼衫", "月宫桂树上的灵蝉身上的蝉翼，并取自瑶池的金丝，经仙界仙女七七四十九天编织而成的软甲。");
	insert(0xA5FB9E1D, 0xF6B7870F, 0, "五彩凤翅衣", "相传女娲娘娘所穿。穿上此衣能得到上古神灵的庇佑。");
	insert(0x510C98D5, 0x9AC1390D, 0, "鎏金浣月衣", "以日月光芒所织造的霞衣，对敌之时往往令其目眩神驰。");
	initIdx();
	initTable(eIcon::项链x);
	insert(0x92AC0A46, 0x1571ECE6, 0, "护身符", "一块护身符，佩带在身上有一定法力作用");
	insert(0xBB237AD4, 0x164EEEA7, 0, "五色飞石", "仙人炼制的饰品，佩带在身上有极强的法力作用");
	insert(0x921C285B, 0xFC424978, 0, "珍珠链", "一串珍珠，佩带在身上有一定法力作用");
	insert(0xCB8137A8, 0xD12A6900, 0, "骷髅吊坠", "皮绳上吊着一个骷髅，佩带在身上有一定法力作用");
	insert(0xFC948E76, 0x70D75356, 0, "苍魂珠", "据说珠里附有魂魄，佩带在身上有较强的法力作用");
	insert(0xED943652, 0x117C58D5, 0, "江湖夜雨", "流传于中土的奇异饰物，佩带在身上有较强的法力作用");
	insert(0x5ED72250, 0x99D89842, 0, "九宫坠", "以九宫制成的坠子，佩带在身上有较强的法力作用");
	insert(0x0E4F4980, 0xFB1404DD, 0, "荧光坠子", "有荧光的宝石，佩带在身上有相当强的法力作用");
	insert(0xF8DA7A38, 0x5DBB74F3, 0, "高速之星", "神秘的项圈，来历至今无人知晓");
	insert(0x056E1227, 0x76A0B4BF, 0, "风月宝链", "名家制成的精致饰品，佩带在身上有较强的法力作用");
	insert(0x50E5B95C, 0xC88803AD, 0, "八卦坠", "以八卦制成的饰物，佩带在身上有较强的法力作用");
	insert(0xA49B9649, 0xEE8F5986, 0, "碧水青龙", "龙形环状可戴在项部，有相当的法力作用");
	insert(0xECDC94AA, 0x8C6F5FF0, 0, "鬼牙攫魂", "来自阴间的饰物，佩带在身上有较强的法力作用");
	insert(0xA7C611A2, 0xE1D8F6EA, 0, "万里卷云", "据说是大禹留下的宝物，佩带在身上有极强的法力作用");
	insert(0x6AB73447, 0xEA5949B5, 0, "疾风之铃", "来历不详的神秘饰物，佩带在身上有极强的法力作用");
	insert(0x03A59378, 0x6AB2DFBE, 0, "七彩玲珑", "串有七彩玲珑的珍珠，集海之灵气，给予佩戴者祥瑞祝福");
	insert(0xFEBBC49F, 0xD659ACA9, 0, "黄玉琉佩", "女娲补天遗留下的神石雕琢而成，拥有神奇的灵力。");
	insert(0x0DF2D9D6, 0x3008F281, 0, "鸾飞凤舞", "仙界仙女们常佩之物。呈祥瑞和平之气，定能给佩戴者带来好运。");
	insert(0x6BC7833A, 0x46104E6A, 0, "衔珠金凤佩", "相传曾为嫦娥仙子佩戴之物。此物寓示着美好的追求与向往。");
	insert(0x08F99E69, 0xC7B46732, 0, "七璜珠玉佩", "以七个天珠以及天丝编制而成的坠子。集天地之灵气，能给予佩戴者吉祥如意。");
	insert(0x057A3A40, 0x78641E8B, 0, "鎏金点翠佩", "玉皇大帝平常佩戴之物，集合了仙界之力，给予佩戴者神奇的魔力。");
	insert(0x2EA16C08, 0x7D644FEE, 0, "紫金碧玺佩", "上古神兽遗留之物。四颗碧玉珠似乎依附着神奇的魔力。");
	insert(0xF4A20950, 0x76685AEF, 0, "落霞陨星坠", "以陨落的星辰制成的宝玉，带有莫名的灵气与能量。");
	initIdx();
	initTable(eIcon::腰带y);
	insert(0x22ACB047, 0x75E8F25A, 0, "腰带", "一条普通的腰带，可以起到防御的作用");
	insert(0xB2FB05F4, 0xF9502CBE, 0, "缎带", "高级丝绸制成的腰带，能起到不错的防御作用");
	insert(0xE9B1F207, 0x618F66ED, 0, "银腰带", "银制的腰带，可以起到防御的作用");
	insert(0x2317BF2F, 0x28D305DA, 0, "水晶腰带", "佩带在腰间的水晶腰带，能起到不错的防御作用");
	insert(0x6BAC940C, 0xD7882F4B, 0, "玉树腰带", "玉树之丝绦制成的腰带，能起到较强的防御作用");
	insert(0x40B85184, 0xF0E1864B, 0, "琥珀腰链", "用琥珀制的腰链，能起到较强的防御作用");
	insert(0xD522DB36, 0xBF4FA059, 0, "白面狼牙", "白色的神镜片，可束在腰间，能起到较强的防御作用");
	insert(0xF3438742, 0x6D190C37, 0, "乱牙咬", "神铁制的腰箍，能起到较强的防御作用");
	insert(0xE97A37D9, 0x0EB143A5, 0, "魔童大牙", "巨大的魔牙，系在腰间能起到极强的防御作用");
	insert(0xD0D1BA12, 0xFF45D8EE, 0, "攫魂铃", "来自阴间的魔铃，佩在腰间，能起到极强的防御作用");
	insert(0xD03D65EE, 0xA069B155, 0, "双魂引", "来自阴间的宝物，可以佩在腰间，能起到极强的防御作用");
	insert(0xAFA474C1, 0x10C86EA1, 0, "兽王腰带", "兽王曾使用过的腰饰，能起到较强的防御作用");
	insert(0x749C9390, 0x1B41AB40, 0, "百窜云", "神秘的缎带，系在腰间能起到较强的防御作用");
	insert(0xFCA16FA2, 0xDB28AB80, 0, "八卦锻带", "暗藏八卦玄机的腰带，能起到极强的防御作用");
	insert(0xF80BBB1A, 0x9B1732F4, 0, "圣王坠", "相传为Saber的缠腰带,不如被谁偷走了,流入市场.");
	insert(0x8E09D47D, 0x33F8C8FA, 0, "幻彩玉带", "以集天界灵气之幻彩宝玉制成，有强大的护佑作用");
	insert(0xF3F1AF4E, 0xEFCE55E8, 0, "珠翠玉环", "集合千年地气生出的翡翠宝珠雕琢而成的腰带，有强大的庇佑作用。");
	insert(0x55A01234, 0x18C61033, 0, "金蟾含珠", "相传“蟾”能口吐金钱为旺财之物。由金身蟾口含夜光珠再辅以金丝编织而成的腰带，世间少有，绝非人界之物。");
	insert(0x3FD1945B, 0x34C30853, 0, "乾坤紫玉带", "千年紫玉雕琢而成的腰带，相传为道家失传的宝物，有极强的庇佑作用。");
	insert(0x2D673201, 0x114BFE8E, 0, "琉璃寒玉带", "天界银河之水经亿万年凝结而成的玉石制成的腰带，不为寻常仙物。");
	insert(0x5022B0CD, 0x8F6B5082, 0, "蝉翼鱼佩带", "月宫桂树上的灵蝉身上的蝉翼以及金丝编织而成的腰带，所散发出来的灵气能抵御极强的伤害。");
	insert(0x98CB2734, 0xEF59C854, 0, "磐龙凤翔带", "远古天神遗物，龙飞凤舞呈吉祥之态，佩戴起来能受到上古神兽的庇护。");
	insert(0xA8551B68, 0x84ED8EB8, 0, "紫霄云芒带", "以云霞束起雷电所制成的腰带，会散发出闪电自行防御来袭的攻击。");
	initIdx();
	initTable(eIcon::鞋子x);
	insert(0x902D047B, 0x9F15DCD5, 0, "布鞋", "布缝制的鞋子，可以起到防御的作用");
	insert(0xF41AB35D, 0x850B4461, 0, "牛皮靴", "牛皮缝制的靴子，速度和防御作用都比较强");
	insert(0xC131874A, 0xD31EF251, 0, "马靴", "皮制的马靴，可以起到防御的作用");
	insert(0x01EB19F4, 0x2142F94B, 0, "侠客履", "非常强的鞋，速度和防御作用都属上品");
	insert(0xEC3F1972, 0x423882CD, 0, "神行靴", "非常轻便的靴子，可以起到防御的作用");
	insert(0x9CDE60C0, 0xEE0695FA, 0, "绿靴", "绿水晶制成的鞋子，防御作用非常的强");
	insert(0x70BDA996, 0xEF75A65E, 0, "追星踏月", "由于鞋上有云月图案而得名，有不错的防御力");
	insert(0x470CFD54, 0x3F383BF8, 0, "九州履", "天下名履，有非常不错的防御力和速度");
	insert(0xAE8AB819, 0x42DC8581, 0, "万里追云履", "可在任何地形疾走的神履，有不错的防御力");
	insert(0x43F9A885, 0x34F5F31D, 0, "踏雪无痕", "包蓄地之灵气，穿之幻影如风，踏雪无痕");
	insert(0x7317D3A9, 0x2DF94DDC, 0, "平步青云", "寻常仙界之物，穿上此靴可平步青云，借风云飞腾。");
	insert(0x448A26A9, 0xB6869E1C, 0, "追云逐电", "相传为雷公电母经过千万年炼化而成，穿上后可以追逐云电，日行万里。");
	insert(0x49D294F7, 0x8FDD216D, 0, "乾坤天罡履", "相传为太上老君所穿。乃天地之气编织而成。");
	insert(0x60CA1A45, 0xA4B71AC0, 0, "七星逐月靴", "天罡星所穿之靴。穿之及疾如风，三界之地任我遨游。");
	insert(0xCDB0FA23, 0x4E37E86D, 0, "碧霞流云履", "相传天界神匠以五彩天霞为材料，缝制而成的靴子。");
	insert(0x39AE3820, 0xA301E3CD, 0, "金丝逐日履", "相传神匠为纪念夸父特造此靴。穿上可追逐太阳，风云皆抛于脑后。");
	insert(0xAD45AA61, 0xCBBE3F2C, 0, "辟尘分光履", "上古秘宝，着此履者可于星尘间穿梭，与霞光相竞逐。");


	initIdx();
	initTable(eIcon::护腕h);
	insert(0x53F8EBA5, 0x809C04C8, 0, "竹编护腕", "竹子做的护腕");
	insert(0x336A2EC6, 0xA8F7F6C0, 0, "皮腕", "皮做的护腕");
	insert(0xC1A4E276, 0x1C28FB6F, 0, "针腕", "针做的护腕");
	insert(0x47680171, 0xDB529E26, 0, "骨镯", "骨做的护腕");
	insert(0x152B263E, 0x9D0CFE72, 0, "青铜护腕", "铜做的护腕");
	insert(0xB3405C3F, 0xDD8EA49F, 0, "玛瑙护腕", "玛缁做的护腕");
	insert(0x3FB923E4, 0xC7A0F7FB, 0, "琉璃护腕", "琉璃的护腕");
	insert(0xB7B54543, 0xE168F7C1, 0, "镂空银镯", "银做的护腕");
	insert(0x307ACF93, 0xFEE14584, 0, "笼玉镯", "玉做的护腕");
	insert(0xBD98D975, 0xA87273E4, 0, "嵌宝金腕", "金做的护腕");
	insert(0x91CD16B5, 0x0B4042DF, 0, "玳瑁护腕", "玳瑁做的护腕");
	insert(0x2DEC7C4E, 0x158E1623, 0, "七星宝腕", "玳瑁做的护腕");
	insert(0x639CF6A5, 0xEA7D3F1C, 0, "缚龙筋", "龙筋做的护腕");
	insert(0x5AA77450, 0xD0B093D0, 0, "凤翎护腕", "凤凰的羽毛做的护腕");
	insert(0x196F1418, 0xF15B5332, 0, "织锦彩带", "锦做的护腕");
	insert(0x27ECB10D, 0xD015AE2E, 0, "冰蚕丝带", "冰蚕丝做的护腕");
	insert(0x9727C44A, 0x41BCD2C1, 0, "狼腕", "狼宝特供");

	initIdx();
	initTable(eIcon::项圈x);
	insert(0x12656D50, 0xC15447DE, 0, "竹编脖环", "竹子做的项圈");
	insert(0x51FE104E, 0xF0E9FA42, 0, "钢圈", "皮做的项圈");
	insert(0x150942F1, 0x82D15D47, 0, "荆棘环", "针做的项圈");
	insert(0x66F4FC81, 0x1A425603, 0, "骨环", "骨做的项圈");
	insert(0x56ABA89B, 0x2EDB4111, 0, "青铜颈环", "铜做的项圈");
	insert(0x1752FDDE, 0x57655BFD, 0, "玛瑙石环", "玛缁做的项圈");
	insert(0x7120F39D, 0x8BA2F5BA, 0, "琉璃环", "琉璃的项圈");
	insert(0xD75A17B9, 0xD1149C66, 0, "九曲环", "银做的项圈");
	insert(0x6E4AFA78, 0xE18E7C61, 0, "笼玉环", "玉做的项圈");
	insert(0xC3B2AC98, 0xC33B353A, 0, "嵌宝金环", "金做的项圈");
	insert(0xC11EADEC, 0x0D69C740, 0, "玳瑁环", "玳瑁做的项圈");
	insert(0x286FA969, 0x20E98108, 0, "七星宝环", "玳瑁做的项圈");
	insert(0x9BB95D35, 0xD002593F, 0, "缚龙圈", "龙筋做的项圈");
	insert(0x8BC3A051, 0x60B55501, 0, "鸾尾环", "凤凰的羽毛做的项圈");
	insert(0xF398CA2B, 0x34F1297C, 0, "织锦颈圈", "锦做的项圈");
	insert(0xCAF49FBE, 0x62C51769, 0, "冰蚕丝圈", "冰蚕丝做的项圈");
	insert(0xF898A805, 0x8930598A, 0, "狼圈", "狼宝特供");

	initIdx();
	initTable(eIcon::护甲h);
	insert(0x440C4E35, 0xE497BC0E, 0, "竹藤甲", "竹子做的铠甲");
	insert(0x6670FC2C, 0x157D0DC8, 0, "皮甲", "皮做的铠甲");
	insert(0xC8E4088B, 0x8D252B7B, 0, "刺甲", "针做的铠甲");
	insert(0x49C82067, 0x749824D3, 0, "骨排甲", "骨做的铠甲");
	insert(0xB9E7C15C, 0x6D01B1A3, 0, "青铜披甲", "铜做的铠甲");
	insert(0xAE0769A0, 0xC7E186AA, 0, "玛瑙软甲", "玛缁做的铠甲");
	insert(0x29804071, 0x9023B123, 0, "琉璃罩甲", "琉璃的铠甲");
	insert(0x2FCBE79A, 0x090B5B8A, 0, "连环铠甲", "银做的铠甲");
	insert(0xF8F0B550, 0x1255FE4D, 0, "笼玉甲", "玉做的铠甲");
	insert(0x234C440C, 0xF7BC24CE, 0, "嵌宝金甲", "金做的铠甲");
	insert(0x563F5BD1, 0x16275C8E, 0, "玳瑁衣", "玳瑁做的铠甲");
	insert(0x5E6FC760, 0x5037E497, 0, "七星宝甲", "玳瑁做的铠甲");
	insert(0x04037AC1, 0xD0125017, 0, "缚龙甲", "龙筋做的铠甲");
	insert(0xED7A9BFE, 0xC47A3765, 0, "凤凰彩衣", "凤凰的羽毛做的铠甲");
	insert(0xC77EE0B7, 0x4E5F4830, 0, "织锦软褡", "锦做的铠甲");
	insert(0x1F3F4E97, 0x9C023588, 0, "冰蚕织甲", "冰蚕丝做的铠甲");
	insert(0xD377ECEA, 0x107DE496, 0, "狼甲", "狼宝特供");

	int prices[] = { 1, 2, 5, 10, 15, 20, 30, 50, 80, 120, 160, 200, 250, 300, 360, 450, 600, 800, 1000 };
	int lv;
	int per = 10000;
	for (int e = (int)eIcon::eWeapon0; e <= (int)eIcon::eWeaponEnd; ++e)
	{
		initTable((eIcon)e);
		for (auto& it : *_table)
		{
			lv = getWeaponLv1ById(it.first);
			it.second.price = prices[lv] * per;
		}
	}
	for (int e = (int)eIcon::equipArmor0; e <= (int)eIcon::equipArmorEnd; ++e)
	{
		initTable((eIcon)e);
		if (e >= (int)eIcon::项链x || e >= (int)eIcon::腰带y)
		{
			for (auto& it : *_table)
			{
				lv = getNeckBeltLv1ById(it.first);
				it.second.price = prices[lv] * per;
			}
		}
		else
		{
			for (auto& it : *_table)
			{
				it.second.price = prices[it.first] * per;
			}
		}
	}
	for (int e = (int)eIcon::equipBaby0; e <= (int)eIcon::equipBabyEnd; ++e)
	{
		initTable((eIcon)e);
		for (auto& it : *_table)
		{
			lv = it.first;
			it.second.price = prices[lv] * per / 10;
		}
	}
}


void txtIcon::initMedicineCook()
{
	txtMedicine* medicine = txtMedicine::getInstance();
	txtMedicine::sEffect medicineEffect;

#define ccc_txt_medicine_insert(_LV_, _HP_, _HP2_, _Mp_, _ALL_)\
medicineEffect.lv = _LV_;\
medicineEffect.hp = _HP_;\
medicineEffect.hp2 = _HP2_;\
medicineEffect.mp = _Mp_;\
medicineEffect.isAll = _ALL_;\
medicine->effects.insert(std::make_pair(_idx, medicineEffect))
#define ccc_txt_medicine_insert_1(_HP_, _Mp_, _HP2_) ccc_txt_medicine_insert(1, _HP_, _HP2_, _Mp_, false)
#define ccc_txt_medicine_insert_2(_HP_, _Mp_, _HP2_) ccc_txt_medicine_insert(2, _HP_, _HP2_, _Mp_, false)
#define ccc_txt_medicine_insert_3(_HP_, _Mp_, _HP2_) ccc_txt_medicine_insert(3, _HP_, _HP2_, _Mp_, false)
#define ccc_txt_medicine_insert_all(_HP_, _Mp_, _HP2_) ccc_txt_medicine_insert(4, _HP_, _HP2_, _Mp_, true)

	initIdx();
	initTable(eIcon::药品y);
	insert(0x8F4023DB, 0xA2C06D7D, 0, "四叶花", "HP+40"); ccc_txt_medicine_insert_1(40, 0, 0);
	insert(0x5CF356A9, 0xE20A1271, 0, "七叶莲", "HP+60"); ccc_txt_medicine_insert_1(60, 0, 0);
	insert(0xA8D4BBC4, 0x11AC6F14, 0, "天青地白", "HP+80"); ccc_txt_medicine_insert_1(80, 0, 0);


	insert(0x97ED09BC, 0x16D97DEB, 0, "佛手", "MP+20"); ccc_txt_medicine_insert_1(0, 20, 0);
	insert(0xC8E09102, 0x528EB408, 0, "紫丹罗", "MP+20"); ccc_txt_medicine_insert_1(0, 20, 0);
	insert(0x20587F69, 0xA3475FBA, 0, "百色花", "MP+30"); ccc_txt_medicine_insert_1(0, 30, 0);
	insert(0x6032AAB4, 0xFD621F30, 0, "香叶", "MP+30"); ccc_txt_medicine_insert_1(0, 30, 0);
	insert(0x3E9E27B6, 0x8927E0C3, 0, "龙须草", "MP+30"); ccc_txt_medicine_insert_1(0, 30, 0);
	insert(0xB31FB97B, 0x6CD8405D, 0, "旋复花", "MP+30"); ccc_txt_medicine_insert_1(0, 30, 0);
	insert(0xE1974971, 0xCDF930E5, 0, "白玉骨头", "MP+40"); ccc_txt_medicine_insert_1(0, 40, 0);
	insert(0x852C04EE, 0xF918B8DB, 0, "灵脂", "MP+40"); ccc_txt_medicine_insert_1(0, 40, 0);
	insert(0x638FED0D, 0x14F9B337, 0, "曼佗罗花", "MP+50"); ccc_txt_medicine_insert_1(0, 50, 0);
	insert(0x33DBD039, 0x23B1D2DA, 0, "丁香水", "MP+75"); ccc_txt_medicine_insert_1(0, 75, 0);
	insert(0x18450CD6, 0xE3307E95, 0, "月星子", "MP+75"); ccc_txt_medicine_insert_1(0, 75, 0);


	insert(0x23E1DE00, 0x5F39ECF5, 0, "月见草", "HP+40,MP+30"); ccc_txt_medicine_insert_1(40, 30, 0);


	insert(0x48B661C2, 0x1134EEB1, 0, "草果", "治疗伤势10"); ccc_txt_medicine_insert_1(0, 0, 10);
	insert(0xC30AE6EF, 0x1BF0DE4E, 0, "九香虫", "治疗伤势15"); ccc_txt_medicine_insert_1(0, 0, 15);
	insert(0x47257634, 0x685E4891, 0, "水黄莲", "治疗伤势20"); ccc_txt_medicine_insert_1(0, 0, 20);


	insert(0x9D941C39, 0xC0EC938B, 0, "山药", "HP+40, 疗伤+10"); ccc_txt_medicine_insert_1(40, 0, 10);
	insert(0x35C25C5F, 0x2B46AADD, 0, "八角莲叶", "HP+60,疗伤+15"); ccc_txt_medicine_insert_1(60, 0, 15);
	insert(0x15E4304F, 0xF09CBA45, 0, "人参", "HP+80,疗伤+20"); ccc_txt_medicine_insert_1(80, 0, 20);


	insert(0x50B560E1, 0x4DE946B5, 0, "血色茶花", "HP+150"); ccc_txt_medicine_insert_2(150, 0, 0);
	insert(0x92DCE8F4, 0x4B5BF1AF, 0, "鹿茸", "HP+150"); ccc_txt_medicine_insert_2(150, 0, 0);
	insert(0x51EC528C, 0x10929E69, 0, "熊胆", "HP+200"); ccc_txt_medicine_insert_2(200, 0, 0);
	insert(0x7A231B4A, 0x6F66E996, 0, "六道轮回", "HP+200"); ccc_txt_medicine_insert_2(200, 0, 0);
	insert(0x5BC584A7, 0x9E720FD5, 0, "凤凰尾", "HP+250"); ccc_txt_medicine_insert_2(250, 0, 0);
	insert(0x338422D9, 0xA49FDDC1, 0, "硫磺草", "HP+250"); ccc_txt_medicine_insert_2(250, 0, 0);
	insert(0xBF847936, 0xC26FA33C, 0, "龙之心屑", "HP+300"); ccc_txt_medicine_insert_2(300, 0, 0);
	insert(0xD0B9CCDF, 0x7756A846, 0, "火凤之睛", "HP+300"); ccc_txt_medicine_insert_2(300, 0, 0);


	insert(0x0789B660, 0x92583E49, 0, "血珊瑚", "MP+100"); ccc_txt_medicine_insert_2(0, 100, 0);
	insert(0x2F7C81CE, 0x696C18EE, 0, "地狱灵芝", "MP+100"); ccc_txt_medicine_insert_2(0, 100, 0);
	insert(0xEB07E77A, 0x28AF1886, 0, "餐风饮露", "MP+100"); ccc_txt_medicine_insert_2(0, 100, 0);
	insert(0x070423BB, 0x6292168E, 0, "麝香", "MP+100"); ccc_txt_medicine_insert_2(0, 100, 0);
	insert(0x388CCEE9, 0x8AC7636D, 0, "紫石英", "MP+100"); ccc_txt_medicine_insert_2(0, 100, 0);
	insert(0xC94308D2, 0x95A825DD, 0, "白露为霜", "MP+100"); ccc_txt_medicine_insert_2(0, 100, 0);
	insert(0xF4A285EE, 0x82670C5A, 0, "孔雀红", "MP+150"); ccc_txt_medicine_insert_2(0, 150, 0);
	insert(0xB5F99FA9, 0x1E547A7E, 0, "仙狐涎", "MP+150"); ccc_txt_medicine_insert_2(0, 150, 0);
	insert(0x3256793E, 0xDA628B3B, 0, "天龙水", "MP+150"); ccc_txt_medicine_insert_2(0, 150, 0);


	insert(0xC849A182, 0xE0ADD9F6, 0, "金创药", "HP+400"); ccc_txt_medicine_insert_3(400, 0, 0);
	insert(0x342C85DF, 0x8EC6D2DD, 0, "金香玉", "HP+800"); ccc_txt_medicine_insert_3(800, 0, 0);


	insert(0x60268567, 0xCD230106, 0, "风水混元丹", "MP+300"); ccc_txt_medicine_insert_3(0, 300, 0);
	insert(0x99341DD1, 0xFC3F5A0E, 0, "定神香", "MP+400"); ccc_txt_medicine_insert_3(0, 400, 0);
	insert(0xB1BE067B, 0xA32D0B05, 0, "蛇蝎美人", "MP+500"); ccc_txt_medicine_insert_3(0, 500, 0);


	insert(0x4B2BCD27, 0xF4FF7A23, 0, "小还丹", "HP+400,疗伤+400"); ccc_txt_medicine_insert_3(400, 0, 400);
	insert(0xEC86D54A, 0x0CA5CBF9, 0, "千年保心丹", "HP+500,疗伤+300"); ccc_txt_medicine_insert_3(500, 0, 300);


	insert(0x8ABE812C, 0x09BA5E8F, 0, "红雪散", "解毒,HP+400"); ccc_txt_medicine_insert_3(400, 0, 0); medicine->_posionId = _idx;
	insert(0x0F81043B, 0xE24080F3, 0, "五龙丹", "解封,HP+100"); ccc_txt_medicine_insert_3(100, 0, 0); medicine->_sealId = _idx;

	// 复活
	insert(0x1F920A65, 0x15A0C084, 0, "佛光舍利子", "复活,疗伤+150"); ccc_txt_medicine_insert_3(0, 0, 150); medicine->_relifeId = _idx;
	insert(0x041C467A, 0x42862CE9, 0, "九转回魂丹", "复活,HP+200,疗伤+200"); ccc_txt_medicine_insert_3(200, 0, 200); medicine->_relifeId2 = _idx;


	// 4级 全体

	insert(0x08DA58E2, 0x1C704A0E, 0, "福灵沙", "全体HP+100"); ccc_txt_medicine_insert_all(150, 0, 0);

	insert(0x5C357F39, 0x5F85B7D2, 0, "五味露", "全体MP+40"); ccc_txt_medicine_insert_all(0, 40, 0);
	insert(0x2A67967E, 0xAF20F884, 0, "玉露羹", "全体MP+60"); ccc_txt_medicine_insert_all(0, 60, 0);
	insert(0x884099A7, 0x125F2DD0, 0, "千金露", "全体MP+80"); ccc_txt_medicine_insert_all(0, 80, 0);


	insert(0x7F51DBB5, 0x8A1909B8, 0, "八珍玉液", "全体HP+150,疗伤+150"); ccc_txt_medicine_insert_all(150, 0, 150);
	insert(0x343860F3, 0x812D644D, 0, "神仙饮", "全体HP+200,MP+50"); ccc_txt_medicine_insert_all(200, 50, 0);

#undef ccc_txt_medicine_insert
#undef ccc_txt_medicine_insert_1
#undef ccc_txt_medicine_insert_2
#undef ccc_txt_medicine_insert_3
#undef ccc_txt_medicine_insert_all

	int prices[] = { 0, 100, 1000, 10000, 30000, 50000 };
//	sTable& table = *_table;
	for (int idx = 0; idx <= _idx; ++idx)
	{
		auto& it = _table->at(idx);
		const auto& effect = medicine->effects.at(idx);

		it.price = prices[effect.lv];

		auto& desc = it.desc;
		desc.clear();
		if (effect.isAll)
		{
			desc += "全体: ";
		}
		if (effect.hp > 0)
		{
			desc += toString("气血+%d ", effect.hp);
		}
		if (effect.mp > 0)
		{
			desc += toString("魔法+%d ", effect.mp);
		}
		if (effect.hp2 > 0)
		{
			desc += toString("疗伤+%d ", effect.hp2);
		}
	}


	txtCook* cook = txtCook::getInstance();
	txtCook::sEffect cookEffect;

#define ccc_txt_cook_insert(_HP_, _Mp_,_HP2_,  _AP_, _NORMAL_)\
cookEffect.hp = _HP_;\
cookEffect.hp2 = _HP2_;\
cookEffect.mp = _Mp_;\
cookEffect.ap = _AP_;\
cookEffect.isNormal = _NORMAL_;\
cook->effects.insert(std::make_pair(_idx, cookEffect))


	initIdx();
	initTable(eIcon::烹饪p);
	insert(0x56E0001D, 0x4DA4F22A, 100, "包子", "HP+150,只能在平时使用"); ccc_txt_cook_insert(150, 0, 0, 0, true);
	insert(0x900198D8, 0xAA17FF00, 0, "烤鸭", "HP+300,疗伤+300,只能在平时使用"); ccc_txt_cook_insert(300, 0, 300, 0, true);

	insert(0xEA4ED968, 0x58130DB3, 0, "豆斋果", "增加召唤师寿命"); ccc_txt_cook_insert(0, 0, 0, 0, true);
	insert(0x9914F83B, 0xC5652305, 0, "长寿面", ""); ccc_txt_cook_insert(0, 0, 0, 0, true);
	insert(0x76A70298, 0x01F1ED48, 0, "佛跳墙", "MP+300,只能在平时使用"); ccc_txt_cook_insert(0, 300, 0, 0, true);
	insert(0x11D6858F, 0x3178273A, 0, "翡翠豆腐", "MP+500,只能在平时使用"); ccc_txt_cook_insert(0, 500, 0, 0, true);

	insert(0x08119E63, 0x712C63EC, 0, "同心肉脯", "HP+1000,MP+500,只能在平时使用"); ccc_txt_cook_insert(1000, 500, 0, 0, true);
	insert(0x88BE1648, 0x00AB4299, 0, "忠义肉脯", "HP+1000,疗伤+800,MP+300,只能在平时使用"); ccc_txt_cook_insert(1000, 300, 800, 0, true);

	insert(0x2ECB8558, 0x5F376254, 0, "女儿红", "愤怒+10"); ccc_txt_cook_insert(0, 0, 0, 10, false);
	insert(0xCD6FDF37, 0x46A54492, 0, "虎骨酒", "愤怒+15"); ccc_txt_cook_insert(0, 0, 0, 15, false);
	insert(0x71F4446B, 0xEFFC63BB, 0, "珍露酒", "愤怒+15"); ccc_txt_cook_insert(0, 0, 0, 15, false);
	insert(0x717E19FF, 0xF8D6B828, 0, "梅花酒", "愤怒+20"); ccc_txt_cook_insert(0, 0, 0, 20, false);
	insert(0x1FA7B36A, 0xFFB20F40, 0, "百味酒", "愤怒+20"); ccc_txt_cook_insert(0, 0, 0, 20, false);
	insert(0x6607309D, 0x67A3D814, 0, "蛇胆酒", "愤怒+25"); ccc_txt_cook_insert(0, 0, 0, 25, false);
	insert(0xED576385, 0x2B2980FB, 0, "醉生梦死", "愤怒+30"); ccc_txt_cook_insert(0, 0, 0, 30, false);

#undef ccc_txt_cook_insert

//	sTable& table = *_table;
	for (int idx = 0; idx <= _idx; ++idx)
	{
		auto& it = _table->at(idx);
		const auto& effect = cook->effects.at(idx);

		auto& desc = it.desc;
		desc.clear();
		if (effect.hp > 0)
		{
			desc += toString("气血+%d ", effect.hp);
		}
		if (effect.mp > 0)
		{
			desc += toString("魔法+%d ", effect.mp);
		}
		if (effect.hp2 > 0)
		{
			desc += toString("疗伤+%d ", effect.hp2);
		}
		if (effect.ap > 0)
		{
			desc += toString("愤怒+%d ", effect.ap);
		}

		if (effect.isNormal)
		{
			desc += "(平时使用)";
		}
	}
}



void txtIcon::initStone()
{
	auto& stoneTable = txtStone::getInstance()->_tables;
	txtStone::sStone stone;
#define ccc_txt_stone_insert(_PRO_, _V_)\
stone.pro = _PRO_;\
stone.value = _V_;\
stoneTable.insert(std::make_pair((eStone)_idx, stone))

	initIdx();
	initTable(eIcon::宝石b);
	////////////////////////////////////////////////////////////////////////// 加载顺序不要改 不然对不上eStone枚举
	insert(0x0ADECF25, 0x41656FA0, 0, "光芒石", "气血+40"); ccc_txt_stone_insert(eProPerty::气血, 40);
	insert(0xFADEE7FC, 0x750B0C1A, 0, "黑宝石", "速度+8"); ccc_txt_stone_insert(eProPerty::速度, 8);
	insert(0xA5E276AE, 0xD9DCF799, 0, "红玛瑙", "命中+25"); ccc_txt_stone_insert(eProPerty::命中, 25);
	insert(0x84D01F40, 0xCB7F4075, 0, "舍利子", "灵力+6"); ccc_txt_stone_insert(eProPerty::灵力, 6);
	insert(0x2CB3CC8D, 0xC365BC0A, 0, "神秘石", "躲避+40"); ccc_txt_stone_insert(eProPerty::躲避, 40);//武器/鞋子
	insert(0x52B2BFF6, 0x8FE88E79, 0, "太阳石", "伤害+8"); ccc_txt_stone_insert(eProPerty::伤害, 8);
	insert(0xCFF52FDF, 0xB6D2F539, 0, "月亮石", "防御+12"); ccc_txt_stone_insert(eProPerty::防御, 12);
	insert(0xACF3F837, 0xA1D20A1D, 0, "翡翠石", "法防+12"); ccc_txt_stone_insert(eProPerty::法防, 12); //铠甲
	insert(0xFC91C407, 0x6397856F, 0, "精魄灵石(红)", "速度+6"); ccc_txt_stone_insert(eProPerty::速度, 6);//项圈
	insert(0x9B0688A2, 0xACAC92BB, 0, "精魄灵石(黄)", "镶灵力+4"); ccc_txt_stone_insert(eProPerty::灵力, 4);//护腕
	insert(0x3BE0A96E, 0x489CFC78, 0, "精魄灵石(蓝)", "防御+8"); ccc_txt_stone_insert(eProPerty::防御, 8);  //铠甲
	insert(0xFC91C407, 0x6397856F, 0, "精魄灵石(红)", "躲避+30"); ccc_txt_stone_insert(eProPerty::躲避, 30); //项圈;
	insert(0x9B0688A2, 0xACAC92BB, 0, "精魄灵石(黄)", "伤害+10"); ccc_txt_stone_insert(eProPerty::伤害, 10); //护腕
	insert(0x3BE0A96E, 0x489CFC78, 0, "精魄灵石(蓝)", "镶气血+30"); ccc_txt_stone_insert(eProPerty::气血, 30);//铠甲
	insert(0x651D319C, 0xD7E9FDB3, 0, "红宝石", "火抗+2"); ccc_txt_stone_insert(eProPerty::火抗, 2);//项链/鞋子
	insert(0x88253E8D, 0x4A96C39E, 0, "黄宝石", "雷抗+2"); ccc_txt_stone_insert(eProPerty::雷抗, 2);//项链/鞋子
	insert(0x791427E4, 0x67107BB6, 0, "蓝宝石", "水抗+2"); ccc_txt_stone_insert(eProPerty::水抗, 2);//项链/鞋子
	insert(0xE59EFA68, 0x0DCD4F81, 0, "绿宝石", "土抗+2"); ccc_txt_stone_insert(eProPerty::土抗, 2);//项链/鞋子

#undef ccc_txt_stone_insert

	for (auto& it : *_table)
	{
		it.second.price = 50000;
		stone = stoneTable.at((eStone)it.first);
		it.second.desc = txtStone::toString(stone.pro) + toString("+%d", stone.value);
	}
}



void txtIcon::initJiaju()
{
	auto& jiajuTable = txtJiaju::getInstance()->_tables;
	initIdx();
	initTable(eIcon::一家y);
	insertJiaju1(0xBB7384E5, 0x1F74CEFC, 0, "一级家具", "黑麻垂曼帘", { 0x9CC0FC97, 0xECF29BBB });
	insertJiaju1(0x0EA3F791, 0x048FAED8, 0, "一级家具", "桦木圆桌", { 0x021B9BBE });
	insertJiaju1(0x40DBF469, 0x950DB91E, 0, "一级家具", "桦木立柜", { 0x534E2BC7, 0xF92EAB94 });
	insertJiaju1(0xD9706246, 0xC77CED21, 1, "一级家具", "草编地毯", { 0x5E95A672, 0x60CA8F51 });
	insertJiaju1(0x2A858ABF, 0xDD195E16, 0, "一级家具", "漆花竹凳", { 0x57B2FF33, 0x6D8CBB1A });
	insertJiaju1(0xA0F59CD4, 0xEA547557, 0, "一级家具", "榛木床", { 0x6D603700, 0xB3C53F3A });
	insertJiaju1(0xA3E461E0, 0xE6265000, 0, "一级家具", "文竹", { 0xFE72755B });
	insertJiaju1(0x8D1C9B16, 0x6E75C55E, 0, "一级家具", "印花屏风", { 0x1DD23345, 0x4853B8FA });
	insertJiaju1(0xAE1FE52C, 0x8A122388, 0, "一级家具", "君子兰", { 0x2D8A3513 });
	insertJiaju1(0xF1AA1CDC, 0x03DCA686, 0, "一级家具", "蝴蝶兰", { 0x74EF6D5E });
	insertJiaju1(0x10ACEF55, 0x2BA074EC, 0, "一级家具", "水仙", { 0x6A38DC23 });
	insertJiaju1(0x3970879B, 0xFB18050C, 0, "一级家具", "仙人掌", { 0xA5C0843E } );
	insertJiaju1(0x1802F06C, 0x966FD5CD, 0, "一级家具", "银烛台", { 0x8986C2B8 } );
	insertJiaju1(0x72B05C62, 0xBD83A424, 0, "一级家具", "玉瓷画瓶", { 0xF70BF42D });
	insertJiaju1(0x9C7E2DE5, 0x8479C234, 0, "一级家具", "八卦镇邪榻", { 0x25936E8E, 0x484F7A84 } );
	insertJiaju1(0x1D00C78D, 0xE14EA35A, 2, "一级家具", "踏春图", { 0x7E810230, 0xC6495528 });
	insertJiaju1(0xBC647367, 0x1133B493, 3, "一级家具", "漆花地板");


	initIdx();
	initTable(eIcon::二家e);
	insertJiaju2(0xD0522308, 0xBA96E2CF, 1, "二级家具", "白鹤展翅帘",{ 0xC93D6B43, 0xDB94B112 });
	insertJiaju2(0x43D43BC3, 0x59166107, 0, "二级家具", "蓝绸绣花帘",{ 0xCD5A958F, 0xE5B707B3 });
	insertJiaju2(0x1E3B47E4, 0xCE322B80, 0, "二级家具", "红木八仙桌",{ 0x24B0DB4B });
	insertJiaju2(0x749A8DE7, 0x822EDE52, 0, "二级家具", "嵌玉虎纹桌",{ 0xECE6D460 });
	insertJiaju2(0x7CF14A8C, 0xFC060E32, 0, "二级家具", "双鱼吉庆柜",{ 0xD4001A88, 0xEF30F5E4 });
	insertJiaju2(0x7336C5AB, 0x0E745545, 0, "二级家具", "神仙帐"    ,{ 0x3CD5A1C1, 0x5D3976CB });
	insertJiaju2(0xA52D57A2, 0x40DC127D, 0, "二级家具", "彩绘立柜"  ,{ 0x6CB98F54, 0xF197C6A3 });
	insertJiaju2(0x69CC2D84, 0xE3EFB84D, 1, "二级家具", "兽皮地毯"  ,{ 0x7F1049D7, 0xCE5F651C });
	insertJiaju2(0xFFC56CAC, 0x6A2EADCD, 1, "二级家具", "麻布地毯"  ,{ 0x0917AA70, 0xEC48F0DC });
	insertJiaju2(0x31FC79B2, 0x6FC9A4F8, 0, "二级家具", "桦木靠背椅",{ 0xD4582E5C, 0xEF3E35B6, 0x291F1300, 0x38D9122F });
	insertJiaju2(0x36FEC0EE, 0x958ACF12, 0, "二级家具", "月牙凳"    ,{ 0x43853A2F, 0xEEA4726F });
	insertJiaju2(0x0C15DCDE, 0xB77C05F8, 0, "二级家具", "狮子图屏风",{ 0xA97E7654, 0xEFACD8B5 });
	insertJiaju2(0x16B2E033, 0xA466DED1, 0, "二级家具", "花鸟图屏风",{ 0xBB82C17C, 0xC155D8B3 });
	insertJiaju2(0x2F988214, 0xC59023F1, 0, "二级家具", "天山云雪"  ,{ 0x6963D165 });
	insertJiaju2(0x17520E38, 0x338882F8, 0, "二级家具", "龟鹤延年灯",{ 0x9CB213E0, 0xF24B1171 });
	insertJiaju2(0x9FAC7C21, 0xDEC76AF6, 0, "二级家具", "长信宫灯"  ,{ 0x2224131A, 0x7C6C1872, 0x2D613E27, 0xD78587D1 });
	insertJiaju2(0x264A5EC9, 0xF0698B61, 0, "二级家具", "雕花马桶"  ,{ 0x4D5F3B18, 0xBBA82846 });
	insertJiaju2(0xD9438601, 0xA3274661, 0, "二级家具", "彩绘花瓶"  ,{ 0x7710A334 });
	insertJiaju2(0x64D8CADE, 0xCC5DD99C, 1, "二级家具", "夕阳山水图",{ 0xA75F8D0D, 0xC9368BE9 });
	insertJiaju2(0x47810AE4, 0x71746931, 1, "二级家具", "猛虎坐山图",{ 0x162A74B1, 0x9561FCA8 });
	insertJiaju2(0x03D705CA, 0x034FC4CD, 0, "二级家具", "海之青石凳",{ 0x53494D3F, 0x94970693 });
	insertJiaju2(0xE5D6ACF3, 0x51FD07AB, 0, "二级家具", "海之缎面帘",{ 0xF1BEC5D7, 0x4A4B88A5 });
	insertJiaju2(0xB8A9E98E, 0xB180CC8C, 0, "二级家具", "海之方桌"  ,{ 0x3BEC7A28 });
	insertJiaju2(0x19F7722C, 0xEC89DB91, 1, "二级家具", "海之珠贝图",{ 0x2ECBC105, 0x8ED10798 });
	insertJiaju2(0x9B80D08B, 0xCFD88602, 0, "二级家具", "玲珑兔圆桌",{ 0x3C8F92D6 });
	insertJiaju2(0xE2A1D30F, 0x8E5DC844, 3, "二级家具", "桦木地板");


	initIdx();
	initTable(eIcon::三家s);
	insertJiaju3(0x373D5C17, 0xE71A42E5, 1, "三级家具", "黄缎锦边帘", { 0x4D8E639F, 0xE649E0EA });
	insertJiaju3(0xDF3EB09B, 0xD78204FC, 0, "三级家具", "紫檀雕花柜", { 0xA666FD13, 0xEC841CBB });
	insertJiaju3(0x33181B3E, 0x38B5ADC6, 0, "三级家具", "百兽镇邪桌", { 0x3A4FB4E6 });
	insertJiaju3(0x34F3E6FA, 0xD941BC31, 0, "三级家具", "八宝呈祥桌", { 0x1D952151 });
	insertJiaju3(0x5FF1A254, 0xE01FC948, 1, "三级家具", "波斯地毯", { 0x3BA5C4F6, 0xA1DB3447 });
	insertJiaju3(0xE873EBDA, 0x2B479E5D, 1, "三级家具", "白虎皮毯", { 0xB590C8E6, 0xF8D7516B, 0x3611E764, 0xC07BE47B });
	insertJiaju3(0xA2F9250A, 0x6E1F9949, 0, "三级家具", "紫檀雕花椅", { 0x4547C5EF, 0x3B7D42C9, 0xF753388E, 0x7924DC61 });
	insertJiaju3(0xDD6A29AE, 0x9662814C, 0, "三级家具", "虎威太师椅", { 0xB50CCD0A, 0x12B7F681, 0xEEF34E15, 0xCDAF25A6 });
	insertJiaju3(0xCA7094E6, 0xF001907F, 0, "三级家具", "龙凤呈祥", { 0x3291E592, 0x368DA460 });
	insertJiaju3(0x1C93E78C, 0xEABCDF89, 0, "三级家具", "壮丽河山", { 0xA4D974C2, 0x335339A5 });
	insertJiaju3(0xBED2AAC0, 0xE43EE153, 0, "三级家具", "金座雕龙屏风", { 0x11C5B94D, 0x1981A498, 0xCCA34401, 0x70459F4E });
	insertJiaju3(0xA86184D9, 0x88C32E14, 0, "三级家具", "紫檀马桶", { 0xF019303B, 0x970FA734, 0x2AEF0F24, 0xDDCB9DA7 });
	insertJiaju3(0xFD182818, 0xA9B71F42, 0, "三级家具", "千佛图", { 0x4F87C814, 0x9F6EDC5B });
	insertJiaju3(0x09AE42B3, 0x4488275C, 1, "三级家具", "凤凰傲意图", { 0xADFDC47A, 0x19668C39 });
	insertJiaju3(0x9FD02022, 0x02033EE5, 0, "三级家具", "海之青石桌", { 0x95923CD3, 0x3B1D456E });
	insertJiaju3(0x2AA4AE65, 0x5860EB63, 0, "三级家具", "海之立柜", { 0x1476C1E4, 0x53B3F1E0 });
	insertJiaju3(0xF28F8139, 0xC496AD4B, 0, "三级家具", "海之藏经架", { 0xD0472BDB, 0x11E849D5 });
	insertJiaju3(0xEFFA3961, 0xA7A41835, 1, "三级家具", "海之彩鱼毯", { 0x56BBF2A8, 0x83A5CFDA });
	insertJiaju3(0x32DBA8F9, 0x8DA6C6F2, 0, "三级家具", "海之明珠屏", { 0xED3C864C, 0xCFA88113 });
	insertJiaju3(0x40F60DBE, 0x97449224, 0, "三级家具", "海之太师椅", { 0xBA7CA01F, 0xC8DCE357 });
	insertJiaju3(0x662A3791, 0x7A147AF6, 0, "三级家具", "海之明珠灯", { 0x9780A89A });
	insertJiaju3(0x3B4C5242, 0x3DA25A39, 0, "三级家具", "海之葵", { 0x03A9C116 });
	insertJiaju3(0xF10B5CF7, 0x999D22CA, 0, "三级家具", "海之巨螺桶", { 0xAC91B75A, 0x41E52168 });
	insertJiaju3(0x5275EB90, 0x30BB01D5, 1, "三级家具", "玲珑兔粉缎帘", { 0x264DB15E, 0x87A09DD8 });
	insertJiaju3(0x72BE0A7D, 0x0B576A19, 0, "三级家具", "玲珑兔立柜", { 0xC8812270, 0xEAB6DFBF });
	insertJiaju3(0x77EDFDF3, 0x33077071, 0, "三级家具", "玲珑兔藏经阁", { 0x9BA56928, 0x9C5EFD57 });
	insertJiaju3(0xB09069B1, 0xA3EF527E, 0, "三级家具", "玲珑兔书桌", { 0xA3579952, 0x72A926A3 });
	insertJiaju3(0x5A4A035E, 0xB0A011AB, 0, "三级家具", "玲珑兔靠背椅", { 0x09E22897, 0x6D4A10D7 });
	insertJiaju3(0x2122C450, 0x41E58771, 0, "三级家具", "玲珑兔摇摇椅", { 0xAF8AFBE6, 0x1F6632D7 });
	insertJiaju3(0x33E7AC88, 0x1F210E72, 0, "三级家具", "玲珑兔迎客屏", { 0xEB21E353, 0x0879D360 });
	insertJiaju3(0xE0F5CABF, 0x52F7CD47, 0, "三级家具", "玲珑兔花瓶", { 0x10B4308D });
	insertJiaju3(0x7BBB3636, 0x84AF8E15, 0, "三级家具", "玲珑兔惬意桶", { 0xF0D05250, 0x1B7BA35B });
	insertJiaju3(0xDD1346DC, 0x35997A39, 3, "三级家具", "红木地板");


	initIdx();
	initTable(eIcon::四家s);
	insertJiaju4(0x6C7143EF, 0x80D12303, 0, "四级家具", "红杏闹春帘", { 0x68F0DA23, 0xA5781F59 });
	insertJiaju4(0x7EF80073, 0xB3589DB5, 0, "四级家具", "招财聚宝柜", { 0x9B75BD21, 0x5E1DC5ED });
	insertJiaju4(0xDB9D4A0F, 0xA02C51DB, 0, "四级家具", "宁夜安梦", { 0x19AFB2FD, 0x788960BB });
	insertJiaju4(0xE14D7033, 0x085E408B, 0, "四级家具", "五谷轮回桶", { 0x1F389D5C, 0xE8E3C910, 0x1FE2A757, 0x62576574 });
	insertJiaju4(0x5F038868, 0xDF229700, 0, "四级家具", "海之珊瑚卧", { 0xE8376979, 0x977D7705 });
	insertJiaju4(0x58F496BC, 0xD13E4DC7, 0, "四级家具", "海之彩贝榻", { 0xE9EAE8CC, 0x4FFD83D8 });
	insertJiaju4(0x81F0A83B, 0x3ACEA619, 0, "四级家具", "玲珑兔贵妃卧", { 0x7D12C9A8, 0xEE1C2260 });
	insertJiaju4(0x8D09DB3D, 0x6122DCE1, 0, "四级家具", "玲珑兔甜梦榻", { 0x4BA2D2CC, 0x4BED0579 });
	insertJiaju4(0xFC2C30F8, 0x7431C5CE, 0, "四级家具", "博古通今桌", { 0x000799C4, 0x4216D197, 0xBA484F88, 0xCB1A0B3B });
	insertJiaju4(0xB9B3D96E, 0xE123EFC8, 0, "四级家具", "翠珠梳妆台", { 0x4EE23265, 0xFE56A6D6 });
	insertJiaju4(0xC57E291C, 0x75CA8F58, 0, "四级家具", "紫檀藏经阁", { 0x3C392709, 0x2436E56F });
	insertJiaju4(0x5519E14F, 0x08624B19, 0, "四级家具", "怡然太师椅", { 0x0E73E53D, 0x794F1443, 0xCAB4283D, 0xDC42F2AD });
	insertJiaju4(0x76F7CA15, 0x0C7BDBAB, 0, "四级家具", "雕花贵妃卧", { 0x15EECE3E, 0x219C1D33 });
	insertJiaju4(0x6E26C2AC, 0xBAFB2D90, 0, "四级家具", "福禄鸳鸯榻", { 0x68596FB3, 0x402D59BB });
	insertJiaju4(0x861E05F9, 0x4917E304, 0, "四级家具", "吉祥祈福案", { 0x02C93AAF, 0x899A7B0C });
//	insert(0x9A928602, 0x811D9452, 4, "四级家具", "花开富贵门");
	insertJiaju4(0xE15A8F82, 0x5A483B55, 5, "四级家具", "海之七色门", { 0xF8696164, 0xD6B0B056, 0x9B4C9F9C, 0x70526BE6, 0x4B24E1A5, 0x41B08225, 0x283DA162, 0x4527CD80, 0x4C1BA5B0, 0x71666D92, 0xD40C60C5 });
	insertJiaju4(0x380BD908, 0x4CEE4CD2, 4, "四级家具", "玲珑兔美梦屏风", { 0xDCCF29C0, 0xB8A8530C, 0xF3DD138B, 0x5D09B0B6, 0x6C0C8D98, 0x4353C25C });
	insertJiaju4(0xA14743EA, 0x5459750C, 3, "四级家具", "海之蔚蓝石砖");
	insertJiaju4(0xA4CEBA00, 0x880A08ED, 3, "四级家具", "玲珑兔梦幻家园");

}



void txtIcon::initMenpai()
{
	initIdx();
	initTable(eIcon::大唐d);
	insertMenpai(0x7A33A5A9, 0x8B6687C7, "为官之道");
	insertMenpai(0xB2BCD78E, 0x83510218, "无双一击");
	insertMenpai(0xFCF64BB4, 0x2C4A485C, "神兵鉴赏");
	insertMenpai(0x20EB6BD0, 0x7D6C0800, "疾风步");
	insertMenpai(0xF4D93CEB, 0x43D35D1B, "十方无敌");
	insertMenpai(0x73C87FDE, 0xEAE7112A, "紫薇之术");
	insertMenpai(0xBBCCFA4E, 0x65DB91C9, "文韬武略");

	initIdx();
	initTable(eIcon::化生h);
	insertMenpai(0x5DC9B771, 0xAE58AD12, "小乘佛法");
	insertMenpai(0xE6409CE3, 0x98FFC4AD, "金刚伏魔");
	insertMenpai(0xD1919F3D, 0x7287C064, "诵经");
	insertMenpai(0xEC71CE44, 0x4B8C1B65, "佛光普照");
	insertMenpai(0x058EC75B, 0x7A8856F3, "大慈大悲");
	insertMenpai(0x86C94C7C, 0x8F00A676, "歧黄之术");
	insertMenpai(0x3004AA75, 0xA8939527, "渡世步");

	initIdx();
	initTable(eIcon::女儿n);
	insertMenpai(0x47B9EF90, 0xBC69ED1E, "毒经");
	insertMenpai(0x56E88235, 0x23697214, "倾国倾城");
	insertMenpai(0x3EC00B8D, 0x1618C7AD, "沉鱼落雁");
	insertMenpai(0xFB265F9E, 0xC5F34CFB, "闭月羞花");
	insertMenpai(0x52788E94, 0xD280080E, "香飘兰麝");
	insertMenpai(0x86FEEA94, 0xCCF72E77, "玉质冰肌");
	insertMenpai(0x91B45987, 0x3D453325, "清歌妙舞");

	initIdx();
	initTable(eIcon::方寸f);
	insertMenpai(0x59783586, 0x9FC18E51, "黄庭经");
	insertMenpai(0x74F253D9, 0x19396997, "磬龙灭法");
	insertMenpai(0x11EAAE6D, 0x0336EB9B, "霹雳咒");
	insertMenpai(0x36F26348, 0xD68D198D, "符之术");
	insertMenpai(0xB293CF00, 0xCD48FDFF, "归元心法");
	insertMenpai(0xE5A2EB07, 0x684DEBB0, "神道无念");
	insertMenpai(0x7E9CCF04, 0x2DD65965, "斜月步");

	initIdx();
	initTable(eIcon::狮驼s);
	insertMenpai(0x009BEBDA, 0xB0013AB2, "魔兽神功");
	insertMenpai(0x513A8A78, 0xBAECB102, "生死搏");
	insertMenpai(0xBA7AD05B, 0x4694D927, "驯兽诀");
	insertMenpai(0xFC7EDF4C, 0x28BACE76, "阴阳二气诀");
	insertMenpai(0x8B61AADA, 0x630CE9C2, "狂兽诀");
	insertMenpai(0x832ACED9, 0x4A1E39A3, "大鹏展翅");
	insertMenpai(0x5108D3A7, 0x1E8A79DF, "魔兽反噬");

	initIdx();
	initTable(eIcon::魔王m);
	insertMenpai(0xA36C5AA6, 0xECEF9C70, "牛逼神功");
	insertMenpai(0x7244B8D8, 0x56612F8E, "震天诀");
	insertMenpai(0x3632166A, 0xF85D38D4, "火云术");
	insertMenpai(0x50F19558, 0x72491389, "火牛阵");
	insertMenpai(0x9495B98F, 0x43541BC6, "牛虱阵");
	insertMenpai(0x9F0522B9, 0x48FC858E, "回身击");
	insertMenpai(0xC70D4DA4, 0xFF7AB8FE, "裂石步");

	initIdx();
	initTable(eIcon::盘丝p);
	insertMenpai(0x8523F7A5, 0x1D0E8D52, "蛛丝阵法");
	insertMenpai(0xB8EACFC0, 0x8FA9C1D7, "催情大法");
	insertMenpai(0x3A278387, 0x653EB3E2, "秋波暗送");
	insertMenpai(0x8AFB1A80, 0xE3ADB1EB, "天外魔音");
	insertMenpai(0x0829E95B, 0x97B0F3BB, "盘丝大法");
	insertMenpai(0x141B5E54, 0xCB126977, "移形换影");
	insertMenpai(0x2397ABE7, 0xBD6854D3, "姐妹相随");

	initIdx();
	initTable(eIcon::地府d);
	insertMenpai(0x2267FDE2, 0x2975C865, "灵通术");
	insertMenpai(0x68FBF782, 0x829863CF, "六道轮回");
	insertMenpai(0x18BC5193, 0x7D7E42B5, "幽冥术");
	insertMenpai(0xCAD7422A, 0x60B5C339, "拘魂诀");
	insertMenpai(0xA717E4EC, 0x90AD7379, "九幽阴魂");
	insertMenpai(0x015E36F3, 0xEE4186E1, "尸腐恶");
	insertMenpai(0x0448AB94, 0xA53AE1E3, "无常步");

	initIdx();
	initTable(eIcon::龙宫l);
	insertMenpai(0x37118266, 0x085CAE13, "九龙诀");
	insertMenpai(0xC57A39B9, 0xF650D185, "破浪诀");
	insertMenpai(0x726EFA79, 0x1A1DE0D4, "呼风唤雨");
	insertMenpai(0x80426D9F, 0xCEEAA576, "龙腾");
	insertMenpai(0xCB06F1FB, 0xB904AD16, "逆鳞");
	insertMenpai(0x12DCA762, 0x671FC66C, "游龙术");
	insertMenpai(0xE007F365, 0xDD742E3A, "龙附");

	initIdx();
	initTable(eIcon::五庄w);
	insertMenpai(0xBDB57B3E, 0x38BA101C, "周易学");
	insertMenpai(0xA24E38FE, 0xD30FDF54, "潇湘仙雨");
	insertMenpai(0xCD3C3C12, 0x86832A8C, "乾坤袖");
	insertMenpai(0x63C0827A, 0xDE2533AE, "修仙术");
	insertMenpai(0xE2720478, 0x283D1B37, "混元道果");
	insertMenpai(0xB7426D01, 0xF49FDAFE, "明性修身");
	insertMenpai(0x8F0D6C4C, 0x3712E54D, "七星遁");

	initIdx();
	initTable(eIcon::普陀p);
	insertMenpai(0xBB5973EF, 0xEB6872B2, "灵性");
	insertMenpai(0x0506BE5D, 0x0D4CE946, "护法金刚");
	insertMenpai(0x71F0219A, 0x5413DD44, "观音咒");
	insertMenpai(0x2BB9F19E, 0xD95C9242, "五行学说");
	insertMenpai(0xF5BD9EB4, 0x91B95A02, "金刚经");
	insertMenpai(0xCE175363, 0xC21CFA93, "五行扭转");
	insertMenpai(0x8347AA63, 0x02427B90, "莲花宝座");

	initIdx();
	initTable(eIcon::天宫t);
	insertMenpai(0x1EDA4D57, 0xFBCA1857, "天罡气");
	insertMenpai(0x3E89723E, 0xB2E190E8, "傲世诀");
	insertMenpai(0xE509DEF5, 0xC096279E, "清明自在");
	insertMenpai(0xD4FE4342, 0x75FC0B6E, "宁气诀");
	insertMenpai(0xB3B26849, 0x268A8DE5, "乾坤塔");
	insertMenpai(0x1CB7C4FF, 0xD92B56C2, "混天术");
	insertMenpai(0xE80ED007, 0x1079CE8A, "云霄步");

	initIdx();
	initTable(eIcon::凌波l);
	insertMenpai(0xD854B619, 0x9BF40DC5, "天地无极");
	insertMenpai(0x66878D1C, 0x6D83F3D1, "九转玄功");
	insertMenpai(0x8837F110, 0xC080EE77, "武神显圣");
	insertMenpai(0x2F79B759, 0x687EDEFE, "啸傲");
	insertMenpai(0x6027C7C6, 0xEEC348EA, "气吞山河");
	insertMenpai(0xA70C7A5A, 0x08F2E772, "诛魔");
	insertMenpai(0xEAB341B6, 0xAA65C1F5, "法天象地");

	initIdx();
	initTable(eIcon::无底w);
	insertMenpai(0xC21CAA3F, 0xEB4FD0B6, "枯骨心法");
	insertMenpai(0x8DAA624D, 0x229B3F36, "阴风绝章");
	insertMenpai(0x2648B742, 0x7F61F010, "鬼蛊灵蕴");
	insertMenpai(0x77DE4303, 0x8386CD36, "燃灯灵宝");
	insertMenpai(0x47B1845A, 0x7B30715D, "地冥妙法");
	insertMenpai(0x7B209C81, 0xC8B6A6A3, "混元神功");
	insertMenpai(0x87D67BAB, 0xF0E46F02, "秘影迷踪");

	initIdx();
	initTable(eIcon::神木s);
	insertMenpai(0xD7468834, 0x056EAA54, "瞬息万变");
	insertMenpai(0xD89652AE, 0x63BC74C4, "万灵诸念");
	insertMenpai(0xEB2A7B26, 0x52B73EBF, "巫咒");
	insertMenpai(0xD37FE4A6, 0x0E11E662, "万物轮转");
	insertMenpai(0x9E505CED, 0x1BCE436A, "天人庇护");
	insertMenpai(0x2ED87112, 0x71EB94AA, "神木恩泽");
	insertMenpai(0x5AD8D3E2, 0xB3E852DE, "驭灵咒");
}



void txtIcon::initSkill()
{
	initTable(eIcon::技能j);
	insertSkill(0x1379151C, 0x99732F02, eSkill::反击, "反击", "受到物理攻击有25%几率反击,反击伤害减半");
	insertSkill(0x01884D50, 0xE9CD05B8, eSkill::反击2, "高级反击", "受到物理攻击有35%几率反击");
	insertSkill(0xDFC6FDFC, 0xEAE7E3EC, eSkill::反震, "反震", "受到物理攻击有25%几率反震25%的伤害");
	insertSkill(0x1E7F5930, 0x71B0F5EE, eSkill::反震2, "高级反震", "受到物理攻击有35%几率反震50%的伤害");
	insertSkill(0x09556A2E, 0x27D53971, eSkill::吸血, "吸血", "物理攻击有15%的吸血效果");
	insertSkill(0x97B369D6, 0x515A38AD, eSkill::吸血2, "高级吸血", "物理攻击有25%的吸血效果");
	insertSkill(0x31C34438, 0x4534723B, eSkill::连击, "连击", "物理攻击有45%的连击率,伤害下降25%");
	insertSkill(0xB3C6A6E2, 0x4ECA2A0F, eSkill::连击2, "高级连击", "物理攻击有55%的连击率,伤害下降20%");
	insertSkill(0x46FA5E55, 0x307E28C8, eSkill::飞行, "飞行", "回避率+10%,命中率+10%,但受暗器伤害+50%");
	insertSkill(0xE5A9F47C, 0xFEF30F0D, eSkill::飞行2, "高级飞行", "回避率+15%,命中率+15%,但受暗器伤害+20%");
	insertSkill(0xEB2AF42F, 0xDD5CEE60, eSkill::夜战, "夜战", "夜晚伤害不降");
	insertSkill(0x5906A6A0, 0x3E81ECFB, eSkill::夜战2, "高级夜战", "夜晚伤害+5%");
	insertSkill(0xB3488AAE, 0x59E4822E, eSkill::隐身, "隐身", "2回合");
	insertSkill(0xAFB8E892, 0x9484D8DE, eSkill::隐身2, "高级隐身", "5回合");
	insertSkill(0xEF245DFC, 0xDB2B3C6A, eSkill::感知, "感知", "可以攻击隐身状态下的敌人");
	insertSkill(0x6CA45F1F, 0x2840330D, eSkill::感知2, "高级感知", "可以攻击隐身状态下的敌人");
	insertSkill(0x86F93A3B, 0xC3F77E8F, eSkill::再生, "再生", "每回合回复气血=等级");
	insertSkill(0xE3126879, 0x1BE87C60, eSkill::再生2, "高级再生", "每回合回复气血=等级*2");
	insertSkill(0xD3E2714A, 0x2514ED1F, eSkill::冥思, "冥思", "每回合回复魔法=等级/4");
	insertSkill(0x81A302FF, 0x66718220, eSkill::冥思2, "高级冥思", "每回合回复魔法=等级/2");
	insertSkill(0xC89A9EDC, 0x56DEF316, eSkill::慧根, "慧根", "法术消耗-25%");
	insertSkill(0xF8CE3E63, 0x0E6F601D, eSkill::慧根2, "高级慧根", "法术消耗减半");
	insertSkill(0x420269A4, 0xE1DA16D6, eSkill::必杀, "必杀", "必杀率+10%");
	insertSkill(0x4C700EA4, 0x63B6486D, eSkill::必杀2, "高级必杀", "必杀率+20%");
	insertSkill(0x40B80312, 0xD8F7385A, eSkill::幸运, "幸运", "免疫必杀");
	insertSkill(0x1CB6FA78, 0x6A29156C, eSkill::幸运2, "高级幸运", "免疫必杀,法术躲避率+10%");
	insertSkill(0x4772D507, 0x4A3BBF91, eSkill::神迹, "神迹", "每回合开始摆脱异常状态");
	insertSkill(0xFC717CFD, 0x2A1026D7, eSkill::神迹2, "高级神迹", "免疫异常状态");
	insertSkill(0xD16002DC, 0x8E539BBA, eSkill::招架, "招架", "格档率+5%");
	insertSkill(0x3CBAC3A9, 0x1ADFDD2B, eSkill::招架2, "高级招架", "格档率+10%");
	insertSkill(0x59EBCAAD, 0x7680EBA8, eSkill::永恒, "永恒", "增益效果时间+3回合");
	insertSkill(0xEC4339C2, 0xF86EA690, eSkill::永恒2, "高级永恒", "增益效果时间+6回合");
	insertSkill(0xFFAC3F6A, 0xBABA11E3, eSkill::敏捷, "敏捷", "速度+10%");
	insertSkill(0x7ADDCB60, 0x4A654A53, eSkill::敏捷2, "高级敏捷", "速度+20%");
	insertSkill(0x2A2C6FCB, 0x56F51981, eSkill::强力, "强力", "攻击力+等级/2");
	insertSkill(0x81C9C93E, 0xD466B3D1, eSkill::强力2, "高级强力", "攻击力+等级/1");
	insertSkill(0xF47ADB17, 0x05728F4B, eSkill::防御, "防御", "防御+等级/2");
	insertSkill(0xE17C3B8E, 0x60551819, eSkill::防御2, "高级防御", "防御+等级/1");
	insertSkill(0x0C425BC3, 0xB5C24835, eSkill::偷袭, "偷袭", "免疫反震反击");
	insertSkill(0x5CB8D73F, 0xEF2EB5D4, eSkill::偷袭2, "高级偷袭", "免疫反震反击, 伤害+5%");
	insertSkill(0xE2C478F8, 0x087AB3EA, eSkill::毒, "毒", "攻击时有10%几率使对手中毒");
	insertSkill(0x40BE8F5E, 0x23205169, eSkill::毒2, "高级毒", "攻击时有15%几率使对手中毒");
	insertSkill(0x7BD73DE0, 0x18CC6B26, eSkill::驱鬼, "驱鬼", "对有鬼魂术的目标伤害+50%");
	insertSkill(0xCBCF6BE3, 0x04512FE2, eSkill::驱鬼2, "高级驱鬼", "对有鬼魂术的目标伤害+100%");
	insertSkill(0xFEE50FAB, 0x307CF1BE, eSkill::鬼魂术, "鬼魂术", "免疫异常状态,死后7回合复活");
	insertSkill(0xD3794A73, 0x913D7735, eSkill::鬼魂术2, "高级鬼魂术", "免疫异常状态,死后5回合复活");
	insertSkill(0x87C81C63, 0x2AD5089A, eSkill::魔之心, "魔之心", "法术伤害+10%");
	insertSkill(0xAB67DBAB, 0x9A24567A, eSkill::魔之心2, "高级魔之心", "法术伤害+20%");
	insertSkill(0xAF7442C5, 0x54037CFF, eSkill::神佑复生, "神佑复生", "死亡时有20%几率复活50%气血");
	insertSkill(0xB5CA5D93, 0x799E08CE, eSkill::神佑复生2, "高级神佑复生", "死亡时有30%几率复活100%气血");
	insertSkill(0xA6DFC207, 0xF6E0F4C0, eSkill::精神集中, "精神集中", "10%抵抗异常");
	insertSkill(0x8EB9B230, 0xBA10735B, eSkill::精神集中2, "高级精神集中", "20%抵抗异常");
	insertSkill(0xB2F61506, 0xC763E399, eSkill::否定信仰, "否定信仰", "击败敌人时,对方神佑率下降10%");
	insertSkill(0x9204C942, 0x1CE3C56D, eSkill::否定信仰2, "高级否定信仰", "击败敌人时,对方神佑率下降20%");
	insertSkill(0x149AB0A5, 0x83251A3C, eSkill::法术连击, "法术连击", "法术15%的几率连击");
	insertSkill(0x70B62C09, 0xCFB487A4, eSkill::法术连击2, "高级法术连击", "法术25%的几率连击");
	insertSkill(0x4210A339, 0x52D97379, eSkill::法术暴击, "法术暴击", "法术10%的几率暴击");
	insertSkill(0x610B7489, 0x7B7E1F49, eSkill::法术暴击2, "高级法术暴击", "法术20%的几率暴击");
	insertSkill(0x0FF374D8, 0x2D6EE6B5, eSkill::法术波动, "法术波动", "100-110%");
	insertSkill(0xDAAF4328, 0x8A6FD1EC, eSkill::法术波动2, "高级法术波动", "100-120%");
	insertSkill(0xB2F61506, 0xE861CC5D, eSkill::迟钝, "迟钝", "速度-50%");
	insertSkill(0x105F0207, 0x9C1EEE54, eSkill::迟钝2, "高级迟钝", "速度-80%");
	insertSkill(0xC58CA678, 0xA71D860C, eSkill::雷属性吸收, "雷属性吸收", "受到雷属性攻击20%吸收伤害");
	insertSkill(0x0723D081, 0x629C475E, eSkill::雷属性吸收2, "高级雷属性吸收", "受到雷属性攻击30%吸收伤害");
	insertSkill(0xD0CD6B99, 0x0801A3EA, eSkill::土属性吸收, "土属性吸收", "受到土属性攻击20%吸收伤害");
	insertSkill(0x2CD0288C, 0x9D518016, eSkill::土属性吸收2, "高级土属性吸收", "受到土属性攻击30%吸收伤害");
	insertSkill(0xF3EDE679, 0xF442D468, eSkill::火属性吸收, "火属性吸收", "受到火属性攻击20%吸收伤害");
	insertSkill(0x50118271, 0xACBCC108, eSkill::火属性吸收2, "高级火属性吸收", "受到火属性攻击30%吸收伤害");
	insertSkill(0x68B24211, 0x0584205F, eSkill::水属性吸收, "水属性吸收", "受到水属性攻击20%吸收伤害");
	insertSkill(0x4E36441F, 0x96F0C044, eSkill::水属性吸收2, "高级水属性吸收", "受到水属性攻击30%吸收伤害");
	insertSkill(0x00000000, 0x04B409B4, eSkill::盾气, "盾气", "进入战斗临时增加(等级*1)的防御,持续5回合且递减");
	insertSkill(0x00000000, 0x8EC237B5, eSkill::盾气2, "高级盾气", "进入战斗临时增加(等级*2)的防御,持续5回合且递减");
	insertSkill(0x00000000, 0x3EDD86F8, eSkill::法术抵抗, "法术抵抗", "受到法术伤害-15%");
	insertSkill(0x00000000, 0xE8FD17ED, eSkill::法术抵抗2, "高级法术抵抗", "受到法术伤害-25%");
	insertSkill(0x00000000, 0xA94D8FEA, eSkill::合纵, "合纵", "攻击无视对方4%防御");
	insertSkill(0x00000000, 0x4EAD21FF, eSkill::合纵2, "高级合纵", "攻击无视对方8%防御");
	insertSkill(0xEEC21546, 0x5C279D6E, eSkill::弱点火, "弱点火", "受到火属性攻击伤害+50%");
	insertSkill(0x4267A335, 0x2FEC0881, eSkill::弱点水, "弱点水", "受到水属性攻击伤害+50%");
	insertSkill(0x36438B51, 0x853524D8, eSkill::弱点土, "弱点土", "受到土属性攻击伤害+50%");
	insertSkill(0x9B4F6936, 0xAC0696AE, eSkill::弱点雷, "弱点雷", "受到雷属性攻击伤害+50%");
	insertSkill(0x00000000, 0x5886F7D3, eSkill::移花接木, "移花接木", "暗器伤害-99%");
	insertSkill(0x00000000, 0xDEF6EAF8, eSkill::灵能激发, "灵能激发", "进入战斗临时增加(等级*1)的灵力,持续5回合且递减");
	insertSkill(0x00000000, 0xC3F4BC0D, eSkill::嗜血追击, "嗜血追击", "目标死亡后追加攻击另一个目标");
	insertSkill(0x00000000, 0x87FC2C8A, eSkill::法力陷阱, "法力陷阱", "30%反弹25%的法术伤害");
	insertSkill(3844768104, 0xE52A8168, eSkill::浮云神马, "浮云神马", "在场时提高自身和主人10%速度5回合");
	insertSkill(0x00000000, 0xC6724A1D, eSkill::苍鸾怒击, "苍鸾怒击", "必杀或连击时,随机追击另一目标,每回合最多触发一次");
	insertSkill(0x00000000, 0x4BB2CD64, eSkill::须弥真言, "须弥真言", "增加魔力*0.4的法术伤害");
	insertSkill(0x00000000, 0x7FFF65B8, eSkill::从天而降, "从天而降", "增加普通攻击时造成的伤害,但有可能腾空失败");
	insertSkill(0x00000000, 0xDFCC02E3, eSkill::灵山禅语, "灵山禅语", "牺牲法术伤害,增加魔力*1的法防");
	insertSkill(0x00000000, 0xFF01A989, eSkill::千钧一怒, "千钧一怒", "普通攻击造成的伤害>=气血10%,自己的主人会获得10点愤怒");
	insertSkill(0x00000000, 0x230CEC5B, eSkill::龙魂, "龙魂", "每三次成功使用法术都会增加自身法术伤害");
	insertSkill(0x00000000, 0x4E3C17E0, eSkill::大快朵颐, "大快朵颐", "普通攻击时有几率提高连击和必杀的概率");
	// 辅助
	insertSkill(0x6F838C3B, 0x9285D9EB, eSkill::强壮, "强壮", "每级+5点气血上限");
	insertSkill(0x2BB02FD3, 0xD6750E0D, eSkill::强身术, "强身术", "每级加1%的气血上限");
	insertSkill(0x35D2CD77, 0x05CA3AA8, eSkill::冥想, "冥想", "每级加1%的魔法上限");
	insertSkill(0x57D857C0, 0x7D3C4887, eSkill::暗器技巧, "暗器技巧", "每级暗器伤害+1%");
	insertSkill(0x617743DB, 0xE67220ED, eSkill::打造技巧, "打造技巧", "造武器时的人品上升");
	insertSkill(0x68D513E9, 0x3FE32FC2, eSkill::裁缝技巧, "裁缝技巧", "造衣服时的人品上升");
	insertSkill(0x13E6F3B0, 0x4EF982E4, eSkill::炼金术, "炼金术", "造项链,鞋子,腰带时,人品上升");
	insertSkill(0x2649EAD5, 0xE72ED95F, eSkill::中药医理, "中药医理", "可以制作药物");
	insertSkill(0xE172DE46, 0x785A800E, eSkill::烹饪技巧, "烹饪技巧", "可以制作烹饪");
	insertSkill(0x6C81040C, 0x476CFC92, eSkill::逃离技巧, "逃离技巧", "每级+1%的逃跑成功率");
	insertSkill(0x35C9EAD4, 0x075D782F, eSkill::追捕技巧, "追捕技巧", "每级敌人的逃跑成功率-1%");
	insertSkill(0x6179CA67, 0x39BF36FD, eSkill::养生之道, "养生之道", "每级+5点活力上限");
	insertSkill(0xBC31F555, 0xD5F04CC0, eSkill::健身术, "健身术", "每级+5点体力上限");
	// 剧情
	insertSkill(0xE9D07953, 0x43CBAF9C, eSkill::火眼金睛, "火眼金睛", "");
	insertSkill(0x61197BD5, 0x93EAB2C8, eSkill::丹元济会, "丹元济会", "");
	insertSkill(0x55CD16AC, 0x8466E376, eSkill::妙手空空, "妙手空空", "");
	insertSkill(0x03B593E3, 0x70FB3A0E, eSkill::召唤兽图鉴, "召唤兽图鉴", "");
	insertSkill(0x3F7B9F82, 0x5A2821B8, eSkill::变化咒, "变化咒", "");
	insertSkill(0x20D43900, 0xDF55F6EF, eSkill::梦幻卡牌, "梦幻卡牌", "");
	insertSkill(0xCB9C5ECC, 0x58F2DDB8, eSkill::小试牛刀, "小试牛刀", "");
	insertSkill(0xC0F1CE88, 0x59EDC2D6, eSkill::猜拳, "猜拳", "");
	insertSkill(0xB6FAD6C9, 0x59FEE007, eSkill::五子棋, "五子棋", "");
	insertSkill(0xE588745D, 0xDB84A5CB, eSkill::装备图鉴, "装备图鉴", "");
	insertSkill(0x2E8A8A30, 0x135FA17A, eSkill::熔炼技巧, "熔炼技巧", "");
	insertSkill(0x72DE84DF, 0x46B9DE47, eSkill::灵石技巧, "灵石技巧", "");
	insertSkill(0x4D48EC9A, 0xB490C429, eSkill::巧匠之术, "巧匠之术", "");
	insertSkill(0x6AAEF804, 0x0D167BFB, eSkill::古董评估, "古董评估", "");
	insertSkill(0x9F2DFDB6, 0x16418D92, eSkill::建筑之术, "建筑之术", "");
	insertSkill(0x47877A93, 0x25064DE5, eSkill::仙灵店铺, "仙灵店铺", "");
	// 坐骑
	insertSkill(0x3FC666BA, 0x00000000, eSkill::破釜沉舟_坐骑, "破釜沉舟", "");
	insertSkill(0x2D685412, 0x00000000, eSkill::开天辟地, "开天辟地", "");
	insertSkill(0x077F08D1, 0x00000000, eSkill::正身清心, "正身清心", "");
	insertSkill(0x497B7159, 0x00000000, eSkill::延年益寿, "延年益寿", "");
	insertSkill(0x624C7E94, 0x00000000, eSkill::金刚护身, "金刚护身", "");
	insertSkill(0x6A4612D6, 0x00000000, eSkill::忠贯日月, "忠贯日月", "");
	insertSkill(0x83A054A5, 0x00000000, eSkill::炫火乱舞, "炫火乱舞", "");
	insertSkill(0xA2572FFC, 0x00000000, eSkill::乾坤借速, "乾坤借速", "");
	insertSkill(0xD1EBF7E3, 0x00000000, eSkill::水来土掩, "水来土掩", "");
	insertSkill(0xD3236E57, 0x00000000, eSkill::飞火流星, "飞火流星", "");
	insertSkill(0xE2296705, 0x00000000, eSkill::大浪淘沙, "大浪淘沙", "");
	insertSkill(0xF0F2E8F1, 0x00000000, eSkill::铜墙铁壁, "铜墙铁壁", "");

	// 宝宝
	insertSkill(0x94BFA7D9, 0xC6E68077, eSkill::雷击, "雷击", "", "Mp_30");
	insertSkill(0xDA8731E8, 0xAA631753, eSkill::奔雷咒, "奔雷咒", "", "Mps_30");
	insertSkill(0x11F08BC1, 0xFBEEDD94, eSkill::落岩, "落岩", "", "Mp_30");
	insertSkill(0xFD4BCB54, 0x1BA20D9E, eSkill::泰山压顶, "泰山压顶", "", "Mps_30");
	insertSkill(0x8FF8B5C0, 0x0511E729, eSkill::水攻, "水攻", "", "Mp_30");
	insertSkill(0xE6883491, 0x9D368B02, eSkill::水漫金山, "水漫金山", "", "Mps_30");
	insertSkill(0x636DADB0, 0xB0CBEBBF, eSkill::烈火, "烈火", "", "Mp_30");
	insertSkill(0xB55E9384, 0xFBBBE334, eSkill::地狱烈火, "地狱烈火", "", "Mps_30");
	insertSkill(0x1671DDFD, 0x1C22C610, eSkill::惊心一剑, "惊心一剑", "攻击并减少对方魔法", "Mp_30");
	insertSkill(0x6D382036, 0x1719FC84, eSkill::夜舞倾城, "夜舞倾城", "广场舞的杀伤力", "Lv_1_10");
	insertSkill(0xFF0E4570, 0x48A24731, eSkill::死亡召唤, "死亡召唤", "15%死亡禁锢", "Lv_1_10");
	insertSkill(0x848155A0, 0xD88B6D52, eSkill::力劈华山, "力劈华山", "伤害低你就惨了", "Lv_2_50");
	insertSkill(0x00000000, 0x63770E47, eSkill::剑荡四方, "剑荡四方", "小浪涌", "HP_10");
	insertSkill(0x2513128B, 0x3543B96C, eSkill::法术防御, "法术防御", "受到法术伤害-60%", "Lv_1_10");
	insertSkill(0x71267227, 0x263B68C3, eSkill::善恶有报, "善恶有报", "不是不报时候未到", "Lv_1_10");
	insertSkill(0x00000000, 0xF1D5925A, eSkill::壁垒击破, "壁垒击破", "防御你就惨了", "Lv_1_10");
	insertSkill(0x00000000, 0x35C47AF8, eSkill::无畏布施, "无畏布施", "增加目标的防御和法防,但会降低自身的防御和法防", "Lv_2_50");
	insertSkill(0x00000000, 0x5BCBB249, eSkill::天降灵葫, "天降灵葫", "随机法术1-5个目标", "Lv_3_30");
	insertSkill(0x00000000, 0xCB238CFE, eSkill::月光, "月光", "代表月亮消灭你", "Lv_1_10");
	insertSkill(0xADA2838B, 0xAA1341AF, eSkill::上古灵符, "上古灵符", "随机施展单体法术", "Lv_1_10");
	insertSkill(0x00000000, 0x00000000, eSkill::吸星大法, "吸星大法", "吸干你", "Mp_200");
	// 特技(descCost空的不要)
	insertSkill(0x35F72F87, 0x0A71DEE7, eSkill::气疗术, "气疗术", "气血+3%+200", "30");
	insertSkill(0xFD3187C7, 0x73735CAC, eSkill::心疗术, "心疗术", "气血+6%+400", "60");
	insertSkill(0x48650DE3, 0x8AB448F6, eSkill::命疗术, "命疗术", "气血+9%+600", "90");
	insertSkill(0xFC3656C8, 0x852E36F5, eSkill::凝气诀, "凝气诀", "魔法+10%+150", "60");
	insertSkill(0xD63AE21B, 0xB36F0828, eSkill::凝神诀, "凝神诀", "魔法+15%+240", "90");
	insertSkill(0x598125FD, 0x67F2A70E, eSkill::气归术, "气归术", "自身气血+25%", "60");
	insertSkill(0x4DCB689E, 0x9A1985E8, eSkill::命归术, "命归术", "自身气血+50%", "130");
	insertSkill(0x8574CDF1, 0x78276F30, eSkill::四海升平, "四海升平", "全体气血+25%", "135");
	insertSkill(0x97838895, 0xE364BF7C, eSkill::回魂咒, "回魂咒", "复活+150", "100");
	insertSkill(0xC3793063, 0x83797F7C, eSkill::起死回生, "起死回生", "复活+50%", "120");
	insertSkill(0x85097919, 0x76847896, eSkill::水清诀, "水清诀", "解除异常", "50");
	insertSkill(0x3B44EE0A, 0xFE796634, eSkill::冰清诀, "冰清诀", "解除异常状态,气血+25%", "100");
	insertSkill(0x3F79D19F, 0x8A21BA6C, eSkill::玉清诀, "玉清诀", "全体解除异常", "125");
	insertSkill(0x82297D26, 0xF81CEDEA, eSkill::晶清诀, "晶清诀", "全体解除异常,气血+15%", "150");
	insertSkill(0x1FFC5C36, 0x6344D17A, eSkill::空位1, "", "", "");
	insertSkill(0x03DF530E, 0x66D173C9, eSkill::空位2, "", "", "");
//	insertSkill(0x1FFC5C36, 0x6344D17A, eSkill::诅咒之伤, eSkillUse::BattleOther, eBuff::None, 40, 0, "诅咒之伤", "单体减少敌方20%气血", "75");
//	insertSkill(0x03DF530E, 0x66D173C9, eSkill::诅咒之亡, eSkillUse::BattleOther, eBuff::None, 40, 0, "诅咒之亡", "单体减少敌方20%魔法", "40");
	insertSkill(0x97A6B22C, 0x17D8A907, eSkill::笑里藏刀, "笑里藏刀", "愤怒-70", "40");
	insertSkill(0x172AE1E0, 0x480A8A7D, eSkill::绝幻魔音, "绝幻魔音", "全体愤怒-20", "60");
	insertSkill(0xB7458413, 0x41A28BC6, eSkill::野兽之力, "野兽之力", "攻击+10%", "40");
	insertSkill(0xF77F8F63, 0x6C8D9D7E, eSkill::魔兽之印, "魔兽之印", "全体攻击+5%", "70");
	insertSkill(0xA7BB3439, 0x85849B5B, eSkill::光辉之甲, "光辉之甲", "防御+10%", "40");
	insertSkill(0xA767CFAB, 0x185C7768, eSkill::圣灵之甲, "圣灵之甲", "全体防御+5%", "70");
	insertSkill(0xA85146A6, 0x9715FA32, eSkill::流云诀, "流云诀", "速度+10%", "40");
	insertSkill(0x96370902, 0x6812F03B, eSkill::啸风诀, "啸风诀", "全体速度+5%", "70");
	insertSkill(0x3CA34035, 0xCA17D132, eSkill::太极护法, "太极护法", "受到的法术伤害减半,持续3回合", "90");
	insertSkill(0xCC019475, 0x61F085F4, eSkill::罗汉金钟, "罗汉金钟", "全体受到的法术伤害减半,持续3回合", "150");
	insertSkill(0x14FF0C1F, 0xA0830D94, eSkill::修罗咒, "修罗咒", "	反弹50%的伤害,持续3回合", "120");
	insertSkill(0x76F6DD9E, 0x68F4FE2B, eSkill::天衣无缝, "天衣无缝", "法术躲避率+50%,持续5回合", "80");
	insertSkill(0x1A4D1A72, 0xDA23CB44, eSkill::放下屠刀, "放下屠刀", "攻击-10%", "30");
	insertSkill(0x52CE6E52, 0xF7A055FD, eSkill::河东狮吼, "河东狮吼", "	全体攻击-5%", "70");
	insertSkill(0x2CD374B0, 0x5460F163, eSkill::破甲术, "破甲术", "防御-10%", "35");
	insertSkill(0x2CD374B0, 0x5460F163, eSkill::碎甲术, "碎甲术", "全体防御-5%", "80");
	insertSkill(0x264D9AC8, 0x8FF3DB32, eSkill::凝滞术, "凝滞术", "速度-10%", "35");
	insertSkill(0x5E68270E, 0x79619181, eSkill::停陷术, "停陷术", "全体速度-5%", "80");
	insertSkill(0x1373420F, 0xFD99EDE1, eSkill::破血狂攻, "破血狂攻", "连击", "80");
	insertSkill(0x7F545B30, 0xF68EB551, eSkill::弱点击破, "弱点击破", "穿刺", "50");
	insertSkill(0x896AAEED, 0x59DBD730, eSkill::空位3, "", "", "");
	insertSkill(0x8A479938, 0xB1392BC1, eSkill::空位4, "", "", "");
	insertSkill(0x51522BBB, 0x77A7C11E, eSkill::星杯圣域, "", "", "");
	insertSkill(0xF572DAB6, 0x356E1001, eSkill::命疗术EX, "", "", "");
	insertSkill(0xCC73C4CE, 0x1D81410E, eSkill::破碎无双, "破碎无双", "攻击并减少对方魔法", "80");
	insertSkill(0x4607A98E, 0xCD0B7124, eSkill::空位5, "", "", "");
	insertSkill(0xD339140A, 0x76FDA5AC, eSkill::破血狂攻2, "", "", "");
	insertSkill(0xA3D648B0, 0xFB726757, eSkill::弱点击破EX, "", "", "");
	insertSkill(0x230AF78C, 0x044670C7, eSkill::破血狂攻EX, "", "", "");
	insertSkill(0x17C3EF40, 0x613B61A6, eSkill::空位6, "", "", "");
	insertSkill(0x9908B56E, 0x7635E819, eSkill::大地之墙, "", "", "");
	insertSkill(0xCB65301D, 0xC352DA37, eSkill::心如明镜, "心如明镜", "物理和法术防御+50%,去除一切异常,持续4回合", "100");
	insertSkill(0x8521B2B4, 0x5F4E6740, eSkill::慈航普渡, "慈航普渡", "都别躺着了起来嗨", "150");
	insertSkill(0x066D7389, 0x51A0423C, eSkill::迅疾如风, "迅疾如风", "明明就是移形换影", "");

	// 门派技能(descCost空/ignore的不要)
	insertSkill(0xB0E3E18B, 0x0900C9A1, eSkill::横扫千军, "横扫千军", "4连击,休息1回合", "HpMax_5");
	insertSkill(0x424D9459, 0xE3094CF3, eSkill::后发制人, "后发制人", "蓄力一回合,+攻击+速度", "HpMax_5");
	insertSkill(0xFE16E718, 0x6C23A98E, eSkill::兵器谱, "兵器谱", "鉴定武器和衣服", "");
	insertSkill(0x66668C4F, 0x00CDE78F, eSkill::千里神行, "千里神行", "传送师门", "Mp_10");
	insertSkill(0x4F10E7C8, 0x63BE01CD, eSkill::杀气诀, "杀气诀", "+命中", "Mp_40");
	insertSkill(0x44B0147F, 0x0262C795, eSkill::斩龙诀, "斩龙诀", "克制龙宫弟子的必杀技", "");
	insertSkill(0x3225863C, 0x08BFC856, eSkill::反间之计, "反间之计", "令对手自相残杀", "Mp_30");
	insertSkill(0x24E57349, 0x5E31990A, eSkill::破釜沉舟, "破釜沉舟", "4分击,休息1回合", "HpMax_5");
	insertSkill(0x8368E31C, 0xBBCA9C0B, eSkill::安神诀, "安神诀", "+灵力", "Mp_30");
	insertSkill(0x3195E34C, 0x8B8E4258, eSkill::嗜血, "嗜血", "", "");

	insertSkill(0x05089B1C, 0x481EAFC6, eSkill::三星灭魔, "三星灭魔", "克制魔王寨弟子的必杀技", "");
	insertSkill(0x4286DDD0, 0xB8F8B6A5, eSkill::五雷咒, "五雷咒", "", "ignore_Mp_30");
	insertSkill(0x6B357065, 0x6A96181C, eSkill::飞行符, "飞行符", "", "");
	insertSkill(0x78C38F19, 0x4B9630F1, eSkill::兵解符, "兵解符", "脱离战斗", "ignore_HpMax_90");
	insertSkill(0x063EAFDB, 0xD209F99A, eSkill::催眠符, "催眠符", "不受打击难以清醒", "Mp_45");
	insertSkill(0xCB1E4D52, 0x59CD3D34, eSkill::失心符, "失心符", "封印法术并降低防御", "Mp_60");
	insertSkill(0x795E9104, 0x5C948CFF, eSkill::落魄符, "落魄符", "封魔+降20%命中", "");
	insertSkill(0xA1343135, 0x5D26E373, eSkill::失忆符, "失忆符", "封印特技", "Mp_60");
	insertSkill(0x8F4B3740, 0x3CDC2403, eSkill::追魂符, "追魂符", "封物理+降防", "ignore_Mp_60");
	insertSkill(0xC7FE7637, 0x00007856, eSkill::离魂符, "离魂符", "封魔+降躲避", "ignore_Mp_60");
	insertSkill(0x8FF10842, 0x78F1ED7F, eSkill::失魂符, "失魂符", "封魔+降防", "ignore_Mp_60");
	insertSkill(0x975DA9B5, 0x0A2B0270, eSkill::定身符, "定身符", "封印物理并降低防御", "Mp_60");
	insertSkill(0xB83BDC9B, 0x936F1197, eSkill::归元咒, "归元咒", "恢复气血", "Mp_20");
	insertSkill(0xB76A6542, 0xE6A885C3, eSkill::凝神术, "凝神术", "恢复魔法", "HpFix_20");
	insertSkill(0x784D72FE, 0xC53E6E37, eSkill::乾天罡气, "乾天罡气", "", "");
	insertSkill(0x19FE3B00, 0x0441F7EC, eSkill::乙木仙遁, "乙木仙遁", "传送师门", "Mp_10");
	insertSkill(0x559B2E13, 0x7D1F9844, eSkill::分身术, "分身术", "+法术躲避", "Mp_80");
	insertSkill(0xBD46AEDE, 0x18E364D5, eSkill::碎甲符, "碎甲符", "降低防御灵力", "Mp_100");
	insertSkill(0xC05584C4, 0xCF367379, eSkill::落雷符, "落雷符", "落雷符", "Mps_30");
	insertSkill(0xB8C8B3C0, 0x488BFA97, eSkill::神兵护法, "神兵护法", "", "");

	insertSkill(0xE98C1B53, 0xD530DA11, eSkill::紫气东来, "紫气东来", "", "");
	insertSkill(0x8D8B8C6C, 0x6EAE4C8A, eSkill::唧唧歪歪, "唧唧歪歪", "子曾经曰过", "Mps_20");
	insertSkill(0xBAAB7B8B, 0x5458D4F3, eSkill::达摩护体, "达摩护体", "", "");
	insertSkill(0xDC94C31C, 0x1C9BA3BB, eSkill::金刚护法, "金刚护法", "+伤害", "Mp_40");
	insertSkill(0xAC27CC91, 0x7E6CCFA6, eSkill::韦陀护法, "韦陀护法", "+命中", "Mp_40");
	insertSkill(0xCDD65C55, 0x52161202, eSkill::金刚护体, "金刚护体", "+防御", "Mp_40");
	insertSkill(0x43C01A12, 0xA8430D24, eSkill::一苇渡江, "一苇渡江", "+速度", "Mp_40");
	insertSkill(0x0FDF6352, 0x5C1B5CF9, eSkill::我佛慈悲, "我佛慈悲", "七级浮屠", "Mp_150");
	insertSkill(0xFFA56FD1, 0x181BFB03, eSkill::推拿, "推拿", "回血+疗伤", "ignore_Mp_50");
	insertSkill(0xAACB2367, 0x9101EBA0, eSkill::活血, "活血", "回血+疗伤+解毒", "Mp_70");
	insertSkill(0x84BDDC3E, 0x39E390DD, eSkill::推气过宫, "推气过宫", "群体回血", "Mp_100");
	insertSkill(0xAF367280, 0x18CD0456, eSkill::妙手回春, "妙手回春", "群体疗伤", "Mp_80");
	insertSkill(0xF7CDB7B9, 0x79D35DAF, eSkill::救死扶伤, "救死扶伤", "群体+疗伤+回血", "Mp_100");
	insertSkill(0x2091C150, 0x753893D8, eSkill::解毒, "解毒", "", "ignore_Mp_40");
	insertSkill(0xCC08B2F3, 0xB29DFB11, eSkill::佛门普渡, "佛门普渡", "传送师门", "Mp_10");
	insertSkill(0x65C3D529, 0x43B4E620, eSkill::舍生取义, "舍生取义", "队友气血填满,但你的防御-5%,灵力-3%", "Mp_150");
	insertSkill(0xB8C91B23, 0x884BB7B5, eSkill::佛法无边, "佛法无边", "+法术连击率", "Mp_150");
	insertSkill(0xA95C700C, 0x0A9B60DA, eSkill::拈花妙指, "拈花妙指", "", "");

	insertSkill(0x68C68B02, 0x20A5F3D0, eSkill::红袖添香, "红袖添香", "", "");
	insertSkill(0x38C7C348, 0xE5042C42, eSkill::楚楚可怜, "楚楚可怜", "隐身", "Mp_100");
	insertSkill(0x662EFA99, 0x875525A2, eSkill::满天花雨, "满天花雨", "普通攻击+中毒", "Mp_50");
	insertSkill(0x935E99ED, 0x712996D6, eSkill::情天恨海, "情天恨海", "", "");
	insertSkill(0xFCF44944, 0xD11D8F4A, eSkill::莲步轻舞, "莲步轻舞", "封印法术", "");
	insertSkill(0x4C8034D4, 0x71FC82F8, eSkill::如花解语, "如花解语", "封印物理", "");
	insertSkill(0xD2123BE8, 0xA2DE2140, eSkill::似玉生香, "似玉生香", "封印物理和法术", "Mp_50");
	insertSkill(0x53B01707, 0x2DC6C0E7, eSkill::娉婷嬝娜, "娉婷嬝娜", "", "");
	insertSkill(0x15E168DD, 0x01FF0F6F, eSkill::轻如鸿毛, "轻如鸿毛", "", "");
	insertSkill(0x37F7C199, 0x02B4928E, eSkill::百毒不侵, "百毒不侵", "", "");
	insertSkill(0x918FB1D3, 0x3E505980, eSkill::移形换影, "移形换影", "传送师门", "Mp_10");
	insertSkill(0x1F215E91, 0xC2B106E9, eSkill::一笑倾城, "一笑倾城", "群体封印法术", "Mps_60");
	insertSkill(0x74FF026F, 0xF2553F61, eSkill::飞花摘叶, "飞花摘叶", "", "");
	insertSkill(0x21883613, 0x92F67200, eSkill::雨落寒沙, "雨落寒沙", "群体暗器", "Mps_10");

	insertSkill(0xFA64E7B9, 0x81925D39, eSkill::天神护体, "天神护体", "+灵力", "Mp_20");
	insertSkill(0xDF877E23, 0xF19A5EFA, eSkill::天神护法, "天神护法", "真爱", "ignore_Mp_50");
	insertSkill(0xDC9BDA8C, 0xB3C8279C, eSkill::天诛地灭, "天诛地灭", "", "");
	insertSkill(0x91EC4841, 0x0BB38F40, eSkill::知己知彼, "知己知彼", "", "");
	insertSkill(0x74B29E7D, 0x9A155954, eSkill::宁心, "宁心", "解除自身的负面效果", "ignore_Mp_50");
	insertSkill(0x0EF91062, 0xA82E9413, eSkill::镇妖, "镇妖", "封印特技", "Mp_45");
	insertSkill(0xFFB5624B, 0xD7E76D2D, eSkill::错乱, "错乱", "封印法术", "Mp_60");
	insertSkill(0xFF5FCC5F, 0xBB32CB83, eSkill::百万神兵, "百万神兵", "封印物理", "Mp_60");
	insertSkill(0x360B497C, 0x72BB2C70, eSkill::腾云驾雾, "腾云驾雾", "传送师门", "Mp_10");
	insertSkill(0x391FBBEB, 0x12CFF6C1, eSkill::天雷斩, "天雷斩", "攻击并降低对方灵力,自己防御-1%每次", "Mps_30");
	insertSkill(0x6CD25687, 0xFC7CEE47, eSkill::五雷轰顶, "五雷轰顶", "气血-25%,魔法-25%,看运气", "Mp_50");
	insertSkill(0x6794F727, 0xF979C506, eSkill::金刚镯, "金刚镯", "", "");
	insertSkill(0x7B003972, 0x45909EE4, eSkill::雷霆万钧, "雷霆万钧", "", "Mps_35");
	insertSkill(0x21D77976, 0xCDA1A3A3, eSkill::浩然正气, "浩然正气", "", "");
	insertSkill(0x5DF74259, 0x2D863D2A, eSkill::掌心雷, "掌心雷", "", "");

	insertSkill(0x6BB78F2A, 0x984CF938, eSkill::解封, "解封", "", "");
	insertSkill(0xD4647700, 0x01590DDC, eSkill::清心, "清心", "解毒", "Mp_30");
	insertSkill(0xD9935972, 0x7CC5EF28, eSkill::龙腾, "龙腾", "单体法术", "Mp_50");
	insertSkill(0x3236D5E1, 0x0C054889, eSkill::龙卷雨击, "龙卷雨击", "群体法术", "Mps_20");
	insertSkill(0xE2C973B2, 0x5905DEC6, eSkill::逆鳞, "逆鳞", "+伤害", "Mp_20");
	insertSkill(0xC06DBC74, 0x055E6A6D, eSkill::乘风破浪, "乘风破浪", "", "");
	insertSkill(0x9F38CFD7, 0x238F9C1B, eSkill::水遁, "水遁", "传送师门", "Mp_10");
	insertSkill(0x7F6E6C02, 0x4E96B443, eSkill::龙吟, "龙吟", "全体固伤并减少魔法", "Mp_50");
	insertSkill(0x7EA52AB5, 0xD93D4F3D, eSkill::龙啸九天, "龙啸九天", "", "");
	insertSkill(0x6A643D2E, 0xAC322FAD, eSkill::龙附, "龙附", "", "");
	insertSkill(0x975B5587, 0x5D2392F9, eSkill::神龙摆尾, "神龙摆尾", "减少20%承受的物理伤害", "Mp_100");
	insertSkill(0x2598BAD0, 0x4B78F4EA, eSkill::二龙戏珠, "二龙戏珠", "双体法术", "Mp_70");

	insertSkill(0xCFF9CA32, 0xE8A1FA06, eSkill::日月乾坤, "日月乾坤", "封印物理法术特技", "Mp_35");
	insertSkill(0x6484CE2C, 0x8EBBB9ED, eSkill::炼气化神, "炼气化神", "持续恢复气血", "HpFix_30");
	insertSkill(0xA4558B86, 0x4126939F, eSkill::生命之泉, "生命之泉", "持续恢复魔法", "Mps_30");
	insertSkill(0x630B9900, 0x6347C97B, eSkill::太极生化, "太极生化", "", "");
	insertSkill(0x2714CD4D, 0x785A5F32, eSkill::斗转星移, "斗转星移", "传送师门", "Mp_10");
	insertSkill(0xBBCF26FE, 0xE34DD120, eSkill::三花聚顶, "三花聚顶", "恢复魔法", "HpFix_30");
	insertSkill(0x271F24E1, 0x4C8E9F62, eSkill::驱魔, "驱魔", "", "");
	insertSkill(0x2097EBF0, 0x4919A4E5, eSkill::驱尸, "驱尸", "解毒", "Mp_40");
	insertSkill(0xD9249EC5, 0xBA3CC9E9, eSkill::烟雨剑法, "烟雨剑法", "连击", "Mp_50");
	insertSkill(0xCA8F3E1A, 0xC2D517D6, eSkill::飘渺式, "飘渺式", "分击", "Mps_30");
	insertSkill(0x00000000, 0xFBC5D873, eSkill::天地同寿, "天地同寿", "为目标临时加上一个防御护罩,吸收全部法术伤害,降低目标50%防御效果,且所受物理伤害会加倍", "ignore_Mp_50");
	insertSkill(0xC464481B, 0x6779E3D4, eSkill::乾坤妙法, "乾坤妙法", "", "");
	insertSkill(0x951F8360, 0xFDC44BC0, eSkill::一气化三清, "一气化三清", "", "");

	insertSkill(0xCB1639D1, 0x290BF9E7, eSkill::普渡众生, "普渡众生", "持续恢复气血", "Mp_50");
	insertSkill(0x3908C648, 0x5DC3D631, eSkill::紧箍咒, "紧箍咒", "持续扣除气血和上限", "Mp_50");
	insertSkill(0x2F5AFA7D, 0xDFF28692, eSkill::杨柳甘露, "杨柳甘露", "强势复活", "Mp_150");
	insertSkill(0x34464142, 0x7B080559, eSkill::日光华, "日光华", "固定伤害", "Mp_50");
	insertSkill(0x6A4D383D, 0x9FB86B6A, eSkill::靛沧海, "靛沧海", "固定伤害", "Mp_50");
	insertSkill(0xE38F0541, 0xBFD75298, eSkill::巨岩破, "巨岩破", "固定伤害", "Mp_50");
	insertSkill(0x8C6D506B, 0x493EEC97, eSkill::苍茫树, "苍茫树", "固定伤害", "Mp_50");
	insertSkill(0x047A00A7, 0xF64BED47, eSkill::地裂火, "地裂火", "固定伤害", "Mp_50");
	insertSkill(0xE57C320E, 0x92CACF3B, eSkill::坐莲, "坐莲", "传送师门", "Mp_10");
	insertSkill(0xDEE056A8, 0x133CEEA4, eSkill::五行错位, "五行错位", "", "");
	insertSkill(0x728DE1CD, 0x890CE894, eSkill::灵动九天, "灵动九天", "群体加灵力", "Mp_100");
	insertSkill(0xD78FBB42, 0x6E44BE66, eSkill::颠倒五行, "颠倒五行", "+五行吸收", "Mp_80");
	insertSkill(0x87C2F0D2, 0xF17355F3, eSkill::莲华妙法, "莲华妙法", "", "");
	insertSkill(0xCBD97FD0, 0x477948A0, eSkill::自在心法, "自在心法", "结算普渡众生", "Mp_30");

	insertSkill(0xCD73E07C, 0xA7459134, eSkill::阎罗令, "阎罗令", "群体固定伤害并减少气血上限", "Mps_20"); //,夜晚攻击效果高于白天,对怪物伤害加倍
	insertSkill(0xDCABAFAD, 0x63A83981, eSkill::判官令, "判官令", "固定伤害并减少魔法", "Mp_20"); //,黑夜使用效果为标准的130%
	insertSkill(0x80305F4B, 0xF2D2EB2F, eSkill::勘察令, "勘察令", "鉴定项链,头盔,鞋,腰带", "");
	insertSkill(0x1CC4C18F, 0x26F78E1F, eSkill::寡欲令, "寡欲令", "解封", "ignore_Mp_50");
	insertSkill(0xA7592BE7, 0x75C1605A, eSkill::幽冥鬼眼, "幽冥鬼眼", "感知,抗封+10%", "Mps_20");
	insertSkill(0x167366B6, 0xD5CE79DD, eSkill::冤魂不散, "冤魂不散", "", "");
	insertSkill(0x8AC6F05B, 0x02ED1F1B, eSkill::尸腐毒, "尸腐毒", "下毒回血", "Mp_40");
	insertSkill(0xB759D696, 0x213794E1, eSkill::修罗隐身, "修罗隐身", "", "Mp_150");
	insertSkill(0x2C0D5A09, 0x7A2AE74E, eSkill::杳无音讯, "杳无音讯", "传送师门", "Mp_10");
	insertSkill(0x1CEE0599, 0xAB58943F, eSkill::还阳术, "还阳术", "复活+伤害", "Mp_150");
	insertSkill(0x70D5CD29, 0xD2D21A8B, eSkill::黄泉之息, "黄泉之息", "攻击并降低速度", "Mp_50"); //,夜间使用效果调整为白天的130%
	insertSkill(0xA21E0165, 0x5F0B6F6D, eSkill::魂飞魄散, "魂飞魄散", "驱散良性状态", "Mp_40");
	insertSkill(0xD3076E45, 0xE451BF95, eSkill::尸气漫天, "尸气漫天", "", "");
	insertSkill(0x2EC10ADD, 0x66F5816E, eSkill::锢魂术, "锢魂术", "死亡召唤", "Mp_50");

	insertSkill(0xE13663E9, 0x37E0D423, eSkill::魔王护持, "魔王护持", "", "");
	insertSkill(0x2C7FBCD6, 0x2A16BFD0, eSkill::飞砂走石, "飞砂走石", "群体法术", "Mps_30");
	insertSkill(0x114F1F2C, 0x25526F4E, eSkill::三昧真火, "三昧真火", "单体法术", "Mps_30");
	insertSkill(0x4062BFE4, 0xD1EC7AD9, eSkill::牛劲, "牛劲", "感知+法术伤害", "Mp_20");
	insertSkill(0xA7AC77E0, 0xF20648E8, eSkill::踏山裂石, "踏山裂石", "", "");
	insertSkill(0x35C31747, 0xE7D2A6F9, eSkill::无敌牛虱, "无敌牛虱", "大牛", "Mp_40");
	insertSkill(0xA5385E3B, 0x1F68ADCC, eSkill::无敌牛妖, "无敌牛妖", "牛妖", "Mp_40");
	insertSkill(0xB56E84D0, 0x3B5C1425, eSkill::魔王回首, "魔王回首", "+反击", "Mp_30");
	insertSkill(0x27D50D56, 0x93EA969B, eSkill::牛屎遁, "牛屎遁", "传送师门", "Mp_10");
	insertSkill(0xC02762DD, 0x902C43A8, eSkill::火甲术, "火甲术", "", "");
	insertSkill(0x69F9FFD0, 0xB5DC536F, eSkill::摇头摆尾, "摇头摆尾", "", "");

	insertSkill(0x067DDF53, 0xBD3FF07D, eSkill::象形, "象形", "封印行动,变身取消", "Mp_50");
	insertSkill(0x56070FE9, 0xBFE91154, eSkill::鹰击, "鹰击", "分击,休息1回合", "Mps_30");
	insertSkill(0x60FFC2C8, 0xDC90DF2F, eSkill::狮搏, "狮搏", "提升伤害进行攻击", "Mp_30");
	insertSkill(0x35532015, 0x04DA6E6F, eSkill::威慑, "威慑", "封印行动,对玩家无效", "Mp_20");
	insertSkill(0xDA9CD712, 0xFF4048E9, eSkill::变身, "变身", "用于 狮搏/鹰击/连环击/象形", "Mp_20");
	insertSkill(0x430D0B1B, 0x38AB6F30, eSkill::魔兽啸天, "魔兽啸天", "", "");
	insertSkill(0x05EFA897, 0xEDB77B1D, eSkill::定心术, "定心术", "+灵力", "Mp_40");
	insertSkill(0x28256D06, 0xD7187347, eSkill::连环击, "连环击", "疯狂连击,变身取消", "Mps_30");
	insertSkill(0xF800E231, 0xD1561312, eSkill::振翅千里, "振翅千里", "传送师门", "Mp_10");
	insertSkill(0xABF46236, 0x15AC16AF, eSkill::极度疯狂, "极度疯狂", "+反击", "Mp_30");
	insertSkill(0x2EEC86A4, 0xD92455F2, eSkill::魔息术, "魔息术", "", "");
	insertSkill(0x93A98451, 0xA1B84C64, eSkill::天魔解体, "天魔解体", "自身加气血上限", "ignore_Mp_50");
	insertSkill(0xE78A87A1, 0xE30F693F, eSkill::神力无穷, "神力无穷", "", "");

	insertSkill(0x2FD480B4, 0xC6AB6795, eSkill::勾魂, "勾魂", "花式吸血", "Mp_40");
	insertSkill(0x06294FA0, 0xA42F7249, eSkill::摄魄, "摄魄", "花式吸元", "Mp_35");
	insertSkill(0x5CACF37F, 0x01E94239, eSkill::魔音摄魂, "魔音摄魂", "剥夺气血和魔法的恢复权", "Mp_40");
	insertSkill(0x16C75EF8, 0x7C23B1B8, eSkill::盘丝舞, "盘丝舞", "", "");
	insertSkill(0xC2CD06E2, 0x0D916626, eSkill::夺命蛛丝, "夺命蛛丝", "", "");
	insertSkill(0x9A5880DC, 0xF50D8C5A, eSkill::含情脉脉, "含情脉脉", "封印物理和法术", "Mp_50");
	insertSkill(0x6974146E, 0x8EC63F2A, eSkill::盘丝阵, "盘丝阵", "+防御", "Mp_40");
	insertSkill(0xAB18B4B0, 0x086B8CFF, eSkill::复苏, "复苏", "自身解除封印和异常", "ignore_Mp_30");
	insertSkill(0x56DE11A1, 0x628E8D59, eSkill::天罗地网, "天罗地网", "固定伤害+封印物理", "Mps_30");
	insertSkill(0x6BB35F00, 0x4C7CC844, eSkill::天蚕丝, "天蚕丝", "传送师门", "Mp_10");
	insertSkill(0x1DEE311E, 0x0286F483, eSkill::姐妹同心, "姐妹同心", "", "ignore_Mp_60");
	insertSkill(0xE63FB407, 0xB5243050, eSkill::瘴气, "瘴气", "", "");
	insertSkill(0x241E44A3, 0x43A1A964, eSkill::幻镜术, "幻镜术", "+法术反弹", "Mp_50");

	insertSkill(0x1C603FAE, 0xF4DCF38F, eSkill::裂石, "裂石", "临时提升必杀几率对单个敌人进行物理攻击,增加1点战意值", "Mp_50");
	insertSkill(0x5C95AF41, 0x5AA54949, eSkill::断岳势, "断岳势", "临时提升必杀几率对单个敌人进行2次物理攻击", "Mp_50");
	insertSkill(0x4C99C220, 0x9ADAEA80, eSkill::天崩地裂, "天崩地裂", "临时提升必杀几率对单个敌人进行3次物理攻击", "Mp_50");
	insertSkill(0x1A289BEA, 0xCE61D91C, eSkill::浪涌, "浪涌", "对多个敌人进行物理攻击,增加1点战意值", "Mps_20");
	insertSkill(0xBE11779C, 0xB91C6953, eSkill::惊涛怒, "惊涛怒", "提升一定伤害力对多个敌人进行物理攻击", "Mps_20");
	insertSkill(0x11879028, 0x26419C11, eSkill::翻江搅海, "翻江搅海", "提升一定伤害力对多个敌人进行物理攻击", "Mps_20");
	insertSkill(0x956BA0A2, 0x569D01F7, eSkill::腾雷, "腾雷", "", "");
	insertSkill(0x00000000, 0x4AB6831C, eSkill::指地成钢, "指地成钢", "", "");
	insertSkill(0x38C47290, 0xD96F2331, eSkill::不动如山, "不动如山", "使用后减少自身受到的法术伤害与物理伤害", "Mp_150");
	insertSkill(0x5F8D7935, 0x136442C0, eSkill::碎星诀, "碎星诀", "提升物理伤害结果", "Mp_30");
	insertSkill(0xF808DCC6, 0x9E1580AA, eSkill::镇魂诀, "镇魂诀", "提升物理必杀几率", "Hp_5");
	insertSkill(0x00E0D005, 0xB7E814EE, eSkill::穿云破空, "穿云破空", "", "");
	insertSkill(0x76FBBEEC, 0xAFDB81A4, eSkill::无穷妙道, "无穷妙道", "", "");
	insertSkill(0xFEF5D678, 0xE6A2AA59, eSkill::纵地金光, "纵地金光", "传送师门", "Mp_10");

	insertSkill(0x85DC4B33, 0x173015AE, eSkill::移魂化骨, "移魂化骨", "消耗自身气血使目标获得吸血效果", "HpMax_10");
	insertSkill(0x076EA85A, 0x62221B56, eSkill::夺魄令, "夺魄令", "令目标一定回合内无法使用法术", "Mp_30");
	insertSkill(0x28D6DCD8, 0xC0504605, eSkill::煞气诀, "煞气诀", "", "");
	insertSkill(0x71307D22, 0xC232A281, eSkill::惊魂掌, "惊魂掌", "", "");
	insertSkill(0xD6A5B20C, 0x1CC2B0B0, eSkill::摧心术, "摧心术", "使敌方2个目标速度降低", "Mp_100");
	insertSkill(0xA9AF9E72, 0x2A3E7A3C, eSkill::夺命咒, "夺命咒", "使用固定伤害攻击对方多人", "Mps_20");
	insertSkill(0x59D84304, 0x54DB6CDE, eSkill::明光宝烛, "明光宝烛", "使己方多人一定回合内承受的物理伤害结果减少", "Mp_100");
	insertSkill(0xFE884980, 0x1BE322B2, eSkill::金身舍利, "金身舍利", "使己方多人一定回合内承受的法术伤害结果减少", "Mp_100");
	insertSkill(0x86AE37EA, 0x40FB7647, eSkill::地涌金莲, "地涌金莲", "恢复自己或者队友的气血与气血上限", "HpMax_3");
	insertSkill(0x00000000, 0x036B4345, eSkill::万木凋枯, "万木凋枯", "", "");
	insertSkill(0x2EF58426, 0xABD57D92, eSkill::元阳护体, "元阳护体", "", "");
	insertSkill(0x34D061C7, 0x1D14968A, eSkill::遁地术, "遁地术", "平时状态下使用，可以瞬间回到自己的门派", "Mp_10");
	insertSkill(0xDB2E1256, 0xDE58924A, eSkill::由己渡人, "由己渡人", "复活", "HpMax_10");

	insertSkill(0x0B8CF3A1, 0x2E734F9D, eSkill::落叶萧萧, "落叶萧萧", "使用法术攻击敌方多个目标", "Mps_30");
	insertSkill(0x6A647570, 0xDD2AB898, eSkill::荆棘舞, "荆棘舞", "使用法术攻击敌方单体目标", "Mp_30");
	insertSkill(0x71C197B0, 0x3FE17E30, eSkill::尘土刃, "尘土刃", "使用法术攻击敌方单体目标,并使目标损失一定HP上限", "Mp_30");
	insertSkill(0x3B12CD18, 0xEDF81F56, eSkill::冰川怒, "冰川怒", "使用法术攻击敌方单体目标,并使目标损失一定愤怒", "Mp_30");
	insertSkill(0x0DA2D8DF, 0x1EE55D3C, eSkill::雾杀, "雾杀", "使用法术攻击敌方单人目标，对敌人造成持续毒性伤害", "Mp_50");
	insertSkill(0x7D52C301, 0x126B932F, eSkill::血雨, "血雨", "消耗自身气血，对敌人单体目标造成大量伤害。 使用后，自己下回合无法使用法术", "HpMax_20");
	insertSkill(0x007E7633, 0xFF613346, eSkill::星月之惠, "星月之惠", "回复自身气血", "Mp_50");
	insertSkill(0xC5D73984, 0xA215E746, eSkill::炎护, "炎护", "抵御50%的气血伤害，每抵御1点伤害消耗1点MP", "Mp_30");
	insertSkill(0x51763883, 0x64FEA3A4, eSkill::叶隐, "叶隐", "平时状态下使用，可以瞬间回到自己的门派", "Mp_10");
	insertSkill(0xF2E06AF8, 0x977F5625, eSkill::神木呓语, "神木呓语", "", "");
	insertSkill(0xF83E2272, 0x058EE366, eSkill::密润, "密润", "增加己方多人的法术伤害力", "Mps_25");
	insertSkill(0xAC574467, 0x00000000, eSkill::蝼蚁蚀天, "蝼蚁蚀天", "", "");

}


void txtIcon::initCard()
{
	//大图 0xF1295C0D
	initIdx();
	initTable(eIcon::卡片k);
	insertCard(0x4A028BEE, 0x98E3377F, eMod::e巨蛙);
	insertCard(0x4A028BEE, 0x3C7B89E8, eMod::e大海龟);
	insertCard(0x4A028BEE, 0x7003F174, eMod::e护卫);
	insertCard(0x4A028BEE, 0x4ED5C9C4, eMod::e树怪);
	insertCard(0x4A028BEE, 0x6BE81A68, eMod::e赌徒);
	insertCard(0x4A028BEE, 0xD5C2566E, eMod::e强盗);
	insertCard(0x4A028BEE, 0x3BD0B554, eMod::e海毛虫);
	insertCard(0x4A028BEE, 0x2481DFCC, eMod::e大蝙蝠);
	insertCard(0x4A028BEE, 0x5F7346A8, eMod::e山贼);
	insertCard(0x4A028BEE, 0xEF3A830D, eMod::e野猪);
	insertCard(0xBB35E1EE, 0xD0BE29D3, eMod::e骷髅怪);
	insertCard(0xBB35E1EE, 0x8F19EF2A, eMod::e羊头怪);
	insertCard(0xBB35E1EE, 0x8A53158C, eMod::e蛤蟆精);
	insertCard(0xBB35E1EE, 0x463F3E9B, eMod::e老虎);
	insertCard(0xBB35E1EE, 0xD4D2660A, eMod::e黑熊);
	insertCard(0xBB35E1EE, 0xD294444C, eMod::e花妖);
	insertCard(0xE7FC64D2, 0x3AF799AA, eMod::e牛妖);
	insertCard(0xE7FC64D2, 0xE05E7656, eMod::e小龙女);
	insertCard(0xE7FC64D2, 0xB90EC617, eMod::e野鬼);
	insertCard(0xE7FC64D2, 0x92B59426, eMod::e狼);
	insertCard(0xE7FC64D2, 0xE89179D1, eMod::e虾兵);
	insertCard(0xE7FC64D2, 0x65DBE48A, eMod::e蟹将);
	insertCard(0xA00740F6, 0x67E0006E, eMod::e龟丞相);
	insertCard(0xA00740F6, 0xA1B8ACD0, eMod::e兔子怪);
	insertCard(0xA00740F6, 0xD2C2093D, eMod::e蜘蛛精);
	insertCard(0xA00740F6, 0x35BDCFC8, eMod::e黑熊精);
	insertCard(0xA00740F6, 0xC7B126C6, eMod::e僵尸);
	insertCard(0xA00740F6, 0x06971D21, eMod::e牛头);
	insertCard(0xA00740F6, 0xCA322977, eMod::e马面);
	insertCard(0x21838782, 0x4E646343, eMod::e雷鸟人);
	insertCard(0x21838782, 0x976975FB, eMod::e蝴蝶仙子);
	insertCard(0x21838782, 0x7728C3B2, eMod::e古代瑞兽);
	insertCard(0x21838782, 0x7092E7F5, eMod::e白熊);
	insertCard(0x21838782, 0x95FDC90D, eMod::e黑山老妖);
	insertCard(0xF1C84EB5, 0x9AB7515F, eMod::e天兵);
	insertCard(0xF1C84EB5, 0x7E86C2A9, eMod::e天将);
	insertCard(0xF1C84EB5, 0xB5FE5920, eMod::e地狱战神);
	insertCard(0xF1C84EB5, 0xDF2F3035, eMod::e风伯);
	insertCard(0xEFA4BA2C, 0x2A4159F7, eMod::e凤凰);
	insertCard(0xEFA4BA2C, 0xD4442C3A, eMod::e蛟龙);
	insertCard(0xEFA4BA2C, 0xF53D7AE7, eMod::e雨师);
	insertCard(0x00000000, 0x411A18C7, eMod::e如意仙子);
	insertCard(0x00000000, 0xBAFBFAA8, eMod::e芙蓉仙子);
	insertCard(0x00000000, 0xFD35D4E3, eMod::e巡游天神);
	insertCard(0x00000000, 0xD226E204, eMod::e星灵仙子);
	insertCard(0x00000000, 0x62875401, eMod::e幽灵);
	insertCard(0x00000000, 0x023AA63E, eMod::e鬼将);
	insertCard(0x00000000, 0x9D5FA3EC, eMod::e吸血鬼);
	insertCard(0x00000000, 0x7E99A5F4, eMod::e净瓶女娲);
	insertCard(0x00000000, 0x4ED64302, eMod::e律法女娲);
	insertCard(0x00000000, 0x5726FB84, eMod::e灵符女娲);
	insertCard(0x00000000, 0x64287AE7, eMod::e大力金刚);
	insertCard(0x00000000, 0xA88F486E, eMod::e雾中仙);
	insertCard(0x00000000, 0xACEF8DB7, eMod::e灵鹤);
	insertCard(0x00000000, 0xAB1EFFB3, eMod::e夜罗刹);
	insertCard(0x00000000, 0xB9917494, eMod::e炎魔神);
	insertCard(0x00000000, 0x8DC23CAE, eMod::e噬天虎);
	insertCard(0x00000000, 0xF1127EEA, eMod::e野猪精);
	insertCard(0x00000000, 0xDC338F6E, eMod::e鼠先锋);
	insertCard(0xEFA4BA2C, 0xAA8E51A5, eMod::e百足将军);
	insertCard(0x00000000, 0xC6F3C665, eMod::e踏云兽);
	insertCard(0x00000000, 0x2D0D5755, eMod::e红萼仙子);
	insertCard(0x00000000, 0x964E7FB8, eMod::e龙龟);
	insertCard(0x00000000, 0x60AC19B3, eMod::e阴阳伞);
	insertCard(0x00000000, 0x9655B4E8, eMod::e机关兽);
	insertCard(0x00000000, 0x8423434C, eMod::e机关鸟);
	insertCard(0x00000000, 0xEA888609, eMod::e机关人);
	insertCard(0x00000000, 0xD123A916, eMod::e连弩车);
	insertCard(0x00000000, 0xBE748368, eMod::e巴蛇);
	insertCard(0x00000000, 0x4BAA9CBE, eMod::e蚌精);
	insertCard(0x00000000, 0x0349DFA6, eMod::e鲛人);
	insertCard(0x00000000, 0x22B8518F, eMod::e碧水夜叉);
	insertCard(0x00000000, 0xEABE811E, eMod::e锦毛貂精);
	insertCard(0x00000000, 0x65D26225, eMod::e千年蛇魅);
	insertCard(0xEFA4BA2C, 0x696AF38B, eMod::e犀牛将军);
	insertCard(0xEFA4BA2C, 0xCABF6445, eMod::e犀牛);
	insertCard(0x00000000, 0xEA888609, eMod::e机关车);
	insertCard(0x00000000, 0xEA888609, eMod::e机关人);
	insertCard(0x00000000, 0x48E257D4, eMod::e葫芦宝贝);
	insertCard(0x00000000, 0x4C82A29E, eMod::e猫灵);
	insertCard(0x00000000, 0x9ED7CAA8, eMod::e猫灵人);
	insertCard(0x00000000, 0xD20879BD, eMod::e狂豹);
	insertCard(0x00000000, 0x5579CC03, eMod::e狂豹人);
	insertCard(0x00000000, 0x07B74E81, eMod::e蝎子精);
	insertCard(0x00000000, 0xA416C496, eMod::e混沌兽);
	insertCard(0x00000000, 0x00000000, eMod::e超级人参娃娃);
	insertCard(0x00000000, 0xB73FB904, eMod::e画魂);
	insertCard(0x00000000, 0xBE6EDEDE, eMod::e长眉灵猴);
	insertCard(0x00000000, 0x99FACF23, eMod::e巨力神猿);
	insertCard(0x00000000, 0x4D34C63C, eMod::e修罗傀儡鬼);
	insertCard(0x00000000, 0x5BC38FA5, eMod::e藤蔓妖花);
	insertCard(0x00000000, 0x904F2844, eMod::e蜃气妖);
	insertCard(0x00000000, 0x5E499D7E, eMod::e修罗傀儡妖);
	insertCard(0x00000000, 0xB1B68D86, eMod::e金身罗汉);
	insertCard(0x00000000, 0xEA0AD25A, eMod::e曼珠沙华);
	insertCard(0x00000000, 0x0BD6B8AC, eMod::e超级泡泡);
	insertCard(0x00000000, 0xC1D91B08, eMod::e超级大熊猫);
	insertCard(0x00000000, 0x00000000, eMod::e超级金猴);
	insertCard(0xD5D3D1A7, 0x00000000, eMod::e超级大象);
	insertCard(0x00000000, 0x00000000, eMod::e超级白泽);
	insertCard(0x00000000, 0x00000000, eMod::e超级灵鹿);
	insertCard(0x00000000, 0x00000000, eMod::e超级赤焰兽);
	insertCard(0x00000000, 0x00000000, eMod::e超级大鹏);
	insertCard(0x404532E8, 0x00000000, eMod::e善财童子);
	insertCard(0x00000000, 0x00000000, eMod::e超级筋斗云);
	insertCard(0x00000000, 0x00000000, eMod::e超级神牛);
	insertCard(0x00000000, 0x00000000, eMod::e超级神虎);
	insertCard(0x00000000, 0x00000000, eMod::e超级海豚);
	insertCard(0x00000000, 0x00000000, eMod::e超级神兔);
	insertCard(0x00000000, 0x00000000, eMod::e小毛头);
	insertCard(0x00000000, 0x00000000, eMod::e小丫丫);
	insertCard(0x00000000, 0x00000000, eMod::e小仙灵);
	insertCard(0x00000000, 0x00000000, eMod::e小仙女);
	insertCard(0x00000000, 0x00000000, eMod::e小精灵);
	insertCard(0x00000000, 0x00000000, eMod::e小魔头);
	insertCard(0x00000000, 0x00000000, eMod::e孙悟空);
	insertCard(0x00000000, 0x00000000, eMod::e沙和尚);
	insertCard(0x00000000, 0x00000000, eMod::e蚩尤);
	insertCard(0x00000000, 0x00000000, eMod::e猪八戒);
	insertCard(0x00000000, 0xDC14E699, eMod::e狐狸精);
	insertCard(0x00000000, 0x00000000, eMod::e黄眉怪);
	insertCard(0x00000000, 0x7F316E08, eMod::e泡泡);
	insertCard(0x00000000, 0x00000000, eMod::e貔貅);
	insertCard(0x00000000, 0x00000000, eMod::e周杰伦);
	insertCard(0x00000000, 0x00000000, eMod::e超级神龙);
	insertCard(0x4A028BEE, 0xABB68989, eMod::e章鱼);
	insertCard(0x4A028BEE, 0xA60EB0D9, eMod::e狸);
	insertCard(0x4A028BEE, 0xE709CDAD, eMod::e海星);
	insertCard(0x00000000, 0x00000000, eMod::e火星人);
	insertCard(0x00000000, 0x00000000, eMod::e转轮王);
	insertCard(0x00000000, 0x00000000, eMod::e九头精怪);
	insertCard(0x66E05E50, 0xFC2930D6, eMod::e腾蛇);
	insertCard(0x00000000, 0x00000000, eMod::e东海龙王);
	insertCard(0x00000000, 0x00000000, eMod::e孙婆婆);
	insertCard(0x00000000, 0x00000000, eMod::e牛魔王);
	insertCard(0x00000000, 0x00000000, eMod::e镇元大仙);
	insertCard(0x00000000, 0x00000000, eMod::e菩提祖师);
	insertCard(0x00000000, 0x00000000, eMod::e白晶晶);
	insertCard(0x00000000, 0xD576EDF9, eMod::e幽萤娃娃);
	insertCard(0x00000000, 0x00000000, eMod::e李靖);
	insertCard(0x00000000, 0x00000000, eMod::e程咬金);
	insertCard(0x00000000, 0x00000000, eMod::e地藏王);
	insertCard(0x00000000, 0x00000000, eMod::e观音姐姐);
	insertCard(0x00000000, 0x00000000, eMod::e空度禅师);
	insertCard(0x00000000, 0x00000000, eMod::e大大王);
	insertCard(0x00000000, 0x00000000, eMod::e啸天犬);
	insertCard(0x00000000, 0x00000000, eMod::e地涌夫人);
	insertCard(0x00000000, 0x00000000, eMod::e二郎神);
	insertCard(0x00000000, 0x00000000, eMod::e占卜师);
	insertCard(0x00000000, 0x00000000, eMod::e巫奎虎);
	insertCard(0x00000000, 0x00000000, eMod::e超级玉兔);
	insertCard(0x00000000, 0x00000000, eMod::e超级孔雀);
	insertCard(0x00000000, 0x00000000, eMod::e超级灵狐);
	insertCard(0x00000000, 0x00000000, eMod::e超级神蛇);
	insertCard(0x00000000, 0x00000000, eMod::e超级神马);
	insertCard(0x00000000, 0x00000000, eMod::e超级青鸾);
	insertCard(0x00000000, 0x00000000, eMod::e超级麒麟);
	insertCard(0x00000000, 0x00000000, eMod::e九色鹿);
	insertCard(0x00000000, 0xE13AF8E0, eMod::e持国巡守);
	insertCard(0x00000000, 0x00000000, eMod::e超级神羊);
	insertCard(0x00000000, 0x00000000, eMod::e超级六耳猕猴);
	insertCard(0x00000000, 0x29A568DE, eMod::e毗舍童子);
	insertCard(0x00000000, 0x021526EC, eMod::e真陀护法);
	insertCard(0x2767C40B, 0x0A545E77, eMod::e镜妖);
	insertCard(0x62D9A3B8, 0xA22EBC2E, eMod::e泪妖);
	insertCard(0xE8A3BD55, 0x3C3F4DB7, eMod::e琴仙);
	insertCard(0x7A0AAFEB, 0xA8259D75, eMod::e金铙僧);
	insertCard(0x5C91F843, 0x275209D3, eMod::e灵灯侍者);
	insertCard(0x81640035, 0xCCD35C11, eMod::e增长巡守);
	insertCard(0x59E4179D, 0xC020441E, eMod::e般若天女);
	insertCard(0x6328756E, 0xA2371213, eMod::e雪人);
	insertCard(0x00000000, 0x00000000, eMod::e小白泽);
	insertCard(0xD5D3D1A7, 0x00000000, eMod::e小象);
	insertCard(0x00000000, 0x7F316E08, eMod::e小泡泡);
	insertCard(0x00000000, 0x00000000, eMod::e超级神猴);
	insertCard(0x00000000, 0x00000000, eMod::e超级神鸡);
	insertCard(0x00000000, 0x00000000, eMod::e超级土地公公);
	insertCard(0x9F1FA73B, 0x820D7720, eMod::e龙马);
	insertCard(0x00000000, 0x00000000, eMod::e骚浪剑);
	insertCard(0x00000000, 0x00000000, eMod::e无痕);
	insertCard(0x00000000, 0x00000000, eMod::e慧海);
	insertCard(0x00000000, 0x00000000, eMod::e镖头);
}



void txtIcon::init()
{
	initWeapon();
	initEquip();
	initMedicineCook();
	
	initIdx();
	initTable(eIcon::法宝f);
	////////////////////////////////////////////////////////////////////////// 加载顺序不要改 不然对不上eFaBao枚举
// 	insert(0x1715E7DE, 0x3AE1FD6A, 0, "曼陀罗", "毒伤害+5%" );
// 	insert(0x6B5B81EF, 0x5723DCC0, 0, "干将莫邪", "物理伤害结果+50" );
// 	insert(0x14846B1B, 0x695614DB, 0, "罗汉珠", "魔法消耗-10%" );
// 	insert(0x743685D8, 0x62AEC7E3, 0, "赤焰", "魔法+10/回合" );
// 	insert(0xEAA6AD2E, 0x450BE7E8, 0, "惊魂铃", "驱鬼+10%" );
// 	insert(0x7729A9E5, 0x4110011C, 0, "混元伞", "20%反弹5%法术伤害" );
// 	insert(0x05896BCC, 0x32F92F8A, 10000, "无魂傀儡", "");
// 	insert(0xF5601CC2, 0x1824AF14, 0, "乾坤玄火塔", "愤怒+2/回合" );
// 	insert(0xABA607A9, 0x1F73D09F, 0, "普渡", "五行吸收+5%" );
// 	insert(0x58C421DC, 0x8C891F83, 10000, "缩地尺", "");
// 	insert(0x95DC9FE9, 0x10ADFCD8, 10000, "月光宝盒", "");
// 	insert(0x63E46E78, 0xA5CCFED9, 10000, "影蛊", "" );
	insert(0x5202B419, 0xB209FF9F, 0, "周杰伦手办", "速度+30" );
// 	insert(0xED26751B, 0x8639741F, 0, "时之环", "神佑率+5%" );
// 	insert(0x4FC565AA, 0xA83BA91E, 10000, "通灵宝玉", "战斗经验+1%" );
// 	insert(0xAE883DD2, 0xCE09A059, 10000, "聚宝盆", "战斗金钱+1%" );
// 	insert(0x60523FF1, 0x7669E147, 0, "碧玉葫芦", "治疗效果+64" );
// 	insert(0x93A0FC49, 0xF07197ED, 0, "神木宝鼎", "被治疗效果+64" );
// 	insert(0xDBDE982D, 0x365A8D06, 0, "八咫镜", "20%反弹5%物理伤害" );
// 	insert(0xD92DF835, 0x50997E59, 0, "嗜血幡", "吸血+5%" );
// 	insert(0x081E1FF5, 0x0BDFD09C, 0, "金甲仙衣", "物理格挡+5%" );
// 	insert(0x8F0E6273, 0xC1B54E00, 0, "降魔斗篷", "法术格挡+5%" );
// 	insert(0x7E21AF3F, 0xB47273A0, 0, "九幽", "治疗效果+2%" );
// 	insert(0xCD4EA3D4, 0xE95997AD, 0, "救命毫毛", "倒地后复活+5%/回合" );
// 	insert(0x9FB5513B, 0xE73D5164, 0, "镇海珠", "法术穿刺+2%" );
// 	insert(0x2890FFA9, 0xC36E1F99, 0, "五火神焰印", "法术暴击+5%" );
// 	insert(0xB7113AA0, 0xB664DE8F, 10000, "忘情", "");
// 	insert(0xA68AB260, 0x880E0979, 0, "慈悲", "治疗暴击+5%" );
// 	insert(0xFBCFDC2F, 0x1ECCABDB, 10000, "梦蝶", "" );
	


	// 1级
	insert(0x00000000, 0x00000000, 0, "碧玉葫芦", "增加师门技能的气血恢复效果");
	insert(0x00000000, 0x00000000, 0, "飞剑", "增加命中");
	insert(0x00000000, 0x00000000, 0, "拭剑石", "增加伤害");
	insert(0x00000000, 0x00000000, 0, "金甲仙衣", "神兵护体");
	insert(0x00000000, 0x00000000, 0, "缚妖索", "捆绑目标，使其无法逃跑");
	// C1D43099将就
	insert(0x00000000, 0x00000000, 0, "鬼脸面具", "战斗中变身");
	insert(0x00000000, 0x00000000, 0, "金钱镖", "战斗中使用当前携带金钱攻击敌人");
	insert(0x00000000, 0x00000000, 0, "惊魂铃", "吓退召唤兽");
	insert(0x00000000, 0x00000000, 0, "嗜血幡", "物理攻击时一定几率攻击多个目标");
	insert(0x00000000, 0x00000000, 0, "九黎战鼓", "提升召唤兽攻击");
	insert(0x00000000, 0x00000000, 0, "盘龙壁", "提升召唤兽防御");
	insert(0x00000000, 0x00000000, 0, "汇灵盏", "提升召唤兽灵力");
	insert(0x00000000, 0x00000000, 0, "五色旗盒", "合成导标旗");
	insert(0x00000000, 0x00000000, 0, "天师符(方寸山)", "增加师门技能等级");
	insert(0x00000000, 0x00000000, 0, "织女扇(女儿村)", "增加师门技能等级");
	insert(0x00000000, 0x00000000, 0, "雷兽(天宫)", "增加师门技能等级");
 	insert(0x00000000, 0x00000000, 0, "迷魂灯(盘丝洞)", "增加师门技能等级");
	insert(0x00000000, 0x00000000, 0, "定风珠(五庄观)", "增加师门技能等级");
	insert(0x00000000, 0x00000000, 0, "幽灵珠(无底洞)", "增加门派技能");
	// 2级
	insert(0x00000000, 0x00000000, 0, "玄冰面具", "战斗中变身");
	insert(0x00000000, 0x00000000, 0, "降魔斗篷", "神兵护体");
	insert(0x00000000, 0x00000000, 0, "附灵玉", "增加灵力");
	insert(0x00000000, 0x00000000, 0, "捆仙绳", "捆绑目标，使其无法逃跑");
	insert(0x00000000, 0x00000000, 0, "现形符", "战斗中识破变身效果");
//	insert(0x00000000, 0xB2E715C3, 0, "", "");
	// 将就 0xEAA6AD2E
	insert(0x00000000, 0x00000000, 0, "聚妖铃", "召唤怪物参战");
	insert(0x00000000, 0x00000000, 0, "万鬼幡", "召唤鬼魂参战");
	insert(0x00000000, 0x00000000, 0, "五彩娃娃", "替主人承受一定伤害");
	insert(0x00000000, 0x00000000, 0, "番天印", "禁止法宝发挥作用");
	insert(0x00000000, 0x00000000, 0, "七杀(大唐官府)", "忽略目标部分防御");
	insert(0x00000000, 0x00000000, 0, "罗汉珠(化生寺)", "一定回合内魔法消耗大幅度减少");
	insert(0x00000000, 0x00000000, 0, "分水(龙宫)", "一定回合内将部分伤害转化为气血");
	insert(0x00000000, 0x00000000, 0, "赤焰(魔王寨)", "回复魔法");
	insert(0x00000000, 0x00000000, 0, "金刚杵(普陀山)", "增加普陀山法术威力");
	insert(0x00000000, 0x00000000, 0, "兽王令(狮驼岭)", "提升召唤兽所有属性");
	insert(0x00000000, 0x00000000, 0, "摄魂(阴曹地府)", "使目标承受的伤害增加");
	insert(0x00000000, 0x00000000, 0, "宝烛(无底洞)", "每回合自动回复气血，回合结束时起效");
	insert(0x00000000, 0x00000000, 0, "天煞(凌波城)", "持续回复魔法值，回合结束时起效，满层情况下回合结束时回复1点战意");
	insert(0x00000000, 0x00000000, 0, "神木宝鼎(神木林)", "将受到的部分伤害转化为魔法值");
	// 3级
	insert(0x00000000, 0x00000000, 0, "神木面具", "战斗中变身");
	insert(0x00000000, 0x00000000, 0, "落雨金钱", "战斗中使用当前携带金钱攻击敌人");
	insert(0x00000000, 0x00000000, 0, "缚龙索", "捆绑目标，使其无法逃跑");
	insert(0x00000000, 0x00000000, 0, "鬼泣", "吓退召唤兽");
	insert(0x00000000, 0x00000000, 0, "灵光宝匣", "定位移动工具");
	insert(0x00000000, 0x00000000, 0, "缩地尺", "移动工具");
	insert(0x00000000, 0x00000000, 0, "影蛊", "跟踪工具");
	insert(0x00000000, 0x00000000, 0, "混元伞", "魔法反弹");
	insert(0x00000000, 0x00000000, 0, "宝落金钱", "击落法宝");
	insert(0x00000000, 0x00000000, 0, "无魂傀儡", "吸引玩家攻击");
	insert(0x00000000, 0x00000000, 0, "苍白纸人", "替主人承受一定伤害");
	insert(0x00000000, 0x00000000, 0, "通灵宝玉", "战斗中获得的经验增加");
	insert(0x00000000, 0x00000000, 0, "聚宝盆", "战斗中获得的金钱增加");
	insert(0x00000000, 0x00000000, 0, "乾坤玄火塔", "增加愤怒值");
	insert(0x00000000, 0x00000000, 0, "无尘扇", "减少愤怒值");
	insert(0x00000000, 0x00000000, 0, "干将莫邪(大唐官府)", "临时增加伤害");
	insert(0x00000000, 0x00000000, 0, "慈悲(化生寺)", "增加师门法术与特技加血效果");
	insert(0x00000000, 0x00000000, 0, "救命毫毛(方寸山)", "自动复活");
	insert(0x00000000, 0x00000000, 0, "普渡(普陀山)", "	一定几率增加恢复个数");
	insert(0x00000000, 0x00000000, 0, "镇海珠(龙宫)", "法术攻击目标时忽视目标1%的灵力");
	insert(0x00000000, 0x00000000, 0, "奇门五行令(五庄观)", "降低受到的伤害");
 	insert(0x00000000, 0x00000000, 0, "失心钹(狮驼岭)", "降低受到的召唤兽伤害");
	insert(0x00000000, 0x00000000, 0, "五火神焰印(魔王寨)", "增加自身法术暴击率");
	insert(0x00000000, 0x00000000, 0, "九幽(阴曹地府)", "利用尸腐毒为己方成员增加血量");
	insert(0x00000000, 0x00000000, 0, "忘情(盘丝洞)", "封的时候有一定几率使目标获得治疗效果减少的状态");
	// 4级
	insert(0x00000000, 0x00000000, 0, "重明战鼓", "增加召唤兽的物理伤害和法术伤害");
	insert(0x00000000, 0x00000000, 0, "梦云幻甲", "增加召唤兽的物理防御和法术防御");
	insert(0x00000000, 0x00000000, 0, "炽焰丹珠", "死亡时保留愤怒值");
	insert(0x00000000, 0x00000000, 0, "太虚玉液	", "回复气血");
	insert(0x00000000, 0x00000000, 0, "蟠龙玉璧", "减免受到的伤害");
	insert(0x00000000, 0x00000000, 0, "九梵清莲", "减免来自召唤兽的物理攻击伤害");
	insert(0x00000000, 0x00000000, 0, "苍灵雪羽", "提升全体法术伤害效果");
	insert(0x00000000, 0x00000000, 0, "烽火狼烟", "提升全体物理伤害效果");
	insert(0x00000000, 0x00000000, 0, "舞雪冰蝶", "降低目标物理命中");
	insert(0x00000000, 0x00000000, 0, "紫火如意	", "对召唤兽造成伤害");
	insert(0x00000000, 0x00000000, 0, "凌波仙符	", "提升速度");
	insert(0x00000000, 0x00000000, 0, "归元圣印", "提升治疗量");
	insert(0x00000000, 0x00000000, 0, "落星飞鸿", "提升物理伤害");
	insert(0x00000000, 0x00000000, 0, "流影云笛", "提升法术伤害");
	insert(0x00000000, 0x00000000, 0, "月影(神木林)", "增加法术连击几率");
	insert(0x00000000, 0x00000000, 0, "斩魔(凌波城)", "物理攻击时增加物理伤害结果");
	insert(0x00000000, 0x00000000, 0, "金蟾(无底洞)", "回复本方所有玩家气血");
	insert(0x00000000, 0x00000000, 0, "软烟罗锦", "提升法术闪避");
	insert(0x00000000, 0x00000000, 0, "谷玄星盘", "增加法术吸收率");
	insert(0x00000000, 0x00000000, 0, "千斗金樽", "增加物理暴击率");
	insert(0x00000000, 0x00000000, 0, "宿幕星河	", "增加法术暴击率");
	insert(0x00000000, 0x00000000, 0, "北冥巨鳞", "增加我方伤害");
	insert(0x00000000, 0x00000000, 0, "血魄元幡", "增加我方法术伤害");
	insert(0x00000000, 0x00000000, 0, "翠碧玉箫", "增加我方抗封");
	insert(0x00000000, 0x00000000, 0, "冷龙石磐", "增加我方防御");
	insert(0x00000000, 0x00000000, 0, "琉璃云罩", "增加我方法术防御");
	insert(0x00000000, 0x00000000, 0, "璞玉灵钵", "降低我方造成和受到的所有伤害");

	
	



	for (auto& it : *_table)
	{
		it.second.price = 500000;
	}

	initIdx();
	initTable(eIcon::暗器a);
	insert(0xA4C811C5, 0x935EC081, 0, "飞刀", "40伤害" );
	insert(0x4C07009E, 0xBF944057, 0, "飞蝗石", "60伤害" );
	insert(0x2851A8EC, 0x5D501D52, 0, "铁蒺藜", "80伤害" );
	insert(0x961527F8, 0x9E5D7895, 0, "无影神针", "100伤害" );
	insert(0xB2657A38, 0x454FC9EB, 0, "孔雀翎", "120伤害" );
	insert(0xBE43C96E, 0xE4366820, 0, "含沙射影", "140伤害" );
	insert(0xCD324F8E, 0x3EF314E5, 0, "回龙摄魂标", "160伤害" );
	insert(0xFB2A8F4C, 0x57255C54, 0, "寸阴若梦", "180伤害" );
	insert(0x82A15466, 0x69404DEA, 0, "魔睛子", "200伤害" );
	insert(0xA1716F61, 0x7AFB7396, 0, "顺逆神针", "220伤害" );

	initIdx();
	initTable(eIcon::跑商p);
	insert(0x2C2D056A, 0x3E45E470, 0, "棉布", "商品");
	insert(0x09A396DF, 0x0C23AB02, 0, "佛珠", "商品");
	insert(0x10095AF2, 0xADE7E512, 0, "扇子", "商品");
	insert(0x3B723D09, 0x5BBC4BD5, 0, "刀", "商品");
	insert(0x475C0227, 0x4EB56D11, 0, "珍珠", "商品");
	insert(0x1214601C, 0xC5D83684, 0, "纸钱", "商品");
	insert(0x6FFE61EF, 0xDBCC855E, 0, "饰品", "商品");
	insert(0x17CDA1A8, 0xD6E56581, 0, "夜明珠", "商品");
	insert(0x1D1B8623, 0x5DA26DF2, 0, "盐", "商品");
	insert(0x455447CE, 0xB3E1E4F1, 0, "布帽", "商品");
	insert(0xF82AAC0F, 0xC5679627, 0, "酒", "商品");
	insert(0xCCA5E33A, 0x1111FBA1, 0, "蜡烛", "商品");
	insert(0xD0FEED23, 0x75EAFA24, 0, "人参", "商品");
	insert(0x4B45F754, 0x4446AACC, 0, "香油", "商品");
	insert(0x254F32EB, 0xDF6AC41C, 0, "铃铛", "商品");
	insert(0x2D2B1B01, 0xA80295E6, 0, "木头", "商品");
	insert(0x4F8A961F, 0x583B0F67, 0, "符", "商品");
	insert(0x1881E054, 0x518D0F0E, 0, "鹿茸", "商品");
	insert(0x7E5D886B, 0x3CE911B4, 0, "面粉", "商品");
	insert(0x39648C11, 0xC0CF8AAE, 0, "锦盒", "商品");
	insert(0xE1B6A57B, 0x7B286785, 0, "花", "商品");
	insert(0x30DCC0A5, 0x3DB8CD54, 0, "木鱼", "商品");
	for (auto& it : *_table)
	{
		it.second.desc = "特产";
	}

	initIdx();
	initTable(eIcon::五宝w);
	insert(0x517A3AFF, 0x797267D4, 0, "金刚石", "兑换神兽要诀");
	insert(0x3B83CE08, 0x605D073F, 0, "定魂珠", "兑换神兽要诀");
	insert(0x4497E508, 0x91BB3A47, 0, "夜光珠", "兑换神兽要诀");
	insert(0x1C64382E, 0x853BB4DA, 0, "龙鳞", "换神兽要诀");
	insert(0xAF394F2F, 0xAF8B6CC5, 0, "避水珠", "兑换神兽要诀");
	for (auto& it : *_table)
	{
		it.second.desc = "五宝,兑换神兽要诀";
	}

	initIdx();
	initTable(eIcon::染色r);
	insert(0x21CD5A41, 0xFD6C9733, 0, "彩果", "染色材料");
	insert(0x1451CF48, 0x64138D72, 0, "颜灵果", "染色材料");
	insert(0xAAE95E4E, 0x2C1693B2, 0, "彩虹草", "染色材料");

	initIdx();
	initTable(eIcon::强化q);
	insert(0xAAF008A6, 0x58FC2360, 0, "青龙石", "强化石");
	insert(0x8873A9DF, 0x23FA7698, 0, "白虎石", "强化石");
	insert(0x2B6055CE, 0xBB8854EA, 0, "玄武石", "强化石");
	insert(0x26C133D0, 0xD9180D40, 0, "朱雀石", "强化石");

	initIdx();
	initTable(eIcon::鬼谷g);
	insert(0xFE9A9D86, 0x4B643BEC, 0, "地载阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "风扬阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "虎翼阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "龙飞阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "鸟翔阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "蛇幡阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "天覆阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "云垂阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "雷绝阵", "鬼谷子");
	insert(0xFE9A9D86, 0x4B643BEC, 0, "鹰啸阵", "鬼谷子");

	initIdx();
	initTable(eIcon::元宵y);
	insert(0x522C3747, 0xF04964D3, 0, "攻击元宵", "增加攻击资质");
	insert(0x522C3747, 0xF04964D3, 0, "防御元宵", "增加防御资质");
	insert(0x522C3747, 0xF04964D3, 0, "体力元宵", "增加体力资质");
	insert(0x522C3747, 0xF04964D3, 0, "法力元宵", "增加法力资质");
	insert(0x522C3747, 0xF04964D3, 0, "速度元宵", "增加速度资质");
	insert(0x522C3747, 0xF04964D3, 0, "躲避元宵", "增加躲避资质");
	insert(0x522C3747, 0xF04964D3, 0, "成长元宵", "增加成长");


	initIdx();
	initTable(eIcon::书书s);
	const auto& tableShoe = _tables.at(eIcon::鞋子x);
	for (int k = 0; k <= 16; ++k)
	{
		insert(0x41B626D7, 0xE5CECBF4, 0, "制造指南书", "");
		auto& it = _table->at(_idx);
		it.desc += toString("%d级", k * 10);
		it.price = tableShoe.at(k).price / 2;
	}

	initIdx();
	initTable(eIcon::铁铁t);
	for (int k = 0; k <= 16; ++k)
	{
		insert(0xECB79EF2, 0x9A14A997, 0, "百炼精铁", "");
		auto& it = _table->at(_idx);
		it.desc += toString("%d级", k * 10);
		it.price = tableShoe.at(k).price / 2;
	}

	initIdx();
	initTable(eIcon::打造d);
	insert(0x05A560CE, 0x09CE8647, 0, "炼妖石", "和召唤兽合成,能做成天眼珠");
	insert(0x9F6993FA, 0xF2379F81, 0, "上古锻造图册", "打造宝宝装备");
	insert(0xD29E5ECE, 0x859C0204, 0, "天眼珠", "打造宝宝装备");
	insert(0x03C1E325, 0x8AABE686, 0, "三眼天珠", "打造宝宝装备");
	insert(0x50E14899, 0x4E9B7820, 0, "九眼天珠", "打造宝宝装备");
	insert(0x2702462A, 0xADB93C16, 0, "陨铁", "打造人物装备");

	
	initIdx();
	initTable(eIcon::导标d);
	insert(0xAA3E658C, 0xC96A2910, 0, "导标旗", "传送指定地点");
	insert(0x842FDAF6, 0x6863A8F9, 0, "导标旗", "传送指定地点");
	insert(0x746BEC9C, 0x3C4BE035, 0, "导标旗", "传送指定地点");
	insert(0x033102B8, 0x144634BA, 0, "导标旗", "传送指定地点");
	insert(0x3F3A3602, 0x27776F07, 0, "导标旗", "传送指定地点");


	initIdx();
	initTable(eIcon::旗子q);
	insert(0x0DE87173, 0x4F8723DA, 0, "红色合成旗", "长安城" );
	insert(0x78C6828D, 0x4D27A80E, 0, "蓝色合成旗", "傲来国" );
	insert(0x306FE9B9, 0xB06EE4C6, 0, "白色合成旗", "长寿村" );
	insert(0xC87EF093, 0x498354A0, 0, "绿色合成旗", "朱紫国" );
	insert(1084205009, 1030021222, 0, "黄色合成旗", "大唐境外");


	initIdx();
	initTable(eIcon::宝图b);
	// 高级
	insert(0xA3DF3AA3, 0x894D37C5, 0, "藏宝图", "记录着宝藏地点");
	insert(0x0C958C8B, 0x7486E2FD, 0, "藏宝图", "记录着宝藏地点");


	initIdx();
	initTable(eIcon::福寿f);
	insert(0xB54FE9D7, 0x569080C7, 0, "黄纸", "祭祀的必备物品");
	insert(0xCB791292, 0x0D81554B, 0, "蜡烛", "红色的蜡烛,用于照明和作法事");
	insert(0x55877D9A, 0x017DD224, 0, "香", "普通的香,点燃后有异香");

	initIdx();
	initTable(eIcon::杂货z);
	insert(0xD3CE3F9D, 0xF0643AC7, 0, "摄妖香", "防止遇怪");
	insert(0xC3E09937, 0xDADEC09B, 0, "洞冥草", "去除摄妖香效果");



	initIdx();
	initTable(eIcon::修炼x);
	insert(0x5A0E9307, 0x6EB440C8, 0, "九转金丹", "增加攻击修炼");
	insert(0x5A0E9307, 0x6EB440C8, 0, "九转金丹", "增加防御修炼");
	insert(0x5A0E9307, 0x6EB440C8, 0, "九转金丹", "增加法术修炼");
	insert(0x5A0E9307, 0x6EB440C8, 0, "九转金丹", "增加法防修炼");
	insert(0x19CEE771, 0x0F2E3E3F, 0, "修炼果", "增加宝宝攻击修炼");
	insert(0x19CEE771, 0x0F2E3E3F, 0, "修炼果", "增加宝宝防御修炼");
	insert(0x19CEE771, 0x0F2E3E3F, 0, "修炼果", "增加宝宝法术修炼");
	insert(0x19CEE771, 0x0F2E3E3F, 0, "修炼果", "增加宝宝法防修炼");


	initIdx();
	initTable(eIcon::宝宝b);
	insert(0xAD87E59A, 0x560E4B3F, 0, "金柳露", "当前参战召唤兽等级重置到携带等级并归还经验");
	insert(0x5DBBFD59, 0xA1230B95, 0, "超级金柳露", "当前参战召唤兽等级重置到携带等级并归还经验, 如果没有参战召唤兽,则作用于其他满足条件的召唤兽");
	insert(0x581C4AC7, 0x0E4C5357, 0, "超六六", "所有召唤兽等级重置到携带等级并归还经验");
	insert(0xE826BAA2, 0x0DA1AB16, 0, "碧耦", "增加召唤兽经验");
	insert(0x722F3F52, 0x46D073B2, 0, "初级内丹", "");
	insert(0x02A776DE, 0x4E43EBFF, 0, "高级内丹", "");


	initIdx();
	initTable(eIcon::师门s);
	insert(0xE83A6DBF, 0x9A0EA431, 0, "乾坤袋", "师门降伏");
	insert(0xD75A7F1C, 0xEA0E76DF, 0, "信件", "师门跑腿");


	initIdx();
	initTable(eIcon::任务r);
	insert(0xDF37C485, 0x7FA4203F, 0, "天眼通符", "");
	insert(0x8FF330C0, 0xFE72166A, 0, "特赦令牌", "剧情道具");
	insert(0x97C77FD8, 0x92F6F4CA, 0, "银票", "白虎堂跑商道具");
	insert(0x9C59875F, 0x6510B629, 0, "镖银", "押镖道具");
	insert(0xCD75440C, 0xFB16405E, 0, "粮草", "军需道具");
	insert(0x4714F3C1, 0xF1CDBB44, 0, "木头", "任务道具");
	insert(0x9BEE2ED1, 0xBCE0AE05, 0, "小雪块", "任务道具");
	insert(0x43F99886, 0x1E5C9739, 0, "大雪块", "任务道具");

	initIdx();
	initTable(eIcon::道具d);
	insert(0xD06DDC41, 0x9A86BD6C, 0, "飞行符", "可以飞行");
//	insert(0xF1D0DFC7, 0x0E4DC36F, 0, "万鬼幡", "召唤一只地府怪助战");
	insert(0xA80AC05A, 0xF316C979, 0, "灵宝图鉴", "鉴定腰带衣服鞋子" );
	insert(0xA523F956, 0x4FB63423, 0, "神兵图鉴", "鉴定武器和衣服" );


	initStone();

	initIdx();
	initTable(eIcon::花卉h);
	insert(0xF26A689A, 0xBEAE27D0, 0, "兰花", "花" );
	insert(0x07870048, 0xAAB0BA1D, 0, "桃花", "花" );
	insert(0x206394EF, 0xCE65E9FA, 0, "百合", "花" );
	insert(0xFFF1B4CE, 0xCFD3A149, 0, "牡丹", "花" );
	insert(0x28DA1984, 0x960C3163, 0, "康乃馨", "花" );
	insert(0x3944ABFA, 0x614A5011, 0, "红玫瑰", "花" );

	initIdx();
	initTable(eIcon::乐器y);
	insert(0x3BAD5575, 0x6B2746E7, 0, "萧", "乐器");
	insert(0x2A798918, 0x3CCB26E8, 0, "钹", "乐器");
	insert(0x171AE24F, 0x6D12F11F, 0, "木鱼", "乐器");
	insert(0xE4D3F15A, 0x1E2183D9, 0, "琵琶", "乐器");
	insert(0x26114A21, 0x7836B5A5, 0, "编钟", "乐器");
	insert(0x80310385, 0xB5758271, 0, "唢呐", "乐器");


	initIdx();
	initTable(eIcon::坐饰z);
	insert(0xD7E977F7, 0x6F09B32F, 0, "展翅高飞", "宝贝葫芦");
	insert(0xD555E56C, 0x942AB7C0, 0, "旗开得胜", "宝贝葫芦");
	insert(0xDBB13B82, 0x01B8900E, 0, "霸王雄风", "宝贝葫芦");
	insert(0x22245346, 0x7F5AF2ED, 0, "独眼观天", "神气小龟");
	insert(0xB4448E15, 0xE11D168A, 0, "威武不屈", "神气小龟");
	insert(0xC210C8A6, 0x38BB89C1, 0, "深藏不露", "神气小龟");
	insert(0x21E6E4AD, 0x2B3BD5AF, 0, "异域浓情", "汉血宝马");
	insert(0x4E622591, 0xE99C9229, 0, "流星天马", "汉血宝马");
	insert(0x6734E476, 0xCA080495, 0, "威猛将军", "汉血宝马");
	insert(0x42C8E012, 0xD84AEFD9, 0, "知情达理", "欢喜羊羊");
	insert(0xC29077C1, 0x153B18EB, 0, "气宇轩昂", "欢喜羊羊");
	insert(0x56A40A70, 0x95F2DAEA, 0, "如花似玉", "欢喜羊羊");
	insert(0x399B3F51, 0xC124D1F4, 0, "傲视天下", "魔力斗兽");
	insert(0xF0ECED8B, 0x369C76E3, 0, "铁血豪情", "魔力斗兽");
	insert(0xD8246960, 0x1F226C87, 0, "唯我独尊", "魔力斗兽");
	insert(0x82DBAAF6, 0x58DC5C54, 0, "叱诧风云", "披甲战狼");
	insert(0xAD1A3DAA, 0xA8C159D5, 0, "异域风情", "披甲战狼");
	insert(0x84389440, 0x6D92CEB9, 0, "假面勇者", "披甲战狼");
	insert(0x347CE5F8, 0xC3127ABF, 0, "霓裳魅影", "闲云野鹤");
	insert(0x7A72E56A, 0xFFB05D4D, 0, "披星戴月", "闲云野鹤");
	insert(0x1FFD79EC, 0x8B15F395, 0, "烈焰燃情", "闲云野鹤");
	insert(0x5B7FC4A3, 0x65099256, 0, "天雨流芳", "云魅仙鹿");
	insert(0x5E631741, 0x0587D5F5, 0, "灵光再现", "云魅仙鹿");
	insert(0x208D42ED, 0x8138AFE1, 0, "倾国倾城", "云魅仙鹿");

	initJiaju();
	initMenpai();
	initSkill();


	const auto& tableSkill = _tables.at(eIcon::技能j);
	initIdx();
	initTable(eIcon::兽决s);
	for (int e = (int)eSkill::ePetSki0; e <= (int)eSkill::ePetSkiEnd; ++e)
	{
		const auto& it = tableSkill.at(e);
		insert(it.big, it.big, 0, "魔兽要诀", it.name);
	}
	insert(0x4A0644D7, 0xAFE21707, 0, "魔兽要诀", "");
	insert(0x6CAD36E8, 0xD86D89B8, 0, "神兽要诀", "");

	initIdx();
	initTable(eIcon::符石f);
	insert(1477316065, 3294501316, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");

	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");
	insert(0x00000000, 0x00000000, 100000, "符石", "");

	initIdx();
	initTable(eIcon::状态z);
	const auto& fushis = txtSkill::getInstance()->getFushis();
	const auto& fs = _tables.at(eIcon::符石f);
	for (int k = 0; k < fushis.size(); ++k)
	{
		const auto& f = fs.at(rand() % fs.size());
		insert(f.small, f.big, 100000, "状态符石", tableSkill.at((int)fushis[k]).name);
	}

	initIdx();
	initTable(eIcon::追加z);
	const auto& zhuijias = txtSkill::getInstance()->getZhuijias();
	for (int k = 0; k < zhuijias.size(); ++k)
	{
		const auto& f = fs.at(rand() % fs.size());
		insert(f.small, f.big, 100000, "追加符石", tableSkill.at((int)zhuijias[k]).name);
	}

	initIdx();
	initTable(eIcon::初丹c);
	insert(0x00000000, 0x00000000, 0, "坚甲", "拥有此技能后对敌人造成的反震伤害得到加强");
	insert(0x00000000, 0x00000000, 0, "矫健", "拥有此技能会提高自身的气血与速度，效果随召唤兽等级提升而增加");
	insert(0x00000000, 0x00000000, 0, "阴伤", "疯狂攻击的第二次伤害更高，但是受到火、雷系法术攻击时承受额外的伤害");
	insert(0x00000000, 0x00000000, 0, "淬毒", "满淬毒汁的毒牙使对手更加胆寒");
	insert(0x00000000, 0x00000000, 0, "擅咒", "你对目标的法术伤害得到提升");
	insert(0x00000000, 0x00000000, 0, "灵身", "法术带来的爆发性更强烈，只是受到强力与高强力技能打击时，所受到的伤害增加");
	insert(0x00000000, 0x00000000, 0, "迅敏", "拥有此技能会提高自己的伤害力与速度，效果随召唤兽等级提升而增加");
	insert(0x00000000, 0x00000000, 0, "圣洁", "拥有此技能后，你的召唤兽使用法术攻击时驱鬼和高驱鬼效果得到提升");
	insert(0x00000000, 0x00000000, 0, "钢化", "带有高级防御、防御技能时的防御值增加，效果随召唤兽等级提升而增加，但是所带来的代价是受到法术伤害额外打击");
	insert(0x00000000, 0x00000000, 0, "狂怒", "在此狂乱状态下必杀的伤害更高，但是受到水、土系法术攻击时承受额外的伤害");
	insert(0x00000000, 0x00000000, 0, "狙刺", "该召唤兽对第一目标造成的法术伤害更大");
	insert(0x00000000, 0x00000000, 0, "深思", "高冥思的效果得到加强");
	insert(0x00000000, 0x00000000, 0, "愤恨", "拥有此技能能够更好的突破幸运、高级幸运技能，对目标造成更大的物理伤害");
	insert(0x00000000, 0x00000000, 0, "慧心", "只要集中精神，抵御封印的能力就会加强");
	insert(0x00000000, 0x00000000, 0, "灵光", "法术的精修必然会为你带来更多好处，效果随召唤兽等级提升而增加");
	insert(0x00000000, 0x00000000, 0, "连环", "拥有此技能时，召唤兽触发连击的几率增加");
	insert(0x00000000, 0x00000000, 0, "撞击", "物理攻击时命中率得到增加，效果与体质点成正比，同时增加一定的伤害结果");
	insert(0x00000000, 0x00000000, 0, "无畏", "拥有此技能能够更好的突破反震、高级反震技能，对目标造成更大的物理伤害");
	insert(0x00000000, 0x00000000, 0, "静岳", "拥有此技能会提高自己的灵力与气血，效果随召唤兽等级提升而增加");

	initIdx();
	initTable(eIcon::高丹g);
	insert(0x00000000, 0x00000000, 0, "腾挪劲", "神奇的护盾，有一定几率能够将你所受的一部分物理伤害腾挪到另一个世界");
	insert(0x00000000, 0x00000000, 0, "隐匿击", "专家级隐身");
	insert(0x00000000, 0x00000000, 0, "舍身击", "置之死地而后生，你对目标造成的物理伤害值受到力量点的加成");
	insert(0x00000000, 0x00000000, 0, "神机步", "入场时你总是活力无限，3回合内极大的增加你的躲避力");
	insert(0x00000000, 0x00000000, 0, "生死决", "此刻你如天神下凡，伤害力临时得到提升而防御力临时降低");
	insert(0x00000000, 0x00000000, 0, "凛冽气", "霸气外露，你的在场是本方所有召唤兽的强心剂，逃跑的几率也减少了");
	insert(0x00000000, 0x00000000, 0, "龙胄铠", "你放弃了伤害，得到的是防御的大幅度提升");
	insert(0x00000000, 0x00000000, 0, "催心浪", "虽然带有法术波动技能时法术力量无法控制，但是总会向更好的方向发展");
	insert(0x00000000, 0x00000000, 0, "玉砥柱", "最尖锐的矛也遇到了一点麻烦，壁垒击破的威力在你面前减弱了，但是对目标造成的伤害也降低");
	insert(0x00000000, 0x00000000, 0, "电魂闪", "神奇的法术，总在不经意间给你惊喜，单体法术攻击时有可能将目标携带的其中一个增益状态驱散");
	insert(0x00000000, 0x00000000, 0, "双星爆", "强大的法术攻击接踵而来，法术连击的威力更强大");
	insert(0x00000000, 0x00000000, 0, "阴阳护", "激发潜力，保护他人！你在保护其他目标的时候所承受的伤害减少");
	insert(0x00000000, 0x00000000, 0, "血债偿", "战友的离去反而激起了你的斗志");
//	insert(0x00000000, 0x00000000, 0, "", ""); // 这个不是内丹?
	insert(0x00000000, 0x00000000, 0, "通灵法", "敏锐的洞察力！能够找出目标法术防御的漏洞，对处在法术减免状态的目标造成更大的伤害");
	insert(0x00000000, 0x00000000, 0, "玄武躯", "你放弃了伤害，得到的是气血的大幅度提升");
	insert(0x00000000, 0x00000000, 0, "碎甲刃", "以千钧之力击碎目标的护甲，30%的几率2回合内降低目标一定防御值，效果与自身力量点相关");

	// 先初始化宝宝
	initCard();
}
