#pragma once

#define CREATE_INIT(_T_, _I_, ...)\
_T_ *pRet = new (std::nothrow)_T_();\
if (pRet && pRet->_I_(__VA_ARGS__))\
{\
	pRet->autorelease();\
	return pRet;\
}\
else\
{\
	delete pRet;\
	return nullptr;\
}
#define CREATE(_TYPE_, ...) CREATE_INIT(_TYPE_, init, __VA_ARGS__)
#define CREATE_FUNC(__TYPE__) static __TYPE__* create(){ CREATE(__TYPE__) }