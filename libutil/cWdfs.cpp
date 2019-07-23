#include "cWdfs.h"

cWdfs::cWdfs()
{
	const auto& fol = cFolder::getInstance();
	const auto& smaps = fol->getSmaps();
	for (const auto& smap : smaps)
	{
		auto reader = new cReader();
		reader->loadRoot(smap.second);
		reader->setType(smap.first);
		_smaps.insert(std::make_pair(smap.first, reader));
	}

	const auto& iters = fol->getWdfs();
	sUIs uiWdfs;
	for (const auto& it2 : iters)
	{
		uiWdfs.clear();
		const auto& eiter = it2.first;
		const auto& uis = it2.second;
		for (const auto& it3 : uis)
		{
			auto reader = new cReader();
			reader->loadRoot(fol->getRoot(), fol->getUpdate());
			reader->loadRoot(it3.second);
			reader->setType(eiter, it3.first);
			uiWdfs.insert(std::make_pair(it3.first, reader));
		}
		_readers.insert(std::make_pair(eiter, uiWdfs));
	}

	_currReaders.insert(std::make_pair(eIterType::wm, nullptr));
	_currReaders.insert(std::make_pair(eIterType::jd, nullptr));
	_currReaders.insert(std::make_pair(eIterType::iter, nullptr));
}


cWdfs* cWdfs::getInstance()
{
	static cWdfs* s_group = new cWdfs();
	return s_group;
}


void cWdfs::setType(eMapType emap)
{
	_esmap = emap;
	_currSmaps = _smaps.at(_esmap);
}

void cWdfs::setType(euiType eui)
{
	_eui = eui;
	_currReaders.at(eIterType::wm) = _readers.at(eIterType::wm).at(_eui);
	_currReaders.at(eIterType::jd) = _readers.at(eIterType::jd).at(_eui);
	_currReaders.at(eIterType::iter) = _readers.at(eIterType::iter).at(_eui);
}

eIterType cWdfs::getCurrIter() const
{
	return _readerTypes.back();
}

cReader* cWdfs::getCurrReader() const
{
	return _currReaders.at(_readerTypes.back());
}


cReader* cWdfs::pushReader(eIterType e)
{
	_readerTypes.push_back(e);
	return _currReaders.at(e);
}

cReader* cWdfs::replaceReader(eIterType e)
{
	auto reader = _currReaders.at(e);
	_readerTypes.back() = e;
	return reader;
}

cReader* cWdfs::popReader()
{
	_readerTypes.pop_back();
	return getCurrReader();
}
