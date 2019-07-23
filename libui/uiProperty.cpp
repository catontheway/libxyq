#include "uiProperty.h"


uiProperty::uiProperty()
{
	std::fill(_points.begin(), _points.end(), nullptr);
}

bool uiProperty::init(Node* parent, int px, int py, int px2, int iy)
{
#define ccc_label_create(_label_)\
parent->addChild(_label_ = cLabel::create("0xFFFF"));\
	_label_->setColor(s565::BLACK)

	// 等级
	ccc_label_create(_labelLv);

	// 名字
	ccc_label_create(_labelName);
	// 气血
	ccc_label_create(_labelHp);
	// 魔法
	ccc_label_create(_labelMp);
	// 愤怒
	ccc_label_create(_labelAp);

	// 命中
	ccc_label_create(_labelHit);
	// 攻击
	ccc_label_create(_labelAtk);
	// 防御
	ccc_label_create(_labelDef);
	// 速度
	ccc_label_create(_labelSpeed);
	// 灵力
	ccc_label_create(_labelMana);
	// 躲避 
	ccc_label_create(_labelEvade);


	// 属性点 体质
	ccc_label_create(_labelBody);
	_labelBody->setPosition(px, py);
	// 属性点 魔力
	ccc_label_create(_labelMag);
	_labelMag->setPosition(px, py + 1 * iy);
	// 属性点 力量
	ccc_label_create(_labelStr);
	_labelStr->setPosition(px, py + 2 * iy);
	// 属性点 耐力
	ccc_label_create(_labelDex);
	_labelDex->setPosition(px, py + 3 * iy);
	// 属性点 敏捷
	ccc_label_create(_labelAgi);
	_labelAgi->setPosition(px, py + 4 * iy);
	// 属性点 剩余
	ccc_label_create(_labelRemian);
	_labelRemian->setPosition(px, py + 5 * iy);

	// 经验
	ccc_label_create(_labelExp);
	ccc_label_create(_labelExpMax);

#undef ccc_label_create
	// 按钮 加减点
	forr(_buttonAdds, k)
	{
		parent->addChild(_buttonAdds[k] = cButton::create(ccu::uAdd));
		parent->addChild(_buttonSubs[k] = cButton::create(ccu::uSub));
// 		_buttonAdds[k]->setTag(k);
// 		_buttonSubs[k]->setTag(k);
		_buttonAdds[k]->setKeep2Click(true);
		_buttonSubs[k]->setKeep2Click(true);
		_buttonAdds[k]->setPosition(px2, py + k * iy);
		_buttonSubs[k]->setPosition(px2 + _buttonAdds[k]->getContentSize().width + 2, py + k * iy);
		_buttonAdds[k]->onClick = [this, k]()
		{
			auto& point = _pro.point;
			ePoint e = (ePoint)k;
			if (!point.add(e, true))
			{
				return;
			}
			point.add(e, false);
			_pointShow.get(e) = point.get(e) + _pros.point.get(e);
			_isPointed = true;
			updatePoint();
		};
		_buttonSubs[k]->onClick = [this, k]()
		{
			auto& point = _pro.point;
			ePoint e = (ePoint)k;
			if (!point.sub(e, true))
			{
				return;
			}
			point.sub(e, false);
			_pointShow.get(e) = point.get(e) + _pros.point.get(e);
			_isPointed = true;
			updatePoint();
		};
	}

	// 按钮 确定加点
	parent->addChild(_buttonSure = cButton::create2("加点"));
	_buttonSure->setDesc("支持长按");
	_buttonSure->onClick = [this]()
	{
		if (_isPointed && !sTeam::getInstance()->isFighting() && onPoint != nullptr)
		{
			onPoint(0, _pro.point);
		}
	};
	return true;
}

void uiProperty::load(const sProperty& pro)
{
	_pro = pro;
	ccp::apply(_pros, pro);
	_pointShow = pro.point + _pros.point;
	forv(_points, k)
	{
		_points[k] = &_pro.point.get((ePoint)k);
	}
	load();
}


void uiProperty::load()
{
	// 等级
	_labelLv->setString(_pro.lv);
	// 等级
	_labelName->setString(_pro.name);
	// 命中
	const auto& attr = _pros.attr;
	_labelHit->setString(attr.hit);
	// 攻击
	_labelAtk->setString(attr.atk);
	// 防御
	_labelDef->setString(attr.def);
	// 速度
	_labelSpeed->setString(attr.speed);
	// 灵力
	_labelMana->setString(attr.mana);
	// 躲避 
	_labelEvade->setString(attr.evade);

	// 气血
	int hpMax = (int)attr.hpMax;
	if (_pro.ispet)
	{
		_labelHp->setString(toString("%d/%d", _pro.hp, hpMax));
	}
	else
	{
		_labelHp->setString(toString("%d/%d/%d", _pro.hp, _pro.hp2, hpMax));
	}
	// 魔法
	int mpMax = (int)attr.mpMax;
	_labelMp->setString(toString("%d/%d", _pro.mp, mpMax));
	// 愤怒
	_labelAp->setString(toString("%d/%d", _pro.ap, sAttribute::cAp150));


	_labelExp->setString(_pro.exp);
	_labelExpMax->setString(sExp::getExp(_pro.lv + 1, _pro.ispet));

	updatePoint();
}




void uiProperty::updatePoint()
{
	// 属性点 体质
	_labelBody->setString(_pointShow.body);
	// 属性点 魔力
	_labelMag->setString(_pointShow.mag);
	// 属性点 力量
	_labelStr->setString(_pointShow.str);
	// 属性点 耐力
	_labelDex->setString(_pointShow.dex);
	// 属性点 敏捷
	_labelAgi->setString(_pointShow.agi);
	// 属性点 剩余
	_labelRemian->setString(_pro.point.remain);

	forv(_buttonAdds, k)
	{
		_buttonAdds[k]->setEnabled(_points[k] != nullptr && _pro.point.remain > 0);
		_buttonSubs[k]->setEnabled(_points[k] != nullptr && *_points[k] > 0);
	}
}
