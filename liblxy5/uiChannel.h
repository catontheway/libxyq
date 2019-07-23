#pragma once
#include "_global.h"

enum eChannel
{
	ec当前, //0
	ec队伍,    //1
	ec世界,
	ec系统,
	ec私聊
};
class cInterfaceChannel :public cInterfaceFather
{
public:
	void OnOff(bool NeedShow){};
	cWasFile m_MoveIcon;
	cWasFile* m_pCurrentChannel;
	cWasFile m_Channel[5];
	cWasFile m_Face[129];
	sFaceText m_ContextList[30];
	int     m_ContextStart;  //第1条的位置
	int     m_ContextNum;//总共有多少条
	int     m_ContextShowStart;//从哪条开始显示
	int    m_ContextShowNum;
	bool AddNewString(string str, string name = "", int channel = 3);
	void UpDateShow();
	void SetPos();
	int m_WidthChannel;
	int m_HeightChannel;

	int m_HeightCube;//行距
	//cWasFile m_Back;
	cObjWas m_BackP[4];
	bool Init();
	ulong m_FaceId[129];
	virtual bool ProcessInput();
	virtual bool CheckL();
	bool Show(cCanvas* pCanvas);
	bool Move(int x, int y);
};
