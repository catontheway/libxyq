#pragma once
#include "_txtinc.h"
#include "eSkill.h"

ccc_txt_class_begin(txtSkill);

txtSkill();

struct sSkill
{
	ulong act;
	ulong state;
	ulong sound;
	eSkiType type;
	eBuff buff;
	eSkiPos pos;
};

// 消耗
struct sCost
{
	// 最大气血%
	int hpmaxper = 0;
	// 当前气血%
	int hpper = 0;
	// 气血
	int hp = 0;
	// 魔法每人
	int mps = 0;
	// 魔法: 等级 / lv + mp
	int lv = 0;
	// 魔法
	int mp = 0;
	// 战意
	int zy = 0;
	// 愤怒
	int ap = 0;
	// 忽略
	bool ignore = false;
	// 
	std::string desc;
};

struct eFFect
{
	eSkiPos pos;
	bool zTop;
};

const std::vector<eSkill>& getFushis(){ return _fushis; }
const std::vector<eSkill>& getZhuijias(){ return _zhuijias; }
const std::map<eSkill, sCost>& getCosts(){ return _costs; }
const std::map<eSkill, std::vector<ulong>>& getActs(){ return _acts; }
const std::map<eSkill, std::vector<ulong>>& getHits(){ return _hits; }
const std::map<eSkill, ulong>& getStateExs(){ return _stateExs; }
const std::map<eSkill, eFFect>& getEffects(){ return _effects; }

// 被动
static bool isEd(eSkill e);
// 门派技能
static bool isMenpai(eSkill e);
// 回师门技能(水遁之类的)
static bool isF1(eSkill e);
// 宝宝技能
static bool isPet(eSkill e);
// 特技
static bool isSpecial(eSkill e);

static int getTargetsCount(eSkill e);
static bool isTargetAtked(eSkill e);
static bool isTargetsTeam(eSkill e);
static void applyIterPos(ulong actid, eSkiPos& pos);
static void applyAtkedDelta(ulong atkid, int& delta);
private:
	void insert(ulong act, ulong state, ulong sound, eSkill skill, eSkiType type = eSkiType::BattleOther, eBuff buff = eBuff::None, eSkiPos pos = eSkiPos::Mid);
	void insert(ulong act, ulong state, ulong sound, eSkill skill, eBuff buff, eSkiPos pos);
	void insert(ulong act, ulong state, ulong sound, eSkill skill, eSkiType type, eSkiPos pos);
	void insert(ulong act, ulong state, ulong sound, eSkill skill, eSkiPos pos);
	void insert(ulong act, ulong state, ulong sound, eSkill skill, eBuff buff);
	void insertAct(eSkill e, ulong a1, ulong a2 = 0, ulong a3 = 0);
	void insertHit(eSkill e, ulong a1, ulong a2 = 0, ulong a3 = 0);
	void insertEffect(eSkill e, eSkiPos pos = eSkiPos::Mid, bool zTop = false);
	void insertEffect(eSkill e, bool zTop);

	void initActs();
	void initFushi();
	void initEffect();

	sSkill _skill;
	std::vector<ulong> _uids;
	eFFect _effect;

	std::vector<eSkill> _fushis;
	std::vector<eSkill> _zhuijias;
	std::map<eSkill, sCost> _costs;
	std::map<eSkill, std::vector<ulong>> _acts;
	std::map<eSkill, std::vector<ulong>> _hits;
	std::map<eSkill, ulong> _stateExs;
	std::map<eSkill, eFFect> _effects;

	friend class txtIcon;
	void insertCost(eSkill e, const std::string& descCost);
ccc_txt_class_end(eSkill, sSkill);