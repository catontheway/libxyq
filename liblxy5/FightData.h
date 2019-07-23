#pragma once
#include "_asert.h"
#include "IntData.h"

struct sFightData
{
	//表示角色战斗时的属性 (战斗时属性会随得到的BUFF而改变.我们当然不能直接拿角色的永久属性来变)
// 	sInt3  m_oldATK;   //伤害
// 	sInt3  m_oldHIT;   //命中
// 	sInt3  m_oldDEF;   //防御
// 	sInt3  m_oldWakan; //灵力
// 	sInt3  m_oldSPD;   //速度
// 	sInt3  m_oldEvade; //躲闪
// 	sInt2  m_oldGoldLive;//神佑
//	bool _isFlyOld;
	//一个角色的状态列表
	int SufferNum;	//记录当回合被打的次数
	int AttackNum;	//记录当回合的攻击数
	int cannotAttack; //是否可以使用物理攻击   
	int cannotMagic;  //是否可以使用魔法
	int cannotSpesialSkill;  //是否可以使用特技
	int cannotUseItem;//是否可以使用道具
	int cannotAddHP;  //是否可以加血
	int cannotAll;  //是否可以动  催眠符的效果就是这个,后发制人也是这个
	int chaos混乱反间;		//是否混乱
	int cannotLive;  //是否可以被复活
	int yanhu; // 炎护
	int zhanyi; // 战意
	bool m_bHit; //记录是否被命中  用这个值来判断是否需要保护	
	bool m_bDefend;//是否防御
	bool m_bCri;//是否被必杀
	vector<int>  m_guardID;//记录是否被成功保护 和 保护它的角色的ID
//	bool _isDieOnceForPet;
// 
// 	int m_MaxDef;
// 	int m_MaxMagicDef;
	//记录强化状态
	int m_AtkIntensify;
	int m_DefIntensify;
	int m_SpdIntensify;
	int m_WallNum; //
	void Reset();
	void Clear()
	{
		m_guardID.clear();
		m_AtkIntensify = 0;
		m_DefIntensify = 0;
		m_SpdIntensify = 0;
		m_WallNum = 0; //
		Reset();
	}
	bool Init();
	// 再生 * 等级， 可惜我已经自己*等级了
	int m_TurnHPAdd;
	int m_TurnHPHurtAdd;
	int m_TurnMPAdd;
};