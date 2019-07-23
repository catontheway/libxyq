#pragma once
#include "cReader.h"

class cWdfs
{
public:
	cWdfs();
	static cWdfs* getInstance();

	void setType(eMapType emap);
	void setType(euiType eui);

	const std::map<eMapType, cReader*>& getSmaps()const { return _smaps; }
	cReader* getSmap() const { return _currSmaps; }
	const eMapType& getSmapType() const { return _esmap; }
	const euiType& getuiType() const { return _eui; }

	typedef std::map<euiType, cReader*> sUIs;
	typedef std::map<eIterType, sUIs> sIters;
	const sIters& getReaders()const { return _readers; }
	const std::map<eIterType, cReader*>& getCurrReaders() const { return _currReaders; }
	eIterType getCurrIter() const;
	cReader* getCurrReader() const;
	cReader* pushReader(eIterType e);
	cReader* replaceReader(eIterType e);
	cReader* popReader();
private:
	std::map<eMapType, cReader*> _smaps;
	sIters _readers;

	cReader* _currSmaps;
	std::map<eIterType, cReader*> _currReaders;
	std::vector<eIterType> _readerTypes;
	eMapType _esmap;
	euiType _eui;
};