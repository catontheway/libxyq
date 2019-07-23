#ifndef _WINDSOUL_MEMORY_H_
#define _WINDSOUL_MEMORY_H_

#pragma once

#include "windsoul.h"

#include <cstddef>
#include <cassert>

#ifdef _DEBUG
#	include <cstdio>
#	include <typeinfo>
#endif

#ifdef new 
#	error user-defined new ?
#endif

// 把下面定义改成 false, 内存分配可以快一点, 但是不是 thread safe 的
#define WINDSOUL_THREAD_SAFE true

WINDSOUL_API void WThreadLock(long *);	// lock 函数, 保证 thread safe 用
WINDSOUL_API void WThreadUnlock(long *);
WINDSOUL_API void* WMemoryAlloc(size_t size);
WINDSOUL_API void WMemoryFree(void *p);

// 因为涉及到内存分配, 必须使用纯代码(不使用std::vector), 才保证不死循环
// 这个简单的 _vector 使用 memcopy 增长, T 必须是简单结构
template <class T>
class _vector {
	T* ptr;
public:
	int number;
	int size;
	void push_back(const T &t);
	const T & operator[](int n) const { return ptr[n]; }
	_vector() : ptr(0),number(0), size(0) {}
	~_vector() { WMemoryFree(ptr); }
};

template <class T>
void _vector<T>::push_back(const T &t)
{
	if (number>=size) {
		int newsize=(size+4)*3/2;
		T* newptr=reinterpret_cast<T*>(WMemoryAlloc(newsize*sizeof(T)));
		memcpy(newptr,ptr,number*sizeof(T));
		WMemoryFree(ptr);
		ptr=newptr,size=newsize;
	}
	ptr[number++]=t;
}

struct memory_object {
	memory_object *next;
};

#ifdef _DEBUG

class WINDSOUL_API memory_stat {
	static int peak;
	static int current;
public:
	static void alloc(size_t size) { 
		current+=size;
		if (current>peak) peak=current;
	}
	static void free(size_t size) {
		current-=size;
	}
	static int get_peak() { return peak; }
	static void reset_peak() { peak=current; }
	static int get_current() { return current; }
};

#endif

template<typename T,bool thread=WINDSOUL_THREAD_SAFE>
class memory {
public:
	static long thread_atom;
	class manager {
		enum { size=32 };
		_vector<memory_object*> pool;
		static void fill_pool(memory_object *p) {
			memory_object *next;
			for (int i=0;i<size-1;i++,p=next) {
				next=reinterpret_cast<memory_object*>(reinterpret_cast<char*>(p)+sizeof(T));
				p->next=next;
			}
			p->next=0;
		}
	public:
		memory_object* allocate() {
			memory_object* p=reinterpret_cast<memory_object*>(WMemoryAlloc(size*sizeof(T)));
			fill_pool(p);
			return p;
		}
		~manager() {
			for (int i=0;i<pool.number;i++)
				WMemoryFree(pool[i]);
		}
	};
#ifdef _DEBUG
	void* operator new(size_t size) { return WNew(size,0,0); }
	void operator delete(void *p) { WDelete(p,0,0); }
	void* operator new(size_t size,const char *file,unsigned line) { 
		return WNew(size,file,line);
	}
	void operator delete(void *p,const char *file,unsigned line) {
		WDelete(p,file,line);
	}
#else
	void* operator new(size_t size) {
		assert(size==sizeof(T) && size>=4);
		if (thread) WThreadLock(&thread_atom);
		if (free_list==0) free_list=pool.allocate();
		memory_object *r=free_list;
		free_list=free_list->next;
		if (thread) WThreadUnlock(&thread_atom);
		return r;
	}
	void operator delete(void *p) {
		if (p==0) return;
		if (thread) WThreadLock(&thread_atom);
		memory_object* pp=reinterpret_cast<memory_object*>(p);
		pp->next=free_list;
		free_list=pp;
		if (thread) WThreadUnlock(&thread_atom);
	}
#endif
private:
	static memory_object* free_list;
	static manager pool;
	friend class memory::manager;
};

template<typename T,bool thread> typename memory<T,thread>::manager memory<T,thread>::pool;
template<typename T,bool thread> memory_object* memory<T,thread>::free_list=0;
template<typename T,bool thread> long memory<T,thread>::thread_atom=0;

extern "C" {
	WINDSOUL_API void * __cdecl WNew(unsigned size);
	WINDSOUL_API void __cdecl WDelete(void *p);
	WINDSOUL_API void * __cdecl WRealloc(void *p,unsigned size);
}

#ifndef _DISABLE_WINDSOUL_NEW

#if !(defined(WINDSOULADD_STATICLIB) || defined(_LIB)) || !defined(_AFXDLL)

inline void* operator new(size_t size) { return WNew(size); }
inline void operator delete(void *p) { WDelete(p); }
inline void* operator new[](size_t size)  { return WNew(size); }
inline void operator delete[](void *p) { WDelete(p); }

#endif

#endif

#ifdef _DEBUG
WINDSOUL_API void * WNew(unsigned size,const char *file,unsigned line);
WINDSOUL_API void WDelete(void *p,const char *file,unsigned line);

#ifndef _DISABLE_WINDSOUL_NEW

inline void* operator new(size_t size,const char *file,unsigned line)
{
	return WNew(size,file,line);
}

inline void operator delete(void *p,const char *file,unsigned line)
{
	WDelete(p,file,line);
}

inline void* operator new[](size_t size,const char *file,unsigned line)
{
	return WNew(size,file,line);
}

inline void operator delete[](void *p,const char *file,unsigned line)
{
	WDelete(p,file,line);
}

#endif

#endif

#ifndef _DISABLE_WINDSOUL_NEW

#ifdef _DEBUG
#	define debug_new new(__FILE__,__LINE__)
#else
#	define debug_new new
#endif

#endif

#endif	// _WINDSOUL_MEMORY_H_