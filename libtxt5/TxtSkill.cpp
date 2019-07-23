#include "TxtSkill.h"
using namespace ctt;

static const std::vector<sSkillPassive> s_skillPassives = 
{
	{ 0x1379151C, 0x99732F02, eSkillPassive::反击fj, { /*ePassiveSkill::高级反击fj*/ }, "反击", "受到物理攻击有30%几率反击,反击伤害减半" },
	{ 0x01884D50, 0xE9CD05B8, eSkillPassive::高级反击fj, { eSkillPassive::反击fj }, "高级反击", "受到物理攻击有30%几率反击" },
	{ 0xDFC6FDFC, 0xEAE7E3EC, eSkillPassive::反震fz, { /*ePassiveSkill::高级反震fz*/ }, "反震", "受到物理攻击有30%几率反震25%的伤害" },
	{ 0x1E7F5930, 0x71B0F5EE, eSkillPassive::高级反震fz, { eSkillPassive::反震fz }, "高级反震", "受到物理攻击有30%几率反震50%的伤害" },
	{ 0x09556A2E, 0x27D53971, eSkillPassive::吸血xx, { /*ePassiveSkill::高级吸血xx*/ }, "吸血", "物理攻击有20%的吸血效果" },
	{ 0x97B369D6, 0x515A38AD, eSkillPassive::高级吸血xx, { eSkillPassive::吸血xx }, "高级吸血", "物理攻击有35%的吸血效果" },
	{ 0x31C34438, 0x4534723B, eSkillPassive::连击lj, { /*ePassiveSkill::高级连击lj*/ }, "连击", "物理攻击有45%的连击率,伤害下降25%" },
	{ 0xB3C6A6E2, 0x4ECA2A0F, eSkillPassive::高级连击lj, { eSkillPassive::连击lj }, "高级连击", "物理攻击有55%的连击率,伤害下降20%" },
	{ 0x46FA5E55, 0x307E28C8, eSkillPassive::飞行fx, { /*ePassiveSkill::高级飞行fx*/ }, "飞行", "回避率+10%,命中率+10%,但受暗器伤害+50%" },
	{ 0xE5A9F47C, 0xFEF30F0D, eSkillPassive::高级飞行fx, { eSkillPassive::飞行fx }, "高级飞行", "回避率+20%,命中率+20%,但受暗器伤害+20%" },
	{ 0xEB2AF42F, 0xDD5CEE60, eSkillPassive::夜战yz, { /*ePassiveSkill::高级夜战yz*/ }, "夜战", "伤害力+5%" },
	{ 0x5906A6A0, 0x3E81ECFB, eSkillPassive::高级夜战yz, { eSkillPassive::夜战yz }, "高级夜战", "伤害力+10%" },
	{ 0xB3488AAE, 0x59E4822E, eSkillPassive::隐身ys, { /*ePassiveSkill::高级隐身ys*/ }, "隐身", "2回合" },
	{ 0xAFB8E892, 0x9484D8DE, eSkillPassive::高级隐身ys, { eSkillPassive::隐身ys }, "高级隐身", "5回合" },
	{ 0xEF245DFC, 0xDB2B3C6A, eSkillPassive::感知gz, { /*ePassiveSkill::高级感知gz*/ }, "感知", "可以攻击隐身状态下的敌人" },
	{ 0x6CA45F1F, 0x2840330D, eSkillPassive::高级感知gz, { eSkillPassive::感知gz }, "高级感知", "可以攻击隐身状态下的敌人,躲避率+20%" },
	{ 0x86F93A3B, 0xC3F77E8F, eSkillPassive::再生zs, { /*ePassiveSkill::高级再生zs*/ }, "再生", "每回合回复气血=等级" },
	{ 0xE3126879, 0x1BE87C60, eSkillPassive::高级再生zs, { eSkillPassive::再生zs }, "高级再生", "每回合回复气血=等级*2" },
	{ 0xD3E2714A, 0x2514ED1F, eSkillPassive::冥思ms, { /*ePassiveSkill::高级冥思ms*/ }, "冥思", "每回合回复魔法=等级/4" },
	{ 0x81A302FF, 0x66718220, eSkillPassive::高级冥思ms, { eSkillPassive::冥思ms }, "高级冥思", "每回合回复魔法=等级/2" },
	{ 0xC89A9EDC, 0x56DEF316, eSkillPassive::慧根hg, { /*ePassiveSkill::高级慧根hg*/ }, "慧根", "法术消耗-25%" },
	{ 0xF8CE3E63, 0x0E6F601D, eSkillPassive::高级慧根hg, { eSkillPassive::慧根hg }, "高级慧根", "法术消耗减半" },
	{ 0x420269A4, 0xE1DA16D6, eSkillPassive::必杀bs, { /*ePassiveSkill::高级必杀bs*/ }, "必杀", "必杀率+10%" },
	{ 0x4C700EA4, 0x63B6486D, eSkillPassive::高级必杀bs, { eSkillPassive::必杀bs }, "高级必杀", "必杀率+20%" },
	{ 0x40B80312, 0xD8F7385A, eSkillPassive::幸运xy, { /*ePassiveSkill::高级幸运xy*/ }, "幸运", "免疫必杀" },
	{ 0x1CB6FA78, 0x6A29156C, eSkillPassive::高级幸运xy, { eSkillPassive::幸运xy }, "高级幸运", "免疫必杀,法术躲避率+10%" },
	{ 0x4772D507, 0x4A3BBF91, eSkillPassive::神迹sj, { /*ePassiveSkill::高级神迹sj*/ eSkillPassive::精神集中js, eSkillPassive::高级精神集中js }, "神迹", "每回合开始摆脱异常状态" },
	{ 0xFC717CFD, 0x2A1026D7, eSkillPassive::高级神迹sj, { eSkillPassive::神迹sj, eSkillPassive::精神集中js, eSkillPassive::高级精神集中js }, "高级神迹", "免疫异常状态" },
	{ 0xD16002DC, 0x8E539BBA, eSkillPassive::招架zj, { /*ePassiveSkill::高级招架zj*/ }, "招架", "格档率+10%" },
	{ 0x3CBAC3A9, 0x1ADFDD2B, eSkillPassive::高级招架zj, { eSkillPassive::招架zj }, "高级招架", "格档率+20%" },
	{ 0x59EBCAAD, 0x7680EBA8, eSkillPassive::永恒yh, { /*ePassiveSkill::高级永恒yh*/ }, "永恒", "增益效果时间+3回合" },
	{ 0xEC4339C2, 0xF86EA690, eSkillPassive::高级永恒yh, { eSkillPassive::永恒yh }, "高级永恒", "增益效果时间+6回合" },
	{ 0xFFAC3F6A, 0xBABA11E3, eSkillPassive::敏捷mj, { /*ePassiveSkill::高级敏捷mj*/ }, "敏捷", "速度+10%" },
	{ 0x7ADDCB60, 0x4A654A53, eSkillPassive::高级敏捷mj, { eSkillPassive::敏捷mj }, "高级敏捷", "速度+20%" },
	{ 0x2A2C6FCB, 0x56F51981, eSkillPassive::强力ql, { /*ePassiveSkill::高级强力ql*/ }, "强力", "攻击力+等级/2" },
	{ 0x81C9C93E, 0xD466B3D1, eSkillPassive::高级强力ql, { eSkillPassive::强力ql }, "高级强力", "攻击力+等级/1" },
	{ 0xF47ADB17, 0x05728F4B, eSkillPassive::防御fy, { /*ePassiveSkill::高级防御fy*/ }, "防御", "防御+等级/2" },
	{ 0xE17C3B8E, 0x60551819, eSkillPassive::高级防御fy, { eSkillPassive::防御fy }, "高级防御", "防御+等级/1" },
	{ 0x0C425BC3, 0xB5C24835, eSkillPassive::偷袭tx, { /*ePassiveSkill::高级偷袭tx*/ }, "偷袭", "60%免疫反震反击" },
	{ 0x5CB8D73F, 0xEF2EB5D4, eSkillPassive::高级偷袭tx, { eSkillPassive::偷袭tx }, "高级偷袭", "99%免疫反震反击" },
	{ 0xE2C478F8, 0x087AB3EA, eSkillPassive::毒d, { /*ePassiveSkill::高级毒d*/ }, "毒", "攻击时有10%几率使对手中毒" },
	{ 0x40BE8F5E, 0x23205169, eSkillPassive::高级毒d, { eSkillPassive::毒d }, "高级毒", "攻击时有20%几率使对手中毒" },
	{ 0x7BD73DE0, 0x18CC6B26, eSkillPassive::驱鬼qg, { /*ePassiveSkill::高级驱鬼qg*/ }, "驱鬼", "对有鬼魂术的目标伤害+50%" },
	{ 0xCBCF6BE3, 0x04512FE2, eSkillPassive::高级驱鬼qg, { eSkillPassive::驱鬼qg }, "高级驱鬼", "对有鬼魂术的目标伤害+100%" },
	{ 0xFEE50FAB, 0x307CF1BE, eSkillPassive::鬼魂术gh, { eSkillPassive::神佑复生sy, eSkillPassive::高级神佑复生sy }, "鬼魂术", "免疫异常状态,死后7回合复活" },
	{ 0xD3794A73, 0x913D7735, eSkillPassive::高级鬼魂术gh, { eSkillPassive::鬼魂术gh, eSkillPassive::神佑复生sy, eSkillPassive::高级神佑复生sy }, "高级鬼魂术", "免疫异常状态,死后5回合复活" },
	{ 0x87C81C63, 0x2AD5089A, eSkillPassive::魔之心mz, { /*ePassiveSkill::高级魔之心mz*/ }, "魔之心", "法术伤害+10%" },
	{ 0xAB67DBAB, 0x9A24567A, eSkillPassive::高级魔之心mz, { eSkillPassive::魔之心mz }, "高级魔之心", "法术伤害+20%" },
	{ 0xAF7442C5, 0x54037CFF, eSkillPassive::神佑复生sy, { /*ePassiveSkill::高级神佑复生sy*/ }, "神佑复生", "死亡时有20%几率复活60%气血" },
	{ 0xB5CA5D93, 0x799E08CE, eSkillPassive::高级神佑复生sy, { eSkillPassive::神佑复生sy }, "高级神佑复生", "死亡时有35%几率复活满血" },
	{ 0xA6DFC207, 0xF6E0F4C0, eSkillPassive::精神集中js, { /*ePassiveSkill::高级精神集中js*/ }, "精神集中", "10%抵抗异常" },
	{ 0x8EB9B230, 0xBA10735B, eSkillPassive::高级精神集中js, { eSkillPassive::精神集中js }, "高级精神集中", "20%抵抗异常" },
	{ 0xB2F61506, 0xC763E399, eSkillPassive::否定信仰fd, { /*ePassiveSkill::高级否定信仰fd*/ }, "否定信仰", "击败敌人时,对方神佑率下降15%" },
	{ 0x9204C942, 0x1CE3C56D, eSkillPassive::高级否定信仰fd, { eSkillPassive::否定信仰fd }, "高级否定信仰", "击败敌人时,对方神佑率下降25%" },
	{ 0x149AB0A5, 0x83251A3C, eSkillPassive::法术连击fs, { /*ePassiveSkill::高级法术连击fs*/ }, "法术连击", "法术15%的几率连击" },
	{ 0x70B62C09, 0xCFB487A4, eSkillPassive::高级法术连击fs, { eSkillPassive::法术连击fs }, "高级法术连击", "法术25%的几率连击" },
	{ 0x4210A339, 0x52D97379, eSkillPassive::法术暴击fs, { /*ePassiveSkill::高级法术暴击fs*/ }, "法术暴击", "法术10%的几率暴击" },
	{ 0x610B7489, 0x7B7E1F49, eSkillPassive::高级法术暴击fs, { eSkillPassive::法术暴击fs }, "高级法术暴击", "法术15%的几率暴击" },
	{ 0x0FF374D8, 0x2D6EE6B5, eSkillPassive::法术波动fs, { /*ePassiveSkill::高级法术波动fs*/ }, "法术波动", "100-110%" },
	{ 0xDAAF4328, 0x8A6FD1EC, eSkillPassive::高级法术波动fs, { eSkillPassive::法术波动fs }, "高级法术波动", "100-120%" },
	{ 0xB2F61506, 0xE861CC5D, eSkillPassive::迟钝cd, { eSkillPassive::敏捷mj, eSkillPassive::高级敏捷mj}, "迟钝", "速度-50%" },
	{ 0x105F0207, 0x9C1EEE54, eSkillPassive::高级迟钝cd, { eSkillPassive::迟钝cd, eSkillPassive::敏捷mj, eSkillPassive::高级敏捷mj }, "高级迟钝", "速度-80%" },

	{ 0xEEC21546, 0x5C279D6E, eSkillPassive::弱点火rd, { eSkillPassive::火属性吸收hs, eSkillPassive::高级火属性吸收hs }, "弱点火", "受到火属性攻击伤害+50%" },
	{ 0x4267A335, 0x2FEC0881, eSkillPassive::弱点水rd, { eSkillPassive::水属性吸收ss, eSkillPassive::高级水属性吸收ss}, "弱点水", "受到水属性攻击伤害+50%" },
	{ 0x36438B51, 0x853524D8, eSkillPassive::弱点土rd, { eSkillPassive::土属性吸收ts, eSkillPassive::高级土属性吸收ts}, "弱点土", "受到土属性攻击伤害+50%" },
	{ 0x9B4F6936, 0xAC0696AE, eSkillPassive::弱点雷rd, { eSkillPassive::雷属性吸收ls, eSkillPassive::高级雷属性吸收ls}, "弱点雷", "受到雷属性攻击伤害+50%" },
	{ 0xC58CA678, 0xA71D860C, eSkillPassive::雷属性吸收ls, { /*ePassiveSkill::高级雷属性吸收ls*/ }, "雷属性吸收", "受到雷属性攻击20%吸收伤害" },
	{ 0x0723D081, 0x629C475E, eSkillPassive::高级雷属性吸收ls, { eSkillPassive::雷属性吸收ls }, "高级雷属性吸收", "受到雷属性攻击30%吸收伤害" },
	{ 0xD0CD6B99, 0x0801A3EA, eSkillPassive::土属性吸收ts, { /*ePassiveSkill::高级土属性吸收ts*/ }, "土属性吸收", "受到土属性攻击20%吸收伤害" },
	{ 0x2CD0288C, 0x9D518016, eSkillPassive::高级土属性吸收ts, { eSkillPassive::土属性吸收ts }, "高级土属性吸收", "受到土属性攻击30%吸收伤害" },
	{ 0xF3EDE679, 0xF442D468, eSkillPassive::火属性吸收hs, { /*ePassiveSkill::高级火属性吸收hs*/ }, "火属性吸收", "受到火属性攻击20%吸收伤害" },
	{ 0x50118271, 0xACBCC108, eSkillPassive::高级火属性吸收hs, { eSkillPassive::火属性吸收hs }, "高级火属性吸收", "受到火属性攻击30%吸收伤害" },
	{ 0x68B24211, 0x0584205F, eSkillPassive::水属性吸收ss, { /*ePassiveSkill::高级水属性吸收ss*/ }, "水属性吸收", "受到水属性攻击20%吸收伤害" },
	{ 0x4E36441F, 0x96F0C044, eSkillPassive::高级水属性吸收ss, { eSkillPassive::水属性吸收ss }, "高级水属性吸收", "受到水属性攻击30%吸收伤害" },
	{ 0x00000000, 0x04B409B4, eSkillPassive::盾气dq, { /*ePassiveSkill::高级盾气dq*/ }, "盾气", "进入战斗临时增加等级*1的防御,持续5回合且递减" },
	{ 0x00000000, 0x8EC237B5, eSkillPassive::高级盾气dq, { eSkillPassive::盾气dq }, "高级盾气", "进入战斗临时增加等级*2的防御,持续5回合且递减" },
	{ 0x00000000, 0x3EDD86F8, eSkillPassive::法术抵抗fs, { /*ePassiveSkill::高级法术抵抗fs*/ }, "法术抵抗", "受到法术伤害-15%" },
	{ 0x00000000, 0xE8FD17ED, eSkillPassive::高级法术抵抗fs, { eSkillPassive::法术抵抗fs }, "高级法术抵抗", "受到法术伤害-25%" },
	{ 0x00000000, 0xA94D8FEA, eSkillPassive::合纵hz, { /*ePassiveSkill::高级合纵hz*/ }, "合纵", "攻击无视对方4%防御" },
	{ 0x00000000, 0x4EAD21FF, eSkillPassive::高级合纵hz, { eSkillPassive::合纵hz }, "高级合纵", "攻击无视对方8%防御" },


	{ 0x00000000, 0x5886F7D3, eSkillPassive::移花接木yh, {}, "移花接木", "暗器伤害-99%" },
	{ 0x00000000, 0xDEF6EAF8, eSkillPassive::灵能激发ln, {}, "灵能激发", "进入战斗临时增加等级*1的灵力,持续5回合且递减" },
	{ 0x00000000, 0xC3F4BC0D, eSkillPassive::嗜血追击sx, {}, "嗜血追击", "目标死亡后追加攻击另一个目标" },
	// 盾气 法术抵抗 合纵
	{ 0x00000000, 0x87FC2C8A, eSkillPassive::法力陷阱fl, {}, "法力陷阱", "30%反弹25%的法术伤害" },
	// 雷击
	// 0xE52A8168
	{ 3844768104, 0xE52A8168, eSkillPassive::浮云神马fy, {}, "浮云神马", "在场时提高自身和主人10%速度5回合" },
	// 法术防御 善恶 壁垒
	{ 0x00000000, 0xC6724A1D, eSkillPassive::苍穹怒击cq, {}, "苍穹怒击", "必杀或连击时,随机追击另一目标,每回合最多触发一次" },
	// 空间震(无畏布施)  大蛇(天降灵葫)
	{ 0x00000000, 0x4BB2CD64, eSkillPassive::须弥真言xm, {}, "须弥真言", "增加魔力*0.4的法术伤害" },
	{ 0x00000000, 0x7FFF65B8, eSkillPassive::从天而降ct, {}, "从天而降", "增加普通攻击时造成的伤害,但有可能腾空失败" },
	// 月光
	{ 0x00000000, 0xDFCC02E3, eSkillPassive::灵山禅语ls, {}, "灵山禅语", "牺牲法术伤害,增加魔力*1的法防" },
	{ 0x00000000, 0xFF01A989, eSkillPassive::千钧一怒qj, {}, "千钧一怒", "普通攻击造成的伤害>=气血10%,自己的主人会获得10点愤怒" },
	{ 0x00000000, 0x230CEC5B, eSkillPassive::龙魂lh, {}, "龙魂", "每三次成功使用法术都会增加自身法术伤害" },
	{ 0x00000000, 0x4E3C17E0, eSkillPassive::大快朵颐dk, {}, "大快朵颐", "普通攻击时有几率提高连击和必杀的概率" },
};



static const std::vector<sSkillFuzhu> s_skillFuzhus =
{
	// 辅助
	{ 0x6F838C3B, 0x9285D9EB, eSkillFuzhu::强壮, "强壮", "每级+5点HP上限" },
	{ 0x2BB02FD3, 0xD6750E0D, eSkillFuzhu::强身术, "强身术", "每级加1%的气血上限" },
	{ 0x35D2CD77, 0x05CA3AA8, eSkillFuzhu::冥想, "冥想", "每级加1%的魔法上限" },
	{ 0x57D857C0, 0x7D3C4887, eSkillFuzhu::暗器技巧, "暗器技巧", "每级暗器伤害+1%" },
	{ 0x617743DB, 0xE67220ED, eSkillFuzhu::打造技巧, "打造技巧", "造武器时的人品上升" },
	{ 0x68D513E9, 0x3FE32FC2, eSkillFuzhu::裁缝技巧, "裁缝技巧", "造衣服时的人品上升" },
	{ 0x13E6F3B0, 0x4EF982E4, eSkillFuzhu::炼金术, "炼金术", "造项链,鞋子,腰带时,人品上升" },
	{ 0x2649EAD5, 0xE72ED95F, eSkillFuzhu::中药医理, "中药医理", "可以制作药物" },
	{ 0xE172DE46, 0x785A800E, eSkillFuzhu::烹饪技巧, "烹饪技巧", "可以制作烹饪" },
	{ 0x6C81040C, 0x476CFC92, eSkillFuzhu::逃离技巧, "逃离技巧", "每级+1%的逃跑成功率" },
	{ 0x35C9EAD4, 0x075D782F, eSkillFuzhu::追捕技巧, "追捕技巧", "每级敌人的逃跑成功率-1%" },
	{ 0x6179CA67, 0x39BF36FD, eSkillFuzhu::养生之道, "养生之道", "每级+5点活力上限" },
	{ 0xBC31F555, 0xD5F04CC0, eSkillFuzhu::健身术, "健身术", "每级+5点体力上限" },
	// 剧情
	{ 0xE9D07953, 0x43CBAF9C, eSkillFuzhu::火眼金睛, "火眼金睛", "" },
	{ 0x61197BD5, 0x93EAB2C8, eSkillFuzhu::丹元济会, "丹元济会", "" },
	{ 0x55CD16AC, 0x8466E376, eSkillFuzhu::妙手空空, "妙手空空", "" },
	{ 0x03B593E3, 0x70FB3A0E, eSkillFuzhu::召唤兽图鉴, "召唤兽图鉴", "" },
	{ 0x3F7B9F82, 0x5A2821B8, eSkillFuzhu::变化咒, "变化咒", "" },
	{ 0x20D43900, 0xDF55F6EF, eSkillFuzhu::梦幻卡牌, "梦幻卡牌", "" },
	{ 0xCB9C5ECC, 0x58F2DDB8, eSkillFuzhu::小试牛刀, "小试牛刀", "" },
	{ 0xC0F1CE88, 0x59EDC2D6, eSkillFuzhu::猜拳, "猜拳", "" },
	{ 0xB6FAD6C9, 0x59FEE007, eSkillFuzhu::五子棋, "五子棋", "" },
	{ 0xE588745D, 0xDB84A5CB, eSkillFuzhu::装备图鉴, "装备图鉴", "" },
	{ 0x2E8A8A30, 0x135FA17A, eSkillFuzhu::熔炼技巧, "熔炼技巧", "" },
	{ 0x72DE84DF, 0x46B9DE47, eSkillFuzhu::灵石技巧, "灵石技巧", "" },
	{ 0x4D48EC9A, 0xB490C429, eSkillFuzhu::巧匠之术, "巧匠之术", "" },
	{ 0x6AAEF804, 0x0D167BFB, eSkillFuzhu::古董评估, "古董评估", "" },
	{ 0x9F2DFDB6, 0x16418D92, eSkillFuzhu::建筑之术, "建筑之术", "" },
	{ 0x47877A93, 0x25064DE5, eSkillFuzhu::仙灵店铺, "仙灵店铺", "" },
	// 坐骑
	{ 0x3FC666BA, 0x00000000, eSkillFuzhu::破釜沉舟, "破釜沉舟", "" },
	{ 0x2D685412, 0x00000000, eSkillFuzhu::开天辟地, "开天辟地", "" },
	{ 0x077F08D1, 0x00000000, eSkillFuzhu::正身清心, "正身清心", "" },
	{ 0x497B7159, 0x00000000, eSkillFuzhu::延年益寿, "延年益寿", "" },
	{ 0x624C7E94, 0x00000000, eSkillFuzhu::金刚护身, "金刚护身", "" },
	{ 0x6A4612D6, 0x00000000, eSkillFuzhu::忠贯日月, "忠贯日月", "" },
	{ 0x83A054A5, 0x00000000, eSkillFuzhu::炫火乱舞, "炫火乱舞", "" },
	{ 0xA2572FFC, 0x00000000, eSkillFuzhu::乾坤借速, "乾坤借速", "" },
	{ 0xD1EBF7E3, 0x00000000, eSkillFuzhu::水来土掩, "水来土掩", "" },
	{ 0xD3236E57, 0x00000000, eSkillFuzhu::飞火流星, "飞火流星", "" },
	{ 0xE2296705, 0x00000000, eSkillFuzhu::大浪淘沙, "大浪淘沙", "" },
	{ 0xF0F2E8F1, 0x00000000, eSkillFuzhu::铜墙铁壁, "铜墙铁壁", "" },
};




static const std::vector<ctt::sSkill> s_skills = 
{
	{ 0x94BFA7D9, 0xC6E68077, 0x0E30CD44, 0x00000000, 0xDDD270F5, eSkill::雷击, eSkillUse::BattleOther, eBuff::None, 30, 0, "雷击", "单体雷属性法术", "30MP" },
	{ 0xDA8731E8, 0xAA631753, 0xF54C4025, 0x00000000, 0x040584F3, eSkill::奔雷咒, eSkillUse::BattleOther, eBuff::None, 30, -10, "奔雷咒", "多人雷属性法术", "MPS" },
	{ 0x11F08BC1, 0xFBEEDD94, 0x0AC30DE6, 0x00000000, 0x564F1090, eSkill::落岩, eSkillUse::BattleOther, eBuff::None, 30, -10, "落岩", "单体土属性法术", "30MP" },
	{ 0xFD4BCB54, 0x1BA20D9E, 0x783F9D20, 0x00000000, 0x22FEF25E, eSkill::泰山压顶, eSkillUse::BattleOther, eBuff::None, 30, 0, "泰山压顶", "多人土属性法术", "MPS" },
	{ 0x8FF8B5C0, 0x0511E729, 0xF933209B, 0x00000000, 0x0071B681, eSkill::水攻, eSkillUse::BattleOther, eBuff::None, 30, -10, "水攻", "单体水属性法术", "30MP" },
	// 0x97311BAD
	{ 0xE6883491, 0x9D368B02, 0x18967984, 0x00000000, 0x4F09C15D, eSkill::水漫金山, eSkillUse::BattleOther, eBuff::None, 30, 0, "水漫金山", "多人水属性法术", "MPS" },
	{ 0x636DADB0, 0xB0CBEBBF, 0xD112913D, 0x00000000, 0x3E2A375C, eSkill::烈火, eSkillUse::BattleOther, eBuff::None, 30, -10, "烈火", "单体火属性法术", "30MP" },
	{ 0xB55E9384, 0xFBBBE334, 0x139426B5, 0x00000000, 0x2E88DCF4, eSkill::地狱烈火, eSkillUse::BattleOther, eBuff::None, 30, 0, "地狱烈火", "多人火属性法术", "MPS" },
	{ 0x1671DDFD, 0x1C22C610, 0x3BA4B993, 0x00000000, 0x675E4E20, eSkill::惊心一剑, eSkillUse::BattleOther, eBuff::None, 30, 0, "惊心一剑", "攻击并扣篮", "30MP" },
	{ 0x6D382036, 0x1719FC84, 0xF18C76DD, 0x00000000, 0x9609FDF4, eSkill::夜舞倾城, eSkillUse::BattleOther, eBuff::None, 10, -10, "夜舞倾城", "广场舞的杀伤力", "CostLv" },
	// 0x19182964
	{ 0xFF0E4570, 0x48A24731, 0x4E02EC44, 0x2C6223D4, 0x739A0BAB, eSkill::死亡召唤, eSkillUse::BattleOther, eBuff::None, 10, 0, "死亡召唤", "15%使附加死亡禁锢效果", "CostLv" },
	{ 0x848155A0, 0xD88B6D52, 0xFF33B0EE, 0x00000000, 0x00000000, eSkill::力劈华山, eSkillUse::BattleOther, eBuff::None, 50, -10, "力劈华山", "伤害低你就惨了", "" },
	{ 0x00000000, 0x63770E47, 0x729ADE62, 0x00000000, 0x0504D379, eSkill::剑荡四方, eSkillUse::BattleOther, eBuff::None, 10, 0, "剑荡四方", "小浪涌", "CostHp" },
	{ 0x2513128B, 0x3543B96C, 0x00000000, 0xDEDEE983, 0x00000000, eSkill::法术防御, eSkillUse::BattleSelf, eBuff::Good, 10, 0, "法术防御", "受到法术伤害-65%", "CostLv" },
	{ 0x71267227, 0x263B68C3, 0x8D8A818D, 0x00000000, 0x2174467F, eSkill::善恶有报, eSkillUse::BattleOther, eBuff::None, 10, 0, "善恶有报", "不是不报时候未到", "CostLv" },
	{ 0x00000000, 0xF1D5925A, 0x99DDC32A, 0x00000000, 0x0504D379, eSkill::壁垒击破, eSkillUse::BattleOther, eBuff::None, 10, 0, "壁垒击破", "防御你就惨了", "CostLv" },
// 	{ 0x00000000, 0xC6724A1D, 0x00000000, 0x00000000, 0x43B4478D, eSkill::苍鸾怒击, eSkillUse::BattleOther, eBuff::None, 0, 0, "苍鸾怒击", "物理伤害*200%", "等级+10MP" },
// 	{ 0xDB2E1256, 0xDE58924A, 0x911E3921, 0x00000000, 0x564F1090, eSkill::迷你空间震, eSkillUse::BattleOther, eBuff::Good, 0, -10, "迷你空间震", "无视全部灵力", "等级+10MP" },
// 	{ 0xDB2E1256, 0xDE58924A, 0x3200B6CC, 0x00000000, 0x752FFCAB, eSkill::大蛇破坏光线, eSkillUse::BattleOther, eBuff::Bad, 0, 0, "大蛇破坏光线", "物理伤害*200%", "等级+100MP" },
// 	{ 0x00000000, 0x4BB2CD64, 0x00000000, 0x00000000, 0x00000000, eSkill::须弥真言, eSkillUse::None, eBuff::None, 0, 0, "须弥真言", "须弥圣言,佛光涤罪", "" },
// 	{ 0x00000000, 0x7FFF65B8, 0x00000000, 0x00000000, 0x00000000, eSkill::从天而降, eSkillUse::None, eBuff::None, 0, 0, "从天而降", "增加普通攻击时造成的伤害,但有可能腾空失败", "" },
	{ 0x00000000, 0x35C47AF8, 0xFB90D9B1, 0x2F3E4271, 0x1353874F, eSkill::无畏布施, eSkillUse::BattleOwnerButSelf, eBuff::None, 50, 10, "无畏布施", "增加目标的防御和法防3回合,但会降低自身的防御和法防", "CostLv" },
	{ 0x00000000, 0x5BCBB249, 0xDCD7A875, 0x00000000, 0x00000000, eSkill::天降灵葫, eSkillUse::BattleOther, eBuff::None, 30, -10, "天降灵葫", "随机攻击1-5个目标", "CostLv" },
	{ 0x00000000, 0xCB238CFE, 0x28DC0E4B, 0x00000000, 0x9609FDF4, eSkill::月光, eSkillUse::BattleOther, eBuff::None, 10, -10, "月光", "代表月亮消灭你", "CostLv" },
	{ 0x00000000, 0x00000000, 0x35AA81A7, 0x00000000, 0x00000000, eSkill::吸星大法xx, eSkillUse::BattleOther, eBuff::None, 10, 0, "吸星大法", "吸干你", "CostLv" },

	{ 0x35F72F87, 0x0A71DEE7, 0xF3B31E4E, 0x00000000, 0x53E82E61, eSkill::气疗术, eSkillUse::BattleOwner, eBuff::None, 30, 0, "气疗术", "单体恢复(上限3%+200)的气血", "20" },
	{ 0xFD3187C7, 0x73735CAC, 0xFBF89980, 0x00000000, 0xE6339003, eSkill::心疗术, eSkillUse::BattleOwner, eBuff::None, 60, 0, "心疗术", "单体恢复(上限6%+400)的气血", "30" },
	{ 0x48650DE3, 0x8AB448F6, 0xF3B31E4E, 0x00000000, 0x53E82E61, eSkill::命疗术, eSkillUse::BattleOwner, eBuff::None, 90, 0, "命疗术", "单体恢复(上限9%+600)的气血", "40" },
	// 0x3240F0D4 好丑
	{ 0xFC3656C8, 0x852E36F5, 0x899241C3, 0x00000000, 0x4B800708, eSkill::凝气诀, eSkillUse::BattleOwner, eBuff::None, 60, -10, "凝气诀", "单体恢复(上限10%+150)的魔法", "50" },
	{ 0xD63AE21B, 0xB36F0828, 0x7EE33126, 0x00000000, 0x4B800708, eSkill::凝神诀, eSkillUse::BattleOwner, eBuff::None, 90, 0, "凝神诀", "单体恢复(上限15%+240)的魔法", "60" },
	{ 0x598125FD, 0x67F2A70E, 0xD077C3A0, 0x00000000, 0x53E82E61, eSkill::气归术, eSkillUse::BattleSelf, eBuff::None, 60, 0, "气归术", "自身恢复1/4的气血", "30" },
	{ 0x4DCB689E, 0x9A1985E8, 0x30F2B60C, 0x00000000, 0x53E82E61, eSkill::命归术, eSkillUse::BattleSelf, eBuff::None, 130, 0, "命归术", "自身恢复1/2的气血", "60" },
	{ 0x8574CDF1, 0x78276F30, 0xD077C3A0, 0x00000000, 0x04E42236, eSkill::四海升平, eSkillUse::BattleOwner, eBuff::None, 135, 0, "四海升平", "全体恢复1/4的气血", "108" },
	{ 0x97838895, 0xE364BF7C, 0x8E92AE82, 0x00000000, 0x97283C40, eSkill::回魂咒, eSkillUse::BattleOwner, eBuff::None, 100, -10, "回魂咒", "单体复活并恢复150气血", "64" },
	{ 0xC3793063, 0x83797F7C, 0x8E92AE82, 0x00000000, 0x97283C40, eSkill::起死回生, eSkillUse::BattleOwner, eBuff::None, 120, -10, "起死回生", "单体复活并恢复1/2的气血", "96" },
	{ 0x85097919, 0x76847896, 0x17238B9F, 0x00000000, 0xE6339003, eSkill::水清诀, eSkillUse::BattleOwner, eBuff::None, 50, -10, "水清诀", "单体解除异常状态", "40" },
	{ 0x3B44EE0A, 0xFE796634, 0x17238B9F, 0x00000000, 0xE6339003, eSkill::冰清诀, eSkillUse::BattleOwner, eBuff::None, 100, -10, "冰清诀", "单体解除异常状态并恢复1/4的气血", "64" },
	{ 0x3F79D19F, 0x8A21BA6C, 0x17238B9F, 0x00000000, 0xFBD946FB, eSkill::玉清诀, eSkillUse::BattleOwner, eBuff::None, 125, -10, "玉清诀", "全体解除异常状态", "80" },
	{ 0x82297D26, 0xF81CEDEA, 0x66150076, 0x00000000, 0xFBD946FB, eSkill::晶清诀, eSkillUse::BattleOwner, eBuff::None, 150, -10, "晶清诀", "全体解除异常状态并恢复15%的气血", "120" },
	{ 0x1FFC5C36, 0x6344D17A, 0x00000000, 0x00000000, 0xA0F588C2, eSkill::空位1, eSkillUse::None, eBuff::None, 75, 0, "空位", "	空 ", "75" },
	{ 0x03DF530E, 0x66D173C9, 0x00000000, 0x00000000, 0xA0F588C2, eSkill::空位2, eSkillUse::None, eBuff::None, 40, 0, "空位", "	空", "40" },
// 	{ 0x1FFC5C36, 0x6344D17A, 0x00000000, 0x00000000, 0xA0F588C2, eSkill::诅咒之伤, eSkillUse::BattleOther, eBuff::None, 40, 0, "诅咒之伤", "单体减少敌方20%气血", "75" },
// 	{ 0x03DF530E, 0x66D173C9, 0x00000000, 0x00000000, 0xA0F588C2, eSkill::诅咒之亡, eSkillUse::BattleOther, eBuff::None, 40, 0, "诅咒之亡", "单体减少敌方20%魔法", "40" },

	{ 0x97A6B22C, 0x17D8A907, 0x5DE57BA4, 0x00000000, 0xCE582B31, eSkill::笑里藏刀, eSkillUse::BattleOther, eBuff::None, 40, 0, "笑里藏刀", "单体减少敌方70点愤怒", "32" },
	{ 0x172AE1E0, 0x480A8A7D, 0x5DE57BA4, 0x00000000, 0x245321A8, eSkill::绝幻魔音, eSkillUse::BattleOther, eBuff::None, 60, 0, "绝幻魔音", "全体减少敌方20点愤怒", "70" },
	{ 0xB7458413, 0x41A28BC6, 0x203B8C75, 0x00000000, 0x019B0A72, eSkill::野兽之力, eSkillUse::BattleOwner, eBuff::None, 40, -10, "野兽之力", "单体攻+10%持续到战斗结束", "40" },
	{ 0xF77F8F63, 0x6C8D9D7E, 0x203B8C75, 0x00000000, 0x019B0A72, eSkill::魔兽之印, eSkillUse::BattleOwner, eBuff::None, 70, -10, "魔兽之印", "全体攻+5%持续到战斗结束", "70" },
	{ 0xA7BB3439, 0x85849B5B, 0x38FD76EA, 0x00000000, 0x245321A8, eSkill::光辉之甲, eSkillUse::BattleOwner, eBuff::None, 40, 0, "光辉之甲", "单体防+10%持续到战斗结束", "40" },
	{ 0xA767CFAB, 0x185C7768, 0x38FD76EA, 0x00000000, 0x245321A8, eSkill::圣灵之甲, eSkillUse::BattleOwner, eBuff::None, 70, 0, "圣灵之甲", "全体防+5%持续到战斗结束", "70" },
	{ 0xA85146A6, 0x9715FA32, 0xFE27EBCF, 0x00000000, 0xBF36842D, eSkill::流云诀, eSkillUse::BattleOwner, eBuff::None, 40, -10, "流云诀", "单体速+10%持续到战斗结束", "40" },
	{ 0x96370902, 0x6812F03B, 0xFE27EBCF, 0x00000000, 0xBF36842D, eSkill::啸风诀, eSkillUse::BattleOwner, eBuff::None, 70, -10, "啸风诀", "全体速+5%持续到战斗结束", "70" },
	{ 0x3CA34035, 0xCA17D132, 0x9B23F38E, 0x5C5C1544, 0x3BF3590C, eSkill::太极护法, eSkillUse::BattleSelf, eBuff::None, 90, 0, "太极护法", "自身受到的法术伤害减半 3回合", "20" },
	{ 0xCC019475, 0x61F085F4, 0x9B23F38E, 0x5C5C1544, 0x3BF3590C, eSkill::罗汉金钟, eSkillUse::BattleOwner, eBuff::None, 150, 0, "罗汉金钟", "全体受到的法术伤害减半 3回合", "120" },
	{ 0x14FF0C1F, 0xA0830D94, 0x95065313, 0x547C4B68, 0x1A67E919, eSkill::修罗咒, eSkillUse::BattleOwner, eBuff::None, 120, 0, "修罗咒", "	单体反弹50%的伤害3回合", "20" },
	{ 0x76F6DD9E, 0x68F4FE2B, 0xC183DB1E, 0xFAF4A2D4, 0x40701F91, eSkill::天衣无缝, eSkillUse::BattleOwner, eBuff::None, 80, -10, "天衣无缝", "法术躲避率+50% 5回合", "80" },
	{ 0x1A4D1A72, 0xDA23CB44, 0x81B4599F, 0x00000000, 0x426F46C8, eSkill::放下屠刀, eSkillUse::BattleOther, eBuff::None, 30, -10, "放下屠刀", "单体攻-10%持续到战斗结束", "40" },
	{ 0x52CE6E52, 0xF7A055FD, 0x81B4599F, 0x00000000, 0x426F46C8, eSkill::河东狮吼, eSkillUse::BattleOther, eBuff::None, 70, -10, "河东狮吼", "	全体攻-5%,持续到战斗结束", "70" },
	{ 0x2CD374B0, 0x5460F163, 0xD0EEC915, 0x00000000, 0x70F1E396, eSkill::破甲术, eSkillUse::BattleOther, eBuff::None, 35, 0, "破甲术", "单体防-10%持续到战斗结束", "40" },
	{ 0x2CD374B0, 0x5460F163, 0xD0EEC915, 0x00000000, 0x70F1E396, eSkill::碎甲术, eSkillUse::BattleOther, eBuff::None, 80, 0, "碎甲术", "全体防-5%,持续到战斗结束", "70" },
	{ 0x264D9AC8, 0x8FF3DB32, 0xD1E593CE, 0x00000000, 0x70F1E396, eSkill::凝滞术, eSkillUse::BattleOther, eBuff::None, 35, -10, "凝滞术", "单体速-10%持续到战斗结束", "40" },
	{ 0x5E68270E, 0x79619181, 0xD1E593CE, 0x00000000, 0x70F1E396, eSkill::停陷术, eSkillUse::BattleOther, eBuff::None, 80, -10, "停陷术", "全体速-5%,持续到战斗结束", "70" },
	{ 0x1373420F, 0xFD99EDE1, 0x171544B2, 0x00000000, 0x4B800708, eSkill::破血狂攻, eSkillUse::BattleOther, eBuff::None, 80, 0, "破血狂攻", "二连击", "64" },
	{ 0x7F545B30, 0xF68EB551, 0xB1822745, 0x00000000, 0x4B800708, eSkill::弱点击破, eSkillUse::BattleOther, eBuff::None, 50, 0, "弱点击破", "忽防攻击", "20" },
	{ 0x896AAEED, 0x59DBD730, 0x00000000, 0x00000000, 0x00000000, eSkill::空位3, eSkillUse::None, eBuff::None, 50, 0, "空", "	 空", "50" },
	{ 0x8A479938, 0xB1392BC1, 0x00000000, 0x00000000, 0x00000000, eSkill::空位4, eSkillUse::None, eBuff::None, 80, 0, "空", "	 空", "80" },
	{ 0x51522BBB, 0x77A7C11E, 0x33084AA4, 0x00000000, 0x00000000, eSkill::星杯圣域, eSkillUse::BattleOwner, eBuff::None, 120, 0, "星杯圣域", "	全体完全防御两次攻击", "120" },
	{ 0xF572DAB6, 0x356E1001, 0x4F116543, 0x00000000, 0x00000000, eSkill::命疗术EX, eSkillUse::BattleOwner, eBuff::None, 40, 0, "命疗术EX", "	单体恢复（上限12%+1000）的气血", "40" },
	{ 0xCC73C4CE, 0x1D81410E, 0x21FAE73F, 0x00000000, 0x00000000, eSkill::破碎无双, eSkillUse::BattleOther, eBuff::None, 80, 0, "破碎无双", "单体攻击并减少对方MP", "50" },
	{ 0x4607A98E, 0xCD0B7124, 0x00000000, 0x00000000, 0x00000000, eSkill::空位5, eSkillUse::None, eBuff::None, 70, 0, "空", "	 空", "70" },
	{ 0xD339140A, 0x76FDA5AC, 0x00000000, 0x00000000, 0x4B800708, eSkill::破血狂攻2, eSkillUse::BattleOther, eBuff::None, 64, 0, "破血狂攻2", "	单体三连击", "64" },
	{ 0xA3D648B0, 0xFB726757, 0x00000000, 0x00000000, 0x4B800708, eSkill::弱点击破EX, eSkillUse::BattleOther, eBuff::None, 80, 0, "弱点击破EX", "	单体无视防御攻击", "80" },
	{ 0x230AF78C, 0x044670C7, 0x00000000, 0x00000000, 0x4B800708, eSkill::破血狂攻EX, eSkillUse::BattleOther, eBuff::None, 80, 0, "破血狂攻EX", "	单体四连击", "80" },
	{ 0x17C3EF40, 0x613B61A6, 0x00000000, 0x00000000, 0x104B1B46, eSkill::空位6, eSkillUse::None, eBuff::None, 70, 0, "空", "	空", "70" },
	{ 0x9908B56E, 0x7635E819, 0xF224F08A, 0x00000000, 0x00000000, eSkill::大地之墙, eSkillUse::BattleOwner, eBuff::None, 100, 0, "大地之墙", "	全体完全防御一次攻击", "100" },
	{ 0xCB65301D, 0xC352DA37, 0x1ADABFA6, 0xE43459EB, 0x40701F91, eSkill::心如明镜, eSkillUse::BattleSelf, eBuff::None, 100, 0, "心如明镜", "物理和法术防御+50%,去除一切异常", "100" },
	{ 0x8521B2B4, 0x5F4E6740, 0xE1084D39, 0x00000000, 0x00000000, eSkill::慈航普渡, eSkillUse::BattleOwner, eBuff::None, 150, -10, "慈航普渡", "全体满血复活", "120" },
	{ 0x918FB1D3, 0x3E505980, 0x95473D14, 0x00000000, 0x00000000, eSkill::迅疾如风, eSkillUse::BattleOwner, eBuff::None, 20, 0, "迅疾如风", "	自身提升速度,躲避", "20" },

	// 休息 0xD9463A0C
	{ 0xB0E3E18B, 0x0900C9A1, 0x19C102D1, 0x56E05B32, 0x30D78CEF, eSkill::横扫千军, eSkillUse::BattleOther, eBuff::None, 1, 0, "横扫千军", "4连击,使用后需休息1回合,HP低于5%则无法使用", "CostHpMax" },
	{ 0x424D9459, 0xE3094CF3, 968268166, 0x2A2A0663, 0x39D047A5, eSkill::后发制人, eSkillUse::BattleOther, eBuff::None, 0, 0, "后发制人", "休息一回合后临时提高伤害力,命中和速度,自动攻击目标", "" },
	{ 0xFE16E718, 0x6C23A98E, 0x00000000, 0x00000000, 0xED520CA0, eSkill::兵器谱, eSkillUse::None, eBuff::None, 0, 0, "兵器谱", "鉴定武器和衣服(右击未鉴定的装备)", "无" },
	{ 0x66668C4F, 0x00CDE78F, 0x00000000, 0x00000000, 0x04E0F4C5, eSkill::千里神行, eSkillUse::NormalSelf, eBuff::None, 10, 0, "千里神行", "传送到大唐", "5%HP" },
	{ 0x4F10E7C8, 0x63BE01CD, 0x94A5BEEC, 0x85B3D6F1, 0x00000000, eSkill::杀气诀, eSkillUse::BattleOwner, eBuff::Good, 40, 0, "杀气诀", "提升命中", "" },
	{ 0x44B0147F, 0x0262C795, 0x00000000, 0x00000000, 0x00000000, eSkill::斩龙诀, eSkillUse::None, eBuff::None, 150, -10, "斩龙诀", "克制龙宫弟子的必杀技", "无" },
	{ 0x3225863C, 0x08BFC856, 0x6B934898, 0x00000000, 0x0B2ED764, eSkill::反间之计, eSkillUse::BattleOther, eBuff::Seal, 30, 0, "反间之计", "令怪物处于混乱状态", "50MP" },
	{ 0x24E57349, 0x5E31990A, 0x19C102D1, 0x56E05B32, 0x795E59BA, eSkill::破釜沉舟, eSkillUse::BattleOther, eBuff::None, 1, 0, "破釜沉舟", "同时攻击对方三个目标,使用后需休息1回合,HP低于5%则无法使用", "CostHpMax" },
	{ 0x8368E31C, 0xBBCA9C0B, 0x25F14A5E, 0x34999043, 0x095B5FC6, eSkill::安神诀, eSkillUse::BattleSelf, eBuff::Good, 30, -10, "安神诀", "提升灵力", "30MP" },
	{ 0x3195E34C, 0x8B8E4258, 0x00000000, 0x00000000, 0x00000000, eSkill::嗜血, eSkillUse::NormalSelf, eBuff::None, 0, 0, "嗜血", "没有被使用", "无" },

	{ 0x05089B1C, 0x481EAFC6, 0x00000000, 0x00000000, 0x00000000, eSkill::三星灭魔, eSkillUse::None, eBuff::None, 150, -10, "三星灭魔", "克制魔王寨弟子的必杀技", "无" },
	{ 0x4286DDD0, 0xB8F8B6A5, 0x387C1EEB, 0x00000000, 0xDDD270F5, eSkill::五雷咒, eSkillUse::BattleOther, eBuff::None, 30, -10, "五雷咒", "单体对鬼造成2倍伤害", "30MP" },
	{ 0x6B357065, 0x6A96181C, 0x00000000, 0x00000000, 0x00000000, eSkill::飞行符, eSkillUse::NormalSelf, eBuff::None, 0, 0, "飞行符", "御纸飞行", "无" },
	{ 0x78C38F19, 0x4B9630F1, 0x00000000, 0x00000000, 0xA309D8A4, eSkill::兵解符, eSkillUse::BattleSelf, eBuff::None, 0, 0, "兵解符", "从战斗逃离成功率100%", "30MP" },
	{ 0x063EAFDB, 0xD209F99A, 0x9EC0624E, 3398426285, 0xAEABE4AC, eSkill::催眠符, eSkillUse::BattleOther, eBuff::Seal, 45, 0, "催眠符", "令对手在受到伤害前无法行动", "40MP" },
	{ 0xCB1E4D52, 0x59CD3D34, 0x091ADDC7, 3635978625, 0x9A1A2884, eSkill::失心符, eSkillUse::BattleOther, eBuff::Seal, 60, 0, "失心符", "封印法术并降低防御灵力", "40MP" },
	{ 0x795E9104, 0x5C948CFF, 0x4FB56243, 0x8B43833D, 0xF6BED451, eSkill::落魄符, eSkillUse::BattleOther, eBuff::Seal, 0, 0, "落魄符", "封魔+降20%命中", "40MP" },
	{ 0xA1343135, 0x5D26E373, 0xD4AA2F8A, 3946646209, 0xF6BED451, eSkill::失忆符, eSkillUse::BattleOther, eBuff::Seal, 50, 0, "失忆符", "令对手一定回合无法使用特技", "60MP" },
	{ 0x8F4B3740, 0x3CDC2403, 0xD4024676, 3655438388, 0xF6BED451, eSkill::追魂符, eSkillUse::BattleOther, eBuff::Seal, 0, 0, "追魂符", "封物理+降防", "60MP" },
	{ 0xC7FE7637, 0x00007856, 0x1919B112, 1214058823, 0xF6BED451, eSkill::离魂符, eSkillUse::BattleOther, eBuff::Seal, 0, 0, "离魂符", "封魔+降躲避", "40MP" },
	{ 0x8FF10842, 0x78F1ED7F, 0x7BCD8BC0, 2336457533, 0xF6BED451, eSkill::失魂符, eSkillUse::BattleOther, eBuff::Seal, 0, 0, "失魂符", "封魔+降防", "60MP" },
	{ 0x975DA9B5, 0x0A2B0270, 0xDE4E3A84, 2461182746, 0xF6BED451, eSkill::定身符, eSkillUse::BattleOther, eBuff::Seal, 60, 0, "定身符", "封印物理并降低防御灵力", "60MP" },
	{ 0xB83BDC9B, 0x936F1197, 0x517656E2, 0x00000000, 0x04E42236, eSkill::归元咒, eSkillUse::BattleSelf, eBuff::None, 20, 0, "归元咒", "消耗魔法值来补充自己的气血", "20MP" },
	{ 0xB76A6542, 0xE6A885C3, 0x517656E2, 0x00000000, 0x04E42236, eSkill::凝神术, eSkillUse::BattleSelf, eBuff::None, 20, 0, "凝神术", "消耗气血来补充自己的魔法值", "CostHpFix" },
	{ 0x784D72FE, 0xC53E6E37, 0x00000000, 0x00000000, 0x00000000, eSkill::乾天罡气, eSkillUse::None, eBuff::None, 0, 0, "乾天罡气", "没有被使用", "无" },
	{ 0x19FE3B00, 0x0441F7EC, 0x00000000, 0x00000000, 0xA309D8A4, eSkill::乙木仙遁, eSkillUse::NormalSelf, eBuff::None, 10, 0, "乙木仙遁", "传送到方寸山", "5%HP" },
	{ 0x559B2E13, 0x7D1F9844, 0x4B9ACA92, 0x00000000, 0x4644FF98, eSkill::分身术, eSkillUse::BattleSelf, eBuff::Good, 80, 0, "分身术", "增加法术躲避", "50MP" },
	// 0x84FA9FA5 符,不是甲 状态0x5525C5FB
	{ 0xBD46AEDE, 0x18E364D5, 0xCB3B68B8, 0xA5D7B0F7, 0xAEABE4AC, eSkill::碎甲符, eSkillUse::BattleOther, eBuff::Bad, 100, -10, "碎甲符", "降低多人防御和灵力", "100MP" },
	{ 0xC05584C4, 0xCF367379, 0xC1731A60, 0x00000000, 0xDDD270F5, eSkill::落雷符, eSkillUse::BattleOther, eBuff::None, 30, 0, "落雷符", "攻击3个目标,对鬼魂伤害增加", "MPS" },
	{ 0xB8C8B3C0, 0x488BFA97, 0x00000000, 0x00000000, 0x00000000, eSkill::神兵护法, eSkillUse::None, eBuff::None, 0, 0, "神兵护法", "没有被使用", "无" },

	{ 0xE98C1B53, 0xD530DA11, 0x00000000, 0x00000000, 0x00000000, eSkill::紫气东来, eSkillUse::None, eBuff::None, 0, 0, "紫气东来", "没有被使用", "无" },
	{ 0x8D8B8C6C, 0x6EAE4C8A, 0xC12C2663, 0x00000000, 0xDBB88662, eSkill::唧唧歪歪, eSkillUse::BattleOther, eBuff::None, 20, 0, "唧唧歪歪", "子曾经曰过", "MPS" },
	{ 0xBAAB7B8B, 0x5458D4F3, 0x00000000, 0x00000000, 0x00000000, eSkill::达摩护体, eSkillUse::None, eBuff::None, 0, 0, "达摩护体", "没有被使用", "无" },
	{ 0xDC94C31C, 0x1C9BA3BB, 0x04DB6C0A, 0x00000000, 0xC0A21592, eSkill::金刚护法, eSkillUse::BattleOwner, eBuff::Good, 40, 0, "金刚护法", "多人加伤害", "40的MP" },
	{ 0xAC27CC91, 0x7E6CCFA6, 0x434750DE, 0x85B3D6F1, 0xBF36842D, eSkill::韦陀护法, eSkillUse::BattleOwner, eBuff::Good, 40, -10, "韦陀护法", "多人加命中", "40的MP" },
	// 0x38C2146B 状态 916220457 
	{ 0xCDD65C55, 0x52161202, 0x9E4E9755, 0x369C6A29, 0xC0A21592, eSkill::金刚护体, eSkillUse::BattleOwner, eBuff::Good, 40, -10, "金刚护体", "多人加防御", "30*N的MP" },
	// 0xF354CCB8
	{ 0x43C01A12, 0xA8430D24, 0x93CFD0AF, 0x061869D7, 0xBF36842D, eSkill::一苇渡江, eSkillUse::BattleOwner, eBuff::Good, 40, 0, "一苇渡江", "多人加速度", "40的MP" },
	{ 0x0FDF6352, 0x5C1B5CF9, 0x203B8773, 0x00000000, 0x97283C40, eSkill::我佛慈悲, eSkillUse::BattleOwner, eBuff::None, 150, 0, "我佛慈悲", "救人", "150MP" },
	{ 0xFFA56FD1, 0x181BFB03, 0x573F92CA, 0x00000000, 0x04E42236, eSkill::推拿, eSkillUse::BothSelf, eBuff::None, 50, 0, "推拿", "自己疗伤+回血", "50MP" },
	{ 0xAACB2367, 0x9101EBA0, 0x03139F50, 0x00000000, 0x04E42236, eSkill::活血, eSkillUse::BothOwner, eBuff::None, 70, 0, "活血", "单体疗伤+回血+解毒", "40MP" },
	{ 0x84BDDC3E, 0x39E390DD, 0xEF9691F3, 0x00000000, 0x04E42236, eSkill::推气过宫, eSkillUse::BothOwner, eBuff::None, 100, 0, "推气过宫", "多人加血", "100的MP" },
	{ 0xAF367280, 0x18CD0456, 0xE869B98A, 0x00000000, 0x04E42236, eSkill::妙手回春, eSkillUse::BothOwner, eBuff::None, 80, 0, "妙手回春", "多人疗伤", "50MP" },
	// 0x28E639AA
	{ 0xF7CDB7B9, 0x79D35DAF, 0x7EEC276B, 0x00000000, 0x04E42236, eSkill::救死扶伤, eSkillUse::BothOwner, eBuff::None, 150, 0, "救死扶伤", "多人疗伤+回血", "150的MP" },
	{ 0x2091C150, 0x753893D8, 0xDE34B83E, 0x00000000, 0x57726FFB, eSkill::解毒, eSkillUse::BattleOwner, eBuff::None, 40, 0, "解毒", "解毒+疗伤+回血", "30MP" },
	{ 0xCC08B2F3, 0xB29DFB11, 0x00000000, 0x00000000, 0x084168D9, eSkill::佛门普渡, eSkillUse::NormalSelf, eBuff::None, 0, 0, "佛门普渡", "传送到化生寺", "5%HP" },
	{ 0x65C3D529, 0x43B4E620, 0xF0CE9045, 0x00000000, 0xCE259E8C, eSkill::舍生取义, eSkillUse::BattleOwner, eBuff::None, 150, -10, "舍生取义", "将目标当前气血恢复到满,每次使用降低自身5%防御,3%灵力", "150MP" },
	{ 0xB8C91B23, 0x884BB7B5, 0xC8011EF1, 3930943562, 0x3E128ADA, eSkill::佛法无边, eSkillUse::BattleOwner, eBuff::Good, 150, -10, "佛法无边", "单体加法术连击率", "150MP" },
	{ 0xA95C700C, 0x0A9B60DA, 0x00000000, 0x00000000, 0x00000000, eSkill::拈花妙指, eSkillUse::None, eBuff::None, 0, 0, "拈花妙指", "没有被使用", "无" },

	{ 0x68C68B02, 0x20A5F3D0, 0x00000000, 0x00000000, 0x00000000, eSkill::红袖添香, eSkillUse::None, eBuff::None, 0, 0, "红袖添香", "没有被使用", "无" },
	{ 0x38C7C348, 0xE5042C42, 0x182CE63B, 0x72AD6DBA, 0xBDCD9588, eSkill::楚楚可怜, eSkillUse::BattleSelf, eBuff::Good, 30, -10, "楚楚可怜", "停止行动并保护自己免受伤害", "100MP" },
	{ 0x662EFA99, 0x875525A2, 0x9D5F7277, 0xDBCEE32C, 0xC99B2900, eSkill::满天花雨, eSkillUse::BattleOther, eBuff::Poison, 40, -10, "满天花雨", "攻击几率中毒", "50MP" },
	{ 0x935E99ED, 0x712996D6, 0x00000000, 0x00000000, 0x00000000, eSkill::情天恨海, eSkillUse::None, eBuff::None, 0, 0, "情天恨海", "没有被使用", "无" },
	{ 0xFCF44944, 0xD11D8F4A, 0x00000000, 0x00000000, 0x00000000, eSkill::莲步轻舞, eSkillUse::None, eBuff::None, 0, 0, "莲步轻舞", "没有被使用", "无" },
	{ 0x4C8034D4, 0x71FC82F8, 0x8A39B79F, 0x00000000, 0xBDCD9588, eSkill::如花解语, eSkillUse::None, eBuff::None, 0, 0, "如花解语", "没有被使用", "无" },
	{ 0xD2123BE8, 0xA2DE2140, 0x46C7B776, 0x59D77EF9, 0xBDCD9588, eSkill::似玉生香, eSkillUse::BattleOther, eBuff::Seal, 50, -10, "似玉生香", "封印物理攻击和法术", "50MP" },
	{ 0x53B01707, 0x2DC6C0E7, 0x00000000, 0x00000000, 0x00000000, eSkill::娉婷嬝娜, eSkillUse::None, eBuff::None, 0, 0, "娉婷嬝娜", "没有被使用", "无" },
	{ 0x15E168DD, 0x01FF0F6F, 0x00000000, 0x00000000, 0x00000000, eSkill::轻如鸿毛, eSkillUse::None, eBuff::None, 0, 0, "轻如鸿毛", "没有被使用", "无" },
	{ 0x37F7C199, 0x02B4928E, 0x00000000, 0x00000000, 0x00000000, eSkill::百毒不侵, eSkillUse::None, eBuff::None, 0, 0, "百毒不侵", "没有被使用", "无" },
	{ 0x066D7389, 0x51A0423C, 0x00000000, 0x00000000, 0xFE189BCC, eSkill::移形换影, eSkillUse::NormalSelf, eBuff::None, 0, 0, "移形换影", "传送到女儿村", "5%HP" },
	{ 0x1F215E91, 0xC2B106E9, 0x8A39B79F, 0x00000000, 0x51F82D7D, eSkill::一笑倾城, eSkillUse::BattleOther, eBuff::None, 0, -10, "一笑倾城", "多人封印法术", "60*N的MP" },
	{ 0x74FF026F, 0xF2553F61, 0x00000000, 0x00000000, 0x00000000, eSkill::飞花摘叶, eSkillUse::None, eBuff::None, 0, 0, "飞花摘叶", "没有被使用", "无" },
	{ 0x21883613, 0x92F67200, 0x00000000, 0x00000000, 0x00000000, eSkill::雨落寒沙, eSkillUse::BattleOther, eBuff::None, 10, 0, "雨落寒沙", "暗器多人攻击", "MPS" },

	{ 0xFA64E7B9, 0x81925D39, 0x00000000, 0x66CC7A29, 0x00000000, eSkill::天神护体, eSkillUse::BattleSelf, eBuff::Good, 20, 10, "天神护体", "战斗中提升自己的灵力", "无" },
	{ 0xDF877E23, 0xF19A5EFA, 0x73604A57, 0x00000000, 0x00000000, eSkill::天神护法, eSkillUse::BattleOwner, eBuff::Good, 0, 0, "天神护法", "战斗中保护同伴", "50MP" },
	{ 0xDC9BDA8C, 0xB3C8279C, 0x00000000, 0x00000000, 0x00000000, eSkill::天诛地灭, eSkillUse::None, eBuff::None, 0, 0, "天诛地灭", "没有被使用", "无" },
	{ 0x91EC4841, 0x0BB38F40, 0x00000000, 0x00000000, 0x00000000, eSkill::知己知彼, eSkillUse::None, eBuff::None, 0, 0, "知己知彼", "没有被使用", "无" },
	{ 0x74B29E7D, 0x9A155954, 0xDC756B6F, 0x00000000, 0x57726FFB, eSkill::宁心, eSkillUse::BattleOwner, eBuff::None, 0, 0, "宁心", "解除自身的负面效果", "50MP" },
	{ 0x0EF91062, 0xA82E9413, 0x1EB0026B, 0x98753F94, 0x318685B7, eSkill::镇妖, eSkillUse::BattleOther, eBuff::Seal, 45, -10, "镇妖", "封印特技", "50MP" },
	{ 0xFFB5624B, 0xD7E76D2D, 0xD35FC051, 0x2F78C46E, 0x5703EB56, eSkill::错乱, eSkillUse::BattleOther, eBuff::Seal, 60, -10, "错乱", "封印法术", "50MP" },
	{ 0xFF5FCC5F, 0xBB32CB83, 0x8B8516F1, 0xC48ABA7B, 0x318685B7, eSkill::百万神兵, eSkillUse::BattleOther, eBuff::Seal, 60, -10, "百万神兵", "封印物理攻击", "50MP" },
	{ 0x360B497C, 0x72BB2C70, 0x00000000, 0x00000000, 0xA12CF973, eSkill::腾云驾雾, eSkillUse::NormalSelf, eBuff::None, 0, 0, "腾云驾雾", "传送到天宫", "5%HP" },
	{ 0x391FBBEB, 0x12CFF6C1, 0x4C117B7C, 0x00000000, 0x251670FB, eSkill::天雷斩, eSkillUse::BattleOther, eBuff::None, 30, -10, "天雷斩", "使用后可以给予敌人重击，并降低灵力。但自己也会减少物理防御力", "MPS" },
	{ 0x6CD25687, 0xFC7CEE47, 0xFFD64CCA, 0x00000000, 0xDB4F9338, eSkill::五雷轰顶, eSkillUse::BattleOther, eBuff::None, 50, -10, "五雷轰顶", "有几率去掉敌人25%的气血和魔法", "50MP" },
	{ 0x6794F727, 0xF979C506, 0x00000000, 0x00000000, 0x00000000, eSkill::金刚镯, eSkillUse::None, eBuff::None, 0, 0, "金刚镯", "没有被使用", "无" },
	{ 0x7B003972, 0x45909EE4, 0x911E3921, 0x00000000, 0x040584F3, eSkill::雷霆万钧, eSkillUse::BattleOther, eBuff::None, 35, 0, "雷霆万钧", "多人法术", "MPS" },
	{ 0x21D77976, 0xCDA1A3A3, 0x00000000, 0x00000000, 0x00000000, eSkill::浩然正气, eSkillUse::None, eBuff::None, 0, 0, "浩然正气", "没有被使用", "无" },
	{ 0x5DF74259, 0x2D863D2A, 0x752464D7, 0x00000000, 0x318685B7, eSkill::掌心雷, eSkillUse::None, eBuff::Good, 0, 0, "掌心雷", "没有被使用", "无" },

	{ 0x6BB78F2A, 0x984CF938, 0xDC756B6F, 0x00000000, 0x57726FFB, eSkill::解封, eSkillUse::BattleOwner, eBuff::None, 0, 0, "解封", "解封", "80MP" },
	{ 0xD4647700, 0x01590DDC, 0xDE34B83E, 0x00000000, 0x57726FFB, eSkill::清心, eSkillUse::BattleOwner, eBuff::None, 30, 0, "清心", "解毒", "无" },
	{ 0xD9935972, 0x7CC5EF28, 0x7367AF0F, 0x00000000, 0x5505BC3C, eSkill::龙腾, eSkillUse::BattleOther, eBuff::None, 30, -10, "龙腾", "单体水属性法术", "50MP" },
	{ 0x3236D5E1, 0x0C054889, 0xA19EAB31, 0x00000000, 0xA39B4CA3, eSkill::龙卷雨击, eSkillUse::BattleOther, eBuff::None, 20, 0, "龙卷雨击", "群体水/雷属性法术", "MPS" },
	{ 0xE2C973B2, 0x5905DEC6, 0x04DB6C0A, 0x00000000, 0xC0A21592, eSkill::逆鳞, eSkillUse::BattleSelf, eBuff::Good, 20, 0, "逆鳞", "提升伤害", "10MP" },
	{ 0xC06DBC74, 0x055E6A6D, 0x00000000, 0x00000000, 0x00000000, eSkill::乘风破浪, eSkillUse::None, eBuff::None, 0, 0, "乘风破浪", "没有被使用", "无" },
	{ 0x9F38CFD7, 0x238F9C1B, 0x00000000, 0x00000000, 0x64AAF170, eSkill::水遁, eSkillUse::NormalSelf, eBuff::None, 0, 0, "水遁", "传送到龙宫", "5%HP" },
	{ 0x7F6E6C02, 0x4E96B443, 0x48639CF5, 0x00000000, 0xA08D7D31, eSkill::龙吟, eSkillUse::BattleOther, eBuff::None, 30, 0, "龙吟", "全体固定伤害并打蓝", "50MP" },
	{ 0x7EA52AB5, 0xD93D4F3D, 0x00000000, 0x00000000, 0x00000000, eSkill::龙啸九天, eSkillUse::None, eBuff::None, 0, 0, "龙啸九天", "没有被使用", "无" },
	{ 0x6A643D2E, 0xAC322FAD, 0x00000000, 0x00000000, 0x00000000, eSkill::龙附, eSkillUse::None, eBuff::None, 0, 0, "龙附", "没有被使用", "无" },
	{ 0x975B5587, 0x5D2392F9, 0xF483EB13, 0x4CCDACCB, 0x00000000, eSkill::神龙摆尾, eSkillUse::BattleSelf, eBuff::Good, 100, -10, "神龙摆尾", "减少20%所承受的物理伤害", "无" },
	{ 0x2598BAD0, 0x4B78F4EA, 0xA680A821, 0x00000000, 0x6F872F79, eSkill::二龙戏珠, eSkillUse::BattleOther, eBuff::None, 70, 0, "二龙戏珠", "双体法术", "100MP" },

	{ 0xCFF9CA32, 0xE8A1FA06, 0xA70D1263, 0x313BCC79, 0xA7B1C535, eSkill::日月乾坤, eSkillUse::BattleOther, eBuff::Seal, 35, -10, "日月乾坤", "封印物理攻击和法术和特技", "50MP" },
	{ 0x6484CE2C, 0x8EBBB9ED, 0x3648247E, 0x719D767F, 0x24A434E5, eSkill::炼气化神, eSkillUse::BattleOwner, eBuff::Good, 30, 10, "炼气化神", "持续回蓝", "CostHpFix" },
	{ 0xA4558B86, 0x4126939F, 0xD2DC9AD3, 0xF8EE853A, 0x24A434E5, eSkill::生命之泉, eSkillUse::BattleOwner, eBuff::Good, 30, 10, "生命之泉", "持续回血", "MPS" },
	{ 0x630B9900, 0x6347C97B, 0x00000000, 0x00000000, 0x00000000, eSkill::太极生化, eSkillUse::None, eBuff::None, 0, 0, "太极生化", "没有被使用", "无" },
	{ 0x2714CD4D, 0x785A5F32, 0x00000000, 0x00000000, 0x9197B5A6, eSkill::斗转星移, eSkillUse::NormalSelf, eBuff::None, 0, 0, "斗转星移", "传送到五庄观", "5%HP" },
	{ 0xBBCF26FE, 0xE34DD120, 0x775FD2E3, 0x00000000, 0x24A434E5, eSkill::三花聚顶, eSkillUse::BattleSelf, eBuff::None, 30, 0, "三花聚顶", "自身加蓝", "CostHpFix" },
	{ 0x271F24E1, 0x4C8E9F62, 0x00000000, 0x00000000, 0x00000000, eSkill::驱魔, eSkillUse::None, eBuff::None, 0, 0, "驱魔", "没有被使用", "无" },
	{ 0x2097EBF0, 0x4919A4E5, 0xDE34B83E, 0x00000000, 0x57726FFB, eSkill::驱尸, eSkillUse::BattleOwner, eBuff::None, 40, 0, "驱尸", "解除各类中毒状态", "无" },
	// 击打动画 0xD06119B3 0xC29A0737
	{ 0xD9249EC5, 0xBA3CC9E9, 0xA3FD9577, 0x00000000, 0x30D78CEF, eSkill::烟雨剑法, eSkillUse::BattleOther, eBuff::None, 50, 0, "烟雨剑法", "二连击", "50MP" },
	{ 0xCA8F3E1A, 0xC2D517D6, 0x66BEBCBA, 0x00000000, 0x00000000, eSkill::飘渺式, eSkillUse::BattleOther, eBuff::None, 30, 0, "飘渺式", "多人物理攻击", "MPS" },
	{ 0x00000000, 0xFBC5D873, 0x00000000, 0x00000000, 0x00000000, eSkill::天地同寿, eSkillUse::BattleOwner, eBuff::Good, 50, 0, "天地同寿", "为目标临时加上一个防御护罩,吸收全部法术伤害,降低目标50%防御效果,且所受物理伤害会加倍", "无" },
	{ 0xC464481B, 0x6779E3D4, 0x00000000, 0x00000000, 0x00000000, eSkill::乾坤妙法, eSkillUse::None, eBuff::None, 0, 0, "乾坤妙法", "没有被使用", "无" },
	{ 0x951F8360, 0xFDC44BC0, 0x00000000, 0x00000000, 0x00000000, eSkill::一气化三清, eSkillUse::None, eBuff::None, 0, 0, "一气化三清", "没有被使用", "无" },
	
	{ 0xCB1639D1, 0x290BF9E7, 0x2FF74578, 0xD8857128, 0x2550B4D0, eSkill::普渡众生, eSkillUse::BattleOwner, eBuff::Good, 50, -10, "普渡众生", "持续回血", "50MP" },
	// 0x5480C749
	{ 0x3908C648, 0x5DC3D631, 0x1EA5FACC, 0xEFE73EB9, 0xD00F519D, eSkill::紧箍咒, eSkillUse::BattleOther, eBuff::Bad, 50, -10, "紧箍咒", "单体掉血和上限", "50MP" },
	{ 0x2F5AFA7D, 0xDFF28692, 0x380337C1, 0xD8857128, 0xA4B9B11E, eSkill::杨柳甘露, eSkillUse::BattleOwner, eBuff::None, 150, -10, "杨柳甘露", "复活,无视锢魂术与死亡召唤", "150MP" },
	{ 0x34464142, 0x7B080559, 0x45CA9913, 0x00000000, 0xCE259E8C, eSkill::日光华, eSkillUse::BattleOther, eBuff::None, 50, 0, "日光华", "群体光属性伤害", "50MP" },
	{ 0x6A4D383D, 0x9FB86B6A, 0x6C5F8376, 0x00000000, 0xE957CD44, eSkill::靛沧海, eSkillUse::BattleOther, eBuff::None, 50, -10, "靛沧海", "群体水属性伤害", "50MP" },
	{ 0xE38F0541, 0xBFD75298, 0xDF4C3BE3, 0x00000000, 0x52BA8E8D, eSkill::巨岩破, eSkillUse::BattleOther, eBuff::None, 50, -10, "巨岩破", "群体土属性伤害", "50MP" },
	{ 0x8C6D506B, 0x493EEC97, 0x9CCB6E84, 0x00000000, 0x251670FB, eSkill::苍茫树, eSkillUse::BattleOther, eBuff::None, 50, 0, "苍茫树", "群体木属性伤害", "50MP" },
	{ 0x047A00A7, 0xF64BED47, 0x18E13BE9, 0x00000000, 0x1366C86B, eSkill::地裂火, eSkillUse::BattleOther, eBuff::None, 50, -10, "地裂火", "群体火属性伤害", "50蓝" },
	{ 0xE57C320E, 0x92CACF3B, 0x00000000, 0x00000000, 0xEFB621F4, eSkill::坐莲, eSkillUse::NormalSelf, eBuff::None, 0, 0, "坐莲", "可以传送到普陀山", "无" },
	{ 0xDEE056A8, 0x133CEEA4, 0x00000000, 0x00000000, 0x00000000, eSkill::五行错位, eSkillUse::None, eBuff::None, 0, 0, "五行错位", "没有被使用", "无" },
	{ 0x728DE1CD, 0x890CE894, 0xAB5DAE52, 0x95FF4460, 0x2550B4D0, eSkill::灵动九天, eSkillUse::BattleOwner, eBuff::Good, 30, 0, "灵动九天", "群体加灵", "100MP" },
	// 0x5A07D50A 状态0x4DDF5690
	{ 0xD78FBB42, 0x6E44BE66, 0x88F19652, 0x2D1E688F, 0xA37E8B19, eSkill::颠倒五行, eSkillUse::BattleOwner, eBuff::Good, 80, -10, "颠倒五行", "增加法术吸收率", "80MP" },
	{ 0x87C2F0D2, 0xF17355F3, 0x00000000, 0x00000000, 0x00000000, eSkill::莲华妙法, eSkillUse::None, eBuff::None, 0, 0, "莲华妙法", "没有被使用", "无" },
	{ 0xCBD97FD0, 0x477948A0, 0x77592664, 0x00000000, 0x00000000, eSkill::自在心法, eSkillUse::BattleOwner, eBuff::None, 30, 0, "自在心法", "结算普渡众生", "无" },

	{ 0xCD73E07C, 0xA7459134, 0x9EB11259, 0x00000000, 0x12A308C0, eSkill::阎罗令, eSkillUse::BattleOther, eBuff::None, 20, -10, "阎罗令", "减少对手的气血和气血上限", "MPS" }, //,夜晚攻击效果高于白天,对怪物伤害加倍
	{ 0xDCABAFAD, 0x63A83981, 0x241C668A, 0x00000000, 0xB6A8CB18, eSkill::判官令, eSkillUse::BattleOther, eBuff::None, 20, 0, "判官令", "减少对手的气血和魔法", "30蓝" }, //,黑夜使用效果为标准的130%
	{ 0x80305F4B, 0xF2D2EB2F, 0x00000000, 0x00000000, 0xED520CA0, eSkill::勘察令, eSkillUse::None, eBuff::None, 0, 0, "勘察令", "鉴定项链,头盔,鞋,腰带(右击未鉴定的装备)", "无" },
	{ 0x1CC4C18F, 0x26F78E1F, 0xDC756B6F, 0x00000000, 0x00000000, eSkill::寡欲令, eSkillUse::BattleOwner, eBuff::None, 0, 0, "寡欲令", "解封", "50MP" },
	{ 0xA7592BE7, 0x75C1605A, 0x07DF52CA, 0x21435203, 0xFBA099F0, eSkill::幽冥鬼眼, eSkillUse::BattleOwner, eBuff::Good, 20, 0, "幽冥鬼眼", "使用后可以看到隐身的目标并增加10%的抗封效果", "MPS" },
	{ 0x167366B6, 0xD5CE79DD, 0x00000000, 0x00000000, 0x00000000, eSkill::冤魂不散, eSkillUse::None, eBuff::None, 0, 0, "冤魂不散", "没有被使用", "无" },
	{ 0x8AC6F05B, 0x02ED1F1B, 0x849E48FB, 0x839CC29A, 0x98BDEC63, eSkill::尸腐毒, eSkillUse::BattleOther, eBuff::Poison, 40, -10, "尸腐毒", "对手中毒并给己方回血", "40MP" },
	{ 0xB759D696, 0x213794E1, 0xBA7D5CD7, 0x00000000, 0x00000000, eSkill::修罗隐身, eSkillUse::BattleOwner, eBuff::None, 150, 0, "修罗隐身", "单体隐身", "150MP" },
	{ 0x2C0D5A09, 0x7A2AE74E, 0x00000000, 0x00000000, 0xBB1E59E8, eSkill::杳无音讯, eSkillUse::NormalSelf, eBuff::None, 0, 0, "杳无音讯", "可以传送到地府", "5%HP" },
	{ 0x1CEE0599, 0xAB58943F, 0x380337C1, 0x00000000, 0x97283C40, eSkill::还阳术, eSkillUse::BattleOwner, eBuff::None, 150, -10, "还阳术", "复活+伤害", "150MP" },
	// 状态 0x5ECEBEDD
	{ 0x70D5CD29, 0xD2D21A8B, 0x2611E02E, 0x69180378, 0xBF36842D, eSkill::黄泉之息, eSkillUse::BattleOther, eBuff::Bad, 50, -10, "黄泉之息", "攻击对方单人,并减少其一定的速度", "80MP" }, //,夜间使用效果调整为白天的130%
	{ 0xA21E0165, 0x5F0B6F6D, 0x057B7209, 0x00000000, 0x814AE8F4, eSkill::魂飞魄散, eSkillUse::BattleOther, eBuff::None, 40, -10, "魂飞魄散", "驱散目标的良性状态", "80MP" },
	{ 0xD3076E45, 0xE451BF95, 0x00000000, 0x00000000, 0x00000000, eSkill::尸气漫天, eSkillUse::None, eBuff::None, 0, 0, "尸气漫天", "没有被使用", "无" },
	{ 0x2EC10ADD, 0x66F5816E, 0x5C0073EE, 0xE02F2E6D, 0x7FDACB76, eSkill::锢魂术, eSkillUse::BattleOther, eBuff::None, 50, 0, "锢魂术", "死亡召唤", "50MP" },

	{ 0xE13663E9, 0x37E0D423, 0x00000000, 0x00000000, 0x00000000, eSkill::魔王护持, eSkillUse::None, eBuff::None, 0, 0, "魔王护持", "没有被使用", "无" },
	{ 0x2C7FBCD6, 0x2A16BFD0, 0x4DB67680, 0x00000000, 0x550EEC3F, eSkill::飞砂走石, eSkillUse::BattleOther, eBuff::None, 30, 0, "飞砂走石", "群体土属性伤害", "MPS" },
	{ 0x114F1F2C, 0x25526F4E, 0xFCDCCCEC, 0x00000000, 0xF4A86696, eSkill::三昧真火, eSkillUse::BattleOther, eBuff::None, 30, -10, "三昧真火", "单体火属性伤害", "30MP" },
	{ 0x4062BFE4, 0xD1EC7AD9, 0x6EA4246E, 0xA168E26F, 0xED47E570, eSkill::牛劲, eSkillUse::BattleSelf, eBuff::Good, 20, 0, "牛劲", "提升法术伤害力", "50MP" },
	{ 0xA7AC77E0, 0xF20648E8, 0x00000000, 0x00000000, 0x00000000, eSkill::踏山裂石, eSkillUse::None, eBuff::None, 0, 0, "踏山裂石", "没有被使用", "无" },
	{ 0x35C31747, 0xE7D2A6F9, 0x00000000, 0x00000000, 0x40E67E07, eSkill::无敌牛虱, eSkillUse::BattleSelf, eBuff::None, 40, 0, "无敌牛虱", "队伍中只能同时存在一只牛虱或牛妖", "无" },
	{ 0xA5385E3B, 0x1F68ADCC, 0x00000000, 0x00000000, 0x40E67E07, eSkill::无敌牛妖, eSkillUse::BattleSelf, eBuff::None, 40, 0, "无敌牛妖", "队伍中只能同时存在一只牛虱或牛妖", "无" },
	{ 0xB56E84D0, 0x3B5C1425, 0x16B27FFC, 0xBBEA83F4, 0x00000000, eSkill::魔王回首, eSkillUse::BattleSelf, eBuff::None, 30, 0, "魔王回首", "使用后可以在受到物理攻击的时候自动反击", "无" },
	{ 0x27D50D56, 0x93EA969B, 0x00000000, 0x00000000, 0x14E55AF2, eSkill::牛屎遁, eSkillUse::NormalSelf, eBuff::None, 0, 0, "牛屎遁", "可以传送到魔王寨", "5%HP" },
	{ 0xC02762DD, 0x902C43A8, 0x00000000, 0x00000000, 0x00000000, eSkill::火甲术, eSkillUse::None, eBuff::None, 0, 0, "火甲术", "没有被使用", "无" },
	{ 0x69F9FFD0, 0xB5DC536F, 0x00000000, 0x00000000, 0x00000000, eSkill::摇头摆尾, eSkillUse::None, eBuff::None, 0, 0, "摇头摆尾", "没有被使用", "无" },

	{ 0x067DDF53, 0xBD3FF07D, 0xBE127823, 0x3646A4D9, 0x7CFA5491, eSkill::象形, eSkillUse::BattleOther, eBuff::None, 50, 0, "象形", "攻击单人并令其下回合无法行动,变身取消(需要变身)", "30MP" },
	{ 0x56070FE9, 0xBFE91154, 2194212682, 0x58628406, 0x61688718, eSkill::鹰击, eSkillUse::BattleOther, eBuff::None, 30, 0, "鹰击", "攻击对方多人,使用后一回合内无法使用法术(需要变身)", "MPS" },
	{ 0x60FFC2C8, 0xDC90DF2F, 0x718754A2, 0x00000000, 0xF3626BEC, eSkill::狮搏, eSkillUse::BattleOther, eBuff::None, 30, 0, "狮搏", "伤害提升攻击(需要变身)", "30MP" },
	{ 0x35532015, 0x04DA6E6F, 0x8476181B, 0x20FCCE94, 0x019B0A72, eSkill::威慑, eSkillUse::BattleOther, eBuff::Seal, 20, 0, "威慑", "令怪物或玩家召唤兽无法行动,不能对玩家使用", "40MP" },
	{ 0xDA9CD712, 0xFF4048E9, 0x29D819DF, 0x85C9AF08, 0xB90610BF, eSkill::变身, eSkillUse::BattleSelf, eBuff::None, 20, 0, "变身", "象形、鹰击、狮搏和连环击的前提", "20MP" },
	{ 0x430D0B1B, 0x38AB6F30, 0x00000000, 0x00000000, 0x00000000, eSkill::魔兽啸天, eSkillUse::None, eBuff::None, 0, 0, "魔兽啸天", "没有被使用", "无" },
	{ 0x05EFA897, 0xEDB77B1D, 755485932, 0x566DC0F3, 0x40701F91, eSkill::定心术, eSkillUse::BattleSelf, eBuff::Good, 40, 0, "定心术", "提升灵力", "40MP" },
	{ 0x28256D06, 0xD7187347, 0x55EBCA6C, 0x58628406, 0x2FFC7F8A, eSkill::连环击, eSkillUse::BattleOther, eBuff::None, 30, 0, "连环击", "连续攻击,使用后一回合内无法使用法术(需要变身)", "MPS" },
	{ 0xF800E231, 0xD1561312, 0x00000000, 0x00000000, 0x35B1FE83, eSkill::振翅千里, eSkillUse::NormalSelf, eBuff::None, 0, 0, "振翅千里", "可以传送到狮驼岭", "5%HP" },
	{ 0xABF46236, 0x15AC16AF, 0x16B27FFC, 0xBBEA83F4, 0x6961CB02, eSkill::极度疯狂, eSkillUse::BattleSelf, eBuff::Good, 30, 0, "极度疯狂", "受到物理攻击时会自动反击敌人", "30MP" },
	{ 0x2EEC86A4, 0xD92455F2, 0x00000000, 0x00000000, 0x00000000, eSkill::魔息术, eSkillUse::None, eBuff::None, 0, 0, "魔息术", "没有被使用", "无" },
	{ 0x93A98451, 0xA1B84C64, 0x3105A01B, 0x3D3FA597, 0x1C7EE63E, eSkill::天魔解体, eSkillUse::BattleSelf, eBuff::None, 0, 0, "天魔解体", "自身加气血上限", "50MP" },
	{ 0xE78A87A1, 0xE30F693F, 0x00000000, 0x00000000, 0x00000000, eSkill::神力无穷, eSkillUse::None, eBuff::None, 0, 0, "神力无穷", "没有被使用", "无" },
	
	{ 0x2FD480B4, 0xC6AB6795, 0x1B472F2F, 0x00000000, 0xC0942A07, eSkill::勾魂, eSkillUse::BattleOther, eBuff::None, 40, 0, "勾魂", "减少对方气血,恢复自身气血", "40MP" },
	{ 0x06294FA0, 0xA42F7249, 0x59BD69F1, 0x00000000, 0xC0942A07, eSkill::摄魄, eSkillUse::BattleOther, eBuff::None, 35, 0, "摄魄", "减少对方魔法,恢复自身魔法", "40MP" },
	{ 0x5CACF37F, 0x01E94239, 0x78246FE4, 0xC4AA8E18, 0xE6F9B619, eSkill::魔音摄魂, eSkillUse::BattleOther, eBuff::Seal, 40, 0, "魔音摄魂", "令对手一定回合内无法恢复气血和疗伤", "35MP" },
	{ 0x16C75EF8, 0x7C23B1B8, 0x00000000, 0x00000000, 0x00000000, eSkill::盘丝舞, eSkillUse::None, eBuff::None, 0, 0, "盘丝舞", "没有被使用", "无" },
	{ 0xC2CD06E2, 0x0D916626, 0x00000000, 0x00000000, 0x00000000, eSkill::夺命蛛丝, eSkillUse::None, eBuff::None, 0, 0, "夺命蛛丝", "没有被使用", "无" },
	{ 0x9A5880DC, 0xF50D8C5A, 0x5363AF2D, 0x8103AFD2, 0x7F5FD02A, eSkill::含情脉脉, eSkillUse::BattleOther, eBuff::Seal, 50, -10, "含情脉脉", "封印物理攻击和法术", "40MP" },
	{ 0x6974146E, 0x8EC63F2A, 0x7CD9C342, 0x369C6A29, 0xA37E8B19, eSkill::盘丝阵, eSkillUse::BattleSelf, eBuff::Good, 40, 0, "盘丝阵", "自身提升物理防御", "50MP" },
	{ 0xAB18B4B0, 0x086B8CFF, 0xDC756B6F, 0x00000000, 0x5007BB0C, eSkill::复苏, eSkillUse::BattleSelf, eBuff::None, 0, 0, "复苏", "自身解除封印和异常", "30MP" },
	{ 0x56DE11A1, 0x628E8D59, 0x8F3E73D5, 0xD671B65E, 0x13848F75, eSkill::天罗地网, eSkillUse::BattleOther, eBuff::Seal, 30, -10, "天罗地网", "群体伤害+封物理", "MPS" },
	{ 0x6BB35F00, 0x4C7CC844, 0x00000000, 0x00000000, 0x95C06373, eSkill::天蚕丝, eSkillUse::NormalSelf, eBuff::None, 0, 0, "天蚕丝", "可以传送到盘丝岭", "5%HP" },
	{ 0x1DEE311E, 0x0286F483, 0x00000000, 0x00000000, 0xC0942A07, eSkill::姐妹同心, eSkillUse::BattleOther, eBuff::None, 0, 0, "姐妹同心", "吸蓝", "60MP" },
	{ 0xE63FB407, 0xB5243050, 0x00000000, 0x00000000, 0x00000000, eSkill::瘴气, eSkillUse::None, eBuff::None, 0, 0, "瘴气", "没有被使用", "无" },
	{ 0x241E44A3, 0x43A1A964, 0x0732894C, 0xCDE5D209, 0x245321A8, eSkill::幻镜术, eSkillUse::BattleSelf, eBuff::Good, 50, 0, "幻镜术", "反弹受到的法术伤害", "80MP" },

	{ 0x1C603FAE, 0xF4DCF38F, 0x00000000, 0x00000000, 0x00000000, eSkill::裂石, eSkillUse::BattleOther, eBuff::None, 50, 0, "裂石", "临时提升必杀几率对单个敌人进行物理攻击,增加1点战意值", "" },
	{ 0x5C95AF41, 0x5AA54949, 0x00000000, 0x00000000, 0x00000000, eSkill::断岳势, eSkillUse::BattleOther, eBuff::None, 50, 0, "断岳势", "临时提升必杀几率对单个敌人进行2次物理攻击", "消耗1战意" },
	{ 0x4C99C220, 0x9ADAEA80, 0x00000000, 0x00000000, 0x00000000, eSkill::天崩地裂, eSkillUse::BattleOther, eBuff::None, 50, 0, "天崩地裂", "临时提升必杀几率对单个敌人进行3次物理攻击", "消耗2战意" },
	{ 0x1A289BEA, 0xCE61D91C, 0x00000000, 0x00000000, 0x00000000, eSkill::浪涌, eSkillUse::BattleOther, eBuff::None, 20, 0, "浪涌", "对多个敌人进行物理攻击,增加1点战意值", "MPS" },
	{ 0xBE11779C, 0xB91C6953, 0x00000000, 0x00000000, 0x00000000, eSkill::惊涛怒, eSkillUse::BattleOther, eBuff::None, 20, -10, "惊涛怒", "提升一定伤害力对多个敌人进行物理攻击", "消耗1战意,MPS" },
	{ 0x11879028, 0x26419C11, 0x00000000, 0x00000000, 0x00000000, eSkill::翻江搅海, eSkillUse::BattleOther, eBuff::None, 20, 0, "翻江搅海", "提升一定伤害力对多个敌人进行物理攻击", "消耗3战意,MPS" },
	{ 0x956BA0A2, 0x569D01F7, 0x00000000, 0x00000000, 0x00000000, eSkill::腾雷, eSkillUse::BattleOther, eBuff::None, 0, 0, "腾雷", "", "" },
	{ 0x00000000, 0x4AB6831C, 0x00000000, 0x00000000, 0x00000000, eSkill::指地成钢, eSkillUse::None, eBuff::None, 0, 0, "指地成钢", "", "" },
	{ 0x38C47290, 0xD96F2331, 0x00000000, 0x00000000, 0x00000000, eSkill::不动如山, eSkillUse::BattleSelf, eBuff::Good, 150, -10, "不动如山", "使用后减少自身受到的法术伤害与物理伤害", "" },
	{ 0x5F8D7935, 0x136442C0, 0x00000000, 0x00000000, 0x00000000, eSkill::碎星诀, eSkillUse::BattleOwner, eBuff::Good, 30, 10, "碎星诀", "提升物理伤害结果", "" },
	{ 0xF808DCC6, 0x9E1580AA, 0x00000000, 0x00000000, 0x00000000, eSkill::镇魂诀, eSkillUse::BattleOwner, eBuff::Good, 5, 10, "镇魂诀", "提升物理必杀几率", "CostHp" },
	{ 0x00E0D005, 0xB7E814EE, 0x00000000, 0x00000000, 0x00000000, eSkill::穿云破空, eSkillUse::None, eBuff::None, 0, 0, "穿云破空", "", "" },
	{ 0x76FBBEEC, 0xAFDB81A4, 0x00000000, 0x00000000, 0x00000000, eSkill::无穷妙道, eSkillUse::BattleOwner, eBuff::None, 0, 0, "无穷妙道", "", "" },
	{ 0xFEF5D678, 0xE6A2AA59, 0x00000000, 0x00000000, 0x00000000, eSkill::纵地金光, eSkillUse::NormalSelf, eBuff::None, 0, 0, "纵地金光", "可以传送到凌波城", "" },

	{ 0x85DC4B33, 0x173015AE, 0x00000000, 0x00000000, 0x00000000, eSkill::移魂化骨, eSkillUse::BattleOwner, eBuff::Good, 10, -10, "移魂化骨", "消耗自身气血使目标获得吸血效果", "CostHpMax" },
	{ 0x076EA85A, 0x62221B56, 0x00000000, 0x00000000, 0x00000000, eSkill::夺魄令, eSkillUse::BattleOther, eBuff::Seal, 30, -10, "夺魄令", "令目标一定回合内无法使用法术", "" },
	{ 0x28D6DCD8, 0xC0504605, 0x00000000, 0x00000000, 0x00000000, eSkill::煞气诀, eSkillUse::BattleOther, eBuff::None, 0, 0, "煞气诀", "", "" },
	{ 0x71307D22, 0xC232A281, 0x00000000, 0x00000000, 0x00000000, eSkill::惊魂掌, eSkillUse::BattleOther, eBuff::None, 0, 0, "惊魂掌", "", "" },
	{ 0xD6A5B20C, 0x1CC2B0B0, 0x00000000, 0x00000000, 0x00000000, eSkill::摧心术, eSkillUse::BattleOther, eBuff::Bad, 100, 0, "摧心术", "使敌方2个目标速度降低", "" },
	{ 0xA9AF9E72, 0x2A3E7A3C, 0x00000000, 0x00000000, 0x00000000, eSkill::夺命咒, eSkillUse::BattleOther, eBuff::None, 20, -10, "夺命咒", "使用固定伤害攻击对方多人", "MPS" },
	{ 0x59D84304, 0x54DB6CDE, 0x00000000, 0x00000000, 0x00000000, eSkill::明光宝烛, eSkillUse::BattleOwner, eBuff::None, 100, 0, "明光宝烛", "使己方多人一定回合内承受的物理伤害结果减少", "" },
	{ 0xFE884980, 0x1BE322B2, 0x00000000, 0x00000000, 0x00000000, eSkill::金身舍利, eSkillUse::BattleOwner, eBuff::None, 100, 0, "金身舍利", "使己方多人一定回合内承受的法术伤害结果减少", "" },
	{ 0x86AE37EA, 0x40FB7647, 0x00000000, 0x00000000, 0x00000000, eSkill::地涌金莲, eSkillUse::BattleOwner, eBuff::None, 3, -10, "地涌金莲", "恢复自己或者队友的气血与气血上限", "CostHpMax" },
	{ 0x00000000, 0x036B4345, 0x00000000, 0x00000000, 0x00000000, eSkill::万木凋枯, eSkillUse::None, eBuff::None, 0, 0, "万木凋枯", "", "" },
	{ 0x2EF58426, 0xABD57D92, 0x00000000, 0x00000000, 0x00000000, eSkill::元阳护体, eSkillUse::None, eBuff::None, 0, 0, "元阳护体", "", "" },
	{ 0x34D061C7, 0x1D14968A, 0x00000000, 0x00000000, 0x00000000, eSkill::遁地术, eSkillUse::NormalSelf, eBuff::None, 0, 0, "遁地术", "平时状态下使用，可以瞬间回到自己的门派", "" },
	{ 0xDB2E1256, 0xDE58924A, 0x00000000, 0x00000000, 0x00000000, eSkill::由己渡人, eSkillUse::BattleOwner, eBuff::None, 10, -10, "由己渡人", "复活", "CostHpMax" },

	{ 0x0B8CF3A1, 0x2E734F9D, 0x00000000, 0x00000000, 0x6061BB93, eSkill::落叶萧萧, eSkillUse::BattleOther, eBuff::None, 30, 0, "落叶萧萧", "使用法术攻击敌方多个目标", "MPS" },
	{ 0x6A647570, 0xDD2AB898, 0x00000000, 0x00000000, 0x00000000, eSkill::荆棘舞, eSkillUse::BattleOther, eBuff::None, 30, -10, "荆棘舞", "使用法术攻击敌方单体目标", "" },
	{ 0x71C197B0, 0x3FE17E30, 0x00000000, 0x00000000, 0x00000000, eSkill::尘土刃, eSkillUse::BattleOther, eBuff::None, 30, -10, "尘土刃", "使用法术攻击敌方单体目标,，并使目标损失一定HP上限", "" },
	{ 0x3B12CD18, 0xEDF81F56, 0x00000000, 0x00000000, 0xF76A183A, eSkill::冰川怒, eSkillUse::BattleOther, eBuff::None, 30, -10, "冰川怒", "使用法术攻击敌方单体目标,，并使目标损失一定愤怒", "" },
	{ 0x0DA2D8DF, 0x1EE55D3C, 0x00000000, 0x00000000, 0x00000000, eSkill::雾杀, eSkillUse::BattleOther, eBuff::Bad, 50, -10, "雾杀", "使用法术攻击敌方单人目标，对敌人造成持续毒性伤害", "" },
	{ 0x7D52C301, 0x126B932F, 0x00000000, 0x00000000, 0x00000000, eSkill::血雨, eSkillUse::BattleOther, eBuff::None, 20, 0, "血雨", "消耗自身气血，对敌人单体目标造成大量伤害。 使用后，自己下回合无法使用法术", "CostHpMax" },
	{ 0x007E7633, 0xFF613346, 0x00000000, 0x00000000, 0x00000000, eSkill::星月之惠, eSkillUse::BattleSelf, eBuff::None, 50, 0, "星月之惠", "回复自身HP", "" },
	{ 0xC5D73984, 0xA215E746, 0x00000000, 0x00000000, 0x00000000, eSkill::炎护, eSkillUse::BattleSelf, eBuff::None, 30, 0, "炎护", "抵御50%的气血伤害，每抵御1点伤害消耗1点MP", "" },
	{ 0x51763883, 0x64FEA3A4, 0x00000000, 0x00000000, 0x00000000, eSkill::叶隐, eSkillUse::NormalSelf, eBuff::None, 0, 0, "叶隐", "平时状态下使用，可以瞬间回到自己的门派", "" },
	{ 0xF2E06AF8, 0x977F5625, 0x00000000, 0x00000000, 0x00000000, eSkill::神木呓语, eSkillUse::None, eBuff::None, 0, 0, "神木呓语", "", "" },
	{ 0xF83E2272, 0x058EE366, 0x00000000, 0x00000000, 0x00000000, eSkill::密润, eSkillUse::BattleOwner, eBuff::None, 25, 10, "密润", "增加己方多人的法术伤害力", "MPS" },
	{ 0xAC574467, 0x00000000, 0x00000000, 0x00000000, 0x00000000, eSkill::蝼蚁蚀天, eSkillUse::None, eBuff::None, 0, 0, "蝼蚁蚀天", "", "" },
};

const vector<sSkillPassive>& ctt::getSkillPassives()
{
	return s_skillPassives;
}

const vector<sSkillFuzhu>& ctt::getSkillFuzhus()
{
	return s_skillFuzhus;
}

const vector<ctt::sSkill>& ctt::getSkills()
{
	return s_skills;
}





static std::vector<sSkillAni> s_sillActs =
{
	{ 0x3200B6CC, 0x00000000, 0x00000000, eSkill::雷击 },
	{ 0x3200B6CC, 0x279AF873, 0x00000000, eSkill::奔雷咒 },
	{ 0xFDF34F35, 0x05391F73, 0x00000000, eSkill::落岩 },
	{ 0x4E86F9B3, 0x00000000, 0x00000000, eSkill::泰山压顶 },
	{ 0xCE33E201, 0x00000000, 0x00000000, eSkill::水攻 },
	{ 0x4CE1ACB6, 0x00000000, 0x00000000, eSkill::水漫金山 }, // 0x439692DE, 0xC9BCA454, 0x60EB2F76, 
	{ 0x22A3D764, 0x00000000, 0x00000000, eSkill::烈火 },
	{ 0xDED2253F, 0x00000000, 0x00000000, eSkill::地狱烈火 },
	

	{ 0x68E51BB6, 0x00000000, 0x00000000, eSkill::夜舞倾城 },

};
const std::vector<sSkillAni>& ctt::getSkillActs()
{
	return s_sillActs;
}



static std::vector<sSkillAni> s_sillHits =
{
	{ 0xACA4A54A, 0x3C45D282, 0xD862FBE7, eSkill::横扫千军 },
	// 0x19C102D1
	{ 0x958FAC37, 0x00000000, 0x00000000, eSkill(1010) },
	{ 0x301F9E4A, 0x6AD55205, 0x00000000, eSkill(1017)/*eSkill::破釜沉舟*/ },

	{ 0xB6141EB9, 0xF17168C5, 0x885ACBE1, eSkill::天雷斩 },

	{ 0x4F8312F6, 0x9215D669, 0xD06119B3, eSkill::烟雨剑法 },
	{ 0x3426ACE0, 0x00000000, 0x00000000, eSkill::飘渺式 },

	{ 0x73DA1CCF, 0x89302F40, 0x00000000, eSkill::象形 },
	{ 0xA463C055, 0x86FE2BC1, 0x83020DAE, eSkill::鹰击 },
	{ 0x42F0386F, 0x096766A8, 0x00000000, eSkill::狮搏 },
	{ 0x00000000, 0x00000000, 0x00000000, eSkill::连环击 },

	{ 0x958FAC37, 0x00000000, 0x00000000, eSkill::裂石 },
	{ 0x958FAC37, 0x00000000, 0x00000000, eSkill::断岳势, },
	{ 0x958FAC37, 0x00000000, 0x00000000, eSkill::天崩地裂 },
	{ 0xD53A25EB, 0x00000000, 0x00000000, eSkill::浪涌 },
	{ 0xB94D0B94, 0x00000000, 0x00000000, /*eSkill::惊涛怒*/eSkill(1171) },
	{ 0xB94D0B94, 0x00000000, 0x00000000, /*eSkill::翻江搅海*/eSkill(1172) },
};
const std::vector<sSkillAni>& ctt::getSkillHits()
{
	return s_sillHits;
}

static vector<int> s_skillStartMap = 
{
	(int)eSkill::逆鳞,
	(int)eSkill::炼气化神,
	(int)eSkill::普渡众生,
	(int)eSkill::修罗隐身,
	(int)eSkill::魔王回首,
	(int)eSkill::定心术,
	(int)eSkill::盘丝阵,
	(int)eSkill::碎星诀,
};

const vector<int>& ctt::getSkillStarts()
{
	return s_skillStartMap;
}
