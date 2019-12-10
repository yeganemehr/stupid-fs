#include <iostream>
#include <cpio.h>
#include "Stmt.h"
#include "Env.h"
#include "Database.h"
#include "commands/touch.h"
#include "commands/rm.h"
#include "commands/cp.h"
#include "commands/mv.h"
#include "commands/ls.h"
#include "commands/cd.h"
#include "commands/mkdir.h"
#include "commands/rmdir.h"
#include "commands/pwd.h"

using namespace std;


int main(int , char **)
{
	Database db("db.dat");
	Directory *root = db.load();
	if (root == nullptr){
		root = new Directory("");
	}
	Env env(root);
	while(true) {
		Stmt stmt;
		cout << env.wd->getPath() << "# ";
		std::getline(std::cin, stmt.str);
		string cmd = stmt.getNextArg();
		bool change = false;
		if (cmd == "touch"){
			change = touch(&env, &stmt);
		} else if (cmd == "rm") {
			change = rm(&env, &stmt);
		} else if (cmd == "cp") {
			change = cp(&env, &stmt);
		} else if (cmd == "mv") {
			change = mv(&env, &stmt);
		} else if (cmd == "ls") {
			ls(&env, &stmt);
		} else if (cmd == "cd") {
			cd(&env, &stmt);
		} else if (cmd == "mkdir") {
			change = mkdir(&env, &stmt);
		} else if (cmd == "rmdir") {
			change = rmdir(&env, &stmt);
		} else if (cmd == "pwd") {
			pwd(&env, &stmt);
		} else if (cmd == "exit") {
			break;
		} else {
			cerr << "Unkown command: " << cmd;
		}
		if (change) {
			db.save(root);
		}
	}
	return 0;
}

