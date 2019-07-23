#pragma once
#include "_uiinc.h"


class cInterfaceFather
{
public:
	int m_Sleeptime = 0;
	virtual bool Init(){ return true; }
	virtual bool initShow(){ return true; }
	virtual bool ProcessInput();
	virtual bool ProcessInputMore(){ return false; }
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	virtual bool CheckRB(){ return false; }
	virtual void OnOff(bool NeedShow);
	virtual void OnOff(){ OnOff(!m_NeedShow); }
	virtual bool Move(int x, int y);
	bool m_NeedShow = false;
	int m_xPos = 0;
	int m_yPos = 0;
	int  m_Prex = 0;
	int  m_Prey = 0;
	bool m_bMoveMode = false;
	bool m_bMove = false;
	bool isInRect(long x, long y, cWasFile* pPic);
	cObjWas m_Cancel;

	bool CheckOn(cWasFile* pTarget, int id);
	bool CheckOn(cObjWas* pTarget, int id);
	bool CheckOn(cText* ptext, int id);

	int m_Select = -1;
	int m_SelectPre = -1;
	cWasFile* m_frampre = 0;
	cObjWas* m_framprep = 0;
	void ResetButton();
protected:
	struct sChild 
	{
		enum class eType{ File, Obj, Text };
		void addChild(eType _e, ulong uid, cWasFile* file, string text, ulong tColor, int x, int y);

		sChild(ulong uid, string text, ulong tColor, int x, int y)
		{
			addChild(eType::File, uid, nullptr, text, tColor, x, y);
		}

		sChild(ulong uid, string text, int x, int y)
		{
			addChild(eType::File, uid, nullptr, text, RGB(0xFF, 0xFF, 0xFF), x, y);
		}

		sChild(ulong uid, int x, int y)
		{
			addChild(eType::File, uid, nullptr, "", RGB(0xFF, 0xFF, 0xFF), x, y);
		}

		sChild(cWasFile* file, string text, ulong tColor, int x, int y)
		{
			addChild(eType::Obj, 0, file, text, tColor, x, y);
		}

		sChild(cWasFile* file, string text, int x, int y)
		{
			addChild(eType::Obj, 0, file, text, RGB(0xFF, 0xFF, 0xFF), x, y);
		}

		sChild(cWasFile* file, int x, int y)
		{
			addChild(eType::Obj, 0, file, "", RGB(0xFF, 0xFF, 0xFF), x, y);
		}


		sChild(string text, ulong tColor, int x, int y)
		{
			addChild(eType::Text, 0, nullptr, text, tColor, x, y);
		}

		sChild(string text, int x, int y)
		{
			addChild(eType::Text, 0, nullptr, text, RGB(0xFF, 0xFF, 0xFF), x, y);
		}

		
		int xx, yy;
		eType e;
		void* ptr = nullptr;
		void* ptr2 = nullptr;
		function<void(const sChild* c)> onClick = nullptr;
		function<void(const sChild* c)> onFrame = nullptr;
		operator ulong(){ return (ulong)ptr; }
		int tag = INT_MIN;
		bool checkon = true;
	};

	void addChild(sChild c)
	{
		_children.push_back(c);
	}

	void loadBack(ulong uid)
	{
		m_Back.Load(uid);
		m_Back.SetStatic(true);
	}

public:
	~cInterfaceFather()
	{
// 		forr(_children, i)
// 		{
// 			auto& c = _children[i];
// 			switch (c.e)
// 			{
// 			case sChild::eType::File:
// 				delete (cWasFile*)c.ptr;
// 				delete (cText*)c.ptr2;
// 				break;
// 			case sChild::eType::Obj:
// 				delete (cObjWas*)c.ptr;
// 				delete (cText*)c.ptr2;
// 				break;
// 			case sChild::eType::Text:
// 				delete (cText*)c.ptr;
// 				break;
// 			}
// 		}
		_children.clear();
	}

protected:
	vector<sChild> _children;
	bool _isInit = false;
	bool _isRclose = true;
public:
	cWasFile m_Back;
};

