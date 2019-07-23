#pragma once
#include "sAttribute.h"
#include "sPropertyInfo.h"

enum eFormation
{
	normal,//ÆÕÍ¨Õó
	land, //µØÔØÕó
	wind,//·çÑïÕó
	tiger,//»¢ÒíÕó
	dragon,//Áú·ÉÕó
	bird,//ÄñÏèÕó
	snake,//Éßó´Õó
	sky,//Ìì¸²Õó
	cloud,//ÔÆ´¹Õó
	thunder,//À×¾øÕó
	eagle//Ó¥Ğ¥Õó
};
// ÕóĞÍ
struct sFormation
{
	static const int c5 = 5;
	std::array<int, c5> xs;
	std::array<int, c5> ys;
	eFormation e;

	sFormation();
	sFormation(eFormation e);

	// Ğ§¹û
	std::string apply(int idx, sPropertyInfo* info, int3* speed);
	// Î»ÖÃ(Î»ÖÃ0-4,ÊÇ·ñ±¦±¦,ÊÇ·ñµĞÕ¾Î», ·µ»Øx, ·µ»Øy)
	bool apply(int idx, bool pet, bool enemy, int& x, int& y);

};