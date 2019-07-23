#include "cReader.h"

bool cReader::loadRoot(const std::string &filename)
{
	auto sp = cSps::getInstance()->loadRoot(filename);
	if (sp == nullptr)
	{
		return false;
	}
	sStrSp strsp;
	strsp.filenameWithoutRoot = filename;
	strsp.sp = sp;
	_sps.push_back(strsp);
	return true;
}


bool cReader::loadRoot(const std::vector<std::string> &filenames)
{
	bool isOk = true;
	for (const auto& filename : filenames)
	{
		if (!loadRoot(filename))
		{
			isOk = false;
		}
	}
	return isOk;
}


bool cReader::loadRoot(const std::string &root, const std::string &path)
{
	auto names = cc::efolder(root + path, true, 0);
	for (auto& name : names)
	{
		name = path + name;
	}
	return loadRoot(names);
}



void cReader::setType(eMapType esmap)
{
	_esmap = esmap;
	_isSmap = true;
}

void cReader::setType(eIterType eiter, euiType eui)
{
	_eiter = eiter;
	_eui = eui;
	_isSmap = false;
}

const sSpDecoder* cReader::getDecoder(ulong uid)
{
	const auto& it = _uidxs.find(uid);
	if (it != _uidxs.end())
	{
		return it->second.sp->getDecoder(uid);
	}

	for (auto strsp : _sps)
	{
		auto decoder = strsp.sp->getDecoder(uid);
		if (decoder != nullptr)
		{
			_uidxs.insert(std::make_pair(uid, strsp));
			return decoder;
		}
	}
	return nullptr;
}

bool cReader::freeDecoder(ulong uid)
{
	const auto& it = _uidxs.find(uid);
	if (it == _uidxs.end())
	{
		return false;

	}
	return it->second.sp->freeDecoder(uid);
}