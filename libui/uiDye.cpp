#include "uiDye.h"
#include "uiManager.h"

bool uiDye::init()
{
	if (!uiPad::init(ccu::uPad, true)) // 0x61E6DAFE
	{
		return false;
	}
	set9(true, 32, 32);
	setContentSize(540, 359);
	setAilgn(eAilgn::Mid);
	

	_randModel = false;
	// 切换 正常/随机 模式
	this->addChild(_buttonMod = cButton::create4("染色模式"));
	_buttonMod->setDesc("随机模式暂无法保存");
 	_buttonMod->setPosition(_contentSize.width / 2 - _buttonMod->getContentSize().width / 2, 2);
	_buttonMod->onClick = [this]()
	{
		_randModel = !_randModel;
		_buttonMod->setString(_randModel ? "随机模式" : "染色模式");
		if (_randModel)
		{
			forr(_button4s, k)
			{
				_button4s[k]->setString("变");
			}
		}
		else
		{
			forr(_button4s, k)
			{
				_button4s[k]->setString("");
			}
		}
	};

	int y = 265, y2 = 295;

	// 左转
	this->addChild(_buttonLeft = cButton::create1("<-"));
	_buttonLeft->setPosition(175, y);
	_buttonLeft->onClick = [this]()
	{
		_sprite->setDirection(false);
	};
	// 右转
	this->addChild(_buttonRight = cButton::create1("->"));
	_buttonRight->setPosition(330, y);
	_buttonRight->onClick = [this]()
	{
		_sprite->setDirection(true);
	};

	// 部位
	this->addChild(_buttonPart = cButton::create4("切换部位"));
	_buttonPart->setPosition(160, y2);
	_buttonPart->onClick = [this]()
	{
		cDyeRender::getInstance()->swtichPart();
	};

	// 确定
	this->addChild(_bottonOk = cButton::create2("确定"));
	_bottonOk->setPosition(240, y2);
	_bottonOk->onClick = [this]()
	{
		cDyeRender::getInstance()->apply();
		doClose();
	};
	// 重置
	this->addChild(_buttonZero = cButton::create4("重置当前"));
	_buttonZero->setPosition(290, y2);
	_buttonZero->onClick = [this]()
	{
		cDyeRender::getInstance()->resetPart();
	};
	// 分段
	cButton* button;
	forr(_button4s, k)
	{
		this->addChild(button = _button4s[k] = cButton::create1());
		button->setPosition(205 + k * 32, y);
		button->setTag(k);
		button->onClick = [this, button]()
		{
			if (_randModel)
			{
				cDyeRender::getInstance()->randMatrix(button->getTag());
			}
			else
			{
				cDyeRender::getInstance()->addMatrix(button->getTag());
			}
		};
	}

	cSprite* spriteShadow = cSprite::create(ccu::uShadow);
	this->addChild(spriteShadow);
	spriteShadow->setPosition(260, 220);

	this->addChild(_sprite = cSprite::create());
	_sprite->setPosition(spriteShadow->getPosition());
	_sprite->play();

	return true;
}

void uiDye::doBind()
{
	cDyeRender::getInstance()->onLoad = [this](const sSp& sp, const std::vector<cDyeRender::sShow>& shows)
	{
		forr(_button4s, k)
		{
			if (k < shows.size())
			{
				_button4s[k]->setVisible(true);
				_button4s[k]->setString(toString("%d/%d", shows.at(k).idx, shows.at(k).total));
			}
			else
			{
				_button4s[k]->setVisible(false);
			}

		}
		_sprite->load(sp);
	};
}
