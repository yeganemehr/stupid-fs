#include "rm.h"
#include <iostream>

using namespace std;

bool rm(Env *env, Stmt *stmt)
{
	string filename = stmt->getNextArg();
	if (filename.empty()) {
		cerr << "use: touch filename\n";
		return false;
	}
	Node *item = env->wd->findByPath(filename);
	if (item == nullptr) {
		cerr << "rm: No such file or directory: " << filename << "\n";
		return false ;
	}
	if (item->type == Node::Type::DIRECTORY) {
		Directory *p = (Directory *) item;
		if (!p->isEmpty()) {
			cerr << "rm: Directory is not empty: " << filename << "\n";
			return false;
		}
		p = env->wd;
		do {
			if (p == item) {
				cerr << "rm: Cannot remove directory in use: " << filename << "\n";
				return false;
			}
			p = p->getParent();
		} while (p != nullptr);
	}
	Directory *parent = item->getParent();
	parent->remove(item);
	delete item;
	return true;
}
