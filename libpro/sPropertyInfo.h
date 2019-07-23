#pragma once

// 对称数据
struct int2
{
	// 激发
	int d1 = 0;
	// 抗性
	int d2 = 0;

	// 我的激发 - 你的抗性
	int operator-(const int2& i)const
	{
		return d1 - i.d2;
	}
};


// 内置属性
struct sPropertyInfo
{
	// <触发率,百分比>
	// 比如: <反击触发率, 反击伤害为平时伤害的百分比>
	struct sRatePer
	{
		// 触发率 0~100
		int rate = 0;
		// 百分比 %
		int per = 0;
	};

	// <触发率,百分比> 专用对称数据结构
	struct sRatePer2
	{
		// 对称触发率
		int2 rate;
		// 对称百分比
		int2 per;

		sRatePer operator-(const sRatePer2& i)const
		{
			sRatePer s;
			s.rate = rate - i.rate;
			s.per = per - i.per;
			return s;
		}
	};

	// <+%,+值>
	// 比如: <伤害+10%, 伤害+10>
	struct sPerAdd
	{
		// 百分比 %
		int per = 0;
		// 附加
		int add = 0;
	};

	// 伤害计算 专用对称数据结构
	struct sPerAdd2
	{
		// 百分比 %
		int2 per;
		// 附加
		int2 add;
		// 附加抗性%
		int per2 = 0;

		sPerAdd operator-(const sPerAdd2& d)const
		{
			sPerAdd s;
			s.per = per - d.per;
			s.add = add - d.add;
			return s;
		}
	};

	// 命中率 专用数据结构
	struct sHit
	{
		// 激发
		int d1 = 0;
		// 抗性
		int d2 = 0;
		// 附加抗性, 额外独立计算
		int dper = 0;
		int operator-(const int2& i)const
		{
			return d1 - i.d2;
		}
	};

	// 特殊 用回调?
	// 夜战 高级晚上+5%
	// 隐身时候降伤害
	// 灵能激发
	// 嗜血追击
	// 盾气
	// 神马浮云
	// 苍穹
	// 从天
	// 千钧
	// 龙魂
	// 大块

	// 再生
	int2 liveHp;
	// 冥思
	int2 liveMp;
	// 愤怒(乾坤玄火塔)
	int2 liveAp;
	// 神迹
	int2 liveStoreRate;
	// 救命毫毛
	int2 liveLifeRate;
	// 慧根25
	int2 mpSave;
	// 愤怒腰带特效 20
	int2 apSave;
	// 法术波动
	int2 magicWave;
	// 永恒
	int2 buffTimeAdd;
	// 临时愤怒
	int2 startAp;
	// 隐身(d1回合数)
	int2 hide;
	// 鬼魂(d1复活间隔 d2驱鬼附加伤害比)
	int2 ghost;



	// 命中率 物理
	sHit hitRate;
	// 命中率 法术
	sHit hitRateMagic;
	// 命中率 封印
	sHit hitRateSeal;
	// 命中率 毒
	sHit hitRatePosion;
	// 命中率 暗器
	sHit hitRateArm;



	// 伤害计算 物理
	sPerAdd2 damage;
	// 伤害计算 法术
	sPerAdd2 damageMagic;
	// 伤害计算 治疗
	sPerAdd2 damageCure;
	// 伤害计算 毒
	sPerAdd2 damagePosion;
	// 伤害计算 暗器
	sPerAdd2 damageArm;
	// 伤害计算 固定伤害
	sPerAdd2 damageFix;



	// 神佑 <触发率,百分比>
	sRatePer2 gad;

	// 格挡 物理
	int2 parryRate;
	// 格挡 法术
	int2 parryRateMagic;

	// 必杀 物理
	int2 criRate;
	// 暴击 法术
	int2 criRateMagic;
	// 暴击 治疗
	int2 criRateCure;
	// 连击 物理
	int2 comboRate;
	// 连击 法术
	int2 comboRateMagic;
	// 穿刺 武器
	int2 pierceRate;
	// 穿刺 法术
	int2 pierceRateMaigc;
	// 反击(火甲术) <触发率,百分比>
	sRatePer2 counter;
	// 吸血 <触发率,百分比>
	sRatePer2 blood;
	// 反震 <触发率,百分比>
	sRatePer2 stab;
	// 法术反弹 <触发率,百分比>
	sRatePer2 stabMagic;
	// 溅射 <触发率,百分比>
	sRatePer2 spurt;

	// 五行火: rate正吸收  rate负弱点 
	sRatePer2 fire;
	// 五行土: rate正吸收  rate负弱点
	sRatePer2 soil;
	// 五行水: rate正吸收  rate负弱点
	sRatePer2 water;
	// 五行雷: rate正吸收  rate负弱点
	sRatePer2 thunder;

	void resetCri();
};
