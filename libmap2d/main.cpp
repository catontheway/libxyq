#include "../libgg/cMain.h"
#include "cMapWriter.h"

#pragma comment(lib, "../libgg/galaxy2d")


static std::string pathScene = "scene/";
static std::vector<int> s_ids;
static int s_index = -1, s_w = GetSystemMetrics(SM_CXSCREEN) - 32, s_h = GetSystemMetrics(SM_CYSCREEN) - 96;

static void onCreateMap(cNode* node, cLabel* labelMapid, cLabel* labelDesc)
{
	if (++s_index >= s_ids.size())
	{
		return;
	}
	auto m = cMapWriter::create(pathScene, s_ids[s_index], labelMapid, labelDesc);
	if (m == nullptr)
	{
		return;
	}
	m->onFinish = [=]()
	{
		onCreateMap(node, labelMapid, labelDesc);
	};
	Size size = m->getContentSize();
	float sc = std::min(s_w / size.width, s_h / size.height);
	sc = std::min(sc, 1.0f);
	m->setScale(sc);
	node->addChild(m);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	cMain m;
	if (!m.init(s_w, s_h))
	{
		return 0;
	}
	gg::setTitle("浪西游.全景图");

	cNode* scene = cNode::getRoot();

	auto floders = cc::efolder(pathScene, true, 0);
	for (auto name : floders)
	{
		int len = name.size();
		if (len == 8 && name[len - 4] == '.' && name[len - 3] == 'm' && name[len - 2] == 'a' && name[len - 1] == 'p')
		{
			name = name.substr(0, 4);
			s_ids.push_back(std::atoi(name.c_str()));
		}
	}

	cLabel* labelDesc = cLabel::create();
	labelDesc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	labelDesc->setPosition(s_w / 2, 0);
	scene->addChild(labelDesc, 1);


	cLabel* labelMapid = cLabel::create("");
	labelMapid->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	labelMapid->setPosition(s_w / 2, 20);
	scene->addChild(labelMapid, 1);

	if (s_ids.empty())
	{
		labelMapid->setString("未找到可识别的map文件");
	}

	onCreateMap(scene, labelMapid, labelDesc);

	m.start();
 	return 0;
}