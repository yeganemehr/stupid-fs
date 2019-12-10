#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <cstdio>
#include "Directory.h"
#include "File.h"

using namespace std;

class Database
{
	public:
		Database(const string &file);
		Directory *load() const;
		void save(Directory *root) const;
	private:
		string file;
		Node::Type loadType(FILE *fd) const;
		string loadName(FILE *fd) const;
		Directory *loadDirectory(FILE *fd) const;
		File *loadFile(FILE *fd) const;
		void save(Node *node, FILE *fd) const;
		void save(Directory *node, FILE *fd) const;
		void save(File *node, FILE *fd) const;
};

#endif // DATABASE_H
