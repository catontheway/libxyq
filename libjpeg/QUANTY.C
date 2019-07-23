/*
 *	Cloud Wu's JPEG decoder
 *
 *			2000/3/4 第 1 版
 *
 *		允许非赢利性质的自由使用, 但如果使用此代码的全部或部分
 *		请署上 Cloud Wu (云风)
 *
 *		商业使用请向作者直接联系
 *
 *		www.codingnow.com
 *		cloudwu@263.net
 *	
 *		读取 Quantize Table 
 */

#include <string.h>
#include <stdlib.h>
#include "jpegint.h"

short *jpeg_qtable[4];

void* read_DQT(void *stream)
{
	WORD seg_size;
	int i;
	void *stream_end;
	short *qtb;
	BYTE qtb_id;
	READ_MWORD(seg_size,stream);
	stream_end=(void*)((unsigned)stream+seg_size-2);
	while (stream<stream_end) {

		qtb_id=READ_BYTE(stream);
		if (qtb_id&0x10) {
			qtb_id&=3;
			jpeg_qtable[qtb_id]=qtb=malloc(256);
			for (i=0;i<64;i++) {
				short tmp;
				READ_MWORD(tmp,stream);
				qtb[i]=tmp<<4;
			}
		}
		else {
			qtb_id&=3;
			jpeg_qtable[qtb_id]=qtb=malloc(256);
			for (i=0;i<64;i++)
				qtb[i]=(READ_BYTE(stream))<<4;
		}
	}

	if (stream!=stream_end)	return NULL;
	return stream_end;
}
