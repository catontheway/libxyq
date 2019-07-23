#pragma once
#include "_asert.h"

// const int TOTAL_MAP_WIDTH = 350;
// const int TOTAL_MAP_HEIGHT = 350;
class cMyMap;
class cObj;
struct VecInt
{
	int x = 0;
	int y = 0;
};

struct AstartNode
{
	//此节点在堆中的位置
	int iHeapPosition = -1; 
	int iG = -1;
	int iH = -1;
	int iF = -1;
	//检测是否可以通过
	int iColor = -1;
	//检测是否在开启列表中
	int isOpen = 0; 
	VecInt father;

	int getF()
	{
		return iH + iG;
	}
};

// 二叉堆
class cHeap
{
public:
	cHeap();
	//移除堆中的第一个元素
	void removeFront(AstartNode**g_Map); 
	//往堆中添加元素
	void push_back(VecInt element, AstartNode**g_Map); 
	//当F值改变时，更新堆
	void newHeap(int position, AstartNode**g_Map);    
	int getSize();
	int getMinF(AstartNode**g_Map);
	bool empty();
	void clear();
	VecInt begin();
private:
	vector<VecInt> vecs;
};

class cFindPath
{
public:
	~cFindPath();
	bool InitMap();
	bool findAstart(cObj* pObj, int Xend, int Yend);
	// 地图二维节点数据
	AstartNode** g_Map;
	//开启列表
	cHeap m_iOpenList; 
	// 用地图初始化二维节点数据
	void  setDataByMap(cMyMap* pMap);
	void  Free();

	int m_Width = 0;
	int m_Height = 0;
private:
	// 检测是否发现了正确的路径
	bool m_isFind = false; 
};

class AES
{
public:
	AES(unsigned char* key);
	virtual ~AES();
	unsigned char* Cipher(unsigned char* input);
	unsigned char* InvCipher(unsigned char* input);
	void* Cipher(void* input, int length = 0);
	void* InvCipher(void* input, int length);

	void Cipher(char *input, char *output);
	void InvCipher(char *inut, char *output);

private:
	unsigned char Sbox[256];
	unsigned char InvSbox[256];
	unsigned char w[11][4][4];

	void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);
	unsigned char FFmul(unsigned char a, unsigned char b);

	void SubBytes(unsigned char state[][4]);
	void ShiftRows(unsigned char state[][4]);
	void MixColumns(unsigned char state[][4]);
	void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

	void InvSubBytes(unsigned char state[][4]);
	void InvShiftRows(unsigned char state[][4]);
	void InvMixColumns(unsigned char state[][4]);

	int strToHex(const char *ch, char *hex);
	int hexToStr(const char *hex, char *ch);
	int ascillToValue(const char ch);
	char valueToHexCh(const int value);
	int getUCharLen(const unsigned char *uch);
	int strToUChar(const char *ch, unsigned char *uch);
	int ucharToStr(const unsigned char *uch, char *ch);
	int ucharToHex(const unsigned char *uch, char *hex);
	int hexToUChar(const char *hex, unsigned char *uch);
};