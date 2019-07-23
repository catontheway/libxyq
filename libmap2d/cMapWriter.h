#pragma once
#include "../libutil/cMapReader.h"
#include "../libgg/cLabel.h"
#include "../libgg/cSprite.h"



class cMapWriter : public cSprite
{
public:
	static cMapWriter* create(const std::string& path, int mapid, cLabel* labelMapid, cLabel* labelDesc){ CREATE(cMapWriter, path, mapid, labelMapid, labelDesc); }

	bool readJPG(int iblock, bool save);
	bool readMask(int iMask);
	bool writeMask(int iMask);
	bool writeObstable();
protected:
	sMap _m;
	std::string _path;
	int _id = 0,  _flag = 0, _iblock = 0, _imask = 0, _smalltimes = 1;
	cLabel* _labelMapid = nullptr;
	cLabel* _labelDesc = nullptr;
	uint* _data = nullptr;
	uint* _dataMask = nullptr;
	Texture2D* _texture = nullptr;
	Texture2D* _textureMask = nullptr;
	virtual bool init(const std::string& path, int mapid, cLabel* labelMapid, cLabel* labelDesc);
	virtual void update(float delta);
public:
	std::function<void()> onFinish = nullptr;
};