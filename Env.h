#ifndef ENV_H
#define ENV_H

#include "Directory.h"

class Env
{
	public:
		Env(Directory *wd);

		Directory *wd;
};

#endif // ENV_H
