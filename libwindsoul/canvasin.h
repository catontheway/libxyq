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

		Description:		风魂画布内部头文件
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/14
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_CANVAS_INTERNAL_H
#define _WINDSOUL_CANVAS_INTERNAL_H

//打开这个宏,你将看见被优化的 Canvas 区域
// #define _DEBUG_CANVAS

#include "objheap.h"

struct CANVAS_LINK {
	BLIT_FUNC blit_func;
	DWORD param;
	CANVAS_LINK *next;
};

struct CANVAS_RECTLINK {
	WRect rect;
	CANVAS_RECTLINK *next;
};

template <class T,int size=128>
class CANVAS_LINKPAGE {
	T page[size];
	CANVAS_LINKPAGE *next;
	int top;
public:
	CANVAS_LINKPAGE() : next(0), top(0) {}
	~CANVAS_LINKPAGE() { if (next) delete(next); }
	void clear() { top=0; }	// 清空
	void clearobj(WObjectHeap &heap);	// 连同对象一起清空
	T *alloc();				// 申请一个节点
};

template <class T,int size>
void CANVAS_LINKPAGE<T,size>::clearobj(WObjectHeap &heap)
{
//	CANVAS_LINKPAGE *p;
//	int i;
//	for (p=this;p;p=p->next)
//		for (i=0;i<p->top;i++)
//			p->page[i].~T();
	heap.Clear();
	top=0;
}

template <class T,int size>
T* CANVAS_LINKPAGE<T,size>::alloc()
{
	CANVAS_LINKPAGE *p=this;
	while (p->top>=size) 
		p=p->next;
	if (++p->top>=size) {
		if (p->next) p->next->top=0;
		else p->next=new CANVAS_LINKPAGE<T,size>;
	}
	return &p->page[p->top-1];
}

class WCanvasBlock : public WBitmap {
	int last;				// 上一帧对象数目
	int obj;				// 当前块上对象数目
	int offset;				// 父位图中的X偏移
	bool m_IsTrans;			// 是否有透明块
	bool m_IsOvl;			// 是否被覆盖
	CANVAS_LINK link;		// 对象链表头
	CANVAS_LINK *change;	// 开始改变的节点
#ifdef _DEBUG_CANVAS
	bool m_IsMasked;		// 是否为没改变的块罩上 Mask
#endif
friend class WSurface;
friend class WCanvas;
public:
#ifdef _DEBUG_CANVAS
	WCanvasBlock() : obj(0), last(0), m_IsMasked(false) {}
#else
	WCanvasBlock() : obj(0), last(0) {}
#endif
};

#ifdef _RECORD_CANVAS

struct WCanvasRecorder {
	struct Block {
		WBitmap bmp;
		WORD id;
		Block *next;
	};
	Block *blocks;
	WORD block_x;
	WORD block_y;
	WORD offset_x;
	WORD offset_y;
	WCanvasRecorder *next;
};
#endif

struct WCanvasInternalData {
	CANVAS_RECTLINK rect_link;	// 覆盖矩形链表头
	CANVAS_LINKPAGE<CANVAS_LINK> object_mem;
	CANVAS_LINKPAGE<CANVAS_RECTLINK> rect_mem;
	WPoint offset;				// 开始点
	WRect viewport;				// 显示区域
	bool moved;					// 滚动标记
	bool laptop;
	WObjectHeap heap;			// Canvas用的分配堆
	short timer;				// fps 控制使用

#ifdef _RECORD_CANVAS
	WCanvasRecorder *recorder_head;
	WCanvasRecorder *recorder_p;

	WCanvasInternalData(int width,int height) : viewport(0,0,width,height),offset(0,0),moved(false),timer(0),recorder_head(0),laptop(false) {}
#else
	WCanvasInternalData(int width,int height) : viewport(0,0,width,height),offset(0,0),moved(false),timer(0),laptop(false) {}
#endif
};

#endif