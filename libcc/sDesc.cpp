#include "sDesc.h"

const bool sDescs::isValid() const
{
	return !(uhead == sDesc::INVALID_UID && name.empty() && descs.empty());
}

void sDescs::clear()
{
	uhead = sDesc::INVALID_UID;
	name.clear();
	descs.clear();
}

void sDescs::push(const sDesc& desc)
{
	descs.push_back(desc);
}

void sDescs::push(const std::string& text, const s565& color)
{
	sDesc desc;
	desc.text = text;
	desc.color = color;
	push(desc);
}