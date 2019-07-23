#pragma once
#include "cSprite.h"

class cTag : public cSprite
{
public:
	static cTag* create(const std::string& text, float second){ CREATE(cTag, text, second); }

protected:
	virtual bool init(const std::string& text, float second);

public:
	void updateOnce(float dt);
};


class cTagManager
{
public:
	static cTagManager* getInstance();

	bool add(Node* parent, const std::string& text, float second);

	bool remove(cTag* tag);

private:
	std::list<cTag*> _tags;
};