#pragma once
#include "_objinc.h"

static const int c_NumofCharacter = 18;
struct sZuoQiZhuangShi
{
	ulong m_ColorID;
	ulong  NodeStand;
	ulong  NodeWalk;
	array<ulong, c_NumofCharacter> Stand;
	array<ulong, c_NumofCharacter>  Walk;
};
struct sZuoQi
{
	ulong m_ColorID;
	int ID;
	string Name;
	ulong  nodeStand;
	ulong  nodeWalk;
	array<ulong, c_NumofCharacter>  CharStand;
	array<ulong, c_NumofCharacter>  CharWalk;
};


struct sZuoQi2
{
	int m_ownerID;
	sZuoQi* m_pZuoQi = 0;
	sItem2  m_ZhuangShi;
	ulong GetID(int Pos){ vector<ulong> out; GetID(Pos, out); return out[0]; }
	void GetID(int Pos, vector<ulong>& out, bool haveChar = true);
};


