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
\brief GUI载入器
*/

#pragma once
#include "ggeguiwindow.h"

namespace gge
{
	typedef ggeGuiWindow*(*GGE_GUICREATEFUNC)(ggeGuiCreateInfo &info);

	/// GUI载入器
	class ggeGuiLoader : public ggeRefCounter
	{
	public:
		/**
		@brief 添加自定义控件创建函数
		@param className 自定义控件类名
		@param func 创建函数
		@note	1.当className与GUI编辑器的"自定义属性"中的"ClassName"项一致时，使用func函数创建控件
				2.className设为0用于设置默认创建函数
				3.如果编辑器中"ClassName"为空或找不到对应的创建函数则使用默认创建函数创建控件，如果没有设置默认创建函数则创建基础控件
		*/
		virtual void AddCreateFunc(const char *className, GGE_GUICREATEFUNC func) = 0;

		/**
		@brief 删除自定义控件创建函数
		@param className 自定义控件类名，0为默认创建函数
		*/
		virtual void DelCreateFunc(const char *className) = 0;

		/// 删除所有自定义控件创建函数
		virtual void DelAllCreateFunc() = 0;

		/**
		@brief 设置资源管理器
		@param resmgr 资源管理器指针
		*/
		virtual void SetResManager(ggeResManager *resmgr) = 0;

		/**
		@brief 载入GUI文件
		@param filename GUI文件名
		@return 载入成功返回true，否则返回false
		*/
		virtual bool Load(const char *filename) = 0;

		/**
		@brief 创建控件
		@param ctrlname 控件名
		@return 创建成功返回控件指针，否则返回0
		@note	1.该函数只能创建GUI控件列表中的顶层控件
				2.必须设置资源管理器，否则创建失败
		*/
		virtual ggeGuiWindow* CreateControl(const char *ctrlname) = 0;
	};

	/// 创建GUI载入器
	GGE_EXPORT ggeGuiLoader*  GUI_CreateGuiLoader();
}