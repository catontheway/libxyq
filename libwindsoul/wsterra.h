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

		Description:		椭圆地面
 		Original Author:	云风
		Authors:
		Create Time:		2001/7/26
		Modify Time:		2001/7/31 

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
       
#ifndef _WINDSOUL_TERRA_H
#define _WINDSOUL_TERRA_H
 
#include "wsaddon.h"  
         
struct WTerraStruct;
class WSprite;    
   
class WINDSOULADD_API WTerra : public WObject {
public:      
	WTerra();
	~WTerra();

	WSERR Bind(const WSprite &sprite);
	void Bind(const WBitmap &bmp,int x,int y);

	int GetW() const;
	int GetH() const;
  
	BLIT_FUNC DrawFunc(DWORD style) const;	// 获得 Draw 函数指针
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WTerraStruct *GetTerraStruct() const { return reinterpret_cast<WTerraStruct *>(objdata); }	// 获取数据结构
};    
          
#endif
