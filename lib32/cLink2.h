#pragma once

#if 0
#include "_window.h"

namespace ccastar
{
	typedef HANDLE _HANDLE;
	typedef LPVOID voidp;
	typedef BYTE uchar;
	typedef DWORD ulong;
}

#else

namespace ccastar
{
	typedef void* _HANDLE;
	typedef void* voidp;
	typedef unsigned char uchar;
	typedef unsigned long ulong;
}
#endif

struct sLink2
{
	sLink2*	parent;
	sLink2*	child;
	ccastar::voidp v;
	ccastar::ulong k;
};

struct sLinkHead
{
	ccastar::_HANDLE handle;
	ccastar::ulong datasize;
	sLink2* first;
	sLink2* tail;
	sLink2* cur;
	ccastar::ulong nodesCount;
};


// Ë«ÏòÁ´±í
class cLink2
{
private:
	sLinkHead head;

public:
	cLink2(ccastar::ulong max);
	~cLink2();

	enum class eInsert{ before, after };
	bool insert(ccastar::voidp v, ccastar::ulong k, eInsert e = eInsert::after);
	void remove();
	void remove(ccastar::voidp link);
	void clear();
	void setCur(ccastar::voidp link);
	bool setParent();
	bool setChild();
	void setFirst();
	void setTail();
	ccastar::voidp getValue();
	ccastar::ulong getKey();
	ccastar::voidp getCur();
	ccastar::ulong getNodesCount();
};