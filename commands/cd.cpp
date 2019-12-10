#include "cd.h"
#include <iostream>

using namespace std;

void cd(Env *env, Stmt *stmt)
{
	string filename = stmt->getNextArg();
	if (filename.empty()) {
		cerr << "use: cd filename\n";
		return;
	}
	Node *item = env->wd->findByPath(filename);
	if (item == nullptr) {
		cerr << "cd: no such file or directory: " << filename << "\n";
		return;
	}
	if (item->type != Node::Type::DIRECTORY) {
		cerr << "cd: not a directory: " << filename << "\n";
		return;
	}
	env->wd = (Directory *)item;
}

