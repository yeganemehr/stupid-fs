#ifndef STMT_H
#define STMT_H

#include <string>

class Stmt {
	public:
		Stmt();
		std::string str;
		std::string getNextArg();
	private:
		size_t start = 0;
};

#endif // STMT_H
