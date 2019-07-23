#pragma once
#include "../libcc/_cc.h"
#include "../libcc/_32.h"
#include "../libcc/_coco.h"



class cSprite;
// u: ui  ui 相关命名空间
namespace ccu
{
	void hideSpriteDesc();
	cSprite* getSpriteDesc();

	static const int zTag = INT_MAX - 1;
	static const int zDesc = zTag - 1;
	static const int zDialog = zDesc - 1;
	static const int zJob = -1;
	static const int zMenu = -1;
	static const int zHead = -1;
	static const int zShichen = -1;

	static const ulong uBtn1 = 0xF9494E3A;
	static const ulong uBtn2 = 0x79D01E0E;
	static const ulong uBtn4 = 0x86D66B9A;
	static const ulong uClose = 0xF11233BB;
	static const ulong uAdd = 3296232902;
	static const ulong uSub = 1577923263;
	static const ulong uUp = 0x08E2D199;
	static const ulong uDown = 0xC013B53B;
	static const ulong uLeft = 0xB05126E8;
	static const ulong uRight = 0x26066130;
	static const ulong uShadow = 3705976162;

	static const ulong uGrid33 = 3705976162;
	static const ulong uGrid34 = 0xCD2B38FD;
	static const ulong uGrid55 = 0xE9C090A3;

	static const ulong uItemCross = 0x6F88F494;
	static const ulong uItemSelect = 0x10921CA7;
	static const ulong uItemSelect9 = 0xD12BC31F;
	static const ulong uPetSelect = 0xF151309F;
	
	static const ulong uPad = 0xC6476D82;
	static const ulong uPad2 = 0x2A797B7F;

	static const ulong uDesc = 0xB5FDF1AC;
	// 居中的
	static const ulong uDescMid = 0xA5ECFCA4;
	static const ulong uDescBlack = 0xB0025203;
	static const ulong uEdgeSross = 0x1761E01E;
	static const ulong uEdgeThin = 0xEE0BCB8A;
	
	// static const ulong uChannel = 0xA0120D38;
	static const ulong uDialog = 0x73D983B7;
	static const ulong uDialog2 = 0xB012CF09;
	static const ulong uDialogName = 0x804455A1;
	static const ulong uDialogSelect = 0x802EB60A;
	

	static const ulong uSkiNextPage = 0xCB50AB1D;
	static const ulong uEquipBack = 0xA393A808;

	// m_FaceTextBack.Load(0xA4120EA9);
}