#pragma once
#include <string>
#include <vector>
#include <map>

enum class eIterType { wm, jd, iter };
enum class eMapType { wm, jd, iter };
enum class euiType { jd, gy, sj, yz };
class cFolder
{
public:
	typedef std::vector<std::string> sStrs;
	cFolder();
	// 资料片wdf文件夹标记
	static const std::string cFlag;
	static cFolder* getInstance();
	static std::string getPath(int cut);
	static void searchRoots(sStrs& roots);

	void init();

	void write(std::ofstream& ofile, const std::string& path);
	bool write();

	void setFront(const sStrs& filenames);
	void setFrontSmap(const sStrs& filenames);

	void read(std::ifstream& ifile);
	bool read(bool toast);

	void apply();
public:
	typedef std::map <euiType, sStrs> sUIs;
	typedef std::map <eIterType, sUIs> sWdfs;
	const std::map<eMapType, sStrs>& getMaps()const { return _maps; }
	const std::map<eMapType, sStrs>& getSmaps()const { return _smaps; }
	const sWdfs& getWdfs() const { return _wdfs; }
	const std::string& getMusic()const { return _music; }
	const std::string& getSound()const { return _sound; }
	const std::string& getColor()const { return _color; }
	const std::string& getRoot()const { return _root; }
	const std::string& getWd() const { return _wdf; }
	const std::string& getUpdate()const { return _update; }
private:
	std::map<eMapType, sStrs> _maps, _smaps;
	sWdfs _wdfs;
	std::string _root, _sceneOri, _sceneWm, _sceneJd, _sceneIter, _update, _wdf;
	std::string _wdfWm, _wdfIter;
	std::string _smapWm, _smapJd, _smapIter;
	std::string _uijd, _uigy, _uisj, _uiyz;
	std::string _music, _sound, _color;
	sStrs _defaults, _fronts, _frontSmaps;
};