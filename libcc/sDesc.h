#pragma once
#include "s565.h"

struct sDesc
{
	static const ulong INVALID_UID = 0;
	std::string text;
	s565 color;
};


struct sDescs
{
	ulong uhead = sDesc::INVALID_UID;
	int wMax = 192;
	std::string name;
	std::vector<sDesc> descs;
	const bool isValid() const;
	void clear();
	void push(const sDesc& desc);
	void push(const std::string& text, const s565& color);
};


