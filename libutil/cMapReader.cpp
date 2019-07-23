#include "cMapReader.h"
#include <fstream>
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

static void ByteSwap(ushort& value) { value = (value << 8) | (value >> 8); }

static uchar* JpgHandler(uchar* Buffer, int inSize, uint* outSize)
{
	static int m_TempBufferNum = inSize;
	static uchar* m_pTempBuffer = (uchar*)malloc(m_TempBufferNum << 1);
	if (inSize > m_TempBufferNum)
	{
		// 临时变量，表示处理后的数据
		m_pTempBuffer = (uchar*)realloc(m_pTempBuffer, (inSize << 1));
		m_TempBufferNum = inSize;
	}
	// JPEG数据处理原理
	// 1、复制D8到D9的数据到缓冲区中
	// 2、删除第3、4个字节 FFA0
	// 3、修改FFDA的长度00 09 为 00 0C
	// 4、在FFDA数据的最后添加00 3F 00
	// 5、替换FFDA到FF D9之间的FF数据为FF 00
	uint TempNum = 0;						// 临时变量，表示已读取的长度
	uchar* pTemp = m_pTempBuffer;	// 已处理数据的开始地址
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

			memcpy(&TempTimes/*, sizeof(ushort)*/, Buffer, sizeof(ushort)); // 读取长度
			ByteSwap(TempTimes); // 将长度转换为Intel顺序


			for (int i = 0; i < TempTimes; i++)
			{
				*m_pTempBuffer++ = *Buffer++;
				TempNum++;
			}

			break;
		case 0xC4:
			*m_pTempBuffer++ = 0xC4;
			*Buffer++;
			TempNum++;

			memcpy(&TempTimes/*, sizeof(ushort)*/, Buffer, sizeof(ushort)); // 读取长度
			ByteSwap(TempTimes); // 将长度转换为Intel顺序

			for (int i = 0; i < TempTimes; i++)
			{
				*m_pTempBuffer++ = *Buffer++;
				TempNum++;
			}
			break;
		case 0xDB:
			*m_pTempBuffer++ = 0xDB;
			*Buffer++;
			TempNum++;

			memcpy(&TempTimes/*, sizeof(ushort)*/, Buffer, sizeof(ushort)); // 读取长度
			ByteSwap(TempTimes); // 将长度转换为Intel顺序

			for (int i = 0; i < TempTimes; i++)
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

			memcpy(&TempTimes, /*sizeof(ushort),*/ Buffer, sizeof(ushort)); // 读取长度
			ByteSwap(TempTimes); // 将长度转换为Intel顺序
			*Buffer++;
			TempNum++;
			*Buffer++;

			for (int i = 2; i < TempTimes; i++)
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
	m_pTempBuffer = pTemp;
	return pTemp;
}

static const int c320 = cMapReader::c320, c240 = cMapReader::c240, c12 = cMapReader::c12, c16 = cMapReader::c16, c20 = cMapReader::c20;

sMapDecode::~sMapDecode()
{
	ccc_delete_array(decodes);
}

const bool sMapDecode::isValid() const
{
	return decodes != nullptr && sSpFrame::isValid();
}

//////////////////////////////////////////////////////////////////////////
bool sMapDecode::decode(uchar* ptr)
{
	if (decodes != nullptr)
	{
		return true;
	}
	auto p = ptr + 16;
	int maskSize = *(int*)p;
	p += 4;
	if (maskSize == 0)
	{
		return false;
	}
	// alignment 4
	int aiginw = ((w >> 2) + (w % 4 != 0)) << 2;
	uchar* pMaskData = p;
	// 4 pixel per Byte, so >> 2
	int mask_index = (aiginw * h) >> 2;
	static int decSize = mask_index;
	static uchar* pMaskDec = (uchar*)malloc(decSize);
	if (mask_index > decSize)
	{
		pMaskDec = (uchar*)realloc(pMaskDec, decSize = mask_index);
	}
	decompress(pMaskData, maskSize, pMaskDec);

	static uchar mask_value;
	decodes = new uchar[w * h];
	memset(decodes, 0, w * h);
	auto decs = decodes;
	for (int k = 0; k < h; ++k)
	{
		for (int i = 0; i < w; ++i, ++decs)
		{
			mask_index = (k * aiginw + i) << 1;			// bit
			mask_value = pMaskDec[mask_index >> 3];		// to byte
			mask_value = mask_value >> (mask_index % 8);// to bit
			if ((mask_value & 3) == 3)
			{
				*decs = 0x0F;
			}
		}
	}
	return true;
}


sMapAlpha::~sMapAlpha()
{
	ccc_delete(bmp);
}

const bool sMapAlpha::isValid() const
{
	return bmp != nullptr;
}

//////////////////////////////////////////////////////////////////////////
cAlphaBmp* sMapAlpha::getAlpha(cBmp* bitmap, const uchar* decodes, int mw)
{
	if (bmp != nullptr)
	{
		return bmp;
	}
	bmp = new cAlphaBmp(w, h);
	s565* bData, *pD;
	auto alphas = decodes + y * mw + x;
	auto pA = bmp->ChannelLine(0);
	for (int k = 0; k < h; ++k, alphas += mw)
	{
		bData = (s565*)((*bitmap)[by + k]);
		pD = (s565*)((*bmp)[k]);
		memcpy(pD, bData + bx, w * 2);
		pA = bmp->ChannelLine(k);
		memcpy(pA, alphas, w);
		for (int i = 0; i < w; ++i, ++pD, ++pA)
		{
			pD->toAlpha(*pA);
		}
	}
	return bmp;
}


static void insert(std::vector<sMapAlpha>& alphas, int bx, int by, int x, int y, int w, int h, int maskIdx)
{
	static sMapAlpha a;
	a.bx = bx, a.by = by, a.x = x, a.y = y, a.w = w, a.h = h, a.maskIdx = maskIdx;
	alphas.push_back(a);
}


//////////////////////////////////////////////////////////////////////////
sMap::sImage::~sImage()
{
	ccc_delete_array(image);
	imageSize = 0;
}


const bool sMap::sImage::isValid() const
{
	return image != nullptr && imageSize != 0;
}

void sMap::sImage::reset()
{
	image = nullptr;
	imageSize = 0;
}

//////////////////////////////////////////////////////////////////////////
sMap::sBMP::~sBMP()
{
	if (jpegBmp != nullptr)
	{
		destroy_bitmap(jpegBmp);
	}
	ccc_delete(bmp);
}


const bool sMap::sBMP::isValid() const
{
	return jpegBmp != nullptr && bmp != nullptr;
}

//////////////////////////////////////////////////////////////////////////
sMap::~sMap()
{
	clear();
}


bool sMap::load(const char* _ptr)
{
	if (blockOffs != nullptr)
	{
		return true;
	}
	ptr = _ptr;
	info.mw = *(uint*)(ptr + 4);
	info.mh = *(uint*)(ptr + 8);
	info.bw = std::ceil(info.mw * 1.0f / c320);
	info.bh = std::ceil(info.mh * 1.0f / c240);
	blocksCount = info.bw * info.bh;
	blockOffs = (uint*)(ptr + 12);
	return true;
}


bool sMap::loadMask()
{
	if (masks != nullptr)
	{
		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	std::vector<sMapAlpha> as;
	sBMP bmp;
	sImage image;
	for (int k = 0; k < blocksCount; ++k)
	{
		images.insert(std::make_pair(k, image));
		bmps.insert(std::make_pair(k, bmp));
		alphas.insert(std::make_pair(k, as));
	}
	//////////////////////////////////////////////////////////////////////////
	auto _ptr = ptr + (12 + 4 * blocksCount + 4);
	masksCount = *(uint*)_ptr;
	maskOffs = (uint*)(_ptr + 4);
	auto mOffs = maskOffs;
	masks = new sMapDecode[masksCount];
	auto m = masks;
	sMapAlpha a;
	int ix, iy, ix2, iy2, k, i;
	int bx, by, rx, ry, rw, rh;
	for (int n = 0; n < masksCount; ++n, ++mOffs, ++m)
	{
		_ptr = ptr + *mOffs;
		memcpy(m, _ptr, 16);
		ix = m->x / c320, iy = m->y / c240, ix2 = (m->x + m->w - 1) / c320, iy2 = (m->y + m->h - 1) / c240;
		if (ix == ix2 && iy == iy2)
		{
			bx = ix * c320;
			by = iy * c240;
			insert(alphas.at(iy * info.bw + ix), m->x - bx, m->y - by, 0, 0, m->w, m->h, n);
			continue;
		}
		for (k = iy; k <= iy2; ++k)
		{
			for (i = ix; i <= ix2; ++i)
			{
				bx = i * c320;
				by = k * c240;
				rx = std::max(bx, m->x);
				ry = std::max(by, m->y);
				rw = std::min(bx + c320, m->x + m->w);
				rh = std::min(by + c240, m->y + m->h);
				insert(alphas.at(k * info.bw + i), rx - bx, ry - by, rx - m->x, ry - m->y, rw - rx, rh - ry, n);
			}
		}
	}
	return true;
}


bool sMap::loadObstacles()
{
	if (obstacles != nullptr)
	{
		return true;
	}
	int ow = info.bw * c16;
	int offy = info.bh * c12;
	obstacles = new uchar[ow * offy];
	memset(obstacles, cAstar::cObstacle, ow * offy);
	auto obs = obstacles;
	uint flag, size;
	auto bOffs = blockOffs;
	auto _ptr = ptr;
	for (int k = 0; k < info.bh; ++k)
	{
		offy = k * c12 * ow;
		for (int i = 0; i < info.bw; ++i, ++bOffs)
		{
			_ptr = ptr + (*bOffs);
			flag = *(uint*)_ptr;
			_ptr += 4;
			if (flag > 0)
			{
				_ptr += (flag << 2);
			}
			bool loop = true;
			while (loop)
			{
				flag = *(uint*)_ptr;
				size = *(uint*)(_ptr + 4);
				_ptr += 8;
				switch (flag)
				{
				case 0x43454C4C: // LLEC "4C 4C 45 43"
					// 默认填1
					flag = -1;
					obs = obstacles + offy + i * c16;
					while (++flag < size)
					{
						if (*_ptr == 0)
						{
							*(obs + (flag / c16 * ow) + (flag % c16)) = 0;
						}
						++_ptr;
					}
					break;
				case 0x494D4147:
				case 0x4D534B32: // 2KSM "32 4B 53 4D"
				case 0x4D41534B: // KSAM "4B 53 41 4D"
				case 0x4A504547: // GEPJ "47 45 50 4A"
				case 1246775090: // 2GPJ
				case 0x424C4F4B: // KOLB "4B 4F 4C 42"
					_ptr += size;
				break;
				case 0x42524947: // GIRB "47 49 52 42"
				case 0x4C494754: // TGIL "54 47 49 4C"
					break;
				case 0x454E4420: //  DNE "20 44 4E 45"
				default:
					loop = false;
					break;
				}
			}
		}
	}
	return true;
}


bool sMap::isObstacle(int x20, int y20)
{
	if (x20 < 0 || y20 < 0 || x20 >= (info.bw * c16) || y20 >= (info.bh * c12))
	{
		return true;
	}
	return *(obstacles + y20 * info.bw * c16 + x20) != 0;
}

sMap::sImage& sMap::getImage(int blockIdx, bool alloc)
{
	auto& image = images.at(blockIdx);
	if (image.isValid())
	{
		return image;
	}

	auto p = ptr + *(blockOffs + blockIdx);
	uint size = *(uint*)p;
	if (size > 0)
	{
		p += (size << 2);
	}
	uint flag = *(uint*)(p + 4);
	size = *(uint*)(p + 8);
	p += 12;
	uchar* pJpgData = nullptr;
	if (flag == 'JPG2')
	{
		pJpgData = (uchar*)p;
	}
	else if (flag == 'JPEG')
	{
		pJpgData = JpgHandler((uchar*)p, size, &flag);
		size = flag;
	}

	image.imageSize = size;
	if (alloc)
	{
		uchar* ima = new uchar[size];
		memcpy(ima, pJpgData, size);
		image.image = ima;
	}
	else
	{
		image.image = pJpgData;
	}
	return image;
}

const sMap::sImage& sMap::getImage(int blockIdx)
{
	return getImage(blockIdx, true);
}

const sMap::sBMP& sMap::getBMP(int blockIdx, bool alloc)
{
	auto& b = bmps.at(blockIdx);
	if (b.isValid())
	{
		return b;
	}
	auto& image = getImage(blockIdx, alloc);
	if (!image.isValid())
	{
		static sBMP bmpEmpty;
		return bmpEmpty;
	}
	static bool s_isNotSetted = true;
	if (s_isNotSetted)
	{
		jpeg_setcolormode(0, 1);
		s_isNotSetted = false;
	}
	b.jpegBmp = Unpak_jpg(image.image, image.imageSize);
	b.bmp = new cBmp(c320, c240, ((BMP*)b.jpegBmp)->line[0]);
	image.reset();
	return b;
}

cBmp* sMap::getBitmap(int blockIdx)
{
	return getBMP(blockIdx, false).bmp;
}


bool sMap::isLoaded()
{
	for (const auto& bmp : bmps)
	{
		if (!bmp.second.isValid())
		{
			return false;
		}
	}
	return true;
}


void sMap::clear()
{
	ccc_delete(astar);
	ccc_delete_array(masks);
	ccc_delete_array(obstacles);
}


bool sMap::search(const cocos2d::Vec2& Start, const cocos2d::Vec2& End, std::vector<cocos2d::Vec2>& paths)
{
	if (!loadObstacles())
	{
		return false;
	}

	cAstar::sXY vStart, vEnd;
	vStart.x = Start.x / c20;
	vStart.y = Start.y / c20;
	vEnd.x = End.x / c20;
	vEnd.y = End.y / c20;
	if (isObstacle(vEnd.x, vEnd.y))
	{
		return false;
	}

	if (astar == nullptr)
	{
		astar = new cAstar();
		astar->load(info.bw * c16, info.bh * c12, obstacles);
	}

	if (!astar->search(vStart, vEnd))
	{
		return false;
	}
	if (!astar->next(vEnd))
	{
		return false;
	}
	cocos2d::Vec2 v;
	paths.clear();
	do
	{
		v.x = vEnd.x * c20 + c20 / 2;
		v.y = vEnd.y * c20 + c20 / 2;
		paths.push_back(v);
		if (vStart.x == vEnd.x && vStart.y == vEnd.y)
		{
			break;
		}
	} while (astar->next(vEnd));
	return true;
}



//////////////////////////////////////////////////////////////////////////
const bool sMapCache::isValid() const
{
	return pMap != nullptr;
}


//////////////////////////////////////////////////////////////////////////
cMapReader::~cMapReader()
{
	for (auto& cache : _caches)
	{
		auto& pMap = cache.second.pMap;
		ccc_delete_array(pMap->ptr);
		ccc_delete(pMap);
	}
}

cMapReader::cMapReader()
{
	std::map<int, std::string> sec;
	_searchs.insert(std::make_pair(eMapType::wm, sec));
	_searchs.insert(std::make_pair(eMapType::jd, sec));
	_searchs.insert(std::make_pair(eMapType::iter, sec));
}

cMapReader* cMapReader::getInstance()
{
	static cMapReader* s_reader = new cMapReader();
	return s_reader;
}


bool cMapReader::isMap(const char* ptr) { uint flag = *(uint*)ptr; return flag == 'MAPX' || flag == 'M1.0'; }


const char* cMapReader::getData(const std::string& filenameWithoutRoot)
{
	static std::ifstream ifile;
	static char ptr4[4];
	int size;
	auto path = filenameWithoutRoot;
	if (filenameWithoutRoot.find(cFolder::cFlag) != std::string::npos)
	{
		path = cFolder::getInstance()->getRoot() + filenameWithoutRoot;
	}
	ifile.open(path, std::ios::binary | std::ios::in);
	if (ifile.is_open())
	{
		ifile.read(ptr4, 4);
		if (!isMap(ptr4))
		{
			ifile.close();
			return nullptr;
		}
		ifile.seekg(0, std::ios::end);
		auto ptr = new char[size = ifile.tellg()];
		ifile.seekg(std::ios::beg);
		ifile.read(ptr, size);
		ifile.close();
		return ptr;
	}
	return nullptr;
}


const std::string& cMapReader::getFileNameWithoutRoot(eMapType e, int mapid)
{
	auto& searchs = _searchs.at(e);
	const auto& it = searchs.find(mapid);
	if (it != searchs.end())
	{
		return it->second;
	}
	std::string name = toString("%d.map", mapid);
	auto fol = cFolder::getInstance();
	auto root = fol->getRoot();
	const auto& folders = fol->getMaps().at(e);
	for (const auto& folder : folders)
	{
		static std::ifstream ifile;
		ifile.open(root + folder + name, std::ios::binary);
		if (ifile.is_open())
		{
			ifile.close();
			searchs.insert(std::make_pair(mapid, folder + name));
			return searchs.at(mapid);
		}
	}
	// 引用,所以也要常驻周期
	static std::string s_strEmpty;
	return s_strEmpty;
}


sMapCache cMapReader::getCache(eMapType e, int mapid)
{
	sMapCache c;
	const auto& filenameWithoutRoot = getFileNameWithoutRoot(e, mapid);
	if (filenameWithoutRoot.empty())
	{
		return c;
	}
	const auto& it = _caches.find(filenameWithoutRoot);
	if (it != _caches.end())
	{
		++it->second.ref;
		c.e = e;
		c.mapid = mapid;
		c.filenameWithoutRoot = filenameWithoutRoot;
		c.pMap = it->second.pMap;
		return c;
	}
	auto ptr = getData(filenameWithoutRoot);
	if (ptr == nullptr)
	{
		return c;
	}
	sRef ref;
	ref.ref = 1;
	ref.pMap = new sMap();
	ref.pMap->load(ptr);
	_caches.insert(std::make_pair(filenameWithoutRoot, ref));
	c.filenameWithoutRoot = filenameWithoutRoot;
	c.mapid = mapid;
	c.pMap = ref.pMap;
	return c;
}


bool cMapReader::freeCache(const sMapCache& cache)
{
	auto& it = _caches.find(cache.filenameWithoutRoot);
	if (it == _caches.end())
	{
		return false;
	}
	auto& c = it->second;
	if ((--c.ref) == 0)
	{
		ccc_delete_array(c.pMap->ptr);
		ccc_delete(c.pMap);
		_caches.erase(it);
		return true;
	}
	return false;
}