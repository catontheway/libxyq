#include "cGame.h"
#include <fstream>


const std::string cGame::cFilename = "配置.txt";

cGame* cGame::getInstance()
{
	static cGame* s_game = new cGame();
	return s_game;
}

static const char* s_space = " ", *s_enter = "\n";
bool cGame::save(const std::string& filename)
{
	std::ofstream ofile(filename);
	if (!ofile.is_open())
	{
		return false;
	}
	ofile << _w << s_space << "//屏幕宽度\n" << _h << s_space << "//屏幕高度\n";
	ofile << (int)_eiter << s_space << "//资源类型(0唯美,1经典,2迭代)\n";
	ofile << (int)_emap << s_space << "//地图类型(0唯美,1经典,2迭代)\n";
	ofile << (int)_eui << s_space << "//ui类型(0经典,1国韵,2水晶,3雅致)\n";
	ofile << _isChatShown << s_space << "//聊天窗口(0不显示,1显示)\n";
//	ofile << _isMp3 << s_space << "//音乐\n" << _volume << s_space << "//音量\n" << _isWav << s_space << "//音效\n";

	ofile.close();
	return true;
}

bool cGame::load(const std::string& filename)
{
	std::ifstream ifile(filename);
	if (!ifile.is_open())
	{
		return false;
	}
	std::string  line;
	ifile >> _w;
	getline(ifile, line);
	ifile >> _h;
	getline(ifile, line);
	int e;
	ifile >> e;
	getline(ifile, line);
	_eiter = (eIterType)e;
	ifile >> e;
	getline(ifile, line);
	_emap = (eMapType)e;
	ifile >> e;
	getline(ifile, line);
	_eui = (euiType)e;
	ifile >> _isChatShown;
// 	getline(ifile, line);
// 	ifile >> _isMp3;
// 	getline(ifile, line);
// 	ifile >> _volume;
// 	getline(ifile, line);
// 	ifile >> _isWav;

	ifile.close();
	return true;
}
