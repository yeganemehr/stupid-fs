#include "ls.h"
#include <iostream>

using namespace std;

void ls(Env *env, Stmt *)
{
	vector<Node *> children = env->wd->getChildren();
	for (const Node *node : children) {
		if (node->type == Node::DIRECTORY) {
			cout << node->getName() << "/" << endl;
		}
	}
	for (const Node *node : children) {
		if (node->type == Node::FILE) {
			cout << node->getName() << endl;
		}
	}
}
