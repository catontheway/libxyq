#pragma once
#include "_global.h"

enum eFormation  //’Û–Õ
{
	normal,//∆’Õ®’Û
	land,//µÿ‘ÿ’Û
	wind,//∑Á—Ô’Û
	tiger,//ª¢“Ì’Û
	dragon,//¡˙∑…’Û
	bird,//ƒÒœË’Û
	snake,//…ﬂÛ¥’Û
	sky,//ÃÏ∏≤’Û
	cloud,//‘∆¥π’Û
	thunder,//¿◊æ¯’Û
	eagle//”•–•’Û
};

// ’Û–Õ
class cInterfaceTeam :public cInterfaceFather
{
public:

	~cInterfaceTeam();
	void FreeFighter(int id);
	cText m_lineupName;
	int   m_ilineupSelect;
	cObjWas m_lineupSelectB;
	vector<cObjWas> m_lineupSelectBP;//“ªπ≤”–11∏ˆ’Û
	cObjWas m_SetFriend;
	cText m_tSetFriend;

	vector<cText>   m_lineupSelectBPT;
	cText m_lineupSelectBT;
	vector<cText> m_Describe;
	cWasFile m_lineupB;
	/*cWfileP m_ControlB;
	cText  m_ControlBT;*/
	cWasFile m_lineupSelectBack;
	bool   m_bLiineupSelect;
	cObjWas m_lineupCancelB;
	cWasFile m_lineupPeople;
	vector<cObjWas*>  m_lineupPeoplepp;
	void  SortLineupPeople();
	vector<cObjWas> m_lineupPeoplep;
	vector<cText> m_lineupPeoplepT;
	void  SetlineupPeople(eFormation select);
	cText  m_lineupBT;
	cText  m_tSmall;
	cText  m_tBig;
	eFormation  m_eLineupSelect;
	cWasFile m_FighterSelect;
	int  m_FighterSelectid;
	//cWasFile m_Back;
	RECT m_FightRect;
	bool Move(int x, int y);
	void OnOff(bool NeedShow);
	void MoveLineSelect(int x, int y);
	bool Init();

	vector<cObj> m_Fighter;
	vector<cText> m_tName;
	vector<cText> m_tLv;
	vector<cText> m_tMengPai;

	array<cObjWas, 5> m_FighterBtns;
	array<cText, 5> m_tFighterBtns;
//	int m_LeaveBegin = 1;
	array<cAccelator, 5> _accs;
	cText m_tLangTime;
	array<cText, 5> _tLeaveings;
	std::vector<cObjWas> _bs;
	std::vector<cText> _ts;

	bool doSwap(int leaveBegin, int select, int target);
	int getLeaveBegin();
	void update(bool setChar, int m_LeaveBegin);

	bool ProcessInput();
	bool ProcessSelectLineup(int xMouse, int yMouse);
	bool CheckL();
	cObjWas* m_plineupButton = 0;
	bool CheckRB();
	ulong GetSmallHead(int id);
	ulong GetPetHead(int id);
	bool Show(cCanvas* pCanvas);
	bool ShowSelectLineup(cCanvas* pCanvas);
	bool UpDate();
	void SetupOneFormationEffect(int Pos, cPropertyData* pPetData, bool UporDown);
	void SetFighterPos(bool enemy);
	vector<int> m_xPosList;
	vector<int> m_yPosList;
	inline int GetXPos(int id);
	inline int GetYPos(int id);
	int  GetReTramTrun(int id);
	int GetTeamTurn(int id){ return m_TeamTurn[id]; }
	void SetTeamTurn(int id, int turn){ m_TeamTurn[id] = turn; }
	void SwapTeamTurn(int id1, int id2);
	void SetFormation(eFormation format, bool enemy = false, bool updatetext = false);

	void UpdatePos();
	void Save(ofstream& File);

	void Load(ifstream& File);
	eFormation m_eEnemyFormation;
	eFormation m_eOurFormation;
private:

	bool AutoSwap(int i);
	bool m_bInit = false;
	vector<int> m_TeamTurn; //”√¿¥µ˜’˚∂”ŒÈŒª÷√
	cFightState* m_pFightState;
	void SetFighterPos2(int** px, int** py, int xOf1, int yOf1, bool enemy);
};
