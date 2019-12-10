#include "Directory.h"

Directory::Directory(const string &name):
	Node(name, Node::DIRECTORY)
{
}

Directory::~Directory()
{
	for (Node *child : children) {
		delete child;
	}
}

void Directory::addChild(Node *child)
{
	child->parent = this;
	children.push_back(child);
}

void Directory::remove(const Node *child)
{
	vector<Node *>::iterator it = children.begin();
	for (; it != children.end(); ++it) {
		if (*it == child) {
			children.erase(it);
			break;
		}
	}
}

vector<Node *> Directory::getChildren() const
{
	return children;
}

bool Directory::isEmpty() const
{
	return this->children.empty();
}

vector<Node *> Directory::getChildrenRecursive() const
{
	vector<Node *> result;
	for (Node *node : this->children) {
		result.push_back(node);
		if (node->type == Node::Type::DIRECTORY) {
			Directory *nodeDir = (Directory *) node;
			for (Node *grandChild : nodeDir->getChildrenRecursive()) {
				result.push_back(grandChild);
			}
		}
	}
	return result;
}

Node *Directory::findByPath(string path)
{
	while (*(path.end()) == '/') {
		path = path.substr(0, path.length() - 1);
	}
	size_t slash = path.find('/');
	if (slash == 0) {
		if (this->parent != nullptr) {
			return this->parent->findByPath(path);
		} else {
			path = path.substr(1);
			slash = path.find('/');
		}
	}
	Node *found = nullptr;
	string childName = path.substr(0, slash);
	if (childName == "..") {
		found = this->parent;
	} else {
		found = findByName(childName);
	}
	if (!found) {
		return nullptr;
	}
	if (slash == string::npos) {
		return found;
	}
	if (found->type == Node::DIRECTORY) {
		Directory *dir = (Directory *)found;
		return dir->findByPath(path.substr(slash + 1));
	}

	if (slash != string::npos && path.length() > slash) { // file in file
		return nullptr;
	}
	return found;
}

Node *Directory::findByName(const string &name)
{
	if (name.empty() || name == ".") {
		return this;
	}
	for (Node *child : children) {
		if (child->name == name) {
			return child;
		}
	}
	return nullptr;
}
