#include "cWas.h"

cWas::~cWas()
{
	if (_file != nullptr)
	{
		fclose(_file);
		_file = nullptr;
	}
}

bool cWas::load(const std::string &filename)
{
	_file = fopen(filename.c_str(), "rb");
	if (_file == nullptr)
	{
		return false;
	}
	uint offset;
	fread(&offset, 1, 4, _file);
	if (offset != 'WDFP') // 0x57444650
	{
		fclose(_file);
		_file = nullptr;
		return false;
	}
	fread(&_indexsCount, 1, 4, _file);
	fread(&offset, 1, 4, _file);

	_indexs = new sIndex[_indexsCount];
	fseek(_file, offset, SEEK_SET);

	auto indexs = _indexs;
	for (int k = 0; k < _indexsCount; ++k, ++indexs)
	{
		fread(indexs, 1, 12, _file);
		// space
		fseek(_file, 4, SEEK_CUR);
	}
	return true;
}


const cWas::sIndex* cWas::search2(ulong uid)
{
	uint begin = 0, end = _indexsCount - 1, middle;

	if (uid < (_indexs + begin)->uid || uid >(_indexs + end)->uid)
	{
		return nullptr;
	}

	auto _middle = _indexs;
	while (begin <= end)
	{
		middle = (begin + end) >> 1;
		_middle = _indexs + middle;
		if (_middle->uid == uid)
		{
			return _middle;
		}
		else if (_middle->uid < uid)
		{
			begin = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	return nullptr;
}


const char* cWas::getData(const sIndex* idx, bool isJudgeSp /* = false */)
{
	if (isJudgeSp)
	{
		static char ptr2[2];
		fseek(_file, idx->offset, SEEK_SET);
		fread(ptr2, 1, 2, _file);
		if (*(ushort*)ptr2 != 0x5053)
		{
			return nullptr;
		}
	}
	auto ptr = new char[idx->size];
	fseek(_file, idx->offset, SEEK_SET);
	fread(ptr, 1, idx->size, _file);
	return ptr;

}


const char* cWas::getData(ulong uid, int& size)
{
	auto idx = search2(uid);
	if (idx == nullptr)
	{
		return nullptr;
	}
	size = idx->size;
	return getData(idx);
}



//////////////////////////////////////////////////////////////////////////
const bool sSpFrame::isValid() const
{
	return w > 0 && h > 0;
}

//////////////////////////////////////////////////////////////////////////
sSpInfo::~sSpInfo()
{
	ccc_delete_array(frames);
}

const bool sSpInfo::isValid() const
{
	return frames != nullptr;
}

int sSpInfo::load(const char* ptr, bool easy16)
{
	directionsCount = *(ushort*)(ptr + 4);
	framesCountPerDirection = *(ushort*)(ptr + 6);
	width = *(ushort*)(ptr + 8);
	height = *(ushort*)(ptr + 10);
	kx = *(short*)(ptr + 12);
	ky = *(short*)(ptr + 14);
	framesCount = directionsCount * framesCountPerDirection;
	if (easy16)
	{
		return 0;
	}

	ushort head = *(ushort*)(ptr + 2);
	head += 4;
	ptr += head;
//	palette = (s565*)ptr;

	ulong* offsets = (ulong*)(ptr + 512);
	frames = new sSpFrame[framesCount];
//	decodes = new sSpDecode[total];

	auto frame = frames;
	auto offs = offsets;
	for (int k = 0; k < framesCount; ++k, ++frame, ++offs)
	{
		if (*offs == 0)
		{
			continue;
		}
		memcpy(frame, (ptr + *offs), 16);
	}
	return head;
}

