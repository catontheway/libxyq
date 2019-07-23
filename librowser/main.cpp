#include <tchar.h>
#include "resource.h"
#include "../libxyq/cMain.h"
#include "../libxyq/cMain.cpp"
#include "uiPad.h"

void ccu::hideSpriteDesc(){}
void cDesc::showDesc(bool show){}
uiManager* ccu::getManager() { return nullptr; }
cGame* cGame::getInstance()
{
	static cGame* s_game = new cGame();
	return s_game;
}
cWdfs::cWdfs(){}
cWdfs* cWdfs::getInstance()
{
	static cWdfs* s_group = new cWdfs();
	return s_group;
}
cReader* cWdfs::getCurrReader() const { return nullptr; }

class cMainBrowser : public cMain
{
public:
	void setTitle(HWND hwnd, HWND child)
	{
		if (hwnd != nullptr)
		{
			::SetWindowText(hwnd, "浪西游筛选器");
		}
		else if (child != nullptr)
		{
			::SetWindowText(child, "v20190720");
		}
	}

	Scene* runScene()
	{
		auto scene = Scene::create();
#if 0
		// wdf
		std::string str1 = "uisj.wdf";
		std::string str2 = "uigy.wdf";
		uiPad* pad = uiPad::create(str1, str2, false, true);
#else
		// was 散装 可把选中的编号移到指定目录
		std::string str1 = "uisj.wdf.unpack/";
		std::string str2 = "uiyz.wdf.unpack/";
		uiPad* pad = uiPad::create(str1, str2, true, true);
#endif
		if (pad == nullptr)
		{
			return scene;
		}
		pad->onKeyEnter = [str1, pad](const std::vector<std::string>& moves)
		{
			return;
			std::string path = s_desktop + "i.move/";
			ccc_md(path);
			if (!moves.empty())
			{
				for (const auto& m : moves)
				{
					ccc_move(s_desktop + str1 + m + ".was", path);
				}
				pad->removeFromParent();
			}
		};



		scene->addChild(pad);
		return scene;
	}
};


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	srand((uint)&hInstance);

	return cMain::uMain(hInstance, new cMainBrowser(), 10, 0, 0, 0, true);
}