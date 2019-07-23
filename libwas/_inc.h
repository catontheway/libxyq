#pragma once
#include "../libcc/_cpp.h"
#include "../libcc/_string.h"
#include "../libcc/cWas.h"
#include "../lib32/_window.h"
#include "../lib32/efolder.h"

#define ccc_u2s(_uid_)toString("%08X", (_uid_))
#define ccc_s2u(_str_)std::strtoul(_str_.c_str(), nullptr, 16);
#define ccc_u2was(_uid_)toString("%08X.was", (_uid_))

#define ccc_md(_path_)system(("md " + cc::replace((_path_), "/", "\\")).c_str())
#define ccc_move(_name_, _path_move_)system(("move " + cc::replace(((_name_) + " " + (_path_move_)), "/", "\\")).c_str())
#define ccc_copy(_name_, _name_copy_)system(("copy " + cc::replace(((_name_) + " " + (_name_copy_)), "/", "\\")).c_str())

#undef min
#undef max

static const int s_countInv = 100;
static const int s_writeTabLen = 8;
static const char* s_writeTab = "        ";
static const std::string s_unpack = ".unpack/";
static const std::string s_desktop = "C:/Users/Deen/Desktop/";

struct sPointer
{
	char *ptr = nullptr;
	int size = 0;

	operator bool()const
	{
		return ptr != nullptr && size > 0;
	}
};

inline void sortUids(std::vector<ulong>& us)
{
	std::sort(us.begin(), us.end(), [](const ulong& a, const ulong& b){return a < b; });
}

inline std::vector<ulong>  getIntersection(const std::vector<ulong>& uSorts, const std::vector<ulong>& uSort2s)
{
	std::vector<ulong> intersections(std::min(uSorts.size(), uSort2s.size()));
	const auto& it = set_intersection(uSort2s.begin(), uSort2s.end(), uSorts.begin(), uSorts.end(), intersections.begin());
	intersections.resize(it - intersections.begin());
	return intersections;
}


inline std::vector<ulong>  getDifference(const std::vector<ulong>& uSorts, const std::vector<ulong>& uSort2s)
{
	std::vector<ulong> intersections(std::max(uSorts.size(), uSort2s.size()));
	const auto& it = set_difference(uSort2s.begin(), uSort2s.end(), uSorts.begin(), uSorts.end(), intersections.begin());
	intersections.resize(it - intersections.begin());
	return intersections;
}



inline void writePointer(const char* ptr, int size, const std::string& filename)
{
	FILE* file = fopen(filename.c_str(), "wb");
	fwrite(ptr, 1, size, file);
	fclose(file);
}


inline void writePointer(const sPointer& pter, const std::string& filename)
{
	writePointer(pter.ptr, pter.size, filename);
}

struct sSpCompare
{
	const bool operator()(const sSpInfo& s2, const sSpInfo& s)const
	{
		if (s2.width != s.width)return s2.width < s.width;
		if (s2.height != s.height)return s2.height < s.height;
		if (s2.kx != s.kx)return s2.kx < s.kx;
		if (s2.ky != s.ky)return s2.ky < s.ky;
		if (s2.directionsCount != s.directionsCount)return s2.directionsCount < s.directionsCount;
		if (s2.framesCountPerDirection != s.framesCountPerDirection)return s2.framesCountPerDirection < s.framesCountPerDirection;
		if (s2.framesCount != s.framesCount) return s2.framesCount < s.framesCount;
		for (int k = 0; k < s.framesCount; ++k)
		{
			const auto& f2 = s2.frames[k];
			const auto& f = s.frames[k];
			if (f2.w != f.w)return f2.w < f.w;
			if (f2.h != f.h)return f2.h < f.h;
			if (f2.x != f.x)return f2.x < f.x;
			if (f2.y != f.y)return f2.y < f.y;
		}
		return false;
	}
};
inline bool isSp(const char* ptr){ return (*(ushort*)ptr) == 0x5053; }

inline sPointer mallocPointer()
{
	sPointer pointer;
	pointer.ptr = (char*)malloc(pointer.size = 0xfff);
	return pointer;
}

inline void resizePointer(sPointer& pointer, int size)
{
	if (pointer.size < size)
	{
		pointer.ptr = (char*)realloc(pointer.ptr, pointer.size = size);
	}
}


class cReaders
{
public:
	cReaders() { _ptr = (char*)malloc(_allocSize = 0x04FF); }
	~cReaders() { for (auto& wdf : _wdfs) delete wdf; free(_ptr); }

	struct sWdf : public cWas { std::string easyName, fullName; };

	bool load(const std::string &filename)
	{
		const auto& istr = filename.find_last_of("/");
		std::string path, name;
		if (istr == std::string::npos)
		{
			name = filename;
		}
		else
		{
			path = filename.substr(0, istr + 1);
			name = filename.substr(istr + 1);
		}

		sWdf* wdf = new sWdf();
		if (!wdf->load(path + name))
		{
			delete wdf;
			return false;
		}
		wdf->easyName = name;
		wdf->fullName = path + name;
		_wdfs.push_back(wdf);
		return true;
	}
	bool loads(const std::string &path)
	{
		auto names = cc::efolder(path, false, 0);
		forv(names, k)
		{
			load(names.at(k));
		}
		if (!names.empty())
		{
			_path = path;
		}
		return true;
	}

	sPointer getPointer(ulong uid)
	{
		sPointer pointer;
		forv(_wdfs, k)
		{
			sWdf* wdf = _wdfs.at(k);
			auto ptr = wdf->getData(uid, pointer.size);
			if (ptr == nullptr)
			{
				continue;
			}
			if (_allocSize < pointer.size)
			{
				_ptr = (char*)realloc(_ptr, _allocSize = pointer.size);
			}
			memcpy(_ptr, ptr, pointer.size);
			pointer.ptr = _ptr;
			break;
		}
		return pointer;
	}
	const std::string& getPath() const { return _path; }
	const std::vector<sWdf*>& getWdfs()const { return _wdfs; }
private:
	std::vector<sWdf*> _wdfs;
	std::string _path;
	ulong _allocSize;
	char *_ptr;
};