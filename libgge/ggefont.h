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
\brief 字体模块
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 字体模块
	class ggeFont : public ggeRefCounter
	{
	public:
		/**
		@brief 返回当前字体的一个副本
		@return 当前字体的一个副本
		*/
		virtual ggeFont* Clone() = 0;

		/**
		@brief 绘制文字
		@param x x坐标
		@param y y坐标
		@param str 字符串
		*/
		virtual void	Render(float x, float y, const char *str) = 0;
		/**
		@brief 绘制文字
		@param x x坐标
		@param y y坐标
		@param format 格式化字符串
		*/
		virtual void	Print(float x, float y, const char *format, ...) = 0;

		/**
		@brief 设置字体颜色
		@param color 字体颜色
		*/
		virtual void	SetColor(guint32 color) = 0;
		/**
		@brief 获得字体颜色
		@return 字体颜色
		*/
		virtual guint32	GetColor() = 0;
		/**
		@brief 设置Z轴
		@param z 0.0f～1.0f，0表示最上层，1表示最下层
		*/
		virtual void	SetZ(float z) = 0;
		/**
		@brief 获得Z轴
		@return Z轴
		*/
		virtual float	GetZ() = 0;
		/**
		@brief 设置混合模式
		@param blend 混合模式，可用"|"结合
		@see BLEND_MODE
		*/
		virtual void	SetBlendMode(int blend) = 0;
		/**
		@brief 获得混合模式
		@return 混合模式
		*/
		virtual int		GetBlendMode() = 0;

		/**
		@brief 设置行宽
		@param width 行宽(单位:像素)，字符串超过行宽自动换行，0为不限制行宽
		*/
		virtual void	SetLineWidth(int width) = 0;
		/**
		@brief 获得行宽
		@return 行宽
		*/
		virtual int		GetLineWidth() = 0;
		/**
		@brief 设置字间距
		@param space 行间距(单位:像素)，默认为0
		*/
		virtual void	SetCharSpace(int space) = 0;
		/**
		@brief 获得字间距
		@return 字间距
		*/
		virtual int		GetCharSpace() = 0;
		/**
		@brief 设置行间距
		@param space 行间距(单位:像素)，默认为0
		*/
		virtual void	SetLineSpace(int space) = 0;
		/**
		@brief 获得行间距
		@return 行间距
		*/
		virtual int		GetLineSpace() = 0;
		/**
		@brief 设置要显示的文字个数
		@param num 文字个数，为-1时则显示所有文字，默认为-1
		*/
		virtual void	SetCharNum(int num) = 0;
		/**
		@brief 返回要显示的字符数
		@return 返回要显示的字符数
		*/
		virtual int		GetCharNum() = 0;
		/**
		@brief 设置字体排版样式
		@param align 字体排版样式
		@see FONT_ALIGN
		*/
		virtual void	SetAlign(int align) = 0;
		/**
		@brief 获得字体排版样式
		@return 字体排版样式
		*/
		virtual int		GetAlign() = 0;
		/**
		@brief 设置字体阴影颜色
		@param color 阴影颜色
		*/
		virtual void	SetShadowColor(guint32 color) = 0;
		/**
		@brief 获得字体阴影颜色
		@return 字体阴影颜色
		*/
		virtual guint32	GetShadowColor() = 0;
		/**
		@brief 设置字体描边颜色(需要创建字体时开启描边功能)
		@param color 描边颜色
		*/
		virtual void	SetBorderColor(guint32 color) = 0;
		/**
		@brief 获得字体描边颜色
		@return 字体描边颜色
		*/
		virtual guint32	GetBorderColor() = 0;
		
		/**
		@brief 获得字体高度
		@return 字体高度
		*/
		virtual int		GetFontHight() = 0;
		/**
		@brief 获得字体大小
		@return 字体大小
		*/
		virtual int		GetFontSize() = 0;

		///字符串信息
		struct StringInfo
		{
			float Width;	///< 字符串宽度
			float Height;	///< 字符串高度
		};
		/**
		@brief 获得字串信息
		@param str 字符串
		@param strinfo 字符串信息 @see StringInfo
		@param len 要扫描的字符串长度，如果为-1则扫描整个字符串
		*/
		virtual void	GetStringInfo(const char *str, StringInfo &strinfo, int len = -1) = 0;
	};

	/**
	@brief 创建字体
	@param filename 字体文件名(*.ttf/*.ttc)
	@param fontSize 字体大小，单位：象素(必须大于4)
	@param createMode 字体创建模式，可用"|"结合 @see FONT_CREATE_MODE
	@return 成功返回ggeFont指针，否则返回0
	@note 引擎底层已对字体资源进行统一调度和管理，重复创建相同属性的字体或Clone字体只会增加少量内存占用量
	*/
	GGE_EXPORT ggeFont*	 Font_Create(const char *filename, int fontSize = 16, int createMode = FONT_MODE_DEFAULT);

	/**
	@brief 从图片创建字体
	@param filename 字体配置文件
	@return 成功返回ggeFont指针，否则返回0
	@code	一个字体配置文件的完整格式如下：
		<?xml version="1.0" encoding="gb2312" ?>
		<Font_File>
			<FontInfo Size="28" LineSpace="28"/>
			<Page Texture="imgfont.png">
				<CharInfo Char="0" X="0" Y="4" W="28" H="27" Adv="28" OX="0" OY = "0"/>
			</Page>
		</Font_File>
		
		FontInfo节点用于配置字体的基础属性
			Size：字体大小(单位：像素)
			LineSpace：默认行距(单位：像素)
		
		Page节点用于配置一张纹理上的文字属性，如果文字分布在多张纹理上，可以写多个Page来包含所有文字
			Texture：当前文字所在的纹理名字，该纹理必须跟字体配置文件处于同一目录
		
		CharInfo节点用于配置文字属性
			X/Y：文字在当前纹理上左上角坐标(单位：像素)
			W/H：文字宽度和高度(单位：像素)
			Adv：绘制下个文字画笔要移动的距离(单位：像素)
			OX/OY：绘制文字时X/Y方向上的偏移量(单位：像素)
	@endcode 
	*/
	GGE_EXPORT ggeFont*	 Font_CreateFromImage(const char *filename);
}