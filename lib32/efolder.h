#pragma once
#include <string>
#include <vector>

namespace cc
{
	// depthLimit -1 meas no limit
	// do not use ../
	std::vector<std::string> efolder(const std::string& path, bool isOnlyName, int depthLimit);
}