/*
 "		   .....            ,;;;;;.           [ String Class v1.0 ]
 '		  ":;;;;`     ....;;;"` ;;`                  (风魂版)
 `		  ,;;"` ..     :;"  ":: ;;   Copyright (c) 2000,Cloud Wu (2000/11/17)
	   .,;;;;;;;;;:    ::...;;` ;"    
	,;;;;;;;;;;"`      :""":;;. :.      http://member.netease.com/~cloudwu 
	 '""`.;;":;;.     ;;..;;":;;:.`.        __      mailto:cloudwu@263.net
	   .;;;;;;;;;;   :;;""`   "";;,':.     /_  _/_      __/ . __
		;;""   ';;   '`          ';;;;:   __/  /_  /_/ /_/ / /_/
 
.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*/

#ifndef _WSTRING_H
#define _WSTRING_H
 
struct STRING_DATA;
  
class WINDSOUL_API WString {
	char *str;
static char *_emptystr;
protected:
	const STRING_DATA &GetData() const;
	STRING_DATA &GetData();
	WString(const WString &s,char c);
	WString(char c,const WString &s);
	WString(const WString &s1,const char *s2);
	WString(const char *s1,const WString &s2);
	WString(const WString &s1,const WString &s2);
	WString(const char *s,unsigned len);
public:
	WString() : str(_emptystr) {}
	WString(char c);
	WString(const char *s);
	WString(const WString &s);
	WString(unsigned max_len);			// 分配至少 max_len 的空间
	~WString();

	WString & operator=(char c);
	WString & operator=(const char *s);
	WString & operator=(const WString &s);
 
	WString & operator+=(char c);
	WString & operator+=(const char *s);
	WString & operator+=(const WString &s);
 
	WString operator+(char c) const { return WString(*this,c); }
	WString operator+(const char *s) const { return WString(*this,s); }
	WString operator+(const WString &s) const { return WString(*this,s); }
	friend inline WString operator+(char c,WString &s) { return WString(c,s); }
	friend inline WString operator+(const char *s1,WString &s2) { return WString(s1,s2); }

	int Compare(const char *s) const;
	int CompareNoCase(const char *s) const;

	bool operator==(char c) const { return (str[0]==c && GetLength()==1); }
	bool operator==(const char *s) const;
	bool operator==(const WString &s) const;

	bool operator!=(char c) const { return (str[0]!=c || GetLength()!=1); }
	bool operator!=(const char *s) const { return !((*this)==s); }
	bool operator!=(const WString &s) const { return !((*this)==s); }

	bool operator>(char c) const { return (str[0]>c || (str[0]==c && GetLength()>1)); }
	bool operator<(char c) const { return (str[0]<c || IsEmpty()); }

	bool operator>(const char *s) const { return Compare(s)>0; }
	bool operator<(const char *s) const { return Compare(s)<0; }

	bool operator>=(char c) const { return !((*this)<c); }
	bool operator<=(char c) const { return !((*this)>c); }
	char operator[](int id) const { ASSERT(id>=0 && id<=GetLength()); return str[id]; }	// 取得第 id 个字符
	char &operator[](int id);							// 取得第 id 个字符的引用

	int GetLength() const;								// 取得长度
	bool IsEmpty() const { return (str==_emptystr); }	// 是否为空
	void Empty();										// 清空
	operator const char*() const { return str; }

	WString operator()(int left) const;					// 取左串
	WString operator()(int from,int len) const;			// 取中串
	WString Left(int left) const;						// 取左串
	WString Mid(int from,int len=-1) const;				// 取中串
	WString Right(int right) const;						// 取右串

	void MakeUpper();									// 变为大写
	void MakeLower();									// 变为小写

	int AsInt() const;									// 转化为 int

	WString &Format(const char *format, ...);				// sprintf

	char *GetBuffer(int minlen);						// 得到 Buffer(数据可能破坏), 设置最小需要的长度
	void ReleaseBuffer();								// 释放 Buffer, 设置新长度
	
	char *LockBuffer();									// lock 住 Buffer(数据不破坏), 不能被引用
	void UnlockBuffer();								// unlock 不能被引用的 Buffer
};

inline WString WString::Left(int left) const
{
	return (*this)(left); 
}

inline WString WString::Mid(int from,int len) const
{
	return (*this)(from,len); 
}

inline WString WString::operator()(int left) const {
	int len=GetLength(); 
	return WString(str,(unsigned)(len<left?len:left)); 
}

inline WString WString::operator()(int from,int len) const {
	int thislen=GetLength()-from; 
	if (thislen<=0) return WString();
	return WString(str+from,((unsigned)thislen<(unsigned)len?(unsigned)thislen:(unsigned)len));
}

inline WString WString::Right(int right) const
{
	int from=GetLength()-right;
	return (*this)((from>0)?from:0,-1);
}

inline bool operator==(char c,const WString &s) { return (s[0]==c && s.GetLength()==1); }
inline bool operator!=(char c,const WString &s) { return (s[0]!=c || s.GetLength()!=1); }
inline bool operator<(char c,const WString &s) { return (s>c); }
inline bool operator>(char c,const WString &s) { return (s<c); }
inline bool operator<=(char c,const WString &s) { return !(s<c); }
inline bool operator>=(char c,const WString &s) { return !(s>c); }

inline bool operator==(const char *s1,const WString &s2) { return s2.operator==(s1); }
inline bool operator!=(const char *s1,const WString &s2) { return s2.operator!=(s1); }
inline bool operator<(const char *s1,const WString &s2) { return (s2>s1); }
inline bool operator>(const char *s1,const WString &s2) { return (s2<s1); }
inline bool operator<=(const char *s1,const WString &s2) { return !(s2<s1); }
inline bool operator>=(const char *s1,const WString &s2) { return !(s2>s1); }

#endif