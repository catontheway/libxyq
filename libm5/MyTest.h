#pragma once
#include "_inc.h"
#include <vector>
#include <set>
#if ccc_date
using namespace std;
class MyTest
{
public:
	static MyTest* getInstance();
	void switch加点方案();
	// 血条
	bool isShowBloodBar = true;
	// 瞬移
	bool isTeleporting = false;
	int juQing = 0;
	int mapSpeed = 2;
	int isClassical = 1;
	int per加点 = 10;
	int perLvup = 1;
	bool isEnemyPKMode = false;
	bool isAutoAtkMode = true;
//	bool isAddPoint50 = false;
	bool isAutoBattle = false;
	bool isControl = false;
	static const int lvFor渡劫头像 = 95;
	static const int minRoleLv = 5;
	static const int maxRoleLv = 175;
	static const int maxBabyLv = 180;
	static const int lv大雁塔触发 = 25;
	static const int lvGapFromRoleAndBaby = 10;
	static const int point额外 = 0;
	static const int maxXiuLian = 30;
	static const int maxSkillLv = 200;
	static const int per进阶 = 45;
	static const int 药品数量 = 5;
	std::set<int> newBabys;
	std::vector<int> putMenpaiSkills;
	std::vector<int> putPetSkills;
	string strDescTemp;
	bool isPushRole15 = false;
	std::set<string> mapNames;
	std::vector<std::string> friendNames;
	void pushZuoqi(const string &desc, unsigned long id);
	void pushZuoqiHead(const string &desc, unsigned long id);
	void pushHome(const string &desc, unsigned long id);
	void pushHomeHead(const string &desc, unsigned long id);
	void pushItem(const string &desc, unsigned long id);
	void pushItemHead(const string &desc, unsigned long id);
	void pushChat(const string &desc, unsigned long id);
	void pushOther(const string &desc, unsigned long id);
	void pushNpc(const string &desc, unsigned long id);
	void pushNpcHead(const string &desc, unsigned long id);
	void pushMpSkill(const string &desc, unsigned long id);
	void pushMpSkillHead(const string &desc, unsigned long id);
	void pushMpHead(const string &desc, unsigned long id);
	void pushBabySkill(const string &desc, unsigned long id);
	void pushBabySkillHead(const string &desc, unsigned long id);
	void pushSpecialSkill(const string &desc, unsigned long id);
	void pushSpecialSkillHead(const string &desc, unsigned long id);
	void pushFuzhuSkillHead(const string &desc, unsigned long id);
	void pushBabyHead(const string &desc, unsigned long id);
	void pushBaby(const string &desc, unsigned long id);
	void pushRoleHead(const string &desc, unsigned long id);
	void pushRole(const string &desc, unsigned long id);
	void pushRoleZuoqi(const string &desc, unsigned long id);
	void pushWeapon(const string &desc, unsigned long id);
	void pushWeaponHead(const string &desc, unsigned long id);
	void saveMyWdf();


	void pushWdf(const string &desc, unsigned long id);
	void pushWdf2(const string &desc, unsigned long id);
	void pushWdf3();
	void saveWdf();
	void saveWdf3();
	void pushTable(unsigned long id, unsigned long idNew);
	unsigned long getUid(unsigned long id);
	void pushIgnore(unsigned long id);
	int isIgnore(unsigned long id);
	// 属性不知道, 反正包裹只有药品了
	void playerNormalize(int lv);
	void initControl();
	void init();
	int getBabyLv();
	// 0~161
	void useCard();
	void addMoney(int money);
	// 好像是PK战斗
	void PK();
	void PK(int state);
	void PKinit();
	void PKover();
	void PKNpc();
	void 暗雷场景马上战斗();
	bool isInBattle();
	void set仙店(int lv);
	bool isAtkMode(int id);
	bool isSpecialOrZZ(int zz);
	// 根据门派返回 特技*10+石头
	int getDesbinOf头盔(int e, int teji = 0);
	int getDesbinOf项链(int e, int teji = 0);
	int getDesbinOf武器(int e, int teji = 0);
	int getDesbinOf铠甲(int e, int teji = 0);
	int getDesbinOf腰带(int e, int teji = 0);
	int getDesbinOf鞋子(int e, bool isAtk = false, int teji = 0);
	int getJinjie(int lv);
};
#endif


// 1470854			海底迷宫
// 64379937			小西天
// 742230768		大雁塔1
// 85077806			大雁塔2
// 406097195		长寿郊外
// 538028226		小雷音寺
// 557996108		北俱芦洲
// 566146437		普陀山
// 640111112		长安城
// 644754520		江南野外
// 790546186		长寿村
// 890606953		傲来国
// 939562604		狮驼岭
// 1248131261		魔王寨
// 1256371635		大唐官府
// 1262960812		东海湾
// 1405279831		方寸山
// 3551908874		地狱迷宫
// 1518748497		地狱迷宫2
// 1527631065		月宫
// 2928358529		龙窟
// 1706625738		龙窟2
// 1761009057		建邺城
// 1880023811		阴曹地府
// 949968628		战斗比武1
// 2663553693		战斗比武2
// 2029784250		战斗比武3
// 4077106857		战斗比武4
// 4212547124		战斗比武5
// 2043826402		龙宫
// 2073070538		帮战入场
// 2220736812		战斗BOSS
// 2229463928		帮派
// 2261053509		牢房
// 2298843722		战斗1
// 2991105991		战斗2
// 3238412417		战斗3
// 2353332476		花果山
// 2360055652		女儿村
// 2398410866		东海海底
// 2463963770		化生寺
// 2801018603		未知鬼城
// 2805137540		家
// 2852135814		战神山
// 2889442616		盘丝岭
// 2967073802		凤巢
// 3007230343		凤巢2
// 3201585121		比武场
// 3597537448		大唐境外
// 3825823042		女娲神迹
// 3889067580		天宫
// 3928368410		大唐国境
// 3956019824		地狱迷宫5
// 4246654863		五庄观
// 2454059136		未知
