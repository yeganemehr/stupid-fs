#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;
class Directory;
class Node
{
	public:
		enum Type {
			FILE,
			DIRECTORY
		};
		static string basename(string path);
		static string dirname(string path);
		Node(const string &name, Type type);
		string getName() const;
		void setName(const string &name);
		string getDirname() const;
		void setParent(Directory *parent);
		Directory *getParent() const;
		string getPath() const;
		string getPath(Directory *upto) const;


		string name;
		Directory *parent = nullptr;
		Type type;
};

#endif // NODE_H
