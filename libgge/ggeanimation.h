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
\brief 动画模块
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 动画模块
	class ggeAnimation : public ggeRefCounter
	{
	public:
		/**
		@brief 复制动画
		@param ani 源动画
		*/
		virtual void		Copy(ggeAnimation *ani) = 0;
		/**
		@brief 返回当前动画的一个副本
		@return 当前动画的一个副本
		*/
		virtual ggeAnimation*	Clone() = 0;

		/**
		@brief 开始播放动画
		*/
		virtual void		Play() = 0;
		/**
		@brief 停止播放动画
		*/
		virtual void		Stop() = 0;
		/**
		@brief 继续播放动画
		*/
		virtual void		Resume() = 0;
		/**
		@brief 刷新动画
		@param dt 上一帧所用时间，可用Timer_GetDelta()获得
		*/
		virtual void		Update(float dt) = 0;
		/**
		@brief 是否正在播放
		@return 正在播放返回true，否则返回false
		*/
		virtual bool		IsPlaying() = 0;

		/**
		@brief 设置播放模式
		@param mode 播放模式，可用"|"结合，默认为：ANI_FORWARD|ANI_LOOP
		$see ANIMATION_MODE
		*/
		virtual void		SetMode(int mode) = 0;
		/**
		@brief 获得播放模式
		@return 播放模式
		*/
		virtual int			GetMode() = 0;
		/**
		@brief 设置帧率
		@param fps 帧率
		*/
		virtual void		SetSpeed(int fps) = 0;
		/**
		@brief 获得帧率 
		@return 帧率
		*/
		virtual int			GetSpeed() = 0;
		/**
		@brief 设置当前动画帧
		@param n 当前动画帧
		*/
		virtual void		SetFrame(int n) = 0;
		/**
		@brief 获得当前动画帧
		@return 当前动画帧
		*/
		virtual int			GetFrame() = 0;

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
		@brief 添加帧精灵
		@param spr 精灵
		@param n 帧数，-1表示添加最后一帧
		*/
		virtual void		AddFrameSprite(ggeSprite *spr, int n = -1) = 0;
		/**
		@brief 返回帧精灵
		@param n 帧数
		@return 返回帧精灵，如果取不到返回0
		*/
		virtual ggeSprite*	GetFrameSprite(int n) = 0;
		/**
		@brief 删除帧精灵
		@param n 帧数,-1表示删除全部精灵
		*/
		virtual void		DelFrameSprite(int n = -1) = 0;
		/**
		@brief 返回动画帧总数  
		@return 返回动画帧总数
		*/
		virtual int			GetFrameCount() = 0;

		/**
		@brief 获得动画宽度
		@return 动画宽度
		*/
		virtual float		GetWidth() = 0;
		/**
		@brief 获得动画高度
		@return 动画高度
		*/
		virtual float		GetHeight() = 0;

		/**
		@brief 获得动画的包围盒
		@param rect 保存包围盒矩形至该参数
		@param x 包围盒中心点x坐标
		@param y 包围盒中心点y坐标
		@return 包围盒矩形
		*/
		virtual ggeRect*	GetBoundingBox(ggeRect *rect, float x, float y) = 0;
		/**
		@brief 获得旋转和翻转后的动画包围盒
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
	@brief 创建动画
	@return 成功返回ggeAnimation指针，否则返回0
	*/
	GGE_EXPORT ggeAnimation*  Animation_Create();
}