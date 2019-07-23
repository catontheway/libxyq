#pragma once
#include <string>
#include <sstream>
#include <stdarg.h>
#include <vector>


namespace cc
{
	// 转 字符串
	template <typename T>
	inline std::string toString(T arg)
	{
		std::stringstream string_stream;
		string_stream << arg;
		return string_stream.str();
	}
}


// 字符串 格式化
inline std::string toString(const char* format, ...)
{
	const int c1024 = 1024;
	char* arr = (char*)malloc(c1024);
	memset(arr, 0, c1024);
	va_list ap;
	va_start(ap, format);
#if 1
	vsnprintf_s(arr, c1024, c1024, format, ap);
#else
	int count = _vsnprintf(arr, (c1024) - 1, format, ap);
	if (count >= 0) 
	{
		arr[count] = 0;
	}
	else 
	{
		arr[c1024 - 1] = 0;
	}
#endif
	va_end(ap);
	std::string str(arr);
	free(arr);
	return str;
}


namespace cc
{
	// 字符串 分割
	inline void split(const std::string &str, const std::string &delim, std::vector<std::string>& ret)
	{
		ret.clear();
		size_t last = 0;
		size_t index = str.find_first_of(delim, last);

		if (index == std::string::npos)
		{
			ret.push_back(str);
			return;
		}

		while (index != std::string::npos)
		{
			ret.push_back(str.substr(last, index - last));
			last = index + 1;
			index = str.find_first_of(delim, last);
		}

		if (index - last > 0)
		{
			ret.push_back(str.substr(last, index - last));
		}
	}


	// 字符串 替换
	inline std::string replace(std::string str, const std::string &to_replace, const std::string &replace)
	{
		std::string::size_type pos = 0;
		std::string::size_type srcLen = to_replace.size();
		std::string::size_type desLen = replace.size();
		pos = str.find(to_replace, pos);
		while ((pos != std::string::npos))
		{
			str.replace(pos, srcLen, replace);
			pos = str.find(to_replace, (pos + desLen));
		}
		return str;
	}
}
