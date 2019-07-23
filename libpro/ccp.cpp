#include "ccp.h"
#include "sBags.h"
////////////////////////////////////////////////////////////////////////// 面板属性
void ccp::apply(sAttribute& attr, int skilv)
{
	float _atk = 0, _def = 0, _mana = 0, _evade = 0;
	for (int i = skilv; i > 0; --i)
	{
		_atk += 1.5f + 0.02f * i;
		_def += 1 + 0.02f * i;
		_mana += 0.5f + 0.01 * i;
		_evade += 2 + 0.02f * i;
	}

	attr.atk.ori += _atk;
	attr.def.ori += _def;
	attr.mana.ori += _mana;
	attr.evade.ori += _evade;
}


void ccp::apply(sAttribute& attr, int fzlv, int fzIdx)
{
	if (fzIdx == 0)
	{
		attr.hpMax.ori += fzlv * 5;
	}
	else if (fzIdx == 1)
	{
		attr.hpMax.per += fzlv;
	}
	else if (fzIdx == 2)
	{
		attr.mpMax.per += fzlv;
	}
}


void ccp::apply(sAttribute& attr, const sPoint& point)
{
	float _atk, _def, _hp, _mana, _mp, _speed, _evade, _hit;
	_atk = point.str/* * 7 / 9*/;
	_def = point.dex * 5 / 3;
	_hp = point.body * 5;
	_mana = point.mag * 7 + point.body * 3 + point.str * 4 + point.dex * 2;
	_mana /= 10;
	_mp = point.mag * 3;
	_speed = point.agi * 7 + point.body + point.str + point.dex;
	_speed /= 10;
	_evade = point.agi;
	_hit = point.str * 7 / 3;

	attr.atk.ori += _atk;
	attr.def.ori += _def;
	attr.hpMax.ori += _hp;
	attr.mpMax.ori += _mp;
	attr.mana.ori += _mana;
	attr.speed.ori += _speed;
	attr.hit.ori += _hit;
	attr.evade.ori += _evade;
}


void ccp::apply(sAttribute& attr, const sPoint& point, const sZz& zz, int lv)
{
	float _atk, _def, _hp, _mana, _mp, _speed, _evade, _hit;
	int _grow = zz.grow100;
	_atk = lv * zz.atk * (1400 + 10 * _grow) / 750000;
	_atk += point.str * _grow / 100;

	_def = (lv * zz.def) * 19 / 7500;
	_def += (point.dex * _grow * 4) / 300;

	_hp = (lv * zz.hp) / 1000;
	_hp += point.body * _grow * 6 / 100;

	_mana = lv * (zz.mag + 1640) * (_grow + 100) / 75000;
	_mana += point.body * 3 + point.mag * (7 + 3) + point.str * 4 + point.dex * 2;
	_mana /= 10;

	_mp = lv * zz.mag / 500 + _grow * point.mag * 3 / 100;

	_speed = zz.speed * point.agi / 1000;
	_evade = zz.evoid * point.agi / 300;

	_hit = sAttribute::cHit40 + _atk / 2;
	_hit += point.str * 5 / 2;

	attr.atk.ori += _atk;
	attr.def.ori += _def;
	attr.hpMax.ori += _hp;
	attr.mpMax.ori += _mp;
	attr.mana.ori += _mana;
	attr.speed.ori += _speed;
	attr.hit.ori += _hit;
	attr.evade.ori += _evade;
}



////////////////////////////////////////////////////////////////////////// 内置属性
std::string ccp::apply(sPropertyInfo& info, int3& speed, eMenpai menpai, int rlv /* = -1 */)
{
	switch (menpai)
	{
	case eMenpai::大唐官府:
		if (rlv >= 0)
		{
			// 穿刺
			info.pierceRate.d1 += 10;
		}
		return "+物理穿刺";
	case eMenpai::化生寺:
		if (rlv >= 0)
		{
			// 治疗
			info.damageCure.add.d1 += rlv;
			info.damageCure.add.d2 += rlv;
			info.criRateCure.d1 += 15;
		}
		return "+慈悲";
	case eMenpai::方寸山:
		if (rlv >= 0)
		{
			// 驱鬼
			info.ghost.d2 += 50;
		}
		return "+驱鬼";
	case eMenpai::女儿村:
		if (rlv >= 0)
		{
			// 速度
			speed.ori += rlv;
		}
		return "+速度";
	case eMenpai::五庄观:
		if (rlv >= 0)
		{
			// 格挡
			info.parryRate.d1 += 10;
		}
		return "+格挡";
	case eMenpai::狮驼岭:
		if (rlv >= 0)
		{
			// 吸血
			info.blood.rate.d1 += 20;
			info.blood.per.d1 += 10;
		}
		return "+吸血";
	case eMenpai::魔王寨:
		if (rlv >= 0)
		{
			// 波动
			info.magicWave.d1 += 15;
		}
		return "+法术波动";
		break;
	case eMenpai::盘丝岭:
		if (rlv >= 0)
		{
			// 防暗器
			info.damageArm.per2 += 100;
		}
		return "+暗器免疫";
	case eMenpai::阴曹地府:
		if (rlv >= 0)
		{
			// 抗封
			info.hitRateSeal.dper += 20;
		}
		return "+封印抵抗";
	case eMenpai::东海龙宫:
		if (rlv >= 0)
		{
			// 法术穿刺
			info.pierceRateMaigc.d1 += 10;
		}
		return "+法术穿刺";
	case eMenpai::普陀山:
		if (rlv >= 0)
		{
			// 五行
			int v = 15;
			info.fire.rate.d1 += v;
			info.soil.rate.d1 += v;
			info.water.rate.d1 += v;
			info.thunder.rate.d1 += v;
		}
		return "+五行吸收";
	case eMenpai::天宫:
		if (rlv >= 0)
		{
			// 神迹
			info.liveStoreRate.d1 += 10;
		}
		return "+神迹";
	case eMenpai::凌波城:
		if (rlv >= 0)
		{
			// 暴击
			info.criRate.d1 += 5;
		}
		return "+物理暴击";
	case eMenpai::无底洞:
		if (rlv >= 0)
		{
			// 再生
			info.liveHp.d1 += rlv;
		}
		return "+再生";
	case eMenpai::神木林:
		if (rlv >= 0)
		{
			// 法连
			info.comboRateMagic.d1 += 5;
		}
		return "+法术连击";
	}
	return "";
}


void ccp::apply(sPropertyInfo& info, const sXl& xl)
{
	info.damage.per.d1 += xl.lvs[0] * 2;
	info.damage.per.d2 += xl.lvs[0] * 2;
	info.damage.add.d1 += xl.lvs[1] * 5;
	info.damage.add.d2 += xl.lvs[1] * 5;

	info.damageMagic.per.d1 += xl.lvs[2] * 2;
	info.damageMagic.per.d2 += xl.lvs[2] * 2;
	info.damageMagic.add.d1 += xl.lvs[3] * 5;
	info.damageMagic.add.d2 += xl.lvs[3] * 5;

	info.hitRateSeal.d1 += xl.lvs[2] * 3 / 2;
	info.hitRateSeal.d2 += xl.lvs[3] * 3 / 2;
}


enum eFaBao
{
	eFaBao0曼陀罗,
	eFaBao1干将莫邪,
	eFaBao2罗汉珠,
	eFaBao3赤焰,
//	eFaBao4万鬼幡,
	eFaBao5惊魂铃,
	eFaBao6混元伞,
	eFaBao7无魂傀儡,
	eFaBao8乾坤玄火塔,
	eFaBao9普渡,
	eFaBao10缩地尺,
	eFaBao11月光宝盒,
	eFaBao16隐蛊,
	eFaBao17周杰伦手办,
	eFaBao18时之环,
	eFaBao19通灵宝玉,
	eFaBao20聚宝盆,
	eFaBao21碧玉葫芦,
	eFaBao22神木宝鼎,
	eFaBao23八咫镜,
	eFaBao24嗜血幡,
	eFaBao25金甲仙衣,
	eFaBao26降魔斗篷,
	eFaBao27九幽,
	eFaBao28救命毫毛,
	eFaBao29镇海珠,
	eFaBao30五火神焰印,
	eFaBao31忘情,
	eFaBao32慈悲,
	eFaBao33梦蝶,
};

void ccp::apply(sPropertyInfo& info, int3& speed, int fabao)
{
	switch (fabao)
	{
	case eFaBao0曼陀罗:
		info.damagePosion.per.d1 += 5;
		break;
	case eFaBao1干将莫邪:
		info.damage.add.d1 += 50;
		break;
	case eFaBao2罗汉珠:
		info.mpSave.d1 += 10;
		break;
	case eFaBao3赤焰:
		info.liveMp.d1 += 10;
		break;
	case eFaBao5惊魂铃:
		info.ghost.d2 += 10;
		break;
	case eFaBao6混元伞:
		info.stabMagic.rate.d1 += 20;
		info.stabMagic.per.d1 += 5;
		break;
	case eFaBao7无魂傀儡:
		break;
	case eFaBao8乾坤玄火塔:
		info.liveAp.d1 += 2;
		break;
	case eFaBao9普渡:
		info.fire.rate.d1 += 5;
		info.water.rate.d1 += 5;
		info.soil.rate.d1 += 5;
		info.thunder.rate.d1 += 5;

		info.fire.per.d1 += 5;
		info.water.per.d1 += 5;
		info.soil.per.d1 += 5;
		info.thunder.per.d1 += 5;
		break;
	case eFaBao10缩地尺:
		break;
	case eFaBao11月光宝盒:
		break;
	case eFaBao16隐蛊:
		break;
	case eFaBao17周杰伦手办:
		speed.ori += 30;
		break;
	case eFaBao18时之环:
		info.gad.rate.d1 += 5;
		break;
	case eFaBao19通灵宝玉:
		break;
	case eFaBao20聚宝盆:
		break;
	case eFaBao21碧玉葫芦:
		info.damageCure.add.d1 += 64;
		break;
	case eFaBao22神木宝鼎:
		info.damageCure.add.d2 += 64;
		break;
	case eFaBao23八咫镜:
		info.stab.rate.d1 += 20;
		info.stab.per.d1 += 5;
		break;
	case eFaBao24嗜血幡:
		info.blood.rate.d1 += 5;
		info.blood.per.d1 += 5;
		break;
	case eFaBao25金甲仙衣:
		info.parryRate.d1 += 5;
		break;
	case eFaBao26降魔斗篷:
		info.parryRateMagic.d1 += 5;
		break;
	case eFaBao27九幽:
		info.damageCure.per.d1 += 2;
		info.damageCure.per.d2 += 2;
		break;
	case eFaBao28救命毫毛:
		info.liveLifeRate.d1 += 5;
		break;
	case eFaBao29镇海珠:
		info.pierceRateMaigc.d1 += 5;
		break;
	case eFaBao30五火神焰印:
		info.criRateMagic.d1 += 5;
		break;
	case eFaBao31忘情:
		break;
	case eFaBao32慈悲:
		info.criRateCure.d1 += 5;
		break;
	case eFaBao33梦蝶:
		break;
	}
}


////////////////////////////////////////////////////////////////////////// 装备
void ccp::apply(sPropertyInfo& info, sAttribute& attr, sPoint& point, const cEquip::sPropertys& pros)
{
	int v;
	forr(pros, k)
	{
		v = pros[k].value;
		switch (pros[k].pro)
		{
		case eProPerty::None:break;
		case eProPerty::伤害:attr.atk.ori += v; break;
		case eProPerty::命中:
			attr.hit.ori += v; 
			attr.atk.ori += v * 7 / 2;
			break;
		case eProPerty::命率:info.hitRate.d1 += v; break;
		case eProPerty::防御:attr.def.ori += v; break;
		case eProPerty::魔法:attr.mpMax.ori += v; break;
		case eProPerty::灵力:attr.mana.ori += v; break;
		case eProPerty::速度:attr.speed.ori += v; break;
		case eProPerty::气血:attr.hpMax.ori += v; break;
		case eProPerty::力量:point.str += v; break;
		case eProPerty::敏捷:point.agi += v; break;
		case eProPerty::体质:point.body += v; break;
		case eProPerty::魔力:point.mag += v; break;
		case eProPerty::耐力:point.dex += v; break;
		case eProPerty::水抗:info.water.rate.d1 += v; break;
		case eProPerty::火抗:info.fire.rate.d1 += v; break;
		case eProPerty::土抗:info.soil.rate.d1 += v; break;
		case eProPerty::雷抗:info.thunder.rate.d1 += v; break;
		case eProPerty::躲避:attr.evade.ori += v; break;
		case eProPerty::法伤:info.damageMagic.add.d1 += v; break;
		case eProPerty::法防:info.damageMagic.add.d2 += v; break;
		case eProPerty::法结:info.damageMagic.add.d1 += v; break;
		case eProPerty::物结:info.damage.add.d1 += v; break;
		case eProPerty::回复:info.damageCure.add.d2 += v; break;
		case eProPerty::愤怒:info.liveAp.d1 += v; break;
		default:break;
		}
	}
}


void ccp::apply(sPropertyInfo& info, sAttribute& attr, sPoint& point, sTz& taozhuang, seSkis& specials, const sItems& equips)
{
	point.reset();
	specials.clear();

	std::map<eSki, int> ztMap;
	std::map<eSki, int> zjMap;
	taozhuang.rate = 0;

	bool isZhuijia;
	eSki eski;

	cEquip::sPropertys pros;

	forr(equips, k)
	{
		auto& e = equips[k];
		if (!e.isValid())
		{
			continue;
		}
		cEquip::apply(e, pros);
		apply(info, attr, point, pros);
		
		eski = cEquip::getTaoZhuang(e, isZhuijia);
		if (eski != eSki::eSkiNone)
		{
			auto pMap = isZhuijia ? (&zjMap) : (&ztMap);
			const auto& it = pMap->find(eski);
			if (it == ztMap.end())
			{
				pMap->insert(std::make_pair(eski, 1));
			}
			else
			{
				++it->second;
			}
		}

		if (cEquip::isGodAngry(e))
		{
			if (cEquip::isWeapon(e.getType()))
			{
				// 神佑
				info.gad.rate.d1 += 15;
			}
			else if (cEquip::isBelt(e.getType()))
			{
				// 愤怒
				info.apSave.d1 += 20;
			}
		}

		eski = cEquip::getSpecial(e);
		if (eski != eSki::eSkiNone)
		{
			specials.push_back(eski);
		}
	}

	for (const auto& zt : ztMap)
	{
		if (zt.second >= cEquip::c3)
		{
			taozhuang.ski = zt.first;
			taozhuang.rate = 100;
			taozhuang.lvGap = (zt.second == cEquip::c3) ? (-sSki::cGap) : (sSki::cGap);
			break;
		}
	}

	for (const auto& zj : zjMap)
	{
		if (zj.second >= cEquip::c3)
		{
			taozhuang.ski = zj.first;
			taozhuang.rate = 14 + (zj.second - cEquip::c3) * 8;
			taozhuang.lvGap = 0;
			break;
		}
	}
}


////////////////////////////////////////////////////////////////////////// 技能
void ccp::apply(sPropertyInfo& info, sAttribute& attr, eSkill ski, int lv)
{
	switch (ski)
	{
//	case eSkill::eSkiCover0:
	case eSkill::反击:
		info.counter.rate.d1 += 25;
		info.counter.per.d1 += 50;
		break;
	case eSkill::反击2:
		info.counter.rate.d1 += 35;
		info.counter.per.d1 += 100;
		break;
	case eSkill::反震:
		info.stab.rate.d1 += 25;
		info.stab.per.d1 += 25;
		break;
	case eSkill::反震2:
		info.stab.rate.d1 += 35;
		info.stab.per.d1 += 50;
		break;
	case eSkill::吸血:
		info.blood.rate.d1 += 100;
		info.blood.per.d1 += 15;
		break;
	case eSkill::吸血2:
		info.blood.rate.d1 += 100;
		info.blood.per.d1 += 25;
		break;
	case eSkill::连击:
		info.comboRate.d1 += 45;
		info.damage.per.d1 -= 25;
		break;
	case eSkill::连击2:
		info.comboRate.d1 += 55;
		info.damage.per.d1 -= 20;
		break;
	case eSkill::飞行:
		info.hitRate.d1 += 10;
		info.hitRate.d2 += 10;
		info.damageArm.per.d2 -= 50;
		break;
	case eSkill::飞行2:
		info.hitRate.d1 += 15;
		info.hitRate.d2 += 15;
		info.damageArm.per.d2 -= 20;
		break;
	case eSkill::夜战:
		//////////////////////////////////////////////////////////////////////////
		break;
	case eSkill::夜战2:
		//////////////////////////////////////////////////////////////////////////
		break;
	case eSkill::隐身:
		info.hide.d1 += 2;
		break;
	case eSkill::隐身2:
		info.hide.d2 += 5;
		break;
	case eSkill::感知:
	case eSkill::感知2:
		info.hide.d2 += cFF;
		break;
	case eSkill::再生:
		info.liveHp.d1 += lv;
		break;
	case eSkill::再生2:
		info.liveHp.d1 += lv * 2;
		break;
	case eSkill::冥思:
		info.liveMp.d1 += lv / 4;
		break;
	case eSkill::冥思2:
		info.liveMp.d1 += lv / 2;
		break;
	case eSkill::慧根:
		info.mpSave.d1 += 25;
		break;
	case eSkill::慧根2:
		info.mpSave.d1 += 50;
		break;
	case eSkill::必杀:
		info.criRate.d1 += 10;
		break;
	case eSkill::必杀2:
		info.criRate.d1 += 20;
		break;
	case eSkill::幸运:
		info.criRate.d2 += cFF;
		break;
	case eSkill::幸运2:
		info.criRate.d2 += cFF;
		info.hitRateMagic.d2 += 10;
		break;
	case eSkill::神迹:
		info.liveStoreRate.d1 += cFF;
		break;
	case eSkill::神迹2:
		info.hitRateSeal.dper += cFF;
		info.hitRatePosion.dper += cFF;
		break;
	case eSkill::招架:
		info.parryRate.d1 += 5;
		break;
	case eSkill::招架2:
		info.parryRate.d1 += 10;
		break;
	case eSkill::永恒:
		info.buffTimeAdd.d1 += 3;
		break;
	case eSkill::永恒2:
		info.buffTimeAdd.d2 += 6;
		break;
	case eSkill::敏捷:
		attr.speed.per += 10;
		break;
	case eSkill::敏捷2:
		attr.speed.per += 20;
		break;
	case eSkill::强力:
		attr.atk.ori += lv / 2;
		break;
	case eSkill::强力2:
		attr.atk.ori += lv;
		break;
	case eSkill::防御:
		attr.def.ori += lv / 2;
		break;
	case eSkill::防御2:
		attr.def.ori += lv;
		break;
	case eSkill::偷袭:
		info.stab.rate.d2 += cFF;
		info.counter.rate.d2 += cFF;
		break;
	case eSkill::偷袭2:
		info.stab.rate.d2 += cFF;
		info.counter.rate.d2 += cFF;
		info.damage.per.d1 += 5;
		break;
	case eSkill::毒:
		info.hitRatePosion.d1 += 10;
		break;
	case eSkill::毒2:
		info.hitRatePosion.d1 += 15;
		break;
	case eSkill::驱鬼:
		info.ghost.d2 += 50;
		break;
	case eSkill::驱鬼2:
		info.ghost.d2 = 100;
		break;
	case eSkill::鬼魂术:
		info.ghost.d1 = 8;
		info.hitRateSeal.dper += cFF;
		info.hitRatePosion.dper += cFF;
		break;
	case eSkill::鬼魂术2:
		info.ghost.d1 = 5;
		info.hitRateSeal.dper += cFF;
		info.hitRatePosion.dper += cFF;
		break;
	case eSkill::魔之心:
		info.damageMagic.per.d1 += 10;
		break;
	case eSkill::魔之心2:
		info.damageMagic.per.d1 += 20;
		break;
	case eSkill::神佑复生:
		info.gad.rate.d1 += 20;
		info.gad.per.d1 += 50;
		break;
	case eSkill::神佑复生2:
		info.gad.rate.d1 += 30;
		info.gad.per.d1 += 100;
		break;
	case eSkill::精神集中:
		info.hitRateSeal.dper += 10;
		info.hitRatePosion.dper += 10;
		break;
	case eSkill::精神集中2:
		info.hitRateSeal.dper += 20;
		info.hitRatePosion.dper += 20;
		break;
	case eSkill::否定信仰:
		info.gad.rate.d2 += 10;
		break;
	case eSkill::否定信仰2:
		info.gad.rate.d2 += 20;
		break;
	case eSkill::法术连击:
		info.comboRateMagic.d1 += 15;
		break;
	case eSkill::法术连击2:
		info.comboRateMagic.d1 += 25;
		break;
	case eSkill::法术暴击:
		info.criRateMagic.d1 += 10;
		break;
	case eSkill::法术暴击2:
		info.criRateMagic.d1 += 20;
		break;
	case eSkill::法术波动:
		info.magicWave.d1 += 10;
		break;
	case eSkill::法术波动2:
		info.magicWave.d1 += 20;
		break;
	case eSkill::迟钝:
		attr.speed.per -= 50;
		break;
	case eSkill::迟钝2:
		attr.speed.per -= 80;
		break;
	case eSkill::雷属性吸收:
		info.thunder.rate.d2 += 20;
		info.thunder.per.d2 += 20;
		break;
	case eSkill::雷属性吸收2:
		info.thunder.rate.d2 += 30;
		info.thunder.per.d2 += 30;
		break;
	case eSkill::土属性吸收:
		info.soil.rate.d2 += 20;
		info.soil.per.d2 += 20;
		break;
	case eSkill::土属性吸收2:
		info.soil.rate.d2 += 30;
		info.soil.per.d2 += 30;
		break;
	case eSkill::火属性吸收:
		info.fire.rate.d2 += 20;
		info.fire.per.d2 += 20;
		break;
	case eSkill::火属性吸收2:
		info.fire.rate.d2 += 30;
		info.fire.per.d2 += 30;
		break;
	case eSkill::水属性吸收:
		info.water.rate.d2 += 20;
		info.water.per.d2 += 20;
		break;
	case eSkill::水属性吸收2:
		info.water.rate.d2 += 20;
		info.water.per.d2 += 20;
		break;
	case eSkill::盾气: // 盾气
		//////////////////////////////////////////////////////////////////////////
		break;
	case eSkill::盾气2:
		//////////////////////////////////////////////////////////////////////////
		break;
	case eSkill::法术抵抗:
		info.damageMagic.per.d2 += 15;
		break;
	case eSkill::法术抵抗2:
		info.damageMagic.per.d2 += 15;
		break;
	case eSkill::合纵:
		info.pierceRate.d1 += 4;
		break;
	case eSkill::合纵2:
		info.pierceRate.d1 += 8;
		break;
		//	case eSkill::eSkiCoverEnd:
	case eSkill::弱点火:
		info.fire.rate.d2 -= cFF;
		info.fire.per.d2 += 50;
		break;
	case eSkill::弱点水:
		info.water.rate.d2 -= cFF;
		info.water.per.d2 += 50;
		break;
	case eSkill::弱点土:
		info.soil.rate.d2 -= cFF;
		info.soil.per.d2 += 50;
		break;
	case eSkill::弱点雷:
		info.thunder.rate.d2 -= cFF;
		info.thunder.per.d2 += 50;
		break;
	case eSkill::移花接木:
		info.damageArm.per.d2 += 200;
		break;
	case eSkill::灵能激发:
		//////////////////////////////////////////////////////////////////////////
		break;
	case eSkill::嗜血追击:
		break;
	case eSkill::法力陷阱:
		info.stabMagic.rate.d1 += 35;
		info.stabMagic.per.d1 += 50;
		break;
	case eSkill::须弥真言:
		//	damageMagic.add.d1 += point.mag * 2 / 5;
		break;
	case eSkill::从天而降:
		//////////////////////////////////////////////////////////////////////////
		break;
	case eSkill::灵山禅语:
// 		damageMagic.add.d2 += point.mag;
// 		{
// 			int mana = lv * (2500 + 1640) * (120 + 100) / 75000;
// 			mana += point.body * 3 + point.mag * 7 + point.str * 4 + point.dex * 2;
// 			mana /= 10;
// 			damageMagic.add.d1 -= mana;
// 		}
		break;
	case eSkill::千钧一怒:
		break;
	case eSkill::浮云神马:
		break;
	case eSkill::苍鸾怒击:
		break;
	case eSkill::龙魂:
		break;
	case eSkill::大快朵颐:
		break;
	}
}

void ccp::apply(sPropertyInfo& info, sAttribute& attr, const sPoint& point, const seSkis& sekis, int lv)
{
	// 技能互斥
	std::set<eSki> unComs;
	forr(sekis, k)
	{
		const auto& e = sekis[k];
		if (e >= eSkill::eSkiCover0 && e <= eSkill::eSkiCoverEnd)
		{
			if ((((int)e) % 2) == 1)
			{
				unComs.insert((eSkill)(((int)e) - 1));
			}
		}
		if (e == eSkill::神迹 || e == eSkill::神迹2)
		{
			unComs.insert(eSkill::精神集中);
			unComs.insert(eSkill::精神集中2);
		}
		else if (e == eSkill::鬼魂术 || e == eSkill::鬼魂术2)
		{
			unComs.insert(eSkill::神佑复生);
			unComs.insert(eSkill::神佑复生2);
		}
		else if (e == eSkill::迟钝 || e == eSkill::迟钝2)
		{
			unComs.insert(eSkill::敏捷);
			unComs.insert(eSkill::敏捷2);
		}
		else if (e == eSkill::弱点火)
		{
			unComs.insert(eSkill::火属性吸收);
			unComs.insert(eSkill::火属性吸收2);
		}
		else if (e == eSkill::弱点水)
		{
			unComs.insert(eSkill::水属性吸收);
			unComs.insert(eSkill::水属性吸收2);
		}
		else if (e == eSkill::弱点土)
		{
			unComs.insert(eSkill::土属性吸收);
			unComs.insert(eSkill::土属性吸收2);
		}
		else if (e == eSkill::弱点雷)
		{
			unComs.insert(eSkill::雷属性吸收);
			unComs.insert(eSkill::雷属性吸收2);
		}
	}
	std::set<eSki> ski2s;
	forr(sekis, k)
	{
		if (!txtSkill::isEd(sekis[k]))
		{
			continue;
		}
		const auto& e = sekis[k];
		if (unComs.find(e) == unComs.end())
		{
			ski2s.insert(e);
		}
	}

	for (const auto& e : sekis)
	{
		switch (e)
		{
	//	case eSkill::eSkiCover0:
		case eSkill::夜战:
			//////////////////////////////////////////////////////////////////////////
			break;
		case eSkill::夜战2:
			//////////////////////////////////////////////////////////////////////////
			break;

		case eSkill::盾气: // 盾气
			//////////////////////////////////////////////////////////////////////////
			break;
		case eSkill::盾气2:
			//////////////////////////////////////////////////////////////////////////
			break;

	//	case eSkill::eSkiCoverEnd:
		case eSkill::灵能激发:
			//////////////////////////////////////////////////////////////////////////
			break;
		case eSkill::嗜血追击:
			break;
	//	case eSkill::法力陷阱:
		case eSkill::须弥真言:
			info.damageMagic.add.d1 += point.mag * 2 / 5;
			break;
		case eSkill::从天而降:
			//////////////////////////////////////////////////////////////////////////
			break;
		case eSkill::灵山禅语:
			info.damageMagic.add.d2 += point.mag;
			{
				int mana = lv * (2500 + 1640) * (120 + 100) / 75000;
				mana += point.body * 3 + point.mag * 7 + point.str * 4 + point.dex * 2;
				mana /= 10;
				info.damageMagic.add.d1 -= mana;
			}
			break;
		case eSkill::千钧一怒:
			break;
		case eSkill::浮云神马:
			break;
		case eSkill::苍鸾怒击:
			break;
		case eSkill::龙魂:
			break;
		case eSkill::大快朵颐:
			break;
	//	case eSkill::eSkiedEnd:
		default:
			apply(info, attr, e, lv);
			break;
		}
	}
}


////////////////////////////////////////////////////////////////////////// 主属性
void ccp::apply(sPropertys& pros, const sProperty* pro)
{
	sPropertyInfo& info = pros.info;
	sAttribute& attr = pros.attr;
	info.resetCri();
	attr.reset();

	sPoint& point = pros.point;
	// 先算好点数
	point.reset(sPoint::c10);

	sTz& taozhuang = pros.taozhuang;
	seSkis& specials = pros.specials;
	// 装备
	sPoint point2;
	apply(info, attr, point2, taozhuang, specials, pro->equips);
	point += point2;
	point2 = pro->point + point;
	if (pro->ispet)
	{
		// 属性
		apply(attr, point2, pro->zz, pro->lv);
		// 内丹
		auto& fz = ((sProperty*)pro)->fuzhus;
		fz[0] = pro->lv;
		fz[1] = std::max(0, pro->zz.grow100 - 100);
	}
	else
	{
		// 属性
		apply(attr, point2);
		// 师门技能
		apply(attr, pro->getSkiLv());
		// 门派特色
		apply(info, attr.speed, pro->menpai, pro->getSkiLv());
		// 法宝
		const auto& fabaos = (dynamic_cast<const sRole*>(pro))->fabaos;
		for (const auto& fb : fabaos)
		{
			if (fb.isValid() && fb.getType() == eIcon::法宝f)
			{
				apply(info, attr.speed, fb.getId());
			}
		}
	}
	// 辅助
	forv(pro->fuzhus, k)
	{
		apply(attr, pro->fuzhus[k], k);
	}
	// 修炼
	apply(info, pro->xl);
	seSkis skis;
	for (const auto& ski : pro->skis)
	{
		skis.push_back(ski.getSki());
	}
	// 被动技能
	apply(info, attr, point2, skis, pro->lv);
}


void ccp::apply(sPropertys& pros, const sProperty& pro)
{
	apply(pros, &pro);
}

void ccp::fillHpMp(sProperty& pro)
{
	sPropertys pros;
	apply(pros, pro);
	pro.hp = pro.hp2 = pros.attr.hpMax;
	pro.mp = pros.attr.mpMax;
}



bool ccp::lvup(sProperty& pro, bool onlyCheck)
{
	if (pro.lv >= (pro.ispet ? ccp::lv180 : ccp::lv175))
	{
		return false;
	}

	int expMax = sExp::getExp(pro.lv + 1, pro.ispet);

	if (pro.exp < expMax)
	{
		return false;
	}

	if (!onlyCheck)
	{
		++pro.lv;
		pro.exp.add(-expMax);
		pro.point.lvup();
	}
	return true;
}


bool ccp::lvdown(sProperty& pro, bool onlyCheck)
{
	if (pro.lv <= 0)
	{
		return false;
	}
	forr(pro.equips, k)
	{
		const auto& e = pro.equips[k];
		if (e.getCount() != 1)
		{
			continue;
		}
		if (cEquip::getTakeLv(e) >= pro.lv)
		{
			return false;
		}
	}
	if (!pro.point.lvdown(true))
	{
		return false;
	}
	if (!onlyCheck)
	{
		pro.point.lvdown(false);
		pro.exp.add(sExp::getExp(pro.lv, pro.ispet));
		--pro.lv;
	}
	return true;
}


bool ccp::lvdown(sRole& role)
{
	int xlv = sXl::getLv(role.lv);
	forr(role.xl.lvs, k)
	{
		while (role.xl.lvs[k] > xlv)
		{
			if (role.xl.lvdown(k, false))
			{
				sBags::getInstance()->money.add(sXl::c2000);
			}
		}
	}
	forr(role.xlbb.lvs, k)
	{
		while (role.xlbb.lvs[k] > xlv)
		{
			if (role.xlbb.lvdown(k, false))
			{
				sBags::getInstance()->money.add(sXl::c2000);
			}
		}
	}

	while (role.skilv > role.lv + sSki::cGap)
	{
		role.exp.add(sSki::getExp(role.skilv));
		sBags::getInstance()->money.add(sSki::getMoney(role.skilv));
		--role.skilv;
	}
	if (!role.setPet(role.fight, true))
	{
		role.unPet();
	}
	return true;
}



bool ccp::addSki(sSkis& skis, eMenpai e, bool normal)
{
	if (e == eMenpai::None)
	{
		return false;
	}
	bool checkValid = true;
	static std::map<eMenpai, eSkill> s_begin;
	static std::map<eMenpai, eSkill> s_end;
	if (s_begin.empty())
	{
		s_begin.insert(std::make_pair(eMenpai::大唐官府, eSkill::eDt0));
		s_begin.insert(std::make_pair(eMenpai::化生寺,eSkill::eHs0));
		s_begin.insert(std::make_pair(eMenpai::女儿村, eSkill::eNe0));
		s_begin.insert(std::make_pair(eMenpai::方寸山, eSkill::eFc0));
		s_begin.insert(std::make_pair(eMenpai::狮驼岭, eSkill::eSt0));
		s_begin.insert(std::make_pair(eMenpai::魔王寨, eSkill::eMw0));
		s_begin.insert(std::make_pair(eMenpai::盘丝岭, eSkill::ePs0));
		s_begin.insert(std::make_pair(eMenpai::阴曹地府, eSkill::eDf0));
		s_begin.insert(std::make_pair(eMenpai::东海龙宫, eSkill::eLg0));
		s_begin.insert(std::make_pair(eMenpai::五庄观, eSkill::eWz0));
		s_begin.insert(std::make_pair(eMenpai::普陀山, eSkill::ePt0));
		s_begin.insert(std::make_pair(eMenpai::天宫, eSkill::eTg0));
		s_begin.insert(std::make_pair(eMenpai::凌波城, eSkill::eLb0));
		s_begin.insert(std::make_pair(eMenpai::无底洞, eSkill::eWd0));
		s_begin.insert(std::make_pair(eMenpai::神木林, eSkill::eSm0));

		s_end.insert(std::make_pair(eMenpai::大唐官府, eSkill::eDtEnd));
		s_end.insert(std::make_pair(eMenpai::化生寺, eSkill::eHsEnd));
		s_end.insert(std::make_pair(eMenpai::女儿村, eSkill::eNeEnd));
		s_end.insert(std::make_pair(eMenpai::方寸山, eSkill::eFcEnd));
		s_end.insert(std::make_pair(eMenpai::狮驼岭, eSkill::eStEnd));
		s_end.insert(std::make_pair(eMenpai::魔王寨, eSkill::eMwEnd));
		s_end.insert(std::make_pair(eMenpai::盘丝岭, eSkill::ePsEnd));
		s_end.insert(std::make_pair(eMenpai::阴曹地府, eSkill::eDfEnd));
		s_end.insert(std::make_pair(eMenpai::东海龙宫, eSkill::eLgEnd));
		s_end.insert(std::make_pair(eMenpai::五庄观, eSkill::eWzEnd));
		s_end.insert(std::make_pair(eMenpai::普陀山, eSkill::ePtEnd));
		s_end.insert(std::make_pair(eMenpai::天宫, eSkill::eTgEnd));
		s_end.insert(std::make_pair(eMenpai::凌波城, eSkill::eLbEnd));
		s_end.insert(std::make_pair(eMenpai::无底洞, eSkill::eWdEnd));
		s_end.insert(std::make_pair(eMenpai::神木林, eSkill::eSmEnd));
	}
	int begin = (int)s_begin.at(e);
	int end = (int)s_end.at(e);
	eSki eski;
	sSki ski;
	const auto& costs = txtSkill::getInstance()->getCosts();
	for (int mp = begin; mp <= end; ++mp)
	{
		eski = (eSki)mp;
		if (!normal && txtSkill::isF1(eski))
		{
			continue;
		}
		if (checkValid)
		{
			const auto& it = costs.find(eski);
			if (it == costs.end())
			{
				continue;
			}
			if (it->second.ignore)
			{
				continue;
			}
		}
		ski.setData(eski);
		skis.push_back(ski);
	}
	return true;
}


bool ccp::addSki(sSkis& skis, sSki ski, int idx /* = -1 */)
{
	int k;
	int size = skis.size();
	for (k = 0; k < size; ++k)
	{
		if (skis[k].getSki() == ski.getSki())
		{
			break;
		}
	}
	if (idx < 0 || idx >= size)
	{
		if (k < size)
		{
			skis[k] = ski;
		}
		else
		{
			skis.push_back(ski);
		}
	}
	else
	{
		if (k < size)
		{
			skis[k] = ski;
		}
		else
		{
			skis[idx] = ski;
		}
	}
	return true;
}


int ccp::getEquipsAtk(const sItems& equips)
{
	int atk = 0;
	cEquip::sPropertys pros;
	forr(equips, k)
	{
		auto& e = equips[k];
		if (e.getCount() != 1)
		{
			continue;
		}
		cEquip::apply(e, pros);
		forr(pros, k)
		{
			if (!pros[k].isVaild())
			{
				continue;
			}
			if (pros[k].pro == eProPerty::伤害)
			{
				atk += pros[k].value;
			}
		}
	}
	return atk;
}


std::string ccp::getMenpaiName(eMenpai menpai)
{
	switch (menpai)
	{
	case eMenpai::大唐官府:   return "大唐官府";
	case eMenpai::化生寺:	  return "化生寺";
	case eMenpai::女儿村:	  return "女儿村";
	case eMenpai::方寸山:	  return "方寸山";
	case eMenpai::狮驼岭:	  return "狮驼岭";
	case eMenpai::魔王寨:	  return "魔王寨";
	case eMenpai::盘丝岭:	  return "盘丝洞";
	case eMenpai::阴曹地府:	  return "阴曹地府";
	case eMenpai::东海龙宫:	  return "东海龙宫";
	case eMenpai::五庄观:	  return "五庄观";
	case eMenpai::普陀山:	  return "普陀山";
	case eMenpai::天宫:	      return "天宫";
	case eMenpai::凌波城:	  return "凌波城";
	case eMenpai::无底洞:	  return "无底洞";
	case eMenpai::神木林:	  return "神木林";
	}
	return "";
}

bool ccp::useItem(const sItem& item, sRole& role)
{
	return false;
}

bool ccp::useItem(const sItem& item, sProperty& pet)
{
	return false;
}
