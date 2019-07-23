/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#ifndef __CCCONFIG_H__
#define __CCCONFIG_H__

#include "../platform/CCPlatformConfig.h"

/**
 * @file
 * cocos2d (cc) configuration file.
*/

/** @def CC_ENABLE_STACKABLE_ACTIONS
 * If enabled, actions that alter the position property (eg: MoveBy, JumpBy, BezierBy, etc..) will be stacked.
 * If you run 2 or more 'position' actions at the same time on a node, then end position will be the sum of all the positions.
 * If disabled, only the last run action will take effect.
 * Enabled by default. Disable to be compatible with v2.0 and older versions.
 * @since v2.1
 */
#ifndef CC_ENABLE_STACKABLE_ACTIONS
#define CC_ENABLE_STACKABLE_ACTIONS 1
#endif


/** Enable Script binding. */
#ifndef CC_ENABLE_SCRIPT_BINDING
#define CC_ENABLE_SCRIPT_BINDING 0
#endif

/** When CC_ENABLE_SCRIPT_BINDING and CC_ENABLE_GC_FOR_NATIVE_OBJECTS are both 1
 then the Garbage collector will release the native objects, only when the JS/Lua objets
 are collected.
 The benefit is that users don't need to retain/release the JS/Lua objects manually.

 By default this behavior is disabled by default
 */
#ifdef CC_ENABLE_SCRIPT_BINDING
  #ifndef CC_ENABLE_GC_FOR_NATIVE_OBJECTS
  #define CC_ENABLE_GC_FOR_NATIVE_OBJECTS 0
  #endif
#endif

/** @def CC_CONSTRUCTOR_ACCESS
 * Indicate the init functions access modifier. If value equals to protected, then these functions are protected.
 * If value equals to public, these functions are public,
 * protected by default.
 */
#ifndef CC_CONSTRUCTOR_ACCESS
  #ifdef CC_ENABLE_SCRIPT_BINDING
    #define CC_CONSTRUCTOR_ACCESS public
  #else
    #define CC_CONSTRUCTOR_ACCESS protected
  #endif
#endif

#endif // __CCCONFIG_H__
