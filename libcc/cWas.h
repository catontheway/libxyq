#pragma once
#include "_cpp.h"

class cWas
{
public:
	struct sIndex { ulong uid, offset, size; };

	~cWas();

	bool load(const std::string &filename);

	const sIndex* search2(ulong uid);

	const sIndex* getIndexs() const { return _indexs; }

	int getIndexsCount() const { return _indexsCount; }

	const char* getData(const sIndex* idx, bool isJudgeSp = false);

	const char* getData(ulong uid, int& size);

protected:
	FILE* _file = 0;
	sIndex* _indexs = nullptr;
	int _indexsCount = 0;
};


struct sSpFrame
{
	int x = 0, y = 0, w = 0, h = 0;
	const bool isValid() const;
};
struct sSpInfo
{
	int directionsCount;
	int framesCountPerDirection;
	int framesCount;
	int width, height, kx, ky;
	sSpFrame* frames = nullptr;

	~sSpInfo();
	const bool isValid()const;

	int load(const char* ptr, bool easy18);
};