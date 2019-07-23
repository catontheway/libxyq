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
\brief 粒子系统
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"
#include "ggecolor.h"
#include "ggemath.h"

namespace gge
{
	/// 创建粒子系统时默认的最大粒子数
	const int MAX_PARTICLES			= 500;
	/// 用于设置粒子系统运行时间，如果运行时间设为该值，则粒子系统一直保持运行状态
	const float PAR_AGE_INCESSANCY	= -1.0f;
	/// 粒子系统已停止运行
	const float PAR_AGE_STOPPED		= -2.0f;
	/// 用于设置粒子系统状态每秒粒子生成数，如果每秒粒子生成数设成该值，则保持最大粒子生成数
	const int PAR_MAX_EMISSION		= -1;

	/// 粒子系统信息
	struct ggeParticleInfo
	{
		/// 粒子发射器类型
		enum PARTICLE_EMITTER_TYPE
		{
			EMT_POINT,			///< 点发射器
			EMT_RECT,			///< 矩形发射器
			EMT_CIRCLE,			///< 圆形发射器
			EMT_RECT_AREA,		///< 矩形区域发射器
			EMT_CIRCLE_AREA,	///< 圆形区域发射器
		};

		/// 粒子发射器发射方向
		enum PARTICLE_EMITTER_DIR
		{
			EMT_NONE,			///< 不改变初始方向
			EMT_IN,				///< 朝向粒子系统中心点
			EMT_OUT,			///< 背向粒子系统中心点
		};
		
		/// 粒子旋转模式
		enum PARTICLE_EMITTER_SPIN_MODE
		{
			EMT_SPIN_NORMAL,		///< 旋转跟运动方向无关
			EMT_SPIN_EMIT_DIR,		///< 发射时旋转到发射方向
			EMT_SPIN_MOTION_DIR,	///< 跟随运动方向
		};

		ggeParticleInfo() : emitterType(EMT_POINT), emitterDir(EMT_NONE), emitterWidth(0), emitterHeight(0), emission(0), 
			lifetime(0), spinMode(EMT_SPIN_NORMAL), particleLifeMin(0), particleLifeMax(0), direction(0), spread(0), speedMin(0), speedMax(0), 
			radialAccelMin(0), radialAccelMax(0), tangentialAccelMin(0), tangentialAccelMax(0), sizeStart(1.0f), sizeStartVar(0), sizeEnd(1.0f), sizeEndVar(0), 
			spinStart(0), spinStartVar(0), spinEnd(0), spinEndVar(0), colorStart(1.0f, 1.0f, 1.0f, 1.0f), colorEnd(1.0f, 1.0f, 1.0f, 0), 
			colorVar(0), alphaVar(0), fadeColor(1.0f, 1.0f, 1.0f, 1.0f), fadeColorWeight(0), fadeColorVar(0), fadeAlphaVar(0) {}

		int			emitterType;		///< 发射器类型 @see PARTICLE_EMITTER_TYPE
		int			emitterDir;			///< 发射器方向，EMT_POINT发射器无效 @see PARTICLE_EMITTER_DIR
		float		emitterWidth;		///< 发射器宽度，EMT_POINT发射器无效
		float		emitterHeight;		///< 发射器高度，EMT_POINT发射器无效
		
		int			emission;			///< 每秒粒子生成数，若为 PAR_MAX_EMISSION 则保持最大粒子数。如果激活的粒子数超过最大粒子数，将不会生成新的粒子
		float		lifetime;			///< 粒子系统运行时间(秒)，若为 PAR_AGE_INCESSANCY 则持续运行

		float		particleLifeMin;	///< 粒子最小生命期(秒)
		float		particleLifeMax;	///< 粒子最大生命期(秒)

		bool		relative;			///< 如果为true，粒子发射角度受当前粒子系统移动方向影响 
		int			spinMode;			///< 旋转模式 @see PARTICLE_EMITTER_SPIN_MODE
		float		direction;			///< 粒子发射角度(弧度) 
		float		spread;				///< 粒子发射角度偏移量，发射角度取值范围为(direction +/- spread) 

		float		speedMin;			///< 最小起始速度(象素/秒)
		float		speedMax;			///< 最大起始速度(象素/秒)

		ggeVector	gravity;			///< 重力加速度

		float		radialAccelMin;		///< 最小线加速度 
		float		radialAccelMax;		///< 最大线加速度 

		float		tangentialAccelMin;	///< 最小角加速度
		float		tangentialAccelMax;	///< 最大角加速度

		float		sizeStart;			///< 起始尺寸，1.0f表示原始尺寸 
		float		sizeStartVar;		///< 起始尺寸浮动值(sizeStart +/- sizeStartVar)
		float		sizeEnd;			///< 结束尺寸，1.0f表示原始尺寸 
		float		sizeEndVar;			///< 结束尺寸浮动值(sizeEnd +/- sizeEndVar) 

		float		spinStart;			///< 起始旋转速度(弧度) 
		float		spinStartVar;		///< 起始旋转速度浮动值(spinStart +/- spinStartVar)
		float		spinEnd;			///< 结束旋转速度(弧度) 
		float		spinEndVar;			///< 结束旋转速度浮动值(spinEnd +/- spinEndVar)

		ggeColor	colorStart;			///< 起始颜色 
		ggeColor	colorEnd;			///< 结束颜色 
		float		colorVar;			///< 起始颜色浮动值(0.0f～1.0f)
		float		alphaVar;			///< 起始颜色Alpha浮动值(0.0f～1.0f)

		float		fadeColorWeight;	///< 过渡颜色权值，越大表示从起始颜色渐变到过渡颜色所需的时间越长，如果为0表示不使用过渡颜色(0.0f～1.0f)
		ggeColor	fadeColor;			///< 过渡颜色
		float		fadeColorVar;		///< 过渡颜色浮动值(0.0f～1.0f)
		float		fadeAlphaVar;		///< 过渡颜色Alpha浮动值(0.0f～1.0f)
	};

	/// 粒子系统
	class ggeParticle : public ggeRefCounter
	{
	public:
		/**
		@brief 复制粒子系统
		@param par 源粒子系统
		*/
		virtual void				Copy(ggeParticle *par) = 0;
		/**
		@brief 返回当前粒子系统的一个副本
		@return 当前粒子系统的一个副本
		*/
		virtual ggeParticle*		Clone() = 0;

		/**
		@brief 刷新粒子系统
		@param dt 上一帧所用时间，可用Timer_GetDelta()获得
		*/
		virtual void				Update(float dt) = 0;
		/**
		@brief 渲染粒子系统
		*/
		virtual void				Render() = 0;
		/**
		@brief 在指定坐标启动粒子系统
		@param x x坐标
		@param y y坐标
		*/
		virtual void				FireAt(float x, float y) = 0;
		/**
		@brief 启动粒子系统
		*/
		virtual void				Fire() = 0;
		/**
		@brief 停止粒子系统
		@param bKillParticles 是否清除还未消亡的粒子
		*/
		virtual void				Stop(bool bKillParticles = false) = 0;
		/**
		@brief 移动粒子系统到指定位置
		@param x x坐标
		@param y y坐标
		@param bMoveParticles 如果为true，所有活动粒子将被移动，否则只移动粒子系统
		*/
		virtual void				MoveTo(float x, float y, bool bMoveParticles = false) = 0;
		/**
		@brief 获得粒子系统坐标
		@param x x坐标
		@param y y坐标
		*/
		virtual void				GetPosition(float *x, float *y) = 0;
		/**
		@brief 设置粒子系统移动位移
		@param x x坐标
		@param y y坐标
		*/
		virtual void				Transpose(float x, float y) = 0;
		/**
		@brief 获得粒子系统位移量
		@param x x坐标
		@param y y坐标
		*/
		virtual void				GetTransposition(float *x, float *y) = 0;
		/**
		@brief 是否开启粒子系统范围跟踪
		@param bTrack 是否开启粒子系统范围跟踪
		*/
		virtual void				TrackBoundingBox(bool bTrack) = 0;
		/**
		@brief 设置粒子系统信息
		@param info 粒子系统信息
		*/
		virtual void				SetParticleInfo(const ggeParticleInfo &info) = 0;
		/**
		@brief 获得粒子系统设置信息
		@return 粒子系统设置信息
		*/
		virtual ggeParticleInfo&	GetParticleInfo() = 0;
		/**
		@brief 设置精灵
		@param sprite 渲染粒子所用精灵
		*/
		virtual void				SetSprite(ggeSprite *sprite) = 0;
		/**
		@brief 获得精灵
		@return 精灵
		*/
		virtual ggeSprite*			GetSprite() = 0;
		/**
		@brief 设置动画
		@param ani 渲染粒子所用动画
		*/
		virtual void				SetAnimation(ggeAnimation *ani) = 0;
		/**
		@brief 获得动画
		@return 动画
		*/
		virtual ggeAnimation*		GetAnimation() = 0 ;

		/**
		@brief 获得粒子总数
		@return 粒子总数
		*/
		virtual int					GetParticleCount() = 0;
		/**
		@brief 获得活动粒子数
		@return 活动粒子数
		*/
		virtual int					GetParticlesAlive() = 0;
		/**
		@brief 获得粒子系统启动到现在逝去秒数
		@return 如果粒子是持续运行的返回PAR_AGE_INCESSANCY，如果粒子系统已停止则返回PAR_AGE_STOPPED
		*/
		virtual float				GetAge() = 0;
		
		/**
		@brief 获得粒子系统包围盒
		@param rect 粒子系统包围盒
		*/
		virtual ggeRect*			GetBoundingBox(ggeRect *rect) = 0;
	};

	/**
	@brief 创建粒子系统
	@param info 指向一个ggeParticleInfo结构体
	@param maxPSNum 最大粒子数
	@return 成功返回ggeParticle指针，否则返回0
	*/
	GGE_EXPORT ggeParticle*  Particle_Create(const ggeParticleInfo &info, int maxPSNum = MAX_PARTICLES);
}