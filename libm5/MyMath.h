#pragma  once

#include <windows.h>
#include <string>


using namespace std;

enum eWeaponType
{
	eWeaponType剑,
	eWeaponType刀,
	eWeaponType枪,
	eWeaponType锤,
	eWeaponType斧,
	eWeaponType扇,
	eWeaponType爪,
	eWeaponType棒,
	eWeaponType飘带,
	eWeaponType鞭,
	eWeaponType环,
	eWeaponType双剑,
	eWeaponType珠,
	eWeaponType弓,
	eWeaponType杖
};
enum eJueSe
{
	eJuSe剑侠客,
	eJuSe逍遥生,
	eJuSe飞燕女,
	eJuSe英女侠,
	eJuSe虎头怪,
	eJuSe巨魔王,
	eJuSe骨精灵,
	eJuSe狐美人,
	eJuSe龙太子,
	eJuSe神天兵,
	eJuSe玄彩蛾,
	eJuSe舞天姬,
	eJuSe巫蛮儿,
	eJuSe羽灵神,
	eJuSe杀破狼
};
void GetWeaponType(int modeid, int& out1, int & out2);
int GetDirection4(int x1, int y1, int xTarget, int yTarget);//通过原点和终点得到向量的方向
//int GetDirection8(int x1, int y1, int xTarget, int yTarget);//通过原点和终点得到向量的方向
int GetDirection8Ex(int predirection, int x1, int y1, int xTarget, int yTarget);
int GetReverseDirection(int Direction);                     //得到相反的方向
int GetRotateDirection(int nowDirection, BOOL directNum4=TRUE, BOOL turn = 0); //用于角色旋转,得到下一方向
BOOL isOn(int x, int y, RECT& rect);
inline BOOL isOn(int x, int y,int w,int h, int left,int top,int right,int bottom);
DWORD GetPriceColor(int Price);

INT64 GetCharacterExp(int Lv); //通过等级计算升级经验
INT64 GetNormalFightExp(int OurLv, int EnemyLv,int NumOfPeople=1);//计算烧双经验
INT64 GetMainSkillExp(int lv); //计算师门技能学习经验 
INT64 GetMainSkillMoney(int lv);//计算师门技能学习金钱
int   GetXiuLIanExp(int lv);
BOOL  CheckCross(RECT& rect1, RECT& rect2, RECT& outrect);  //两个矩形取交集,如果没有交集,返回0
BOOL  CheckCross(RECT& rect1, RECT& rect2);
int   GetOffsetID(int FrameMax, int NowFrame, int DirectionNum, int NowDirection);

BOOL StringToWString(const std::string &str, std::wstring &wstr);
int Direction8To4(int direction); 
void CoutPoint(float distance, float xstart, float ystart, float xend, float yend, float  &xout, float& yout);
float CoutDistance(float xstart, float ystart, float xend, float yend);
int AddUpZero(int& target, const int num);//target加上num 如果结果小于0  返回target+num的值   target等于0 否则返回0
int ReadInt(HANDLE& f);
int ReadCharNum(HANDLE& f,char& out);//读取1字节,如果是数字,返回1,否则返回0 如果是文件结尾,返回2
int GetNumByChar(char data);
void SetINT(int num, int id);
BOOL CheckINT(int num, int id);
