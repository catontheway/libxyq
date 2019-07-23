#include "_global.h"

// 签到系统
class Sign// : public Node
{
public:
	// 创建签到对象(存档日期, 存档数据, 满签天数)
//	static Sign* create(int &signDate, int &signData, int signMax){ QQ_CREATE(Sign, signDate, signData, signMax); }


	bool init(int &signDate, int &signData, int signMax)
	{
		_signDate = &signDate;
		_signData = &signData;
		_signMax = signMax;
//		return Node::init();
		return true;
	}
		

	// 设置条件(满签是否重置, 断签处理)
	// 断签处理<签的第几天,签的连续天>
	void setCondition(bool isResetIfFull, function<void(int&, int&)> funcBreak = nullptr)
	{
		time_t tt = time(nullptr);
		tm* t = localtime(&tt);
		_yearDay = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;

		if (isNeverSignd())
		{
			return;
		}

		int yearDayLast(*_signDate);

		if (_isSigndToday = _yearDay == yearDayLast)
		{
			return;
		}

//		_signNow = totalContinuity % 10000;
//		XYZ signLastContinue(*_signData);
//		_signNow = signLastContinue.x;

//		if (!isDayContinue(yearDayLast.x, yearDayLast.y, _yearDay.x, _yearDay.y))
		int ydayLast = mDay_to_yDay(yearDayLast / 10000, (yearDayLast % 10000) / 100, (yearDayLast % 100));
		int yday = mDay_to_yDay(_yearDay / 10000, (_yearDay % 10000) / 100, (_yearDay % 100));
		if (!isDayContinue(yearDayLast / 10000, ydayLast, _yearDay / 10000, yday))
		{
// 			if (funcBreak)
// 			{
// 				funcBreak(_signNow, signLastContinue.z);
// 				(*_signData) = signLastContinue;
//			}
			(*_signData) = getSignTotal() * 10000;
		}
// 		else if (_signNow == _signMax - 1 && isResetIfFull)
// 		{
// 			_signNow = 0;
// 		}
// 		else if (++_signNow >= _signMax)
// 		{
// 			_signNow = _signMax - 1;
// 		}
	}

	// 签到
	// 今日已签到; 连续签到次数+1
	// 请主动存档
	void doSign()
	{
		*_signDate = _yearDay;
// 		XYZ signLastContinue(*_signData);
// 		signLastContinue.y = signLastContinue.x;
// 		signLastContinue.x = _signNow;
// 		++signLastContinue.z;
//		*_signData = signLastContinue;
		*_signData = (getSignTotal() + 1) * 10000 + (getSignContinue() + 1);
		_isSigndToday = true;
	}


	// 如果今天要签, 签的是第几次(0~满签次数-1)
// 	int getSignToday()const
// 	{
// 		if (this->isSignedToday())
// 		{
// 			return XYZ(*_signData).x;
// 		}
// 		return _signNow;
// 	}



	// 上一次签的是第几次(0~满签次数-1)
	// 不包括今天签的这次
// 	int getSignLast()const
// 	{
// 		XYZ(*_signData).y;
// 	}



	// 连续签到次数
	int getSignContinue()const
	{
		return (*_signData) % 10000;
//		return XYZ (*_signData).z;
	}

	// 累计签到次数
	int getSignTotal()const
	{
		return (*_signData) / 10000;
	}

	// 今天你签了么...
	bool isSignedToday()const
	{
		return _isSigndToday;
	}



	// 已签(0~满签次数-1)
// 	bool isSigned(int sign)const
// 	{
// 		QQ_ASSERT(sign >= 0 && sign < _signMax, "签到系统 签次错误");
// 		if (this->isSignedToday())
// 		{
// 			return sign <= this->getSignToday();
// 		}
// 		return sign < this->getSignToday();
// 	}



	// 能签?(0~满签次数-1)
	// 签到过后,当天全都不能签
// 	bool isSignable(int sign)const
// 	{
// 		QQ_ASSERT(sign >= 0 && sign < _signMax, "签到系统 签次错误");
// 		if (this->isSignedToday())
// 		{
// 			return false;
// 		}
// 		return sign == this->getSignToday();
// 	}


	// 从未签到
	bool isNeverSignd()
	{
		return !(*_signData) && !(*_signDate);
	}


private:
	// 本次签
//	int _signNow = 0;

 	// 满签次数
 	int _signMax;
public:
	// 存档日期 年月日
	int *_signDate = nullptr;

	// 存档数据 累签连签
	int *_signData = nullptr;
private:
	// 当前日期 年月日
	int _yearDay;

	// 上次签到日期
	bool _isSigndToday = false;


	// 闰年
	bool isLeapYear(int year){ return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; }


	// 转换成0~365天
	int mDay_to_yDay(int year, int month, int mday)
	{
		static char days[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = mday;
		for (int i = 0; i < month - 1; ++i)
		{
			day += days[i];
		}

		if (!isLeapYear(year) && month > 2)
		{
			--day;
		}
		return day;
	}



	// 0~365天, 是否连续
	bool isDayContinue(int yearOld, int dayOld, int year, int day)
	{
		// 年份不一致肯定不连续了...
		if (year > yearOld + 1 || year < yearOld)
		{
			return false;
		}

		// 相差一年的情况: 除了 (year_old最后一天 <--> year第一天), 其他都不连续
		if (year == yearOld + 1)
		{
			if (day > 0)
			{
				return false;
			}
			else
			{
				// 平年和闰年的最后一天不一样(364,365)
				if (isLeapYear(yearOld))
				{
					if (dayOld != 365)
					{
						return false;
					}
				}
				else if (dayOld != 364)
				{
					return false;
				}
			}
		}
		// 同一年的情况:
		else if (year == yearOld)
		{
			if (day != dayOld + 1)
				return false;
		}
		return true;
	}
};


static Sign sign;
static long s_langtimeOnce = 0;
static long s_langtimeLast = 0;
static int s_time20 = 0;
static int s_time21;
bool uiSign::Init()
{
	if (!cInterfaceFather::Init())
	{
		return false;
	}
	loadBack(0x5B8B823E);

	sChild tTitle("签到", 250, 12);
	addChild(tTitle);

	sChild context(" ", 80, 100);
	addChild(context);
	_text = (cText*)context.ptr;



	cInterfaceFather::sChild btn(&g_pMainState->m_Button4, "textBtn", 235, 360);
	_textBtn = (cText*)btn.ptr2;
	btn.onClick = [&](const sChild* c)
	{
		if (sign.isSignedToday())
		{
			return;
		}

		static bool isSignd = false;
		if (isSignd)
		{
			g_pMainState->m_Tags.Add("本次在线已经签过到");
			return;
		}

		if (g_iFPS < 21600)
		{
			g_pMainState->m_Tags.Add(toString("再等%d分钟", (21600 - g_iFPS) / 3600));
			return;
		}
		sign.doSign();
		isSignd = true;

		int r = sign.getSignContinue();
		if (r > 1)
		{
			int e = r * 30;
			g_pMainState->awardk(e, r * 10);
		}

		int e = rand() % 100;
		if (e < 40)
		{
			if (!g_pMainState->awardBookIron(100))
			{
				g_pMainState->awardShouJue1();
			}
		}
		else if (e < 80)
		{
			if (rand() % 100 < r)
			{
				g_pMainState->awardShouJue2();
			}
			else
			{
				g_pMainState->awardShouJue1();
			}
		}
		else
		{
			g_pMainState->award5bao();
		}

		cct::autoSave();
		initShow();
	};
	addChild(btn);
	Move(125, 65);

	sign.init(g_GlobalValues[18], g_GlobalValues[19], 0xFFFF);
	sign.setCondition(false);
	return true;
}


bool uiSign::initShow()
{
	_textBtn->SetString(sign.isSignedToday() ? "今日已签" : "今日签到");
	if (sign.isNeverSignd())
	{
		return true;
	}
	string str = toString("上次签到: #Y%d-%02d-%02d#Y\n\n累计签到: #Y%d#Y\n\n连续签到: #Y%d#Y", 
		(*sign._signDate) / 10000, ((*sign._signDate) % 10000) / 100, ((*sign._signDate) % 100),
		sign.getSignTotal(), sign.getSignContinue());
	_ftext.SetFaceText(str,g_pMainState->m_hFont[0], 480);
	return true;
}


static int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
bool uiSign::Show(cCanvas* pCanvas)
{
	cInterfaceFather::Show(pCanvas);
	if (_text)
	{
		_ftext.SetPos(_text->GetX(), _text->GetY());
	}
	_ftext.Show(pCanvas);
	return true;
}