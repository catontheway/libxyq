#include "TxtMenpai.h"
using namespace ctt;
static const std::vector<sMenpai> s_menpais =
{
	{ eMenpai::Dt, "大唐官府", "程咬金", "大唐官府", "程咬金府",
	{
		{ { 0x00, 0x7A33A5A9, 0x8B6687C7, "为官之道", ePromote::None, { { 30, eSkill::杀气诀 } } },
		{ 0x01, 0xB2BCD78E, 0x83510218, "无双一击", ePromote::None, { { 45, eSkill::后发制人 } } },
		{ 0x02, 0xFCF64BB4, 0x2C4A485C, "神兵鉴赏", ePromote::None, { /*{ 65, eSkill::兵器谱 }*/ } },
		{ 0x03, 0x20EB6BD0, 0x7D6C0800, "疾风步", ePromote::None, { { 1, eSkill::千里神行 } } },
		{ 0x04, 0xF4D93CEB, 0x43D35D1B, "十方无敌", ePromote::None, { { 30, eSkill::横扫千军 }, { 60, eSkill::破釜沉舟 } } },
		{ 0x05, 0x73C87FDE, 0xEAE7112A, "紫薇之术", ePromote::None, { { 120, eSkill::安神诀 } } },
		{ 0x06, 0xBBCCFA4E, 0x65DB91C9, "文韬武略", ePromote::None, { { 50, eSkill::反间之计 } } } } }
	},
	{ eMenpai::Hs, "化生寺", "空度禅师", "化生寺", "藏经阁",
	{
		{ { 0x0E, 0x5DC9B771, 0xAE58AD12, "小乘佛法", ePromote::None, {} },
		{ 0x0F, 0xE6409CE3, 0x98FFC4AD, "金刚伏魔", ePromote::None, { { 120, eSkill::佛法无边 } } },
		{ 0x10, 0xD1919F3D, 0x7287C064, "诵经", ePromote::None, { { 20, eSkill::唧唧歪歪 } } },
		{ 0x11, 0xEC71CE44, 0x4B8C1B65, "佛光普照", ePromote::None,
		{
			{ 30, eSkill::金刚护法 },
			{ 50, eSkill::韦陀护法 },
			{ 60, eSkill::金刚护体 },
			{ 70, eSkill::一苇渡江 }
		} },
		{ 0x12, 0x058EC75B, 0x7A8856F3, "大慈大悲", ePromote::None, { { 20, eSkill::我佛慈悲 } } },
		{ 0x13, 0x86C94C7C, 0x8F00A676, "歧黄之术", ePromote::None,
		{
//			{ 15, eSkill::推拿 },
			{ 25, eSkill::救死扶伤 },
			{ 10, eSkill::活血 },
			{ 120, eSkill::舍生取义 }
		} },
		{ 0x14, 0x3004AA75, 0xA8939527, "渡世步", ePromote::None, { { 1, eSkill::佛门普渡 } } } } }
	},
	{ eMenpai::Ne, "女儿村", "孙婆婆", "女儿村", "女儿村村长家",
	{
		{ { 0x15, 0x47B9EF90, 0xBC69ED1E, "毒经", ePromote::None, {} },
		{ 0x16, 0x56E88235, 0x23697214, "倾国倾城", ePromote::None, { { 50, eSkill::楚楚可怜 }/*, { 120, eSkill::一笑倾城 } */} },
		{ 0x17, 0x3EC00B8D, 0x1618C7AD, "沉鱼落雁", ePromote::None, { { 20, eSkill::满天花雨 }, { 20, eSkill::雨落寒沙 } } },
		{ 0x18, 0xFB265F9E, 0xC5F34CFB, "闭月羞花", ePromote::None, { { 30, eSkill::似玉生香 } } },
		{ 0x19, 0x52788E94, 0xD280080E, "香飘兰麝", ePromote::None, {} }, 
		{ 0x1A, 0x86FEEA94, 0xCCF72E77, "玉质冰肌", ePromote::None, {} },
		{ 0x1B, 0x91B45987, 0x3D453325, "清歌妙舞", ePromote::None, { { 1, eSkill::移形换影 } } } } }
	},
	{ eMenpai::Fc, "方寸山", "菩提祖师", "方寸山", "灵台宫",
	{
		{ { 0x07, 0x59783586, 0x9FC18E51, "黄庭经", ePromote::None, {} },
		{ 0x08, 0x74F253D9, 0x19396997, "磬龙灭法", ePromote::None, {} },
		{ 0x09, 0x11EAAE6D, 0x0336EB9B, "霹雳咒", ePromote::None, { { 30, eSkill::落雷符 } } },
		{ 0x0A, 0x36F26348, 0xD68D198D, "符之术", ePromote::None,
		{
			{ 20, eSkill::飞行符 },
			{ 40, eSkill::催眠符 },
			{ 30, eSkill::失心符 },
			{ 40, eSkill::失忆符 },
			{ 40, eSkill::定身符 },
			{ 120, eSkill::碎甲符 }
		} },
		{ 0x0B, 0xB293CF00, 0xCD48FDFF, "归元心法", ePromote::None, { { 40, eSkill::归元咒 }, { 40, eSkill::凝神术 } } },
		{ 0x0C, 0xE5A2EB07, 0x684DEBB0, "神道无念", ePromote::None, { { 120, eSkill::分身术 } } },
		{ 0x0D, 0x7E9CCF04, 0x2DD65965, "斜月步", ePromote::None, { { 1, eSkill::乙木仙遁 } } } } }
	},
	{ eMenpai::St, "狮驼岭", "大大王", "狮驼岭", "狮王洞",
	{
		{ { 0x46, 0x009BEBDA, 0xB0013AB2, "魔兽神功", ePromote::None, { { 50, eSkill::变身 }, { 20, eSkill::定心术 } } },
		{ 0x47, 0x513A8A78, 0xBAECB102, "生死搏", ePromote::None, { { 55, eSkill::象形 }, { 60, eSkill::鹰击 }, /*{ 1, eSkill::天魔解体 },*/ { 30, eSkill::狮搏 } } },
		{ 0x48, 0xBA7AD05B, 0x4694D927, "驯兽诀", ePromote::None, { { 30, eSkill::威慑 } } },
		{ 0x49, 0xFC7EDF4C, 0x28BACE76, "阴阳二气诀", ePromote::None, {} },
		{ 0x4A, 0x8B61AADA, 0x630CE9C2, "狂兽诀", ePromote::None, { { 50, eSkill::连环击 } } },
		{ 0x4B, 0x832ACED9, 0x4A1E39A3, "大鹏展翅", ePromote::None, { { 1, eSkill::振翅千里 } } },
		{ 0x4C, 0x5108D3A7, 0x1E8A79DF, "魔兽反噬", ePromote::None, { { 40, eSkill::极度疯狂 } } } }
	}
	},
	{ eMenpai::Mw, "魔王寨", "牛魔王", "魔王寨", "魔王居",
	{
		{ { 0x3F, 0xA36C5AA6, 0xECEF9C70, "牛逼神功", ePromote::None, {} },
		{ 0x40, 0x7244B8D8, 0x56612F8E, "震天诀", ePromote::None, { /*{ 5, eSkill::摇头摆尾 } */} },
		{ 0x41, 0x3632166A, 0xF85D38D4, "火云术", ePromote::None, { { 30, eSkill::飞砂走石 }, { 50, eSkill::三昧真火 } } },
		{ 0x42, 0x50F19558, 0x72491389, "火牛阵", ePromote::None, { { 60, eSkill::牛劲 } } },
		{ 0x43, 0x9495B98F, 0x43541BC6, "牛虱阵", ePromote::None, { { 25, eSkill::无敌牛虱 }, { 25, eSkill::无敌牛妖 } } },
		{ 0x44, 0x9F0522B9, 0x48FC858E, "回身击", ePromote::None, { { 30, eSkill::魔王回首 } } },
		{ 0x45, 0xC70D4DA4, 0xFF7AB8FE, "裂石步", ePromote::None, { { 1, eSkill::牛屎遁 } } } } }
	},
	{ eMenpai::Ps, "盘丝洞", "白晶晶", "盘丝岭", "盘丝洞",
	{ { { 0x4D, 0x8523F7A5, 0x1D0E8D52, "蛛丝阵法", ePromote::None, {} },
	{ 0x4E, 0xB8EACFC0, 0x8FA9C1D7, "催情大法", ePromote::None, { { 40, eSkill::含情脉脉 } } },
	{ 0x4F, 0x3A278387, 0x653EB3E2, "秋波暗送", ePromote::None, { { 30, eSkill::勾魂 }, { 40, eSkill::摄魄 } } },
	{ 0x50, 0x8AFB1A80, 0xE3ADB1EB, "天外魔音", ePromote::None, { { 40, eSkill::魔音摄魂 } } },
	{ 0x51, 0x0829E95B, 0x97B0F3BB, "盘丝大法", ePromote::None, { { 5, eSkill::盘丝阵 }/*, { 60, eSkill::复苏 }*/ } },
	{ 0x52, 0x141B5E54, 0xCB126977, "移形换影", ePromote::None, { { 30, eSkill::天罗地网 }, { 1, eSkill::天蚕丝 }, { 120, eSkill::幻镜术 } } },
	{ 0x53, 0x2397ABE7, 0xBD6854D3, "姐妹相随", ePromote::None, {} } } }
	},
	{ eMenpai::Df, "阴曹地府", "地藏王", "阴曹地府", "地藏王府",
	{
		{ { 0x38, 0x2267FDE2, 0x2975C865, "灵通术", ePromote::None, { /*{ 1, eSkill::勘察令 }, { 30, eSkill::寡欲令 }*/ } },
		{ 0x39, 0x68FBF782, 0x829863CF, "六道轮回", ePromote::None, { { 50, eSkill::魂飞魄散 } } },
		{ 0x3A, 0x18BC5193, 0x7D7E42B5, "幽冥术", ePromote::None, { { 20, eSkill::阎罗令 }, { 120, eSkill::锢魂术 }, { 120, eSkill::黄泉之息 } } },
		{ 0x3B, 0xCAD7422A, 0x60B5C339, "拘魂诀", ePromote::None, { { 30, eSkill::判官令 }, { 120, eSkill::还阳术 } } },
		{ 0x3C, 0xA717E4EC, 0x90AD7379, "九幽阴魂", ePromote::None, { { 40, eSkill::幽冥鬼眼 } } },
		{ 0x3D, 0x015E36F3, 0xEE4186E1, "尸腐恶", ePromote::None, { { 30, eSkill::尸腐毒 }, { 20, eSkill::修罗隐身 } } },
		{ 0x3E, 0x0448AB94, 0xA53AE1E3, "无常步", ePromote::None, { { 1, eSkill::杳无音讯 } } } } }
	},
	{ eMenpai::Lg, "龙宫", "东海龙王", "龙宫", "水晶宫",
	{
		{ { 0x23, 0x37118266, 0x085CAE13, "九龙诀", ePromote::None, { /*{ 60, eSkill::解封 }, */{ 15, eSkill::清心 }, { 120, eSkill::二龙戏珠 } } },
		{ 0x24, 0xC57A39B9, 0xF650D185, "破浪诀", ePromote::None, { { 120, eSkill::神龙摆尾 } } },
		{ 0x25, 0x726EFA79, 0x1A1DE0D4, "呼风唤雨", ePromote::None, { { 15, eSkill::龙卷雨击 } } },
		{ 0x26, 0x80426D9F, 0xCEEAA576, "龙腾", ePromote::None, { { 50, eSkill::龙腾 } } },
		{ 0x27, 0xCB06F1FB, 0xB904AD16, "逆鳞", ePromote::None, { { 60, eSkill::逆鳞 } } },
		{ 0x28, 0x12DCA762, 0x671FC66C, "游龙术", ePromote::None, { { 1, eSkill::水遁 } } },
		{ 0x29, 0xE007F365, 0xDD742E3A, "龙附", ePromote::None, { { 30, eSkill::龙吟 } } } } }
	},
	{ eMenpai::Wz, "五庄观", "镇元大仙", "五庄观", "乾坤殿",
	{
		{ { 0x2A, 0xBDB57B3E, 0x38BA101C, "周易学", ePromote::None, { { 80, eSkill::驱尸 } } },
		{ 0x2B, 0xA24E38FE, 0xD30FDF54, "潇湘仙雨", ePromote::None, { { 10, eSkill::烟雨剑法 }, { 30, eSkill::飘渺式 } } },
		{ 0x2C, 0xCD3C3C12, 0x86832A8C, "乾坤袖", ePromote::None, { { 50, eSkill::日月乾坤 }/*, { 80, eSkill::天地同寿 }*/ } },
		{ 0x2D, 0x63C0827A, 0xDE2533AE, "修仙术", ePromote::None, { { 30, eSkill::炼气化神 }, { 20, eSkill::生命之泉 } } },
		{ 0x2E, 0xE2720478, 0x283D1B37, "混元道果", ePromote::None, {} },
		{ 0x2F, 0xB7426D01, 0xF49FDAFE, "明性修身", ePromote::None, { { 70, eSkill::三花聚顶 } } },
		{ 0x30, 0x8F0D6C4C, 0x3712E54D, "七星遁", ePromote::None, { { 1, eSkill::斗转星移 } } } } }
	},
	{ eMenpai::Pt, "普陀山", "观音姐姐", "普陀山", "潮音洞",
	{
		{ { 0x31, 0xBB5973EF, 0xEB6872B2, "灵性", ePromote::None, { { 120, eSkill::颠倒五行 }, { 60, eSkill::自在心法 } } },
		{ 0x32, 0x0506BE5D, 0x0D4CE946, "护法金刚", ePromote::None, {} },
		{ 0x33, 0x71F0219A, 0x5413DD44, "观音咒", ePromote::None, { { 30, eSkill::紧箍咒 }, { 40, eSkill::杨柳甘露 } } },
		{ 0x34, 0x2BB9F19E, 0xD95C9242, "五行学说", ePromote::None,
		{
			{ 30, eSkill::日光华 },
			{ 30, eSkill::靛沧海 },
			{ 30, eSkill::巨岩破 },
			{ 30, eSkill::苍茫树 },
			{ 30, eSkill::地裂火 }
		} },
		{ 0x35, 0xF5BD9EB4, 0x91B95A02, "金刚经", ePromote::None, { { 30, eSkill::普渡众生 } } },
		{ 0x36, 0xCE175363, 0xC21CFA93, "五行扭转", ePromote::None, {} },
		{ 0x37, 0x8347AA63, 0x02427B90, "莲花宝座", ePromote::None, { { 1, eSkill::坐莲 }, { 120, eSkill::灵动九天 } } } } }
	},
	{ eMenpai::Tg, "天宫", "李靖", "天宫", "凌宵宝殿",
	{
		{ { 0x1C, 0x1EDA4D57, 0xFBCA1857, "天罡气", ePromote::None, { { 50, eSkill::五雷轰顶 }, { 120, eSkill::雷霆万钧 }, { 30, eSkill::天神护体 } } },
		{ 0x1D, 0x3E89723E, 0xB2E190E8, "傲世诀", ePromote::None, { { 30, eSkill::天雷斩 } } },
		{ 0x1E, 0xE509DEF5, 0xC096279E, "清明自在", ePromote::None, {} },
		{ 0x1F, 0xD4FE4342, 0x75FC0B6E, "宁气诀", ePromote::None, { /*{ 20, eSkill::宁心 }*/ } },
		{ 0x20, 0xB3B26849, 0x268A8DE5, "乾坤塔", ePromote::None, { { 50, eSkill::镇妖 }, { 40, eSkill::错乱 } } },
		{ 0x21, 0x1CB7C4FF, 0xD92B56C2, "混天术", ePromote::None, { { 40, eSkill::百万神兵 } } },
		{ 0x22, 0xE80ED007, 0x1079CE8A, "云霄步", ePromote::None, { { 1, eSkill::腾云驾雾 } } } } }
	},
	{ eMenpai::Lb, "凌波城", "二郎神", "凌波城", "凌波城",
	{
		{ { 0x54, 0xD854B619, 0x9BF40DC5, "天地无极", ePromote::None, { { 5, eSkill::浪涌 } } },
		{ 0x55, 0x66878D1C, 0x6D83F3D1, "九转玄功", ePromote::None, { { 50, eSkill::不动如山 } } },
		{ 0x56, 0x8837F110, 0xC080EE77, "武神显圣", ePromote::None, { { 40, eSkill::碎星诀 }, { 50, eSkill::镇魂诀 } } },
		{ 0x57, 0x2F79B759, 0x687EDEFE, "啸傲", ePromote::None, { /*{ 30, eSkill::穿云破空 }*/ } },
		{ 0x58, 0x6027C7C6, 0xEEC348EA, "气吞山河", ePromote::None,
		{
			{ 20, eSkill::裂石 },
			{ 30, eSkill::断岳势 },
			{ 40, eSkill::天崩地裂 },
			{ 60, eSkill::惊涛怒 },
			{ 80, eSkill::翻江搅海 }
		} },
		{ 0x59, 0xA70C7A5A, 0x08F2E772, "诛魔", ePromote::None, { /*{ 5, eSkill::腾雷 }, { 5, eSkill::指地成钢 }*/ } },
		{ 0x5A, 0xEAB341B6, 0xAA65C1F5, "法天象地", ePromote::None, { /*{ 5, eSkill::无穷妙道 },*/ { 1, eSkill::纵地金光 } } } } }
	},
	{ eMenpai::Wd, "无底洞", "地涌夫人", "无底洞", "琉璃殿",
	{
		{ { 0x5B, 0xC21CAA3F, 0xEB4FD0B6, "枯骨心法", ePromote::None, { { 50, eSkill::移魂化骨 } } },
		{ 0x5C, 0x8DAA624D, 0x229B3F36, "阴风绝章", ePromote::None,
		{
			{ 40, eSkill::夺魄令 },
// 			{ 5, eSkill::煞气诀 },
// 			{ 50, eSkill::惊魂掌 },
			{ 100, eSkill::摧心术 }
		} },
		{ 0x5D, 0x2648B742, 0x7F61F010, "鬼蛊灵蕴", ePromote::None, { { 60, eSkill::夺命咒 } } },
		{ 0x5E, 0x77DE4303, 0x8386CD36, "燃灯灵宝", ePromote::None, { { 5, eSkill::明光宝烛 } } },
		{ 0x5F, 0x47B1845A, 0x7B30715D, "地冥妙法", ePromote::None, { { 20, eSkill::地涌金莲 }, /*{ 40, eSkill::万木凋枯 },*/{ 10, eSkill::由己渡人 } } },
		{ 0x60, 0x7B209C81, 0xC8B6A6A3, "混元神功", ePromote::None, { /*{ 5, eSkill::元阳护体 }*/ } },
		{ 0x61, 0x87D67BAB, 0xF0E46F02, "秘影迷踪", ePromote::None, { { 1, eSkill::遁地术 }, { 5, eSkill::金身舍利 } } } } }
	},
	{ eMenpai::Sm, "神木林", "巫奎虎", "神木林", "神木屋",
	{
		{ { 0x62, 0xD7468834, 0x056EAA54, "瞬息万变", ePromote::None, { { 20, eSkill::落叶萧萧 } } },
		{ 0x63, 0xD89652AE, 0x63BC74C4, "万灵诸念", ePromote::None, { { 20, eSkill::荆棘舞 }, { 20, eSkill::尘土刃 }, { 20, eSkill::冰川怒 } } },
		{ 0x64, 0xEB2A7B26, 0x52B73EBF, "巫咒", ePromote::None, { { 50, eSkill::雾杀 }, { 80, eSkill::血雨 } } },
		{ 0x65, 0xD37FE4A6, 0x0E11E662, "万物轮转", ePromote::None, { { 40, eSkill::星月之惠 } } },
		{ 0x66, 0x9E505CED, 0x1BCE436A, "天人庇护", ePromote::None, { { 115, eSkill::炎护 }, { 1, eSkill::叶隐 } } },
		{ 0x67, 0x2ED87112, 0x71EB94AA, "神木恩泽", ePromote::None, { /*{ 5, eSkill::神木呓语 }*/ } },
		{ 0x68, 0x5AD8D3E2, 0xB3E852DE, "驭灵咒", ePromote::None, { { 5, eSkill::密润 }/*, { 40, eSkill::蝼蚁蚀天 }*/ } } } }
	},
};

const vector<sMenpai>& ctt::getMenpais()
{
	return s_menpais;
}
