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
 *		JPEG 内部头文件
 */

#ifndef _JPEG_INTERNAL_
#define _JPEG_INTERNAL_

#include "stdio.h"
#include "jpeg.h"

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )

#pragma pack (push)
#pragma pack (1)

typedef struct {
	WORD code;	// huffman 编码
	BYTE len;	// 掩码长度
	BYTE num;	// 代表的字节
} JPEG_HUFFMANCODE;

typedef struct {
	BYTE v;
	BYTE h;
	BYTE qtb;
	BYTE act;
	BYTE dct;
} JPEG_COMPONENT;

typedef struct {
	BYTE colordepth;
	WORD height;
	WORD width;
	BYTE components;
	JPEG_COMPONENT component[3];
} JPEG_SOF0;

#pragma pack (pop)

typedef struct {
	JPEG_HUFFMANCODE *htb;
	int num;
} JPEG_HUFFMANTABLE;

/*************************************************************************************/

#ifdef _DEBUG
#ifndef DEBUGINFOON
#define DEBUGINFOON
#endif
#endif

#ifdef DEBUGINFOON
#define DEBUGINFO debuginfohead(__FILE__,__LINE__);debuginfo
#else
#define DEBUGINFO
#endif

//extern int is555;
//extern int isMMX;

// 一个色点的类型 (暂时不能修改)
//typedef unsigned short int PIXEL;

// 一个色点的字节长度 (暂时不能修改)
#define SIZEOFPIXEL 2

// 文件名(包括虚拟路径) 最大长度
#define PATHMAXLEN 80

// 数据包文件读缓冲数量
#define FILEBUFFERNUM 8
/*
// 游戏库中使用的不压缩的位图结构
typedef struct {
	int w,h,pitch;      //位图宽和高以及每行实际字节数
	int cl,ct,cr,cb;    //位图剪裁矩形的左上角顶点坐标
	//剪裁矩形的宽和高
	PIXEL *line[1];     //创建位图时动态分配大小
} BMP;
*/
#pragma pack (push)
#pragma pack (2)

typedef struct {
	FILE *file;				// 实际文件指针
	unsigned short filenum; // 包内有多少个小文件
	struct {
		unsigned id;		// 包内文件的 ID 32bit
		unsigned offset;	// 文件相对于文件开始的偏移量
		unsigned len;		// 解压后的长度
	} block[1];
} DATAFILE;

typedef struct {
	FILE *datafile;			//数据文件指针(可以是单独的文件本身)
	unsigned offset;		//第一块的偏移量,0 表示是单独文件
	unsigned len;			//文件长度
	unsigned pos;			//读指针的位置(解码后的位置)
	unsigned char *buf;		//读缓冲指针(缓冲固定为64K)
	unsigned datapos;		//在压缩包里的位置
	unsigned short block[1];//每块的长度
} PACKFILE;

#pragma pack (pop)

PACKFILE *pack_fopen(char *);
unsigned pack_fread(void *buffer, unsigned size, PACKFILE *f);
void pack_fclose(PACKFILE *);

unsigned filename2id(char *);

// 创建非压缩的位图
BMP *create_bitmap(int w,int h);

int decompress(void *src, unsigned src_len,	void *dst);

/*************************************************************************************/

extern JPEG_HUFFMANTABLE jpeg_htable[8];
extern short *jpeg_qtable[4];
extern JPEG_SOF0 jpeg_head;
extern short jpeg_DC[3];
extern BYTE jpeg_bit,*jpeg_stream;
extern BYTE jpeg_zigzag[64];
extern WORD jpeg_DRI;

#define READ_MWORD(a,stream) \
	__asm mov esi,stream	\
	__asm xor eax,eax		\
	__asm lodsw				\
    __asm xchg al,ah		\
	__asm mov a,ax			\
	__asm mov stream,esi	

#define READ_BYTE(stream) (*((BYTE*)stream)++)
#define READ_WORD(stream) (*((WORD*)stream)++)

void* read_DQT(void *stream);
void* read_DHT(void *stream);
void *read_SOF0(void *stream);
void *read_DRI(void *stream);
void *read_SOS(void *stream);
void *skip_SEG(void *stream);

// 预处理, 去掉 FF
void jpeg_preprocess(BYTE *stream);

// 从数据流 jpeg_stream 解码一个 DU 到 buf
void jpeg_decode_DU(short *buf,int com);

void jpeg_idct8x8aan (short *src_result);
void jpeg_idct2d(short *buf);
extern void (*jpeg_idct) (short *buf);
void Y2RGB(WORD *bmppixel,int pitch);	
extern void (*YCbCr411)(WORD *bmppixel,int pitch);
void YCbCr111(WORD *bmppixel,int pitch);
void jpeg_setcolormode(int is555,int isMMX);

#endif