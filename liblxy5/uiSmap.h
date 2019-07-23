#pragma once
#include "_uiinc.h"

class cInterfaceSmallMap :public cInterfaceFather
{
public:
	cInterfaceSmallMap(){ m_NeedShow = false; }
	bool Init();
	bool ProcessInput();
	bool CheckL();
	cWasFile m_PathPoint;
	cObjWas m_PathPointp[30];
	cWasFile m_PCPoint;
	bool Show(cCanvas* pCanvas);
	int m_xTarget;
	int m_yTarget;
	void OnOff(bool bShow);
	cText m_MousePos;
	cWasFile m_MousePosBack;
private:

	bool m_bInit = false;
	bool PrePareFindPath(int xMouse, int yMouse);

public:
	void clear();
	void addNpc(const std::string& name, int x, int y, ulong color);
	void addNpc(const sNpc* npc);
	struct sText5 { cText t; int x, y; };
	std::vector<sText5*> _npcs;
};

