#include "cMapRender.h"


cMapRender* cMapRender::getInstance()
{
	static cMapRender* s_mapRender = new cMapRender();
	return s_mapRender;
}

static const int c320 = cMapReader::c320, c240 = cMapReader::c240, c12 = cMapReader::c12, c16 = cMapReader::c16, c20 = cMapReader::c20;

void cMapRender::getScrew(int x0, int y0, int row, int cel, int bw, int bh, int& x1, int& y1, int& x2, int& y2)
{
	x1 = std::max(0, x0 - row);
	y1 = std::max(0, y0 - cel);
	x2 = std::min(bw, x0 + row + 1);
	y2 = std::min(bh, y0 + cel + 1);

// 	if (x0 == bw - 1)
// 	{
// 		x1 = std::max(0, x0 - row - 1);
// 	}
// 	else if (y0 == bh - 1)
// 	{
// 		y1 = std::max(0, y0 - cel - 1);
// 	}
}


int cMapRender::forScrew(int x0, int y0, bool limit)
{
	int idx = y0 * _bw + x0;
	const auto& bmps = _pMap->bmps;
	if (!bmps.at(idx).isValid())
	{
		return idx;
	}
	static const int ds[][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
	int x1 = limit ? _x1 : 0;
	int x2 = limit ? _x2 : _bw;
	int y1 = limit ? _y1 : 0;
	int y2 = limit ? _y2 : _bh;

	bool isL = false;
	bool isR = false;
	bool isU = false;
	bool isD = false;
	bool isok = false;
	for (int n = 0;; ++n)
	{
		for (int i = 0; i < (n / 2 + 1); ++i)
		{
			x0 += ds[n % 4][0];
			y0 += ds[n % 4][1];

			if (x0 < x1)
			{
				isL = true;
				continue;
			}
			if (x0 >= x2)
			{
				isR = true;
				continue;
			}

			if (y0 < y1)
			{
				isD = true;
				continue;
			}
			if (y0 >= y2)
			{
				isU = true;
				continue;
			}

			idx = y0 * _bw + x0;
			if (!bmps.at(idx).isValid())
			{
				isok = true;
				break;
			}
		}
		if (isok)
		{
			break;
		}
		if (isL && isR && isU && isD)
		{
			break;
		}
	}
	if (isok)
	{
		return idx;
	}
	return -1;
}



void cMapRender::setMap(sMap* pMap)
{
	_pMap = pMap;
	if (_pMap == nullptr)
	{
		reset();
		_x2 = _y2 = 0;
	}
	else 
	{
		_bw = _pMap->info.bw;
		_bh = _pMap->info.bh;
	}
}

void cMapRender::reset()
{
	_bitmap = nullptr;
	_alphas = nullptr;
	_alpha = nullptr;
	_flag = _mask = -1;
	_isLoaded = false;
}

void cMapRender::onSize(float sw, float sh)
{
	_row = std::ceil(sw / c320);
	_cel = std::ceil(sh / c240);
}


bool cMapRender::step(const cocos2d::Vec2& vCenter, bool limit)
{
	if (_pMap == nullptr)
	{
		return false;
	}
	// 先计算位置
	_x320 = std::max(0, (int)vCenter.x / c320);
	_y240 = std::max(0, (int)vCenter.y / c240);
	_x320 = std::min(_x320, _bw - 1);
	_y240 = std::min(_y240, _bh - 1);
	getScrew(_x320, _y240, _row, _cel, _bw, _bh, _x1, _y1, _x2, _y2);
	// 再判断是否加载完成, 不然有可能有黑边
	if (_isLoaded)
	{
		return false;
	}
	auto& info = _pMap->info;
	if (_flag == -1 && _mask == -1)
	{
		_x320 = std::max(0, (int)vCenter.x / c320);
		_y240 = std::max(0, (int)vCenter.y / c240);
		_x320 = std::min(_x320, _bw - 1);
		_y240 = std::min(_y240, _bh - 1);
		getScrew(_x320, _y240, _row, _cel, _bw, _bh, _x1, _y1, _x2, _y2);
		_flag = forScrew(_x320, _y240, limit);
	}
	else if (_mask == -1)
	{
		_bitmap = _pMap->getBitmap(_flag);
		if (_bitmap != nullptr)
		{
			_alphas = &_pMap->alphas.at(_flag);
			if (_alphas->empty())
			{
				if (_pMap->isLoaded())
				{
					_isLoaded = true;
				}
				else
				{
					reset();
				}
			}
			else 
			{
				_mask = 0;
				_alpha = &_alphas->at(0);
			}
		}

	}
	else 
	{
		auto m = _pMap->masks + _alpha->maskIdx;
		if (m->decode((uchar*)_pMap->ptr + *(_pMap->maskOffs + _alpha->maskIdx)))
		{
			_alpha->getAlpha(_bitmap, m->decodes, m->w);
		}
		if((++_mask) == _alphas->size())
		{
			if (_pMap->isLoaded())
			{
				_isLoaded = true;
			}
			else
			{
				reset();
			}
		}
		else
		{
			_alpha = &_alphas->at(_mask);
		}
	}
	return true;
}


void cMapRender::draw(cCanvas* canves, const cocos2d::Vec2& vPort)
{
	if (_pMap == nullptr)
	{
		return;
	}
	int idx;
	for (int k = _y1; k < _y2; ++k)
	{
		for (int i = _x1; i < _x2; ++i)
		{
			idx = k * _bw + i;
			if (_pMap->bmps.at(idx).isValid())
			{
				canves->SetPos(i * c320 - vPort.x, k * c240 - vPort.y);
				canves->Draw(*_pMap->getBitmap(idx), BLIT_NORMAL);
			}
		}
	}
}


void cMapRender::drawMask(cCanvas* canves, const cocos2d::Vec2& vPort)
{
	if (_pMap == nullptr)
	{
		return;
	}
	int idx;
	for (int k = _y1; k < _y2; ++k)
	{
		for (int i = _x1; i < _x2; ++i)
		{
			idx = k * _bw + i;
			const auto& ms = _pMap->alphas.at(idx);
			if (ms.empty())
			{
				continue;
			}
			for (const auto& m : ms)
			{
				if (!m.isValid())
				{
					continue;
				}

				canves->SetPos(i * c320 - vPort.x + m.bx, k * c240 - vPort.y + m.by);
				canves->Draw(*m.bmp, BLIT_NORMAL);
			}
		}
	}
}
