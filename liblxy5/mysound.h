#pragma once
#include <string>

class cMySound
{
public:
	void Reset();
	void Load(std::string path);
	void CheckEnd();
	void Free();
	void Stop();
	void Play();
	~cMySound(){ Free(); };
private:
	unsigned long _uid = 0;
};


class cMyWav
{
public:
	~cMyWav(){ Free(); };
	void Load(unsigned char* pdata,int size,int pos=0, bool bPlay=true);
	void Free();
	void SetPosition(int num);
	int GetNowPostion();
	void play();
private:
	char* _ptr = nullptr;
	int _size = 0;
};



































































