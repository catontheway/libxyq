#pragma once
#include "sDye.h"

class cDyeRender
{
public:
	static cDyeRender* getInstance();

	bool load(eMod epet, int jdx, const std::vector<sDye>& dyes);
	bool load(eMod erole, int idx, const sDye& dye);
	bool load(eMod erole, eIcon eweapon, int weaponid, const sDye& dye);
	bool load(eZuoqi ezq, const sDye& dye);
	bool load(int zsid, const sDye& dye);
	void load(bool part0 = false);

	bool swtichPart();
	bool resetPart();
	bool addMatrix(int sectionIdx);
	bool randMatrix(int sectionIdx);

	void apply();
private:
	struct sSpDye
	{
		ulong uid, cid;
		sDye dye;
	};
	std::vector<sSpDye> _spDyes;
	int _partIdx = 0;
	cDye::sSections _sections;
	sSp _spMatrixs;
public:
	struct sShow { int idx, total; };
	std::function<void(const sSp&, std::vector<sShow>&)> onLoad = nullptr;
	std::function<void(const std::vector<sDye>& dyes)> onApply = nullptr;
};