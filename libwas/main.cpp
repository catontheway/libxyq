#include "was.h"
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
	printf(" made in china by 狼宝\n");
	// 打包
//	wasPack();
	// 解包
//	wasUnpack(); 


// 	std::vector<ulong> uids;
// 	std::set<ulong> uid2;
// 	std::ifstream ifile(s_desktop + "乱舞对比.txt");
// 	std::string temp;
// 	while (ifile >> temp)
// 	{
// 		if (temp.empty() || temp.front() == '#' || temp == "0" || temp == "0000")
// 		{
// 			continue;
// 		}
// 		ulong uid = 0;
// 		if (temp.front() == '0' && temp.at(1) == 'x')
// 		{
// 			uid = ccc_s2u(temp);
// 		}
// 		else
// 		{
// 			uid = std::strtoul(temp.c_str(), nullptr, 10);
// 		}
// 		if (uid < 6000)
// 		{
// 			continue;
// 		}
// 		if (uid2.find(uid) != uid2.end())
// 		{
// 			continue;
// 		}
// 		uids.push_back(uid);
// 		uid2.insert(uid);
// 	}

	// 计较两个文件夹的 was集合的 同帧 同向 差集(前者有而后者没有)
	setSameSpNO(getUids(s_desktop + "i.media/", true),s_desktop + "i.media/", s_desktop + "i.lxy/", s_desktop + "i.out/");

	printf("运行完成");
	for (;;);
}



