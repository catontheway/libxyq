#include "cSprite.h"

bool cSpriteCache::sCache::isValid() const
{
	return uid != cSp::c0 && decoder != nullptr && decoder->isValid();
}
//////////////////////////////////////////////////////////////////////////
cSpriteCache::cSpriteCache()
{
}

cSpriteCache::~cSpriteCache()
{
	freeCache();
}



bool cSpriteCache::init(const sSps& sps)
{
	setReader(cWdfs::getInstance()->getCurrReader());
	return load(sps);
}



void cSpriteCache::setReader(const cReader* reader)
{
	if (_reader == reader)
	{
		return;
	}
	freeCache();
	_reader = (cReader*)reader;
}


bool cSpriteCache::load(const sSps& sps)
{
	if (_isWas)
	{
		freeCache();
		return false;
	}
	if (_caches.size() == 1 && sps.size() == 1)
	{
		auto& c = _caches.at(0);
		const auto& sp = sps.at(0);
		if (c.uid == sp.uid)
		{
			if (!sp.matrixs.empty() && c.isValid())
			{
				c.decoder->removeMatrix(c.matrixid);
				c.matrixid = c.decoder->getMatrix(&sp.matrixs);
				updateFrame(_direction, _frame);
			}
			return true;
		}
	}
	freeCache();
	if (sps.size() <= 1 && sps.at(0).uid == cSp::c0)
	{
		return true;
	}
	_caches.resize(sps.size());
	forv(_caches, k)
	{
		auto& c = _caches.at(k);
		const auto& sp = sps.at(k);
		c.uid = sp.uid;
		c.decoder = (sSpDecoder*)_reader->getDecoder(sp.uid);
		if (c.isValid() && !sp.matrixs.empty())
		{
			c.matrixid = c.decoder->getMatrix(&sp.matrixs);
		}
		else
		{
			c.matrixid = 0;
		}
		if (_info == nullptr && c.isValid())
		{
			_info = &c.decoder->info;
		}
	}
	updateFrame(0);
	return true;
}


bool cSpriteCache::load(const char* ptr)
{
	freeCache();
	_reader = (cReader*)1;
	_isWas = true;
	_caches.resize(1);
	auto& c = _caches.at(0);
	c.uid = (ulong)ptr;
	c.decoder = new sSpDecoder();
	c.decoder->load(ptr);
	if (c.isValid())
	{
		_info = &c.decoder->info;
	}
	updateFrame(0);
	return true;
}

bool cSpriteCache::isValid() const
{
	return _reader != nullptr && _info != nullptr;
}


const sSpInfo* cSpriteCache::getInfo() const
{
	return _info;
}

void cSpriteCache::freeCache()
{
	if (_isWas)
	{
		for (auto& c : _caches)
		{
			if (c.isValid())
			{
				delete c.decoder;
				delete[] ((char*)c.uid);
			}
		}
	}
	else
	{
		for (auto& c : _caches)
		{
			if (c.isValid())
			{
				c.decoder->removeMatrix(c.matrixid);
				_reader->freeDecoder(c.uid);
			}
		}
	}
	_caches.clear();
	_info = nullptr;
	_iframe = 0;
}


void cSpriteCache::setFrame(int framePerDirection, bool update /* = true */)
{
	if (getInfo() == nullptr)
	{
		return;
	}
	if (framePerDirection >= getInfo()->framesCountPerDirection)
	{
		framePerDirection = getInfo()->framesCountPerDirection - 1;
	}
	if (update)
	{
		updateFrame(_direction, framePerDirection);
	}
}


void cSpriteCache::setDirection(int direction, bool update /* = true */)
{
	if (getInfo() == nullptr)
	{
		return;
	}
	if (direction >= getInfo()->directionsCount)
	{
		direction = getInfo()->directionsCount - 1;
	}
	if (update)
	{
		updateFrame(direction, _frame);
	}
}


void cSpriteCache::setDirection(bool isClockwise)
{
	if (getInfo() == nullptr)
	{
		return;
	}
	int dc = getInfo()->directionsCount;
	int d;
	if (dc == 8)
	{
		d = cDirection::getDirectionRound8(_direction, isClockwise);
	}
	else if (dc == 4)
	{
		d = cDirection::getDirectionRound4(_direction, isClockwise);
	}
	else if (isClockwise)
	{
		if (_direction >= dc - 1)
		{
			d = 0;
		}
		else
		{
			d = _direction + 1;
		}
	}
	else
	{
		if (_direction <= 0)
		{
			d = dc - 1;
		}
		else
		{
			d = _direction - 1;
		}
	}
	updateFrame(d, _frame);
}


void cSpriteCache::updateFrame(int direction, int framePerDirection)
{
	if (direction == _direction && framePerDirection == _frame)
	{
		return;
	}
	_direction = direction;
	_frame = framePerDirection;
	_iframe = direction * getInfo()->framesCountPerDirection + framePerDirection;
	updateFrame(_iframe);
	setRedraw(true);
}


void cSpriteCache::updateFrame(int iframe)
{
	if (getInfo() == nullptr)
	{
		return;
	}
	const auto& frame = getInfo()->frames + iframe;
	_spriteTarget->setContentSize(frame->w, frame->h);
	if (_isAutoAp)
	{
		_spriteTarget->setAnchorPoint(Vec2(frame->x * 1.0f / frame->w, frame->y * 1.0f / frame->h));
	}
}


bool cSpriteCache::step()
{
	if (getInfo() == nullptr)
	{
		return false;
	}
	int framePerDirection = _frame + 1;
	if (framePerDirection >= getInfo()->framesCountPerDirection)
	{
		return true;
	}
	updateFrame(_direction, framePerDirection);
	return false;
}


void cSpriteCache::setBlend(eBlend e)
{
	if (_blend != e)
	{
		setRedraw(true);
	}
	_blend = e;
}


const cAlphaBmp* cSpriteCache::getBitmap(int index, uchar opacity)
{
	if (index < 0 || index >= _caches.size())
	{
		return nullptr;
	}
	auto& c = _caches.at(index);
	if (!c.isValid())
	{
		return nullptr;
	}
	return c.decoder->getBitmap(c.matrixid, _iframe, _blend, opacity);
}




//////////////////////////////////////////////////////////////////////////
cStepper* cStepper::getInstance()
{
	static cStepper* s_delta = new cStepper();
	return s_delta;
}


cStepper* cStepper::getWalk()
{
	static cStepper* s_deltaWalk = new cStepper();
	return s_deltaWalk;
}

float cStepper::step(float delta)
{
	static float s_delta = 0.12f;
	delta = (_delta += delta * _speed) - s_delta;
	if (_delta >= s_delta)
	{
		_delta -= s_delta;
	}
	_isStepd = delta > 0;
	return delta;
}


cSprite::cSprite()
{
}

cSprite::~cSprite()
{
//	freeCache();
}

bool cSprite::init(const sSps& sps)
{
	_spriteTarget = this;
	return cNode::init() && cSpriteCache::init(sps);
}


bool cSprite::init(ulong uid, void*)
{
	_spriteTarget = this;
	sSps sps(1);
	sps.at(0).uid = uid;
	return cNode::init() && cSpriteCache::init(sps);
}


cSprite* cSprite::create(const sSp& sp)
{
	sSps sps(1);
	sps.at(0) = sp;
	return create(sps);
}

cSprite* cSprite::create(ulong uid, const sMatrixs& matrixs)
{
	sSps sps(1);
	sps.at(0).uid = uid;
	sps.at(0).matrixs = matrixs;
	return create( sps );
}

cSprite* cSprite::create(ulong uid /*= cSp::c0*/)
{
	sSps sps(1);
	sps.at(0).uid = uid;
	return create( sps );
}

cSprite* cSprite::create(const char* ptr)
{
	CREATE_INIT(cSprite, load, ptr);
}

bool cSprite::load(const sSp& sp)
{
	sSps sps(1);
	sps.at(0) = sp;
	return load( sps );
}


bool cSprite::load(ulong uid, const sMatrixs& matrixs)
{
	sSps sps(1);
	sps.at(0).uid = uid;
	sps.at(0).matrixs = matrixs;
	return load( sps );
}


bool cSprite::load(ulong uid /* = cSp::c0 */)
{
	sSps sps(1);
	sps.at(0).uid = uid;
	return load( sps );
}


bool cSprite::load(const sSps& sps)
{
	return cSpriteCache::load(sps);
}

bool cSprite::load(const char* ptr)
{
	_spriteTarget = this;
	return cSpriteCache::load(ptr);
}

void cSprite::setRenderSize()
{
	const auto& frame = getInfo()->frames + _iframe;
	if (_isClip)
	{
		_sizeClip.width = std::min(_contentSize.width, frame->w - _originClip.x);
		_sizeClip.height = std::min(_contentSize.height, frame->h - _originClip.y);
		_isRenderClip9 = !Size(frame->w, frame->h).equals(_sizeClip);
	}
	else
	{
		_isRenderClip9 = !Size(frame->w, frame->h).equals(_contentSize);
	}
}


void cSprite::setContentSize(const Size& contentSize)
{
	cNode::setContentSize(contentSize);
	if ((_isClip || _is9) && isValid())
	{
		setRenderSize();
	}
}


bool cSprite::isSnatched(const Vec2& v)
{
	if (getInfo() == nullptr)
	{
		return cNode::isSnatched(v);
	}
	bool isori = !_isSnatchPixel || _is9 || _isClip;
	if (isori && _caches.size() <= 1)
	{
		return cNode::isSnatched(v);
	}

	static Vec2 v2;
	// v2 = v; // -_anchorPointInPoints;
	const auto& f = getInfo()->frames + _iframe;
	for (const auto& c : _caches)
	{
		if (!c.isValid())
		{
			continue;
		}
		const auto& f2 = c.decoder->info.frames + _iframe;
		v2.x = v.x - (f->x - f2->x);
		v2.y = v.y - (f->y - f2->y);
		if (v2.x < 0 || v2.x >= f2->w || v2.y < 0 || v2.y >= f2->h)
		{
			continue;
		}
		if (isori)
		{
			return true;
		}
		c.decoder->decode(_iframe);
		auto decodes = c.decoder->decodes + _iframe;
		if (*(decodes->alphas + (int)v2.y * decodes->w + (int)v2.x) > 0)
		{
			return true;
		}
	}
	return cNode::isSnatched(v);
}


const int cSprite::cRepeatMax;

void cSprite::setClip(int clipx, int clipy)
{
	_isClip = true;
	_isAutoAp = false;
	_is9 = false;
	_originClip.x = clipx;
	_originClip.y = clipy;
	if (isValid())
	{
		setRenderSize();
	}
}

const int cSprite::cEdge;

void cSprite::set9(bool is9, int edgew /* = cEdge */, int edgeh /* = cEdge */)
{
	if (_is9 = is9)
	{
		_edgew = edgew;
		_edgeh = edgeh;
		_isAutoAp = false;
		_isClip = false;
		if (isValid())
		{
			setRenderSize();
		}
	}
}


void cSprite::draw(cCanvas* canvas, const uint32_t& flags)
{
//	_canvas->setChange(flags || _isDraw, false);
// 	if (flags || _isDraw)
// 	{
// 		canvas->Change();
// 	}
// 	else
// 	{
// 		canvas->UnChange();
// 	}
	if (!isValid())
	{
		return;
	}
	if (_caches.size() == 1)
	{
		auto bmp = getBitmap(0, _realOpacity);
		if (bmp == nullptr)
		{
			return;
		}
		if (_isClip && _isRenderClip9)
		{
			canvas->SetPos(_wx, _wy);
			cWindSoul::drawSub(
				canvas, bmp,
				_originClip.x,
				_originClip.y,
				_sizeClip.width,
				_sizeClip.height,
				_realOpacity);
		}
		else if (_is9 && _isRenderClip9)
		{
			const auto& frame = getInfo()->frames + _iframe;
			canvas->SetPos(_wx, _wy);
			cWindSoul::drawSub(canvas, bmp, 0, 0, _contentSize.width - _edgew, _contentSize.height - _edgeh, _realOpacity);
			canvas->SetPos(_wx + _contentSize.width - _edgew, _wy);
			cWindSoul::drawSub(canvas, bmp, frame->w - _edgew, 0, _edgew, _contentSize.height - _edgeh, _realOpacity);
			canvas->SetPos(_wx, _wy + _contentSize.height - _edgeh);
			cWindSoul::drawSub(canvas, bmp, 0, frame->h - _edgeh, _contentSize.width - _edgew, _edgeh, _realOpacity);
			canvas->SetPos(_wx + _contentSize.width - _edgew, _wy + _contentSize.height - _edgeh);
			cWindSoul::drawSub(canvas, bmp, frame->w - _edgew, frame->h - _edgeh, _edgew, _edgeh, _realOpacity);
		}
		else
		{
			canvas->SetPos(_wx, _wy);
			canvas->Draw(*bmp, BLIT_NORMAL);
		}

		if (_isCover && flags)
		{
			static const int c20 = 20;
			int w, h;
			w = _contentSize.width;
			h = _contentSize.height;
			if (w > c20 * 2 && h > c20 * 2)
			{
				canvas->SetPos(_wx + c20, _wy);
				canvas->SetOvlRect(w - c20 * 2, c20);
				canvas->SetPos(_wx, _wy + c20);
				canvas->SetOvlRect(w, h - c20 * 2);
				canvas->SetPos(_wx + c20, _wy + h - c20);
				canvas->SetOvlRect(w - c20 * 2, c20);
			}
		}
		return;
	}
	const auto& f = getInfo()->frames + _iframe;
	forr (_caches, k)
	{
		auto& c = _caches.at(k);
		if (!c.isValid())
		{
			continue;
		}
		if (_iframe >= c.decoder->info.framesCount)
		{
			continue;
		}
		auto bmp = c.decoder->getBitmap(c.matrixid, _iframe, _blend, _realOpacity);
		if (bmp == nullptr)
		{
			continue;
		}
		const auto& f2 = c.decoder->info.frames + _iframe;
		canvas->SetPos(_wx + (f->x - f2->x), _wy + (f->y - f2->y));
		canvas->Draw(*bmp, BLIT_NORMAL);
	}
}

void cSprite::play(int repeat /*= cRepeatMax*/, bool removeSelf /*= false*/)
{
	_repeat = 1;
	_repeatMax = repeat;
	_isRemoveSelf = removeSelf;
	scheduleUpdate();
}


void cSprite::update(float delta)
{
	if (cStepper::step(delta) < 0)
	{
		return;
	}
	if (!cSpriteCache::step())
	{
		return;
	}
	if (_repeat >= _repeatMax)
	{
		unscheduleUpdate();
		if (_isRemoveSelf)
		{
			this->removeFromParent();
		}
	}
	else
	{
		updateFrame(_direction, 0);
		++_repeat;
	}
}
