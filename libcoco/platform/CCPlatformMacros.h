/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef __CC_PLATFORM_MACROS_H__
#define __CC_PLATFORM_MACROS_H__

/**
 * define some platform specific macros
 */
#include "../base/ccConfig.h"
#include "CCPlatformConfig.h"
#include "CCPlatformDefine.h"


// namespace cocos2d {}
#ifdef __cplusplus
    #define NS_CC_BEGIN                     namespace cocos2d {
    #define NS_CC_END                       }
    #define USING_NS_CC                     using namespace cocos2d
	#define NS_CC                           ::cocos2d
#else
    #define NS_CC_BEGIN 
    #define NS_CC_END 
    #define USING_NS_CC 
    #define NS_CC
#endif 

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define CC_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define CC_SAFE_RELEASE(p)          do { if(p) { (p)->release(); } } while(0)
#define CC_SAFE_RELEASE_NULL(p)     do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define CC_SAFE_RETAIN(p)           do { if(p) { (p)->retain(); } } while(0)

#define __CCLOGWITHFUNCTION(s, ...) \
    log("%s : %s",__FUNCTION__, StringUtils::format(s, ##__VA_ARGS__).c_str())

// cocos2d debug
#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 1//0
#define CCLOG(...)       do {} while (0)
#define CCLOGINFO(...)   do {} while (0)
#define CCLOGERROR(...)  do {} while (0)
#define CCLOGWARN(...)   do {} while (0)

#elif COCOS2D_DEBUG == 1
#define CCLOG(format, ...)      cocos2d::log(format, ##__VA_ARGS__)
#define CCLOGERROR(format,...)  cocos2d::log(format, ##__VA_ARGS__)
#define CCLOGINFO(format,...)   do {} while (0)
#define CCLOGWARN(...) __CCLOGWITHFUNCTION(__VA_ARGS__)

#elif COCOS2D_DEBUG > 1
#define CCLOG(format, ...)      cocos2d::log(format, ##__VA_ARGS__)
#define CCLOGERROR(format,...)  cocos2d::log(format, ##__VA_ARGS__)
#define CCLOGINFO(format,...)   cocos2d::log(format, ##__VA_ARGS__)
#define CCLOGWARN(...) __CCLOGWITHFUNCTION(__VA_ARGS__)
#endif // COCOS2D_DEBUG


// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) \
	|| (defined(__clang__) && (__clang_major__ >= 3)) || (_MSC_VER >= 1800)
#define CC_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete; \
    TypeName &operator =(const TypeName &) = delete;
#else
#define CC_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &); \
    TypeName &operator =(const TypeName &);
#endif

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#define CC_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName)    \
    TypeName();                                        \
    CC_DISALLOW_COPY_AND_ASSIGN(TypeName)

/*
 * only certain compilers support __attribute__((deprecated))
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
	#define CC_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
    #define CC_DEPRECATED_ATTRIBUTE __declspec(deprecated) 
#else
    #define CC_DEPRECATED_ATTRIBUTE
#endif 

//
// CC_REQUIRES_NULL_TERMINATION
//
#if !defined(CC_REQUIRES_NULL_TERMINATION)
    #if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
        #define CC_REQUIRES_NULL_TERMINATION __attribute__((sentinel(0,1)))
    #elif defined(__GNUC__)
        #define CC_REQUIRES_NULL_TERMINATION __attribute__((sentinel))
    #else
        #define CC_REQUIRES_NULL_TERMINATION
    #endif
#endif

#endif // __CC_PLATFORM_MACROS_H__
