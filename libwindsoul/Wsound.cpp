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

		Description:		风魂声音
 		Original Author:	云风
		Authors:
		Create Time:		2001/8/7
		Modify Time:		2002/3/11

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>
#include <dsound.h>
#include <string.h>
#include <malloc.h>
#include "windsoul.h"
#include "wsound.h"
// #include "wsfile.h"
// #include "wscache.h"
#include "sndint.h"

static DSBUFFERDESC dsbd;
static WAVEFORMATEX wf;

WSound::WSound(HWND h_wnd,int cachesize)
{
	m_pDevice=new WSoundDevice(cachesize);
	m_CurrentMix=0;

	//  Create DirectSound
	if(FAILED(DirectSoundCreate(NULL,&(m_pDevice->lpDS),NULL))) {
		// DirectSound 创建失败
		m_pDevice->lpDS=NULL;
		return;
	}
	if(FAILED(m_pDevice->lpDS->SetCooperativeLevel(h_wnd,DSSCL_PRIORITY))){
		m_pDevice->lpDS->Release();
		m_pDevice->lpDS=NULL;
		return;
	}
	//  Primary Buffer Desc
	dsbd.dwSize=sizeof(DSBUFFERDESC);
	dsbd.dwFlags=DSBCAPS_PRIMARYBUFFER|DSBCAPS_CTRLVOLUME;
	dsbd.dwBufferBytes=0;
	dsbd.dwReserved=0;
	dsbd.lpwfxFormat=NULL;

	if (FAILED(m_pDevice->lpDS->CreateSoundBuffer(&dsbd,&(m_pDevice->lpDSP),NULL))) {
		m_pDevice->lpDS->Release();
		m_pDevice->lpDS=NULL;
		return;
	}

	wf.cbSize=0;
	wf.wFormatTag=WAVE_FORMAT_PCM;
	wf.nChannels=c_Channels;
	wf.nSamplesPerSec=c_SPS;
	wf.wBitsPerSample=c_BPS;
	wf.nBlockAlign=c_BPS/8*c_Channels;
	wf.nAvgBytesPerSec=c_SPS*wf.nBlockAlign;

	m_pDevice->lpDSP->SetFormat(&wf);
//	TestAc();
}
/*
#include "wstimer.h"
#include "wsstring.h"

void WSound::TestAc()
{
	if (!IsAvailable()) return;
	WTimer timer;
	LPDIRECTSOUNDBUFFER buffer;

	dsbd.dwSize=sizeof(DSBUFFERDESC);
	dsbd.dwFlags=WSSB_CAPS|DSBCAPS_LOCSOFTWARE;
	dsbd.dwBufferBytes=c_SPS*wf.nBlockAlign;
	dsbd.dwReserved=0;
	dsbd.lpwfxFormat=&wf;

	wf.cbSize=0;
	wf.wFormatTag=WAVE_FORMAT_PCM;
	wf.nChannels=c_Channels;
	wf.nSamplesPerSec=c_SPS;
	wf.wBitsPerSample=c_BPS;
	wf.nBlockAlign=c_BPS/8*c_Channels;
	wf.nAvgBytesPerSec=c_SPS*wf.nBlockAlign;
	
	m_pDevice->lpDS->CreateSoundBuffer(&dsbd,&buffer,NULL);

	HANDLE event[2];
	event[0]=CreateEvent(NULL,FALSE,FALSE,NULL);
	event[1]=CreateEvent(NULL,FALSE,FALSE,NULL);
	LPDIRECTSOUNDNOTIFY dsn;
	DSBPOSITIONNOTIFY dsbpn[2];
	dsbpn[0].hEventNotify=event[0];
	dsbpn[0].dwOffset=c_SPS*wf.nBlockAlign/2;
	dsbpn[1].hEventNotify=event[1];
	dsbpn[1].dwOffset=DSBPN_OFFSETSTOP;
	buffer->QueryInterface(IID_IDirectSoundNotify,(LPVOID *)&dsn);
	dsn->SetNotificationPositions(2,dsbpn);
	DWORD size,time;
	char *temp;
	buffer->Lock(0,0,(void**)&temp,&size,NULL,NULL,DSBLOCK_ENTIREBUFFER);
	memset(temp,0,size);
	buffer->Unlock(temp,size,NULL,0);
	buffer->Play(0,0,0);
	WaitForSingleObject(event[0],INFINITE);
	timer.Start();
	WaitForSingleObject(event[1],INFINITE);
	time=timer.Stop();
	dsn->Release();	
	buffer->Release();
	CloseHandle(event[0]);
	CloseHandle(event[1]);
	int t=timer.Time(time);
	if (t>5150) {
		timer.Set2GHz();
	}
}
*/

WSound::~WSound()
{
	int i;

	for (i=0;i<m_CurrentMix;i++) {
		if (m_pCurrentSample[i]) {
			m_pCurrentSample[i]->Stop();
		}
	}

	IsPlaying(0);	// 清除播放链表

	if (m_pDevice->lpMusic) {
		delete m_pDevice->lpMusic;
	}

	LPDIRECTSOUND lpDS=m_pDevice->lpDS;

	if (lpDS) {
		m_pDevice->lpDSP->Release();
	}

	delete m_pDevice;

	if (lpDS) 
		lpDS->Release();
}

bool WSound::IsAvailable() const
{
	return (m_pDevice->lpDS!=0);
}

void WSound::TurnOn()
{
	if (IsAvailable()) {
		m_pDevice->lpDSP->Play(0,0,DSBPLAY_LOOPING);
	}
}

void WSound::TurnOff()
{
	if (IsAvailable()) {
		m_pDevice->lpDSP->Stop();
	}
}

void WSound::SetVolume(long vol)
{
	if (IsAvailable()) {
		m_pDevice->lpDSP->SetVolume(vol);
	}
}

long WSound::GetVolume() const
{
	if (IsAvailable()) {
		long r;
		m_pDevice->lpDSP->GetVolume(&r);
		return r;
	}
	else return 0;
}

#include <stdio.h>
#include <string.h>
#include <mmreg.h>
#include <msacm.h>
#include "wsfile.h"

void * WSound::ReadWav(const char *filename,int &rSize)
{
	if (!IsAvailable()) return 0;
	LPDIRECTSOUNDBUFFER temp;
	WFile hSrcWaveFile;
	struct {
		DWORD id;
		DWORD size;
	} chunk;

	if (hSrcWaveFile.Open(filename)!=WS_OK)
		return 0;

	hSrcWaveFile.Read(&chunk,sizeof(chunk));
	if (chunk.id!=WFourCC("RIFF")) return 0;
	hSrcWaveFile.Read(&chunk.id,sizeof(chunk.id));
	if (chunk.id!=WFourCC("WAVE")) return 0;
	hSrcWaveFile.Read(&chunk,sizeof(chunk));
	if (chunk.id!=WFourCC("fmt ")) return 0;

	int SrcHeaderSize=chunk.size;
	if(SrcHeaderSize<sizeof(WAVEFORMATEX))
		SrcHeaderSize=sizeof(WAVEFORMATEX);
	WAVEFORMATEX *SrcHeader=(WAVEFORMATEX *)_alloca(SrcHeaderSize);
	ZeroMemory(SrcHeader,SrcHeaderSize);
	hSrcWaveFile.Read(SrcHeader,chunk.size);

	for (;;) {
		hSrcWaveFile.Read(&chunk,sizeof(chunk));
		if (chunk.id==WFourCC("data")) break;
		hSrcWaveFile.Skip(chunk.size);
		if (hSrcWaveFile.IsEnd()) return 0;
	} 

	if (SrcHeader->wFormatTag!=WAVE_FORMAT_PCM) {

		// 准备变换后的handle
		WAVEFORMATEX *DstHeader=(WAVEFORMATEX *)_alloca(SrcHeaderSize);
		memcpy(DstHeader,SrcHeader,SrcHeaderSize);
		DstHeader->wFormatTag=WAVE_FORMAT_PCM;
		MMRESULT Result;
		Result=acmFormatSuggest(NULL,SrcHeader,DstHeader,SrcHeaderSize,ACM_FORMATSUGGESTF_WFORMATTAG);
		if (Result!=0) return 0;

		// 准备ACM STREAM
		HACMSTREAM acm;
		Result=acmStreamOpen(&acm,NULL,SrcHeader,DstHeader,NULL,NULL,0,0);//ACM_STREAMOPENF_NONREALTIME);
		if (Result!=0) return 0;

		// 对应输出Bytes获得输入Bytes
		DWORD DefaultWriteSize;
		DWORD DefaultReadSize=chunk.size;
		Result=acmStreamSize(acm,DefaultReadSize,&DefaultWriteSize,ACM_STREAMSIZEF_SOURCE);
		if (Result!=0) {
			acmStreamClose(acm,0);
			return 0;
		}

		DSBUFFERDESC dsbd;

		dsbd.dwSize=sizeof(DSBUFFERDESC);
		dsbd.dwFlags=WSSB_CAPS|DSBCAPS_LOCSOFTWARE;
		dsbd.dwBufferBytes=DefaultWriteSize;
		dsbd.dwReserved=0;
		dsbd.lpwfxFormat=DstHeader;

		HRESULT hr;
		hr=m_pDevice->lpDS->CreateSoundBuffer(&dsbd,&temp,NULL);
		if (hr==DSERR_CONTROLUNAVAIL) {
			dsbd.dwFlags=WSSB_CAPS2|DSBCAPS_LOCSOFTWARE;
			hr=m_pDevice->lpDS->CreateSoundBuffer(&dsbd,&temp,NULL);
			if (hr==DSERR_CONTROLUNAVAIL) {
				dsbd.dwFlags=DSBCAPS_LOCSOFTWARE;
				hr=m_pDevice->lpDS->CreateSoundBuffer(&dsbd,&temp,NULL);
			}
		}

		rSize=DefaultWriteSize;

		if (!FAILED(hr)) {
			char *soundbuf;
			temp->Lock(0,0,(void**)&soundbuf,&DefaultWriteSize,NULL,NULL,DSBLOCK_ENTIREBUFFER);

			// 准备变换buffer
			ACMSTREAMHEADER stream;
			ZeroMemory(&stream,sizeof(stream));
			stream.cbStruct=sizeof(stream);
			stream.pbSrc=(BYTE*)WAlloc(DefaultReadSize);
			stream.cbSrcLength=DefaultReadSize;
			stream.pbDst=(BYTE*)soundbuf;
			stream.cbDstLength=DefaultWriteSize;
			Result=acmStreamPrepareHeader(acm,&stream,0);
			if (Result!=0) goto __decode_error;

			hSrcWaveFile.Read(stream.pbSrc,DefaultReadSize);

			stream.cbSrcLength=DefaultReadSize;
				// 变换
			Result=acmStreamConvert(acm,&stream,0);
			if (Result!=0) goto __decode_error;

			temp->Unlock(soundbuf,DefaultWriteSize,NULL,0);

			WFree(stream.pbSrc);
			acmStreamUnprepareHeader(acm,&stream,0);

			Result=acmStreamClose(acm,0);
			if (0) {
			// 解码失败
			__decode_error:
				WFree(stream.pbSrc);
				acmStreamUnprepareHeader(acm,&stream,0);
				acmStreamClose(acm,0);
				temp->Unlock(soundbuf,DefaultWriteSize,NULL,0);
				temp->Release();
				return 0;
			}
		}
	}
	else {
		DSBUFFERDESC dsbd;
		DWORD size=chunk.size;

		dsbd.dwSize=sizeof(DSBUFFERDESC);
		dsbd.dwFlags=WSSB_CAPS|DSBCAPS_LOCSOFTWARE;
		dsbd.dwBufferBytes=size;
		dsbd.dwReserved=0;
		dsbd.lpwfxFormat=SrcHeader;

		m_pDevice->lpDS->CreateSoundBuffer(&dsbd,&temp,NULL);

		char *soundbuf;
		temp->Lock(0,0,(void**)&soundbuf,&size,NULL,NULL,DSBLOCK_ENTIREBUFFER);

		hSrcWaveFile.Read(soundbuf,size);

		temp->Unlock(soundbuf,size,NULL,0);

		rSize=size;

	}

	hSrcWaveFile.Close();

	return temp;
}

void WSound::PlaySample(const char *filename,long vol)
{
	if (!IsAvailable()) return;
	WSampleNode *sample=m_pDevice->Cache.Quest(filename);
	if (sample==0) return;
	WSample* temp=new WSample(this);
	temp->m_SS->m_Node=sample;
	if (vol!=0) temp->SetVolume(vol);
	temp->Play(play_once);
}

WSample* WSound::LoadSample(const char *filename)
{
	if (!IsAvailable()) return 0;
	WSampleNode *sample=m_pDevice->Cache.Quest(filename);
	if (sample==0) return 0;
	WSample* temp=new WSample(this);
	temp->m_SS->m_Node=sample;
	return temp;
}

bool WSound::IsPlaying(void *buf)
{
	bool result=false;
	int i,j;
	DWORD status;
	for (i=0;i<m_CurrentMix;i++) {
		WSampleStruct *sample=m_pCurrentSample[i]->m_SS;
		LPDIRECTSOUNDBUFFER buffer;
		bool over=false;
		if (buffer=sample->m_Duplicate) {
			// 复制出来的 sound buffer 
			buffer->GetStatus(&status);
			if (status&DSBSTATUS_BUFFERLOST)
				buffer->Restore();
			if (!(status&DSBSTATUS_PLAYING)) {
				buffer->Release();
				sample->m_Duplicate=0;
				if (sample->m_Mode==play_once) {
					// 一次 wav 播放完了.
					sample->m_Mode=play_over;
					delete m_pCurrentSample[i];
					sample=0;
				}
				over=true;
			}
		}
		else {
			WSampleBuffer *temp=sample->m_Node->Quest(this);
			ASSERT(temp && temp->m_Buffer);
			buffer=temp->m_Buffer;
			buffer->GetStatus(&status);
			if (status&DSBSTATUS_BUFFERLOST)
				buffer->Restore();
			if (!(status&DSBSTATUS_PLAYING)) {
				if (sample->m_Mode==play_once) {
					// 一次 wav 播放完了.
					sample->m_Mode=play_over;
					delete m_pCurrentSample[i];
					sample=0;
				}
				over=true;
			}
			else if (buffer==buf) {
				result=true;
			}
		}
		if (over) {
			if (sample) {
				sample->m_Mode=play_over;
				sample->m_Node->Release();
				sample->m_Node->Unlock();
			}
			--m_CurrentMix;
			for (j=i;j<m_CurrentMix;j++) {
				m_pCurrentSample[j]=m_pCurrentSample[j+1];
			}
			--i;
		}
	}
	return result;
}

void WSound::Play(WSample *s)
{
	if (!IsAvailable()) return;

	// 检查是否已经在播放, 如果是, 重新播放
	int i;
	for (i=0;i<m_CurrentMix;i++) {
		if (m_pCurrentSample[i]==s) {
			WPlayMode mode=s->m_SS->m_Mode;
			LPDIRECTSOUNDBUFFER buffer=s->m_SS->m_Node->Quest(this)->m_Buffer;
			DWORD status;
			buffer->GetStatus(&status);
			if (status&DSBSTATUS_BUFFERLOST)
				buffer->Restore();
			if (!(status&DSBSTATUS_PLAYING)) {
				buffer->Play(0,0,(mode==play_loop)?DSBPLAY_LOOPING:0);
			}
			else {
				buffer->SetCurrentPosition(0);
			}
			return;
		}
	}

	WSampleBuffer *sbuffer=s->m_SS->m_Node->Quest(this);
	if (sbuffer==0) {
		if (s->m_SS->m_Mode==play_once) {
			s->m_SS->m_Mode=play_over;
			delete s;
		}
		return;
	}
	LPDIRECTSOUNDBUFFER buffer=sbuffer->m_Buffer;
	ASSERT(buffer && "cache 请求失败");
	if (IsPlaying(buffer)) {
		if (m_CurrentMix>=MaxMix) {
			// 同时播放已满
			if (s->m_SS->m_Mode==play_once) {
				s->m_SS->m_Mode=play_over;
				delete s;
			}
			return;
		}
		s->DuplicateBuffer();
		buffer=s->m_SS->m_Duplicate;
	}
	else if (m_CurrentMix>=MaxMix) {
		// 同时播放已满
		if (s->m_SS->m_Mode==play_once) {
			s->m_SS->m_Mode=play_over;
//			s->m_SS->m_Node->Release();
			s->m_SS->m_Node->Unlock();
			delete s;
		}
		return;
	}
	m_pCurrentSample[m_CurrentMix++]=s;
	buffer->SetVolume(s->m_SS->m_Vol);
	WPlayMode mode=s->m_SS->m_Mode;
	buffer->Play(0,0,(mode==play_loop)?DSBPLAY_LOOPING:0);
	if (mode!=play_once)
		s->m_SS->m_Node->AddRef();
}

void WSound::DeletePlayingSample(WSample *s)
{
	int i;
	for (i=0;i<m_CurrentMix;i++) {
		if (m_pCurrentSample[i]==s) {
			int j;
			--m_CurrentMix;
			for (j=i;j<m_CurrentMix;j++) {
				m_pCurrentSample[j]=m_pCurrentSample[j+1];
			}
			return;
		}
	}

	ASSERT(0 && "找不到正在播放的音效");
}

 ///   音效
///////////////////////////////

WSample::WSample(WSound *dev) : m_DS(dev) {
	m_SS=new WSampleStruct;
}

WSample::~WSample()
{
	if (IsPlaying()) {
		m_DS->DeletePlayingSample(this);
		m_SS->m_Node->Release();
	}
	delete m_SS;
}


WSampleBuffer::~WSampleBuffer()
{
	if (m_Buffer) {
		m_Buffer->Release();
	}
}

void WSample::SetVolume(long vol)
{
	m_SS->m_Vol=vol;
	if (IsPlaying()) {
		if (m_SS->m_Duplicate) {
			m_SS->m_Duplicate->SetVolume(vol);
		}
		else {
			WSampleBuffer *buffer=m_SS->m_Node->Quest(m_DS);
			ASSERT(buffer->m_Buffer && "Cache 请求失败");
			buffer->m_Buffer->SetVolume(vol);
		}
	}
}

long WSample::GetVolume() const
{
	return m_SS->m_Vol;
}

void WSample::Play(WSound::WPlayMode mode)
{
	m_SS->m_Mode=mode;
	m_DS->Play(this);
}

void WSample::Stop()
{
	if (IsPlaying()) {
		if (m_SS->m_Duplicate) {
			m_SS->m_Duplicate->Stop();
			m_SS->m_Duplicate=0;
		}
		else {
			WSampleBuffer *buffer=m_SS->m_Node->Quest(m_DS);
			ASSERT(buffer->m_Buffer && "Cache 请求失败");
			buffer->m_Buffer->Stop();
		}
	}
}

void WSample::DuplicateBuffer()
{
	ASSERT(m_DS->IsAvailable() && "DirectSound 没有创建");

	WSampleBuffer *buffer=m_SS->m_Node->Quest();
	if (buffer) {
		m_DS->m_pDevice->lpDS->DuplicateSoundBuffer(buffer->m_Buffer,&(m_SS->m_Duplicate));
	}
}

bool WSample::IsPlaying()
{
	return (m_SS->m_Mode!=WSound::play_over);
}


//#define  _SUPPORT_MP3
 ///   音乐
///////////////////////////////

#ifdef _SUPPORT_MP3

#include	<stdio.h>
#include	<stdlib.h>
#include	"mp3lib/tmp3.h"

#pragma comment(lib,"mp3lib/mp3lib.lib")

//-------------------------------------------------------
class	StdDataIO	: public DATAIO
{
protected:
	WFile m_File;

	StdDataIO(int bufsize)
	{
		//流模式
		mode	= IOMODE_STREAM;
		length	= bufsize;
		data	= (unsigned char *)malloc(length);
		size	= 0;

/*		//立即模式
		handle	= fopen((char *)filename, "rb");
		mode	= IOMODE_DIRECT;
		fseek(handle, 0, SEEK_END);
		length	= ftell(handle);
		fseek(handle, 0, SEEK_SET);
		data	= (unsigned char *)malloc(length);
		size	= 0;
*/
	}

public:
	
	int	IOControl(int mode)
	{
		switch (mode)
		{
			case	IO_READ:
				m_File.Read(data,length,&size);
				return size;

			case	IO_REWIND:
			default:
				m_File.Read(0,0,0);	// rewind
				size = 0;
				return 1;
		}
		return 0;
	}

	static StdDataIO *Create(void *filename, int bufsize)
	{
		StdDataIO * ret=new StdDataIO(bufsize);
		WSERR r=ret->m_File.Open((const char *)filename);
		if (r!=WS_OK) {
			if (ret->data)
				free(ret->data);
			delete ret;
			return NULL;
		}

		ret->IOControl(IO_READ);

		return ret;
	}

	void Release()
	{
		m_File.Close();
		free(data);
		delete this;
	}
};

#endif

struct WMusicStruct {
	LPDIRECTSOUNDBUFFER lpBuffer;
	WSound::WPlayMode mode;
	LPDIRECTSOUNDNOTIFY lpDSN;
	HANDLE MusicBufferEvent[3];		// 两个断点和退出标记

	ACMSTREAMHEADER stream1;
	ACMSTREAMHEADER stream2;
	HACMSTREAM acm;
	WFile hSrcWaveFile;

	LONG SeekHead;
	DWORD MusicSize;
	DWORD ReadSize;
	DWORD AlreadyRead;
	HANDLE hThread;
	int LastRead;
#ifdef _SUPPORT_MP3
	bool IsMp3;
	MP3IO			*mi;
	DATAIO			*io;
#endif

//	FILE *file;
//	int thisblock;
//	int datapoint;
};

#include "wsrandom.h"
#include "wsstring.h"

WMusic* WSound::GetMusic()
{
	if (!IsAvailable()) return 0;
	return m_pDevice->lpMusic;
}

WMusic* WSound::OpenMusic(const char *filename)
{
	if (!IsAvailable()) return 0;
//	return 0;
	if (m_pDevice->lpMusic==0) {
		m_pDevice->lpMusic=new WMusic(this);
	}
	else {
//		MessageBox(0,"已经有声音, 停止","声音",0);
		m_pDevice->lpMusic->Stop();
	}
	WSERR r;
	if ((r=m_pDevice->lpMusic->OpenFile(filename))!=WS_OK) {
//		WString s;
//		s.Format("%c%c%c%c",WSERR_STRING(r));
//		MessageBox(0,s,"声音",0);
		if (m_pDevice->lpMusic) {
				delete m_pDevice->lpMusic;
				m_pDevice->lpMusic=0;
			}
		return 0;
	}
	return m_pDevice->lpMusic;
}

unsigned long __stdcall WMusic::MusicThread(void *p)
{
	WMusic *pThis=(WMusic *)p;
	void *soundbuffer;
	DWORD num,buffersize;
	for (;;) {
		num=MsgWaitForMultipleObjects(3,pThis->m_pMS->MusicBufferEvent,FALSE,INFINITE,0);
		num-=WAIT_OBJECT_0;
		if (num==2) {
			break;
		}
		if (WaitForSingleObject(pThis->m_pMS->MusicBufferEvent[2],0)==WAIT_OBJECT_0) {
			break;
		}
//		if (num==2) {
//			break;
//		}
//		if (num<3) {
		if (pThis->m_pMS->mode==WSound::play_over) {
			pThis->StopBuffer();
			return 0;
		}

		if (FAILED(pThis->m_pMS->lpBuffer->Lock((num==0)?0:c_BufferSize/2,c_BufferSize/2,&soundbuffer,&buffersize,NULL,NULL,0))) continue;
		ASSERT(c_BufferSize/2==buffersize && "音乐 Buffer 大小不对");
		pThis->ReadNext(soundbuffer);
		pThis->m_pMS->lpBuffer->Unlock(soundbuffer,buffersize,NULL,0);
//		}
	}
	pThis->m_pMS->lpBuffer->Stop();
	return 0;
}

WMusic::WMusic(WSound *ws) : m_DS(ws)
{
	m_pMS=new WMusicStruct;
	m_pMS->MusicBufferEvent[0]=CreateEvent(NULL,FALSE,FALSE,NULL);
	m_pMS->MusicBufferEvent[1]=CreateEvent(NULL,FALSE,FALSE,NULL);
	m_pMS->MusicBufferEvent[2]=CreateEvent(NULL,TRUE,FALSE,NULL);
	m_pMS->hThread=NULL;
	m_pMS->mode=WSound::play_over;
	m_pMS->lpBuffer=0;
	m_pMS->lpDSN=0;
#ifdef _SUPPORT_MP3
	m_pMS->io=0;
#endif
}

WMusic::~WMusic()
{
	Release();
}

void WMusic::Release()
{
	Stop();
	CloseHandle(m_pMS->MusicBufferEvent[0]);
	CloseHandle(m_pMS->MusicBufferEvent[1]);
	CloseHandle(m_pMS->MusicBufferEvent[2]);
	delete m_pMS;
}

void WMusic::StopBuffer()
{
	ResetEvent(m_pMS->MusicBufferEvent[0]);
	ResetEvent(m_pMS->MusicBufferEvent[1]);
	if (m_pMS->lpBuffer) {
//		fclose(m_pMS->file);
//		m_pMS->file=0;
#ifdef _SUPPORT_MP3
		if (!m_pMS->IsMp3) {
#endif
			WFree(m_pMS->stream1.pbSrc);
			WFree(m_pMS->stream2.pbSrc);

			acmStreamUnprepareHeader(m_pMS->acm,&m_pMS->stream1,0);
			acmStreamUnprepareHeader(m_pMS->acm,&m_pMS->stream2,0);

			acmStreamClose(m_pMS->acm,0);

			m_pMS->hSrcWaveFile.Close();
#ifdef _SUPPORT_MP3
		}
#endif
	}
	if (m_pMS->lpDSN) {
		m_pMS->lpDSN->Release();
		m_pMS->lpDSN=0;
	}
	if (m_pMS->lpBuffer) {
		m_pMS->lpBuffer->Stop();
		m_pMS->lpBuffer->Release();
		m_pMS->lpBuffer=0;
	}
	m_pMS->mode=WSound::play_over;
//	ResetEvent(m_pMS->MusicEnd);
}

void WMusic::Stop()
{
	ASSERT(m_pMS);
	if (m_pMS->hThread) {	
		SetEvent(m_pMS->MusicBufferEvent[2]);
		WaitForSingleObject(m_pMS->hThread,INFINITE);
		m_pMS->hThread=NULL;
		StopBuffer();
	}
#ifdef _SUPPORT_MP3
	if (m_pMS->io) {
		m_pMS->io->Release();
		m_pMS->io=0;
	}
#endif
//	Sleep(100);
}

bool WMusic::IsAvailable() const
{
	return m_pMS->lpBuffer!=0;
}

void WMusic::Play(WSound::WPlayMode mode)
{
	DWORD buffersize;
	void *soundbuffer;
	if (!IsAvailable()) {
		m_pMS->hThread=NULL;
		return;
	}
	LPDIRECTSOUNDBUFFER buffer=m_pMS->lpBuffer;
	ASSERT (buffer!=0);
	m_pMS->mode=mode;

	buffer->Lock(0,c_BufferSize/2,&soundbuffer,&buffersize,NULL,NULL,0);
	ReadNext(soundbuffer);
	buffer->Unlock(soundbuffer,buffersize,NULL,0);
	buffer->SetCurrentPosition(0);

	buffer->Play(0,0,DSBPLAY_LOOPING);
	m_pMS->LastRead=0;
	DWORD ThreadID;
	m_pMS->hThread=CreateThread(NULL,0,MusicThread,this,0,&ThreadID);
}


WSERR WMusic::OpenFile(const char *filename)
{
	WSERR wr;
	WFile &hSrcWaveFile=m_pMS->hSrcWaveFile;
	struct {
		DWORD id;
		DWORD size;
	} chunk;

	wr=hSrcWaveFile.Open(filename);
	if (wr!=WS_OK) return wr;
	MMRESULT Result;
	WAVEFORMATEX *DstHeader=0;

	hSrcWaveFile.Read(&chunk,sizeof(chunk));
	if ((chunk.id&0xe0ff)==0xe0ff) {
#ifdef _SUPPORT_MP3
		DstHeader=(WAVEFORMATEX *)_alloca(sizeof(WAVEFORMATEX));
		m_pMS->IsMp3=true;
		hSrcWaveFile.Close();
		m_pMS->io=StdDataIO::Create((void *)filename, 4096);
		m_pMS->mi	= tMP3Create(m_pMS->io);
		DstHeader->wFormatTag=WAVE_FORMAT_PCM;
		DstHeader->wBitsPerSample=16;
		DstHeader->nChannels=m_pMS->mi->Channels;
		DstHeader->cbSize=0;
		DstHeader->nSamplesPerSec=m_pMS->mi->Rate;
		DstHeader->nBlockAlign=DstHeader->nChannels*2;
		DstHeader->nAvgBytesPerSec=DstHeader->nSamplesPerSec*DstHeader->nBlockAlign;
#else
		return WS_INVALIDWAVETYPE;
#endif
	}
	else {
#ifdef _SUPPORT_MP3
		m_pMS->IsMp3=false;
#endif
		if (chunk.id!=WFourCC("RIFF")) return WS_INVALIDWAVETYPE;
		hSrcWaveFile.Read(&chunk.id,sizeof(chunk.id));
		if (chunk.id!=WFourCC("WAVE")) return WS_INVALIDWAVETYPE;
		hSrcWaveFile.Read(&chunk,sizeof(chunk));
		if (chunk.id!=WFourCC("fmt ")) return WS_INVALIDWAVETYPE;

		int SrcHeaderSize=chunk.size;
		if(SrcHeaderSize<sizeof(WAVEFORMATEX))
			SrcHeaderSize=sizeof(WAVEFORMATEX);
		WAVEFORMATEX &SrcHeader=*(WAVEFORMATEX *)_alloca(SrcHeaderSize);
		ZeroMemory(&SrcHeader,SrcHeaderSize);
		hSrcWaveFile.Read(&SrcHeader,chunk.size);

		for (;;) {
			hSrcWaveFile.Read(&chunk,sizeof(chunk));
			if (chunk.id==WFourCC("data")) break;
			hSrcWaveFile.Skip(chunk.size);
			if (hSrcWaveFile.IsEnd()) return WS_INVALIDWAVETYPE;
		} 

		m_pMS->SeekHead=hSrcWaveFile.Tell();

		// 准备变换后的handle
		DstHeader=(WAVEFORMATEX *)_alloca(SrcHeaderSize);
		memcpy(DstHeader,&SrcHeader,SrcHeaderSize);
		DstHeader->wFormatTag=WAVE_FORMAT_PCM;
		Result=acmFormatSuggest(NULL,&SrcHeader,DstHeader,SrcHeaderSize,ACM_FORMATSUGGESTF_WFORMATTAG);
		if (Result!=0) return WS_UNSUPPORTWAVETYPE;

		// 准备ACM STREAM
		Result=acmStreamOpen(&m_pMS->acm,NULL,&SrcHeader,DstHeader,NULL,NULL,0,0);//ACM_STREAMOPENF_NONREALTIME);
		if (Result!=0) return WS_UNSUPPORTWAVETYPE;

		// 取得源声音的长度
		m_pMS->MusicSize=chunk.size;
		m_pMS->AlreadyRead=0;

		// 对应输出Bytes获得输入Bytes
		Result=acmStreamSize(m_pMS->acm,c_BufferSize/2,&(m_pMS->ReadSize),ACM_STREAMSIZEF_DESTINATION);
		if (Result!=0) {
			acmStreamClose(m_pMS->acm,0);
			return WS_UNSUPPORTWAVETYPE;
		}
	}

	// 构造 DirectSoundBuffer
	DSBUFFERDESC dsbd;

	dsbd.dwSize=sizeof(DSBUFFERDESC);
	dsbd.dwFlags=WSSB_CAPS|DSBCAPS_LOCSOFTWARE|DSBCAPS_GLOBALFOCUS|DSBCAPS_CTRLPOSITIONNOTIFY;
	dsbd.dwBufferBytes=c_BufferSize;
	dsbd.dwReserved=0;
	dsbd.lpwfxFormat=DstHeader;

	if (FAILED(m_DS->m_pDevice->lpDS->CreateSoundBuffer(&dsbd,&(m_pMS->lpBuffer),NULL))) {
#ifdef _SUPPORT_MP3
		if (m_pMS->IsMp3) 
			return WS_DIRECTSOUNDERROR;
#endif
		acmStreamClose(m_pMS->acm,0);
		return WS_DIRECTSOUNDERROR;
	}

	BYTE *soundbuf;
	DWORD size;
	m_pMS->lpBuffer->Lock(0,0,(void**)&soundbuf,&size,NULL,NULL,DSBLOCK_ENTIREBUFFER);

#ifdef _SUPPORT_MP3
	if (!m_pMS->IsMp3) {
#endif
	// 准备变换buffer
	ZeroMemory(&(m_pMS->stream1),sizeof(m_pMS->stream1));
	m_pMS->stream1.cbStruct=sizeof(m_pMS->stream1);
	m_pMS->stream1.pbSrc=(BYTE*)WAlloc(m_pMS->ReadSize);
	m_pMS->stream1.cbSrcLength=m_pMS->ReadSize;
	m_pMS->stream1.pbDst=soundbuf;
	m_pMS->stream1.cbDstLength=c_BufferSize/2;
	Result=acmStreamPrepareHeader(m_pMS->acm,&(m_pMS->stream1),0);
	ASSERT(Result==0);

	ZeroMemory(&(m_pMS->stream2),sizeof(m_pMS->stream2));
	m_pMS->stream2.cbStruct=sizeof(m_pMS->stream2);
	m_pMS->stream2.pbSrc=(BYTE*)WAlloc(m_pMS->ReadSize);
	m_pMS->stream2.cbSrcLength=m_pMS->ReadSize;
	m_pMS->stream2.pbDst=soundbuf+c_BufferSize/2;
	m_pMS->stream2.cbDstLength=c_BufferSize/2;
	Result=acmStreamPrepareHeader(m_pMS->acm,&(m_pMS->stream2),0);
	ASSERT(Result==0);

#ifdef _SUPPORT_MP3
	}
#endif

	m_pMS->lpBuffer->Unlock(soundbuf,size,NULL,0);

	InitBuffer();

	return WS_OK;			
}

void WMusic::InitBuffer()
{
	ASSERT(m_pMS->lpBuffer);
	DSBPOSITIONNOTIFY dsbpn[2];

	ResetEvent(m_pMS->MusicBufferEvent[0]);
	ResetEvent(m_pMS->MusicBufferEvent[1]);
	ResetEvent(m_pMS->MusicBufferEvent[2]);

	dsbpn[0].hEventNotify=m_pMS->MusicBufferEvent[0];
	dsbpn[0].dwOffset=c_BufferSize/2;
	dsbpn[1].hEventNotify=m_pMS->MusicBufferEvent[1];
	dsbpn[1].dwOffset=0;//DSBPN_OFFSETSTOP;

	m_pMS->lpBuffer->QueryInterface(IID_IDirectSoundNotify,(LPVOID *)&m_pMS->lpDSN);
	m_pMS->lpDSN->SetNotificationPositions(2,dsbpn);

}

void WMusic::ReadNext(void *soundbuffer)
{
#ifdef _SUPPORT_MP3
	if (m_pMS->IsMp3) {
		int read=tMP3GetFrame(m_pMS->mi, soundbuffer, c_BufferSize/2);
		if (read<c_BufferSize/2) {
			if (m_pMS->mode!=WSound::play_loop) {
				m_pMS->mode=WSound::play_over;
				memset((BYTE*)soundbuffer+read,0,c_BufferSize/2-read);
			}
			else {
				tMP3Reset(m_pMS->mi);
				tMP3GetFrame(m_pMS->mi, (BYTE*)soundbuffer+read, c_BufferSize/2-read);
			}
		}
		return;
	}
#endif
	ACMSTREAMHEADER *s = nullptr;
	if (m_pMS->mode!=WSound::play_loop && m_pMS->AlreadyRead>=m_pMS->MusicSize) {
		m_pMS->mode=WSound::play_over;
		return;
	}
	DWORD ReadSize=MIN(m_pMS->ReadSize,m_pMS->MusicSize-m_pMS->AlreadyRead);
//	m_pMS->stream.pbDst=buffer;
	if (soundbuffer==m_pMS->stream1.pbDst) {
		s=&m_pMS->stream1;
	}
	else if (soundbuffer==m_pMS->stream2.pbDst) {
		s=&m_pMS->stream2;
	}
	else ASSERT(0 && "sound buffer 错误");

	s->cbSrcLength=ReadSize;
		// 变换

	m_pMS->AlreadyRead+=ReadSize;

	char *buf=(char*)s->pbSrc;

	if (m_pMS->AlreadyRead>=m_pMS->MusicSize) {
//		ZeroMemory(s->pbDst,c_BufferSize/2);
		if (m_pMS->mode==WSound::play_loop) {
			m_pMS->hSrcWaveFile.Read(buf,ReadSize);
			buf+=ReadSize;
			ReadSize=m_pMS->ReadSize-ReadSize;
			s->cbSrcLength+=ReadSize;
			m_pMS->hSrcWaveFile.Read(0,0,m_pMS->SeekHead);
			m_pMS->AlreadyRead=ReadSize;
		}
		else {
			m_pMS->hSrcWaveFile.Read(buf,ReadSize);
			buf+=ReadSize;
			ReadSize=m_pMS->ReadSize-ReadSize;
		}
	}
	MMRESULT Result;
	if (ReadSize>0) m_pMS->hSrcWaveFile.Read(buf,ReadSize);
	if (ReadSize<m_pMS->ReadSize && m_pMS->mode!=WSound::play_loop) {
		memset(soundbuffer,0,c_BufferSize/2);
	}
	Result=acmStreamConvert(m_pMS->acm,s,0);
//	WMemCpy(soundbuffer,m_pMS->stream.pbDst,c_BufferSize/2);
}

void WMusic::SetVolume(long vol)
{
	if (!m_DS->IsAvailable()) return;
	if (m_pMS->lpBuffer) m_pMS->lpBuffer->SetVolume(vol);
}

long WMusic::GetVolume() const
{
	long r;
	if (!m_DS->IsAvailable()) return 0;
	if (m_pMS->lpBuffer) m_pMS->lpBuffer->GetVolume(&r);
	return r;
}

bool WMusic::IsEnd() const
{
	if (!m_DS->IsAvailable()) return true;
	return (m_pMS->mode==WSound::play_over);
}