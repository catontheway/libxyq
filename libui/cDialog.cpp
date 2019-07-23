#include "cDialog.h"
#include "uiPad.h"

class cDialogButton : public cNode
{
public:
	static cDialogButton* create(const std::string& text) { CREATE(cDialogButton, text); }

	void setWidth(float w)
	{
		_sprite->setContentSize(w, _sprite->getContentSize().height);
		this->setContentSize(_sprite->getContentSize());
	}
protected:
	bool init(const std::string& text)
	{
		if (!cNode::init())
		{
			return false;
		}
		this->addChild(_sprite = cSprite::create(ccu::uDialogSelect));
		_sprite->setVisible(false);

		this->addChild(_text = cText::create());
		_text->setColor(_color);
		_text->setString(_textStr = text);
		_vText.x = 8;
		_vText.y = 2;
		Size size(_vText * 2 + _text->getContentSize());
		float h = _sprite->getContentSize().height;
		if (_text->getContentSize().height > h)
		{
			_sprite->load(ccu::uEdgeSross);
			_sprite->set9(true);
			_sprite->setContentSize(size);
			
		}
		else
		{
			_sprite->set9(true);
			_sprite->setContentSize(size.width, h);
			_vText.y = (h - _text->getContentSize().height) / 2;
		}
		_text->setPosition(_vText);
		this->setContentSize(_sprite->getContentSize());
		
		
		this->setSnatchNode(true);
		return true;
	}


	void setState(eMouseState state)
	{
		_text->setPosition(_vText + ((state == eMouseState::Down) ? Vec2(1, 1) : Vec2::ZERO));
		_sprite->setVisible(state == eMouseState::Cross || state == eMouseState::Down);
		if (_sprite->isVisible())
		{
			_text->setColor(s565::YELLOW);
			_text->setString(_textStr);
		}
		else
		{
			_text->setColor(_color);
			_text->setString(_textStr);
		}
	}

	Vec2 _vText;
	s565 _color = s565::RED;
	std::string _textStr;
	cSprite* _sprite = nullptr;
	cText* _text = nullptr;
};

static const int s_edge = 8;
bool cDialog::init()
{
	if (!cNode::init())
	{
		return false;
	}

	this->setContentSize(cc::vsSize());

	cSprite* spriteDialog = cSprite::create(ccu::uDialog);
	_vDialog = cc::vsCenter();
	_vDialog.x -= spriteDialog->getContentSize().width / 2;
	spriteDialog->setPosition(_vDialog);
	spriteDialog->onClick = [this]()
	{
		setVisible(false);
	};

	_sizeDialog = spriteDialog->getContentSize();
	_sizeDialog.width -= s_edge * 2;

	this->addChild(_spriteHead = cSprite::create());
	_spriteHead->setPosition(_vDialog);

	this->addChild(_spriteDialog = spriteDialog);

	cSprite* spriteName = cSprite::create(ccu::uDialogName);
	spriteName->set9(true);
	spriteName->setContentSize(Size(0, spriteName->getContentSize().height));
	spriteName->setPosition(_vDialog.x + s_edge, _vDialog.y - s_edge);
	this->addChild(_spriteName = spriteName);

	this->addChild(_labelName = cLabel::create(" "));
	_labelName->setPosition(spriteName->getPositionX() + s_edge * 2, spriteName->getPositionY() + spriteName->getContentSize().height / 2 - _labelName->getContentSize().height / 2);

	cButtonClose* btnClose = cButtonClose::create();
	this->addChild(btnClose);
	btnClose->setPositionX(_vDialog.x + spriteDialog->getContentSize().width - btnClose->getContentSize().width - uiPad::cClosex);
	btnClose->setPositionY(_vDialog.y + uiPad::cClosex);
	btnClose->onClick = [this]()
	{
		setVisible(false);
	};


	this->addChild(_text = cText::create(_sizeDialog.width));
	_vText = _vDialog + Vec2(s_edge, 24);
	_text->setPosition(_vText);

	this->setSnatchNode(true);
	setVisible(false);
	return true;
}


void cDialog::setClose(bool closeOnClickPad)
{
	_isCloseOnClickPad = closeOnClickPad;
	_spriteDialog->setSnatchNode(closeOnClickPad);
}


void cDialog::setCancel(bool cancel)
{
	_isCancelLast = cancel;
}

void cDialog::load(ulong head, const std::string& name, const std::string& text, const std::vector<std::string>& selects /* =  */, const CB& cb /* = nullptr */)
{
	_spriteHead->load(head);
	_spriteHead->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	_labelName->setString(name);
	_spriteName->setContentSize(_labelName->getContentSize().width + s_edge * 4, _spriteName->getContentSize().height);
	_text->setString(text);

	const int cCancel = 32;
	for (int k = 0; k <= cCancel; ++k)
	{
		this->removeChildByTag(k);
	}

	if (selects.empty())
	{
		_spriteDialog->setSnatchNode(true);
		setVisible(true);
		return;
	}
	_spriteDialog->setSnatchNode(false);
	_buttons.clear();
	cDialogButton* button;
	float wMax = 0;
	float hMax = 0;
	int tag, selectsCount = selects.size();
	for (int k = 0; k < selectsCount; ++k)
	{
		this->addChild(button = cDialogButton::create(selects[k]));
		_buttons.push_back(button);
		wMax = std::max(wMax, button->getContentSize().width);
		hMax = std::max(hMax, button->getContentSize().height);

		if (_isCancelLast && k == selectsCount - 1)
		{
			button->setTag(tag = cCancel);
		}
		else
		{
			button->setTag(tag = k);
		}
		button->onClick = [this, tag, cb, selectsCount, cCancel]()
		{
			if (tag == cCancel)
			{
				if (cb != nullptr && !sTeam::getInstance()->isFighting())
				{
					cb(selectsCount - 1);
				}
				this->setVisible(false);
			}
			else
			{
				if (cb != nullptr && !sTeam::getInstance()->isFighting())
				{
					cb(tag);
				}
				if (_isCloseOnClickPad)
				{
					this->setVisible(false);
				}
			}
		};
	}

	Vec2 v;
	const int inv = 2;
	v.y = _text->getContentSize().height;
	int wEmpty = _sizeDialog.width;
	int hEmpty = _sizeDialog.height - v.y - s_edge;
	int rMax = hEmpty / (hMax + inv);
	int cMax = wEmpty / (wMax + inv);
	int rCount = selectsCount;
	int cCount = 1;
	int squre = 1024;
	int r = rCount, c = cCount;
	while (true)
	{
		if (rCount == 1 || cCount == selectsCount)
		{
			break;
		}
		if (rCount <= rMax && cCount <= cMax && rCount * cCount <= squre)
		{
			squre = rCount * cCount;
			r = rCount;
			c = cCount;
		}
		rCount = std::ceil(selectsCount * 1.0f / (++cCount));
	}

	v += _vText;
	v.y += 4;
	r = (hMax + inv) * r;
	r = hEmpty - r;
	if (r > hMax * 2)
	{
		v.y += r / 3;
	}
	for (int k = 0; k < selectsCount; ++k)
	{
		((cDialogButton*)_buttons[k])->setWidth(wMax);
		_buttons[k]->setPosition(v.x + (k % c) * (wMax + inv), v.y + (k / c) * (hMax + inv));
	}

	this->setVisible(true);
}

void cDialog::load(const sHeadName& headName, const std::string& text, const std::vector<std::string>& selects /* =  */, const CB& cb /* = nullptr */)
{
	load(headName.head, headName.name, text, selects, cb);
}

