#include "mv.h"
#include <iostream>

using namespace std;

bool mv(Env *env, Stmt *stmt)
{
	string source = stmt->getNextArg();
	if (source.empty()) {
		cerr << "use: mv source dist\n";
		return false;
	}

	string dist = stmt->getNextArg();
	if (dist.empty()) {
		cerr << "use: mv source dist\n";
		return false;
	}
	Node *sourceNode = env->wd->findByPath(source);
	if (sourceNode == nullptr) {
		cerr << "mv: Cannot move: No such file or directory: " << source << endl;
		return false;
	}
	string newName = sourceNode->name;
	Node *distParentNode = env->wd->findByPath(dist);
	if (distParentNode == nullptr) {
		newName = Node::basename(dist);
		distParentNode = env->wd->findByPath(Node::dirname(dist));
	}
	if (distParentNode == nullptr) {
		cerr << "mv: Cannot move: No such file or directory: " << dist << endl;
		return false;
	}
	if (distParentNode->type != Node::Type::DIRECTORY) {
		cerr << "mv: Cannot move: Not a directory: " << dist << endl;
		return false;
	}

	Node *p = distParentNode;
	do {
		if (p == sourceNode) {
			cerr << "rm: Cannot move directory to it's child: " << source << "\n";
			return false;
		}
		p = p->getParent();
	} while (p != nullptr);

	Directory *distDir = (Directory *)distParentNode;
	Node *distNode = distDir->findByName(newName);
	if (distNode != nullptr) {
		cerr << "mv: Cannot move: File exists: " << dist << endl;
		return false;
	}
	sourceNode->getParent()->remove(sourceNode);
	sourceNode->setParent(distDir);
	sourceNode->setName(newName);
	distDir->addChild(sourceNode);
	return true;
}
