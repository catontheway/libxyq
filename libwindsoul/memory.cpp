#include <windows.h>
#include "windsoul.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "wsmemory.h"

//#define LOG_MEMORY

#ifdef new
#	undef new
#endif

#ifdef _LIB
#	define INLINE
#else
#	define INLINE inline
#endif

#ifdef _DEBUG

int memory_stat::peak=0;
int memory_stat::current=0;

#endif

#ifdef _DEBUG

INLINE void WThreadLock(long * atom)
{
	if (InterlockedExchange(atom,1)) {
		// 别的地方 lock 住了
		int i;
		for (/*int */i=0;InterlockedExchange(atom,1) && i<128;i++) {
			Sleep(0);
		}
		if (i>=128) {
			for (/*int */i=0;InterlockedExchange(atom,1) && i<16;i++) {
				Sleep(50);
			}
			ASSERT(i<16 && "lock 时间太长了");
		}
	}
}

#else

INLINE void WThreadLock(long* atom)
{
	if (InterlockedExchange(atom,1)) {
		// 别的地方 lock 住了
		while (InterlockedExchange(atom,1)) {
			// 等待别的地方 Unlock
			Sleep(0);
		}
	}
}

#endif

INLINE void WThreadUnlock(long * atom)
{
	InterlockedExchange(atom,0);
}

void* WMemoryAlloc(size_t size)
{
	return malloc(size);
}

void WMemoryFree(void *p)
{
	free(p);
}

enum { _align=8,_max_bytes=128,_pool_size=128 };

struct memory_cookie {
#ifdef _DEBUG
	const char *file;
	unsigned line;
	unsigned id;
#endif
	size_t size;
	union {
		memory_cookie *next;
		unsigned char data[1];
	};
};

static long _global_thread_atom=0;

class memory_pool {
	_vector<memory_cookie *> pool;
#ifdef _DEBUG
	_vector<size_t> size;
#endif
	static size_t round_up(size_t bytes) { // 把 bytes 对齐到 _align
		return ((bytes + (size_t)_align-1) & ~((size_t)_align - 1)); 
	}
	static void memory_pool::fill_pool(memory_cookie *p,size_t s);
public:
	memory_pool() {}
	~memory_pool();
	memory_cookie *allocate(size_t);
};

class memory_small {
	static long thread_atom;
	static memory_small * __instance;
	memory_cookie *pool[_max_bytes/_align];
	memory_small() {
		for (int i=0;i<_max_bytes/_align;i++) {
			pool[i]=0;
		}
	}
public:
	memory_pool mpool;
	void dump(memory_cookie *p,size_t size);
	void* allocate(size_t);
	void deallocate(void *);
	void* reallocate(void *,size_t);
	static memory_small& instance() {
		return *__instance;
	}
	friend class memory_init;
};

long memory_small::thread_atom=0;
memory_small* memory_small::__instance=0;

class memory_global {
	static memory_global* __instance;
	struct cookie {
#ifdef _DEBUG
		cookie *prev;
		cookie *next;
		const char *file;
		unsigned line;
		unsigned id;
#endif
		size_t size;
	};
#ifdef _DEBUG
	cookie *memory_link;
	int dump();
	memory_global() : memory_link(0) {}
public:
	~memory_global() { dump(); }
#endif
public:
	void *allocate(size_t size);
	void deallocate(void *p);
	static memory_global& instance() { 
		return *__instance;
	}
	friend class memory_init;
};

memory_global* memory_global::__instance=0;

class memory_init {
	static unsigned alloc_id;
public:
	memory_init() {
		static memory_small __memory_small__instance;
		static memory_global __memory_global__instance;
		if (memory_small::__instance==0) {
			memory_small::__instance=&__memory_small__instance;
			memory_global::__instance=&__memory_global__instance;
		}
	}
	static unsigned get_id() { 
		return ++alloc_id; 
	}
};

unsigned memory_init::alloc_id=0;

#ifdef _DEBUG

int memory_dump=-1;

int memory_global::dump()
{
	static char debug[256];
	memory_dump=0;
	for (;memory_link;memory_link=memory_link->next) {
		if (memory_link->file) {
			sprintf(debug,"%s(%u) [%u]: %u bytes < ",memory_link->file,memory_link->line,
				memory_link->id,memory_link->size-sizeof(cookie));
		}
		else {
			sprintf(debug,"unknown [%u]: %u bytes < ", memory_link->id, memory_link->size-sizeof(cookie));
		}
		OutputDebugString(debug);
		for (int j=0;j<8;j++) {
			sprintf(debug,"%02x ",reinterpret_cast<unsigned char*>(memory_link+1)[j]);
			OutputDebugString(debug);
		}
		OutputDebugString(">\n");
	}
	sprintf(debug,"Max memory used: [%d k]\n",memory_stat::get_peak()/1024);
	OutputDebugString(debug);
	return 0;
}

void memory_small::dump(memory_cookie *p,size_t size)
{
	static memory_cookie* array[_pool_size];
	static char debug[256];
	int i;
	char *pp=reinterpret_cast<char *>(p);
	for (i=0;i<_pool_size;++i,pp+=size) 
		array[i]=reinterpret_cast<memory_cookie*>(pp);

	char *begin=reinterpret_cast<char*>(p);
	memory_cookie **last=&pool[size/_align-1];

	for (p=*last;p;p=*last) {
		int n=(reinterpret_cast<char *>(p)-begin)/size;
		if (n>=0 && n<_pool_size) {
			array[n]=0;
			*last=p->next;
			}
		else last=&(p->next);
	}

	for (i=0;i<_pool_size;++i) {
		if (array[i]!=0) {
			if (array[i]->file) {
				sprintf(debug,"%s(%u) [%u]: %u bytes < ",array[i]->file,array[i]->line,
					array[i]->id,array[i]->size-sizeof(memory_cookie)+sizeof(memory_cookie*));
			}
			else {
				sprintf(debug,"unknown [%u]: %u bytes < ", array[i]->id,
					array[i]->size-sizeof(memory_cookie)+sizeof(memory_cookie*));
			}
			OutputDebugString(debug);
			for (int j=0;j<8;j++) {
				sprintf(debug,"%02x ",array[i]->data[j]);
				OutputDebugString(debug);
			}
			OutputDebugString(">\n");
		}
	}
}

#endif

// debug 版本, 可以把 memory_small 里的 leak dump 出来
memory_pool::~memory_pool()
{
	for (int i=0;i<pool.number;i++) {
#ifdef _DEBUG
		memory_small::instance().dump(pool[i],size[i]);
#endif
		free(pool[i]);
	}
}

// 把分配来的 pool 填充成 s 大小的小块 (s>0 已经是 _align 的整数倍)
void memory_pool::fill_pool(memory_cookie *p,size_t s)
{
	char *pp=reinterpret_cast<char *>(p),*next;
	for (size_t i=0;i<_pool_size-1;++i,pp=next) {
		next=pp+s;
		reinterpret_cast<memory_cookie*>(pp)->next=reinterpret_cast<memory_cookie*>(next);
		reinterpret_cast<memory_cookie*>(pp)->size=s;
	}
	reinterpret_cast<memory_cookie*>(pp)->next=0;
	reinterpret_cast<memory_cookie*>(pp)->size=s;
}

memory_cookie* memory_pool::allocate(size_t s)
{
	if (s==0)
		return 0;
	s=round_up(s);
	if (WINDSOUL_THREAD_SAFE) WThreadLock(&_global_thread_atom);
	memory_cookie *p=reinterpret_cast<memory_cookie*>(malloc(_pool_size*s));
	pool.push_back(p);
	fill_pool(p,s);
#ifdef _DEBUG
	size.push_back(s);
#endif
	if (WINDSOUL_THREAD_SAFE) WThreadUnlock(&_global_thread_atom);
	return p;
}

void* memory_global::allocate(size_t size)
{
	if (WINDSOUL_THREAD_SAFE) WThreadLock(&_global_thread_atom);
	cookie *p=reinterpret_cast<cookie*>(malloc(size + sizeof(cookie)-(sizeof(memory_cookie)-sizeof(memory_cookie*)) ));
	if (WINDSOUL_THREAD_SAFE) WThreadUnlock(&_global_thread_atom);
	p->size=size;
#ifdef _DEBUG
	p->prev=0,p->next=memory_link;
	if (memory_link) memory_link->prev=p;
	memory_link=p;
	p->id=memory_init::get_id();
	p->file=0;
#endif
	return ++p;
}

void memory_global::deallocate(void *p)
{
	if (p==0) return;
	cookie *block=reinterpret_cast<cookie *>(reinterpret_cast<char*>(p)-sizeof(cookie));
#ifdef _DEBUG	
	cookie *pp=block->prev, *pn=block->next;
	if (pp) pp->next=pn;
	else {
		if (pn==0) memory_link=0;
		else memory_link=pn;
	}
	if (pn) pn->prev=pp;
#endif		
	free(block);
}

void* memory_small::allocate(size_t size)
{
	size+=sizeof(memory_cookie)-sizeof(memory_cookie*);
#ifdef _DEBUG
	memory_stat::alloc(size);
#endif
	if (size>_max_bytes) {
		return memory_global::instance().allocate(size);
	}
	memory_cookie * &free_list=pool[(size-1)/_align];
	if (WINDSOUL_THREAD_SAFE) WThreadLock(&thread_atom);
	if (free_list==0) 
		free_list=mpool.allocate(size);
	void *r=free_list->data;
#ifdef _DEBUG
	free_list->id=memory_init::get_id();
	free_list->file=0;
#endif
	free_list=free_list->next;
	if (WINDSOUL_THREAD_SAFE) WThreadUnlock(&thread_atom);
	return r;
}

void* memory_small::reallocate(void *p,size_t size)
{
	if (p==0) {
		return allocate(size);
	}
	if (size==0) {
		deallocate(p);
		return 0;
	}
	memory_cookie *pp=reinterpret_cast<memory_cookie*>(reinterpret_cast<char*>(p)-
		sizeof(memory_cookie)+sizeof(memory_cookie*));
	const int cookie_size=sizeof(memory_cookie)-sizeof(memory_cookie*);

	if (pp->size >= size+cookie_size) {
		return p;
	}

	void *ret=allocate(size);

    memcpy(ret,p,pp->size-cookie_size);
	deallocate(p);
	return ret;
}


void memory_small::deallocate(void *p)
{
	if (p==0) return;
	memory_cookie *pp=reinterpret_cast<memory_cookie*>(reinterpret_cast<char*>(p)-
		sizeof(memory_cookie)+sizeof(memory_cookie*));

	size_t size=pp->size;

#ifdef _DEBUG
	memory_stat::free(size);
	if (memory_dump>=0) {
		static char debug[256];
		sprintf(debug,"delete [id=%d,%d]\n",pp->id,memory_dump++);
		::OutputDebugString(debug);		
	}
#endif

	if (size>_max_bytes) {
		memory_global::instance().deallocate(p);
		return;
	}

	memory_cookie * &free_list=pool[(size-1)/_align];
	if (WINDSOUL_THREAD_SAFE) WThreadLock(&thread_atom);
	pp->next=free_list;
	free_list=pp;
	if (WINDSOUL_THREAD_SAFE) WThreadUnlock(&thread_atom);
}

#ifdef LOG_MEMORY

#include <cstdio>

FILE *log_memory=0;

void log_alloc(size_t s,void *p)  
{
	if (log_memory==0) {
		log_memory=fopen("mlog.txt","w");
	}
	fprintf(log_memory,"a:%d,0x%x\n",s,p);
}

void log_free(void *p)
{
	if (log_memory==0) {
		return;
	}
	fprintf(log_memory,"f:0x%x\n",p);
}

#else

inline void log_alloc(size_t,void *p) {}
inline void log_free(void *) {}

#endif

void WDelete(void *p)
{
	log_free(p);
	memory_small::instance().deallocate(p);
}

INLINE void* WRealloc(void *p,unsigned size)
{
	static memory_init __init;
	return memory_small::instance().reallocate(p,size);
}

INLINE void* WNew(size_t size)
{
	void *r=WRealloc(0,size);
	log_alloc(size,r);
	return r;
}

#ifdef _DEBUG

void* WNew(size_t size,const char *file,unsigned line)
{
	char *r=reinterpret_cast<char*>(WNew(size));
	memory_cookie *p=reinterpret_cast<memory_cookie*>(r-sizeof(memory_cookie)+sizeof(memory_cookie*));
	p->file=file,p->line=line;
	return r;
}

void WDelete(void *p,const char *file,unsigned line)
{
	memory_small::instance().deallocate(p);
}

#endif
