#pragma once
#include "_uiinc.h"

class ui5B8B823E : public cInterfaceFather
{
public:
	virtual bool initShow();
	virtual void onInitShow(int tag, int idx, bool isShow){}
	bool init(int cel, int row, int size);
	virtual cInterfaceFather::sChild initBtn(int k, int i);
	virtual cInterfaceFather::sChild initWas(int k, int i);

	int _page = 0;
	int _row;
	int _cel;
	int _size;
	cText* _title = nullptr;
	vector<cWasFile*> _objs;
};


class uiXiangRui :public ui5B8B823E
{
public:
	virtual void onInitShow(int tag, int idx, bool isShow);
	virtual bool Init();
	virtual sChild initBtn(int k, int i);
	virtual sChild initWas(int k, int i);
	vector<cWasFile*> _obj2s;
};


class uiHeadTop :public ui5B8B823E
{
public:
	virtual void onInitShow(int tag, int idx, bool isShow);
	virtual bool Init();
	virtual sChild initBtn(int k, int i);
	virtual sChild initWas(int k, int i);
};


class uiFoot : public ui5B8B823E
{
	virtual void onInitShow(int tag, int idx, bool isShow);
	virtual bool Init();
	virtual sChild initBtn(int k, int i);
	virtual sChild initWas(int k, int i);
};



class uiFoot2 : public ui5B8B823E
{
	virtual void onInitShow(int tag, int idx, bool isShow);
	virtual bool Init();
	virtual sChild initBtn(int k, int i);
	virtual sChild initWas(int k, int i);
};




class uiAnimalSign : public ui5B8B823E
{
	virtual void onInitShow(int tag, int idx, bool isShow);
	virtual bool Init();
	virtual sChild initBtn(int k, int i);
	virtual sChild initWas(int k, int i);
};


class uiChangeCharacter : public ui5B8B823E
{
	virtual void onInitShow(int tag, int idx, bool isShow);
	virtual bool Init();
	virtual sChild initBtn(int k, int i);
	virtual sChild initWas(int k, int i);
	vector<cText*> _tNames;
};

class uiCangKu : public cInterfaceFather
{
public:
	virtual bool Init();
	virtual bool Move(int x, int y);
	virtual bool ProcessInput();
	virtual bool CheckRB();
	virtual bool Show(cCanvas* pCanvas);
	array<cItemSelect, 2> _itemSelects;
	array<sItem2, 20> _items;
};



class uiDesc : public cInterfaceFather
{
public:
	virtual bool initShow();
	virtual bool Init();
	virtual bool Show(cCanvas* pCanvas);
	int _page = 0;
	int _size;
	cText* _title = nullptr;
	cText* _text = nullptr;
	sFaceText _ftext;
};