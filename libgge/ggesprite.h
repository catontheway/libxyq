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
\brief 精灵模块
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 精灵模块
	class ggeSprite : public ggeRefCounter
	{
	public:
		/**
		@brief 复制精灵
		@param spr 源精灵
		*/
		virtual void		Copy(ggeSprite *spr) = 0;
		/**
		@brief 返回当前精灵的一个副本
		@return 当前精灵的一个副本
		*/
		virtual ggeSprite*	Clone() = 0;

		/**
		@brief 渲染
		@param x x坐标
		@param y y坐标
		*/
		virtual void		Render(float x, float y) = 0;
		/**
		@brief 渲染
		@param x x坐标
		@param y y坐标
		@param rotation 旋转弧度数
		@param hscale 水平缩放系数
		@param vscale 垂直缩放系数，若该值为0.0f，则取hscale
		*/
		virtual void		RenderEx(float x, float y, float rotation, float hscale = 1.0f, float vscale = 0.0f) = 0;
		/**
		@brief 渲染
		@param x1 左上角x坐标
		@param y1 左上角y坐标
		@param x2 右下角x坐标
		@param y2 右下角y坐标
		*/
		virtual void		RenderStretch(float x1, float y1, float x2, float y2) = 0;
		/**
		@brief 渲染
		@param x0 左上角x坐标
		@param y0 左上角y坐标
		@param x1 右上角x坐标
		@param y1 右上角y坐标
		@param x2 左下角x坐标
		@param y2 左下角y坐标
		@param x3 右下角x坐标
		@param y3 右下角y坐标
		*/
		virtual void		Render4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) = 0;
		/**
		@brief 设置渲染坐标
		@param x x坐标
		@param y y坐标
		*/
		virtual void		SetPosition(float x, float y) = 0;
		/**
		@brief 设置渲染坐标
		@param x x坐标
		@param y y坐标
		@param rotation 旋转弧度数
		@param hscale 水平缩放系数
		@param vscale 垂直缩放系数，若该值为0.0f，则取hscale
		*/
		virtual void		SetPositionEx(float x, float y, float rotation, float hscale = 1.0f, float vscale = 0.0f) = 0;
		/**
		@brief 设置渲染坐标
		@param x1 左上角x坐标
		@param y1 左上角y坐标
		@param x2 右下角x坐标
		@param y2 右下角y坐标
		*/
		virtual void		SetPositionStretch(float x1, float y1, float x2, float y2) = 0;
		/**
		@brief 设置渲染坐标
		@param x0 左上角x坐标
		@param y0 左上角y坐标
		@param x1 右上角x坐标
		@param y1 右上角y坐标
		@param x2 左下角x坐标
		@param y2 左下角y坐标
		@param x3 右下角x坐标
		@param y3 右下角y坐标
		*/
		virtual void		SetPosition4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) = 0;
		/**
		@brief 渲染用SetPosition()等函数设置后的精灵，如果精灵不是经常变化位置，用这种方式渲染可以提高渲染效率
		*/
		virtual void		RenderPosition() = 0;

		/**
		@brief 设置渲染纹理，设置后纹理区域自动设为整个纹理
		@param texture 渲染纹理
		*/
		virtual void		SetTexture(ggeTexture *texture) = 0;
		/**
		@brief 获得用于渲染的纹理指针
		@return 用于渲染的纹理指针
		*/
		virtual ggeTexture*	GetTexture() = 0;
		/**
		@brief 设置渲染纹理区域
		@param x x坐标
		@param y y坐标
		@param width 宽度
		@param height 高度
		*/
		virtual void		SetTextureRect(float x, float y, float width, float height) = 0;
		/**
		@brief 获得用于渲染的纹理区域
		@param x x坐标
		@param y y坐标
		@param width 宽度
		@param height 高度
		*/
		virtual void		GetTextureRect(float *x, float *y, float *width, float *height) = 0;
		/**
		@brief 设置渲染颜色
		@param color 渲染颜色
		@param i 要设置的顶点(0~3)，-1则四个顶点都设置为该值
		*/
		virtual void		SetColor(guint32 color, int i = -1) = 0;
		/**
		@brief 获得指定的顶点颜色
		@param i 顶点序号
		@return 顶点颜色
		*/
		virtual guint32		GetColor(int i = 0) = 0;	
		/**
		@brief 设置Z轴
		@param z 0.0f～1.0f，0表示最上层，1表示最下层
		@param i 要设置的顶点(0~3)，-1则四个顶点都设置为该值
		*/
		virtual void		SetZ(float z, int i = -1) = 0;
		/**
		@brief 获得Z轴
		@param i 顶点序号
		@return Z轴
		*/
		virtual float		GetZ(int i = 0) = 0;
		/**
		@brief 设置混合模式
		@param blend 混合模式，可用"|"结合
		@see BLEND_MODE
		*/
		virtual void		SetBlendMode(int blend) = 0;
		/**
		@brief 获得混合模式
		@return 混合模式
		*/
		virtual int			GetBlendMode() = 0;
		/**
		@brief 设置锚点
		@param x x坐标
		@param y y坐标
		*/
		virtual void		SetHotSpot(float x, float y) = 0;
		/**
		@brief 获得锚点坐标
		@param x x坐标
		@param y y坐标
		*/
		virtual void		GetHotSpot(float *x, float *y) = 0;
		/**
		@brief 设置纹理翻转属性
		@param bX 水平翻转
		@param bY 垂直翻转
		@param bHotSpot 是否翻转原点
		*/
		virtual void		SetFlip(bool bX, bool bY, bool bHotSpot = false) = 0;
		/**
		@brief 获得翻转模式属性
		@param bX 水平翻转
		@param bY 垂直翻转
		*/
		virtual void		GetFlip(bool *bX, bool *bY) = 0;
		
		/**
		@brief 获得宽度
		@return 宽度
		*/
		virtual float		GetWidth() = 0;
		/**
		@brief 获得高度
		@return 高度
		*/
		virtual float		GetHeight() = 0;
		/**
		@brief 获得四边形数据
		@return 四边形数据
		*/
		virtual ggeQuad&	GetQuad() = 0;

		/**
		@brief 获得精灵的包围盒
		@param rect 保存包围盒矩形至该参数
		@param x 包围盒中心点x坐标
		@param y 包围盒中心点y坐标
		@return 包围盒矩形
		*/
		virtual ggeRect*	GetBoundingBox(ggeRect *rect, float x, float y) = 0;
		/**
		@brief 获得旋转和翻转后的精灵包围盒
		@param rect 保存包围盒矩形至该参数
		@param x 包围盒中心点x坐标
		@param y 包围盒中心点y坐标
		@param rotation 旋转弧度数,0.0f设为默认
		@param hscale 水平缩放系数,1.0f设为默认
		@param vscale 垂直缩放系数,1.0f设为默认
		@return 包围盒矩形
		*/
		virtual ggeRect*	GetBoundingBoxEx(ggeRect *rect, float x, float y, float rotation, float hscale, float vscale) = 0;
	};

	/**
	@brief 创建精灵
	@param texture 精灵使用的纹理
	@param x 纹理x坐标
	@param y 纹理y坐标
	@param width 纹理宽度
	@param height 纹理高度
	@return 成功返回ggeSprite指针，否则返回0
	*/
	GGE_EXPORT ggeSprite*	 Sprite_Create(ggeTexture *texture, float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f);
}