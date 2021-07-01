#pragma once

#include <string>

class Error
{
private:
public:
	static void fatal(std::string error);
};