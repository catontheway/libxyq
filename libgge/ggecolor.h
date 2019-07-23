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
\brief 颜色模块
*/


#pragma once
#include "ggetypes.h"

namespace gge
{
	/** @name Color
	*  @{
	*/

	/// 生成颜色值
	inline guint32 Color_ARGB(guint32 a, guint32 r, guint32 g, guint32 b)	{ return (a << 24) + (r << 16) + (g << 8) + b; }
	/// 生成颜色值
	inline guint32 Color_XRGB(guint32 r, guint32 g, guint32 b)			{ return Color_ARGB(255, r, g, b); }
	/// 返回alpha值
	inline guint32 Color_GetA(guint32 col)							{ return col >> 24; }
	/// 设置alpha值
	inline guint32 Color_SetA(guint32 col, guint32 a)					{ return (col & 0x00FFFFFF) + (a << 24); }
	/// 返回红色值
	inline guint32 Color_GetR(guint32 col)							{ return (col >> 16) & 0xFF; }
	/// 设置红色值
	inline guint32 Color_SetR(guint32 col, guint32 r)					{ return (col & 0xFF00FFFF) + (r << 16); }
	/// 返回绿色值
	inline guint32 Color_GetG(guint32 col)							{ return (col >> 8) & 0xFF; }
	/// 设置绿色值
	inline guint32 Color_SetG(guint32 col, guint32 g)					{ return (col & 0xFFFF00FF) + (g << 8); }
	/// 返回蓝色值
	inline guint32 Color_GetB(guint32 col)							{ return col & 0xFF; }
	/// 设置蓝色值
	inline guint32 Color_SetB(guint32 col, guint32 b)					{ return (col & 0xFFFFFF00) + b; }

	/** 
	@} 
	*/

	/// 颜色模块
	class ggeColor
	{
	public:
		float	r;	///< 红色分量(0.0f~1.0f)
		float	g;	///< 绿色分量(0.0f~1.0f)
		float	b;	///< 蓝色分量(0.0f~1.0f)
		float	a;	///< alpha分量(0.0f~1.0f)

		/// 构造函数
		ggeColor(float _r, float _g, float _b, float _a) { r = _r; g = _g; b = _b; a = _a; }
		/// 构造函数
		ggeColor(guint32 c)	{ SetColor(c); }
		/// 构造函数
		ggeColor()			{ r = g = b = a = 0; }

		/// 运算符重载
		ggeColor	operator-  (const ggeColor &c)	{ return ggeColor(r - c.r, g - c.g, b - c.b, a - c.a); }
		/// 运算符重载
		ggeColor	operator+  (const ggeColor &c)	{ return ggeColor(r + c.r, g + c.g, b + c.b, a + c.a); }
		/// 运算符重载
		ggeColor	operator*  (const ggeColor &c)  { return ggeColor(r * c.r, g * c.g, b * c.b, a * c.a); }
		/// 运算符重载
		ggeColor&	operator-= (const ggeColor &c)	{ r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this; }
		/// 运算符重载
		ggeColor&	operator+= (const ggeColor &c)	{ r += c.r; g +=c .g; b += c.b; a += c.a; return *this; }
		/// 运算符重载
		bool		operator== (const ggeColor &c)	{ return (r == c.r && g == c.g && b == c.b && a == c.a); }
		/// 运算符重载
		bool		operator!= (const ggeColor &c)	{ return (r != c.r || g != c.g || b != c.b || a != c.a); }

		/// 运算符重载
		ggeColor	operator*  (float scalar)		{ return ggeColor(r * scalar, g * scalar, b * scalar, a * scalar); }
		/// 运算符重载
		ggeColor	operator/  (float scalar)		{ return ggeColor(r / scalar, g / scalar, b / scalar, a / scalar); }
		/// 运算符重载
		ggeColor&	operator*= (float scalar)		{ r *= scalar; g *= scalar; b *= scalar; a *= scalar; return *this; }

		/**
		@brief 设置颜色值
		@param wcolor 32位颜色值
		*/
		void	SetColor(guint32 wcolor)				{ a = (wcolor >> 24) / 255.0f; r = ((wcolor >> 16) & 0xFF) / 255.0f; g = ((wcolor >> 8) & 0xFF) / 255.0f; b = (wcolor & 0xFF) / 255.0f; }
		/**
		@brief 获得32位颜色值
		@return 32位颜色值
		*/
		guint32	GetColor() const					{ return (guint32(a * 255.0f) << 24) + (guint32(r * 255.0f) << 16) + (guint32(g * 255.0f) << 8) + guint32(b * 255.0f); }
		/**
		@brief 使颜色值在0.0f~1.0f范围内
		*/
		GGE_EXPORT void	Clamp();
		/**
		@brief 保存c1和c2间线性插值的结果
		@param c1 颜色1
		@param c2 颜色2
		@param s 插值，越小越接近c1
		@return 返回自身引用
		*/
		GGE_EXPORT ggeColor& Lerp(const ggeColor &c1, const ggeColor &c2, float s);
	};

	/** @name Color
	*  @{
	*/

	/// 颜色运算符重载
	inline ggeColor operator* (const ggeColor &c, float s)	{ return ggeColor(s * c.r, s * c.g, s * c.b, s * c.a); }
	/// 颜色运算符重载
	inline ggeColor operator* (float s, const ggeColor &c)	{ return ggeColor(s * c.r, s * c.g, s * c.b, s * c.a); }

	/** 
	@} 
	*/
}