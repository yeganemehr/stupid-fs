#include "rmdir.h"
#include <iostream>

using namespace std;

bool rmdir(Env *env, Stmt *stmt)
{
	string filename = stmt->getNextArg();
	if (filename.empty()) {
		cerr << "use: rmdir filename\n";
		return false;
	}
	Node *item = env->wd->findByPath(filename);
	if (item == nullptr) {
		cerr << "rmdir: No such file or directory: " << filename << "\n";
		return false;
	}
	if (item->type != Node::Type::DIRECTORY) {
		cerr << "rmdir: failed to remove " << filename << ": Not a directory\n";
		return false;
	}
	Directory *p = (Directory *) item;
	if (!p->isEmpty()) {
		cerr << "rmdir: Directory is not empty: " << filename << "\n";
		return false;
	}
	p = env->wd;
	do {
		if (p == item) {
			cerr << "rmdir: Cannot remove directory in use: " << filename << "\n";
			return false;
		}
		p = p->getParent();
	} while (p != nullptr);
	Directory *parent = item->getParent();
	parent->remove(item);
	delete item;
	return true;
}
