#pragma once
#include "repeat.h"


// 171 40849个
// 单个文件直接用查看器保存打包更快
inline void setSp(const std::string& pathCopyFrom, const std::string& pathUnpack, const std::string& pathRepack)
{
	// 171 40849个
	cReaders reader171;
	reader171.loads(pathCopyFrom);
	const auto& wdfs = reader171.getWdfs();
	std::string strTemp;
	int count = 0;
	char ptr2[2];
	sPointer pter = mallocPointer();
	for (int k = 0; k < wdfs.size(); ++k)
	{
		const auto& wdf = wdfs[k];
		strTemp = pathCopyFrom + wdf->easyName;
		FILE* file = fopen(strTemp.c_str(), "rb");
		strTemp = pathUnpack + wdf->easyName + "/";
		ccc_md(strTemp);
		for (int i = 0; i < wdf->getIndexsCount(); ++i)
		{
			const auto& index = wdf->getIndexs()[i];
			fseek(file, index.offset, SEEK_SET);
			fread(ptr2, 1, 2, file);
			if (!isSp(ptr2))
			{
				continue;
			}
			printf("%d.", ++count);
			resizePointer(pter, index.size);
			fseek(file, index.offset, SEEK_SET);
			fread(pter.ptr, 1, index.size, file);
			writePointer(pter.ptr, index.size, strTemp + ccc_u2was(index.uid));
		}
		fclose(file);
		if (k == 0)
		{
			ccc_md(pathRepack);
		}
		wasPack(strTemp, pathRepack + wdf->easyName, false);
	}
}



std::vector<std::string> getWdfs(bool shape1)
{
	std::vector<std::string> wdfs;
	wdfs.push_back("shape.wda");
	wdfs.push_back("shape.wdb");
	wdfs.push_back("shape.wdc");
	wdfs.push_back("shape.wdf");
	if (shape1)
	{
		// 旧英女侠
		wdfs.push_back("shape1.wdf");
	}
//	wdfs.push_back("shape.wd1");  // 调色板
	wdfs.push_back("shape.wd2");
	wdfs.push_back("shape.wd3");
	wdfs.push_back("shape.wd4");
	wdfs.push_back("shape.wd5");
	wdfs.push_back("shape.wd6");
	wdfs.push_back("shape.wd7");
	wdfs.push_back("shape.wd8");
	wdfs.push_back("shape.wd9");
	wdfs.push_back("shape.wd11");
	wdfs.push_back("wzife.wd1");
	wdfs.push_back("wzife.wd2");
	wdfs.push_back("wzife.wd3");
	wdfs.push_back("wzife.wd4");
	wdfs.push_back("wzife.wdf");
//	wdfs.push_back("smap.wdf");   // 小地图
	wdfs.push_back("item.wdf");
	wdfs.push_back("item.wd1");
	wdfs.push_back("item.wd2");
	wdfs.push_back("addon.wdf");
	wdfs.push_back("magic.wdf");
//	wdfs.push_back("新资源.wdf");  // 非梦5
	wdfs.push_back("magic.wd1");
	wdfs.push_back("magic.wd2");
	wdfs.push_back("waddon.wdf");  // 状态
//	wdfs.push_back("waddon.wd1");  // 非梦5
//	wdfs.push_back("sound.wdf");
//	wdfs.push_back("sound1.wdf");
	wdfs.push_back("mapani.wdf");  // 地图动画
	wdfs.push_back("atom.wdf");
	return wdfs;
}


std::vector<std::string> getWeimei()
{
	std::vector<std::string> wdfs;
	wdfs.push_back("shape.wd0");
	wdfs.push_back("shbabyape.wdf");
	wdfs.push_back("shape.wdf");
	wdfs.push_back("shape.wd2");
	wdfs.push_back("uijd.wdf");
	return wdfs;
}


// 编号来自5, 5必有
// 所幸txt5编号都不与repeat171有交集
// smap171都有,而且有几张迭代小地图
inline void setSameSpNO(const std::vector<ulong>& uids, std::string path5, std::string path171, const std::string& pathout)
{
//	asert(getIntersection(uids, getRepeat(getSpDup171ori())).empty(), "SameSpNO与重复编号有交集");

	cReaders r5, r;
#if 1
	r5.loads(path5);
#else
#endif

#if 1
	r.loads(path171);
#else
#endif

	bool isDF = false;
	bool isD = false;
	bool isNO = false;
	bool isDiff = false;
	bool isNoSp = false;

	// 没有/就返回字符串本身
	// 有/就返回至少两个(左右)
	std::vector<std::string> strs;
	cc::split(path5, "/", strs);
	std::string str1 = strs[strs.size() - 2];
	if (!str1.empty())
	{
		path5 = str1 + "/";
	}

	cc::split(path171, "/", strs);
	str1 = strs[strs.size() - 2];
	if (!str1.empty())
	{
		path171 = str1 + "/";
	}

	const char* strDF = "同帧/";
	const char* strD = "同向/";
	const char* strNO = "同号/";
	const char* strDiff = "差集/";

	auto rep = [](const std::string& s)
	{
		return cc::replace(s, "/", ".");
	};

	sPointer p5, p;
	sSpInfo sp5, sp;
	std::string str, str2;
	sSpCompare compare;
	for (const auto& u : uids)
	{
		printf(".");
		p = r.getPointer(u);
		if (p.ptr == nullptr || p.size == 0)
		{
			str1 = pathout + strDiff;
			if (!isDiff)
			{
				ccc_md(str1);
				isDiff = true;
			}
			p5 = r5.getPointer(u);
			writePointer(p5, str1 + ccc_u2was(u));
			continue;
		}
		sp.load(p.ptr, false);
		p5 = r5.getPointer(u);
		if (!isSp(p5.ptr))
		{
			if (!isNoSp)
			{
				ccc_md(pathout + "notsp/");
				isNoSp = true;
			}
			writePointer(p5, pathout + "notsp/" + ccc_u2was(u));
			continue;
		}
		sp5.load(p5.ptr, false);
		// 为什么不一样?
		// 因为每个pter不是单独内存
		if (sp.directionsCount == sp5.directionsCount)
		{
			if (sp.framesCountPerDirection == sp.framesCountPerDirection)
			{
				// if ((sp.dCount > 1 && (compare(sp, sp5) || compare(sp5, sp))) || (sp.dCount == 1 && string(p.ptr, p.size) != string(p5.ptr, p5.size)))
				if(std::string(p.ptr, p.size) != std::string(p5.ptr, p5.size))
				{
					str1 = pathout + strDF + path5;
					str2 = pathout + strDF + path171;
					if (!isDF)
					{
						ccc_md(str1);
						ccc_md(str2);
						isDF = true;
					}
					writePointer(p5, str1 + ccc_u2was(u));
					writePointer(p, str2 + ccc_u2was(u));
				}
			}
			else
			{
				str1 = pathout + strD + path5;
				str2 = pathout + strD + path171;
				if (!isD)
				{
					ccc_md(str1);
					ccc_md(str2);
					isD = true;
				}
				writePointer(p5, str1 + ccc_u2was(u));
				writePointer(p, str2 + ccc_u2was(u));
			}
		}
		else
		{
			str1 = pathout + strNO + path5;
			str2 = pathout + strNO + path171;
			if (!isNO)
			{
				ccc_md(str1);
				ccc_md(str2);
				isNO = true;
			}
			writePointer(p5, str1 + ccc_u2was(u));
			writePointer(p, str2 + ccc_u2was(u));
		}
	}

	if (isDF)
	{
		str1 = pathout + strDF + path5;
		str2 = pathout + strDF + path171;
		wasPack(str1, pathout + rep(strDF + path5), false);
		wasPack(str2, pathout + rep(strDF + path171), false);
	}
	if (isD)
	{
		str1 = pathout + strD + path5;
		str2 = pathout + strD + path171;
		wasPack(str1, pathout + rep(strD + path5), false);
		wasPack(str2, pathout + rep(strD + path171), false);

	}
	if (isNO)
	{
		str1 = pathout + strNO + path5;
		str2 = pathout + strNO + path171;
		wasPack(str1, pathout + rep(strNO + path5), false);
		wasPack(str2, pathout + rep(strNO + path171), false);
	}
	if (isDiff)
	{
		str1 = pathout + strDiff;
		wasPack(str1, pathout + rep(std::string(strDiff) + "wdf"), false);
	}
}
