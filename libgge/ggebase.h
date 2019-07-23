/*
**  =======================================================
**                Galaxy2D Game Engine       
**                                
**       版权所有(c) 2005 沈明. 保留所有权利.
**    主页地址: http://www.cnblogs.com/jianguhan/
**			 电子邮箱: jianguhan@126.com
**  =======================================================
*/

/** \file
\brief 基础函数
*/

#pragma once
#include "ggecommon.h"

namespace gge
{
	/// 引擎版本号
	#define GGE_VERSION 42

	/** @name 基础函数
	*  @{
	*/

	/**
	@brief 创建引擎
	@param ver 版本号
	@return 成功返回true，失败返回false
	*/
	GGE_EXPORT bool			 Engine_Create(int ver = GGE_VERSION);
	/**
	@brief 释放引擎
	*/
	GGE_EXPORT void			 Engine_Release();

	/**
	@brief 初始化系统
	@return 成功返回true，失败返回false
	@note 系统未初始化前只有System_SetState函数有效
	*/
	GGE_EXPORT bool			 System_Initiate();
	/**
	@brief 系统开始运行
	@return 正常结束返回true，否则返回false
	@note 运行该函数前必须设置帧函数
	*/
	GGE_EXPORT bool			 System_Start();

	/**
	@brief 设置系统状态
	@param state 状态
	@param value 状态值
	*/
	GGE_EXPORT void			 System_SetState(GGE_STATE_INT state, int value);
	/**
	@brief 设置系统状态
	@param state 状态
	@param value 状态值
	*/
	GGE_EXPORT void			 System_SetState(GGE_STATE_BOOL state, bool value);
	/**
	@brief 设置系统状态
	@param state 状态
	@param value 状态值
	*/
	GGE_EXPORT void			 System_SetState(GGE_STATE_CHAR state, const char *value);
	/**
	@brief 设置系统状态
	@param state 状态
	@param value 状态值
	*/
	GGE_EXPORT void			 System_SetState(GGE_STATE_BOOL_FUN state, GGE_BOOLFUN value);
	/**
	@brief 设置系统状态
	@param state 状态
	@param value 状态值
	*/
	GGE_EXPORT void			 System_SetState(GGE_STATE_SYS_VAL state, const void *value);

	/**
	@brief 返回系统状态
	@param state 状态
	*/
	GGE_EXPORT int			 System_GetState(GGE_STATE_INT state);
	/**
	@brief 返回系统状态
	@param state 状态
	*/
	GGE_EXPORT bool			 System_GetState(GGE_STATE_BOOL state);
	/**
	@brief 返回系统状态
	@param state 状态
	*/
	GGE_EXPORT const char*	 System_GetState(GGE_STATE_CHAR state);
	/**
	@brief 返回系统状态
	@param state 状态
	*/
	GGE_EXPORT GGE_BOOLFUN	 System_GetState(GGE_STATE_BOOL_FUN state);
	/**
	@brief 返回系统状态
	@param state 状态
	*/
	GGE_EXPORT void*		System_GetState(GGE_STATE_SYS_VAL state);

	/**
	@brief 写入调试Log
	@param format log记录
	*/
	GGE_EXPORT void			 System_Log(const char *format, ...);
	/**
	@brief 运行外部可执行文件或打开URL
	@param url 可执行文件或URL
	*/
	GGE_EXPORT bool			 System_Launch(const char *url);

	/**
	@brief 读取资源文件
	@param filename 资源文件名
	@param size 读取文件成功后将文件大小写入该参数
	@return 读取成功返回资源内存指针，否则返回0
	@note 该函数优先读取绑定的文件包内的文件
	*/
	GGE_EXPORT char*		 Resource_Load(const char *filename, guint32 *size = 0);
	/**
	@brief 读取资源文件到指定的内存中
	@param filename 资源文件名
	@param buf 用于保存资源文件的内存
	@param size 内存大小，如果小于文件大小读取将会失败
	@return 读取成功返回实际读取的字节数，读取失败返回0
	@note 该函数优先读取绑定的文件包内的文件
	*/
	GGE_EXPORT guint32		 Resource_LoadTo(const char *filename, char *buf, guint32 size);
	/**
	@brief 获取资源文件大小
	@param filename 资源文件名
	@return 资源文件大小
	@note 该函数优先读取绑定的文件包内的文件
	*/
	GGE_EXPORT guint32		 Resource_GetSize(const char *filename);
	/**
	@brief 检测资源文件是否存在
	@param filename 资源文件名
	@return 资源文件存在返回true，否则返回false
	*/
	GGE_EXPORT bool			 Resource_IsExist(const char *filename);
	/**
	@brief 释放资源
	@param buf Resource_Load()函数载入的资源
	*/
	GGE_EXPORT void			 Resource_Free(const char *buf);
	/**
	@brief 绑定文件包，文件包可以用引擎附带的文件打包工具生成，也可以是一个zip压缩文件
	@param filename 文件名
	@param password 密码
	@return 绑定成功返回true，否则返回false
	@note 若有多个文件包，依次绑定即可。搜索文件时从第一个绑定文件包开始查找文件，如果找到立即返回，忽略后面文件包中的同名文件。
	*/
	GGE_EXPORT bool			 Resource_AttachPack(const char *filename, const char *password = 0);
	/**
	@brief 移除文件包
	@param filename 文件名
	*/
	GGE_EXPORT void			 Resource_RemovePack(const char *filename = 0);
	/**
	@brief 添加资源文件搜索路径
	若Resource_Load()函数在当前目录无法找到资源文件，会尝试从搜索路径中查找文件，搜索路径可添加多个但不可删除
	@param pathname 资源搜索路径
	*/
	GGE_EXPORT void			 Resource_AddPath(const char *pathname);

	/**
	@brief 设置用于操作的ini文件，如果配置文件在但前目录下要在文件名前加"./"，例如：Ini_SetFile("./cfg.ini")
	@param filename 文件名
	@note 配置文件格式:\n
	;注释\n
	[字段名]\n
	键名=键值\n
	*/
	GGE_EXPORT void			 Ini_SetFile(const char *filename);
	/**
	@brief 将int类型值写入配置文件
	@param section 字段名
	@param name 键名
	@param value 键值
	*/
	GGE_EXPORT void			 Ini_SetInt(const char *section, const char *name, int value);
	/**
	@brief 获得int类型值
	@param section 字段名
	@param name 键名
	@param def_val 默认值
	@return 如果找到指定的键值返回该值否则返回defval
	*/
	GGE_EXPORT int			 Ini_GetInt(const char *section, const char *name, int def_val);
	/**
	@brief 将float类型值写入配置文件
	@param section 字段名
	@param name 键名
	@param value 键值
	*/
	GGE_EXPORT void			 Ini_SetFloat(const char *section, const char *name, float value);
	/**
	@brief 获得float类型值
	@param section 字段名
	@param name 键名
	@param def_val 默认值
	@return 如果找到指定的键值返回该值否则返回defval
	*/
	GGE_EXPORT float		 Ini_GetFloat(const char *section, const char *name, float def_val);
	/**
	@brief 将字符串写入配置文件
	@param section 字段名
	@param name 键名
	@param value 键值
	*/
	GGE_EXPORT void			 Ini_SetString(const char *section, const char *name, const char *value);
	/**
	@brief 获得字符串 
	@param section 字段名
	@param name 键名
	@param def_val 默认值
	@return 如果找到指定的键值返回该值否则返回defval(注意，字符串不能超过255个英文字符，否则超过的部分将被丢弃)
	*/
	GGE_EXPORT const char*	 Ini_GetString(const char *section, const char *name, const char *def_val);

	/**
	@brief 游戏启动后经过的时间，每帧刷新一次，精确到1毫秒
	@return 返回游戏时间
	*/
	GGE_EXPORT guint32		 Timer_GetTime();
	/**
	@brief 返回实时时间，一帧内两次调用该函数，返回值可能不同，精确到1毫秒
	@return 返回当前时间
	*/
	GGE_EXPORT guint32		 Timer_GetTick();
	/**
	@brief 返回上一帧所用时间
	@return 返回上一帧所用时间，精确到0.001秒
	*/
	GGE_EXPORT float		 Timer_GetDelta();
	/**
	@brief 返回帧率
	@return 返回帧率
	*/
	GGE_EXPORT int			 Timer_GetFPS();

	/**
	@brief 创建一个独立的随机数生成器，以防止被其他因素干扰
	@return 随机数生成器ID
	*/
	GGE_EXPORT guint32		 Random_Create();
	/**
	@brief 设置随机数种子
	@param seed 随机数种子
	@param rid 随机数生成器ID，为0时表示默认生成器
	*/
	GGE_EXPORT void			 Random_Seed(guint32 seed, guint32 rid = 0);
	/**
	@brief 返回int类型随机数
	@param min 最小值
	@param max 最大值
	@param rid 随机数生成器ID，为0时表示默认生成器
	@return min到max间的随机数，包括min和max
	*/
	GGE_EXPORT int			 Random_Int(int min, int max, guint32 rid = 0);
	/**
	@brief 返回float类型随机数
	@param min 最小值
	@param max 最大值
	@param rid 随机数生成器ID，为0时表示默认生成器
	@return min到max间的随机数，包括min和max
	*/
	GGE_EXPORT float		 Random_Float(float min, float max, guint32 rid = 0);
	/**
	@brief 创建一个独立的随机数生成器(Mersenne Twister)，以防止被其他因素干扰
	@return 随机数生成器ID
	*/
	GGE_EXPORT guint32		 Random_CreateMt();
	/**
	@brief 设置随机数种子(Mersenne Twister)
	@param seed 随机数种子
	@param rid 随机数生成器ID，为0时表示默认生成器
	*/
	GGE_EXPORT void			 Random_SeedMt(guint32 seed, guint32 rid = 0);
	/**
	@brief 返回int类型随机数(Mersenne Twister)
	@param min 最小值
	@param max 最大值
	@param rid 随机数生成器ID，为0时表示默认生成器
	@return min到max间的随机数，包括min和max
	*/
	GGE_EXPORT int			 Random_IntMt(int min, int max, guint32 rid = 0);
	/**
	@brief 返回unsigned int类型随机数(Mersenne Twister)
	@param min 最小值
	@param max 最大值
	@param rid 随机数生成器ID，为0时表示默认生成器
	@return min到max间的随机数，包括min和max
	*/
	GGE_EXPORT guint32		 Random_UIntMt(guint32 min, guint32 max, guint32 rid = 0);
	/**
	@brief 返回float类型随机数(Mersenne Twister)
	@param min 最小值
	@param max 最大值
	@param rid 随机数生成器ID，为0时表示默认生成器
	@return min到max间的随机数，包括min，不包括max
	*/
	GGE_EXPORT float		 Random_FloatMt(float min, float max, guint32 rid = 0);

	/**
	@brief 以指定颜色清除屏幕
	@param color 清除屏幕颜色
	*/
	GGE_EXPORT void			 Graph_Clear(guint32 color = 0xFF000000);
	/**
	@brief 开始渲染
	@param texture 若该纹理为渲染目标纹理，则渲染到该纹理，否则渲染到默认渲染目标
	@return 调用成功返回true
	*/
	GGE_EXPORT bool			 Graph_BeginScene(ggeTexture *texture = 0);
	/**
	@brief 结束渲染
	@param bPresent 是否渲染后台缓冲区到屏幕，如果设置了渲染目标纹理，该参数无效
	*/
	GGE_EXPORT void			 Graph_EndScene(bool bPresent = true);
	/**
	@brief 复制渲染后台缓冲区
	@param texture 复制后台缓冲区内容到此纹理(必须是渲染目标纹理)
	@param srcRt 后台缓冲区要复制的区域，为0时表示所有区域
	@param destRt 目标纹理区域，为0时表示所有区域
	*/
	GGE_EXPORT bool			 Graph_CopyBackBuffer(ggeTexture *texture, ggeRect *srcRt = 0, ggeRect *destRt = 0, bool btFilter = false);
	/**
	@brief 复制渲染目标纹理
	@param src 源纹理
	@param dest 目标纹理
	@param srcRt 源纹理区域，为0时表示所有区域
	@param destRt 目标纹理区域，为0时表示所有区域
	*/
	GGE_EXPORT bool			 Graph_CopyRanderTarget(ggeTexture *src, ggeTexture *dest, ggeRect *srcRt = 0, ggeRect *destRt = 0, bool btFilter = false);
		/**
	@brief 设置当前Shader
	@param shader 要设置的Shader，如果为0则清除当前Shader
	*/
	GGE_EXPORT void			 Graph_SetCurrentShader(ggeShader *shader = 0);
	/**
	@brief 返回当前Shader
	*/
	GGE_EXPORT ggeShader*	 Graph_GetCurrentShader();
	/**
	@brief 从点(x1,y1)至(x2,y2)画线
	@param x1 起始点x坐标
	@param y1 起始点y坐标
	@param x2 结束点x坐标
	@param y2 结束点y坐标
	@param color 指定线的颜色
	*/
	GGE_EXPORT void			 Graph_RenderLine(float x1, float y1, float x2, float y2, guint32 color = 0xFFFFFFFF);
	/**
	@brief 从点(x1,y1)至(x2,y2)画矩形
	@param x1 起始点x坐标
	@param y1 起始点y坐标
	@param x2 结束点x坐标
	@param y2 结束点y坐标
	@param color 指定线的颜色
	*/
	GGE_EXPORT void			 Graph_RenderRect(float x1, float y1, float x2, float y2, guint32 color = 0xFFFFFFFF);
	/**
	@brief 画三角形
	@param triple 三角形数据 
	*/
	GGE_EXPORT void			 Graph_RenderTriple(const ggeTriple &triple);
	/**
	@brief 画四边形
	@param quad 四边形数据 
	*/
	GGE_EXPORT void			 Graph_RenderQuad(const ggeQuad &quad);

	/**
	@brief 渲染自定义图元(该函数会增加DrawCall)
	@param primType 图元类型
	@param vt 顶点数组
	@param primNum 图元数量
	@param tex 渲染图元时使用的纹理
	@param blend 纹理混合模式，可用"|"结合
	@see PRIM_TYPE
	@see BLEND_MODE
	*/
	GGE_EXPORT void					Graph_RenderBatch(PRIM_TYPE primType, const ggeVertex *vt, int primNum, ggeTexture *tex = 0, int blend = BLEND_DEFAULT);
	/**
	@brief 渲染自定义索引图元(该函数会增加DrawCall)
	@param primType 图元类型，不支持 PRIM_POINTS, PRIM_QUADS
	@param vt 顶点数组
	@param vertexNum 顶点数量
	@param indices 索引数组
	@param primNum 图元数量
	@param tex 渲染图元时使用的纹理
	@param blend 纹理混合模式，可用"|"结合
	@see PRIM_TYPE
	@see BLEND_MODE
	*/
	GGE_EXPORT void					Graph_RenderBatchIndices(PRIM_TYPE primType, const ggeVertex *vt, int vertexNum, const guint16 *indices, int primNum, ggeTexture *tex = 0, int blend = BLEND_DEFAULT);
	/**
	@brief 设置剪裁区域并压栈(该函数会增加DrawCall)
	@param rt 剪裁区域
	*/
	GGE_EXPORT void					Graph_PushClipRect(const ggeClipRect &rt);
	/**
	@brief 返回剪裁区域，如果之前没有设置过剪裁区域则返回0
	*/
	GGE_EXPORT const ggeClipRect*	 Graph_GetClipRect();
	/**
	@brief 弹出当前剪裁区域，恢复上一个剪裁区域，如果栈中没有剩余的剪裁区域，则关闭裁剪功能(该函数会增加DrawCall)
	*/
	GGE_EXPORT void					Graph_PopClipRect();
	/**
	@brief 返回已设置的裁剪区域数量
	*/
	GGE_EXPORT guint32				Graph_GetClipRectCount();
	/**
	@brief 设置变换矩阵并压栈(该函数使用CPU计算顶点坐标，不会增加DrawCall)
	@param mat 变换矩阵
	*/
	GGE_EXPORT void					Graph_PushTransformMatrix(const ggeMatrix4 &mat);
	/**
	@brief 返回变换矩阵，如果之前没有设置过变换矩阵则返回0
	*/
	GGE_EXPORT const ggeMatrix4*	Graph_GetTransformMatrix();
	/**
	@brief 弹出当前变换矩阵，恢复上一个变换矩阵
	*/
	GGE_EXPORT void					Graph_PopTransformMatrix();
	/**
	@brief 返回已设置的变换矩阵数量
	*/
	GGE_EXPORT guint32				Graph_GetTransformMatrixCount();
	/**
	@brief 设置视图矩阵并压栈(该函数会增加DrawCall)
	@param dx x坐标偏移量 
	@param dy y坐标偏移量 
	@param hscale 横坐标缩放比例
	@param vscale 纵坐标缩放比例
	@param rot 旋转角度(单位:弧度)
	@param hx 中心点x坐标
	@param hy 中心点y坐标
	*/
	GGE_EXPORT void					Graph_PushViewTransform(float dx, float dy, float hscale = 1.0f, float vscale = 1.0f, float rot = 0.0f, float hx = 0.0f, float hy = 0.0f); 
	/**
	@brief 设置视图矩阵并压栈(该函数会增加DrawCall)
	@param mat 视图矩阵
	*/
	GGE_EXPORT void					Graph_PushViewMatrix(const ggeMatrix4 &mat);
	/**
	@brief 返回视图矩阵
	*/
	GGE_EXPORT const ggeMatrix4&	Graph_GetViewMatrix();
	/**
	@brief 弹出当前视图矩阵，恢复上一个视图矩阵(该函数会增加DrawCall)
	*/
	GGE_EXPORT void					Graph_PopViewMatrix();
	/**
	@brief 返回已设置的视图矩阵数量
	*/
	GGE_EXPORT guint32				Graph_GetViewMatrixCount();
	/**
	@brief 设置投影矩阵并压栈(该函数会增加DrawCall)
	@param mat 投影矩阵
	*/
	GGE_EXPORT void					Graph_PushProjectionMatrix(const ggeMatrix4 &mat);
	/**
	@brief 返回投影矩阵
	*/
	GGE_EXPORT const ggeMatrix4&	Graph_GetProjectionMatrix();
	/**
	@brief 弹出当前投影矩阵，恢复上一个投影矩阵(该函数会增加DrawCall)
	*/
	GGE_EXPORT void					Graph_PopProjectionMatrix();
	/**
	@brief 返回已设置的投影矩阵数量
	*/
	GGE_EXPORT	guint32				Graph_GetProjectionMatrixCount();
	/**
	@brief 保存屏幕截图
	@param filename 保存文件名
	@param imageFormat 文件格式(该函数不支持dds压缩格式)
	*/
	GGE_EXPORT void					Graph_Snapshot(const char *filename, GGE_IMAGE_FORMAT imageFormat = IMAGE_PNG);
	/**
	@brief 获取显示模式数量，调用Engine_Create()函数后有效
	*/
	GGE_EXPORT int					Graph_GetDisplayModeCount();
	/**
	@brief 获取显示模式，调用Engine_Create()函数后有效
	*/
	GGE_EXPORT void					Graph_GetDisplayMode(int index, int &width, int &height);
	/**
	@brief 获取渲染批次数
	*/
	GGE_EXPORT int					Graph_GetDrawnBatches();

	/**
	@brief 设置全局最大音量
	@param volume 全局最大音量，范围0～100
	*/
	GGE_EXPORT void					Audio_SetMaxVolume(float volume);
	/**
	@brief 返回全局最大音量
	*/
	GGE_EXPORT float				Audio_GetMaxVolume();
	/**
	@brief 设置监听器位置
	@param position 监听器位置(右手坐标系)
	*/
	GGE_EXPORT void					Audio_SetListenerPosition(const ggeVector3 &position);
	/**
	@brief 返回监听器位置
	*/
	GGE_EXPORT const ggeVector3&	Audio_GetListenerPosition();
	/**
	@brief 设置监听器速度
	@param velocity 监听器速度
	*/
	GGE_EXPORT void					Audio_SetListenerVelocity(const ggeVector3 &velocity);
	/**
	@brief 返回监听器速度
	*/
	GGE_EXPORT const ggeVector3&	Audio_GetListenerVelocity();
	/**
	@brief 设置监听器方向
	@param forward 前方向，默认(0, 0, -1)
	@param up 上方向，默认(0, 1, 0)
	*/
	GGE_EXPORT void					Audio_SetListenerOrientation(const ggeVector3 &forward, const ggeVector3 &up);
	/**
	@brief 返回监听器前方向
	*/
	GGE_EXPORT const ggeVector3&	Audio_GetListenerOrientationForward();
	/**
	@brief 返回监听器上方向
	*/
	GGE_EXPORT const ggeVector3&	Audio_GetListenerOrientationUp();
	/**
	@brief 设置多普勒系数
	@param scale 多普勒系数，默认1，值越大影响越大
	*/
	GGE_EXPORT void					Audio_SetDopplerScale(float scale);
	/**
	@brief 返回多普勒系数
	*/
	GGE_EXPORT float				Audio_GetDopplerScale();
	/**
	@brief 设置距离模型
	@param model 距离模型，默认 AUDIO_DISTANCE_INVERSE_CLAMPED
	@see AUDIO_DISTANCE_MODEL
	*/
	GGE_EXPORT void					Audio_SetDistanceModel(AUDIO_DISTANCE_MODEL model);
	/**
	@brief 返回距离模型
	*/
	GGE_EXPORT AUDIO_DISTANCE_MODEL Audio_GetDistanceModel();

	/**
	@brief 获得鼠标X坐标
	@return 鼠标X坐标
	*/
	GGE_EXPORT float 		 Input_GetMousePosX();
	/**
	@brief 获得鼠标Y坐标
	@return 鼠标Y坐标
	*/
	GGE_EXPORT float 		 Input_GetMousePosY();
	/**
	@brief 设置鼠标位置
	@param x 鼠标x轴坐标
	@param y 鼠标y轴坐标
	*/
	GGE_EXPORT void			 Input_SetMousePos(float x, float y);
	/**
	@brief 获得鼠标滚轮位移
	@return 鼠标滚轮位移
	*/
	GGE_EXPORT int			 Input_GetMouseWheel();
	/**
	@brief 鼠标是否在窗口内
	@return 如果鼠标在窗口内返回true，否则返回false
	*/
	GGE_EXPORT bool			 Input_IsMouseOver();
	/**
	@brief 是否有按键正被按住
	@param key 要检测的键盘编码
	@return 有则返回true，否则返回false
	*/
	GGE_EXPORT bool			 Input_IsKeyPress(int key);
	/**
	@brief 是否有按键抬起
	@param key 要检测的键盘编码
	@return 有则返回true，否则返回false
	*/
	GGE_EXPORT bool			 Input_IsKeyUp(int key);
	/**
	@brief 是否有按键按下
	@param key 要检测的键盘编码
	@return 有则返回true，否则返回false
	*/
	GGE_EXPORT bool			 Input_IsKeyDown(int key);
	/**
	@brief 是否有鼠标按键正被按住
	@param key 要检测的鼠标按键编码
	@return 有则返回true，否则返回false
	*/
	GGE_EXPORT bool			 Input_IsMousePress(int key);
	/**
	@brief 是否有鼠标按键抬起
	@param key 要检测的鼠标按键编码
	@return 有则返回true，否则返回false
	*/
	GGE_EXPORT bool			 Input_IsMouseUp(int key);
	/**
	@brief 是否有鼠标按键按下
	@param key 要检测的鼠标按键编码
	@return 有则返回true，否则返回false
	*/
	GGE_EXPORT bool			 Input_IsMouseDown(int key);
	/**
	@brief 返回当前按下的按键的键值
	@return 当前按下的按键的键值，若无键按下返回-1
	@note 可以像如下方式使用该函数：\n
	\code switch (Input_GetKey())
	{
	case GGEK_A:
		fnt->Print(0.0f, 0.0f, "A Key Down!");
		break;
	} \endcode
	*/
	GGE_EXPORT int			 Input_GetKey();
	/**
	@brief 返回当前输入的字符或字符串
	@return 当前输入的字符或字符串,支持中文输入法
	*/
	GGE_EXPORT const char*	 Input_GetChar();
	/**
	@brief 返回按键名字
	@return 按键名字
	*/
	GGE_EXPORT const char*	 Input_GetKeyName(int key);


	/** @} */
}

