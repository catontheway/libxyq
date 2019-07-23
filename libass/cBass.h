#pragma once
#include "bass.h"
#include <list>
#include "../libcc/_cpp.h"

class cBass
{
public:
	cBass();
	~cBass();
	static cBass* getInstance();
	void preload(ulong uid, const char* ptr, int size);
	void play(ulong uid, const char* ptr, int size);
	void play(const char* ptr, int size);
	// 0~100
	void setWav(uchar v);
	uchar getWav();
	// 0~100
	void setMp3(uchar v);
	uchar getMp3();
private:
	void playHandle(ulong handle, bool loop);
	std::map<ulong, ulong> _preloads;
	ulong _uid = 0/*cSp::INVALID_UID*/;
	struct sMp3 { ulong handle = 0; const char* ptr = nullptr; } _mp3;
	struct sWav { ulong hsample = 0; const char* ptr = nullptr; };
	std::list<sWav> _wavs;
	uchar _vWav = 100, _vMp3 = 100;
};