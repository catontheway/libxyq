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
\brief 资源管理器
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 资源类型
	enum GGE_RES_TYPE
	{
		GRT_TEXTURE,		///< 纹理
		GRT_SOUND,			///< 音效
		GRT_MUSIC,			///< 音乐
		GRT_SPRITE,			///< 精灵
		GRT_ANIMATION,		///< 动画
		GRT_FONT,			///< 字体
		GRT_PARTICLE,		///< 粒子
		GRT_MESH,			///< 网格
		GRT_STRING,			///< 字符串
		GRT_CUSTOMRES,		///< 自定义资源
		GRT_LAST,
		GRT_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 资源管理器遍历资源回调
	class ggeTraversalResCallBack
	{
	public:
		virtual ~ggeTraversalResCallBack() {}
		/**
		@brief 遍历资源回调
		@param name 资源名
		@param type 资源类型
		@return 如果要中断枚举返回true
		*/
		virtual bool OnTraversalRes(const char *name, GGE_RES_TYPE type) { return false; }
	};

	/// 资源管理器
	class ggeResManager : public ggeRefCounter
	{
	public:
		/**
		@brief 载入资源文件，可以载入多个资源文件，后载入的资源文件中重名的资源将被忽略
		@param filename 资源文件名
		@return 载入成功true,否则返回false
		*/
		virtual bool	LoadResFile(const char *filename) = 0;
		/**
		@brief 预缓存资源
		@return 成功返回true，否则返回false
		*/
		virtual bool	PrepareCache() = 0;
		/**
		@brief 开始载入资源
		@return 返回资源总数
		*/
		virtual int		BeginLoadRes() = 0;
		/**
		@brief 载入下个资源
		@return 成功返回true，失败返回false
		@note 示例：\n
		int ResCount = ResMgr->BeginLoadRes();\n
		for (int i = 1; i <= ResCount; i++) \n
		{\n
			ResMgr->LoadNextRes();\n
			printf("载入进度:%d\n", i * 100 / ResCount);\n
		}\n
		*/
		virtual bool	LoadNextRes() = 0;
		/**
		@brief 清除资源文件以及已载入的资源
		*/
		virtual void	Clear() = 0;
		/**
		@brief 设置垃圾回收时间
		@param gcTime 垃圾回收时间(单位:秒),当gcTime>0时引擎会自动回收超过gcTime未使用的资源，如果gcTime=0则需要手动进行垃圾回收,默认gcTime=60
		*/
		virtual void	SetGarbageCollectTime(float gcTime) = 0;
		/**
		@brief 手动垃圾回收
		@param bForce 为true时回收所有未引用的资源，否则只回收已过期资源
		@note 用于手动清除所有未引用的资源，或者在外部窗口模式下手动回收资源
		*/
		virtual	void	 GarbageCollect(bool bForce = false) = 0;
		/**
		@brief 遍历资源管理器中的资源
		@param callback 资源管理器遍历资源回调
		*/
		virtual void	TraversalRes(ggeTraversalResCallBack *callback) = 0;

		/**
		@brief 返回指定资源名的纹理
		@param name 资源名
		@return 成功返回纹理，失败返回0
		*/
		virtual ggeTexture*		CreateTexture(const char *name) = 0;
		/**
		@brief 返回指定资源名的纹理，如果没找到就用指定的参数创建一个
		@param name 资源名
		@param filename 文件名
		@param colorKey 颜色键
		@return 成功返回纹理，失败返回0
		*/
		virtual ggeTexture*		CreateTextureFromFile(const char *name, const char *filename, guint32 colorKey = 0) = 0;
		/**
		@brief 返回指定资源名的音效
		@param name 资源名
		@return 成功返回音效，失败返回0
		*/
		virtual ggeSound*		CreateSound(const char *name) = 0;
		/**
		@brief 返回指定资源名的音效，如果没找到就创建一个
		@param name 资源名
		@param filename 文件名
		@return 成功返回音效，失败返回0
		*/
		virtual ggeSound*		CreateSoundFromFile(const char *name, const char *filename) = 0;
		/**
		@brief 返回指定资源名的音乐
		@param name 资源名
		@return 成功返回音乐，失败返回0
		*/
		virtual ggeMusic*		CreateMusic(const char *name) = 0;
		/**
		@brief 返回指定资源名的音乐，如果没找到就创建一个
		@param name 资源名
		@param filename 文件名
		@return 成功返回音效，失败返回0
		*/
		virtual ggeMusic*		CreateMusicFromFile(const char *name, const char *filename) = 0;
		/**
		@brief 返回指定资源名的精灵
		@param name 资源名
		@return 成功返回精灵，失败返回0
		*/
		virtual ggeSprite*		CreateSprite(const char *name) = 0;
		/**
		@brief 返回指定资源名的动画
		@param name 资源名
		@return 成功返回动画，失败返回0
		*/
		virtual ggeAnimation*	CreateAnimation(const char *name) = 0;
		/**
		@brief 返回指定资源名的字体
		@param name 资源名
		@return 成功返回字体，失败返回0
		*/
		virtual ggeFont*		CreateFont(const char *name) = 0;
		/**
		@brief 返回指定资源名的字体，如果没找到就用指定的参数创建一个
		@param name 资源名
		@param filename 字体文件名(*.ttf/*.ttc)
		@param size 字体大小，单位：象素
		@param createMode 字体创建模式，可用"|"结合 @see FONT_CREATE_MODE
		@return 成功返回字体，失败返回0
		*/
		virtual ggeFont*		CreateCustomFont(const char *name, const char *filename, int size = 16, int createMode = FONT_MODE_DEFAULT) = 0;
		/**
		@brief 返回指定资源名的字体，如果没找到就用指定的参数创建一个
		@param name 资源名
		@param filename 字体配置文件
		@return 成功返回字体，失败返回0
		*/
		virtual ggeFont*		CreateCustomFontFromImage(const char *name, const char *filename) = 0;
		/**
		@brief 返回指定资源名的粒子系统
		@param name 资源名
		@return 成功返回粒子系统，失败返回0
		*/
		virtual ggeParticle*	CreateParticle(const char *name) = 0;
		/**
		@brief 返回指定资源名的网格
		@param name 资源名
		@return 成功返回网格，失败返回0
		*/
		virtual ggeMesh*		CreateMesh(const char *name) = 0;
		/**
		@brief 返回指定资源名的字符串
		@param name 资源名
		@return 成功返回字符串，失败返回0
		*/
		virtual const char*		GetString(const char *name) = 0;
		/**
		@brief 添加托管的自定义资源
		@param name 资源名
		@param res 托管的资源
		@note 该函数会增加引用计数
		*/
		virtual void			AddCustomRes(const char *name, ggeRefCounter *res) = 0;
		/**
		@brief 返回托管的自定义资源
		@param name 资源名
		@return 成功返回自定义资源，失败返回0
		@note 如果资源管理器开启了垃圾回收机制，托管的资源也会被回收。
		如果托管资源被回收，该函数将返回0，外部需要再次创建该资源并调用AddCustomRes()函数添加到资源管理器
		*/
		virtual ggeRefCounter*	CreateCustomRes(const char *name) = 0;
	};

	/**
	@brief 创建资源管理器
	@return 创建成功返回ggeResManager指针，否则返回0
	*/
	GGE_EXPORT ggeResManager*	 ResManager_Create();
}