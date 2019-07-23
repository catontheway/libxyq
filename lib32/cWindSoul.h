#pragma once
// 基于云风的风魂++引擎:
/*
 "               ..;;;;,                     ;;;,
 '           ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
 `     ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/
	   ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
	  .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
	 ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/
	 ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
	:;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
  .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
 ;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/
 ""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/

						Windsoul++

				by 云风 (Cloud Wu)  1999-2001

		http://member.netease.com/~cloudwu
		mailto:cloudwu@263.net

		请阅读 readme.txt 中的版权信息
		See readme.txt for copyright information.


.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
// 
// 抄自云风原话:
// 在遵守下面的约定的情况下, 你可以任意使用风魂所包含的一切代码.但是我对使用这些代码带来的任何后果不负责.我将尽我可能的发现并且修正代码中存在的Bug, 补充新的特性, 回答使用者遇到的问题.如果有一天我对此失去了兴趣, 却有可能放弃对此代码的维护工作.所以你自己需要承担使用这些代码可能存在的风险。
// 版权
// 风魂系列是云风独立开发完成, 以公开源代码的形式对所有人开放使用.如果您想将其或其中一部分代码用于商业软件使用, 请将云风的名字署入软件.如果用于的软件属非赢利性质, 请在软件使用者可以看到的地方注明使用了风魂.若想直接将风魂的源代码用于赢利用途(例如收录于各种光盘, 加入到赢利性质的程序库或控件, 编入各种出版物等等) 请务必先和云风联系.

#include <windows.h>
#include <vector>
#include <map>

#undef MAX
#undef MIN
#include "../libwindsoul/windsoul.h"
#include "../libwindsoul/wsgeo.h"
#include "../libwindsoul/wsfont.h"
#include "../libwindsoul/wsalpha.h"
#include "../libwindsoul/wscanvas.h"
#include "../libwindsoul/wsurface.h"
#undef max
#undef min

typedef WBitmap cBmp;
typedef WAlphaBitmap cAlphaBmp;
typedef WFont cFont;
typedef WChar cChar;
typedef WLine cLine;
typedef WCanvas cCanvas;
//////////////////////////////////////////////////////////////////////////

// 按顺序
enum class eRender { norFont, nor, mapFont, mapMask, mapObj, map };
enum class eCanvas { nor, chat };
class cRender
{
public:
	cRender();
	~cRender();
	void setCanvas(eCanvas e);

	void setRender(eRender e) { _eRender = e; }

	void setRedraw(bool redraw) { _isDraw = redraw; }

	virtual void draw(cCanvas* canvas, const uint32_t& flags){}
protected:
	eRender _eRender = eRender::nor;

	eCanvas _eCanvas;
	cCanvas* _canvas = nullptr;

	uint32_t _flags;
	// 重绘条件: 对象改变(移除,层次,可视,换帧),或对象变化(位置,大小,颜色(调色),透明度)
	bool _isDraw = true;
	friend class cDraw;
};



class cDraw
{
public:
	cDraw();
	static cDraw* getInstance();

	void push(cRender* render, const uint32_t& flags);

	void onRemove(cRender* render);

	void render();

	void clear();

private:
	std::map<eRender, std::vector<cRender*>> _list;
	friend class cWindSoul;
};

enum class eFont { nor, big, smal, chat };
class cWindSoul
{
public:
	~cWindSoul();
	static cWindSoul* getInstance();

	static void drawSub(cCanvas* canvas, const cAlphaBmp* alphabmp, int x, int y, int w, int h, unsigned char opacity);

	bool create(HWND hwnd, HWND childhwnd, int w, int h, int cw);

	cCanvas* getCanvas(eCanvas e);

	cFont* getFont(eFont e);

	void clear();

	void blit();
private:
	std::map<eCanvas, cCanvas*> _canvas;

	WSurface* _surfaceChat = nullptr, _surface;
	WPixel _pixel;
	std::map<eFont, cFont*> _fonts;
};