#pragma once
#include "_asert.h"

//WDF文件头,记录着文件的类型(WDF),子文件的数量,子文件列表的位置
struct WPixel
{
	union
	{
		ushort color;								// 16bit 高彩
		struct
		{
			ushort blue : 5;						// 5bit 兰色
			ushort green : 6;						// 6bit 绿色
			ushort red : 5;							// 5bit 红色
		};
		struct
		{
			uchar l;
			uchar h;
		};
	};
	WPixel(){};
	// 5 5 5 格式转 5 6 5
	void operator =(ushort color);
	void operator =(ulong color1);
	WPixel(int r, int g, int b) : red(r >> 3), green(g >> 2), blue(b >> 3) {}
};



struct WDataFileHeader {
	ulong id;
	int number;
	unsigned offset;
};
//子文件的ID 位置 大小 
struct WDataFileIndex {
	ulong uid;
	ulong offset;
	ulong size;
	ulong space;
};

//was文件头
struct WASFILEHEADER{
	ushort wastitle;			//文件标示 SP
	ushort szHheard;			//文件头大小
	ushort nDirection;		//动画的方向数
	ushort nFrame;			//每个方向的帧数
	ushort nWidth;			//动画的宽度
	ushort nHeigh;			//动画的高度
	short xCenter;			//动画的中心 X
	short yCenter;			//动画的中心 Y
};

//数据头
struct DATEHEARD
{
	int FramX;				//图片中心 X
	int FramY;				//图片中心 Y
	int Width;				//图片宽度
	int Height;				//图片高度
};

class CWdf
{
public:
	CWdf(){ m_pIndex = 0; }
	~CWdf(){ Free(); }
	bool Free();
	bool Open(const char* FileName);
	std::string m_Name;
	WDataFileIndex* SearchFile(ulong id);
	ifstream* GetFileHandle() { return &m_File; }
	WDataFileIndex *m_pIndex;

	uint m_Number;
private:
	ifstream m_File;
};

// 
// #define tile_num(x,y) ((y)*map_w+(x))  //将 x,y 坐标转换为地图上块的编号
// #define tile_x(n) ((n)%map_w)          //由块编号得出 x,y 坐标
// #define tile_y(n) ((n)/map_w)