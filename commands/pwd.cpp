#include "pwd.h"
#include <iostream>

using namespace std;

void pwd(Env *env, Stmt *)
{
	cout << env->wd->getPath() << endl;
}
