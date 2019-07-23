#pragma once
#include "_objinc.h"

// class cInterfaceChannel;
// class cCanvas;
struct sTextLine   //一行
{
	static const int MaxLine = 32;
	array<cObjWas, MaxLine> m_Face;
	array<int, MaxLine>    m_xFace;
	int m_NumFace;
	cText m_line;
	int m_Height;
};
struct sColorTag
{
	int m_linenum; //所在行数
	int m_start;  //所在字数
	ulong m_Color; //颜色
};
struct sFaceText //一句 带表情的文字
{
	vector<sColorTag> m_ColorTag;
	int m_Height = 0;
	int m_Gap = 0;
	int m_FirstAdd;//首行缩进
	void Show(cCanvas* pCanvas);
	void SetPos(int x, int y);
	cObjWas m_Channel; //频道
	cText m_Name;  //名字
	int m_LineNum;  //行数
	void SetColor(ulong color){ for (int i = 0; i < sTextLine::MaxLine; i++)m_TextLineList[i].m_line.SetColor(color); }
	vector<sTextLine> m_TextLineList; //一句最多9行
	//                  
	bool SetFaceText(cWasFile* pChannel, string name, string tex, HFONT hFont, int LineWidth);
	bool SetFaceText(string tex, HFONT hFont, int LineWidth);
	sFaceText()
	{
		m_TextLineList.resize(sTextLine::MaxLine);
		m_Channel.m_bStatic = true;
		for (int i = 0; i < sTextLine::MaxLine; i++)
		{
			m_TextLineList[i].m_line.SetColor(RGB(255, 255, 255));
		}
	}
	int m_ShowStyle = 0;  //0表示不显示频道和名字 1表示不显示名字  2表示全部表示  
	void SetTagColor(sColorTag& starttag, sColorTag& endtag);
};