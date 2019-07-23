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
\brief 常用宏定义及类声明
*/

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include "ggetypes.h"

/// Galaxy2D Game Engine 名字空间
namespace gge
{
	/// 混合模式
	enum BLEND_MODE
	{
		BLEND_COLORMUL	= 0,												///< 颜色乘
		BLEND_COLORADD	= 1,												///< 颜色加
		BLEND_ALPHAMUL	= 0,												///< alpha乘
		BLEND_ALPHAADD	= 2,												///< alpha加
		BLEND_NOZWRITE	= 0,												///< 关闭Z缓冲
		BLEND_ZWRITE	= 4,												///< 开启Z缓冲
		BLEND_NOTEXFILTER = 0,												///< 关闭纹理过滤
		BLEND_TEXFILTER	= 8,												///< 开启纹理过滤
		BLEND_DEFAULT	= BLEND_COLORMUL|BLEND_ALPHAMUL|BLEND_NOZWRITE,		///< 默认混合模式
		BLEND_DEFAULT_Z	= BLEND_COLORMUL|BLEND_ALPHAMUL|BLEND_ZWRITE,		///< 默认开启Z轴写入混合模式
		BLEND_FORCE32BIT = 0x7FFFFFFF,
	};

	/// Alpha混合模式
	enum ALPHA_BLEND_MODE
	{
		ALPHA_BLEND_DEFAULT		 = 0,	///< 默认值
		ALPHA_BLEND_ZERO         = 1,	///< ( 0, 0, 0, 0 )
		ALPHA_BLEND_ONE          = 2,	///< ( 1, 1, 1, 1 )
		ALPHA_BLEND_SRCCOLOR     = 3,	///< ( Rs, Gs, Bs, As )
		ALPHA_BLEND_INVSRCCOLOR  = 4,	///< ( 1 - Rs, 1 - Gs, 1 - Bs, 1 - As )
		ALPHA_BLEND_SRCALPHA     = 5,	///< ( As, As, As, As )
		ALPHA_BLEND_INVSRCALPHA  = 6,	///< ( 1 - As, 1 - As, 1 - As, 1 - As )
		ALPHA_BLEND_DESTALPHA    = 7,	///< ( Ad, Ad, Ad, Ad )
		ALPHA_BLEND_INVDESTALPHA = 8,	///< ( 1 - Ad, 1 - Ad, 1 - Ad, 1 - Ad )
		ALPHA_BLEND_DESTCOLOR    = 9,	///< ( Rd, Gd, Bd, Ad )
		ALPHA_BLEND_INVDESTCOLOR = 10,	///< ( 1 - Rd, 1 - Gd, 1 - Bd, 1 - Ad )
		ALPHA_BLEND_SRCALPHASAT  = 11,	///< ( f, f, f, 1 ); f = min( As, 1 - Ad )
		ALPHA_BLEND__FORCE32BIT = 0x7FFFFFFF,
	};

	/// Alpha混合掩码
	enum ALPHA_BLEND_MASK
	{
		ALPHA_BLEND_SRC_MASK = 0xF << 28,
		ALPHA_BLEND_DST_MASK = 0xF << 24,
		ALPHA_CHANNEL_SRC_MASK = 0xF << 20,
		ALPHA_CHANNEL_DST_MASK = 0xF << 16,
		ALPHA_CHANNEL_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 生成Alpha混合模式参数，可以与BLEND_MODE参数用"|"结合使用。当指定dstBlend参数时BLEND_ALPHAMUL/BLEND_ALPHAADD将失效，颜色将采用 Color = SrcColor * SrcBlend + DestColor * DestBlend 方式混合。
	inline int GenAlphaBlendModeArg(ALPHA_BLEND_MODE srcBlend, ALPHA_BLEND_MODE dstBlend)
	{
		return srcBlend << 28 | dstBlend << 24;
	}

	/// 生成Alpha通道混合模式参数，可以与BLEND_MODE参数用"|"结合使用，当前渲染目标纹理带Alpha通道时有效。当指定该参数时Alpha将采用 Alpha = SrcAlpha * SrcBlend + DestAlpha * DestBlend 方式混合
	inline int GenAlphaChannelBlendModeArg(ALPHA_BLEND_MODE srcBlend, ALPHA_BLEND_MODE dstBlend)
	{
		return srcBlend << 20 | dstBlend << 16;
	}

	/// 纹理寻址混合模式
	enum TEXTURE_ADDRESS_BLEND_MODE
	{
		TEXTURE_ADDRESS_WRAP = 0,	///< 重叠映射寻址
		TEXTURE_ADDRESS_MIRROR = 1,	///< 镜像纹理寻址
		TEXTURE_ADDRESS_CLAMP = 2,	///< 夹取纹理寻址
	};

	/// 纹理寻址模式掩码
	const int TEXTURE_ADDRESS_MASK = 0x3 << 14;

	/// 生成纹理寻址混合模式参数，可以与BLEND_MODE参数用"|"结合使用
	inline int GenTextureAddressBlendModeArg(TEXTURE_ADDRESS_BLEND_MODE mode)
	{
		return mode << 14;
	}

	/// 纹理格式
	enum TEXTURE_FORMAT
	{
		TEXFMT_UNKNOWN ,
		TEXFMT_A8R8G8B8,		///< 32位ARGB格式纹理
		TEXFMT_X8R8G8B8,		///< 32位XRGB格式纹理

		TEXFMT_A1R5G5B5,		///< A1R5G5B5
		TEXFMT_A4R4G4B4,		///< A4R4G4B4
		TEXFMT_X1R5G5B5,		///< X1R5G5B5
		TEXFMT_X4R4G4B4,		///< X4R4G4B4
		TEXFMT_R5G6B5,			///< R5G6B5
		TEXFMT_R3G3B2,			///< R3G3B2

		TEXFMT_A8,				///< A8
		TEXFMT_L8,				///< L8
		TEXFMT_L16,				///< L16
		TEXFMT_A8L8,			///< A8L8
		TEXFMT_A4L4,			///< A4L4

		TEXFMT_A8B8G8R8,		///< A8B8G8R8
		TEXFMT_X8B8G8R8,		///< X8B8G8R8
		TEXFMT_A8R3G3B2,		///< A8R3G3B2
		TEXFMT_A2R10G10B10,		///< A2R10G10B10
		TEXFMT_A16B16G16R16,	///< A16B16G16R16

		TEXFMT_DXT1,			///< DXT1
		TEXFMT_DXT2,			///< DXT2
		TEXFMT_DXT3,			///< DXT3
		TEXFMT_DXT4,			///< DXT4
		TEXFMT_DXT5,			///< DXT5

		TTEXFMT_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 音频距离模型
	enum AUDIO_DISTANCE_MODEL
	{
		/// 无
		AUDIO_DISTANCE_NONE,
		/**
		@brief 倒数衰减
		@note	Volume = MinDistance / (MinDistance + RolloffFactor * (Distance – MinDistance));
		*/
		AUDIO_DISTANCE_INVERSE,
		/**
		@brief 倒数衰减
		@note	Distance = max(Distance, MinDistance);\n
				Distance = min(Distance, MaxDistance);\n
				Volume = MinDistance / (MinDistance + RolloffFactor * (Distance – MinDistance));\n
		*/
		AUDIO_DISTANCE_INVERSE_CLAMPED,
		/**
		@brief 线性衰减
		@note	Distance = min(Distance, MaxDistance)\n
				Volume = (1 – RolloffFactor * (Distance – MinDistance) / (MaxDistance – Distance))
		*/
		AUDIO_DISTANCE_LINEAR,
		/**
		@brief 线性衰减
		@note	Distance = max(Distance, MinDistance)\n
				Distance = min(Distance, MaxDistance)\n
				Volume = (1 – RolloffFactor * (Distance – MinDistance) / (MaxDistance – MinDistance))
		*/
		AUDIO_DISTANCE_LINEAR_CLAMPED,
		/**
		@brief 指数衰减
		@note	Volume = (Distance / MinDistance) ^ (-RolloffFactor)
		*/
		AUDIO_DISTANCE_EXPONENT,
		/**
		@brief 指数衰减
		@note	Distance = max(Distance, MinDistance)\n
				Distance = min(Distance, MaxDistance)\n
				Volume = (Distance / MinDistance) ^ (-RolloffFactor)
		*/
		AUDIO_DISTANCE_EXPONENT_CLAMPED,
		AUDIO_DISTANCE_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 字体创建模式
	enum FONT_CREATE_MODE
	{
		FONT_MODE_DEFAULT	= 0,	///< 默认
		FONT_MODE_BOLD		= 1,	///< 粗体
		FONT_MODE_BORDER	= 2,	///< 开启描边功能，开启该功能后设置边框颜色函数才有效
		FONT_MODE_MONO		= 4,	///< 关闭抗锯齿功能，用于渲染点阵字体等情况
		FONT_MODE_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 字体排版样式
	enum FONT_ALIGN
	{
		TEXT_LEFT,		///< 左对齐
		TEXT_CENTER,	///< 居中对齐
		TEXT_RIGHT,		///< 右对齐
		TEXT_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 播放模式
	enum ANIMATION_MODE
	{
		ANI_FORWARD		= 0,	///< 向前播放
		ANI_REVERSAL	= 1,	///< 向后播放
		ANI_REPEAT	 	= 2,	///< 往返播放
		ANI_NOREPEAT	= 0,	///< 不往返播放
		ANI_LOOP		= 4,	///< 循环播放
		ANI_NOLOOP		= 0,	///< 不循环
		ANI_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 图元类型
	enum PRIM_TYPE
	{
		PRIM_POINTS			= 1, ///< 画点
		PRIM_LINES			= 2, ///< 画线
		PRIM_TRIPLES		= 3, ///< 画三角形
		PRIM_QUADS			= 4, ///< 画四边形
		PRIM_LINESTRIP		= 5, ///< 画线带
		PRIM_TRIANGLESTRIP	= 6, ///< 画三角带
		PRIM_TRIANGLEFAN	= 7, ///< 画扇形
		PRIM_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 屏幕截图格式
	enum GGE_IMAGE_FORMAT
	{
		IMAGE_JPG, ///< jpg文件
		IMAGE_PNG, ///< png文件
		IMAGE_BMP, ///< bmp文件
		IMAGE_TGA, ///< tga文件
		IMAGE_DXT1,///< dds文件
		IMAGE_DXT3,///< dds文件
		IMAGE_DXT5,///< dds文件
		IMAGE_FORCE32BIT = 0x7FFFFFFF,
	};

	/// PixelShader版本
	enum PIXEL_SHADER_VERSION
	{
		PS_NONE,	///< 不支持PixelShader
		PS_1_1,		///< ps1.1
		PS_1_2,		///< ps1.2
		PS_1_3,		///< ps1.3
		PS_1_4,		///< ps1.4
		PS_2_0,		///< ps2.0
		PS_LAST,
		PS_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 屏幕模式
	enum SCREEN_MODE
	{
		SCREEN_WINDOWED,				///< 窗口模式
		SCREEN_WINDOWED_FULLSCREEN,		///< 窗口全屏模式
		SCREEN_FULLSCREEN,				///< 独占全屏模式
		SCREEN_LAST,
		SCREEN_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 系统状态
	enum GGE_STATE_BOOL_FUN
	{
		GGE_FRAMEFUNC,		///< bool*()	帧函数，可在运行时更改，必须设置,返回true则退出，false继续运行
		GGE_EXITFUNC,		///< bool*()	收到退出消息回调(例如按Alt+F4)，可在运行时更改，返回true则退出，false继续运行
		GGE_FOCUSLOSTFUNC,	///< bool*()	失去焦点回调，可在运行时更改，返回值无用，建议返回false
		GGE_FOCUSGAINFUNC,	///< bool*()	获得焦点回调，可在运行时更改，返回值无用，建议返回false
		GGE_FORCE32BIT_STATE_BF = 0x7FFFFFFF,
	};

	/// 系统状态
	enum GGE_STATE_SYS_VAL
	{
		GGE_HWND,					///< HWND								窗口句柄，当用System_SetState()函数设置时，显示模式强制使用窗口模式，并且所有Input函数以及帧时间相关函数将不可用，主要用于制作游戏编辑器等工具软件(使用方法可参考示例程序sample3)。当用于System_GetState()函数时，如果之前设置过窗口句柄，则返回之前设置的窗口句柄，否则返回引擎创建的窗口的窗口句柄。
		GGE_MESSAGEFUNC,			///< bool*(HWND, UINT, WPARAM, LPARAM)	窗口消息处理函数,如果函数返回true表示该条消息已处理，不会传到默认消息处理函数，可在运行时更改
		GGE_FLUSH_BATCH_FUNC,		///< void*()							引擎内部开始渲染时回调该函数，如果外部渲染自定义图元时做了缓存，可在此时刷新缓存
		GGE_FORCE32BIT_STATE_MF = 0x7FFFFFFF,
	};

	/// 系统状态
	enum GGE_STATE_INT
	{
		GGE_ICON,			///< int	设置图标(资源ID)
		GGE_FPS,			///< int	设置帧率(0:不限制 | >0:限制为该帧率)，可在运行时更改，默认:0
		GGE_SCREENMODE,		///< int	是否全屏模式，可在运行时更改，默认:SCREEN_WINDOWED @see SCREEN_MODE
		GGE_SCREENWIDTH,    ///< int	屏幕宽度，可在运行时更改，默认:640
		GGE_SCREENHEIGHT,   ///< int	屏幕高度，可在运行时更改，默认:480
		GGE_SCREENBPP,		///< int	色深(16/32)，可在运行时更改，默认:32
		GGE_TEXTURESIZE,	///< int	获得纹理最大尺寸，只用于System_GetState()函数
		GGE_PSVERSION,		///< int	PixelShader版本，只用于System_GetState()函数 @see PIXEL_SHADER_VERSION
		GGE_MAXTEXTUREUNITS,///< int	显卡支持的最大纹理单元数，只用于System_GetState()函数
		GGE_CODEPAGE,		///< int	代码页，用于引擎内部编码转换，可在运行时更改，默认:936
		GGE_FORCE32BIT_STATE_I = 0x7FFFFFFF,
	};

	/// 系统状态
	enum GGE_STATE_BOOL
	{
		GGE_HIDEMOUSE,			///< bool	是否隐藏系统鼠标，可在运行时更改，默认:true
		GGE_DEBUGLOG,			///< bool	是否开启调试信息，可在运行时更改，默认:true
		GGE_SUSPEND,			///< bool	非激活状态时是否挂起，默认:false
		GGE_ZBUFFER,			///< bool	是否开启Z缓冲，可在运行时更改，默认:false（注意：如果要用该功能，必须在引擎初始化前将改状态设成true，否则该功能无效）
		GGE_VSYNC,				///< bool	是否开启垂直同步，可在运行时更改，默认:false
		GGE_FORCETEXFILTER,		///< bool	强制开启纹理过滤，可在运行时更改，默认:false
		GGE_FORCE32BITTEXTURE,	///< bool	载入纹理时强制转换成32位纹理(压缩格式除外)，可在运行时更改，默认:true
		GGE_AUDIOINITED,		///< bool	音频引擎是否初始化成功，只用于System_GetState()函数
		GGE_ALPHARENDERTARGET,	///< bool	显卡是否支持带Alpha通道的渲染目标纹理，只用于System_GetState()函数
		GGE_SOUNDEFFECT,		///< bool	声卡是否支持音频效果器，只用于System_GetState()函数
		GGE_FORCE32BIT_STATE_B = 0x7FFFFFFF,
	};

	/// 系统状态
	enum GGE_STATE_CHAR
	{
		GGE_TITLE,			///< char*		设置窗口标题，可在运行时更改
		GGE_LOGNAME,		///< char*		Log文件名，默认:"galaxy2d.log"
		GGE_FORCE32BIT_STATE_C = 0x7FFFFFFF,
	};

	typedef bool (*GGE_MSGFUN)(HWND, UINT, WPARAM, LPARAM);
	typedef bool (*GGE_BOOLFUN)();

	class ggeAnimation;
	class ggeMesh;
	class ggeMusic;
	class ggeParticle;
	class ggeSound;
	class ggeMusic;
	class ggeSoundEffect;
	class ggeSprite;
	class ggeTexture;
	class ggeFont;
	class ggeSwapChain;
	class ggeGuiManager;
	class ggeGuiWindow;
	class ggeGuiButton;
	class ggeGuiCheckButton;
	class ggeGuiEditBox;
	class ggeGuiListBox;
	class ggeGuiSlider;
	class ggeGuiRichText;
	class ggeGuiRenderState;
	class ggeGuiCreateInfo;
	class ggeGuiFactory;
	class ggeGuiLoader;
	class ggeResManager;
	class ggeColor;
	class ggeRect;
	class ggeVector;
	class ggeVector3;
	class ggeMatrix3;
	class ggeMatrix4;
	class ggeShader;

	/// 顶点定义
	struct ggeVertex
	{
		float	x, y;		///< 屏幕坐标
		float	z;			///< Z缓冲(0~1)
		guint32	color;		///< 顶点颜色
		float	tx, ty;		///< 纹理坐标
	};

	/// 三角形数据结构
	struct ggeTriple
	{
		ggeVertex	v[3];		///< 顶点
		ggeTexture	*texture;	///< 纹理
		int			blend;		///< 混合模式
	};

	/// 四边形据结构
	struct ggeQuad
	{
		ggeVertex	v[4];		///< 顶点
		ggeTexture	*texture;	///< 纹理
		int			blend;		///< 混合模式
	};

	/// 裁剪区域矩形
	struct ggeClipRect
	{
		int    x;		///< 左上角x坐标
		int    y;		///< 左上角y坐标
		int    width;	///< 宽度
		int    height;	///< 高度
	};

	/** @name 鼠标按键编码
	*  @{
	*/

	#define GGEK_LBUTTON	0x00
	#define GGEK_RBUTTON	0x01
	#define GGEK_MBUTTON	0x02

	/** @} */

	/** @name 键盘编码
	*  @{
	*/

	#define GGEK_ESCAPE		0x1B
	#define GGEK_BACKSPACE	0x08
	#define GGEK_TAB		0x09
	#define GGEK_ENTER		0x0D
	#define GGEK_SPACE		0x20

	#define GGEK_SHIFT		0x10
	#define GGEK_CTRL		0x11
	#define GGEK_ALT		0x12

	#define GGEK_LWIN		0x5B
	#define GGEK_RWIN		0x5C
	#define GGEK_APPS		0x5D

	#define GGEK_PAUSE		0x13
	#define GGEK_CAPSLOCK	0x14
	#define GGEK_NUMLOCK	0x90
	#define GGEK_SCROLLLOCK	0x91

	#define GGEK_PGUP		0x21
	#define GGEK_PGDN		0x22
	#define GGEK_HOME		0x24
	#define GGEK_END		0x23
	#define GGEK_INSERT		0x2D
	#define GGEK_DELETE		0x2E

	#define GGEK_LEFT		0x25
	#define GGEK_UP			0x26
	#define GGEK_RIGHT		0x27
	#define GGEK_DOWN		0x28

	#define GGEK_0			0x30
	#define GGEK_1			0x31
	#define GGEK_2			0x32
	#define GGEK_3			0x33
	#define GGEK_4			0x34
	#define GGEK_5			0x35
	#define GGEK_6			0x36
	#define GGEK_7			0x37
	#define GGEK_8			0x38
	#define GGEK_9			0x39

	#define GGEK_A			0x41
	#define GGEK_B			0x42
	#define GGEK_C			0x43
	#define GGEK_D			0x44
	#define GGEK_E			0x45
	#define GGEK_F			0x46
	#define GGEK_G			0x47
	#define GGEK_H			0x48
	#define GGEK_I			0x49
	#define GGEK_J			0x4A
	#define GGEK_K			0x4B
	#define GGEK_L			0x4C
	#define GGEK_M			0x4D
	#define GGEK_N			0x4E
	#define GGEK_O			0x4F
	#define GGEK_P			0x50
	#define GGEK_Q			0x51
	#define GGEK_R			0x52
	#define GGEK_S			0x53
	#define GGEK_T			0x54
	#define GGEK_U			0x55
	#define GGEK_V			0x56
	#define GGEK_W			0x57
	#define GGEK_X			0x58
	#define GGEK_Y			0x59
	#define GGEK_Z			0x5A

	#define GGEK_GRAVE		0xC0
	#define GGEK_MINUS		0xBD
	#define GGEK_EQUALS		0xBB
	#define GGEK_BACKSLASH	0xDC
	#define GGEK_LBRACKET	0xDB
	#define GGEK_RBRACKET	0xDD
	#define GGEK_SEMICOLON	0xBA
	#define GGEK_APOSTROPHE	0xDE
	#define GGEK_COMMA		0xBC
	#define GGEK_PERIOD		0xBE
	#define GGEK_SLASH		0xBF

	#define GGEK_NUMPAD0	0x60
	#define GGEK_NUMPAD1	0x61
	#define GGEK_NUMPAD2	0x62
	#define GGEK_NUMPAD3	0x63
	#define GGEK_NUMPAD4	0x64
	#define GGEK_NUMPAD5	0x65
	#define GGEK_NUMPAD6	0x66
	#define GGEK_NUMPAD7	0x67
	#define GGEK_NUMPAD8	0x68
	#define GGEK_NUMPAD9	0x69

	#define GGEK_MULTIPLY	0x6A
	#define GGEK_DIVIDE		0x6F
	#define GGEK_ADD		0x6B
	#define GGEK_SUBTRACT	0x6D
	#define GGEK_DECIMAL	0x6E

	#define GGEK_F1			0x70
	#define GGEK_F2			0x71
	#define GGEK_F3			0x72
	#define GGEK_F4			0x73
	#define GGEK_F5			0x74
	#define GGEK_F6			0x75
	#define GGEK_F7			0x76
	#define GGEK_F8			0x77
	#define GGEK_F9			0x78
	#define GGEK_F10		0x79
	#define GGEK_F11		0x7A
	#define GGEK_F12		0x7B

	/** @} */
}
