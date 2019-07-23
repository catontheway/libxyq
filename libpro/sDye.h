#pragma once
#include "_inc.h"

// 染料 染色
class sDye
{
public:
	sDye();
	bool resetZero();
	// 不用
	void reset();
	void reset(const cDye::sIdxs& idxs);
	bool isZero()const;
	// 不用
	bool resize(int size);

	operator const cDye::sIdxs&() const;
	operator cDye::sIdxs&();

	void save()const;
	void load();
private:
	cDye::sIdxs _idxs;
};

