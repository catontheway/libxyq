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
\brief Shader模块

Shader扩展模块目前只支持PixelShader
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 纹理状态
	enum TEXTURE_STATE
	{
		TEXSTATE_WRAP		= 1,	///< 重叠映射寻址
		TEXSTATE_MIRROR		= 2,	///< 镜像纹理寻址
		TEXSTATE_CLAMP		= 3,	///< 夹取纹理寻址
		TEXSTATE_BORDER		= 4,	///< 边框颜色寻址
		TEXSTATE_FILTER		= 8,	///< 纹理过滤，可以与寻址参数用"|"结合使用
		TEXSTATE_FORCE32BIT = 0x7FFFFFFF,
	};

	/// Shader模块
	class ggeShader : public ggeRefCounter
	{
	public:
		/**
		@brief 设置纹理，调用Graph_SetCurrentShader()函数设置为当前Shader后该函数生效
		@param name 纹理名
		@param tex 纹理
		@param texState 纹理状态
		@param borderColor 边框颜色寻址所用的边框颜色
		@see TEXTURE_STATE
		@return 成功返回true，失败返回false
		*/
		virtual bool SetTexture(const char *name, ggeTexture *tex, guint32 texState = TEXSTATE_WRAP, guint32 borderColor = 0) = 0;
		/**
		@brief 设置float类型值，调用Graph_SetCurrentShader()函数设置为当前Shader后该函数生效
		@param name 变量名
		@param f 变量值
		@return 成功返回true，失败返回false
		*/
		virtual bool SetFloat(const char *name, float f) = 0;
		/**
		@brief 设置float类型数组，调用Graph_SetCurrentShader()函数设置为当前Shader后该函数生效
		@param name 变量名
		@param pf 变量数组
		@param count 变量个数
		@return 成功返回true，失败返回false
		*/
		virtual bool SetFloatArray(const char *name, const float *pf, guint32 count) = 0;

		/**
		@brief 设置纹理，调用Graph_SetCurrentShader()函数设置为当前Shader后该函数生效
		@param startRegister 起始寄存器
		@param tex 纹理
		@param texState 纹理状态
		@param borderColor 边框颜色寻址所用的边框颜色
		@return 成功返回true，失败返回false
		*/
		virtual bool SetTextureEx(guint32 startRegister, ggeTexture *tex, guint32 texState = TEXSTATE_WRAP, guint32 borderColor = 0) = 0;
		/**
		@brief 设置float类型值，调用Graph_SetCurrentShader()函数设置为当前Shader后该函数生效
		@param startRegister 起始寄存器
		@param f 变量值
		@return 成功返回true，失败返回false
		*/
		virtual bool SetFloatEx(guint32 startRegister, float f) = 0;
		/**
		@brief 设置float类型数组，调用Graph_SetCurrentShader()函数设置为当前Shader后该函数生效
		@param startRegister 起始寄存器
		@param pf 变量数组
		@param count 变量个数
		@return 成功返回true，失败返回false
		*/
		virtual bool SetFloatArrayEx(guint32 startRegister, const float *pf, guint32 count) = 0;
	};

	/**
	@brief 载入Shader文件
	@param filename 文件名
	@param function 入口函数名，为0时表示载入已编译的代码
	@param psVersion PixelShader版本
	@return 成功返回ggeShader*，失败返回0
	*/
	GGE_EXPORT ggeShader*	 Shader_Load(const char *filename, const char *function = 0, PIXEL_SHADER_VERSION psVersion = PS_1_1);
	/**
	@brief 从字符串创建Shader
	@param shaderstr shader字符串
	@param function 入口函数名，为0时表示载入已编译的代码
	@param psVersion PixelShader版本
	@return 成功返回ggeShader指针，失败返回0
	*/
	GGE_EXPORT ggeShader*	 Shader_Create(const char *shaderstr, const char *function = 0, PIXEL_SHADER_VERSION psVersion = PS_1_1);
}