#include "efolder.h"
#include <functional>

#ifdef _WIN32
#include "io.h"
#define ccc_efolder32
#include "_window.h"
#endif

#ifdef ccc_efolder32

static bool ccc_enumFiles(std::string fullDir,
	std::string partDir,
	const std::function<bool(const std::string&)> &cb,
	std::stringstream& ss,
	bool &isNeedCallback,
	bool &isOnlyName)
{
	WIN32_FIND_DATAA data;
	std::string path = fullDir + "*";
	//这样处理后可以partDir + cFileName
	if (partDir.size() == 1 && partDir.back() == '/')
		partDir.clear();
	else if (partDir.size() > 1 && partDir.back() != '/')
		partDir += '/';

	HANDLE handle = FindFirstFileA(path.c_str(), &data);
	asert(handle != INVALID_HANDLE_VALUE, "efolder fail: %s", path.c_str());

	do
	{
		//本目录或者上级目录
		if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && data.cFileName[0] == '.')
			continue;

		//目录
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string new_fullDir = fullDir + data.cFileName + "/";
			std::string new_partDir = partDir + data.cFileName + "/";
			if (ccc_enumFiles(new_fullDir, new_partDir, cb, ss, isNeedCallback, isOnlyName))
			{
				FindClose(handle);
				return true;
			}
			continue;
		}

		if (ss.tellp())
			ss << "\n";
		ss << partDir + data.cFileName;

		//文件
		if (isNeedCallback)
		{
			if (isOnlyName)
			{
				if (cb(data.cFileName))
				{
					isNeedCallback = false;
				}
			}
			else
			{
				if (cb(partDir + data.cFileName))
				{
					isNeedCallback = false;
				}
			}
		}
	} while (FindNextFileA(handle, &data));

	FindClose(handle);

	return false;
}
#else
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

static std::vector<std::string> getFilePathAtVec(const std::string& folderPath, const bool& isOnlyName, int depth)
{
	std::vector<std::string> path_vec;
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if ((dp = opendir(folderPath.c_str())) == NULL)
	{
		asert(false,"efolder fail: %s", folderPath.c_str());
//		fprintf(stderr, "cannot open directory: %s\n", folderPath.c_str());
		return path_vec;
	}
	chdir(folderPath.c_str());
	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{

			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
			{
				continue;
			}
//			printf("%*s%s/\n", depth, "", entry->d_name);
			getFilePathAtVec(entry->d_name, isOnlyName, depth + 4);
		}
		else
		{
//			string filename = entry->d_name;
//			path_vec.push_back(filename);
			if (isOnlyName)
			{
				path_vec.push_back(entry->d_name);
			}
			else
			{
				path_vec.push_back(folderPath + entry->d_name);
			}
		}
	}
	chdir("..");
	closedir(dp);
	return path_vec;
}
#endif



static void dfsFolder(std::vector<std::string>& names, const bool& isOnlyName, const std::string& folderPath, const int&folderPathStrLen, int& depth, const int& depthLimit)
{
#ifdef ccc_efolder32
	_finddata_t FileInfo;
	std::string strTemp = folderPath + "*";// "\\*";
	long Handle = _findfirst(strTemp.c_str(), &FileInfo);

	if (Handle == -1L)
	{
// 		cerr << "can not match the folder path" << endl;
// 		exit(-1);
		return;
	}
	do{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)
		{
			if (depthLimit >= 0 && depth >= depthLimit)
			{
				continue;
			}
			//这个语句很重要
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
			{

				strTemp =  folderPath + FileInfo.name + "/";
				++depth;
				dfsFolder(names, isOnlyName, strTemp, folderPathStrLen, depth, depthLimit);
				--depth;
			}
		}
		else
		{
// 			string filename = (folderPath + "\\" + FileInfo.name);
// 			cout << folderPath << "\\" << FileInfo.name << " " << endl;
			if (isOnlyName)
			{
				names.push_back(FileInfo.name);
			}
			else
			{
				names.push_back(folderPath + FileInfo.name);
			}
		}
	}
	while (_findnext(Handle, &FileInfo) == 0);
	_findclose(Handle);
#else
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if ((dp = opendir(folderPath.c_str())) == NULL)
	{
//		fprintf(stderr, "cannot open directory: %s\n", folderPath.c_str());
		return;
	}
	chdir(folderPath.c_str());
	std::string strTemp = folderPath;
	while ((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) 
		{
			if(depthLimit >= 0 && depth >= depthLimit)
			{
				continue;
			}
			if(entry->d_name[0] == '.')
			{
				continue;
			}
			if (strcmp(".", entry->d_name) == 0 ||  strcmp("..", entry->d_name) == 0)
			{
				continue;
			}
//			printf("%*s%s/\n", depth, "", entry->d_name);	
			std::string strTemp = folderPath + entry->d_name;
			strTemp += "/";
			++depth;
			dfsFolder(names, isOnlyName, strTemp, folderPathStrLen, depth, depthLimit);
			--depth;
		}
		else 
		{
			if(entry->d_name[0] == '.')
			{
				continue;
			}
//			string filename = entry->d_name;
//			printf("%*s%s\n", depth, "", entry->d_name);
			if (isOnlyName)
			{
				names.push_back(entry->d_name);
			}
			else
			{
				names.push_back(folderPath.substr(folderPathStrLen) + entry->d_name);
			}
		}
	}
	chdir("..");
	closedir(dp);
#endif
}

std::vector<std::string> cc::efolder(const std::string& path, bool isOnlyName, int depthLimit)
{

	std::vector<std::string> fileNames;
	std::string fullDir = path;
	fullDir = cc::replace(fullDir, "\\", "/");
//	asert(fullDir.size(), "efolder fail: %s", path.c_str());
	//这样处理后可以partDir + cFileName
	if (fullDir.size() && fullDir.back() != '/')
	{
		fullDir += '/';
	}

	int depth = 0;
	dfsFolder(fileNames, isOnlyName, fullDir, fullDir.size(), depth, depthLimit);
	return fileNames;
#ifdef ccc_efolder32
	std::string partDir = "";
	std::stringstream ss;
	auto func = [&fileNames](const std::string &filename)
	{
		fileNames.push_back(filename);
		return false;
	};
	ccc_enumFiles(fullDir, partDir, func, ss, isOnlyName, isOnlyName);
	return fileNames;
#else
	return getFilePathAtVec(path, isOnlyName, 0);
	std::vector<std::string> path_vec;
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
//	int i = 0;

	if (!(dp = opendir(path.c_str())))
	{
		fprintf(stderr, "efolder fail: %s", path.c_str());
//		exit(1);
		return path_vec;
	}
	chdir(path.c_str());

	while ((entry = readdir(dp)) != NULL/* && i < 0xff*/)
	{
		stat(entry->d_name, &statbuf);
		if (!S_ISREG(statbuf.st_mode))
		{
			continue;
		}
		if(isOnlyName)
		{
			path_vec.push_back(entry->d_name);
		}
		else
		{
			path_vec.push_back(path + entry->d_name);
		}
	}
	return path_vec;
#endif
}
