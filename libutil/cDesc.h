#pragma once
#include "_inc.h"

class cSprite;
class cDesc
{
public:
	void setDesc(const sDescs& descs) { _descs = descs; }

	void setDesc(const std::string& desc, const s565& color = s565::WHITE);

	void showDesc(bool show);

	static void toSpriteDesc(cSprite* sprite, const sDescs& descs);

protected:
	sDescs _descs;
};
