#include "Wdf.h"


#pragma pack (push)
#pragma pack (1)
struct TGAFILEHEADER{
	uchar bIDLength;						//附加信息长度
	uchar bPalType;						//调色板信息(不支持)
	uchar bImageType;					//图象类型(只支持 2,10)
	ushort wPalIndex;						//调色板第一个索引值
	ushort wPalLength;					//调色板索引数
	uchar bPalBits;						//一个调色板单位位数(15,16,24,32)
	ushort wLeft;							//图象左端坐标(基本不用)
	ushort wBottom;						//图象底端坐标(基本不用)
	ushort wWidth;						//图象宽度
	ushort wHeight;						//图象高度
	uchar bBits;							//一个象素位数
	uchar bAlphaBits : 4;					//Alpha位数
	uchar bReserved : 1;					//保留,必须为0
	uchar bTopDown : 1;					//为1表示从上到下(只支持从下到上)
	uchar bInterleaving : 2;				//隔行(一般为0)
};
#pragma pack (pop)

void WPixel::operator=(ushort color)
{
	blue = color & 0x1f;
	green = (color >> 5 & 0x1f) << 1;
	if (green)green += 1;
	red = color >> 10 & 0x1f;
}
void WPixel::operator=(ulong color1)
{
	red = color1 >> 3 & 0x1f;
	green = (color1 >> 11 & 0x1f) << 1;
	if (green)green += 1;
	blue = color1 >> 19 & 0x1f;
}

bool CWdf::Open(const char* FileName)
{
// 	static WdfReader r;
// 	r.clear();
// 	r.load(FileName);
// 	if (r.getWdfs().empty())
// 	{
// 		return false;
// 	}
	m_File.open(FileName, ios::binary);
	if (!m_File)
	{
// 		MessageBoxA(/*g_hWnd*/nullptr, "没有找到文件", "", MB_OK);
// 		assert(0);
		ccc_log("没有找到WDF文件:%s", FileName);
		return false;
	}
// 	const auto& wdf = r.getWdfs().front();
// 	m_pIndex = new WDataFileIndex[m_Number = wdf.indexsCount];
// 	memcpy(m_pIndex, wdf.indexs, m_Number * sizeof(WDataFileIndex));
// 	return true;

	//读取文件头
	WDataFileHeader header;
	m_File.read((char*)&header, sizeof(header));

	//确保是WDF文件
	if (header.id != 'WDFP')
	{
		m_File.close();
		//		MessageBoxA(g_hWnd, "无效的WDF文件", "", MB_OK);
		ccc_log("无效的WDF文件:%s", FileName);
		return false;
	}
	//保存子文件列表
	m_pIndex = new WDataFileIndex[header.number];
	m_File.seekg(header.offset, ios_base::beg);
	int size = sizeof(ulong);
	for (int i = 0; i < header.number; i++)
	{
		m_File.read((char*)&m_pIndex[i].uid, size);
		m_File.read((char*)&m_pIndex[i].offset, size);
		m_File.read((char*)&m_pIndex[i].size, size);
		m_File.read((char*)&m_pIndex[i].space, size);
	}
	m_Number = header.number;
	return true;
}



bool CWdf::Free()
{
	SAFE_DELETE_ARRAY(m_pIndex);
	return true;
}


