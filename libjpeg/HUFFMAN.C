/*
 *	Cloud Wu's JPEG decoder
 *
 *			2000/3/4 第 1 版 2003/1/21 bug fix
 *
 *		允许非赢利性质的自由使用, 但如果使用此代码的全部或部分
 *		请署上 Cloud Wu (云风)
 *
 *		商业使用请向作者直接联系
 *
 *		www.codingnow.com
 *		cloudwu@263.net
 *	
 *		Huffman Table 的解码
 */

#include <string.h>
#include <stdlib.h>
#include "jpegint.h"

JPEG_HUFFMANTABLE jpeg_htable[8];

void* read_DHT(void *stream)
{
	WORD seg_size;
	int i,j,p,code,si;
	void *stream_end;
	JPEG_HUFFMANCODE *htb;
	BYTE htb_id,*code_len;
	READ_MWORD(seg_size,stream);
	stream_end=(void*)((unsigned)stream+seg_size-2);
	while (stream<stream_end) {

// 取信息码
		htb_id=*((BYTE *)stream)++;
		htb_id=(htb_id&0x10)?(htb_id&3|4):(htb_id&3);

// 统计HTB长度,分配内存
		code_len=(BYTE *)stream;
		for (i=0;i<16;i++)
			jpeg_htable[htb_id].num+=code_len[i];
		stream=(void *)((BYTE *)stream+16);
		htb=jpeg_htable[htb_id].htb=malloc(jpeg_htable[htb_id].num*sizeof(JPEG_HUFFMANCODE));

// 计算代码表
		for (i = 0, p=0; i < 16; i++) 
			for (j = 0; j < code_len[i]; j++)
				htb[p].num = READ_BYTE(stream), htb[p++].len = i+1;

		for (si=htb[0].len,i=code=0; i<p ; code<<=1,si++)
			while (htb[i].len == si && i<p) 
				htb[i++].code = code ++;
	}

	if (stream!=stream_end)	return NULL;
	return stream_end;
}


