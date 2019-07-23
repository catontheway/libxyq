#include "_global.h"
#include "../libass/cBass.h"

CWdf* cWasFile::m_pWdf[c64];
CWdf* cWasFile::m_pWdfMap[c8];

WDataFileIndex* CWdf::SearchFile(ulong id)
{
	int begin, end, middle;
	begin = 0, end = m_Number - 1;
	// 折半/二分查找 
	// 前提: 有序
	while (begin <= end)
	{
		middle = (begin + end) >> 1;
		if (m_pIndex[middle].uid == id) return &m_pIndex[middle];
		else if (m_pIndex[middle].uid < id) begin = middle + 1;
		else end = middle - 1;
	}
	return 0;
}


bool cWasFile::Open(const char* FileName)
{
	static bool s_isLoaded = false;
	if (!s_isLoaded)
	{
		s_isLoaded = true;
//		if (m_pWdf[s_wdfNum] != 0)
			for (int i = 0; i < c64; i++)
				m_pWdf[i] = 0;
	}
	int i;
	for (i = 0; i < c64; i++)
		if (m_pWdf[i] == 0)
			break;
	if (i == c64)
		return 0;

	m_pWdf[i] = new CWdf();
	if (m_pWdf[i]->Open(FileName))
	{
		m_pWdf[i]->m_Name = FileName;
		return true;
	}
	delete m_pWdf[i];
	m_pWdf[i] = 0;
	return false;
}

bool cWasFile::OpenMap(const char* filename)
{
	static bool s_isLoaded = false;
	if (!s_isLoaded)
	{
		s_isLoaded = true;
//		if (m_pWdf[s_wdfNum] != 0)
		for (int i = 0; i < c8; i++)
			m_pWdfMap[i] = 0;
	}
	int i;
	for (i = 0; i < c8; i++)
		if (m_pWdfMap[i] == 0)
			break;
	if (i == c8)
		return 0;

	m_pWdfMap[i] = new CWdf();
	if (m_pWdfMap[i]->Open(filename))
	{
		m_pWdfMap[i]->m_Name = filename;
		return true;
	}
	delete m_pWdf[i];
	m_pWdf[i] = 0;
	return false;

//	return Open(filename);
	static bool s_isOnce = true;
	if (s_isOnce)
	{
		s_isOnce = false;
		m_pWdfMap[0] = new CWdf();
	}
	
	if (m_pWdfMap[0]->Open(filename))
	{
	//	strcpy_s(m_pWdfMap[0]->m_Name, 256, filename);
		return true;
	}
	return false;
}


void cWasFile::PlayWav()
{
	m_Wav.play();
}
void cWasFile::LoadWav(ulong uid, int position, bool bPlay)
{
	//防止重复加载
	if (!uid)
	{
		Free();
		return;
	}

	if (m_NowID == uid)
	{
		if (bPlay)
		{
			PlayWav();
		}
		return;
// 		if (m_Wav.m_pPrimaryBuffer)
// 		{
// 			m_Wav.m_pPrimaryBuffer->SetCurrentPosition(0);
// 			if (0 == g_GlobalValues[17])
// 				if (bPlay)m_Wav.m_pPrimaryBuffer->Play(0, 0, 0);
// 			return;
// 		}
	}
	m_NowID = uid;

	ifstream* f = 0;
	if (!GetFileP(uid, f))
	{
		Free();
		return;
	}

	//加载文件
	if (m_lpSize < m_Size)
	{
		SAFE_DELETE_ARRAY(lp);
		lp = new uchar[m_Size];
		m_lpSize = m_Size;
	}
	f->read((char*)lp, m_Size);
	m_Wav.Load(lp, m_Size, position, bPlay);
}
bool cWasFile::Load(ulong uid, sChangeColorData* pChangeColorData, string str)
{
 	if (m_NowID == uid)
	{
		return true;
	}
	m_NowID = uid;
	if (!uid)
	{
		Free();
		return true;
	}
	ifstream* f = 0;
	if (!GetFileP(uid, f))
	{
		Free();
		return true;
	}
	//加载文件
	if (m_lpSize < m_Size)
	{
		SAFE_DELETE_ARRAY(lp);
		lp = new uchar[m_Size];
		m_lpSize = m_Size;
	}
	f->read((char*)lp, m_Size);
	switch (m_Type)
	{
	case 1://was
		m_Picture.Load(lp, m_Size, m_Type, pChangeColorData);
		break;
	default:
		LoadWav(uid, 0);
		break;
	}

	return true;
}

bool cWasFile::LoadMap(ulong uid)
{
//	return Load(uid);

	if (m_NowID == uid)
		return true;
	m_NowID = uid;
	if (!uid)
	{
		Free();
		return true;
	}

	ifstream* f = 0;
	if (!GetFileP(uid, m_pWdfMap, c8, f))
	{
		Free();
		return true;
	}
	//加载文件
	if (m_lpSize < m_Size)
	{
		SAFE_DELETE_ARRAY(lp);
		lp = new uchar[m_Size];
		m_lpSize = m_Size;
	}
	f->read((char*)lp, m_Size);
	switch (m_Type)
	{
	case 1://was
		m_Picture.Load(lp, m_Size, m_Type, nullptr);
		break;
// 	default:
// 		LoadWav(uid, 0);
// 		break;
	}
	return true;
}


bool cWasFile::Free()
{
	if (!m_NowID)
		return true;
	m_NowID = 0;
	switch (m_Type)
	{
	case 1:
		m_Picture.Free();
		break;
	default:
		m_Wav.Free();
		break;
	}
	m_NeedShow = true;
	return true;
};

cWasFile::cWasFile()
{
	lp = 0;
	m_PreShowRect.right = -1;
	m_isStatic = false;
	m_NowID = 0;
	m_bMove = false;
}



bool cWasFile::isSelectOn(int x, int y)
{
	int a = m_Picture.getFrameIdx();
	RECT  rect;
	GetPicRange(rect);
	if (isOn(x, y, rect))
	{
		int x1 = x - rect.left;
		int y1 = y - rect.top;
		//?
		if (0 != m_Picture.Spr.lpAlpha[a][x1 + y1*m_Picture.m_Width])
			return true;
	}
	return false;
}

bool cWasFile::CloseWDF()
{
	for (int i = 0; i < c64; i++)
	{
		if (cWasFile::m_pWdf[i])
		{
			cWasFile::m_pWdf[i]->Free();
			SAFE_DELETE(cWasFile::m_pWdf[i]);
		}
	}
// 	if (cWasFile::m_pWdfMap[0])
// 	{
// 		cWasFile::m_pWdfMap[0]->Free();
// 		SAFE_DELETE(cWasFile::m_pWdfMap[0]);
// 	}
	return true;
}


void cWasFile::GetPicRange(RECT& rect)
{
	if (!m_Picture.Spr.m_bLoad)
	{
		rect.right = -1;
		return;
	}
	int a = m_Picture.getFrameIdx();
	DATEHEARD& datehead = m_Picture.Spr.m_pDataOffsetList[a];
	rect.left = m_Picture.m_x - datehead.FramX;
	rect.top = m_Picture.m_y - datehead.FramY;

	if (0 == m_Picture.m_ShowWidth)
		rect.right = rect.left + datehead.Width;
	else
		rect.right = rect.left + GetShowWidth();
	if (0 == m_Picture.m_ShowHeight)
		rect.bottom = rect.top + datehead.Height;
	else
		rect.bottom = rect.top + GetShowHeight();
}
RECT cWasFile::GetPicRange()
{
	RECT rect;
	int a = m_Picture.getFrameIdx();
	rect.left = m_Picture.m_x - m_Picture.Spr.m_pDataOffsetList[a].FramX;
	rect.top = m_Picture.m_y - m_Picture.Spr.m_pDataOffsetList[a].FramY;

	if (0 == GetShowWidth())
		rect.right = rect.left + m_Picture.m_Width;
	else
		rect.right = rect.left + GetShowWidth();

	if (0 == GetShowHeight())
		rect.bottom = rect.top + m_Picture.m_Height;
	else
		rect.bottom = rect.top + GetShowHeight();
	return rect;
}
bool cWasFile::NextFrame()
{
	if (m_isStatic)return false;
	if (1 == m_Picture.m_FrameGap)return false;
	if (m_Picture.m_FrameGap <= m_Picture.m_StepUpdate)
	{
		m_Picture.m_StepUpdate = 0;
		m_Picture.now_frame += 1;
		if (m_Picture.now_frame == m_Picture.Spr.GetMaxFrame())
		{
			if (m_bCircle)
			{
				m_Picture.now_frame = 0;
				if (m_ShowOnce)
					m_NeedShow = false;
			}
			else
			{
				m_Picture.now_frame = (m_Picture.Spr.GetMaxFrame() - 1);
			}
		}
		return true;
	}
	else
	{
//		static int s_fps = 0;
//		if (s_fps != g_iFPS)
//		{
			m_Picture.m_StepUpdate += 1;
//			s_fps = g_iFPS;
//		}
	}

	return false;
}
bool cWasFile::PreFrame()
{
	if (m_isStatic)return false;
	if (0 == m_Picture.m_StepUpdate)
	{
		m_Picture.m_StepUpdate = m_Picture.m_FrameGap - 1;
		m_Picture.now_frame -= 1;
		if (-1 == m_Picture.now_frame)
			m_Picture.now_frame = m_Picture.Spr.GetMaxFrame() - 1;
		return true;
	}
	else
		m_Picture.m_StepUpdate = 0;

	return false;
}
void cWasFile::SetDirection(int dir)
{
	if (m_Direction == dir)return;
	m_Direction = dir;
	m_Picture.m_direction = dir;
	m_bMove = true;

}

bool cWasFile::LoadBMP(string path)
{
	m_NowID = 100;
	m_Type = 6;
	if (m_Picture.Spr.LoadBMP(path))
	{
		m_Picture.m_Width = m_Picture.Spr.GetWidth();
		m_Picture.m_Height = m_Picture.Spr.GetHeight();
	}
	return true;
}

bool cWasFile::GetWillNextFrame()
{
	////////////////////////////////////////////////////////////////////////// 呵呵哒 动画帧
	if (m_Picture.m_StepUpdate == m_Picture.m_FrameGap - 1)
		return true;
	return false;
}

void cWasFile::SetFrame(int frame)
{
	if (!GetMaxFrame())ERRBOX;

	if (m_Picture.GetFrame() != frame)
	{
		m_bMove = true;
		if (m_Picture.Spr.GetMaxFrame() > frame)
		{
			m_Picture.m_StepUpdate = 0;
			m_Picture.SetFrame帧(frame);
		}
		else
			m_Picture.SetFrame帧(0);
	}


}

bool cWasFile::GetFileP(ulong uid, ifstream*& f, const function<void(const uchar *data18)> &cb /* = nullptr */)
{
	if (uid == 204)
	{
		return false;
	}
	return GetFileP(uid, m_pWdf, c64, f, cb);
	//先找到对应的文件
	WDataFileIndex * pf = 0;
	int i;
	//	int ignore = cct::get()->isIgnore(uid);
	int ignoreIndex = 0;
	for (i = 0; i < c64; i++)
	{
		if (m_pWdf[i] == 0)continue;
		pf = m_pWdf[i]->SearchFile(uid);
		if (pf)
		{
// 			if (ignoreIndex != ignore)
// 			{
// 				++ignoreIndex;
// 				continue;
// 			}
			f = m_pWdf[i]->GetFileHandle();
			m_Offset = pf->offset;
			m_Size = pf->size;
			ushort hdw;
			f->seekg(m_Offset, ios_base::beg);
			int dwsize = sizeof(ushort);
			f->read((char*)&hdw, dwsize);
			if (hdw == 'PS')m_Type = 1;
			else m_Type = 0;

			if (cb)
			{
				f->seekg(m_Offset, ios_base::beg);
				unsigned char *ccc = new unsigned char[18];
				f->read((char*)ccc, 18);
				cb(ccc);
				delete[] ccc;
			}

			f->seekg(m_Offset, ios_base::beg);
			m_bMove = true;
			return true;
		}
	}
	if (uid)
	{
		ccc_msgbox("资源读取错误: 0x%8X, %u", uid, uid);
	}
	return false;
}

bool cWasFile::GetFileP(ulong uid, CWdf* wdfs[], int size, ifstream*& f, const function<void(const uchar *data18)> &cb /*= nullptr*/)
{
	//先找到对应的文件
	WDataFileIndex * pf = 0;
	int i;
//	int ignore = cct::get()->isIgnore(uid);
	int ignoreIndex = 0;
	for (i = 0; i < size; i++)
	{
		if (wdfs[i] == 0)continue;
		pf = wdfs[i]->SearchFile(uid);
		if (pf)
		{
// 			if (ignoreIndex != ignore)
// 			{
// 				++ignoreIndex;
// 				continue;
// 			}
			f = wdfs[i]->GetFileHandle();
			m_Offset = pf->offset;
			m_Size = pf->size;
			ushort hdw;
			f->seekg(m_Offset, ios_base::beg);
			int dwsize = sizeof(ushort);
			f->read((char*)&hdw, dwsize);
			if (hdw == 'PS')m_Type = 1;
			else m_Type = 0;

			if (cb)
			{
				f->seekg(m_Offset, ios_base::beg);
				unsigned char *ccc = new unsigned char[18];
				f->read((char*)ccc, 18);
				cb(ccc);
				delete[] ccc;
			}

			f->seekg(m_Offset, ios_base::beg);
			m_bMove = true;
			return true;
		}
	}
	if (uid)
	{
		ccc_msgbox("资源读取错误: 0x%8X, %u", uid, uid);
	}
	return false;
}

//void CWFile::Save(string name)
//{
//	name += ".was";
//	ofstream oss;
//	oss.open(name, ios::binary);
//	oss.write((char*)lp, m_Size);
//	oss.close();
//}

cWasFile::~cWasFile()
{
	SAFE_DELETE_ARRAY(lp);
}

//int CWFile::setfiletype(ExsDate esdate)
//{
//	if (esdate.hdw == 'PS') return 1;                             //was/tcp文件
//	else if (esdate.hdw == 'MB') return 6;						   //bmp文件
//	else if (esdate.sst == 'FIFJ') return 3;                      //jpg文件
//	else if (esdate.dss == 'ELIF') return 4;                      //tga文件
//	else if (esdate.hdw == 'IR' && esdate.nst == 'EVAW') return 5;  //wav文件
//	else if ((esdate.dsg[0] == 0x11) && (esdate.dsg[1] == 0) && (esdate.dsg[2] == 0) && ((esdate.sss == 0x1000) || (esdate.sss == 0x0f00))) return 7;
//	else if ((esdate.hdw & 0x00ff) == 0x00ff) return 2;			   //mp3文件
//	else return 0;
//	return 0;
//}
