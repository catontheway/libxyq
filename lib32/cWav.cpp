#include "cWav.h"

#include <list>
#include <mmreg.h>
#include <msacm.h>
#include <malloc.h>
#pragma comment(lib,"dsound.lib")


// struct sWaveHeader
// {
// 	char  RiffSig[4];         // 'RIFF'
// 	long  WaveformChunkSize;  // 8
// 	char  WaveSig[4];         // 'WAVE'
// 	char  FormatSig[4];       // 'fmt ' (notice space after)
// 	long  FormatChunkSize;    // 16
// 	short FormatTag;          // WAVE_FORMAT_PCM
// 	short Channels;           // # of channels
// 	long  SampleRate;         // sampling rate
// 	long  BytesPerSec;        // bytes per second
// 	short BlockAlign;         // sample block alignment
// 	short BitsPerSample;      // bits per second
// 	char  DataSig[4];         // 'data'
// 	long  DataSize;           // size of waveform data
// };

cWav* cWav::getInstance()
{
	static cWav* s_wav = new cWav();
	return s_wav;
}


void cWav::setHwnd(HWND hwnd)
{
	_hwnd = hwnd;
}

struct
{
	unsigned long id;
	unsigned long size;
} chunk;

void cWav::load(char* pdata, int size, int pos, bool bPlay)
{
	free();

	//////////////////////////////////////////////////////////////////////////
	static std::list<char*> s_ptrs;
	s_ptrs.push_back(pdata);
	if (s_ptrs.size() >= 0x44)
	{
		delete[] s_ptrs.front();
		s_ptrs.pop_front();
	}
	//////////////////////////////////////////////////////////////////////////
	static LPDIRECTSOUND8 g_pDirectSound = nullptr;
	if (g_pDirectSound == nullptr)
	{
		DirectSoundCreate8(NULL, &g_pDirectSound, NULL);
		g_pDirectSound->SetCooperativeLevel(_hwnd, DSSCL_NORMAL);
	}
	//////////////////////////////////////////////////////////////////////////


	memcpy(&chunk, pdata, sizeof(chunk));
	pdata += sizeof(chunk);
	if (chunk.id != 'FFIR')// WFourCC("RIFF"))
	{
		return;
	}
	memcpy(&chunk.id, pdata, sizeof(chunk.id));
	pdata += sizeof(chunk.id);
	if (chunk.id != 'EVAW'/*WFourCC("WAVE")*/)
	{
		return;
	}
	memcpy(&chunk, pdata, sizeof(chunk));
	pdata += sizeof(chunk);
	if (chunk.id != ' tmf'/*WFourCC("fmt ")*/)
	{
		return;
	}

	int SrcHeaderSize = chunk.size;
	if (SrcHeaderSize < sizeof(WAVEFORMATEX))SrcHeaderSize = sizeof(WAVEFORMATEX);
	WAVEFORMATEX *SrcHeader = (WAVEFORMATEX *)_alloca(SrcHeaderSize);
	ZeroMemory(SrcHeader, SrcHeaderSize);
	memcpy(SrcHeader, pdata, chunk.size);
	pdata += chunk.size;

	for (;;)
	{
		memcpy(&chunk, pdata, sizeof(chunk));
		pdata += sizeof(chunk);
		if (chunk.id == 'atad'/*WFourCC("data")*/) break;
		pdata += chunk.size;
	}
	if (SrcHeader->wFormatTag != WAVE_FORMAT_PCM)
	{
		// 准备变换后的handle
		WAVEFORMATEX *DstHeader = (WAVEFORMATEX *)_alloca(SrcHeaderSize);
		memcpy(DstHeader, SrcHeader, SrcHeaderSize);

		DstHeader->wFormatTag = WAVE_FORMAT_PCM;

		MMRESULT Result;
		Result = acmFormatSuggest(NULL, SrcHeader, DstHeader, SrcHeaderSize, ACM_FORMATSUGGESTF_WFORMATTAG);
		if (Result != 0)
		{
			return;
			//	ERRBOX;
		}

		// 准备ACM STREAM
		HACMSTREAM acm;
		Result = acmStreamOpen(&acm, NULL, SrcHeader, DstHeader, NULL, NULL, 0, 0);
		if (Result != 0)
		{
			return;
			//	ERRBOX;
		}

		// 对应输出Bytes获得输入Bytes
		unsigned long DefaultWriteSize;
		unsigned long DefaultReadSize = chunk.size;
		Result = acmStreamSize(acm, DefaultReadSize, &DefaultWriteSize, ACM_STREAMSIZEF_SOURCE);
		if (Result != 0)
		{
			acmStreamClose(acm, 0);
			return;
			//	ERRBOX;
		}
		DSBUFFERDESC dsbd;
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_STATIC;
		dsbd.dwBufferBytes = DefaultWriteSize;
		dsbd.dwReserved = 0;
		dsbd.lpwfxFormat = DstHeader;
		g_pDirectSound->CreateSoundBuffer(&dsbd, &m_pPrimaryBuffer, NULL);
		char *soundbuf;
		m_pPrimaryBuffer->Lock(0, 0, (void**)&soundbuf, &DefaultWriteSize, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		// 准备变换buffer
		ACMSTREAMHEADER stream;
		ZeroMemory(&stream, sizeof(stream));
		stream.cbStruct = sizeof(stream);
		stream.pbSrc = new unsigned char[DefaultReadSize];
		stream.cbSrcLength = DefaultReadSize;
		stream.pbDst = (unsigned char*)soundbuf;
		stream.cbDstLength = DefaultWriteSize;
		Result = acmStreamPrepareHeader(acm, &stream, 0);
		if (Result != 0)
		{
			return;
			//	ERRBOX;
		}
		memcpy(stream.pbSrc, pdata, DefaultReadSize);
		pdata += DefaultReadSize;
		stream.cbSrcLength = DefaultReadSize;
		// 变换
		Result = acmStreamConvert(acm, &stream, 0);
		if (Result != 0)
		{
			return;
			//	ERRBOX;
		}
		m_pPrimaryBuffer->Unlock(soundbuf, DefaultWriteSize, NULL, 0);
		delete[] stream.pbSrc;
		acmStreamUnprepareHeader(acm, &stream, 0);
		Result = acmStreamClose(acm, 0);
		m_size = DefaultWriteSize;
	}
	else
	{
		DSBUFFERDESC dsbd;
		unsigned long size = chunk.size;

		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_STATIC;// WSSB_CAPS
		dsbd.dwBufferBytes = size;
		dsbd.dwReserved = 0;
		dsbd.lpwfxFormat = SrcHeader;

		g_pDirectSound->CreateSoundBuffer(&dsbd, &m_pPrimaryBuffer, NULL);
		char *soundbuf;
		m_pPrimaryBuffer->Lock(0, 0, (void**)&soundbuf, &size, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		memcpy(soundbuf, pdata, size);
		pdata += size;
		m_pPrimaryBuffer->Unlock(soundbuf, size, NULL, 0);

	}
	bLoad = true;
	setPosition(pos);
	//	if (0 == g_GlobalValues[17])
	{
		if (bPlay)
		{
			m_pPrimaryBuffer->Play(0, 0, 0);
		}
	}
}

void cWav::free()
{
	if (!m_pPrimaryBuffer)
	{
		return;
	}
	m_pPrimaryBuffer->Release();
	m_pPrimaryBuffer = nullptr;
	bLoad = false;
}

void cWav::setPosition(int num)
{
	if (num == 0)
	{
		m_pPrimaryBuffer->SetCurrentPosition(0);
	}
	else
	{
		m_pPrimaryBuffer->SetCurrentPosition((m_size * num) / 100);
	}

}

int cWav::getNowPostion()
{
	return m_pPrimaryBuffer->GetCurrentPosition(0, 0);
}
