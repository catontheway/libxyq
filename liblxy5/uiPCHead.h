#pragma once
#include "_global.h"

class cPCHead :public cInterfaceFather
{
public:

	bool CheckL();

	int m_MouseOn;
	int m_MouseOnPre = -1;
	//记录上一次的角色血条,如果不一样,再计算
	//总比每帧都计算乘法除法好


	void UpdatePcHp();
	void UpdatePcMp();
	void UpdatePcCp();
	void UpdatePcExp();
	void UpdatePetHp();
	void UpdatePetMp();
	void UpdatePetExp();

	bool UpDateHead();
	cWasFile m_PetFaceBack; //召唤兽头像背景
	cWasFile m_PCFace;
	vector<cWasFile> m_TeamFace;
	vector<cWasFile> m_TeamBack;
	vector<cWasFile> m_TeamPetFace;
	cWasFile m_PetFace;

	cPet*       m_pPet = 0;      //在选择时的召唤兽
	void SetPetHead(ulong head);
	void UpdateDate();
	bool UpdatePet();
	bool Init();
	// 战斗移动到右下角
	void MoveTeamHead(bool mode);
	bool SetPcID(int id);
	bool Show(cCanvas* pCanvas);
	bool ProcessInput();
	virtual void OnOff(bool NeedShow){};
	bool CheckRB();

	vector<cObjWas> m_EmptyLinep;
	cWasFile m_EmptyLine;


	vector<cObjWas> m_HPlinep;
	vector<cObjWas> m_HeartHurtp;
	vector<cObjWas> m_MPlinep;
	vector<cObjWas> m_EXPlinep;

	cWasFile m_MPline;
	cWasFile m_CPline;
	cWasFile m_HeartHurt;
	cWasFile m_EXPline;
	cWasFile m_HPline;

	cWasFile m_Heart;
	cWasFile m_PetHead;
	cWasFile m_CharacterHead;
	cText m_TMouseOnLine;
private:
	bool m_bPetHeadMode[5];
	bool m_bInit = false;
};

