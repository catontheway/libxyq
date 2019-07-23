#include "_global.h"

void sFaceText::SetPos(int x, int y)
{
	int bottom = y + m_Gap + m_TextLineList[0].m_Height;
	SIZE  size1;

	//int firstgap = 0;//
	//第一行还要算进去频道图片的宽度
	GetTextExtentPointA(g_DC, m_TextLineList[0].m_line.GetString().c_str(), 3, &size1);
	m_TextLineList[0].m_line.SetXY(x + m_FirstAdd, bottom - size1.cy);
	switch (m_ShowStyle)
	{
	case 2:
		GetTextExtentPointA(g_DC, m_Name.GetString().c_str(), 3, &size1);
		m_Name.SetXY(x + 30, bottom - size1.cy);
	case 1:
		m_Channel.SetXY(x, bottom);
		break;
	}

	for (int j = 0; j < m_TextLineList[0].m_NumFace; j++)
	{
		m_TextLineList[0].m_Face[j].m_x = x + m_FirstAdd + m_TextLineList[0].m_xFace[j];
		m_TextLineList[0].m_Face[j].m_y = bottom + 5;
	}
	for (int i = 1; i < m_LineNum; i++)
	{
		bottom += m_Gap + m_TextLineList[i].m_Height;
		GetTextExtentPointA(g_DC, m_TextLineList[i].m_line.GetString().c_str(), 3, &size1);
		m_TextLineList[i].m_line.SetXY(x, bottom - size1.cy);
		for (int j = 0; j < m_TextLineList[i].m_NumFace; j++)
		{
			m_TextLineList[i].m_Face[j].m_x = x + m_TextLineList[i].m_xFace[j];
			m_TextLineList[i].m_Face[j].m_y = bottom;
		}
	}
}
bool sFaceText::SetFaceText(string tex, HFONT hFont, int LineWidth)
{
	return SetFaceText(0, "", tex, hFont, LineWidth);
}
bool sFaceText::SetFaceText(cWasFile* pChannel, string name, string tex, HFONT hFont, int LineWidth)
{
	for (int i = 0; i < m_TextLineList.size(); i++)
	{
		m_TextLineList[i].m_NumFace = 0;
	}
	m_ColorTag.clear();
	SIZE size1;
	cInterfaceChannel* p = &g_pMainState->m_Channel;
	HFONT oldFont = (HFONT)SelectObject(g_DC, hFont);
	char line[1024];
	if (pChannel)
		m_Channel.Set(pChannel);
	if (0 < m_ShowStyle)
	{
		m_FirstAdd = 35;//计算首行缩进
	}
	else
		m_FirstAdd = 0;
	if (2 == m_ShowStyle)
	{
		//保存名字
		if (name.size())
		{
			char name1[20];
			memcpy_s(name1, 20, name.c_str(), name.size());
			char name2[20];
			name2[0] = ' ';
			name2[1] = '[';
			int k = 2;
			for (int i = 0; i < name.size(); i++)
			{
				name2[k] = name1[i];
				k += 1;
			}
			name2[k] = ']';
			name2[k + 1] = 0;
			string name3 = name2;
			m_Name.SetString(name3);
			GetTextExtentPointA(g_DC, m_Name.GetString().c_str(), m_Name.GetString().size(), &size1);
			m_FirstAdd += size1.cx;
		}
		else m_ShowStyle = 1;
	}
	//计算1个空格的宽度,
	GetTextExtentPointA(g_DC, " ", 3, &size1);
	int spaceLength = size1.cx;

	m_LineNum = 0; //重新计算行数
	//m_TextLineList[m_LineNum].m_NumFace = 0;

	int TextNum = 0;//保存一行的字数;
	int totalWidth = LineWidth - m_FirstAdd;//第一行的宽度
	uchar  cha[1024];
	memcpy_s(cha, 1024, tex.c_str(), tex.size());
	int kk32 = tex.size();
	const int limitH = 22;
	m_TextLineList[0].m_Height = limitH;
	for (int i = 0; i < kk32; i++)
	{
		//如果不在0-128之内(也就是说,它是汉字)
		if (cha[i]>127)
		{
			line[TextNum] = cha[i];
			i += 1;
			line[TextNum + 1] = cha[i];
			TextNum += 2;
			GetTextExtentPointA(g_DC, line, TextNum, &size1);

			if (size1.cx >= totalWidth)
			{

				line[TextNum - 2] = 0;
				m_TextLineList[m_LineNum].m_line.SetString(line);
				m_LineNum += 1;
				//换行
				totalWidth = LineWidth - 3;
				TextNum = 0;
				//	m_TextLineList[m_LineNum].m_NumFace = 0;
				m_TextLineList[m_LineNum].m_Height = limitH;
				line[TextNum] = cha[i - 1];
				line[TextNum + 1] = cha[i];
				TextNum += 2;
			}
		}
		else
		{
			if (cha[i] == '\t')
			{
				//	i += 1;
				continue;
			}
			else
				if (cha[i] == '\n')
				{
				//	i += 1;
				line[TextNum] = 0;
				m_TextLineList[m_LineNum].m_line.SetString(line);
				m_LineNum += 1;
				//换行
				totalWidth = LineWidth - 3;
				TextNum = 0;
				//	m_TextLineList[m_LineNum].m_NumFace = 0;
				m_TextLineList[m_LineNum].m_Height = limitH;
				}
				else
					if (cha[i] == '#')
					{
				int kk = 0; //数字的位数
				while (cha[i + 1 + kk] == '\r' || cha[i + 1 + kk] == '\n')
					kk += 1;
				int IDNum = 0;
				if (i == kk32 - 1)break;
				int type = cha[i + 1];
				if (type >= 47 && type < 58)//数字
				{
					//读取表情的ID	

					char dust1[5];
					while (1)
					{
						if (cha[i + 1 + IDNum] == '\r' || cha[i + 1 + IDNum] == '\n')
							IDNum += 1;
						else
						{
							if (cha[i + 1 + IDNum] >= 47 && cha[i + 1 + IDNum] < 58)//是否是数字
							{
								dust1[IDNum] = cha[i + 1 + IDNum];
								IDNum += 1;
							}
							else
								break;
						}
					}
					dust1[IDNum] = 0;
					//计算表情宽度
					GetTextExtentPointA(g_DC, line, TextNum, &size1);
					int faceid = atoi(dust1);
					if (faceid > 128)faceid = 0;
					cWasFile& pWFile = p->m_Face[faceid];
					if (0 == pWFile.m_NowID)
						pWFile.Load(g_pMainState->m_Channel.m_FaceId[faceid]);
					////////////////////////////////////////////////////////////////////////// 呵呵哒
					size1.cx += 3;
					if (size1.cx + pWFile.m_Picture.m_Width > totalWidth)
					{

						line[TextNum] = 0;
						m_TextLineList[m_LineNum].m_line.SetString(line);

						//换行
						m_LineNum += 1;
						totalWidth = LineWidth - 3;
						TextNum = 0;
						m_TextLineList[m_LineNum].m_Height = limitH;
						//	m_TextLineList[m_LineNum].m_NumFace += 1;
						m_TextLineList[m_LineNum].m_xFace[m_TextLineList[m_LineNum].m_NumFace] = 0;
					}
					else
					{
						m_TextLineList[m_LineNum].m_xFace[m_TextLineList[m_LineNum].m_NumFace] = size1.cx;// +namelength;
					}
					//计算高度
					if (pWFile.GetHeight() > m_Height)
					{
						m_TextLineList[m_LineNum].m_Height = pWFile.GetHeight();
					}
					m_TextLineList[m_LineNum].m_Face[m_TextLineList[m_LineNum].m_NumFace].Set(&pWFile);
					m_TextLineList[m_LineNum].m_NumFace += 1;
					int kkk = (pWFile.m_Picture.m_Width) / spaceLength + 2;
					for (int f = 0; f <= kkk; f++)
					{
						line[TextNum] = ' ';
						TextNum += 1;
					}
					i += IDNum + kk;
				}
				else
				{
					ulong color = 0;
					switch (type)  //是否是颜色
					{
					case 87:
					case 119:  //W  白
						color = RGB(255, 255, 255);
						break;
					case 88:
					case 120:  //X  B被占用了,就用X代替吧
						color = RGB(0, 0, 0);
						break;
					case  89:  //Y  黄
					case 121:
						color = RGB(255, 255, 0);
						break;
					case  82:  //r 红
					case 114:
						color = RGB(255, 0, 0);
						break;
					case  71:  //g  绿
					case 103:
						color = RGB(0, 255, 0);
						break;
					case  66:  //b   蓝
					case  98:
						color = RGB(0, 0, 255);
						break;
					default:
						continue;
						break;
					}
					sColorTag tag;
					tag.m_Color = color;
					tag.m_linenum = m_LineNum;
					GetTextExtentPointA(g_DC, line, TextNum, &size1);
					tag.m_start = size1.cx;
					m_ColorTag.push_back(tag);
					i += 1 + kk;
				}
					}
					else
					{
						line[TextNum] = cha[i];
						TextNum += 1;
						GetTextExtentPointA(g_DC, line, TextNum, &size1);
						if (size1.cx > totalWidth)
						{
							totalWidth = LineWidth - 3;
							line[TextNum - 1] = 0;
							m_TextLineList[m_LineNum].m_line.SetString(line);
							//下一行
							m_LineNum += 1;
							//	m_TextLineList[m_LineNum].m_NumFace = 0;
							m_TextLineList[m_LineNum].m_Height = limitH;
							TextNum = 0;
							line[TextNum] = cha[i];
							TextNum += 1;
						}
					}
		}
	}
	line[TextNum] = 0;
	m_TextLineList[m_LineNum].m_line.SetString(line);
	m_LineNum += 1;
	//颜色修正
	if (m_ColorTag.size())
	{
		int num = m_ColorTag.size() / 2;
		for (int i = 0; i < num; i += 1)
		{
			if (m_ColorTag[i * 2].m_linenum != m_ColorTag[i * 2 + 1].m_linenum)
			{
				int linenum = m_ColorTag[i * 2 + 1].m_linenum - m_ColorTag[i * 2].m_linenum;

				m_TextLineList[m_ColorTag[i * 2].m_linenum].m_line.SetTagColor(
					m_ColorTag[i * 2].m_start,
					-1,
					m_ColorTag[i * 2].m_Color);
				for (int i2 = 1; i2 < linenum; i2++)
				{
					m_TextLineList[m_ColorTag[i * 2].m_linenum + i2].m_line.SetTagColor(
						-1,
						-1,
						m_ColorTag[i * 2].m_Color);
				}
				m_TextLineList[m_ColorTag[i * 2 + 1].m_linenum].m_line.SetTagColor(
					0,
					m_ColorTag[i * 2 + 1].m_start,
					m_ColorTag[i * 2].m_Color);
			}
			else
				m_TextLineList[m_ColorTag[i * 2].m_linenum].m_line.SetTagColor(
				m_ColorTag[i * 2].m_start,
				m_ColorTag[i * 2 + 1].m_start,
				m_ColorTag[i * 2].m_Color);
		}
	}

	//计算高度
	m_Height = 0;
	for (int i = 0; i < m_LineNum; i++)
	{
		m_Height += m_TextLineList[i].m_Height + m_Gap;
	}
	SelectObject(g_DC, oldFont);
	return true;
}


void sFaceText::Show(cCanvas* pCanvas)
{
	switch (m_ShowStyle)
	{
	case 2:
		pCanvas->Add(&m_Name);
	case 1:
		pCanvas->Add(&m_Channel, 1);
		break;
	}
	for (int i = 0; i < m_LineNum; i++)
	{
		pCanvas->Add(&m_TextLineList[i].m_line);
		for (int j = 0; j < m_TextLineList[i].m_NumFace; j++)
		{
			pCanvas->Add(&m_TextLineList[i].m_Face[j], 1);
		}
	}

}

void sFaceText::SetTagColor(sColorTag& starttag, sColorTag& endtag)
{
	if (endtag.m_linenum == starttag.m_linenum)
		m_TextLineList[starttag.m_linenum].m_line.SetTagColor(starttag.m_start, endtag.m_start, starttag.m_Color);
	else
	{
		m_TextLineList[starttag.m_linenum].m_line.SetTagColor(starttag.m_start, -1, starttag.m_Color);

		for (int i = starttag.m_linenum + 1; i < endtag.m_linenum; i++)
		{
			m_TextLineList[starttag.m_linenum].m_line.SetTagColor(-1, -1, starttag.m_Color);

		}
		m_TextLineList[starttag.m_linenum].m_line.SetTagColor(-1, endtag.m_start, starttag.m_Color);
	}
}
