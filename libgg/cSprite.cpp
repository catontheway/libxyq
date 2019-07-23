#include "cSprite.h"

cSprite::cSprite() : _sprite(nullptr)
{

}

cSprite::~cSprite()
{
	if(_sprite != nullptr)
	{
		if(_sprite->GetTexture() != nullptr)
		{
			_sprite->GetTexture()->Release();
		}
		_sprite->Release();
	}
}

bool cSprite::setTexture(Texture2D *texture)
{
	setRender(true);
	if (_sprite != nullptr)
	{
		_sprite->SetTexture(texture);
		setContentSize(_sprite->GetWidth(), _sprite->GetHeight());
	}
	else
	{
		_sprite = gge::Sprite_Create(texture);
	}
	return true;
}

Texture2D* cSprite::getTexture()
{
	if (_sprite == nullptr)
	{
		return nullptr;
	}
	return _sprite->GetTexture();
}



void cSprite::onColor(uchar opacity, uchar r, uchar g, uchar b)
{
	if(_sprite != nullptr)
	{
		_sprite->SetColor(gge::Color_ARGB(opacity, r, g, b));
	}
}

void cSprite::onTransform(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y)
{
	if(_sprite != nullptr)
	{
		_sprite->SetPosition4V(x1, y1, x2, y2, x3, y3, x4, y4);
	}
}

void cSprite::onRender(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y)
{
	if(_sprite != nullptr)
	{
		_sprite->RenderPosition();
	}
}