#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "Base_Command.hpp"

using namespace std;
class Execute_Strategy{

private: 

	Base_Command* foo;

public:

	Execute_Strategy(Base_Command* bar) : foo(bar){}
	Execute_Strategy(){}
	virtual ~Execute_Strategy(){}

	bool executeTest();
  
 };
