/*
**  =======================================================
**              Galaxy2D Game Engine       
**                                
**       版权所有(c) 2005 沈明. 保留所有权利.
**    主页地址: http://www.cnblogs.com/jianguhan/
**			 电子邮箱: jianguhan@126.com
**  =======================================================
*/

/** \file
\brief 交换链模块
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 交换链模块
	class ggeSwapChain : public ggeRefCounter
	{
	public:
		/**
		@brief 开始交换链渲染
		@param color 以该颜色刷新窗口
		@return 成功返回true，失败返回false
		*/
		virtual bool BeginScene(guint32 color = 0xFF000000) = 0;
		/**
		@brief 结束交换链渲染。如果设置渲染区域，在当前交换链所有内容都渲染到该区域，如果渲染区域尺寸与交换链尺寸不同，渲染出来的画面将会被拉伸或压缩
		@param x x坐标
		@param y y坐标
		@param width 宽度
		@param height 高度
		*/
		virtual void EndScene(int x = 0, int y = 0, int width = 0, int height = 0) = 0;
	};

	/**
	@brief 创建一个指定窗口句柄的交换链
	@param hwnd 窗口句柄
	@param width 后台缓存宽度，为0则使用GGE_SCREENWIDTH
	@param height 后台缓存高度，为0则使用GGE_SCREENHEIGHT
	@return 创建成功返回ggeSwapChain指针，否则返回0
	*/
	GGE_EXPORT ggeSwapChain*  SwapChain_Create(HWND hwnd, int width = 0, int height = 0);
}