#include "Stmt.h"

Stmt::Stmt()
{
	start = 0;
}

std::string Stmt::getNextArg()
{
	if (start == std::string::npos) {
		return "";
	}
	size_t lastSpace = str.find(' ', start);
	std::string arg = str.substr(start, lastSpace - start);
	start = (lastSpace == std::string::npos) ? lastSpace : lastSpace + 1;
	return arg;
}
