#pragma once
#include "_uiinc.h"


class cFriend :public cInterfaceFather
{
public:
	struct sFriend
	{
		cObj* obj;
		int pre = -1;
		int prebb = -1;
		int dski = -1;
		bool ctrl = true;
	};
	vector<sFriend> _friends;

	cInterfaceFriendQiangHua m_friendqianghua;
	static const int m_MaxNameNum = 8;
	static const int _hInv = 28;
	static const int _yStart = 100;
	cText m_ButtonText[4];

	cObjWas m_Buttonp[4];

	cWasFile m_PetSelectBack[2];
	int  m_TrueFriendSelect = -1;

	cText m_NameList[m_MaxNameNum];//
	cWasFile m_NameListHead[m_MaxNameNum];
	bool UpdateList(int page = -1);
	//cWasFile m_Back;
	bool Move(int x, int y);
	bool Init();
	struct sMessageList
	{
		string	messagePath;
		int id;
		cTaskFather* p;
		int taskid;
		void Save(ofstream& File);
		void Load(ifstream& File);
	};
	void AddMeesage(string path, int id, cTaskFather* ptask, int taskid);
	vector<sMessageList> m_MessageList;

	bool ProcessInput();
	bool CheckL();
	void JuanZeng(int num);
	void UnJuanZeng(int num);
	bool CheckRB();
	bool Show(cCanvas* pCanvas);

	void OnOff(bool NeedShow);

	bool Invite(string name, int fighterid = -1);
	bool UnInvite(string name);
	bool UnInvite(int id);
	vector<sFriendList> m_FriendList;
	void Save(ofstream& File);
	void Load(ifstream&File);
	bool AddFriend(string filepath);
	int FindFriend(string name);
	sFriendList* FindFriend2(string name){ return &m_FriendList[FindFriend(name)]; }
	void ReMove(string name);
	void AddDay();
private:
	void operator=(cFriend& list){}
	bool Invite(int id, int fighterid = -1);//邀请   返回是否邀请成功
	RECT m_Rect;
	bool m_bInit = false;
	int m_nowPage = 0;
	int m_NameNum = 0;
};
