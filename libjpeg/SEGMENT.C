/*
 *	Cloud Wu's JPEG decoder
 *
 *			2000/6/19 第 2 版
 *
 *		允许非赢利性质的自由使用, 但如果使用此代码的全部或部分
 *		请署上 Cloud Wu (云风)
 *
 *		商业使用请向作者直接联系
 *
 *		www.codingnow.com
 *		cloudwu@263.net
 *	
 *		读取 SEGMENT
 */

#include "jpegint.h"

#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )

// 跳过一个有内容的段
void *skip_SEG(void *stream)
{
	void *stream_end;
	WORD seg_size;

	READ_MWORD(seg_size,stream);
	stream_end=(void*)((unsigned)stream+seg_size-2);
	return stream_end;
}


/*
SOF0: Start Of Frame 0:
~~~~~~~~~~~~~~~~~~~~~~~

  - $ff, $c0 (SOF0)
  - 长度 (高字节, 低字节), 8+components*3
  - 数据精度 (1 byte) 每个样本位数, 通常是 8 (大多数软件不支持 12 和 16)
  - 图片高度 (高字节, 低字节), 如果不支持 DNL 就必须 >0
  - 图片宽度 (高字节, 低字节), 如果不支持 DNL 就必须 >0
  - components 数量(1 byte), 灰度图是 1, YCbCr/YIQ 彩色图是 3, CMYK 彩色图
    是 4
  - 每个 component: 3 bytes
     - component id (1 = Y, 2 = Cb, 3 = Cr, 4 = I, 5 = Q)
     - 采样系数 (bit 0-3 vert., 4-7 hor.)
     - quantization table 号
*/

JPEG_SOF0 jpeg_head;

void *read_SOF0(void *stream)
{
	void *stream_end;
	WORD seg_size;
	BYTE id,q,i;
	READ_MWORD(seg_size,stream);
	stream_end=(void*)((unsigned)stream+seg_size-2);
	jpeg_head.colordepth=READ_BYTE(stream);
	READ_MWORD(jpeg_head.height,stream);
	READ_MWORD(jpeg_head.width,stream);
	if ((jpeg_head.components=READ_BYTE(stream)) >3) 
		return NULL;	// 不支持 3 个组件以上
	for (i=0;i<jpeg_head.components;i++) {
		if ((id=READ_BYTE(stream))>3) return NULL; //不支持的模式
		if (--id<0) return NULL;
		q=READ_BYTE(stream);
		if ((jpeg_head.component[id].v=q&0xf)>2) 
			return NULL; // 不支持超过 2 的采样率
		if ((jpeg_head.component[id].h=q>>4)>2)
			return NULL; // 不支持超过 2 的采样率
		jpeg_head.component[id].qtb=READ_BYTE(stream)&3;
	}
	return stream_end;
}

/*
SOS: Start Of Scan:
~~~~~~~~~~~~~~~~~~~

  - $ff, $da (SOS)
  - 长度 (高字节, 低字节), 必须是 6+2*(扫描行内组件的数量)
  - 扫描行内组件的数量 (1 byte), 必须 >= 1 , <=4 (否则是错的) 通常是 3
  - 每个组件: 2 bytes
     - component id (1 = Y, 2 = Cb, 3 = Cr, 4 = I, 5 = Q), 见 SOF0
     - 使用的 Huffman 表:
	- bit 0..3: AC table (0..3)
	- bit 4..7: DC table (0..3)
  - 忽略 3 bytes (???)
*/

void *read_SOS(void *stream)
{
	void *stream_end;
	WORD seg_size;
	BYTE i,id,com,q;
	READ_MWORD(seg_size,stream);
	stream_end=(void*)((unsigned)stream+seg_size-2);
	if ((com=READ_BYTE(stream))!=jpeg_head.components) 
		return NULL; // 组件数目不对

	for (i=0;i<com;i++) {
		if ((id=READ_BYTE(stream))>3) return NULL; //不支持的模式
		if (--id<0) return NULL;
		q=READ_BYTE(stream);
		jpeg_head.component[id].act=(q&3)|4;
		jpeg_head.component[id].dct=(q>>4)&3;
	}
	return stream_end;
}

/*
DRI: Define Restart Interval:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  - $ff, $dd (DRI)
  - 长度 (高字节, 低字节), 必须是 4
  - MCU 块的单元中的重新开始间隔 (高字节, 低字节),
    意思是说, 每 n 个 MCU 块就有一个 RSTn 标记.
    第一个标记是 RST0, 然后是 RST1 等, RST7 后再从 RST0 重复 
*/

WORD jpeg_DRI=0;

void *read_DRI(void *stream)
{
	void *stream_end;
	WORD seg_size;
	READ_MWORD(seg_size,stream);
	stream_end=(void*)((unsigned)stream+seg_size-2);
	READ_MWORD(jpeg_DRI,stream);
	return stream_end;
}
