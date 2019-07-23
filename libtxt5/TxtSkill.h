#pragma once
#include "_txtinc.h"

static const int c_2000 = 2000;
static const int c_3000 = 3000;
enum class eSkillPassive
{
	反击fj = ePS_反击 + c_2000,
	高级反击fj,
	反震fz,
	高级反震fz,
	吸血xx,
	高级吸血xx,
	连击lj,
	高级连击lj,
	飞行fx,
	高级飞行fx,
	夜战yz,
	高级夜战yz,
	隐身ys,
	高级隐身ys,
	感知gz,
	高级感知gz,
	再生zs,
	高级再生zs,
	冥思ms,
	高级冥思ms,
	慧根hg,
	高级慧根hg,
	必杀bs = ePS_必杀 + c_2000,
	高级必杀bs,
	幸运xy,
	高级幸运xy,
	神迹sj,
	高级神迹sj,
	招架zj,
	高级招架zj,
	永恒yh,
	高级永恒yh,
	敏捷mj,
	高级敏捷mj,
	强力ql,
	高级强力ql,
	防御fy,
	高级防御fy,
	偷袭tx,
	高级偷袭tx,
	毒d,
	高级毒d,
	驱鬼qg,
	高级驱鬼qg,
	鬼魂术gh,
	高级鬼魂术gh,
	魔之心mz,
	高级魔之心mz,
	神佑复生sy,
	高级神佑复生sy,
	精神集中js,
	高级精神集中js,
	否定信仰fd,
	高级否定信仰fd,
	法术连击fs,
	高级法术连击fs,
	法术暴击fs,
	高级法术暴击fs,
	法术波动fs,
	高级法术波动fs,
	迟钝cd,
	高级迟钝cd = ePS_不幸 + c_2000,
	弱点火rd = ePS_弱点火 + c_2000,
	弱点水rd,
	弱点土rd,
	弱点雷rd,
	雷属性吸收ls,
	高级雷属性吸收ls,
	土属性吸收ts,
	高级土属性吸收ts,
	火属性吸收hs,
	高级火属性吸收hs,
	水属性吸收ss,
	高级水属性吸收ss,
	盾气dq = ePS_龙鳞防御 + c_2000,
	高级盾气dq = ePS_龙神守护 + c_2000,
	法术抵抗fs = ePS_法术抵抗 + c_2000,
	高级法术抵抗fs = ePS_高级法术抵抗 + c_2000,
	合纵hz = ePS_直死 + c_2000,
	高级合纵hz = ePS_风华武圣 + c_2000,

	嗜血追击sx = ePS_嗜血追击 + c_2000,
	移花接木yh = ePS_移花接木 + c_2000,
	灵能激发ln = ePS_风刃 + c_2000,
	法力陷阱fl = ePS_法术陷井 + c_2000,
	须弥真言xm = ePS_须弥真言 + c_2000,
	从天而降ct = ePS_从天而降 + c_2000,
	灵山禅语ls = ePS_灵山禅语 + c_2000,
	千钧一怒qj = ePS_千钧一怒 + c_2000,
	浮云神马fy = ePS_浮云神马 + c_2000,
	苍穹怒击cq = ePS_苍鸾怒击 + c_2000,
	龙魂lh = ePS_龙魂 + c_2000,
	大快朵颐dk = ePS_大快朵颐 + c_2000,
};



enum class eSkillFuzhu
{
	// 辅助
	强壮,
	强身术,
	冥想,
	暗器技巧,
	打造技巧,
	裁缝技巧,
	炼金术,
	中药医理,
	烹饪技巧,
	逃离技巧,
	追捕技巧,
	养生之道,
	健身术,
	// 剧情
	调息,
	打坐,
	宝石工艺,
	奇门遁甲,
	变化之术,
	火眼金睛,
	丹元济会,
	妙手空空,
	召唤兽图鉴,
	变化咒,
	梦幻卡牌,
	小试牛刀,
	猜拳,
	五子棋,
	装备图鉴,
	熔炼技巧,
	灵石技巧,
	巧匠之术,
	古董评估,
	建筑之术,
	仙灵店铺,
	// 坐骑
	破釜沉舟,
	开天辟地,
	正身清心,
	延年益寿,
	金刚护身,
	忠贯日月,
	炫火乱舞,
	乾坤借速,
	水来土掩,
	飞火流星,
	大浪淘沙,
	铜墙铁壁,
};



enum class eSkill
{
	雷击 = ePS_雷击 + c_2000,
	奔雷咒,
	落岩,
	泰山压顶,
	水攻,
	水漫金山,
	烈火,
	地狱烈火,
	惊心一剑,
	夜舞倾城,
	死亡召唤,
	力劈华山,
	剑荡四方 = ePS_剑荡四方 + c_2000,
	法术防御 = ePS_法术防御 + c_2000,
	善恶有报 = ePS_善恶有报 + c_2000,
	壁垒击破 = ePS_壁垒击破 + c_2000,
	无畏布施 = ePS_迷你空间震 + c_2000,
	天降灵葫 = ePS_大蛇破坏光线 + c_2000,
	月光 = ePS_月光 + c_2000,
	吸星大法xx = ePS_吸星大法 + c_2000,
	气疗术 = c_3000,
	心疗术,
	命疗术,
	凝气诀,
	凝神诀,
	气归术,
	命归术,
	四海升平,
	回魂咒,
	起死回生,
	水清诀,
	冰清诀,
	玉清诀,
	晶清诀,

	空位1, // 诅咒之伤
	空位2, // 诅咒之亡

// 	诅咒之伤 = c_3000 + 50,
// 	诅咒之亡 = c_3000 + 51,
	笑里藏刀 = c_3000 + 16,
	绝幻魔音,
	野兽之力,
	魔兽之印,
	光辉之甲,
	圣灵之甲,
	流云诀,
	啸风诀,
	太极护法,
	罗汉金钟,
	修罗咒,
	天衣无缝,
	放下屠刀,
	//////////////////////////////////////////////////////////////////////////
	河东狮吼,
	//////////////////////////////////////////////////////////////////////////
	破甲术,
	碎甲术,
	凝滞术,
	停陷术,
	破血狂攻,
	弱点击破,
	//////////////////////////////////////////////////////////////////////////
	空位3, // 吸血
	空位4, // 残月
	星杯圣域, // 冥王暴杀
	命疗术EX, // 乾坤斩
	//////////////////////////////////////////////////////////////////////////
	破碎无双,
	//////////////////////////////////////////////////////////////////////////
	空位5, // 帝释无双
	破血狂攻2, // 伽罗无双
	弱点击破EX, // 虚空之刃
	破血狂攻EX, // 亡灵之刃
	空位6, // 死亡之音
	大地之墙, // 身似菩提
	//////////////////////////////////////////////////////////////////////////
	心如明镜,
	慈航普渡,
	//////////////////////////////////////////////////////////////////////////
	迅疾如风, // 移形换影

	横扫千军 = 0,
	后发制人,
	兵器谱,
	千里神行,
	杀气诀,
	斩龙诀,
	反间之计,
	破釜沉舟,
	安神诀,
	嗜血,
	三星灭魔,
	五雷咒,
	飞行符,
	兵解符,
	催眠符,
	失心符,
	落魄符,
	失忆符,
	追魂符,
	离魂符,
	失魂符,
	定身符,
	归元咒,
	凝神术,
	乾天罡气,
	乙木仙遁,
	分身术,
	碎甲符,
	落雷符,
	神兵护法,
	紫气东来,
	唧唧歪歪,
	达摩护体,
	金刚护法,
	韦陀护法,
	金刚护体,
	一苇渡江,
	我佛慈悲,
	推拿,
	活血,
	推气过宫,
	妙手回春,
	救死扶伤,
	解毒,
	佛门普渡,
	舍生取义,
	佛法无边,
	拈花妙指,
	红袖添香,
	楚楚可怜,
	满天花雨,
	情天恨海,
	莲步轻舞,
	如花解语,
	似玉生香,
	娉婷嬝娜,
	轻如鸿毛,
	百毒不侵,
	移形换影,
	一笑倾城,
	飞花摘叶,
	雨落寒沙,
	天神护体,
	天神护法,
	天诛地灭,
	知己知彼,
	宁心,
	镇妖,
	错乱,
	百万神兵,
	腾云驾雾,
	天雷斩,
	五雷轰顶,
	金刚镯,
	雷霆万钧,
	浩然正气,
	掌心雷,
	解封,
	清心,
	龙腾,
	龙卷雨击,
	逆鳞,
	乘风破浪,
	水遁,
	龙吟,
	龙啸九天,
	龙附,
	神龙摆尾,
	二龙戏珠,
	日月乾坤,
	炼气化神,
	生命之泉,
	太极生化,
	斗转星移,
	三花聚顶,
	驱魔,
	驱尸,
	烟雨剑法,
	飘渺式,
	天地同寿,
	乾坤妙法,
	一气化三清,
	普渡众生,
	紧箍咒,
	杨柳甘露,
	日光华,
	靛沧海,
	巨岩破,
	苍茫树,
	地裂火,
	坐莲,
	五行错位,
	灵动九天,
	颠倒五行,
	莲华妙法,
	自在心法,
	阎罗令,
	判官令,
	勘察令,
	寡欲令,
	幽冥鬼眼,
	冤魂不散,
	尸腐毒,
	修罗隐身,
	杳无音讯,
	还阳术,
	黄泉之息,
	魂飞魄散,
	尸气漫天,
	锢魂术,
	魔王护持,
	飞砂走石,
	三昧真火,
	牛劲,
	踏山裂石,
	无敌牛虱,
	无敌牛妖,
	魔王回首,
	牛屎遁,
	火甲术,
	摇头摆尾,
	象形,
	鹰击,
	狮搏,
	威慑,
	变身,
	魔兽啸天,
	定心术,
	连环击,
	振翅千里,
	极度疯狂,
	魔息术,
	天魔解体,
	神力无穷,
	勾魂,
	摄魄,
	魔音摄魂,
	盘丝舞,
	夺命蛛丝,
	含情脉脉,
	盘丝阵,
	复苏,
	天罗地网,
	天蚕丝,
	姐妹同心,
	瘴气,
	幻镜术,
	裂石,
	断岳势,
	天崩地裂,
	浪涌,
	惊涛怒,
	翻江搅海,
	腾雷,
	指地成钢,
	不动如山,
	碎星诀,
	镇魂诀,
	穿云破空,
	无穷妙道,
	纵地金光,
	移魂化骨,
	夺魄令,
	煞气诀,
	惊魂掌,
	摧心术,
	夺命咒,
	明光宝烛,
	金身舍利,
	地涌金莲,
	万木凋枯,
	元阳护体,
	遁地术,
	由己渡人,
	落叶萧萧,
	荆棘舞,
	尘土刃,
	冰川怒,
	雾杀,
	血雨,
	星月之惠,
	炎护,
	叶隐,
	神木呓语,
	密润,
	蝼蚁蚀天,
};




namespace ctt
{
	struct sSkillPassive
	{
		ulong small;
		ulong big;
		eSkillPassive e;
		std::vector<eSkillPassive> covers;
		std::string name;
		std::string desc;
	};

	struct sSkillFuzhu
	{
		ulong small;
		ulong big;
		eSkillFuzhu e;
		std::string name;
		std::string desc;
	};

	enum eSkillUse
	{
		None = 7,
		// 自己
		NormalSelf = 0,
		// 己方
		NormalOwner,
		// 自己
		BattleSelf,
		// 己方
		BattleOwner,
		// 己方非己
		BattleOwnerButSelf = 9,
		BattleOther = 4,
		BothSelf,
		BothOwner,
	};


	enum class eBuff
	{
		None = eBuffType其它,
		Seal = eBuffType封印,
		Good = eBuffType增益,
		Bad = eBuffType负面,
		Poison = eBuffType毒,
	};

	struct sSkill
	{
		ulong small;
		ulong big;
		ulong uAct;
		ulong state;
		ulong sound;
		eSkill e;
		eSkillUse useType;
		eBuff buffType;
		int costvalue;
		int positiony;
		std::string name;
		std::string desc;
		std::string descCost;
	};


	const vector<sSkillPassive>& getSkillPassives();
	const vector<sSkillFuzhu>& getSkillFuzhus();
	const vector<sSkill>& getSkills();
	const vector<int>& getSkillStarts();


	struct sSkillAni
	{
		ulong u1, u2, u3;
		eSkill e;
	};
	const std::vector<sSkillAni>& getSkillActs();
	const std::vector<sSkillAni>& getSkillHits();


	inline vector<ulong> getWdfFromTxtSkillWithoutSounds()
	{
		set<ulong> us;
		auto ps = getSkillPassives();
		for (const auto& p : ps)
		{
			if (p.e == eSkillPassive::须弥真言xm || p.e == eSkillPassive::从天而降ct)
			{
				continue;
			}
			us.insert(p.small);
			us.insert(p.big);
		}

		auto fs = getSkillFuzhus();
		for (const auto& f : fs)
		{
			us.insert(f.small);
			us.insert(f.big);
		}


		auto ss = getSkills();

		for (const auto& s : ss)
		{
			if (s.e == eSkill::月光)
			{
				continue;
			}
			us.insert(s.small);
			us.insert(s.big);
//			us.insert(s.uSound);
			us.insert(s.uAct);
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}



	inline vector<ulong> getWdfFromTxtSkillSounds()
	{
		set<ulong> us;
		auto ss = getSkills();

		for (const auto& s : ss)
		{
			if (s.e == eSkill::月光)
			{
				continue;
			}
			us.insert(s.sound);
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}