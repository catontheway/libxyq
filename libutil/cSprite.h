#pragma once
#include "cNode.h"
#include "cWdfs.h"

class cSpriteCache
{
public:
	cSpriteCache();
	~cSpriteCache();
protected:
	bool init(const sSps& sps);
	virtual void setRedraw(bool redraw) {}
public:
	void setReader(const cReader* reader);

	bool load(const sSps& sps);
	bool load(const char* ptr);

	bool isValid() const;

	const sSpInfo* getInfo() const;

	void setAutoAp(bool autoAp) { _isAutoAp = autoAp; }

protected:
	void freeCache();
public:
	void setFrame(int framePerDirection, bool update = true);

	void setDirection(int direction, bool update = true);
	void setDirection(bool isClockwise);
	int getDirection() const { return _direction; }
protected:
	void updateFrame(int iframe);
	void updateFrame(int direction, int framePerDirection);
public:
	bool step();

	void setBlend(eBlend e);

	// Ãæ°åÌØÐÔ
	void setCover(bool cover) { _isCover = cover; }

	const cAlphaBmp* getBitmap(int index, uchar opacity);

protected:
	struct sCache
	{
		ulong uid = cSp::c0;
		int matrixid = 0;
		sSpDecoder* decoder = nullptr;
		bool isValid() const;
	};
	cReader* _reader = nullptr;
	std::vector<sCache> _caches;
	sSpInfo* _info = nullptr;
	bool _isAutoAp = true;
	bool _isWas = false;

	int _frame = 0, _direction = 0, _iframe = 0;

	eBlend _blend = eBlend::normal;
	bool _isCover = false;

	Node* _spriteTarget = nullptr;
};


class cStepper
{
public:
	static cStepper* getInstance();
	static cStepper* getWalk();
	float step(float delta);
	bool isStepd() { return _isStepd; }
	void setSpeed(float speed) { _speed = speed; }
protected:
	float _delta = 0;
	float _speed = 1;
	bool _isStepd = false;
};


class cSprite : public cNode, public cSpriteCache, public cStepper
{
public:
	cSprite();
	~cSprite();
protected:
	bool init(const sSps& sps);
	bool init(ulong uid, void*);
public:
	static cSprite* create(const sSps& sps) { CREATE(cSprite, sps); }
	static cSprite* create(const sSp& sp);
	static cSprite* create(ulong uid, const sMatrixs& matrixs);
	static cSprite* create(ulong uid = cSp::c0);
	static cSprite* create(const char* ptr);

	bool load(const sSps& sps);
	bool load(const sSp& sp);
	bool load(ulong uid, const sMatrixs& matrixs);
	bool load(ulong uid = cSp::c0);
	bool load(const char* ptr);

	void setRedraw(bool redraw) { cRender::setRedraw(redraw); }

	void setClip(int clipx, int clipy);
	static const int cEdge = 0x10;
	void set9(bool is9, int edgew = cEdge, int edgeh = cEdge);
protected:
	void setRenderSize();
public:
	virtual void setContentSize(const Size& contentSize);
	virtual void setContentSize(float w, float h) { setContentSize(Size(w, h)); }

	void setSnatchPixel(bool isSnatchPixel) { _isSnatchPixel = isSnatchPixel; }
	virtual bool isSnatched(const Vec2& v);

	static const int cRepeatMax = INT_MAX;
	void play(int repeat = cRepeatMax, bool removeSelf = false);
protected:
	void draw(cCanvas* canvas, const uint32_t& flags);
	void update(float delta);

// 	cReader* _reader = nullptr;
// 	ulong _uid = cSp::INVALID_UID;
// 	sSpDecoder* _decoder = nullptr;
// 	const s565* _palette = nullptr;
// 	sSpMatrixs _matrixs;
// 	bool _isAutoAp = true;
// 
// 	int _frame = 0, _direction = 0, _iframe = 0;
// //	sSpCache _cache;
// 
// 	eBlend _blend = eBlend::normal;
// 	bool _isCover = false;

	bool _isSnatchPixel = false;
	bool _isClip = false;
	bool _isRenderClip9 = false;
	Vec2 _originClip;
	Size _sizeClip;
	
	bool _is9 = false;
	int _edgew = cEdge;
	int _edgeh = cEdge;

	int _repeat = 0;
	int _repeatMax = cRepeatMax;
	bool _isRemoveSelf = false;
};