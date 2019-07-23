#include "cBass.h"
#if defined(_MSC_VER)
#pragma comment(lib,"bass")
#endif

cBass::cBass()
{
	BASS_Init(-1, 44100, 0, nullptr, nullptr);
}

cBass::~cBass()
{
	BASS_Free();
}

cBass* cBass::getInstance()
{
	static cBass* s_bass = new cBass();
	return s_bass;
}

void cBass::preload(ulong uid, const char* ptr, int size)
{
	if (_preloads.find(uid) != _preloads.end())
	{
		return;
	}
	auto handle = BASS_StreamCreateFile(TRUE, ptr, 0, size, BASS_MUSIC_LOOP);
	if (handle)
	{
		_preloads.insert(std::make_pair(uid, handle));
	}
}

void cBass::play(ulong uid, const char* ptr, int size)
{
	if (uid == _uid)
	{
		return;
	}
	if (_mp3.handle)
	{
	//  BASS_ChannelStop(_handle);
		BASS_StreamFree(_mp3.handle);
		_mp3.handle = 0;
		if (_mp3.ptr != nullptr)
		{
			delete[] _mp3.ptr;
			_mp3.ptr = nullptr;
		}
	}
	_uid = uid;
	_mp3.handle = BASS_StreamCreateFile(TRUE, ptr, 0, size, /*BASS_STREAM_AUTOFREE | */BASS_MUSIC_LOOP);
	if (_mp3.handle)
	{
		BASS_ChannelPlay(_mp3.handle, TRUE);
		_mp3.ptr = ptr;
	}
	else
	{
		delete[] ptr;
	}
}



void cBass::play(const char* ptr, int size)
{
	auto hsample = BASS_SampleLoad(TRUE, ptr, 0, size, 0xFFFF, BASS_SAMPLE_MONO);
	if (!hsample)
	{
		delete[] ptr;
		return;
	}
	auto handle = BASS_SampleGetChannel(hsample, FALSE);
//	auto handle = BASS_StreamCreateFile(TRUE, ptr, 0, size, BASS_STREAM_AUTOFREE);
	if (!handle)
	{
		delete[] ptr;
		return;
	}
//	playHandle(handle, false);
	BASS_ChannelPlay(handle, TRUE);

	sWav wav;
	wav.hsample = hsample;
	wav.ptr = ptr;
	_wavs.push_back(wav);
	if (_wavs.size() > 0x20)
	{
		BASS_SampleFree(_wavs.front().hsample);
		delete[] _wavs.front().ptr;
		_wavs.pop_front();
	}
}

void cBass::setWav(uchar v)
{
	BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, v * 100);
}


uchar cBass::getWav()
{
	return BASS_GetConfig(BASS_CONFIG_GVOL_SAMPLE) / 100;
}

void cBass::setMp3(uchar v)
{
	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, v * 100);
}


uchar cBass::getMp3()
{
	return BASS_GetConfig(BASS_CONFIG_GVOL_STREAM) / 100;
}

void cBass::playHandle(ulong handle, bool loop)
{
	BASS_CHANNELINFO info;
	BASS_ChannelGetInfo(handle, &info);
	if (loop)
	{
		info.flags |= BASS_MUSIC_LOOP;
	}
	else
	{
		info.flags &= ~BASS_MUSIC_LOOP;
	}
	BASS_ChannelFlags(handle, info.flags, 0);
//	BASS_ChannelSetAttribute(handle, BASS_ATTRIB_VOL, BASS_GetConfig(BASS_CONFIG_GVOL_SAMPLE) / 100.0f);
	BASS_ChannelPlay(handle, TRUE);
}
