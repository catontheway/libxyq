#pragma  once
#include "_asert.h"

int GetDirection4(int x1, int y1, int xTarget, int yTarget);//通过原点和终点得到向量的方向
//int GetDirection8(int x1, int y1, int xTarget, int yTarget);//通过原点和终点得到向量的方向
int GetDirection8Ex(int predirection, int x1, int y1, int xTarget, int yTarget);
int GetReverseDirection(int Direction);                     //得到相反的方向
int GetRotateDirection(int nowDirection, bool directNum4=true, bool turn = 0); //用于角色旋转,得到下一方向
bool isOn(int x, int y, RECT& rect);
inline bool isOn(int x, int y,int w,int h, int left,int top,int right,int bottom);
ulong GetPriceColor(INT64 Price);

int GetCharacterExp(int Lv); //通过等级计算升级经验
int GetPetExp(int Lv); //通过等级计算升级经验
int GetNormalFightExp(int OurLv, int EnemyLv, int NumOfPeople = 1);//计算烧双经验
int GetMainSkillExp(int lv); //计算师门技能学习经验 
int GetMainSkillMoney(int lv);//计算师门技能学习金钱
int   GetXiuLIanExp(int lv);
bool  CheckCross(RECT& rect1, RECT& rect2, RECT& outrect);  //两个矩形取交集,如果没有交集,返回0
bool  CheckCross(RECT& rect1, RECT& rect2);
int   GetFrameIndex(int FrameMax, int NowFrame, int DirectionNum, int NowDirection);

bool StringToWString(const std::string &str, std::wstring &wstr);
int Direction8To4(int direction); 
void CoutPoint(float distance, float xstart, float ystart, float xend, float yend, float  &xout, float& yout);
float CoutDistance(float xstart, float ystart, float xend, float yend);
INT64 AddUpZero(INT64& target, const int num);//target加上num 如果结果小于0  返回target+num的值   target等于0 否则返回0
int ReadInt(HANDLE& f);
int ReadCharNum(HANDLE& f,char& out);//读取1字节,如果是数字,返回1,否则返回0 如果是文件结尾,返回2
int GetNumByChar(char data);
void SetINT(int num, int id);
bool CheckINT(int num, int id);
