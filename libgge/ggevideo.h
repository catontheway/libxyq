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
\brief 视频模块
*/

#pragma once
#include "ggerefcounter.h"
#include "ggetypes.h"

namespace gge
{
	class ggeVideo : public ggeRefCounter
	{
	public:
		/**
		@brief 渲染
		@param x x坐标
		@param y y坐标
		*/
		virtual void	Render(float x, float y) = 0;
		/**
		@brief 渲染
		@param x x坐标
		@param y y坐标
		@param rotation 旋转弧度数
		@param hscale 水平缩放系数
		@param vscale 垂直缩放系数，若该值为0.0f，则取hscale
		*/
		virtual void	RenderEx(float x, float y, float rotation, float hscale, float vscale) = 0;
		/**
		@brief 渲染
		@param x1 左上角x坐标
		@param y1 左上角y坐标
		@param x2 右下角x坐标
		@param y2 右下角y坐标
		*/
		virtual void	RenderStretch(float x1, float y1, float x2, float y2) = 0;
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
		virtual void	Render4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) = 0;

		/**
		@brief 播放
		*/
		virtual void	Play() = 0;
		/**
		@brief 暂停播放
		*/
		virtual void	Pause() = 0;
		/**
		@brief 继续播放
		*/
		virtual void	Resume() = 0;
		/**
		@brief 停止播放
		*/
		virtual void	Stop() = 0;
		/**
		@brief 返回是否正在播放
		*/
		virtual bool	IsPlaying() = 0;
		/**
		@brief 返回当前播放时间(单位:秒)
		*/
		virtual float	GetPlayingTime() = 0;

		/**
		@brief 设置重复播放
		@param bLoop 设为true时重复播放
		*/
		virtual void	SetLoop(bool bLoop) = 0;
		/**
		@brief 返回是否重复播放
		*/
		virtual bool	IsLoop() = 0;
		/**
		@brief 设置音量
		@param volume 设置音量，范围0～100
		*/
		virtual void	SetVolume(float volume) = 0;
		/**
		@brief 返回音量
		*/
		virtual float	GetVolume() = 0;
		
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
		@brief 设置锚点
		@param x x坐标
		@param y y坐标
		*/
		virtual void	SetHotSpot(float x, float y) = 0;
		/**
		@brief 获得锚点坐标
		@param x x坐标
		@param y y坐标
		*/
		virtual void	GetHotSpot(float *x, float *y) = 0;

		/**
		@brief 获得宽度
		@return 宽度
		*/
		virtual int		GetWidth() = 0;
		/**
		@brief 获得高度
		@return 高度
		*/
		virtual int		GetHeight() = 0;
	};

	/**
	@brief 载入视频文件
	@param filename 音效文件名，支持文件格式：.ogv
	@return 成功返回ggeVideo指针，否则返回0
	@note	如果要从文件包中载入视频文件，视频文件的后缀名必须是".ogv"，并且使用引擎自带的文件打包工具，否则将读取失败
	*/
	GGE_EXPORT ggeVideo* Video_Load(const char *filename);
}