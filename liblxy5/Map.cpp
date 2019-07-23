#include "_global.h"
// jpg
#ifdef  __cplusplus
extern "C"
{
#endif
#include "../libjpeg/jpeg.h"
#include "../libjpeg/JPEGINT.H"
#if defined(_DEBUG)
#pragma comment(lib,"libjpeg_mdd.lib")
#else
#pragma comment(lib,"libjpeg_mt.lib")
#endif
#ifdef  __cplusplus
}
#endif

bool cMap::Load(char* name, int mapid)
{
	while (!m_bLoadReady2)
	{
		Sleep(1);
//		_mySleep->sleep(1);
	}
	m_MapID = mapid;
	m_bLoadReady2 = false;
	m_bLoadReady = false;
	g_pMainState->m_Canvas.m_Time = 0;


// 	if (!_reader)
// 	{
// 		_reader = new MapReader;
// 	}
// 	if (!_reader->load(name))
// 	{
// 		asert(false, "无法打开%s", name);
// 	}

	Free();

// 	m_HeightNum = _reader->m_bh;
// 	m_WidthNum = _reader->m_bw;
// 	m_Width = _reader->m_mw;
// 	m_Height = _reader->m_mh;
// 
// 	m_NumBlock = m_HeightNum * m_WidthNum;
// 	m_MaskNum = _reader->m_MasksCount;
// 
// 	m_pMaskRect = new sMASKRect[m_MaskNum];

	m_File.open(name, ios::binary | ios::in);
	if (!m_File)
	{
		ERRBOX;
		asert(false, "无法打开%s", name);
	}

	m_File2.open(name, ios::binary | ios::in);
	if (!m_File2)
	{
		ERRBOX;
		asert(false, "新线程无法打开%s", name);
	}


	SMap_Header	FileHeader;
	m_File.read((char*)&FileHeader, sizeof(SMap_Header));//读取地图头




	// 计算地图的大小,数量,并分配内存
	m_HeightNum = (int)ceil((float)FileHeader.map_height / 240.0f);
	m_WidthNum = (int)ceil((float)FileHeader.map_width / 320.0f);
	m_Width = FileHeader.map_width;// m_WidthNum * 320;
	m_Height = FileHeader.map_height;//m_HeightNum * 240;


	//----------------------------------
	// 读地图块的偏移信息
	//----------------------------------
	int block_num = m_WidthNum * m_HeightNum;
	m_NumBlock = block_num;
	m_pBlockOffset = new uint[block_num];
	m_File.read((char*)m_pBlockOffset, sizeof(uint)*block_num);

	//----------------------------------
	// 读SMaskHead数据
	//----------------------------------
	SMaskHead maskHead;
	m_File.read((char*)&maskHead, sizeof(SMaskHead));


	//----------------------------------
	// 读mask数据的偏移信息
	//----------------------------------
	m_pMaskDataOffset = new uint[maskHead.mask_num];
	m_File.read((char*)m_pMaskDataOffset, sizeof(uint)*maskHead.mask_num);

	//创建mask矩形
	m_pMaskRect = new sMASKRect[maskHead.mask_num];
	//----------------------------------
	// 填充矩形数据
	//----------------------------------
	m_MaskNum = maskHead.mask_num;

	m_align_width = new int[m_MaskNum];
	m_pMaskDataDec = new uchar*[m_MaskNum];
	for (int i = 0; i < m_MaskNum; i++)
	{
		m_align_width[i] = 0;
		m_pMaskDataDec[i] = 0;
	}
	for (long i = 0; i < m_MaskNum; i++)
	{
		ReadMask(m_pMaskDataOffset[i], i);
	}


	//创建线程
	if (!m_hThread)
	{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0,ThreadProc, this, CREATE_SUSPENDED, NULL);
//		m_hThread = CreateThread(0, 0, ThreadProc, this, CREATE_SUSPENDED, 0);
	}
//	initHeheda();
// 	if (!_mySleep)
// 	{
// 		_mySleep = new MySleep;
// 		_mySleep->thread(ThreadProc);
// 	}

	return true;
}

void cMap::ReadBlock(int block_offset, ushort* map)
{
	m_pTexture = map;


// 	auto pter = _reader->readJPG(block_offset);
// 	BMP* pBmpData = Unpak_jpg((uchar*)pter.ptr, pter.size);
// 	if (pBmpData == 0) return;
// 	memcpy_s(m_pTexture, 153600, pBmpData->line[0], 153600);
// 	destroy_bitmap(pBmpData);
// 	return;

	//读取数据头
	SBlockInfo blockInfo = { 0 };

	m_File.seekg(block_offset, ios_base::beg);
	m_File.read((char*)&blockInfo.UnitN, sizeof(uint) );
	if (blockInfo.UnitN>0)
	{
		if (blockInfo.UnitN > m_UnitNDataSize)
		{
			m_UnitNDataSize = blockInfo.UnitN;
			SAFE_DELETE_ARRAY(m_pUnitNData);
			m_pUnitNData = new uchar[m_UnitNDataSize << 2];
		}
		m_File.read((char*)m_pUnitNData, blockInfo.UnitN << 2);
	}
	m_File.read((char*)&blockInfo.flag, 8);

	char ccc[4];
	memcpy(ccc, &blockInfo.flag, 4);
	
	if (m_MapJpgDataSize < blockInfo.size)
	{
		m_MapJpgDataSize=blockInfo.size;
		SAFE_DELETE_ARRAY(m_pMapJpgData);
		m_pMapJpgData = new uchar[m_MapJpgDataSize];
	}
	m_File.read((char*)m_pMapJpgData, blockInfo.size);


	BMP* pBmpData = nullptr;
	if (blockInfo.flag == 1246775090)
	{
		pBmpData = Unpak_jpg(m_pMapJpgData, blockInfo.size);	// 解压后的像素格式为ARGB565
	}
	else
	{
		uint jpg_size = 0;
		uchar* pJpgData = JpgHandler(m_pMapJpgData, blockInfo.size, &jpg_size);
		// 解压jpg
		pBmpData = Unpak_jpg(pJpgData, jpg_size);	// 解压后的像素格式为ARGB565
	}

	if (pBmpData == 0)  return;

	memcpy_s(m_pTexture, 153600, pBmpData->line[0], 153600);
	destroy_bitmap(pBmpData);

}

uchar* cMap::JpgHandler(uchar* Buffer, int inSize, uint* outSize)
{

	// JPEG数据处理原理
	// 1、复制D8到D9的数据到缓冲区中
	// 2、删除第3、4个字节 FFA0
	// 3、修改FFDA的长度00 09 为 00 0C
	// 4、在FFDA数据的最后添加00 3F 00
	// 5、替换FFDA到FF D9之间的FF数据为FF 00

	uint TempNum = 0;						// 临时变量，表示已读取的长度
	uchar* outBuffer;
	if (inSize > m_TempBufferNum)
	{
		m_TempBufferNum = inSize;
		SAFE_DELETE_ARRAY(m_pTempBuffer);
		m_pTempBuffer = new uchar[inSize <<1];		// 临时变量，表示处理后的数据
	}
	outBuffer = m_pTempBuffer;					// 已处理数据的开始地址
	ushort TempTimes = 0;					// 临时变量，表示循环的次数
	uint Temp = 0;

	// 当已读取数据的长度小于总长度时继续
	while (TempNum < inSize && *Buffer++ == 0xFF)
	{
		*m_pTempBuffer++ = 0xFF;
		TempNum++;
		switch (*Buffer)
		{
		case 0xD8:
			*m_pTempBuffer++ = 0xD8;
			*Buffer++;
			TempNum++;
			break;
		case 0xA0:
			*Buffer++;
			m_pTempBuffer--;
			TempNum++;
			break;
		case 0xC0:
			*m_pTempBuffer++ = 0xC0;
			*Buffer++;
			TempNum++;

			memcpy(&TempTimes, Buffer, sizeof(ushort)); // 读取长度
			ByteSwap(TempTimes); // 将长度转换为Intel顺序


			for (int i = 0; i< TempTimes; i++)
			{
				*m_pTempBuffer++ = *Buffer++;
				TempNum++;
			}

			break;
		case 0xC4:
			*m_pTempBuffer++ = 0xC4;
			*Buffer++;
			TempNum++;

			memcpy(&TempTimes, Buffer, sizeof(ushort)); // 读取长度
			ByteSwap(TempTimes); // 将长度转换为Intel顺序

			for (int i = 0; i< TempTimes; i++)
			{
				*m_pTempBuffer++ = *Buffer++;
				TempNum++;
			}
			break;
		case 0xDB:
			*m_pTempBuffer++ = 0xDB;
			*Buffer++;
			TempNum++;

			memcpy(&TempTimes, Buffer, sizeof(ushort)); // 读取长度
			ByteSwap(TempTimes); // 将长度转换为Intel顺序

			for (int i = 0; i< TempTimes; i++)
			{
				*m_pTempBuffer++ = *Buffer++;
				TempNum++;
			}
			break;
		case 0xDA:
			*m_pTempBuffer++ = 0xDA;
			*m_pTempBuffer++ = 0x00;
			*m_pTempBuffer++ = 0x0C;
			*Buffer++;
			TempNum++;

			memcpy(&TempTimes, Buffer, sizeof(ushort)); // 读取长度
			ByteSwap(TempTimes); // 将长度转换为Intel顺序
			*Buffer++;
			TempNum++;
			*Buffer++;

			for (int i = 2; i< TempTimes; i++)
			{
				*m_pTempBuffer++ = *Buffer++;
				TempNum++;
			}
			*m_pTempBuffer++ = 0x00;
			*m_pTempBuffer++ = 0x3F;
			*m_pTempBuffer++ = 0x00;
			Temp += 1; // 这里应该是+3的，因为前面的0xFFA0没有-2，所以这里只+1。

			// 循环处理0xFFDA到0xFFD9之间所有的0xFF替换为0xFF00
			for (; TempNum < inSize - 2;)
			{
				if (*Buffer == 0xFF)
				{
					*m_pTempBuffer++ = 0xFF;
					*m_pTempBuffer++ = 0x00;
					*Buffer++;
					TempNum++;
					Temp++;
				}
				else
				{
					*m_pTempBuffer++ = *Buffer++;
					TempNum++;
				}
			}
			// 直接在这里写上了0xFFD9结束Jpeg图片.
			Temp--; // 这里多了一个字节，所以减去。
			*m_pTempBuffer--;
			*m_pTempBuffer-- = 0xD9;
			break;
		case 0xD9:
			// 算法问题，这里不会被执行，但结果一样。
			*m_pTempBuffer++ = 0xD9;
			TempNum++;
			break;
		default:
			break;
		}
	}
	Temp += inSize;
	*outSize = Temp;
	m_pTempBuffer = outBuffer;
	return outBuffer;
}






cMap::cMap()
{
	m_pMaskDataOffset = 0;
	m_pBlockOffset = 0;
	m_pMaskRect = 0;
	m_WidthNum = 0;
	m_HeightNum = 0;
	m_Width = 0;
	m_Height = 0;
	m_hThread = 0;
	m_bLoadReady = true;
	m_bLoadReady2 = true;
	jpeg_setcolormode(0, 1);

	m_pBmpinfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+sizeof(RGBQUAD)* 2);
	m_pBmpinfo->bmiHeader.biPlanes = 1;
	m_pBmpinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpinfo->bmiHeader.biBitCount = 16;
	m_pBmpinfo->bmiHeader.biClrUsed = 0;
	m_pBmpinfo->bmiHeader.biClrImportant = 0;
	m_pBmpinfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpinfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpinfo->bmiHeader.biWidth = 320;
	m_pBmpinfo->bmiHeader.biHeight = -240;
	m_pBmpinfo->bmiHeader.biSizeImage = 320 * 240 * 2;
	m_pBmpinfo->bmiHeader.biCompression = 0;


	ulong colorbit = 0xf800;
	memmove(&g_pBmpinfo->bmiColors[0], &colorbit, sizeof(RGBQUAD));
	colorbit = 0x7e0;
	memmove(&g_pBmpinfo->bmiColors[1], &colorbit, sizeof(RGBQUAD));
	colorbit = 0x1f;
	memmove(&g_pBmpinfo->bmiColors[2], &colorbit, sizeof(RGBQUAD));

	m_BitmapID.resize(1600);
	m_pBitmap = new uchar*[1600];
	for (int i = 0; i < 1600; i++)
	{
		m_BitmapID[i] = -1;
		m_pBitmap[i] = 0;
	}
}


bool cMap::Show(uchar* pPic, const RECT& rect)
{
// 	if (!m_bLoadReady2)
// 	{
// 		return true;
// 	}
	while (!m_bLoadReady2)
	{
		Sleep(1);
	}

	static int cx; cx = m_xCenter - g_half320;
	static int cy; cy = m_yCenter - g_half240;
	static int bx, by, idx, ix, iy, bx2, w, temp;
	static uchar* pf, *pb;
	for (int k = rect.top; k < rect.bottom; ++k)
	{
		by = (cy + k) / 240;
		iy = (cy + k) % 240;
		bx = (cx + rect.left) / 320;
		ix = (cx + rect.left) % 320;
		idx = by * m_WidthNum + bx;
		w = 32;
		bx2 = (cx + rect.right - 1) / 320;
		if (bx2 != bx)
		{
			w = 320 - ix;
			if (idx >= 0 && idx < m_NumBlock)
			{
				pf = &pPic[((k - rect.top) * 32) * 2];
				temp = iy * 320 + ix;
				if (temp >= 0)
				{
					pb = &m_pBitmap[idx][temp * 2];
					memcpy(pf, pb, w * 2);
				}

			}

			idx = by * m_WidthNum + bx2;
			if (idx >= 0 && idx < m_NumBlock)
			{
				
				pf = &pPic[((k - rect.top) * 32 + w) * 2];
				temp = iy * 320/* + w*/;
				if (temp >= 0)
				{
					pb = &m_pBitmap[idx][temp * 2];
					w = 32 - w;
					memcpy(pf, pb, w * 2);
				}

			}

		}
		else if (idx >= 0 && idx < m_NumBlock)
		{
			pf = &pPic[((k - rect.top) * 32) * 2];
			temp = iy * 320 + ix;
			if (temp >= 0)
			{
				pb = &m_pBitmap[idx][temp * 2];
				memcpy(pf, pb, 64);
			}

		}
	}

	return true;

	// rect 画布块
	int xstart = rect.left + m_xCenterOffset + 320 - g_half320;
	int ystart = rect.top + m_yCenterOffset + 240 - g_half240;
	// 画布块在地图快中的偏移
	int xstart2 = (xstart) % 320;
	int ystart2 = (ystart) % 240;
	int ycube = 0;
	int xcube = 0;
	int xOff1, yOff1;


	bool isok = false;
	int _320 = g_half320;
	int _240 = g_half240;
	for (int i = /*24*/0; i <= (g_480 + 240); i += 240)
	{
		if (ystart < i)
		{
			ycube = ((i - 240) / 240) - 1;
			yOff1 = ystart - (i - 240);
			isok = true;
			break;
		}
	}
	if (!isok)
	{
		return false;
	}


// 	if (ystart < 240)
// 	{
// 		ycube = -1;
// 		yOff1 = ystart;//第一排要加120
// 	}
// 	else
// 	if (ystart < 480)
// 	{
// 		ycube = 0;
// 		yOff1 = ystart - 240;
// 	}
// 	else
// 	if (ystart < 720)
// 	{
// 		ycube = 1;
// 		yOff1 = ystart - 480;
// 	}
// 	else
// 		return false;

	isok = false;
	for (int i = /*32*/0; i <= (g_640 + 320); i += 320)
	{
		if (xstart < i)
		{
			xcube = ((i - 320) / 320) - 1;
			xOff1 = xstart - (i - 320);
			isok = true;
			break;
		}
	}
	if (!isok)
	{
		return false;
	}

// 	if (xstart < 320)
// 	{
// 		xcube = -1;
// 		xOff1 = xstart; //第一排的图片只有半张,所以要+160
// 	}
// 	else
// 	if (xstart < 640)
// 	{
// 		xcube = 0;
// 		xOff1 = xstart - 320;
// 	}
// 	else
// 	if (xstart < 960)
// 	{
// 		xcube = 1;
// 		xOff1 = xstart - 640;
// 	}
// 	else
// 		return false;

	int k = m_xCenterNum + xcube + (ycube + m_yCenterNum) * m_WidthNum;

	if (k < 0 || k >= m_NumBlock)
	{
		return false;
	}

	int w1 = 32;
	if ((xstart2) > 288)
		w1 = 320 - (xstart2);

	int h1 = 32;
	if ((ystart2) > 208)
		h1 = 240 - (ystart2);

	uchar* P1 = pPic;
	uchar* P2 = &m_pBitmap[k][(320 * yOff1 + xOff1) << 1];

	int w2 = w1 << 1;
	for (int i = 0; i < h1; i++)
	{
		if (memcpy_s(P1, 64, P2, w2))
		{
		}
		P1 += 64;
		P2 += 640;
	}

	int index11, index22;
	//图块可能在边界
	if ((xstart2 > 288) && (xcube < 1))
	{
		int k2 = k + 1;
		if (k2 < m_NumBlock && k2 > -1)
		{
			int index = 640 * yOff1;
			int index2 = w1 << 1;
			index11 = index;
			index22 = index2;
			int  w2 = 32 - w1;
			for (int i = 0; i < h1; i++)
			{
				for (int j = 0; j < w2; j++)
				{
					pPic[index22] = m_pBitmap[k2][index11];
					pPic[index22 + 1] = m_pBitmap[k2][index11 + 1];
					index11 += 2;
					index22 += 2;
				}
				index += 640;
				index2 += 64;
				index11 = index;
				index22 = index2;
			}
		}
	}

	if ((ystart2 > 208) && (ycube < 1))
	{
		int k3 = k + m_WidthNum;
		if (k3 < m_NumBlock && k3>-1)
		{
			int index = xOff1 << 1;
			int index2 = h1 << 6;
			index11 = index;
			index22 = index2;
			int h2 = 32 - h1;
			for (int i = 0; i < h2; i++)
			{
				for (int j = 0; j < w1; j++)
				{
					pPic[index22] = m_pBitmap[k3][index11];
					pPic[index22 + 1] = m_pBitmap[k3][index11 + 1];
					index11 += 2;
					index22 += 2;
				}
				index += 640;
				index2 += 64;
				index11 = index;
				index22 = index2;
			}
		}
	}

	if ((xstart2 > 288) && (ystart2 > 208) && (xcube < 1) && (ycube < 1))
	{
		k = k + 1 + m_WidthNum;
		if (k < m_NumBlock && k>-1)
		{
			int h2 = 32 - h1;
			int w2 = 32 - w1;
			int index = 0;
			int index2 = ((h1 << 5) + w1) << 1;
			index11 = index;
			index22 = index2;
			for (int i = 0; i < h2; i++)
			{
				for (int j = 0; j < w2; j++)
				{
					pPic[index22] = m_pBitmap[k][index11];
					pPic[index22 + 1] = m_pBitmap[k][index11 + 1];
					index11 += 2;
					index22 += 2;
				}
				index += 640;
				index2 += 64;
				index11 = index;
				index22 = index2;
			}
		}
	}
	////图块可能在边界
	//if ((xstart2 > 288) && (ystart2 > 208) && (xcube < 1) && (ycube < 1))
	//{
	//	k = k + 1 + m_WidthNum;
	//	if (k < m_NumBlock&&k>-1)
	//	{
	//		int k3 = k + m_WidthNum;
	//		if (k3 < m_NumBlock&&k3>-1)
	//		{
	//			uchar* P1 = &pPic[((h1 << 5) + w1) << 1];
	//			uchar* P2 = &m_pBitmap[k][0];
	//			int h2 = 32 - h1;
	//			int w2 = (32 - w1) << 1;
	//			for (int i = 0; i < h2; i++)
	//			{
	//				memcpy_s(P1, 64, P2, w2);
	//				P1 += 64;
	//				P2 += 640;
	//			}
	//		}
	//	}
	//}

	//if ((xstart2 > 288) && (xcube < 1))
	//{
	//	int k2 = k + 1;
	//	if (k2 < m_NumBlock&&k2>-1)
	//	{
	//		uchar* P1 = &pPic[w1 << 1];
	//		uchar* P2 = &m_pBitmap[k2][640 * yOff1];
	//		int  w2 = (32 - w1) << 1;
	//		for (int i = 0; i < h1; i++)
	//		{
	//			memcpy_s(P1, 64, P2, w2);
	//			P1 += 64;
	//			P2 += 640;
	//		}
	//	}
	//}

	//if ((ystart2 > 208) && (ycube < 1))
	//{
	//	int k3 = k + m_WidthNum;
	//	if (k3 < m_NumBlock&&k3>-1)
	//	{
	//		uchar* P1 = &pPic[h1 << 6];
	//		uchar* P2 = &m_pBitmap[k3][xOff1 << 1];
	//		int  w2 = w1 << 1;
	//		int h2 = 32 - h1;
	//		for (int i = 0; i < h2; i++)
	//		{
	//			memcpy_s(P1, 64, P2, w2);
	//			P1 += 64;
	//			P2 += 640;
	//		}
	//	}
	//}

	

	return true;
}





void cMap::WriteMapPixel(ushort* pBmp16, int width, int height, int pitch)
{

	ushort* pDst = m_pTexture;
	WPixel pix;
	for (int h = 0; h<height; h++)
	{
		for (int i = 0; i < width; i++)
		{
			/*pix = *(pBmp16 + i);
			pDst[i] = pix.color;*/
			pDst[i] =* (pBmp16 + i);
		}
		pBmp16 += width;
		pDst += width;
	}

}

bool cMap::MoveMap()
{
	g_pMainState->FindObj();

	m_xCenterNum = GetXCenter() / 320;
	m_yCenterNum = GetYCenter() / 240;
	CountMaskList();
	if (1)
	{
		m_bLoadReady = false;
		m_bLoadReady2 = false;
	}

	ResumeThread(m_hThread);
	return true;
}

bool cMap::initHeheda()
{
	cMap*  pMap = this;// (cMap*)lpParameter;
//	while (1)
	{
		pMap->m_bLoadReady = false;
		pMap->m_bLoadReady2 = false;
		int HeightNum = pMap->m_yCenterNum;
		int WidthNum = pMap->m_xCenterNum;
		pMap->m_NowMapNum = (HeightNum)*pMap->m_WidthNum + WidthNum;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				int k = pMap->m_NowMapNum + j + i * pMap->m_WidthNum;
				//防止数组越界
				if (k < 0)
					continue;
				if (i + HeightNum >= pMap->m_HeightNum)
					continue;
				if (j + WidthNum >= pMap->m_WidthNum)
					continue;
				if (pMap->m_MapID != pMap->m_BitmapID[k])
				{
					pMap->m_BitmapID[k] = pMap->m_MapID;
					if (!pMap->m_pBitmap[k])
						pMap->m_pBitmap[k] = new uchar[153600];
					pMap->ReadBlock(pMap->m_pBlockOffset[k], (ushort*)pMap->m_pBitmap[k]);
				}

			}
		}


		pMap->m_bLoadReady = true;

		for (int i = -2; i < 3; i += 4)
			for (int j = -2; j < 3; j++)
			{
			int k = pMap->m_NowMapNum + j + i*pMap->m_WidthNum;
			//防止数组越界
			if (k < 0)
				continue;
			if (i + HeightNum >= pMap->m_HeightNum)
				continue;
			if (j + WidthNum >= pMap->m_WidthNum)
				continue;

			if (pMap->m_MapID != pMap->m_BitmapID[k])
			{
				pMap->m_BitmapID[k] = pMap->m_MapID;
				if (!pMap->m_pBitmap[k])pMap->m_pBitmap[k] = new uchar[153600];
				pMap->ReadBlock(pMap->m_pBlockOffset[k], (ushort*)pMap->m_pBitmap[k]);
			}
			}

		for (int i = -1; i < 2; i++)
		{

			for (int j = -2; j < 3; j += 4)
			{

				int k = pMap->m_NowMapNum + j + i*pMap->m_WidthNum;
				//防止数组越界
				if (k < 0)
					continue;
				if (i + HeightNum >= pMap->m_HeightNum)
					continue;
				if (j + WidthNum >= pMap->m_WidthNum)
					continue;

				if (pMap->m_MapID != pMap->m_BitmapID[k])
				{
					pMap->m_BitmapID[k] = pMap->m_MapID;
					if (!pMap->m_pBitmap[k])pMap->m_pBitmap[k] = new uchar[153600];
					{
						pMap->ReadBlock(pMap->m_pBlockOffset[k], (ushort*)pMap->m_pBitmap[k]);
					}
				}
			}

		}

		pMap->m_bLoadReady2 = true;
		//加载完就睡觉
//		SuspendThread(pMap->m_hThread);


	}
	return true;
}

unsigned int WINAPI cMap::ThreadProc(_In_ LPVOID lpParameter)
{
	cMap*  pMap = (cMap*)lpParameter;
	int _1 = 0;
	while (1)
	{
		pMap->m_bLoadReady = false;
		pMap->m_bLoadReady2 = false;
		int HeightNum = pMap->m_yCenterNum;
		int WidthNum =  pMap->m_xCenterNum;
		pMap->m_NowMapNum = (HeightNum)*pMap->m_WidthNum + WidthNum;
		for (int i = -1 - _1; i < 2 + _1; i++)
		{
			for (int j = -1 - _1; j < 2 + _1; j++)
			{
				int k = pMap->m_NowMapNum + j + i * pMap->m_WidthNum;
				//防止数组越界
				if (k < 0)
					continue;
				if (i + HeightNum >= pMap->m_HeightNum)
					continue;
				if (j + WidthNum >= pMap->m_WidthNum)
					continue;
				if (pMap->m_MapID != pMap->m_BitmapID[k])
				{
					pMap->m_BitmapID[k] = pMap->m_MapID;
					if (!pMap->m_pBitmap[k])
						pMap->m_pBitmap[k] = new uchar[153600];
					pMap->ReadBlock(pMap->m_pBlockOffset[k],(ushort*)pMap->m_pBitmap[k]);
				}

			}
		}


		pMap->m_bLoadReady = true;

		for (int i = -2 - _1; i < 3 + _1; i += 4 + _1 * 2)
			for (int j = -2 - _1; j < 3 + _1; j++)
		{
			int k = pMap->m_NowMapNum + j + i*pMap->m_WidthNum;
			//防止数组越界
			if (k < 0)
				continue;
			if (i + HeightNum >= pMap->m_HeightNum)
				continue;
			if (j + WidthNum >= pMap->m_WidthNum)
				continue;

			if (pMap->m_MapID != pMap->m_BitmapID[k])
			{
				pMap->m_BitmapID[k] = pMap->m_MapID;
				if (!pMap->m_pBitmap[k])pMap->m_pBitmap[k] = new uchar[153600];
				pMap->ReadBlock(pMap->m_pBlockOffset[k], (ushort*)pMap->m_pBitmap[k]);
			}
		}
		
		for (int i = -1 - _1; i < 2 + _1; i++)
		{

			for (int j = -2 - _1; j < 3 + _1; j += 4 + _1 * 2)
				{

					int k = pMap->m_NowMapNum + j + i * pMap->m_WidthNum;
					//防止数组越界
					if (k < 0)
						continue;
					if (i + HeightNum >= pMap->m_HeightNum)
						continue;
					if (j + WidthNum >= pMap->m_WidthNum)
						continue;

					if (pMap->m_MapID != pMap->m_BitmapID[k])
					{
						pMap->m_BitmapID[k] = pMap->m_MapID;
						if (!pMap->m_pBitmap[k])pMap->m_pBitmap[k] = new uchar[153600];
						{
							pMap->ReadBlock(pMap->m_pBlockOffset[k], (ushort*)pMap->m_pBitmap[k]);
						}
					}
				}
				
		}
	
		pMap->m_bLoadReady2 = true;
		//加载完就睡觉
		SuspendThread(pMap->m_hThread);
	}
	return 0;
}

void cMap::Free()
{
	SAFE_DELETE_ARRAY(m_pBlockOffset);
	SAFE_DELETE_ARRAY(m_pMaskDataOffset);
	SAFE_DELETE_ARRAY(m_pMaskRect);
	for (int i = 0; i < m_MaskNum; i++)
	{
		SAFE_DELETE_ARRAY(m_pMaskDataDec[i]);
	}
	SAFE_DELETE_ARRAY(m_pMaskDataDec);
	SAFE_DELETE_ARRAY(m_align_width);

	m_MaskNum = 0;
	m_File.close();
	m_File2.close();
}


void cMap::ReadMask(int offset, int mask_index)
{
// 	auto& p = m_pMaskRect[mask_index];
// 	auto m = _reader->readMask(mask_index, true);
// 	p.w = m.w;
// 	p.h = m.h;
// 	p.x = m.x;
// 	p.y = m.y;
// 	return;

	SMaskInfo maskInfo = { 0 };
	// 读mask文件头
	m_File.seekg(offset, ios_base::beg);
	m_File.read((char*)&maskInfo, sizeof(SMaskInfo));

	if (maskInfo.width == 0 || maskInfo.height == 0 || maskInfo.mask_size == 0)
		return;

	m_pMaskRect[mask_index].w = maskInfo.width;
	m_pMaskRect[mask_index].h = maskInfo.height;
	m_pMaskRect[mask_index].x = maskInfo.startX;
	m_pMaskRect[mask_index].y = maskInfo.startY;
//	m_pMaskRect[mask_index].Index = mask_index;
}

int cMap::DecompressMask(void* in, void* out)
{

	register uchar *op;
	register  uchar *ip;
	register unsigned t;
	register  uchar *m_pos;

	op = (uchar *)out;
	ip = (uchar *)in;

	if (*ip > 17) {
		t = *ip++ - 17;
		if (t < 4)
			goto match_next;
		do *op++ = *ip++; while (--t > 0);
		goto first_literal_run;
	}

	while (1) {
		t = *ip++;
		if (t >= 16) goto match;
		if (t == 0) {
			while (*ip == 0) {
				t += 255;
				ip++;
			}
			t += 15 + *ip++;
		}

		*(unsigned *)op = *(unsigned *)ip;
		op += 4; ip += 4;
		if (--t > 0)
		{
			if (t >= 4)
			{
				do {
					*(unsigned *)op = *(unsigned *)ip;
					op += 4; ip += 4; t -= 4;
				} while (t >= 4);
				if (t > 0) do *op++ = *ip++; while (--t > 0);
			}
			else do *op++ = *ip++; while (--t > 0);
		}

	first_literal_run:

		t = *ip++;
		if (t >= 16)
			goto match;

		m_pos = op - 0x0801;
		m_pos -= t >> 2;
		m_pos -= *ip++ << 2;

		*op++ = *m_pos++; *op++ = *m_pos++; *op++ = *m_pos;

		goto match_done;

		while (1)
		{
		match:
			if (t >= 64)
			{

				m_pos = op - 1;
				m_pos -= (t >> 2) & 7;
				m_pos -= *ip++ << 3;
				t = (t >> 5) - 1;

				goto copy_match;

			}
			else if (t >= 32)
			{
				t &= 31;
				if (t == 0)	{
					while (*ip == 0) {
						t += 255;
						ip++;
					}
					t += 31 + *ip++;
				}

				m_pos = op - 1;
				m_pos -= (*(unsigned short *)ip) >> 2;
				ip += 2;
			}
			else if (t >= 16) {
				m_pos = op;
				m_pos -= (t & 8) << 11;
				t &= 7;
				if (t == 0) {
					while (*ip == 0) {
						t += 255;
						ip++;
					}
					t += 7 + *ip++;
				}
				m_pos -= (*(unsigned short *)ip) >> 2;
				ip += 2;
				if (m_pos == op)
					goto eof_found;
				m_pos -= 0x4000;
			}
			else {
				m_pos = op - 1;
				m_pos -= t >> 2;
				m_pos -= *ip++ << 2;
				*op++ = *m_pos++; *op++ = *m_pos;
				goto match_done;
			}

			if (t >= 6 && (op - m_pos) >= 4) {
				*(unsigned *)op = *(unsigned *)m_pos;
				op += 4; m_pos += 4; t -= 2;
				do {
					*(unsigned *)op = *(unsigned *)m_pos;
					op += 4; m_pos += 4; t -= 4;
				} while (t >= 4);
				if (t > 0) do *op++ = *m_pos++; while (--t > 0);
			}
			else {
			copy_match:
				*op++ = *m_pos++; *op++ = *m_pos++;
				do *op++ = *m_pos++; while (--t > 0);
			}

		match_done:

			t = ip[-2] & 3;
			if (t == 0)	break;

		match_next:
			do *op++ = *ip++; while (--t > 0);
			t = *ip++;
		}
	}

eof_found:
	//   if (ip != ip_end) return -1;

	return (op - (uchar*)out);
}



bool cMap::isInRect(int x1, int y1, int w1, int h1, int x, int y, int w, int h)
{
	if (x1>x + w)
		return false;
	if (x1 + w1<x)
		return false;
	if (y1>y + h)
		return false;
	if (y1 + h1<y)
		return false;
	return true;
}

void cMap::ScreenToWorld(int x, int y, int& xOut, int& yOut)
{
	xOut = x + GetXCenter() - g_half320;
	yOut = g_480 - y + GetYCenter() - g_half240 / 2;
}

void cMap::WorldToScreen(int x, int y, int& xOut, int& yOut)
{
	xOut = x - GetXCenter() + g_half320;
	yOut = y - GetYCenter() + g_half240 / 2;
}


HBITMAP cMap::DIBtoDDB(ushort* data,HDC dc)
{

	
	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)m_pBmpinfo;
	HBITMAP hbm;
	HPALETTE Pal = 0;
	HPALETTE OldPal = 0;
	
	int nColors = lpbi->biClrUsed ? lpbi->biClrUsed : 1 << lpbi->biBitCount; //颜色表项的个数
	if (nColors <= 256 && GetDeviceCaps(dc, RASTERCAPS) & RC_PALETTE)
	{
		uint nSize = sizeof(LOGPALETTE)+(sizeof(PALETTEENTRY)* nColors);
		LOGPALETTE *plp = (LOGPALETTE *) new uchar[nSize];
		plp->palVersion = 0x300;
		plp->palNumEntries = nColors;

		for (int i = 0; i < nColors; i++)
		{
			plp->palPalEntry[i].peRed = g_pBmpinfo->bmiColors[i].rgbRed;
			plp->palPalEntry[i].peGreen = g_pBmpinfo->bmiColors[i].rgbGreen;
			plp->palPalEntry[i].peBlue = g_pBmpinfo->bmiColors[i].rgbBlue;
			plp->palPalEntry[i].peFlags = 0;
		}
		Pal = CreatePalette(plp);
		delete[] plp; //要及时处理
		// select and realize the palette
		OldPal = SelectPalette(dc, Pal, false);
		RealizePalette(dc);
	}
	hbm = CreateDIBitmap(
		dc, //设备上下文的句柄
		(LPBITMAPINFOHEADER)lpbi, //位图信息头指针
		(long)CBM_INIT, //初始化标志
		(void*)data,//lpDIBits, //初始化数据指针
		(LPBITMAPINFO)lpbi, //位图信息指针
		DIB_RGB_COLORS
		); //颜色数据的使用方式
	if (Pal)
	{
		SelectPalette(dc, OldPal, false);
	}
	
	return hbm;
}

cMap::~cMap()
{
	Free();
	free(m_pBmpinfo);
	for (int i = 0; i < 1600; i++)
	{
		SAFE_DELETE_ARRAY(m_pBitmap[i]);
	}
	SAFE_DELETE_ARRAY(m_pBitmap);
	SAFE_DELETE_ARRAY(m_pMapJpgData);
	SAFE_DELETE_ARRAY(m_pUnitNData);
	SAFE_DELETE_ARRAY(m_pTempBuffer);

	SAFE_DELETE_ARRAY(m_pBlockOffset);
	SAFE_DELETE_ARRAY(m_pMaskDataOffset);
	SAFE_DELETE_ARRAY(m_pMaskRect);
	for (int i = 0; i < m_MaskNum; i++)
	{
		SAFE_DELETE_ARRAY(m_pMaskDataDec[i]);
	}
	SAFE_DELETE_ARRAY(m_pMaskDataDec);
	SAFE_DELETE_ARRAY(m_align_width);
}

bool cMap::Follow(cObj* pObj)
{
	int xHero,  yHero;
	xHero = pObj->GetX();
	yHero = pObj->GetY();
	m_bMove = false;
	
	if (m_LockMap)
	{
		if (abs(m_xLock - m_xCenter) < 5 && abs(m_yLock - m_yCenter) < 5)
			return true;
		float dust1, dust2;
		dust1 = (float)(m_yLock - m_yCenter);
		dust2 = (float)(m_xLock - m_xCenter);
		float angel = atan2(dust1,dust2);
		
		int yMove1 =(int)(6 * sin(angel));
		int xMove1 = (int)(6 * cos(angel));
		xMove(xMove1);
		yMove(yMove1);

		m_bMove = true;
	}
	else if (m_ReturnMap)
	{
		if (abs(xHero - m_xCenter) < 10 && abs(yHero - m_yCenter) < 10)
		{
			m_ReturnMap = false;
			return true;
		}
		float dus1, dus2;
		dus1 = (float)(yHero - m_yCenter);
		dus2 = (float)(xHero - m_xCenter);
		float angel = atan2(dus1,dus2);
		int yMove1 = (int)(6 * sin(angel));
		int xMove1 = (int)(6 * cos(angel));
		xMove(xMove1);
		yMove(yMove1);
		m_bMove = true;
	}
	else
	{
		if (GetXCenter() != pObj->GetX() || GetYCenter() != pObj->GetY())
		{
			m_bMove = true;
			m_xCenter = pObj->m_xPos;
			m_yCenter = pObj->m_yPos;
			g_pMainState->m_Canvas.SetRedrawAll(false);
		}
	}
	if (!m_bMove)
	{
		return true;
	}

	int _320 = g_half320;
	int _240 = g_half240;
	if (m_xCenter < _320)m_xCenter = _320;
	if (m_yCenter < _240)m_yCenter = _240;
	if (m_xCenter > (float)m_Width - _320 - 1)m_xCenter = (float)m_Width - _320 - 1;
	if (m_yCenter > (float)m_Height - _240 - 1)m_yCenter = (float)m_Height - _240 - 1;
	
	
	m_xCenterOffset = GetXCenter() % 320;
	m_yCenterOffset = GetYCenter() % 240;

	//如果X Y方向上都发生了改变
	if (m_xCenterNum != (GetXCenter() / 320) || m_yCenterNum != (GetYCenter() / 240))
	{
		while (!m_bLoadReady2)
		{
			Sleep(1);
//			_mySleep->sleep(1);
		}
		MoveMap();
	}
	return true;
}

bool cMap::SetCenter(float xHero, float yHero)
{
	m_xCenter = xHero;
	m_yCenter = yHero;
	float _320 = g_half320;
	float _240 = g_half240;
	if (xHero < _320)
		m_xCenter = _320;
	else
		if (xHero>float(m_Width - _320 - 1))
			m_xCenter = (float)(m_Width - _320 - 1);
	if (yHero < _240)
		m_yCenter = _240;
	else
		if (yHero>(float)(m_Height - _240 - 1))
			m_yCenter = (float)(m_Height - _240 - 1);
	return true;
}

void cMap::CountAlpha(WPixel& color1, WPixel& color2, uchar* pPic,int index2,int time)
{
	WPixel color3;
	color3.red = color1.red + (color2.red - color1.red) / time;
	color3.green = color1.green + (color2.green - color1.green) / time;
	color3.blue = color1.blue + (color2.blue - color1.blue) / time;
	pPic[index2] = color3.l;
	pPic[index2 + 1] = color3.h;
}


void cMap::xMove(int x)
{
	if (0 == x)return;
	if (x > 0)
	{
		if (x * m_AddSpeed > m_xPreSpeed)
		{
			m_xPreSpeed += 1;
			m_xCenter += m_xPreSpeed / m_AddSpeed;
		}
		else  m_xCenter += x;
	}
	else
	{
		if (x * m_AddSpeed < m_xPreSpeed)
		{
			m_xPreSpeed -= 1;
			m_xCenter += m_xPreSpeed / m_AddSpeed;
		}
		else  m_xCenter += x;
	}
}
void cMap::yMove(int y)
{
	if (y > 0)
	{
		if (y * m_AddSpeed > m_yPreSpeed)
		{
			m_yPreSpeed += 1;
			m_yCenter += m_yPreSpeed / m_AddSpeed;
		}
		else  m_yCenter += y;
	}
	else
	{
		if (y * m_AddSpeed < m_yPreSpeed)
		{
			m_yPreSpeed -= 1;
			m_yCenter += m_yPreSpeed / m_AddSpeed;
		}
		else  m_yCenter += y;
	}
}

void cMap::CountMaskList()
{
	m_MaskIDList.clear();
	RECT rect,rect2;
	////////////////////////////////////////////////////////////////////////// 呵呵哒 遮罩块
	rect.left = GetXCenter() - g_half320 * 3 / 2;
	rect.right = GetXCenter() + g_half320 * 3 / 2;
	rect.top = GetYCenter() - g_half240 * 3 / 2;
	rect.bottom = GetYCenter() + g_half240 * 3 / 2;
	for (int i = 0; i < m_MaskNum; i++)
	{
		rect2.left = m_pMaskRect[i].x;
		rect2.right = m_pMaskRect[i].x + m_pMaskRect[i].w;
		rect2.top = m_pMaskRect[i].y;
		rect2.bottom = rect2.top+ m_pMaskRect[i].h;
		if (CheckCross(rect2, rect))
			m_MaskIDList.push_back(i);
	}
}




bool cBmp::Load(char* Name)
{
	if (oldmap == Name)
		return true;
	string txtmap; // = g_pathMap + Name + ".map";
// 	_reader->load(Name);
// 	m_Width = _reader->m_mw;
// 	m_Height = _reader->m_mh;
// 
// 	return true;


	locale::global(locale(""));//将全局区域设为操作系统默认区域
	ifstream file(Name, ios::binary | ios::in);
	locale::global(locale("C"));//还原全局区域设定
	if (!file)
		ERRBOX;
	cMap::SMap_Header mapFileHeader;
	file.read((char*)&mapFileHeader, sizeof(cMap::SMap_Header));
	// 计算地图的大小,数量,并分配内存
	int m_HeightNum = (int)ceil((float)mapFileHeader.map_height / 240.0f);
	int m_WidthNum = (int)ceil((float)mapFileHeader.map_width / 320.0f);
	m_Width = mapFileHeader.map_width;// m_WidthNum * 320;
	m_Height = mapFileHeader.map_height;//m_HeightNum * 240;

	_fold2s.resize(ceil(m_Height * 1.0f / 240) * 12);
	for (int i = _fold2s.size() - 1; i >= 0; --i)
	{
		_fold2s[i].resize(ceil(m_Width * 1.0f / 320) * 16);
		for (int k = 0; k < _fold2s[i].size(); ++k)
		{
			_fold2s[i][k] = false;
		}
	}

	//----------------------------------
	// 读地图块的偏移信息
	//----------------------------------
	int block_num = m_WidthNum * m_HeightNum;
	uint *m_pBlockOffset = new uint[block_num];
	file.read((char*)m_pBlockOffset, sizeof(uint)*block_num);

	// 地图的单元头
	struct UnitHeader
	{
		unsigned int Flag;		// 单元标志
		unsigned int Size;		// 单元大小
	};

	for (int UnitNum = 0; UnitNum < block_num; ++UnitNum)
	{
		long seek;
		bool loop = true;
		seek = m_pBlockOffset[UnitNum];
		file.seekg(seek);
		{
			unsigned int Num = 0; // 单元开始的头4个字节
			file.read((char*)&Num, sizeof(unsigned int));
			unsigned int *unitHead = new unsigned int[Num];
			for (int i = 0; i < Num; i++)
			{
				file.read((char*)&unitHead[i], sizeof(unsigned int));
			}
		}

		UnitHeader *unit = new UnitHeader[1];
		ZeroMemory(unit, sizeof(UnitHeader));

		int offy = (UnitNum / m_WidthNum) * 12;
		int offx = (UnitNum % m_WidthNum) * 16;
		while (loop)
		{
			file.read((char*)unit, sizeof(UnitHeader));
			switch (unit->Flag)
			{
			case 0x494D4147:
				// 2KSM "32 4B 53 4D"
			case 0x4D534B32:
				// KSAM "4B 53 41 4D"
			case 0x4D41534B:
				// GEPJ "47 45 50 4A"
			case 0x4A504547:
			case 1246775090:
				// KOLB "4B 4F 4C 42"
			case 0x424C4F4B:
			{
				unsigned char *data = new unsigned char[unit->Size];
				file.read((char*)data, unit->Size);
				delete[] data;
			}
				break;
			// LLEC "4C 4C 45 43"
			case 0x43454C4C:
			{
				unsigned char *data = new unsigned char[unit->Size];
				file.read((char*)data, unit->Size);
				for (int i = 0; i < unit->Size; ++i)
				{
					int x = ((i) % 16) + offx;
					int y = ((i) / 16) + offy;
					if (*(data + i)/* || x >= (m_WidthNum * 16) || y >= (m_HeightNum * 12)*/)
					{
						_fold2s[y][x] = true;
					}
				}
				delete[] data;
			}
				break;
				// GIRB "47 49 52 42"
			case 0x42524947:
// 			{
// 				unsigned char *data = new unsigned char[unit->Size];
// 				file.read((char*)data, unit->Size);
// 				vector<unsigned char> data2;
// 				for (int i = 0; i < unit->Size; ++i)
// 				{
// 					data2.push_back(*(data + i));
// 				}
// 				wstring str = (wchar_t*)data;
// 				delete[] data;
// 			}
// 				break;
				// TGIL "54 47 49 4C"
			case 0x4C494754:
			{
				unsigned char *data = new unsigned char[unit->Size];
				file.read((char*)data, unit->Size);
				delete[] data;
			}
				break;
				//  DNE "20 44 4E 45"
			case 0x454E4420:
				loop = false;
				break;
			default:
				loop = false;
				break;
			}
		}
		delete[] unit;
	}
	delete[] m_pBlockOffset;
	file.close();
	return true;

	stringstream oss("");
//	oss << g_pathMap << Name << ".bmp";
	string textbmp = oss.str();
	//得到地图的高度 MASK的高度要和地图的高度一致,否则计算不正确
	ifstream File2;
	File2.open(txtmap, ios::binary | ios::in);
	if (!File2)
		ERRBOX;
	cMap::SMap_Header	FileHeader2;
	File2.read((char*)&FileHeader2, sizeof(cMap::SMap_Header));//读取地图头
	m_Height = FileHeader2.map_height;
	File2.close();
	//
	ifstream File;
	File.open(textbmp, ios::binary);
	if (!File)
		ERRBOX;
	BITMAPFILEHEADER FileHeader;		// bitmap file-header
	BITMAPINFO info;
	File.read((char*)&FileHeader, sizeof(BITMAPFILEHEADER));
	File.read((char*)&info, sizeof(BITMAPINFO));
	m_Width = info.bmiHeader.biWidth;
	File.seekg(FileHeader.bfOffBits,ios::beg);  //设置输入流的指针位置
	
	int wpitch = (m_Width + 7)>>3;
	int gap = (info.bmiHeader.biHeight - m_Height) *wpitch;
	int size = (wpitch*m_Height);
	if (m_capacity < size)
	{
		Free();
		m_capacity = size;
		m_pBmp = new uchar[size];
	}
	File.read((char*)m_pBmp, gap);
	File.read((char*)m_pBmp, size);
	File.close();
	return true;
}

bool cBmp::isFold(int x, int y)
{
	x /= 20;
	y /= 20;
//	return _reader->_astar.isObstacle(x, y);


	if (x < 0 || x >= _fold2s.front().size())
		return true;
	if (y < 0 || y >= _fold2s.size())
		return true;
	return _fold2s[y][x];



// 		_cell2s[y][x - 1] ||
// 		_cell2s[y][x + 1] ||
// 		_cell2s[y - 1][x] ||
// 		_cell2s[y - 1][x - 1] ||
// 		_cell2s[y - 1][x + 1] ||
// 		_cell2s[y + 1][x] ||
// 		_cell2s[y + 1][x - 1] ||
// 		_cell2s[y + 1][x + 1];
	int index = (m_Height - 1 - y)*m_Width + x;
	if (m_pBmp[index >> 3])return true; return false;
}

cBmp::~cBmp()
{
	Free();
}

bool cBmp::Free()
{
	SAFE_DELETE_ARRAY(m_pBmp);
	return true;
}

