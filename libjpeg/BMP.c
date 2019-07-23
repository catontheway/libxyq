#include <stdlib.h>
#include <memory.h>
#include "jpegint.h"

// 创建非压缩的位图
BMP *create_bitmap(int w,int h)
{
	BMP *tmp;
	PIXEL *t;
	int i,bmpw=w;
	if (w&3) w=(w+3)&0xfffffffc;    //保证对齐,所以每行都是4 倍数点宽度
	tmp=(BMP *)malloc(sizeof(BMP)+(h-1)*sizeof(PIXEL *)+w*h*SIZEOFPIXEL);
	if (!tmp) return NULL;
	tmp->w=tmp->cr=bmpw;
	tmp->pitch=w*SIZEOFPIXEL;
	tmp->h=tmp->cb=h;
	tmp->cl=tmp->ct=0;
	t=tmp->line[0]=(PIXEL *)((char *)tmp+sizeof(BMP)+(h-1)*sizeof(PIXEL *));
	for (i=1;i<h;i++)
		tmp->line[i]=(t+=w);
	return tmp;
}