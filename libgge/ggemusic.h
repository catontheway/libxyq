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
\brief音乐模块
*/

#pragma once
#include "ggerefcounter.h"
#include "ggemath.h"
#include "ggecommon.h"

namespace gge
{
	/// 音乐模块
	class ggeMusic : public ggeRefCounter
	{
	public:
		/**
		@brief 播放
		@param offset 起始偏移时间(单位:秒)
		*/
		virtual void	Play(float offset = 0) = 0;	
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
		@brief 设置重复播放时间点
		@param startTime 循环起始时间(单位:秒)，默认0
		@param endTime 循环结束时间(单位:秒)，当播放到该位置时跳到startTime处继续播放，而不是从头播放，为0时设置为音乐结束时间
		*/
		virtual void	SetLoopTime(float startTime, float endTime = 0) = 0;
		/**
		@brief 返回循环播放起始时间(单位:秒)
		*/
		virtual float	GetLoopStartTime() = 0;
		/**
		@brief 返回循环播放结束时间(单位:秒)
		*/
		virtual float	GetLoopEndTime() = 0;
		/**
		@brief 返回当前播放时间(单位:秒)
		*/
		virtual float	GetPlayingTime() = 0;
		/**
		@brief 返回时长(单位:秒)
		*/
		virtual float	GetDuration() = 0;

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
		@brief 设置频率
		@param pitch 设置频率，范围0～10，1表示原始频率
		*/
		virtual void	SetPitch(float pitch) = 0;
		/**
		@brief 返回频率
		*/
		virtual float	GetPitch() = 0;

		/**
		@brief 设置音源坐标是否是相对坐标 
		@param bRelative 设为true时音源坐标为相对于监听器的坐标
		*/
		virtual void	SetRelativeToListener(bool bRelative) = 0;
		/**
		@brief 返回音源坐标是否是相对坐标
		*/
		virtual bool	IsRelativeToListener() = 0;
		/**
		@brief 设置音源坐标 
		@param position 音源坐标
		*/
		virtual void	SetPosition(const ggeVector3 &position) = 0;
		/**
		@brief 返回音源坐标
		*/
		virtual const ggeVector3& GetPosition() = 0;
		/**
		@brief 设置音源速度
		@param velocity 音源速度
		*/
		virtual void	SetVelocity(const ggeVector3 &velocity) = 0;
		/**
		@brief 返回音源速度
		*/
		virtual const ggeVector3& GetVelocity() = 0;
		/**
		@brief 设置音源方向
		@param direction 音源方向
		*/
		virtual void	SetDirection(const ggeVector3 &direction) = 0;
		/**
		@brief 返回音源方向
		*/
		virtual const ggeVector3& GetDirection() = 0;
		/**
		@brief 设置音锥参数
		@param innerAngle 内锥角度，默认360
		@param outerAngle 外锥角度，默认360
		@param outerVolume 外锥音量，范围0～1，默认0
		@param outerHighGain 高频音量，范围0～10，默认1
		*/
		virtual void	SetCone(float innerAngle, float outerAngle, float outerVolume, float outerHighGain = 1.0f) = 0;
		/**
		@brief 返回音锥参数
		@param innerAngle 内锥角度
		@param outerAngle 外锥角度
		@param outerVolume 外锥音量
		@param outerHighGain 高频音量
		*/
		virtual void	GetCone(float &innerAngle, float &outerAngle, float &outerVolume, float &outerHighGain) = 0;
		/**
		@brief 设置音源最小距离
		@param distance 音源最小距离
		*/
		virtual void	SetMinDistance(float distance) = 0;
		/**
		@brief 返回音源最小距离
		*/
		virtual float	GetMinDistance() = 0;
		/**
		@brief 设置音源最大距离
		@param distance 音源最大距离
		*/
		virtual void	SetMaxDistance(float distance) = 0;
		/**
		@brief 返回音源最大距离
		*/
		virtual float	GetMaxDistance() = 0;
		/**
		@brief 设置音源音量衰减速度
		@param factor 音源衰减速度，越大衰减越快，默认1
		*/
		virtual void	SetRolloffFactor(float factor) = 0;
		/**
		@brief 返回音源音量衰减速度
		*/
		virtual float	GetRolloffFactor() = 0;
		/**
		@brief 设置音源空气吸收率
		@param factor 音源空气吸收率，越大高频衰减越快，范围0~10，默认0
		*/
		virtual	void	SetAirAbsorptionFactor(float factor) = 0;
		/**
		@brief 返回音源空气吸收率
		*/
		virtual float	GetAirAbsorptionFactor() = 0;

		/**
		@brief 添加音效器
		@param effect 音效器，如果添加数量超过音源最大音效器数量，返回false @see SoundEffect_GetMaxEffectsPerSound
		*/
		virtual	bool	AddEffect(ggeSoundEffect *effect) = 0;
		/**
		@brief 移除音效器
		@param effect 音效器
		*/
		virtual bool	RemoveEffect(ggeSoundEffect *effect) = 0;
		/**
		@brief 清除音效器
		*/
		virtual void	ClearEffect() = 0;
		/**
		@brief 返回音效器数量
		*/
		virtual int		GetEffectCount() = 0;
		/**
		@brief 返回音效器
		*/
		virtual ggeSoundEffect*	GetEffect(int n) = 0;
	};

	/**
	@brief 载入音乐文件
	@param filename 音乐文件名，支持文件格式：wave, ogg, mp3
	@param size 内存大小，为0时从文件载入音乐，否则将filename做为音乐文件在内存中的地址，该值指示这块内存的大小，从内存中载入音效
	@return 成功返回ggeMusic指针，否则返回0
	@note	1.音乐模块每次播放时都会从头开始播放，但是占用内存比较小，适用于播放游戏背景音乐等情况
			2.必须是单声道音乐文件才可以使用3D音效功能\n
			3.3D音效功能使用的是右手坐标系
	*/
	GGE_EXPORT ggeMusic* Music_Load(const char *filename, guint32 size = 0);
}