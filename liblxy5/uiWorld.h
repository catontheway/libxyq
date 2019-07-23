#pragma once
#include "_global.h"


class cWorldMap :public cInterfaceFather
{
public:
	enum  eMap
	{
		eMapWorld,
		eMapWorldEast,
		eMapWorldWest,
		eMapWorldSouth,
		eMapWorldNorth,
		eMapWorldLG,
		eMapWorldTG,
		eMapWorldYG,
		eMapWorldPTY,
		eMapSouth,
		eMapNorth,
		eMapEast,
		eMapWest,
		eMapFenChao, //北俱芦洲 13-16
		eMapLongKu,
		eMapNvWa,
		eMapAL,		//东胜神洲 16-20
		eMapHGS,
		eMapNR,
		eMapPengLai,
		eMapCA,		//南 20-38
		eMapDT,
		eMapDF,
		eMapGLZ,
		eMapHZ,
		eMapHS,
		eMapJY,
		eMapJZ,
		eMapLG,
		eMapMW,
		eMapPS,
		eMapPT,
		eMapSML,
		eMapST,
		eMapD5,
		eMapWZ,
		eMapXXT,
		eMapMJC,
		eMapBX,		//西  38-45
		eMapBQ,
		eMapCS,
		eMapFC,
		eMapZZ,
		eMapXL,
		eMapQLS
	};

	bool CheckRB();
	int m_xPre = 0;
	int m_yPre = 0;
	cText m_text;
	void OnOff(bool bShow);
	bool  MoveTest(cWasFile& Target);
	virtual bool ProcessInput();
	bool ProcessInput0(); //世界
	bool ProcessInput1(); //东
	bool ProcessInput2(); //西
	bool ProcessInput3(); //南
	bool ProcessInput4(); //北
	virtual bool Show(cCanvas* pCanvas);
	bool	Show0(cCanvas* pCanvas);
	bool	Show1(cCanvas* pCanvas);
	bool	Show2(cCanvas* pCanvas);
	bool	Show3(cCanvas* pCanvas);
	bool	Show4(cCanvas* pCanvas);
	virtual bool CheckL();
	int m_Mode;
	cWasFile m_Data[45];
	string m_MapName[45];
	bool Init();
	void InitPos();
	cWasFile* m_pShow = 0;
private:
	bool m_bInit = false;
};

