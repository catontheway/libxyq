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
\brief 音效器模块
*/

#pragma once
#include "ggerefcounter.h"
#include "ggevariant.h"

namespace gge
{
	/// 音效器类型
	enum SOUND_EFFECT_TYPE
	{
		EFFECT_NONE,			///< 无
		EFFECT_REVERB,			///< 混响
		EFFECT_CHORUS,			///< 合唱
		EFFECT_DISTORTION,		///< 失真
		EFFECT_ECHO,			///< 回声
		EFFECT_FLANGER,			///< 镶边
		EFFECT_MODULATOR,		///< 调制
		EFFECT_COMPRESSOR,		///< 压缩
		EFFECT_EQUALIZER,		///< 均衡
		EFFECT_LAST,
		EFFECT_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 音效器参数
	enum SOUND_EFFECT_PARAMETER
	{
		SEP_REVERB_GAIN,		///< 范围0~1，默认0.32
		SEP_REVERB_HFGAIN,		///< 范围0~1，默认0.89
		SEP_REVERB_DENSITY,		///< 范围0~1，默认1
		SEP_REVERB_DIFFUSION,	///< 范围0~1，默认1
		SEP_REVERB_DECAY,		///< 范围0.1~20，默认1.49
		SEP_REVERB_HFDECAY,		///< 范围0.1~2，默认0.83
		SEP_REVERB_EARLYGAIN,	///< 范围0~3.16，默认0.05
		SEP_REVERB_EARLYDELAY,	///< 范围0~3，默认0.007
		SEP_REVERB_LATEGAIN,	///< 范围0~10，默认1.26
		SEP_REVERB_LATEDELAY,	///< 范围0~0.1，默认0.011
		SEP_REVERB_ROLLOFF,		///< 范围0~10，默认0
		SEP_REVERB_AIRHFGAIN,	///< 范围0.892~1.0，默认0.994
		SEP_REVERB_HFLIMITER,	///< 范围true/false，默认true

		SEP_CHORUS_WAVEFORM,	///< 范围 WAVE_SINE / WAVE_TRIANGLE，默认 WAVE_TRIANGLE
		SEP_CHORUS_PHASE,		///< 范围(int)-180~180，默认90
		SEP_CHORUS_RATE,		///< 范围0~10，默认1.1
		SEP_CHORUS_DEPTH,		///< 范围0~1，默认0.1
		SEP_CHORUS_FEEDBACK,	///< 范围-1~1，默认0.25
		SEP_CHORUS_DELAY,		///< 范围0~0.016，默认0.016
									 
		SEP_DISTORTION_GAIN,	///< 范围0.01~1，默认0.05
		SEP_DISTORTION_EDGE,	///< 范围0~1，默认0.2
		SEP_DISTORTION_LOWCUT,	///< 范围80~24000，默认8000
		SEP_DISTORTION_EQCENTER,///< 范围80~24000，默认3600
		SEP_DISTORTION_EQBAND,	///< 范围80~24000，默认3600
									 
		SEP_ECHO_DELAY,			///< 范围0~0.2，默认0.1
		SEP_ECHO_LRDELAY,		///< 范围0~0.4，默认0.1
		SEP_ECHO_DAMPING,		///< 范围0~0.99，默认0.5
		SEP_ECHO_FEEDBACK,		///< 范围0~1，默认0.5
		SEP_ECHO_SPREAD,		///< 范围-1~1，默认-1
									 
		SEP_FLANGER_WAVEFORM,	///< 范围 WAVE_SINE / WAVE_TRIANGLE，默认 WAVE_TRIANGLE
		SEP_FLANGER_PHASE,		///< 范围(int)-180~180，默认0
		SEP_FLANGER_RATE,		///< 范围0~10，默认0.27
		SEP_FLANGER_DEPTH,		///< 范围0~1，默认1
		SEP_FLANGER_FEEDBACK,	///< 范围-1~1，默认-0.5
		SEP_FLANGER_DELAY,		///< 范围0~0.004，默认0.002
									 
		SEP_MODULATOR_WAVEFORM,	///< 范围 WAVE_SINE / WAVE_SAWTOOTH/WAVE_SQUARE，默认 WAVE_TRIANGLE
		SEP_MODULATOR_FREQ,		///< 范围0~8000，默认440
		SEP_MODULATOR_HIGHCUT,	///< 范围0~24000，默认800
									 
		SEP_COMPRESSOR_ENABLE,	///< 范围ture/false，默认true
									 
		SEP_EQUALIZER_LOWGAIN,	///< 范围0.126~7.943，默认1
		SEP_EQUALIZER_LOWCUT,	///< 范围50~800，默认200
		SEP_EQUALIZER_MID1GAIN,	///< 范围0.126~7.943，默认1
		SEP_EQUALIZER_MID1FREQ,	///< 范围200~3000，默认500
		SEP_EQUALIZER_MID1BAND,	///< 范围0.01~1，默认1
		SEP_EQUALIZER_MID2GAIN,	///< 范围0.126~7.943，默认1
		SEP_EQUALIZER_MID2FREQ,	///< 范围1000~8000，默认3000
		SEP_EQUALIZER_MID2BAND,	///< 范围0.01~1，默认1
		SEP_EQUALIZER_HIGHGAIN,	///< 范围0.126~7.943，默认1
		SEP_EQUALIZER_HIGHCUT,	///< 范围4000~16000，默认6000

		SEP_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 音效器波形类型
	enum SOUND_EFFECT_WAVEFORM
	{
		WAVE_SINE,			///< 正弦波
		WAVE_TRIANGLE,		///< 三角波
		WAVE_SAWTOOTH,		///< 锯齿波
		WAVE_SQUARE,		///< 方波
		WAVE_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 音效器模块
	class ggeSoundEffect : public ggeRefCounter
	{
	public:
		/**
		@brief 设置音效器类型
		@param type 音效器类型
		*/
		virtual void				SetType(SOUND_EFFECT_TYPE type) = 0;
		/**
		@brief 返回音效器类型
		*/
		virtual SOUND_EFFECT_TYPE	GetType() = 0;
		/**
		@brief 设置音效器参数
		@param par 音效器参数 @see SOUND_EFFECT_PARAMETER
		@param var 音效器数值 
		*/
		virtual void				SetParameter(SOUND_EFFECT_PARAMETER par, ggeVariant var) = 0;
		/**
		@brief 返回音效器参数
		*/
		virtual ggeVariant			GetParameter(SOUND_EFFECT_PARAMETER par) = 0;
		/**
		@brief 设置音效器音量
		@param v 音效器音量
		*/
		virtual void				SetVolume(float v) = 0;
		/**
		@brief 返回音效器音量
		*/
		virtual float				GetVolume() = 0;
		/**
		@brief 用当前设置的参数激活音效器
		@param b 为true时激活音效器,false为取消激活，如果激活的音效器超过最大支持的音效器数量，返回false @see SoundEffect_GetMaxEffectsSupported
		@note 音效器激活后可设置到多个音效上，如果激活后修改了音效器的类型或参数，需要重新激活，新的设置才会生效
		*/
		virtual bool				SetActive(bool b) = 0;
		/**
		@brief 返回音效器是否激活
		*/
		virtual bool				IsActive() = 0;
	};

	/**
	@brief 创建音效器，如果声卡不支持音效器，返回0 @see GGE_SOUNDEFFECT
	*/
	GGE_EXPORT ggeSoundEffect* SoundEffect_Create();
	/**
	@brief 返回声卡最大支持的音效器数量(可激活音效器的最大数量)
	*/
	GGE_EXPORT int SoundEffect_GetMaxEffectsSupported();
	/**
	@brief 返回单个音源可设置的最大音效器数量
	*/
	GGE_EXPORT int SoundEffect_GetMaxEffectsPerSound();
	/**
	@brief 返回当前已激活的音效器数量
	*/
	GGE_EXPORT int SoundEffect_GetActiveEffectCount();
}