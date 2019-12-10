#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <vector>
#include "Node.h"

using namespace std;

class Directory : public Node
{
	public:
		Directory(const string &name);
		~Directory();
		void addChild(Node *child);
		Node *findByPath(string path);
		Node *findByName(const string &name);
		void remove(const Node *child);
		vector<Node *> getChildren() const;
		bool isEmpty() const;
		vector<Node *> getChildrenRecursive() const;
	private:
		vector<Node *> children;
};

#endif // DIRECTORY_H
