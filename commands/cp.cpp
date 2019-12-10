#include "cp.h"
#include "File.h"
#include <iostream>

using namespace std;

char askForOverwrite(const string &path) {
	do {
		cout << "cp: overwrite : " << path << "? [y=Yes, n=No, a=All]: ";
		string str;
		std::getline(std::cin, str);
		if (str == "n" || str == "y" || str == "a") {
			return str.at(0);
		}
	} while(true);
}

unsigned char copyNode(Node *node, const string &relativePath, Directory *distDir, bool &overwriteAll) {
	Node *pathInDist = distDir->findByPath(relativePath);
	if (pathInDist != nullptr) {
		if (node->type != pathInDist->type) {
			cerr << "cp: cannot overwrite directory '" << relativePath << "' with non-directory\n";
			return 1;
		}
		char overwrite = overwriteAll ? 'y' : askForOverwrite(relativePath);
		if (overwrite == 'n') {
			cerr << "cancelled\n";
			return 1;
		}
		if (overwrite == 'a') {
			overwriteAll = true;
		}
	} else {
		string basename = Node::basename(relativePath);
		string dirname = Node::dirname(relativePath);
		Directory *parent = (Directory *)distDir->findByPath(dirname);
		Node *newNode;
		if (node->type == Node::Type::DIRECTORY) {
			newNode = new Directory(basename);
		} else if (node->type == Node::Type::FILE) {
			newNode = new File(basename);
		}
		newNode->setParent(parent);
		parent->addChild(newNode);
	}
	return 0;
}

bool cp(Env *env, Stmt *stmt)
{
	string source = stmt->getNextArg();
	if (source.empty()) {
		cerr << "use: cp source dist\n";
		return false;
	}

	string dist = stmt->getNextArg();
	if (dist.empty()) {
		cerr << "use: cp source dist\n";
		return false;
	}
	Node *sourceNode = env->wd->findByPath(source);
	if (sourceNode == nullptr) {
		cerr << "cp: Cannot move: No such file or directory: " << source << endl;
		return false;
	}
	string newName = sourceNode->name;
	Node *distParentNode = env->wd->findByPath(dist);
	if (distParentNode == nullptr) {
		newName = Node::basename(dist);
		distParentNode = env->wd->findByPath(Node::dirname(dist));
	}
	if (distParentNode == nullptr) {
		cerr << "cp: Cannot copy: No such file or directory: " << dist << endl;
		return false;
	}
	if (distParentNode->type != Node::Type::DIRECTORY) {
		cerr << "cp: omitting directory: " << dist << endl;
		return false;
	}

	Directory *distDir = (Directory *)distParentNode;
	bool overwriteAll = false;
	bool change = false;
	if (copyNode(sourceNode, newName, distDir, overwriteAll) != 0) {
		return change;
	}
	change = true;
	if (sourceNode->type == Node::Type::DIRECTORY) {
		Directory *srcDir = (Directory *)sourceNode;
		for (Node *node : srcDir->getChildrenRecursive()) {
			if (copyNode(node, newName + "/" + node->getPath(srcDir), distDir, overwriteAll) != 0) {
				return change;
			}
			change = true;
		}
	}
	return change;

}
