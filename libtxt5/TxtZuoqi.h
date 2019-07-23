#pragma once
#include "eModel.h"
#include "TxtItem.h"

enum class eZuoqi
{
	±¦±´ºùÂ«,
	ÉñÆøÐ¡¹ê,
	ººÑª±¦Âí,
	»¶Ï²ÑòÑò,
	Ä§Á¦¶·ÊÞ,
	Åû¼×Õ½ÀÇ,
	ÏÐÔÆÒ°º×,
	ÔÆ÷ÈÏÉÂ¹,
	_8,
	_9,
	_10,
	_11,
	_12,
	_13,
	_14,
	_15,
	_16,
	_17,
	_18,
	_19,
	_20,
	_21,
	_22,
	_23,
	_24,
	_25,
	_26,
	_27,
	_28,
	_29,
	_30,
	_31,
	_32,
	_33,
	_34,
	_35,
	_36,
	_37,
	_38,
	_39,
	_40,
	_41,
	_42,
	_43,
	_44,
	_45,
	_46,
	_47,
	_48,
	_49,
	_50,
	_51,
	_52,
	_53,
	_54,
	_55,
	_56,
	_57,
	_58,
	_59,
	_60,
	_61,
	_62,
	_63,
	_64,
	_65,
	_66,
	_67,
	_68,
	_69,
	_70,
	_71,
	_72,
	_73,
	_74,
	_75,
	_76,
	_77,
	_78,
	_79,
	_80,
	_81,
	_82,
	_83,
	_84,
	_85,
	_86,
	_87,
	_88,
	_89,
	_90,
	_91,
	_92,
	_93,
	_94,
	_95,
	_96,
	_97,
	_98,
	_99,
	_100,
	_101,
	_102,
	_103,
	_104,
	_105,
	_106,
	_107,
	_108,
	_109,
	_110,
	_111,
	_112,
	_113,
	_114,
	_115,
	_116,
	_117,
	_118,
	_119,
	_120,
	_121,
	_122,
	_123,
	_124,
	_125,
	_126,
	_127,
	_128,
	_129,
	_130,
	_131,
	_132,
	_133,
	_134,
	_135,
	_136,
	_137,
	_138,
	_139,
	_140,
	_141,
	_142,
	_143,
	_144,
	_145,
	_146,
	_147,
	_148,
	_149,
	_150,
	_151,
};


namespace ctt
{
	struct sZuoqi
	{
		eZuoqi e;
		ulong stand;
		ulong walk;
		ulong color;
		ulong color2;
		std::string name;
		struct sModeuu
		{
			eModel master;
			ulong stand;
			ulong walk;
		};
		std::vector<sModeuu> masters;
	};




	struct sZqzs
	{
		eItem type;
		int id;
		ulong small;
		ulong big;
		ulong stand;
		ulong walk;
		ulong color;
		std::string name;
		struct sModeuu
		{
			eModel master;
			ulong stand;
			ulong walk;
		};
		std::vector<sModeuu> masters;
	};


	const vector<sZuoqi>& getZqs();

	const vector<sZqzs>& getZqzss();

	inline vector<ulong> getWdfFromTxtZq()
	{
		auto zs = getZqs();
		set<ulong> us;
		for (const auto& z : zs)
		{
			us.insert(z.stand);
			us.insert(z.walk);
			for (const auto& m : z.masters)
			{
				us.insert(m.stand);
				us.insert(m.walk);
			}
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}

	inline vector<ulong> getWdfFromTxtZqzs()
	{
		auto zs = getZqzss();
		set<ulong> us;
		for (const auto& z : zs)
		{
			us.insert(z.small);
			us.insert(z.big);
			us.insert(z.stand);
			us.insert(z.walk);
			for (const auto& m : z.masters)
			{
				us.insert(m.stand);
				us.insert(m.walk);
			}
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}