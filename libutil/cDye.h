#pragma once
#include "cSp.h"

class cDye
{
public:
	struct sSection
	{
		ushort start, end;
		std::vector<sMatrix9> matrix9s;
	};
	typedef std::vector<sSection> sSections;
	typedef std::vector<int> sIdxs;

	static bool toSections(sSections& sections, ulong color);

	static bool toMatrixs(sMatrixs& matrixs, const sSections& sections, const sIdxs& idxs);
	static bool toMatrixs(sMatrixs& matrixs, ulong color, const sIdxs& idxs);
	static bool toMatrixs(sMatrixs& matrixs, int idx1657);
	static void toMatrixs(sMatrixs& matrixs);

	static void resetMatrix(sMatrix9& matrix9, bool rand = false);
};