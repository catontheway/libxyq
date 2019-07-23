#pragma once
#include "_inc.h"

class uiManager;
namespace ccu
{
	uiManager* getManager();
	void setManager(uiManager* ui);
}

class uiAccelator;
class uiChannel;
class cDialog;
class uiDye;
// class uiFriend;
class uiFoot;
class uiFoot2;
class uiHeader;
class uiItem;
class uiJob;
class uiLeaderTop;
class uiLearn;
class uiMenu;
class uiPet;
class uiSee;
class uiShichen;
class uiShop;
class uiSkill;
class uiSkiSelect;
class uiSmap;
class uiState;
class uiWorld;
class uiXiangRui;
class uiZz;
// ui管理器
class uiManager : public cNode
{
public:
	CREATE_FUNC(uiManager);

protected:
	virtual bool init();

public:

	// 加点方案
// 	uiAddpoint* getAddpoint(){ return _addpoint; }
// 	uiAddpoint* _addpoint = nullptr;


	// 快捷键
	uiAccelator* getAccelator(){ return _accelator; }
	uiAccelator* _accelator = nullptr;

	// 加点方案
// 	uiInputNO* getInputNO() { return _inputNO; }
// 	uiInputNO* _inputNO = nullptr;


 
	// 添加频道(频道类型, 名字, 文本)
	// #0~#119 表情
	// #W #Y #R #G #B #M #O 颜色
	void addChannel(eChannel e, const std::string& name, const std::string& text);
	void addChannel(const std::string& text);
	uiChannel* getChannel() { return _channel; }
	uiChannel* _channel = nullptr;
	uiChannel* _chat = nullptr;

// 	// 置光标(光标状态)
// 	void setCursor(eCursor e);
// 	// 取光标状态
// 	const eCursor& getCursor();
// 	uiCursor* _cursor = nullptr;
// 
// 
// 	// 打造
// 	uiDazao* getDazao(){ return _dazao; }
// 	uiDazao* _dazao = nullptr;
// 
	// 描述
	cSprite* getDesc(){ return _desc; }
	cSprite* _desc = nullptr;

	// 对话
	cDialog* getDialog(){ return _dialog; }
	cDialog* _dialog = nullptr;

	// 染色
	uiDye* geDye() { return _dye; }
	uiDye* _dye = nullptr;

	// 好友
// 	uiFriend* getFriend() { return _friend; }
// 	uiFriend* _friend = nullptr;

	// 站立足迹
	uiFoot* getFoot(){ return _foot; }
	uiFoot* _foot = nullptr;

	// 足迹
	uiFoot2* getFoot2(){ return _foot2; }
	uiFoot2* _foot2 = nullptr;

	// 右上角的头像和血条
	uiHeader* getHeader(bool pet) { return pet ? _headerPet : _headerRole; }
	uiHeader* _headerRole = nullptr;
	uiHeader* _headerPet = nullptr;

	//物品
	uiItem* getItem() { return _item; }
	uiItem* _item = nullptr;

	// 添加任务(标题, 内容)
	// 重复的标题会被认为更新任务
	void addJob(const std::string& title, const std::string& text);
	uiJob* _job = nullptr;

	// 队长令牌
	uiLeaderTop* getLeaderTop() { return _leaderTop; }
	uiLeaderTop* _leaderTop = nullptr;

	// 帮派技能学习
	uiLearn* getLearnBp(){ return _learnBp; }
	uiLearn* _learnBp = nullptr;

	// 门派技能学习
	uiLearn* getLearnMp(){ return _learnMp; }
	uiLearn* _learnMp = nullptr;

	// 菜单 窗口下方的一排图标
	uiMenu* getMenu(){ return _menu; }
	uiMenu* _menu = nullptr;

	// 宝宝
	uiPet* getPet(){ return _pet; }
	uiPet* _pet = nullptr;

	// 查看
	uiSee* getSee(){ return _see; }
	uiSee* _see = nullptr;

	// 时辰 左上角
	uiShichen* getShichen(){ return _shichen; }
	uiShichen* _shichen = nullptr;

	// 购买
	uiShop* getShop(){ return _shop; }
	uiShop* _shop = nullptr;

	// 人物技能
	uiSkill* getSkill(){ return _skill; }
	uiSkill* _skill = nullptr;

	// 技能选择
	uiSkiSelect* getSkiSelect(){ return _skillSelect; }
	uiSkiSelect* _skillSelect = nullptr;

 	// 小地图
	uiSmap* getSmap(){ return _smap; }
	uiSmap* _smap = nullptr;

	// 人物状态
	uiState* getState(){ return _state; }
	uiState* _state = nullptr;

	// 添加提示(文本, 停留:秒)
	void toast(const std::string& text, float second = 5);

	// 世界地图
	uiWorld* getWorld(){ return _world; }
	uiWorld* _world = nullptr;

	// 祥瑞
	uiXiangRui* getXiangRui(){ return _xiangrui; }
	uiXiangRui* _xiangrui = nullptr;

	// 资质
	uiZz* getZz() { return _zz; }
	uiZz* _zz = nullptr;



	void setBattle(bool battle);
};