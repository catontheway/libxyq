#pragma once
#include "_objinc.h"

struct sJiaJu
{
	sItem2 m_JiaJu;
	int m_xPos;
	int m_yPos;
	int m_Direction = 0;
	void Save(ofstream& File)
	{
		File << g_strSpace;
		File << m_xPos << g_strSpace;
		File << m_yPos << g_strSpace;
		File << m_Direction << g_strSpace;
		m_JiaJu.Save(File);
	}
	void Load(ifstream& File)
	{
		File >> m_xPos;
		File >> m_yPos;
		File >> m_Direction;
		m_JiaJu.Load(File);
	}
};

class cFangWu
{
public:
	void GetBB();
	void RemoveBB(cObj* yahuan);
	void RemovePreJiaJu();
	cFangWu();
	void Init();
	int GetHuanJin();
	void GoIn();
	void CheckHuanJin();
	bool AddJiaJu(sJiaJu& jiaju);
	string GetMapName();
	void Move(int x, int y, cObj* p);

	int GetGuiMo(){ return m_GuiMo; }
	void SetGuiMo(int num);
	void Save(ofstream& File);
	void Load(ifstream& File);

	vector<sNpc> m_List; //镇宅兽数  影响环境度 =5点环境度

	sNpc m_GuanJia;//管家 
	sItem2 m_DiBan;//地板
	vector<sJiaJu> m_JiaJu;//家具
	vector<int>  m_YaHuangIDList;
private:
	int m_PreHuanJin = 0;
	bool m_bInit = false;
	int m_GuiMo = -1;//规模 规模越大,能摆放的家具越多
	int m_HuanJinDu = 0;//环境度  
};
