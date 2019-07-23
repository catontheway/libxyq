#pragma once
#include "_stateinc.h"

class CGameState
{
public:
	CGameState(){ isInit = 0; };
	virtual ~CGameState(){};
	virtual bool Init(void* pData = 0) = 0;
	virtual bool Frame(void* pData = 0) = 0;
	virtual bool Free() = 0;
	bool isInit;
};

class cFightState :public CGameState
{
private:
	void FillHpMpMedicine();
	void EndFight(bool bFillHpMpMedicine = true);
public:
	cFightState();
	void EscapeFight();
	void SuccessFight();
	void FailFight();
	void DieEffect(int endTitle_or_fly2DF);//飞到地府,并损失一定经验钱



	void ClearState(int id);//去除所有BUFF
	bool AddState(int userID, sBuff buf);//增加一个BUFF
	bool ReMoveStateID(int id, int userID);//去除一个ID为userID的 BUFF
	bool ReMoveSealState(int userID);//解封
	bool ReMovePoisionState(int userID);//解毒
	bool ReMoveBuffState(int userID);//解增益BUFF
	bool ReMoveDeBuffState(int userID);//解负面BUFF
	bool ReMoveState(eBuffType Type, int userID);

	void SetFightBufDown(int i);
	bool m_bEscape = false;//逃跑标志
	void SetDie(int ID, bool dynamicFly = false);//检测一个对象是否死亡,并作出动作(飞掉,或倒下)
	HDC     m_hFightBack;
	HBITMAP m_hFightBack1;
	cWasFile  m_FightBack1;
	uchar*     m_pFightBack = 0;
	int m_turn;  //等待接收命令,战斗
	int m_CurrIDPerTurn;//当前在行动的ID
	int _turn = 0;
	int _leaveBegin;
	bool SortBySpeed();


	//这个线程负责加载法术图片,这样法术显示就不会卡了0_0!
	cWasFile* m_pFileToLoad[5];
	ulong   m_IDtoLoad[5];

	bool   m_ThreadSleep = true;
	HANDLE m_hThread;

	int m_HiddenWeaponsUseNum = 0;
	cWasFile m_HiddenWeapons;
	cWasFile _magicCri;
	cObjWas m_HiddenWeaponsp[10];
	int   m_HiddenWeaponsTargetID[10];
//	bool HiddenWeaponsFly();
	bool HiddenWeaponsMove(int id, int yoffset = 0);
	int   m_ShowTurnType[30];
	void*  m_pShowTurn[30];
	int   m_ShowTurnUseNum;

	static unsigned int WINAPI ThreadProc(_In_  LPVOID lpParameter);

	cFullMagic m_FullSkill;

	cInterfaceFight m_FightMenu;
	cText m_Frame;  //测试用
	bool Suffer(int ID);
	float m_Sufferspd = 4;
	void SortShow();

	bool MagicSuffer(int ID);
	bool SetWork(int ID, int Type);
	bool SetMagicSuffer(int ID, int direction);//把一个对象设置成被法术打状态
	bool SwitchMagicSuffer(int ID);  //把一个单位从受法术状态转成被打状态
	bool SwitchMagicSufferAvoid(int ID);  //把一个单位从受法术状态转成被回避状态
	bool SetSuffer_state30(int ID, int direction, int userid);//把一个对象设置成被打状态


	bool SetAvoid_state15(int ID, int direction);
	void SetTarget(int ID, int Target);
	// Id使用skillid目标target,不一定返回target
	int CheckTarget(int ID, int target, int skillid);
	bool DoWork();
	bool isInRect(long x, long y, cWasFile* pPic, cMyMap* pMap);
	bool Init(void* pData = 0);
	bool Frame(void* pData = 0);

	int GetSelect(long x, long y);
	bool Free();
	bool ProcessInput();
	int  AutoSelectRand(bool isSelectEnemy);//随机选择一个对象,如果Enemy为1 则选择敌方,如果为0,则选择我方.  如果无法选到对象,则返回-1(不可能出现这种情况吧?)
	bool FallDown(int ID);//角色死亡
	//	bool Catch(int ID);
	bool Avoid(int ID);
	bool ApproachProtect(int ID, int TargetID);
	// 无视
	bool Guard(int ID, int xTarget, int yTarget);
	bool Counter(int ID);
	void SetCounter(int ID, int TargetID);
	bool SetDefend_stage30(int ID, int direction, int userid);
	bool Defend(int ID);
	bool Approach(int ID, int TargetID, bool gap = false, float Speed = 15.0f);  //如果移动到了范围内,返回true 
	bool ReturnApproach(int ID, float Speed = 20.0f);  //如果移动到了范围内,返回true
	// 0 接近中 1 2 3 攻击点?  伤害点?
	int WorkAttack(int userID);//如果目标不在攻击范围内,会先调用Approach接近 代表一次物理攻击的开始到攻击判定,使用完此函数,需要用WaitPosEnd等待动作结束
	bool WaitPosEnd(int userID);//此函数仅仅是等待动作完成而已.
	vector<sFightWork*>  m_pFightWorkList;

	int  m_SpeedListPos[20];
	int m_战斗坐标xs[20];
	int m_战斗坐标ys[20];
	cText m_MiaoShu;

	void CheckPetExp();
	bool PrePareToFight(int i);
	bool BackFromFight(int i);
private:


};
