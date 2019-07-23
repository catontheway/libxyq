#pragma once
#include "_txtinc.h"

enum class eNpc
{
	阿米国师,
	百晓星君,
	宝石商人,
	宝象国国王,
	陈妈妈,
	程夫人,
	吹牛王,
	崔判官,
	翠花,
	当铺老板,
	赌霸天,
	房都尉,
	冯铁匠,
	服装店老板,
	符石道人,
	海产收购商,
	简师爷,
	轿夫,
	教书先生,
	金圣宫,
	空慈方丈,
	老孙头,
	乐器店老板,
	雷黑子,
	李世民,
	刘老爹,
	柳飞絮,
	鲁成,
	孟大娘,
	南极仙翁,
	樵夫,
	秦琼,
	清风,
	穷汉,
	太上老君,
	王大嫂,
	赵元宝,
	香料店老板,
	小木匠,
	小桃红,
	许大娘,
	太白金星,
	药店老板,
	驿站老板,
	月老,
	张老财,
	张老头,
	招罗弟,
	赵捕头,
//	郑镖头 = 49, 
	钟馗 = 50,
	周猎户,
	朱紫校尉,
//	白晶晶 = 53,
	春三十娘 = 54,
	二大王,
	三大王,
	婆婆,
	大宝,
	哪吒,
	满天星,
	玉皇大帝,
	白无常,
	酒店老板,
	管家,
	灵鼠娃娃,
	火焰山土地 = 66,
	// 金圣宫
	仓库管理员 = 68,
	守门天将,
	嫦娥,
	王母娘娘,
	至尊宝,
	红毛猿,
	唐僧,
//	有个和尚 = 75,
	黑无常 = 76,
	罗道人,
	颜如羽,
	小宝,
	杨戟,
	魏征,
	云小奴,
	超级巫医,
	马副将,
	西梁女兵,
	巨子,
	西梁女国国王,
	莫夫人,
	小笛,
	上官丞相,
	袁天罡,
	小二,
	宝象国国王坐,
	莫爷爷,
	小宝贝,
	蒋大全,
	女,
	舞狮人,
	狮子,
	媒婆,
	轿子,
	骑马新郎,
	吹号手,
	女随从,
	宝象国国王2,
	禄星,
	禄星2,
	福星,
	福星2,
	金圣宫2,
	小西天长和尚,
	小西天和尚,
	二郎神,
	铁匠,
	酒仙,
	小白龙,
//	空度禅师 = 116,
	桃树 = 118,
	道观,
	雪人,
	雪人2,
	雪人3,
	雪人4,
	雪人5,
	宝箱,
// 	巫奎虎,
// 	地涌夫人,
// 	二郎神,
	生肖鼠 = 49,
	生肖牛 = 53,
	生肖虎 = 67,
	生肖兔 = 75,
	生肖龙 = 117,
	生肖蛇 = 126,
	生肖马,
	生肖羊,
	生肖猴,
	生肖鸡,
	生肖狗,
	生肖猪,
	// 133 空档
	班主 = 134,
	剑侠客,
	马猴,
	花儿,
	小龙,
	小狗,
	仙鹤,
	小象,
	小虎,
	GM男,
	GM女,
	传送,
};


namespace ctt
{

	struct sNpc
	{
		ulong stand;
		ulong walk;
		ulong dialog;
		eNpc e;
		std::string name;
	};



	const vector<sNpc>& getNpcs();


	inline vector<ulong> getWdfFromTxtNpcStandWalks()
	{
		auto ns = getNpcs();
		set<ulong> us;
		for (const auto& n : ns)
		{
			us.insert(n.stand);
			us.insert(n.walk);
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}

	inline vector<ulong> getWdfFromTxtNpcHeads()
	{
		auto ns = getNpcs();
		set<ulong> us;
		for (const auto& n : ns)
		{
			us.insert(n.dialog);
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}