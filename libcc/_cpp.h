#pragma once

// C++
#include <string>
#include <math.h>
#include <functional>


// STL
#include <array>
#include <vector>
#include <set>
#include <map>
#include <algorithm>




// 无符号
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned __int64 u64;




////////////////////////////////////////////////////////////////////////// delete
#define ccc_delete(_p_) if(_p_ != nullptr){delete _p_; _p_ = nullptr;}
#define ccc_delete_array(_p_) if(_p_ != nullptr){delete[] _p_; _p_ = nullptr;}
#define ccc_delete_array1(_p_, _n_)\
if(_p_ != nullptr)\
{\
	for(int _i_ = (_n_) - 1; _i_ >= 0; --_i_)\
	{\
		ccc_delete(_p_[_i_])\
	}\
	delete[] _p_;\
	_p_ = nullptr;\
}
#define ccc_delete_array2(_p_, _n_)\
if(_p_ != nullptr)\
{\
	for(int _i_ = (_n_) - 1; _i_ >= 0; --_i_)\
	{\
		ccc_delete_array(_p_[_i_])\
	}\
	delete[] _p_;\
	_p_ = nullptr;\
}



////////////////////////////////////////////////////////////////////////// STL
// 正序for
#define forr(_vect_,_i_) for(int _i_ = (int)_vect_.size() - 1; _i_ >= 0; --_i_)
// 反序for
#define forv(_vect_,_i_) for(int _size_ = (int)_vect_.size(), _i_ = 0; _i_ < _size_; ++_i_)
// 迭代for
#define forit(_vect_,_it_) for(auto& _it_ = _vect_.begin(), _itend_ =  _vect_.end(); _it_ != _itend_; ++_it_)

// 通用查找容器迭代器
#define ccc_find_it(_STL_, _V_) std::find(_STL_.begin(), _STL_.end(), _V_)
// 容器能否找到元素
#define ccc_find(_STL_, _V_) (ccc_find_it(_STL_, _V_) != _STL_.end())
