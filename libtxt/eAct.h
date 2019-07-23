#pragma once

// 模型动作
enum class eAct
{
	// 站(地图)
	Stand,
	// 走(地图)
	Walk,
	// 站(战斗)
	Fight,
	// 前进(战斗)
	Go,
	// 攻击(战斗)
	Atk,
	// 攻击2(战斗)
	Atk2,
	// 施法(战斗)
	Magic,
	// 防御(战斗)
	Def,
	// 被打(战斗)
	Suffer,
	// 死亡(战斗)
	Dead,
	// 返回(战斗)
	Back,

	// 大头像
	Big,
	// 小头像
	Small,
	// 对话头像
	Dialog,

	// 攻击(音效)
	eAtk,
	// 攻击2(音效)
	eAtk2,
	// 施法(音效)
	eMagic,
	// 防御(音效)
	eDef,
	// 被打(音效)
	eSuffer,
	// 死亡(音效)
	eDead,

	// 其他
	Amigo,
	HappySmall,
	HappyBig,
	SadSmall,
	SadBig,
	ProudSmall,
	ProudBig,
	// 肢体
	BodyBow,
	BodyCry,
	BodyDance,
	BodyGreet,
	BodySit,
	BodyAngry
};