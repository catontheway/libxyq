#include "global.h"


void cMySound::Load(std::string path)
{
	if (path == "无")
	{
		_uid = 0;
		Free();
		return;
	}

	static std::map<std::string, std::string> s_transMap = 
	{
		{"比武背景", "帮战入场"},
		{"比武2", "比武场"},
		{"凤巢3", "未知"},
		{"战斗_比武_DT", ""},
	};
	if (s_transMap.find(path) != s_transMap.end())
	{
		path = s_transMap.at(path);
	}

	if (path == "战斗4" || path == "战斗5")
	{
		path = toString("战斗%d", (rand() % 3) + 1);
	}
	if (path == "战斗比武" || path == "战斗_任务" || path == "战斗_任务2")
	{
		path = toString("战斗比武%d", (rand() % 4) + 1);
	}

	// 战斗比武没有5
	// 无名鬼蜮还是无名鬼城?
	static std::map<std::string, unsigned long> s_map = {
	{"海底迷宫", 0x00167186},
	{"海底迷宫2", 0x00167186},
	{"麒麟山", 0x012D9DD7},
	{"神木林", 0x016F4476},
	{"小西天", 0x03D65C21}, //小雷音寺
	{"大雁塔2", 0x05122F2E},
	{"凌波城", 0x0B16F601},
	{"蟠桃园", 0x10D7ABF1},
	{"蓬莱仙岛", 0x10DF6DF7},
	{"长寿郊外", 0x18348D2B},
	{"小雷音寺", 0x2011A8C2},
	{"北俱芦洲", 0x2142584C},
	{"普陀山", 0x21BEB585},
	{"长安城", 0x26275208},
	{"江南野外", 0x266E2C58},
	{"大雁塔1", 0x2C3D8AF0},
	{"长寿村", 0x2F1EC70A},
	{"宝象国", 0x3127BBB8},
	{"傲来国", 0x35159569},
	{"狮驼岭", 0x3800966C},
	{"战斗比武1", 0x389F5EF4},
	{"凌云渡", 0x3F24C153},
	{"须弥东界", 0x41645B50},
	{"魔王寨", 0x4A64F8BD},
	{"大唐官府", 0x4AE2B5B3},
	{"东海湾", 0x4B4740AC},
	{"丝绸之路", 0x52A0B4EE},
	{"方寸山", 0x53C2DE57},
	{"地狱迷宫2", 0x5A864351},
	{"月宫", 0x5B0DCCD9},
	{"柳林坡", 0x5B9DC400},
	{"龙窟2", 0x65B90ACA},
	{"建邺城", 0x68F6DDA1},
	{"阴曹地府", 0x700EE303},
	{"桃源村", 0x76C2A481},
	{"", 0x78FC0CBA}, // 像大唐
	{"龙宫", 0x79D250E2},
	{"帮战入场", 0x7B908BCA},
	{"墨家村", 0x7C4D04B2},
	{"战斗BOSS", 0x845DC12C},
	{"西梁女国", 0x8482AF70},
	{"帮派", 0x84E2EB78},
	{"监狱", 0x86C4F045}, // 牢房  地牢 
	{"碗子山", 0x88CD5404},
	{"战斗1", 0x8905924A},
	{"花果山", 0x8C4500FC},
	{"女儿村", 0x8CAB9764},
	{"东海海底", 0x8EF4D872},
	{"未知", 0x9245F880}, // 宏伟 佛系
	{"化生寺", 0x92DD1A7A},
	{"无底洞", 0x95C16AD7},
	{"墨家禁地", 0x9E05AC95},
	{"战斗比武2", 0x9EC29A9D}, // 战斗5-草原
	{"朱紫国", 0xA602567C},
	{"未知鬼域", 0xA6F426EB},
	{"家", 0xA7330084},
	{"比丘国", 0xA8A9DBB9},
	{"战神山", 0xAA002386},
	{"盘丝岭", 0xAC396538},
	{"龙窟", 0xAE8B3481},
	{"子母河底", 0xAE8C1555},
	{"凤巢", 0xB0D9F40A},
	{"战斗3", 0xB248A7C7}, // 战斗7-山地
	{"凤巢2", 0xB33EB187},
	{"比武场", 0xBED44FE1},
	{"战斗2", 0xC1064081}, // 战斗6-城市
	{"波月洞", 0xCD525622},
	{"地狱迷宫", 0xD3B5D40A},
	{"大唐境外", 0xD66E10A8},
	{"解阳山", 0xDABAC06C},
	{"女娲神迹", 0xE4096D42},
	{"天宫", 0xE7CE763C},
	{"大唐国境", 0xEA26251A},
	{"地狱迷宫5", 0xEBCC1270}, // 无名鬼蜮
	{"无名鬼域", 0xEBCC1270},
	{"战斗比武3", 0xF303B6A9},
	{"战斗比武4", 0xFB165E34},
	{"五庄观", 0xFD1ECF8F},
	}; 

	if (s_map.find(path) == s_map.end())
	{
		std::ifstream ifile(g_strMediaPath + "music/" + path + ".mp3", std::ios::binary);
		if (ifile.is_open())
		{
			if (g_pMainState->m_GlobalButton[16] == 0)
			{
				// 播放mp3文件
				char* ptr = nullptr;
				int size;
				ifile.seekg(0, std::ios::end);
				size = ifile.tellg();
				ptr = new char[size];
				ifile.seekg(std::ios::beg);
				ifile.read(ptr, size);
				ifile.close();
				if (ptr != nullptr)
				{
					static ulong uid = 0;
					cBass::getInstance()->play(_uid = ++uid, ptr, size);
				}
			}
			return;
		}
		path = "战斗BOSS";
	}

	const auto& it = s_map.find(path);
	if (it == s_map.end() || _uid == it->second)
	{
		return;
	}
	_uid = it->second;
	Play();
}

void cMySound::Free()
{
}

void cMySound::CheckEnd()
{

}

void cMySound::Reset()
{

}

void cMySound::Stop()
{
	cBass::getInstance()->setMp3(0);
}


void cMySound::Play()
{
	if (g_pMainState->m_GlobalButton[16] == 0)
	{
		cBass::getInstance()->setMp3(100);
		int size;
		auto ptr = cWdf::getMp3()->getData(_uid, size);
		if (ptr != nullptr)
		{
			cBass::getInstance()->play(_uid, ptr, size);
		}
		
	}

}

void cMyWav::Load(unsigned char* pdata,int size,int pos/* =0 */, bool bPlay/* =true */)
{

}

void cMyWav::Free()
{
}

void cMyWav::SetPosition(int num)
{
}

int cMyWav::GetNowPostion()
{
	return 0;
}



