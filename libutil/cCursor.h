#pragma once
// 光标
enum class eCursor
{
	// 平时
	Normal,
	// 给予
	Give,
	// ?
	Forbig,
	// 交易
	Trade,
	// 攻击
	Atk,
	// 法术选择(转圈圈)
	Magic,
	// 组队(旗)
	Team,
	// 手指?
	Hand,
	// 指挥??
	Guard,
	// 抓捕
	Grab,
	// 不
	No,
};


class cCursor
{
public:
	static cCursor* getInstance();

	void setCursor(eCursor e);

	const eCursor& getCursor() { return _cursor; }

protected:
	eCursor _cursor = eCursor::Normal;
};


