#pragma once
#include "_inc.h"

class expRank
{
public:
	expRank();
	expRank(int w, int winv = 0);
	void init(int w, int winv = 0);
	void iters(const std::vector<cSprite*>& sprites, bool end = false);
	void iters();
	void iter(cNode* node, bool end = false);
	void iter();
	Size getSize()const { return Size(_wMax, _y); }
private:
	int _w = 0, _x = 0, _y = 0, _wMax = 0, _hMax = 0, _kMax = 0, _wInv = 0;
	std::vector<std::vector<cSprite*>> _sprites;
	bool _ignoreKxy = false;
public:
	int _btnw = 0, _btnh = 0, _labelw = 0;
	static const int c10 = 10;
};
