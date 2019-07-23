#include "sDye.h"


sDye::sDye()
{
	_idxs.resize(5);
	resetZero();
}

bool sDye::resetZero()
{
	std::fill(_idxs.begin(), _idxs.end(), 0);
	return true;
}

void sDye::reset()
{
	_idxs.clear();
}

void sDye::reset(const cDye::sIdxs& idxs)
{
	_idxs = idxs;
}


bool sDye::isZero()const
{
	forr(_idxs, k)
	{
		if (_idxs[k] != 0)
		{
			return false;
		}
	}
	return true;
}

bool sDye::resize(int size)
{
	while (_idxs.size() > size)
	{
		_idxs.pop_back();
	}
	while (_idxs.size() < size)
	{
		_idxs.push_back(0);
	}
	return true;
}


sDye::operator const cDye::sIdxs&() const
{
	return _idxs;
}

sDye::operator cDye::sIdxs&()
{
	return _idxs;
}


void sDye::save()const
{
	sStream& sav = *cSave::getSave();
	sav << _idxs.size() << s_space;
	forr(_idxs, k)
	{
		sav << _idxs[k] << s_space;
	}
}

void sDye::load()
{
	sStream& sav = *cSave::getLoad();
	int size;
	sav >> size;
	_idxs.resize(size);
	forr(_idxs, k)
	{
		sav >> _idxs[k];
	}
}


