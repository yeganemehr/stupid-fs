#include "Database.h"

Database::Database(const string &file)
{
	this->file = file;
}

Directory *Database::load() const
{
	FILE *fd = fopen(this->file.c_str(), "rb");
	if (!fd){
		return nullptr;
	}
	if (loadType(fd) != Node::Type::DIRECTORY) {
		fclose(fd);
		return nullptr;
	}
	return loadDirectory(fd);
}

void Database::save(Directory *root) const
{
	FILE *fd = fopen(this->file.c_str(), "wb");
	save(root, fd);
	fclose(fd);
}

Node::Type Database::loadType(FILE *fd) const
{
	unsigned char type;
	if (fread(&type, sizeof(unsigned char), 1, fd) != 1) {
		return (Node::Type)2;
	}
	return (Node::Type)type;
}

string Database::loadName(FILE *fd) const
{
	size_t size;
	if (fread(&size, sizeof(size_t), 1, fd) != 1) {
		return "";
	}
	char *name = new char[size + 1];
	fread(name, sizeof(char), size, fd);
	name[size] = '\0';
	return string(name);
}

Directory *Database::loadDirectory(FILE *fd) const
{
	string name = loadName(fd);
	Directory *node = new Directory(name);
	size_t children;
	if (fread(&children, sizeof(size_t), 1, fd) != 1) {
		children = 0;
	}
	for (size_t x = 0;x < children; x++) {
		Node::Type type = loadType(fd);
		Node *child;
		if (type == Node::Type::FILE) {
			child = loadFile(fd);
		} else if (type == Node::Type::DIRECTORY) {
			child = loadDirectory(fd);
		}
		node->addChild(child);
	}
	return node;
}

File *Database::loadFile(FILE *fd) const
{
	string name = loadName(fd);
	File *node = new File(name);
	return node;
}


void Database::save(Node *node, FILE *fd) const
{
	unsigned char type = node->type;
	fwrite(&type, sizeof(unsigned char), 1, fd);
	size_t size = node->name.length();
	fwrite(&size, sizeof(size_t), 1, fd);
	if (size) {
		fwrite(node->name.c_str(), sizeof(char), size, fd);
	}
}

void Database::save(Directory *node, FILE *fd) const
{
	save((Node *)node, fd);
	vector<Node *> children = node->getChildren();
	size_t size = children.size();
	fwrite(&size, sizeof(size_t), 1, fd);

	for (const Node *child : children) {
		if (child->type == Node::Type::FILE) {
			save((File *)child, fd);
		} else if (child->type == Node::Type::DIRECTORY) {
			save((Directory *)child, fd);
		}
	}
}

void Database::save(File *node, FILE *fd) const
{
	save((Node *)node, fd);
}

