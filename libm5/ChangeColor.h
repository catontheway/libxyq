#include "global.h"

struct sChangeColorMatrix //一个矩阵
{
	int m_start=0;
	int m_end=0;
	int x1 = 0;
	int x2 = 0; 
	int x3 = 0;
	int y1 = 0;
	int y2 = 0;
	int y3 = 0;
	int z1 = 0;
	int z2 = 0;
	int z3 = 0;
	void operator=(sChangeColorMatrix& data)
	{
		m_start=data.m_start;
		m_end=data.m_end;
		x1=data.x1; 
		x2 = data.x2;
		x3 = data.x3;
		y1 = data.y1; 
		y2 = data.y2;
		y3 = data.y3;
		z1 = data.z1; 
		z2 = data.z2;
		z3 = data.z3;
	}
};
struct sChangeColorSplit  //一个部位
{
	vector<sChangeColorMatrix> m_ColorMatrix;
};
struct sChangeColor  //一个配置文件
{
	vector<sChangeColorSplit> m_stagesplit;	
};
struct sChangeColorData;
class cChangeColor
{
public:
	void Init();
	void GetColorMatrix( int part, int matrixid, sChangeColorMatrix& out);
	void Set(DWORD picid);
	void SetPet(DWORD id,int part=0);
	void SetCharacter(DWORD id);
	int GetPartNum();
	int GetMatirxNum(int id);
	sChangeColor m_CharacterColor;
	DWORD m_oldid = 0;
	void Give(sChangeColorData* pData);
	void Give2(sChangeColorData* pData, int modeid,int part=0);
private:	
	
};

