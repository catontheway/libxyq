#pragma  once;
#include "_taskinc.h"

class TaskZhuXian :public cTaskFather
{
public:
	void Init();
	TaskZhuXian();
	virtual bool Process(int stage);
	bool Process0(int stage);//商人的鬼魂
	bool Process1(int stage);//玄奘
	bool Process2(int stage);//四琉璃
	bool Process3(int stage);//小白龙
	bool Process4(int stage);//八戒
	bool Process5(int stage);//真假悟空
	bool Process6(int stage);//三打白骨精
	bool Process7(int stage);//智取芭蕉扇
	bool Process8(int stage);//西梁女国
	bool Process9(int stage);//飞升剧情
	bool Process10(int stage);
	bool Process11(int stage);
	bool Process12(int stage);
	bool Process13(int stage);
	bool Process14(int stage);
	bool Process15(int stage);
	bool Process16(int stage);
	bool Process17(int stage);
	bool Process18(int stage);
	bool Process19(int stage);
	bool Process20(int stage);
	bool Process21(int stage);
	bool Process22(int stage);
	bool Process23(int stage);
	bool Process24(int stage);
	bool Process25(int stage);
	bool Process26(int stage);
	bool Process27(int stage);
	bool Process28(int stage);
	bool Process29(int stage);
	bool Process30(int stage);
	bool Process31(int stage);
	bool Process32(int stage);
	bool Process33(int stage);
	bool Process34(int stage);
	bool Process35(int stage);
	bool Process36(int stage);
	bool Process37(int stage);
	bool Process38(int stage);
	bool Process39(int stage);
	bool Process40(int stage);

	void SetChapter(int chapter);
	int GetChapter(){ return m_Chapter; }
private:
	cObj* m_pObj = 0;
	int m_Chapter;
};
