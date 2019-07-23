#include "cFolder.h"

const std::string cFolder::cFlag = "scene.";
cFolder::cFolder() {}
cFolder* cFolder::getInstance()
{
	static cFolder* s_folder = new cFolder();
	return s_folder;
}