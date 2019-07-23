#include "sBags.h"
#include "cEquip.h"

sBags* sBags::getInstance()
{
	static sBags* s_bags = new sBags();
	return s_bags;
}

sBags::sBags()
{
	items.resize(sItem::c60);
}

int sBags::find(const sItem& item)
{
	forv(items, k)
	{
		const auto& it = items.at(k);
		if (!it.isValid())
		{
			continue;
		}
		if (it == item)
		{
			return k;
		}
	}
	return c_1;
}

bool sBags::add(int money_, bool onlyCheck /* = false */)
{
	return money.add(money_, onlyCheck);
}

int sBags::add(sItems& items, const sItem& item, bool onlyCheck /*= false*/)
{
	std::vector<int> emptys;
	int iSame = c_1;
	// ¿Éµþ¼Ó
	bool overlay = item.isOverly();
	forv(items, k)
	{
		const auto& it = items.at(k);
		if (!it.isValid())
		{
			emptys.push_back(k);
			continue;
		}
		if (overlay && iSame == c_1 && item == it)
		{
			iSame = k;
			break;
		}
	}
	if (iSame != c_1)
	{
		if (!onlyCheck)
		{
			items[iSame].add(item.getCount());
		}
		return iSame;
	}
	iSame = emptys.size();
	if (iSame > 0)
	{
		if (iSame < item.getCount())
		{
			return c_1;
		}
		iSame = item.getCount();
		for (int k = 0; k < iSame; ++k)
		{
			auto& it = items.at(emptys.at(k));
			it = item;
			it._num = 1;
		}
		return emptys.at(iSame - 1);
	}
	return c_1;
}



int sBags::add(const sItem& item, bool onlyCheck /* = false */)
{
	return add(items, item, onlyCheck);
}

void sBags::save() const
{
	sStream& sav = *cSave::getSave();
	sav << money.union64 << s_space;
	forr(items, k)
	{
		items.at(k).save();
	}
}

void sBags::load()
{
	sStream& sav = *cSave::getLoad();
	sav >> money.union64;
	forr(items, k)
	{
		items.at(k).load();
	}
}
