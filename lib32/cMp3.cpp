#include "cMp3.h"
#pragma comment(lib,"Strmiids.lib") 
#pragma comment(lib,"Msacm32.lib") 



cMp3* cMp3::getInstance()
{
	static cMp3* s_mp3 = new cMp3();
	return s_mp3;
}


const std::string& cMp3::getEasyName()
{
	return _easyName;
}


bool cMp3::load(const std::string& path, const std::string& easyname, bool checkpre /* = true */)
{
	if (checkpre && _easyName == easyname)
	{
		return true;
	}

	std::string name = path + easyname + ".mp3";
	FILE* file = fopen(name.c_str(), "rb");
	// fopen_s(&file, name.c_str(), "rb");
	if (file == nullptr)
	{
		return true;
	}
	else
	{
		fclose(file);
	}


	std::wstring wstr;
	int nLen = (int)name.length();
	wstr.resize(nLen, L' ');
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)name.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);

	free();
	reset();
	if (m_pGraphBuilder == nullptr)
	{
		return false;
	}
	// ¼ÓÔØMP3Êý¾Ý
	if (m_pGraphBuilder->RenderFile(wstr.c_str(), NULL))
	{
		return false;
	}

	play();
	_easyName = easyname;
	return true;
}

void cMp3::free()
{
	if (!m_pMediaControl)
	{
		return;
	}

	m_pMediaControl->Stop();
	m_pMediaControl->Release();
	m_pMediaControl = nullptr;

	if (m_media_event)
	{
		m_media_event->Release();
		m_media_event = nullptr;
	}

	if (m_pMediaPosition)
	{
		m_pMediaPosition->Release();
		m_pMediaPosition = nullptr;
	}

	if (m_pGraphBuilder)
	{
		m_pGraphBuilder->Release();
		m_pGraphBuilder = nullptr;
	}
}

void cMp3::checkEnd()
{
// 	if (m_pGraphBuilder == nullptr && !m_PrePath.empty())
// 	{
// 		load(m_PrePath, false);
// 	}
	if (!m_media_event)
	{
		return;
	}

	long event_code, param1, param2;
	// retrieves the next notification event
	if (SUCCEEDED(m_media_event->GetEvent(&event_code, &param1, &param2, 0)))
	{
		if (event_code == EC_COMPLETE)
//		if (event_code)
		{
			// frees resources associated with the parameters of an events.
			m_media_event->FreeEventParams(event_code, param1, param2);

			m_pMediaPosition->put_CurrentPosition(0);
		}
	}
	return;

	long msg;
	m_media_event->WaitForCompletion(0, &msg);
	if (msg)
	{
		m_pMediaPosition->put_CurrentPosition(0);
	}
}

void cMp3::reset()
{
	if (m_pMediaControl)
	{
		return;
	}
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,IID_IGraphBuilder, (void**)&m_pGraphBuilder);
	if (!m_pGraphBuilder)
	{
		return;
	}
	m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);
	m_pGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_pMediaPosition);
	m_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&m_media_event);
}

void cMp3::stop()
{
	if (m_pMediaControl)
	{
		m_pMediaControl->Stop();
	}
}

void cMp3::play()
{
	if (m_pMediaControl)
	{
		m_pMediaControl->Run();
	}
}

cMp3::~cMp3()
{
	free();
}
