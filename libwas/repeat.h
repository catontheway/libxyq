#pragma once
#include "pack.h"
// #include <io.h>

// need wdfs
#define forwdf_file_kibegin(_path_, _wdfs_, _file_, _index_, _k_, _i_)\
forv(_wdfs_, _k_)\
{\
	FILE* _file_ = fopen((_path_ + _wdfs_[_k_]->easyName).c_str(), "rb");\
	for (int _i_ = 0; _i_ < _wdfs_[_k_]->getIndexsCount(); ++_i_)\
	{\
		const auto& _index_ = _wdfs_[_k_]->getIndexs()[_i_];\
		fseek(_file_, _index_.offset, SEEK_SET);

// need wdfs, pter
#define forwdf_file_pter_kibegin(_path_, _wdfs_, _file_, _index_, _pter_, _k_, _i_)\
forwdf_file_kibegin(_path_, _wdfs_, _file_, _index_, _k_, _i_)\
resizePointer(_pter_, _index_.size);\
fread(_pter_.ptr, 1, _index_.size, _file_);


#define forwdf_file_end(_file_)}fclose(_file_);}

// need wdfs
#define forwdf_kibegin(_wdfs_, _index_, _k_, _i_)\
forv(_wdfs_, _k_)\
{\
	for (int _i_ = 0; _i_ < _wdfs_[_k_]->getIndexsCount(); ++_i_)\
	{\
		const auto& _index_ = _wdfs_[_k_]->getIndexs()[_i_];

// need wdfs
#define forwdf_begin(_wdfs_)forwdf_kibegin(_wdfs_, index, k, i)
#define forwdf_end }}





// 取得编号 vector 不论重复
std::vector<ulong> getUids(const std::string& path, bool isJudgeSp)
{
	cReaders r;
	r.loads(path);
	const auto& wdfs = r.getWdfs();
	std::vector<ulong> uids;
	if (isJudgeSp)
	{
		char arr4[4];
		forwdf_file_kibegin(path, wdfs, file, index, k, i);
		fseek(file, index.offset, SEEK_SET);
		fread(arr4, 1, 4, file);
		if (isSp(arr4))
		{
			uids.push_back(index.uid);
		}
		forwdf_file_end(file);
	}
	else
	{
		forwdf_begin(wdfs);
		uids.push_back(index.uid);
		forwdf_end;
	}
	sortUids(uids);
	return uids;
}



// 取得编号 (一个文件肯定不重复)
std::vector<ulong> getUids(const std::string& name)
{
	cReaders r;
	r.load(name);
	const auto& wdfs = r.getWdfs();
	std::vector<ulong> uids;
	forwdf_begin(wdfs);
	uids.push_back(index.uid);
	forwdf_end;
	sortUids(uids);
	return uids;
}



std::map <ulong, std::vector<int>> getDup(const std::vector<cReaders::sWdf*>& wdfs)
{
	std::map<ulong, std::vector<int>> uRepeats;
	forwdf_begin(wdfs);
	const auto& it = uRepeats.find(index.uid);
	if (it == uRepeats.end())
	{
		std::vector < int > is;
		is.push_back(k);
		uRepeats.insert(make_pair(index.uid, is));
	}
	else
	{
		it->second.push_back(k);
	}
	forwdf_end;

	std::map<ulong, std::vector<int>> dups;
	for (const auto& ur : uRepeats)
	{
		if (ur.second.size() > 1)
		{
			dups.insert(ur);
		}
	}
	return dups;
}


// 仅仅是找重复编号
// 171 重复三次  1个 1350671f addon.wdf magic.wdf waddon.wdf
// 171 重复两次 42个
std::map <ulong, std::vector<std::string>> getDup(const std::string& pathCopyFrom)
{
	cReaders r;
	r.loads(pathCopyFrom);
	const auto& wdfs = r.getWdfs();
	auto uRepeats = getDup(wdfs);

	std::map<ulong, std::vector<std::string>> dups;
	std::vector<std::string> strs;
	for (const auto& ur : uRepeats)
	{
		strs.clear();
		for (const auto& k : ur.second)
		{
			strs.push_back(wdfs[k]->easyName);
		}
		dups.insert(make_pair(ur.first, strs));
	}
	return dups;
}


void setDup(const std::string& pathUnpack, int eFolderDeep)
{
	auto names = cc::efolder(pathUnpack, false, eFolderDeep);
	std::map<ulong, std::string> uidclss;
	std::string str;
	ulong uid;
	int count = 0;
	char ptr4[4];
	for (const auto& name : names)
	{
		printf("%d.", ++count);
		str = name.substr(name.find_last_of("/") + 1);
		uid = ccc_s2u(str);
		str = name.substr(pathUnpack.length());
		const auto& it = uidclss.find(uid);
		if (it != uidclss.end())
		{
			printf("\n%s  %s\n", str.c_str(), it->second.c_str());
			getchar();
		}
		uidclss.insert(make_pair(uid, str));
		FILE* file = fopen(name.c_str(), "rb");
		fread(ptr4, 1, 4, file);
		if (!isSp(ptr4))
		{
			fclose(file);
			printf("\n%s 不是精灵\n", str.c_str());
			getchar();
		}
		fclose(file);
//		ccc_copy(name, s_desktop + "sp.171/" + ccc_u2was(uid));
	}
}



std::vector<ulong> getRepeat(const std::map <ulong, std::vector<std::string>>& dups)
{
	std::vector<ulong> uids;
	for (const auto& u : dups)
	{
		uids.push_back(u.first);
	}
	return uids;
}



// 未包括smap
// 5.but.other 0个
// other.5 16个,不过都==得上
inline std::map <ulong, std::vector<std::string>> getSpDup171ori()
{
	return std::map <ulong, std::vector<std::string>>();
#if 0
	return {
			{ 0x0DE2BF9C, { "goods.wdf", "waddon.wdf" } },
			{ 0x1350671F, { "addon.wdf", "magic.wdf", "waddon.wdf" } },
			{ 0x171544B2, { "addon.wdf", "magic.wdf" } },
			{ 0x1B291F17, { "addon.wdf", "magic.wdf" } },
			{ 0x20FCCE94, { "goods.wdf", "waddon.wdf" } },
			{ 0x21FAE73F, { "addon.wdf", "magic.wdf" } },
			{ 0x23EBA54C, { "addon.wdf", "magic.wdf" } },
			{ 0x2691C760, { "addon.wdf", "magic.wdf" } },
			{ 0x31FB9EF9, { "waddon.wdf", "_magic.wdf" } },
			{ 0x32D3023F, { "magic.wdf", "waddon.wdf" } },
			{ 0x369C6A29, { "goods.wdf", "waddon.wdf" } },
			{ 0x3BA4B993, { "addon.wdf", "magic.wdf" } },
			{ 0x3C45D282, { "addon.wdf", "magic.wdf" } },
			{ 0x3E912705, { "addon.wdf", "magic.wdf" } },
			{ 0x42F0386F, { "addon.wdf", "magic.wdf" } },
			{ 0x434750DE, { "magic.wd1", "_wzife.wd1" } },
			{ 0x47F867FF, { "magic.wdf", "waddon.wdf" } },
			{ 0x4F8312F6, { "addon.wdf", "magic.wdf" } },
			{ 0x55EBCA6C, { "addon.wdf", "magic.wdf" } },
			{ 0x5829CF13, { "addon.wdf", "_magic.wdf" } },
			{ 0x66CC7A29, { "goods.wdf", "waddon.wdf" } },
			{ 0x688EA54B, { "addon.wdf", "magic.wdf" } },
			{ 0x6A0ED9F9, { "magic.wdf", "_wzife.wd1" } },
			{ 0x6B59951D, { "addon.wdf", "magic.wdf" } },
			{ 0x6EA4246E, { "addon.wdf", "magic.wdf" } },
			{ 0x719D767F, { "goods.wdf", "waddon.wdf" } },
			{ 0x72574DC2, { "magic.wdf", "waddon.wdf" } },
			{ 0x729ADE62, { "addon.wdf", "magic.wdf" } },
			{ 0x77D2082D, { "addon.wdf", "magic.wdf" } },
			{ 0x7838CE56, { "magic.wdf", "waddon.wdf" } },
			{ 0x7AEF08A1, { "magic.wdf", "waddon.wdf" } },
			{ 0x808CEB72, { "addon.wdf", "magic.wdf" } },
			{ 0x82C9074A, { "addon.wdf", "magic.wdf" } },
			{ 0x885ACBE1, { "addon.wdf", "magic.wdf" } },
			{ 0x89302F40, { "addon.wdf", "magic.wdf" } },
			{ 0x8AA8F567, { "addon.wdf", "magic.wdf" } },
			{ 0x8D8A818D, { "addon.wdf", "magic.wdf" } },
			{ 0x9215D669, { "addon.wdf", "magic.wdf" } },
			{ 0x973BCF2C, { "magic.wdf", "waddon.wdf" } },
			{ 0x99DDC32A, { "addon.wdf", "magic.wdf" } },
			{ 0xA463C055, { "addon.wdf", "magic.wdf" } },
			{ 0xAC3D253B, { "addon.wdf", "magic.wdf" } },
			{ 0xAFFB5781, { "goods.wdf", "waddon.wdf" } },
			{ 0xB0B36693, { "addon.wdf", "magic.wdf" } },
			{ 0xB1822745, { "addon.wdf", "magic.wdf" } },
			{ 0xB6141EB9, { "addon.wdf", "magic.wdf" } },
			{ 0xBBE9480B, { "magic.wdf", "_wzife.wd1" } },
			{ 0xBE127823, { "addon.wdf", "magic.wdf" } },
			{ 0xC8A44737, { "goods.wdf", "waddon.wdf" } },
			{ 0xD06119B3, { "addon.wdf", "magic.wdf" } },
			{ 0xD45D5973, { "goods.wdf", "waddon.wdf" } },
			{ 0xD862FBE7, { "addon.wdf", "magic.wdf" } },
			{ 0xDF5559A5, { "magic.wdf", "waddon.wdf" } },
			{ 0xE02F2E6D, { "magic.wdf", "waddon.wdf" } },
			{ 0xE7F90843, { "addon.wdf", "magic.wdf" } },
			{ 0xEBB2BD9A, { "magic.wdf", "_wzife.wd1" } },
			{ 0xECD0E003, { "addon.wdf", "magic.wdf" } },
			{ 0xEFE73EB9, { "goods.wdf", "waddon.wdf" } },
			{ 0xF8EE853A, { "goods.wdf", "waddon.wdf" } },
			{ 0xFE962B69, { "addon.wdf", "magic.wdf" } }
	};
#endif
}


inline std::map<ulong, ulong> getColorTable()
{
	return std::map<ulong, ulong>();
#if 0
	return
	{
		{ 0x00001003, 0xBE4F5219 },
		{ 0x00001006, 0x26C2375D },
		{ 0x00001007, 0xA28871AD },
		{ 0x00001008, 0x57958970 },
		{ 0x00001009, 0x0AEF634B },
		{ 0x00001010, 0x1CCF29E1 },
		{ 0x00001012, 0x5188D3B1 },
		{ 0x00001015, 0x04919945 },
		{ 0x00001016, 0x557EBB0E },
		{ 0x00001018, 0xF1715BBE },
		{ 0x00001019, 0x27DE564B },
		{ 0x00001020, 0xE65A0536 },
		{ 0x00001021, 0xD8F30F4F },
		{ 0x00001022, 0x71713126 },
		{ 0x00001023, 0x93BC42AE },
		{ 0x00001024, 0x6764A282 },
		{ 0x00001025, 0x1AE6CFEC },
		{ 0x00001026, 0x82BEA88C },
		{ 0x00001027, 0xE5188970 },
		{ 0x00001028, 0xC96F6BA8 },
		{ 0x00001031, 0x9042F2BD },
		{ 0x00001032, 0x0AEF634B },
		{ 0x00001033, 0x46083877 },
		{ 0x00001035, 0x15934BF7 },
		{ 0x00001036, 0x3CBCA9E9 },
		{ 0x00001037, 0x0297434F },
		{ 0x00001038, 0x1F769E85 },
		{ 0x00001039, 0xFDA93552 },
		{ 0x00001041, 0x5D0164EE },
		{ 0x00001042, 0x3FD4AE5E },
		{ 0x00001043, 0x366AE543 },
		{ 0x00001045, 0x9042F2BD },
		{ 0x00001048, 0x73386347 },
		{ 0x00001049, 0x85CFD988 },
		{ 0x00001050, 0xB922A4F8 },
		{ 0x00001051, 0xE94D96A9 },
		{ 0x00001053, 0xF3DB1F51 },
		{ 0x00001054, 0xEBD934C0 },
		{ 0x00001055, 0xD2A8C9CC },
		{ 0x00001058, 0xC4DAEDE4 },
		{ 0x00001059, 0x69614BED },
		{ 0x00001060, 0x89CB2B8C },
		{ 0x00001061, 0x1B790B81 },
		{ 0x00001062, 0xB9057571 },
		{ 0x00001077, 0x63999FC7 },
		{ 0x00001095, 0x48D67CDC },
		{ 0x00001108, 0xA28B2143 },
		{ 0x00001109, 0xAA09BF40 },
		{ 0x00001110, 0x6BB09644 },
		{ 0x00001111, 0x4CCB52B0 },
		{ 0x00001112, 0xB7C042FD },
		{ 0x00001113, 0xE1954C9F },
		{ 0x00001118, 0x5EEB9C73 },
		{ 0x00002000, 0xDFADD6D6 },
		{ 0x00002005, 0xE88CE841 },
		{ 0x00002100, 0x63999FC7 },
		{ 0x00002101, 0x6FFB9A9B },
		{ 0x00002102, 0x365DD585 },
		{ 0x00002103, 0x040C3FAE },
		{ 0x00002104, 0x2BC951EA },
		{ 0x00002105, 0x6B289253 },
		{ 0x00002106, 0x03FF92C0 },
		{ 0x00002107, 0x65D2A1A4 },
		{ 0x00002200, 0x834E83B8 },
		{ 0x00002201, 0x09B3E018 },
		{ 0x00002202, 0x283DFE4A },
		{ 0x00002206, 0x962EF053 },
		{ 0x00002207, 0x1E638EA4 },
		{ 0x00002208, 0xFE076F18 },
		{ 0x00002210, 0xF3EDF088 },
		{ 0x00002218, 0x53377FEF },
		{ 0x00002219, 0x584C55F8 },
		{ 0x00002220, 0x6218BD0D }
	};
#endif
}