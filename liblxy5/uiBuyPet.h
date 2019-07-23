#pragma once
#include "_uiinc.h"

class  uiBuyPet : public cInterfaceFather
{
public:
	bool Init();
	bool Move(int x, int y);
	bool Show(cCanvas* pCanvas);
//	void OnOff(bool bshow);
	virtual bool initShow();
	void addPet(cPet* p);
//private:
	virtual bool ProcessInput();
	virtual bool CheckL();
	bool CheckRB();
	bool Set(cPet* item, int rate);
	void UpdateText();


	RECT m_Rect;
	cWasFile m_MouseOnMark;

	cWasFile m_SelectMark;
	int m_TrueSelect = -1;

	array<cText, 6> m_Text;
//	int m_ItemNum = 0;
//	array<cPet*, 20> m_Item;
	vector<cPet*> m_Item;
	array<int, 20> m_pricerate;
	array<cWasFile, 20> m_ItemHead;

	bool m_bInit = false;
	int m_PriceTotal;
	void CoutTotal();
	//cWasFile m_Back;

	cWasFile m_Button, m_Button2;
	cInterfaceNumShuRu m_NumBuy;
};







struct sShangPinPet
{
	int m_modeid;
	string m_name;
	vector<int>  m_skillid;
	int m_price;
	sAddPoint m_addpoint; //加点
	sZiZhi m_zizhi;//资质
	sChangeColorData2 m_ranse;
	void operator=(sShangPinPet pet)
	{
		m_modeid = pet.m_modeid;
		m_name = pet.m_name;
		m_skillid.swap(pet.m_skillid);
		m_price = pet.m_price;
		m_addpoint = pet.m_addpoint; //加点
		m_zizhi = pet.m_zizhi;//资质
		m_ranse = pet.m_ranse;
	}
	void Set(int modeid, sAddPoint* addpoint = 0, int stronglv = 100, bool needskill = false);
	void AddSkill(int id);
	void Save(ofstream& File);
	void Read(ifstream& File);//从商店读取简化的召唤兽
	void Load(ifstream& File, int positon);//从存档读取
	void LoadEasy(int id, int strong = -1);
};


struct sFriendList;
class  cInterFaceBuyPet : public cInterfaceFather
{
public:

	void UpdateText();
	RECT m_Rect;
	cWasFile m_MouseOnMark;

	cWasFile m_SelectMark;
	int m_TrueSelect = -1;

	virtual bool ProcessInput();
	virtual bool CheckL();
	bool CheckRB();
	bool Init();
	bool Set(sShangPinPet& item, int rate);
	bool Move(int x, int y);
	bool Show(cCanvas* pCanvas);
	cText m_Text[6];
	int m_ItemNum = 0;
	sShangPinPet m_Item[20];
	int m_pricerate[20];
	cWasFile m_ItemHead[20];
	void OnOff(bool bshow);
	void Init2(sFriendList* plist, uint page1, uint page2);
	void Init3();
	void AddPage();
	void SubPage();
	void updatePetsAfterBuy(string name, int stronglv, int lv);
	sShangPinPet& GetPet3(int id);
private:
	cWasFile m_Left;
	cWasFile m_Right;
	vector<sShangPinPet> m_ShangPinList[8];
	vector<sShangPinPet> m_ShangPinList3;
	bool m_bInit3 = false;
	int m_page = 0;
	int m_page2 = 0;//比如0级召唤兽,如果数量超过20,则m_page2可以有两页
	sFriendList* m_plist = 0;
	bool m_bInit = false;
	int m_PriceTotal;
	void CoutTotal();
	//cWasFile m_Back;

	cWasFile m_Button;
	cInterfaceNumShuRu m_NumBuy;
};



