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

                  基于 DirectX 的游戏程序库               
        A Game Programming Library Base On DirectX    
  
                by 云风 (Cloud Wu)  1999-2000                          
 
		http://member.netease.com/~cloudwu 
		mailto:cloudwu@263.net
 
		请阅读 readme.txt 中的版权信息
		See readme.txt for copyright information.

		Description:		风魂对象内部头文件
 		Original Author:	云风
		Authors:
		Create Time:		2000/1/2
		Modify Time:

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef WINDSOUL_OBJECT_INTERNAL_H_
#define WINDSOUL_OBJECT_INTERNAL_H_

struct WObjStruct {
	int kx;									// 中心点 x
	int ky;									// 中心点 y
	void *operator new(unsigned size,WObjectHeap *heap);		// 从指定堆分配(不单个释放)
	void operator delete(void *p,WObjectHeap *heap) {};
};

#endif
