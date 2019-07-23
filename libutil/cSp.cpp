#include "cSp.h"
#include "../libfolderEx/cFolder.h"

cWdf* cWdf::getColor()
{
	static cWdf* s_color = new cWdf();
	return s_color;
}

cWdf* cWdf::getMp3()
{
	static cWdf* s_mp3 = new cWdf();
	return s_mp3;
}

cWdf* cWdf::getWav()
{
	static cWdf* s_wav = new cWdf();
	return s_wav;
}


bool cWdf::loadRoot(const std::string &filename)
{
	auto path = filename;
	if (filename.find(cFolder::cFlag) != std::string::npos)
	{
		path = cFolder::getInstance()->getRoot() + filename;
	}
	return load(path);
}



//////////////////////////////////////////////////////////////////////////
sSpDecode::sSpDecode()
{
}

sSpDecode::~sSpDecode()
{
	ccc_delete_array(palIdxs);
	ccc_delete_array(alphas);
}

const bool sSpDecode::isValid() const
{
	return palIdxs != nullptr && alphas != nullptr;
}


void sSpDecode::decode(int _w, int _h, const uchar* ptrHead, ulong offs)
{
	w = _w, h = _h;
	palIdxs = new uchar[w * h];
	alphas = new uchar[w * h];
	memset(alphas, 0, w * h);

	auto li = (ulong*)(ptrHead + offs + 16);
	auto _palIdxs = palIdxs;
	auto _alphas = alphas;
	auto palIdx = _palIdxs;
	auto alpha = _alphas;
	auto ptr = ptrHead;
	bool isgh = true, parity; //∆Ê≈º–‘
	for (int k = 0; k < h; ++k, ++li, _palIdxs += w, _alphas += w)
	{
		ptr = ptrHead + offs + *li;
		palIdx = _palIdxs;
		alpha = _alphas;
		parity = ((k % 2) == 1);
		for (int ix = 0; ix < w;)
		{
			static uchar s_dataCheck;
			s_dataCheck = *ptr;
			if (s_dataCheck == 0)// œÒÀÿ––Ω· ¯  
			{
				break;
			}
			++ptr;
			static uint s_size, s_size2;
			static uchar s_dataWait, s_alphaWait;
			switch (s_dataCheck & 0xC0)
			{
			case 0x00: //Bit7-8=00
				if (isgh && parity)
				{
					isgh = false;
				}
				if (s_dataCheck & 0x20)// »ÙBit6=1
				{
					s_alphaWait = (s_dataCheck & 0x1F);// Bit1-5
					if (s_alphaWait)
					{
						*palIdx = *ptr;
						*alpha = s_alphaWait;
					}
					++ptr;
					++ix;
					++palIdx;
					++alpha;
				}
				else
				{
					s_alphaWait = *ptr;
					if (s_alphaWait)
					{
						s_size = (s_dataCheck & 0x1F);
						s_dataWait = *(ptr + 1);
						s_size2 = std::min(s_size, (uint)(w - ix));
						memset(palIdx, s_dataWait, s_size2);
						memset(alpha, s_alphaWait, s_size2);
						ix += s_size;
						palIdx += s_size;
						alpha += s_size;
					}
					ptr += 2;

				}
				break;
			case 0x40: //Bit7-8=01
				if (isgh && parity)
				{
					isgh = false;
				}
				s_size = (s_dataCheck & 0x3f);
				s_size2 = std::min(s_size, (uint)(w - ix));
				memcpy(palIdx, ptr, s_size2);
				memset(alpha, 0x20, s_size2);
				ptr += s_size;
				ix += s_size;
				palIdx += s_size;
				alpha += s_size;
				break;
			case 0x80: //Bit7-8=10
				if (isgh && parity)
				{
					isgh = false;
				}
				s_size = (s_dataCheck & 0x3F);
				s_dataWait = *ptr;
				++ptr;
				s_size2 = std::min(s_size, (uint)(w - ix));
				memset(palIdx, s_dataWait, s_size2);
				memset(alpha, 0x20, s_size2);
				ix += s_size;
				palIdx += s_size;
				alpha += s_size;
				break;
			default:
				s_size = (s_dataCheck & 0x3F);
				if (0 == s_size)
				{
					ptr += 2;
				}
				else
				{
					ix += s_size;
					palIdx += s_size;
					alpha += s_size;
				}
				break;
			}
		}
	}
	if (isgh)
	{
		palIdx = palIdxs;
		alpha = alphas;
		for (int k = 0; k < h - 1; k += 2, palIdx += w * 2, alpha += w * 2)
		{
			memcpy(palIdx + w, palIdx, w);
			memcpy(alpha + w, alpha, w);
		}
	}
}


const cAlphaBmp*  sSpDecode::getBitmap(const s565* palettes, eBlend e, uchar opacity)
{
	cAlphaBmp* bitmap = new cAlphaBmp(w, h);

	auto palIdx = palIdxs;
	auto alpha = alphas;
	auto palette = palettes;
	s565* pD;
	auto pA = alpha;
	auto pIdx = palIdx;
	if (e == eBlend::light)
	{
		for (int k = 0; k < h; ++k, palIdx += w, alpha += w)
		{
			pA = bitmap->ChannelLine(k);
			memcpy(pA, alpha, w);
			pD = (s565*)(*bitmap)[k];
			pIdx = palIdx;
			for (int i = 0; i < w; ++i, ++pD, ++pIdx, ++pA)
			{
				*pD = palette[*pIdx];
				*pA = *pA * opacity / 0xFF;
				pD->toAlpha(*pA);
				pD->toLight();
			}
		}
	}
	else if (e == eBlend::blink)
	{
		for (int k = 0; k < h; ++k, palIdx += w, alpha += w)
		{
			pA = bitmap->ChannelLine(k);
			memcpy(pA, alpha, w);
			pD = (s565*)(*bitmap)[k];
			pIdx = palIdx;
			for (int i = 0; i < w; ++i, ++pD, ++pIdx, ++pA)
			{
				*pD = palette[*pIdx];
				*pA = *pA * opacity / 0xFF;
				pD->toAlpha(*pA);
				pD->toBlick();
			}
		}
	}
	else if (e == eBlend::normal)
	{
		for (int k = 0; k < h; ++k, palIdx += w, alpha += w)
		{
			pA = bitmap->ChannelLine(k);
			memcpy(pA, alpha, w);
			pD = (s565*)(*bitmap)[k];
			pIdx = palIdx;
			for (int i = 0; i < w; ++i, ++pD, ++pIdx, ++pA)
			{
				*pD = palette[*pIdx];
				*pA = *pA * opacity / 0xFF;
				pD->toAlpha(*pA);
			}
		}
	}
	return bitmap;
}

//////////////////////////////////////////////////////////////////////////
sSpBitmaps::sSpBitmaps()
{
	sOps opacities;
	bmps.insert(std::make_pair(eBlend::normal, opacities));
	bmps.insert(std::make_pair(eBlend::blink, opacities));
	bmps.insert(std::make_pair(eBlend::light, opacities));
}

sSpBitmaps::~sSpBitmaps()
{
	for (auto& opacities : bmps)
	{
		for (auto& bmp : opacities.second)
		{
			ccc_delete(bmp.second);
		}
	}
}

void sSpBitmaps::insert(eBlend e, uchar opacity, const cAlphaBmp* bitmap)
{
	auto& opacities = bmps.at(e);
	opacities.insert(std::make_pair(opacity, bitmap));
}

const cAlphaBmp* sSpBitmaps::getBitmap(eBlend e, uchar opacity)
{
	auto& opacities = bmps.at(e);
	auto& it = opacities.find(opacity);
	if (it != opacities.end())
	{
		return it->second;
	}
	return nullptr;
}



//////////////////////////////////////////////////////////////////////////
sSpDecoder::sSpDecoder()
{

}

sSpDecoder::~sSpDecoder()
{
	ccc_delete_array(decodes);
	for (auto& pal : palettes)
	{
		delete[] pal.second;
	}
	for (auto& b : bitmaps)
	{
		delete b.second;
	}
}


const bool sSpDecoder::isValid() const
{
	return decodes != nullptr && info.isValid();
}


void sSpDecoder::load(const char* ptr)
{
	ushort head = info.load(ptr, false);
	ptr += head;
	palette = (s565*)ptr;
	offsets = (ulong*)(ptr + 512);
	decodes = new sSpDecode[info.framesCount];
}


void sSpDecoder::decode(int iframe)
{
	const auto& frame = info.frames + iframe;
	if (!frame->isValid())
	{
		return;
	}
	auto decs = decodes + iframe;
	if (decs->isValid())
	{
		return;
	}
	decs->decode(frame->w, frame->h, (uchar*)palette, *(offsets + iframe));
}


int sSpDecoder::getMatrix(const sMatrixs* matrixs)
{
	if (matrixs == nullptr || matrixs->empty())
	{
		return 0;
	}
	auto pal = new s565[256];
	memcpy(pal, palette, 512);
	cSp::toPalette(pal, matrixs);
	palettes.insert(std::make_pair(++matrixid, pal));
	return matrixid;
}

bool sSpDecoder::removeMatrix(int mid)
{
	if (!isValid())
	{
		return false;
	}
	for (int k = info.framesCount - 1; k >= 0; --k)
	{
		const auto& it = bitmaps.find((mid << cMatrixFlag) + k);
		if (it == bitmaps.end())
		{
			continue;
		}
		delete it->second;
		bitmaps.erase(it);
	}
	if (mid == 0)
	{
		return true;
	}
	const auto& it = palettes.find(mid);
	if (it == palettes.end())
	{
		return false;
	}
	delete[] it->second;
	palettes.erase(it);
	return true;
}

const cAlphaBmp* sSpDecoder::getBitmap(int mid, int iframe, eBlend e, uchar opacity)
{
	int index = (mid << cMatrixFlag) + iframe;
	const auto& it = bitmaps.find(index);
	sSpBitmaps* pBitmaps;
	if (it != bitmaps.end())
	{
		pBitmaps = it->second;
	}
	else
	{
		pBitmaps = new sSpBitmaps();
		bitmaps.insert(std::make_pair(index, pBitmaps));
	}
	auto bitmap = pBitmaps->getBitmap(e, opacity);
	if (bitmap != nullptr)
	{
		return bitmap;
	}

	decode(iframe);
	auto decs = decodes + iframe;
	if (!decs->isValid())
	{
		return nullptr;
	}
	bitmap = decs->getBitmap(mid == 0 ? palette : palettes.at(mid), e, opacity);
	if (bitmap != nullptr)
	{
		pBitmaps->insert(e, opacity, bitmap);
	}
	return bitmap;
}

//////////////////////////////////////////////////////////////////////////
cSp::~cSp()
{
	for (auto& r : _refs)
	{
		delete r.second.ptr;
	}
}


void cSp::toPalette(s565* palette, const sMatrixs* matrixs)
{
	if (matrixs == nullptr || matrixs->empty())
	{
		return;
	}
	int r, g, b;
	auto p565 = palette;
	for (int k = 0, size = matrixs->size(); k < size; ++k)
	{
		const auto& m = matrixs->at(k);
		const auto& matrix = m.matrix;
		// p565 = palette + m.start;
		for (int i = m.start; i < m.end; ++i, ++p565)
		{
			r = p565->r * matrix.r1 + p565->g * matrix.r2 + p565->b * matrix.r3;
			g = p565->r * matrix.g1 + p565->g * matrix.g2 + p565->b * matrix.g3;
			b = p565->r * matrix.b1 + p565->g * matrix.b2 + p565->b * matrix.b3;
			r = r >> 8;
			g = g >> 8;
			b = b >> 8;
			if (r > 31) r = 31;
			if (g > 63) g = 63;
			if (b > 31)	b = 31;
			p565->r = r;
			p565->g = g;
			p565->b = b;
		}
	}
}


const sSpDecoder* cSp::getDecoder(ulong uid)
{
	auto& it = _refs.find(uid);
	if (it != _refs.end())
	{
		++it->second.ref;
		return &it->second.decoder;
	}
	auto idx = search2(uid);
	if (idx == nullptr)
	{
		return nullptr;
	}
	auto ptr = getData(idx, true);
	if (ptr == nullptr)
	{
		return nullptr;
	}
	sRef r;
	r.ptr = ptr;
	r.ref = 1;
	_refs.insert(std::make_pair(uid, r));
	auto& decoder = _refs.at(uid).decoder;
	decoder.load(ptr);
	return &decoder;
}


bool cSp::freeDecoder(ulong uid)
{
	const auto& it = _refs.find(uid);
	if (it == _refs.end())
	{
		return false;
	}

	auto& ref = it->second;
	if ((--ref.ref) == 0)
	{
		delete[] ref.ptr;
		_refs.erase(it);
		return true;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
cSps::~cSps()
{
	for (auto& sp : _sps)
	{
		delete sp.second;
	}
}

cSps* cSps::getInstance()
{
	static cSps* s_sps = new cSps();
	return s_sps;
}

cSp* cSps::loadRoot(const std::string &filenameWithoutRoot)
{
	const auto& it = _sps.find(filenameWithoutRoot);
	if (it != _sps.end())
	{
		return it->second;
	}

	cSp* sp = new cSp();
	if (!sp->loadRoot(filenameWithoutRoot))
	{
		delete sp;
		return nullptr;
	}
	_sps.insert(std::make_pair(filenameWithoutRoot, sp));
	return sp;
}

cSp* cSps::getSp(const std::string &filenameWithoutRoot)
{
	return _sps.at(filenameWithoutRoot);
}
