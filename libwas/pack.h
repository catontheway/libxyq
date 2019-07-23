#pragma once
#include "_inc.h"

void wasUnpack(const std::string& path, bool isNeedPrintf = false)
{
	cReaders *reader = new cReaders();
	reader->loads(path);
	auto wdfs = reader->getWdfs();

	std::string str;
	forr(wdfs, i)
	{
		str = path + wdfs[i]->easyName + s_unpack;
		ccc_md(str);
		if (isNeedPrintf)
		{
			str = "\n 找到文件: " + path + wdfs[i]->easyName;
			printf(str.c_str());
		}
	}
	int count = 0;
	auto pter = mallocPointer();
	forv(wdfs, k)
	{
		const auto& wdf = wdfs[k];
		if (isNeedPrintf)
		{
			str = "\n " + wdf->easyName + " --> " + wdf->easyName + s_unpack;
			printf(str.c_str());
		}
		FILE* fp = fopen((path + wdf->easyName).c_str(), "rb");
		for (int _i_ = 0; _i_ < wdf->getIndexsCount(); ++_i_)
		{
			const auto& index = wdf->getIndexs()[_i_];
			if (isNeedPrintf)
			{
				if ((count % s_countInv) == 0)
				{
					printf(".");
				}
				++count;
			}
			resizePointer(pter, index.size);
			fseek(fp, index.offset, SEEK_SET);
			fread(pter.ptr, 1, index.size, fp);
			writePointer(pter.ptr, index.size, path + wdf->easyName + s_unpack + ccc_u2was(index.uid));
		}
	}
	if (isNeedPrintf)
	{
		printf("\n 解包完毕\n");
	}
	delete reader;
}


inline void wasUnpack()
{
	printf(" 请把此App和(需要解包的文件们)放在一起\n 然后按任意键开始:");
	getchar();
	wasUnpack("", true);
	for (;;);
}


std::map<ulong, std::string> wasPack(const std::string& path)
{
	auto names = cc::efolder(path, true, 0);
	std::map<ulong, std::string> uMap;
	std::vector<ulong> uids;
	ulong uid;
	std::string str;
	for (const auto& name : names)
	{
		uid = ccc_s2u(name);
		uids.push_back(uid);
		if (uid > 0)
		{
			uMap.insert(make_pair(uid, name));
		}
		else
		{
			uMap.clear();
			return uMap;
		}
	}
	if (uids.size() != uMap.size())
	{
		uMap.clear();
	}
	return uMap;
}


// 先判断文件夹是否合格
void wasPack(std::map<ulong, std::string>& uMap, const std::string& path, const std::string& packname_include_path, bool isNeedPrintf, bool isNeedMd)
{
	std::vector<ulong> uids;
	for (const auto& u : uMap)
	{
		uids.push_back(u.first);
	}
	// 记得小到大排序
 	std::sort(uids.begin(), uids.end(), [](const ulong& a, const ulong& b){return a < b; });

	if (isNeedMd)
	{
		const auto& istr = packname_include_path.find_last_of('/');
		if (istr != std::string::npos)
		{
			std::string str = packname_include_path.substr(0, istr + 1);
			ccc_md(str);
		}
	}


	FILE* file;
	FILE* filePacker = fopen(packname_include_path.c_str(), "wb");
	ulong flag = 0x57444650;
//	flag = 'WDFP';
	fwrite(&flag, 1, 4, filePacker);

	int count = uids.size();
	fwrite(&count, 1, 4, filePacker);
	uint offset = 4 * 3;
// 	fwrite(&offset, 4, 1, filePacker);
// 	offset += count * 16;
	fseek(filePacker, 4, SEEK_CUR);
	cReaders::sWdf::sIndex* indexs = new cReaders::sWdf::sIndex[count];
	int mallocSize = 0xfff;
	char* ptr = (char*)malloc(mallocSize);

	std::string str;
	if (isNeedPrintf)
	{
		std::vector<std::string> strs;
		cc::split(packname_include_path, "/", strs);
		str = "\n " + path + " --> " + strs.back();
		printf(str.c_str());
	}
	for (int i = 0; i < count; ++i)
	{
		if (isNeedPrintf && (i % s_countInv) == 0)
		{
			printf(".");
		}
		file = fopen((path + uMap[uids[i]]).c_str(), "rb");
		fseek(file, 0, SEEK_END);
		indexs[i].uid = uids[i];
		indexs[i].size = ftell(file);
		if (mallocSize < indexs[i].size)
		{
			ptr = (char*)realloc(ptr, mallocSize = indexs[i].size);
		}
		fseek(file, 0, SEEK_SET);
		fread(ptr, 1, indexs[i].size, file);
		fclose(file);

		indexs[i].offset = offset;
//		indexs[i].space = 0;
		offset += indexs[i].size/* + indexs[i].space*/;

		fwrite(ptr, 1, indexs[i].size, filePacker);
//		fseek(filePacker, indexs[i].space, SEEK_CUR);
	}
	for (int i = 0; i < count; ++i)
	{
		fwrite(&indexs[i], 1, 16, filePacker);
	}
	fseek(filePacker, 8, SEEK_SET);
	fwrite(&offset, 1, 4, filePacker);

	delete[] indexs;
	fclose(filePacker);
	free(ptr);
	if (isNeedPrintf)
	{
		str = "\n " + packname_include_path + "打包完成";
		printf("ok");
	}
}


// 自动创建目录
inline void wasPack(const std::string& path, const std::string& packname_include_path, bool isNeedMd)
{
	auto names = cc::efolder(path, true, 0);
	std::map<ulong, std::string> uMap;
	ulong uid;
	for (const auto& name : names)
	{
		uid = std::strtoul(name.c_str(), nullptr, 16);
		uMap.insert(make_pair(uid, name));
	}
	wasPack(uMap, path, packname_include_path, false, isNeedMd);
}



void wasPack()
{
	printf(" 请把此App和 <(里面放了需要打包的文件)的文件夹们> 放在一起\n 记得删掉隐藏文件desktop.ini之类的\n 然后按任意键开始:");
	getchar();
	auto names = cc::efolder("", false, 1);
	std::set<std::string> pathSet;
	std::map<ulong, std::string> uMap;
	std::map<std::string, std::map<ulong, std::string>> paths;
	std::string str;
	for (const auto& name : names)
	{
		const auto istr = name.find_last_of('/');
		if (istr == std::string::npos)
		{
			continue;
		}
		str = name.substr(0, istr + 1);
		
		if (pathSet.find(str) != pathSet.end())
		{
			continue;
		}
		pathSet.insert(str);

		printf("\n 分析 %s", str.c_str());

		uMap = wasPack(str);
		if (uMap.size() > 0)
		{
			paths.insert(make_pair(str, uMap));
		}
		else
		{
			printf(": 有0/重复/无效/空/的编号,请检查后再打包");
		}
	}

	if (paths.size() > 0)
	{
		system("md _打包完毕_\\");
	}
	for (auto& path : paths)
	{
		str = path.first;
		const auto& istr = str.find(s_unpack);
		if (istr != std::string::npos)
		{
			str.erase(istr + 1, s_unpack.length());		
		}
		else if (str.back() == '/')
		{
			str.pop_back();
		}

		wasPack(path.second, path.first, "_打包完毕_/" + str, true, false);
	}

	printf("\n打包完毕");
	for (;;);
}

