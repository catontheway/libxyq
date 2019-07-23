#include "IntData.h"

void sInt3::Save(ofstream& File)
{
	File << " ";
	File << m_Data << " ";
	File << add << " ";
	File << precent << " ";
	File << origin << "\n";
}

void sInt3::Load(ifstream& File)
{
	File >> m_Data;
	File >> add;
	File >> precent;
	File >> origin;
}


