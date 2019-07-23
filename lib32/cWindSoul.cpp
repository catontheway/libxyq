#include "cWindSoul.h"

#include <list>
#include "cApp.h"


cRender::cRender()
{
	setCanvas(eCanvas::nor);
}

//////////////////////////////////////////////////////////////////////////
cRender::~cRender()
{
	cDraw::getInstance()->onRemove(this);
}


void cRender::setCanvas(eCanvas e)
{
	_canvas = cWindSoul::getInstance()->getCanvas(_eCanvas = e);
}


//////////////////////////////////////////////////////////////////////////
cDraw::cDraw()
{
	std::vector<cRender*> sec;
	_list.insert(std::make_pair(eRender::norFont, sec));
	_list.insert(std::make_pair(eRender::nor, sec));
	_list.insert(std::make_pair(eRender::mapFont, sec));
	_list.insert(std::make_pair(eRender::mapMask, sec));
	_list.insert(std::make_pair(eRender::mapObj, sec));
	_list.insert(std::make_pair(eRender::map, sec));
}
cDraw* cDraw::getInstance()
{
	static cDraw* s_draw = new cDraw();
	return s_draw;
}


void cDraw::push(cRender* render, const uint32_t& flags)
{
	if (render->_eCanvas == eCanvas::chat)
	{
		if (render->_canvas != nullptr)
		{
			if (flags || render->_isDraw)
			{
				render->_canvas->Change();
			}
			else
			{
				render->_canvas->UnChange();
			}
			render->draw(render->_canvas, flags);
			render->setRedraw(false);
		}
	}
	else
	{
		render->_flags = flags;
		_list.at(render->_eRender).push_back(render);
	}
	
}


void cDraw::onRemove(cRender* render)
{
	for (auto& lis : _list)
	{
		auto& li = lis.second;
		bool isok = false;
		for(int k = li.size() - 1; k >= 0; --k)
		{
			if (li.at(k) == render)
			{
				li.erase(li.begin() + k);
				isok = true;
				break;
			}
		}
		if (isok)
		{
			break;
		}
	}
}

void cDraw::render()
{
	for (auto& dlist : _list)
	{
		auto& lis = dlist.second;
		for (auto& it = lis.rbegin(), itend = lis.rend(); it != itend; ++it)
		{
			auto r = (*it);
			if (r->_canvas != nullptr)
			{
				if (r->_flags || r->_isDraw)
				{
					r->_canvas->Change();
				}
				else
				{
					r->_canvas->UnChange();
				}
				r->draw(r->_canvas, r->_flags);
				r->setRedraw(false);
			}
		}
	}
}

void cDraw::clear()
{
	for (auto& li : _list)
	{
		li.second.clear();
	}
}

//////////////////////////////////////////////////////////////////////////
cWindSoul::~cWindSoul()
{
	/*ccc_delete_array*/delete[](_surfaceChat);
	for (auto& fnt : _fonts)
	{
		/*ccc_delete_array*/delete[](fnt.second);
	}
	for (auto& c : _canvas)
	{
		/*ccc_delete_array*/delete[](c.second);
	}
}

cWindSoul* cWindSoul::getInstance()
{
	static cWindSoul* s_windsoul = new cWindSoul();
	return s_windsoul;
}

void cWindSoul::drawSub(cCanvas* canvas, const cAlphaBmp* alphabmp, int x, int y, int w, int h, unsigned char opacity)
{
	if (alphabmp == nullptr)
	{
		return;
	}
	auto al = alphabmp->SubBitmap(x, y, w, h);
	canvas->Draw(*al, BLIT_NORMAL);
	al->SetData(nullptr);
	delete al;
}


bool cWindSoul::create(HWND hwnd, HWND childhwnd, int w, int h, int cw)
{
	auto c = new cCanvas(w, h);
	_canvas.insert(std::make_pair(eCanvas::nor, c));
	_surface.Create(hwnd, *c);

	if (childhwnd != nullptr)
	{
		_surfaceChat = new WSurface();
		c = new cCanvas(cw, h);
		_canvas.insert(std::make_pair(eCanvas::chat, c));
		_surfaceChat->Create(childhwnd, *c);
		_pixel.red = rand() % 4;
		_pixel.green = rand() % 8;
		_pixel.blue = rand() % 4;
	}
	else
	{
		_canvas.insert(std::make_pair(eCanvas::chat, nullptr));
	}
	_fonts.insert(std::make_pair(eFont::smal, new cFont(cApp::createFontEasy(12), 0, 0xFF)));
	_fonts.insert(std::make_pair(eFont::nor, new cFont(cApp::createFontEasy(16), 0, 0xFFF)));
	_fonts.insert(std::make_pair(eFont::big, new cFont(cApp::createFontEasy(20), 0, 0xFF)));
	_fonts.insert(std::make_pair(eFont::chat, new cFont(cApp::createFontEasy(14), 0, 0xFF)));
	return true;
}

cCanvas* cWindSoul::getCanvas(eCanvas e)
{
	return _canvas.at(e);
}

cFont* cWindSoul::getFont(eFont e)
{
	return _fonts.at(e);
}

void cWindSoul::clear()
{
	_canvas.at(eCanvas::nor)->Clear(0);
	if (_surfaceChat != nullptr)
	{
		_canvas.at(eCanvas::chat)->Clear(_pixel);
	}
}


void cWindSoul::blit()
{
	_surface.Blit2Screen();
	if (_surfaceChat != nullptr)
	{
		_surfaceChat->Blit2Screen();
	}
}
