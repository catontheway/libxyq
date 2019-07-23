#pragma once
#include "_asert.h"

enum eAIUseItemType
{
	eAIUseItemTypeHP,
	eAIUseItemTypeHPALL,
	eAIUseItemTypeMP,
	eAIUseItemTypeMPALL,
	eAIUseItemTypeHPHurt,
	eAIUseItemTypelive,
	eAIUseItemTypeUnseal,
	eAIUseItemTypeCP,
	eAIUseItemType暗器
};


struct sFightWork;
// class cObj;
// class cCharacter;
// class cPetData;
class cAI
{
public:
//	cAI();
// 	
// 	int m_ButtonSelect = -1;
// 	int m_ObjSelectid=-1;
//	bool m_bPKMode = false;//如果这个打开,难度将提升
//	void resetNeed();

	bool See(int user, int target, bool check = true);

	// 主要是检测主角
	void checkHero();

	void Escape(int userID);//逃跑
	// 防御
	// 不存在/行动不能 return;
	// 附加 格挡状态1回合
	// sFightList::m_WorkType = -2 ?? 为什么不是 WorkType_defense
	void defense(int userID);

//	int m_FightTarget[20];

	enum eEnemyType
	{
		// 敌方类型
		eET上金刚33,  //加了1力以上
		eET上灵动112, //加了1蓝以上
		eET可封系,	  // FC NR PS WZ TG WD
//		eET需要蓝系,  // 非DT
		eET医疗系,    // HS PT WD 血宠
//		eET法宠,
//		eET攻宠,
//		eET血宠,
		eET血最少,
//		eET中死亡对象,
		eET防最低,
		eET灵最低,
//		eET被封物理,
//		eET被封法术,
//		eET被禁疗,
		eET无召唤兽,
		eET人物死亡,
		eET速度最快,
		eET速度最快2,
		eET封印对象,
		eET加血,
		eET可物理系,
 		eET可法系,
 		eET反间6,
		eET颠倒五行113,
		eET佛法无边46,
		eET力劈华山95,
		eET壁垒击破99,
		eET锢魂术129,
		eET黄泉之息126,
		eET魂飞魄散127,
		eET鬼眼120,
	};

	int finds(bool CheckDie, bool bCheckWork, vector<POINT>& out, eEnemyType type, int userid, int data = -1, int data2 = -1);//寻找特定对象


	enum class eFindType
	{
		None,
		SpeedMax,
		Hp30,
		Hp70,
		HpNotFull,
		HpRateMin,
		Mp0,
		MpMin,
		ManaMin,
		MpSeal,
		MpCure,
		MpPhy,
		MpMag,
		Dying,
		Relifeable,
		Sealable,
		UnSeal,
		UnSealAndPosion,
		Hide,
	};

	// 救人和解封
	map<eFindType, set<int>> _controlMap;


	vector<int> finds(int user, int start, int end, eFindType e = eFindType::None, const function<bool(int)>& condition = nullptr, int checkState = -1, bool checkDie = true, bool checkHide = true);

	vector<int> findOthers(int user, eFindType e = eFindType::None, const function<bool(int)>& condition = nullptr, int checkState = -1, bool checkDie = true, bool checkHide = true)
	{
		int start = user < 10 ? 10 : 0;
		int end = start + 10;
		return finds(user, start, end, e, condition, checkState, checkDie, checkHide);
	}

	vector<int> findOwners(int user, eFindType e = eFindType::None, const function<bool(int)>& condition = nullptr, int checkState = -1, bool checkDie = true, bool checkHide = true)
	{
		int start = user / 10 * 10;
		int end = start + 10;
		return finds(user, start, end, e, condition, checkState, checkDie, checkHide);
	}

//	vector<int> check隐身(vector<POINT>& out, int user);


//	void RunZhiHui(int start, int end, int mode, int select);
//	void GetNeed(int start,int end);//需求,比如血不够了,要求加血
//private:
//	void PreRun(int start, int end);//满足需求
//	bool SaveOneself(int start, int end);//自救
//	int FintTarget(int i);

	vector<int> findTarget(int skill, int& findsCount);
	vector<int> findTarget(int skill){ int findsCount;  return findTarget(skill, findsCount); }
//	int FindCpMaxTarget(int num=100);//寻找敌方CP>num的对象
//	int FindDefminTarget(int start, int end, eProPerty prop,bool maxormin, int userID = -1);
//	int FindDefminTarget(eProPerty prop, bool isMax){ return FindDefminTarget(m_UserID < 10 ? 10 : 0, m_UserID < 10 ? 20 : 10, prop, isMax, m_UserID); }
//	int find尸腐毒对象();
//	int find安全套();
// 	int Find未Seal(int num);
// 	int Find未Seal(int start, int end);
// 	// 0法 1物 2特技  
// 	int Find未Seal(char &isMorA);
// 	bool Find未Seal(int id, char &isMorA);
public:
	bool AutoRunAi(int id);//,int targetid);
//private:
//	void AutoRunEnemyAi(int id);
//	bool CheckHaveState(int userid,int skillid);
	void NormalAtk(const vector<int>& targets);
	bool Summon();//召唤
public:
	void UseSkill(int id, const vector<int>& targets);
//private:
//	void NpcTryMagic(int id);//测试是否有足够的蓝用魔法,否则就物理攻击



//	bool UseItem(eAIUseItemType mode);
//	bool CheckItem(eAIUseItemType mode);
	int m_HPLimit = 66;//1-99 HP低于 100 - m_HPLimit时加血
//	void ResetNeed();
// 	int m_bNeedAddHp[20];//当回合该对象是否需要加血
// 	int m_bNeedAddHpHurt[20];
// 	int m_bNeedUnSeal[20];//当回合该对象是否需要解封
// 	int m_bNeedlive[20];
// 	int m_bNeedAddMp[20];
// 	bool m_bBeSeal[20];//是否被封
// 	bool  m_bSeal[20];//
// 	int  m_bAtk[20];//
// 	bool  _isShiFudu[20];
	//bool  m_bBeLive[20];//是否被复活
	//bool m_bCure[20];//被治疗
	//bool m_bCureMP[20];//被加MP
	////void CoutIdleList(int start,int end);
	

	void SetUser(int userid);
	int m_UserID = -1;
	sFightWork* pUserList=0;
	cObj* m_pUser=0;
	cCharacter* m_pUserPc=0;
	cPropertyData* m_pUserData=0;

// 	void SetTarget(int target);
// 	int m_TargetID = -1;
// 	sFightWork* m_pTargetList=0;
// 	cObj* m_pTarget=0;
// 	cCharacter* m_pTargetPc = 0;
// 	cPropertyData* m_pTargetData=0;

public:
//	void ZhiHui(bool bOut);//
//private:
// 	void ContentLive(int start,int end);
// 	void ContentLive2(int start,int end);
// 	void ContentHP(int start, int end);
// 	void ContentHP2(int start, int end);
// 	void ContentUnSeal(int start, int end);
// 	void ContentUnSeal2(int start, int end);
	bool Cost(int skillid);
	bool Cost(int user, int skill);
public:
	bool isHadPetSkill(cPropertyData *data, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills);
	bool isHadPetSkill(const vector<sSkill*> &skills, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills);
// private:
//	int getVisibleNO(int userID, bool userTeam, bool isCheckPeopleSpecial);
//	int getVisibleNO(){ return getVisibleNO(m_UserID, false, true); }

	bool runPoxueRuodianPosui3000();
	bool runUnSeal3000(bool isSelf);
	bool runResurgence3000();
	bool runCure3000();
//	bool isAtkMode(){ return cct::get()->isAtkMode(m_UserID); }
	bool isCanAtk(){ return !m_pUserData->m_FightData.cannotAttack; }
	bool isCanMag(){ return !m_pUserData->m_FightData.cannotMagic && !m_pUser->CheckHaveState(199); }
	bool isCanSpec(){ return !m_pUserData->m_FightData.cannotSpesialSkill; }
//	bool isPut(){ return false/*m_pUserPetData->m_ZiZhi.grow < (int)cct::get()->putMenpaiSkills.size()*/; }
//	bool isPutRate();
//	bool isPetRate(){ return rand() % 100 < 38; }
//	bool isUseOtherRate(){ return rand() % 100 < 62; }
//	bool selectAtk();
	// 0不做
	// 1攻击
	// 2状态
	// 3驱动
	// 4法术
	int RunPet();
	bool RunLH();
	bool RunDT();
	bool RunHS();
	bool RunNR();
	bool RunFC();
	bool RunLG();
	bool RunWZ();
	bool RunPT();
	bool RunTG();
	bool RunDF();
	bool RunPS();
	bool RunMW();
	bool RunST();
	bool RunWD();
	bool RunLB();
	bool RunSM();
//	void SaveOneself2(int id);
 	bool resurgence(int user/*, int target*/);
// 	void resurgence2(vector<POINT>& user, vector<POINT>& target,int targetID);
 	bool Cure(int user/*, int target,bool toall=false*/);
	bool CureSelf();
// 	void Cure2(vector<POINT>& tlist, int start, int end);
// 	void UnSeal2(vector<POINT>& tlist, int start, int end);
// 	bool UnSeal(int user, int target);
// 
// 	bool CureMP(int user, int target, bool toall = false);
// 	void CureMP2(vector<POINT>& tlist, int start, int end);


// 	enum eEnemyCorrect
// 	{
// 		eEC道具
// 	};
// 	void CorrectEnemy(vector<POINT>& out,eEnemyCorrect typ);



	// 随机选择目标
	// SelectType 是法术的类型
	// 0 平时自己
	// 1 平时己方
	// 2 战斗自己
	// 3 战斗己方
	// 4 战斗敌方
	// 5 平时战斗自己
	// 6 平时战斗己方
	// 7 被动
	// 8 未
	// 9 战斗己方but自己
	int  find追击反间月光(int userID, int SelectType, bool isCheckPeopleSpecial);
	vector<int>  findSkillType2(int userID, int SelectType);
	vector<int>  findSkillType(int user, int skill);
	// 溅射或者双救
	// Num 0~19 没啥用
	// bLive
	// 0 空位
	// 1 活的
	// 2 存在
	// 3 看得见的活物
	int  find溅射暗器(int usetId, int ID, int idx, int bLive);

	// 目前只用在己方空位
	int  find空位(int ID, int Num, int bLive);




	bool isSkillSeal(int skill);
	bool isSkillResurgence(int skill);
	sFightWork* s_list1, *s_list2;
	cObj* s_obj1, *s_obj2;
	cPropertyData* s_data1, *s_data2;
	void setData(int i1, int i2);
	int getMagicDamage(int user, int target, int Damageup);
	int getPhyDamage(int UserID, int TargetID, int Damageup);
	int getDamage(int user, int target, int skill);
	bool isAtkFromPoint(cPropertyData* data);
	bool isMagFromPoint(cPropertyData* data);
	bool isState(cObj* obj, const vector<int>& ss);
	bool isStateDMag(cObj* obj);
	bool isNotState(cObj* obj, const vector<int>& ss);
	bool isPosion(cObj* obj);
	bool isMpSeal(cPcData* pc);
	bool isMpCure(cPcData* pc);
	bool isMpPhy(cPcData* pc);
	bool isMpMag(cPcData* pc);
	vector<int> getCures(int user);
	vector<int> getSeals(int user);
	vector<int> getCureSeals(int user);
// 	bool runSkill(eSkill skill, int size);
// 	bool runSkill(const vector<eSkill>& skills);
// 	bool runSkill(eSkill s);
	vector<int> getFires(int user);
	bool isHpLessThan(cPropertyData* data, int rate);

};