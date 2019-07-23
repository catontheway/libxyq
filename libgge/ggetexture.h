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
\brief 纹理模块
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 渲染目标纹理类型
	enum TARGET_TYPE
	{
		TARGET_DEFAULT = 0,		///< 默认类型
		TARGET_ZBUFFER = 1,		///< 开启ZBuffer
		TARGET_LOCKABLE = 2,	///< 渲染目标纹理可以被锁定
		TARGET_ALPHA = 4,		///< 渲染目标纹理带Alpha通道(可通过系统状态 GGE_ALPHARENDERTARGET 检测显卡是否支持创建带Alpha通道的渲染目标纹理)
		TARGET_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 纹理
	class ggeTexture : public ggeRefCounter
	{
	public:
		/**
		@brief 锁定纹理
		@param bReadOnly 是否只读(如果不需要写入数据，可将该值设为true以提高效率)
		@param left 设置锁定区域左边位置
		@param top 设置锁定区域上方位置
		@param width 设置锁定区域宽度
		@param height 设置锁定区域高度
		@param pitch 一行数据的长度
		@return 成功返回纹理数据，否则返回0
		@note 1.未设置锁定区域时将锁定整个纹理，为了提高效率锁定纹理时应尽量指定锁定区域\n
		2.根据纹理格式，使用对应的数据结构读取或设置颜色值，例如当纹理格式是TEXFMT_A8R8G8B8时，可以这样读取或设置颜色值：\n
		\code
		guint32 *buf = tex->Lock();
		guint32 color = buf[y * textureWidth + x]; 
		buf[y * textureWidth + x] = newColor; 
		\endcode
		其中textureWidth可用GetWidth()函数获得。\n
		3.创建渲染目标纹理时如果指定了TARGET_LOCKABLE，则该纹理也可以Lock
		*/
		virtual guint32* Lock(bool bReadOnly = true, int left = 0, int top = 0, int width = 0, int height = 0, int *pitch = 0) = 0;
		/**
		@brief 解除纹理锁定
		*/
		virtual void	Unlock() = 0;

		/**
		@brief 获得纹理宽度
		@param bOrginal 为true时返回纹理原始宽度，为false时返回纹理在显存宽度
		@return 纹理宽度
		*/
		virtual int		GetWidth(bool bOrginal = false) = 0;
		/**
		@brief 获得纹理高度
		@param bOrginal 为true时返回纹理原始高度，为false时返回纹理在显存高度
		@return 纹理高度
		*/
		virtual int		GetHeight(bool bOrginal = false) = 0;
		/**
		@brief 获得纹理格式
		*/
		virtual TEXTURE_FORMAT GetFormat() = 0;

		/**
		@brief 保存到文件
		@param filename 文件名
		@param imageFormat 文件格式，默认保存为PNG格式图片
		@return 返回保存是否成功
		*/
		virtual bool	SaveToFile(const char *filename, GGE_IMAGE_FORMAT imageFormat = IMAGE_PNG) = 0;
	};

	/**
	@brief 创建纹理
	@param width 纹理宽度
	@param height 纹理高度
	@param format 纹理格式 @see TEXTURE_FORMAT
	@return 成功返回ggeTexture指针，失败返回0
	*/
	GGE_EXPORT ggeTexture*	 Texture_Create(int width, int height, TEXTURE_FORMAT format = TEXFMT_A8R8G8B8);
	/**
	@brief 创建渲染目标纹理
	@param width 纹理宽度
	@param height 纹理高度
	@param targetType 渲染目标纹理类型，可用"|"结合 @see TARGET_TYPE
	@return 成功返回ggeTexture指针，失败返回0
	*/
	GGE_EXPORT ggeTexture*	 Texture_CreateRenderTarget(int width, int height, int targetType = TARGET_DEFAULT);
	/**
	@brief 载入纹理
	@param filename 纹理文件名，支持文件类型：bmp, png, jpg, tga, dds(DXT1-DXT5)
	@param colorKey 颜色键
	@param size 内存大小，为0时从文件载入纹理，否则将filename做为纹理文件在内存中的地址，该值指示这块内存的大小，从内存中载入纹理
	@param format 纹理格式，如果图片不能以该格式载入，则自动转换为TEXFMT_A8R8G8B8格式，当该参数为TEXFMT_UNKNOWN时如果未开启强制纹理转换，会根据图片格式自动设置为最合适的格式
	@return 成功返回ggeTexture指针，失败返回0
	*/
	GGE_EXPORT ggeTexture*	 Texture_Load(const char *filename, guint32 colorKey = 0x00000000, guint32 size = 0, TEXTURE_FORMAT format = TEXFMT_UNKNOWN);
}