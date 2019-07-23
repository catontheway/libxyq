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
\brief GUI管理器
*/

#pragma once
#include "ggecommon.h"

namespace gge
{
	/**
	@brief 刷新GUI系统
	@param dt 上一帧所用时间，可用Timer_GetDelta()获得
	*/
	GGE_EXPORT void			GUI_Update(float dt);
	/**
	@brief 渲染GUI系统
	*/
	GGE_EXPORT void			GUI_Render();

	/**
	@brief 设置顶层窗口
	@param wnd 顶层窗口
	*/
	GGE_EXPORT void			GUI_SetRootWindow(ggeGuiWindow *wnd);
	/**
	@brief 返回顶层窗口
	@return 顶层窗口
	*/
	GGE_EXPORT ggeGuiWindow* GUI_GetRootWindow();
	/**
	@brief 是否启用鼠标，默认启用
	*/
	GGE_EXPORT void			GUI_EnableMouse(bool b);
	/**
	@brief 设置焦点控件，如果为0则清除当前焦点控件的焦点状态
	*/
	GGE_EXPORT void			GUI_SetFocusCtrl(ggeGuiWindow *ctrl = 0);
	/**
	@brief 返回当前焦点控件
	*/
	GGE_EXPORT ggeGuiWindow* GUI_GetFocusCtrl();
	/**
	@brief 设置用于显示ToolTip的控件，该控件不能有父窗口
	*/
	GGE_EXPORT void			GUI_SetToolTipCtrl(ggeGuiRichText *ctrl);
	/**
	@brief 返回用于显示ToolTip的控件
	*/
	GGE_EXPORT ggeGuiRichText* GUI_GetToolTipCtrl();
	/**
	@brief 设置显示ToolTip延时，单位：秒
	*/
	GGE_EXPORT void			GUI_SetToolTipDelay(float t);
	/**
	@brief 返回显示ToolTip延时
	*/
	GGE_EXPORT float		GUI_GetToolTipDelay();

	/**
	@brief 添加模态窗口(注意：模态窗口不能有父窗口，窗口关闭时需要调用RemoveModalWnd()函数移除该窗口)
	*/
	GGE_EXPORT void			GUI_AddModalWnd(ggeGuiWindow *wnd);
	/**
	@brief 移除模态窗口
	*/
	GGE_EXPORT void			GUI_RemoveModalWnd(ggeGuiWindow *wnd);
	/**
	@brief 移除所有模态窗口
	*/
	GGE_EXPORT void			GUI_RemoveAllModalWnd();
	/**
	@brief 移除所有窗口
	*/
	GGE_EXPORT void			GUI_Clear();
}