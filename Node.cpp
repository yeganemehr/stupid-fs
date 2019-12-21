#include "Node.h"
#include "Directory.h"
#include <algorithm>

string Node::basename(string path)
{
	path.erase(std::max((size_t) 1, path.find_last_not_of('/') + 1));
	size_t lastSlash = path.find_last_of('/');
	if (lastSlash != string::npos) {
		return path.substr(lastSlash + 1);
	}
	return path;
}

string Node::dirname(string path)
{
	path.erase(std::max((size_t) 1, path.find_last_not_of('/') + 1));
	size_t lastSlash = path.find_last_of('/');
	if (lastSlash != string::npos) {
		return path.substr(0, lastSlash);
	}
	return "";
}

Node::Node(const string &name, Type type)
{
	this->name = name;
	this->type = type;
}

string Node::getName() const
{
	return name;
}

void Node::setName(const string &name)
{
	this->name = name;
}

string Node::getDirname() const
{
	return (this->parent != nullptr) ? this->parent->getPath() : "";
}

void Node::setParent(Directory *parent)
{
	this->parent = parent;
}

Directory *Node::getParent() const
{
	return parent;
}

string Node::getPath() const
{
	return getPath(nullptr);
}

string Node::getPath(Directory *upto) const
{
	if (this == upto) {
		return "";
	}
	if (this->parent == nullptr) {
		return "/";
	}
	string path = this->parent->getPath(upto);
	if (!path.empty() && path.at(path.length() - 1) != '/') {
		path.insert(path.length(), 1, '/');
	}
	path.append(this->name);
	return path;
}
