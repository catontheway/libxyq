#pragma once
#include "2d/CCActionInstant.h"
#include "2d/CCActionCatmullRom.h"
#include "2d/CCActionEase.h"
#include "2d/CCActionTween.h"
#include "2d/CCActionEase.h"
#include "2d/CCComponent.h"
#include "2d/CCComponentContainer.h"

#include "base/CCDirector.h"
#include "base/CCScheduler.h"

USING_NS_CC;
namespace cc
{
	////////////////////////////////////////////////////////////////////////// getNowSec
// 	inline double getNowSec()
// 	{
// 		timeval nowtime;
// 		cocos2d::gettimeofday(&nowtime, nullptr);
// 		return (long long)(nowtime.tv_sec) + nowtime.tv_usec / 1000000.0f;
// 	}


	template<typename T> // ¿ªÇø¼ä
	inline T random(T min, T max) { return cocos2d::random(min, max); }
	inline int random() { return cocos2d::random(0, 99); }

	inline Vec2 vsOrigin(){ return Director::getInstance()->getVisibleOrigin(); }
	inline Size vsSize() { return Director::getInstance()->getVisibleSize(); }
	inline Size vsSize(float x_0_1, float y_0_1)
	{
		Size size = Director::getInstance()->getVisibleSize();
		size.width *= x_0_1;
		size.height *= y_0_1;
		return size;
	}
	inline Vec2 vsAt(float x_0_1, float y_0_1){ return vsOrigin() + vsSize(x_0_1, y_0_1); }
	inline Vec2 vsCenter(){ return vsOrigin() + vsSize() / 2; }
	inline Vec2 vsRand(){ return vsAt(random(0.0f, 1.0f), random(0.0f, 1.0f)); }
	inline float vsX(float x_0_1){ return vsOrigin().x + vsSize().width * x_0_1; }
	inline float vsY(float y_0_1){ return vsOrigin().y + vsSize().height * y_0_1; }
	inline bool isVisible(Node* node)
	{
		do 
		{
			if (node == nullptr || !node->isVisible())
			{
				return false;
			}
			node = node->getParent();
		} 
		while (true);
		return true;
	}
}