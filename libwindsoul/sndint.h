#ifndef _WINDSOUL_SOUND_INTERNAL_H_
#define _WINDSOUL_SOUND_INTERNAL_H_

#pragma once

//#define _SUPPORT_MP3

#pragma comment (lib,"msacm32.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"dsound.lib")

#define WSSB_CAPS DSBCAPS_CTRLPAN|DSBCAPS_CTRLVOLUME
#define WSSB_CAPS2 DSBCAPS_CTRLVOLUME

struct WSampleBuffer {
	LPDIRECTSOUNDBUFFER m_Buffer;
	WSampleBuffer(void *buffer) : m_Buffer ((LPDIRECTSOUNDBUFFER)buffer) {}
	~WSampleBuffer();
};

class WSampleLoader : public WCacheNode<WSampleBuffer> {
	int DoLoad(void *hint) {
		int size=0;
		void *buffer=((WSound*)hint)->ReadWav(m_Filename,size);
		if (buffer) {
			m_Object=new WSampleBuffer(buffer);
		}
		return size;
	}
};

class WSoundDevice {
public:
	LPDIRECTSOUND lpDS;
	LPDIRECTSOUNDBUFFER lpDSP;
	WMusic *lpMusic;
	WCache<WSampleBuffer,WSampleLoader> Cache;

	WSoundDevice(int cachesize) : Cache(cachesize), lpMusic(0) {}
};

typedef WNode<WSampleBuffer,WSampleLoader> WSampleNode;

struct WSampleStruct {
	long m_Vol;
	WSound::WPlayMode m_Mode;	// 播放状态
	LPDIRECTSOUNDBUFFER m_Duplicate;	// 是否是复制出来的 Buffer
	WSampleNode *m_Node;		// 用于 Quest 出 WSampleBuffer 的节点

	WSampleStruct() : m_Vol(0), m_Mode(WSound::play_over), m_Duplicate(0), m_Node(0) { }
	~WSampleStruct() {
		ASSERT(m_Duplicate==0);
		if (m_Node) m_Node->Release();
	}
};

#endif