#pragma once
#include "_inc.h"

// 任务
class uiJob : public cNode
{
public:
	CREATE_FUNC(uiJob);
	virtual bool init();

	// 添加任务(标题, 内容)
	// 重复的标题会被认为更新任务
	bool add(const std::string& title, const std::string& text);
	// 移除任务(标题, 内容)
	bool remove(const std::string& title);

	void updateList();

	cButton* _btnEx = nullptr;
	cButton* _btnLeft = nullptr;
	std::vector<cButton*> _buttonTitles;
	std::vector<cText*> _texts;
	bool _isShow = true;
	bool _isLeft = true;
};