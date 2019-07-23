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

		Description:		风魂几何函数内部头文件
 		Original Author:	云风 
		Authors:
		Create Time:		2001/1/17
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
 
#ifndef _WINDSOUL_GEOMETRY_INTERNAL_H
#define _WINDSOUL_GEOMETRY_INTERNAL_H
  
struct WLineStruct : public WObjStruct, memory<WLineStruct> {
	int x;									// X 偏移
	int y;									// Y 偏移
	bool positive;
	WPixel color;							// 颜色
	int userdata;							// 用户数据

	WLineStruct(int x,int y,WPixel color);
	WLineStruct() {}
	WLineStruct(const WLineStruct& line) { x=line.x,y=line.y,positive=line.positive,color=line.color,userdata=line.userdata; }
	using memory<WLineStruct>::operator new;
	using memory<WLineStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WLineStruct& operator=(const WLineStruct&box);		//无此函数
};  
  
inline WLineStruct::WLineStruct(int xx,int yy,WPixel color) : color(color) 
{
	if (xx>=0) kx=0,x=xx,positive=true;
	else kx=-xx,x=-xx,positive=false;
	if (yy>=0) ky=0,y=yy;
	else ky=-yy,y=-yy,positive=!positive;
}
 
struct WBoxStruct : public WObjStruct, memory<WBoxStruct> {
	int w;
	int h;
	int userdata;
	WPixel color;

	WBoxStruct(int w,int h,WPixel color) : w(w), h(h), color(color) { kx=ky=0; }
	WBoxStruct() {}
	WBoxStruct(const WBoxStruct &box) { w=box.w, h=box.h, userdata=box.userdata, color=box.color; }
	using memory<WBoxStruct>::operator new;
	using memory<WBoxStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WBoxStruct& operator=(const WBoxStruct&box);		//无此函数
};
 
#endif
