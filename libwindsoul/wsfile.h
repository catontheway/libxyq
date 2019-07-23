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

		Description:		风魂文件处理头文件
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/14
		Modify Time:		2001/10/10

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_FILE_H
#define _WINDSOUL_FILE_H

 ///	数据文件
//////////////////////

#define WS_DATAFILECANTOPEN MAKE_ERR(_ERR_FILE,'DAT')
#define WS_INVALIDDATAFILE MAKE_ERR(_ERR_FILE,'DAH')

class WINDSOUL_API WFile {
protected:
	void *m_Ptr;
	DWORD m_Offset;
	HANDLE m_File;
	DWORD m_Size;
public:
	WFile();
	virtual ~WFile();
	static WSERR OpenDataFile(const char *filename);	// 打开数据包 (.wdf)
	WSERR Load(const char *filename);	// 加载一个文件
	operator void *() const { return m_Ptr; }
	void *GetPtr() { return m_Ptr; }		// 读数据指针
	void *GetPtr(int offset) { return (void*)((unsigned)m_Ptr+offset); }
	WSERR Open(const char *filename);	// 打开一个文件
	WSERR Read(void *buffer,int s,int offset,int *read=0);	// 读数据到指定 Buffer
	void Skip(int s);					// 跳过 s 字节
	WSERR Read(void *buffer,int s,int *read=0);		// 读数据到指定 Buffer
	DWORD GetSize() { return m_Size; }	// 取文件长度
	DWORD Tell() const;					// 取文件指针
	void Close();
	bool IsEnd() const { return Tell()>=m_Size; }	// 是否到文件尾
};

#endif
