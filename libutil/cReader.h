#pragma once
#include "cSp.h"
#include "cFolder.h"

class cReader
{
public:
	bool loadRoot(const std::string &filename);
	bool loadRoot(const std::vector<std::string> &filenames);
	bool loadRoot(const std::string &root, const std::string &path);

	void setType(eMapType esmap);
	void setType(eIterType eiter, euiType eui);

	const eMapType& getSmapType() const { return _esmap; }
	const eIterType& getIterType() const { return _eiter; }
	const euiType& getuiType() const { return _eui; }

	const sSpDecoder* getDecoder(ulong uid);

	bool freeDecoder(ulong uid);

private:
	eMapType _esmap;
	eIterType _eiter;
	euiType _eui;
	bool _isSmap;

	struct sStrSp
	{
		std::string filenameWithoutRoot;
		cSp* sp = nullptr;
	};
	std::vector<sStrSp> _sps;
	std::map<ulong, sStrSp> _uidxs;
};
