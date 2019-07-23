#pragma once
#include "../libxyq/cMain.h"

struct sTour
{
	std::string name;
	std::vector<int> mapids;
	int x20 = 0, y20 = 0;
	sTour() {}
	sTour(int umap) : mapids({ umap }) {}
	sTour(int umap, int umap2) : mapids({ umap, umap2 }) {}
	sTour(int umap, const std::string& mapname) : name(mapname), mapids({ umap }) {}
	sTour(int umap, int umap2, const std::string& mapname) : name(mapname), mapids({ umap, umap2 }) {}
};

class cMap;
class uiShichen;
class uiSmap;
class cMainTour : public cMain
{
public:
	void setTitle(HWND hwnd, HWND child);

	Scene* runScene();

protected:
	void beforeMainLoop();

	void loadRand();
	void toMap(const sTour& tour);
	void loadTrans(int x, int y, int w, int inv, const std::vector<sTour>& tours);

	cMap* _map = nullptr;
	uiShichen* _shichen = nullptr;
	uiSmap* _smap = nullptr;
	std::vector<sTour> _tours;
};
