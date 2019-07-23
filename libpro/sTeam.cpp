#include "sTeam.h"

sTeam* sTeam::getInstance()
{
	static sTeam* s_team = new sTeam();
	return s_team;
}

sTeam::sTeam()
{
	members.resize(c5);
	forv(members, k)
	{
		members.at(k).teamIdx = k;
		doObj(k, k);
	}
}

sTeam::~sTeam()
{

}

bool sTeam::setLeader(int idx)
{
	return swap(idx, 0);
}

sRole& sTeam::getLeader()
{
	return members.at(0);
}

sRole& sTeam::getMember(int idx)
{
	return members.at(idx);
}

bool sTeam::swap(int idx)
{
	return swap(idx, idx - 1);
}

bool sTeam::swap(int idx, int idx2)
{
	if (idx == idx2 || idx < 0 || idx >= c5 || idx2 < 0 || idx2 >= c5)
	{
		return false;
	}
	auto& m1 = members.at(idx);
	auto& m2 = members.at(idx2);
	std::swap(m1, m2);
	std::swap(m1.teamIdx, m2.teamIdx);
	doObj(idx, idx2);
	doObj(idx2, idx);
	return true;
}


bool sTeam::add()
{
	if (count >= c5)
	{
		return false;
	}
	++count;
	doObj(count - 1, count - 1);
	return true;
}

bool sTeam::remove(int idx)
{
	if (count <= 1 || idx < 0 || idx >= count)
	{
		return false;
	}
	std::vector<int> idxs;
	forv(members, k)
	{
		idxs.push_back(members.at(k).teamIdx);
	}
	auto r = members.at(idx);
	members.erase(members.begin() + idx);
	members.push_back(r);
	--count;
	forv(members, k)
	{
		members.at(k).teamIdx = k;
		doObj(idxs.at(k), k);
	}
	return true;
}




bool sTeam::isFighting()
{
	return fight;
}


void sTeam::doObj(int tag, int tagNew)
{
	if (onObj != nullptr)
	{
		onObj(tag, tagNew, tagNew < count);
	}
}

bool sTeam::beginFight()
{
	fight = true;
	return true;
}

bool sTeam::endFight()
{
	fight = false;
	return true;
}

