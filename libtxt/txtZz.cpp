#include "txtZz.h"

ccc_txt_instance_cpp(txtZz);

void txtZz::init(eMod pet, int takelv, eAp ap)
{
	_zz = &_tables.at(pet);
	_zz->takelv = takelv;
	_zz->ap = ap;
	_skills = &_zz->skills;
}

void txtZz::insert(int atk, int def, int hp, int mp, int speed, int evoid, int grow)
{
	_zz->atk = atk;
	_zz->def = def;
	_zz->hp = hp;
	_zz->mp = mp;
	_zz->speed = speed;
	_zz->evoid = evoid;
	_zz->grow = grow;
}



void txtZz::insert(eSkill ski)
{
	_skills->push_back(ski);
	correctSkill();
}
void txtZz::insert(eSkill ski, eSkill ski2)
{ 
	insert(ski);
	_skills->push_back(ski2);
	correctSkill();
}
void txtZz::insert(eSkill ski, eSkill ski2, eSkill ski3)
{
	insert(ski, ski2);
	_skills->push_back(ski3);
	correctSkill();
}
void txtZz::insert(eSkill ski, eSkill ski2, eSkill ski3, eSkill ski4)
{
	insert(ski, ski2, ski3); 
	_skills->push_back(ski4);
	correctSkill();
}
void txtZz::insert(eSkill ski, eSkill ski2, eSkill ski3, eSkill ski4, eSkill ski5)
{
	insert(ski, ski2, ski3, ski4); 
	_skills->push_back(ski5);
	correctSkill();
}
void txtZz::insert(eSkill ski, eSkill ski2, eSkill ski3, eSkill ski4, eSkill ski5, eSkill ski6)
{
	insert(ski, ski2, ski3, ski4, ski5);
	_skills->push_back(ski6);
	correctSkill();
}
void txtZz::insert(eSkill ski, eSkill ski2, eSkill ski3, eSkill ski4, eSkill ski5, eSkill ski6, eSkill ski7)
{
	insert(ski, ski2, ski3, ski4, ski5, ski6);
	_skills->push_back(ski7);
	correctSkill();
}


void txtZz::correctSkill()
{
	auto& ski = _skills->back();
}


txtZz::txtZz()
{
	sZz zz;
	for (int e = (int)eMod::ePet0; e <= (int)eMod::ePetEnd; ++e)
	{
		_tables.insert(std::make_pair((eMod)e, zz));
	}

	init(eMod::e泡泡, 5, eAp::GiveMagic);
	insert(1320, 1380, 4200, 2160, 1320, 1320, 112);
	insert(eSkill::防御2, eSkill::幸运2, eSkill::连击, eSkill::精神集中, eSkill::再生);


	init(eMod::e大海龟, 5, eAp::GiveMagic);
	insert(1036, 1036, 3888, 1296, 907, 1425, 92);
	insert(eSkill::反震, eSkill::慧根, eSkill::幸运, eSkill::水属性吸收, eSkill::防御);


	init(eMod::e章鱼, 5, eAp::Atk);
	insert(1555, 907, 2592, 1296, 1425, 1296, 103);
	insert(eSkill::连击, eSkill::毒, eSkill::吸血, eSkill::水属性吸收, eSkill::弱点火);


	init(eMod::e海星, 5, eAp::GiveMagic);
	insert(1166, 1231, 2592, 1555, 1296, 1101, 92);
	insert(eSkill::慧根, eSkill::反震2, eSkill::水攻, eSkill::水属性吸收, eSkill::弱点火);


	init(eMod::e护卫, 5, eAp::Atk);
	insert(1231, 1101, 2916, 1944, 1296, 1296, 97);
	insert(eSkill::反击, eSkill::必杀, eSkill::强力);


	init(eMod::e狸, 5, eAp::Atk);
	insert(1555, 972, 3110, 1296, 1490, 1425, 104);
	insert(eSkill::幸运, eSkill::偷袭, eSkill::必杀, eSkill::招架);


	init(eMod::e巨蛙, 5, eAp::Magic);
	insert(1166, 907, 2916, 1296, 1425, 1101, 92);
	insert(eSkill::慧根, eSkill::幸运, eSkill::水攻, eSkill::弱点火);


	init(eMod::e树怪, 5, eAp::Atk);
	insert(1425, 1425, 3564, 1425, 972, 1036, 92);
	insert(eSkill::反击, eSkill::感知, eSkill::驱鬼, eSkill::再生, eSkill::弱点火, eSkill::迟钝);


	init(eMod::e赌徒, 5, eAp::Atk);
	insert(1101, 1231, 3240, 1555, 1555, 1490, 97);
	insert(eSkill::反击, eSkill::偷袭);


	init(eMod::e强盗, 5, eAp::Atk);
	insert(1360, 1360, 3564, 1490, 1296, 1296, 103);
	insert(eSkill::连击, eSkill::烈火, eSkill::强力, eSkill::否定信仰);


	init(eMod::e海毛虫, 5, eAp::Atk);
	insert(1555, 972, 2592, 1296, 1425, 1296, 103);
	insert(eSkill::毒, eSkill::反震2, eSkill::必杀, eSkill::夜战, eSkill::弱点火);


	init(eMod::e大蝙蝠, 5, eAp::GiveMagic);
	insert(1166, 1231, 2721, 1944, 1620, 1620, 110);
	insert(eSkill::吸血, eSkill::感知2, eSkill::驱鬼, eSkill::飞行, eSkill::夜战, eSkill::弱点水);


	init(eMod::e山贼, 5, eAp::Atk);
	insert(1166, 1296, 3888, 1296, 1296, 1425, 104);
	insert(eSkill::招架, eSkill::偷袭, eSkill::强力, eSkill::否定信仰2);


	init(eMod::e野猪, 5, eAp::Atk);
	insert(1231, 1231, 4147, 1360, 1231, 1296, 104);
	insert(eSkill::感知, eSkill::感知2, eSkill::幸运2, eSkill::强力, eSkill::弱点土, eSkill::弱点火);


	init(eMod::e骷髅怪, 15, eAp::Atk);
	insert(1296, 1296, 3240, 1296, 1296, 1620, 105);
	insert(eSkill::鬼魂术, eSkill::弱点雷, eSkill::夜战, eSkill::土属性吸收);


	init(eMod::e羊头怪, 15, eAp::Atk);
	insert(1360, 1490, 3628, 1425, 1296, 1296, 105);
	insert(eSkill::必杀, eSkill::连击, eSkill::幸运, eSkill::永恒);


	init(eMod::e蛤蟆精, 15, eAp::Atk);
	insert(1490, 1231, 3564, 1296, 1425, 1425, 105);
	insert(eSkill::必杀, eSkill::毒);


	init(eMod::e狐狸精, 15, eAp::Atk);
	insert(1425, 1360, 3240, 1555, 1425, 1296, 105);
	insert(eSkill::夜战, eSkill::感知2, eSkill::慧根, eSkill::慧根2, eSkill::弱点雷);


	init(eMod::e老虎, 15, eAp::Atk);
	insert(1490, 1166, 3888, 1490, 1296, 1166, 105);
	insert(eSkill::连击, eSkill::驱鬼, eSkill::幸运, eSkill::强力);


	init(eMod::e黑熊, 15, eAp::Atk);
	insert(1231, 1425, 4536, 1425, 1166, 1425, 105);
	insert(eSkill::反击, eSkill::必杀, eSkill::强力, eSkill::防御, eSkill::迟钝);


	init(eMod::e花妖, 15, eAp::Magic);
	insert(1101, 1555, 4082, 1555, 1231, 1231, 107);
	insert(eSkill::感知, eSkill::慧根, eSkill::落岩, eSkill::防御, eSkill::水属性吸收);


	init(eMod::e牛妖, 25, eAp::Atk);
	insert(1620, 1101, 3240, 1231, 1425, 1036, 112);
	insert(eSkill::烈火, eSkill::反击2, eSkill::防御2, eSkill::慧根2);


	init(eMod::e小龙女, 25, eAp::Magic);
	insert(1231, 1490, 4147, 1944, 1555, 1166, 109);
	insert(eSkill::水攻, eSkill::水属性吸收2, eSkill::驱鬼2, eSkill::神佑复生, eSkill::慧根);


	init(eMod::e野鬼, 25, eAp::Atk);
	insert(1425, 1425, 4536, 1296, 1231, 1360, 104);
	insert(eSkill::夜战, eSkill::鬼魂术, eSkill::土属性吸收, eSkill::落岩);


	init(eMod::e狼, 25, eAp::Atk);
	insert(1555, 1036, 3888, 1296, 1620, 1581, 104);
	insert(eSkill::夜战, eSkill::连击, eSkill::连击2, eSkill::偷袭, eSkill::驱鬼);


	init(eMod::e虾兵, 25, eAp::Atk);
	insert(1296, 1490, 5184, 2592, 1166, 1555, 106);
	insert(eSkill::必杀2, eSkill::反击2, eSkill::水属性吸收, eSkill::驱鬼);


	init(eMod::e蟹将, 25, eAp::Atk);
	insert(1425, 1296, 5508, 2462, 1296, 1296, 107);
	insert(eSkill::连击2, eSkill::招架, eSkill::水属性吸收, eSkill::精神集中);


	init(eMod::e龟丞相, 35, eAp::Magic);
	insert(1101, 1555, 6285, 2138, 972, 1231, 108);
	insert(eSkill::驱鬼, eSkill::冥思, eSkill::水攻, eSkill::水漫金山, eSkill::水属性吸收, eSkill::防御);


	init(eMod::e兔子怪, 35, eAp::GiveMagic);
	insert(1425, 1231, 4536, 2592, 1555, 1231, 114);
	insert(eSkill::幸运2, eSkill::敏捷2, eSkill::感知2, eSkill::冥思2, eSkill::永恒2, eSkill::驱鬼2, eSkill::弱点土);


	init(eMod::e蜘蛛精, 35, eAp::GiveMagic);
	insert(1231, 1463, 5378, 2786, 1166, 1296, 111);
	insert(eSkill::毒2, eSkill::吸血, eSkill::感知2, eSkill::弱点土);


	init(eMod::e黑熊精, 35, eAp::Atk);
	insert(1490, 1360, 5443, 2332, 1101, 1425, 107);
	insert(eSkill::强力2, eSkill::幸运, eSkill::必杀, eSkill::反震, eSkill::弱点雷);


	init(eMod::e僵尸, 35, eAp::Atk);
	insert(1555, 1166, 4665, 2592, 1296, 1490, 109);
	insert(eSkill::鬼魂术, eSkill::夜战, eSkill::土属性吸收, eSkill::防御, eSkill::弱点雷);


	init(eMod::e牛头, 35, eAp::Atk);
	insert(1425, 1425, 3888, 1944, 1555, 1296, 110);
	insert(eSkill::鬼魂术2, eSkill::必杀2, eSkill::夜战, eSkill::驱鬼, eSkill::招架);


	init(eMod::e马面, 35, eAp::Atk);
	insert(1425, 1425, 3888, 1944, 1555, 1296, 109);
	insert(eSkill::鬼魂术2, eSkill::必杀2, eSkill::夜战, eSkill::驱鬼, eSkill::强力);


	init(eMod::e雷鸟人, 45, eAp::GiveMagic);
	insert(1296, 1296, 4536, 2073, 1555, 1231, 117);
	insert(eSkill::飞行, eSkill::雷击, eSkill::奔雷咒, eSkill::雷属性吸收2, eSkill::弱点土);


	init(eMod::e蝴蝶仙子, 45, eAp::GiveMagic);
	insert(1425, 1231, 3240, 3240, 1555, 1555, 112);
	insert(eSkill::飞行, eSkill::弱点水, eSkill::敏捷2, eSkill::神迹, eSkill::魔之心2);


	init(eMod::e古代瑞兽, 45, eAp::Magic);
	insert(1231, 1360, 3888, 2592, 1490, 1296, 117);
	insert(eSkill::神迹2, eSkill::泰山压顶, eSkill::驱鬼2, eSkill::反震2);


	init(eMod::e白熊, 45, eAp::Atk);
	insert(1425, 1425, 5702, 1944, 1036, 1490, 114);
	insert(eSkill::反击2, eSkill::必杀2, eSkill::迟钝2, eSkill::强力, eSkill::防御);


	init(eMod::e黑山老妖, 45, eAp::Atk);
	insert(1231, 1555, 6480, 2592, 1036, 1425, 115);
	insert(eSkill::吸血2, eSkill::偷袭2, eSkill::精神集中2);


	init(eMod::e天兵, 55, eAp::Atk);
	insert(1425, 1620, 5508, 2397, 1425, 1425, 117);
	insert(eSkill::必杀, eSkill::防御2, eSkill::驱鬼2, eSkill::感知2);


	init(eMod::e天将, 55, eAp::Atk);
	insert(1490, 1231, 5184, 2527, 1490, 1296, 118);
	insert(eSkill::强力2, eSkill::幸运, eSkill::连击, eSkill::驱鬼);


	init(eMod::e地狱战神, 55, eAp::Rand);
	insert(1620, 1555, 4860, 1944, 1166, 1620, 115);
	insert(eSkill::连击2, eSkill::泰山压顶, eSkill::反震2, eSkill::魔之心2);


	init(eMod::e风伯, 55, eAp::GiveMagic);
	insert(1490, 1503, 4536, 2397, 1620, 1555, 117);
	insert(eSkill::奔雷咒, eSkill::敏捷2, eSkill::飞行2, eSkill::雷属性吸收2);


	init(eMod::e凤凰, 65, eAp::Magic);
	insert(1296, 1555, 4536, 2592, 1684, 1425, 122);
	insert(eSkill::火属性吸收2, eSkill::地狱烈火, eSkill::神佑复生2, eSkill::飞行);


	init(eMod::e蛟龙, 65, eAp::Rand);
	insert(1555, 1555, 4924, 3240, 1296, 1425, 122);
	insert(eSkill::水漫金山, eSkill::水属性吸收2, eSkill::感知, eSkill::永恒2);


	init(eMod::e雨师, 65, eAp::Magic);
	insert(1296, 1490, 4536, 3240, 1555, 1749, 120);
	insert(eSkill::水攻, eSkill::水属性吸收2, eSkill::雷属性吸收2, eSkill::土属性吸收2, eSkill::火属性吸收2);


	init(eMod::e蚌精, 65, eAp::Magic);
	insert(1296, 1620, 4147, 3110, 1296, 1231, 122);
	insert(eSkill::水攻, eSkill::慧根, eSkill::神迹, eSkill::冥思, eSkill::水属性吸收2);


	init(eMod::e鲛人, 65, eAp::Atk);
	insert(1555, 1555, 4924, 2073, 1490, 1555, 122);
	insert(eSkill::连击, eSkill::水属性吸收2, eSkill::移花接木, eSkill::敏捷);


	init(eMod::e碧水夜叉, 65, eAp::Rand);
	insert(1490, 1425, 4536, 2980, 1555, 1944, 123);
	insert(eSkill::壁垒击破, eSkill::奔雷咒, eSkill::反震2, eSkill::强力);


	init(eMod::e如意仙子, 75, eAp::Magic);
	insert(1296, 1529, 4730, 2916, 1555, 1490, 125);
	insert(eSkill::奔雷咒, eSkill::弱点水, eSkill::泰山压顶, eSkill::烈火, eSkill::地狱烈火);


	init(eMod::e芙蓉仙子, 75, eAp::Atk);
	insert(1555, 1555, 4924, 2592, 1490, 1555, 125);
	insert(eSkill::再生2, eSkill::飞行2, eSkill::幸运2);


	init(eMod::e巡游天神, 75, eAp::Rand);
	insert(1490, 1490, 5832, 2851, 1296, 1814, 124);
	insert(eSkill::必杀2, eSkill::招架2, eSkill::泰山压顶, eSkill::地狱烈火);


	init(eMod::e星灵仙子, 75, eAp::Magic);
	insert(1296, 1529, 4730, 2916, 1555, 1490, 125);
	insert(eSkill::奔雷咒, eSkill::水漫金山, eSkill::雷击, eSkill::慧根2);


	init(eMod::e锦毛貂精, 75, eAp::Magic);
	insert(1296, 1360, 4536, 2927, 1684, 1814, 125);
	insert(eSkill::泰山压顶, eSkill::敏捷, eSkill::冥思, eSkill::法术连击);


	init(eMod::e千年蛇魅, 75, eAp::Atk);
	insert(1490, 1425, 4730, 2851, 1555, 1620, 124);
	insert(eSkill::毒, eSkill::偷袭, eSkill::吸血, eSkill::敏捷);


	init(eMod::e犀牛将军, 75, eAp::Atk);
	insert(1555, 1581, 5184, 2721, 1296, 1231, 125);
	insert(eSkill::剑荡四方, eSkill::幸运2, eSkill::再生, eSkill::强力2);


	init(eMod::e犀牛, 75, eAp::Magic);
	insert(1555, 1581, 5184, 2721, 1296, 1231, 125);
	insert(eSkill::落岩, eSkill::法术暴击, eSkill::法术波动, eSkill::土属性吸收);


	init(eMod::e镜妖, 85, eAp::Atk);
	insert(1581, 1425, 4147, 2592, 1684, 1555, 125);
	insert(eSkill::反震, eSkill::感知2, eSkill::鬼魂术, eSkill::雷击);


	init(eMod::e泪妖, 85, eAp::Magic);
	insert(1296, 1296, 3888, 2592, 1296, 1684, 122);
	insert(eSkill::冥思, eSkill::魔之心2, eSkill::法术暴击, eSkill::弱点土, eSkill::水攻);


	init(eMod::e野猪精, 85, eAp::Atk);
	insert(1581, 1684, 5184, 2592, 1296, 1425, 125);
	insert(eSkill::反击, eSkill::弱点水, eSkill::感知, eSkill::强力2);


	init(eMod::e鼠先锋, 85, eAp::Magic);
	insert(1296, 1555, 4795, 3110, 1684, 1684, 125);
	insert(eSkill::泰山压顶, eSkill::敏捷, eSkill::夜战, eSkill::冥思);


	init(eMod::e百足将军, 85, eAp::Atk);
	insert(1555, 1425, 4924, 2851, 1684, 1425, 125);
	insert(eSkill::弱点水, eSkill::落岩, eSkill::毒, eSkill::夜战2);


	init(eMod::e律法女娲, 95, eAp::Atk);
	insert(1555, 1684, 4795, 2592, 1555, 1814, 125);
	insert(eSkill::反击2, eSkill::再生, eSkill::善恶有报, eSkill::敏捷);


	init(eMod::e灵符女娲, 95, eAp::Magic);
	insert(1425, 1684, 5184, 3240, 1555, 1555, 125);
	insert(eSkill::冥思2, eSkill::上古灵符, eSkill::地狱烈火);


	init(eMod::e幽灵, 95, eAp::Atk);
	insert(1594, 1555, 4536, 2851, 1425, 1814, 125);
	insert(eSkill::鬼魂术, eSkill::死亡召唤, eSkill::飞行2, eSkill::反击2);


	init(eMod::e吸血鬼, 95, eAp::Atk);
	insert(1555, 1425, 3888, 2592, 1425, 1944, 125);
	insert(eSkill::吸血, eSkill::夜战, eSkill::弱点水, eSkill::鬼魂术, eSkill::偷袭);


	init(eMod::e阴阳伞, 95, eAp::Magic);
	insert(1555, 1555, 5184, 3240, 1620, 1555, 126);
	insert(eSkill::剑荡四方, eSkill::驱鬼, eSkill::飞行2, eSkill::上古灵符);


	init(eMod::e鬼将, 105, eAp::Atk);
	insert(1645, 1490, 5443, 1555, 1425, 1425, 126);
	insert(eSkill::必杀2, eSkill::鬼魂术, eSkill::惊心一剑, eSkill::冥思);


	init(eMod::e净瓶女娲, 105, eAp::Rand);
	insert(1581, 1555, 5184, 3045, 1684, 1684, 126);
	insert(eSkill::感知, eSkill::慧根2, eSkill::奔雷咒, eSkill::上古灵符);


	init(eMod::e画魂, 105, eAp::Magic);
	insert(1490, 1555, 4665, 3110, 1425, 1555, 126);
	insert(eSkill::鬼魂术2, eSkill::魔之心2, eSkill::地狱烈火, eSkill::幸运);


	init(eMod::e幽萤娃娃, 105, eAp::Atk);
	insert(1555, 1555, 4536, 2851, 1658, 1684, 126);
	insert(eSkill::鬼魂术2, eSkill::防御2, eSkill::敏捷, eSkill::法术抵抗2);


	init(eMod::e雾中仙, 125, eAp::GiveMagic);
	insert(1555, 1620, 5832, 3240, 1425, 1944, 126);
	insert(eSkill::感知2, eSkill::法术连击, eSkill::敏捷, eSkill::神佑复生2);


	init(eMod::e灵鹤, 125, eAp::GiveMagic);
	insert(1555, 1555, 4924, 2980, 1684, 1555, 126);
	insert(eSkill::飞行, eSkill::慧根2, eSkill::再生2, eSkill::永恒2, eSkill::驱鬼2);


	init(eMod::e炎魔神, 125, eAp::Atk);
	insert(1620, 1555, 5184, 3240, 1555, 1425, 126);
	insert(eSkill::地狱烈火, eSkill::烈火, eSkill::火属性吸收2, eSkill::必杀2);


	init(eMod::e噬天虎, 125, eAp::Atk);
	insert(1620, 1555, 5184, 2592, 1620, 1684, 126);
	insert(eSkill::强力2, eSkill::连击2, eSkill::幸运, eSkill::驱鬼);


	init(eMod::e琴仙, 125, eAp::Magic);
	insert(1555, 1555, 5184, 3499, 1490, 1555, 126);
	insert(eSkill::泰山压顶, eSkill::感知, eSkill::神佑复生, eSkill::再生, eSkill::敏捷);


	init(eMod::e金铙僧, 125, eAp::Atk);
	insert(1620, 1555, 5443, 2462, 1555, 1684, 126);
	insert(eSkill::再生, eSkill::必杀, eSkill::招架, eSkill::偷袭, eSkill::雷属性吸收2);


	init(eMod::e大力金刚, 125, eAp::Atk);
	insert(1671, 1451, 6480, 2851, 1296, 1425, 126);
	insert(eSkill::力劈华山, eSkill::强力2, eSkill::泰山压顶, eSkill::永恒2);


	init(eMod::e夜罗刹, 125, eAp::GiveMagic);
	insert(1620, 1555, 6220, 3110, 1555, 1555, 126);
	insert(eSkill::敏捷2, eSkill::必杀, eSkill::夜舞倾城, eSkill::魔之心2);


	init(eMod::e踏云兽, 135, eAp::Atk);
	insert(1645, 1555, 5832, 1944, 1555, 1555, 126);
	insert(eSkill::弱点土, eSkill::强力2, eSkill::必杀2, eSkill::招架2);


	init(eMod::e红萼仙子, 135, eAp::Rand);
	insert(1620, 1620, 5832, 3240, 1036, 1944, 127);
	insert(eSkill::飞行2, eSkill::冥思2, eSkill::奔雷咒, eSkill::上古灵符);


	init(eMod::e蝎子精, 135, eAp::GiveMagic);
	insert(1581, 1581, 6739, 3110, 1425, 2073, 127);
	insert(eSkill::毒, eSkill::招架, eSkill::反震2, eSkill::再生2);


	init(eMod::e葫芦宝贝, 135, eAp::Magic);
	insert(1555, 1620, 5184, 2980, 1425, 1944, 126);
	insert(eSkill::冥思2, eSkill::反震, eSkill::魔之心, eSkill::上古灵符);


	init(eMod::e龙龟, 135, eAp::Magic);
	insert(1555, 1684, 6220, 3240, 1296, 1684, 127);
	insert(eSkill::法术防御, eSkill::水属性吸收, eSkill::反震, eSkill::防御2, eSkill::水攻);


	init(eMod::e机关车, 135, eAp::Atk);
	insert(1620, 1620, 5832, 1814, 1425, 1555, 127);
	insert(eSkill::招架2, eSkill::壁垒击破, eSkill::弱点火, eSkill::必杀);


	init(eMod::e机关人, 135, eAp::Atk);
	insert(1620, 1620, 5832, 1814, 1425, 1555, 127);
	insert(eSkill::招架2, eSkill::壁垒击破, eSkill::弱点火, eSkill::必杀);


	init(eMod::e猫灵人, 155, eAp::Atk);
	insert(1645, 1581, 4924, 2851, 1620, 1814, 128);
	insert(eSkill::敏捷, eSkill::反击, eSkill::必杀, eSkill::偷袭2, eSkill::幸运2);


	init(eMod::e狂豹, 145, eAp::Atk);
	insert(1620, 1555, 4924, 2332, 1425, 1684, 126);
	insert(eSkill::飞行2, eSkill::偷袭, eSkill::强力2, eSkill::夜战);


	init(eMod::e机关兽, 145, eAp::Magic);
	insert(1555, 1620, 5702, 3110, 1555, 1555, 126);
	insert(eSkill::烈火, eSkill::魔之心, eSkill::法术连击2, eSkill::土属性吸收);


	init(eMod::e机关鸟, 145, eAp::Atk);
	insert(1620, 1451, 5184, 2721, 1684, 1684, 126);
	insert(eSkill::飞行, eSkill::偷袭2, eSkill::否定信仰, eSkill::再生2, eSkill::夜战);


	init(eMod::e连弩车, 145, eAp::Atk);
	insert(1620, 1684, 5832, 2592, 1296, 1425, 126);
	insert(eSkill::迟钝2, eSkill::强力2, eSkill::防御, eSkill::连击);


	init(eMod::e巴蛇, 145, eAp::Atk);
	insert(1645, 1555, 5184, 1684, 1684, 1684, 128);
	insert(eSkill::敏捷, eSkill::嗜血追击, eSkill::感知, eSkill::毒, eSkill::再生);


	init(eMod::e长眉灵猴, 155, eAp::Magic);
	insert(1555, 1620, 6091, 3499, 1296, 1684, 127);
	insert(eSkill::法术暴击, eSkill::再生2, eSkill::冥思, eSkill::奔雷咒);


	init(eMod::e巨力神猿, 155, eAp::Atk);
	insert(1620, 1555, 4924, 2851, 1620, 1684, 128);
	insert(eSkill::敏捷, eSkill::连击2, eSkill::强力, eSkill::驱鬼2, eSkill::盾气2);


	init(eMod::e修罗傀儡鬼, 155, eAp::Atk);
	insert(1645, 1490, 5443, 2592, 1555, 1555, 128);
	insert(eSkill::嗜血追击, eSkill::强力, eSkill::反震, eSkill::夜战2, eSkill::必杀2);


	init(eMod::e藤蔓妖花, 155, eAp::Magic);
	insert(1581, 1555, 4924, 3369, 1296, 1555, 128);
	insert(eSkill::法术连击2, eSkill::落岩, eSkill::招架2, eSkill::灵能激发);


	init(eMod::e蜃气妖, 155, eAp::Magic);
	insert(1581, 1555, 5443, 3499, 1425, 1555, 128);
	insert(eSkill::法术连击2, eSkill::法术暴击, eSkill::上古灵符);


	init(eMod::e猫灵, 135, eAp::Atk);
	insert(1581, 1581, 4406, 2592, 1684, 1814, 126);
	insert(eSkill::敏捷, eSkill::必杀, eSkill::偷袭2, eSkill::弱点水);


	init(eMod::e狂豹人, 155, eAp::Atk);
	insert(1658, 1555, 5184, 2462, 1555, 1684, 127);
	insert(eSkill::偷袭, eSkill::吸血, eSkill::飞行2, eSkill::夜战, eSkill::强力2);


	init(eMod::e混沌兽, 155, eAp::Magic);
	insert(1555, 1594, 5830, 3499, 1425, 1684, 129);
	insert(eSkill::再生, eSkill::永恒2, eSkill::慧根2, eSkill::魔之心2, eSkill::奔雷咒);


	init(eMod::e修罗傀儡妖, 165, eAp::Atk);
	insert(1658, 1490, 5184, 2592, 1620, 1555, 128);
	insert(eSkill::连击2, eSkill::幸运2, eSkill::感知, eSkill::合纵);


	init(eMod::e金身罗汉, 165, eAp::Atk);
	insert(1490, 1620, 5832, 2592, 1684, 1555, 129);
	insert(eSkill::永恒, eSkill::反震2, eSkill::神佑复生, eSkill::盾气, eSkill::敏捷2);


	init(eMod::e曼珠沙华, 165, eAp::GiveMagic);
	insert(1555, 1555, 5184, 2851, 1620, 1555, 129);
	insert(eSkill::反震, eSkill::再生2, eSkill::招架, eSkill::法术抵抗, eSkill::灵能激发);


	init(eMod::e灵灯侍者, 175, eAp::Rand);
	insert(1516, 1645, 6220, 2980, 1658, 1555, 129);
	insert(eSkill::慧根2, eSkill::防御, eSkill::雷击, eSkill::水属性吸收2, eSkill::无畏布施);


	init(eMod::e真陀护法, 175, eAp::Atk);
	insert(1658, 1555, 5443, 2592, 1490, 1684, 127);
	insert(eSkill::精神集中2, eSkill::必杀, eSkill::偷袭, eSkill::吸血, eSkill::夜战, eSkill::连击);


	init(eMod::e持国巡守, 175, eAp::Magic);
	insert(1555, 1490, 6480, 3240, 1296, 1036, 127);
	insert(eSkill::再生, eSkill::奔雷咒, eSkill::神佑复生, eSkill::须弥真言);


	init(eMod::e增长巡守, 175, eAp::Atk);
	insert(1620, 1490, 6480, 2980, 1296, 1036, 127);
	insert(eSkill::招架2, eSkill::驱鬼, eSkill::神佑复生, eSkill::灵山禅语);


	init(eMod::e毗舍童子, 175, eAp::Atk);
	insert(1684, 1542, 4536, 2332, 1555, 1749, 128);
	insert(eSkill::连击, eSkill::法术抵抗2, eSkill::合纵2, eSkill::敏捷, eSkill::神迹);


	init(eMod::e般若天女, 175, eAp::Magic);
	insert(1579, 1579, 5953, 3559, 1597, 1693, 129);
	insert(eSkill::飞行2, eSkill::幸运2, eSkill::敏捷, eSkill::魔之心, eSkill::慧根2, eSkill::上古灵符);


	init(eMod::e小毛头, 0, eAp::Atk);


	init(eMod::e小丫丫, 0, eAp::Atk);


	init(eMod::e小仙灵, 0, eAp::Atk);


	init(eMod::e小仙女, 0, eAp::Atk);


	init(eMod::e小精灵, 0, eAp::Atk);


	init(eMod::e小魔头, 0, eAp::Atk);


	init(eMod::e超级人参娃娃, 0, eAp::Atk);
	insert(eSkill::壁垒击破, eSkill::必杀2, eSkill::强力2, eSkill::幸运, eSkill::驱鬼2);


	init(eMod::e超级泡泡, 0, eAp::Atk);
	insert(eSkill::必杀2, eSkill::神佑复生2, eSkill::感知2, eSkill::夜战, eSkill::飞行2);


	init(eMod::e超级大熊猫, 0, eAp::Atk);
	insert(eSkill::感知2, eSkill::强力2, eSkill::防御2, eSkill::夜战, eSkill::连击2);


	init(eMod::e超级金猴, 0, eAp::Atk);
	insert(eSkill::偷袭2, eSkill::敏捷2, eSkill::幸运2, eSkill::夜战, eSkill::连击2);


	init(eMod::e超级大象, 0, eAp::Atk);
	insert(eSkill::强力2, eSkill::反震2, eSkill::再生2, eSkill::夜战, eSkill::必杀2);


	init(eMod::e超级白泽, 0, eAp::Atk);
	insert(eSkill::必杀2, eSkill::敏捷2, eSkill::夜战2, eSkill::感知, eSkill::幸运2);


	init(eMod::e超级灵鹿, 0, eAp::Atk);
	insert(eSkill::善恶有报, eSkill::再生2, eSkill::冥思2, eSkill::永恒, eSkill::偷袭2);


	init(eMod::e超级赤焰兽, 0, eAp::Atk);
	insert(eSkill::感知2, eSkill::必杀2, eSkill::反击2, eSkill::幸运, eSkill::毒2);


	init(eMod::e超级大鹏, 0, eAp::Atk);
	insert(eSkill::必杀, eSkill::飞行2, eSkill::敏捷2, eSkill::神佑复生2, eSkill::偷袭2);


	init(eMod::e超级筋斗云, 0, eAp::Atk);
	insert(eSkill::神佑复生2, eSkill::偷袭2, eSkill::敏捷2, eSkill::强力, eSkill::夜战2);


	init(eMod::e超级海豚, 0, eAp::Atk);
	insert(eSkill::剑荡四方, eSkill::偷袭2, eSkill::必杀2, eSkill::夜战, eSkill::幸运2);


	init(eMod::e超级玉兔, 0, eAp::Magic);
	insert(eSkill::法术暴击, eSkill::法术波动2, eSkill::月光, eSkill::驱鬼, eSkill::神佑复生2);


	init(eMod::e超级孔雀, 0, eAp::Atk);
	insert(eSkill::偷袭2, eSkill::飞行2, eSkill::再生2, eSkill::必杀, eSkill::连击2);


	init(eMod::e超级灵狐, 0, eAp::Atk);
	insert(eSkill::惊心一剑, eSkill::敏捷2, eSkill::必杀2, eSkill::夜战, eSkill::偷袭2);


	init(eMod::e超级青鸾, 0, eAp::Atk);
	insert(eSkill::苍鸾怒击, eSkill::夜战2, eSkill::飞行2, eSkill::反震, eSkill::连击2);


	init(eMod::e超级麒麟, 0, eAp::Atk);
	insert(eSkill::合纵2, eSkill::连击2, eSkill::幸运2, eSkill::偷袭, eSkill::夜战2);


	init(eMod::e超级六耳猕猴, 0, eAp::Magic);
	insert(eSkill::须弥真言, eSkill::法术连击2, eSkill::法术暴击2, eSkill::永恒, eSkill::上古灵符);


	init(eMod::e超级土地公公, 0, eAp::Magic);
	insert(eSkill::神佑复生2, eSkill::法术连击2, eSkill::天降灵葫, eSkill::招架, eSkill::魔之心2);


	init(eMod::e超级神牛, 0, eAp::Atk);
	insert(eSkill::力劈华山, eSkill::幸运2, eSkill::招架2, eSkill::必杀, eSkill::强力);


	init(eMod::e超级神虎, 0, eAp::Atk);
	insert(eSkill::感知2, eSkill::嗜血追击, eSkill::夜战2, eSkill::连击, eSkill::强力);


	init(eMod::e超级神兔, 0, eAp::Atk);
	insert(eSkill::连击2, eSkill::偷袭2, eSkill::敏捷2, eSkill::夜战, eSkill::幸运);


	init(eMod::e超级神龙, 0, eAp::Magic);
	insert(eSkill::奔雷咒, eSkill::龙魂, eSkill::法术波动, eSkill::魔之心, eSkill::再生);


	init(eMod::e超级神蛇, 0, eAp::Magic);
	insert(eSkill::地狱烈火, eSkill::灵能激发, eSkill::法术波动2, eSkill::魔之心, eSkill::永恒);


	init(eMod::e超级神马, 0, eAp::Atk);
	insert(eSkill::连击2, eSkill::神佑复生2, eSkill::浮云神马, eSkill::幸运, eSkill::神迹);


	init(eMod::e超级神羊, 0, eAp::Atk);
	insert(eSkill::必杀2, eSkill::连击2, eSkill::千钧一怒, eSkill::反震, eSkill::感知);


	init(eMod::e超级神猴, 0, eAp::Atk);
	insert(eSkill::神佑复生2, eSkill::吸血2, eSkill::大快朵颐, eSkill::必杀, eSkill::连击);


	init(eMod::e超级神鸡, 0, eAp::Atk);
	insert(eSkill::神佑复生2, eSkill::强力2, eSkill::从天而降, eSkill::夜战, eSkill::必杀);


	init(eMod::e程咬金, 115, eAp::Atk);


	init(eMod::e东海龙王, 115, eAp::Atk);


	init(eMod::e白晶晶, 115, eAp::Atk);


	init(eMod::e菩提祖师, 115, eAp::Atk);


	init(eMod::e牛魔王, 115, eAp::Atk);


	init(eMod::e空度禅师, 115, eAp::Atk);


	init(eMod::e观音姐姐, 115, eAp::Atk);


	init(eMod::e孙婆婆, 115, eAp::Atk);


	init(eMod::e镇元大仙, 115, eAp::Atk);


	init(eMod::e大大王, 115, eAp::Atk);


	init(eMod::e李靖, 115, eAp::Atk);


	init(eMod::e地藏王, 115, eAp::Atk);


	init(eMod::e二郎神, 115, eAp::Atk);


	init(eMod::e地涌夫人, 115, eAp::Atk);


	init(eMod::e巫奎虎, 115, eAp::Atk);


	init(eMod::e啸天犬, 115, eAp::Atk);


	init(eMod::e火星人, 115, eAp::Atk);


	init(eMod::e占卜师, 115, eAp::Atk);


	init(eMod::e转轮王, 115, eAp::Atk);


	init(eMod::e九色鹿, 115, eAp::Atk);


	init(eMod::e腾蛇, 115, eAp::Atk);


	init(eMod::e善财童子, 115, eAp::Atk);


	init(eMod::e周杰伦, 115, eAp::Atk);


	init(eMod::e孙悟空, 115, eAp::Atk);


	init(eMod::e猪八戒, 115, eAp::Atk);


	init(eMod::e沙和尚, 115, eAp::Atk);


	init(eMod::e貔貅, 115, eAp::Atk);


	init(eMod::e九头精怪, 115, eAp::Atk);


	init(eMod::e黄眉怪, 115, eAp::Atk);


	init(eMod::e蚩尤, 115, eAp::Atk);


	init(eMod::e雪人, 115, eAp::Atk);


	init(eMod::e小白泽, 0, eAp::GiveMagic);


	init(eMod::e小象, 0, eAp::GiveMagic);


	init(eMod::e小泡泡, 0, eAp::GiveMagic);


	init(eMod::e龙马, 115, eAp::Atk);


	init(eMod::e骚浪剑, 0, eAp::Atk);


	init(eMod::e无痕, 0, eAp::Atk);


	init(eMod::e慧海, 115, eAp::Atk);


	init(eMod::e镖头, 115, eAp::Atk);


	init(eMod::e蜈蚣精, 995, eAp::GiveMagic);
	insert(2000, 2000, 9980, 3800, 2000, 2000, 130);


	init(eMod::e自在天魔, 995, eAp::GiveMagic);
	insert(2000, 2000, 9980, 3800, 2000, 2000, 130);

	//////////////////////////////////////////////////////////////////////////
	for (eMod e = eMod::ePet0; e <= eMod::ePet0end; e = (eMod)((int)e + 1))
	{
		_zz = &_tables.at(e);
		insert(1500, 1500, 5000, 2500, 1500, 1500, 125);
	}
	for (eMod e = eMod::ePetBaby0; e <= eMod::ePetBabyEnd; e = (eMod)((int)e + 1))
	{
		_zz = &_tables.at(e);
		insert(1600, 1600, 6000, 3000, 1600, 1600, 130);
	}

	for (eMod e = eMod::ePet115; e <= eMod::ePet115end; e = (eMod)((int)e + 1))
	{
		_zz = &_tables.at(e);
		insert(1600, 1600, 6000, 3000, 1600, 1600, 130);
	}

	_tables.at(eMod::e小白泽) = _tables.at(eMod::e超级白泽);
	_tables.at(eMod::e小象) = _tables.at(eMod::e超级大象);
	_tables.at(eMod::e小泡泡) = _tables.at(eMod::e超级泡泡);

};