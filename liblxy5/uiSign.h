#pragma once
#include "_uiinc.h"

class uiSign : public cInterfaceFather
{
public:
	virtual bool initShow();
	virtual bool Init();
	virtual bool Show(cCanvas* pCanvas);
	cText* _text = nullptr;
	cText* _textBtn = nullptr;
	sFaceText _ftext;
};