#include "FightData.h"

bool sFightData::Init()
{
	chaos混乱反间 = 0;
	cannotAttack = 0; //是否可以使用物理攻击   
	cannotMagic = 0;  //是否可以使用魔法
	cannotSpesialSkill = 0;  //是否可以使用特技
	cannotUseItem = 0;//是否可以使用道具
	cannotAddHP = 0;  //是否可以加血
	cannotAll = 0;  //是否可以动  催眠符的效果就是这个,后发制人也是这个
	cannotLive = 0;
	m_bHit = 0; //记录是否被命中  用这个值来判断是否需要保护
	yanhu = 0;
	zhanyi = 0;
	//记录是否被成功保护 和 保护它的角色的ID
	m_guardID.clear();
// 	m_MaxDef = 0;
// 	m_MaxMagicDef = 0;

	m_TurnHPAdd = 0;
	m_TurnMPAdd = 0;

	m_TurnHPHurtAdd = 0;
	//一个角色的状态列表
	Clear();

//	_isDieOnceForPet = false;
	return true;
}

void sFightData::Reset()
{
	SufferNum = 0;//记录一回合中角色被打的次数
	AttackNum = 0; //记录角色当回合的攻击数
}


