#pragma once
#include "../libfolderEx/cFolder.h"
#include <functional>

class cGame
{
public:
	static const std::string cFilename;
	static cGame* getInstance();

	void setwh(int w, int h) { _w = w, _h = h; }
	int getw() { return _w; }
	int geth() { return _h; }
	int isChatShown() { return _isChatShown; }
	void switchChatShown() { _isChatShown = !_isChatShown; }

	eIterType getIter() { return _eiter; }
	void setIter(eIterType iter) { _eiter = iter; }
	eMapType getMap() { return _emap; }
	void setMap(eMapType type) { _emap = type; }
	euiType getui() { return _eui; }
	void setui(euiType ui) { _eui = ui; }

	bool isMp3() { return _isMp3; }
	void setMp3(bool mp3) { _isMp3 = mp3; }
	bool isWav() { return _isWav; }
	void setWav(bool wav) { _isWav = wav; }
	int getVolume() { return _volume; }
	void setVolume(int volume) { _volume = volume; }

	bool save(const std::string& filename);
	bool load(const std::string& filename);

	bool isIter() { return _eiter == eIterType::iter; }
	bool isPhone() { return _isPhone; }
	void setPhone(bool phone) { _isPhone = phone; }
	bool isIterMagic() { return _isIterMagic; }
	void setItetMagic(bool iter) { _isIterMagic = iter; }
private:
	int _w = 800, _h = 600;
	bool _isChatShown = true;
	eIterType _eiter = eIterType::iter;
	eMapType _emap = eMapType::iter;
	euiType _eui = euiType::sj;
	int _volume = 100;
	bool _isMp3 = true;
	bool _isWav = true;
	bool _isPhone = false;
	bool _isIterMagic = false;
};