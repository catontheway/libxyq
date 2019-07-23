#pragma once
#include "../libcc/_cpp.h"
#include "../libcc/_string.h"

#if 0
template<typename T_FIRST, typename T_SECOND>
class txtTemplate
{
public:
	template<typename T_FIRST, typename T_SECOND>
	static void insert(std::map<T_FIRST, T_SECOND>& table, const T_FIRST& first, const T_SECOND& second)
	{
		table.insert(std::make_pair(first, second));
	}
	const std::map<T_FIRST, T_SECOND>& getTable()const{ return _table; }
	void insert(const T_FIRST& first, const T_SECOND& second){ ctt::insert(_table, first, second); }
protected:
	std::map<T_FIRST, T_SECOND> _table;
};
#endif

#undef small

#define ccc_txt_instance_h(_CLASS_)static _CLASS_* getInstance()
#define ccc_txt_instance_cpp(_CLASS_)\
_CLASS_* _CLASS_::getInstance()\
{\
	static _CLASS_* s_##_CLASS_##Instance = new _CLASS_();\
	return s_##_CLASS_##Instance;\
}

#define ccc_txt_class_begin(T_CLASS)\
class T_CLASS\
{\
public:\
	ccc_txt_instance_h(T_CLASS)
	

#define ccc_txt_class_end(T_FIRST, T_SECOND)\
public:\
	const std::map<T_FIRST, T_SECOND>& getTables()const{ return _tables; }\
protected:\
	std::map<T_FIRST, T_SECOND> _tables;\
}