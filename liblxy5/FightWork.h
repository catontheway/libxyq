#pragma once
#include "_stateinc.h"

struct sFightWork
{
	int m_FriendListid = -1;//用来记录是不是玩家的好友,从而更新好友状态
	bool Swap(sFightWork& fightlist);

	//用于记录角色战斗前的位置
	int  xOldPos;
	int  yOldPos;
	int  m_oldDirection;
	int m_WorkType;
	bool Free();
	//召唤兽死亡时击飞效果
	bool InitFly();
	bool m_bFlyInit;
	int  m_DiePoint;
	// 狼: 说好的状态机呢?
	bool DieFly();

	int  m_rotateRate;
	bool Rotate(int rotaterate = 3);
	//让一个角色等待  ,比如说,转换攻击目标时要停几秒,否则看起来很怪
	int m_SleepTime;
	bool Sleep(int Time, bool bStatic = true);
	//受到的伤害
	cObjWas m_Damage[5]; //五位,也就是最大能显示99999的伤害
	int   m_DamageTime[5];
	int m_DamageNum;   //伤害有几位
	bool ShowDamage(CMainState* p);
	bool SetDamageRect(int Num); //设置每个字的位置 两个参数分别是 第几个字和总字数
	//
	bool m_bSufferFullSkill;//该角色是否被全体法术打

	sFightSkillSelect m_SkillSelect;
	sFightSkillSelect m_SkillPreSelect;
	sFightSkillSelect m_SkillSelectForCounter;
	int               m_ItemSelectID;
	int               m_autoItemSelectID;
	const sFightPoint* GetFightPoint();
//	int           m_SkillIDEx;//当不使用法术时被使用

	cObj* m_pObj = 0;

	// 缥缈式迭代
	bool NextTarget(cFightState* pFightState, int skillid);
	int  targetID = -1;
	int  m_NowTargetID;
	int  m_NowBeAtkowner = -1;
	vector<int>  targetlist;
	int  m_MaxTargetNum; //最多攻击目标
	int  m_NowTargetIdx;//当前目标在目标列表中的位置
	struct sWork
	{
		int type = -1;
		int stage = -1;
	};
	// 狼:为什么不用栈...
	int GetNowWorkType(){ if (!m_work.size())return -1;  return m_work[m_work.size() - 1].type; }
	int GetNowWorkStage(){ if (!m_work.size())return -1; return m_work[m_work.size() - 1].stage; }
	void SetWork(int type, int state = 0);
	void SetWorkFront(int type, int state = 0);
	vector<sWork>  m_work;  //角色的工作
	sWork* GetWork(){ return &m_work[m_work.size() - 1]; }

	//角色是否存在 ,比如角色在被击飞的时候,已经死了,但它还存在
	bool isExist = false;
	bool m_bPrePareFight = false;

	int  m_sufferDirection = 1;

	bool SetMagiSufferID(ulong MagicID, int MagicPos, cWasFile* pFile, bool up = 1);
	bool ShowOnScreen(cCanvas* pCanvas);
	sFightWork();
	~sFightWork();
	void RestTarget();
//	void operator=(sFightWork& flist);
	void SetDie(bool bDie){ m_bDie = bDie; }
	bool CheckDie(){ return m_bDie; }
	int _turnOfSpeed = -1;

	int _myTurn;
	int _ghostTurn;
	int _zhuiji;
	int _nuji;
// 	int _nujiFromCri;
// 	int _nujiFromCom;
	int _longhun;
	int _endmagic;
	int _combo;
	int _moon;
	int _magicCri;

	void reset()
	{
		_myTurn = 0;
		_ghostTurn = 0;
		_zhuiji = 0;
		_nuji = 0;
		_longhun = 0;
		_endmagic = -1;
		_combo = 0;
		_moon = 0;
		_magicCri = 0;
		// 嗜血追击
		if (m_pObj && m_pObj->getPropertyData() && m_pObj->getPropertyData()->isHadPetSkill(2076))
		{
			_zhuiji = 1;
		}
		// 苍穹弩机
		if (m_pObj && m_pObj->getPropertyData() && m_pObj->getPropertyData()->isHadPetSkill(2100))
		{
			_nuji = 1;
		}
	}

private:
	bool m_bDie = false;  //角色是否活着
};

