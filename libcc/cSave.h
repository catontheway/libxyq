#pragma once
#include <fstream>
#include <sstream>
#include <string>

typedef std::stringstream sStream;
static const char* s_space = " ";
static const char* s_enter = "\n";
class cSave
{
public:
	static cSave* getSave();
	static cSave* getSaveEncode();
	static cSave* getLoad();
	static cSave* getLoadEncode();

	bool save(const std::string& filename, bool encode);
	bool load(const std::string& filename, bool encode);

	operator sStream& ();
protected:
	std::fstream _file;
	sStream _str;
};