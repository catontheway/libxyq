#pragma once
#include <string>
#include <dshow.h>

class cMp3
{
public:
	~cMp3();
	static cMp3* getInstance();
	const std::string& getEasyName();
	bool load(const std::string& path, const std::string& easyname, bool checkpre = true);
	void checkEnd();
	void stop();
	void play();
private:
	void free();
	void reset();
	IGraphBuilder* m_pGraphBuilder = nullptr;
	IMediaControl* m_pMediaControl = nullptr;
	IMediaPosition* m_pMediaPosition = nullptr;
	IMediaEvent* m_media_event = 0;
	std::string _easyName;
};