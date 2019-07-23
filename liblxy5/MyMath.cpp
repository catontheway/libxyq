#include "_global.h"

static vector<int> s_expTable =
{
	10, 40, 110, 237, 450, 779, 1252, 1898, 2745, 3822, 5159, 6784,
	8726, 11013, 13674, 16739, 20236, 24149, 28641, 33606, 39119, 45208,
	51902, 59229, 67218, 75899, 85300, 95450, 106377, 118110, 130679, 144112,
	158438, 173685, 189882, 207059, 225244, 244466, 264753, 286134, 308639, 332296,
	357134, 383181, 410466, 439019, 468868, 500042, 532569, 566478, 601799, 638560,
	676690, 716517, 757770, 800579, 844972, 890978, 938625, 987942, 1038959, 1091704,
	1146206, 1202493, 1260594, 1320593, 1382356, 1446074, 151172, 1579326, 1648919, 1720528,
	1794182, 1869909, 1947738, 2027699, 2109820, 2194130, 2280657, 2369431, 2460479, 2553832,
	2649518, 2747565, 2848003, 2950859, 3056164, 3163946, 3274233, 3387055, 3502439, 3620416,
	3741014, 3864261, 3990187, 4118819, 4250188, 4384322, 4521249, 4660999, 4803599, 4998571,
	5199419, 5406260, 5609213, 5838379, 6063933, 6295941, 6534544, 6779867, 7032035, 7291172,
	7557407, 7830869, 8111686, 8399990, 8695912, 8999586, 9311145, 9630726, 9958463, 10294496,
	10638964, 10992005, 11353761, 11724374, 12103988, 12492748, 12890799, 13298287, 13715362, 14142172,
	14578867, 15025600, 15482522, 15949788, 16427552, 16915970, 17415202, 17925402, 18446732, 18979354,
	19523428, 20079116, 20646584, 21225998, 43635044, 44842648, 46075148, 47332886, 48616200, 74888150,
	76891401, 78934581, 81018219, 83142834, 85308968, 87517159, 89767944, 92061872, 94399488, 129041783,
	132277315, 135573313, 138930533, 142349724, 218747456, 224065576, 229840080, 234992173, 240602904, 533679362,
	819407100, 1118169974, 1430306664, 1756161225, 2000000000
};

struct sExpMoney
{
	int exp;
	int money;
};
static vector<sExpMoney> s_skillTable =
{{ 1, 1 },
	{ 16, 6 },
	{ 32, 12 },
	{ 52, 19 },
	{ 75, 28 },
	{ 103, 38 },
	{ 136, 51 },
	{ 179, 67 },
	{ 231, 86 },
	{ 295, 110 },
	{ 372, 139 },
	{ 466, 174 },
	{ 578, 216 },
	{ 711, 266 },
	{ 867, 325 },
	{ 1049, 393 },
	{ 1260, 472 },
	{ 1503, 563 },
	{ 1780, 667 },
	{ 2096, 786 },
	{ 2452, 919 },
	{ 2854, 1070 },
	{ 3304, 1238 },
	{ 3807, 1426 },
	{ 4364, 1636 },
	{ 4983, 1868 },
	{ 5664, 2124 },
	{ 6415, 2404 },
	{ 7238, 2714 },
	{ 8138, 3050 },
	{ 9120, 3420 },
	{ 10188, 3820 },
	{ 11347, 4255 },
	{ 12602, 4725 },
	{ 13959, 5234 },
	{ 15423, 5783 },
	{ 16998, 6374 },
	{ 18692, 7009 },
	{ 20508, 7690 },
	{ 22452, 8419 },
	{ 24532, 9199 },
	{ 26753, 10032 },
	{ 29121, 10920 },
	{ 31642, 11865 },
	{ 34323, 12871 },
	{ 37169, 13938 },
	{ 40188, 15070 },
	{ 43388, 16270 },
	{ 46773, 17540 },
	{ 50352, 18882 },
	{ 54132, 20299 },
	{ 58120, 21795 },
	{ 62324, 23371 },
	{ 66750, 25031 },
	{ 71407, 26777 },
	{ 76303, 28613 },
	{ 81444, 30541 },
	{ 86840, 32565 },
	{ 92500, 34687 },
	{ 98430, 36911 },
	{ 104640, 39240 },
	{ 111136, 41676 },
	{ 117931, 44224 },
	{ 125031, 46886 },
	{ 132444, 49666 },
	{ 140183, 52568 },
	{ 148253, 55595 },
	{ 156666, 58749 },
	{ 165430, 62036 },
	{ 174556, 65458 },
	{ 184052, 69019 },
	{ 193930, 72723 },
	{ 204198, 76574 },
	{ 214868, 80575 },
	{ 225948, 84730 },
	{ 237449, 89043 },
	{ 249383, 93518 },
	{ 261760, 98160 },
	{ 274589, 102971 },
	{ 287884, 107956 },
	{ 301652, 113119 },
	{ 315908, 118465 },
	{ 330662, 123998 },
	{ 345924, 129721 },
	{ 361708, 135640 },
	{ 378023, 141758 },
	{ 394882, 148080 },
	{ 412297, 154611 },
	{ 430280, 161355 },
	{ 448844, 168316 },
	{ 468000, 175500 },
	{ 487760, 182910 },
	{ 508137, 190551 },
	{ 529145, 198429 },
	{ 550796, 206548 },
	{ 573103, 214913 },
	{ 596078, 223529 },
	{ 619735, 232400 },
	{ 644088, 241533 },
	{ 669149, 250931 },
	{ 694932, 260599 },
	{ 721452, 270544 },
	{ 748722, 280770 },
	{ 776755, 291283 },
	{ 805566, 302087 },
	{ 835169, 313188 },
	{ 865579, 324592 },
	{ 896809, 336303 },
	{ 928876, 348328 },
	{ 961792, 360672 },
	{ 995572, 373339 },
	{ 1030234, 386337 },
	{ 1065190, 399671 },
	{ 1102256, 413346 },
	{ 1139649, 427368 },
	{ 1177983, 441743 },
	{ 1217273, 456477 },
	{ 1256104, 471576 },
	{ 1298787, 487045 },
	{ 1341043, 502891 },
	{ 1384320, 519120 },
	{ 1428632, 535737 },
	{ 1473999, 552749 },
	{ 1520435, 570163 },
	{ 1567957, 587984 },
	{ 1616583, 606218 },
	{ 1666328, 624873 },
	{ 1717211, 643954 },
	{ 1769248, 663468 },
	{ 1822456, 683421 },
	{ 1876852, 703819 },
	{ 1932456, 724671 },
	{ 1989284, 745981 },
	{ 2047353, 767757 },
	{ 2106682, 790005 },
	{ 2167289, 812733 },
	{ 2229192, 835947 },
	{ 2292410, 859653 },
	{ 2356960, 883860 },
	{ 2422861, 908573 },
	{ 2490132, 933799 },
	{ 2558792, 959547 },
	{ 2628860, 985822 },
	{ 2700356, 1012633 },
	{ 2773296, 1039986 },
	{ 2847703, 1067888 },
	{ 2923593, 1096347 },
	{ 3000989, 1125371 },
	{ 3079908, 1154965 },
	{ 3160372, 1185139 },
	{ 3242400, 1215900 },
	{ 6652022, 2494508 },
	{ 6822452, 2558419 },
	{ 6996132, 2623549 },
	{ 7173104, 2689914 },
	{ 7353406, 2757527 },
	{ 11305620, 4239607 },
	{ 11586254, 4344845 },
	{ 11872072, 4452027 },
	{ 12163140, 4561177 },
	{ 12459518, 4672319 },
	{ 15033471, 450041 },
	{ 15315219, 4594563 },
	{ 15600468, 4680138 },
	{ 15889236, 4766769 },
	{ 16181550, 4854465 },
	{ 16477425, 4943226 },
	{ 16776885, 5033064 },
	{ 17079954, 5123985 },
	{ 17386650, 5215995 },
	{ 17697000, 5309100 },
	{ 24014692, 7204407 },
	{ 24438308, 7331490 },
	{ 24866880, 7460064 },
	{ 25300432, 7590129 },
	{ 25739000, 7721700 },
	{ 32728255, 9818475 },
	{ 33289095, 9986727 },
	{ 33856310, 10156893 },
	{ 34492930, 10328979 },
	{ 40842000, 12252600 },

	{ 408420000, 122526000 },
	{ 408420000, 122526000 },
	{ 408420000, 122526000 },
};


int GetDirection4(int x1, int y1, int xTarget, int yTarget)
{
	if (x1 > xTarget)
	{
		if (y1 > yTarget)
		{
			return 7;
		}
		else
			return 1;
	}
	else
	{
		if (y1 > yTarget)
		{
			return 9;
		}
		else
			return 3;
	}
}


int GetReverseDirection(int Direction)
{
	switch (Direction)
	{
	case 1:
		return 9;
	case 2:
		return 8;
	case 3:
		return 7;
	case 4:
		return 6;
	case 6:
		return 4;
	case 7:
		return 3;
	case 8:
		return 2;
	case 9:
		return 1;
	}
	return 0;
}

bool isOn(int x, int y, RECT& rect)
{
	if (x > rect.left &&
		x<rect.right&&
		y > rect.top&&
		y<rect.bottom)return true;
	return false;
}

bool isOn(int x, int y, int w, int h, int left, int top, int right, int bottom)
{
	if (x > right)return false;
	if (y > bottom)return false;
	if (x + w < left)return false;
	if (y + h < top)return false;
	return true;
}

int GetCharacterExp(int Lv)
{
	return s_expTable[Lv];
// 	INT64 Exp = GetNormalFightExp(Lv, Lv, 5);
// 	int k = Lv - 1;
// 	if (k < 0)k = 0;
// 	Exp = 200;
// 	Exp += Exp * ((Lv*Lv*Lv) - (k*k*k));// / 100;
// 	Exp = Exp * Lv / 10;
// 	if (Lv >= 165)
// 	{
// 		Exp *= 10;
// 		if (Lv > 175)
// 		{
// 			Exp *= ((Lv - 165) / 10) * 10;
// 		}
// 	}
// 	if (Lv>145)
// 	{
// 		Exp = (Exp*(Lv - 140)) / 2;
// 	/*	if (Lv > 170)
// 			Exp *= 3;
// 		else
// 		if (Lv > 160)
// 			Exp *= 2;*/
// 	}
//	return Exp;
}



int GetPetExp(int Lv)
{
	if (Lv == 0)
	{
		return 10;
	}
	if (Lv == cct::MaxBabyLv + 1)
	{
		return 800000000;
	}
	int exp = Lv * 10000;
	exp = exp * Lv / cct::MaxBabyLv;
	return exp;
// 	int Exp = GetNormalFightExp(Lv, Lv, 5);
// 	int k = Lv - 1;
// 	if (k < 0)k = 0;
// 	Exp = 2;
// 	Exp += Exp * ((Lv*Lv*Lv) - (k*k*k));// / 100;
// 	Exp = Exp * Lv / 10 + (Lv * 10) + 10;
// 	if (Lv >= 165)
// 	{
// 		Exp *= 10;
// 		if (Lv > 175)
// 		{
// 			Exp *= ((Lv - 165) / 10) * 10;
// 		}
// 	}
// 	if (Lv>145)
// 	{
// 		Exp = (Exp*(Lv - 140)) / 2;
// 	/*	if (Lv > 170)
// 			Exp *= 3;
// 		else
// 		if (Lv > 160)
// 			Exp *= 2;*/
// 	}
//	return Exp;
}



int GetNormalFightExp(int OurLv, int EnemyLv, int NumOfPeople)
{
	int EarnExp = (25 + EnemyLv * 8) * (NumOfPeople + 5) * 3 / 2 + 128;

// 	int Offset = OurLv - EnemyLv;// abs(OurLv - EnemyLv);
// 	if (Offset > 15)
// 		EarnExp = 1;
// 	else
// 	if (Offset > 10)
// 	{
// 		EarnExp=EarnExp >> 1;
// 	}
// 	else
// 	if (Offset > 5)
// 	{
// 		EarnExp = EarnExp * 80 / 100;
// 	}
// 	else
// 	if (Offset < -5)//我方等级低于怪物等级5级
// 	{
// 		EarnExp = EarnExp * 120 / 100;
// 
// 	}
// 	else
// 	if (Offset < -10)//我方等级低于怪物等级10级
// 	{
// 		EarnExp = EarnExp * 150 / 100;
// 	}
	if (EarnExp < 1)EarnExp = 1;
	return EarnExp;
}

ulong GetPriceColor(INT64 Price)
{
	if (Price < 10000)
		return  RGB(0,0,0);
	if (Price < 100000)
		return  RGB(0,0,255);
	if (Price<1000000)
		return  RGB(0, 140, 0);
	if (Price < 10000000)
		return  RGB(255, 0, 0);
    return  RGB(238,0,238);
}

int GetXiuLIanExp(int lv)
{
	if (lv == 0)
	{
		return 0;
	}
	int exp = 150;
	for (int i = 1; i < lv; ++i)
	{
		exp += (4 + i * 2) * 10;
	}
	return exp;
}

bool CheckCross(RECT& rect1, RECT& rect2, RECT& outrect)
{
	if (rect1.right < rect2.left)return false;
	if (rect2.right < rect1.left)return false;
	if (rect1.bottom < rect2.top)return false;
	if (rect2.bottom < rect1.top)return false;
	outrect.left = rect1.left>rect2.left ? rect1.left : rect2.left;
	outrect.right = rect1.right > rect2.right ? rect2.right : rect1.right;
	outrect.top = rect1.top > rect2.top ? rect1.top : rect2.top;
	outrect.bottom = rect1.bottom > rect2.bottom ? rect2.bottom : rect1.bottom;
	return true;
}
bool CheckCross(RECT& rect1, RECT& rect2)
{
	if (rect1.right < rect2.left)return false;
	if (rect2.right < rect1.left)return false;
	if (rect1.bottom < rect2.top)return false;
	if (rect2.bottom < rect1.top)return false;
	return true;
}




int GetMainSkillExp(int lv)
{
	return s_skillTable[lv].exp;
	int exp = 3*lv*lv*lv + lv*lv + 14 * lv+10;
	return exp / 10;
}

int GetMainSkillMoney(int lv)
{
	return s_skillTable[lv].money;
	int money = lv*lv*lv + lv*lv + 12 * lv+10;
	return money / 10;
}

bool StringToWString(const std::string &str, std::wstring &wstr)
{
	int nLen = (int)str.length();
	wstr.resize(nLen, L' ');

	int nResult = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);

	if (nResult == 0)
	{
		return false;
	}

	return true;
}

int GetRotateDirection(int nowDirection, bool directNum4 /*= true*/, bool turn /*= 0*/)
{
	if (turn)
	{
		switch (nowDirection)
		{
		case 1:if (directNum4)return 7; else return 4;
		case 2:return 1;
		case 3:if (directNum4)return 1; else return 2;
		case 4:return 7;
		case 6:return 3;
		case 7:if (directNum4)return 9; else return 8;
		case 8:return 9;
		default:if (directNum4)return 3; else return 3;
		}
	}
	else
	{
		switch (nowDirection)
		{
		case 1:if (directNum4)return 3; else return 2;
		case 2:return 3;
		case 3:if (directNum4)return 9; else return 6;
		case 4:return 1;
		case 6:return 9;
		case 7:if (directNum4)return 1; else return 4;
		case 8:return 7;
		default:if (directNum4)return 7; else return 8;
		}
	}
}

int Direction8To4(int direction)
{
	if (direction > 9)direction = 9;
	switch (direction)
	{
	case 2:return 1;
	case 4:return 3;
	case 5:return 9;
	case 6:return 3;
	case 8:return 7;
	}
	return 1;
}


void CoutPoint(float distance, float xstart, float ystart, float xend, float yend, float &xout, float& yout)
{//计算 从 xstart ystart  到 xstart ystart  距离为 ditance 的点的坐标
	float angel = atan2(yend - ystart, xend - xstart);
	yout =ystart+ distance*sin(angel);
	xout =xstart+ distance*cos(angel);
}

float CoutDistance(float xstart, float ystart, float xend, float yend)
{
	float x = (xstart - xend);
	float y = (ystart - yend);
	x *= x;
	y *= y;
	return sqrt(x + y);
}

int GetDirection8Ex(int predirection, int x1, int y1, int xTarget, int yTarget)
{//通过原点和终点得到向量的方向
	float  yOffset = (float)(yTarget-y1);
	float  xOffset = (float)(xTarget-x1);
	float angel = atan2(yOffset, xOffset);

	if (angel>0)
	{
		if (angel < 0.2618)
			return 6;
		else
		if (angel < 0.5236)
		{
			if (predirection == 6 || predirection == 3)
				return predirection;
			else
			{
				if (angel < 0.3927)
					return 6;
				else return 3;
			}
		}
		else if (angel < 1.0472)
			return 3;
		else if (angel < 1.3089)
		{
			if (predirection == 2 || predirection == 3)
				return predirection;
			else
			{
				if (angel < 1.178)
					return 6;
				else return 3;
			}
		}
		else if (angel < 1.8326)
			return 2;
		else if (angel < 2.0944)
		{
			if (predirection == 2 || predirection == 1)
				return predirection;
			else
			{
				if (angel < 1.9635)
					return 2;
				else return 1;
			}
		}
		else if (angel < 2.618)
			return 1;
		else  if (angel < 2.8798)
		{
			if (predirection == 4 || predirection == 1)
				return predirection;
			else
			{
				if (angel < 2.7489)
					return 1;
				else return 4;
			}
		}
		else return 4;
	}
	else
	{//左
		if (angel > -0.2618)
			return 6;
		else
		if (angel > -0.5236)
		{
			if (predirection == 6 || predirection == 9)
				return predirection;
			else
			{
				if (angel > -0.3927)
					return 6;
				else return 9;
			}
		}
		else if (angel > -1.0472)
			return 9;
		else if (angel > -1.3089)
		{
			if (predirection == 9 || predirection == 8)
				return predirection;
			else
			{
				if (angel > -1.178)
					return 9;
				else return 8;
			}
		}
		else if (angel > -1.8326)
			return 8;
		else if (angel > -2.0944)
		{
			if (predirection == 8 || predirection == 7)
				return predirection;
			else
			{
				if (angel > -1.9635)
					return 8;
				else return 7;
			}
		}
		else if (angel > -2.618)
			return 7;
		else  if (angel > -2.8798)
		{
			if (predirection == 7 || predirection == 4)
				return predirection;
			else
			{
				if (angel > -2.7489)
					return 7;
				else return 4;
			}
		}
		else return 4;
	}
}

INT64 AddUpZero(INT64& target, const int num)
{
	target += num;
	if (target < 0)
	{
		INT64 ret = target;
		target = 0;
		return ret;
	}
	else return 0;
}

int ReadInt(HANDLE& f)
{
	//ulong exdata;
	char data;
	while (1)
	{
		bool bFind = false;
		while (1)
		{
			switch (ReadCharNum(f, data))
			{
			case 0:
				break;
			case 1:
				bFind = true;
				break;
			case 2:
				return -1;
			}
			if (bFind)break;
		}
		int numlist[20];
		int num = 0;
		numlist[0] = GetNumByChar(data);
		num += 1;
				while (1==ReadCharNum(f, data))
				{//找到剩下的数字
					numlist[num] = GetNumByChar(data);
					num += 1;
					if (num == 11)
						return -1;
				}
			
				int outnum=0;
				for (int i = 0; i < num; i++)
				{					
					switch (num-i-1)
					{
					case 0:
						outnum += numlist[i];
						break;
					case 1:outnum  += numlist[i] * 10; break;
					case 2:outnum  += numlist[i] * 100; break;
					case 3:outnum  += numlist[i] * 1000; break;
					case 4:outnum  += numlist[i] * 10000; break;
					case 5:outnum  += numlist[i] * 100000; break;
					case 6:outnum += numlist[i] * 1000000; break;
					case 7:outnum += numlist[i] * 10000000; break;
					case 8:outnum += numlist[i] * 100000000; break;
					case 9:outnum += numlist[i] * 1000000000; break;
					}

				}
				return outnum;
	}
}
#include <io.h>
int ReadCharNum(HANDLE& f, char& out)
{
	ulong exdata;
	//bool bSpace = false;

	ReadFile(f, &out, 1, &exdata, 0);
	//if (0 == exdata)
	//	int k = 0;
	if (out >= '0'&&out <= '9')
	{
		return 1;
	}
	return 0;
}

int GetNumByChar(char data)
{
	data -= '0';
	return (int)data;
}

void SetINT(int num, int id)
{
	int k = 0x01;
	k = k << id;
	g_GlobalValues[num] |= k;
}

bool CheckINT(int num, int id)
{
	g_GlobalValues[id];
	if ((g_GlobalValues[num] >> id) & 0x01)return true;
	return false;
}

int GetFrameIndex(int FrameMax, int NowFrame, int DirectionNum, int NowDirection)
{
	if (FrameMax == 1 && DirectionNum == 1)
	{
		return 0;
	}
	else
	{
		if (NowFrame >= FrameMax)
		{
			NowFrame = FrameMax - 1;
		}
		if (DirectionNum >= 9)
		{
			DirectionNum = 9;
		}
		if (DirectionNum == 1)
		{
			return NowFrame;
		}
		else
		{
			int a = 0;
			switch (NowDirection)
			{
			case 8:a = 6; break;
			case 2:a = 4; break;
			case 4:a = 5; break;
			case 6:a = 7; break;
			case 9:a = 3; break;
			case 3:return NowFrame;
			case 1:a = 1; break;
			case 7:a = 2; break;
			}
			a = FrameMax * a + NowFrame;
			if (a >= FrameMax * DirectionNum)
			{
				a = FrameMax * DirectionNum - 1;
			}
			return a;
		}
	}
}


