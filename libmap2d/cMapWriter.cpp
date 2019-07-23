#include "cMapWriter.h"
#include "../libwas/_inc.h"

#include "stdlib.h"
#include "../libpng/png.h"
#pragma comment(lib, "../libpng/libpng")
#pragma comment(lib, "../libpng/libzlib")

static bool hasAlpha() { return true; }
static bool save2png(const char* filename, unsigned char* _data, int _width, int _height)
{
	bool isToRGB = false;

	// #if CC_USE_WIC
	// 	return encodeWithWIC(filePath, isToRGB, GUID_ContainerFormatPng);
	// #elif CC_USE_PNG
	bool ret = false;
	do
	{
		FILE *fp = nullptr;
		png_structp png_ptr;
		png_infop info_ptr;
		png_colorp palette;
		png_bytep *row_pointers;

		// 		fp = fopen(FileUtils::getInstance()->getSuitableFOpen(filePath).c_str(), "wb");
		//		CC_BREAK_IF(nullptr == fp);
		fp = fopen(filename, "wb");
		if (fp == nullptr)
		{
			break;
		}

		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

		if (nullptr == png_ptr)
		{
			fclose(fp);
			break;
		}

		info_ptr = png_create_info_struct(png_ptr);
		if (nullptr == info_ptr)
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr, nullptr);
			break;
		}


#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA && CC_TARGET_PLATFORM != CC_PLATFORM_NACL && CC_TARGET_PLATFORM != CC_PLATFORM_TIZEN)
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			break;
		}
#endif
		png_init_io(png_ptr, fp);

		if (!isToRGB && hasAlpha())
		{
			png_set_IHDR(png_ptr, info_ptr, _width, _height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
				PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
		}
		else
		{
			png_set_IHDR(png_ptr, info_ptr, _width, _height, 8, PNG_COLOR_TYPE_RGB,
				PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
		}

		palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * sizeof(png_color));
		png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);

		png_write_info(png_ptr, info_ptr);

		png_set_packing(png_ptr);

		row_pointers = (png_bytep *)malloc(_height * sizeof(png_bytep));
		if (row_pointers == nullptr)
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			break;
		}

		if (!hasAlpha())
		{
			for (int i = 0; i < (int)_height; i++)
			{
				row_pointers[i] = (png_bytep)_data + i * _width * 3;
			}

			png_write_image(png_ptr, row_pointers);

			free(row_pointers);
			row_pointers = nullptr;
		}
		else
		{
			if (isToRGB)
			{
				unsigned char *tempData = static_cast<unsigned char*>(malloc(_width * _height * 3 * sizeof(unsigned char)));
				if (nullptr == tempData)
				{
					fclose(fp);
					png_destroy_write_struct(&png_ptr, &info_ptr);

					free(row_pointers);
					row_pointers = nullptr;
					break;
				}

				for (int i = 0; i < _height; ++i)
				{
					for (int j = 0; j < _width; ++j)
					{
						tempData[(i * _width + j) * 3] = _data[(i * _width + j) * 4];
						tempData[(i * _width + j) * 3 + 1] = _data[(i * _width + j) * 4 + 1];
						tempData[(i * _width + j) * 3 + 2] = _data[(i * _width + j) * 4 + 2];
					}
				}

				for (int i = 0; i < (int)_height; i++)
				{
					row_pointers[i] = (png_bytep)tempData + i * _width * 3;
				}

				png_write_image(png_ptr, row_pointers);

				free(row_pointers);
				row_pointers = nullptr;

				if (tempData != nullptr)
				{
					free(tempData);
				}
			}
			else
			{
				for (int i = 0; i < (int)_height; i++)
				{
					row_pointers[i] = (png_bytep)_data + i * _width * 4;
				}

				png_write_image(png_ptr, row_pointers);

				free(row_pointers);
				row_pointers = nullptr;
			}
		}

		png_write_end(png_ptr, info_ptr);

		png_free(png_ptr, palette);
		palette = nullptr;

		png_destroy_write_struct(&png_ptr, &info_ptr);

		fclose(fp);

		ret = true;
	} while (0);
	return ret;
	// #else
	// 	CCLOG("png is not enabled, please enable it in ccConfig.h");
	// 	return false;
	// #endif // CC_USE_PNG
}


static const char* s_folderCut = "图块";
static const char* s_folderMask = "遮罩";
static const int c320 = cMapReader::c320, c240 = cMapReader::c240;

bool cMapWriter::init(const std::string& path, int mapid, cLabel* labelMapid, cLabel* labelDesc)
{
	if (!cSprite::init())
	{
		return false;
	}
	_path = path;
	_labelMapid = labelMapid;
	_labelMapid->setColor(s888::GREEN);

	_path = path + toString("%04d.map", _id = mapid);
	auto ptr = cMapReader::getData(_path);

	if (ptr == nullptr)
	{
		_labelMapid->setString(_path + "无法读取");
		return false;
	}
	_m.clear();
	if (!_m.load(ptr))
	{
		_labelMapid->setString(_path + "无法读取");
		return false;
	}
	_m.loadMask();


	mapid = gge::System_GetState(gge::GGE_STATE_INT::GGE_TEXTURESIZE);
	const auto& info = _m.info;
	while (info.mw / _smalltimes > mapid || info.mh / _smalltimes > mapid)
	{
		++_smalltimes;
	}

	if (_smalltimes > 1)
	{
		_labelMapid->setColor(s888::RED);
		_labelMapid->setString(cc::toString(_id) + " 超过显卡最大纹理尺寸,导出大图将格外耗费内存");
		_data = new uint[info.mw * info.mh];
		_dataMask = new uint[info.mw * info.mh];
		memset(_dataMask, 0, info.mw * info.mh * 4);
	}
	else
	{
		_labelMapid->setString(cc::toString(_id));
	}

	_texture = gge::Texture_Create(info.mw / _smalltimes, info.mh / _smalltimes);
	_textureMask = gge::Texture_Create(_texture->GetWidth(), _texture->GetHeight());
	auto ptrMask = _textureMask->Lock();
	memset(ptrMask, 0, _textureMask->GetWidth() * _textureMask->GetHeight() * 4);
	_textureMask->Unlock();
//	_texture->FillColor(0);
//	_textureMask->FillColor(0);
	cSprite::setTexture(_texture);
//	cSprite::setTextureRect(Rect(0, 0, _texture->GetWidth(), _texture->GetHeight())); // 到底要不要设置区域
	this->setContentSize(Size(_texture->GetWidth(), _texture->GetHeight()));

	_labelDesc = labelDesc;
	_labelDesc->setColor(s888::YELLOW);

	auto& image = _m.getImage(0, false);
	if(image.isValid())
	{
		_path = path + toString("%d/%s/", _id, s_folderCut);
		ccc_md(_path);
		_path = path + toString("%d/%s/", _id, s_folderMask);
		ccc_md(_path);
	}
	_path = path;
	scheduleUpdate();
	return true;
}

// 一个色点的类型 (暂时不能修改)
typedef unsigned short int PIXEL;
// 游戏库中使用的不压缩的位图结构
typedef struct {
	int w, h, pitch;      //位图宽和高以及每行实际字节数
	int cl, ct, cr, cb;    //位图剪裁矩形的左上角顶点坐标
	//剪裁矩形的宽和高
	PIXEL *line[1];     //创建位图时动态分配大小
} BMP;

bool cMapWriter::readJPG(int iBlock, bool save)
{
	const auto& info = _m.info;
	int x = (iBlock % info.bw) * c320;
	int y = (iBlock / info.bw) * c240;
	uint* ptr = _texture->Lock(false, x / _smalltimes, y / _smalltimes, std::min(c320, info.mw - x) / _smalltimes, std::min(c240, info.mh - y) / _smalltimes);
	auto& image = _m.getImage(iBlock, false);
	if (!image.isValid())
	{
		return false;
	}
	gge::ggeTexture *textureCut = gge::Texture_Load((char*)image.image, 0, image.imageSize);
	image.reset();
	if (!textureCut)
	{
// 		gge::ggeTexture *textureCut = gge::Texture_Create(c320, c240);
// 		uint* data = textureCut->Lock();
// 		auto bmp = Unpak_jpg((uchar*)point.ptr, /*jpg_size*/point.size);
// 		auto line = bmp->line[0];
// 		WasReader::sRGB c;
// 		for (int i = c320 * c240 - 1; i >= 0; --i)
// 		{
// 			c.color = line[i];
// 			data[i] = ccg::color2gge32(Color4B(c.r << 3, c.g << 2, c.b << 3, 0xff));
// 		}
// 		destroy_bitmap(bmp);
// 		textureCut->Unlock();
	}
	uint* data = textureCut->Lock();


	int ix, iy, iwData;
	for (int h = 0; h < c240; h += 1/*smalltimes*/)
	{
		iy = y + h;
		if (y / c240 == info.bh - 1 && iy >= info.mh)
		{
			continue;
		}
		iwData = 1280;
		if (x / c320 == info.bw - 1)
		{
			iwData = (info.mw - x) * 4;
		}
		if (!_data)
		{
			memcpy(&ptr[h * info.mw], &data[h * c320], iwData);
		}
		else
		{
			memcpy(&_data[iy * info.mw + x], &data[h * c320], iwData);
			uchar* c;
			for (int w = iwData / 4 - 1; w >= 0; --w)
			{
				c = (uchar*)&_data[iy * info.mw + x + w];
				std::swap(c[0], c[2]);
			}

			if ((h % _smalltimes) == 0)
			{
				for (int w = 0; w < c320; w += _smalltimes)
				{
					ix = x + w;
					if (x / c320 == info.bw - 1 && ix >= info.mw)
					{
						continue;
					}
					ptr[(h / _smalltimes) * (info.mw / _smalltimes) + w / _smalltimes] = data[h * c320 + w];
				}
			}
		}
	}

// 	uchar* c;
// 	for (int i = c320 * c240 - 1; i >= 0; --i)
// 	{
// 		c = (uchar*)&data[i];
// 		std::swap(c[0], c[2]);
// 	}
// 	save2png(cpp::toString("%d/%s/%d-%02d-%02d.jpg", _id, s_folderCut, _id, iBlock % info.bw, iBlock / info.bw).c_str(), (uchar*)data, c320, c240);
	_texture->Unlock();
	textureCut->Unlock();
	if(save)
	{
		textureCut->SaveToFile(toString("%s%d/%s/%d-%02d-%02d.jpg", _path.c_str(), _id, s_folderCut, _id, iBlock % info.bw, iBlock / info.bw).c_str(), gge::GGE_IMAGE_FORMAT::IMAGE_PNG);
	}
	textureCut->Release();
	return true;
}



bool cMapWriter::readMask(int iMask)
{
	auto& mask = _m.masks[iMask];
	if (mask.x < 0 || mask.y < 0)
	{
//		ccc_delete_array(mask.masks);
		return true;
	}
	if (!mask.decode((uchar*)_m.ptr + *(_m.maskOffs + iMask)))
	{
		return true;
	}
	const auto& info = _m.info;
	int x, y;
	uint* ptr = _texture->Lock(true, mask.x / _smalltimes, mask.y / _smalltimes, std::min(mask.w, info.mw - mask.x) / _smalltimes, std::min(mask.h, info.mh - mask.y) / _smalltimes);
	uint* ptrMask = _textureMask->Lock(false, mask.x / _smalltimes, mask.y / _smalltimes, std::min(mask.w, info.mw - mask.x) / _smalltimes, std::min(mask.h, info.mh - mask.y) / _smalltimes);
	uchar* c;
	for (int h = mask.h - 1; h >= 0; --h)
	{
		for (int w = mask.w - 1; w >= 0; --w)
		{
			if (mask.decodes[h * mask.w + w])
			{
				x = mask.x + w;
				y = mask.y + h;
				if (x >= info.mw)
				{
					continue;
				}
				if (y >= info.mh)
				{
					continue;
				}
				if (_data)
				{
					_dataMask[y * info.mw + x] = _data[y * info.mw + x];
					c = (uchar*)&_dataMask[y * info.mw + x];
					c[3] = 0x88;
				}
				if ((x % _smalltimes) || (h % _smalltimes))
				{
					continue;
				}
// 				c = (uchar*)&ptr[(h / smalltimes) * (info.mw / smalltimes) + w / smalltimes];
// 				std::swap(c[0], c[2]);
// 				c[3] = 0x88;
// 				ptrMask[(h / smalltimes) * (info.mw / smalltimes) + w / smalltimes] = *(uint*)c;
				ptrMask[(h / _smalltimes) * (info.mw / _smalltimes) + w / _smalltimes] = ptr[(h / _smalltimes) * (info.mw / _smalltimes) + w / _smalltimes];
					
			}
		}
	}
	_textureMask->Unlock();
	_texture->Unlock();
//	ccc_delete_array(mask.masks);
	return true;
}


bool cMapWriter::writeMask(int iBlock)
{
	const auto& info = _m.info;
	int x = (iBlock % info.bw) * c320;
	int y = (iBlock / info.bw) * c240;
	uint* ptr = _texture->Lock(false, x / _smalltimes, y / _smalltimes, std::min(c320, info.mw - x) / _smalltimes, std::min(c240, info.mh - y) / _smalltimes);
	uint* ptrMask = _textureMask->Lock(true, x / _smalltimes, y / _smalltimes, std::min(c320, info.mw - x) / _smalltimes, std::min(c240, info.mh - y) / _smalltimes);

	uint* ptrCut = new uint[c320 * c240];
	memset(ptrCut, 0, c320 * c240 * 4);
	int iy, iwData;
	for (int h = 0; h < c240; ++h)
	{
		iy = y + h;
		if (y / c240 == info.bh - 1 && iy >= info.mh)
		{
			continue;
		}
		iwData = c320;
		if (x / c320 == info.bw - 1)
		{
			iwData = (info.mw - x);
		}
		if ((h % _smalltimes) == 0)
		{
			memcpy(&ptr[(h / _smalltimes) * (info.mw / _smalltimes)], &ptrMask[(h / _smalltimes) * (info.mw / _smalltimes)], iwData / _smalltimes * 4);
		}

		if (_data)
		{
			memcpy(&ptrCut[h * c320], &_dataMask[iy * info.mw + x], iwData * 4);
		}
		else
		{
			memcpy(&ptrCut[h * c320], &ptr[h * info.mw], iwData * 4);
			uchar* c;
			for (int w = iwData - 1; w >= 0; --w)
			{
				uint& c4 = ptrCut[h * c320 + w];
				if (c4)
				{
					c = (uchar*)&c4;
					std::swap(c[0], c[2]);
					c[3] = 0x88;
				}
			}

		}
	}
	_texture->Unlock();
	_textureMask->Unlock();
	save2png(toString("%s%d/%s/%d-%02d-%02d.png", _path.c_str(), _id, s_folderMask, _id, iBlock % info.bw, iBlock / info.bw).c_str(), (uchar*)ptrCut, c320, c240);
	delete[] ptrCut;
	return true;

}



bool cMapWriter::writeObstable()
{
	const auto& info = _m.info;
	gge::ggeTexture* textureObstacle = gge::Texture_Create(info.bw * 16, info.bh * 12);
//	textureObstacle->FillColor(0xffffffff);
	uint* ptr = textureObstacle->Lock();
	memset(ptr, 0xFF, info.bw * 16 * info.bh * 12 * 4);
	for (int k = 0; k < info.bh * 12; ++k)
	{
		for (int i = 0; i < info.bw * 16; ++i)
		{
			if (_m.isObstacle(k, i))
			{
				ptr[k * info.bw * 16 + i] = 0xff000000;
			}
		}
	}
	textureObstacle->Unlock();
	textureObstacle->SaveToFile(toString("%s%d/%d.bmp", _path.c_str(), _id, _id).c_str(), gge::GGE_IMAGE_FORMAT::IMAGE_BMP);
	textureObstacle->Release();
	return true;
}




void cMapWriter::update(float delta)
{
// 	float scroll = gge::Input_GetMouseWheel();
// 	float scale = getScale();
// 	if (scroll != 0)
// 	{
// 		scale *= 1 - scroll * 0.1f;
// 		scale = std::max(0.1f, std::min(1.0f, scale));
// 		setScale(scale);
// 	}
	const auto& info = _m.info;
#if 1
	if (_flag == 0)
	{
		if (_iblock < info.bw * info.bh)
		{
			if(readJPG(_iblock, false))
			{
				_labelDesc->setString(toString("导出切图 %d:%d", ++_iblock, info.bw * info.bh));
			}
			else 
			{
				_m.clear();
				std::string name = _path + toString("%d.map", _id);
				ccc_move(name, "error/");
				unscheduleUpdate();
				if (onFinish)
				{
					onFinish();
				}
				this->removeFromParent();
				return;
			}
		}
		else
		{
			_labelDesc->setString("导出大图.很久");
			++_flag;
		}
	}
	else if (_flag == 1)
	{
		std::string str = toString("%s%d/%d.jpg",_path.c_str(), _id, _id);
		if (_data)
		{
			save2png(str.c_str(), (uchar*)_data, info.mw, info.mh);
		}
		else
		{
			_texture->SaveToFile(str.c_str(), gge::GGE_IMAGE_FORMAT::IMAGE_PNG);
		}

		//////////////////////////////////////////////////////////////////////////
#if 1
		_texture->Release();
		_textureMask->Release();
		_labelDesc->setString("导出完毕");
		unscheduleUpdate();
		if (onFinish)
		{
			onFinish();
		}
		this->removeFromParent();
		return;
#endif
		//////////////////////////////////////////////////////////////////////////

		cSprite::setTexture(_textureMask);
		++_flag;
	}
	else if (_flag == 2)
	{
		if (_imask < _m.masksCount)
		{
			readMask(_imask);
			_labelDesc->setString(toString("分析遮罩 %d:%d", ++_imask, _m.masksCount));
		}
		else
		{
			_iblock = 0;
		//	_texture->FillColor(0);
			auto ptr = _texture->Lock();
			memset(ptr, 0, _texture->GetWidth() * _texture->GetHeight() * 4);
			_texture->Unlock();
			cSprite::setTexture(_texture);
			++_flag;
		}
	}
	else if (_flag == 3)
	{
		if (_iblock < info.bw * info.bh)
		{
			writeMask(_iblock);
			_labelDesc->setString(toString("导出遮罩 %d:%d", ++_iblock, info.bw * info.bh));
		}
		else
		{
			_labelDesc->setString("导出大遮罩.很久");
			++_flag;
		}
	}
	else if (_flag == 4)
	{
		std::string str = toString("%s%d/%d.png", _path.c_str(), _id, _id);
		if (_data)
		{
			save2png(str.c_str(), (uchar*)_dataMask, info.mw, info.mh);
			delete[] _data;
			delete[] _dataMask;
		}
		else
		{
			uint* ptr = _texture->Lock();
			uchar* c;
			for (int i = info.mw * info.mh - 1; i >= 0; --i)
			{
				if (ptr[i])
				{
					c = (uchar*)&ptr[i];
					std::swap(c[0], c[2]);
					c[3] = 0x88;
				}
			}
			save2png(str.c_str(), (uchar*)ptr, info.mw, info.mh);
			_texture->Unlock();
		}
		_texture->Release();
		_textureMask->Release();
		++_flag;
	}
	else if (_flag == 5)
	{
		_labelDesc->setString("导出完毕");
		if (_m.loadObstacles())
		{
			writeObstable();
		}
		unscheduleUpdate();
		if (onFinish)
		{
			onFinish();
		}
		this->removeFromParent();
	}
#endif
}

