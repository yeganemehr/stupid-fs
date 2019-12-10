#include "mkdir.h"
#include <iostream>

using namespace std;

bool mkdir(Env *env, Stmt *stmt)
{
	string filename = stmt->getNextArg();
	if (filename.empty()) {
		cerr << "use: mkdir filename\n";
		return false;
	}
	string dirname = Node::dirname(filename);
	string basename = Node::basename(filename);
	Node *parent = env->wd->findByPath(dirname);
	if (parent == nullptr) {
		cerr << "mkdir: cannot create directory \"" << filename << "\": No such file or directory\n";
		return false;
	}
	if (parent->type != Node::Type::DIRECTORY) {
		cerr << "mkdir: cannot create directory \"" << filename << "\": No a directory\n";
		return false;
	}
	Directory *dir = (Directory *)parent;
	Node *newItem = dir->findByPath(basename);
	if (newItem != nullptr) {
		cerr << "mkdir: cannot create directory \"" << filename << "\": File exists\n";
		return false;
	}
	Directory *newDir = new Directory(basename);
	dir->addChild(newDir);
	return true;
}
