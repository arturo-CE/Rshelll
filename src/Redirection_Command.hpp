#pragma once
#include <iostream>
#include "Base_Command.hpp"

using namespace std;

class Redirection_Command{
	public:
	virtual char* getArg()=0;
	virtual bool execute(Redirection_Command*, int*)=0;


};
