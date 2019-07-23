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

		Description:		RLE Sprite Cache 头文件
 		Original Author:	云风
		Authors:
		Create Time:		2001/6/11
		Modify Time:		2001/11/7

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#pragma once

#ifndef _WINDSOUL_SPRITE_CACHE_H_
#define _WINDSOUL_SPRITE_CACHE_H_

#include "wsprite.h"

class WSpriteCache;
class WSpriteNode;

class WINDSOULADD_API memory<WSpriteNode>::manager;
template class WINDSOULADD_API memory<WSpriteNode>;

class WINDSOULADD_API WSpriteNode : public memory<WSpriteNode> {
	char m_Filename[256];
	WSpritePak *m_Data;
	int m_Ref;
	DWORD m_Id;
	WSpriteNode *m_Last;
	WSpriteNode *m_Next;
	WSpriteCache *m_Cache;
	friend class WSpriteCache;
	friend class WSpriteData;

	WSERR Reload();
	void Unload();
	void LinkNextTo(WSpriteNode &node);
public:
	short Direction;
	short Frames;
	short Width;
	short Height;
	short Kx;
	short Ky;

	WSpriteNode() : m_Data(0), m_Id(0), m_Last(0), m_Next(0), m_Ref(0), m_Cache(0) {}
	~WSpriteNode();
	WSpriteNode *GetCacheHead();
//	void CheckRef();
};

class WINDSOULADD_API WSpriteCache {
	DWORD m_CacheSize;
	DWORD m_CacheUsed;
	WSpriteNode m_Head;
	WSpriteNode m_Unlocked;	// 没有 Lock 住的 Sprite 链表
	WSpriteNode m_NoUsed;	// 没有被使用的部分
	WSpriteNode m_Tail;		// Sprite 链表尾巴, 不放数据
	WSpriteNode *m_pNode;	// 当前增加节点的位置

	void Increase(DWORD size);	// Cache 增加 size 字节

	friend class WSpriteNode;
public:
	int Overflow() const { return m_CacheUsed-m_CacheSize; }
	void Lock() { Unlock();	m_pNode=&m_Head; }
	void Unlock();
	const DWORD CacheSize() const { return m_CacheSize; }
	void CacheSize(DWORD newsize) { m_CacheSize=newsize; }
	WSpriteCache(DWORD size=0x2000000); // 缺省有 32M cache
	~WSpriteCache();

	WSpriteNode *Load(const char *filename);	// 取出 方向和 frame
};

class WINDSOULADD_API WSpriteData {
	WSpriteNode *m_Data;
public:
	WSpriteData() : m_Data(0) {}
	~WSpriteData() { Unload(); }

	short GetDirection() const { return m_Data->Direction; }
	short GetFrames() const { return m_Data->Frames; }
	short GetWidth() const { return m_Data->Width; }
	short GetHeight() const { return m_Data->Height; }
	short GetX() const { return m_Data->Kx; }
	short GetY() const { return m_Data->Ky; }

	void Create(WSpriteNode *node);
	void Unload();
	WSpritePak* Quest() { m_Data->Reload(); return m_Data->m_Data; }
	const WSprite* operator[](int n) const { return (*(m_Data->m_Data))[n]; }
	const WSpritePak* operator->() const { return m_Data->m_Data; }
	const WSpritePak* GetSprite() const { return m_Data->m_Data; }
};

inline WSpriteNode* WSpriteNode::GetCacheHead()	
{
	return m_Cache->m_pNode; 
}

#endif