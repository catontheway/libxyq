#include "cDye.h"

static int readIColor9(char*& ptr, int& i, int size)
{
	if (i >= size)
	{
		return -1;
	}
	int v = atoi(ptr);
	do
	{
		++ptr;
		if (++i >= size)
		{
			return v;
		}
	} while ((*ptr) >= '0' && (*ptr) <= '9');

	do
	{
		++ptr;
		if (++i >= size)
		{
			return v;
		}
	} while ((*ptr) < '0' || (*ptr) > '9');

	return v;
}


static bool readColorPal(cDye::sSections& c, char* ptr, int& idx, int size)
{
	int n = readIColor9(ptr, idx, size);
	c.resize(n % 10);
	std::vector<int> parts;
	parts.resize(c.size() + 1);
	forv(parts, i)
	{
		parts[i] = readIColor9(ptr, idx, size);
	}

	forv(c, k)
	{
		auto& part = c.at(k);
		auto& matrixs = part.matrix9s;
		matrixs.resize(readIColor9(ptr, idx, size));
		forv(matrixs, i)
		{
			if (n > 1000)
			{
				readIColor9(ptr, idx, size);
			}
			auto& m = matrixs[i];
			m.r1 = readIColor9(ptr, idx, size);
			m.r2 = readIColor9(ptr, idx, size);
			m.r3 = readIColor9(ptr, idx, size);
			m.g1 = readIColor9(ptr, idx, size);
			m.g2 = readIColor9(ptr, idx, size);
			m.g3 = readIColor9(ptr, idx, size);
			m.b1 = readIColor9(ptr, idx, size);
			m.b2 = readIColor9(ptr, idx, size);
			m.b3 = readIColor9(ptr, idx, size);
			part.start = parts[k];
			part.end = parts[k + 1];
			if (n > 1000)
			{
				readIColor9(ptr, idx, size);
				readIColor9(ptr, idx, size);
				readIColor9(ptr, idx, size);
				readIColor9(ptr, idx, size);
			}
			if (idx >= size)
			{
				return false;
			}
		}

	}
	return true;
}


static bool readColorPal(cDye::sSections& c, std::istringstream& sstr)
{
	int head, n;
	sstr >> head;
	c.resize(head % 10);
	std::vector<int> parts;
	parts.resize(c.size() + 1);
	forv(parts, i)
	{
		sstr >> parts[i];
	}
	std::string temp;
	getline(sstr, temp);
	forv(c, k)
	{
		auto& part = c.at(k);
		auto& matrixs = part.matrix9s;
		sstr >> n;
		matrixs.resize(n);
		getline(sstr, temp);
		forv(matrixs, i)
		{
			if (head > 1000)
			{
				getline(sstr, temp);
			}
			auto& m = matrixs[i];
			sstr >> m.r1 >> m.r2 >> m.r3 >> m.g1 >> m.g2 >> m.g3 >> m.b1 >> m.b2 >> m.b3;
			part.start = parts[k];
			part.end = parts[k + 1];
			if (head > 1000)
			{
				getline(sstr, temp);
			}
			getline(sstr, temp);
		}

	}
	return true;
}


bool cDye::toSections(sSections& sections, ulong color)
{
	sections.clear();
	if (color == cSp::c0)
	{
		color = 0x00001657;
	}
	int size;
	auto ptr = cWdf::getColor()->getData(color, size);
	if (ptr == nullptr)
	{
		return false;
	}
#if 1
	std::istringstream sstr(std::string(ptr, size));
	delete[] ptr;
	readColorPal(sections, sstr);
#else
	char* p = (char*)ptr;
	int idx = 0;
	readColorPal(sections, p, idx, size);
	delete[] ptr;
#endif
	return true;
}


bool cDye::toMatrixs(sMatrixs& matrixs, const sSections& sections, const sIdxs& idxs)
{
	if (sections.empty())
	{
		matrixs.clear();
		return false;
	}
	int i, size = sections.size();
	matrixs.resize(size);
	forv(sections, k)
	{
		auto& m = matrixs.at(k);
		auto& s = sections.at(k);
		m.start = s.start;
		m.end = s.end;
		auto& m9 = m.matrix;
		const auto& m9s = sections.at(k).matrix9s;
		if (k < size)
		{
			i = idxs.at(k);
			if (i < m9s.size())
			{
				m9 = m9s.at(i);
			}
			else
			{
				resetMatrix(m9);
			}
		}
		else
		{
			resetMatrix(m9);
		}
	}
	return true;
}



bool cDye::toMatrixs(sMatrixs& matrixs, ulong color, const sIdxs& idxs)
{
	sSections sections;
	if (!toSections(sections, color))
	{
		matrixs.clear();
		return false;
	}
	return toMatrixs(matrixs, sections, idxs);
}


void cDye::toMatrixs(sMatrixs& matrixs)
{
	for (auto& m : matrixs)
	{
		resetMatrix(m.matrix, true);
	}
}


void cDye::resetMatrix(sMatrix9& matrix9, bool rand /* = false */)
{
	matrix9.r1 = 0x1FF;
	matrix9.r2 = 0;
	matrix9.r3 = 0;
	matrix9.g1 = 0;
	matrix9.g2 = 0x1FF;
	matrix9.g3 = 0;
	matrix9.b1 = 0;
	matrix9.b2 = 0;
	matrix9.b3 = 0x1FF;
	if (rand)
	{
		matrix9.r1 = cc::random(0, 0x1FF);
		matrix9.g2 = cc::random(0, 0x1FF);
		matrix9.b3 = cc::random(0, 0x1FF);
	}
}
