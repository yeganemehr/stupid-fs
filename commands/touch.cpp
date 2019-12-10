#include <iostream>
#include "touch.h"
#include "File.h"

using namespace std;

bool touch(Env *env, Stmt *stmt)
{
	string filename = stmt->getNextArg();
	if (filename.empty()) {
		cerr << "use: touch filename\n";
		return false;
	}
	string dirname = Node::dirname(filename);
	string basename = Node::basename(filename);
	Node *parent = env->wd->findByPath(dirname);
	if (parent == nullptr) {
		cerr << "touch: cannot touch \"" << filename << "\": No such file or directory\n";
		return false;
	}
	if (parent->type != Node::Type::DIRECTORY) {
		cerr << "mkdir: touch \"" << filename << "\": Not a directory\n";
		return false;
	}
	Directory *dir = (Directory *)parent;
	Node *newItem = dir->findByPath(basename);
	if (newItem != nullptr) {
		return false;
	}
	File *newFile = new File(basename);
	dir->addChild(newFile);
	return true;
}
