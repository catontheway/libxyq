#include "_global.h"


bool TaskZhuXian::Process(int stage)
{
	if (stage == -1)
	{
		return true;
	}
	Init();
	_next = stage + 1;
	switch (m_Chapter)
	{
	case 0:return Process0(stage);
	case 1:return Process1(stage);
	case 2:return Process2(stage);
	case 3:return Process3(stage);
	case 4:return Process4(stage);
	case 5:return Process5(stage);
	case 6:return Process6(stage);
	case 7:return Process7(stage);
	case 8:return Process8(stage);
//	case 9:return Process9(stage);
//	case 10:return Process10(stage);
// 	case 11:return Process11(stage);
// 	case 12:return Process12(stage);
// 	case 13:return Process13(stage);
// 	case 14:return Process14(stage);
// 	case 15:return Process15(stage);
// 	case 16:return Process16(stage);
// 	case 17:return Process17(stage);
// 	case 18:return Process18(stage);
// 	case 19:return Process19(stage);
// 	case 20:return Process20(stage);
// 	case 21:return Process21(stage);
// 	case 22:return Process22(stage);
// 	case 23:return Process23(stage);
// 	case 24:return Process24(stage);
// 	case 25:return Process25(stage);
// 	case 26:return Process26(stage);
// 	case 27:return Process27(stage);
// 	case 28:return Process28(stage);
// 	case 29:return Process29(stage);
// 	case 30:return Process30(stage);
// 	case 31:return Process31(stage);
// 	case 32:return Process32(stage);
	}
	ERRBOX;
	return false;
}

void TaskZhuXian::Init()
{
	m_type = TASK_TYPE_ZHUXIAN;
	m_bInit = true;
	/*m_AutoPath = "¾çÇé";*/
}

TaskZhuXian::TaskZhuXian()
{
	Init();
}

void TaskZhuXian::SetChapter(int chapter)
{
	m_Chapter = chapter;
}

