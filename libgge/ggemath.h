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
\brief 数学库
*/

#pragma once
#include "ggetypes.h"

namespace gge
{
	/** @name Math
	*  @{
	*/

	#define GGE_PI		3.14159265358979323846f		///< 圆周率
	#define GGE_PI_2	1.57079632679489661923f		///< 圆周率
	#define GGE_PI_4	0.785398163397448309616f	///< 圆周率
	#define GGE_1_PI	0.318309886183790671538f	///< 圆周率
	#define GGE_2_PI	0.636619772367581343076f	///< 圆周率

	/// 弧度转角度
	inline float ToDegree(float radian) { return radian * (180.0f / (float)GGE_PI); }
	/// 角度转弧度
	inline float ToRadian(float degree) { return degree * ((float)GGE_PI / 180.0f); }
	/// 以s为参数在v1和v2间线性插值
	inline float LinearErp(float v1, float v2, float s) { return v1 + s * (v2 - v1); }

	/** 
	@} 
	*/

	/// Vector
	class ggeVector
	{
	public:
		float	x;	///< x
		float	y;	///< y

		/// 构造函数
		ggeVector(float _x, float _y) : x(_x), y(_y) {}
		/// 构造函数
		ggeVector() : x(0), y(0) {}

		/// 运算符重载
		ggeVector	operator+  (const ggeVector &v)	const	{ return ggeVector(x + v.x, y + v.y); }
		/// 运算符重载
		ggeVector	operator-  (const ggeVector &v)	const	{ return ggeVector(x - v.x, y - v.y); }
		/// 运算符重载
		ggeVector	operator*  (const ggeVector &v)	const	{ return ggeVector(x * v.x, y * v.y); }
		/// 运算符重载
		ggeVector	operator/  (const ggeVector &v)	const	{ return ggeVector(x / v.x, y / v.y); }
		/// 运算符重载
		ggeVector	operator+  (const float v)	const		{ return ggeVector(x + v, y + v); }
		/// 运算符重载
		ggeVector	operator-  (const float v)	const		{ return ggeVector(x - v, y - v); }
		/// 运算符重载
		ggeVector	operator*  (const float v)	const		{ return ggeVector(x * v, y * v); }
		/// 运算符重载
		ggeVector	operator/  (const float v)	const		{ return ggeVector(x / v, y / v); }
		/// 运算符重载
		ggeVector&	operator+= (const ggeVector &v)			{ x += v.x; y += v.y; return *this; }
		/// 运算符重载
		ggeVector&	operator-= (const ggeVector &v)			{ x -= v.x; y -= v.y; return *this; }
		/// 运算符重载
		ggeVector&	operator*= (const ggeVector &v)			{ x *= v.x; y *= v.y; return *this; }
		/// 运算符重载
		ggeVector&	operator/= (const ggeVector &v)			{ x /= v.x; y /= v.y; return *this; }
		/// 运算符重载
		ggeVector&	operator+= (const float v)				{ x += v; y += v; return *this; }
		/// 运算符重载
		ggeVector&	operator-= (const float v)				{ x -= v; y -= v; return *this; }
		/// 运算符重载
		ggeVector&	operator*= (const float v)				{ x *= v; y *= v; return *this; }
		/// 运算符重载
		ggeVector&	operator/= (const float v)				{ x /= v; y /= v; return *this; }
		/// 运算符重载
		ggeVector	operator-  ()					const	{ return ggeVector(-x, -y); }
		/// 运算符重载
		bool		operator== (const ggeVector &v)	const	{ return (x == v.x && y == v.y); }
		/// 运算符重载
		bool		operator!= (const ggeVector &v)	const	{ return (x != v.x || y != v.y); }

		/**
		@brief 获得两矢量点积
		@param v 矢量
		@return 两矢量点积
		*/
		GGE_EXPORT float		Dot(const ggeVector &v) const;
		/**
		@brief 标准化矢量
		*/
		GGE_EXPORT void			Normalize();	
		/**
		@brief 获得矢量长度
		@return 矢量长度
		*/
		GGE_EXPORT float		Length() const;
		/**
		@brief 获得矢量长度的平方
		@return 矢量长度的平方
		*/
		GGE_EXPORT float		LengthSquared() const;
		/**
		@brief 返回与X轴的角度
		@return 返回与X轴的角度
		*/
		GGE_EXPORT float		Angle() const;
		/**
		@brief 获得两矢量间角度
		@param v 矢量
		@return 两矢量间角度
		*/
		GGE_EXPORT float		AngleTo(const ggeVector &v) const;
		/**
		@brief 如果v在该矢量的顺时针方向返回1，如果在逆时针方向返回-1，否则返回0
		@param v 矢量
		@return 如果v在该矢量的顺时针方向返回1，如果在逆时针方向返回-1，否则返回0
		*/
		GGE_EXPORT int			Sign(const ggeVector &v) const;
		/**
		@brief 返回与该矢量垂直的矢量
		@return 返回与该矢量垂直的矢量
		*/
		GGE_EXPORT ggeVector	Perpendicular() const;
		/**
		@brief 返回以v为平面的反射矢量，v必须是标准化矢量
		@return 返回以v为平面的反射矢量
		*/
		GGE_EXPORT ggeVector	Reflect(const ggeVector &v) const;
		/**
		@brief 设置成以v为平面的反射矢量，v必须是标准化矢量
		@return 返回该矢量
		*/
		GGE_EXPORT ggeVector&	ToReflect(const ggeVector &v);
		/**
		@brief 将矢量旋转指定角度
		@param radian 旋转角度
		*/
		GGE_EXPORT void			Rotate(float radian);
		/**
		@brief 使矢量长度不超过指定的长度
		@param max 最大长度
		*/
		GGE_EXPORT void			Clamp(float max);
	};
	
	/** @name Vector
	*  @{
	*/

	/// Vector运算符重载
	inline ggeVector operator* (const float s, const ggeVector &v)	{ return ggeVector(s * v.x, s * v.y); }
	/// Vector运算符重载
	inline ggeVector operator/ (const float s, const ggeVector &v)	{ return ggeVector(s / v.x, s / v.y); }

	/** 
	@} 
	*/

	/// Vector3
	class  ggeVector3
	{
	public:
		float	x;	///< x
		float	y;	///< y
		float	z;	///< z

		/// 构造函数
		ggeVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		/// 构造函数
		ggeVector3() : x(0), y(0), z(0) {}

		/// 运算符重载
		ggeVector3	operator+  (const ggeVector3 &v)	const	{ return ggeVector3(x + v.x, y + v.y, z + v.z); }
		/// 运算符重载
		ggeVector3	operator-  (const ggeVector3 &v)	const	{ return ggeVector3(x - v.x, y - v.y, z - v.z); }
		/// 运算符重载
		ggeVector3	operator*  (const ggeVector3 &v)	const	{ return ggeVector3(x * v.x, y * v.y, z * v.z); }
		/// 运算符重载
		ggeVector3	operator/  (const ggeVector3 &v)	const	{ return ggeVector3(x / v.x, y / v.y, z / v.z); }
		/// 运算符重载
		ggeVector3	operator+  (const float v)	const			{ return ggeVector3(x + v, y + v, z + v); }
		/// 运算符重载
		ggeVector3	operator-  (const float v)	const			{ return ggeVector3(x - v, y - v, z - v); }
		/// 运算符重载
		ggeVector3	operator*  (const float v)	const			{ return ggeVector3(x * v, y * v, z * v); }
		/// 运算符重载
		ggeVector3	operator/  (const float v)	const			{ return ggeVector3(x / v, y / v, z / v); }
		/// 运算符重载
		ggeVector3&	operator+= (const ggeVector3 &v)			{ x += v.x; y += v.y; z += v.z; return *this; }
		/// 运算符重载
		ggeVector3&	operator-= (const ggeVector3 &v)			{ x -= v.x; y -= v.y; z -= v.z; return *this; }
		/// 运算符重载
		ggeVector3&	operator*= (const ggeVector3 &v)			{ x *= v.x; y *= v.y; z *= v.z; return *this; }
		/// 运算符重载
		ggeVector3&	operator/= (const ggeVector3 &v)			{ x /= v.x; y /= v.y; z /= v.z; return *this; }
		/// 运算符重载
		ggeVector3&	operator+= (const float v)					{ x += v; y += v; z += v; return *this; }
		/// 运算符重载
		ggeVector3&	operator-= (const float v)					{ x -= v; y -= v; z -= v; return *this; }
		/// 运算符重载
		ggeVector3&	operator*= (const float v)					{ x *= v; y *= v; z *= v; return *this; }
		/// 运算符重载
		ggeVector3&	operator/= (const float v)					{ x /= v; y /= v; z /= v; return *this; }
		/// 运算符重载
		ggeVector3	operator-  ()						const	{ return ggeVector3(-x, -y, -z); }
		/// 运算符重载
		bool		operator== (const ggeVector3 &v)	const	{ return (x == v.x && y == v.y && z == v.z); }
		/// 运算符重载
		bool		operator!= (const ggeVector3 &v)	const	{ return (x != v.x || y != v.y || z != v.z); }

		/**
		@brief 获得两矢量点积
		@param v 矢量
		@return 两矢量点积
		*/
		GGE_EXPORT float		Dot(const ggeVector3 &v) const;
		/**
		@brief 获得两矢量叉积
		@param v 矢量
		@return 两矢量叉积
		*/
		GGE_EXPORT ggeVector3	Cross(const ggeVector3 &v) const;
		/**
		@brief 标准化矢量
		*/
		GGE_EXPORT void			Normalize();
		/**
		@brief 获得矢量长度
		@return 矢量长度
		*/
		GGE_EXPORT float		Length() const;
		/**
		@brief 获得矢量长度的平方
		@return 矢量长度的平方
		*/
		GGE_EXPORT float		LengthSquared() const;
		/**
		@brief 获得两矢量间角度
		@param v 矢量
		@return 两矢量间角度
		*/
		GGE_EXPORT float		Angle(const ggeVector3 &v) const;
		/**
		@brief 使矢量长度不超过指定的长度
		@param max 最大长度
		*/
		GGE_EXPORT void			Clamp(float max);
	};

	/** @name Vector3
	*  @{
	*/

	/// Vector3运算符重载
	inline ggeVector3 operator* (const float s, const ggeVector3 &v)	{ return ggeVector3(s * v.x, s * v.y, s * v.z); }
	/// Vector3运算符重载
	inline ggeVector3 operator/ (const float s, const ggeVector3 &v)	{ return ggeVector3(s / v.x, s / v.y, s / v.z); }

	/** 
	@} 
	*/

	/// Rect
	class ggeRect
	{
	public:
		float	x1;	///< 左上角x坐标
		float	y1; ///< 左上角y坐标
		float	x2; ///< 右下角x坐标
		float	y2; ///< 右下角y坐标

		/// 构造函数
		ggeRect() : m_bClean(true) {}
		/// 构造函数
		ggeRect(float _x1, float _y1, float _x2, float _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), m_bClean(false) {}

		/// 运算符重载
		bool		operator== (const ggeRect &v)	const	{ return (x1 == v.x1 && y1 == v.y1 && x2 == v.x2 && y2 == v.y2); }
		/// 运算符重载
		bool		operator!= (const ggeRect &v)	const	{ return (x1 != v.x1 || y1 != v.y1 || x2 != v.x2 || y2 != v.y2); }

		/// 设置宽度
		void	SetWidth(float w)	{ x2 = x1 + w; }
		/// 返回宽度
		float	GetWidth()			{ return x2 - x1; }
		/// 设置高度
		void	SetHeight(float h)	{ y2 = y1 + h; }
		/// 返回高度
		float	GetHeight()			{ return y2 - y1; }

		/**
		@brief 设置矩形坐标
		@param _x1 左上角x坐标
		@param _y1 左上角y坐标
		@param _x2 右下角x坐标
		@param _y2 右下角y坐标
		*/
		GGE_EXPORT void Set(float _x1, float _y1, float _x2, float _y2);
		/**
		@brief 清除矩形
		*/
		GGE_EXPORT void Clear();
		/**
		@brief 矩形是否有效
		@return 矩形是否有效
		*/
		GGE_EXPORT bool IsClean() const;
		/**
		@brief 移动矩形到点(x, y)，矩形大小不变
		@param x x坐标
		@param y y坐标
		*/
		GGE_EXPORT void Move(float x, float y);
		/**
		@brief 设置矩形范围
		@param x 矩形中心x坐标
		@param y 矩形中心y坐标
		@param r 矩形范围
		*/
		GGE_EXPORT void SetRadius(float x, float y, float r);
		/**
		@brief 调整矩形大小使其能够包含点(x, y)
		@param x x坐标
		@param y y坐标
		*/
		GGE_EXPORT void Encapsulate(float x, float y);
		/**
		@brief 用另一个矩形来裁剪该矩形
		@param rect 用于裁剪的矩形
		*/
		GGE_EXPORT void ClipWith(const ggeRect &rect);
		/**
		@brief 测试点(x, y)是否在该矩形框内
		@param x x坐标
		@param y y坐标
		@return 点是否在该矩形框内
		*/
		GGE_EXPORT bool TestPoint(float x, float y) const;
		/**
		@brief 测试两个矩形框是否相交
		@param rect 要测试的矩形
		@return 两个矩形框是否相交
		*/
		GGE_EXPORT bool Intersect(const ggeRect &rect) const;

	private:
		bool	m_bClean;
	};
}