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

		Description:		风魂++ 出错信息的定义
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/12
		Modify Time:		2001/5/25

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_ERROR_H
#define _WINDSOUL_ERROR_H

#define MAKE_ERR(fac,code) (((int)fac)<<24|((int)code))
#ifdef _BCB
	#define WSERR_STRING(e) e&0xff,(e>>8)&0xff,(e>>16)&0xff,(e>>24)&0xff
#else
	#define WSERR_STRING(e) (e>>24)&0xff,(e>>16)&0xff,(e>>8)&0xff,e&0xff
#endif

// #define _ERR_GRAPH	'_GRP'
#define _ERR_BMP 'b'
#define _ERR_GDI 'g'
#define _ERR_MEM 'm'
#define _ERR_FILE 'f'
#define _ERR_SYSTEM 's'
#define _ERR_DDRAW 'd'
#define _ERR_CHAR 'c'

#define WS_OK (0L)
#define WS_GDIBLITFAIL MAKE_ERR(_ERR_GDI,'BLT')
#define WS_INVALIDBMPTYPE MAKE_ERR(_ERR_BMP,'TYP')
#define WS_INVALIDBMPFILE MAKE_ERR(_ERR_BMP,'FIL')
#define WS_UNSUPPORTBLITTYPE MAKE_ERR(_ERR_BMP,'UBT')
#define WS_CANTCREATEBITMAP MAKE_ERR(_ERR_BMP,'CRT')
#define WS_CANTBLIT MAKE_ERR(_ERR_BMP,'BLT')
#define WS_NULLBITMAP MAKE_ERR(_ERR_BMP,'NUL')
#define WS_CANTOPEN MAKE_ERR(_ERR_FILE,'OPN')
#define WS_CANTREAD MAKE_ERR(_ERR_FILE,'RED')
#define WS_MEMDELETEFAIL MAKE_ERR(_ERR_MEM,'DEL')
#define WS_FLOATPOINT MAKE_ERR(_ERR_SYSTEM,'flt')
#define WS_CREARTSURFACEFAIL MAKE_ERR(_ERR_DDRAW,'CRT')
#define WS_CREATEDDRAWFAIL MAKE_ERR(_ERR_DDRAW,'DRW')
#define WS_CANTCREATECHAR MAKE_ERR(_ERR_CHAR,'CRT')
#define WS_CANTCREATEFONT MAKE_ERR(_ERR_CHAR,'FNT')
#define WS_ERRORCHAR MAKE_ERR(_ERR_CHAR,'ERR')

#endif