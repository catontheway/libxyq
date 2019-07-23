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

		Description:		Cache 管理
 		Original Author:	云风
		Authors:
		Create Time:		2002/3/5
		Modify Time:		2002/3/7

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/


#ifndef _WINDSOUL_CACHE_H_
#define _WINDSOUL_CACHE_H_

#pragma once

#include "wsaddon.h"
#include "wsstring.h"

class WINDSOULADD_API WCacheNodeBase {
protected:
	WString m_Filename;			// 在硬盘上的文件名
	int m_Id;					// 文件名对应 ID
	int m_Size;					// 数据长度
	int m_Ref;					// 引用次数
protected:
	virtual int DoLoad(void *hint)=0;			// 从硬盘加载(返回数据长度,返回 0 表示加载失败)
	WCacheNodeBase() : m_Id(0), m_Size(0), m_Ref(0) {}
	~WCacheNodeBase() { ASSERT(m_Ref==0); }
public:
	const WString& GetFilename() const { return m_Filename; }
	int GetSize() const { return m_Size; }		// 返回占用内存数
	int GetId() const { return m_Id; }			// 返回 ID
	void AddRef() { ++m_Ref; }					// 增加引用次数
	int Release() { return --m_Ref; }			// 减少引用次数(返回引用次数)
	void Load(void *hint) { if (m_Id) m_Size=DoLoad(hint); }// 读盘
	virtual int Create(const WString &filename,int id) {	// 加载文件(非0 失败)
		ASSERT((unsigned)id==WString2ID(filename));
		m_Filename=filename;
		m_Id=id;
		AddRef();
		return 0;
	};
};

template <typename T>
class WCacheNode : public WCacheNodeBase {
protected:
	T *m_Object;				// 对象

	WCacheNode() : m_Object(0) {};
public:
	~WCacheNode() { Unload(); }
	void Unload() { delete m_Object; m_Object=0; }	// 卸载对象数据
	T* Object() const { return m_Object; }		// 获取对象
	T* Quest(void *hint) {			// Quest 对象, 返回指针
		if (!m_Object) {
			Load(hint);
		}
		return m_Object;
	}
};

class WCacheBase;

class WINDSOULADD_API WCacheNodeLink {
public:
	WCacheNodeLink(WCacheBase *container) { m_Next=this, m_Prev=this, m_Container=container; }
	void Unlock() { MoveTo(InRam); }			// Unlock 自己
	virtual void Release()=0;					// 释放自己(减少引用次数)
	friend WCacheBase;
protected:
	enum Status { Locked=0, InRam=1, OutRam=2, Garbage=3 };
	virtual ~WCacheNodeLink();
	virtual WCacheNodeLink* Clone() const=0;	// Clone 一个自己
	virtual int GetSize() const=0;				// 返回节点占用空间的大小
	virtual bool IsFile(int id) const=0;		// 判断是否是这个文件
	virtual void AddRef()=0;					// 增加引用次数
	virtual void Unload()=0;					// 卸载数据
	virtual WCacheNodeLink* AllocNode(const WString &name,int id);		// 构造一个节点, 连接在自己的后面

	WCacheNodeLink* GetNode(int id);			// 从文件名检索出节点
	void LinkHead(WCacheNodeLink *link);		// 把一条链加在前面
	void LinkNext(WCacheNodeLink *node);		// 把节点连接在自己的后面
	void ReleaseThis();							// 把节点脱离链(记得删除!)
	bool IsEmpty() const { return m_Next==this; }	// 是否为空
	void MoveTo(Status p);						// 移动自己到容器的指定位置

	WCacheNodeLink *m_Next;
	WCacheNodeLink *m_Prev;
	WCacheBase *m_Container;					// 容器
};

class WINDSOULADD_API WCacheBase {
protected:
	WCacheNodeLink *m_Link[4];				// 数据链表
	int m_CacheSize;						// Cache 大小
	int m_CacheUsed;						// Cache 使用了的大小
	friend class WCacheNodeLink;
protected:
	WCacheBase(int size) : m_CacheSize(size),m_CacheUsed(0) {}	// 应该由派生类来初始化
	~WCacheBase();							// 释放所有节点
	void GC();								// 垃圾回收
	WCacheNodeLink *QuestFileInNeed(const WString &name);	// 根据需要加载一个文件
public:
	void LoadNode(WCacheNodeLink *node) {
		node->MoveTo(WCacheNodeLink::Locked);
		m_CacheUsed+=node->GetSize();
		GC();
	}
	void UnLock();							// UnLock 掉上次 Lock 的节点
	int GetCacheUsed() const { return m_CacheUsed; }	// 返回 Cache 使用情况
};

template <typename T, typename NodeT>
class WNode : public WCacheNodeLink {
public:
	WNode(WCacheBase *container) : WCacheNodeLink(container) , m_Node(0) {}
	void AddRef() { m_Node->AddRef(); }						// 增加引用次数
	void Release() {								// 释放自己(减少引用次数)
		if (m_Node->Release()==0) 
			MoveTo(Garbage);
	}
	T* Quest(void *hint=0) { 									// 请求一个对象, 肯定在内存
		T *p=m_Node->Object();
		if (p) {
			MoveTo(Locked);
		}
		else {
			p=m_Node->Quest(hint);
			if (p)
				m_Container->LoadNode(this);
		}
		return p; 
	}
	const WString& GetFilename() const { return m_Node->GetFilename(); }
	int GetSize() const { return m_Node->GetSize(); }		// 返回节点占用空间的大小
	friend WCacheBase;
protected:
	~WNode() { 
		delete m_Node; 
	}
	WCacheNodeLink* Clone() const {							// Clone 一个自己
		WNode<T,NodeT>* p=new WNode<T,NodeT>(m_Container); 
		p->m_Node=new NodeT;
		return p;
	}	
	WCacheNodeLink* AllocNode(const WString &name,int id) {	// 构造一个节点, 连接在自己的后面
		WNode<T,NodeT> *p=(WNode<T,NodeT>*)WCacheNodeLink::AllocNode(name,id);
		p->m_Node->Create(name,id);
		return p;
	}
	bool IsFile(int id) const { return id==m_Node->GetId(); }// 判断是否是这个文件
	void Unload() { m_Node->Unload(); }						// 卸载数据

	WCacheNode<T> *m_Node;
};


template <typename T, typename NodeT>
class WCache : public WCacheBase {
public:
	WCache(int size) : WCacheBase(size) {			// 初始化 m_Link[4]
		for (int i=0;i<4;i++) {
			m_Link[i]=new WNode<T,NodeT>(this);
		}
	}
	WNode<T,NodeT> *Quest(const WString &name) {	// 请求一个文件
		return (WNode<T,NodeT>*)QuestFileInNeed(name); 
	}	
};

#endif