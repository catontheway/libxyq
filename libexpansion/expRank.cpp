#include "expRank.h"

expRank::expRank()
{
}

expRank::expRank(int w, int winv /*= 0*/)
{
	init(w, winv);
}

void expRank::init(int w, int winv /* = 0 */)
{
	if (_btnw == 0)
	{
		cButton* button = cButton::create4();
		_btnw = button->getContentSize().width;
		_btnh = button->getContentSize().height;
		_labelw = cLabel::create("88888888")->getContentSize().width;
	}
	_w = w;
	_x = _y = _wMax = _hMax = _kMax = 0;
	_wInv = winv;
	_sprites.clear();

}

void expRank::iters(const std::vector<cSprite *>& sprites, bool end /* = false */)
{
	int wMax = std::max(_labelw, _wInv), hMax = 0, kMax = 0, kxMax = 0;
	for (const auto& sprite : sprites)
	{
		if (!sprite->isValid())
		{
			continue;
		}
		if (wMax < sprite->getInfo()->width)
		{
			wMax = sprite->getInfo()->width;
		}
		if (hMax < sprite->getInfo()->height)
		{
			hMax = sprite->getInfo()->height;
		}
		if (kMax < sprite->getInfo()->ky)
		{
			kMax = sprite->getInfo()->ky;
		}
		if (kxMax < sprite->getInfo()->kx)
		{
			kxMax = sprite->getInfo()->kx;
		}
	}
	if (_x + wMax > _w)
	{
		_x = wMax + c10;
		for (const auto& sprite : sprites)
		{
			if (!sprite->isValid())
			{
				continue;
			}
			// sprite->setPositionX((_ignoreKxy ? sprite->getInfo()->kx : kxMax) + (wMax - sprite->getInfo()->width) / 2);
			sprite->setPositionX(kxMax);
		}

		for (auto& it = _sprites.begin(); it != _sprites.end(); ++it)
		{
			for (const auto& sprite : *it)
			{
				if (!sprite->isValid())
				{
					continue;
				}
				// sprite->setPositionY(_y + (_ignoreKxy ? sprite->getInfo()->ky :  _kMax));
				sprite->setPositionY(_y + _kMax);
			}
		}
		_sprites.clear();
		_sprites.push_back(sprites);
		_y += _hMax + c10;
		_hMax = hMax;
		_kMax = kMax;
	}
	else
	{
		for (const auto& sprite : sprites)
		{
			if (!sprite->isValid())
			{
				continue;
			}
			// sprite->setPositionX(_x + (_ignoreKxy ? sprite->getInfo()->kx : kxMax) + (wMax - sprite->getInfo()->width) / 2);
			sprite->setPositionX(_x + kxMax);
		}
		_x += wMax + c10;
		if (_wMax < _x)
		{
			_wMax = _x;
		}
		if (_hMax < hMax)
		{
			_hMax = hMax;
		}
		if (_kMax < kMax)
		{
			_kMax = kMax;
		}
		_sprites.push_back(sprites);
	}

	if (end)
	{
		iters();
	}
}

void expRank::iters()
{
	for (auto& it = _sprites.begin(); it != _sprites.end(); ++it)
	{
		for (const auto& sprite : *it)
		{
			if (!sprite->isValid())
			{
				continue;
			}
			// sprite->setPositionY(_y + (_ignoreKxy ? sprite->getInfo()->ky : _kMax));
			sprite->setPositionY(_y + _kMax);
		}
	}
	_y += _hMax + c10;
}

void expRank::iter(cNode* node, bool end /* = false */)
{
	int wMax = std::max(std::max(_labelw, _wInv), (int)node->getContentSize().width);
	int hMax = node->getContentSize().height;

	if (_x + wMax > _w)
	{
		_x = wMax + c10;
		node->setPosition(0, _y += (_hMax + c10));
		_hMax = hMax;
	}
	else
	{
		node->setPosition(_x, _y);
		_x += wMax + c10;
		if (_wMax < _x)
		{
			_wMax = _x;
		}
		if (_hMax < hMax)
		{
			_hMax = hMax;
		}
	}

	if (end)
	{
		iter();
	}
}





void expRank::iter()
{
	_y += _hMax + c10;
}


#if 0
cNode* uiEasy::initEasy(const txtEasy::sTable& table, int wMin /* = 0 */)
{
	_w = cc::vsSize().width;
	int length = wMin;
	wMin = cLabel::create("88888888")->getContentSize().width;
	if (length > wMin)
	{
		wMin = length;
	}
	length = table.size();
	int x = 0, y = 0, wMax = 0, hMax = 0, kMax = 0;
	cSprite* sprite;
	std::vector<cSprite*> sprites, sprite2s;
	const sSpInfo* info;
	cLabel* label;
	cNode* nodeDrag = cNode::create();
	ulong tag;
	for (int k = 0; k < length; ++k)
	{
		tag = table.at(k);
		nodeDrag->addChild(sprite = cSprite::create(tag));
		sprite->setName(toString("%08X", tag));
		sprite2s.push_back(sprite);
		info = sprite->getInfo();
		if (info == nullptr)
		{
			continue;
		}
		if (x + std::max(info->width, wMin) > _w)
		{
			x = info->width + c10;
			sprite->setPositionX(info->kx);
			if (info->width < wMin)
			{
				x = wMin;
				sprite->setPositionX(sprite->getPositionX() + (wMin - info->width) / 2);
			}
			for (auto& it = sprites.begin(); it != sprites.end(); ++it)
			{
				(*it)->setPositionY(y + kMax);
			}
			sprites.clear();
			sprites.push_back(sprite);
			y += hMax + c10;
			hMax = info->height;
			kMax = info->ky;
		}
		else
		{
			sprite->setPositionX(x + info->kx);
			x += info->width + c10;
			if (info->width < wMin)
			{
				x += wMin - info->width;
				sprite->setPositionX(sprite->getPositionX() + (wMin - info->width) / 2);
			}
			if (wMax < x)
			{
				wMax = x;
			}
			if (hMax < info->height)
			{
				hMax = info->height;
			}
			if (kMax < info->ky)
			{
				kMax = info->ky;
			}
			sprites.push_back(sprite);
		}
		if (sprite->getInfo()->framesCount > 1)
		{
			sprite->play();
		}
		if (k == length - 1)
		{
			for (auto& it = sprites.begin(); it != sprites.end(); ++it)
			{
				(*it)->setPositionY(y + kMax);
			}
			y += hMax + c10;
		}
	}
	if (0)
	{
		for (auto& it = sprite2s.begin(); it != sprite2s.end(); ++it)
		{
			sprite = *it;
			label = cLabel::create(sprite->getName(), eFont::Small);
			nodeDrag->addChild(label);
			label->setPosition(sprite->getPositionX() - label->getContentSize().width / 2, sprite->getPositionY());
			label->setColor(s565::GREEN);
		}
	}
	nodeDrag->setContentSize(/*wMax*/_w, y);
	nodeDrag->setPositionX(c10);
	return nodeDrag;
}
#endif