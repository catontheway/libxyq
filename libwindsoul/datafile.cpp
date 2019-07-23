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

		Description:		风魂++ 数据文件管理
 		Original Author:	云风
		Authors:
		Create Time:		2000/10/16
		Modify Time:		2001/12/26

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>
#include "windsoul.h"
#include "string.h"
#include "wsfile.h"
#define new debug_new

extern "C" DWORD _stdcall _string2id(const char* string);
#define MAXDATAFILE 64

#ifdef _BCB

DWORD _stdcall WString2ID(const char* string)
{
	return (_string2id(string));
}

#else

__declspec( naked ) DWORD _stdcall WString2ID(const char* string)
{
	__asm jmp _string2id;
}

__declspec( naked ) __int64 _stdcall WString2LID(const char* string)
{
	__asm jmp _string2id;
}

#endif

static DWORD string_id(const char *filename)
{
	char buffer[256];
	int i;
	for (i=0;filename[i];i++) {
		if (filename[i]>='A' && filename[i]<='Z') buffer[i]=filename[i]+'a'-'A';
		else if (filename[i]=='/') buffer[i]='\\';
		else buffer[i]=filename[i];
	}
	buffer[i]=0;
	return WString2ID(buffer);
}

struct WDataFileIndex {
	DWORD uid;
	DWORD offset;
	DWORD size;
	DWORD space;
};

struct WDataFileHeader {
	DWORD id;
	int number;
	unsigned offset;
};

class WDataFile {
	HANDLE m_File;
	WDataFileIndex *m_Index;
	DWORD m_Id;
	int m_Number;
public:
	WDataFile() : m_Index(0), m_File(INVALID_HANDLE_VALUE), m_Id(0) {}
	~WDataFile();
	WSERR Open(const char *name,DWORD id);
	void Close();
	bool IsOpen(DWORD id) const { return m_Id==id; }
	bool IsValid() const { return m_File!=INVALID_HANDLE_VALUE; }
	WDataFileIndex* SearchFile(DWORD id) const;
	HANDLE GetFileHandle() const { return m_File; }
};

class wdf_files {
	WDataFile _WDF[MAXDATAFILE];
public:
	static WDataFile& instance(int idx);
};

WDataFile& wdf_files::instance(int idx)
{
	static wdf_files __inst;
	return __inst._WDF[idx];
}

//static WDataFile _WDF[MAXDATAFILE];

WDataFile::~WDataFile()
{
	Close();
}

void WDataFile::Close()
{
	if (m_File!=INVALID_HANDLE_VALUE) {
		CloseHandle(m_File);
	}
	if (m_Index!=0) {
		WFree(m_Index);
		m_Index=0;
	}
	m_Id=0;
}

WDataFileIndex* WDataFile::SearchFile(DWORD id) const
{
	int begin,end,middle;
	begin=0,end=m_Number-1;
	while (begin<=end) {
		middle=(begin+end)/2;
		if (m_Index[middle].uid==id) return &m_Index[middle];
		else if (m_Index[middle].uid<id) begin=middle+1;
		else end=middle-1;
	}
	return 0;
}

WSERR WDataFile::Open(const char *filename,DWORD id)
{
	HANDLE f;
	WDataFileHeader header;
	DWORD bytes;
	if (m_File!=INVALID_HANDLE_VALUE) {
		Close();
	}
	f=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if (f==INVALID_HANDLE_VALUE)
		return WS_DATAFILECANTOPEN;
	if (ReadFile(f,&header,sizeof(header),&bytes,0)==0) {
		CloseHandle(f);
		return WS_INVALIDDATAFILE;
	}
	if (header.id!='WDFP') {
		CloseHandle(f);
		return WS_INVALIDDATAFILE;
	}
	m_Index=(WDataFileIndex*)WAlloc(sizeof(WDataFileIndex)*header.number);
	SetFilePointer(f,header.offset,0,FILE_BEGIN);
	if (ReadFile(f,m_Index,sizeof(WDataFileIndex)*header.number,&bytes,0)==0) {
		CloseHandle(f);
		WFree(m_Index);
		return WS_INVALIDDATAFILE;
	}
	m_Number=header.number;
	m_File=f;
	m_Id=id;
	return WS_OK;
}

// 打开数据包 (.wdf)
WSERR WFile::OpenDataFile(const char *filename)
{
	int i;
	DWORD id=string_id(filename);

	for (i=0;i<MAXDATAFILE && wdf_files::instance(i).IsValid();i++) {
		if (wdf_files::instance(i).IsOpen(id)) return WS_OK;
	}
	for (i=0;i<MAXDATAFILE;i++) {
		if (!wdf_files::instance(i).IsValid()) {
			return wdf_files::instance(i).Open(filename,id);
		}
	}
	return WS_DATAFILECANTOPEN;
}

WFile::WFile() : m_Ptr(0), m_Offset(0), m_File(0), m_Size(0)
{
	m_File=INVALID_HANDLE_VALUE;
}

static DWORD pack_name(const char *filename,int number=0)
{
	char buffer[256];
	char ext[5]=".wdf";
	if (number>0) {
		ext[3]='0'+number;
	}
	int i;
	for (i=0;filename[i];i++) {
		if (filename[i]=='/') {
			WMemCpy(buffer+i,ext,5);
			break;
		}
		if (filename[i]>='A' && filename[i]<='Z') buffer[i]=filename[i]+'a'-'A';
		else buffer[i]=filename[i];
	}
	if (i==0) return 0;
	return WString2ID(buffer);
}

static DWORD real_name(const char *filename)
{
	int i;
	for (i=0;filename[i];i++) {
		if (filename[i]=='/') {
			return string_id(filename+i+1);
		}
	}
	return 0;
}

WSERR WFile::Load(const char *filename)
{
	HANDLE f;
	DWORD bytes;
	f=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if (f==INVALID_HANDLE_VALUE) {
		DWORD fid=real_name(filename);
		int i, j;
		for (/*int */i=0;i<10;i++) {
			DWORD id=pack_name(filename,i);
			WDataFileIndex * pf;
			for (/*int */j=0;j<MAXDATAFILE;j++) {
				if (wdf_files::instance(j).IsOpen(id)) {
					pf=wdf_files::instance(j).SearchFile(fid);
					if (pf==0) {
						goto _continue;
					}
					f=wdf_files::instance(j).GetFileHandle();
					m_Offset=pf->offset;
					m_Size=pf->size;
					SetFilePointer(f,m_Offset,0,FILE_BEGIN);
					goto _break;
				}
			}
			if (j==MAXDATAFILE) return WS_CANTOPEN;
_continue:
			;
		}
		if (i==10) {
			return WS_CANTOPEN;
		}
_break:
		;
	}
	else {
		m_Offset=0;
		m_Size=GetFileSize(f,0);
	}
		
	if (m_Ptr) WFree(m_Ptr);
	m_Ptr=WAlloc(m_Size+1);

	if (ReadFile(f,m_Ptr,m_Size,&bytes,0)==0) {
		WFree(m_Ptr);
		m_Ptr=0;
		if (m_Offset==0) CloseHandle(f);
		return WS_CANTREAD;
	}
	((char *)m_Ptr)[m_Size]=0;

	if (m_Offset==0) CloseHandle(f);
	return WS_OK;
}

WFile::~WFile()
{
	Close();
	if (m_Ptr) 
		WFree(m_Ptr);
	m_Ptr=0;
}

WSERR WFile::Open(const char *filename)
{
	HANDLE f;
	f=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if (f==INVALID_HANDLE_VALUE) {
		DWORD fid=real_name(filename);
		int i, j;
		for (/*int */i=0;i<10;i++) {
			DWORD id=pack_name(filename,i);
			WDataFileIndex * pf;
			for (/*int */j=0;j<MAXDATAFILE;j++) {
				if (wdf_files::instance(j).IsOpen(id)) {
					pf=wdf_files::instance(j).SearchFile(fid);
					if (pf==0) {
						goto _continue;
					}
					m_File=wdf_files::instance(j).GetFileHandle();
					m_Offset=pf->offset;
					m_Size=pf->size;
					SetFilePointer(m_File,m_Offset,0,FILE_BEGIN);
					goto _break;
				}
			}
			if (j==MAXDATAFILE) return WS_CANTOPEN;
_continue:
			;
		}
		if (i==10) {
			return WS_CANTOPEN;
		}
_break:
		;
	}
	else {
		m_Offset=0;
		m_Size=GetFileSize(f,0);
		m_File=f;
	}
	return WS_OK;
}

void WFile::Close()
{
	if (m_Offset==0) {
		if (m_File!=INVALID_HANDLE_VALUE) {
			CloseHandle(m_File);
		}
	}
	else m_Offset=0;
	m_File=INVALID_HANDLE_VALUE;
}

WSERR WFile::Read(void *buffer,int s,int offset,int *read)
{
	ASSERT(m_File!=INVALID_HANDLE_VALUE);
	s=MIN(s,(int)(m_Size-offset));
//	ASSERT((unsigned)(offset+s)<=m_Size);
	DWORD bytes;
	SetFilePointer(m_File,m_Offset+offset,0,FILE_BEGIN);
	if (s==0) {
		if (read) *read=0;
		return WS_OK;
	}
	if (ReadFile(m_File,buffer,s,&bytes,0)==0) {
//		CloseHandle(m_File);
//		m_File=INVALID_HANDLE_VALUE;
		return WS_CANTREAD;
	}
	if (read) *read=bytes;
	return WS_OK;
}

DWORD WFile::Tell() const 
{
	DWORD r;
	ASSERT(m_File!=INVALID_HANDLE_VALUE);
	r=SetFilePointer(m_File,0,0,FILE_CURRENT);
	return r-m_Offset;
}

void WFile::Skip(int s)
{
	ASSERT(m_File!=INVALID_HANDLE_VALUE);
	SetFilePointer(m_File,s,0,FILE_CURRENT);
}

WSERR WFile::Read(void *buffer,int s,int *read)
{
	ASSERT(m_File!=INVALID_HANDLE_VALUE);
	DWORD bytes,r;
//	SetFilePointer(m_File,m_Offset,0,FILE_BEGIN);
	if (read) {
		r=SetFilePointer(m_File,0,0,FILE_CURRENT);
		s=MIN(s,(int)(m_Size-(r-m_Offset)));
	}
	if (ReadFile(m_File,buffer,s,&bytes,0)==0) {
//		CloseHandle(m_File);
//		m_File=INVALID_HANDLE_VALUE;
		return WS_CANTREAD;
	}
	if (read) *read=bytes;
	return WS_OK;
}
