/*
 "		   .....            ,;;;;;.           [ String Class v1.0 ]
 '		  ":;;;;`     ....;;;"` ;;`     
 `		  ,;;"` ..     :;"  ":: ;;   Copyright (c) 2000,Cloud Wu (2000/12/19)
	   .,;;;;;;;;;:    ::...;;` ;"                               (2001/11/30)
	,;;;;;;;;;;"`      :""":;;. :.      http://member.netease.com/~cloudwu 
	 '""`.;;":;;.     ;;..;;":;;:.`.        __      mailto:cloudwu@263.net
	   .;;;;;;;;;;   :;;""`   "";;,':.     /_  _/_      __/ . __
		;;""   ';;   '`          ';;;;:   __/  /_  /_/ /_/ / /_/
 
.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*/
#ifdef WIN32

#include <windows.h>

#define VSPRINTF wvsprintf

#else

#include <stdio.h>

#define VSPRINTF vsprintf

#endif

#include <stdarg.h>
#include "windsoul.h"
#include "wsstring.h"

#ifndef _DISABLE_WINDSOUL_NEW
	#define new debug_new
#endif

struct STRING_DATA {
	unsigned len;					// 长度
	unsigned max_len;				// 最长长度
	mutable unsigned times;			// 引用次数
	STRING_DATA (unsigned max) : max_len(max) {}
};

inline const STRING_DATA &WString::GetData() const 
{
	return *(reinterpret_cast<const STRING_DATA *>(str)-1); 
}

inline STRING_DATA &WString::GetData() { 
	return *(reinterpret_cast<STRING_DATA *>(str)-1); 
}

#ifndef _LIB
	inline
#endif

int WString::GetLength() const 
{ 
	return GetData().len; 
}

struct STR64 : public memory<STR64> {
	STRING_DATA data;
	char str[64];
	STR64() : data(63) {}
};

struct STR128 : public memory<STR128> {
	STRING_DATA data;
	char str[128];
	STR128() : data(127) {}
};

struct STR256 : public memory<STR256> {
	STRING_DATA data;
	char str[256];
	STR256() : data(255) {}
};

struct STR_NOLIMIT {
	STRING_DATA data;
	char str[512];
	STR_NOLIMIT() : data(511) {}
};

struct STR_EMPTY {
	int used;
	STRING_DATA data;
	char str[1];
	STR_EMPTY() : data(0) { data.len=0,data.times=0; str[0]='\0'; }
};

static STR_EMPTY _str_empty;
char *WString::_emptystr=_str_empty.str;

static inline void _str_clear(STRING_DATA &str_data)
{
	switch (str_data.times) {
	case 0: return;
	case 1:
		if (str_data.max_len>255) {
			delete &str_data;
		}
		else {
			switch (str_data.max_len) {
			case 63:
				delete ((STR64*)&str_data);
				break;
			case 127:
				delete ((STR128*)&str_data);
				break;
			case 255:
				delete ((STR256*)&str_data);
				break;
			default:
				assert(0);
				break;
			}
		}
		break;
	default:
		--str_data.times;
		break;
	}
}

static inline unsigned _strlen(const char *s)
{
    int i;
	for (i=0;s[i];i++) ;
	return i;
}

static inline void _strncpy(const char *from,char *to,unsigned len)
{
	unsigned i;
	const unsigned long *p1=reinterpret_cast<const unsigned long*>(from);
	unsigned long *p2=(unsigned long*)to;
	for (i=0;i<len/4;i++,p1++,p2++) *p2=*p1;
	for (i*=4;i<len;i++) to[i]=from[i];
	to[i]=0;
}

// 比较字符串是否相等 (相等 true)
static inline bool _strequ(const char *s1,const char *s2,unsigned len)
{
	unsigned i;
	const unsigned long *p1=(const unsigned long *)s1;
	const unsigned long *p2=(const unsigned long *)s2;
	for (i=0;i<len/4;i++,p1++,p2++) {
		if (*p1!=*p2) return false;
	}
	for (i*=4;i<len;i++) if (s1[i]!=s2[i]) return false;
	return true;
}

// 分配一块内存给字符串使用
static char * __fastcall _stralloc(unsigned len)
{
	if (len<64) {
		STR64 *p=new STR64;
		p->data.len=len,
		p->data.times=1;
		p->data.max_len=63;
		return p->str;
	}
	else if (len<128) {
		STR128 *p=new STR128;
		p->data.len=len,
		p->data.times=1;
		p->data.max_len=127;
		return p->str;
	}
	else if (len<256) {
		STR256 *p=new STR256;
		p->data.len=len,
		p->data.times=1;
		p->data.max_len=255;
		return p->str;
	}
	else {
		unsigned max_len;
		if (len<0x400) max_len=0x400;
		else if (len<0x1000) max_len=0x1000;
		else if (len<0x4000) max_len=0x4000;
		else if (len<0x10000) max_len=0x10000;
		else max_len=(len/0x40000+1)*0x40000;
		STR_NOLIMIT *p=(STR_NOLIMIT *)new char[sizeof(STR_NOLIMIT)-512+max_len];
		p->data.len=len;
		p->data.max_len=max_len-1;
		p->data.times=1;
		return p->str;
	}
}

// 复制一个长度为 len 的 const char *
static inline char *  _strdup(const char *s,unsigned len)
{
	if (len>0) {
		char *str=_stralloc(len);
		_strncpy(s,str,len);
		return str;
	}
	return _str_empty.str;
}

// 复制一个长度为 len-1 的 const char * 并把 char c 连接到后面
static inline char * _strdup(const char *s,char c,unsigned len)
{
	if (c==0) {
		return _strdup(s,len-1);
	}
	char *str=_stralloc(len);
	_strncpy(s,str,len-1);
	str[len-1]=c;
	str[len]=0;
	return str;
}

static inline char * _strdup(char c,const char *s,unsigned len)
{
	if (c==0) {
		return _str_empty.str;
	}
	char *str=_stralloc(len);
	str[0]=c;
	_strncpy(s,str+1,len-1);
	return str;
}

// 连接一个长度为 len1 和一个长度为 len2 的 string
static inline char * _strdup(const char *s1,const char *s2,unsigned len1,unsigned len2)
{
	if (len2==0) {
		return _strdup(s1,len1);
	}
	unsigned len=len1+len2;
	char *str=_stralloc(len);
	_strncpy(s1,str,len1);
	_strncpy(s2,str+len1,len2);
	return str;
}

WString::WString(unsigned max_len)
{
	if (max_len==0) {
		str=_emptystr;
	}
	else {
		str=_stralloc(max_len);
	}
}

WString::WString(char c)
{
	if (c==0) {
		str=_emptystr;
		return;
	}
	STR64 *p=new STR64;
	p->data.len=p->data.times=1;
	str=p->str;
	str[0]=c,str[1]=0;
}

WString::WString(const char *s)
{
	int len=_strlen(s);
	str=_strdup(s,len);
}

WString::WString(const WString &s)
{
	if (s.IsEmpty()) { str=_emptystr; return; }
	const STRING_DATA &str_data=s.GetData();
	str=s.str;
	++str_data.times;
}

WString::WString(const WString &s,char c)
{
	str=_strdup(s.str,c,s.GetLength()+1);
}

WString::WString(char c,const WString &s)
{
	str=_strdup(c,s.str,s.GetLength()+1);
}

WString::WString(const WString &s1,const char *s2)
{
	str=_strdup(s1.str,s2,s1.GetLength(),_strlen(s2));
}

WString::WString(const char *s1,const WString &s2)
{
	str=_strdup(s1,s2.str,_strlen(s1),s2.GetLength());
}

WString::WString(const WString &s1,const WString &s2)
{
	str=_strdup(s1.str,s2.str,s1.GetLength(),s2.GetLength());
}

WString::WString(const char *s,unsigned len)
{
	str=_strdup(s,len);
}

WString::~WString()
{
	_str_clear(GetData());
	str=_emptystr;
}

void WString::Empty()
{
	STRING_DATA &str_data=GetData();
	_str_clear(str_data);
	str=_emptystr;
}

WString & WString::operator=(char c)
{
	if (c==0) {
		Empty();
		return *this;
	}
	STRING_DATA &str_data=GetData();
	if (str_data.times>1) {
		--str_data.times;
		STR64 *p=new STR64;
		p->data.len=p->data.times=1;
		p->str[0]=c,p->str[1]=0;
		str=p->str;
	}
	else if (str==_emptystr) {
		STR64 *p=new STR64;
		p->data.len=p->data.times=1;
		p->str[0]=c,p->str[1]=0;
		str=p->str;
	}
	else {
		str_data.len=1;
		str[0]=c,str[1]=0;
	}
	return *this;
}

WString & WString::operator=(const char *s)
{
	unsigned len=_strlen(s);
	if (len==0) {
		Empty();
		return *this;
	}
	STRING_DATA &str_data=GetData();
	if (str_data.times>1) {
		--str_data.times;
		str=_strdup(s,len);
	}
	else {
		unsigned len=_strlen(s);
		if (len<=str_data.max_len) {
			_strncpy(s,str,len);
			str_data.len=len;
		}
		else {
			_str_clear(str_data);
			str=_strdup(s,len);
		}
	}
	return *this;
}

WString & WString::operator=(const WString &s)
{
	if (str==s.str) return *this;
	if (s.IsEmpty()) { 
		_str_clear(GetData()); 
		str=_emptystr; 
		return *this; 
	}
	const STRING_DATA &str_data=s.GetData();
	if (str_data.times==(unsigned)-1) {		// 如果被 Lock
		STRING_DATA &thisstr_data=GetData();
		if (thisstr_data.times>1) {
			--thisstr_data.times;
			str=_strdup(s.str,str_data.len);
		}
		else {
			if (str_data.len<=thisstr_data.max_len) {
				_strncpy(s.str,str,str_data.len);
				thisstr_data.len=str_data.len;
			}
			else {
				_str_clear(thisstr_data);
				str=_strdup(s.str,str_data.len);
			}
		}
	}
	else {
		_str_clear(GetData());
		++str_data.times;
		str=s.str;
	}
	return *this;
}

WString & WString::operator+=(char c)
{
	if (c==0) return *this;
	STRING_DATA &str_data=GetData();
	if (str_data.times>1) {
		--str_data.times;
		str=_strdup(str,c,str_data.len+1);
		return *this;
	}
	unsigned len=str_data.len+1;
	if (len<=str_data.max_len) {
		str[len-1]=c,str[len]=0;
		++str_data.len;
	}
	else {
		str=_strdup(str,c,len);
		_str_clear(str_data);
	}
	return *this;
}

WString & WString::operator+=(const char *s)
{
	unsigned len2=_strlen(s);
	if (len2==0) return *this;
	STRING_DATA &str_data=GetData();
	if (str_data.times>1) {
		--str_data.times;
		str=_strdup(str,s,str_data.len,len2);
		return *this;
	}
	unsigned len=str_data.len+len2;
	if (len<=str_data.max_len) {
		_strncpy(s,str+str_data.len,len2);
		str_data.len=len;
	}
	else {
		str=_strdup(str,s,str_data.len,len2);
		_str_clear(str_data);
	}
	return *this;
}

WString & WString::operator+=(const WString &s)
{
	unsigned len2=s.GetLength();
	if (len2==0) return *this;
	STRING_DATA &str_data=GetData();
	if (str_data.times>1) {
		--str_data.times;
		str=_strdup(str,s,str_data.len,len2);
		return *this;
	}
	unsigned len=str_data.len+len2;
	if (len<=str_data.max_len) {
		_strncpy(s.str,str+str_data.len,len2);
		str_data.len=len;
	}
	else {
		str=_strdup(str,s,str_data.len,len2);
		_str_clear(str_data);
	}
	return *this;
}

// 取得第 id 个字符的引用
char & WString::operator[](int id)
{
	STRING_DATA &str_data=GetData();
	if (str_data.times>1) {
		--str_data.times;
		str=_strdup(str,GetLength());
		ASSERT(id>=0 && id<=GetLength());
	}
	return str[id];
}

bool WString::operator==(const char *s) const
{
	unsigned len=GetLength();
	return _strequ(str,s,len+1);
}

bool WString::operator==(const WString &s) const
{
	int len=GetLength();
	if (len!=s.GetLength()) return false;
	if (s.str==str) return true;
	return _strequ(str,s.str,len);
}

int WString::Compare(const char *s2) const
{
	unsigned i,len=GetLength();
	const unsigned char *s1=(const unsigned char *)str;
	const unsigned char *s=(const unsigned char *)s2;
	if (s1==s) return 0;
	for (i=0;i<=len;i++,s1++,s++) {
		if (*s1<*s) return -1;
		else if (*s1>*s) return 1;
	}
	return 0;
}

int WString::CompareNoCase(const char *s2) const
{
	unsigned i,len=GetLength();
	const unsigned char *s1=(const unsigned char *)str;
	const unsigned char *s=(const unsigned char *)s2;
	if (s1==s) return 0;
	for (i=0;i<=len;i++,s1++,s++) {
		if (*s1==*s) continue;
		if ( ((*s1>='A' && *s1<='Z') && *s1==*s-('a'-'A')) ||
			((*s1>='a' && *s1<='z') && *s1==*s+('a'-'A')) ) continue;
		if (*s1<*s) return -1;
		else return 1;
	}
	return 0;
}

void WString::MakeUpper()
{
	unsigned i,len=GetLength();
	char *s=str;
	for (i=0;i<=len;i++,s++) {
		if (*s>='a' && *s <='z') *s-=('a'-'A');
	}
}

void WString::MakeLower()
{
	unsigned i,len=GetLength();
	char *s=str;
	for (i=0;i<=len;i++,s++) {
		if (*s>='A' && *s <='Z') *s+=('a'-'A');
	}
}

// 得到 Buffer, 设置最小需要的长度
char *WString::GetBuffer(int minlen)
{
	STRING_DATA &str_data=GetData();
	if (str_data.times>1) {
		--str_data.times;
		str=_stralloc(minlen);
	}
	else {
		if ((unsigned)minlen<=str_data.max_len) {
			str_data.len=minlen;
		}
		else {
			_str_clear(str_data);
			str=_stralloc(minlen);
		}
	}
	return str;
}

// 释放 Buffer, 设置新长度
void WString::ReleaseBuffer()
{
	STRING_DATA &str_data=GetData();
	str_data.len=_strlen(str);	
}

// lock 住 Buffer, 不能被引用
char *WString::LockBuffer()
{
	ASSERT(!IsEmpty());
	STRING_DATA *str_data=&GetData();
	if (str_data->times>1) {
		char *p;
		unsigned len=str_data->len;
		--str_data->times;
		p=_strdup(str,len);
		str=p;
		str_data=&GetData();
	}
	str_data->times=(unsigned)-1;
	return str;
}

// unlock 引用住的 Buffer
void WString::UnlockBuffer()
{
	STRING_DATA &str_data=GetData();
	str_data.len=_strlen(str);
	str_data.times=1;
}

inline int _atoi(const char *str)
{
	const char *s=str;
	int r=0;
	if (s[0]=='+') ++s;
	if (s[0]=='-') {
		for (int i=1;s[i]>='0' && s[i]<='9';i++) r=r*10+(s[i]-'0');
		return -r;
	}
	for (int i=0;s[i]>='0' && s[i]<='9';i++) r=r*10+(s[i]-'0');
	return r;
}

int WString::AsInt() const
{
	return _atoi(str);
}

static unsigned _format_len(const char *format,va_list argList)
{
	unsigned len = 0;
	for (const char *lpsz = format; *lpsz != '\0'; ++lpsz) {
		// 找到 '%', (避开 "%%")
		if (*lpsz != '%' || *(++lpsz) == '%') {
			++len;
			continue;
		}

		int item_len = 0;
		int width = 0;
		for (; *lpsz != '\0'; ++lpsz)
		{
			if (*lpsz == '#')
				len += 2;   // '0x'
			else if (*lpsz == '*')
				width = va_arg(argList, int);
			else if (*lpsz != '-' && *lpsz != '+' && *lpsz != '0' && *lpsz != ' ') break;
		}

		if (width == 0)
		{
			width = _atoi(lpsz);
			for (; *lpsz != '\0' && (*lpsz>='0' && *lpsz<='9'); ++lpsz)	;
		}

		int width2 = 0;
		if (*lpsz == '.')
		{
			++lpsz;

			if (*lpsz == '*')
			{
				width2 = va_arg(argList, int);
				++lpsz;
			}
			else
			{
				width2 = _atoi(lpsz);
				for (; *lpsz != '\0' && (*lpsz>='0' && *lpsz<='9'); ++lpsz)	;
			}
		}

		// 去掉长度修饰
		switch (*lpsz) {
		case 'h':
		case 'l':
		case 'F':
		case 'N':
		case 'L':
			++lpsz;
			break;
		}

		switch (*lpsz) {
		case 'c':
		case 'C':
			item_len=2;
			va_arg(argList, char);
			break;

		case 's':
		case 'S':
			{
				const char * nextstr = va_arg(argList, const char *);
				if (nextstr == 0) item_len = 6;  // "(null)"
				else item_len = (nextstr[0]=='\0')?1:_strlen(nextstr);
			}
			break;
		}

		if (item_len != 0) {
			if (width2 != 0) {
				if (width2<item_len) item_len=width2;
			}
			if (width>item_len) item_len=width;
		}
		else {
			switch (*lpsz)
			{
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
				va_arg(argList, int);
				item_len = (32>width+width2)?32:width+width2;
				break;

			case 'e':
			case 'g':
			case 'G':
			case 'f':
#ifdef WIN32
				OutputDebugString("wsprintf doesn't support float\n");
				exit(WS_FLOATPOINT);
#endif
				va_arg(argList, double);
				item_len = (128>width+width2)?128:width+width2;
				break;

			case 'p':
				va_arg(argList, void*);
				item_len = (32>width+width2)?32:width+width2;
				break;

			// no output
			case 'n':
				va_arg(argList, int*);
				break;

			}
		}

		len+=item_len;
	}
	return len;
}

/*
#include <stdio.h>

#define VSPRINTF vsprintf
*/


WString& WString::Format(const char *format, ...)
{
	unsigned max_len;
	STRING_DATA &str_data=GetData();
	va_list argList;
	va_start(argList, format);
	max_len=_format_len(format,argList);

	if (str_data.times>1)
		--str_data.times;
	else if (max_len<=str_data.max_len) {
			VSPRINTF(str,format,argList);
			str_data.len=_strlen(str);
			va_end(argList);
			return *this;
		}
	else _str_clear(str_data);
	str=_stralloc(max_len);
	VSPRINTF(str,format,argList);
	STRING_DATA &newstr_data=GetData();
	newstr_data.len=_strlen(str);
	va_end(argList);
	return *this;
}
