#pragma once
#include "_inc.h"
#include "cFolder.h"

struct sMapInfo { int mw, mh, bw, bh; };

struct sMapDecode : public sSpFrame
{
	uchar* decodes = nullptr;

	~sMapDecode();
	const bool isValid() const;
	bool decode(uchar* ptr);
};


struct sMapAlpha : public sSpFrame
{
	int maskIdx, bx, by;
	cAlphaBmp* bmp = nullptr;

	~sMapAlpha();
	const bool isValid() const;
	cAlphaBmp* getAlpha(cBmp* bitmap, const uchar* decodes, int mw);
};



struct sMap
{
	const char* ptr;
	sMapInfo info;
	int blocksCount, masksCount;
	uint* blockOffs = nullptr;
	uint* maskOffs = nullptr;
	sMapDecode* masks = nullptr;
	uchar* obstacles = nullptr;
	cAstar* astar = nullptr;

	struct sImage
	{
		uchar* image = nullptr;
		int imageSize = 0;

		~sImage();
		const bool isValid() const;
		void reset();
	};
	struct sBMP
	{
		void* jpegBmp = nullptr;
		cBmp* bmp = nullptr;

		~sBMP();
		const bool isValid() const;
	};
	std::map<int, std::vector<sMapAlpha>> alphas;
	// for map2d
	std::map<int, sImage> images;
	std::map<int, sBMP> bmps;

	~sMap();
	bool load(const char* ptr);
	bool loadMask();
	bool loadObstacles();
	bool isObstacle(int x20, int y20);
	sImage& getImage(int blockIdx, bool alloc);
	const sImage& getImage(int blockIdx);
	const sBMP& getBMP(int blockIdx, bool alloc);
	cBmp* getBitmap(int blockIdx);
	bool isLoaded();
	void clear();

	bool search(const cocos2d::Vec2& vStart, const cocos2d::Vec2& vEnd, std::vector<cocos2d::Vec2>& paths);
};


struct sMapCache
{
	eMapType e;
	int mapid = 0;
	std::string filenameWithoutRoot;
	sMap* pMap = nullptr;
	const bool isValid() const;
};

class cMapReader
{
public:
	cMapReader();
	~cMapReader();
	static cMapReader* getInstance();

	static bool isMap(const char* ptr);

	static const char* getData(const std::string& filenameWithoutRoot);

	const std::string& getFileNameWithoutRoot(eMapType e, int mapid);

	sMapCache getCache(eMapType e, int mapid);

	bool freeCache(const sMapCache& cache);

private:
	struct sRef
	{
		sMap* pMap = nullptr;
		int ref;
	};
	std::map<std::string, sRef> _caches;
	std::map<eMapType, std::map<int, std::string>> _searchs;
public:
	static const int c320 = 320, c240 = 240;
	static const int c16 = 16, c12 = 12, c20 = 20;
};

