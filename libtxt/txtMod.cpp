#include "txtMod.h"

bool txtMod::isPet(eMod mod)
{
	return mod >= eMod::ePet0 && mod <= eMod::ePetEnd;
}

bool txtMod::isNpc(eMod mod)
{
	return mod >= eMod::eNpc0 && mod <= eMod::eNpcEnd;
}

bool txtMod::isRole(eMod mod)
{
	return mod >= eMod::eJueSe0 && mod <= eMod::eJueSeEnd;;
}


bool txtMod::isBoy(eMod eRole)
{
	switch (eRole)
	{
	case eMod::eJueSe½£ÏÀ¿Í:
	case eMod::eJueSeåÐÒ£Éú:
	case eMod::eJueSe»¢Í·¹Ö:
	case eMod::eJueSe¾ÞÄ§Íõ:
	case eMod::eJueSeÁúÌ«×Ó:
	case eMod::eJueSeÉñÌì±ø:
	case eMod::eJueSeÓðÁéÉñ:
	case eMod::eJueSeÉ±ÆÆÀÇ:
	case eMod::eJueSeÙÈÎÞÊ¦:
		return true;
	}
	return false;
}
